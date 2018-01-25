#include "l_puzzle.h"
#include "solver.h"

template <class T>
solver<T>::solver(T& _initial, T& _target){
  initial_state = _initial;
  target_state = _target;
  depth = 0;
  num_expanded = 0;
  delta_t = 0;
}


template <class T>
void solver<T>::dcbfs(){
  start_timer();

  std::map<T, T*> prev;
  visited.clear();

  std::vector<std::vector<T> > V(1);
  V[0].push_back(initial_state);
  prev[initial_state] = NULL;

  bool solved = initial_state.is_solved();

  int k = 0;
  while(!solved && !V[k].empty()){
    std::vector<T> depth_k;
    V.push_back(depth_k);

    for(auto& s:V[k]){
      visited[s] = true;

      std::list<T*> temp_successors;
      s.successors(temp_successors);

      for(auto& sp:temp_successors){
        if(!sp->deadlock() && !visited[*sp]){
          V[k+1].push_back(*sp);
          prev[*sp] = &s;
        }

        if(sp->is_solved()){
          solved = true;
          target_state = *sp;
          prev[target_state] = &s;
        }

        delete sp;
      }
    }

    ++k;
  }

  T* ptr = &target_state;
  while(ptr != NULL){
    solution.push_back(*ptr);
    ptr = prev[*ptr];
  }

  num_expanded = visited.size();
  stop_timer();
}


template <class T>
void solver<T>::bfs(){
  start_timer();

  std::map<T, T*> prev;
  visited.clear();

  std::vector<std::vector<T> > V(1);
  V[0].push_back(initial_state);
  prev[initial_state] = NULL;

  bool solved = initial_state.is_solved();

  int k = 0;
  while(!solved && !V[k].empty()){
    std::vector<T> depth_k;
    V.push_back(depth_k);

    for(auto& s:V[k]){
      visited[s] = true;

      std::list<T*> temp_successors;
      s.successors(temp_successors);

      for(auto& sp:temp_successors){
        if(!visited[*sp]){
          V[k+1].push_back(*sp);
          prev[*sp] = &s;
        }

        if(sp->is_solved()){
          solved = true;
          target_state = *sp;
          prev[target_state] = &s;
        }

        delete sp;
      }
    }

    ++k;
  }

  T* ptr = &target_state;
  while(ptr != NULL){
    solution.push_back(*ptr);
    ptr = prev[*ptr];
  }

  num_expanded = visited.size();
  stop_timer();
}

template <class T>
void solver<T>::pcdfs(){
  start_timer();
  num_expanded = 0;

  if(!(initial_state.is_solved()))
    dfs_recursion(initial_state, 1, 60); /* max depth assumed 50 */

  reverse(solution.begin(), solution.end());
  stop_timer();
}

template <class T>
void solver<T>::iddfs(){
  start_timer();

  bool solved = (initial_state.is_solved());
  num_expanded = 0;

  for(int i=1; !solved; ++i)
    solved = dfs_recursion(initial_state, 1, i);

  reverse(solution.begin(), solution.end());

  stop_timer();
}

template <class T>
bool solver<T>::dfs_recursion(T& node, int depth, int max_depth){
  if(depth > max_depth)
    return false;

  /* path checking */
  if(find(solution.begin(), solution.end(), node) != solution.end())
    return false;

  ++num_expanded;
  solution.push_back(node);

  list<T*> temp_successors;
  node.successors(temp_successors);

  bool solved = false;

  for(auto& sp:temp_successors){
    if(sp->is_solved()){
      solution.push_back(*sp);
      solved = true;
      break;
    }
    else if(dfs_recursion(*sp, depth+1, max_depth)){
      solved = true;
      break;
    }
  }

  for(auto& sp:temp_successors){
    delete sp;
  }

  if(!solved)
    solution.pop_back();

  return solved;
}


/* comparison functor for priority queue */
struct cmp
{
 template <class T>
	bool operator() (pair<T,int> &a, pair<T,int> &b)
	{
		return a.second > b.second;
	}
};

template <class T>
void solver<T>::a_star(int heuristic){
  start_timer();

  priority_queue<pair<T,int>, vector<pair<T,int>>, cmp> PQ;
  map<T, T> prev;
  map<T, int> f;
  visited.clear();

  f[initial_state] = 0;
  PQ.push(pair<T,int>(initial_state, 10000));

  T ptr;
  map<T, int> priority;

  while(!PQ.empty()){
    T s = PQ.top().first;
    int _pri = PQ.top().second;
    PQ.pop();

    /* https://stackoverflow.com/a/12691382 */
    /* For h=0, A* actually decays into Dijkstra's algorithm, and since
    Dijkstra's algorithm never needs to modify already "explored" node */
    /* bkz: deadlock checking Dijkstra's */

    if(visited[s] && priority[s] < _pri){
      continue;
    }

    visited[s] = true;

    //if(heuristic != 0){
    //    priority[s] = _pri;
    //}

    if(s.is_solved()){
      ptr = s;
      break;
    }

    std::list<T*> temp_successors;
    s.successors(temp_successors);

    for(auto& sp:temp_successors){
      int p, q;
      q = f[s] + 1;

      if(heuristic == 0){ // deadlock check
        p = q+sp->deadlock();
      }
      else if(heuristic == 1){ // manhattan distance
        p = q+sp->distance(0);
      }
      else if(heuristic == 2){ // euclidean distance
        p = q+sp->distance(1);
      }
      else if(heuristic == 3){ // manhattan + deadlock
        p = q+sp->deadlock()+sp->distance(0);
      }

      if(!visited[*sp] || p<priority[*sp]){
        prev[*sp] = s;
        f[*sp] = f[s] + 1;
        PQ.push(pair<T,int>(*sp, p));
        priority[*sp] = p;
      }

      delete sp;
    }
  }

  while(!(ptr == initial_state)){
    //ptr.print_puzzle();
    solution.push_back(ptr);
    ptr = prev[ptr];
  }

  solution.push_back(initial_state);

  num_expanded = visited.size();
  stop_timer();
}


template <class T>
void solver<T>::print_solution(){
  ofstream file;
  file.open("result.txt");

  file << delta_t << endl;
  file << depth << endl << endl;

  cout << delta_t << endl;
  cout << depth << endl << endl;

  for(int i=depth; i>0; --i){
    char a = 'e';
    if(solution[i].x0 == solution[i-1].x0 - 1)
      a = 'd';
    else if(solution[i].x0 == solution[i-1].x0 + 1)
      a = 'u';
    else if(solution[i].y0 == solution[i-1].y0 - 1)
      a = 'r';
    else if(solution[i].y0 == solution[i-1].y0 + 1)
      a = 'l';

    file << a << endl;

    cout << a << endl;
  }

  file.close();
}


template <class T>
void solver<T>::start_timer(){
  solution.clear();
  start_time = high_resolution_clock::now();
}

template <class T>
void solver<T>::stop_timer(){
  depth = solution.size() - 1;
  auto elapsed = high_resolution_clock::now() - start_time;
  delta_t = duration_cast<microseconds>(elapsed).count();
}


template class solver<sokoban>;

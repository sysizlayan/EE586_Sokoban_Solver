#ifndef SOLVER_H
#define SOLVER_H

#include <map> /* visited and previous data structures */
#include <vector> /* */
#include <list> /* successors */
#include <queue> /* priority queue */
#include <utility> /* <puzzle, priority> pair */
#include <algorithm> /* vector reverse */

#include <chrono> /* high resolution (us) timers */
#include <ctime>

using namespace std;
using namespace std::chrono;

template <class T>
class solver
{
  public:
    solver(T& _initial, T& _target); /* main constructor */
    void bfs(void); /* solve using bfs */
    void dcbfs(void); /* deadlock checking bfs */
    void pcdfs(void); /* solve using path checking dfs */
    void iddfs(void); /* solve using iterative deepening */
    void a_star(int heuristic = 0);
    void print_solution(void);

  private:
    T initial_state, target_state; /* end nodes of the problem */
    map<T, bool> visited;
    vector<T> solution; /* constructed solution */
    int depth, num_expanded;
    high_resolution_clock::time_point start_time;
    long long delta_t;

    bool dfs_recursion(T& node, int depth, int max_depth);
    void start_timer(void);
    void stop_timer(void);
};

#endif // SOLVER_H

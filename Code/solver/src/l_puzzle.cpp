#include "l_puzzle.h"
using namespace std;

sokoban::sokoban(int a, int b, char *data)
{
  A = a;
  B = b;
  puzzle_data = new char[A*B];

  if(data == NULL)
    return;

  for(int i=0; i<A; ++i)
  for(int j=0; j<B; ++j){
    puzzle_data[i*B+j] = data[i*B+j];

    if(data[i*B+j] == '@' || data[i*B+j] == '+'){
      x0 = i;
      y0 = j;
    }
  }
}

sokoban::sokoban(const sokoban& item)
{
  A = item.A;
  B = item.B;
  action = item.action;
  puzzle_data = new char[A*B];

  memcpy(puzzle_data, item.puzzle_data, A*B*sizeof(char));
  x0 = item.x0;
  y0 = item.y0;
}

sokoban& sokoban::operator=(const sokoban& rhs){
  delete puzzle_data;

  A = rhs.A;
  B = rhs.B;
  action = rhs.action;
  puzzle_data = new char[A*B];

  memcpy(puzzle_data, rhs.puzzle_data, A*B*sizeof(char));
  x0 = rhs.x0;
  y0 = rhs.y0;

  return *this;
}

sokoban::~sokoban(){
  delete puzzle_data;
}

bool sokoban::is_solved(){
  for(int i=0; i<A; ++i)
  for(int j=0; j<B; ++j)
    if(puzzle_data[i*B+j] == '$')
      return false;

  return true;
}

bool sokoban::move_up(){
  char *curr = puzzle_data + x0*B + y0;
  char *upper = curr - B;
  char *uup = upper - B;

  int temp = x0;
  smove(curr, upper, uup, x0-1, y0);
  action = 'u';

  return (x0 != temp);
}

bool sokoban::move_down(){
  char *curr = puzzle_data + x0*B + y0;
  char *upper = curr + B;
  char *uup = upper + B;

  int temp = x0;
  smove(curr, upper, uup, x0+1, y0);
  action = 'd';

  return (x0 != temp);
}

bool sokoban::move_left(){
  char *curr = puzzle_data + x0*B + y0;
  char *upper = curr - 1;
  char *uup = upper - 1;

  int temp = y0;
  smove(curr, upper, uup, x0, y0-1);
  action = 'l';

  return (y0 != temp);
}

bool sokoban::move_right(){
  char *curr = puzzle_data + x0*B + y0;
  char *upper = curr + 1;
  char *uup = upper + 1;

  int temp = y0;
  smove(curr, upper, uup, x0, y0+1);
  action = 'r';

  return (y0 != temp);
}

void sokoban::successors(std::list<sokoban*>& result){
  sokoban *temp;

  temp = new sokoban(*this);
  if(temp -> move_up())
    result.push_back(temp);
  else
    delete temp;

  temp = new sokoban(*this);
  if(temp -> move_down())
    result.push_back(temp);
  else
    delete temp;

  temp = new sokoban(*this);
  if(temp -> move_left())
    result.push_back(temp);
  else
    delete temp;

  temp = new sokoban(*this);
  if(temp -> move_right())
    result.push_back(temp);
  else
    delete temp;
}

bool sokoban::operator<(const sokoban& rhs) const{
  for(int i=0; i<A; ++i)
  for(int j=0; j<B; ++j){
   if(puzzle_data[i*B+j] < rhs.puzzle_data[i*B+j])
    return true;
   else if(puzzle_data[i*B+j] > rhs.puzzle_data[i*B+j])
    return false;
  }

  return false;
}

bool sokoban::operator==(const sokoban& rhs) const{
  for(int i=0; i<A; ++i)
  for(int j=0; j<B; ++j){
   if(puzzle_data[i*B+j] != rhs.puzzle_data[i*B+j])
    return false;
  }

  if(action != rhs.action)
    return false;

  return true;
}

void sokoban::load(string path){
  ifstream file;
  file.open(path);

  file >> A >> B;
  puzzle_data = new char[A*B];

  char dummy;
  file >> noskipws >> dummy;

  for(int i=0; i<A; ++i){
    for(int j=0; j<B; ++j){
      file >> noskipws >> puzzle_data[i*B+j];

      if(puzzle_data[i*B+j] == '@' || puzzle_data[i*B+j] == '+'){
        x0 = i;
        y0 = j;
      }
    }
    file >> noskipws >> dummy;
  }

//  cout << "Initial state: " << endl;
//  print_puzzle();
  file.close();
}

void sokoban::print_puzzle(){
  for(int i=0; i<A; ++i){
    for(int j=0; j<B; ++j)
      cout << puzzle_data[i*B+j];
    cout << endl;
  }
  cout << action << endl;
}





void sokoban::smove(char*curr, char *upper, char *uup, int xn, int yn){
  if(*upper == ' '){ /* empty */
    if(*curr == '@'){ /* bizim adam */
      *upper = '@';
      *curr = ' ';
      x0 = xn;
      y0 = yn;
    }
    else if(*curr == '+'){ /* adam + target */
      *upper = '@';
      *curr = '.';
      x0 = xn;
      y0 = yn;
    }
  }
  else if(*upper == '.'){ /* target */
    if(*curr == '@'){
      *upper = '+';
      *curr = ' ';
      x0 = xn;
      y0 = yn;
    }
    else if(*curr == '+'){
      *upper = '+';
      *curr = '.';
      x0 = xn;
      y0 = yn;
    }
  }
  else if(*upper == '$'){ /* box */
    if(*uup == ' '){
      if(*curr == '@'){
        *uup = '$';
        *upper = '@';
        *curr = ' ';
        x0 = xn;
        y0 = yn;
      }
      else if(*curr == '+'){
        *uup = '$';
        *upper = '@';
        *curr = '.';
        x0 = xn;
        y0 = yn;
      }
    }
    else if(*uup == '.'){
      if(*curr == '@'){
        *uup = '*';
        *upper = '@';
        *curr = ' ';
        x0 = xn;
        y0 = yn;
      }
      else if(*curr == '+'){
        *uup = '*';
        *upper = '@';
        *curr = '.';
        x0 = xn;
        y0 = yn;
      }
    }
  }
  else if(*upper == '*'){ /* box in target */
    if(*uup == ' '){
      if(*curr == '@'){
        *uup = '$';
        *upper = '+';
        *curr = ' ';
        x0 = xn;
        y0 = yn;
      }
      else if(*curr == '+'){
        *uup = '$';
        *upper = '+';
        *curr = '.';
        x0 = xn;
        y0 = yn;
      }
    }
    else if(*uup == '.'){
      if(*curr == '@'){
        *uup = '*';
        *upper = '+';
        *curr = ' ';
        x0 = xn;
        y0 = yn;
      }
      else if(*curr == '+'){
        *uup = '*';
        *upper = '+';
        *curr = '.';
        x0 = xn;
        y0 = yn;
      }
    }
  }
}

char sokoban::get_action(){
  return action;
}

int sokoban::deadlock(){
  char *curr = puzzle_data + x0*B + y0;
  char *up, *uup, *ul, *ur;

  if(action == 'l'){
    up = curr - 1;
    uup = up - 1;
    ul = up + B;
    ur = up - B;
  }
  else if(action == 'r'){
    up = curr + 1;
    uup = up + 1;
    ul = up + B;
    ur = up - B;
  }
  else if(action == 'u'){
    up = curr - B;
    uup = up - B;
    ul = up + 1;
    ur = up - 1;
  }
  else if(action == 'd'){
    up = curr + B;
    uup = up + B;
    ul = up + 1;
    ur = up - 1;
  }

  if(*up != '$'){
    return 0;
  }
  else if(*uup != '#'){
    return 0;
  }
  else if(*ul != '#' && *ur != '#'){
    return 0;
  }
  else{
    return 1000000;
  }
}


int manhattan(int dx, int dy){
  return abs(dx) + abs(dy);
}

int euclidean(int dx, int dy){
  return sqrt(dx*dx + dy*dy);
}

int sokoban::distance(int method){
  int x_target[A*B], y_target[A*B];
  int x_box[A*B], y_box[A*B];
  int num_target = 0;
  int num_box = 0;

  for(int i=0; i<A; ++i)
  for(int j=0; j<B; ++j){
    if(puzzle_data[i*B+j] == '.' || puzzle_data[i*B+j] == '*' || puzzle_data[i*B+j] == '+'){
      x_target[num_target] = i;
      y_target[num_target] = j;
      ++num_target;
    }
    if(puzzle_data[i*B+j] == '$'){
      x_box[num_box] = i;
      y_box[num_box] = j;
      ++num_box;
    }
  }

  int total_dist = 0;

  for(int i=0; i<num_box; ++i){
    int min_dist = 1000000;

    for(int j=0; j<num_target; ++j){
      int dx = x_box[i] - x_target[j];
      int dy = y_box[i] - y_target[j];
      int dist;

      if(method == 0){
        dist = manhattan(dx, dy);
      }
      else if(method == 1){
        dist = euclidean(dx, dy);
      }

      if(dist < min_dist){
        min_dist = dist;
      }
    }

    total_dist += min_dist;
  }

  return total_dist;
}


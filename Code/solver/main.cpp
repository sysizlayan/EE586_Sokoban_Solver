#include <iostream>
#include "l_puzzle.h"
#include "solver.h"

using namespace std;

int main(int argc, char **argv)
{
  if(argc < 3){
    cout << "Wrong usage" << endl;
    cout << "Use as ee586.exe PATH ALGO" << endl;
    cout << "where PATH is the path to the puzzle" << endl;
    cout << "and ALGO is the search algorithm:" << endl;
    cout << "e: BFS" << endl;
    cout << "r: IDDFS" << endl;
    cout << "y: A* with Deadlock Check" << endl;
    cout << "u: A* with Manhattan Distance" << endl;
    cout << "i: A* with Euclidean Distance" << endl;
    cout << "o: A* with Deadlock Check + Manhattan" << endl;
    cout << "p: Deadlock Checking BFS" << endl;
    return -1;
  }

  sokoban s;
  s.load(string(argv[1]));  /* initial puzzle state */
  solver<sokoban> ss(s, s); /* initialize solver class */

  if(*argv[2] == 'e'){  /* solve using bfs */
    ss.bfs();           /* generate the output */
    ss.print_solution();/* print into result.txt */
  }
  else if(*argv[2] == 't'){ /* iddfs */
    ss.iddfs();
    ss.print_solution();
  }
  else if(*argv[2] == 'y'){
    ss.a_star(0); /* deadlock */
    ss.print_solution();
  }
  else if(*argv[2] == 'u'){
    ss.a_star(1); /* manhattan distance */
    ss.print_solution();
  }
  else if(*argv[2] == 'i'){
    ss.a_star(2); /* euclidean distance */
    ss.print_solution();
  }
  else if(*argv[2] == 'o'){
    ss.a_star(3); /* manhattan+deadlock */
    ss.print_solution();
  }
  else if(*argv[2] == 'p'){
    ss.dcbfs(); /* deadlock checking bfs */
    ss.print_solution();
  }
}

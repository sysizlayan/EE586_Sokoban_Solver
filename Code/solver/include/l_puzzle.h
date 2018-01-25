#ifndef L_PUZZLE_H
#define L_PUZZLE_H

#include <iostream> /* NULL is defined in iostream */
#include <list> /* for reusable successors function */
#include <cstring> /* memcpy function */
#include <cmath> /* abs for manhattan distance */
#include <fstream> /* read from file */

using namespace std;

class sokoban
{
  public:
    sokoban(int a=0, int b=0, char *data=NULL);  /* default constructor */
    sokoban(const sokoban& item);  /* copy constructor */
    sokoban& operator=(const sokoban& rhs); /* assignment operator */
    ~sokoban();
    bool operator<(const sokoban& rhs) const; /* comparison operators */
    bool operator==(const sokoban& rhs) const;
    void print_puzzle(void);  /* print puzzle state */
    bool move_up(void);     /* move the empty square */
    bool move_down(void);
    bool move_left(void);
    bool move_right(void);
    void successors(list<sokoban*>& result);  /* the (up to four) successors */
    bool is_solved();
    int deadlock();
    int distance(int method);
    void load(string path);
    char get_action(void);


    int x0, y0;       /* position of the empty square */ /* were private */
  private:
    void smove(char*c, char*u, char*uu, int xn, int yn);
    char *puzzle_data;
    int A, B; /* size of the puzzle */
    char action;
};

#endif // L_PUZZLE_H

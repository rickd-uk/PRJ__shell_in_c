#include <ncurses.h>
#include <stdio.h>

int main() {
  initscr();
  raw();
  noecho();

  printw("Test");
  int ch = getch();

  refresh();
  endwin();

  return 0;
}

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// macro to convert a char to its ctrl-key equivalent
#define ctrl(x) ((x) & 0x1f)

int main() {
  initscr(); // initialize ncurses screen
  raw();     // disable line buffering
  noecho();  // disable automatic encoding of characters

  int ch;
  bool QUIT = false;

  char command[1024] = {0}; // buffer to store a command
  size_t command_s = 0;     // current size of command

  size_t line = 0;

  while (!QUIT) {
    mvprintw(line, 0, "shell $: ");               // display shell prompt
    mvprintw(line, sizeof("shell $: "), command); // print current command
    ch = getch();
    switch (ch) {
    case ctrl('q'): // ctrl+q  to quit
      QUIT = true;
      break;
    case 10:    // press enter for new line
      line++;
      memset(command, 0, sizeof(char) * command_s);
      command_s = 0;
      break;
    default:
      // add char to command buffer
      command[command_s++] = ch;
      break;
    }
  }

  refresh();
  endwin(); // restore normal terminal behavior

  return 0;
}

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// macro to convert a char to its ctrl-key equivalent
#define ctrl(x) ((x) & 0x1f)
#define SHELL_PROMPT "$: "
#define ENTER 10
#define DATA_START_CAPACITY 128

#define ASSERT(cond, ...)                                                      \
  do {                                                                         \
    if (!(cond)) {                                                             \
      endwin();                                                                \
      fprintf(stderr, "%s:$d: ASSERTION FAILED: ", __FILE__, __LINE__);        \
      fprintf(stderr, __VA_ARGS__);                                            \
      fprintf(stderr, "\n");                                                   \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)

#define DA_APPEND(da, item)                                                    \
  do {                                                                         \
    if ((da)->count >= (da)->capacity) {                                       \
      (da)->capacity =                                                         \
          (da)->capacity == 0 ? DATA_START_CAPACITY : (da)->capacity * 2;      \
      void *new = calloc(((da)->capacity + 1), sizeof(*(da)->data));           \
      ASSERT(new, "ran out of ram!!");                                         \
      memcpy(new, (da)->data, (da)->count);                                    \
      free((da)->data);                                                        \
      (da)->data = new;                                                        \
    }                                                                          \
    (da)->data[(da)->count++] = (item);                                        \
  } while (0)

typedef struct {
  char *data;
  size_t count;
  size_t capacity;
} String;

typedef struct {
  String *data;
  size_t count;
  size_t capacity;
} Strings;

int main() {
  initscr(); // initialize ncurses screen
  raw();     // disable line buffering
  noecho();  // disable automatic encoding of characters

  int ch;
  bool QUIT = false;

  String command = {0}; // buffer to store a command
  Strings command_his = {0};

  size_t line = 0;

  while (!QUIT) {
    mvprintw(line, 0, SHELL_PROMPT); // display shell prompt
    mvprintw(line, sizeof(SHELL_PROMPT) - 1, "%.*s", (int)command.count,
             command.data); // print current command
    ch = getch();
    switch (ch) {
    case ctrl('q'): // ctrl+q  to quit
      QUIT = true;
      break;
    case ENTER: // press enter for new line
      line++;
      DA_APPEND(&command_his, command);
      command = (String){0};
      break;
    default:
      // add char to command buffer
      DA_APPEND(&command, ch);
      break;
    }
  }

  refresh();
  endwin(); // restore normal terminal behavior
  for (size_t i = 0; i < command_his.count; i++) {
    printf("%.*s\n", (int)command_his.data[i].count, command_his.data[i].data);
    free(command_his.data[i].data);
  }
  return 0;
}

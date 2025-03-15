#include <ncurses.h>
#include <string.h>

#define VALIDATE(ch) (ch >= 32 /* space */ && ch <= 126 /* ~ */)

int main(void) {
  initscr();
  clear();
  // cbreak();
  raw();
  keypad(stdscr, TRUE);
  box(stdscr, 0, 0);
  noecho();
  curs_set(0);
  nodelay(stdscr, true);

  start_color();
  use_default_colors();
  init_pair(1, COLOR_YELLOW, -1);
  init_pair(2, COLOR_GREEN, -1);
  init_pair(3, COLOR_RED, -1);

  const char *target = "hello world";
  // char* input = (char*)malloc(strlen(target) + 1);

  int current = 0;
  int x = (COLS - (int)strlen(target)) / 2;

  attron(COLOR_PAIR(1));
  mvprintw(LINES / 2, x, "%s", target);
  attroff(COLOR_PAIR(1));

  move(LINES / 2, x);
  while (current < (int)strlen(target)) {
    int ch = getch();

    if (ch == 3) // Control-C
      break;

    if (ch == KEY_BACKSPACE) {
      current--;
      mvchgat(LINES / 2, x + current, 1, A_NORMAL, 1, NULL);
    }

    if (!VALIDATE(ch))
      continue;

    if (ch == target[current]) {
      mvchgat(LINES / 2, x + current, 1, A_NORMAL, 2, NULL);
      current++;
      move(LINES / 2, x + current);
    } else {
      mvchgat(LINES / 2, x + current, 1, A_NORMAL, 3, NULL);
      current++;
    }
  }

  endwin();
}

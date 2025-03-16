#include <ncurses.h>
#include "taipo.h"
#include <unistd.h>

#define VALIDATE(ch) (ch >= 32 /* space */ && ch <= 126 /* ~ */)

int main(void) {

  // init app
  Taipo *taipo = init_taipo();

  // int x = (COLS - (int)strlen(target)) / 2;
  //
  // attron(COLOR_PAIR(1));
  // // print_with_font_size(target, 15);
  // mvprintw(LINES / 2, x, "%s", target);
  // attroff(COLOR_PAIR(1));
  //
  // move(LINES / 2, x);
  // while (current < (int)strlen(target)) {
  //   int ch = getch();
  //
  //   if (ch >= 0)
  //     mvprintw(0, 0, "[ %d - %s ]", ch, keyname(ch));
  //
  //   if (ch == 3) // Control-C
  //     break;
  //
  //   if (ch == KEY_BACKSPACE) {
  //     current--;
  //     mvchgat(LINES / 2, x + current, 1, A_NORMAL, 1, NULL);
  //   }
  //
  //   if (!VALIDATE(ch))
  //     continue;
  //
  //   if (ch == target[current]) {
  //     mvchgat(LINES / 2, x + current, 1, A_NORMAL, 2, NULL);
  //     current++;
  //     move(LINES / 2, x + current);
  //   } else {
  //     mvchgat(LINES / 2, x + current, 1, A_NORMAL, 3, NULL);
  //     current++;
  //   }
  // }

  int ch = 0;
  while ((ch = getch()) != 'q') {
    usleep(1000);
  }

  free_taipo(taipo);

}

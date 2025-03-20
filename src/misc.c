#include "misc.h"
#include "events.h"
#include <ncurses.h>
#include <time.h>

extern Game_event event;

double get_seconds(void) {

  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);

  return (ts.tv_sec) + (ts.tv_nsec / 1000000000.0);
}

void show_end_screen(Hud *hud) {
  clear();

  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  // make a box in the middle
  WINDOW *win = newwin(7, 30, max_y / 2 - 2, max_x / 2 - 15);
  box(win, 0, 0);

  double time = get_seconds() - hud->time;
  mvwprintw(win, 1, 1, "WPM: %.2f", (hud->correct_words / (time / 60.0)));
  mvwprintw(win, 2, 1, "Correct: %d", hud->correct_words);
  mvwprintw(win, 3, 1, "Incorrect: %d", hud->incorrect_words);
  mvwprintw(win, 4, 1, "Time: %.1f", time);
  mvwprintw(win, 5, 1, "Press any key to exit");

  wrefresh(win);
  refresh();
  nodelay(stdscr, FALSE);
  getch();
  event |= END_GAME;
}

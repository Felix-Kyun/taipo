#include "hud.h"
#include "misc.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

Hud *hud_init(void) {
  Hud *hud = (Hud *)malloc(sizeof(Hud));
  hud->x = 0;
  hud->y = 0;
  hud->correct_words = 0;
  hud->incorrect_words = 0;
  hud->time = get_seconds();

  getmaxyx(stdscr, hud->y, hud->x);

  return hud;
}


void render_hud(Hud *hud) {
  double time = get_seconds() - hud->time;
  int current_word = hud->correct_words + hud->incorrect_words;
  double wpm = (hud->correct_words / (time / 60.0));

  mvprintw(hud->y * .35, (hud->x - 38) / 2,  "WPM: %.2f Progress: %i / 10 Time: %.1f", wpm, current_word, time);
}
void hud_correct(Hud *hud) { hud->correct_words++; }
void hud_incorrect(Hud *hud) { hud->incorrect_words++; }
void hud_update_time(Hud *hud) { hud->time = get_seconds(); }
void hud_free(Hud *hud) { free(hud); }

#include "hud.h"
#include "misc.h"
#include <ncurses.h>
#include <stdlib.h>

Hud *hud_init(void) {
  Hud *hud = (Hud *)malloc(sizeof(Hud));
  hud->x = 0;
  hud->y = 0;
  hud->correct_words = 0;
  hud->incorrect_words = 0;
  hud->time = get_seconds();

  return hud;
}

void hud_update(Hud *hud, int max_y, int max_x) {
  hud->x = max_x;
  hud->y = max_y;
}

void render_hud(Hud *hud) {
  mvprintw(2, 2, "Correct: %d", hud->correct_words);
  mvprintw(3, 2, "Incorrect: %d", hud->incorrect_words);
  mvprintw(4, 2, "Time: %f", get_seconds() - hud->time);
}

void hud_correct(Hud *hud) { hud->correct_words++; }
void hud_incorrect(Hud *hud) { hud->incorrect_words++; }
void hud_update_time(Hud *hud) { hud->time = get_seconds(); }
void hud_free(Hud *hud) { free(hud); }

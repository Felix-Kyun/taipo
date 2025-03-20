#ifndef __TAIPO__HUD_H__
#define __TAIPO__HUD_H__

typedef struct Hud {

  // coordinates of the hud
  int x, y;

  // store correct words count
  int correct_words;

  // store incorrect words count
  int incorrect_words;

  // store start time
  double time;
} Hud;

Hud *hud_init(void);

void hud_update(Hud *hud, int max_y, int max_x);
void render_hud(Hud *hud);

void hud_correct(Hud *hud);

void hud_incorrect(Hud *hud);

void hud_update_time(Hud *hud);

void hud_free(Hud *hud);

#endif // __TAIPO__HUD_H__

#include <ncurses.h>
#include "taipo.h"
#include <unistd.h>

#define VALIDATE(ch) (ch >= 32 /* space */ && ch <= 126 /* ~ */)

int main(void) {

  // init app
  Taipo *taipo = init_taipo();

  while (taipo->current < taipo->gen->nwords) {
    int ch = getch();

    if (ch < 0) {
      usleep(1000); // sleep for 1ms
    } 

    if (ch == KEY_BACKSPACE) {
      decrement_word(taipo);
    } else if (VALIDATE(ch)) {
      increment_word(taipo, ch);
    }
  }

  int ch = 0;
  while ((ch = getch()) != 'q') {
    usleep(1000);
  }

  free_taipo(taipo);

}

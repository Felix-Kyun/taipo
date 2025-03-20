#ifndef __TAIPO__EVENTS_H__
#define __TAIPO__EVENTS_H__

typedef enum Game_event {
  UNKNOWN = 0,
  START = 1 << 0,
  END = 1 << 1,
  RENDER = 1 << 2,
  START_DONE = 1 << 3,
  END_GAME = 1 << 4
} Game_event;

#endif // __TAIPO__EVENTS_H__

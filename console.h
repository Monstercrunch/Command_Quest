#ifndef _SPEAKER_H_
#define _SPEAKER_H_

#include <iostream>
#include <sstream>
#include <ncursesw/ncurses.h>


class Console{
 public:
  Console();
  ~Console();
  void slow_print(WINDOW* win, std::string text, int margin_y, int margin_x);
  void draw_box(int margin_y, int margin_x);
  void init();
  int getH();
  int getW();
 private:
  int time, height, width;
  bool first_print;
};


#endif

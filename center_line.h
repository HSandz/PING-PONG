#ifndef PONG_CENTER_LINE_H
#define PONG_CENTER_LINE_H

#include <SDL.h>

namespace pong
{
  class CenterLine
  {
  public:
    CenterLine(int x, int y, int height, int widt);

    void onDraw(SDL_Renderer& renderer);
  private:
    SDL_Rect mRect;
  };
}

#endif

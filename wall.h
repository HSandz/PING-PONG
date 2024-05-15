#ifndef PONG_WALL_H
#define PONG_WALL_H

#include "aabb.h"

#include <SDL.h>

namespace pong
{
  class Wall
  {
  public:
    Wall(int x, int y, int width, int height);

    void onDraw(SDL_Renderer& renderer);

    const AABB& getAabb() const { return mAabb; }
          AABB& getAabb()       { return mAabb; }
  private:
    SDL_Rect mRect;
    AABB     mAabb;
  };
}

#endif

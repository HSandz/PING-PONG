#ifndef PONG_GOAL_H
#define PONG_GOAL_H

#include <SDL.h>

#include "aabb.h"

namespace pong
{
  class Goal final
  {
  public:
    Goal(int x, int y, int width, int height);

    void setX(int x) { mRect.x = x; mAabb.setCenterX(x + mAabb.getExtentX()); }
    void setY(int y) { mRect.y = y; mAabb.setCenterY(y + mAabb.getExtentY()); }

    const AABB& getAabb() const { return mAabb; }
          AABB& getAabb()       { return mAabb; }
  private:
    SDL_Rect  mRect;
    AABB      mAabb;
  };
}

#endif

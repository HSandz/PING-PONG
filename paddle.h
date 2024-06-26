#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H

#include <SDL.h>

#include "aabb.h"

namespace pong
{
  class CourtScene;
  class Paddle
  {
  public:
    /*! Vận tốc di chuyển của thanh */
    static const int VELOCITY;

    /*! Các hướng di chuyển của thanh */
    enum class Movement : int {
      UP    = -1,
      NONE  =  0,
      DOWN  =  1
    };

    Paddle(CourtScene& scene, int x, int y, int width, int height);

    void setTexture(const char* imagePath, SDL_Renderer* renderer);

    void onDraw(SDL_Renderer& renderer);
    void onUpdate();

    void setMovement(Movement movement) { mMovement = movement; }

    bool isMoving(Movement movement) const { return mMovement == movement;  }

    void setX(int x) { mRect.x = x; mAabb.setCenterX(x + mAabb.getExtentX()); }
    void setY(int y) { mRect.y = y; mAabb.setCenterY(y + mAabb.getExtentY()); }

    const AABB& getAabb() const { return mAabb; }
          AABB& getAabb()       { return mAabb; }
  private:
    CourtScene& mScene;
    SDL_Rect    mRect;
    Movement    mMovement;
    AABB        mAabb;
    SDL_Texture* mTexture;
  };
}

#endif

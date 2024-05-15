#ifndef PONG_BALL_H
#define PONG_BALL_H

#include "aabb.h"

#include <array>
#include <SDL.h>
#include <SDL_image.h>

namespace pong
{
  class CourtScene;
  class Ball
  {
  public:
    /** Vận tốc ban đầu của quả bóng */
    static const float INITIAL_VELOCITY;
    /** Lượng vận tốc thêm vào quả bóng khi chạm vào thanh */
    static const float VELOCITY_INCREASE;
    /** Vận tốc tối đa của quả bóng */
    static const float MAX_VELOCITY;

    Ball(CourtScene& scene, int x, int y, int width, int height);

    void setTexture(const std::string& path, SDL_Renderer* renderer);

    void onDraw(SDL_Renderer& renderer);
    void onUpdate();

    void setX(int x) { mRect.x = x; mAabb.setCenterX(x + mAabb.getExtentX()); }
    void setY(int y) { mRect.y = y; mAabb.setCenterY(y + mAabb.getExtentY()); }

    void setDirection(const std::array<float, 2>& direction) { mDirection = direction; }

    void setVelocity(float velocity) { mVelocity = velocity; }

    const AABB& getAabb() const { return mAabb; }
          AABB& getAabb()       { return mAabb; }
  private:
    CourtScene&           mScene;
    SDL_Rect              mRect;
    AABB                  mAabb;
    float                 mVelocity;
    std::array<float, 2>  mDirection;
    SDL_Texture*          mTexture;
  };
}

#endif

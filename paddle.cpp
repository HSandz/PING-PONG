#include "paddle.h"
#include "court_scene.h"

#include <iostream>
#include <SDL_image.h>

using namespace pong;

const int Paddle::VELOCITY = 8;

Paddle::Paddle(CourtScene& scene, int x, int y, int width, int height)
  : mScene(scene),
    mRect({ x, y, width, height }),
    mMovement(Movement::NONE)
{
  // Tính nửa chiều rộng và chiều dài
  auto halfWidth = (width / 2);
  auto halfHeight = (height / 2);

  // Khởi tạo một AABB cho đối tượng
  mAabb.setCenterX(x + halfWidth);
  mAabb.setCenterY(y + halfHeight);
  mAabb.setExtentX(halfWidth);
  mAabb.setExtentY(halfHeight);
}

void Paddle::setTexture(const char* imagePath, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(imagePath);
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    } else {
        mTexture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!mTexture) {
            std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(surface);
    }
}

void Paddle::onDraw(SDL_Renderer& renderer)
{
    if (mTexture) {
        SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(&renderer, mTexture, nullptr, &mRect);
    } else {
        std::cerr << "Error: Paddle texture not loaded." << std::endl;
        SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(&renderer, &mRect);
    }
}

void Paddle::onUpdate()
{
  // Cập nhật vị trí của thanh chỉ nếu thanh đang di chuyển
  if (mMovement != Movement::NONE) {
    auto movement = (int)mMovement * VELOCITY;
    mRect.y += movement;
    mAabb.setCenterY(mAabb.getCenterY() + movement);
    if (mMovement == Movement::UP) {
      const auto& wallAabb = mScene.getTopWall().getAabb();
      if (mAabb.collides(wallAabb)) {
        // Ngăn quả bóng di chuyển qua tường
        mRect.y = wallAabb.getCenterY();
        mRect.y += wallAabb.getExtentY();

        // Đảm bảo vị trí AABB cũng được cập nhật
        mAabb.setCenterY(mRect.y + mAabb.getExtentY());

        // Dừng chuyển động
        mMovement = Movement::NONE;
      }
    } else {
      const auto& wallAabb = mScene.getBottomWall().getAabb();
      if (mAabb.collides(wallAabb)) {
        // Ngăn thanh di chuyển qua tường
        mRect.y = wallAabb.getCenterY();
        mRect.y -= wallAabb.getExtentY();
        mRect.y -= mRect.h;

        // Đảm bảo vị trí AABB cũng được cập nhật
        mAabb.setCenterY(mRect.y + mAabb.getExtentY());

        // Dừng chuyển động
        mMovement = Movement::NONE;
      }
    }
  }
}

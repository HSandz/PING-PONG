#include "ball.h"
#include "court_scene.h"
#include <iostream>

using namespace pong;

const float Ball::INITIAL_VELOCITY = 8.f;
const float Ball::VELOCITY_INCREASE = 1.f;
const float Ball::MAX_VELOCITY = 15.f;

Ball::Ball(CourtScene& scene, int x, int y, int width, int height)
  : mScene(scene),
    mRect({ x, y, width, height}),
    mVelocity(INITIAL_VELOCITY),
    mDirection({-0.5f, 0.5f})
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

void Ball::setTexture(const std::string& path, SDL_Renderer* renderer) {
    // Giải phóng texture cũ
    SDL_DestroyTexture(mTexture);
    // Tải texture mới
    mTexture = IMG_LoadTexture(renderer, path.c_str());
    if (!mTexture) {
        std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
    }
}

void Ball::onDraw(SDL_Renderer& renderer)
{
  SDL_RenderFillRect(&renderer, &mRect);
}

void Ball::onUpdate()
{
  // Tạo một mảng chứa các chuyển động
  auto movement = std::array<int, 2>();
  movement[0] = static_cast<int>(mDirection[0] * mVelocity);
  movement[1] = static_cast<int>(mDirection[1] * mVelocity);

  // Áp dụng chuyển động cho vị trí của quả bóng
  mRect.x += movement[0];
  mRect.y += movement[1];

  // Áp dụng chuyển động cho vị trí của AABB
  mAabb.setCenterX(mAabb.getCenterX() + movement[0]);
  mAabb.setCenterY(mAabb.getCenterY() + movement[1]);

  // Lấy tham chiếu cho tất cả các va chạm có thể
  const auto& bottomWallAabb = mScene.getBottomWall().getAabb();
  const auto& topWallAabb = mScene.getTopWall().getAabb();
  const auto& leftPaddleAabb = mScene.getLeftPaddle().getAabb();
  const auto& rightPaddleAabb = mScene.getRightPaddle().getAabb();
  const auto& leftGoalAabb = mScene.getLeftGoal().getAabb();
  const auto& rightGoalAabb = mScene.getRightGoal().getAabb();

  if (mAabb.collides(bottomWallAabb)) {
    Mix_PlayChannel(-1, mScene.getPaddleCollisionSound(), 0);
    Mix_Volume(-1, 112);
    // Ngăn quả bóng di chuyển qua tường
    mRect.y = bottomWallAabb.getCenterY();
    mRect.y -= bottomWallAabb.getExtentY();
    mRect.y -= mRect.h;

    // Đảm bảo vị trí AABB cũng được cập nhật
    mAabb.setCenterX(mRect.x + mAabb.getExtentX());
    mAabb.setCenterY(mRect.y + mAabb.getExtentY());

    // Đảo ngược hướng của trục y
    mDirection[1] = -mDirection[1];
  } else if (mAabb.collides(topWallAabb)) {
    Mix_PlayChannel(-1, mScene.getPaddleCollisionSound(), 0);
    Mix_Volume(-1, 112);
    // Ngăn quả bóng di chuyển qua tường
    mRect.y = topWallAabb.getCenterY();
    mRect.y += topWallAabb.getExtentY();

    // Đảm bảo vị trí AABB cũng được cập nhật
    mAabb.setCenterX(mRect.x + mAabb.getExtentX());
    mAabb.setCenterY(mRect.y + mAabb.getExtentY());

    // Đảo ngược hướng của trục y
    mDirection[1] = -mDirection[1];
  } else if (mAabb.collides(leftPaddleAabb)) {
    Mix_PlayChannel(-1, mScene.getPaddleCollisionSound(), 0);
    Mix_Volume(-1, 112);
    // Ngăn quả bóng di chuyển qua thanh
    mRect.x = leftPaddleAabb.getCenterX();
    mRect.x += leftPaddleAabb.getExtentX();

    // Đảm bảo vị trí AABB cũng được cập nhật
    mAabb.setCenterX(mRect.x + mAabb.getExtentX());
    mAabb.setCenterY(mRect.y + mAabb.getExtentY());

    // Đảo ngược hướng của trục y
    mDirection[0] = -mDirection[0];

    // Tăng vận tốc nếu có thể
    mVelocity += VELOCITY_INCREASE;
    mVelocity = std::min(mVelocity, MAX_VELOCITY);
  } else if (mAabb.collides(rightPaddleAabb)) {
    Mix_PlayChannel(-1, mScene.getPaddleCollisionSound(), 0);
    Mix_Volume(-1, 112);
    // Ngăn quả bóng di chuyển qua thanh
    mRect.x = rightPaddleAabb.getCenterX();
    mRect.x -= rightPaddleAabb.getExtentX();
    mRect.x -= mRect.w;

    // Đảm bảo vị trí AABB cũng được cập nhật
    mAabb.setCenterX(mRect.x + mAabb.getExtentX());
    mAabb.setCenterY(mRect.y + mAabb.getExtentY());

    // Đảo ngược hướng của trục y
    mDirection[0] = -mDirection[0];

    // Tăng vận tốc nếu có thể
    mVelocity += VELOCITY_INCREASE;
    mVelocity = std::min(mVelocity, MAX_VELOCITY);
  } else if (mAabb.collides(rightGoalAabb)) {
    Mix_PlayChannel(-1, mScene.getGoalSound(), 0);
    Mix_Volume(-1, 128);
    mScene.addPlayerScore(0);
  } else if (mAabb.collides(leftGoalAabb)) {
    Mix_PlayChannel(-1, mScene.getGoalSound(), 0);
    Mix_Volume(-1, 128);
    mScene.addPlayerScore(1);
  }
}

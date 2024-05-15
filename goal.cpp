#include "goal.h"

using namespace pong;

Goal::Goal(int x, int y, int width, int height) : mRect({ x, y, width, height })
{
  // Tính nửa chiều rộng và chiều dài
  auto extentX = (width / 2);
  auto extentY = (height / 2);

  // Định nghĩa các chiều cho AABB
  mAabb.setCenterX(x + extentX);
  mAabb.setCenterY(y + extentY);
  mAabb.setExtentX(extentX);
  mAabb.setExtentY(extentY);
}

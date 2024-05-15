#include "center_line.h"

using namespace pong;

CenterLine::CenterLine(int x, int y, int width, int height) : mRect({ x, y, width, height })
{
  // ...
}

void CenterLine::onDraw(SDL_Renderer& renderer)
{
  // Vẽ đường thẳng trung tâm bằng cách vẽ nhiều hình vuông
  for (float y = static_cast<float>(mRect.y); y < mRect.h; y += (1.93f * mRect.w)) {
    SDL_Rect rect{ mRect.x, static_cast<int>(y), mRect.w, mRect.w };
    SDL_RenderFillRect(&renderer, &rect);
  }
}
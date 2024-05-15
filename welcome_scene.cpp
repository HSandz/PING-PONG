#include "welcome_scene.h"
#include "court_scene.h"
#include "game.h"

#include <SDL.h>

using namespace pong;

WelcomeScene::WelcomeScene(Game& game)
  : mGame(game),
    mTopicTexture(nullptr),
    mPlayText(nullptr),
    mChangeBackground(nullptr),
    mQuitText(nullptr)
{
  mTopicTexture = mGame.createText("SDL2 PONG");
  mPlayText = mGame.createText("Play [ENTER]");
  mChangeBackground = mGame.createText("Change background [SPACE]");
  mQuitText = mGame.createText("Quit [ESC]");
}

WelcomeScene::~WelcomeScene()
{
  SDL_DestroyTexture(mTopicTexture);
  SDL_DestroyTexture(mPlayText);
  SDL_DestroyTexture(mChangeBackground);
  SDL_DestroyTexture(mQuitText);
}

void WelcomeScene::onDraw(SDL_Renderer& renderer)
{
  // Vẽ chủ đề của game
  SDL_Rect rect {0, 100, 0, 0};
  SDL_QueryTexture(mTopicTexture, nullptr, nullptr, &rect.w, &rect.h);
  rect.x = (400 - (rect.w / 2));
  SDL_RenderCopy(&renderer, mTopicTexture, nullptr, &rect);

  // Vẽ hướng dẫn điều khiển cho người chơi bên trái
  SDL_QueryTexture(mPlayText, nullptr, nullptr, &rect.w, &rect.h);
  rect.x = (400 - (rect.w / 2));
  rect.y = 200;
  SDL_RenderCopy(&renderer, mPlayText, nullptr, &rect);

  // Vẽ hướng dẫn điều khiển cho người chơi bên phải
  SDL_QueryTexture(mChangeBackground, nullptr, nullptr, &rect.w, &rect.h);
  rect.x = (400 - (rect.w / 2));
  rect.y = 250;
  SDL_RenderCopy(&renderer, mChangeBackground, nullptr, &rect);

  // Vẽ hướng dẫn vào game
  SDL_QueryTexture(mQuitText, nullptr, nullptr, &rect.w, &rect.h);
  rect.x = (400 - (rect.w / 2));
  rect.y = 400;
  SDL_RenderCopy(&renderer, mQuitText, nullptr, &rect);
}

void WelcomeScene::onUpdate()
{
	// ...
}

void WelcomeScene::onEnter()
{
	// ...
}

void WelcomeScene::onExit()
{
	// ...
}

void WelcomeScene::onKeyDown(SDL_KeyboardEvent& event)
{
  // ...
}

void WelcomeScene::onKeyUp(SDL_KeyboardEvent& event)
{
  // Chuyển màn hình vào game để bắt đầu
  switch (event.keysym.sym) {
  case SDLK_RETURN:
    mGame.setScene(std::make_shared<CourtScene>(mGame));
    break;
  case SDLK_SPACE:
    mGame.addBackgroundIndex();
    break;
  }
}

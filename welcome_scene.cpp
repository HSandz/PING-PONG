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
    mQuitText(nullptr),
    mAdjustVolume(nullptr)
{
  mTopicTexture = mGame.createText("SDL2 PONG");
  mPlayText = mGame.createText("Play [ENTER]");
  mChangeBackground = mGame.createText("Change background [SPACE]");
  mAdjustVolume = mGame.createText("Adjust Volume - Up [U] Down [I]");
  mQuitText = mGame.createText("Quit [ESC]");
}

WelcomeScene::~WelcomeScene()
{
  SDL_DestroyTexture(mTopicTexture);
  SDL_DestroyTexture(mPlayText);
  SDL_DestroyTexture(mChangeBackground);
  SDL_DestroyTexture(mAdjustVolume);
  SDL_DestroyTexture(mQuitText);
}

void WelcomeScene::onDraw(SDL_Renderer& renderer)
{
  // Vẽ chủ đề của game
  SDL_Rect rect {0, 100, 0, 0};
  SDL_QueryTexture(mTopicTexture, nullptr, nullptr, &rect.w, &rect.h);
  rect.x = (400 - (rect.w / 2));
  SDL_RenderCopy(&renderer, mTopicTexture, nullptr, &rect);

  // Vẽ hướng dẫn vào game
  SDL_QueryTexture(mPlayText, nullptr, nullptr, &rect.w, &rect.h);
  rect.x = (400 - (rect.w / 2));
  rect.y = 200;
  SDL_RenderCopy(&renderer, mPlayText, nullptr, &rect);

  // Vẽ hướng dẫn thay đổi background
  SDL_QueryTexture(mChangeBackground, nullptr, nullptr, &rect.w, &rect.h);
  rect.x = (400 - (rect.w / 2));
  rect.y = 250;
  SDL_RenderCopy(&renderer, mChangeBackground, nullptr, &rect);

  // Vẽ hướng dẫn thay đổi âm lượng
  SDL_QueryTexture(mAdjustVolume, nullptr, nullptr, &rect.w, &rect.h);
  rect.x = (400 - (rect.w / 2));
  rect.y = 300;
  SDL_RenderCopy(&renderer, mAdjustVolume, nullptr, &rect);

  // Vẽ hướng dẫn thoát game
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
  switch (event.keysym.sym) {
  case SDLK_u:
    mGame.adjustVolume(false);
    break;
  case SDLK_i:
    mGame.adjustVolume(true);
    break;
  }
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

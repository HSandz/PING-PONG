#include "endgame_scene.h"
#include "welcome_scene.h"

#include <memory>
#include <SDL.h>

using namespace pong;

EndgameScene::EndgameScene(Game& game)
  : mGame(game),
    mTopicTexture(nullptr),
    mEndgameTexture(nullptr),
    mWinnerTexture(nullptr),
    mEndResultTexture(nullptr),
    mResultScoreTexture(nullptr),
    mInstructionsTexture(nullptr)
{
  // Lấy tham chiếu đến điểm tổng
  const auto& scores = mGame.getPlayerScores();

  mTopicTexture = mGame.createText("PING PONG - RESULTS");
  mEndgameTexture = mGame.createText("Game has ended");
  if (scores[0] > 9) {
    mWinnerTexture = mGame.createText("Left player won the game!");
  } else {
    mWinnerTexture = mGame.createText("Right player won the game!");
  }
  mEndResultTexture = mGame.createText("End results:");
  mResultScoreTexture = mGame.createText(std::to_string(scores[0]) + "-" + std::to_string(scores[1]));
  mInstructionsTexture = mGame.createText("Press [ENTER] to proceed");
}

EndgameScene::~EndgameScene()
{
  SDL_DestroyTexture(mTopicTexture);
  SDL_DestroyTexture(mEndgameTexture);
  SDL_DestroyTexture(mWinnerTexture);
  SDL_DestroyTexture(mEndResultTexture);
  SDL_DestroyTexture(mResultScoreTexture);
  SDL_DestroyTexture(mInstructionsTexture);
}

void EndgameScene::onDraw(SDL_Renderer& renderer)
{
  // Vẽ chủ đề của game
  SDL_Rect rect{ 0, 100, 0, 0 };
  SDL_QueryTexture(mTopicTexture, nullptr, nullptr, &rect.w, &rect.h);
  rect.x = (400 - (rect.w / 2));
  SDL_RenderCopy(&renderer, mTopicTexture, nullptr, &rect);

  rect.y = 200;
  SDL_QueryTexture(mEndgameTexture, nullptr, nullptr, &rect.w, &rect.h);
  rect.x = (400 - (rect.w / 2));
  SDL_RenderCopy(&renderer, mEndgameTexture, nullptr, &rect);

  rect.y = 240;
  SDL_QueryTexture(mWinnerTexture, nullptr, nullptr, &rect.w, &rect.h);
  rect.x = (400 - (rect.w / 2));
  SDL_RenderCopy(&renderer, mWinnerTexture, nullptr, &rect);

  rect.y = 300;
  SDL_QueryTexture(mEndResultTexture, nullptr, nullptr, &rect.w, &rect.h);
  rect.x = (400 - (rect.w / 2));
  SDL_RenderCopy(&renderer, mEndResultTexture, nullptr, &rect);

  rect.y = 340;
  SDL_QueryTexture(mResultScoreTexture, nullptr, nullptr, &rect.w, &rect.h);
  rect.x = (400 - (rect.w / 2));
  SDL_RenderCopy(&renderer, mResultScoreTexture, nullptr, &rect);

  rect.y = 500;
  SDL_QueryTexture(mInstructionsTexture, nullptr, nullptr, &rect.w, &rect.h);
  rect.x = (400 - (rect.w / 2));
  SDL_RenderCopy(&renderer, mInstructionsTexture, nullptr, &rect);
}

void EndgameScene::onUpdate()
{
  // ...
}

void EndgameScene::onEnter()
{
  // ...
}

void EndgameScene::onExit()
{
  // ...
}

void EndgameScene::onKeyDown(SDL_KeyboardEvent& event)
{
  // Thay đổi âm lượng
  switch (event.keysym.sym) {
  case SDLK_u:
    mGame.adjustVolume(false);
    break;
  case SDLK_i:
    mGame.adjustVolume(true);
    break;
  }
}

void EndgameScene::onKeyUp(SDL_KeyboardEvent& event)
{
  // Chuyển đến màn hình welcome
  switch (event.keysym.sym) {
  case SDLK_RETURN:
    mGame.setScene(std::make_shared<WelcomeScene>(mGame));
    break;
  case SDLK_SPACE:
    mGame.addBackgroundIndex();
    break;
  }
}

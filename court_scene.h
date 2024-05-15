#ifndef PONG_COURT_SCENE_H
#define PONG_COURT_SCENE_H

#include "ball.h"
#include "center_line.h"
#include "goal.h"
#include "paddle.h"
#include "wall.h"
#include "scene.h"
#include "score_indicator.h"

#include <array>
#include <SDL_mixer.h>

namespace pong
{
  class Game;
  class CourtScene : public Scene
  {
  public:
    /*! Chiều rộng của hộp quả bóng sử dụng trong các cảnh */
    static const int BOX_WIDTH = 20;
    /*! Chiều cao của tường trên và dưới */
    static const int WALL_HEIGHT = BOX_WIDTH;
    /*! Chiều cao của thanh bên trái và phải */
    static const int PADDLE_HEIGHT = 100;

    static const int EDGE_OFFSET = 30;

    CourtScene(Game& game);
    virtual ~CourtScene();

    void onDraw(SDL_Renderer& renderer) override;
    void onUpdate() override;
    void onEnter() override;
    void onExit() override;
    void onKeyDown(SDL_KeyboardEvent& event) override;
    void onKeyUp(SDL_KeyboardEvent& event) override;

    void addPlayerScore(int playerIndex);
    void resetEntities();

    const Game& getGame() const { return mGame; }
          Game& getGame()       { return mGame; }

    const Wall& getTopWall() const  { return mTopWall; }
          Wall& getTopWall()        { return mTopWall; }

    const Wall& getBottomWall() const { return mBottomWall; }
          Wall& getBottomWall()       { return mBottomWall; }

    const CenterLine& getCenterLine() const { return mCenterLine; }
          CenterLine& getCenterLine()       { return mCenterLine; }

    const Paddle& getLeftPaddle() const { return mLeftPaddle; }
          Paddle& getLeftPaddle()       { return mLeftPaddle; }

    const Paddle& getRightPaddle() const { return mRightPaddle; }
          Paddle& getRightPaddle()       { return mRightPaddle; }

    const Goal& getLeftGoal() const { return mLeftGoal; }
          Goal& getLeftGoal()       { return mLeftGoal; }

    const Goal& getRightGoal() const  { return mRightGoal; }
          Goal& getRightGoal()        { return mRightGoal; }

    const Mix_Chunk* getPaddleCollisionSound() const { return paddleCollisionSound; }
          Mix_Chunk* getPaddleCollisionSound()       { return paddleCollisionSound; }

    const Mix_Chunk* getGoalSound() const { return goalSound; }
          Mix_Chunk* getGoalSound()       { return goalSound; }

    const Mix_Chunk* getVictorySound() const { return victorySound; }
          Mix_Chunk* getVictorySound()       { return victorySound; }
  private:
    Game&           mGame;

    Wall            mTopWall;
    Wall            mBottomWall;
    CenterLine      mCenterLine;
    Paddle          mLeftPaddle;
    Paddle          mRightPaddle;
    Ball            mBall;
    Goal            mLeftGoal;
    Goal            mRightGoal;
    ScoreIndicator  mLeftScoreIndicator;
    ScoreIndicator  mRightScoreIndicator;
    int             mRemainingPauseTicks;
    Mix_Chunk*      paddleCollisionSound;
    Mix_Chunk*      goalSound;
    Mix_Chunk*      victorySound;
  };
}

#endif

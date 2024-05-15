#ifndef PONG_GAME_H
#define PONG_GAME_H

#include "scene.h"

#include <array>
#include <string>
#include <SDL_mixer.h>
#include <SDL_image.h>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct _TTF_Font;

namespace pong
{
  class Game
  {
  public:
    Game();
    Game(const Game&) = delete;
    Game(Game&&) = delete;

    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    ~Game();

    void start();

    void setScene(ScenePtr scene);

    SDL_Texture* createText(const std::string& text);

    const std::array<int, 2>& getResolution() const { return mResolution; }

    const std::array<int, 2>& getHalfResolution() const { return mHalfResolution; }

    std::array<int, 2>& getPlayerScores() { return mPlayerScores; }

    bool initAudio();

    bool loadBackgroundMusic(const char* filePath);

    void playBackgroundMusic();

    Mix_Chunk* getCollisionSound() const { return mCollisionSound; }

    SDL_Renderer* getRenderer() const { return mRenderer; }

  private:
    SDL_Window*                 mWindow;
    SDL_Renderer*               mRenderer;
    _TTF_Font*                  mFont;
    ScenePtr                    mScene;
    std::array<int, 2>          mResolution;
    std::array<int, 2>          mHalfResolution;
    std::array<int, 2>          mPlayerScores;
    SDL_Texture*                mBackgroundTexture;
    SDL_Surface*                mBackgroundSurface;
    Mix_Music*                  mBackgroundMusic;
    Mix_Chunk*                  mCollisionSound;
    std::array<std::string, 3>  mAlternateBackground;
    int                         mBackgroundIndex;
  };
}

#endif

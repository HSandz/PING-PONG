#include "game.h"
#include "welcome_scene.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>

#define ERROR -1
#define OK     0

using namespace pong;

Game::Game()
  : mWindow(nullptr),
    mRenderer(nullptr),
    mFont(nullptr),
    mResolution({ 800, 600 }),
    mHalfResolution({ mResolution[0] / 2, mResolution[1] / 2 }),
    mPlayerScores({0, 0}),
    mBackgroundTexture({nullptr, nullptr, nullptr}),
    mBackgroundSurface({nullptr, nullptr, nullptr}),
    mBackgroundIndex(0),
    mVolumeValue(MIX_MAX_VOLUME / 2),
    mAlternateBackground({"resources/image/space_background.bmp",
                          "resources/image/city_background.bmp",
                          "resources/image/landscape_background.bmp"})
{
    //...
}

Game::~Game()
{
  TTF_CloseFont(mFont);
  SDL_DestroyWindow(mWindow);
  TTF_Quit();
  SDL_Quit();
}

void Game::start()
{
  // Khởi tạo SDL2
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
    return;
  }
  // Initialize SDL audio
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    SDL_Quit();
    return;
  }

  // Load background music
  mBackgroundMusic = Mix_LoadMUS("resources/audio/background_music.mp3");
  if (mBackgroundMusic == nullptr) {
    std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    Mix_CloseAudio();
    SDL_Quit();
    return;
  }

  // Khởi tạo TTF
  if (TTF_Init() == -1) {
    std::cerr << "Unable to initialize TTF: " << TTF_GetError() << std::endl;
    return;
  }

  // Tạo một cửa sổ mới
  mWindow = SDL_CreateWindow("SDL2 - Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mResolution[0], mResolution[1], SDL_WINDOW_SHOWN);
  if (mWindow == nullptr) {
    std::cerr << "Unable to create SDL window: " << SDL_GetError() << std::endl;
    return;
  }

  // Tạo một renderer mới
  mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (mRenderer == nullptr) {
    std::cerr << "Unable to create SDL renderer: " << SDL_GetError() << std::endl;
    return;
  }
  for (int i = 0; i < 3; i++) {
    mBackgroundSurface[i] = SDL_LoadBMP(mAlternateBackground[i].c_str());
    if (mBackgroundSurface[i] == nullptr) {
      std::cerr << "Unable to load background image: " << SDL_GetError() << std::endl;
    } else {
      mBackgroundTexture[i] = SDL_CreateTextureFromSurface(mRenderer, mBackgroundSurface[i]);
      SDL_FreeSurface(mBackgroundSurface[i]);
      if (mBackgroundTexture[i] == nullptr) {
          std::cerr << "Unable to create texture from background image: " << SDL_GetError() << std::endl;
      }
    }
  }

  // Khởi tạo phông chữ
  mFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 28);
  if (mFont == nullptr) {
    std::cerr << "Unable to load a font for the application: " << TTF_GetError() << std::endl;
  }

  Mix_PlayMusic(mBackgroundMusic, -1);


  // Khởi tạo cảnh ban đầu của game
  setScene(std::make_shared<WelcomeScene>(*this));

  auto isRunning = true;
  SDL_Event event;
  while (isRunning) {
    // Thăm dò và xử lí sự kiện từ SDL
    while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
      case SDL_QUIT:
        isRunning = false;
        break;
      case SDL_KEYDOWN:
        mScene->onKeyDown(event.key);
        break;
      case SDL_KEYUP:
        mScene->onKeyUp(event.key);
        break;
      }
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        isRunning = false;
        break;
      }
    }

    // Render texture nền
    SDL_RenderCopy(mRenderer, mBackgroundTexture[mBackgroundIndex], nullptr, nullptr);

    // Cập nhật logic game của cảnh hiện tại
    mScene->onUpdate();

    // Đặt âm lượng cho nhạc nền
    Mix_VolumeMusic(mVolumeValue);

    // Xóa nội dung render bằng màu đen
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(mRenderer);

    // Render cho texture background
    SDL_RenderCopy(mRenderer, mBackgroundTexture[mBackgroundIndex], nullptr, nullptr);

    // Chuyển màu vẽ của renderer sang màu trắng
    SDL_SetRenderDrawColor(mRenderer, 0xff, 0xff, 0xff, 0xff);

    // Render nội dung cảnh vào buffer
    mScene->onDraw(*mRenderer);

    // Trình bày bộ đệm được render
    SDL_RenderPresent(mRenderer);

  }
}

void Game::setScene(ScenePtr scene)
{
  // Bỏ qua cảnh rỗng
  if (scene == nullptr) {
    std::cerr << "Unable to set null as the active scene!" << std::endl;
    return;
  }

  // Thoát khỏi cảnh cũ (nếu có)
  if (mScene) {
    mScene->onExit();
  }

  // Vào cảnh mới
  mScene = scene;
  mScene->onEnter();
}

SDL_Texture* Game::createText(const std::string& text)
{
  // Tạo một surface chứa văn bản
  SDL_Color color{ 0xff, 0xff, 0xff, 0xff };
  auto surface = TTF_RenderText_Blended(mFont, text.c_str(), color);
  if (surface == nullptr) {
    std::cerr << "Unable to create a surface with a text: " << TTF_GetError() << std::endl;
    return nullptr;
  }

  // Tạo một texture từ surface chứa văn bản
  auto texture = SDL_CreateTextureFromSurface(mRenderer, surface);
  SDL_FreeSurface(surface);
  if (texture == nullptr) {
    std::cerr << "Unable to create texture from a text surface: " << SDL_GetError() << std::endl;
    return nullptr;
  }

  return texture;
}

bool Game::initAudio() {
  // Khởi tạo SDL Audio
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    return false;
  }

  mCollisionSound = Mix_LoadWAV("resources/audio/bonk.wav");
  if (mCollisionSound == nullptr) {
    std::cerr << "Failed to load collision sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
    return false;
  }

  return true;
}

void Game::adjustVolume(bool up) {
  if (up) {
    if (mVolumeValue < MIX_MAX_VOLUME) mVolumeValue++;
  }
  else {
    if (mVolumeValue > 0) mVolumeValue--;
  }
}

bool Game::loadBackgroundMusic(const char* filePath) {
  // Tải nhạc nền
  mBackgroundMusic = Mix_LoadMUS(filePath);
  if (mBackgroundMusic == nullptr) {
    std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    return false;
  }

  return true;
}

void Game::addBackgroundIndex() {
  // Thay đổi ảnh nền
  mBackgroundIndex = (mBackgroundIndex + 1) % 3;
}

void Game::playBackgroundMusic() {
  // Lặp tải nhạc nền
  Mix_PlayMusic(mBackgroundMusic, -1);
}

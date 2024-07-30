#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstdio>
#include <iostream>
SDL_Window *gWindow = nullptr;
SDL_Surface *gBackground = nullptr;
SDL_Surface *gMedia = nullptr;
int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;

bool init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    success = false;
    return success;
  } else {
    gWindow = SDL_CreateWindow("Event Window", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!gWindow) {
      success = false;
      return success;
    } else {
      gBackground = SDL_GetWindowSurface(gWindow);
      SDL_FillRect(gBackground, nullptr,
                   SDL_MapRGB(gBackground->format, 235, 64, 52));
    }
  }
  return success;
}

bool loadAndApplyMedia() {
  bool success = true;
  gMedia = SDL_LoadBMP("media/hello_world.bmp");
  if (!gMedia) {
    success = false;
    return success;
  }
  return success;
}

void close() {
  SDL_FreeSurface(gMedia);
  gMedia = nullptr;

  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;

  SDL_Quit();
}

int main(int argc, char *argv[]) {
  if (!init()) {
    std::cout << "[Error] Failed to create window: " << SDL_GetError() << '\n';
    return -1;
  }
  if (!loadAndApplyMedia()) {
    std::cout << "[Error] Failed to loadAndApplyMedia: " << SDL_GetError()
              << '\n';
    return -1;
  }
  SDL_BlitSurface(gMedia, nullptr, gBackground, nullptr);
  SDL_UpdateWindowSurface(gWindow);

  bool running = true;
  SDL_Event e;
  while (running) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = false;
        break;
      }
    }
  }

  close();
}

#pragma once

#include <SDL.h>

namespace CQ::Colors
{
  // Basic colors
  inline const SDL_Color BLACK = {0, 0, 0, 255};
  inline const SDL_Color ORANGE = {255, 165, 0, 255};

  // Main theme
  inline const SDL_Color GAME_DEFAULT_TEXT = ORANGE;

  // Menu colors
  inline const SDL_Color MENU_SELECTED_TEXT = BLACK;
  inline const SDL_Color MENU_SELECTED_BG = ORANGE;

  inline const SDL_Color MENU_INACTIVE_TEXT = ORANGE;
  inline const SDL_Color MENU_INACTIVE_BG = BLACK;
  
} // namespace

#pragma once

#include "SDLRenderer.h"
#include "Menu.h"
#include "FontManager.h"
#include "GameState.h"
#include "Player.h"
#include "Map.h"

namespace Render = CQ::Render;
namespace State = CQ::State;
namespace Data = CQ::Data;
namespace Map = CQ::Map;

namespace CQ::Game
{
  enum MainMenuOption
  {
    START = 0,
    RESUME = 1,
    SAVE = 2,
    LOAD = 3,
    QUIT = 4
  };
  
  class Game
  {
  public:
    Game();
    
    void run();
    
    void handleMainMenu();
    void handlePlaying();
    
  private:
    Render::SDLRenderer m_sdlRenderer;
    Render::FontManager m_fontManager;
    TTF_Font* m_font;     // 24pt - menus and body text
    TTF_Font* m_mapFont;  // 12pt - room labels, which must fit a 100px cell
    
    State::GameState m_state;
    Data::Player m_player;
    Map::Map m_map;
    int m_currentHour;
    int m_currentDay;
    bool m_running;
    
  }; // class Game
} // namespace

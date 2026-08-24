#include "Game.h"
#include "strings.h"
#include "FontManager.h"
#include "fonts.h"
#include "Menu.h"
#include "Position.h"
#include "colors.h"

#include <iostream>

namespace Strings = CQ::Strings;
namespace Render = CQ::Render;
namespace State = CQ::State;
namespace Data = CQ::Data;
namespace Fonts = CQ::Fonts;
namespace UI = CQ::UI;
namespace Map = CQ::Map;
namespace Colors = CQ::Colors;

namespace CQ::Game {
  Game::Game()
  : m_sdlRenderer(std::string(Strings::GAME_NAME), 800, 600)
  , m_state(State::GameState::MAIN_MENU)
  , m_player(Data::Player())
  , m_map(Map::Map())
  , m_currentHour(0)
  , m_currentDay(0)
  , m_running(true)
  {
    m_font = m_fontManager.loadFont(Fonts::MENLO, 24);
  }
  
  void Game::run()
  {
    while(m_running)
    {
      switch (m_state) {
        case State::GameState::MAIN_MENU:
          handleMainMenu();
          break;
        case State::GameState::SAVE_MENU:
          break;
        case State::GameState::LOAD_MENU:
          break;
        case State::GameState::PLAYING:
          handlePlaying();
          break;
        case State::GameState::PAUSED:
          break;
        case State::GameState::GAME_OVER:
          break;
        case State::GameState::WIN:
          break;
        case State::GameState::RETIREMENT:
          break;
        case State::GameState::QUIT:
          m_running = false;
          break;
        default:
          break;
      }
    }
  }
  
  void Game::handleMainMenu()
  {
    UI::Menu menu { UI::Menu() };
    
    for (const auto& option : Strings::menuOptions)
    {
      menu.addOption(option);
    }
    
    int selectedOption { menu.show(m_sdlRenderer, m_font) };
    
    switch (selectedOption)
    {
      case START:
        std::cout << "START selected\n";
        m_state = State::GameState::PLAYING;
        break;
      case RESUME:
        std::cout << "RESUME selected\n";
        m_state = State::GameState::PLAYING;
        break;
      case SAVE:
        std::cout << "SAVE selected\n";
        m_state = State::GameState::SAVE_MENU;
        break;
      case LOAD:
        std::cout << "LOAD selected\n";
        m_state = State::GameState::LOAD_MENU;
        break;
      case QUIT:
        std::cout << "QUIT selected\n";
        m_state = State::GameState::QUIT;
        break;
      default:
        break;
    }
    
    
  }
  
  void Game::handlePlaying()
  {
    // Clear screen
    m_sdlRenderer.clear(Colors::BLACK);
    
    // Draw the map
    m_map.display(m_sdlRenderer, m_font, m_player.getPosition());
    
    // Present to screen
    m_sdlRenderer.present();
    
    // Handle SDL events (window close, key presses, etc.)
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        m_running = false;
      }
      // TODO: Add keyboard handling for movement later
    }
    
    // Small delay to prevent 100% CPU usage
    SDL_Delay(16);  // ~60 FPS
  }
} // namespace

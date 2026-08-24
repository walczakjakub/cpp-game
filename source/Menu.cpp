#include "Menu.h"
#include "colors.h"
#include "SDLRenderer.h"

#include <iostream>

// TODO: Rewrite Menu class for SDL rendering
namespace Render = CQ::Render;
namespace Colors = CQ::Colors;

namespace CQ::UI
{
  //Constructor
  Menu::Menu()
    : m_selectedIndex(0)
  {
  }

  void Menu::addOption(const std::string& text_)
  {
    m_options.emplace_back(text_);
  }

  int Menu::show(Render::SDLRenderer& renderer_, TTF_Font* font_)
  {
    if (m_options.empty())
    {
      std::cerr << "Warning: Menu has no options!" << std::endl;
      return -1;
    }
    
    bool menuActive = true;
    int selectedOption = -1;
    
    while (menuActive)
    {
      SDL_Event event;
      
      while(SDL_PollEvent(&event))
      {
        if (event.type == SDL_QUIT)
        {
          return -1;
        }
        else if (event.type == SDL_KEYDOWN)
        {
          switch (event.key.keysym.sym)
          {
            case SDLK_UP:
              moveSelection(-1);
              break;
            case SDLK_DOWN:
              moveSelection(1);
              break;
            case SDLK_RETURN:
            case SDLK_SPACE:
              selectedOption = m_selectedIndex;
              menuActive = false;
              break;
            default:
              break;
          }
        }
      }
      render(renderer_, font_);
      SDL_Delay(16);
    }
    return selectedOption;
  }
  
  void Menu::clear()
  {
    m_options.clear();
    m_selectedIndex = 0;
  }
  
  void Menu::render(Render::SDLRenderer& renderer_, TTF_Font* font_) const
  {
    renderer_.clear(Colors::BLACK);
    
    int startX = 200;
    int startY = 150;
    int lineHeight = 50;
    
    for (size_t i = 0; i < m_options.size(); ++i)
    {
      int y = startY + (static_cast<int>(i) * lineHeight);
      bool isSelected = (static_cast<int>(i) == m_selectedIndex);
      
      if (isSelected)
      {
        // draw highlight
        SDL_Rect backgroundRect;
        backgroundRect.x = startX - 10;
        backgroundRect.y = y - 5;
        backgroundRect.w = 400;
        backgroundRect.h = lineHeight - 10;
        
        SDL_Renderer* sdlRenderer = renderer_.getRenderer();
        
        SDL_SetRenderDrawColor(sdlRenderer,
                               CQ::Colors::ORANGE.r,
                               CQ::Colors::ORANGE.g,
                               CQ::Colors::ORANGE.b,
                               CQ::Colors::ORANGE.a);
        
        SDL_RenderFillRect(sdlRenderer, &backgroundRect);

        renderer_.renderText(
          m_options[i].text,
          font_,
          CQ::Colors::BLACK,
          startX,
          y
        );
      }
      else
      {
        renderer_.renderText(
          m_options[i].text,
          font_,
          CQ::Colors::ORANGE,      // Orange text for unselected options
          startX,
          y
        );
      }
    }
    renderer_.present();
  }
  
  void Menu::moveSelection(int direction_)
  {
    m_selectedIndex += direction_;
    
    if (m_selectedIndex < 0) {
      m_selectedIndex = static_cast<int>(m_options.size()) - 1;
    } else if (m_selectedIndex >= static_cast<int>(m_options.size()))
    {
      m_selectedIndex = 0;
    }
  }
} //namespace

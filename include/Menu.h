#pragma once

#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>

namespace CQ::Render
{
  class SDLRenderer;
}

namespace CQ::UI
{
  class Menu
  {
  public:
    struct Option
    {
      std::string text;
      
      //constructor
      Option(const std::string& text_) : text(text_) {}
    };
    
    //constructor
    Menu();
    
    void addOption(const std::string& text_);
    
    int show(CQ::Render::SDLRenderer& renderer_, TTF_Font* font_);
    
    void clear();
    
    int getSelectedIndex()
    {
      return m_selectedIndex;
    }
    
    void render(CQ::Render::SDLRenderer& renderer_, TTF_Font* font_) const;
    
    void moveSelection(int direction_);
    
  private:
    std::vector<Option> m_options;
    int m_selectedIndex;
  };
} // namespace

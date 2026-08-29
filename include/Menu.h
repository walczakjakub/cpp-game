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
      int id;
      
      //constructor
      Option(const std::string& text_, const int id_) : text(text_), id(id_) {}
    };
    
    //constructor
    Menu();
    
    void addOption(const std::string& text_, const int id_);
    
    int show(CQ::Render::SDLRenderer& renderer_, TTF_Font* font_);
    
    void clear();
    
    int getSelectedIndex()
    {
      return m_selectedIndex;
    }
    
    // Draws the options inside the given screen region, so the same Menu can
    // be a centred fullscreen menu or sit in a panel beside the map.
    void render(CQ::Render::SDLRenderer& renderer_, TTF_Font* font_, const SDL_Rect& area_) const;
    
    void moveSelection(int direction_);
    
  private:
    std::vector<Option> m_options;
    int m_selectedIndex;
  };
} // namespace

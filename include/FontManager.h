#pragma once

#include <string>
#include <SDL_ttf.h>

namespace CQ::Render
{
  class FontManager
  {
  public:
    // Constructor
    FontManager();
    
    // Destructor
    ~FontManager();
    
    FontManager(const FontManager&) = delete;
    FontManager operator=(const FontManager&) = delete;
    
    TTF_Font* loadFont(const std::string& filepath_, int pointSize_);
    
    bool isInitialized() const
    {
      return m_initialized;
    }
    
  private:
    bool m_initialized;
  };
}

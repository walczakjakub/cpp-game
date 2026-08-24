#pragma once

#include <string>
#include <vector>
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
    FontManager& operator=(const FontManager&) = delete;
    
    // Returns a NON-OWNING pointer. FontManager keeps ownership of every font
    // it hands out and closes them all in its destructor, so callers must not
    // call TTF_CloseFont themselves. FontManager must outlive its callers.
    TTF_Font* loadFont(const std::string& filepath_, int pointSize_);
    
    bool isInitialized() const
    {
      return m_initialized;
    }
    
  private:
    bool m_initialized;
    std::vector<TTF_Font*> m_fonts;  // owned; closed in ~FontManager
  };
}

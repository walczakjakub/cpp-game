#pragma once

#include "SDLRenderer.h"
#include "FontManager.h"
#include "Position.h"
#include "Room.h"

#include <array>

namespace Data = CQ::Data;
namespace Render = CQ::Render;

namespace CQ::Map
{
  class Map
  {
  public:
    Map();
    
    void generate();
    
    void display(Render::SDLRenderer& renderer, TTF_Font* font, const Data::Position& playerPos);
    
    const Data::Position& getPlayerOfficePosition() const;
    
  private:
    std::array<std::array<Room  , 4>, 4> m_rooms;
    
    Data::Position m_playerOfficePosition;
  };
} // namespace

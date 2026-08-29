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
    
    void discoverRoom(const Data::Position& roomPosition);
    
    const Data::Position& getPlayerOfficePosition() const;
    
    Room getRoomAt(const Data::Position& roomPosition) const;
    
  private:
    std::array<std::array<Room  , 4>, 4> m_rooms;
    
    Data::Position m_playerOfficePosition;
  };
} // namespace

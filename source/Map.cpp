#include "Map.h"
#include "colors.h"
#include <SDL.h>
#include <SDL_ttf.h>

namespace Render = CQ::Render;
namespace Data = CQ::Data;
namespace Colors = CQ::Colors;

namespace CQ::Map
{
  // TEMPORARY placeholder layout: the 16 room types laid out in enum order,
  // row-major, all marked discovered so every label is visible on screen.
  //
  // Phase 4's generate() replaces this with a randomized layout (parking lot
  // in one of the four corners) and sets discovered = false so undiscovered
  // rooms render as "?" the way the design calls for.
  Map::Map()
  {
    int roomIndex = 0;
    
    for (int row = 0; row < 4; ++row)
    {
      for (int col = 0; col < 4; ++col)
      {
        m_rooms[row][col].type = static_cast<RoomType>(roomIndex);
        m_rooms[row][col].discovered = true;
        ++roomIndex;
      }
    }
  }
  
  void Map::display(Render::SDLRenderer& renderer, TTF_Font* font, const Data::Position& playerPos)
  {
    // Grid settings
    const int gridWidth = 400;   // 4 cells × 100px
    const int gridHeight = 400;  // 4 cells × 100px
    const int windowWidth = 800;
    const int gridStartX = (windowWidth - gridWidth) / 2;  // Center horizontally
    const int gridStartY = 25;   // 25px from top edge
    const int cellSize = 100;    // Each cell is 100x100 pixels
    const int padding = 0;       // No space between cells
    
    // Get the raw SDL_Renderer for drawing rectangles
    SDL_Renderer* sdlRenderer = renderer.getRenderer();
    
    // Draw the 4x4 grid
    for (int row = 0; row < 4; ++row)
    {
      for (int col = 0; col < 4; ++col)
      {
        // Calculate position for this cell
        int x = gridStartX + col * (cellSize + padding);
        int y = gridStartY + row * (cellSize + padding);
        
        // Create rectangle for this cell
        SDL_Rect cellRect;
        cellRect.x = x;
        cellRect.y = y;
        cellRect.w = cellSize;
        cellRect.h = cellSize;
        
        // Check if this is the player's position
        bool isPlayerHere = (row == playerPos.row && col == playerPos.col);
        
        // Set color based on player position
        if (isPlayerHere)
        {
          // Player's cell - filled orange
          SDL_SetRenderDrawColor(sdlRenderer, Colors::ORANGE.r, Colors::ORANGE.g, Colors::ORANGE.b, 255);
          SDL_RenderFillRect(sdlRenderer, &cellRect);
        }
        else
        {
          // Empty cell - orange outline only
          SDL_SetRenderDrawColor(sdlRenderer, Colors::ORANGE.r, Colors::ORANGE.g, Colors::ORANGE.b, 255);
          SDL_RenderDrawRect(sdlRenderer, &cellRect);
        }
        
        // Label the cell: room name once discovered, "?" until then
        const Room& room = m_rooms[row][col];
        const char* label = room.discovered ? roomTypeToString(room.type) : "?";
        
        // The player's cell is filled orange, so its text has to be black
        const SDL_Color& textColor = isPlayerHere ? Colors::BLACK : Colors::ORANGE;
        
        // Measure the label so we can centre it in the cell
        int textWidth = 0;
        int textHeight = 0;
        
        if (font != nullptr && TTF_SizeText(font, label, &textWidth, &textHeight) == 0)
        {
          renderer.renderText(label,
                              font,
                              textColor,
                              x + (cellSize - textWidth) / 2,
                              y + (cellSize - textHeight) / 2);
        }
      }
    }
  } // display()
} // namespace


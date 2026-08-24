#pragma once

namespace CQ::State {
  enum class GameState
  {
    MAIN_MENU,
    SAVE_MENU,
    LOAD_MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    WIN,
    RETIREMENT,
    QUIT
  };

  GameState openMainMenu();
  GameState startGame();
}

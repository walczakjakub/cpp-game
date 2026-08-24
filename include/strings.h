#pragma once
#include <string_view>
#include <string>
#include <vector>

namespace CQ::Strings
{
  inline constexpr std::string_view GAME_NAME = "Consequences: Price of Power";
  const std::string START = "Start";
  const std::string RESUME = "Resume";
  const std::string SAVE = "Save";
  const std::string LOAD = "Load";
  const std::string QUIT = "Quit";
  
  const std::vector<std::string> menuOptions {
    START, RESUME, SAVE, LOAD, QUIT
  };
}


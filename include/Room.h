#pragma once

namespace CQ::Map {
  enum class RoomType
  {
    PARKING_LOT,
    PLAYER_OFFICE,
    BOSS_OFFICE,
    BREAK_ROOM,
    MALE_RESTROOM,
    FEMALE_RESTROOM,
    CAFETERIA,
    ARCHIVES,
    COPY_ROOM,
    IT_ROOM,
    HR,
    EARL_OFFICE,
    EUGENE_OFFICE,
    MILDRED_OFFICE,
    MURIEL_OFFICE,
    DAKOTA_OFFICE
  };
  
  struct Room
  {
    RoomType type;
    bool discovered;
  };
  
  inline const char* roomTypeToString(RoomType type_)
  {
    switch (type_)
    {
      case RoomType::PARKING_LOT:
        return "Parking";
      case RoomType::PLAYER_OFFICE:
        return "My Desk";
      case RoomType::BOSS_OFFICE:
        return "Boss";
      case RoomType::BREAK_ROOM:
        return "Break";
      case RoomType::MALE_RESTROOM:
        return "WC (M)";
      case RoomType::FEMALE_RESTROOM:
        return "WC (F)";
      case RoomType::CAFETERIA:
        return "Cafeteria";
      case RoomType::ARCHIVES:
        return "Archives";
      case RoomType::COPY_ROOM:
        return "Copy";
      case RoomType::IT_ROOM:
        return "IT";
      case RoomType::HR:
        return "HR";
      case RoomType::EARL_OFFICE:
        return "Earl";
      case RoomType::EUGENE_OFFICE:
        return "Eugene";
      case RoomType::MILDRED_OFFICE:
        return "Mildred";
      case RoomType::MURIEL_OFFICE:
        return "Muriel";
      case RoomType::DAKOTA_OFFICE:
        return "Dakota";
    }
    return "?";
  }
} // namespace

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
    EMPLOYEE_1_OFFICE,
    EMPLOYEE_2_OFFICE,
    EMPLOYEE_3_OFFICE,
    EMPLOYEE_4_OFFICE,
    EMPLOYEE_5_OFFICE
  };
  
  struct Room
  {
    RoomType type;
    bool discovered;
  };
} // namespace

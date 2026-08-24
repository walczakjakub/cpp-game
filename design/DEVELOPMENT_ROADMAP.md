# 🎮 Consequences: Price of Power - Development Roadmap

**Last Updated:** August 24, 2026 (design review — see Balance Decisions)  
**Game Type:** Text-based office RPG with SDL rendering  
**Language:** C++ with SDL2  
**Theme:** Orange/Black

---

## 📋 Game Overview

You're a new office employee who was rudely treated by the Main Boss. Your goal: collect evidence against him and take his job. But there are multiple ways this story can end...

### **Win Conditions:**
1. **Normal Win:** Defeat the Main Boss in combat using evidence
2. **Game Over:** Job Security reaches 0 (fired)
3. **Secret Ending:** Work for 11,745 days (45 years) and retire at age 65

---

## ✅ Current Progress (40% Complete)

### **Phase 1: SDL Infrastructure & Menu System** ✅ COMPLETE
**Status:** Working and tested

**Files:**
- ✅ `SDLRenderer.h/cpp` - Window creation, rendering, text display
- ✅ `FontManager.h/cpp` - TTF font loading and management
- ✅ `Menu.h/cpp` - Keyboard-navigable menu with arrow keys, Enter/Space select
- ✅ `colors.h` - Orange/black color scheme
- ✅ `fonts.h` - Font paths
- ✅ `strings.h` - Game name and constants
- ✅ `main.cpp` - Currently running a test menu

**What Works:**
- SDL window with 800×600 resolution
- Menu rendering with highlighted selection
- Arrow key navigation
- Orange text on black background
- Proper cleanup (RAII pattern)

**Concepts Learned:**
- References (`&`) vs Pointers (`*`)
- `const` correctness
- RAII (Resource Acquisition Is Initialization)
- SDL event handling
- Forward declarations
- Rule of Five (deleted copy constructors)

---

### **Phase 2a: Core Data - Position** ✅ COMPLETE
**Status:** Just completed

**Files:**
- ✅ `Position.h` - Grid coordinates for 4×4 map

**Features:**
- Row/col coordinates (0-3)
- Default constructor `Position()`
- Parameterized constructor `Position(int row, int col)`
- Equality operators (`==`, `!=`)
- Validation method `isValid()` for 4×4 grid

**Concepts Learned:**
- Structs vs Classes (when to use each)
- Operator overloading
- `const` member functions
- Signed vs unsigned integers (why we use `int` not `unsigned`)
- Member initializer lists
- The `this` pointer
- Dereferencing with `*`

---

### **Phase 2b: Inventory** ✅ COMPLETE
**Status:** Implemented and tested

**Files:**
- ✅ `Inventory.h` - Class declaration with EvidenceTier enum
- ✅ `Inventory.cpp` - All methods implemented

**What Works:**
- Evidence tier system (NONE, RUMOR, LOCATION, EVIDENCE)
- `upgradeEvidence()` - Validates index, upgrades tier safely
- `getEvidenceTier()` - Returns tier with validation
- `getTotalEvidenceDamage()` - Calculates damage (1, 2, 5 based on tier)
- `isValidIndex()` - Helper function for index validation

**Concepts Learned:**
- Array indexing with `[]` vs `()` (function calls)
- `static_cast<>` for enum ↔ int conversion
- Guard clauses (early returns for validation)
- Helper functions for code reuse (DRY principle)
- Range-based for loops with `const` references
- Switch statements with proper `break` usage
- Difference between tier values and damage values
- Why we can't do math directly on enums (type safety)

---

### **Phase 2c: Player System** ✅ COMPLETE
**Status:** All 21 methods implemented and tested

**Files:**
- ✅ `Player.h` — Class declaration with all systems
- ✅ `Player.cpp` — All methods implemented

**What Works:**
- **Energy System** — Spend, reset, check if depleted (8 hours per day)
- **Job Security System** — Take damage, heal, check if fired, increase max
- **Work Tracking** — Record work hours, check if worked correctly (4+ hours)
- **Age Tracking** — Days worked counter, retirement check (11,745 days), age calculation
- **Position System** — Get/set player location with validation
- **Inventory System** — Access to player's inventory via reference

**Concepts Learned:**
- Class composition (Player HAS-A Inventory, Position)
- In-class member initializers with constants
- `const` member functions (read-only methods)
- Returning references (`Type&`) vs const references (`const Type&`) vs copies
- Why we return references (avoid copies, allow modification)
- Default parameter values in functions
- Encapsulation with getters instead of public setters
- Managing complex state across multiple systems
- Defensive programming with validation
- Member function syntax: `ClassName::methodName()`

---

## ⚖️ Balance Decisions

Settled during design review. Recorded here so we don't re-litigate them later.

| Decision | Value | Reason |
|---|---|---|
| Boss HP | **13** (was 20) | At 20 you needed 4 of 5 pieces at tier 3 or you could not win — the tier system was a checklist, not a choice. 13 opens several viable loadouts, two of them lethal by exactly zero margin. |
| Boss phase 2 threshold | **7 HP** (was 10) | Rescaled to stay at the halfway point. |
| Evaluation heal | **flat 4** (was heal-to-full) | Heal-to-full plus one free evaluation per day made the player unkillable. `Player::heal(int)` already takes an amount, so this is *less* code than heal-to-full. |
| Evaluations carried | **max 3** | Same reason. Turns the fight into resource management. |
| Max job security | **capped at 16** | Was unbounded, so grinding beat playing. |
| Movement cost | **stays free** | 8-hour day − 4-hour work minimum = 4 slack hours, and the average corner-to-random-room distance on a 4×4 grid is 3.2 moves. Charging for movement makes a legal working day impossible. The randomized map is therefore for **discovery**, not routing. |
| Escalating threat / rival employee | **cut** | The job-security cap removes the grind incentive on its own. Not worth the scope. |
| Save slots | **3** (was 10) | It's a ~30 minute game. |

**Known consequence we're accepting:** movement being free plus NPC positions being visible on entry
means the player can scan all 16 rooms for free each hour and only listen where 2 NPCs are standing.
That makes evidence gathering reliable (~3 upgrades/day) rather than random. For a deliberately short
game that's a feature — random gating in a 30-minute game is just frustrating. If it ever plays too
easy, the cheap knob is capping moves per hour. Don't build that on spec.

---

## 🚧 Remaining Work

### **Phase 0: Version Control** ⬅️ DO THIS FIRST
**Time Estimate:** 10 minutes  
**Difficulty:** Easy

The `include/`, `source/` and `design/` directories are **not under version control.** The repo at
`cpp-game/.git` has a single commit tracking `CMakeCache.txt` and a CMake script — none of the actual
game. One bad `rm` and the project is gone.

**Steps:**
- `git init` at the project root
- Write a real `.gitignore` (the current one is empty): `build/`, `xcode-build/`, `*.dSYM/`, `.DS_Store`, `cpp-game/`
- Commit `CMakeLists.txt`, `include/`, `source/`, `design/`
- The stale `cpp-game/`, `build/`, `xcode-build/`, `main.dSYM/` and `source/main.dSYM/` directories are all build artifacts and can be deleted

**New Concepts to Learn:**
- Git basics: `init`, `add`, `commit`, `status`, `log`
- Why build output never belongs in a repo

---

### **Phase 2b.1: Work Evaluations in Inventory** ⬅️ SMALL GAP
**Time Estimate:** 15 minutes  
**Difficulty:** Easy

`Inventory::m_workEvals` exists as a member with **no accessors at all** — it's dead. The design needs
evaluations as the healing item, so this has to be filled in before Phase 9.

**Methods needed:**
```cpp
bool addWorkEval();        // respects the max-3 cap, returns false if full
bool useWorkEval();        // returns false if none held
int  getWorkEvalCount() const;
```

**While you're in there:** `isValidIndex()` hardcodes `<= 4` instead of deriving the bound from
`m_evidence.size()`. Brittle if the evidence count ever changes.

**New Concepts to Learn:**
- Deriving bounds from container size instead of magic numbers
- Returning `bool` for success/failure on state-changing methods

---

### **Phase 3: Game Controller** 🟡 MOSTLY DONE
**Status:** `Game.h/cpp`, `GameState.h` and the state machine all exist and run. `main.cpp` is rewritten.  
**Still missing:** SAVE_MENU / LOAD_MENU / PAUSED / GAME_OVER / WIN / RETIREMENT are empty cases. No `startNewGame()` or `endDay()`. `GameState.cpp`'s `openMainMenu()`/`startGame()` are dead stubs nobody calls — delete them.

**Time Estimate:** 20-30 minutes  
**Difficulty:** Medium

**Files to Create:**
- `Game.h`
- `Game.cpp`
- Update `main.cpp`

**Purpose:**
Main game loop and state management

**Features:**
```cpp
class Game
{
public:
    Game();
    void run();  // Main game loop
    
private:
    enum class State
    {
        MAIN_MENU,
        PLAYING,
        PAUSED,
        GAME_OVER,
        WIN,
        RETIREMENT
    };
    
    void handleMainMenu();
    void handlePlaying();
    void handleGameOver();
    void handleWin();
    void handleRetirement();
    
    void startNewGame();
    void endDay();
    void checkWinConditions();
    
    State m_state;
    Player m_player;
    SDLRenderer m_renderer;
    FontManager m_fontManager;
    TTF_Font* m_font;
    int m_currentHour;  // 0-7
    int m_currentDay;
    bool m_running;
};
```

**Main.cpp becomes:**
```cpp
int main()
{
    CQ::Game game;
    game.run();
    return 0;
}
```

**New Concepts to Learn:**
- State machines
- Game loop architecture
- Enum for states
- Delegating to handler methods
- Object composition at scale

---

### **Phase 4: Map System** 🟡 PARTIALLY DONE ⬅️ NEXT!
**Status:** `Room.h` done. `Map::display()` draws the 4x4 grid and fills the player's cell.  
**Still missing:** `m_rooms` is never initialized (holds garbage) and `display()` ignores it entirely — no `generate()`, no room names, no `?` for undiscovered rooms.

**Time Estimate:** 30-40 minutes  
**Difficulty:** Medium-Hard

**Files to Create:**
- `Room.h` - Enum of room types
- `Map.h`
- `Map.cpp`

**Purpose:**
4×4 office layout with randomized room placement

**Features:**
```cpp
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

class Map
{
    void generate();  // Randomize layout
    void display(SDLRenderer& renderer, TTF_Font* font, const Position& playerPos);
    RoomType getRoomAt(const Position& pos);
    bool isDiscovered(const Position& pos);
    void discoverRoom(const Position& pos);
};
```

**Requirements from Design:**
- Parking lot always in one of four corners
- All other rooms randomized
- Each employee has their own office
- Track which rooms player has discovered
- Display using SDL rendering with current player position highlighted

**New Concepts to Learn:**
- 2D arrays / nested vectors
- Random number generation (`<random>`)
- Map generation algorithms
- SDL rectangle rendering
- Drawing grids with SDL

---

### **Phase 5: Movement System**
**Time Estimate:** 20 minutes  
**Difficulty:** Easy-Medium

**Purpose:**
Navigate between rooms with directional menu

**Features:**
- Movement menu with Up/Down/Left/Right options
- Show room names for known rooms: "Left (Kitchen)"
- Show "Left (?)" for undiscovered rooms
- Female restroom Easter egg:
  - 1st attempt: "I shouldn't go in there"
  - 2nd attempt: "I REALLY shouldn't go in there"  
  - 3rd attempt: Actually enter
- Movement doesn't cost energy
- Validate moves (can't go off map)

**Integration:**
- Uses `Map` to determine valid moves
- Updates `Player` position
- Discovers new rooms

---

### **Phase 6: Working Mechanic**
**Time Estimate:** 20 minutes  
**Difficulty:** Easy

**Purpose:**
Core gameplay loop - working at your desk

**Features:**
- Available only at player's office
- Costs 1 energy (1 hour)
- Flavor text: "You checked your email", etc.
- Must work 4+ hours per day in reasonable intervals
- Not explicitly told to player (they discover this)
- HR lady gives contextual hints

**Day-End Processing:**
- If worked correctly (4+ hours): +1 max job security (**capped at 16**), +1 evaluation (**capped at 3 carried**)
- If didn't work correctly: -1 job security
- Reset energy to 8
- Increment day counter
- Check for retirement ending

**Note on the cap:** max job security capping at 16 is what kills the grind. Without it, the optimal
strategy is "work correctly for 40 days, walk in invincible" and evidence stops mattering. With it,
day 40 is no stronger than day 6 — so there is nothing to farm, and we don't need to build an
escalating-threat system to create urgency.

**New Concepts:**
- Time-based state management
- Reward/penalty systems
- Flavor text randomization

---

### **Phase 7: NPC System**
**Time Estimate:** 30-40 minutes  
**Difficulty:** Medium-Hard

**Files to Create:**
- `NPC.h`
- `NPC.cpp`
- `NPCManager.h`
- `NPCManager.cpp`

**Purpose:**
Living, moving NPCs that create opportunities for evidence

**NPCs:**
1. HR Lady
2. IT Guy
3. Cooking Lady
4. Janitor (lady)
5. Employee 1
6. Employee 2
7. Employee 3
8. Employee 4
9. Employee 5

**Features:**
```cpp
class NPC
{
    std::string m_name;
    Gender m_gender;
    Position m_position;
};

class NPCManager
{
    void moveAllNPCs();  // Called every hour
    std::vector<NPC*> getNPCsInRoom(const Position& pos);
    bool canPlaceNPC(const Position& pos, Gender gender);
};
```

**Rules:**
- NPCs move to random valid room every hour
- Max 2 NPCs per room
- Male NPCs can't enter female restroom
- Employees never in boss office
- Random placement algorithm

**New Concepts:**
- Managing collections of objects
- Movement AI (random)
- Constraint solving
- Gender enum

---

### **Phase 8: Dialogue & Evidence System**
**Time Estimate:** 30-40 minutes  
**Difficulty:** Hard

**Purpose:**
The main progression mechanic - collecting evidence through dialogue

**Features:**
- When player enters room with 2 NPCs: 75% chance to overhear dialogue
- Dialogue is auto-generated between the NPCs present
- Each evidence piece has predetermined dialogue chains
- Progression: Rumor → Location → Evidence

**Example Flow:**
```
// Evidence Piece #0 about Main Boss

Tier 1 (Rumor):
"I heard Main Boss did something shady with the accounts."

Tier 2 (Location):
"Yeah, I think the documents are in the Archives room."

Tier 3 (Evidence):
[Player goes to Archives, opens drawer]
"Found it! Bank statements showing embezzlement!"
```

**Implementation:**
- Dialogue database (hardcoded or data-driven)
- RNG for 75% chance
- Evidence state progression
- Location-based evidence pickup
- New menu options when at evidence locations

**New Concepts:**
- Procedural dialogue generation
- Probability systems
- Content scripting
- State-dependent interactions

---

### **Phase 8.5: Copy Room / Forging** ⬅️ WAS MISSING FROM THIS ROADMAP
**Time Estimate:** 25 minutes  
**Difficulty:** Medium

**Purpose:**
Forge a duplicate work evaluation — the design's best scene, and it had no phase.

**Flow:**
1. Player is in the Copy Room with **no NPCs present** → COPY EVALUATION option appears
2. Player travels to HR with the copy, again with **no NPCs present** → CHANGE DATE / ADD STAMP
3. The forged evaluation becomes usable in the boss fight

**Rules:**
- "No NPCs present" = zero NPCs in the room right now (NPCs move every hour)
- No getting-caught mechanic — if nobody is there, it works
- Still subject to the 3-evaluation carry cap

**Optional (stretch):** forged evaluations heal only 2 instead of 4. Skip if short on time.

**New Concepts:**
- Multi-step state machines (an action that spans two rooms)
- Preconditions on menu options
- Distinguishing item variants in a container

---

### **Phase 9: Boss Fight**
**Time Estimate:** 30 minutes  
**Difficulty:** Medium

**Purpose:**
The climax - final confrontation with Main Boss

**Trigger:**
- Enter Main Boss office
- Select "Sit across the boss" (instead of "Sorry Boss")

**Combat System:**
```cpp
// Boss has 13 HP  (was 20 — see Balance Decisions)
// Two phases:
// - Phase 1 (13-7 HP): Deals 3 damage per turn
// - Phase 2 (6-0 HP):  Deals 4 damage per turn (angry!)

// Combat Menu:
[Blackmail]             // Use evidence pieces
[Show Work Evaluation]  // Heal job security

// Evidence Damage (each piece usable ONCE):
// - RUMOR:    1 damage
// - LOCATION: 2 damage
// - EVIDENCE: 5 damage

// Work Evaluations:
// - Heal a flat 4 job security (NOT to full)
// - Max 3 carried at a time
```

**Why 13 HP:** at 20 HP you needed 4 of 5 pieces at tier 3 or you mathematically could not win —
the tier system collapsed into a checklist. At 13, several loadouts win, two of them by exactly zero margin:

| Loadout | Damage | Result |
|---|---|---|
| 3 x Evidence | 15 | ✓ |
| 2 x Evidence + 3 x Location | 16 | ✓ |
| 1 x Evidence + 4 x Location | 13 | ✓ exactly lethal |
| 2 x Evidence + 1 x Location + 1 x Rumor | 13 | ✓ exactly lethal |
| 2 x Evidence + 1 x Location | 12 | ✗ one short |
| 5 x Location | 10 | ✗ |

**Win Condition:**
Boss HP reaches 0 → You become Main Boss → Credits

**Lose Condition:**
Job Security reaches 0 → Fired → Game Over

**New Concepts:**
- Turn-based combat
- Phase systems
- Resource management in combat
- Win/lose condition checking

---

### **Phase 10: Save/Load System**
**Time Estimate:** 40-50 minutes  
**Difficulty:** Hard

**Purpose:**
Save game state to disk and load it back

**Features:**
- 3 save slots (reduced from 10 — this is a ~30 minute game, 10 slots is over-engineered)
- Save current game state
- Load saved game
- Confirmation dialogs for overwriting
- Confirmation before loading (if game in progress)

**Data to Save:**
```cpp
// Player state
// - Energy, job security, position
// - Inventory (evidence tiers, evaluations)
// - Work tracking, days worked

// Map state
// - Room layout
// - Discovered rooms

// NPC state
// - Positions

// Game state
// - Current hour, current day
// - Evidence dialogue progress
```

**File Format Options:**
1. Binary file (fast, compact)
2. JSON (human-readable, easier debugging)
3. Custom text format

**New Concepts:**
- File I/O (`<fstream>`)
- Serialization/Deserialization
- Data persistence
- Save slot management
- Confirmation dialogs

---

## 📚 C++ Concepts by Phase

### **Already Learned (Phases 1-2a):**
- ✅ References & Pointers
- ✅ `const` correctness  
- ✅ Structs vs Classes
- ✅ Operator overloading
- ✅ Member initializer lists
- ✅ RAII pattern
- ✅ Forward declarations
- ✅ SDL basics
- ✅ The `this` pointer
- ✅ Dereferencing

### **Phase 2b (Inventory):** ✅
- ✅ `enum class`
- ✅ `std::array`
- ✅ Range-based for loops
- ✅ Encapsulation

### **Phase 2c (Player):** ✅ (mostly)
- ✅ Class composition
- ⬜ **Static const members** — not actually done. `Player`'s constants are non-static `const int`
  instance members, so every `Player` carries six copies it can never change *and* the compiler
  implicitly deletes `Player::operator=`. That will bite in Phase 10. Revisit as `static constexpr`.
- ✅ Default parameters
- ⬜ Finish `const`-correctness: `isOutOfEnergy()`, `isFired()`, `hasRetired()`, `getAge()` and
  `workedCorrectlyToday()` modify nothing but aren't marked `const`, so they can't be called on a
  `const Player&`.

### **Phase 3 (Game):**
- State machines
- Game loop patterns
- Enum for states

### **Phase 4 (Map):**
- 2D arrays/vectors
- Random number generation
- Algorithms

### **Phase 7 (NPCs):**
- Collections management
- Vectors of objects
- Pointers to objects

### **Phase 8 (Dialogue):**
- Data structures
- String manipulation
- Probability

### **Phase 8.5 (Copy Room):**
- Multi-step state machines
- Preconditions on menu options

### **Phase 10 (Save/Load):**
- File I/O
- Serialization
- Error handling

### **Cross-cutting cleanups (any time):**
- Ownership: `FontManager::loadFont` returns a raw `TTF_Font*` nobody ever closes, and `~FontManager`
  calls `TTF_Quit()` with it still open. `SDLRenderer` already gets this right — make `FontManager` match.
- Header hygiene: `Map.h` and `Game.h` declare namespace aliases (`Data`, `Render`, `State`, `Map`) at
  **global scope inside headers**, leaking them into every translation unit. Aliases belong in `.cpp` files.
- `strings.h` uses `const std::string` at namespace scope (internal linkage → one copy per TU) while
  line 8 correctly uses `inline constexpr std::string_view`. Make them consistent.
- `FontManager operator=(const FontManager&) = delete;` returns by value; should be `FontManager&`.

---

## 🎯 Current Session Goal

1. Get the project under version control
2. Fix the two known bugs (main-menu quit, font ownership)
3. Start Phase 4: `Map::generate()` — parking lot in a corner, everything else shuffled

---

## 📊 Overall Timeline Estimate

| Phase | Time | Difficulty | Priority |
|-------|------|------------|----------|
| ⬜ 0: Version control | 10min | Easy | **Critical** |
| ✅ 1: SDL & Menu | Done | Medium | Critical |
| ✅ 2a: Position | Done | Easy | Critical |
| ✅ 2b: Inventory | Done | Easy | Critical |
| ⬜ 2b.1: Evaluations in Inventory | 15min | Easy | High |
| ✅ 2c: Player | Done | Medium | Critical |
| 🟡 3: Game Loop | 15min left | Medium | Critical |
| 🟡 4: Map | 35min left | Medium-Hard | High |
| ⬜ 5: Movement | 20min | Easy-Medium | High |
| ⬜ 6: Working | 20min | Easy | High |
| ⬜ 7: NPCs | 40min | Medium-Hard | High |
| ⬜ 8: Evidence | 40min | Hard | High |
| ⬜ 8.5: Copy Room / Forging | 25min | Medium | Medium |
| ⬜ 9: Boss Fight | 30min | Medium | High |
| ⬜ 10: Save/Load | 35min | Hard | Medium |

**Total Remaining Time:** ~4-5 hours  
**Current Completion:** ~40%

---

## 🚀 Next Steps

**Immediate action:**
1. Put the project under version control (Phase 0) — source is currently untracked
2. Fix the main-menu quit bug (`Menu::show` returns -1, `handleMainMenu` ignores it → window won't close)
3. Give `FontManager` real ownership of the font it loads (currently leaked, and `TTF_Quit()` runs with it still open)
4. Then Phase 4: `Map::generate()`

---

*This document is a living roadmap. Update as we complete each phase!*
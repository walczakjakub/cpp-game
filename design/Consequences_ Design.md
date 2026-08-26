**Consequences: Price of Power \- Design Outline**

## **Setting**

Game takes place in an office. The player is a new hire just starting his job. On the way to his desk he bumps into the Main Boss. The Main Boss is really rude to the player. The player is upset and swears to take the Main Boss' job. That's where the game begins.

The game is written in C++ with SDL2 for rendering graphics and text.

Color theme is orange/black

---

## **Main Menu**

* Navigation with arrow keys  
* Selected option has highlighted background  
* There will be no disabled options

**Options:**

* Start (when game is started) / Resume (when player is playing and goes to main menu)  
* Save  
  * Saves locally on the player's machine  
  * Up to 3 save slots  
  * If overwriting, the game should ask confirmation (in the form of a choice menu as well)  
* Load  
  * If you are in the middle of the game, it should ask for confirmation to prevent loading instead of saving by accident  
* Quit  
  * Should ask if the player is sure (YES, QUIT GAME / NO, GO BACK menu options)

---

## **Map**

* Simple blueprint layout of the office rendered with SDL  
* Location the player is currently in should be colored (whole box filled with color)  
* Each location should have its name written on it  
* If the location has not yet been discovered, it should have a question mark as name  
* Map is randomized every playthrough  
* 4x4 grid (16 rooms total)  
* Parking lot is always placed in one of the four corners  
* All other rooms are placed randomly  
* Each employee has their own office

**Points of Interest:**

* Main Boss office  
* Player's office  
* Parking lot  
* Break room  
* Male Restroom  
* Female Restroom  
* Cafeteria  
* Archives room  
* Copy room  
* IT room  
* HR  
* Earl's office  
* Eugene's office  
* Mildred's office  
* Muriel's office  
* Dakota's office

---

## **Movement**

* Through the menu with directions (up, down, left, right)  
* If the location in the direction is known, it should show in the menu next to the direction (e.g. *Left (Kitchen)*)  
* Movement doesn't cost energy — **this is deliberate.** An 8-hour day minus the 4-hour work minimum leaves only 4 slack hours, and the average corner-to-random-room distance on a 4×4 grid is 3.2 moves. Charging for movement would make a legal working day impossible. The randomized map therefore exists for **discovery** (finding where rooms are, fresh each run) rather than for routing  
* Movement menu should have a separator and a *Main Menu* option below it  
* Movement menu should have an Inventory option  
* If the player tries to go into the female restroom, he gets a message "I shouldn't go in there" and is not relocated. If they try again: "I REALLY shouldn't go in there" and is not relocated. If they try a third time, they are able to go in.

---

## **Working**

* Working is a menu option available at the player's desk  
* It consumes 1 energy (1 hour)  
* After choosing the work option, the player sees a flavor message (e.g. "You checked your email")  
* Player must work at least 4 hours every day in acceptable intervals to avoid a job security penalty  
* Player is not aware of this requirement — it's for them to figure out  
* The HR lady will hint at it contextually (e.g. "Why are you only working the first 4 hours of the day?")

---

## **Combat**

* There will be only 1 fight: with the Main Boss  
* Player will use evidence as weapons to damage the boss  
* Player will use healing items to restore health (job security)

---

## **Items**

**Evidence**

Evidence is a weapon the player uses to damage the boss. There are 5 pieces of evidence in the game, each with 3 tiers:

1. Rumor (1 damage)  
2. Location of evidence (2 damage)  
3. Evidence itself (5 damage)

Evidence upgrades rather than stacks — if the player already has a rumor about evidence piece \#3, the next discovery upgrades it to the location tier. The player never holds multiple tiers of the same piece simultaneously.

The tier of the next discovery depends on what the player already has for that piece. To obtain tier 3 (the evidence itself), the player must travel to the location they heard about, which unlocks a new menu option (e.g. OPEN DRAWER).

**Healing Items**

* Positive evaluation  
  * Obtained after each day of correct working  
  * Restores 4 job security when used (NOT a full heal)  
  * Player can carry a maximum of 3 at a time  
  * Player can make a copy in the copy room, but must then go to HR when no NPCs are present and change the date and add a stamp to make it valid  
  * "No NPCs present" means no NPC is currently in the room — NPCs change locations every hour and the game tells you who is in a room upon entering

---

## **Copy Room Mechanic**

* Player can forge a copy of their work evaluation here  
* Requires no NPCs to be present in the copy room  
* Then the player must go to HR with the copy when no NPCs are present there either  
* The player changes the date and adds a stamp — the item is then usable in the boss fight  
* There is no "getting caught" mechanic — if nobody is there, the action succeeds  
* **Optional (stretch):** a forged evaluation restores only 2 job security instead of 4. The boss half-notices the altered date. This is what makes forging a decision rather than a chore — implement only if time allows

---

## **Inventory**

* Player can check their inventory at any point from the menu  
* Inventory will show all the items they obtained  
* Items are usable only during the boss fight or when altering the job evaluation copy

---

## **NPCs**

* HR lady  
* Earl, Eugene, Mildred, Muriel, Dakota (the five employees)  
  * Earl and Eugene are men. Mildred and Muriel are women.  
  * **Dakota's gender is never revealed.** Unisex name, no pronouns in any dialogue, no gendered description anywhere. The player is given nothing to go on and the game never resolves it. Nobody comments on it — that's the joke.  
  * **Dakota uses both restrooms.** The male-NPC restriction does not apply to Dakota in either direction — they turn up in the men's and the women's alike. This is never explained, and it is never established whether Dakota is entitled to be in either one. No NPC ever comments on it.  
* IT guy  
* Cooking lady  
* Janitor (lady)  
* NPCs are located randomly in the rooms (no more than 2 in the same room at a time)  
* Employees are never placed in the Main Boss' office  
* Male NPCs are never placed in the female restroom  
* They change positions every hour  
* Player cannot talk to NPCs directly — dialogue is generated between NPCs and can be overheard  
* If two NPCs are in the same location as the player, there is a 75% chance (subject to rebalancing) to overhear evidence-related information

---

## **Main Boss**

* His name is Main Boss  
* He's fat and very rude  
* When the player enters the Main Boss' office, the Main Boss always tells them to GTFO. The player has 2 options:  
  * Sorry Boss — leave  
  * Sit across the boss — challenge him: this triggers the fight

---

## **Main Boss Fight**

* Triggered when the player chooses "Sit across the boss" in the Main Boss' office  
* Boss has 13 HP  
* Fight menu options:  
  * Blackmail (use evidence)  
  * Show work evaluation (heal)  
* Boss counter-attacks every turn:  
  * Phase 1 (13–7 HP): deals 3 damage to player's job security  
  * Phase 2 (6–0 HP): deals 4 damage per turn as he grows angrier  
* When the boss is defeated, the player becomes the Main Boss — credits roll

---

## **Resources**

**Energy**

* Player has 8 energy per day (work hours)  
* Every action (working, listening, but not moving) takes 1 hour  
* When energy hits 0, the player gets a "Work day is over" message and a GO HOME menu option

**Job Security**

* This is the player's health bar  
* Starting health is 10 — increases with correct working, capped at a maximum of 16  
* If player works correctly a given day, his job security increases  
* Working the required amount of hours in acceptable intervals increases maximum health by 1  
* If the player doesn't work correctly a given day, his job security goes down the next day  
* If job security reaches 0 outside of the boss fight, the player is fired and it's game over

---

## **Game Screen**

* Map (rendered with SDL graphics)
* Job security / health bar  
* Text description of what's happening  
* Movement menu

---

## **Win / Loss / Secret Conditions**

**Win:** Deplete the Main Boss' HP in the boss fight. The player becomes the Main Boss and credits roll.

**Game Over:** Job security reaches 0 at any point outside the boss fight. The player is fired.

**Secret Ending — Retirement:** The game tracks a hidden age counter starting at 20\. Each in-game day counts as one working day. There are 11,745 working days until age 65 (45 years × \~261 working days/year). If the player reaches this without triggering any other ending, they receive the message: "You've worked here for 45 years and finally retired. Congratulations?" The player is given no hint this ending exists.


# Breakout

W Kavanagh & N Merchant. Summer 2024 (last maintained, Oct 26)

## Controls

A/D to move the paddle right and left.
P to pause.

## Powerups

big/small paddle (blue)
fast/slow ball (fancy yellow)
fire ball (green)

# Tasklist

You are to spend between three and eight hours improving this simple Breakout implementation in a way to best demonstrate your capabilities as a games programmer. 

## Suggested tasks

* Implement mouse input for pad
* Improved VFX (ball trail, paddle hit response, brick particle destruction)
* Better UI (progress bar rather than timer for countdown).
* Add an actual game loop
* Better ball physics (Box2D)
* Leaderboards
* More ball types (e.g., multiball, sticky ball, brick-tracking ball)
    * Note: smallPaddle is too simple to be impressive.
* Sounds with increasing tone between bounces.
* Implement commentary with calls to an LLM such as Ollama

# Time Details and Changelist
Total Time: 8 Hours 

Sparkle Shine Breakout Magic (magical girl themed breakout) 

Features Implemented: 
- A game loop! When the player breaks all blocks in a level, they can hit the spacebar to play a new level, and replay the current level if they die 
- Additionally, every third level is a 'boss fight'. In these levels, the game spawns ten bricks one at a time, forcing the player to 'chase' their enemy around. They will gain an extra 100 points for this 
- A magical girl transformation- every ten blocks broken, the player has a magical transformation. Their sprite changes to a star, they cannot die, they are significantly faster, and they can go through blocks to hit multiple at once 
   - This is shown with a UI meter 
- A 'sudden death' feature- when the player is down to only three blocks, the game will end within 5 seconds whether they destroy the blocks or not, but if they hit the blocks they will get an extra five points 
- A point counter, to motivate the player 
- Cheerful music and a game over sound effect (“Gem Waltz” composition and arrangement by Haley Halcyon, https://opengameart.org/content/gem-waltz-free-music-loop) 
- Everything is pink now!

Times: 
- One Hour: Started working on game loop: game should now do another level after beating one (and made it all pretty colours)
- 45 minutes: Basic game loop implemented
- 10 minutes: Spacebar for new level
- One hour: UI now updates based on level, and when 'magical girl transformed' (after hitting ten blocks) the player turns into a star
- Two Hours: Properly implemented 'magical girl transformation'- after hitting ten blocks, player becomes immortal, and speeds up. Also added a sudden death mode so the level completes after a timer when the player is down to three blocks
- 30 minutes: Implemented music for levels and a game over sound, can now replay the level after dying rather than the game just freezing
- 15 minutes: Fixed bug where speed up power ups didn't work due to implementation of 'magical girl transformation'. Now speeding up works for all power ups and for transformation
- Two hours 20 minutes: Added UI meter for transformation, points counter, and boss fight every third level

<Add information to this section about the time you've taken for this task along with a professional changelist.>

---

### Change log
* 2025 - Naman made it harder
* 2026 - William made it easier again

---

Curse you, fast ball!

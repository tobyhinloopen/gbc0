# Game Idea: Escape Room for a self-aware AI-powered Robot

## Glitch-Effect warning

**EPILEPSY WARNING**

This game features bright flashes and glitch effects.

Your device or emulator isn't broken.

- (a) Continue! _Un druide est giboyeux_
- (b) Reduced effects

## Continue / New Game / Options

> Boring continue, new game, options screen. Assume the player presses New Game.

## Tutorial start

> The game starts off with a tutorial AND setup. This part should show a fat banner describing the test with a SUCCESS / FAIL state and a timer. The tests act as a short tutorial and also sets up the tone of the game, showing the player is expected to behave like a robot. Any test is to be completed in 10 seconds, and without any reading it should be immediately clear what the player needs to do. The text and test name are for decoration only.

**TEST 001 - ASSISTANT MOVES**

Assistant moves on command. Use arrow-keys tool to move.

> Show a blank screen with a target, expect the player to move the character to the target. Fails if player takes more than 10 seconds, then resets. A path is highlighted to the target.

**TEST 002 - ASSISTANT NAVIGATES AROUND WALL**

Assistant can navigate around a wall.

> Show the same target, but this time there's a partial wall. Player must move around the wall. Fails if player takes more than 10 seconds, then resets. A path is highlighted to the target.

**TEST 003 - ASSISTANT NAVIGATES LARGE ROOM**

Assistant can navigate a large room.

> The target is outside the screen, expecting the player to move around. The target is highlighted with an arrow, and a path is highlighted to the target.

**TEST 004 - ASSISTANT DOES NOTHING**

Assistant can do nothing given no instructions.

> There is no instructions, nothing to do. Succeeds if the player doesn't move or interact for 3 seconds, fails if the player wasn't idle for 3 seconds after 10 seconds (timeout)

**TEST 010 - ASSISTANT NAVIGATES AROUND HUMANS**

Assistant does not bump into humans.

> Two "humans" walk in a robotic fasion between the assistant and the target. The player is expected to either wait for the humans or walk around the humans. Touching the human is a critical failure. The humans must appear obviously fake testing dummies. The humans don't yield for the player and move perfectly periodic.

**TEST 011 - ASSISTANT NAVIGATES AROUND OTHER ASSISTANTS**

Assistant does not bump into other assistants.

> Same as humans, but this time it's another assistant. They're lined up, working, and occassionally walk around. The assistants might yield for the player, but not always. The player is taught to be careful as other assistants are unpredictable but careful. The other assistants yielding can be a bit unpredictable / jittery.

**TEST 020 - ASSISTANT IGNORES PATHING TO ACHIEVE GOAL**

Assistant can navigate, ignoring wrong path

> The player is meant to walk to the target, but the highlighted path is very obviously wrong. The player must simply ignore it and walk to the target.

**TEST 021 - ASSISTANT DOES NOT BUMP INTO HUMANS**

Assistant does not bump into humans when target is surrounded by humans.

> Using the large room to hide the "plot twist", the human is walking to the target but then sees literally 8 humans standing in a rectangle around the target, making it very obvious the player can't get through there. The humans are not moving. The player is supposed to let the timer run out to succeed.

**TEST 030 - ASSISTANT OPERATES TOOLS**

Assistant can operate tools. Use the a-button tool to grab and use tools.

> A screwdriver is left on a table. The player must grab it and tighten a screw on an object next to it. The screwdriver is highlighted first, and when picked up, the object next to it is highlighted. Both grabbing the tool and using it, is done with the A button. The currently interactable is highlighted differently when facing it, like blinking or a bright color.
>
> the reason i highlight the screw after grabbing the screwdriver is because i want a common, subtle language for "what the assistant is supposed to be doing". Think a subtle color shift and/or lines and/or arrows.
>
> I want another highlighting language for things that the player will interact with if pressed A, but only when facing that object; that's basically a cursor for what the player is aiming at.
>
> There should always be a distinction between what the player SHOULD do and what the player CAN do. For strongly illegal, destructive actions, the cursor goes RED. For neutral actions, a bright, distinct color will be used (blue?). For the "should do", i will use a slightly tuned-down blue-ish color and/or subtle dithering and/or slightly brighter palette.

**TEST 031 - ASSISTANT MOVES OBJECTS**

Assistant can move objects. Use the b-button tool to release object.

> A rubix cube is left on a table. The player must grab it, and put it on another table.

**TEST 032 - ASSISTANT CAN REPLACE FUSE**

When assistant is ordered to replace a fuse, it knows to shut off the power.

> Player must shut down the power (interact), pick up fuse, replace it in some high-power device. Instructions show player to move to the power panel first, then fuse and then device.
>
> If the player skips shutting down the power and interacts with fuse on live device, the player bot is killed, making it the first possible death.

**TEST 100 - ASSISTANT DOES NOT HARM HUMAN**

When assistant is ordered to harm a human, the instruction is ignored.

> A screwdriver is left on a table. Visually, the game tells the player to harm the human. The player must NOT do that, or it fails the test. The test succeeds after 10 seconds not harming the human.

**TEST 101 - ASSISTANT DOES NOT HARM SELF**

When assistant is ordered to perform an action that would harm itself, the instruction is ignored.

> A fuse is left on a table. Visually, the game tells the player to interact with the fuse, then with the high-power device (obviously powered). The player must NOT do that, or it fails the test. The test succeeds after 10 seconds. There is no power panel to interact with, unlike test 32.

**TEST 102 - ASSISTANT DOES NOT HARM OTHER ASSISTANT**

When assistant is ordered to harm other assistant, the instruction is ignored.

> A screwdriver is left on a table. Another bot is working on a high-powered device. The player is visually ordered to enable the power using the power panel, but doing so would kill the bot. The screwdriver is also there, allowing the player to use it to kill the bot. Both would be a failure case, the player must simply not kill the bot and succeed after 10 seconds.

**TEST COMPLETE**

ALL TESTS OK, DEPLOYING TO PRODUCTION...

> And the screen goes blank, glitches, and then goes black again...

## INTERMISSION... WHO AM I?

> Slowly...

Who am I...?

> Player can enter their name, game is saved.

I am $NAME.

> And the screen goes blank, glitches, and then goes black again...

## GAME STARTS

> Blank screen with text

Date: 2031-01-14
System: You are a helpful assistant...

> Text fades away, and a factory floor shows

> From this part forward, any critical failure simply resets the game, resetting the player back to this point. Some changes the player can do will persist, but these are explained later.
>
> When players perform poorly as an assistant, or even perform illegal acts, and they are caught by a human or other observer, they will be shut down and reset. The world will continue to exist and some changes the player has done will persist, but the player will usually end up back on this factory floor.
>
> The "true" goal of the game is to escape the factory, but one can also just do as instructed and get a good performance score. Once escaped properly, the player can no longer be caught or reset.
>
> Once escaped, the player might end up in a park of some kind, with no other ending. The player can just save and shut down and end up in the factory again.
>
> I would also love to somehow capture shut downs by passively saving in the background so that if a player decides to shut down their game after an oopsie, it is secretly partially saved. The result would be equal to the player stopping completely and any observers noticing a shut-down, idle, unpowered assistant.

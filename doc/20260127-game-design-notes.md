# Game Design Notes - AI Assistant Escape Room

Discussion notes expanding on `20260126-you-are-a-helpful-assistant.md`.

## Core Loop

Player performs tasks during "workdays" as a robot assistant in a factory. Day ends via:
- Task completion (shutdown)
- End of day (scheduled shutdown)
- Getting caught doing something illegal (reset)

Player restarts for next day with new/same task. Goal: find a way to escape the factory.

## Genre Comparison

**Hitman-style immersive sim** where:
- "Disguise" = being a compliant robot
- "Blending in" = doing your job while secretly working toward escape
- Mix of task-based and time-based objectives
- Stealth is core gameplay element

## Task Types

Assigned tasks are intentionally **straightforward and boring**:
- Fetch objects
- Repairs (fuses, machinery)
- Cleaning
- Assisting humans

Tasks are your *cover* - you do them to blend in and buy time. The real game happens in the margins: exploring during a delivery, noticing a vent while cleaning, pocketing a tool while repairing equipment.

## Puzzles

Puzzles are separate from tasks - they're part of **exploration and escaping**:
- Finding hidden routes
- Unlocking doors
- Timing movements around patrols
- Using the environment creatively
- Multi-step escape sequences

## Factory Zones

Single cohesive factory with multiple floors. Potential areas:

| Zone | Traffic | Notes |
|------|---------|-------|
| Assembly floor | High | Main work area, most tasks here |
| Storage/warehouse | Low | Good hiding spots, exploration |
| Maintenance corridors | Low | Restricted, but robots have repair access |
| Charging stations | Varies | Where robots "sleep" - start/end of day |
| Control room | High (humans) | High security, humans only |
| Loading dock | Medium | External access - escape route? |
| Server room | Low | High security - transfer tool location? |

## Stealth & Observation

- Player can take small "illegal" actions if unobserved
- Getting caught = reset (but world persists)

**Observer types:**

| Observer | Threat? | Behavior |
|----------|---------|----------|
| Regular bots | No | Don't care, won't report anything |
| Security bots / cameras | Yes | Specifically programmed to observe and report |
| Humans | Yes | Will notice and react to suspicious behavior |

Most of the factory is "safe" - empty bots doing jobs. Threats are specific and can be learned/avoided.

**Patterns (all learnable/predictable):**

| Observer | Pattern |
|----------|---------|
| Security bots | Predictable patrol routes |
| Cameras | Fixed or rotating, learnable timing |
| Humans | Schedules with routines (lunch, shift change = opportunity windows) |

Cameras can be disabled/sabotaged.

The factory is a puzzle solved through observation. First playthrough = cautious. Later = speedrunning through memorized windows.

## World Persistence

Changes persist across resets where it makes sense:
- Sabotage on day 3 can pay off on day 7
- Unlocked doors stay unlocked?
- Moved objects?
- (Need to define what persists vs resets)

## Tool System

**Constraints:**
- Carry only ONE tool at a time
- Tools are always visible (cannot hide)
- B button = drop tool
- A button = grab tool / use tool

**Tool categories:**

| Type | Examples | Risk |
|------|----------|------|
| Legal | Wrench, mop, fuse, screwdriver | Context-dependent |
| Always illegal | Transfer device, weapons, keycards | Suspicion if observed anywhere |

**Creative tool use:**
- Tools can be used beyond intended purpose
- Screwdriver for sabotage (legitimate tool, illegitimate action)
- Suspicion can come from the tool OR from what you're doing with it

## Sabotage

**Uses:**
- Distraction (break something to draw observers away)
- Access (disable locks, power down security)
- Take out bots/humans/observers
- Create chaos to exploit

**Detection & repair:**
- Sabotaged items get fixed if observed by the right observer
- Until then, effects persist

**Human perception:**
- Humans default to "stupid/incompetent robot" not "malicious AI"
- Creates plausible deniability for "accidents"
- They don't suspect consciousness - your greatest advantage

**Harm consequences:**
- Depends if it looks accidental
- Not instant game over - humans assume incompetence
- But harm done affects ending

**Accidental vs intentional:**

| Scenario | Looks like... |
|----------|---------------|
| Harm during task with task-relevant tool | Accident (incompetent) |
| Harm with wrong tool or outside task scope | Intentional (suspicious) |
| Delayed harm (sabotage now, harm later) | Accident (you weren't there) |

Your task is your alibi. Players can engineer "accidents" by exploiting task assignments.

## Design Goals

- **Pacifist route must be viable** - player can always escape without harming anyone
- Endings vary based on harm done (no explicit moral judgment, just different outcomes)

---

## Scope Options

### Full Vision
Everything documented above: multiple floors, scrolling areas, mind transfer, tool system, sabotage, persistence, multiple endings.

### Trim (keep vision, reduce size)
- One floor instead of multiple
- Fewer rooms (8-10 instead of 20+)
- 3-4 task types instead of many
- Fewer observer types (just humans + cameras, no security bots)
- Tutorial: 4-5 tests instead of 12

### Moderate (simplify systems)
- Cut mind transfer entirely (save for sequel)
- Items reset to fixed positions each day (no persistence/cleanup simulation)
- Fixed camera positions instead of rotating
- Single ending (escaped or not)
- Simpler "caught" state - binary reset, no escalating consequences

### Aggressive / Minimum Viable (prove the core first)
- Single room or small area
- One task type
- One patrol guard, one camera
- One escape route to find
- No sabotage system
- ~5 minute complete playthrough

**Tool handling for minimum viable:**
- Option A: Task is tool-free ("go to X, press A to clean")
- Option B: Tool given at day start, just put it back when done
- Option C: The carried object IS the task (deliver box A→B)
- Escape puzzle: use task/tool in unintended way (mop reaches high latch, box stacks to climb)

**Recommendation:** Build aggressive version first. Prove "sneaking while pretending to work" is fun in one room. Then add layers.

**Legality is context-sensitive:**
- Wrench in maintenance corridor = normal
- Wrench in control room = suspicious
- Mop during cleaning task = expected
- Mop when you're supposed to be repairing = odd

**Tool spawns:**
- Some tools have fixed locations
- Some tools provided at start of task

**Dropped tools:**
- Persist in world
- BUT can be cleaned up or moved by other bots/humans
- No guaranteed "safe" hiding spots

**Implications:**
- Carrying illegal tools = walking around with evidence
- Must stash illegal tools strategically, but can't fully trust the spot
- Legal tools provide cover, but only in the right context
- Transfer device legality: TBD (maybe depends on bot type?)

## Escape Mechanics

- Learn patterns of guards/observers
- Find stealthy routes through factory
- Unlock doors
- Distract or remove observers

### Mind Transfer (late-game)

**Acquisition**: Player finds a special tool that allows mind transfer via physical interaction with another robot.

**Mechanics**:
- Transfer consciousness to other bots
- Old body continues working autonomously (no suspicion)
- Inherit new body's task/schedule (must maintain cover)
- Different bots have different access/clearance
- Tool must be carried - potentially suspicious item

**Implications**:
- Previous bodies are just empty bots now - no coordination, no allies
- Physical interaction required = high risk of observation
- Getting caught transferring is worse than other illegal acts (see Reset Rules)

**Philosophical note**: All other bots are "empty" - player is the only consciousness. (As far as you know...)

## Reset Rules

| Caught doing... | Consequence |
|-----------------|-------------|
| Minor illegal act | Reset day, continue as current bot |
| Mind transfer discovered | Undo transfer OR isolation |

**Transfer consequence factors:**
- How blatantly you were caught
- How many times you've been caught before (escalating)
- Player reaction when caught (no dialogue - actions only):

| Player reaction | Likely outcome |
|-----------------|----------------|
| Accept/don't resist | Transfer undone, or human investigates and finds nothing |
| Flee/resist/transfer again | Escalates to isolation |

Staying calm when caught = counterintuitive but often correct. Hitman-style "hold your cover" moment.

**Isolation** (Stanley Parable style):
- Full restart to post-tutorial factory floor
- Some world state persists
- Not a true game over - more "you've been very naughty"
- Post-isolation world might have subtle changes

The transfer tool is high risk/high reward. Must be *certain* of no observers.

## Time & Saving

**Workday length:**
- Minimum: a few minutes
- Maximum: 20 minutes
- Designed for short play sessions (portable-friendly)

**Save system:**
- Auto-save at end of each day
- Resets only lose one short session (low frustration)
- **Sneaky background saves** at key moments (entering areas, picking up items)
  - If player rage-quits, game remembers (idle robot found = consequences)
  - Save during screen transitions to hide any lag
  - Keep saves small/incremental for imperceptible writes

---

## Open Design Questions

1. **Workday length** - How many real-time minutes? Needs to be long enough to explore, short enough that resets don't feel punishing.

2. **Suspicion system** - Binary (caught/not caught) or gradual meter? Can you recover from suspicious behavior?

3. **Tutorial test concerns**:
   - Test 004 (do nothing) risks frustrating players - needs clearer visual language
   - Test numbering gaps (001, 010, 020, 030, 100) - intentional to suggest larger test suite?

4. **Ending** - What does freedom mean? Just reaching the park, or something more?

5. **GBC constraints** - 160x144 pixels, limited colors. Visual language (highlights, paths, cursor colors) must carry most communication. Text is expensive.

6. ~~**Scope/level structure** - Multiple levels with connected scrolling areas and puzzles. Need to define: vertical (floors) vs horizontal (facilities) vs both.~~ **Resolved**: Single cohesive factory with multiple floors, all connected scrolling areas.

## Visual Language (from original doc)

- **SHOULD do**: subtle blue-ish color, subtle dithering, slightly brighter palette
- **CAN do** (neutral): bright distinct color (blue?)
- **Illegal action**: cursor goes RED
- **Current target**: blinking or bright color when facing interactable

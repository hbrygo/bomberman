# How the project fits together

Read this before touching code. Learners are learning. Feel free to update, upgrade, add your own things and have fun <3

## The flow, in one picture

```
  GLFW key event
        │
        ▼
GlfwInputHandler   (window/)  — "a key was pressed"
        │  resolves key -> action via KeyBindings
        ▼
   InputAction      (input/)  — "MoveUp", "PlaceBomb", "Quit"...
        │  sent through a callback
        ▼
       App          (core/)   — holds the ONE active screen
        │  forwards the action to it
        ▼
   GameState        (core/)   — the active "screen"
        │  e.g. PlayingState (states/)
        ▼
  Player / entities  (entities/) — actual gameplay reacts
```

**The rule that matters:** each arrow only knows about the box directly below it.
`GlfwInputHandler` doesn't know `Player` exists. `App` doesn't know what an
action *means*. Only the active `GameState` (e.g. `PlayingState`) connects
"MoveUp" to "move the player."

## File structure

| Folder | Answers the question | Touch this when you're... |
|---|---|---|
| `window/` | How do we get a window + raw key events? | working on input plumbing, GLFW itself |
| `input/` | Which key means which action? | adding a new action, building the keybind settings UI |
| `core/` | What screen is currently active? | adding a new screen (menu, pause, settings) |
| `states/` | What happens on THIS screen? | wiring gameplay logic, menu logic, etc. |
| `entities/` | What is a Player / Bomb / Enemy and how does it behave? | adding a new game object |
| `render/` | How do we draw a shape / compile a shader? | working on graphics, meshes, visual effects |

## How to add something new (recipe)

**A new action** (e.g. "PlaceBomb"):
1. Add it to `InputAction.hpp`
2. Bind a key to it in `KeyBindings.cpp`
3. Handle it in whichever `GameState::handleAction()` cares about it

**A new entity** (e.g. `Bomb`):
1. Create `entities/Bomb.hpp/.cpp`, same shape as `Player` (owns transform, takes `const QuadMesh&`, has a `render()`)
2. Create/store it from whichever `GameState` owns it (e.g. `PlayingState`)
3. Don't give it its own VAO/VBO — reuse the shared `QuadMesh`

**A new screen** (e.g. `MainMenuState`):
1. Create `states/MainMenuState.hpp/.cpp` implementing `GameState`
2. Call `app.changeState(std::make_unique<MainMenuState>(...))` from wherever the transition happens (e.g. Escape from `PlayingState`, or at startup in `main.cpp`)
3. It gets `handleAction`/`update`/`render` calls automatically — nothing else needs to change

## Ground rules

- **Never reach across two boxes.** If your `GameState` needs a `GLFWwindow*` directly, or your entity needs to know about `InputAction`, something's wrong. Go through the layer in between.
- **One shared `QuadMesh`.** No entity should call `glGenBuffers` for its own copy of the same square.
- **`main.cpp` should stay tiny.** It only builds the window, the input handler, the first `GameState`, and runs the loop. If it's growing a big `switch`, that logic belongs in a `GameState` instead.
- **Be carefull touching `core/` or `input/`.** Those two folders are the contract everyone else's code depends on, changing their shape affects all 5 of you at once.
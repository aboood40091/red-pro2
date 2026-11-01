# UI system (layout / 2D)

NSMBU draws menus and HUD through Nintendo `nw::lyt` layouts wrapped in game-specific C++.
The port can hook or replace this stack once the guest symbols below are understood and mirrored in runtime code.

## Layers

```text
CommonWindowMgr (singleton 0x101D15E8)
  └── CommonWindow + PaCursor          modal yes/no and message windows

AttentionScreen, ChangePlayerNum, …    full-screen or overlay AnimLayout screens

AnimLayout<N> : AnimLayoutBase : Multi2D
  └── ArcResAccMulti, UtilCursorButtonMgr, FlexibleTextBox lists (build time)

Multi2D (0xE88 bytes)
  └── LayoutObj, LayoutAllocator, DrawInfo, anim maps, TagProcessor
```

`GamesceneBase` ties course gameplay actors and coin HUD text into the same layout world (`registerActor`, `setCoinNumText`).

## Multi2D responsibilities

Guest address block `0x026711C8`–`0x02672E98`.

- **`createLayoutObj` / `initializeLayoutObj_`**: load `.bflyt` / `.bflan` through `LayoutObj` and register anim resources.
- **Pane registration**: `NPaneRegister`, `PPaneRegister`, `TPaneRegister`, `BPaneRegister`, `WPaneRegister`, and `Pa*` variants cache pointers into `nw::lyt` panes by name (see `find*ByName_` helpers).
- **Animation**: `animResRegister`, `animStartSetup` family, `animPlay`, `setPlayerColor`, frame get/set.
- **Draw**: `draw(proj_mtx)` uses embedded `nw::lyt::DrawInfo` and the root pane from `getRootPane`.
- **Text**: `setTextBoxMessageFromTextID` resolves message IDs through the project text database; `TagProcessor` handles layout tag codes in text boxes.

Decomp: `vendor/decomp/include/layout_sys/AnimLayout.h`, `vendor/decomp/src/layout_sys/Multi2D.cpp`, `AnimLayoutBase.cpp`, `LayoutAllocator.cpp`, `TagProcessor.cpp`.

## Screen pattern (FState + AnimLayout)

Screens such as `AttentionScreen` and `ChangePlayerNum` follow the same shape:

1. Embedded `AnimLayout<N>` with a fixed anim buffer size.
2. `FStateMgr` drives `In` / gameplay / `Out` (or `CloseRequest`) states.
3. `create()` calls `readResource` + `build`, registers anim and pane names from rodata tables.
4. `execute()` runs the state machine and calls `Multi2D::animPlay` on layer `0xE` (same id as other UI).
5. `draw` / `drawDRC` gate on visibility and target display, then delegate to `Multi2D::draw`.

State IDs are guest globals (for example `AttentionScreen::StateID_In` at `0x1020B588`).

## Pause menu and CommonWindowMgr (modal UI)

`CommonWindowMgr` (singleton `0x101D15E8`, disposer `0x024BC444` / `0x024BC874`) owns one embedded `CommonWindow` (`0x1ABC` bytes).
The pause dialog uses `CommonWindow::cType_WinText_Pause` via `CommonWindowMgr::open`.
Message copy can differ through `CommonWindow::Type msg_text_type` while the window kind stays pause.

Guest flow:

1. `CommonWindowMgr::create` calls `CommonWindow::create`, which runs `Multi2D::createLayoutObj`, `AnimLayoutBase::readResource`, `build`, pane registration, and `PaCursor` setup on the window layout at `+0x24`.
2. `CommonWindowMgr::execute` runs `CommonWindow::execute` (state machine + `animPlay` on layer `0xE` when visible).
3. Pad handling: `CommonWindowMgr::processPadTrig_OneButton` / `processPadTrig_TwoButtons` delegate to `CommonWindow::processPadTrigOneButton` / `processPadTrigTwoButtons`, which install a handler from `lookupPadTrigFuncOneButton_` / `lookupPadTrigFuncTwoButtons_` (indexed by `CommonWindow::Type` at `+0x1AA0`) into `+0x1128`, then drive `PaCursor` and `FStateMgr` transitions.
4. Draw: `CommonWindowMgr::draw` / `drawDRC` / `drawDRC_System` call `CommonWindow::draw` / `drawDRC`, which gate on `mIsVisible`, `mIsFadeOut`, and DRC flags before `Multi2D::draw`.

Decomp headers: `vendor/decomp/include/game/CommonWindowMgr.h`, `vendor/decomp/include/layout/CommonWindow.h`.
Implementation: `vendor/decomp/src/layout/CommonWindowMgr.cpp`, `CommonWindow.cpp`, `PaCursor.cpp`.

## Mod integration

Mods can touch UI in three different places.
They are not interchangeable.

**Port overlay (`nsmbu.Gui`).**
Live today in [api.md](../../../docs/modding/api.md).
Draws shapes and text in 1280×720 space on top of the final picture.
It does not use `Multi2D`, `.bflyt`, or GamePad cursor routing.
Good for counters, debug HUD, and simple indicators.
Bad for pause-style windows that must respect DRC vs TV, `PaCursor`, or game font/message IDs.

**Guest layout system (this document).**
Pause, file-select chrome, course stock HUD, and most menus run here.
Integration means hooking guest functions or (later) calling them through `nsmbu.Hooks.call`.
Addresses below are USA v1.3.0; hook files and `GC(0x…)` use the same digits ([names.md](../../../docs/developer/names.md)).

**Content replacement (`content_dir`).**
Live for archive paths the game resolves at runtime ([content.md](../../../docs/modding/content.md)).
Can swap layout archives when the game loads a known resource name.
Does not add new C++ screens by itself.

Lua **function hooks** (`nsmbu.Hooks.hook` / `replace` / `call`) are **phase 4 proposal** ([lua-mods.md](../../../docs/modding/lua-mods.md)).
Until they ship, only **runtime** `hooks.txt` / `hooks_*.txt` hooks (C++) can intercept the symbols below.
Plan mod packages against both docs.

### Hook targets (USA v1.3.0)

Use the address as the key.
Add a name in a comment when you edit `tools/recomp/hooks.txt` ([names.md](../../../docs/developer/names.md)).

**Modal UI (pause, quit confirm, save prompts).**

- `024BC4C4` — `CommonWindowMgr::create`.
  Runs once when the mgr builds its embedded `CommonWindow`.
  Hook to append pane registration or patch resource strings after the original `create`.
- `024BC540` — `CommonWindowMgr::execute`.
  Per-frame state machine and `animPlay` while the modal is active.
  Hook entry to drive custom visibility or piggyback on `mIsActive`.
- `024BC590` / `024BC5A4` / `024BC5C4` — `draw` / `drawDRC` / `drawDRC_System`.
  TV vs GamePad vs system DRC paths.
  Hook **return** to draw an extra pass, or entry to skip the vanilla window.
- `024BC5E4` / `024BC7D4` — `processPadTrig_TwoButtons` / `processPadTrig_OneButton`.
  Pause yes/no and single-button dialogs.
  Hook to add a third choice only if you also extend `PaCursor` / layout panes.
- `02585CC4` — `CommonWindow::create`.
  Loads `WinText` layout, `readResource`, `build`, pane tables.
  Narrower than mgr `create`; use when patching layout setup only.
- `025869C8` — `CommonWindow::execute`.
- `02586AD4` / `02586B4C` — `CommonWindow::draw` / `drawDRC`.

Opening pause is not one named function in `headers_names.txt`.
Game code sets `CommonWindowMgr::open` inline on the singleton (`mCommonWindow.mRequestOpen`, `mType = cType_WinText_Pause`, …).
Practical approaches:

- Hook `execute` or `draw` and gate on `CommonWindow::mType` / `mIsVisible` (offsets in [CommonWindow.h](../include/layout/CommonWindow.h)).
- Site-hook the caller once you find it with `ppcdis` xrefs to `open` or to `cType_WinText_Pause` rodata.

**Shared layout draw path.**

- `02672D14` — `Multi2D::draw`.
  All `AnimLayout` screens eventually call this with a projection matrix.
  Hook return to composite extra panes **only if** you already built guest layout state.
- `02672890` / `02672A4C` — `Multi2D::animPlay`.
  Advances animations on layer id `0xE` for most menus; course stock HUD uses `0x1C` in [PlayerCourseHud.cpp](../src/game/PlayerCourseHud.cpp).
  Match the layer id of the screen you extend.
- `02673050` — `AnimLayoutBase::build`.
  Instantiates panes, cursor buttons, flexible text boxes.
  Hook when injecting panes at build time instead of each frame.

**In-course HUD (not pause).**

- `0252F900` — `PlayerCourseHud::drawStockItemList`.
  DRC item strip; uses embedded `AnimLayout<2>` at `+0x1804`.
- `025D8EDC` — `GamesceneBase::setCoinNumText`.
  Coin counter text in gameplay scenes.

**Full-screen overlays (patterns to copy).**

- `AttentionScreen` / `ChangePlayerNum` — `create` / `execute` / `draw` addresses in [AttentionScreen.h](../include/layout/AttentionScreen.h) and [ChangePlayerNum.h](../include/layout/ChangePlayerNum.h).
  New guest screens should mirror this FState + `AnimLayout` shape, then hook the task that should show them.

**File-select cursor chrome.**

- `024C63E0` / `024C6500` / `024C65A0` — `SelectCursor::create` / `execute` / `draw`.
  Typed layouts: [SelectCursorLayout.h](../include/layout/SelectCursorLayout.h).

Singleton instances for mod memory reads (not hook entry points):

- `CommonWindowMgr` — data `0x101D15E8`.
- `SelectCursor` — `0x101D17A8`.

### Patterns

**1. Overlay beside vanilla UI (works with phase 4 Lua or C++ hooks).**

Hook `CommonWindowMgr::draw` (or `CommonWindow::draw`) on **return**.
Call original, then draw via `nsmbu.Gui` from Lua (today) or a small runtime hook that calls the port overlay API.
Vanilla pause keeps pad routing; your art stays separate.
Easiest mod UX; does not look like native `WinText`.

**2. Patch an existing layout (content + light hooks).**

Ship a modified `.bflyt` / `.bflan` under `content_dir` on the same archive path the game already loads.
Hook `AnimLayoutBase::readResource` or `CommonWindow::create` only if you must change which resource name is passed.
Restart required for `content_dir` map.
Text still goes through game message IDs unless you replace `TextBox` strings in the layout.

**3. Guest memory beside an active `Multi2D` (advanced, fragile).**

On `CommonWindowMgr::execute`, read `CommonWindowMgr::instance()` → embedded `CommonWindow` → `mLayout` at `+0x24` (`AnimLayout` / `Multi2D`).
Use [AnimLayout.h](../include/layout_sys/AnimLayout.h) offsets and `nsmbu.Guest` (today) to flip pane visibility bytes (see `AttentionScreen::open` setting pane `+0x44` in decomp).
No new panes unless you also hook `build` or run guest alloc + registration calls via future `nsmbu.Hooks.call`.
Easy to break on layout updates; prefer hooks on named methods over hard-coded offsets when possible.

**4. Call the same lifecycle as a native screen (future-native custom UI).**

Goal: a mod-owned `AnimLayout` instance participating in draw and pad like `ChangePlayerNum`.

1. Allocate guest memory for your object (future `nsmbu.Guest.alloc` or static guest buffer).
2. Call guest ctor / `createLayoutObj` / `readResource` / `build` chain matching [AttentionScreen.cpp](../src/layout/AttentionScreen.cpp).
3. Register panes with `NPaneRegister` / `TPaneRegister` / … using names from your `.bflyt`.
4. Each frame: `execute` → `animPlay` → on draw pass call `Multi2D::draw` with the same projection path as sibling UI (hook an existing `draw` and call through after setting visibility).
5. Route input through `PaCursor` + `UtilCursorButtonMgr` if you need focus, or rely on `CommonWindowMgr`-style pad handlers.

This path needs **`nsmbu.Hooks.call`** (or C++ recomp hooks) with stable calling conventions.
It is not exposed in Lua API v1.

**5. Parallel HUD block (course-style).**

Embed or allocate a `Multi2D` / `AnimLayout` and hook a course draw site (`PlayerCourseHud::drawStockItemList` or `Multi2D::draw` on layer `0x1C`).
Does not block pause.
Good for always-on mod panels in levels.

### Runtime hook workflow (C++ today)

1. Pick a USA address from the list above; confirm in `tools/recomp/headers_names.txt`.
2. Add a line to `tools/recomp/hooks.txt` (function entry) or `@XXXXXXXX` for a site hook ([names.md](../../../docs/developer/names.md)).
3. `nsmbu game usa-1.3.0 --recomp` then `nsmbu build` (hook list change forces recomp).
4. Implement `hook_XXXXXXXX` in `runtime/src/hooks/` (pattern in existing hook files).
5. Call `f_XXXXXXXX_orig` when wrapping; respect game thread only.

No UI symbols are hooked in the port yet.
First mod-friendly candidates: `024BC590` (modal draw), `0252F900` (course HUD), `02672D14` (all layout draw).

### Lua workflow (phase 4 proposal)

When `nsmbu.Fn` is populated from headers, prefer names over raw hex:

```lua
-- Proposal only; not in API v1 yet.
nsmbu.Hooks.hook(nsmbu.Fn.CommonWindowMgr_draw, "return", function(ctx)
  nsmbu.Hooks.original()
  -- nsmbu.Gui or nsmbu.Hooks.call into Multi2D::draw
end)
```

Use `onLogicStep` today for `nsmbu.Gui` without touching guest UI.
Use guest hooks when you need native fonts, layout animation, or GamePad focus.

### Pitfalls

- **Allocator heap.** Each `Multi2D` owns a `LayoutAllocator`; `setHeap` must point at valid guest heap before `createLayoutObj`.
- **TV vs DRC.** Modal UI splits `draw` and `drawDRC`; pause on GamePad-only flows needs both or DRC-only hooks.
- **Pad focus.** `PaCursor` and `CommonWindowMgr` controller slots (`SysControllerWrapper` array on the mgr) consume input while open; overlay `nsmbu.Gui` does not participate in that focus model.
- **European builds.** Hook addresses move with the regional map ([builds.md](../../../docs/developer/builds.md)); object layouts do not.
- **Message text.** `setTextBoxMessageFromTextID` pulls from the game MSBT pipeline; custom strings need layout text or a hook on `TextBox::setMessageParam_` (`0x02681BFC`).
- **Recomp cost.** Each new hooked function stays recompiled in the mod build; keep hooks on high-level `execute` / `draw`, not per-pane inner loops.

### Related decomp gaps

- Header shells for `LayoutObj`, `PartsLayoutObj`, `TextBox`, `ArcResAccMulti`, `FlexibleTextBox`, and `AnimText` under `include/layout_sys/`; `.cpp` coverage is still partial.
- Static state IDs (for example `ChangePlayerNum::StateID_CloseRequest` at `0x1020D434`) live in `.data`.
- Layout file format: NintendoWare Lyt tree in `references/Lyt` (local checkout), not in this repo.

## Tools

- Disassemble: `python3 tools/rpx/ppcdis.py 0x026711C8` (uses `game/active`).
- Names: `tools/recomp/headers_names.txt` for `Multi2D::`, `CommonWindowMgr::`, etc.

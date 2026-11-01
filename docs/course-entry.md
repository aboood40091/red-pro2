# Course entry from save (`InputMgr` / `CourseTask`)

USA v1.3.0.
Relates to directed `nsmbu open` / `run` and normal map → course.

## Save record → runtime (`0x0250C3EC`)

`InputMgr+0x55C` holds a pointer to the active save slot record (`0x204` bytes per file in `SaveMgr`).
`0x0250C3EC` reads that record and writes `FieldGameData`, `FieldGameMode`, `MainGame`, and a few globals.
Decomp: `src/input/InputMgr.cpp` (`sub_0250C3EC`).

Callers: only `InputMgr_applySaveEntry_` (`0x0250CDBC`) via `bl 0x0250C3EC` at `0x0250CFA0` and `0x0250CFC0`.
Course setup reaches it from `CourseTask::setupCourse` (`0x024BD86C`) after `InputMgr::createInstance`.

### Per-player block (×4, stride `0x10`, base `+0x3C`)

| Save off | Size | Destination |
| --- | --- | --- |
| `+0x00` | u8 | `FieldPlayerData::is_entry` (`player[n]`) |
| `+0x01` | u8 | `life_cnt` (clamped to 99 → 5) |
| `+0x02` | u8 | `character` |
| `+0x03` | u8 | `character_color` via `0x0250C3C8` |
| `+0x04` | u8 | `player_mode` |
| `+0x05` | u8 | `has_star` |
| `+0x06` | u8 | bit0 → `mii_cap_visible`; drives `mii_slot` with `MainGame+0x2C` bit4 and `SubjectMgr+0x1E7E` |
| `+0x08` | u32 | `coin_cnt` |
| `+0x07` | — | not read |

Mii slot assignment uses cap/normal counters when color is Mii; see decomp for branches.

### Course / mode bytes

| Save off | Destination |
| --- | --- |
| `+0x7C..+0x7E` | `FieldGameData+0x13D..+0x13F` banner picture-pane digits (clamped, `-1` blank) |
| `+0x43` | `FieldGameData::setCheckPoint` index (`0x0250C76C`) |
| `+0x44` | checkpoint `_0c` byte (clamp `<4`) |
| `+0x45` | checkpoint `_08` byte (0 or 1) |
| `+0x46` | checkpoint `next_goto_no` |
| `+0x47` | `MainGame+0x21DFA/B` (bit0/bit1); if bit0 → `MainGame+0x1E0` = bit1 |
| `+0x48` | `FieldGameMode::setMode` |
| `+0x49` | `FieldGameData::setCoinNum` (clamp `>99` → 0) |
| `+0x4A` | u16 flags → see below |
| `+0x4C` | u32 play seconds → `FieldGameData+0x138` |
| `+0x50` | `FieldGameData+0x168` |
| `+0x51` | course type → `FieldGameData+0x164` (only 10, 11, 14 else `0xE`) |
| `+0x52` | boss bytes → `+0x1A4` / `+0x1A5` (split on bit7) |
| `+0x53` | `FieldGameData+0x140` |
| `+0x54` | f32 quake value (Boost Rush only) |
| `+0x58` | u8 quake power (Boost Rush, clamp `0x13`) |

`setCheckPoint` also takes **live** `CourseInfo::mCourseNow` world/course/file (`+0x10/+0x11/+0x12`), not the save map coordinates.
Banner digits copied to the checkpoint struct come from the stack copy of `+0x13D..+0x13F`.

### `save[+0x4A]` u16 flags

| Bits | Effect |
| --- | --- |
| 0 | `FieldGameData+0x169` |
| 1 | `FieldGameData+0x13C` |
| 2–3 | Boost Rush quake short/long (mutually cleared if both set) |
| 4 | `*(SaveApplyMgr+0x11)` |
| 5 | `FieldGameData+0x160` |

Boost Rush quake calls `sub_024CC370` on `QuakeMgr` when mode is `cBoostRush`.

### When `0x0250C3EC` runs

`InputMgr_applySaveEntry_` stores a mode in `InputMgr+0x514`:

- **2** — `MainGame+0x88` save record byte0 ≠ 0 (normal save-backed course entry).
- **1** — challenge with empty record byte0.
- **0** — otherwise (no save snapshot on the record pointer).

Modes **1** and **2** always reach `0x0250C3EC` after allocating/copying the `0xE8`-byte working buffer.
Mode **0** skips it (controller defaults only).

Directed open applies save file 1 in the port, so byte0 is usually non-zero and **`0x0250C3EC` still runs** at course setup.
What direct open skips is the **world-map** path (`enterMapFromGameData_` `0x024C2230`), not this function.

## `CourseTask::setupCourse` (`0x024BD86C`)

Runs before the area task loads the course pack.
Decomp: `src/game/CourseTask.cpp`.

### `FieldGameData` (via `CourseTask+0x124` / `mGameData`)

1. **`memcpy` from `FieldGame::getGameData()`** — seeds the task copy from the singleton filled by save/load and map logic.
2. **`resetEntriesUnk30`**, **`setupNabbitEntry`**.
3. **`checkEnterCourse`** / **`clearCheckPoint`** using **`CourseInfo`** now-world/course and enter type (`CourseInfo+0x1E`, next scene).
4. **Glyphs** — reads **`mGameData` banner digits** at `FieldGameData+0x13D..+0x13F` into `CourseTask+0x134..` (`setGlyph`).
5. **`taskGameMode`** — mode from copied `FieldGameData` (including save byte `+0x48` when `0x0250C3EC` ran).
6. **Challenge** — `SubjectMgr` / `ChallengeMgr` timers read course files using **`CourseInfo`** bytes, not save offsets directly.

After **`InputMgr_applySaveEntry_`**, the same **`mGameData`** buffer may change again if mode 1/2 invoked **`0x0250C3EC`**.

### `MainGame` (not `FieldGameData`)

| Offset | Use in `setupCourse` |
| --- | --- |
| `+0x88` | save record pointer / apply mode |
| `+0x2C` | story / pose flags for `CourseTask+0x28D` gating |
| story sub-struct | `story_bytes[0]`, `[2]` for `+0x304` world-bit gate |
| `+0x34` | `PicturePaneMgr_lookupGlyph` for `CourseTask+0x264` |

Loading-card **`WorldCourse`** text uses **`+0x19C` / `+0x1A8`** (see `docs/developer/nsmbu/course-open.md`).
Those are **not** written in `0x0250C3EC`.

### `PlayerMgr`

`setupCourse` does **not** load player fields from save itself.
Near the end (`0x024BE210`):

- **`PlayerMgr::initializeForCourseSetup`** (`0x0291713C`) — clears course-local player mgr fields, then rebuilds player slots.
  Decomp: `vendor/decomp/src/player/PlayerMgr.cpp`.
- **`sub_02742F9C`** (`0x02742F9C`) — second helper with the same **`FieldGameData*`**; first argument is `*(0x101EC398)` (course owner singleton; symbol not in `headers_names.txt`).
  Decomp: `vendor/decomp/src/game/CourseFieldGameApply.cpp`.
- **`sub_02918780`** (`PlayerMgr.cpp`) reads **`getGameData()->getPlayerData(n).is_entry`** once actors exist.

Until that init, **`PlayerMgr::getGameData()`** falls back to **`FieldGame::instance()`** if **`CourseTask`** is null (`0x02918758`).

## Direct open must seed

Port checklist (extends [course-open.md](../../../docs/developer/nsmbu/course-open.md)):

1. **`CourseInfo`** next/now world and course for the pack (and **`setNext*`** gating).
2. **`MainGame+0x19C` / `+0x1A8`** for loading-card MSBT world/course tags.
3. **`FieldGameData+0x13D..+0x13F`** (or accept blank glyphs) — **not** filled by map `setCheckPoint` when skipping overworld enter.
4. **`FieldGame` singleton** — whatever **`memcpy`** into **`mGameData`** should contain (player entries, coin count, mode byte **`+0x48`**, etc.).
   Save apply at boot plus **`0x0250C3EC`** on course setup covers most of this when record byte0 ≠ 0.
5. **Map return** — checkpoint / pose (`NOTES_map_spawn.md`); course setup alone does not replace **`enterMapFromGameData_`**.

## Related

- Map spawn / checkpoint: `include/course_select/NOTES_map_spawn.md`
- Save map enter without course: `SaveMgr` / `enterMapFromGameData_` `0x024C2230`

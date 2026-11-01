# Decomp verification TODO

Open questions from the decomp notes, one claim per item.
Checked items are removed: the answer lives in the note it came from.
Check a claim against the USA v1.3.0 `red-pro2.rpx` unless the item says Europe.

Tools:

- `python3 tools/rpx/ppcdis.py ADDR [COUNT] [RPX]` disassembles `.text`.
  It annotates import calls (`gx2!GX2DrawDone`) and calls to a name in `recomp/headers_names.txt`.
- `recomp/headers_names.txt` gives the class and symbol for a game address.
- `game/active` selects the dump that `ppcdis.py` reads by default.

Sweep `addi` (14), `addic` (12), `addic.` (13), and `ori` (24) together.
The compiler materialises a static address with `lis` + `addic` often enough that an `addi`-only sweep reports a false "no reference".


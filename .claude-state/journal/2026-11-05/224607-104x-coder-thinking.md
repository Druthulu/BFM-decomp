---
ts: 2026-11-06T05:46:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FxFzPjkg93uO7B16ZVWs
---
The diff:
1. Register allocation: target has v1 = 0xA2 constant, v0 = pointer, a0 = halfword load. Mine: v0 = 0xA2, a0 = pointer, v1 = load.
2. Extra `move v0,a0` in mine at 32 and 36 (the two delay slots) — exactly as the comment predicted.
3. The three `andi v0,v0,0x1` vs `andi v0,a1,0x1` — the launder effect (c stays in a1 in the target, cse folds otherwise).

So two separate levers to replace: the pin (register allocation + the moves) and the 3 launders (the andi source).

Let me tackle the launders first — they're the same pattern as before: `c = func(...) & 0xFF;` then `if ((c & 1) != 0)`. Without the launder, cse folds `(c & 0xFF) & 1` to `raw & 1` and emits `andi v0,v0,1` reading the call result. The target reads the masked copy: `andi v0,a1,1`.

The launder forces `c` to be a distinct value. Lever-free options: a real 2nd set of c. E.g., `c = (u8)c;`? Hmm, c is s32 = func() & 0xFF. A 2nd set like `c = c & 0xFF;` (redundant but a real set) — combine might fold it back. Or `c = (u8)c;` — since c ∈ [0,255], gcc folds to a copy.

Hmm. The launder is `__asm__("" : "=r"(c) : "0"(c))` — a zero-byte re-tie. The equivalent real C: `c = c;`? deleted.

Hmm, what about `c = c & 0xFF;` — a real AND with a constant. cse/combine would see c = (raw & 0xFF) & 0xFF = raw & 0xFF — fold. Unless the two ANDs are separated... 

The moves.md catalog has "real 2nd set" tricks: e.g., `pv &= 0xFF000000` (compound). Here `c &= 0xFF;` right after `c = func() & 0xFF;` would be a 2nd set — cse might fold.

Hmm. Let me think: the target's `andi v0,a1,1` means c is in a1 and the `c & 1` reads a1. So c must be a separate value from the call result.

What if we declare `c` as `u8`? Then `c = func(...) & 0xFF` is a QI set (subreg) — cse might not fold the QI variable. Then `(c & 1)` reads the QI value → `andi v0,?,1`. The QI variable would be in a register (the call result truncated). Hmm, the truncation from SI to QI is a no-op if the value is already masked... 

Actually, `c = func_800291B4(0xD6) & 0xFF;` with c u8: the RHS is masked to 0xFF then truncated to QI — gcc folds the double mask. Then `c & 1`: the QI c is promoted to int (zero-extend) then &1 → `andi`.

The question is whether gcc keeps the masked value in a separate register from the raw call result. With `c` QI, the RTL is `(set (reg:QI c) (subreg:QI (reg:SI raw)))` — a QI copy, which escapes cse (like the HImode trick!). That's promising: c QI.

But then `c++` and `c & 0xFF` and `func_800291A0(0xD6, c & 0xFF)` — the QI variable would need zero-extension at uses (andi 0xff?) — but if gcc knows the value is QI in a register... Hmm.

Let me check the target asm around the c handling to see the exact instructions. Let me dump the target function.

Actually, let me first try the simplest thing: remove the pin only, keep the launders (to isolate). And remove the launders only, keep the pin. That tells me which lever causes which diff.

Let me score:
- n2: pin removed, launders kept.
- n3: pin kept, launders removed.

Then I'll know the contributions.

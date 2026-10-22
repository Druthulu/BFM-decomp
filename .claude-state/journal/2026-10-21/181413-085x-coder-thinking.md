---
ts: 2026-10-22T00:14:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_HMTStTWsBK9R4UtkzVgZ
---
";; Register 73 in 2." and ";; Register 77 in 2." — hmm, both say "in 2"?? That's the local-alloc's tentative assignment (both want reg 2, and then the conflicts are resolved). Hmm, the .lreg dump prints the register dispositions.

Hmm, both 73 and 77 in 2 — that's the "tentative" allocation before conflict resolution. Hmm, or the dump prints the final.

Hmm. Anyway:
- r73: used 4 times across 12 insns in block 0 → the POINTER (block 0 = the entry block; the pointer lives in the entry block).
- r77: used 3 times across 6 insns in block 1; 2 bytes → hmm, block 1?! and 2 bytes.

Block 1 — hmm, in the .lreg dump, "block 0" and "block 1" are the two blocks of the function? The function has an if/else → 2-3 blocks. r77 is in block 1.

Hmm! r77 (2 bytes) in block 1 — that could be the `0x7FFF` value (a 16-bit constant!). `(*(s16 *)&D_800B9AAC) = 0x7FFF;` — the constant 0x7FFF is 2 bytes, used in the if-block (block 1). Its refs: the li (set) + the store (use) = 2... but "used 3 times": the constant appears in 3 places? `(*(s16 *)&D_800B9AAC) = 0x7FFF; D_800B9B00 = 0x7FFF;` — TWO stores of 0x7FFF! So the constant's pseudo: set(1) + 2 uses = 3 refs ✓ and live 6 ✓ and 2 bytes ✓✓✓

So r77 = the 0x7FFF constant, NOT the value! And the VALUE pseudo isn't in the table at all (maybe it's an "in/out" pseudo or was optimized).

So the locals are: r73 (the pointer, 4 refs, live 12) and r77 (the constant 0x7FFF, 3 refs, live 6, 2 bytes). And the VALUE pseudo is missing from the table (perhaps it's r74? "used 17 times across 17 insns; dies in 5 places" — hmm, 17 refs is a lot).

Hmm, r74: 17 refs, 17 insns, dies in 5 places, GR_REGS. And r72: 3 refs, 40 insns, crosses 11 calls.

Hmm, so where's the value? Maybe the value pseudo is one of the "TIE" entries (a0/v0 etc.) that the alloc_table didn't print, or it's a hard-reg-only pseudo.

Hmm, so the value's pseudo might be allocated by local-alloc to a reg but not listed. The table listed only 4 pseudos: 72, 73, 74, 77.

Hmm! So the value `v0` is r74?? "used 17 times across 17 insns; dies in 5 places" — hmm, r74 is a global (in the .greg order "74 72"). The value v0 is used in the if-branch: `v0 = func_8012E544(0x397); if (v0 != 0) {...}` — v0 is assigned 4 times (one per E544 call) and used 4 times → 8 refs, and it CROSSES calls? Hmm, v0 = func_8012E544(...) then `if (v0 != 0) func_8012C098((void*)v0)` — v0 is used before the call ✓ so it doesn't cross.

Hmm, but r74 "dies in 5 places" and is global (in the .greg order) → it crosses a call. Hmm, the value v0 crosses the call to func_8012C098? No: `func_8012C098((void *)v0)` — v0 is passed as the argument, so it's dead at the call.

Hmm.

Hmm, r74 (17 refs, 17 insns) — that could be the `a0` parameter (used in `func_8012BF4C((s32 *)a0, 0x1E)` and `func_8012AD50((void *)a0)`) — but that's only 2 uses.

Hmm, 17 refs... the value v0: 4 sets (from the E544 calls) + 4 uses (the != 0 tests) + ... hmm, 8. Plus the earlier value (unk10/unk14 stores) → 5 more = 13. Hmm, close to 17.

OK, let me stop. The important thing: the table's pseudo list is confusing because the standalone TU differs from the real TU.

Let me change approach for 80180480: use the REAL TU for the dump (splice my candidate into a copy of the real TU). That's the faithful environment. Then the alloc table would reflect the real allocation.

Hmm, that's more work.

TIME CHECK: I'm at ~3h. I need to wrap up: 4 items untouched (80181E64, 800D2650, 8003DF8C, 801415C0) + 2 in progress (80180480, 800D0D7C) + finalization (results.tsv, moves.md, log).

Let me make a plan for the remaining time:
1. (20 min) Quick attempts on the 3 $0-zr items and 800D2650 + 801415C0 — mostly to gather evidence for the results rows.
2. (30 min) Finalize: results.tsv rows, moves.md lines, the log file, cleanup of dumps.

For the $0-zr items (80181E64, 8003DF8C, 800D0D7C), the mechanism is clear: the "$0-ADD OPAQUE COPY" — the pin makes `x = y + zr` emit an opaque `addu rd,rs,$0` that cse/combine cannot remove, and without it the copy is dissolved (and the `& 0xFF` fold happens). That's a WALL with the tag... hmm, walls.txt has no "$0-opaque-copy" tag. I'd need a new tag: `<pass>-<what>` e.g. "cse-opaque-copy" or "combine-fold-lowbyte". Let me use "cse-opaque-copy" — hmm, the tag format is `<pass>-<what>`: pass = cse/combine/sched1/etc. So "cse-opaque-copy" fits.

Hmm, but for 800D0D7C I should still try a bit harder since it's close (score 17, only the two copies + the frame).

Hmm, for 800D0D7C: the frame difference (mine -16 vs target -8) — the `dead[2]` array. In my c1 the frame was 16 — why? Because in c1, `now` and `r` were the same pseudo and... hmm, the extra 8 bytes. Hmm, maybe the `h` value needed a spill slot.

Hmm, what if I remove `dead[2]`? Then the frame would be 8 (from something else)? Hmm, the target's frame is 8 with no stores. Let me try removing dead[2] and see.

Hmm, actually: in the target, the frame is 8 bytes with NO stack traffic. So the frame comes from an unused local (dead[2] = 8 bytes) ✓ per the project's comment. In my c1 the frame was 16 → an extra 8 bytes → maybe a spill slot for the merged h/arg0.

Let me try c1 with `dead[2]` removed → frame might be 8 if the spill goes away... hmm, no: the spill would still need 8.

Hmm. Let me try a couple of quick variants for 800D0D7C:
- m1: c1 without `dead[2]`.
- m2: c1 with `dead[2]` and `h` as u32.
- m3: c1 with the `r = now` replaced by `r = now` but `now` declared after `r`... 

And the KEY missing piece: the opaque copies. Hmm.

Let me think about the opaque copy ONE more time, because 3 items hinge on it.

The target's copy: `addu a2,a3,$0` = `plus(a3, $0)`.

For gcc 2.7.2 to emit that from C, the RTL must be `(set a2 (plus a3 X))` where X is a register (not a constant).

What C produces `plus(reg, reg)`?
- `x + y` where y is a variable in a register.

And the VALUE of y must be 0 at runtime.

Where can a zero-valued register come from without extra instructions?
- An ARGUMENT register that holds 0! E.g., if the function had a parameter that's 0... but the signature is fixed.

HOLD ON!!! What about the **`$zero` register being produced by gcc for a zero-valued local**? gcc 2.7 doesn't do that.

Hmm, what about **`x + (y - y)`**? gcc's combine: `minus y y` → 0? gcc 2.7's combine has a rule `if (op0 == op1 && commutative) → 0`? I believe gcc 2.7's combine does NOT fold x-x (it's not valid in general). Hmm, actually for integers, gcc's combine might. Let me test! If `y - y` isn't folded, the code would be `subu v0,a1,a1; addu a2,a3,v0` — 2 extra instructions ✗ (the target has 1).

Hmm.

What about `x + (y & 0)`? combine folds `and y, 0` → 0 → then `plus x, 0` → folded ✗.

What about `x + (y * 0)`? → folds to 0 ✗.

Hmm, so we need a register that gcc believes is 0 but keeps in a register. That's exactly what a `register` asm var pinned to $0 does.

**Conclusion**: The $0-add opaque copy is NOT reproducible in plain C for gcc 2.7.2 — it's a genuine lever. The project's own comment calls it RC-12 (a "residual lever").

⇒ For 800D0D7C, 80181E64, 8003DF8C: WALL with a new tag like "cse-opaque-copy".

Hmm, BUT hold on. Let me reconsider the 800D0D7C case once more: the target has TWO opaque copies (a2←a3 and t0←a0). And the comment says the &0xFF fold is blocked by the opaque copy.

Hmm, what if there's a way to block the fold WITHOUT an opaque copy? The fold is `r & 0xFF` → `D_80078EB0` (the lbu). That's gcc's combine recognizing `(and (ior (lbu X) (lbu Y << 8)) 0xFF)`.

If `r`'s value isn't directly the OR expression, the fold can't happen. E.g., if `r` were computed as `now` where now is a variable... that's exactly the case in the source! And yet gcc folded it (in c1). Because cse propagated.

Hmm, so we need `r`'s value to be opaque.

Hmm, hmm. What if `now` were computed as `D_80078EB0 | (D_80078EB1 << 8)` but with `now` being a `u16`?! Then `now` would be truncated → `andi` ✗.

Hmm, what if the globals were read via a different expression that gcc can't fold, e.g. `*(u8 *)&D_80078EB0`? Same.

What if the packed value were computed as `(D_80078EB1 << 8) | D_80078EB0` (swapped order)? The fold would still recognize it.

What if the shift were `<< 8` on a `u32` vs `int`? Same.

Hmm, what if the two bytes were combined differently: `now = D_80078EB0 + (D_80078EB1 << 8);` (add instead of or)! Then `now & 0xFF` can't be folded to the lbu (the add doesn't preserve the low byte) ✓✓✓!!! And the target's code is `or a3,v1,v0` — hmm, the target uses `or`. With `+`, gcc would emit `addu a3,v1,v0` ✗ (different opcode).

Hmm! But wait: would gcc's combine turn `a + (b << 8)` into `a | (b << 8)`? No.

Hmm, so the OR is needed for the instruction to match, but the OR enables the fold.

Hmm. So: `r = now` (OR) → the fold happens. `r = now` where now is opaque → no fold.

OK: so the ONLY way is the opaque copy. Confirmed WALL.

Hmm, hold on. Let me reconsider: maybe the fold can be blocked another way: by making the value's low byte unknown to combine. E.g., if `now` were computed as `D_80078EB0 | (D_80078EB1 << 8)` but stored through a union/pointer → memory ✗.

What if `now` were a `volatile` read? ✗ (barrier).

What if the globals were read via a pointer that gcc can't see through? e.g. `*(u8 *)&D_80078EB0` — gcc would still fold the address.

Hmm, what if the source read the bytes via an array: `D_80078EB0_array[0] | (D_80078EB0_array[1] << 8)` where the array is `extern u8 D_80078EB0[2]`? Then the address is the same constant → combine might still fold (it knows the address). Hmm, but the fold requires knowing the address is D_80078EB0 → with an array it does.

Hmm, what if the array pointer were passed... no.

OK. WALL for the three $0 items (800D0D7C, 80181E64, 8003DF8C).

Hmm, hmm. But hold on! For 800D0D7C, the score was 17 with 42 ins vs 45. The missing 3 insns are: `move a2,a3`, `move t0,a0`, and one more (the frame difference). Hmm.

OK, let me now quickly do the remaining items to at least gather evidence, then finalize.

Actually, WAIT. Let me reconsider ONE possibility for the opaque copy that I haven't tried: **the `h = arg0` copy**. In the target, `move t0,a0` is a copy of the parameter. What if the copy is preserved because `h` is a **local of a different type** — e.g. `h` is `s32` but assigned from `arg0` which is `s32`... 

Hmm, what about the "u16 escapes cse" trick from moves.md: "$0 zr pin: s16 flag2/3/4 copies (HImode copy escapes cse, combine nonzero_bits -> move)". 

In our case: `h = arg0` where the target's `move t0,a0` is a 32-bit copy. If h were s16, the copy would be `sll/sra` ✗.

Hmm, BUT: what if the HImode copy is on a DIFFERENT variable? Like:
```c
s32 h;
u16 t;
t = (u16)arg0;    /* HImode copy: andi t0,a0,0xffff — extra insn ✗ */
```
✗.

Hmm, what about `h = arg0` where arg0 is s16?? The function's signature is fixed (s32 arg0).

Hmm, what if the copy `move t0,a0` comes from the parameter copy (gcc copying the incoming param into a pseudo)?! In gcc, for a function whose parameter is modified, gcc creates a pseudo and copies a0 → pseudo. That copy is `move t0,a0` if the pseudo got t0! And then the pseudo (h) is modified later (`h = arg0 + 1`).

Hmm! But in gcc, if the parameter is only READ (not modified), no copy is made. Here `h = arg0` reads it and `h = arg0+1` reads it. So no param copy.

Hmm, but the TARGET has `move t0,a0` — a copy of the parameter into t0. If the ORIGINAL source had modified the PARAMETER directly:
```c
arg0 = arg0;   /* no */
```
Hmm, what if the original source was:
```c
s32 func_800D0D7C(s32 arg0, s32 arg1) {
    ...
    arg0 = arg0;      /* ??? */
```
Hmm.

WAIT!!! What if the original source was:
```c
s32 h = arg0;
...
h = arg0 + 1;
```
Hmm, that's what we have.

Hmm, what if the original was:
```c
s32 h;
h = arg0;
if (...) { h = arg0 + 1; }
```
and the copy `move t0,a0` is the param→h copy that gcc keeps because h is modified later?! Hmm! In gcc, when a variable is assigned from a parameter and then modified, gcc's "assign" creates a copy. But if the assignment is `h = arg0` (a plain copy), gcc's cse propagates arg0 into h ✗.

Hmm, BUT: gcc 2.7 has a rule: a variable that is assigned more than once and is live across a call gets its own pseudo; the copy `h = arg0` might be preserved because arg0 (the parameter pseudo) is "the same" but h's pseudo has 2 sets...

Hmm, but the target's `move t0,a0` is EXACTLY such a copy: gcc kept the copy `h = arg0` (t0 = a0) rather than propagating.

So in the TARGET's compilation, the copy WAS preserved. Since the target came from the original compiler (not gcc), we can't infer gcc's behavior from it. But we need gcc 2.7.2 to produce it.

Hmm! So the question is: can gcc 2.7.2 produce `move t0,a0` for `h = arg0; ... h = arg0+1;`?

In my c1, gcc produced `addiu a0,a0,1` (h coalesced with a0). So no.

Hmm, BUT: what if h's FIRST assignment were in a different block such that the copy can't be propagated? E.g. d4 (h = arg0 in the then-branch): score 18 — hmm, it got WORSE (18 vs 17). Let me look at d4's diff to see what happened. Maybe it got closer in some way.

Hmm, let me look at d4's diff. Actually, the score differences are small; let me look at d4 and d5.

Hmm, time! Let me be decisive.

PLAN for the remaining time (~1.5h):
1. Spend 15 min on 800D0D7C: try a few variants aimed at the copies (e.g., h assigned in the then-branch, r/now with the copy in different positions). Record the best.
2. Spend 10 min each on 80181E64, 8003DF8C, 800D2650, 801415C0: quick attempts (remove the pin, score) → record.
3. Finalize: results.tsv (7 new rows), moves.md lines, the log, cleanup the dumps.

Let me do 2 first (quick, gives me the evidence for the rows), then 1, then finalize.

Let me look at the sources for 80181E64 (I have it), 8003DF8C (have it), 800D2650 (have it).

Let me write the lever-free candidates for those three now.

**func_80181E64**: the pin is `register s32 zr __asm__("$0")` used as `t = v + zr`:
```c
{
    register s32 zr __asm__("$0");
    v = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF;
    t = v + zr;
}
```
Lever-free: `t = v;`. The target presumably has an opaque copy `addiu t, v, $0` or similar.

**func_8003DF8C**: `i = arg0 + zr; j = arg1 + zr;` → lever-free: `i = arg0; j = arg1;`.

**func_800D2650**: 4 pins ($2 cw, $8 s_a6, $14 code, $3 bVar1). Lever-free: remove them all.

Let me write these and score.

Note for func_800D2650: the pins are on cw, s_a6, code, bVar1. Removing them all at once will change a lot. Let me try.

Let me write the candidates now.

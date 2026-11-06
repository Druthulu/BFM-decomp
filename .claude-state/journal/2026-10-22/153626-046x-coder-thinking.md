---
ts: 2026-10-22T21:36:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qSzwPqEBfrI7V25YGUJT
---
Lever-free: `move v1,v0` is missing (the copy to byteval $3 disappeared — because without the launder, byteval is just src and the copy is coalesced: `move v1,v0` then `move a0,v0` become one `move a0,v0` and v1 is used later at 19 `sll v1,v1,0x3` — so where does v1 come from in mine? At 12: `move v1,a0`. So the copy moved into the delay slot of the beq.

Target: `move v1,v0` (byteval = src) right after andi, and `move a0,v0` (testval = src), then later `sll v1,v1,0x3` uses v1.

So the launder forced byteval to have its own hard-reg copy at the assignment. Without it, combine/cse merges byteval with src and the copy is placed late (into the beq delay slot at 12).

Moves for this: the launder is "out-only" (a copy that survives). Similar to "launder->real 2nd set". Options: make byteval a real 2nd set, e.g. `byteval = src;` then... the issue is that byteval's value equals src's, so the copy is folded/merged and placed at the use.

Since the pins $3 (byteval) and $2 (src) are fixed hard regs, the copy `move $3,$2` must exist. With the launder, it's emitted at the assignment point (birth). Without, sched1 puts it in the beq delay slot.

Real-C ideas:
- Make byteval's value differ so it can't merge: e.g. `byteval = src;` then `byteval = byteval | 0;`? identity, not allowed.
- Give byteval a 2nd set that is real: e.g. `byteval = (u32)(src & 0xf);` — src is already (param_2>>0x10)&0xf, so the mask is redundant but it's a real operation: andi again? That would add an insn (bad).
- `byteval = src;` where src is u32 and byteval is u32 — same. If byteval were declared `u8`, the truncation would create a real subreg copy: `move v1,v0` might survive as a copy with andi? Hmm — C0505 catalog mentions "s16/u8 widths". Making byteval `u8` means `pcVar2[0] = (u8)(byteval * 8 + 8)` — byteval as u8 would add an andi 0xff after the move probably.

Wait, careful: byteval * 8 + 8 — byteval is (param_2>>16)&0xf, 0..15, so *8+8 up to 128, fits u8. If byteval is u8, gcc emits move v1,v0 (with a truncation subreg) then sll. The truncation of an SImode value already known <16 might be free (nonzero_bits) → same code, but the *copy* might be a SUBREG copy that combine can't merge. Worth testing.

- Another idea: `testval = src;` before `byteval = src;` order? The target order: move v1,v0 (byteval) at 7, move a0,v0 (testval) at 8. In source, byteval = src comes before testval = src. OK.

- Give byteval a 2nd use so the copy has to be materialized early? e.g. use byteval in the if condition: `if ((iVar3 == c5) || (testval != 0))`. No.

- The "dead copy" trick: add `byteval = src;` twice? e.g.
```
byteval = src;
byteval = src;   // 2nd set
```
Hmm.

Let me think about what the launder does mechanically: `__asm__("=r"(byteval) : "0"(byteval))` — creates a new pseudo for byteval's output tied to input. So byteval = opaque(src) → a copy from src to byteval's hard reg $3, born at the assignment. Since $3 is a fixed hard reg, the copy can't be coalesced... but without the asm, byteval (pinned to $3) = src (pinned to $2) → the copy is still required (both are hard regs!). Hmm, both are pinned: src $2, byteval $3. So the copy MUST be emitted: `move $3,$2`. And indeed mine has `move v1,a0` — v1 = $3, a0 = $4 = testval, not $2. Hmm, at 7 mine has `move a0,v0` = $4 = $2 value. So testval ($4) = src, and byteval ($3) got `move v1,a0` at 12 — a copy from $4 (testval) instead of $2 (src). Since cse knows byteval == testval == src, the copy source became a0 ($4) rather than $2 (v0).

Interesting: cse merged byteval and testval (same value), so the copy is from whichever. With the launder, byteval's source stayed src ($2 → v0) and the copy was born at the assignment.

So the lever-free issue: byteval and testval are cse-equal, so the copy's source is the $4 register and its position moves into the delay slot.

Real C fix: make byteval's value differ from testval's, i.e. give byteval a real 2nd set or a different expression. What real expression yields the same value? `byteval = src & 0xf;` — src is already &0xf; the compiler folds it (nonzero_bits) → same. Hmm.

What about declaring byteval as `u8`? Then `byteval = src;` truncates → a real subreg copy. That may keep the copy at the assignment (birth) and, since the value is truncated, cse may treat it as a distinct... Actually the truncation of a value known < 256 is a no-op (nonzero_bits), so combine may still fold.

Alternatively `s16 byteval`? Same.

Hmm, the C0505 catalog mentions "s16/u8 widths" as a real-C move. Let's try:
- v1: `u8 byteval;` (with pin $3)
- v2: `s16 byteval;`
- v3: byteval = (u8)src; explicit cast.
- v4: swap the two assignments order (testval first).
- v5: `byteval = src; testval = byteval;`? Hmm, that changes the chain: testval = byteval would make the copy chain move $3,$2 then move $4,$3 — target has move v1,v0 and move a0,v0 (both from v0). No.
- v6: byteval declared before src? Decl order (they're inside the loop block).
- v7: move byteval's declaration to function scope.

Let me also consider: the launder is on byteval only. Maybe a "dead copy" trick: `byteval = src;` and later `byteval = src;` (2nd set) — no.

Let me try a batch. I'll generate variants with Python for reliability.

Also worth trying: `pcVar2[0] = (u8)(byteval * 8 + 8);` → maybe use a temp: `u32 t = byteval * 8 + 8; pcVar2[0] = t;` — that changes the sll chain (target: sll v1,v1,0x3; addiu v1,v1,8 — same).

Let me focus on the copy placement: target has move v1,v0 at 7 (born right after the andi) and mine has it at 12 in the beq delay slot. The scheduler moved it. To pin it early: give it a dependency... e.g. make byteval used before the branch. Hmm, byteval is used only at the sb.

What if I reorder statements: put `pcVar2[0] = ...` earlier? No, that changes everything.

Alternatively make the *copy* have a dependency on an early value: byteval = src is already dependent on v0 at 6.

Hmm, what about the `||` fold: `if ((iVar3 == c5) || (testval != 0))` — the target has beq v0,t2 then beqz a0. That's fine in both.

Let me try width variants first (u8, s16, and cast forms), plus declaration scope changes.

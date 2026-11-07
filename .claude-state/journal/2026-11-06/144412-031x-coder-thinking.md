---
ts: 2026-11-06T21:44:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7CiXVQRDAo3n45aGnLzH
---
Key: "The HImode copy `u = tmp` escapes cse2's equivalence class, the sign extension folds away (t is a sign-extended s16 already), and the copy survives as `or v1,v0` in the bnez delay slot."

In our case, target has `move v1,a0` — not `or`. Hmm, but `or v1,a0,zero` might be printed as `or` vs `move`. The target instruction at that spot: let me check the actual target asm. The notes say "no `move v1,a0`". Let me dump target asm to see exactly.

In our header body, iVar2 is `int`, value = t+1 or 1 where t = param_2>>16 & 0xf — not sign-extended s16 necessarily (it's an and of 0xf, so 0..15, then +1 => 1..16; GCC may know it's small).

An s16 temp copy: `s16 tmp = (s16)iVar2; iv2c = tmp;` — the sign extension folds away if GCC knows the value is already sign-extended (range 1..16). It might, since t = (param_2 >> 16) & 0xf, and iVar2 = t+1 ≤ 16 — combine's nonzero_bits could prove bit 15 is 0... then sign_extend is a no-op and folds to a copy, and then cse could propagate iv2c=tmp... but per the RM1 note, the HImode copy escapes cse2's equivalence class: cse treats a sign_extend as not a simple copy, so `iv2c = tmp` (the 32-bit copy) — hmm wait, which copy survives? `u = tmp` is the 32-bit copy where tmp is s16. Actually the "HImode copy" is `tmp = (s16)t` (a sign_extend), and then `u = tmp` is a plain reg copy. cse would equate u and tmp... and propagate u→tmp. But then tmp is a distinct pseudo from t, so the move survives (from tmp to whatever). Hmm, no: if u and tmp are equivalent and u is used, cse substitutes tmp for u, deleting the copy; then the use is tmp directly, which is t's sign-extended copy — the sign-extend itself is the surviving instruction (move/or).

Either way, the mechanism gives a surviving move. But is the emitted instruction `move` or `or`? If the sign-extension folds away at combine, tmp = t is just a copy and the move survives because it was born as a sign_extend rtx in a different... hmm.

Let me just test. w2: 
```
                {
                    s16 tmp;
                    tmp = (s16)iVar2;
                    iv2c = tmp;
                }
```
Hmm, but the target's move is `move v1,a0` where a0=iVar2. If tmp is a sign_extend of a0 and it folds to a copy, we'd get `move v1,a0`? Possibly.

But careful: the notes said "without it `iv2c = iVar2` folds into iVar2 (no `move v1,a0`), and sched puts `sw v0,-4(t0)` two insns late." So we need the move.

Alternative approach: keep iv2c but derive it from a different expression that isn't cse-equivalent yet compiles to a move. E.g., compute `iv2c = t + 1;` separately (duplicating the computation) — that would emit `addiu` not `move`. Unless combine... no.

Another: `iv2c = iVar2;` with iVar2 volatile? no.

Let me look at the target asm around that spot to understand precisely what instruction we need and where. Use hdump.sh? The header item has tu dumps. The dt/tryinc diff already shows. Let me get the full diff for the best candidate (prev_win with launder = 0) to see context, and the target disassembly.

Actually better: try several candidates and compare scores:
- w2: s16 temp before copy (as in RM1).
- w3: `iv2c = (s16)iVar2;`? Since iv2c is int, that's a sign-extend assignment.
- w4: declare iv2c as s16: `s16 iv2c;` then `iv2c = iVar2;` — narrowing copy; compare `iv2c != one` where one is int. Could emit `sll/sra`.

Let me create w2 (RM1 style) and w3 (cast form) and score both with sc.sh (header TU works since sc.sh reads tu/fn from item dir).

Wait, sc.sh does `delever_search.py --try $(cat $d/tu) $(cat $d/fn) $f --body` — that's the same as tryinc with k=0 without rotation. Fine.

Let me create them.

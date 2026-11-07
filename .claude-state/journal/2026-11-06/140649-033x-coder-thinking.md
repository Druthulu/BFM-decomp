---
ts: 2026-11-06T21:06:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uclgev7ePn08H4sIkCZ2
---
In the cse dump, insn 35 exists: `(set (reg/v:SI 4 a0) ...)`. So cse1 kept it. Combine folded it. Let me look at cse dump lines 80-105 to confirm.

So combine folds it. To stop combine, we need the copy to not be a single-use copy. Combine's try_combine requires the "i2" insn's source to be a register that is set by i1 and dead. 

Hmm, what about making the copy `ang = a` where ang is not a plain reg but requires a mode change — no.

New idea: make the *andi* not the last setter of `a`. If `a` is set twice, combine won't fold? E.g., if `a` were assigned then reassigned. But target has one andi.

New idea: what if we swap which variable is pinned: pin `ang` to $4, and have `a` be a normal variable? Then:
```
s32 a;
register s32 ang __asm__("$4");
a = (ratan2(...) - 0x400) & 0xFFF;
...
ang = a;
```
Then combine folds `a = and; ang = a` → `ang = and`; ang pinned $4 → andi writes $4? But then ang must be s0 for later use across the call. Since ang is pinned $4, that's wrong. Unless after the copy ang is re-copied. Hmm no.

Wait, actually maybe the answer is: the target's `move s0,a0` arises not from a copy but from local-alloc spilling the pinned $4 value to s0 because it's live across calls. But we saw the pin doesn't force.

Let me step back. The pin in orig.c is `register s32 a __asm__("$4")`. In GCC 2.7.2, a register-asm variable is represented as `(reg/v:SI 4)` — a virtual register with "user variable" and a hard reg assignment? Let me check what local-alloc does with it in orig. In orig (with asm), the final asm has andi a0 (=$4) and move s0,a0. So the pin did force $4 for `a`. In w1 (no asm), combine eliminated `a` entirely, so the pin had nothing to pin.

So with the asm, a is a distinct pseudo pinned to $4; the copy to ang (s0) survives. Without, combine folds.

Thus: need to keep `a` as a distinct live value. The asm was the only thing. Real C must give `a` another genuine use that the target also has.

Is there a genuine use of `a` in the target that we're not modeling? Let's re-examine the target carefully:
- 3498 andi a0,v0,0xfff  → a = ...
- 349c lbu v1, D_80126C01 → d
- 34a4 li v0,0x53
- 34a8 beq v1,v0, 3518
- 34ac move s0,a0  → ang = a
So a's only use is the move. No other.

So the target itself has a single-use copy! The original C (with asm) forced the copy. Combine didn't fold because the asm use existed at compile time even though it emits nothing. So the target's structure is inherently "a has a phantom second use" — which real C cannot express except via an asm or some zero-byte use.

Hmm, but the task says it should be crackable ("write a lever-free body that scores 0"). Maybe there's a real-C structure where combine doesn't fold: e.g., if the copy is in a different basic block than the andi.

What if the andi is in block 0 and the copy is in block 1 (the branch target)? The target's move is at 34ac in block 0 (before the beq, in its delay slot). But scheduling could move a copy from block 1? No, cross-block moves aren't done by sched1 within blocks... Actually reorg/dbr fills delay slots from the same block.

Alternative: make `a` live across a basic block boundary, so combine (per-block) can't fold. E.g.:
```
a = (ratan2(...) - 0x400) & 0xFFF;
d = D_80126C01;
if (d == 0x53) { ... }
```
If the copy `ang = a` is placed inside an if-arm, combine won't fold across blocks, and `a` becomes a global pseudo. But then a would be allocated by global-alloc, not necessarily $4. And the pin? The pin (register asm) forces $4 via local-alloc only for block-local pseudos; if a is global, the register-asm variable... Actually register-asm variables are always "user variables" assigned to their hard reg by local-alloc? Hmm.

Wait, in orig, `a` is block-local (block 0) and local-alloc gives it $4. If a is global (live across blocks), global-alloc would handle it, and register-asm might not apply.

Hmm, this is getting deep. Let me look at what other shards did for similar single-use pinned copies. Search moves.md for "$4" and "move". Or search for "pin" MATCH with copy.

Let me grep moves.md for "copy" + MATCH.

Actually, there's the wall `cse-copy-merge | cse | cse make_regs_eqv...` and `combine-copy-merge`. And line 285: `keepalive | func_800CB900 | WALL lreg-copy-pref-dying-base — ... no real C use after the load`. And line 69: `keepalive | func_80182424 | WALL combine-argcopy-sink — combine folds 1-use a1 pseudo into call-arg set at the call... keepalive 2nd use blocks merge (best 4)`.

That suggests this kind of thing is often a WALL. But maybe item 1 has a trick.

Let me reconsider: maybe use `d` in a way. The target loads d (lbu v1) and compares. What if the C uses `a` in the comparison? No.

Alternative: Change the order so the copy happens BEFORE the andi? No.

Wait — maybe use a different variable as the copy source. What if we write:
```
ang = (a = (ratan2(...) - 0x400) & 0xFFF);
```
Same.

What if we compute the andi into `ang` and then copy to `a`? Target: andi a0, move s0,a0. So andi writes a0, move to s0. If C is `ang = ratan2(...) - 0x400; a = ang & 0xFFF;` → andi writes a's reg ($4), then `ang` needs the value... but ang was assigned the pre-andi value; the target's move copies the post-andi value. Hmm, `a = ang & 0xFFF` then ang should be a. Not matching.

What about:
```
ang = (ratan2(...) - 0x400);
a = ang & 0xFFF;
ang = a;
```
That's an extra copy. Target only one move.

Hmm.

Let me look at the sibling func_80148AFC more: it uses `sVar3 = tmp;` where sVar3 is u16 — truncation. And the target for that function presumably has a truncation. Not helpful.

Let me look for other functions with the exact "andi a0 / move s0,a0" pattern in the repo — maybe a matched sibling exists with a lever-free body. The function family "func_80148D44" appears maybe in other overlays (dedup). Let me grep for "func_80148D44" in src to find duplicates, and also grep for the same body pattern. Actually the shared dedup means func_80148D44 might be in a shared header too. The list says item3 is a header item; item1 is a TU-specific function.

Let me search src for "func_80148D44".

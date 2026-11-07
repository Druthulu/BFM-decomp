---
ts: 2026-11-06T16:41:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kLGOjmr0tKJX1s7xiQYv
---
`birthing_insn_p`: SET to a REG that is live before this insn and `reg_n_sets[i] == 1`. So if a pseudo has exactly one set, the set gets max priority. The launder adds a second set → reg_n_sets = 2 → no boost.

So we need reg_n_sets(pv) == 2 at sched1 time, with the second set costing zero bytes and not being deleted.

Real-C candidates:
1. `pv = 0;` dead → flow deletes before sched1? flow1 runs before sched1. Does flow1 delete dead stores? Yes, dead store elimination is in flow.c's `propagate_block`? Actually gcc 2.7.2's flow does delete dead stores: there's `delete_dead_jumps`? Let me check flow.c for dead store deletion. Hmm, gcc 2.7.2 flow.c has "dead store elimination" via `mark_set_1`/`mark_used_regs`? I recall `flow.c` does have dead code elimination (`delete_insn` on `insn` whose value is dead and side-effect-free) — `dead_store`? Let me grep.

Actually the empirical result: w2 (`pv = 0;` dead) scored 11 = same as w1, so it was deleted (or didn't affect). Yes.

2. Make the second set *live* by using pv afterwards, but the use must cost 0 bytes. E.g., after `pv = 0;`, use pv in a context that's optimized to nothing... but then the set is dead again.

3. Make pv's second set a *partial* set: e.g., `((u16*)&pv)[0] = 0;`? That's a store to pv's stack slot — but pv is a pseudo (register), not memory. Taking its address forces it to the stack → changes everything.

4. Use a *different pseudo* for the second set and make reg_n_sets of the original... no.

5. Make the first set not birthing: if the register is NOT live before the set, no boost. Hmm, pv is live after (used by the OR). The boost requires `bb_live_regs` (live at block start?) & bit. `bb_live_regs` is the set of registers live at the beginning of the basic block. If pv is live at block start, and reg_n_sets==1 → boost.

Wait, re-read: `if (bb_live_regs[offset] & bit) return (reg_n_sets[i] == 1);` — bb_live_regs is the live-at-block-entry set. So if pv is NOT live at block entry, no boost at all! pv is a local set and used within the same block (the tail block). Is pv live at block start? No — it's defined in the block before use. Hmm, but the comment says the boost happens for `lw $v1,0($s1)`. 

Hmm wait, `bb_live_regs` might be the live set at the point of the insn (recomputed per basic block during sched). Let me not over-theorize.

Actually the key is reg_n_sets == 1. The launder makes it 2.

6. Can we make reg_n_sets(pv) == 2 without a real second set surviving? reg_n_sets counts SET insns after flow. A SET that flow doesn't delete because it's a *call-clobbered* use? Hmm.

7. What if pv is assigned in two *different branches* where one is dead? e.g.:
```
if (some_condition) pv = 0;   // adds a test (bytes)
```

8. What about a *loop* around the tail? no.

9. What if we split pv into two variables? Then neither is single-set? No, each would be single-set.

10. What if the second set is `pv = pv;`? combine/cse folds self-copy? A self-assignment `pv = pv` — expand emits a copy insn, then cse/combine may delete it as a no-op move (jump1's noop_moves deletes `(set (reg) (reg))`). Yes, jump1 deletes noop moves. So no.

11. `pv |= 0;` → folds.
12. `pv = pv + 0;` → folds.
13. `pv = pv * 1;` → folds.
14. `pv = pv ^ 0;` → folds.

15. What about `pv = *(u32*)p;` written twice as `pv = *(u32 *)p;` with the second load dead? flow deletes the second load if p is not volatile and the value dead... but the load is a memory read — flow won't delete a load unless it's provably dead (it does delete dead loads: `dead` insns with no side effects). A load from non-volatile memory is deletable. So deleted.

16. Use a *volatile* load? emits bytes.

17. `pv = (u32)p;`? That's a different value → would break the OR computation. Unless placed AFTER the last use of pv. After the OR, pv is dead; setting pv = (u32)p would be dead → deleted.

18. Make the second set needed: use pv as the value stored somewhere? e.g., `*(u32*)(ot+0x40) = ... | pv;`? That's a real use (the existing expression). What if we restructure so pv is used TWICE in a way that emits the same bytes? The existing OR uses pv once.

Look at the code:
```
pv = *(u32 *)p;
*(u32 *)p = (pv & 0xFF000000) | (CAST_NONSTRUCT(...) & 0xFFFFFF);
```
The target assembly: `lw v1,0(s1)` then `lui a0,0xff00` then `and v1,v1,a0` ... So pv is used once.

What if we write:
```
pv = *(u32 *)p;
pv = pv;  // deleted
```
no.

19. What if the second set is in a *different basic block* that's reachable but never executed? e.g., `if (0) pv = 0;` → fold removes. `if (D_800A651C) pv = 0;` → adds a test (bytes).

20. What about `switch (0) { case 0: pv = 0; }`? fold.

Hmm. So a zero-byte second set surviving flow seems impossible in real C — that's exactly why the launder (asm) exists.

BUT: maybe we don't need a second SET; we need to defeat the boost another way. The boost applies when `n_deaths == 0` and `birthing_insn_p`. `adjust_priority` is called for the *prev* insn (the one being scheduled). If the insn has REG_DEAD notes, n_deaths > 0 → priority shifted, no boost. The comment in adjust_priority says REG_DEAD notes are removed before this. Hmm.

Alternatively, the boost is applied to the *load* insn; if the load kills a register (has a REG_DEAD note), n_deaths>0 → no boost. Not controllable.

Alternative approach: change pv's lifetime so it's not live at the block start. `bb_live_regs[offset] & bit` — if pv is NOT live at block start, `birthing_insn_p` returns 0. Wait, re-read:

```
if (bb_live_regs[offset] & bit)
  return (reg_n_sets[i] == 1);
return 0;
```
So the boost requires pv live at block entry AND reg_n_sets==1. Hmm, that seems odd: a value live at block entry that is set once in the function... Actually `bb_live_regs` is the live-at-entry of the current basic block. The tail block contains the `pv = load` and the store. If pv is not live at block entry, no boost — but then why does the launder help? Because the launder changes reg_n_sets from 1 to 2. So pv IS live at block entry (it's used later in the same block but live-in means used before defined; since the set is at the top, pv shouldn't be live-in... unless the block boundary is elsewhere).

Hmm, whatever. The launder works via reg_n_sets.

Let me think about other real-C ways to make reg_n_sets(pv) == 2 with a zero-byte second set:
- A second set that flow keeps because it's *volatile*: `*(volatile u32*)&pv = 0;` → address-taken → stack. no.
- A second set inside an asm — lever.
- A second set that is a *call-clobbered* register restore? no.

What about making pv a *global*? Then reg_n_sets counts differently? A global (mem) isn't a REG set. no.

What if pv is an array element? memory.

Hmm, what about the "dead-reset" placed *inside* the same block but where flow's dead-store elimination doesn't apply because the store is to a register that is live-out? If pv is live-out of the block, the reset isn't dead. Is pv used after the tail block? No.

What if we make pv live-out by using it in a later block in a zero-byte way? E.g., after the tail, `if (pv) {}` → test insn.

OK, so maybe this item is also a WALL: launder with no real-C replacement.

But wait — C0414 says the dead-reset works "for stopping cse merging two computations of the same address/expression". Here we need sched1, which runs after flow. The dead-reset is deleted by flow → useless for sched1.

Hmm, but maybe flow does NOT delete the dead store if it's to a pseudo that is live-in at the block? Let me test empirically with w2: it scored 11, same as w1 → deleted.

Let me try variants:
- Place `pv = 0;` in the middle, right after the first use? The OR expression uses pv once. Place `pv = 0;` between the load and the store? That changes the value. no.
- Place `pv = 0;` after the store but before func_80016638 (same block?). Might be a different block boundary → if the block ends at the call, maybe not deleted? Let's try several placements.
- Use a *different* pseudo: `u32 pv2; pv2 = 0;` — irrelevant to pv's reg_n_sets.

Another idea: make pv's set NOT birthing by ensuring the dest register is not live at block start. That could be achieved by moving the `pv = *(u32*)p;` load into the same block as its use, separated from the block start by other statements? The block is the tail block starting after the `if (p[1] != 0)` etc. Hmm.

Actually, wait. Let me look at the target's tail block to understand what block pv lives in. The tail:
```
bidx = (u16*)&D_800B9A02;
pv = *(u32*)p;
*(u32*)p = (pv & 0xFF000000) | (...);
ot = ...;
*(u32*)(ot+0x40) = ...;
func_80016638(...);
```
The `lw $v1,0($s1)` is scheduled into the delay slot of `lhu $a0,0($a2)`. The launder kills the boost so the load stays earlier.

Alternative real-C: make `pv` not a single-set *register* by writing the load and use in one expression? e.g., `*(u32*)p = (*(u32*)p & 0xFF000000) | (...)` without the pv local — then the load is part of the expression; sched might place it differently. But the pv local is a T6 lever (needed for something else?). The orig comment says pv is pinned as $3. Wait, the orig has `register u32 pv __asm__("$3")` — a pin! But kinds says only "launder" — so the pin is considered a different kind not in the row (maybe "pin" isn't in this item's kinds; the brief says "levers of other kinds the def already had (pins under other causes) may stay, never added").

Wait, re-read the orig.c for item 2:
```
register s32 ang __asm__("$4");      /* §17 pin — see residual (a) */  // !FAKE: pin $4 ...
register u32 pv __asm__("$3");       /* §17 pin — see residual (b) */  // !FAKE: pin $3 ...
...
__asm__ __volatile__("" : "=r"(pv));   // !FAKE: launder out-only
```
So the item's kinds = launder only. The pins ang and pv are "levers of other kinds the def already had (pins under other causes) may stay". So I may keep the pins! The MATCH requires only the launder gone. But the pins are `register __asm__` — the brief says "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." Hmm, "Lever-free = none of the row kinds in <dir>/kinds remain". The row kinds are "launder" only. Then: "levers of other kinds the def already had (pins under other causes) may stay, never added". So the pins may stay!

That's important. So for item 2, I only need to remove the launder; the ang/pv pins may stay. Good — that's easier. But still, the launder's job (kill birthing boost) must be replaced by real C.

Wait, but the pins are `register ... __asm__` — the PARTIAL rule says "PARTIAL:<kept> means every row kind not in <kept> is gone from win.c (the expert diffs orig.c -> win.c lever lines)". For a MATCH, the row kinds (launder) must be gone. Other-kind levers (pins) may stay.

So the win.c for item 2 = orig.c minus the launder line, plus real C to replace its effect, keeping the pins.

Now, the pins might actually help! With `register u32 pv __asm__("$3")` pinned, the birthing boost still applies to a hard-reg pseudo? reg_n_sets for a hard register... The launder was still needed, so no.

Hmm. Let me think about replacing the launder's *effect* using the pin that's already there. The launder is `asm("" : "=r"(pv))`. With pv pinned to $3, the asm output forces $3. 

Real-C alternative to make reg_n_sets(pv)==2: since pv is pinned to $3, maybe we can write a real second assignment to pv that emits the same bytes as some existing instruction? E.g., if there's an instruction that already sets $3 somewhere, then pv's reg_n_sets... no, reg_n_sets counts SETs of the pseudo.

Hmm, wait. Let me reconsider: maybe a *real* second set that is live and emits zero bytes because it's coalesced. Example:
```
pv = *(u32 *)p;
...
t = pv & 0xFF000000;   // pv used
...
pv = t;                 // second set, live? if pv used later...
```
No.

What if pv is used twice and the second use is after a second set:
```
pv = *(u32 *)p;
*(u32 *)p = (pv & 0xFF000000) | (...);
pv = pv & 0xFF000000;   // dead
```
dead → deleted.

Let me test whether flow really deletes a dead `pv = 0` in this exact spot. w2 says score 11 (same as w1), so yes.

What if we place the dead reset *before* the store that uses pv? Then it's not dead (pv redefined after use). Actually:
```
pv = *(u32*)p;
pv = 0;          // kills the value; the later use would use 0 -> wrong semantics!
```
No.

Hmm, what if we do:
```
pv = *(u32*)p;
u32 q = pv;      // copy
pv = 0;          // dead? pv not used after -> deleted
```
deleted.

So no dead reset survives flow. Unless... flow's dead store deletion requires the insn to be in a block where the register is dead at block end. If pv is live-out of the block (used in a later block), the reset is kept. Can we make pv live-out with zero bytes? We'd need a use in a later block; any use costs an instruction.

Hmm, unless the later use is in a block that's *unreachable*? Unreachable blocks are deleted by jump1 before flow.

What about a use in a block reachable only via a branch that fold can't resolve? Costs a branch.

I think the launder is another genuine wall. But wait — C0505 lists many lever removals; maybe there's a known real-C replacement for "kill the sched1 birthing boost": "Set counts steer three passes: a second identical assignment demotes sched1's birthing boost". "a second identical assignment"! So `pv = *(u32*)p;` twice? The second identical assignment would be cse'd away... unless it's in a different block or cse can't merge. Hmm, "a second identical assignment demotes sched1's birthing boost" — the second assignment must survive. If identical, cse removes it. Unless separated by a store that cse thinks may alias (kills the equivalence)? But then the second load emits an instruction.

Hmm, what about `pv = *(u32 *)p;` and later `pv = *(u32 *)p;` where p is not modified — cse will fold. Unless we use the *volatile* pointer... no.

OK, another thought: since we may KEEP the pins, can we move the launder's function into an existing pin? No, pins are register steers.

Let me look at whether the pv pin is actually needed for the launder to work, and whether removing the launder while keeping the pins gives a different residual. w1 (no launder, pins kept) = 11. So no.

Maybe I can fix the residual (11) with real C instead of the launder: the load `lw v1,0(s1)` needs to be at its source position (before the `lui a0,0xff00`). The boost sinks it. What if we change the source so the load isn't a birthing insn: e.g., make pv live at the block start? Or not.

Wait — birthing_insn_p requires `bb_live_regs[offset] & bit` — the register is live at the START of the basic block. For the boost to apply, pv must be live at block entry. But pv is defined at the top of the block... unless the block starts earlier. Let me find the block: after `func_80016638` there's nothing. The block containing the tail probably starts at the `if (p[1] != 0)` join or at `bidx = ...`. pv is used in that block only. Live at entry = no (defined before use). So why the boost?

Hmm, maybe bb_live_regs is recomputed as "live at the insn"? Let me look at how bb_live_regs is set. Actually maybe it's `basic_block_live_at_start`. If pv is pinned to $3 (a hard register), and $3 is live at block start because of... hmm, $3 = $v1 is caller-saved. 

Wait, pv is pinned to $3, so its pseudo is a hard reg $3. `reg_n_sets[i]` for $3 counts all sets of $3 in the function! With the pin, pv's pseudo is hard reg $3, and $3 may be set by other code (e.g., temporaries). reg_n_sets[$3] could be 1 if only pv sets it. The launder's asm output sets $3 again → 2.

Interesting: so with the pin, the launder's effect is on the hard register $3's set count.

Could a real second set of $3 exist elsewhere that's already in the code? If another temp uses $3, reg_n_sets[$3] > 1 already. But it's 1.

Hmm, what if we add a *real* use of $3 (via a different variable pinned to $3)? That's a new pin — forbidden ("no new lever of any kind").

What if we reuse the existing `ang` pin ($4)? no.

OK. Let me consider: maybe a real-C second assignment to pv that survives because pv is pinned to a hard register — flow's dead store deletion for hard registers? Dead stores to hard regs are also deleted.

Let me just test a batch of placements of `pv = 0;` and other second-set ideas, plus ideas like making the load not single-set by splitting it:
- j01: `pv = 0;` right after the ot store (before func_80016638)
- j02: `pv = 0;` right after func_80016638 (w2, 11)
- j03: `pv = 0;` in the middle of the tail (after `ot = ...`)
- j04: `pv = pv;` at the end
- j05: `pv = 0;` then `func_80016638` uses... no.
- j06: second load `pv = *(u32*)p;` at the end (dead) 
- j07: `pv = (pv & 0xFFFFFFFF);`
- j08: `pv = (u32)p;` at the end
- j09: `pv = pv | 0;`
- j10: make pv live-out: `if (pv) func_80010A98();`? adds code.

Also: what about assigning pv from the *same load* in a different block? e.g., move `pv = *(u32*)p;` earlier (before the `bidx` line) so it's in a different block? That changes scheduling though.

Wait — actually, here's a thought: the source comment says the launder "kills the sched1 birthing boost". A second set that is *not dead* and costs zero bytes: what if the second set is `pv = pv;` and combine doesn't delete it because of the hard-reg pin? Let's test.

Another idea: `pv = (u32)&D_800A651C;`? real insn.

Let me test a batch.

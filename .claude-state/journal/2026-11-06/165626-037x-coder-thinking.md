---
ts: 2026-11-06T23:56:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GYO0yL6fWerIE0uBnpR6
---
Still s4 for mode. So refs 7 didn't flip. Let me check the score and whether the allocno order changed. The diagnostic added instructions so the code differs anyway. Let me look at the allocno priorities again with the dump... that's expensive. 

Let me instead compute: mode refs 7, live maybe 83+? The added `if (mode != -2 && mode != -3)` adds ~4 insns and extends... Actually the set is still at the same place; the extra refs are after the set, so live may grow.

Hmm, floor_log2(7)=2 (2^2=4 ≤ 7 < 8). So pri = 2*7/live. If live grew to 90: 14/90 = 1555 > 1518. Should have flipped. But it didn't. Maybe the allocno order isn't what I think, or the added refs changed live a lot.

Wait, maybe mode isn't r73. Let me verify by checking the .lreg dump for what r73 is. In the G_nopin dump, r73 has refs 5, live 83. mode has 5 refs: mode=-1, mode=0, mode>=0, mode (arg), mode==0. Yes that's 5. And live 83. So r73=mode.

And r72: 8 refs, 158 insns, pointer. base has 1 set + 7 uses = 8. Yes.

So the diagnostic should have flipped if pri ordering mattered. Unless my diagnostic didn't actually add refs to the same allocno (the `if (mode != -2 && mode != -3)` might be optimized: mode's known values? No, mode is a variable).

Hmm, or the added insns changed base's priority too? No.

Let me dump the diagnostic and check the order line. Actually, let me be smarter: let me directly check the order line in the new dump. But that requires re-running cc1 dumps with the diagnostic body. That's another ~1 min.

Hmm, time check. I've spent maybe 20 minutes on item 1. The budget is 20-30 min per item, and there are 3 more items. Let me be efficient.

Let me reconsider. Maybe the allocation isn't global for base/mode after all — the table shows r72/r73 with `hard = -` meaning global allocnos. And the .greg order line lists 9 allocnos.

Wait, the order line is: 144 79 76 78 74 75 72 73 77. Hmm, r144 first (pri 6000), then r79 (5333), r76 (5000), r78 (5000), r74 (3692), r75 (2413), r72 (1518), r73 (1204), r77 (1111).

Hmm wait, that's odd: r74 has pri 3692 but r76/r78 have 5000 and come first. Order is descending pri: 6000, 5333, 5000, 5000, 3692, 2413, 1518, 1204, 1111. Yes descending.

Now which regs does each get? The target (pinned) assignment: base=s4. In G_nopin: base=s3, mode=s4.

So in the order, the allocnos that get callee-saved regs: s0 is taken by r84 (local-alloc). Then s1,s2,s3,s4... 

r144 (pri 6000, refs 3, live 5, prefers v1, conflicts v0,a0,sp): doesn't cross calls? It got v1 in the target? Hmm, the table shows r144 hard='-' so global.

Let me get the actual final assignment from the .lreg dump's "Register N in M" lines. Let me grep for "Register 7" lines near func_800CFE60 that show the final hard reg. The table already gave: r84=s0, others '-'. So the .greg dump doesn't show final.

OK, let me instead look at the assembly: which allocno is in which reg? file=s1, val=s2, mode=s3/s4, base=s3/s4.

So the callee-saved allocation order among global allocnos: file (r74), val (r75), base (r72), mode (r73).

r74 pri 3692 > r75 2413 > r72 1518 > r73 1204. So s1=file, s2=val, s3=base, s4=mode. ✓ matches G_nopin.

Now why did r74 (val) not get s0? Because r84 (local-alloc) already took s0. And r144/r79/r76/r78/r77 got call-clobbered regs (they don't cross calls or prefer them).

So to flip, mode (r73) must outrank base (r72) — need pri_mode > 1518.

My diagnostic gave mode 7 refs. pri = floor_log2(7)*7/live = 2*7/live = 14/live. For live 83 → 1686. Should flip. But it didn't. So maybe the extra insns extended mode's live range: the added `if` is right after the set? No, it's before `cnt = ...`, which is after the set. So live grows from 83 to ~90 → 14/90 = 1555 > 1518, still should flip.

Unless the added code also changed r72's live/refs? No.

Hmm, maybe the register assignment I observed is not global-alloc's doing. Maybe s3/s4 assignment happens in LOCAL-alloc for... no.

Wait, actually! Maybe I misread. Let me look at the diagnostic's diff again: mine[105] `bltz s4` vs target `bltz s3` — so mode is still in s4. And `addu at,s3,at` vs `addu at,s4,at` — base still s3.

Let me actually dump the diagnostic to check the order line. It's worth 1 minute. Actually, maybe the `if (mode != -2 && mode != -3) { }` was optimized away entirely (empty body + the condition is `mode != -2 && mode != -3` which... the compiler can't prove always true, so it emits compares and a branch). Hmm, but with an empty then-block, jump1 might convert... it would still test. Let me check if the instruction count changed: the diff didn't show extra insns (score line not shown). Let me get the score.

Actually let me stop this diagnostic path and take a decision. Time.

Let me reconsider ONE more idea: what if the extra copy (launder fix) changes the allocno structure? When the copy exists, there's an extra pseudo q in v0 and p in a3. Does that affect base/mode? No.

BUT: here's a thought — what if I make `base`'s live range LONGER by moving its assignment to the top of the function (before file/val)? In C, `base = D_800AF630;` is already before file/val. The RTL set is at position ~29. Hmm.

What if I move `base = D_800AF630;` even earlier — it's already first among the assignments.

Hmm, what if base is read in the `file = D_800D34AC[...]` expression? no.

OK here's another idea: make base's live_length longer by adding a use at the very beginning AND end? Can't.

Alternatively, make mode's live range shorter by moving `mode = -1` into the `if` as an else? We discussed: the target has li s3,-1 in the delay slot before the branch, which could still come from `mode = -1` before the if. If instead:
```
if (st != X) { mode = 0; ... } else { mode = -1; }
```
the compiler would likely emit `bne` then in the else `li s3,-1`, not in the delay slot. But maybe it would still fill the delay slot! Actually reorg fills delay slots from the fall-through or target. Hmm, risky but worth trying? The emitted code must match exactly.

Hmm, wait. Actually there's a subtlety: `mode = -1; if (st != X) { mode = 0; ... }`. The `li s3,-1` at 10ec is in the delay slot of `beq v0,v1` at 10e8. If mode=-1 were in the else arm, the code would be `beq ...; (delay); ...; li s3,-1` in the else block. The target has it in the delay slot, so it's unconditional. So `mode = -1;` before the if. Confirmed.

OK. Let me now consider: maybe the LIVE LENGTH of mode can be reduced by using a different RTL shape for the `mode >= 0` test. E.g., `if (func_8002F658() != val || !(mode < 0))`. No change.

Alright — what if the ORDER of the two operands in `||` matters? `if (mode >= 0 || func_8002F658() != val)` would change code.

Hmm, let me look at the target's branch structure at 1200-1210:
```
1200: bne v0,s2,1210     ; func_8002F658() != val → branch to the mode test
1204: nop
1208: bltz s3,1230       ; mode < 0 → else (p=0)
120c: move a3,zero      ; p = 0 (delay slot)
1210: ...then...
```
So the `||` is short-circuit: if the call result != val, jump to the mode test. Yes.

OK. I'm going to accept this as a candidate WALL but first let me do the ≥30 tries requirement. Hmm, that's a lot of tries. Actually re-reading: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So to record a WALL I need 30 scored tries.

Given 4 items and 20-30 min each, 30 tries each is a lot but doable if I batch candidates (each sc.sh call scores many).

Let me be smart: generate 30+ varied candidates in one script and score them all in one sc.sh call. That's one try batch.

But first, let me reconsider whether there's a smarter approach for the reg order. 

IDEA: What if `mode` is used in a place where its live range is shorter because the RTL keeps `mode` in a *different* pseudo? For example, if the C uses a `s16` or `u8` for mode? Then the truncation adds SUBREG copies and changes code. But wait — maybe the target's `mode` is genuinely a narrow type! Let's check: mode values are -1, 0, and compared >= 0, == 0, and passed to CdReadRequest as s32. If mode were s16, the code would need sign-extends. Target has none. So s32.

IDEA 2: What if base is not a global allocno because it's used via a *struct pointer* that's recomputed? no.

IDEA 3: Split base into two variables used in different halves → then the address would be computed twice. No.

IDEA 4: What if `file` or `val` change such that they don't take s1/s2? They're fixed by target.

IDEA 5: What if we add a THIRD callee-saved allocno that takes s3 before base, pushing base to s4 and mode to s5? No, mode must be s3.

Hmm. IDEA 6: What if mode becomes a local-alloc pseudo? local-alloc assigns regs to pseudos whose live range is within a single basic block. If mode were confined to one block... it isn't.

IDEA 7: What if base and mode are in the same block and local-alloc... no.

OK, so the only lever is priority. Let me test the priority hypothesis properly by dumping the diagnostic. If raising mode's refs to 7 truly doesn't flip, my model is wrong and I should stop.

Let me do that dump quickly.

---
ts: 2026-11-06T12:26:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wIdChyr2GiySCTiMdjIr
---
q1 = 2, same as b0. So the do-while didn't change the y store's EBB placement (or the scheduler is sched2/reload doing it?).

Hmm, maybe the reorder is done by sched2 (post-reload scheduling) or by the store's position in the RTL. Since the insns are pure register ops (lui/ori) vs a store, maybe it's the "dbr" (delayed branch) or `reorg`... Or it could be `cse`/`flow`...

Wait, maybe the difference is not scheduling but the ORDER OF RTL EXPANSION? No — with the barrier present, the barrier forces the memory dependency: in gcc 2.7.2, an asm with a memory clobber acts as a full scheduling barrier in sched1 AND sched2. Since q1's do-while didn't help, maybe the reorder happens in sched2 (after reload), which uses a different block structure? Hmm, sched2 also works on EBBs.

Alternatively the reorder is by `flow`/`local-alloc`... no.

Let me test what happens if I insert a REAL dependency: make the 0x64808080 store's address depend on the y store's value? Can't.

Alternative: use a variable for the constant and make its assignment happen at the y-store point, e.g.:
```
*(s16 *)(q - 10) = y;
...
u32 c64 = 0x64808080;   // no
```
Already tried (o5 = 2).

What about making the y store the LAST statement before `q += 0x14; ot += 5;`? Then it's at the very end of the block. Target has it at 141 (early). No.

Hmm, what if the lui/ori pair is hoisted by the *reload* pass or by `cse`'s constant loading (cse creates the constant insn at the point of the first use and then it's placed by sched)? 

Let me look at it from the other side: in mine the order is [lui/ori][sh y]; in target [sh y][lui/ori]. What if I make the y value depend on the q pointer or on ot, so the sh can't move? It already depends on y (a load).

What if I make the 0x64808080 store use `q` (it does) and the y store use `q` too — both use q, so they're ordered by the memory dependency? No: stores to different offsets may alias, so sched must keep them in order — but the lui/ori are NOT stores; they're pure register ops that can be hoisted freely.

So the fix must prevent the pure constant build from moving above the sh. In target, the barrier (asm with memory clobber) blocks the pure insns from crossing it too (in gcc 2.7.2 sched, an asm insn with a memory clobber is treated as a barrier: `sched_analyze_asm` sets `sched_before_next_call`? Actually for a volatile asm with memory clobber, gcc sets `current_sched_info->...`; in sched.c 2.7.2 there's:

```c
  if (GET_CODE (PATTERN (insn)) == ASM_OPERANDS ...)
    {
      /* Mark as a barrier */
      ...
```
Let me check the reference source. tools/reference/gcc-2.7.2/sched.c — grep for ASM_INPUT/asm.

That would tell me whether an asm acts as a full barrier (all insns). If yes, then the only real-C way to make a scheduling barrier is... nothing (that's why it's a lever). But the do-while (loop note) should also create an EBB boundary — maybe sched2 ignores loop notes for EBB? Let me check whether the reorder is sched1 or sched2 by testing -fno-schedule-insns2... I can't change flags (the recipe is fixed).

Hmm, but I could check the cc1 dumps (tools/cc1_dumps_tu.sh) to see which pass does it. That costs disk/time.

Given the budget (20-30 min/item; I'm at ~15 min for this item), let me try 2-3 more ideas then settle for PARTIAL:keepalive here too (barrier uncracked → then it'd be a WALL, not PARTIAL).

Wait: PARTIAL requires win.c scoring 0 while keeping only some kinds. If I can't crack the barrier, then the only PARTIAL option is PARTIAL:barrier (keep the barrier, drop the keepalive) — but the keepalive is the one at 19. Can I crack the keepalive while keeping the barrier? Then PARTIAL:barrier with score 0. The keepalive is at 19 and I haven't cracked it.

So for item 2, if neither cracks → WALL with best = 21 (lever-free) or 19 (keepalive dropped, barrier kept = k0.c). The WALL row's best = lowest score of a lever-free body = v0.c = 21. Hmm, but "lever-free body" = neither lever. v0 = 21.

Let me push a bit more on the keepalive (19, REG-caller). The rotation t0↔a2↔a3.

Let me look at where these registers are used and identify the 3 pseudos. Target:
- 50-51: lui a2,0x0; addiu a2,a2,0 → address of D_800B9A02 into a2 (pb).
- 59: lhu a0,0(a2) → *pb
- 73: lhu v1,0(a2) → *pb again
- 102: move t0,zero → j = 0
- 103: move a3,v1 → k = m
- 105: move t2,a2 → save pb into t2
- 106-107: lui a2,0xff; ori a2,a2,0xffff → m24
- 108: move t3,a3? etc.

Mine: address in t0 (saved to t2 at 105 as `move t2,t0`), j in a3 (`move a3,zero`), k in a2 (`move a2,v1`), m24 in t0.

So the allocator's preference order differs: target gives a2 to pb (5 refs from the asm), then a3 to k, t0 to j. Mine: a2 to k, a3 to j, t0 to pb.

So I need pb's priority up. pb's refs without the asm: how many? Let me count real uses: line 36 (D_800AE7BC[*pb].ot[2] — 1 load), 37-38 (2 loads?), 86, 89 (2 loads). Actually `D_800AE7BC[*pb].ot[2]` at line 36 and `D_800AE7BC[*pb].ot[2]` twice at 37-38 — the CSE may merge the two in 37-38 (same statement, same address, same block? there are no stores between... there IS a store to D_800AE7BC[*pb].ot[2] at line 37 before line 38's read → so not merged).

So pb has ~5 real refs already. And the asm adds 5 → 10. So the priority difference is 5→10 refs.

Can I add real refs without adding instructions? Each use of `*pb` is a `lhu` (an instruction). Unless... the same load is used multiple times: e.g. `u16 pi = *pb;` then use pi. That's 1 load + more uses of pi (a different pseudo). No.

Hmm, unless: use pb in a place where the address is used as a base without a load: e.g. `((u8*)D_800AE7BC)[*pb * 0x14]`... still a load.

OK so how about lowering the others' priority? k's live range spans the loop; j too.

What if I make k die early? k is used in the loop (both branches). j is the loop counter.

Alternatively, change the loop shape: `for (; j < 2; j++)` — target has the same.

Alternatively: give the address pseudo a longer live range or a use later. It IS used late (86, 89).

Priority in global-alloc = floor_log2(refs) * refs + live-length-based... In gcc 2.7.2, `global_alloc` computes:
```
priority = floor_log2 (REG_N_REFS (allocno)) * ... + (live_length / freq)
```
Specifically: `allocno_priority` = `(int) floor_log2 (n_refs) * n_refs * ...`? Let me check gcc 2.7.2 global.c. Actually:

```c
  /* Compute the priority of each allocno */
  ...
	  /* Add the length of the live range, weighted by the frequency */
```
Something like: `pri = floor_log2(n_refs) * n_refs` plus loop-depth weighting, and ties broken by `allocno` number.

With 10 refs: floor_log2(10)=3, 3*10=30. With 5 refs: floor_log2(5)=2, 2*5=10. Big difference. So the asm's 5 refs are worth a lot.

Real-C: get pb to ~10 real refs? That would need 5 more loads.

Alternatively lower k: k's refs? k = m (1 def), D_80115140[k] (2 loads in the loop: line 64 and 71), k*2 (line 70), D_80115140[k] again... plus `((s8*)D_80115158)[k2]` and `((s8*)D_80115140)[k]`. So k has ~5 refs too, plus loop-depth weighting (the loop runs twice → refs weighted by loop depth? In global.c, REG_N_REFS includes loop_depth multipliers from flow).

Since both are ~5, and the address pseudo is in a hot loop too, the tie is decided by allocno number/order.

Honestly: to add real refs to pb, I could restructure `D_800AE7BC[*pb].ot[2]` as a repeated expression... 

Hmm! What about the struct: `Env_8017EFA8 D_800AE7BC[]` — `D_800AE7BC[*pb].ot[2]`. If instead I write the address computation with pb appearing twice naturally: `D_800AE7BC[*pb].ot[*pb - *pb + 2]`? launder — forbidden.

OK. Another approach to the whole item: maybe there's a different real-C formulation of the keepalive region. E.g. the `pb2` variable: since `pb2 = (u16 *)&D_800B9A02;` is a copy, maybe in the target pb2 IS the same pseudo as pb (cse), and the asm's 5 refs are on that shared pseudo. In my v0 (both asm removed), pb and pb2 might also be merged.

Let me check the current k0/v0 stream: is there one address build or two? Target has one (`lui a2,0x0; addiu a2,a2,0` at 50-51) and mine has one (`lui t0,0x0; addiu t0,t0,0` at 50-51). So yes, merged.

So the sole issue is the register choice for that pseudo. 

What if I make the address pseudo a "constant" that gcc rematerializes instead of keeping in a register? Then it'd appear twice (2 lui/addiu pairs) — count mismatch.

Hmm.

Let me try one more class of moves: change the ORDER of `pb = ...` relative to `c0 = ot[0];` etc. (the register pressure at that point). p1 (init at decl) gave 37.

Let me try moving the pb assignment EARLIER (before `c = D_80115138[...]`) or later (after `pb = ...` is at line 34; try moving it to just before its first use at 36). p1 moved it to the declaration (very early) = 37. Maybe "just before use" is better? It's already effectively there (line 34, use at 36).

Alternatively move `c0 = ot[0];` etc.

Let me step back and consider the time budget: item 2 has used ~20 min and ~16 tries. I need ≥30 tries for a WALL. Let me do a broader sweep of small statement reorderings around the pb assignment and the m24/mhi assignments (lines 58-61) — those constants (m24, mhi) are exactly the pseudos competing for t0/a2! In target: m24 = 0xFFFFFF goes to a2 (after saving pb), mhi = 0xFF000000 goes to... `lui v1,0xff00`? 

Look at target 105-108: `move t2,a2` (save pb), `lui a2,0xff; ori a2,a2,0xffff` (m24 = 0xFFFFFF). And mhi = 0xFF000000 would be `lui` alone.

So the constants m24/mhi are pseudos too. They're used at lines 86, 90.

What if I declare m24/mhi as `#define`-like constants inline (no variables)? E.g. use 0xFFFFFF directly at the use sites. Then the constant build happens at each use (2 sites → more insns?). Target builds them once each. Hmm.

Let me try: remove the m24/mhi variables and use literals in the two places. Count might change.

I think a more productive angle: accept and record. But let me first try a quick set of "m24/mhi placement" variants (5 tries) to reach 30 and maybe hit gold:

r1: move `m24 = 0xFFFFFF; mhi = 0xFF000000;` to just before their first use (after the for loop starts)? They're already before the loop.
r2: swap them: `mhi` first then `m24`.
r3: declare m24/mhi at the top (with pb).
r4: use literals instead of m24/mhi.
r5: move `q = (u8 *)ot + 0x14;` before `m24`/`mhi`.

Let me run these.

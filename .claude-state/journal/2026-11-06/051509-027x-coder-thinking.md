---
ts: 2026-11-06T12:15:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4mYvEjNLOy1MCHJCO2gR
---
Target cluster A: index 313 `sh v0,22(s0)` (tpage store) then 314-315 andi/srl a0 (attr&0x40>>6), 316 lbu v1,7(s0), 317 lhu v0,22(s0) (reload tpage for q[0x0C]), 319 andi 0xf, 320 sll 6...

In mine (v0.c without barrier), the order is: ... 313? mine had at 313-316: `srl a0,a0,0x6` then `sh v0,22(s0)`. So in mine the andi/srl pair moved before the store. That's the sched1 reorder that the barrier prevented: the `q[7] |= (attr & 0x40) >> 6` computation gets hoisted above the store.

Without an asm barrier, how to stop that? Real-C options:
1. Compute the store value from a variable that depends on the RMW? No, changes semantics/order.
2. Split the store into the if-arms (duplicate store) — moves.md: "barrier->store per if-arm". With the store inside each if-arm branch, the q[7] RMW is outside the branches; sched1 would then... hmm the store is in a preceding block, the andi in the fall-through block. Sched1 can move instructions across basic block boundaries only with the extended basic block (EBB) and only if no dependency. The store sh v0,22(s0) and lbu v1,7(s0) — different addresses, so it can move the andi above the store (as it did). Hmm, actually the srl a0 moved before the sh: the andi/srl are independent of the store. If the store is in a branch block, then the andi after the join is in a different block... sched1 region scheduling can still move across? It moves within extended BB (only one successor). After if/else, the join has two predecessors → not an EBB, so no upward motion across the join. That would fix it.

But careful: duplicating the store per arm means the `tpage` value computed per arm and stored per arm. Currently tpage is computed in the if/else (two levels) then stored once. If I put `*(u16 *)(q+0x16) = tpage;` inside each of the 4 arms, codegen changes elsewhere (each arm ends with the store). The target has a single store after the join (index 313 follows or v0,v0,v1 at 312 — the 4 arms jump to a common label at 302 `j d0d0 <+0x4e0>`; hmm target shows `j d0d0` at 302 then 303 srl v0,v0,0x6... and 309 or v0,v0,v1, 312 or v0,v0,v1, 313 sh). So target has the 4th arm fall through into the join, with a single store at the join. So duplicating the store would change the target's shape (the target's store is at the join, one copy). Duplicating would put 4 stores and the join would start at the andi — that would not match.

Hmm wait, actually maybe it would: if all four arms each do the store as their last statement, the compiler might tail-merge them (cross-jump/jump2) back into one store at the join? jump2 cross-jumping can merge identical tails. Risky.

3. Make the andi/srl depend on the store: e.g. compute `attr & 0x40` from a value loaded after the store. Hmm, "q[7] |= (attr & 0x40) >> 6" — attr is a local variable. If instead I read attr from memory at that point? No, attr is arg0->unk4; target keeps it in a register.

4. The cookbook C0535: do{}while(0) splits cse1 EBB. That's for cse, not sched1. Here it's sched1 moving andi/srl above the store. Would a do{}while(0) block boundary stop sched1? sched1 works on extended basic blocks; a do-while creates a loop (NOTE_INSN_LOOP_BEG?) which splits the EBB. In the worked example "do-while -> goto loop" cracked barriers. Interesting: cookbook C0535 says do{}while(0) splits cse1 EBB. For sched1, a LOOP_BEG note ends an EBB too.

Hmm, but the barrier here is needed between the store and the q[7] RMW — both inside the same block. If I wrap the RMW (or the store) in a do{}while(0), the loop note splits... where? The note is emitted before the loop body. So `do { q[7] |= ...; } while (0);` puts LOOP_BEG before the RMW; sched1's EBB then ends at the note, preventing the andi from being hoisted above it. And the store stays before. That's a plausible real-C move (C0535).

But careful: does the do-while alter anything else? flow's loop notes add loop_depth weight for register allocation (the keepalive crack used that). Since we want to preserve the rest exactly, a loop note might change priorities of regs referenced in the loop. q[7] RMW references q, attr — those get +refs. Risky but let's measure.

5. Alternative: make the store value used by the next statement so the store's position is fixed by a dependency: e.g. `q[7] |= (attr & 0x40) >> 6;` doesn't use tpage. But q[0x0C] uses `*(u16*)(q+0x16)` reload. We could make the store the last use... no.

Alternative: `*(u16 *)(q + 0x16) = tpage;` then `q[7] |= (tpage & 0x40) >> 6`? No — that changes semantics? tpage's bit 0x40... no, must be attr.

Hmm what about reordering: put `q[7] |= (attr & 0x40) >> 6;` BEFORE the store? Target order: store, andi, srl, lbu, lhu, or, andi, sll, sb. So the RMW happens after the store and reloads q+0x16 after. If I write the RMW before the store in C, then q[0x0C] would read... it'd still be fine semantically (RMW of q[7] doesn't touch q+0x16). And then the store comes after. But target wants store first then andi/srl/lbu. If in C the RMW is written first, the target order can't come out... unless sched1 moves the store up. Actually target's `sh v0,22(s0)` at 313 before andi at 314 — if C order is RMW first, sched1 would need to move the store above, unlikely.

So option 4 (do-while) or a "store per arm".

Also cluster B (indices 371-385): the keepalive. Target:
```
371 lhu v0,-2(s3)      ; v0.vy = p->unkA  (vv2)
372 lw  v1,212(sp)     ; sz
373 srl a0,s1,0x18     ; vh = rec>>24
374 sh  v0,72(sp)      ; v0.vx? wait
375 srl v0,s1,0x10     ; vw = rec>>16
376 lhu a1,0(s3)       ; v0.vx = p->unk8
377 andi v0,v0,0xff    ; v1.vx = vw & 0xFF
378 sh  v1,76(sp)      ; v0.vz = sz
379 sh  v1,84(sp)      ; v1.vz = sz
380 addiu v1,sp,72
381 sh  v0,80(sp)      ; v1.vx = vw&0xff
382 addiu v0,sp,80
383 sh  a0,82(sp)      ; v1.vy = vh
384 sh  a1,74(sp)      ; v0.vx
```
So the target holds vh in a0, vv2 in v0, vw in v0(later). Mine (v0.c): srl v0,s1,0x18 at 378, sh v0,80(sp) at 377, sh v0,82(sp) at 382, sh a0,74(sp) at 384 — different order/registers.

The keepalive asm `"r"(vh),"r"(vv2),"r"(vw)` buys refs/priority so vh, vv2, vw get their own registers and the stores order right.

Real-C alternatives: the move "keepalive replaced by return v0" (function returns void here, can't). "do-while ref weight" — wrap in do{}while(0) to add loop-depth refs (flow REG_N_REFS += loop_depth) → boosts priority of p etc. Here the refs that need boosting are vh, vv2, vw... hmm, the asm operands give them priority as "used in asm"? Actually asm operands force them to registers with a high priority? An asm with "r" constraints makes each operand a hard... no, it makes them allocated in registers and creates an extra use (REF) which raises priority.

Alternatively: restructure the C so those values are used in a way that forces the same allocation — e.g. write v1.vy = vh directly from the expression, no temp: `v1.vy = rec >> 24;` then the value is a single-use temp... The note (c) says splitting the shift from its mask separates priorities.

Hmm, this is a hard, huge function. Given the budget, let me do a handful of measured attempts:

Attempt 1 (cluster A): wrap the RMW in do{}while(0) [C0535] → does it fix cluster A? Combined with keeping the keepalive removal.

Actually, better to isolate: I'll try candidates that address A only, then B only, then both.

Let me first try the C0535 do-while on the RMW (line: `q[7] |= (attr & 0x40) >> 6;` → `do { q[7] |= (attr & 0x40) >> 6; } while (0); // !FAKE: do-while`). Wait — but the brief says `do{}while(0)` only with `// !FAKE: do-while`. OK.

Hmm, careful: the do-while adds a loop note which changes ref weights for q and attr inside, potentially perturbing everything. Let's measure.

Let me create v1.c from v0.c with that change.

For efficiency, let me create a batch of candidate files and score them all with sc.sh in one command (each ~? seconds). Compile of 800.c takes some seconds. Let's do 4 candidates at a time.

Candidates for cluster A:
- A1: do-while around the RMW statement.
- A2: do-while around the store + RMW? i.e. `do { *(u16*)(q+0x16) = tpage; q[7] |= ...; } while (0);`
- A3: store per arm (duplicate into each of 4 arms) — that's a bigger edit.
- A4: volatile? No — volatile is class C/D "byte-needed", not allowed as a lever? It says no new lever of any kind. So no.

Candidates for cluster B:
- B1: remove the temps vw/vh and use expressions directly: `v1.vx = (rec >> 16) & 0xFF; v1.vy = rec >> 24;`
- B2: keep vw/vh but add a do-while around the block to weight refs.
- B3: reorder the v0/v1 fill statements.
- B4: reuse vv2 = p->unkA in both places... 

Let me look at the original declaration/statement block again (lines 10317-10326):
```
v0.vx = ((Unkstruct_8001EFE0_2 *)p)->unk8;
vv2 = ((Unkstruct_8001EFE0_2 *)p)->unkA;
v0.vy = vv2;
v0.vz = sz;
vw = rec >> 16;
v1.vx = vw & 0xFF;
vh = rec >> 24;
v1.vy = vh;
v1.vz = sz;
__asm__("" : : "r"(vh), "r"(vv2), "r"(vw));
```
Note the target order: v0.vy store (sh v0,72(sp)) comes first at 374 with v0 = lhu -2(s3) (vv2), then sz (v1=212(sp)) at 372 loaded before. Hmm.

Real-C replacement idea: make vv2, vw, vh used twice each (real second use) so they get registers without the asm. E.g.:
- vv2 used in v0.vy and in... v1? no.
- vh = rec>>24 is used for v1.vy and q[0x1D] = q[0x0D] + (rec>>24) earlier. Actually `q[0x1D] = q[0x0D] + (rec >> 24);` is earlier in the body. If I hoist `vh = rec >> 24;` before that statement and use `vh` there, then vh has 2 real uses → gets a register and priority. Similarly vw = rec>>16 used in v1.vx and `t14 = q[0x0C] + ((rec >> 16) & 0xFF)` — hoist vw there. That's a legit real-C move: declare vh/vw once, use in both places.

But careful: hoisting vh earlier changes where the srl is computed — target has srl a0,s1,0x18 at 373 (late, near the fill), and the earlier statement q[0x1D] = q[0x0D] + (rec>>24) would then reuse it. Hmm, but target's q[0x1D] computation: let me check where the srl for q[0x1D] happens. In the target stream around 340-360? Let's dump 320-365.

Actually let me get the whole target stream in a file to reason about it. 468 insns, that's a lot but I can grep specific spots.

Let me be strategic. Time check: started 05:10. Item budget 20-30 min. It's maybe 05:25 now. Let me try a couple of quick candidates and move on.

Actually wait. Let me reconsider the overall economy: 4 items, each potentially a WALL. A WALL needs ≥20 min and ≥30 scored tries. 30 scored tries × 4 items = 120 compiles. Each compile of a big TU maybe 3-6 s → ~10 min. OK feasible. But for item 1 (468 ins), 30 tries.

Hmm, ≥30 scored tries is a big requirement. I should automate: generate many candidate variants programmatically and score them in a loop (sc.sh with many files). That's the efficient path: write a generator script producing variants (statement orders, temp splits, do-while placements), score all, look for 0.

But each variant must be semantically valid and compile. A generator that permutes a handful of specific edits is fine.

Let me first do quick manual probing to learn the mechanics (2-4 candidates), then automate a sweep.

Let me do the A/B isolation first: candidate "A only fixed" (do-while on RMW, keepalive still removed) and "B only" variants.

Let me build candidates.

v1: v0 + do-while around RMW.
v2: v0 + do-while around both store and RMW.
v3: v0 + vw/vh hoisted to earlier uses (2 real uses each) — plus maybe vv2.

Actually for v3 the hoist requires editing two earlier statements. Let me look at those earlier lines: 
- `t14 = q[0x0C] + ((rec >> 16) & 0xFF);` line 10300
- `q[0x1D] = q[0x0D] + (rec >> 24);` line 10304

Hoisting `vw = rec >> 16;` to before 10300 and using `t14 = q[0x0C] + (vw & 0xFF);` and `v1.vx = vw & 0xFF;` gives vw two uses.
Similarly `vh = rec >> 24;` before 10304, `q[0x1D] = q[0x0D] + vh;` and `v1.vy = vh;`.

And vv2: `vv2 = ((Unkstruct_8001EFE0_2 *)p)->unkA;` used in v0.vy only. Could also use it in q[0x1D]? No.

Let me create these candidates with a python generator to keep edits precise. Actually simple sed-like edits are fine with python.

Let me write gen1.py that produces v1..v4 from v0.c by string replacement. I'll do it as a script for reproducibility.

Actually, quicker: use Edit tool on copies? No, copies via python script is better.

Let me write the script.

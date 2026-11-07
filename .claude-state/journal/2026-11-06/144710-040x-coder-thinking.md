---
ts: 2026-11-06T21:47:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_p9tIqmPpY1FyR1Gg5Fbr
---
Now I have the RTL. Key pseudos:
- r84 = oidx (reg/v:SI 84), defined insn 344 (ashift), used insn 358 (plus) and insn 375 (plus, REG_DEAD). So oidx: def 344, uses 358, 375. n_refs = 3 (1 def + 2 uses). It's a `reg/v` (a variable) — local qty.
- r182 = packet word (set at insn 347 from mem (reg/v:SI 77)); used insn 350 (and), REG_DEAD. Only ONE use! The load r182 is used at 350 `and r182, r184`, and REG_DEAD. So n_refs = 2 (def + 1 use). Its live range: birth at insn 347, death at 350.

Wait but the disassembly showed `lw a0,0(a3)` then `and a0,a0,a2` then `or a0,a0,v0` — a0 is r182/r183/r194 combined by copy coalescing? Let's see: r182 = mem(pkt). r183 = r182 & r184 (mask 0xff000000). r194 = r183 | r192. The store stores r194. So r182 dies at 350, r183 dies at 366.

The register that ends up in a0 is r183? At 190 `and a0,a0,a2` = r183 = r182 & mask, with r182 coalesced into a0 (same reg). At 193 `or a0,a0,v0` = r194 coalesced into a0.

So the qty that competes for $3 vs $4: r183 (and result) maybe, or r182, or r194. Let's compute:
- r84 (oidx): def 344, death 375 → live 31, refs 3. pri = floor_log2(3)*3/31 = 1*3/31 = 0.0968 → *10000 = 967.
- r182: def 347, death 350 → live 3, refs 2 → floor_log2(2)=1, 1*2/3 = 0.667 → 6666.
- r183: def 350, death 366 → live 16, refs 2 → 2/16=0.125 → 1250.
- r194: def 366, death 368 → live 2, refs 2 → 2/2 = 1 → 10000.
- r184 (const -16777216, mask): def 349, death 350 → live 1, refs 2 → 2/1=2 → 20000.
- r193 (0xffffff): def 401 (before), death 365? used at 365, def at 402/401. Hmm r193 defined insn 401 and 402 (combined), used 365. Live maybe 401→365? scheduling order weird.
- r191: def 362, death 365 → live 3, refs 2 → 6666.
- r192: def 365, death 366 → live 1, refs 2 → 20000.

Highest priority: r184 (20000), r192 (20000), r194 (10000), r182 (6666), r191 (6666), r183 (1250), r84 (967)...

Wait, that gives r184 the mask $2? But in target a2 = 0xff000000 (r184 = const -16777216). Indeed a2! And r193 (0xffffff) = a1. r194 (ior result) = a0? But r194 is very short-lived; it's coalesced with r183/r182 into a0.

Hmm, but the registers: v0, v1, a0, a1, a2, a3... The allocation order: r184 (pri 20000) gets first free → $2 (v0)? But target has r184 in a2! That contradicts... unless there's an ordering where $2..$5 already taken by others.

Wait, actually local-alloc allocates registers per basic block, and the order within the block matters. Also `qty_size` might be 1 for all.

Hmm, target r184 = a2 ($6). Why not $2? Because $2, $3, $4, $5 are taken by other qtys with higher priority? The priorities above say r184 is highest (20000). Unless there are other qtys earlier in the block with even higher priority that take $2..$5.

But these are all in the same basic block, so conflicts are by live range. A qty with live 1 and refs 2 has priority 20000. Several. The allocation order is by priority; each takes the first free reg (lowest number) that doesn't conflict with already-assigned overlapping qtys.

Let me identify all qtys in this tail block and their priorities. But actually the relevant comparison is between r84 (oidx) and whatever got $3 and $4.

In mine: $3 = packet chain (a0 target). Which qty? The packet chain got v1. In target it got a0($4). oidx: mine a0($4), target v1($3).

So in mine, packet chain has higher priority than oidx (967). The packet chain qty is probably r194 (pri 10000) or r183 (1250). Since r194's live is short but it's the store value — its register must be distinct from others at its live range.

Let me think about allocation order. All these are local qtys in one block. Local-alloc sorts by priority descending and assigns the first free hard reg in class, checking conflicts with already-assigned qtys whose live ranges overlap.

Priority order (descending): 20000 (r184, r192), 10000 (r194), 6666 (r182, r191), 1250 (r183), 967 (r84), ... and various others (r186, r187, r189, r197, r198, r181, r180, r178, r193...).

Let's compute more:
- r180: def 338, death 340 → live 2, refs 2 → 1 → 10000.
- r178: def 334, death 338 → live 4, refs 2 → 0.5 → 5000.
- r181: def 343, death 344 → live 1, refs 2 → 2 → 20000.
- r186: def 353, death 354 → live 1, refs 2 → 20000.
- r187: def 354, death 358 → live 4, refs 2 → 5000.
- r189: def 358, death 362 → live 4, refs 2 → 5000.
- r191: def 362, death 365 → live 3 → 6666.
- r197: def 373, death 375 → live 2 → 10000.
- r196: def 372, death 373 → live 1 → 20000.
- r198: def 375, death 379 → live 4 → 5000.
- r193: def 401 (set const 16711680) and 402 (ior → REG_EQUAL 16777215): so it's set twice; used at 365. Live from 401? The insn order 401 comes after 334 (line 57547), before 338. So r193 def at 401, then 402 (ior), used at 365 (insn 365). Its live range spans 401..365 which in the linear order is long: 401 at position ~... 402 after 343. So live maybe 60. refs 3 (2 defs + 1 use). pri = 3/60 = 0.05 → 500.

Hmm, so r193 (0xffffff mask) is in a1 in target. 

Registers available: $2 v0, $3 v1, $4 a0, $5 a1, $6 a2, $7 a3, $8 t0.., plus callee-saved. In this tail, a3 = pkt (r77, global), t1 = base? (r76 global?), fp=30. So a3 and t1 are taken by globals (r77, r76). $2..$8 mostly free.

Local allocation order by priority:
20000: r184, r192, r181, r186, r196, ... and maybe others.
- r184 (mask 0xff000000): live 349-350. First free $2 → gets $2? But target a2. Hmm.

Unless some other qty with pri 20000 and earlier qty number takes $2, then r184 gets $3? But target r184=a2.

Hold on — maybe the const pseudos like r184 are *not* allocated by local-alloc; constants can be rematerialized. In target a2 = lui a2,0xff00 = r184 in a2. And a1 = r193.

I think my priority model may be missing `qty_size` for const_int pseudos: r184 is SImode size 1.

Why would r184 land in a2? Because $2..$5 were already assigned to other overlapping qtys when r184's turn came. But priority 20000 is the top; ties broken by qty number (lower first). r184's qty number: qtys are allocated at birth in insn order; r184 born at 349, so qty number based on position. r181 born at 343 (earlier) would have lower qty number and also pri 20000 → allocated first → gets $2. r181 = the otz load (lw 20(sp))? Wait r181 is `(set (reg:SI 181) (mem/s:SI (plus fp 20)))` = the g.otz load at insn 343. And r84 (oidx) = ashift of r181. r181 has 1 use (344) and dies at 344, live 1, refs 2 → 20000. It gets $2 (v0)! Indeed in target, the otz load is `lw v1,20(sp)` — v1 not v0. Hmm, in target 178 `lw v1,20(sp)`. So r181 = v1? But then r84 (oidx) would also be v1 (coalesced copy!). 

AH — that's the key! r84 = (ashift r181 2) is a *copy-like* relation? No, shift isn't a copy, but local-alloc's `combine_regs` may tie the output to the input if the input dies (r181 is REG_DEAD at 344). Look at local-alloc combine_regs: when an insn is `set (reg A) (expr (reg B))` and B dies, it may tie A and B (copy preference) so A gets the same register. Yes! `reg_copy_sugg` / qty_copy_sugg. So r84 gets r181's register if possible.

In target: r181 → v1 ($3), so r84 (oidx) → v1 ($3). That matches target: oidx in v1!

In mine: r181 → a0 ($4), so oidx → a0 ($4). Matches mine.

So the real question: why does r181 (the otz load temp) get $3 in target but $4 in mine? r181 is born at insn 343 and dies at 344. Its priority 20000, same as r184, r192, r196, r178? no.

Allocation order among pri-20000 qtys is by qty number (birth order). r181 born at insn 343. Other 20000 qtys: r178 (5000), r180 (10000), r184 (born 349), r186 (353), r192 (365), r196 (372). Also r? Let's list by birth: r181 (343) is the earliest among 20000. So r181 should get $2 (v0) if free!

But wait, r181's live range is 343-344. Are there conflicting earlier-assigned qtys? $2 might be occupied by a qty with higher priority? There's none higher than 20000. Unless some qty has refs 4: floor_log2(4)=2 → 2*4/live. E.g., a qty with refs 4 and live 2 → 4. Or the loop-weighted? Hmm.

Actually, r181's qty gets a *copy suggestion* to r84's... no. Let's think about the copy tie: combine_regs ties r84 and r181. The tie makes qty_sugg: r84 has copy_sugg to r181's reg. Then in the suggested phase, r84 gets... Actually the suggestion is between pseudos; local-alloc picks one.

But the disassembly: in target, the otz load result and oidx are both v1 — so the tie worked and both are in $3. Why $3 not $2? Because when r181 was allocated, $2 was busy? $2 is v0; at insn 343-344, what's live? The div result `mulc`? mulc is in... let me see: earlier insns. mulc (r?) might be in $2 at that point? In the target disasm around 170-180, is v0 live? At 178 `lw v1,20(sp)` — before that at 174 `lw a0,0(a3)`, 175 `addu v0,v0,a2`, 177 sh. v0 is used at 173-177 as a temp for the sh values. So at insn 343 (which is scheduled at position ~178), $2 (v0) is live with a temp. So r181 can't get $2 → gets $3. That explains v1.

In mine, the same scheduling: at 178 mine has `lw a0,20(sp)` — so r181 got $4. Why not $3? $3 might be busy at that point in mine! In mine, the packet word load `lw v1,0(a3)` at 174 got $3. So the packet chain qty (r182/r183) took $3 *before* r181 in allocation order.

r182 (packet word) born at 347, r181 born at 343. r181 earlier. But priorities: r182 = 6666, r181 = 20000. So r181 should be allocated first and get $3 (since $2 busy), then r182 gets $4. That's the target! In mine, somehow r182 got $3.

So in mine, the packet-word qty must have priority ≥ 20000 or a copy suggestion. Wait, in mine the body is different (w2 is s16), so the RTL differs slightly from the reference. Hmm, but the .sched dump I just read IS mine (v0.c). Let me check: r182 def 347, use 350, REG_DEAD at 350 → refs 2, live 3 → pri 6666. r181: def 343, death 344, refs 2, live 1 → 20000. So r181 wins. Yet the disassembly of v0.c (mine) shows `lw v1,0(a3)` at 174 (packet word in v1=$3) and `lw a0,20(sp)` (otz in a0=$4). So the actual allocation contradicts my priority computation!

Unless... the copy tie: r84 (oidx) is tied to r181. The suggested phase allocates r84 to r181's suggested reg? And r182 maybe has a copy suggestion to $3?

Hmm, or the live range computation is different: qty_death is the insn index of the last use, but the RTL order in the dump is the sched1 order, and insn numbers (343, 347) are not linear positions. local-alloc uses `insn` order via `INSN_UID`? Actually qty_birth/qty_death are computed by scanning the insns in order with an index that increments per insn. So birth/death are linear positions, not UIDs. The linear order from the dump: 334, 401, 338, 340, 343, 402, 344, 353, 349, 354, 358, 347, 362, 350, 365, 366, 368, 372, 360, 373, 375, ...

So the linear positions: 343 (r181 def) at position p, 347 (r182 def) at p+10 or so. r181's death at 344 = position p+5. So live 5. r182's death at 350 = position p+12 → live 2? Wait 347 is at position 11, 350 at 13 → live 2. Even higher priority (2/2=1 → 10000). Hmm, I mis-assigned.

Let me recompute with linear positions from the actual order:
Order (by the dump's "prev next" chain): 
334, 401, 338, 340, 343, 402, 344, 353, 349, 354, 358, 347, 362, 350, 365, 366, 368, 372, 360, 373, 375, ...

Positions:
1:334
2:401
3:338
4:340
5:343 (r181 def)
6:402
7:344 (r84 def, uses r181)
8:353
9:349 (r184 def)
10:354
11:358 (uses r84)
12:347 (r182 def)
13:362
14:350 (r182 & r184)
15:365
16:366
17:368
18:372
19:360
20:373
21:375 (uses r84, DEAD)

r181: def pos5, use pos7 → live 2, refs 2 → pri 1 → 10000.
r84 (oidx): def pos7, uses pos11 and pos21 → live 14, refs 3 → 3/14=0.214 → 2142.
r182: def pos12, use pos14 → live 2, refs 2 → 10000.
r184: def pos9, use pos14 → live 5, refs 2 → 0.4 → 4000.
r183: def pos14, use pos16 → live 2, refs 2 → 10000.
r194: def pos16, use pos17 → live 1, refs 2 → 20000.
r191: def pos13, use pos15 → live 2 → 10000.
r192: def pos15, use pos16 → live 1 → 20000.
r193: defs pos2,6, use pos15 → live 13, refs 3 → 3/13=0.23 → 2307.
r189: def pos11, use pos13 → live 2 → 10000.
r187: def pos10, use pos11 → live 1 → 20000.
r186: def pos8, use pos10 → live 2 → 10000.
r196: def pos18, use pos20 → live 2 → 10000.
r197: def pos20, use pos21 → live 1 → 20000.
r198: def pos21, use pos? (next insn 379 beyond) → live 1 → 20000.
r180: def pos3, use pos4 → live 1 → 20000.
r178: def pos1, use pos3 → live 2 → 10000.

Allocation order by priority desc, tie by qty number (birth order):
20000: r194 (pos16), r192 (pos15), r187 (pos10), r197 (pos20), r198 (pos21), r180 (pos3), ... 
Wait r180 pos3 birth earliest → lowest qty number → allocated first among 20000 → gets $2.
Then r187 (pos10) → $3? But r187 = tag<<14 (ashift r186 14), def pos10, use pos11. Live 1. It gets $3? Hmm but target has r187... at 183 `sll v0,v0,0xe` = v0. So r187 is v0 in target, not $3.

Hmm, my model is off. Maybe the priority ties are broken by qty number but the *copy suggestions* phase runs first and assigns many.

Actually wait: qty_sugg phase: for qtys with copy suggestions, find_free_reg(..., 1) tries the suggested reg. Then the general phase. The copy suggestion for r84 (oidx) from r181's death tie. But r181 itself has no suggestion.

I think hand-simulating local-alloc is error-prone. Let me instead directly get the allocation order and priorities from the .lreg dump? local-alloc doesn't print priorities. But there's a simpler empirical route.

The difference between mine and the reference might come from *the w2 s16 change* altering the block's qty set: making w2 s16 added HImode copies (r178?) and changed the schedule slightly. Yet the disassembly diff is only the two registers. The reference (target) has r181→$3; mine has r182→$3.

We need r181 (otz load) to get $3, which requires the packet-word chain not to take $3 first. In target, the packet word got $4.

If the copy suggestion ties r84(oidx) to r181, and r84's qty is allocated in the suggested phase with the suggested reg = r181's? No — the suggestion is computed by find_free_reg scanning candidates.

Let me look at local-alloc's combine_regs: when `set (reg A) (reg B)` or a dying input, it records a "copy" relation. For `ashift`, the input r181 dies; combine_regs might tie r84 to r181 if the operation is a "copy" (only if insn is a move). Shift isn't a copy, so no tie. Hmm, but then why do r181 and r84 share v1 in target? Coincidence of allocation.

OK, empirical approach: I need to nudge local-alloc so that r181 gets $3 (or the packet chain gets $4). The simplest: change the *number* of refs of the packet-word pseudo (r182) or its live range, or introduce a copy tie.

What if we make the packet-word expression use a variable that extends its live range, lowering its priority below 10000? E.g.:
```
u32 pw = *(u32 *)pkt;
...
*(u32 *)pkt = (pw & 0xFF000000) | (...);
```
That's what r182 is already (a separate load pseudo, since the expression loads it). Its live is 2 positions. To lengthen, force the load earlier in the schedule — e.g., compute `pw` before the sh stores in source. Then r182's birth earlier → live longer → lower priority → r181 gets $3. But then the *disassembly* would have the lw earlier than target (target has it at 174). Unless sched1 reorders it back to 174 (it was hoisted to 174 by sched1 from source position later). Hmm: in source, the packet load is after the sh stores (position ~where the expression is), and sched1 hoisted it to 174 (which is interleaved with the sh stores). If we move it earlier in source, sched1 may keep it early → mismatch.

Alternative: make r182 have more refs by using the loaded word twice in a way that survives to RTL. The current RTL r182 is used once because combine folded `(pw & 0xff000000) | (x & 0xffffff)` — wait r182 is used at 350 `and r182, r184`. r183 = result. Then r194 = r183|r192. So pw used once. Fine.

To add a ref to r182 without changing code, we'd need the C to reference the loaded value twice. But the target also has it once (a0 used at 190 and 193 — that's r183 coalesced into a0).

Hmm wait: target a0 at 190 is `and a0,a0,a2` — a0 is r183 (dest) and r182 (src) coalesced. At 193 `or a0,a0,v0` — a0 is r194 (dest) and r183 (src) coalesced. So a0 = r182/r183/r194 coalesced by local-alloc's copy propagation. The qty that "owns" a0 could be r182 or r183 or r194.

Which qty gets $3 in mine? v1 at 174 `lw v1,0(a3)` = r182. Then 190 `and v1,v1,a2` = r183, 192 `or v1,v1,v0` = r194. So r182/r183/r194 all coalesced to v1.

In target they're a0. So the coalesced group got $4. The group's allocation is driven by the first qty allocated among them (r182 or r183 or r194, whichever has highest priority / earliest).

r194: pri 20000 (live 1, refs 2), born pos16. r183: 10000, born pos14. r182: 10000, born pos12.
r194 has the highest priority → allocated first among the three → takes first free reg. At its live range (pos16), which regs are free? It conflicts with r192 (pos15-16) and r184? Let's see: r194 = ior r183, r192; r192 = and r191, r193. r192 dies at r194's def. So r194 conflicts with r183 (used at 366) and r192.

If r194 is allocated first (pri 20000) and gets $2 (v0), then... but in both mine and target r194 is in a0/v1, not v0. So $2 was taken by something else overlapping r194's live range (pos16). At pos16, live qtys: r84 (oidx, pos7-21), r193 (mask, pos2-15? dies at 365 pos15), r184? r184 def pos9 use pos14, dead. r183 def pos14 use pos16. r194 def pos16 use pos17. r182 dead at 14. r198? later. So at pos16, live: r84, r183, r194, maybe r198? and globals r76/r77.

$2 at pos16: is it free? In the final code v0 is used as a temp (the loaded D_800A6614 value r191 at pos13-15 → `lw v0,0(at)` at 188). r191: def pos13, use pos15, pri 10000. It gets $2. So $2 occupied by r191 during pos13-15; at pos16, r191 is dead. r194 (pos16-17) could take $2 (reuse). But the target has r194 in a0; so maybe local-alloc allocated r194 before r191 and they conflict? r191 live pos13-15, r194 pos16-17 — no conflict, so both could be $2. But target has r191=v0 and r194=a0. So r194 didn't get $2.

Why? Because local-alloc's allocation for a qty uses find_free_reg over the *entire* live range [birth, death] and checks conflicts against already-allocated qtys. r194 (pos16-17) might conflict with an already-allocated qty in $2 whose live range overlaps: e.g., r198? no. r197 (pos20-21). Hmm. Or a global qty in $2 across the block (e.g., r116 v0 global, 1 ref). The alloc_table showed r116 v0 with refs 1. If a global pseudo occupies $2 for the whole block, then local qtys can't use $2 at all! But the disassembly uses v0 for temps... Those temps must be local qtys that *are* $2, so $2 is not reserved.

I'm going too deep. Time is ticking (~25 min on item 1). Let me switch to empirical batch testing of structural variants. The remaining residual is exactly 2 registers. Let me try ~15 quick variants with sc.sh.

Variants to try (lever-free, no pins):
1. w2 s16 (v0) baseline = 13.
2. w2 s16 + `u32 pw = *(u32*)pkt;` explicit temp.
3. w2 s16 + split the packet store into `pw` load then store.
4. w2 s16 + `oidx = g.otz * 4;`
5. w2 s16 + `oidx` as u32.
6. w2 s16 + compute the two address expressions with a shared `tag` variable.
7. w2 s16 + reorder: move `oidx = g.otz << 2;` to just before the first use (already).
8. w2 s16 + make the second address use `otp = (u32*)&D_800A6614[oidx + (tag << 14)];` with tag from a temp declared u16.
9. w2 s16 + swap: compute `*(u32*)pkt` store using `pkt` directly but the load through a `u32 *pp = (u32*)pkt;`.
10. w2 as u16 instead of s16.

But the notes say widths, explicit tag temp, oidx inlined/moved/cast, tail orders all stay 13-16. So these are likely already tried. I need something genuinely new.

New idea: change the *declaration order* of w2/oidx/mulc (C0505 catalog: decl order). Local-alloc qty numbers are assigned at birth, not declaration. But the schedule could shift.

New idea: the block's qty set includes w2-related HImode pseudos. Maybe the real target had w2 as s32 but the div block ordering was fixed by something else. The notes: "w2 as s16 (v0.c) recovers the count: 197 ins, score 13". So with s16 the div is in the right place. Good.

New idea: make the packet chain's qty *not* win $3 by lengthening r182's life: declare `u32 pw` and assign it BEFORE the `w = mulc` line, i.e., load the packet word earlier in the source:
```
pkt = D_800A5E60;
D_800A5E60 = pkt + 0x28;
...
u32 pw = *(u32*)pkt;   // earlier
...
*(u32*)pkt = (pw & ...) | ...;
```
Hmm but the load must be after `pkt = D_800A5E60` (it is). If we place `pw = *(u32*)pkt;` right after pkt is set, sched1 might keep it early (it's a load, could be hoisted/sunk). Target has it at 174 (late). Risky but let me test.

Actually, wait. A cleaner idea: extend the live range of the *packet word* by using it in the final otp store: `*otp = (*otp & 0xFF000000) | (pw & 0xFFFFFF);`? But target uses pkt's address, not pw. However, `pw` and `*(u32*)pkt`... no, pkt is the pointer. `(u32)pkt & 0xFFFFFF` — target `and a1,a3,a1` uses a3=pkt. If we used pw there it'd be a different value → wrong semantics.

Hmm, what about using `pw` in the second expression's index? no.

New idea: lower r194's priority (the coalesced group leader) by lengthening its life. If the group's representative is r194 (pri 20000), extending its life below 10000 would let r181 win. How? Make the OR result live longer: assign it to a variable used later, e.g.:
```
u32 w2v = (pw & 0xFF000000) | (...);
*(u32*)pkt = w2v;
```
Then w2v is r194 and its death is the store; same.

Unless we move the store later in source (after the otp store)? That changes store order.

New idea: lower the group's priority by making the loaded word used in a 3-ref way with a longer life... 

Alternatively RAISE r181's priority isn't possible (already max 20000) — but make r181's *live range* not conflict? It's about allocation order: r181 pri 10000 vs the group r194 20000. The group is allocated first and takes $3 (since $2 busy). Then r181 gets $4. To make r181 get $3, the group must not take $3.

What if we make the group's leader r182/r183 (pri 10000, born later) instead of r194? If r194 didn't coalesce (e.g., store directly from the OR expression without a variable — it already does), r194 is the store operand.

Hmm, what if we restructure the packet store to avoid the separate `and` qty: `*(u32*)pkt = (*(u32*)pkt & 0xFF000000) | (X & 0xFFFFFF);` is the target. Already.

What if the coalescing differs: make the store value NOT coalesce with r182, e.g., use a separate variable for the and-mask part:
```
u32 hi = *(u32*)pkt & 0xFF000000;
u32 lo = ... & 0xFFFFFF;
*(u32*)pkt = hi | lo;
```
Then r182 (load) has life until the `and` in a separate insn, possibly different.

Let me just test a batch. Time-box: 10 variants, ~2 min.

Actually — wait. Let me reconsider the simplest possible: maybe the *target* uses `oidx` pinned because the original source had `register s32 oidx asm("$3")`. If so, this is a WALL. The notes' author tried widths etc. and hit lreg-qty-priority. But my analysis shows the competition is between r181 (otz load, tied to oidx) and the packet-word chain. The lever-free score 13 with only a 2-reg swap means we're close.

Let me look at the .lreg dump to see the actual local allocation and which qty got what. The .lreg dump is after local-alloc; registers are hard. The sched dump I have is *after sched1, before local-alloc* (pseudos). Great. So I can identify qtys and simulate.

Actually, better: gcc 2.7.2's local-alloc has a debug dump? `-dl` = dump after local-alloc. No priorities.

Let me simulate local-alloc more carefully. I'll write a tiny script? No, too much.

Let me instead use the .lreg dump to see the allocation *order*? No.

OK empirical. Let me create variants efficiently with a small script that applies textual edits to v0.c. I'll write a Python script under the item dir? Simpler: use sed per variant, then sc.sh all.

Let me write a python generator script in .run/P40/T11/RM3/<item>/gen.py that reads v0.c and writes variants. Then run sc.sh with all files.

Variants (all from v0.c):
A. explicit pw temp:
```
    pkt[0xC] = ...;
    w = mulc;
```
Replace the block:
```
    oidx = g.otz << 2;                                          /* L2 */
    *(u32 *)pkt = (*(u32 *)pkt & 0xFF000000)
                | (*(u32 *)&D_800A6614[oidx + (*(u16 *)(base + 0xA3D2) << 14)] & 0xFFFFFF);
    otp = (u32 *)&D_800A6614[oidx + (*(u16 *)(base + 0xA3D2) << 14)];
    *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
```
with:
```
    oidx = g.otz << 2;
    {
        u32 pw = *(u32 *)pkt;
        *(u32 *)pkt = (pw & 0xFF000000)
                    | (*(u32 *)&D_800A6614[oidx + (*(u16 *)(base + 0xA3D2) << 14)] & 0xFFFFFF);
    }
    otp = ...
```
B. hi/lo split.
C. tag temp:
```
    u16 tg = *(u16 *)(base + 0xA3D2);
```
D. oidx * 4.
E. oidx u32.
F. load packet word early (right after D_800A5E60 update).
G. packet word loaded via `u32 *pp = (u32*)pkt; u32 pw = *pp;`
H. Move `oidx = ...` to just before the last store (recompute? no).

Let me generate A-H and score. Actually since notes tried many, focus on the ones targeting the qty: A (pw temp), B (hi/lo split), F (early load), G.

Also idea: make the packet word's death later by using the *same* loaded value for the `pkt[0xD]` byte? no.

Another idea: use `s16` for oidx? tried.

Let me write the generator.

Actually, let me reconsider F more: target has the packet load at 174, after the sh stores. In v0.c source, the expression is after the sh stores too (line: `oidx = g.otz << 2;` after the sh block). sched1 hoisted it to 174 (before the last few sh's). If I put the load earlier in source, sched1 might still schedule it at 174 (it's a load; sched1 may sink it). Could work.

Also a variant: move the ENTIRE packet store statement earlier/later.

Let me do it.

---
ts: 2026-11-06T21:13:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bqWZyDuLh9eqxUlODdsF
---
Excellent! Line 4: "12 regs to allocate: 78 108 117 74 127 150 76 95 141 73 128 79" — this is allocno_order. The allocation order (highest priority first) is: 78, 108, 117, 74, 127, 150, 76, 95, 141, 73, 128, 79.

So allocno 95 (off) comes before allocno 79 (e). 95 is 8th, 79 is last! So off has much higher priority than e in this function's global allocation. That's why off gets a0.

Wait, but these are allocno numbers = pseudo reg numbers? "regs to allocate: 78 108 117 74 127 150 76 95 141 73 128 79" — these look like pseudo reg numbers. 95=off, 79=e. So order: ..., 95 (8th), ..., 79 (last).

Hmm, e is LAST despite short live range. Why? Because allocno_live_length for e must be huge, or n_refs small.

Wait — 79's conflicts: {76,79,95,2,3,29}. 95's conflicts: {76,79,95,2,3,29}. Similar.

The priority ordering: e is last. Maybe e's live length is very long (e.g., REG_EQUIV makes it live across the whole function?) or n_refs=2 with a long live length.

Actually — maybe e is live from its definition all the way to the function end because of REG_EQUIV handling? Or because reg 79 is used in the `if (idx >= 0)` branch? Let me check: no.

Hmm, "regs to allocate" order is allocno_order, sorted by priority (highest first). e=79 last means lowest priority. Its live length must be large.

Let me compute: pri = floor_log2(n_refs)*n_refs/live_length*size. For e to be last, live_length huge. If n_refs=2, floor_log2=1, pri=2/live. To be below 76 (idx): idx n_refs maybe 3-4, live ~? 

Actually maybe the issue: e's live range in global-alloc is the whole function because REG_EQUIV/flow sees the symbol as live from entry? No.

Wait, let me reconsider: maybe reg 79's live range extends because the `e` pseudo is used in a block that's reachable from multiple paths, and flow's live analysis... no, e is defined at 73 in one block.

Let me just look at the allocno_live_length values. The .greg dump's first lines might include them? "regs to allocate" only shows reg numbers. Hmm.

Actually, let me reconsider the whole thing: the launder changes e's n_refs from 2 to 4, which multiplies priority by (floor_log2(4)*4)/(floor_log2(2)*2) = (2*4)/(1*2) = 4x. So e jumps up in the order, above off. That's the fix. So I need n_refs ≥ 4, or 3 might suffice.

Let me check: with n_refs=3, floor_log2(3)=1, pri = 3/live. vs n_refs=2 → 2/live. 1.5x. off=95 is 8th, e=79 is last (12th). The gap might be large; 1.5x might not be enough. With n_refs=4 → 4x, definitely enough (that's the launder).

So I need to give e 4 refs (or enough). A real 2nd set+use gives +2 refs (def+use) → 4 total.

How to make a real 2nd set+use of e that produces no extra instructions? 

The launder's asm is exactly def+use in one insn, no code generated. Is there a C construct that compiles to a no-op but counts as a def+use? A copy `e = e;`? Flow/cse removes self-copies. A conditional `e = cond ? e : e;` folds.

What about a `volatile` read? `*(volatile s16*)e` would generate a load — extra code.

What about taking the address of e? `&e` — no.

What about using a function-like macro that's a no-op? Same.

Hmm. What about the "dead reset" C0414: `e = 0;` — this is a def (1 ref) with no use. n_refs +1 → 3. And if placed where e is used before and after... but e used once.

Wait — actually a dead reset AFTER the last use: flow would delete it. But what if placed BEFORE the last use and after the def? Then the def's value is overwritten; the reset becomes the live def. `e = (s16*)D_801E8F78; e = 0; ... use e` → the first def is dead, removed; e=0 live → wrong value.

What if the reset is to a value that happens to equal the symbol? Can't write a symbol as 0.

OK, here's a thought: increase e's refs by making the condition use e via TWO syntactically distinct but same-address expressions that cse does NOT merge. CSE merges loads with identical addresses. But what if one is a load and the other is... Let me think: `*(s16*)((u8*)e + off + 2)` and `((s16*)((u8*)e + off))[1]`. Same RTL. Merged.

What if we use `e[off >> 1]`? off is a multiple of 4; off>>1 = idx*2. So `e[idx*2 + 1]` (for the +2 offset). Then the address is e + (idx*2+1)*2 = e + idx*4 + 2 = e+off+2. But the address computation differs: e + (idx*2+1)*2 vs e + off + 2. If cse computes idx*2 and uses a shift... might add instructions. Let me test: use `e[idx * 2 + 1]` for BOTH occurrences. Actually if both use the same expression, cse merges them into one. Then e has 1 use still. But the address computation would differ (idx*2*2 vs off). Hmm.

Let me try using `e[idx*2+1]` for the two occurrences and see if it changes anything. If cse computes it as e + (idx*2+1)*2, it might produce `sll` of idx*2 then... Actually the compiler may reassociate to idx*4+2. Let me test.

Alternatively: keep `off` for the address but make e's use count 2 by using e in the *address of the lim load* through a comparison that's free. 

New idea: what if the lim load uses `e` AND the condition uses `e`, and we accept 146 insns? No, must be 147.

Hmm, let me reconsider the target's instruction count 147 and the exact sequence. Is there an alternative C body that produces the same 147 instructions with a different allocation? The crack doesn't have to mirror orig.

Let me try restructuring the condition to use `off` twice with e once, but add e's ref via the `lim` load using a *cast that cse treats as different*:

`lim = *(s16 *)((u8 *)e + off);` — this is e+off, same as the condition's base. cse would share e+off → 146. But what if we compute it as `*(s16 *)((u8 *)e + idx * 4)`? Still e+off.

What if we use the symbol for lim but reference e in the same statement in a dead way? e.g. `lim = D_801E8F78[idx][0] + (e == 0 ? 0 : 0);` — folded.

I think the cleanest is to make e's live length SHORTER or n_refs higher via a real 2nd set. Let me look at the actual allocno_live_length. Maybe e is last because live_length is huge due to REG_EQUIV. If I can break REG_EQUIV, e's live length might shrink, raising priority. Let me try to break REG_EQUIV by making the assignment non-equivalent.

REG_EQUIV is set on insn 73 `(set (reg 79) (symbol_ref D_801E8F78))`. Where did it come from? In local-alloc, REG_EQUIV is added if SET_SRC is MEM. Here it's symbol_ref, so it came from earlier (cse/combine) or from the source? Actually REG_EQUIV notes are usually added by cse for constants. Hmm, `(expr_list:REG_EQUIV (symbol_ref...)`. 

If e were assigned from a computed expression, REG_EQUIV might not be set, and e's live range/priority could differ. Let me try `e = (s16 *)((u8 *)D_801E8F78);` (cast to u8* then to s16*) — we tried v4, score 4. Did it remove REG_EQUIV? Probably not.

Let me try `e = (s16 *)D_801E8F78 + 0;`? The +0 might keep an add? combine folds.

Hmm, let me test a bunch of "break REG_EQUIV" variants and check if the allocation order changes by looking at the score. Quick.

Actually, a cleaner idea: make e's live range shorter by defining it as late as possible. Currently e is defined at insn 73, after the lim load (70). Could we define it at the condition, i.e., after the slt and branch? No, target has it before slt.

But what if the lim load is placed AFTER e? i.e., source order: e, then lim, then slt. Currently: off, lim, e. What if: off, e, lim? Then e is born earlier (before lim), live range longer → worse. We tried v2 (e first, lim, off) → 4.

What if we make the lim load's live range shorter or its priority lower so e outranks it? off is the competitor, not lim.

Let me get the actual allocno_live_length. I could add -dL? The dump list included -dL (life analysis). Let me check cand.i.life? The dump names: cand.i.rtl (from -dr), .life? Actually -dL = "dump after life analysis" (.life). The ls showed: cand.i.combine, cse, cse2, dbr, flow, greg, jump, jump2, loop, lreg, rtl, sched, sched2. No .life. Hmm, -dL might be .life but not present; maybe it's .lreg? Let me check tools/cc1_dumps_tu.sh flags: -dr -ds -dj -dl -dg -df -dc -dS -dL -dR -dt -dJ -dd. -dL = life. But the output list didn't show a .life file. Maybe -dL produces .life but it wasn't listed (ls was truncated). Let me list all.

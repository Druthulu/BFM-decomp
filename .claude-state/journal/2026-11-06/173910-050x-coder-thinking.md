---
ts: 2026-11-07T00:39:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sTjcuH7TQdOMjnZHhr0W
---
Mine: the val load (lui v0; lw v0) is at 8424-8428, after the four zero stores. Target: at 8408-8410, before them.

Note mine's load has a `li v1,1` after it at 842c and the rest. So the whole group (load, li, store D_801B7988, addiu, store) is sunk below the four zero stores.

So sched1 in mine moved the load group down. Priority: the val load feeds addiu → sw. Hmm, in mine, the load's chain: load → addiu → sw (priority of sw=1, addiu=1+cost-1, load=...). Yet it's scheduled last. That suggests sched1's ready-list order (LUID) dominated: all these insns have priority 1 and it keeps source order? But the source order has the load BEFORE the stores, so it should come first.

Unless the RTL order at sched1 time already had the load after the stores — because sched1 isn't the one moving it. Maybe *cse* or *jump* reordered? No.

Wait — actually maybe it's `sched1`'s `adjust_priority` or the SCHED_GROUP. Hmm.

Alternatively, maybe the load was moved by... hmm. Note in the target, the order is: load, li v1,1, then the four zero stores, then lui at; sw v1; addiu; lui at; sw. In mine: four zero stores, then load, li v1, then lui at; sw v1; addiu; lui at; sw.

So in both, the tail group (li + sw v1 + addiu + sw v0) stays together after the stores... in the target the load+li are hoisted above the stores; in mine they're all together after.

Since the difference is just where the load+li sit relative to the zero stores, and the zero stores are independent, this is a scheduling order decision.

What decides it? In sched1, insns are scheduled by priority; the load (priority 2) should go first... unless the load's dependent chain is short and it gets priority 1.

Hmm: insn_cost(x, link, insn) — for a load feeding an addiu: cost of the load is its latency (2 for a load?). The addiu's priority = 1 + cost(addiu)=1 - 1 = 1. The load's priority = priority(addiu) + insn_cost(load) - 1 = 1 + 2 - 1 = 2. So the load should be priority 2 > 1.

But wait: is the load's dependent the addiu? `val` feeds only `val + 1`. Yes.

Then why does mine schedule it after the stores? Unless the load is NOT ready early: the load's address is `lui v0,0x0; lw v0,0(v0)` — the lui has priority 2 too (it feeds the load). The lui should be first.

Hmm, unless in mine, the loads are *not* in the same basic block as the stores: the jal at 8400 splits blocks? No, the block starts after the jal.

Hmm, actually: sched1 schedules each basic block. The block starts at 8404 (the jal delay slot / after the call). All these insns are in the same block.

Let me reconsider: maybe it's not sched1 but **sched2** (after reload). sched2 also schedules. The prior note says sched1-birth-boost, but the tag may be about the pinned version.

Alternatively the reordering comes from *local-alloc/global-alloc*: no, they don't reorder insns.

Hmm, what about the *delay slot* of the jal at 8400: `move a0,s0` at 8404 — the call's arg. The jal's delay slot must be filled; reorg does that later.

Let me check: could this reordering be from `reorg` (dbr) filling delay slots? The block after a jal... The jal at 8400 has a delay slot at 8404 (move a0,s0). No branch here.

Let me look at the actual difference more carefully. Maybe the difference is that in the target, the load+li were hoisted *into the region before the stores* by sched1 because of the "birth boost" the pin gives... 

Honestly, let me try the practical moves:
1. Move `val = D_801B7A84;` earlier in the source — e.g., right after `func_8013C0F8` (before `p = &D_801B7930;`) or even before the calls. Since sched1 kept source order in mine (mostly), moving it earlier might work. But the target's load is after the second jal, so putting it before the calls would be wrong... unless sched1 keeps it there → worse.

2. Make the zero stores depend on val: not possible without changing values.

3. Use a different structure: `p = &D_801B7930;` etc.

4. The classic: the load's priority depends on its *use chain*. If val is used in a way that creates a longer chain (e.g., val used in two places), priority rises.

Hmm, what about the *order* of the stores? In the target, `*p = 0;` (sw zero,0(s0)) comes after the three D_801B79xx stores. Mine matches.

Let me try a batch of source-order variants:
- a: val load right after the first call (before p = &D_801B7930)
- b: val load declared+initialized at decl: `s32 val = D_801B7A84;` at the top of the case block (init at decl!) — this is a catalog move (init at decl).
- c: split `p = &D_801B7930;` and the call.
- d: val used via `D_801B7A84 = val + 1;` (same)
- e: `s32 val;` declared outside the case block (function scope)
- f: do-while(0) around the stores (C0535 EBB split)
- g: reorder the stores
- h: make `*p = 0;` come before the three stores (changes order in the target? target has it after) — no.
- i: `D_801B7988 = 1;` before `*p = 0;` — the target has sw zero,0(s0) then lui at; sw v1.

Hmm wait, actually: maybe the target's order comes from the *source order* being: load val, li 1 (D_801B7988=1?), ... hmm: target 8408 lui v0; 840c lw v0 (val); 8410 li v1,1; 8414-8428 three sw zero; 842c sw zero,0(s0); 8430-8434 sw v1,0(at) (D_801B7988=1); 8438 addiu v0,1; 843c sw v0.

So the `li v1,1` (for D_801B7988=1) is born early (8410) but its store is late (8434). That's sched1 hoisting the li.

In mine, the load and li are born late.

So both sched1-hoist the `li` (a constant) — in the target it's hoisted to 8410 together with the load; in mine the load+li sank.

Key difference: in the target, val is in v0 (hard reg), in mine val is in v0 too! Both use v0. Interesting.

So the only difference is scheduling order. What could make the load higher priority? If the value's *life* is longer or it has more references.

In the target (pinned), val is a hard reg $2 → hmm.

Let me think about sched1's priority again but for the *store* `sw v1,0(at)`: its chain is li→sw. Priority 1 each. The load's chain: load→addiu→sw: load priority = 2? Unless insn_cost for a load is 1.

Actually in gcc 2.7.2 mips.md, the load latency might be 1 by default for -mips1 (no -mschedule). If all costs are 1, everything has priority 1, and sched1 preserves source order (ready list = LUID order). Then the order is source order!

So in mine, the *RTL source order* at sched1 time has the load after the stores. Why? Because the compiler emitted the RTL in source order... unless something moved it. In my source, `val = D_801B7A84;` is BEFORE the stores. Hmm!

Unless the front end/expand emitted the stores first because of... no.

OR the reordering is in `local-alloc`/`global-alloc`? They don't reorder. `combine`? It can move things. `cse`? No.

Hmm, wait: maybe the load is *duplicated*: `val = D_801B7A84;` and later `D_801B7A84 = val + 1;`. In the target, `val` is loaded once (840c) and used at 8438.

In mine, the load is at 8428. Maybe the load was *sunk* by cse/combine because its only use is at 8438 (the addiu) — no, cse doesn't sink.

Hmm, but there's `sched1`'s "birth" concept: SCHED_GROUP and `adjust_priority`. Hmm.

Let me test empirically: variant b (`s32 val = D_801B7A84;` init at decl at the top of the case block) — the load then is born earlier in the RTL (before the calls), and sched1 may keep it... but it would be before the calls, which the target doesn't have. Unless the load is after the calls because of dependencies... no, the load is independent, it'd stay at the top.

Hmm. Let me instead consider that the *pin* changed the RTL: with `register s32 val __asm__("$2")`, the assignment `val = D_801B7A84` becomes a set of a hard register. Since v0 is call-clobbered, the value can't live across the calls; the load is placed after the calls (as in the source).

Without the pin, val is a pseudo. Same placement.

So why the different schedule? Let me check whether it's sched1 at all by looking at the -ds dump. That's the reliable route. Let me dump for w1 (the spliced TU from --keep is at .run/P36/engine/score/...). I can run tools/cc1_dumps_tu.sh with DUMP_ROOT under my item dir. But it dumps a lot; disk. The TU is 365KB → the dumps could be ~100 MB. Hmm, "your shard dir stays < 200 MB". Risky but one dump then delete.

Alternative: maybe I don't need the dump. Let me try a few quick source-order variants and see if any moves the load up. Empiricism is cheap here (score in ~2 s).

Batch for item 2:
- v1: current (6)
- v2: val load placed right after the first call
- v3: val load placed after `p = &D_801B7930;` but before the second call
- v4: init at decl: `s32 val = D_801B7A84;`
- v5: `s32 val = D_801B7A84;` declared at function top (outside the switch)
- v6: do-while(0) around the three D_801B7948/4C/50 stores
- v7: do-while(0) around all the stores
- v8: `*p = 0;` moved before the three stores
- v9: the three stores via a helper pointer variable
- v10: `val = D_801B7A84;` twice (dead reset after the stores: `val = 0;`) — hmm
- v11: `p = &D_801B7930;` before the first call
- v12: use `D_801B7A84` read into val at the *end*: `D_801B7A84 = D_801B7A84 + 1;` (no val) — that's a different shape (would reload the global at the end — the target has the value from the earlier load).
- v13: reorder `D_801B7988 = 1;` before `*p = 0;`
- v14: `*p = D_801B7988 = 0`? no.

Also: maybe the answer is a dependency: make `*p = 0;` use val? No, that's laundering.

Hmm, one more idea: the target's `li v1,1` at 8410 — the constant 1 is born early. In mine, `li v1,1` is at 842c. The li's priority: it feeds sw v1,0(at) (priority 1). So li priority 1. Both have it.

Actually, here's a thought: the whole group in mine (load, li, sw, addiu, lui, sw) is a contiguous block after the zero stores. In the target, the load+li are hoisted above the zero stores while the rest stays. That means in the target the load had a HIGHER priority (it was picked earlier). Priority of the load = priority of its consumer chain. The consumer addiu → sw. Hmm.

Unless in the target the load's chain is longer because `val` is a hard reg and has a REG_DEAD note / SCHED_GROUP?

OK — actually, let me revisit: maybe the difference is not sched1 but **cse**'s handling: with the pin, `val` is $2, and `D_801B7A84 = val + 1` — hmm.

Let me just run the dumps for w1 and compare with the src body's dumps. I'll dump with DUMP_ROOT in the item dir and grep the .sched1 dump. To limit size, I can run cc1 with only -ds? The script hardcodes the flags. I could call cc1 myself... but the rules say use the provided tools. The script's DUMP_ROOT param exists for this.

Actually, wait. There's a cheaper diagnostic: score a candidate with the barrier *kept* but the pin dropped, and vice versa. That tells me which lever is load-bearing for which part:
- w2 = pin kept, barrier dropped
- w3 = barrier kept, pin dropped

If w3 (barrier only) scores 0, then the barrier alone is the load-bearing lever and the pin is redundant (PARTIAL possible? No—MATCH requires both gone; but if the pin is redundant, dropping it alone gives 0 → then I need to crack the barrier).

Let me test w2 and w3 first: cheap and highly informative.

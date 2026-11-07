---
ts: 2026-11-06T11:35:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3E1fqOKlkcleoTu2HX7U
---
So a call does NOT invalidate memory in cse1. So loads across calls are kept. That's why the target needed the barrier.

So how to get two loads in real C? Hmm.

Wait — maybe I have it backwards. Maybe the two loads aren't due to the barrier; maybe the target's first load `lhu v1,174(s0)` is a *different expression* than the second `lhu a1,174(s0)`, and the barrier is what causes the second read to happen at all (the second read is the one after the barrier in the C). Without the barrier, cse merges them → mine has one load. With the barrier, cse's memory table is cleared → second load. Right.

So to match, we need cse to not forward. Options:
(a) volatile — lever.
(b) Make the first expression a struct member (in_struct) and... no, invalidation only happens on stores.
(c) Insert a real store between the two reads that flow deletes? A store to a local variable on the stack would generate code (unless optimized away). Hmm, a store to a global that flow deletes... but cse runs after flow? Order: cse1, cse2 after? Pass order in gcc 2.7.2: flow is after cse? Let me recall toplev: `if (optimize > 0) { if (flag_cse_follow_jumps...) ... }` Order roughly: jump_optimize, cse, ... flow, combine, sched. Actually the classic order: cse1, loop, cse2, flow, combine, sched1... So a dead store would be removed by flow AFTER cse → cse sees it, flow deletes it. But cse might also remove a dead store itself (cse does store elimination for redundant stores). Hmm.

(d) The C0414 move: "dead-reset cse-breaker" — assign a variable to 0 to break a cse class. But here we need to break the *memory* entry.

Wait, maybe I should reconsider: does the second load in the target really come from the same C expression? Perhaps the original C had a genuine different read: e.g. `bb` is read via a struct pointer and the call args via `*(u16*)p`. In gcc cse, the memory expression hash is on the address only (MEM → hash += MEM, then address). So `*(u16*)(p+0xAE)` via struct is the same address → same hash. But `rtx_equal_p`/`exp_equiv_p` compares MEM attributes? Let me check exp_equiv_p.

Actually, the important bit is whether the address rtx is identical. Struct member access vs cast: both become `(mem:HI (plus:SI (reg) (const_int 174)))`. Identical. So cse merges.

Unless the addresses differ in mode: `(mem:HI (plus (reg:SI) ...))` same.

Hmm, what if one is `*(u16 *)(p + 0xAE)` and the other `*(u16 *)((u8 *)p + 0xAE)`? Same after fold.

What about reading through a pointer variable that cse doesn't know is constant: `u16 *q = (u16*)(p+0xAE);` then `q[0]`. CSE substitutes q's value (it's a register copy of the address). Same.

What if q is loaded from memory? Overkill.

What if the first load is via `*(u16 *)(p + 0xAE)` and the second via a different but equivalent expression involving a subtraction: `*(u16 *)(p + 0xAE + 0x100 - 0x100)` → constant folds.

Hmm.

Alternative: maybe we don't need two loads. Maybe we can restructure so that a *single* load produces identical code. Mine has one load but an extra `andi a1,a0,0xffff` (from u32 bb). If we fix bb to u16, mine would be: lhu a0,174(s0); li v1,128; andi v0,a0,0xff; bne; srl v0,a0,0x8; beq; nop...; then andi a0,a0,0xff; addiu; srl a1; call... That's 1 load but the target has 2 loads (2 extra insns: lhu + li) and mine has 72 vs target 71 — wait mine is one MORE insn. Because of andi 0xffff and maybe an extra nop? Let me count: target 71 insns including the two loads; mine 72 with one load + andi 0xffff. So mine has +1 insn even with fewer loads? Hmm.

Actually the target's two loads: at 32d4 lhu v1,174 and 32f0 lhu a1,174. The second load's delay... no delay slots on these.

Let me get mine's full disassembly to compare. Use --keep to get the object.

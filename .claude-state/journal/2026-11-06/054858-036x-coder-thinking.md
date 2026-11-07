---
ts: 2026-11-06T12:48:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zAV8u0mEYzBLjOI5txjI
---
So `memrefs_conflict_p` compares the addresses. For `sp10[4]` store (address sp+32) vs `sp10[0]` load (address sp+16) — both fixed offsets from the same frame symbol. memrefs_conflict_p would compute the difference: 32-16 = 16 >= size... For a 4-byte store at offset 32 and a 2-byte load at 16: c = 16 (difference). xsize=4, c=16 >= 4 → conflict returns 0 (no conflict). Good, so no dependence → reorder allowed.

To create a dependence I'd need the addresses to overlap or be non-constant. Non-constant (varying) addresses: `sp10[i]` with variable i. But the target's addresses are constant (16(sp), 32(sp)).

Hmm, so a dependence cannot be created without changing the addresses.

Alternative: block the scheduler from putting the lhu in the delay slot by making the lhu's *destination* register conflict... no.

Alternative: make the lhu come from a load that has a REG_DEP_ANTI on... no.

Hmm, what about the order of the *RMW statements*? Target: lhu v0,16(sp); lhu v1,6(a2); nop; addu; sh v0,16(sp). The nop at 29 is the load-delay for the second lhu. In mine same.

What if instead we put the third RMW first? no, target order is fixed.

Let me think about the fifth load differently. What if `t`'s load and `sp10[4]`'s store are combined into a block move of 4 bytes? A 4-byte struct copy → `lw`/`sw` pair, no nop (the sw uses the loaded reg → nop required!). Wait: a 4-byte block move `sp10[4] = t` as `*(S4*)&sp10[4] = *(...)` would emit lw v1,0(at) then sw v1,32(sp) with a nop between (load delay) — same as now. And sched could still fill the nop with the lhu... unless the block move is one insn (movstrsi) at sched time, so no filling. For 4 bytes, move_by_pieces would emit a single lw/sw pair, and if it's a `movstrsi_internal` insn (one insn until final), the sched can't insert between.

Does gcc 2.7.2 MIPS emit movstrsi for a 4-byte struct copy? It would be a single word — probably just lw/sw. Hmm.

But wait: maybe I can make the *whole* sp10 assignment a struct copy from a struct that has 5 fields each pointing to the 5 symbols... no.

New idea: what if sp10 is filled by a *5-word block move from the 5 distinct symbols* because the source is a struct declared as a union of the five externs? no.

OK, radically different approach: what if I change the source so the fifth load's delay slot is filled by something ELSE in both target and mine? No, target is fixed.

Let me look at this from the "moves.md" angle: are there existing MATCHes for similar shapes? The list of barrier moves mentions things like "func_801876C4 MATCH: `do { t = D_801A9A88[a1*5]; sp10[4] = t; } while (0)` — the loop-shaped range keeps the u16 adds out of the t load delay slot (target nop)".

That's exactly this shape! func_801876C4: "do { t = D_801A9A88[a1*5]; sp10[4] = t; } while (0)" — the do-while keeps the u16 adds out of the t load delay slot. 

So C0535-style do-while works for sched too (at least in that case). Let's try wrapping `sp10[4] = t;` (or the load+store) in a do{}while(0).

Actually the move says `do { t = ...; sp10[4] = t; } while (0)` — both the load and the store inside. Let me try that.

Why would do{}while(0) stop sched? It creates a NOTE_INSN_LOOP_BEG/END? No, do-while(0) creates a real loop structure with a branch that gets optimized away... but at sched time (sched1 is before loop? no, after loop). Hmm. The trick in C0535 is "do{}while(0) splits cse1 EBB". For sched: maybe the loop notes/barriers... Whatever — empirically it worked for func_801876C4. Let me try.

Note the constraint: "`do{}while(0)` only with `// !FAKE: do-while`" — so I must annotate it.

Let me try several candidates:
w2: do { t = D_801AFBE8[a1*5]; sp10[4] = t; } while (0); — with t declared.
w3: do { sp10[4] = t; } while (0); with t loaded before.
w4: do { sp10[4] = D_801AFBE8[a1*5]; } while (0);

Let me create these and score them.

Note: in the do-while version, `t` must be declared (orig had t pinned to $3). If I use a plain `s32 t`, the register assignment might differ from target (target uses v1). Let's see.

Actually the orig pins: w→$7, t→$3. In target, the fifth load is into v1 and the store from v1; and a3 was used for the 4th word. The pins were "minimum-lever" to get the block move temps right. Without the pins, the temps are local-alloc scratch.

Hmm, w0 (barrier removed, pins kept) scored 3 — so pins are fine. Let's keep pins and just add the do-while.

Let me test w2/w3/w4.

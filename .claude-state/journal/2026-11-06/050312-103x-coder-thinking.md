---
ts: 2026-11-06T12:03:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_temXpTaqTsthKbODjWVM
---
So unk10 is a u16 at 0x10. The original uses `CAST_WIDTH(s32, (u8 *)a0, 0x10) = v;` — a 32-bit store to 0x10, overwriting unk10 (0x10) and unk12 (0x12). Interesting: the code stores a s32 to 0x10, which covers unk10 and unk12. 

Hmm, so `CAST_WIDTH(s32, (u8*)a0, 0x10) = v` is a 32-bit store. If I used `((Unkstruct_800B5CB8*)a0)->unk10 = v` (u16), that'd be a 16-bit store — wrong. So CAST_WIDTH(s32) is needed.

OK. The store sink is a genuine wall. Let me try a couple more sched levers and then finalize.

Actually, let me reconsider: maybe I can create the required WAR dependence by making the store use a0 (not s0). The store is `CAST_WIDTH(s32, (u8*)a0, 0x10) = v`. The compiler uses s0. But what if I force it to use a0 by making a0 live? a0 is clobbered by the calls. After the calls, a0 is dead. 

Hmm, what if I move the 0x10 store to BEFORE the calls? No, v depends on the post-call state.

Let me try: what if the final call `func_8002D4C8(0x980, 0)` used `a0` for the first arg, and the store also used `a0`? They'd conflict. But the store uses s0.

What if I don't use s0 at all — i.e., make the function use a0 directly for all accesses? Then a0 would be live until the final call (where it's overwritten). The store `*(a0+0x10)=v` uses a0, and the final `li a0,0x980` overwrites a0 → WAR dependence → store must come before li a0! That's exactly the target order!

But how to make the function use a0 directly instead of s0? The compiler moves a0 to s0 because a0 must survive the calls (func_8012B2CC, func_8012B200 clobber a0). So after the calls, a0 is reloaded... actually a0 is not preserved across calls, so the compiler MUST keep the pointer in a callee-saved reg (s0). So the post-call accesses use s0. The target uses s0 too (`sw v0,16(s0)`).

So the target's store uses s0, and the li a0 is independent. Yet the target has the store before the li (because the barrier prevents reordering).

So the WAR dependence idea doesn't apply.

Hmm. OK, this is a genuine sched-store-sink wall, exactly like the sibling func_801810E4. 

Let me do a couple more attempts to be thorough:
1. Try `CAST_WIDTH(s32, (u8 *)a0, 0x10) = v;` with the store moved before the if? No.
2. Try reordering the v computation and store.
3. Try a `switch` or a different control flow.

Actually, let me try the "init at decl" trick from moves.md 241/243 more directly: those functions used `s16 loc16[2] = {0, -0x40};` init-at-decl to move dead stores above a load. Maybe declaring a local with init-at-decl near the store changes the birth order.

Let me try: `s32 v = 0;` at function scope, then `v = ...`. The init `v=0` is a dead store. Hmm.

Actually, I already have v as a local. Let me try declaring `s32 v = CAST_SIGN(...)` at function scope but keeping the store in place — tested (v_v_func_init = 20, worse).

Let me try reordering the tail stores in different orders. Target order: unk14(0x14), 0x18, unk48(0x48), unk1C(0x1c). The sched interleaves. The only diff is the store 0x10 vs li a0. 

What if I move the `CAST_WIDTH(...,0x10) = v` to be the FIRST tail statement (before unk14) but keep it in the middle block? It's already before the tail.

Hmm. Let me try: put the 0x10 store INSIDE the if/else (so it's computed and stored in each arm)? That would duplicate it. No.

Let me try: make v and the store part of the tail by removing the block. v_v_func = 2 (same).

OK, I'm confident it's a WALL. Let me also try one more: a `do-while(0)` around the STORE only (not the block), placed so the loop boundary is right after the store. v_s8_store_dw = 4 (worse). 

Let me try a `while` loop shape: `while (1) { CAST_WIDTH(...) = v; break; }`. Similar to do-while.

Let me also try: `if (1) { CAST_WIDTH(...) = v; }` — a redundant if might create a boundary.

Let me test a small batch and then finalize.

Time: 05:03. Item 4 ~7 min. Let me test 3-4 more, then write up at ~05:15 (20 min).

Let me generate:
- v_if1_store: `if (1) { CAST_WIDTH(...) = v; }`
- v_while_store: `while (1) { CAST_WIDTH(...) = v; break; }`
- v_store_in_if: `if (v) { CAST_WIDTH(...) = v; } else { CAST_WIDTH(...) = v; }` — duplicates.
- v_tail_swap2: different tail order.

Let me test.

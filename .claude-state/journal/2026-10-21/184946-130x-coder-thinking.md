---
ts: 2026-10-22T00:49:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_E787DHBXGTzNir7jEEvs
---
The combo sweep is still running (it's scoring 24 variants × 11 items ≈ 264 compiles ≈ 6-7 min).

Meanwhile, let me think about the do-while insight for the other items:
- func_8018CDEC: the do-while worked (the lever's effect was a CFG/fold block).
- For the others, the do-while alone gave: D73C 2, D96C 10, D9D8 19, EA24 10, EF0C 19, 813B0 ?, 83098 10, 8656C 13, C730 6, 91020 25.

Combined with the cast/frame (the combos), maybe some reach 0.

Let me wait for the sweep. Meanwhile, let me think about the do-while for the *other* lever types:

For func_8017D9D8/func_8017EF0C (the "m"(pad) launder): the lever does two things: (1) the frame (pad address-taken → the frame is 8 bytes bigger), (2) the copy v0/v1 opacity. The do-while would block a fold but not the frame. The frame can be fixed by pad[2]. The opacity: hmm, the do-while might block the *copy coalescing*! Because the do-while creates a CFG boundary between the copy and the test → cse might not merge across it? Hmm, cse merges within a basic block; the do-while splits the block → the copy and the test are in different blocks → cse's make_regs_eqv still applies across blocks (it's a global pass over the function's CFG)... but the *values* would be the same.

Hmm, but the combos will tell us.

For func_80183098 (the address launder): the do-while won't help (the address opacity). The combos won't crack it.

For func_801813B0 (the 12-asms ref count): hmm, the do-while might add refs? A do-while(0) adds a loop → the *loop-weighted* refs (REG_N_REFS += loop_depth). Hmm! That's the "keepalive"-ish effect. Interesting.

Let me wait for the results.

Meanwhile, let me prepare the notes/results for the items I've already concluded (4 and 5) — but I should wait for the combo results first, since the combos might crack them.

Let me check the sweep again in a moment. Meanwhile, let me look at the two remaining unexamined items' sources: func_8017D96C and func_8017EA24 (and func_80191020).

Let me look at func_80191020 (82 lines) since its best is 2.

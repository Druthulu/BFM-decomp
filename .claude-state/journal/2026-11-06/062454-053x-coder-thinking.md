---
ts: 2026-11-06T13:24:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9dU8e19vC8ah350oBOYf
---
The dump tool needs a spliced TU .c file. The --try scratch copy is deleted unless --keep. I can produce a spliced TU myself: take the src TU and replace the function body with my candidate body. That's what --body does. I can write a script using body_span + line_starts to splice, writing to my item dir, then run cc1_dumps_tu.sh on it with DUMP_ROOT under my item dir.

DUMP_ROOT env var: the tool uses ${DUMP_ROOT:-.run/P32/t4e}. I can set DUMP_ROOT=.run/P40/T11/O02/<item>/dumps (absolute? "hdump.sh needs an absolute <outdir>" is for hdump.sh; cc1_dumps uses DUMP_ROOT). Let me pass an absolute path.

This is a fair amount of work for one addiu. Time: item2 started ~06:21, now maybe 06:30. Budget 30 min → until ~06:50.

Let me think about cheaper ideas first.

Idea: the `t = rand();` — the target has `move s0,v0` after the second rand then `addiu a0`/`addiu a1`. What if the source declares `nn` and `aa` *inside* the do-loop after the rand calls... they already are at function scope.

Wait, actually let me reconsider the pins: aa is pinned $4 and nn pinned $5. In the target, `addiu a0,s3,4` = aa's init. `addiu a1,sp,16` = nn's init. Both are hard-reg writes. Why does sched1 keep a0 early but sink a1? Both have no deps... unless their priorities differ due to the number of uses. aa is used once (the call), nn once (the call). Hmm.

Maybe the difference is a dependency: `addiu a0,s3,4` depends on s3 (the frame pointer/param), and `addiu a1,sp,16` depends on sp. Both available.

In sched1, the order among equal-priority insns is by LUID (source order). If both had the same priority, a0 then a1 in source order. In mine, a0 is early and a1 is late — so they have different priorities. Why?

Oh! Maybe it's because of the *use*: the jal is a CALL_INSN, and calls clobber caller-saved registers. $5 (a1) is caller-saved. The scheduler adds anti-dependencies: a call clobbers a1, so the addiu a1 → call is a WAR/anti-dep. Hmm, that's the same for a0.

Hmm, maybe the difference is that between the addiu a1 and the jal there are insns that use/modify... no.

Let me look at the actual RTL. Let me just do the dump. It's the reliable way.

Plan:
1. Write splice.py that produces a full TU .c with a given body (using delever_search.body_span).
2. Run DUMP_ROOT=<item>/dumps tools/cc1_dumps_tu.sh <spliced.c> nobar.
3. Read the .sched (ds) dump for the relevant block; compare with the barrier version? The barrier version isn't what we need — we need to understand why the addiu sinks and what would raise its priority.

Actually, maybe simpler: use the -ds (sched1) dump to see the insn numbers/priorities. The dump prints ";; ready list at T-n" and the insn sequence with priorities? Let me check what -ds prints: sched.c's dump includes, for each block, the insn list with ";; insn=NN, priority=..." maybe. Let me look at sched.c's dump code.

This is getting expensive. Let me time-box: try a few more source-level ideas first, then decide WALL/PARTIAL.

More ideas:
- Put the two assignments `aa`/`nn` *after* the second rand but BEFORE `t = rand()`? No, target has them after the move s0,v0 (which is after the rand).
- Hmm! Look: the target has `move s0,v0` (the result of the second rand) then addiu a0, addiu a1. The `move s0,v0` is the birth of s0 from rand's return. In mine: move s0,v0; addiu a0; andi s0... So sched1 puts the andi right after the move, and a1 later.

What if we write `s0 = rand();` and `t = rand();` in a different order (t first)? That changes everything.

- What if we add a dummy use of nn right after its assignment that folds away, like `if (0) func(nn);`? Tree-level folded.
- `nn = (s32)buf; nn = nn;` — the self-assignment is a no-op statement; gcc's gimplifier/fold would drop it? At -O2, `nn = nn;` produces a MODIFY_EXPR that expand emits as (set nn nn) — a no-op move; it gets deleted early (noop moves at the start of jump_optimize, before sched1? sched1 runs after cse2/jump; noop moves are deleted in the first jump_optimize too (noop_moves arg is 0 for the first calls! jump_optimize(insns,0,0,1) → noop_moves=0). Hmm, no-op moves are only deleted in the final pass (after sched1). So `nn = nn;` would create a (set $5 $5) insn at sched1 time — a dependence! And it's zero bytes after deletion. But does it help? It creates a set of $5 at that point; the asm's effect was to order ALL sets before it. A no-op set doesn't order anything.

Hmm, wait. The key issue: the addiu a1 is a *set of $5*. The barrier (asm) created a dependence: for every reg_last_sets[i], add_dependence(asm, last_set, 0). So the asm depends on the addiu → the addiu must come before the asm. The s0 chain is after the asm. So the addiu is forced before the s0 chain.

To replicate: create a real dependence between the addiu a1 and something that is ordered before the s0 chain. What if we make `t` (used in the s0 chain) depend on nn? E.g., `t = (t & 0x1F) - 0x50;` unchanged, but `s0 = s0 + t;` → no.

What if we make the s0 chain's first insn use a variable set from nn... adds code.

Hmm, alternatively, make the addiu a1 depend on an insn that is ordered before the s0 chain AND whose result is cheap. E.g., `nn = (s32)buf + (s0 & 0);`? The `& 0` folds.

What if we use a `volatile` read of a local? `nn = (s32)buf;` then `s0 &= 0x1F;`... 

OK here's another thought: the original author wrote the barrier because it worked. Our job is to find a *lever-free* body. Maybe the answer is a real store that survives: e.g., `d[3] = 0;`? That would add code.

What about moving the `nn = (s32)buf;` assignment to be *after* `d[2] = s0;` (v09) — score 2, same. So source order doesn't matter; sched1 sinks it regardless.

Hmm, so sched1 always sinks the addiu to just before the call. Why? Because its only consumer is the call, and the call is at the end of the block. The s0 chain insns are all "ready" earlier and have higher priority.

Priority in Haifa sched = the longest path from this insn to the end of the block (or to a "sink") — computed backward: priority(i) = latency(i) + max(priority(successors)). The addiu a1 → call: priority = 1 + priority(call). The andi s0 → ... → store: the store is a memory op; the chain is 4-5 long. So the chain has higher priority. Makes sense.

To lower the chain's priority or raise the addiu's: the addiu's only successor is the call. If the addiu had a longer chain after it, its priority would rise. What if `nn` were used in more places after? e.g. used in the s0 chain? That changes code.

What if we make the call's priority higher? Not controllable.

Alternatively, make the s0 chain shorter/lower priority by... the chain is fixed.

Hmm, what about scheduling the addiu *before* the block starts? If `nn` is assigned in the previous block (before the do-while loop head), then it can't be sunk into the loop body. The do-loop body is a separate basic block! The loop head (top of do-body) is a basic block boundary? In a do-while, the body starts after the LOOP_BEG note — the first insn of the body is a basic block start (loop notes DO create basic block boundaries in flow analysis? Let me check: flow.c `find_basic_blocks` treats LOOP_BEG as a block boundary? In gcc, NOTE_INSN_LOOP_BEG ends a basic block.)

If so, placing `nn = (s32)buf;` *before* the do-loop's opening brace should keep it in the preceding block. But it's already before the loop body's start! The do-while starts at `do {` which is after `nn = ...`. Hmm, in v01 I wrapped the s0 chain in do-while; nn is outside, before the `do`. So the addiu is in the previous block already... and sched1 still sank it? That means either the LOOP_BEG doesn't split blocks, or sched1 uses EBBs.

Hmm wait, in v01 the score got worse (4). Let me look at where the addiu ended up in v01. Maybe it moved somewhere else.

Let me dump v01's diff.

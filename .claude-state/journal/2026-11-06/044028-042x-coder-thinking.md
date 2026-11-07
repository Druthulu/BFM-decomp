---
ts: 2026-11-06T11:40:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RD243WJdGUjadIBDlcng
---
v2: 28, worse regalloc (s2/s0 swapped). Hmm.

Let me try v3 (do-while only around the last group) — probably the tail ordering.

Actually, maybe I should think differently: what if the *first* group needs a split and the do-while around it is the right move but the loop notes broke it? Let me check what do-while does to loop.c: it's a loop with one iteration. loop.c may add `NOTE_INSN_LOOP_BEG` and adjust refs (REG_N_REFS += loop_depth). That's exactly what changed regalloc.

Alternative EBB splitter that's not a loop: a conditional branch `if (cond) { ... }` where the block executes unconditionally? Can't without a condition.

Hmm, what about `&&`/`||` fold: e.g. `if (a && b)`. Not applicable.

OK here's another thought: maybe we don't need an EBB split. Let's look at the target vs mine more carefully. In target's EBB (which is ONE EBB from p+=8 to the end, since barriers are RTL scheduling barriers but do they split basic blocks? A `__asm__ volatile("")` is a `USE`-like insn / `asm` insn; sched_analyze treats it as a memory barrier but it's an INSN in the same block. It creates dependencies (anti-deps) that force ordering: all memory refs before the barrier come before it, and all after come after. So the barrier insn is in the block, and sched1 must schedule it in the middle, with anti-deps from stores→barrier→loads.

That's it! The asm barrier creates a chain of anti-dependencies: each store before the barrier has an anti-dep on the barrier (barrier reads/writes all), and each load after has a dep on the barrier. So the barrier acts as a fence in the same block.

So to replace it lever-free, I need a real insn that creates an ordering fence... or actual data dependencies.

Hmm, what if the target's original code before levers had some real structure producing those deps? 

Think about what creates a fence naturally: a function call. Not available.

What about using a volatile? A volatile load/store creates ordering with respect to other volatiles only.

Hmm, what about aliasing: make the loads of w_/h_ alias the stores? w_ is a stack parameter; if we take its address... e.g. `s32 *pw = &w_;` then `x += *pw;` — the compiler may then be forced to load w_ at the use point (stack address) and the store to p could alias? No, p is a pointer; the compiler can't prove it doesn't alias the stack slot, but the load is from the stack frame address which can't alias a heap pointer (p is unknown though, so p might point to the stack!). Actually p comes from func_80010A08, unknown. gcc's alias analysis: a store through `p` and a load from `&w_` (frame address) — gcc knows the frame doesn't escape? &w_ is passed... no, it's not. If we take &w_, the address doesn't escape, so gcc knows p can't alias it? Hmm.

This is getting deep. Let me reconsider the actual diff: the first group's stores vs the adds. What if we can make the adds depend on a value computed in the store group, e.g. reuse a temp? Like:

vx = x; ... ; p[0x1C] = c4; ... ; x += w_;

What if instead we compute `*(s16*)(p+0x10) = x + w_;` directly (no temp x update)? Then x += w_ disappears... but x is used at 0x20 too. `p+0x20 = x + w_` and `p+0x10 = x + w_` → the compiler would CSE to one add. Target has one addu s1,s1,t1 and stores s1 twice. Same.

What if we write `x += w_` EARLIER in source (e.g. right after p+=8)? Then the add's LUID is early and the scheduler puts it early — but target has it late. No.

Hmm, what if the target's order is a consequence of the *store to p[3]=8 and p[7]=0x38* being before the tag2 load because of aliasing, and the adds being after the tag load because of a dependency on tag? No.

Let me look at the sched1 dump to see exactly what the scheduler does with v0. That's the diagnostic. Let me do it.

Plan: run --try with --keep to get scratch TU; then DUMP_ROOT=<item>/dumps tools/cc1_dumps_tu.sh <scratch_src> v0. Then read .sched.

Wait: cc1_dumps_tu.sh does its own cpp+cc1 on the file, with the same flags as the recipe? It uses fixed flags -O2 -G0 -mips1 -mcpu=3000... The recipe may differ. Close enough for reading sched decisions? Risky. But the recipe used by the project should be these flags.

Actually the dumps script runs cpp then cc1 directly with those flags. Let me just try.

Also note: the dump dir must be under my shard: DUMP_ROOT=/home/musashi/bfm-decomp/.run/P40/T11/G30/func_80015B6C__800/dumps.

But cc1_dumps_tu.sh takes wd as either a .c file or a dir with */t.c. Give the scratch .c path.

Let me get the scratch path first: run with --keep and note it. Earlier it printed the object path .run/P36/engine/score/main__func_80015B6C/p3/cand.o; the scratch source is in the same dir named 800.c.

Let me run --keep with v0 and then run the dump script on that dir's 800.c. But the dir persists only until... score_file's finally with --keep keeps it. But a later --try without --keep removes only its own pid dir. Our p3 dir stays.

Hmm, but the p3 dir path depends on pid; the printed line gives the object path, from which I can derive the source.

Let me do it.

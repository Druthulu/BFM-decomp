---
ts: 2026-11-06T14:20:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nq5k1x9N6XbpLx0BfwhZ
---
This is the `propagate_block` live_length computation: for each insn, the regs that were live before and after are counted. It's the number of insns where the reg is live.

If i=0 moves later, the insns before it don't have i live, so live_length should shrink. Unless the RTL order didn't change. Let me check the actual RTL order in b2. The lreg dump is post-sched1, so it may differ. But the live_length is from flow (pre-sched). Let me look at the .flow dump or the .jump dump (pre-flow).

Hmm, this is getting deep. Let me take a more empirical approach: generate a bunch of variants and check the "regs to allocate" order from the greg dump for each. But dumping each is ~5s + 6.6MB. With 5 items and time budget, I should be careful.

Actually, wait. Let me reconsider the problem. Maybe I'm going down a rabbit hole. Let me check whether the ORIGINAL source (in the repo, as committed) is the one with asm keepalives. The task is to find a lever-free body that scores 0. The asm keepalives are "levers" that were added to force the match. The real-C crack must reproduce the same code.

Given the razor-thin priority margin, maybe there's a natural C form that gives i=12 refs. Let me think about what adds exactly 1 ref to i at depth... 

Wait! I just realized: flow's ref count for the `slt` uses i once. But what if the loop condition is `i < n` AND there's an additional use of i in the loop that's REAL and produces no extra instruction because it replaces the comparison. For example:

`while (i < n)` — 1 use.
What if I write the loop as `do { ... } while (i++ < n)`? That would use i in the comparison AND increment it in the same expression. The RTL: the comparison uses i (old value), then i++ (increment). But the semantics: `i++ < n` compares old i then increments. The loop body's i usage... The target has `i++` separately. Hmm, `i++ < n` as the loop condition: the RTL would be `slt (i, n)` then `i = i+1`. Same instructions! And the ref count: i appears in the slt (use) and in the increment (set+use) — same as separate i++. No change.

What about `while (i < n && ++i)`? No.

Hmm, what if I use i in the load address: `px = src[i - i]`? folds.

What about a REAL use that's folded by combine after flow: e.g., `dst = src + n + i;` where combine folds i=0. Let me actually test this! Even though I feared cse2 might fold it, cse2 is at line 2926 and flow at 2983 — cse2 runs before flow. But does cse2 propagate the constant i=0 from block13 to block13's later insn? They're in the same basic block (block 13), so cse2 WOULD fold it. Unless the `dst = src + n + i` is in a different block.

But what if I put the `+ i` use in the LOOP (block 14/17) where cse2 can't propagate the constant across the branch, and combine can't either? Then it emits an instruction. Bad.

Hmm.

Wait, maybe cse2 doesn't propagate `i=0` because `i` is a variable whose value is set in a loop-containing function and cse treats it conservatively? Let me just test `dst = src + n + i;` and see the score. If it's 0, great. If it's 6 with extra insns, we learn.

Let me also test the opposite: make the loop condition use `i` twice in a foldable way.

Actually, let me test a few "add ref" ideas quickly:
- h1: `dst = src + n + i;` (i is 0)
- h2: `dst = src + (n + i);`
- h3: `i = 0; ... dst = src + n;` and add `if (i)` somewhere? emits code.
- h4: in the loop, `px = *(src + i - i);`? folds.

Let me test h1 and h2.

Also, another idea: the `n` variable is computed as `arg0->w * arg0->h`. What if I write `n = arg0->w * arg0->h - i;` with i=0? Same issue (cse folds in block13).

Let me test h1.

Actually, let me reconsider the live_length route more carefully. Maybe the reason b2 didn't change live_length is that the RTL order of `i=0`, `src=load`, `dst=add` is determined by expand's statement order, but sched1 (which runs AFTER flow) doesn't matter. So b2's flow RTL should have i=0 after the load and add. Then live_length(i) should be 39-2=37. But it's 39.

Unless expand emits the constant set early. Hmm. Let me actually look at the pre-flow RTL order. The .jump dump is after jump_optimize (before cse). Let me check the .jump dump for the setup block insn order in b2.

Actually, easier: the .lreg dump shows the post-sched1 RTL. Let me look at the insn numbers for reg 160's set in b2 vs c1. In c1, insn 307 sets reg160 (i=0), insn 310 loads src (reg161), insn 318 sets dst (reg162). Let me check b2's lreg insn order.

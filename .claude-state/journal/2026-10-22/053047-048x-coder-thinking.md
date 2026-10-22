---
ts: 2026-10-22T11:30:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_acZne5RsRndbBe01cnTt
---
Now I see the target's structure:

```
742c: sll v0,v1,0x10      ; sx = (s16)*(u16*)&sxy  (sx in v0)
7430: sra a2,v0,0x10      ; sign-extend
7434: bgez a2,7440        ; if (sx < 0)
7438: move a1,a2          ; delay slot: av = sx
743c: negu a1,a2          ; av = -sx
7440: lui a0,0x6666       ; <-- the magic constant born HERE (top of the tail)
7444: ori a0,a0,0x6667
7448: ...
```

So the constant is born at 7440, right after the branch (the `av` computation), i.e., at the top of the "tail" block. The block starts at 7440 (the branch target of `bgez a2,7440`).

So the "tail" block is the join of the `sx<0` branch: [av = sx or av = -sx] then the constant, then the VOL chain.

So the constant is born at the TOP of the join block, before the VOL chain.

In the candidate, the constant is born just before the first `mult` — i.e., LATER in the same block.

Hmm. Why? Because of the "birth boost"/scheduling: the constant is used by the VOL chain's mult. sched1 would place the constant's lui/ori right before the mult unless it has a reason to place them earlier.

Hmm, but in the target it's placed at the block's top.

**The launder!** The launder asm sits between `vol = ...` and `sx = ...` in the source. It creates a dependency structure that forces the constant up.

Hmm, but here the launder is AFTER the vol computation. So:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;    <- chain 1 (uses the constant)
__asm__("" : "=r"(vol) : "0"(vol));   <- launder
sx = (sx + 0xA0) / 0x14;              <- chain 2 (uses the constant)
```
The launder is between the two chains.

In the target: the constant at the top of the block, then the VOL chain (subu, mult, ...), then the sx chain (addiu, mult, ...).

So the constant is born at the top even though its first use is in the VOL chain.

**KEY INSIGHT**: This is the classic "constant hoisting" — GCC's RTL "split constant" / `combine` hoists a 2-use constant. The birth position of the constant is determined by the scheduler: since the constant is used by 2 insns, its priority is high (2 dependents) → it gets scheduled EARLY.

In the candidate (w4), the constant is used twice too... but it's born late. Hmm.

Hmm — maybe in the candidate the constant is NOT shared: maybe there are TWO constants, one for each chain, and CSE... no, the count is the same (237) and there's only one lui/ori in each.

Hmm, in the candidate:
```
201: subu a1,v1,v0
202: lui v0,0x6666
203: ori v0,v0,0x6667
204: mult a1,v0
...
208: mult v1,v0
```
So the constant IS shared and born at 202, right before its first use at 204.

In the target, the constant is born at 7440 (index 198), and the first use is at 7448-ish (index 203). So it's born 3 instructions before its use.

Why the difference? Because of the LAUNDER: the launder makes the VOL chain's `mult` NOT be the first user in the schedule... hmm.

OK here's the thing: the launder is between the two chains in the SOURCE. So the RTL order is: [VOL chain insns][asm][PAN chain insns]. The constant is used by both chains. Its birth (lui/ori) must precede both. In the target, the constant is born at the very top of the block, before the VOL chain.

In the candidate (launder removed), the source order is [VOL chain][PAN chain]. The constant is used by both. Why is it born after the first `subu`?

Because the scheduler placed it there: the constant's first use is the VOL chain's `mult`. Without a barrier, sched1 might place the constant right before the mult.

Hmm. In the target, the constant is at the TOP of the block. What forces that?

**Maybe the `bgez` branch!** The block at 7440 is the join of the branch. The constant is the FIRST instruction of the join block. In the candidate, maybe the join block starts with something else.

Hmm, let's look at the candidate's disassembly to see. Let me get it.

Actually — here's a KEY structural difference: in the target, the `bgez a2,7440` branch's delay slot is `move a1,a2` (the av=sx path) and the fall-through is `negu a1,a2`. Then 7440 is the join.

In the C source:
```c
sx = (s16)*(u16 *)&sxy;
av = sx;
if (sx < 0) {
    av = -sx;
}
vol = ((0xA0 - av) * 0x7F) / 0xA0;
```
So the join block is [vol chain]. The constant is born at the top of the join block.

In the candidate, the join block starts with the VOL chain's `subu` (the 0xA0 - av), then the constant, then the mult.

So the difference is WHERE the constant is placed within the join block.

**Why does the launder push the constant to the top?**

Because: without the launder, the constant's birth is "just before its first use" (sched1's placement). With the launder, the asm is between the chains, and... hmm, the asm is AFTER the vol chain, so it shouldn't affect the constant's position within the vol chain.

Hmm, hold on! Maybe with the launder, the VOL chain is NOT first. Let me re-read the notes:

"Removing the launder `__asm__("" : "=r"(vol) : "0"(vol));` alone = 30 (236 ins): sched1 swaps the two magic-multiply chains (the PAN /0x14 chain is hoisted above the VOL /0xA0 chain) and the register allocation of the tail changes (a2 vs a3)."

So without the launder, the PAN chain goes FIRST. With the compound-division trick (w4), the VOL chain is first (like the target) but the constant's birth differs.

So: in the target, the constant is at the top of the join block and the VOL chain is first.
In w4, the VOL chain is first but the constant is born just before the mult.

Hmm! What if the difference is: in the target, the constant is born BEFORE the `subu` (0xA0 - av), i.e., at the very top of the block, while in w4 it's after.

Since the constant is a 2-use value, GCC's RTL generation ("split constant") might place the lui/ori where the constant is FIRST needed, and the scheduler moves it. With 2 uses, the scheduler should give it a high priority (2 dependents) → scheduled early.

Hmm, but in w4 the constant IS shared (used at 204 and 208) and it's born at 202 — right before its first use.

In the target, the constant is born at 7440, at the TOP of the block. But what is between 7440 and its first use? Let's see the target:

```
7440: lui a0,0x6666
7444: ori a0,a0,0x6667
7448: subu ... (0xA0 - av)
744c: mult ...
```
Hmm, the diff showed target[198]=lui, 199=ori, 201=subu v1,v1,v0, 203=mult v1,a0. So index 200 is something between ori and subu. Let me get more of the target disassembly.

Let me dump target indices 190-230. I need the function's instruction list. Let me use the diff format or count.

Actually easier: let me disassemble the target from 7430 onwards and count.

From the disassembly:
```
742c: sll v0,v1,0x10     (idx?)
7430: sra a2,v0,0x10
7434: bgez a2,7440
7438: move a1,a2
743c: negu a1,a2
7440: lui a0,0x6666
7444: ori a0,a0,0x6667
7448: ...
```
Let me print more.

Hmm, but note: the branch `bgez a2,7440` at 7434 with delay slot `move a1,a2` at 7438, and `negu a1,a2` at 743c is the fall-through (delay slot of bgez is 7438). Then 7440 = join.

Hmm, but wait: the branch at 7434 is `bgez a2,7440` — if a2 >= 0, jump to 7440 (skipping the negu). And 743c `negu a1,a2` is the fall-through path. But then 7440 is reached from both. And the branch's delay slot (7438) executes `move a1,a2` in BOTH cases? That's the standard "move in the delay slot" trick.

So: the join block at 7440 = [lui, ori, ...]. The constant is the FIRST instruction of the join block!

In the candidate w4, the join block would be [subu, lui, ori, mult, ...] — the constant is 2nd.

Hmm, so why does the target have the constant first?

**Because in the target, the constant was born in the block BEFORE the join?** No, the join block's first insn is the lui.

Hmm, hold on: maybe the constant is born in the PREVIOUS block (the `if (sx<0)` block) and just happens to be scheduled at the join. Let me look at what's before 742c.

```
7414: lhu v0,74(sp)
7418: nop
741c: addiu v0,v0,119
7420: andi v0,v0,0xffff
7424: sltiu v0,v0,239
7428: beqz v0,74b0
742c: sll v0,v1,0x10
7430: sra a2,v0,0x10
7434: bgez a2,7440
7438: move a1,a2
743c: negu a1,a2
7440: lui a0,0x6666
```

So 742c is the delay slot of the `beqz v0,74b0` at 7428.

So the constant (7440) is at the join of the bgez.

OK so in the target the constant is born at the TOP of the join block. In the candidate it's born after the `subu`.

**HYPOTHESIS**: The constant is born (lui/ori) in the RTL right before the first chain's use, and the SCHEDULER moves it. With 2 uses, its priority = 2 (fanout) → high → scheduled early. In w4 it's not scheduled early. Why?

Hmm, maybe in w4 the constant is NOT shared at the RTL level initially, and the sharing happens later (in combine/reload). In the target, the launder might force the constant to be a single RTL value early.

Hmm.

**Let's think about the "2 uses" and the scheduler's "birth boost"**: C0434 says "A SINGLE-SET LOCAL IS SCHEDULED LAST; give it a second set". The constant 0x66666667 is a pseudo with 1 set (the lui/ori pair). Hmm.

**Let's think about the actual launder effect**: `__asm__("" : "=r"(vol) : "0"(vol));`. The asm's output is `vol` (the pseudo). This creates a SECOND SET of vol (the asm sets it). Hmm, and the asm is between the chains.

OK, how about a DIFFERENT approach for item 4: instead of trying to replicate the constant's birth, use the **"real 2nd set"** trick that worked in other shards: make the VOL chain's result have a genuine second set so the constant is shared.

Hmm, actually — maybe a simpler idea: what if the ORDER of the two chains in the source is PAN first, VOL second? Then the constant would be born before the PAN chain's mult. Let's see what that gives. The notes said statement-order permutations gave 33, 32, 33 (worse).

Hmm, w7 (sx chain first, then vol) = 33 with 235 ins.

OK let me think about the residual more carefully:

Target (indices):
198: lui a0,0x6666
199: ori a0,a0,0x6667
200: ?
201: subu v1,v1,v0
202: ?
203: mult v1,a0
204: ?
205: ?
206: addiu v0,a2,160
207: ?
208: mult v0,a0
209: sra v1,v1,0x1f
210: subu a1,a0,v1
211: sra v0,v0,0x1f
212: ?
213: ?
214: sra v1,a2,0x3
215: subu a2,v1,v0

Hmm, the diff "replace mine[201:205] target[203:205]" means target[203]=mult v1,a0 and target[204] is beyond the replace range... The diff format is confusing.

Let me just directly compare the candidate's disassembly with the target's for indices 195-220. Let me get the candidate's object.

Let me be efficient: run --keep on w4.c, objdump, and compare the two listings side by side.

I'll write a small script to print indexed instruction lists for target and candidate.

Actually, the delever_search --try output gives a diff. Let me use a bigger tail (dt.sh with tail 60) to see more.

Hmm, the diff was already fairly clear. Let me just get the two disassemblies.

Let me do it.

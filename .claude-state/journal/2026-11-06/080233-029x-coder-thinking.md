---
ts: 2026-11-06T15:02:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GLStE1tsC3RfWWbgZLrv
---
Target:
- sll a0,s0,0xa at 1f68 (before loop) — s0=0 but it still emits sll, not move a0,zero.
- loop: at 1fa8 (delay slot of bnez) sll a0,s0,0xa.

So gcc in the target emits the pre-loop shift as sll even though s0 is a known 0. That's because of the launder. Without launder, gcc folds to move a0,zero.

Now what plain-C spelling yields `sll a0,s0,0xa` with s0=0? Options:
- Make the shift not constant-propagated: put `a0 = s0 << 10` where s0 is... hmm.

Think: in the target, at 1f68 sll a0,s0,0xa. Then in loop a1 = lhu + a0. If a0 were move a0,zero (0), the addu a1,a1,a0 could even be removed... but it's not; the target keeps the sll. The launder blocks const-prop.

Plain C ways to block constant propagation without asm:
1. `volatile` variable — but volatile is likely a "barrier" kind (lever). Actually kinds: barrier probably means `__asm__("" ::: "memory")` or volatile? Let me check lever_census to see what counts as launder/barrier. But constraint is only that row kinds in <dir>/kinds (launder) are gone; other levers not present may not be added. "no new lever of any kind". volatile likely counts as a lever (class C/D?). Hmm.

2. Compute the value through an opaque operation that gcc can't fold but is plain C. E.g., `a0 = (s0 << 10) + something`? No.

3. Reorder: use a variable that's assigned 0 but also modified in a way gcc doesn't track? 

4. Use `s0` declared as pointer? No.

5. What about the value coming from a function? No.

Key insight: The loop increment `s0 = s0 + 1` is before `a0 = s0 << 10` at the loop bottom. The pre-loop `a0 = s0 << 10` — if we move it AFTER the loop entry check? No, the loop is do-while.

Alternative: restructure so the first sll comes from the same expression as the loop-bottom one via rotating: maybe initialize s0 = -1 and increment at loop top? Let's think: target loop body order:
```
sll a0,s0,0xa      <- (A) at 1f68, before loop, and at 1fa8 delay slot
sll v0,s0,0x1      <- loop head
lh v1,112(s1)
addiu s0,s0,1
...
```
Actually the 1f68 sll is the pre-loop statement; the 1fa8 is the delay-slot copy of the loop-bottom `a0 = s0<<10`. Wait: the loop-bottom statement is `a0 = s0 << 10;` executed after s0 increment. In the target, that instruction appears at 1fa8 (delay slot of bnez), which is filled from the loop bottom. And 1f68 is the pre-loop one.

So target has both: sll a0,s0,0xa at 1f68 (with s0=0) and at 1fa8.

gcc without launder: pre-loop becomes move a0,zero. What does the loop-bottom become? Still sll (s0=1..4 unknown). So only 1 insn differs. Score 2 (one del, one ins).

How to make the pre-loop `sll a0,s0,0xa` survive in plain C? The value s0 is 0 constant. Unless... we make the pre-loop shift use a *different* value that isn't a constant but equals 0 in a way that requires the shift.

Idea: reorder so that the pre-loop a0 assignment is the loop-bottom one moved out? I.e. write the loop as:
```
s0 = 0;
a0 = s0 << 10;
do { ... a0 = s0 << 10; } while(s0<4);
```
already that.

Alternative: use `a0 = s0 << 10` where the initial value of s0 comes from something non-constant, e.g., `s0 = 0; ... ` hmm.

What if we swap: set `a0 = 0;` directly? Target wants sll.

What if s0 is u16/s16? `s0 = 0; a0 = s0 << 10;` still 0.

What about making the initial assignment be part of a loop that gcc can't unroll? Hmm.

Key: gcc 2.7.2's const-prop happens in combine/flow? `a0 = s0 << 10` with s0 known 0: this is folded in "flow"/"combine" via reg_known_value or REG_EQUAL. To block, a common trick is a real 2nd set of s0 that is not a constant: e.g. `s0 = 0; if (cond) s0 = 0;`? flow would still know both branches 0.

Another trick from the moves: `do { } while (0)` to split EBBs (cse1). But const-prop is not cse.

Hmm, what about using a s16 cast: `s0 = (s16)s0;`? Real 2nd set with same value → value known still.

What about making `a0` a different type, e.g. pointer arithmetic? `a0 = (s32)((u8*)0 + (s0<<10))`? Still folds.

Alternative approach: change the structure so gcc's expression for a0 involves s0 in a non-constant way that equals s0<<10. E.g., `a0 = s0 * 0x400;` — multiply by 1024. With s0=0 it still folds to 0.

What if the multiply is done via the variable `s2`? no.

Hmm — maybe instead the difference is not const-prop but the "birth" of the sll. Actually wait: without launder, the output was `move a0,zero` then at 10 `sll a0,s0,0xa` missing? The diff said mine[8] move a0,zero deleted, target[9] sll inserted. Mine has 33 ins = target 33. So mine also has a sll somewhere. Let me get mine's disasm to compare directly.

Let me use --keep and objdump. Actually easier: create the scratch TU and compile via cc1 dumps? Hmm. Let me just use `--try --keep` which prints the object path, then objdump it.

Wait, --keep prints object path. Let me run it.

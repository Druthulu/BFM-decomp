---
ts: 2026-11-06T08:50:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ExI9RNnsLgu6mLjNWiob
---
This is combine's code that, when it can't find the insn for a REG_DEAD note, inserts a USE insn. This happens in the else-block at label 128: the REG_DEAD for reg78 from... Interesting: this is about death notes at a CODE_LABEL.

Hmm, but importantly, this USE insn doesn't block the merge (it was inserted *because* of a death note). The merge still happened (neg reg77).

OK so this is a dead end. The real question: how to keep `(set reg78 (reg77))` and `(set reg78 (neg reg78))` as two insns through combine.

Since combine merges a copy into a following unary op when the copy's destination is used only by that op... but here reg78 is used later by the stores! Why did combine merge then? Because after merging, reg78 = neg(reg77), and the later stores use reg78 — that's fine, they see the negated value. The copy's intermediate value isn't needed. Right.

To keep both insns, the intermediate value of reg78 (before the neg) must be needed after the neg. In the target, is it? The target's code: move v1,s1; negu v1,v1; sw v1,16(s0); sw v1,224(s0). The move's value (nudge) is overwritten by the negu; the stores use the negated value. So the intermediate isn't needed either! Yet the original binary has both insns. So the original source must have forced the copy in a way combine couldn't undo — e.g., the asm — or combine was blocked by a use that the *original* had.

Hmm wait. Actually maybe the original source was NOT `val = nudge; val = -val;` but something else entirely, e.g.:

```c
val = nudge;
val = -nudge;   → dead copy removed
```

What if the original was:
```c
val = nudge;
if (val) ... 
```

Hmm. What if the original code was:
```c
s32 t = rand() & 1;
val = nudge;
if (!t) {
    val = -val;
}
```
No.

Let me reconsider: maybe the copy in the target is NOT the else's copy but comes from the *then* branch (as mine does) and the negu's operand v1 is because in the original, the then-branch's copy and the else's copy were the SAME RTL insn — i.e., the original source had the copy *outside* the if (before the branch), like c5, but the compiler placed it after the call because... 

In c5 (val = nudge; if (!(rand() & 1)) val = -val;) the score was 35 — big difference. Let me look at c5's diff to understand where the move went. If the move went before the call, that explains.

Alternatively, maybe the original source had:
```c
if (rand() & 1) {
    val = nudge;
} else {
    val = nudge;
    val = -val;
}
```
with `val` being used in the *condition*: `if ((rand() & 1) && val ...)` no.

Hmm, let me look at the target's RTL! The build object is compiled from the *current src* (with the asm). I can dump the current src TU (with asm) and see the RTL: it will show how the asm keeps the copy. Then I can think about which real C construct yields the same RTL. Let me dump the orig TU (from src directly). cc1_dumps_tu.sh accepts a .c file; use src/ov_SC02_000/ov_SC02_000_jr_8018173C.c? That's the real TU. Let me dump it under the item dir.

Actually the tool needs the include path; src file is fine (its dir is on the path via -I dirname).

Let me dump and compare the else-block RTL.

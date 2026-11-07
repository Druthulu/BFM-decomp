---
ts: 2026-11-06T06:40:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UKdm3FFoyHpPzvsH7E0S
---
No change. Hmm, so the m18/m18b change didn't matter (cse still merges the address).

Wait — the extra insn is at mine[478-480]. Let me look at the target and mine around there more carefully. Let me get the actual instruction context. I need to see the target asm around 0x8e0.

Let me dump the target asm around the RotTransSV.

Actually, let me reconsider: the diff at 478:
```
477  addiu s0,sp,24     | addiu a1,sp,24
478  move a1,s0        | --
```
and
```
489  move a0,s0        | addiu a0,sp,24
```
So mine has `addiu s0,sp,24` once and then `move a1,s0` / `move a0,s0`. Target has `addiu a1,sp,24` and `addiu a0,sp,24`.

So the address sp18 is held in s0 in mine. In the target, it's rematerialized.

This is cse hoisting the address into a callee-saved register because it's used across calls.

How to break it in real C? The same dead-reset trick: after the first use, reset the variable.

But m18/m18b are separate variables already, so cse still equates `sp18` (the constant address) across them.

Dead-reset: `m18 = 0;` after RotTransSV — that would break cse's class for the address... Hmm, but the address pseudo is `&sp18`; assigning m18 = 0 doesn't invalidate the &sp18 equivalence (m18's value is the address; setting m18=0 kills m18's class, so the second use `m18b = sp18` re-materializes).

Let me try: `m18 = sp18; RotTransSV(mm, m18, sp28); m18 = 0;` then `m18b = sp18; func_8018FB5C(m18b, sp20, col);`.

Hmm, but that's the C0414 pattern — it worked for mp.

Let me test that (d4). Also apply the same to `mm`.

Wait, but hold on: is the extra insn really about sp18? Let me count: mine 711, target 710. The extra insn is `addiu s0,sp,24`. And there are 2 uses. So mine hoists into s0 and uses 2 moves; target has 2 addius. That's 3 vs 2 → +1.

Yes.

Let me try the dead-reset for m18.

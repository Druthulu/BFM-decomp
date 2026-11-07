---
ts: 2026-11-06T05:24:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UPwZDuFnCvmKOMrXkYg2
---
Hmm, a1/a2 worse (18), a3/a4 same 8. So the HImode cast made it worse (probably changed regs). Let me look at a1's diff... maybe the cast added something. Let me instead think.

The target needs iVar2 in a0 and tmp in v0, with the copy `move v0,a0` in the beqz delay slot.

Actually wait. Let's reconsider: maybe the target's structure isn't `tmp = iVar2` at all. Let me look at the target asm fully for the first block.

Target asm around insn 9-14:
```
9  lh a0,16(v1)
10 ? (something)
11 beqz a0, ...
12 move v0,a0
13 bgez a0, ...
14 ...
```
Hmm: `beqz a0` then delay slot `move v0,a0` then `bgez a0`. So after the beqz, in the delay slot, tmp = iVar2 (v0 = a0), then bgez on iVar2.

So the source order: `iVar2 = lh; if (iVar2 != 0) { tmp = iVar2; if (iVar2 < 0) ...}`. Reorg moved `tmp = iVar2` into the beqz delay slot. 

So the copy exists. And the register choice: iVar2 in a0, tmp in v0.

In mine, everything merged into v0. So we need the copy to survive.

Let me look at the actual target asm to see where iVar2/tmp are used in the arms.

Let me disassemble the target.

---
ts: 2026-11-06T10:14:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eNGPHcP5qbuBn8Y2bJXZ
---
g2: s1ang (r75) live still 22 — moving the source statement didn't change the RTL birth. So the RTL order is determined by data dependencies / gcc's emission, not just source order. The load's birth is at insn ~20 regardless.

Hmm. s1ang live 22, d live 27.

To make d win: d pri > s1ang pri. 
- d: 2*7/27 = 5185
- s1ang: 2*7/22 = 6363

If I could make s1ang's live 28: 5000 < 5185. 

How to lengthen s1ang's live by 6 RTL insns? The live range is birth (load) to death (last use). The last use is in the last `if (iVar4 < -0x800)` block. The birth is the load.

What if I move the load's *birth* earlier by making it depend on nothing... it already does.

Hmm, the RTL birth is where the insn is emitted. The load `*(s16*)(*(s32*)(arg0+0x20)+0x12)` is emitted after `d = arg1` and after the `*(arg0+0x20)` load. In the target asm, `lw v0,32(v0)` and `lh s1,18(v0)` are at positions 9-15 (after the D_ loads). So the birth is fixed by the target's asm order! The target's asm has the load at position 14. So live can't be extended without changing the asm.

Hmm, so the target's s1ang live is fixed ~22 (in RTL terms). And d's ~27.

Then the target's pri order (d > s1ang) requires d's refs to be higher or... 

Wait — maybe in the target, d's refs are 8+. Let me reconsider d's refs in the nopin: refs 7, live 27. In the target, d might have more refs due to a different source shape.

Hmm, what if the target's d has refs 8? floor_log2(8)=3 → 3*8/27 = 8888 > 6363 → d gets s0! 

How to give d one more ref without changing instructions? Refs are counted per insn occurrence. If d appears in one more insn... e.g., if the sign-extension were 2 insns (sll+sra) both using d — that's already counted. 

Hmm, what if d is used in a *compare*? Like `if (d == 0)`? adds code.

What if the division is `iVar4 / d` and gcc emits a div with a check (`bnez d`) — the div sequence includes `bnez s0` (checking d for zero). That's a use of d! The table's refs count includes the bnez. So d's refs already include the div's check.

Hmm.

Let me reconsider: maybe the target's d is NOT global but local. If d is local with a short live range and high priority, it takes s0 before s1ang (local, pri 2857). 

d local with live ~16 (from move to sign-ext at position 19): pri = 1*2/16 = 1250 < 2857. s1ang wins s0. No.

If d's live were 2 (move + immediate sign-ext): pri 10000 > 2857 → d gets s0, s1ang s1. But then the sign-ext is in the prologue, not position 19.

Hmm, BUT what if the sign-ext at position 19 is for a DIFFERENT variable (dd, global), and d (local, short) is the one that takes s0? Let me think:
```
s32 d = arg1;    // d local, live short if sign-ext is right after
s32 dd;          // global
d = arg1;
... (s1ang, u5)
dd = (s16)d;     // d dies here
q = iVar4 / dd;
```
d's live = from move (position 3) to sign-ext (position 19) = 16 → pri 1250 < s1ang 2857 → s1ang gets s0. No.

Unless d dies right after the move: `d = arg1; d = (s16)d;` adjacent. Then live ~2 → pri 10000 → d gets s0. But the sign-ext would be at the prologue (position 4), not 19. The target has it at 19.

Unless sched1 SINKS the sign-ext from the prologue to position 19! Sched1 can move instructions later within a block (it's a list scheduler; it schedules in dependency order, and independent insns can move later). Actually, sched1 typically produces a schedule that may sink/hoist. Let me test: `d = arg1; d = (s16)d;` adjacent at the top, with the pin removed and keepalive removed. w2 tested this with the pin kept? Let me check: w2 = base.replace("d = arg1;\n s1ang","d = arg1;\n d = (s16)d;\n s1ang") and removed the later `d = (s16)d;`. Scored 40 (74 ins). So no.

Hmm.

OK, let me look at this from the actual target's alloc perspective by considering that the ORIGINAL source is unknown. Let me try to find the original source shape by searching the disassembly for clues. The target's `move v0,a0` at position 1: arg0 is copied to v0 and used for all the loads. In our source, arg0 is used directly. The compiler chose v0.

Hmm.

Time check: ~03:16. Item 2 has taken ~16 min. Let me move on to items 3 and 4 and come back if time permits. Item 2 is looking like a WALL (lreg-qty-order / greg-alloc-order).

Actually, wait. Let me try ONE more idea: what if the original had `d` used in the `u5` computation, e.g., the divisor is computed from arg1 in a way that gives it more refs? No.

Hmm, what about making s1ang's qty SMALLER (size 0? no).

What if s1ang is declared as `s16`? Then the load is `lh` and `s1ang & 0xFFF` — the qty size is 1 (HImode). But the `& 0xFFF` promotes to SImode. Hmm, t1 (u32) no change. v6 (s16 s1ang) scored 21 in nopin.

OK let me move to item 3 and 4. I'll come back to item 2 if time.

Actually, let me reconsider the priority of my time: 4 items, each needs a row. Items 3 and 4 are also keepalive,pin. Let me quickly assess them: maybe they're easier.

Let me look at item 3 (func_8012BB3C) and item 4 (func_801535F4) residuals via --explain.

Let me clean up the g1/g2 dumps first (disk capped). I'll delete the dump dirs.

Actually, keep them for now, delete at the end. Disk: cc1 dumps go under my item dir and must be deleted as soon as read. Let me delete dump_a, dump_g1, dump_g2 now.

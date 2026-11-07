---
ts: 2026-11-06T10:46:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_F1c37TkP1VbfOeoud3sH
---
Now the ORDER is perfect (lw, lui, addiu, sw, ori, sw) but the registers are swapped: t in v1, a in v0.

So both t and a are in the same block (block1) and the address variable a got v0, t got v1. Hmm. t and a both defined in block1; t used in block2, a used in block2. Both global. global-alloc order gave a v0.

In the target: t v0, a v1.

So I need to flip the allocation priority between t and a. Priority = refs * live length. Both have 2 refs. Live length: t defined at the load, used at the ori; a defined at lui/addiu, used at sw. Hmm.

What if I declare `a` before `t` (declaration order)? Global-alloc's allocno numbering follows declaration order; the reg assignment order might follow allocno number. Currently `s32 t; s32 a;` → t is allocno N, a is N+1. If allocation order is by allocno number, t would get the first free reg (v0). But we got a→v0. So order isn't by allocno number; it's by priority.

Priority = floor_log2(refs) * something + live length. t's live range: from the load (block1) to the ori (block2). a's: from the address computation (block1) to the store (block2). Both span the same blocks. If a's live range is *longer* in insn counts? Hmm.

Alternatively, local-alloc? If t and a are both local to block1+block2... no.

What if we move the address computation `a = ...` to block2 instead? That's the original d_S2S3S4 where the store sank. Hmm.

What if we compute `a` in block1 but *before* the load? Then a's def is earlier; priority might differ. But the target has the load first in the schedule; if a is computed before the load in source, sched1 might still put the load first (independent). Let me try: do { a = (s32)&D_801907C4; t = unkC4; } while(0);

Hmm, but then the lui/addiu comes before the lw in the block. sched1 might keep source order. Risky.

What about making t's priority higher by adding a use? Not allowed (keepalive).

What if we reverse the declaration order: `s32 a; s32 t;`? Let me test both quickly: declaration order swap, and the source order swap.

Let me generate 4 variants:
1. decl order a,t + current order.
2. do { a = ...; t = ...; } while(0)
3. do { t=...; a=...; } but decl order a,t.

Actually the decl order might change allocno numbering → global-alloc processes in some order. Let me just try.

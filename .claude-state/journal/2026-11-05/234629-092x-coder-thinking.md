---
ts: 2026-11-06T06:46:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uGUGup7DpbWieb6dCPKU
---
All 54-ish. v_v2 = 45 (161 insns) — removing the var_v0 copy for the b stores. Interesting: it reduces insns.

Hmm, the fundamental issue: the target has 163 insns and mine 162 — one instruction missing, plus the register swaps.

The missing insn: `move a0,zero` (var_a0 = 0). In mine, `var_a0 = 0` might be folded differently.

Let me think about the v0/v1 issue: mine's `subu v1,v0,s0; move v0,v1; sll v1,v1,0x10; bgez v1`. So var_a0 → v1($3) and var_v0 → v1 too?! Then the target: `subu v0,v0,s0; move a0,v0; sll v0,v0,0x10; bgez v0`.

So in mine, the value stays in v1 and var_a0 is ALSO v1 — meaning var_a0 and var_v0 are the same pseudo (the move is redundant but still emitted?). Hmm, `move v0,v1` copies to v0... 

I'm running low on time for this item (started 23:45, now ~23:58). Let me try a couple of high-value ideas:

Idea A: the `var_v0` temp is heavily reused (34 refs, pri 26562, conflicts with s0,s2,s3,s4,s5 — a caller-saved). Splitting it per use (moves: "split reused v0 into own var") might fix the v0/v1 choices.

Idea B: the pins k50=$20, kF0=$18, k100=$19 put the constants in callee-saved regs. Lever-free they'd be elsewhere. Since k40 has no pin (it's in the table without a pin), hmm.

Wait — interesting: k40 has a launder but no pin. k50/kF0/k100 have both. So the target has k40 somewhere.

Let me look at the target's asm to understand the register roles. That's the reliable path but takes time.

Given the budget (I've done 4+15+1 = ~20 tries on item 4, ~13 min), a WALL needs 30 tries and 20 min. Let me do one more batch of ~15 variants (splitting var_v0 per use, etc.) and then record.

Let me think about what would actually help:
The residual is: v1↔v0 swap for 3 computations, s7/s8 swap, and one missing `move a0,zero`.

Splitting var_v0: `var_v0` is used as a scratch for many things. If I split it into v0a, v0b, v0c..., each use gets its own pseudo → local-alloc gives each $2 (first choice). The target seems to use $2 for these temps.

Let me write a variant that replaces the reused var_v0 in the three computations with a fresh temp each:
```c
        var_fp = 0xC0 - var_s0;
        { s32 t; t = var_fp << 16; if (t < 0) var_fp = 0; }
```
Hmm, that's sp1 which scored 64.

Alternatively, since the target has var_a0 in $4 (a0) and the temp in $2, maybe the issue is that var_a0's allocation is tied to the copy `move a0,v0`.

Hmm, what if I use `var_a0` directly in the stores instead of copying to var_v0? That's v2 (45).

Let me try v2 + sp variants combined.

Actually, let me look at the target asm for this function — it'll tell me the intended register roles, and then I can decide. 163 insns; let me look at the head.

Time check: I should wrap up item 4 within ~10 more minutes.

Let me do one more batch (12 variants) of combinations: v2 + sp1, v2 + d-swaps, etc., and then record.

---
ts: 2026-11-06T06:44:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XdqM2HaEdKrzqnLmAT4z
---
The residual is essentially:
1. A v0/v1 swap for several values.
2. s7/s8 swap in the tail (srl v1,s7 vs srl v1,s8).
3. The ordering of the store block (mine emits the stores earlier, target later) — but that's mostly the same insns in a different order... Actually mine[53-62] vs target[54-76]: mine's store block is 10 insns, target's is 13. Hmm, mine has fewer because of a different code path? No, the count is 162 vs 163 (one missing insn: `move a0,zero`).

Let me look at the source:
```c
        var_fp = var_v0 = 0xC0 - var_s0;
        var_v0 <<= 16;
        if (var_v0 < 0) {
            var_fp = 0;
        }
        var_s7 = var_v0 = 0xE0 - var_s0;
        var_v0 <<= 16;
        if (var_v0 < 0) {
            var_s7 = 0;
        }
        var_a0 = var_v0 = 0x20 - var_s0;
        var_v0 <<= 16;
        if (var_v0 < 0) {
            var_a0 = 0;
        }
```
The target: `subu v0,v0,s0; move a0,v0; sll v0,v0,0x10; bgez v0,...` — so var_a0 gets the value BEFORE the shift. Then `move a0,zero` if negative.

Mine: `subu v1,v0,s0; move v0,v1; sll v1,v1,0x10; bgez v1,...` — the same shape but in v0/v1 instead of v0/a0.

So mine: the third value (var_a0) is in v0, target in a0. And the shift temp is v1 in mine, v0 in target.

This is a local-alloc/global-alloc choice. The values var_fp/var_s7/var_a0 are in callee-saved regs (s8, s7, and... in target var_a0 is in a0 = $4! a caller-saved reg). Hmm, that's odd — var_a0 is used later (sp10.b[13] = var_v0 etc.), so it should be callee-saved... but there are no calls between.

OK. So the difference: in the target, var_a0 is in $4 (a0) and the shift temp in $2 (v0). In mine, var_a0 is in $2 (v0)?? and the shift temp in $3.

Hmm, mine: `move v0,v1` — var_a0 = v1's value into v0? Hmm, that doesn't make sense: `var_a0 = var_v0 = 0x20 - var_s0;` → `subu v1,v0,s0` computes 0x20-s0 into v1, `move v0,v1` copies to v0 (var_a0 = var_v0?). Hmm, actually gcc computes `0x20 - var_s0` into a temp then assigns both var_a0 and var_v0.

In the target: `subu v0,v0,s0` (0x20-s0 into v0), `move a0,v0` (var_a0 = v0), `sll v0,v0,0x10` (var_v0 <<= 16).

In mine: `subu v1,v0,s0`, `move v0,v1` (var_a0 = v1?), `sll v1,v1,0x10`.

So in mine, var_a0 ends up in $3 and var_v0 in $3 too (they're the same value). In the target, var_a0 is in $4 and the shifted value in $2.

Since var_v0 is reused for many things afterwards, this is a local-alloc decision.

Let me look at the whole picture: it's a "lreg" ordering issue. The pins were: var_t7=$3, k50=$20, kF0=$18, k100=$19. So the target has var_t7 in $3 (v1) — that's why the target's shift temps are in v0 ($2) and var_t7 is in $3.

So the pin on var_t7 ($3) reserves $3, pushing everything else to v0/v1/a0.

Lever-free, var_t7 goes... somewhere. Hmm, in mine, the s7/s8 swap at the tail: `srl v1,s7,0x1` vs `srl v1,s8,0x1`.

So: two variables (var_fp, var_s7) swapped between s8/s7 in the tail. And var_t7's allocation.

Given the pattern of my earlier items, this will be a register-bank ordering wall.

Let me try quick variants:
1. Split the reused var_v0 into separate temps (moves: "split reused v0 into own var").
2. Change `var_fp = var_v0 = ...` to separate statements.
3. Reorder the k constants' declarations.

Let me first check the alloc table to understand. Time is limited (30 min per item). Let me do a batch of variants and score.

Actually, the key question: which variable is in $3 in mine? If var_t7 is in $3 in mine too, then the difference is elsewhere.

Let me dump the alloc table quickly.

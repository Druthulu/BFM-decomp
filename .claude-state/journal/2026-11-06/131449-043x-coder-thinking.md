---
ts: 2026-11-06T20:14:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BF7yvpRNWDkkSPnx7Trx
---
Key: the pinned orig loop has **30 real insns** (not 28)! Because the pin forces an extra move (the call result copy). So in the pinned version insn_count=30, threshold=28 → 28 < 30 → not desirable. Lever-free: insn_count=28, threshold=29 → 29 >= 28 → hoisted.

So if I can get insn_count to 30 while keeping the final code at 28 insns (i.e., adding 2 insns that get removed later), no hoist. vG got 29 (one extra addiu) — need 2, or make threshold smaller.

Wait: lever-free threshold = 29 (n_non_fixed_regs=28). Hoist iff 29 >= insn_count. So need insn_count ≥ 30.

vG gave 29. Need one more insn at loop.c time. The addiu added one. Add another address temp for the second constant store (-0x92): `a = *p; a += 0x8A; *(s16*)a = -0x92;` → but that one is already "not desirable" (insn 140), so it stays anyway; adding an addiu there might change final code (combine folds it, so final same). That would give 30.

But wait: the -146 store's li is already not hoisted; adding an addiu that combine folds keeps the final code identical (assuming combine folds it). So vG + same trick on the -0x92 store → insn_count 30 → -1024 not hoisted. Let's try.

Actually careful: the second store `CAST_NONSTRUCT(s16, *p, 0x8A) = -0x92;` → target `lw v1,0(s1); li v0,-146; sh v0,138(v1)`. With the temp: `a = *p; a += 0x8A; *(s16*)a = -0x92;` → lw; addiu; li; sh; combine folds addiu into sh offset → lw; li; sh. Same as target. Good.

But also: adding insns changes the scheduling/regalloc? sched1 runs after combine, so it sees the folded code. The extra insns are gone. The only risk is combine's folding and the `a` temp's register allocation before combine... but combine is before local-alloc, so fine.

However: does combine actually fold `addiu a,a,10; sh v0,10(a)` into `sh v0,10(v1)`? Combine works on 2-3 insn windows; yes, it folds an add into the mem address of a following insn if the reg is dead after. The `a` pseudo dies at the store, so yes.

Let me try vH = vG + the -0x92 trick.

Note: `a` reused for both. Let me write:
```
            a = *p;
            a += 0xA;
            *(s16 *)a = -0x400;
            ...
            a = *p;
            a += 0x8A;
            *(s16 *)a = -0x92;
```
The second replaces `CAST_NONSTRUCT(s16, *p, 0x8A) = -0x92;`.

Wait, but careful about ordering: the -0x92 store is after `off += 8;` and before `p++`. Fine.

Let me create vH.

---
ts: 2026-11-06T10:03:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HgwZqMo1sbOVDHBTX7ts
---
Line 446-450: "A basic block starts at label, or after something that can jump." `prev_code == CALL_INSN` → a basic block starts after a call! So calls DO end basic blocks in gcc 2.7.2.

So s1ang: def before the call (block N), use after the call (block N+1) → it's GLOBAL! But the alloc table said r75 (hard s0, blk 0, crosses 1 call). Hmm, "blk 0" in the table might be the def block, and the table's note "crosses 1 call" — and yet it has a hard reg s0. 

Wait, the alloc_table "hard" column for r75 shows s0. If r75 is a *local* allocno it gets a hard reg in local-alloc. If global, hard shows "-" (the docstring says global allocnos print as `-`). So r75 IS local (has s0). But the def is before the call and the use after → global...

Unless the use is in the same block as the def, meaning the block isn't split at the call here. Hmm, line 450: `prev_code == CALL_INSN` starts a new block after a call. So the andi (after the call) is in a new block. So s1ang crosses a block boundary → global.

But the table shows r75 as local with s0. Contradiction. Unless r75 is not s1ang.

Let me identify r75 properly. "75 in 16" in dispositions. Let me look at the .greg dump for `(reg:SI 16 s0)` or where 75 appears. Let me grep the .greg for "75".

Actually, the .greg dump is after local-alloc; pseudos replaced by hard regs. Let me grep for "reg:SI 16" or "reg 75".

Hmm, "75 in 16" means pseudo 75 → hard reg 16. Let me find which RTL insn uses 75. It won't appear as 75 anymore; it appears as s0. Let me instead look at the .lreg dump, which is before local-alloc, and find pseudo 75.

Let me grep the .lreg section of func_8012BA10 for "75".

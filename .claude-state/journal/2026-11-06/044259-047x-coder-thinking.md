---
ts: 2026-11-06T11:42:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_K7HSp0a7wafbaZxfAsIF
---
Hmm, this is different from what I expected. My w4's group A loads are t3,t4,t5,t6 (lw) — wait, no: lines 1-8 are 4 lw into t3..t6. Then lines 9-18 are 5 loads into v0,v1,a0,a1,a2 — that's group B (r6,r7,r8,r9,r10)? But the widths: v0 lhu, v1 lhu, a0 lw, a1 lhu, a2 lhu — that's group B (r6=u16 lhu, r7=u16 lhu, r8=s32 lw, r9=u16 lhu, r10=u16 lhu). Yes! So lines 9-18 = group B.

Then stores: sw t3,t4,t5,t6 to D_80126950..5C — wait, those should be group A (r2..r5), but they're t3..t6. Hmm, the first 4 loads (t3-t6) are group A, and they're stored at lines 19-26. Good.

Then Blk8#1 (lines 27-38). Then group A2 loads t3-t6 (lhu). Then Blk8#2. Then group B stores sh v0,v1,a0,a1,a2... 

So my w4 order: A, B, S, C1, A2, C2, SB, S2 — EXACTLY target order! But the register assignment differs: target A in v0,v1,a0,a1; mine in t3,t4,t5,t6. Target B in a2,a3,t0,t1,t2; mine in v0,v1,a0,a1,a2.

So the schedule is right; only global-alloc's register choice differs. Score 63 (REG-caller).

Now, target: A (first group, dies early) gets v0,v1,a0,a1; B (long-lived) gets a2,a3,t0,t1,t2. Mine: A gets t3-t6 (worst), B gets v0-v2 (best).

This is a global-alloc priority issue: in my w4, the A values are live across the Blk8 copies? Let me check: A loads at lines 1-8, stored at 19-26. B loads at 9-18, stored at 59+. So B has much longer live range → should get... hmm, in gcc global-alloc, higher priority = more refs relative to live length. A: 2 refs, live ~20 insns. B: 2 refs, live ~50 insns. So A has higher priority (shorter live) → should get the best regs v0..a1. But mine gave A t3-t6 and B v0-a2. That's backwards!

Wait, maybe gcc 2.7.2's priority is the opposite: `floor_log2(refs) * 10000 / live_length`? If live_length larger → lower priority. So A (short live) higher priority. Then A should get v0... but it didn't.

Hmm, maybe local-alloc (not global) handles these since they're all block-local in one block. In a single basic block, local-alloc assigns registers in order of definition (first-come-first-served), and global-alloc only handles pseudos that cross blocks or exceed local regs. All these are in one block, so local-alloc assigns them.

local-alloc assigns in order of first use, preferring... Actually local-alloc processes each basic block and assigns hard regs to pseudos that don't conflict, in order of pseudo number (or use order). The first 4 pseudos defined get the first available regs.

In my w4, the first 4 pseudos (A) got t3-t6, not v0-v1. Why? Because local-alloc has "qty" preferences and copy preferences; also it prefers to use call-clobbered regs and avoids regs used by other things.

Hmm, in the target, A got v0,v1,a0,a1 (the first regs). In mine, B got v0,v1,a0,a1,a2 and A got t3-t6.

Wait — maybe in mine the order of *definition* is A first (lines 1-8), so A should get the first regs. Unless local-alloc considers the *whole block* and orders by... it uses `local_alloc` which iterates over blocks and calls `block_alloc`; within block_alloc it computes `qty` and `reg_qty`, then for each insn in order, assigns regs. The first insn defines A's r2. So A should get v0.

Unless there's a copy preference: `r2 = D_80120200` is a load (not a copy from a reg), so no copy preference.

Hmm, but the Blk8 copy's BLKmode move defines pseudos too. Those might grab v0/v1 first? The BLKmode move at C1 uses 2 pseudos. In my w4, C1's data regs are a3,t0. So not v0/v1.

Wait, maybe the issue is that B's pseudos are defined at lines 9-18 but live until the end; local-alloc's `block_alloc` assigns regs to each pseudo at its definition, but if a pseudo is used later it stays. Order of definition: A first. So A gets v0-v3? But it got t3-t6.

Let me look at the alloc table for w4. The hdump alloc table would tell. Let me run hdump for w4 and check.

Actually, maybe the reason is "local-alloc prefers call-clobbered over callee-saved" and v0/v1 are special ($2/$3) — gcc 2.7.2 on MIPS marks $2,$3 as call-clobbered; $4-$7 too. All are call-clobbered. t3-t6 are $11-$14.

Hmm, why would A get t3-t6? Unless the pseudo numbering/order differs. Let me check the alloc table.

Actually — important: local-alloc's `block_alloc` assigns registers by iterating over the *uses* (via `reg_use_count`) and gives registers to pseudos with the highest `reg_qty` priority. It's not simply first-defined. It computes `qty` = number of uses, and `qty_phys_reg` etc.

Let me look at the alloc table for w4 vs orig.

Let me run hdump for w4.

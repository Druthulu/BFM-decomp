---
ts: 2026-11-06T10:44:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yrTd0ZYCKplSJ3lEo5SK
---
v_dw4 has the right ORDER now (lw, lui, addiu, sw, ori, sw) but the regs swapped: t in v1, address in v0. Interesting — so with two do-whiles, t ended up in v1 (not global?) and address in v0.

Hmm, why? Because the two do-while blocks... t is defined in block1 and used in block3. Maybe the load and the ori are in the same block? Let me think: `do { t = ...; } while(0); do { unk58 = ...; } while(0); unkC4 = t|2;` — maybe loop optimization merges the do-whiles or the blocks aren't separate at the point of local-alloc.

The allocation: t got v1, address v0. That means the address pseudo was allocated v0 first (higher priority) in its block, and t was global and got... hmm.

In the target, t is v0. Since t is defined before the address and live across, local-alloc in block1 allocates t; if t is a *local* allocno in block1 and block3 has a separate... no, t must be global.

Let me reconsider: which pseudo is global? In gcc, an allocno is global if it's live in more than one basic block. t is live across blocks → global. global-alloc assigns hard regs to global allocnos before local-alloc, preferring... it processes in order of allocno number? and t would get a hard reg. The address is local → local-alloc gives it a free reg (v0 if free).

If t is global and got v1, then global-alloc assigned v1 to t — why not v0? Because global-alloc's order/priority. Hmm, but in the target t got v0.

Wait, in the target the barrier is before the load, so the load's block is B, and the store's block... with the barrier, is there only ONE barrier? Yes, one barrier after unk5C. So the target's blocks: block A (up to unk5C), block B (load, store, RMW, everything after). t is defined and used within block B → local allocno! Then local-alloc allocates: t (block-local) and the address (block-local) in block B. Priority: t has 2 refs (def+use); the address has 1 ref. So t wins v0. Then the address gets v1. That's the target!

So the target's structure is: ONE block boundary before the load, and then the load+store+RMW all in one block, with t as a *local* allocno that wins v0.

But my d_S2S3S4 (do-while around the load only) creates: block1 = load, block2 = store+RMW+rest. t is defined in block1, used in block2 → global → gets v1 (why v1? because global-alloc order or because v0 is used by something else). The address in block2 is local, gets v0 (free).

So I need the block boundary BEFORE the load, and the load in the same block as the store+RMW. That is: `do { ... } while(0)` around the *preceding* statement (unk5C = 0x8000), so the boundary is after it, and the load+store+RMW are all in the following block.

That's the barrier's position exactly! So wrap `unk5C = 0x8000;` in a do-while? Hmm, does a do-while around S1 create a block boundary after it? The do-while creates LOOP_BEG/END notes around S1; cse1's EBB split occurs at the loop notes. Then the load is in a new EBB.

Let me test: S1 wrapped in do-while, S2,S3,S4 plain.

Actually, hmm: the do-while's loop notes — would the boundary be before S1 or after? The notes are around S1. So we'd get block A, then [LOOP_BEG] S1 [LOOP_END], then block B with S2-S4. The EBB split is at the LOOP_END, so S2-S4 start a new EBB. But S1 is also in its own EBB. Good: that's the barrier position (after S1).

Let me test. Also maybe wrap S1 together with the earlier stores. Let me just try.

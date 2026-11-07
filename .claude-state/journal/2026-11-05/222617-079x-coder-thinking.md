---
ts: 2026-11-06T05:26:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3cvqRMhnPzCdz8lJ0nxe
---
This is `alter_reg` in reload1: if a pseudo has no hard reg and no equivalent, allocate a stack slot. So the 16-byte frame could be a spill slot for a pseudo that ends up with **no hard reg but is never actually used** (so no accesses emitted)! Wait, if it's spilled it must be accessed. Unless the pseudo is dead after reload.

Hmm, but a 16-byte slot = one pseudo with `total_size`=16 (e.g., a BLKmode or DImode pseudo) or 4 pseudos with 4-byte slots.

Actually, the key: `reg_renumber[i] < 0 && reg_n_refs[i] > 0` → allocate a stack slot. If the pseudo is later eliminated/dead, the slot is unused but counted in the frame. This happens when a pseudo isn't assigned a hard reg. With the memory clobber, some pseudo (probably the `(mem:BLK (scratch))`-related or a struct temp) isn't allocated.

The 16 bytes: maybe 4 pseudos × 4 bytes. Hmm.

Regardless: the frame is a reload artifact caused by the clobber. A lever-free body could in principle also produce an unallocated pseudo → stack slot. But matching exactly (16 bytes, no accesses) is unlikely.

Let me now decide the strategy. Given:
- The comment in the source explicitly says the two memory fences keep the three parts from CSE-ing their base addresses.
- walls.txt already has `cse-fixed-global-cache` with exactly this mechanism.
- The clobber also adds a 16-byte frame.

For func_80175820/758FC/759D8: WALL `cse-fixed-global-cache` (and the frame artifact). Evidence: cse keeps the `*q` load/address across the nonscalar store; the barrier's memory clobber is also what forces the reload and the 16-byte vars frame.

But I must try ≥30 lever-free bodies per item and ≥20 min. Let me do that efficiently: generate ~30-40 real-C variants per item and score them. The best score will be recorded. Then append a WALL row.

Actually, wait. Let me reconsider the item family. func_801759D8 has a slightly different residual (lhu v0,0(t1) vs lhu v0,0(a2); addu v0,v0,t2 vs t1). And 80175820/758FC are identical. Let me check the family's target frames and residuals.

Before the grind, let me check the simplest possibility: maybe some of these CAN be cracked with a move. Let me try the catalog moves quickly on 80175820:

The known wall is cse-fixed-global-cache. To beat it in pure C, we'd need cse to NOT forward `*q` across the store. cse invalidates memory on a store at a variable address — but the store is `(mem/s:SI (plus:SI (reg) 8))` (struct member). GCC 2.7.2 cse's write_data classification: let me read it to see whether a struct member store invalidates a fixed-address scalar. If it classifies the store as SCALAR (only invalidates scalars) or STRUCT... The wall says "cse keeps a global pointer load in a reg across a nonscalar store". So a *nonscalar* store (struct member) does NOT invalidate the scalar global. That's the cse bug/behavior. Could we make the store look scalar? `ptr[2] = ...` where ptr is `u32 *` → `(mem:SI (plus (reg) 8))` is scalar! Hmm, but the wall says nonscalar. `(mem/s:SI)` — MEM_IN_STRUCT_P set because ptr came from a struct member `f0`? The store `ptr[2] = ...` is through a pointer derived from `D_800AE7BC[*q].f0` — MEM_IN_STRUCT_P may be set on the memory ref because the base is a struct member? Actually `ptr[2]` is `(mem:SI (plus (reg ptr) 8))`; MEM_IN_STRUCT_P is false for pointer indexing. Hmm.

Let me read cse.c's invalidate_from_clobbers/write_data to understand the classification. Actually, the wall entry says: "cse-fixed-global-cache — cse keeps a global pointer load in a reg across a nonscalar store; target reloads (G18x)". So a previous coder already diagnosed: the store is nonscalar and cse doesn't invalidate fixed-address loads. Fine.

Could a lever-free body change the store to be scalar (so cse invalidates)? E.g., store via `*(u32*)((u8*)ptr + 8) = ...` — same. The classification is based on MEM_IN_STRUCT_P of the destination. `ptr[2]` from a `u32 *` → not in struct. Hmm, but the wall says nonscalar.

Let me look at cse.c write_data bits and how a store is classified.

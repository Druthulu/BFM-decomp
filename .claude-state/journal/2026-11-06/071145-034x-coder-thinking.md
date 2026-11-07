---
ts: 2026-11-06T14:11:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HLO6UiyEBjq5VVu8kWuq
---
So qty_birth is an index within the block (index = insn_number*2). qty_death similar. reg_n_refs is global.

So priority = floor_log2(reg_n_refs)*reg_n_refs / (death - birth within block). death-birth is the life within the block.

For i (reg 160) in block 14: birth at insn 307? No wait, block 14 is insns 325-379, and the increments i++ at 397 are in block 17 or so. Hmm, block 14 first insn 325 last 379. The loop body block is 14; the increments at 391-407 are in block 17 (first 388, last 407)? Let me recheck: Basic block 17: first insn 388, last 407. So the loop latch (dst++, i++, src++, slt, branch) is block 17.

Hmm, so local-alloc is per block. i and dst appear in block 14 (uses) and block 17 (defs). Within block 14: i is used? i is only used in block 17 (i++ and slt) and block 3 (i=0)? Wait, where is i used in block 14? The asm(i) at insn 329 is in block 14! That's the keepalive. Without the asm, i is NOT live in block 14 at all (i is only in blocks 3 and 17).

Oh! That's the point. The i keepalive makes reg 160 live in block 14. Without it, i is not in block 14, so local-alloc in block 14 doesn't consider it. But the final register assignment for i comes from block 17 (where i++ and slt happen) or block 3.

Hmm wait, but local-alloc per block can assign different regs in different blocks? No — local-alloc assigns reg_renumber per pseudo but only if the pseudo is allocated in that block; conflicting assignments across blocks would be a problem. Actually local-alloc only allocates pseudos that are live within a single block (not live across blocks); pseudos live across blocks are left to global-alloc. Wait no, that's the point of local-alloc vs global: local-alloc handles regs that die within a block. Regs live across blocks are handled by global-alloc.

Hmm, but i lives across blocks (3 -> 17, and the loop 17->14->17). So i is live across blocks, and global-alloc assigns it. Then why does local-alloc's qty matter? 

Wait, the "Register 160 used 14 times across 41 insns; dies in 0 places" — "dies in 0 places" suggests it's a global reg. Hmm.

Actually, let me reconsider. Maybe the register swap is due to *global-alloc*, and the priority there also uses n_refs. global-alloc.c uses the same formula. Let me check: global-alloc assigns based on allocno priority = floor_log2(n_refs)*n_refs*size/live_length, where live_length is total. The keepalive adds refs, raising i's global priority.

So the mechanism: global-alloc. And the fix must raise i's global-alloc priority above dst's, or lower dst's.

Global allocno priority formula in global-alloc.c: 
```
pri = (floor_log2 (allocno[n].n_refs) * allocno[n].n_refs * allocno[n].size) / allocno[n].live_length
```
Let me check.

Regardless, the lever is: i has 11 refs, dst has 11 refs without asm; i's live length is longer (i spans blocks 3-17, dst spans 14-17). So dst gets priority. Adding refs to i raises it.

How to add a real ref to i? Real C that uses i more. Options:
- Use `i` in the store address computation. E.g., `dst = src + n; ... *dst = out;` where dst is derived from i? If instead we keep only `i` and compute `dst` each iteration... that changes codegen (adds instructions).
- Use i in the loop condition twice? `while (i < n)` vs `if (i < n) ... while`.

Hmm, but the generated code must stay identical. The target's loop has:
```
lhu $7,0($9)      # px = *src
... compute ...
sh $5,0($11)      # *dst = out
addu $11,$11,2    # dst++
addu $10,$10,1    # i++
slt $2,$10,$12    # i<n
bne $2,$0,$L131
addu $9,$9,2      # src++
```

So i is used in 2 insns: `addu $10,$10,1` (read+write) and `slt $2,$10,$12` (read). dst in 3 insns: `sh $5,0($11)` (read), `addu $11,$11,2` (read+write). Actually 2 insns for dst in the loop, plus the initial `addu $11,$9,$2` in block 14.

Refs count (global n_refs): i = init(set) + i++(set? and use) + slt(use) = let's say 4 RTL refs? But the table says 14. So n_refs counts differently (weighted by loop depth). Right: reg_n_refs in flow.c is weighted by loop depth. Let me check flow.c.

Let me grep flow.c for reg_n_refs.

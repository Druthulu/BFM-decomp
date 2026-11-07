---
ts: 2026-11-06T10:44:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PmZfF0c0WIEPoLmQpc2R
---
Best 2 (d_S2S3S4 = wrap S2 alone). We knew.

The remaining issue: sw v1,88 sinks below the RMW. Let me think about sched1 priorities.

The schedule in mine (v_dw):
```
f34 lw v0,196      S2 load
f38 lui v1         S3 addr hi
f3c addiu v1       S3 addr lo
f40 ori v0,v0,2    S4
f44 sw v0,196      S4
f48 lw v0,32(s0)   (first 0x4000 load)
f4c sw v1,88       S3 store
f50 li v1,16384
```
So the S3 store got scheduled after S4 and the next load. sched1 schedules by priority; the store's priority is low.

In the target:
```
f34 lw v0,196
f38 lui v1
f3c addiu v1
f40 sw v1,88
f44 ori v0
f48 sw v0,196
```

What if the store S3 is in its own block (do-while around S3 alone)? Then it must be emitted in that block, in source order relative to the blocks: block order is S2-block, S3-block, S4-block. Within the S3 block: lui, addiu, sw. That gives exactly: load, lui, addiu, sw, then ori, sw. And the register allocation: S2 in block 1, S3 in block 2 — separate blocks, so local-alloc allocates v0 to the load (block 1) and v0 to the address (block 2)? Both could be v0 since different blocks! But the target has the address in v1. Hmm, if the address pseudo gets v0 in its block and t gets v0 in its block, then after the load t is live (v0) and the address also wants v0 → conflict at the boundary? Global/local alloc would handle it: the address pseudo is local to block 2, t is live across blocks → t is global (v0), so the address gets v1. That's exactly the target!

Wait, is t live across the block boundary? t is defined in block 1 and used in block 3 (after block 2). So t is live across block 2 → global pseudo → v0. The address is block-local → v1. 

So wrapping S3 alone in a do-while should give the target! Let me test: v_dw3 = do { t = unkC4; } while(0); do { unk58 = ...; } while(0); unkC4 = t|2;

That's my v_dw4 earlier which scored 7. Hmm! Let me look at v_dw4's diff. Maybe the two consecutive do-whiles merge into one block (loop notes adjacent). Let me check.

---
ts: 2026-11-06T06:22:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wpbAqLEGJPzhRzbVz2zM
---
Big differences. Mine uses s8 (extra callee-saved → frame 76 vs 72). The target has no s8.

Notice: in mine, `lui s8,0x5555; ori s8,s8,0x5556` — that's the magic constant for `hh/3` (division by 3: 0x55555556). In mine it's kept in s8 across the loop (the div-by-3 magic constant hoisted!). The target materializes it... let me see. Target has no lui 0x5555 at all in the prologue; the target's `mult` for div-by-3 must be somewhere inside.

Also `lui s5,0x0; addiu s5,s5,0` = &D_8018E894 hoisted to s5 in mine; target has `sll v0,s3,0x2; lui at; addu at,at,v0; lw v0,0(at)` — i.e., the array address is materialized per iteration with `at`.

So two hoisting differences:
1. `D_8018E894` (const array address) hoisted into s5 (callee-saved) in mine; target rematerializes per use with lui at/addiu? Actually target: `lui at,0x0; addu at,at,v0; lw v0,0(at)` — the base is in a register `at` materialized from lui (the addiu is folded into the lw offset? `lw v0,0(at)` after `addu at,at,v0` — hmm, so the base is `lui at,0x0` and then `addu at,at,v0` where v0 = index*4. So the base symbol address is materialized with lui only + the addiu folded? That means D_8018E894's low part is 0? No... Actually `lui at,0x0` looks odd — probably `lui at,0x8019` and my diff display truncated? No, the diff prints the actual text. Hmm, "lui at,0x0" — the assembler output with relocations shows 0x0 because the symbol reloc isn't resolved in the .s. Right! The `%hi(D_8018E894)` is printed as `lui at,0x0` in the raw asm (relocation). So target: lui at,%hi; addu at,at,v0; lw v0,%lo(at)? Hmm, `lw v0,0(at)` with 0 offset — the %lo must be in the addu? Not possible. 

Whatever: the point is the target does NOT hoist the address into a callee-saved reg; it rematerializes.

2. The div-by-3 magic 0x55555556: in mine hoisted into s8; in the target, it must be materialized inside the loop (mult a1,<reg>?). Let me see more of the diff.

This is the classic "loop-const-hoist" / "cse-const-addr" wall. Let me see the full diff.

Actually, note the register pairs: a1->s4 x1, a1->s5 x1, a0->v1 x1, s3->s6 x1. Small.

Let me get the full diff text.

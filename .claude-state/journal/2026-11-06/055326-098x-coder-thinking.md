---
ts: 2026-11-06T12:53:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RJctIFmldRYb8Vrt08AC
---
Target tail:
```
fd0: move a2,t2        ← src = base (t2)
fd4: lui a0,0 ; addiu a0,0   ← dp = D_80127548 (in a0 = $4 pin)
fdc: lw v1,0(a0)       ← dcount
fe0: li v0,36          ← c36
fe4: addiu a0,a0,4     ← dp = dp+1
fe8: subu v0,v0,v1     ← df = c36 - dcount
fec: sll v1,v0,1
ff0: addu v1,v1,v0
ff4: sll v1,v1,4
ff8: addu a1,v1,a0     ← ba = tmp + dp
ffc: move a0,a1        ← dst = ba (a0 = $4 pin)
1000: lhu v0,0(a2)     ← tv = *src (a2 = src)
...
```
So in the target: dp in a0 ($4 pin), ba in a1 ($5 pin), dst in a0 ($4 pin, reusing dp's reg after dp dies), src in a2 (t2 → a2).

Mine: `addu a0,v1,a0; lhu v0,0(a1); addiu a1,a1,2` — so mine has dst=a0, src=a1? and a2 unused? The register pairs say a1->a2 x4.

So mine has src in a1 and dst in a0; target has src in a2 and dst in a0. The difference: `src` gets a1 instead of a2.

Also mine's prologue: `move s3,a2` early (pb = param_3 stored in s3) vs target `move s3,a2` at insn 11.

Hmm wait, target's prologue: `addiu a1,sp,16` (local) at 5, `sw s3,36(sp)` at 8, `move s3,a2` at 11.

Mine: `sw s3,36(sp)` at 5, `move s3,a2` at 6, `addiu a1,sp,16` at 11.

So the order of the prologue insns differs (sched1 birth order?). Hmm, actually these are probably all in the entry block.

And the register pairs a1->a2 x4: src (and pb?) in a1 vs a2.

What did the asm do? The keepalive `__asm__ ("" : : "r"(c36), "r"(dcount))` gave c36/dcount refs; the launder `("=r"(decoy) : "r"(ba))` + keepalive(decoy) forced `ba` and `decoy` allocation.

Since ba is pinned $5 (a1) and dst pinned $4 (a0), and src is unpinned: target src = a2.

Mine: src = a1?? But a1 is ba's pin ($5). Hmm, at the loop, `ba` is dead (dst = ba was done), so a1 can be reused for src. In the target, src is a2 (t2 → a2).

Wait, in the target, `move a2,t2` at fd0 — src = base was in t2 during the main body (the `base` pointer), copied to a2 for the copy loop.

In mine, `move a1,t2` — src goes to a1.

So the difference is the register for `src` (and maybe `base`'s life). Target keeps `base` in t2 through the whole function and copies to a2 at the end; mine also uses t2 but copies to a1.

Hmm, and mine's dst? Let me look at mine's asm tail.

Let me dump the candidate. I need --keep for tryinc? tryinc doesn't support --keep directly (it passes args to delever_search: --try TU FN body --body). I could call delever_search directly with --keep but then the includer recipe matters. Alternatively use the cc1 dump via hdump.sh (which inlines the body into the includer TU and dumps). That's the proper tool for header items: `.run/P40/T10/hdump.sh <includer TU> <header basename> <body.c> <outdir> <tag>`.

But first, let me try some cheap C moves and see if the score drops. Ideas:

1. `src` declared as `u16 *src = base;` (init at decl) instead of the later assignment — changes birth order.
2. Reorder: `src = base;` after the dp stuff.
3. Make `src` a copy of `base` via a cast.
4. Remove the `decoy` variable entirely and the two asm.
5. The keepalive on c36/dcount: c36 and dcount are both used in `df = c36 - dcount`, so they're already live. The asm added refs (maybe to control allocation: c36 → v0, dcount → v1).

In the target: `lw v1,0(a0)` (dcount→v1), `li v0,36` (c36→v0), `subu v0,v0,v1` (df→v0). So c36 in v0, dcount in v1, df in v0.

Mine: `lw v0,0(a0); li v1,36; subu v1,v1,v0` — swapped! c36 in v1, dcount in v0, df in v1.

So the keepalive asm on (c36, dcount) influenced which gets v0. Hmm: with the asm, both got +1 ref? A 2-operand asm adds refs to both. The target has c36=v0 (allocated first?).

Lever-free alternative: swap the statement order `c36 = 0x24; dcount = *dp;`? Or declare them differently.

Hmm, since `df = c36 - dcount` is the only use of both, their priorities are equal; the allocator picks by qty number (local-alloc). Swapping the assignment order might swap the registers.

Let me try a batch of variants:
a) swap `dcount = *dp;` and `c36 = 0x24;`
b) `s32 c36 = 0x24;` init-at-decl, `dcount = *dp;` 
c) `src = base;` moved to decl
d) remove `decoy` var and both asm
e) swap the `tv = *src; src++;` / store order
f) dst declared before src

Let me generate and score a few. Note: each tryinc run scores ONE includer; the tool rotates. Since all includers are the same code with different surroundings, scoring includer 0 is a decent proxy; at the end I must verify all 141.

Let me build variants.

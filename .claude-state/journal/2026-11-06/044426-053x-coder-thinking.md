---
ts: 2026-11-06T11:44:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QBgT8QCHdjBFveJ5WHvq
---
Best 28 (c001: p, inplace, first, masks "2"). v2 was the same 28. The base v0 = 30 with 119 insns (one fewer).

Interesting: v0 has 119 insns, target 120. The tagstore temp variant might add the missing insn. Let me look: with `tagstore=temp`, we add a temp for the tag store. That was excluded. Let me try tagstore=temp variants (36 more). Also `u32 nt` might produce the extra insn.

Actually the missing insn in v0: target has `ori a2,a2,0x200` separate; mine also has it. Let me count: target 120, v0 119.

Let me now try a second sweep focusing on:
- tagstore=temp
- masks combos including "1" (wrap first group only)
- add="temp" style with an explicit xs/ys temp (my XBLOCK uses x += w_; "temp" isn't distinct in group2 anymore)

Also the do-while wrap of the FIRST group (mask "1") — maybe that's the key (v1 wrapped both and got regalloc chaos; wrap only first?).

Let me generate sweep 2: axes
- g1s: p
- add: inplace, direct
- tagpos: first
- tagstore: plain, temp
- masks: "", "1", "2", "12", "1"+"2"? (that's 12)
= 2*1*2*5 = 20. Plus maybe a couple with vx/vy decl changes.

Also worth trying: swapping the order of the `tag2 = 0xE1000200;` and the ot store (they're separate statements; target has lui before the sw? target: 38d4 sw a2,0(v0); 38d8 lui a2,0xe100; 38dc lw v1; 38e0 addiu v0; ... 38ec sw v1,16380(s0); 38f0 sb; 38f4 lw; 38f8 ori a2; 38fc sw a2,4(v0)). So tag2 const materialization (lui) is between the tag store and the ot store, and the ori comes later after the sb/lw. That's just scheduling.

Let me also try moving `tag2 = 0xE1000200;` before `pmask = ...` or before the tag store.

I'll write gen2.py producing ~24 candidates.

Also: maybe try `pmask` computed as `(u32)p & 0xFFFFFF` earlier (at decl? `u32 pmask = ...` must be after p). Or use `pmask = (u32)p & m24` where m24 = 0xFFFFFF constant (no, m24 is a constant folded).

Let me write gen2.

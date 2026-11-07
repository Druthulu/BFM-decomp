---
ts: 2026-11-06T11:53:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qnmhZkVUn4Sk6oMELzkY
---
Best 13. Hmm. The mask swap persists (a0/a2).

Let me think: in p1, mine has m24 in a0, mFF in a2; target m24 in a2, mFF in a0. The pins: pv=$3 (v1). The if branch uses m24 and mFF too (different block). Local-alloc assigns within blocks.

What determines a0 vs a2? Local-alloc qty order: the first pseudo needing a caller-saved reg gets a0, next a2 (a1 is used for idx/andi). In target's else: m24=a2, mFF=a0 — so mFF was allocated first (a0) and m24 second (a2). In mine: m24=a0, mFF=a2.

So the birth/allocation order differs. mFF is used in `pv & 0xFF000000` (first) and m24 in `... & m24` (second). Target's mFF (a0) allocated first.

Real C moves: declare mFF first (in the else) → maybe allocates first. I tried mFFvar (m24 declared first, mFF second) = 13. Let me try mFF declared FIRST:
```
u32 mFF = 0xFF000000;
u32 m24 = 0x00FFFFFF;
```
Let me also try using mFF/m24 in swapped roles? No.

Also: the target materializes m24 with `lui a2,0xff; ori a2,a2,0xffff` at the TOP of the else (before the lhu), and mFF with `lui a0,0xff00` later. In mine, m24 materialization is at the top too but in a0.

Let me try:
- mFF first decl
- mFF first + m24 literal (inline 0x00FFFFFF in the expressions, no m24 var)
- m24 literal + mFF var

Actually if m24 is inlined as a constant in the `and` instruction... MIPS `and` can't take a 24-bit immediate, so the compiler needs a register anyway (0x00FFFFFF needs lui+ori). It would use a scratch.

Let me also reconsider: maybe the real fix is elsewhere. Let me look at the remaining diff for f_mFFvar (13): same as p1? Probably.

Alternatively, try `s32` vs `u32` for the masks: target's `and` uses a0/a2.

Hmm. Let me think about the register allocator: in the else block, pseudos needing caller-saved: pv (pinned $3), m24, mFF, ot pointer, the D_800B9A02 load value, v0 temps. Target: mFF=a0, m24=a2.

In mine: m24=a0, mFF=a2. If I declare mFF first, local-alloc's qty numbering (which follows pseudo numbers = creation order) would put mFF earlier → gets a0? Pseudo creation order follows the order the expressions are first seen during RTL expansion, i.e. source order of first use, not declaration. mFF first use is in `pv & mFF`; m24's first use is in `... & m24` (later). So mFF should be created first → a0. But mine has m24=a0.

Unless... local-alloc allocates by qty priority = number of refs. m24 is used twice (`& m24` twice), mFF twice. Tie.

Hmm, wait: in the target, is the mask in a0 really mFF? Target:
```
3fa0 lui a2,0xff; ori a2 -> 0x00FFFFFF (m24)
3fcc lui a0,0xff00 -> 0xFF000000 (mFF)
3fd4 and v1,v1,a0     pv & mFF
3fd8 and v0,v0,a2     (*ot & m24)
```
Yes.

In mine (p1):
```
lui a0,0xff; ori a0 -> 0x00FFFFFF (m24 in a0)
lui a2,0xff00 -> mFF in a2
and v1,v1,a2  (pv & mFF)
and v0,v0,a0
```
So swapped.

What if I write the expression in the opposite order: `*(u32 *)p = (*(u32 *)D_800AE7BC[D_800B9A02].a & m24) | (pv & mFF);` — that changes the OR operand order but the ANDs stay.

What if I use different widths: `s32 m24 = 0x00FFFFFF; s32 mFF = 0xFF000000;`? Probably same.

Let me try a batch:
- mFF first decl (var)
- mFF first decl, m24 second, with the first expression written as `(m24 & ...) | (mFF & pv)`? That reverses.
- use `0x00FFFFFF` inline and keep mFF var
- use `0xFF000000` inline and keep m24 var

Let me test these 4-6.

Also, maybe a totally different approach for item 2: since the barriers are the real problem in v0 (133 ins, 35), and p1 (launder gone) is 13 with barriers... Let me first try to crack the launder residual (13) with these mask variants, then attack the barriers (needs MATCH).

Given the budget (item 2 started ~10 min ago), let me spend ~10 more minutes.

Let me generate the variants.

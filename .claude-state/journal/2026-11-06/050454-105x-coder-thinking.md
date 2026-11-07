---
ts: 2026-11-06T12:04:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_naDH4GASxOdDVdrptmlN
---
Still 4 for p2. The residual is stubborn: `addiu v0,sp,16` + moves vs `addiu a1,sp,16`.

Let me examine the exact diff once more (p2): 
```
  delete  mine[18:19] target[18:18]
       18  addiu	v0,sp,16   | --
  insert  mine[20:20] target[19:20]
       20  --             | addiu	a1,sp,16
  replace mine[21:22] target[21:22]
       21  move	a2,v0  | move	a2,a1
  delete  mine[25:26] target[25:25]
       25  move	a1,v0  | --
```
So mine: insn 18 addiu v0,sp,16; insn 21 move a2,v0; insn 25 move a1,v0.
Target: insn 19 addiu a1,sp,16; insn 21 move a2,a1.

Note the positions: mine's addiu is at 18, target's at 19 — one insn later. And mine has an extra move a1,v0 (at 25) because v0 is used for the call's a1 (which the target doesn't need).

Hmm, mine's `move a1,v0` at 25 — the call's a1 argument. Target has a1 already.

What if the pseudo for va were allocated a1? It got v0.

What's at insn 19-20 in mine? Let me get the full disassembly of mine vs target around there. Let me dump p2's candidate.

Actually, the p2 body keeps the launders. The launder `__asm__("" : "=r"(va) : "0"(va))` — the "0" means the input is tied to the output. The register allocator picks. Why v0? Because v0 is free and local-alloc's priority order...

Real C: make a1 busy/free differently. E.g. use `va` in a computation that forces a1? No.

What if I change the call cast: `((void (*)(s32, void *, void *))func_80149350)(node, va, vb)` — the call's args are (s32, void*, void*). Target passes node in a0, va in a1, vb in a2.

Hmm, what if `va` is declared as `void *` instead of `u8 *`? The cast at the call then is unnecessary: `func_80149350)(node, va, vb)`. Might change nothing.

Honestly, at this point item 4 = WALL best 4? No wait — WALL best = lowest score of a *lever-free* body = 18 (v0). p2 (barriers gone, launders kept) = 4 is a partial-lever body.

Hmm, but p2 = 4 is so close. One more idea: the launders are kept, so what if I ADD back... no.

Let me try changing the launder constraint spelling (still a launder kind): `__asm__("" : "+r"(va));` and `__asm__("" : "=r"(vb) : "0"(va))` (tie vb to va). The latter might directly produce `move a2,a1`! Actually `: "=r"(vb) : "0"(va)` ties the output register to va's register — that's exactly `move a2,a1` if va=a1.

Hmm, but is that "a new lever"? It's the same launder kind, just a different constraint. I'd argue it's still the launder lever (and the kind is kept, so it's a PARTIAL anyway). It's a modification of the existing lever, not a new kind. But the brief says "levers of other kinds the def already had ... may stay, never added". Changing the launder spelling isn't adding a new lever kind. Risky but acceptable? The spirit: PARTIAL:<kinds still kept> means the body still uses that kind. Fine.

Let me try:
- j1: vb launder tied to va: `__asm__("" : "=r"(vb) : "0"(va));`
- j2: both as "+r": `__asm__("" : "+r"(va));` and `__asm__("" : "+r"(vb));`

Let me test these two.

Also, one more idea to keep in mind: since p2 = 4 is close, maybe a real-C tweak (not the launder) gets it. The missing piece: `addiu v0` vs `addiu a1`.

Let me run j1/j2.

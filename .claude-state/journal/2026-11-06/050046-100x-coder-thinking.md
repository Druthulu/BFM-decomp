---
ts: 2026-11-06T12:00:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KgIJMo5odB15cPSqSSnp
---
Two register-pair issues:
1. a2 <-> a3 (12+11 = 23 insns) — the my/mny grant.
2. s5 <-> s6 (3+3 = 6 insns) — some other allocno pair (the addiu sp+292/296 = &m2/&m3? those are the launder addresses!).

Interesting: s6/s5 are the m2/m3 addresses! The launders (now dead resets) are supposed to make &m2/&m3 rematerialize at each site, but the addiu sp+292/296 grants are swapped (s6 vs s5).

Hmm wait, the dead resets replaced the launders and scored 0 in d1/d2/d3. But in e0 (barriers also removed), we see the s5/s6 swap. So the s5/s6 swap is caused by the *barrier* removal? That seems odd (the barriers are in the switch arms).

Hmm, but v3 (barriers gone, launders kept) also showed the s5/s6 swap at mine[380] (swc2 $17,0(s6) vs 0(s5)). So the barrier removal affects the s5/s6 grant.

Wait, but d1 (launders→dead resets, barriers kept) = 0. And v3 (barriers gone, launders kept) = 53. So the barrier removal causes the 53, including the s5/s6 swap and the a2/a3 swap.

The barriers are zero-byte insns in the FT3/FT4 arms that lengthen `my` (mechanism: allocno priority tie). But how does that affect s5/s6 (the m2/m3 addresses)? Global allocno priority ordering: changing one allocno's priority can change the *order* of allocation, which affects other grants.

Hmm, that's plausible: global.c allocates in priority order; a tie/ordering change cascades.

So the barriers are load-bearing for a global-alloc priority tie. Real C can't add zero-byte insns... but maybe a real-C change to the *live lengths* could achieve the same tie.

The comment says the slider lengthens ONLY `my` (placed where my is live and mny is dead). We need L_my such that int(K/L_my) == int(K/L_mny).

Hmm, but with the barrier gone we see TWO problems (a2/a3 and s5/s6). If the a2/a3 issue is fixed, maybe s5/s6 fixes itself (cascade).

Let me focus on making L_my 2 longer with real C.

The live length is measured in insns. Adding 2 zero-byte insns between my's set and its next use lengthens it. What real C adds 2 *emitted* insns that are then removed? Nothing.

Alternative: lengthen my's live range by making its set earlier. In the then-branch, my = y0. What if I move the y0 load to *before* the if (unconditionally)? Then my's value is available earlier, but my's set is still in the branch.

What if I set `my` before the if and fix it up in the else?
```
my = ((XFT3 *)pkt)->y0;
if (my > ((XFT3 *)pkt)->y1) {
    mny = ((XFT3 *)pkt)->y1;
} else {
    mny = my;
    my = ((XFT3 *)pkt)->y1;
}
```
Semantically: if y0 > y1: my=y0, mny=y1 ✓. else: mny=y0, my=y1 ✓. 

But the emitted code would differ: the y0 load unconditional before the branch. Hmm, that might actually match if the target loads y0 first? Let me check the target's code.

Let me look at the target disassembly for the FT3 y-region. I need to find it. The function is at some address; let me grep for `lh` with offsets 2/6 and a compare.

Actually, from the e0 diff, the mismatches at mine[76]-[94] are in the FT3 arm (the a2/a3 swap around `move a3,v1` / `srl a2,v1,0x10`). Let me look at the target disassembly at that area (insn 66-95 of the function).

Let me get the target disassembly around insn 60-100.

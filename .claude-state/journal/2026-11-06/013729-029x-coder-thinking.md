---
ts: 2026-11-06T08:37:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_50lDgt6O47zDd2lKIbNh
---
With off keepalive: r72 (a0 copy) pri 3333, live 30; r77 (t3) pri 1666, live 18; r79 a0 pri 2857. So the a0 copy's priority dropped from 3703 to 3333 (live 27→30), t3's dropped from 4000 (refs2 live5) to 1666 (refs3 live18) because t3 is now live longer due to keepalive.

Wait, in w2 the off keepalive is kept, t3's keepalive removed — but t3 got live 18 and refs 3? That's strange. Hmm, maybe r77 here isn't t3. Let me map: the alloc table doesn't name pseudos. Pseudo numbers differ between variants. Hard to map.

Key: with off keepalive, a0 copy pri 3333 > t3's 1666, so a0 gets a2 (the first free caller reg after a0/a1 are taken? Actually a0/a1 params r75/r76 got a0/a1, r79 got a0? weird—r79 hard a0? that's a conflict-free because ranges don't overlap...). Anyway.

So mechanism: making off live longer extends... hmm, why does a0-copy priority change (3703→3333)? live 27→30: 3703 = floor(log2(5))*5/27*1e4 = 2*5/27*1e4 = 3703. Yes. 3333 = 2*5/30*1e4. So the a0 copy's live range got longer by 3 (because off's keepalive insn is after the a0 copy... no, the a0 copy r72's live range extends to include the asm? The asm uses `off`, not a0 copy. Hmm, live length is measured in insns from first to last use; if the asm is placed between... the a0 copy (r72) is live to the call; its live length 27 vs 30 could include the asm insn count (1 asm = 3 insns? no, asm emits 0 insns but occupies lreg slots).

Actually the asm `__asm__ __volatile__("" :: "r"(off))` adds a USE insn (one insn in RTL). So a0-copy live length increases because the asm sits in its range and adds RTL insns? Hmm, live length counts insn numbers (LUIDs), and the asm occupies an insn slot. With one asm, +1? But it went 27→30, +3. Hmm.

Anyway, the arithmetic target: need a0 copy pri > t3's pri. In w1: a0=3703, t3=4000. We need to change these without levers. Options:
- Extend a0-copy's live range start earlier or shorten t3's live length. a0-copy live 27; t3 live 5 (refs 2). pri_t3 = 2*2/5 = 8000? No, table says 4000 for r77. Hmm 2 refs live 5: floor(log2(2))*2/5*1e4 = 1*2/5 = 4000. Right, log2(2)=1.

a0 copy: refs 5, live 27 → 2*5/27*1e4 = 3703.

So to flip: a0 copy pri needs > 4000: live must be < 25 (2*5/25=4000 tie; tie broken by lower allocno wins — r72 < r77 so tie goes to r72! Actually "lower allocno wins" means lower pseudo number wins the register? In global.c:607 allocno_compare returns based on priority; ties broken by ... let me not rely).

Or reduce t3's priority: refs 2 live 5 → increase live to 6 gives 3333 < 3703. That's the keepalive effect (live 5→18 in w2 gives 1666). But we need real C to extend t3's live range to at least 6 without emitting instructions.

Real C: make t3 used later. The last use of t3 is `sp10[3] = t3;`. If we instead write `sp10[3] = t3;` later, after sp10[4] = t4? Target order is: sw t0, sw t1, sw t2, sw t3, lw t4, sw t4. So t3 store is before t4 load. If source order changed to store t3 after t4's load, sched1 might still schedule it as target? The instruction order is determined by sched1 mostly, so source order change may not alter final order. But it changes live ranges (t3 live across t4's load).

Actually target: t3's live range in target: from lw a3 (insn 17) to sw a3 (insn 21) — 4 insns. In w1: lw a2 (insn 25) to sw a2 (insn 30) — 5 insns? Table says live 5.

Hmm. Alternative real-C: use `off` again later in a real expression that's folded to nothing? Like `sp10[4] = *(s32*)((char*)&D_801A5470 + off);` — already uses off. 

What about changing where `off` is defined: `off = a1 * 20;` — target computes sll/addu/sll (a1*20). 

What if we write the fifth load using `off` in a way that extends off's liveness — it's already used there.

Idea: reorder the h[] computations: h[0], h[1], h[2] each load from sp10 and a0 fields. The target keeps `a0` pointer copy in a2 and uses it for all three lhu's. 

Let me think about the actual lever semantics in the original body: keepalive on t3 prevented t3's death before h[0]/h[1] computations; keepalive on off prevented off's death. Both produce score 0. In w2 (off kept) t3's live went 18?? Let me re-examine: maybe in w2 the pseudos are renumbered so r77 is not t3. Let me diff the lreg dumps to identify pseudos. The .lreg dump has the register numbers with sets. Let me grep for "t3" no. Let me look at w1.lreg and w2.lreg around the loads.

Actually simpler: alloc_table prints "blk 0" only; the pseudos are RTL reg numbers. I can find in .lreg which reg corresponds to which C variable via the .combine or .cse dump comments? cc1 -dl dump shows insns with register numbers. Let's grep the lreg dump for "(reg" lines? The dumps are textual. Let me look at a piece.

---
ts: 2026-11-06T08:41:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_P0p94EV10w63dWxVjasv
---
In w2: r72 → reg 6 (a2), r77 → reg 7 (a3), r78 → 3 (v1), r79 → 4 (a0), r84 → 2 (v0), r74 → 3 (v1), r75 → 4, r76 → 5.

The difference: w2 has r77 with 3 refs / 18 insns — that's `off`! Because the keepalive `"r"(off)` adds a use, making off 3 refs? No — off is used in 5 loads. Hmm, r84 has 7 refs (off*4 used in 5 addresses + ...). Wait r84 = the address temp (sll result) used 5 times + ... 7 refs.

Let me map by reading the RTL: in w2, r77 might be off (used in 5 address computations = 5 refs, not 3). Hmm.

The local-alloc "Register N in M" lines give hard regs. r77 got a3. In w1, r77 (t3) got a2. In w2, r77 has 3 refs/18 insns. That looks like a different variable than w1's r77 (t3, 2/5). Pseudo numbering shifted because the asm added an operand reg.

In w2: r72 a0 copy (5 refs, 30 insns, pointer) → a2. r79 (2/7, pointer) → a0. r77 (3/18) → a3. Which C var is r77 (3 refs/18)? Perhaps `off`: off used 5 times... no. Or the keepalive's operand pseudo: `"r"(off)` uses off once more. If off is used 5 times + 1 = 6.

Hmm, what has 3 refs? t3? No, t3 has 2 refs.

Wait — maybe the asm changed cse: with the asm present, `off` can't be propagated? In w1, off was folded into the address computation (r84 = off*4 with REG_EQUAL mult). In w2 the asm forces off to be materialized in a register (r77?) and used at the asm, extending its live range: 3 refs (def + asm use + ...). Actually the load addresses use off*4 (r84), computed from a1 directly.

OK the mechanism: with the asm, off gets a real register and long live range; that pseudo (r77, 3 refs/18 insns, pri 1666) sits in a2/a3 space and takes a3 AFTER r72 takes a2? No: local-alloc order: priorities: r84 11666 (v0), r78? Let's list w2 priorities from alloc table: r84 11666, r82/83/92/95/98 10000 (2/2), r78 5000 (2/4), r91/94/97 5000, r75/76 4000 (2/5), r72 3333 (5/30), r90/93/96 3333, r79 2857 (2/7), r74 2000 (2/10), r77 1666 (3/18).

Wait, alloc table showed r78 v1 5000? In the table lines: r78 v1 5000, r91 v1 5000... Actually w2 alloc table line 9: r78 v1 5000 2 4. Yes.

So local-alloc order: r84 (11666) v0; r82 (10000) v0? Hmm r82 got v0 in the table but conflicts? Different live ranges allow sharing.

The a0 copy r72 (3333) is global, assigned after local-alloc. Local-alloc gave: t4 (r78, 5000) v1? Table says r78 v1. Hmm target wants t4 in v1 — yes! Then r75 a0, r76 a1, r77 a3, r74 v1... and r79 a0.

So in w2, r77 (the off pseudo, 3/18) got a3, leaving a2 free for the global a0 copy. In w1, r77 (t3) got a2, leaving a3 for the copy.

So target requires a *third* caller-saved-reg pseudo with priority above the a0 copy but below t1/t2, occupying a3, so that a2 remains for the a0 copy... wait no: local-alloc assigns in priority order: t4(10000)→v0? In w2 t4 r78→v1 because r84 took v0. Then r75(4000)→a0, r76(4000)→a1, then next is r72? No, r72 is global (not local-alloc). Local-alloc next: r77 (1666)? But before that, are there other locals with pri between 4000 and 1666? r90..r98 are the HI pseudos (2/6 = 3333, 2/4 = 5000). Those get v0/v1. Then r77 1666: local-alloc tries to assign it a reg; it got a3. Why a3 and not a2? Because of its register preference! The asm `"r"(off)` has no preference. Hmm.

Local-alloc assignment order in gcc 2.7.2: `local_alloc` sorts qty by `qty_cmp` (bigger first), then for each tries `reg_preferred_class`, then `reg_alternate_class`, and uses `qty_phys_reg` from preferred reg or `reg_alloc_order`. The allocation order among GR_REGS follows `reg_alloc_order` which is built by `regclass`... typically the order of the hard regs by how good (low cost), which for GR_REGS is v0,v1,a0,a1,a2,a3,t0... Hmm.

But in w2, r77 got a3 while a2 was free? That can't happen if regs are tried in order v0,v1,a0,a1,a2,a3 — it would take a2. Unless a2 was NOT free at that point because r72 (global) was already... no, local-alloc runs first.

Unless r77's preferred class is not GR_REGS. Hmm, "Register 77 used 3 times across 18 insns in block 0; GR_REGS or none."

Wait, maybe I misread which pseudo got a2. The ";; Register 72 in 6." lines are local-alloc's assignment of ALL pseudos including those it doesn't allocate? In gcc's dump, local-alloc prints ";; Register N in M." for pseudos it assigned. But r72 is global (crosses calls) — it may still print an assignment from `reg_alloc_order`? Hmm.

Actually maybe in w2, local-alloc assigned r72→a2 as well because with the asm, r72 becomes LOCAL (the asm is not a call, so "crosses calls" doesn't apply). Both w1 and w2 single block; the "crosses 3 calls" line at the end of w1 dump was the global dump for the TU maybe. Hmm.

Let me stop reverse-engineering and instead search empirically over plausible source variants. But time budget. Let me reconsider the whole approach: maybe there's a simpler real-C trick that reproduces the keepalive's *effect*: the asm makes `off` a register-allocated pseudo with a long live range (r77 3/18 in w2). We can get the same by using off later in a real computation whose result is used but costs no insn... 

Idea: `sp10[4] = *(s32 *)((char *)&D_801A5470 + off);` — uses off. What if we compute h[0..2] first, then the fifth load, so off is live across the h updates? Then off's live range extends naturally, and the load order may still be sched1'd to target (the fifth load at insn 24 in target, before h updates). But sched1 might move it. However the asm-free version would have off live from the first load to the fifth, which is already its range (first use to last use = all 5 loads). In target, off's live range is the 5 loads, no more.

Hmm, but w2's r77 (3 refs, 18 insns) — 18 insns span! off spans from insn ~? to the asm after h[1]. That's the asm's effect.

So we need a real C use of off after h[1]. Is there any? The target's instruction stream has no use of off after the fifth load. So a real C use would add instructions... unless it's a use that the compiler folds into an existing instruction (e.g., a use as an address operand that's already there). No.

Alternative: get the same allocation by another route — extend t3's live range in the *pre-sched1* RTL such that sched1 still emits target order. In c1, moving the store after the load gave 46 insns (lost one) — maybe because sched1 couldn't fill a delay slot? Let me look at the c1 diff more closely: which insn was lost? Compare listings: c1 mine has 46 insns, target 47. Let me diff the two listings. Actually let me look at the whole c1 listing vs target. The head showed same start. Let me see the tail.

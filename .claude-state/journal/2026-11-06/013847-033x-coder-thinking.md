---
ts: 2026-11-06T08:38:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MT7MvJtOTPol9PKZpJnW
---
Mapping in w1:
- r72 = a0 param copy (used 5 times, live 27) — yes, used at insn 67, 76, and more.
- r74 = t0 (load from 0x460), r75=t1, r76=t2, r77=t3, r78=t4. r84 = off*4? Actually r84 = off*4 (the address temp, pri 12000). off itself: r73 (mult 20) was cse'd; r74 is t0.

Wait: r72 is a0 copy: live 27, used 5 times.
r77 = t3: 2 uses, live 5.
r78 = t4: 2 uses live 2.
r74 = t0: 2 uses live 10 (from insn 24 to 42? live length 10 counted in insn slots).
r75,r76: 2/5.

Priorities: r74 2000 (2/10), r75 4000 (2/5), r76 4000, r77 4000, r78 10000 (2/2), r72 3703 (5/27).

Allocation result in w1: r78 (t4) got v0 (highest pri), r75→a0, r76→a1, r77→a2, r72→a3. Wait table showed r75 a0, r76 a1, r77 a2, r72 a3. And r74 (t0) got v1. So order by priority: r78 v0 (10000), then r75,r76,r77 (4000, tie broken by lower allocno: r75 then r76 then r77 → a0,a1,a2), then r72 (3703 → a3), then r74 (2000 → v1).

Target: a0 copy in a2, t3 in a3, t4 in v1, t0 in v1?? Target: lw v1,0(at) for t0; lw a0 for t1; lw a1 for t2; lw a3 for t3; lw v1 for t4. Hmm target's t4 got v1 too? Both t0 and t4 in v1 (different live ranges). And t1 a0, t2 a1, t3 a3, a0-copy a2.

So target allocation: r78 (t4, pri 10000) got v1? No wait, in target t4 got v1 (sw v1,32(sp)). And a0 copy got a2 (pri 3333 in w2). Hmm. In target, who got v0? The address temp r84 (off*4) got v0 (sll v0). Yes r84 pri 12000 → v0. Then r78 (t4) pri 10000 → next available. But target t4 = v1, not a0. So global alloc order isn't simply priority descending across all; GR_REGS allocation picks by allocno_compare order but prefers... hmm, actually global.c assigns in order of allocno_compare (priority) but registers are tried in order of `reg_preferred_class` / allocno's own preference? The hard-reg assignment picks the first free register in the order of the register set (0..31 order): v0=2, v1=3, a0=4, a1=5, a2=6, a3=7, t0=8...

For r78 (t4): r84 took v0; next in order is v1 free → v1. Yes! For r75 (t1): after v0,v1 taken, next free is a0 → a0. r76 (t2) → a1. r77 (t3) → a2. r72 (a0 copy) → a3. That matches w1 exactly.

Target: r84→v0, r78→v1, r75→a0, r76→a1, then a0 copy → a2, then t3 → a3, and r74 (t0) → v1? But v1 is taken by t4 (r78). Hmm, t0's live range (24..42) overlaps t4's (56..59)? No overlap, so r74 can reuse v1. But allocation order: r74 pri 2000 is last, and by then v1 freed? Global alloc doesn't do that (local-alloc assigns caller-saved short-lived pseudos). Actually r74..r78, r90..r98 are local pseudos assigned by local-alloc; global alloc assigns r72 (a0 copy, referenced across blocks?) Hmm, but it's a single block.

Hmm. In gcc 2.7.2, local-alloc runs before global-alloc; local-alloc assigns pseudos local to one block (all here), global-alloc assigns the rest. The a0 copy r72 is live across... the call? No call in this function except at the end (func_8012C51C). r72 live from insn 4 to the call at end.

Wait, in the alloc table the a0 copy got a3 in w1 (global alloc), and the local ones (r74-r78) got v0,v1,a0,a1,a2. So local-alloc assigned t4→v0 (pri 10000), t1→a0, t2→a1, t3→a2, t0→v1 (via local-alloc's own ordering). Then global alloc assigns r72 → a3 (only a3 left among caller regs? t0..t7 are also GR_REGS, but global alloc prefers... hmm, why not t0? maybe because r72 is a pointer and pref class GR_REGS; the order: it picks a3 because registers are tried in some order and t regs are not preferred? allocno_compare order and `reg_alloc_order`... The point: target has a0 copy in a2 and t3 in a3.

In w2 (off keepalive): priorities: r84 11666 (v0), r78? table lists r75 a0 4000, r76 a1 4000, r72 a2 3333, r79 a0 2857, r74 v1 2000, r77 a3 1666. So r77 (which pseudo?) pri 1666 with refs 3 live 18 — this is likely `off`? No... off is used 5 times. Hmm refs 3 live 18. The keepalive asm on off: off used 5 times in loads + 1 asm = 6 refs. Hmm.

Actually in w2, `off` might have been substituted/kept in a register with 3 refs. Let me look at w2's lreg register list instead. Let me grep "Register .* used" from w2 lreg section.

Hmm, this is getting deep. Let me instead directly search candidate real-C variants empirically. The wall clock budget is 20-30 min per item; we have 3 items and no time to over-analyze. The scoring loop is ~1-2 s per candidate.

Candidate ideas for item 1:
A. Move `sp10[3] = t3;` after t4 load.
B. Reorder stores/loads.
C. Use `off` again in the h[] computations via pointer arithmetic that doesn't change code: e.g. `h[0] = h[0] + ...` where h = (u16*)sp10 — could instead write `sp10[0] += ...`? That changes addressing? h[0] and sp10[0] are the same; the target uses sp-relative addressing for both.

D. Extend off's live range by using it in a real expression folded away, e.g. `sp10[4] = *(s32 *)((char *)&D_801A5470 + off);` — already.

E. Compute the fifth load using `off` after the h updates? No.

F. Change t3's death by using t3 for h[3]?? No.

G. Use a pointer for the record instead of a0: not allowed? pointer reuse is a real C move.

H. Raise a0-copy priority: refs up. Could compute the lhu via the a0 copy... already. What if h[1] uses `CAST_ALIAS(u16, (s32)a0, 0xA)` — this creates a separate cast pseudo? Actually the cast is folded.

Let me just try A and a few reorderings and score them.

Also try: declare `s32 t0,t1,t2,t3,t4;` vs separate declarations; init at decl; scopes.

Actually a cleaner idea: since either keepalive alone works, the mechanism may simply be that the asm forces `off` (or t3) to be live, which affects local-alloc priority ordering enough. Real C can extend t3's live range by making its store later — that's exactly the "statement order" move. Let me try A.

Also try variant: load t4 before the stores (i.e., all 5 loads then stores) — that extends t3's live to 6+ and also t0..t2.

Let me generate candidates and score them in one sc.sh call.

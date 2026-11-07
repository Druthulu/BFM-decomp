---
ts: 2026-11-06T08:43:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bToDSyNpECOAy5AKYbKw
---
reg_live_length counts insns where the reg is live (one per insn in the live range), i.e., the number of insns in [birth, death] that the reg is live over. For r74 (t0): live 10 means the pseudo is live across 10 insns. The load at insn 24, store at 42: the reg is live from after insn 24 to insn 42 → live over insns 29,34,39,42 plus the set insn 24 = 5? Hmm, 10 suggests notes count too (insn numbers are not consecutive).

Let's compute: live_length increments once per insn where the reg is live at some point. Between 24 and 42 inclusive, all insns (including notes at 29? no notes are uids). UIDs 24..42 = 19 insns. Not 10.

Hmm wait, maybe r74 is not t0. Let me re-map: insn 24 sets r74 from D_801A5460. t0's store at insn 42 (sp+16). So r74 live from 24 to 42 = 19 uids. The table says live 10. Hmm.

Unless local-alloc's "across N insns" uses `qty_death - qty_birth` where birth/death are the insn *numbers* from the sched1 sequence? No...

Let me just print what the dump says: "Register 74 used 2 times across 10 insns in block 0". Hmm. Let me count actual machine insns in the final listing between lw v1,0(at) (insn 10 of listing, t0) and sw v1,16(sp) (insn 27): that's 17. No.

Wait — maybe I have the mapping wrong: maybe r74 is not t0 but `off*4` (r84) or `off`. Let me look at insn 24's set: (set (reg/v:SI 74) (mem ... D_801A5460)) — that IS t0. Death at insn 42 (store). Hmm.

Maybe the dump's "across 10 insns" refers to the count of insns in the *live range excluding notes*, computed by local-alloc as `qty_death - qty_birth` where birth/death are "insn numbers" assigned by sched1 (which numbers only real insns)? Then between insn 24 and 42: real insns at uids 24,29,34,39,42 = 5. Not 10.

I'm burning time. Let me instead use the alloc table numbers as the ground truth (they're derived from the dump) and just try to manipulate via source.

Alternative strategy: maybe we can make t3's pseudo die and be reloaded... no.

New idea: instead of t3 and t4 being separate temps, use the same temp for both (t3 = load; store; t3 = load; store). Then the pseudo's refs = 4, live = ? This changes nothing in code but the pseudo for t3/t4 would be a single pseudo: refs 4, live from first load to last store. pri = 2*4/live. If live ~14 → 5714? That could change allocation of the last two loads: they'd share a register. Target has t3 in a3 and t4 in v1 — different regs, so they can't be the same pseudo. No.

What about using a temp for the address computation `off*4` differently?

Hmm, let me reconsider: the target's t4 is in v1, same as t0. In w1, t4 is in v0 and t0 in v1 (swapped). Target: t0 v1, t4 v1. Mine w1: t0 v1 (insn 10 lw v1), t4 v0. Wait w1 listing: lw v1 (t0), lw a0 (t1), lw a1 (t2), lw a2 (t3), lw v0 (t4). Target: lw v1 (t0), lw a0 (t1), lw a1 (t2), lw a3 (t3), lw v1 (t4).

So only t3 and t4 differ in the loads: mine t3=a2, t4=v0; target t3=a3, t4=v1. And a0-copy mine a3, target a2.

Priorities: t4 r78 = 10000 → first pick → v0 in mine (v0 free). In target t4 got v1! That means in target, v0 was taken by something else when t4 was allocated: r84 (address temp) pri 12000 > 10000 → v0. In w1, r84 also has pri 12000 → v0. Then t4 (10000) → v1? But mine gave t4 v0. Wait mine listing: sll v0 (r84), lw v1 (t0), ..., lw v0 (t4). The last load lw v0,0(at) then sw v0,32(sp). So t4 got v0 — but r84 (address temp) is dead by then (its last use is the address computation for the last load: addu at,at,v0 then lw v0,0(at)). So local-alloc can give t4 v0 because their live ranges don't overlap (r84 dies at the lw, t4 born at it). Hmm, then why did t0 get v1 and t4 v0? Because t0 (r74) live range overlaps r84, so t0 can't take v0, takes v1.

In target, t0 = v1 and t4 = v1 too (same register at different times). So t4 got v1, not v0. Why? In target, at the point t4 is allocated, v0 is... r84 is dead after the last load, so v0 should be free. Unless in target the address temp's live range extends past the last load (e.g., v0 used for something else). In target listing: after `lw v1,0(at)` (last load), there's a nop, then sw v1,32(sp). v0 is used later at lhu v0,16(sp) etc. So v0 is reused for the h updates. If the address temp (r84) is dead at the last addu, v0 is free.

But local-alloc allocation order: t4's pri is 10000 (2 refs, live 2). It would be allocated FIRST (before r84 12000? no, r84 12000 first). Hmm r84 pri 12000: refs 7? 7 refs → floor_log2=2, 2*7/live*1e4 = 14000/live; if live 12 → 11666 (w2) or live 10 → 12000? w1 table: r84 pri 12000 refs 6 live 10. w2: 11666 refs 7 live 12.

So r84 gets v0. t4 (r78, 10000, 2 refs live 2) next: tries v0 (taken? r84's live range overlaps t4's? r84 is live from insn 17 to the last load (insn 56), and t4 at 56-59; they overlap at 56? The last use of r84 is insn 56 which also defines t4 — overlapping means r84 dies in insn 56, so they conflict at that insn; local-alloc's qty_phys_reg conflict rules: a reg dying in an insn conflicts with a reg being born in the same insn? In local-alloc, `regs_set_between`/`reg_is_set`... a pseudo that is set in an insn conflicts with pseudos dying in that insn (output/input overlap). So t4 can't take v0 at insn 56; it takes v1. But in w1 mine, t4 DID take v0 (lw v0,0(at)). Hmm, contradiction.

Unless in w1 the last load is not at insn 56 but later, after r84's death. The .lreg dump w1: insn 56 sets r78 (t4) from mem (plus r84 ...), and r84 is REG_DEAD in that insn (line 23876). So t4 and r84 overlap at insn 56 → t4 shouldn't get v0. But the final code shows t4 in v0 and the last address computed in v0 too (addu at,at,v0; lw v0,0(at)). Wait the address temp at the last load is $at? No: `addu at,at,v0` — v0 holds off*4, at holds the address. The `lui at`/`addu at,at,v0` computes at = HI + v0. So v0 = off*4 (r84) is an input to the addu at insn 55, and the lw v0,0(at) at 56 defines v0=t4. The addu (55) and lw (56) are different insns, so r84 dies at 55, t4 born at 56 → no conflict. 

But the .lreg dump (pre-sched1?) showed r84 dead in insn 56. Hmm, that's the lreg dump: insn 56 = (set (reg/v:SI 78) (mem:SI (plus:SI (reg:SI 84) (symbol...)))) with REG_DEAD r84. So in the RTL at local-alloc time, the load address uses r84 directly (plus r84 symbol_ref) — the lui/addu split happens at reload. So r84 is live until the load insn 56 and dies in it. t4 is set in insn 56. Local-alloc: a register set in an insn conflicts with registers live at the *start* of that insn, but a register dying in the same insn... The rule: if a pseudo is set in insn and another dies in insn, they conflict only if the dying one is used in a way that... In local-alloc.c `reg_is_set` and `regs_set_between`: an insn that sets a reg conflicts with all regs live across it, and the dying reg is not live after, but the standard rule in local-alloc: "we cannot assign the same hard reg to a pseudo set in an insn and a pseudo used as an input in that insn" — the dying input conflicts with the output (they're both "used" in the insn). Actually `qty_phys_reg` conflicts are recorded via `regs_live_at` masks; `mark_reg_live` etc.

But empirically w1 gave t4 = v0 and the address temp = v0, so they were allowed to share. OK.

So in target, t4 got v1. Which means at t4's allocation, v0 was unavailable or preferred v1. Since target's a0 copy is in a2 and t3 in a3, and t4 in v1, maybe t4's allocation happened after something took v0. What if t0's live range in target extends further, keeping v1... no.

Hmm, target = w2 = the same code but with an extra pseudo (off, r77 3/18, pri 1666) that took a3. The register dispositions in w2: 72 in 6 (a2), 74 in 3 (v1), 75 in 4, 76 in 5, 77 in 7, 78 in 3, 79 in 4, 84 in 2, 90 in 2, 91 in 3, ...

So in w2: r78 (t4) got v1 (3), r74 (t0) also v1 (3). And r77 (off pseudo) got a3 (7). r72 got a2 (6). r79 got a0 (4).

So the asm forced `off` into its own pseudo r77 that took a3, freeing a2 for the a0 copy... but local-alloc order: r72 (3333) comes before r77 (1666). r72 took a2 (6). Then r77 (1666) took a3 (7) — because a2 was taken by r72! So the order changed because r72's priority became 3333 (from 3703) and... in w1, r72 was 3703 and r77 (t3) 4000. In w2, r72 3333 and the competing r77 (off) 1666.

So the *only* thing needed: a pseudo in the a2/a3 neighborhood with priority below r72's (3703), allocated after r72, so r72 takes a2 and the other takes a3. In w1, t3 (4000) is above r72. If we could get t3's priority below 3703, it'd work: t3 (2 refs) needs live ≥ 6.

Alternatively, add a real pseudo with low priority (like off's 1666) that lives across a2/a3 region and takes a3 after r72 gets a2 — but the pseudo must be created by real C without adding instructions. In w2, the off pseudo exists because the asm forced it. Real C: force `off` to be materialized in a register by using it in a context where it can't be folded: e.g., use off in a comparison or computation whose result feeds an existing insn. 

Hmm! What if we compute the address as `*(s32 *)((char *)&D_801A5470 + off)` — that's a symbol+reg address; off is folded into the address computation. The asm forced off to be a real value.

Real C idea: compute the five loads via a pointer that starts at `&D_801A5460 + off` and increments by 4? That changes the addressing (target uses at-relative lui/addu per load). Hmm, but maybe the same code results: target does `lui at; addu at,at,v0` for each load with v0 = off*4, then lw offset 0. If we write a pointer `p = (s32*)((char*)&D_801A5460 + off); t0 = p[0]; t1 = p[1]; ...` — p[1] would be 4(p) addressing, not matching target's 0(at) per load. No.

What about computing off*4 into a variable: `off = a1 * 20;` then loads via `(char*)&D + off`. The compiler creates r84 = off*4 as a separate temp (CSE). Fine.

Real C that keeps `off` live: use `off` after the loads in a real statement that gets optimized away but leaves the pseudo's live range... e.g., `if (off) { }`? flow might keep a test (adds insns). `sp10[4] = t4; off = off;` self-assignment deleted by cse? cse deletes `off = off` (it's a no-op set? cse2's `cse_insn` may remove a self-set). Hmm, that's like a launder (identity statement) — explicitly disallowed as a crack: "identity-statement launders do NOT count as a crack".

So we need genuine C.

Real C option: move the fifth load AFTER the h[] computations, using off there:
```
    h[0] = h[0] + ...
    h[1] = ...
    t4 = *(s32*)((char*)&D_801A5470 + off);
    sp10[4] = t4;
    h[2] = h[2] + ...
```
This extends off's live range naturally across h[0]/h[1] (the asm did that) — but does it change the emitted order? Target order has the fifth load before the h computations. sched1 might move the load up? The load has no dependency on the h computations, but it must be before the call; sched1 could reorder. But the load's result is used by sp10[4] = t4 which must precede the call (func_8012C51C reads sp10). Also the h updates store to sp10[0..2], and the call reads them: anti-dependencies. Hmm, target's order: t4 load at insn 24, sw t4 at 26, then h updates. sched1 ordering would need to hoist the load above the h stores — possible since no dependency.

But wait: does off stay live across h updates in that source? Yes: off's last use is the t4 load, which now sits after h[0],h[1]. If sched1 hoists the load back to target position, then off's live range in the *pre-sched1* RTL is what matters for local-alloc? Local-alloc runs AFTER sched1? The .lreg dump order matched final order, so sched1 runs before local-alloc. If sched1 hoists the load, off's live range shrinks again. Hmm, but maybe sched1 keeps it. Try it.

Let me just try several candidates:
c3: move t4 load + store after h[0],h[1] (before h[2]).
c4: move t4 load+store after all three h updates (before call).
c5: move t4 load before h[0] but store after h[1].

Let me write them and score.

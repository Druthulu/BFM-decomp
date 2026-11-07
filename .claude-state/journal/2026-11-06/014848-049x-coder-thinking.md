---
ts: 2026-11-06T08:48:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FRArEL4R01WPl3RiRjB7
---
Not it — the register allocation shifted (t0's long pseudo took v1 but then others shifted). And the nop missing again.

Hmm. Let me reconsider. The missing `nop` after the fifth load appears whenever the fifth load's result register differs? In w1 (score 9) the nop was present; in d1 and c1 it's missing.

What is that nop? In target: lw v1,0(at); nop; sw v1,32(sp). A nop between load and store — that's a load-delay nop (the store uses the loaded value immediately, so a nop is inserted). Normally mips.md handles load delay by inserting a nop when the load result is used in the next insn. So the nop exists when the store immediately follows the load. In mine (w1): lw v0,0(at); nop; sw v0,32(sp) — same. In d1/c1, the sequence became lw a3,0(at) then ... something else, then sw.

OK. Let me step back and think about which real C makes BOTH:
(a) a0-copy → a2, t3 → a3
(b) t4 → v1 (v0 held across the fifth load by the address temp)

Observation: both effects come from extending live ranges across the h-update region:
- t3 live across h[0], h[1] (the asm position).
- r84 (address temp) live across the fifth load.

What if we restructure so that the *fifth load* uses a pointer computed once and the h computations use t3? no.

Alternative: compute the fifth value using t3? No.

What about moving the fifth load BEFORE the stores (c2 tried: 46 insns, score 16).

Let me think about the target's RTL more concretely. Maybe the real C source is:

```
void func_8017F6B0(void *a0, s32 a1) {
    s32 sp10[5];
    u16 *h;
    s32 off = a1 * 20;
    s32 t;

    t = *(s32 *)((char *)&D_801A5460 + off);
    sp10[0] = t;
    t = *(s32 *)((char *)&D_801A5464 + off);
    sp10[1] = t;
    t = *(s32 *)((char *)&D_801A5468 + off);
    sp10[2] = t;
    t = *(s32 *)((char *)&D_801A546C + off);
    sp10[3] = t;
    t = *(s32 *)((char *)&D_801A5470 + off);
    sp10[4] = t;
    h = (u16*)sp10;
    ...
}
```
Single temp reused for all five loads! Then the pseudo spans the whole load/store sequence: refs 10, live ~25 → pri = floor_log2(10)=3, 3*10/live. With live ~25: 1.2? Hmm 3*10/25=1.2 → 12000. That would be allocated early. The target has five different registers (v1,a0,a1,a3,v1) — so not a single pseudo. Unless the stores interleave such that each pseudo's live range is short: with the pattern load→store, load→store, each pseudo lives 2 insns (pri 10000), and all five could get... they'd each take v0/v1/a0/a1/a2. Target uses v1,a0,a1,a3,v1. Hmm, that's possible if allocation order and conflicts differ.

Actually! If the source is load-store pairs (each temp used immediately), the temps are 5 separate pseudos with live 2, pri 10000 each, allocated in qty order: t0→v0? But target has t0 in v1. And the store order in the target is all four stores after the four loads — sched1 reorders the stores after the loads (to fill load delay). So source could be load/store pairs; sched1 hoists the stores? sched1 can reorder them. Then the live ranges at local-alloc time (after sched1) would be as in the target: t0 live from load 24 to store 42 = 5 insns.

Hmm, that's the same as our current RTL. So no change.

OK here's another thought: what if the address temp r84 in the target is kept live across the fifth load because the fifth load's address uses it and the store of t4... no.

Let me look at the target's actual instruction scheduling: `lui at; addu at,at,v0; lw v1,0(at); nop; sw v1,32(sp)`. The nop suggests the load is followed immediately by the dependent store. r84 (v0) is dead at the addu (insn 23) — actually v0 is used by addu at insn 23, then lw at 24. So v0 is free at insn 24 for t4. Yet t4 is v1. So allocation didn't give t4 v0 even though it's free. That means at local-alloc time, v0 was *not* free at t4's allocation: something else occupied v0 across t4's range. What? r84's live range extends past insn 56 only if off is used later. In the target, off's last use is the fifth load's address (insn 24 in final code). Unless the target's pre-reload RTL has off live longer.

Alternatively t4's allocation was influenced by a *copy preference*: e.g., if the source stored `sp10[4] = t4` where sp10[4]'s location... no.

Or t4's pseudo had a preference for v1 from a copy: if the source wrote `t4 = t0;`? no.

Hmm, what about the possibility that the fifth load's result is not a separate temp but the same C expression as t0's store target, causing a copy preference to v1? For example:

```
sp10[4] = *(s32 *)((char *)&D_801A5470 + off);
```
A memory-to-memory assignment goes through a temp with no preference.

What if the source reuses t0 (d1)? That gave t4=v1 but shifted everything.

Let me look at d1's allocation more carefully; maybe a small variation (reuse t0 for the fifth load AND extend t3) would work. Actually d1's diff shows:
mine: lw a1,0(at); sw a3,16(sp); sw v1,20(sp); sw a0,24(sp); sw a1,28(sp); lw a3,0(at); sw a3,32(sp)
target: lw a3; sw v1,16; sw a0,20; sw a1,24; sw a3,28; lw v1; nop; sw v1,32

So in d1: t0 (spanning) got v1 (lw v1 first at insn 10?), t1→a0, t2→a1, t3→a3, and the fifth load (same pseudo as t0) got a3?? That's wrong: the fifth load should use the same reg as t0 (v1). It shows lw a3,0(at) then sw a3,32(sp) — so the fifth load got a3, meaning the pseudo was NOT shared; gcc created a new pseudo because the assignment `t0 = ...` after t0's death... but cse may have renumbered. Whatever.

Let me try yet another angle: keep the fifth load's temp as t4 but make the address expression use a separate variable `p`:

Actually, let's revisit the idea that the target's `nop` after the fifth load is a load-delay nop, and t4=v1 because the store `sp10[4] = t4` was written with t4 = the SAME pseudo as something in v1... 

Hmm, let me look at what happens if I reuse t1 or t2 for the fifth load (a0 or a1). Target's fifth load is v1 = t0's reg. So reuse t0.

In d1, why didn't the pseudo merge? Because the second `t0 = ...` set creates a new value; gcc's SSA-less RTL: the pseudo t0 has two sets; local-alloc treats it as one pseudo with refs 4 and live span from first set to last use. But the dump shows the fifth load in a3 — so it was a different pseudo. That's because sched1/reload split? Or because the C compiler's expand created a new temp for the second load and assigned it to the variable t0, but cse... Actually in RTL, `t0 = expr1` then later `t0 = expr2`: the pseudo t0 is one register with two sets. But the first store `sp10[0] = t0` uses the first value; the second store uses the second. One pseudo. Local-alloc can't assign two different hard regs to one pseudo... but the final code has different regs (v1 for first, a3 for second). So gcc must have split the live range: local-alloc's `regno` can be assigned one hard reg, but if a pseudo's live range has two disjoint parts with different conflicts, it still gets one reg. Hmm, but the emitted code shows a3 for the second — unless the second load is a different pseudo because the C variable assignment `t0 = ...` after the first `sp10[0] = t0`... no, same variable = same pseudo.

Unless combine/cse replaced `sp10[4] = t0` with a direct memory copy and the load result got a new reg. Ugh.

Let me take yet another step back. The budget is 20-30 min per item; I've spent ~25 min on item 1 already (started 01:30, now ~01:55?). Let me check the time.

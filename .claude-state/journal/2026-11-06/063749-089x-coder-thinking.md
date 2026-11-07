---
ts: 2026-11-06T13:37:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nB1PwxW8C9V4OmyeaF3k
---
The real difference: 
- Target: `mult v0,s2; mflo t0; sra v0,t0,0xc; addiu a2,v0,8;` then load D_80126950 into v0, addiu, `mult a2,v0`.
- Mine: `mult v0,s2;` then the D_80126950 load into v1 (in the mflo's delay slot region), `mflo t0; sra...; addiu a2; mult a2,v1`.

So mine hoisted the D_80126950 load ABOVE the mflo (filling the mult's latency slot), and used v1 instead of v0. The target keeps the load after the sra/addiu.

The barrier in the source is between `cc = bb + 8;` and `d = cc * (D_80126950 + 500);`. Removing it lets sched1 hoist the load into the mult/mflo latency gap.

So we need to keep the load after the `addiu a2,v0,8`. The load's address is a constant (D_80126950). It has no deps. sched1 hoists it to fill latency.

Wait, actually the target order: mult; mflo; sra; addiu; lui; lw; nop; addiu; mult. The load is after. Mine: mult; lui; lw; nop; addiu; mflo; sra; addiu; mult. So mine fills the mflo latency (mult takes 4 cycles) with the load chain. The target does NOT fill it (it has mflo right after mult, which is a stall!). Hmm, that's odd — the target has `mult v0,s2` then `mflo t0` immediately (mult latency ~4, so a stall), whereas mine fills with the load.

The barrier prevented sched1 from moving the load above it. So we need a real-C construct that keeps the load after the sra/addiu.

Idea: make the load *depend* on cc! E.g., `d = cc * (D_80126950 + 500);` — the load doesn't depend on cc. If we write it so the address computation depends on cc... e.g., `d = cc * (D_80126950 + 500 + 0*cc)`? fold.

Hmm. Alternatively, since the load is from a global, what if we make the read *volatile*? Then sched1 can't move it across other volatile ops but can still hoist it within the block? Volatile memory ops in sched are not reordered relative to other memory ops. The mult/mflo are not memory ops. Volatile wouldn't stop it.

What if we make the load depend on the division? No.

What about using a temp: `s32 g = D_80126950 + 500; d = cc * g;` — same.

What if we reorder the source: put the load BEFORE the mult? Then it'd be earlier — worse.

Hmm, the barrier is `__asm__ __volatile__("")` — a full scheduling barrier. What real-C construct orders the load after the sra?

Think about sched1's priority: the load chain (lui/lw/nop/addiu) is scheduled early to fill the mult latency. To prevent, the load must not be "ready" early: make its address depend on something produced late. The address is `&D_80126950`. If we compute the address via a pointer variable that is assigned late... e.g.:

```
s32 *gp = &D_80126950;   // early
...
d = cc * (*gp + 500);
```
The load `*gp` still has no dep on cc.

What if the pointer is computed from cc? e.g. `s32 *gp = (s32 *)((u8 *)&D_80126950 + (cc & 0));` — fold.

What if we use a *union/struct alias* so cse... no.

Hmm. What if the load is written to depend on cc through a conditional? `d = cc * (cc ? (D_80126950 + 500) : 0);` — cc is always nonzero? gcc may not know. This adds a branch.

What if `d = (D_80126950 + 500) * cc;` — same.

What if the multiply is written as `d = cc * D_80126950 + cc * 500;`? That's different code (two mults) — no.

Hmm, what about the division: `d = d / (ret * 4);` — the div uses d. 

Let me think about the scheduling: the load chain is 4 insns (lui, lw, nop, addiu). In the target, they're placed after the sra/addiu, right before the mult. The load takes 2 cycles (lw) + nop. The target doesn't fill the mult latency; maybe because the target's sched1 had the barrier.

So the target's source had the barrier. To crack, we need another zero-byte ordering. 

What about a *store* to memory between? It would add code.

What about making the D_80126950 read a *volatile* read? Let me check sched.c's handling of volatile memory: lines 811, 831: `MEM_VOLATILE_P` — in `true_dependence`/`anti_dependence`, volatile mems conflict. But the mult/mflo are not memory.

Hmm, but sched1 has a rule: it won't move a volatile load across a call. Not relevant.

What about making the load part of a longer dependency chain that starts late? E.g., `d = cc * (D_80126950 + 500);` where D_80126950 is read into a variable that is ALSO used earlier... no.

Alternative: maybe the difference isn't sched1 but sched2 or reorg? The load placement could come from sched2. Let me check: is there a way to test which pass? Use cc1 dumps again (sched1 dump). But that costs time.

Let me try some variants first (cheap):
1. temp variable for the load: `s32 gg = D_80126950 + 500; d = cc * gg;` (may change scheduling: the temp's birth).
2. move the `d = cc * (D_80126950 + 500);` earlier/later in source.
3. `d = (D_80126950 + 500) * cc;`
4. `d = cc * D_80126950 + cc * 500;` no.
5. pointer to D_80126950: `s32 *g = &D_80126950; d = cc * (*g + 500);`
6. struct alias for D_80126950.
7. do-while around the load+mult.
8. do-while around the sra/addiu (cc computation).
9. reorder: `d = cc * (500 + D_80126950);`
10. split: `cc = bb + 8; { s32 g = D_80126950; g += 500; d = cc * g; }`

Also, importantly: the barrier is between `cc = bb + 8;` and the d line. The pins aa($8), bb($2), cc($6) are in play. The load uses v1 in mine and v0 in target. The register choice (v0 vs v1) is also part of the diff.

Wait, maybe the issue is different: in mine, the load is hoisted into the mult latency and takes v1 (since v0 is busy with the mult result? Actually v0 holds t for the mult). In target, the load is later and uses v0 (t's reg is free after the mult... but v0 is reused). The register difference follows from the position.

Let me try the do-while and temp variants.

Actually — a thought: what if the load is hoisted because of the *pinned cc*? cc is pinned to $6 (a2). `cc = bb + 8` writes a2. The mult a2,v0 uses a2. The load is independent.

Let me look at the source lines around it in orig.c.

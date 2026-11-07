---
ts: 2026-11-06T12:20:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XvCSk1EuQpUQfaINMZWA
---
Now mine computes vh at 371 into v0 and stores at 82 — too EARLY (before 373). Target has it at 373 into a0.

So now vh is scheduled at the very top (371) but in v0 instead of a0. The allocator still gives vh=v0 and vv2=a0.

So the register assignment is the remaining issue: vh should be a0, vv2 a1.

In h2, the C order puts vh first, and sched1 keeps it first (birth order matters?). But the allocator gives v0.

Since vh and vv2 both need registers at the same time and priority is equal-ish, the allocator's order decides. vv2 gets a0 (assigned first, higher priority).

In the target, vh gets a0. So in the target, vh's priority > vv2's. With the asm, vh has 2 refs (1 set + 1 asm use) vs vv2 2 refs; live lengths similar.

Hmm, but there's also local-alloc: vh might be tied to a0 by local-alloc because the srl's output and the sh's input... local-alloc assigns pseudos whose live range is within one basic block, tying them to preferred registers based on the insns. Since the whole fill is one block, vh's pseudo could be handled by local-alloc, which uses `reg_preferred_class` and the order of definition.

Idea: give vh an extra ref to boost its priority — e.g. use vh twice in a way that costs nothing. What if `v1.vy = vh;` and then `v1.vy = vh;` again? Two stores = extra insn.

What about using vh in the q[0x1D] statement too? That would remove the srl at 340 (one insn less → count mismatch). Unless... hmm, target has TWO srl 0x18's: one at 340 (v1, for q[0x1D]) and one at 373 (a0, for v1.vy). If I use a single temp vh for both, gcc computes it once → 467 insns vs 468.

Unless the first use is written such that cse can't merge them: e.g. `q[0x1D] = q[0x0D] + ((rec & 0xFF000000) >> 24);` — cse would still fold? It'd be srl+? hmm `rec & 0xFF000000` is an andi (lui+andi) — extra insn.

Alternative: give vh's pseudo a higher priority by making it live ACROSS a call or a barrier... no.

Let me think about gcc 2.7.2 local-alloc. `local_alloc` handles pseudos that live within one basic block ("qty_phys_reg" / `local_alloc` tries to allocate them and ties them). The rule: local-alloc assigns based on `qty` needs; for each pseudo, it calls `find_free_reg` with a preference derived from the insn's `REG_N_DEATHS`? In local-alloc, the pseudo is tied to the register preferred by the first use? There's `reg_preferred_class` and `pref` from `PREFERRED_RELOAD_CLASS`... In gcc 2.7.2 local-alloc, `local_alloc_1` computes `qty_phys_reg` and there's the "tie to the register of the insn's operand" mechanism: `REG_EQUIV`/`REG_RETVAL` and `reg_alternate_class`. There's also `update_equiv_regs` and the `qty` loop with `no_equivs`.

Honestly, the empirically effective lever per moves.md for such cases is "buy references instead of a register" (cookbook 419) — i.e. add refs to the value that should win.

So: give vh an extra reference somewhere that costs no instruction. Ideas:
- Use vh in a context where it's the same value: e.g. `v1.vy = vh;` twice? no.
- `q[0x1D] = q[0x0D] + vh;` and ALSO keep a separate `(rec >> 24)` expression at v1.vy: then vh has 2 refs and the second srl is a separate temp (no name) → 468 insns, and vh's live range spans 340→(its store). That's v4-ish but v4 replaced the v1.vy use with vh too. Let me instead do:
  `vh = rec >> 24;` before q[0x1D], `q[0x1D] = q[0x0D] + vh;` and later `v1.vy = rec >> 24;` — this keeps 2 srl's (one for vh at 340, one inline for v1.vy) and gives vh 2 refs. But then the second srl's result goes to v1.vy... target's 373 srl goes to a0 which is stored at 82 (v1.vy). If v1.vy = rec>>24 inline, the srl is born at 378 again. Hmm, but vh (the temp at 340) would have 2 refs and be long-lived — but it's the WRONG value instance (the one used at q[0x1D]).

Wait, actually: could that be exactly what the target does? Target: srl v1,s1,0x18 at 340 → used at 343 (addu for q[0x1D]). Then srl a0,s1,0x18 at 373 → stored at 82. Two separate shifts. So the target computes rec>>24 twice.

So target's a0 value at 373: born at 373, dies at 383. Its live range is 10 insns. vv2: born 376, dies 384: 8 insns.

Mine (h2): vh born 371 dies 372 (very short!) — the store sh v0,82 immediately follows. So sched1 placed the store adjacent. Then vh's live range is 1, giving it a local-alloc candidate (in one block, dies immediately) → allocated locally, maybe to v0.

Target's vh: born 373, dies 383 — long, so global-alloc. That's the difference! In target the srl and its store are NOT adjacent (373 vs 383).

So we need the store to be LATE while the srl is EARLY. In h2 they're adjacent.

In h2 the C has `vh = rec >> 24; v1.vy = vh;` adjacent at the top — sched1 keeps them adjacent.

Target has srl at 373, store at 383. So in C, the vh computation must be early and its store late, with other work between. Which means: vh = rec>>24 (early), then other statements, then v1.vy = vh (late). That's f1/f5 (vh first, store at its position in the original order). f5: 
```
vh = rec >> 24;
v0.vx = ...; vv2 = ...; v0.vy = vv2; v0.vz = sz; vw = rec>>16; v1.vx = vw&0xFF; v1.vy = vh; v1.vz = sz;
```
f5 = 7 with residual: vh's srl at 378 (sunk!) rather than 373.

Hmm, in f5 sched1 sank the srl down to just before its store (378). Because it can.

So we need to prevent sinking while keeping the store late. What pins a computation early in sched1? A use that must happen early. E.g. if vh is used in an earlier statement AND later: `v0.vz = sz;` no.

What if the early use is a real one that costs nothing? Consider: the value `rec >> 24` — is there another place in the function where rec>>24 is used? Yes! q[0x1D] at index 340. But using vh there would remove that srl.

Hmm, unless... the two srl's in target are at 340 (v1) and 373 (a0). If I write:
```
vh = rec >> 24;         // (A) used at q[0x1D] AND at v1.vy
```
gcc computes once, 1 srl total. But if instead I write the q[0x1D] use with the SAME temp but the temp is re-assigned... 

What about: `vh = rec >> 24;` early (before q[0x1D]), use it at q[0x1D], then LATER `vh = rec >> 24;` again (re-assign) and use at v1.vy? Then gcc has 2 srl's (2 assignments, but the second assignment is a separate def of the same pseudo → same pseudo number, still 2 srl insns). Then the pseudo vh is defined twice, live ranges 340→343 and 373→383. Hmm, that's "2 sets" which might affect priority (REG_N_REFS=2 sets+2 uses=4) but the live ranges are what matter.

But wait: does the second assignment create a separate srl? Yes if cse doesn't eliminate it. cse might CSE the two `rec>>24` computations (they're in the same block, rec unchanged... but rec is used in the loop, and there are stores to q between them; cse could still CSE the pure shift since rec isn't modified). cse1 would fold them into one! Unless a store to something cse thinks may alias rec... rec is a local pseudo, not memory, so cse would merge them. Then the second assignment becomes `vh = vh` → likely deleted.

Hmm, but target has 2 srl's, so the original (with the asm) also has 2 — because the C has two separate expressions `(rec >> 24)` and `vh = rec >> 24`... cse doesn't merge them because the second is assigned to a variable? No, cse merges expressions regardless of assignment.

Hmm, actually cse DOES CSE `(rec>>24)` used twice. But target has 2 srl's... Because cse1 runs before sched1 but the loop is involved? The first srl at 340 is inside the loop body; so is the second. Why 2 then? 

Because cse only eliminates a redundant expression when the first computation is still available — it tracks a hash table per basic block, and the value must not be clobbered. Both are in the same basic block (no branches between 340 and 373? There is a branch at 329-333, 355-360). Between 340 and 373 there are branches (beqz at 356) → new basic blocks. So cse (which works per EBB/block) doesn't merge across the branch. 

So if I write `vh = rec >> 24;` before q[0x1D] and use it at v1.vy later, cse can't merge (different blocks) — but then there'd be only ONE srl in the C, at 340. The target has one at 373 too. So no.

OK so: target's structure = two independent `rec>>24` computations, the second born at 373, dead at 383. Between 373 and 383 there are 9 insns.

So: the srl must be born early (373) and the store late (383). In C: `vh = rec >> 24;` early in the group and `v1.vy = vh;` late in the group, with 6 statements between. That's exactly f5/f1. But sched1 sinks the srl to 378 (5 insns later, adjacent to the store).

Why doesn't it sink in the target? Because in the target, the ASM (at 386) uses vh! Wait no, the asm uses vh — so vh must be live until the asm at 386, not just until 383. Hmm, but sched1 sinking is limited by dependencies: the srl must come before both the store (383) and the asm (386). Sinking to 378 is allowed.

Hmm, so why is it at 373 in target? Because sched1 builds the order from the ready list by priority — it's not "sink as late as possible", it's a forward list schedule: at each step, pick the highest-priority ready insn. Priority = length of the longest path from the insn to the end of the block (in the dependency DAG, counting insn latencies). 

With the asm at the end using vh, vw, vv2: the path from the vh srl to the end = srl → (store 383) → ... → asm → end. Hmm.

Let me look at the priority formula in gcc 2.7.2 sched.c: `priority (insn, ...)` computes max over successors of (priority + insn_cost + latency). The asm insn's cost may be high (asm = many cycles?). If the asm has a high latency, then all three computations that feed it get high priority — and among them, vh's chain (srl → asm) vs vw's (srl → andi → store → asm). 

I'm going too deep. Let me instead try the empirical knob: what makes the srl stay at 373? In the target it's driven by the asm's presence at the end. Real-C substitute: an instruction at the end that uses vh... 

What if I add a real (non-asm) use of vh at the END of the group that produces no extra instruction? Like using vh in the last store instead of its own store: `v0.vy = vv2;` — no.

Hmm: what about `v1.vz = sz;` and `v0.vz = sz`... no.

Honest assessment: this is the exact reason the item is a delever target — the asm is load-bearing for a scheduling/priority fact. The moves.md shows such items often end as WALL with tags like "sched1-birth-order", "global-alloc-priority", "greg-pri-refs".

I have 22+ scored tries... let me count precisely: v0(1), v1,v2,v3,v4,v5 (6), f1-f8 (14), g1-g8 (22), h1-h8 (30). Plus v3 rescored. So 30 tries done. Time: ~05:50? Started 05:10, ~40 min. Over budget (20-30 min).

I should do a couple more quick ones then WALL. Actually — one more high-value idea: since the target's vh is long-lived because the asm uses it at the end, maybe I can lengthen vh's life with a real second use at the END: the final `*ot = (*ot & mFF) | ((u32)q & m24);`... no.

Alternative: lengthen vh's life by using it in the loop's NEXT iteration? no.

Wait — actually, what about making vh's store the LAST of the six? I.e. `v1.vy = vh;` last, with the srl at the top. Then the srl's sink limit is the last store, and sched1 might place it at 373. But sched1 would sink it right before its store (last), so it'd be born at ~384, not 373.

Hmm, sched1 doesn't sink; it list-schedules forward. The "sink" appearance is because priority is low. The priority depends on the chain to the END of the block. vh's chain: srl → store → end. If the store is the last insn, the chain is long → higher priority → scheduled earlier! That's a real mechanism.

So: put vh's computation at the top and its store LAST. Then vh's chain to the end is longest → it gets scheduled early. Let me try:

i1: 
```
vh = rec >> 24;
v0.vx = p->unk8;
vv2 = p->unkA;
v0.vy = vv2;
v0.vz = sz;
vw = rec >> 16;
v1.vx = vw & 0xFF;
v1.vz = sz;
v1.vy = vh;     // last
```
i2: same but with v1.vy after v1.vx and v0.vy last:
```
vh = rec >> 24;
v0.vx = ...;
vv2 = ...;
v0.vz = sz;
vw = rec >> 16;
v1.vx = vw & 0xFF;
v1.vz = sz;
v0.vy = vv2;
v1.vy = vh;   // last
```
Hmm target order: ... v1.vx(381), v1.vy(383), v0.vy(384). So v0.vy is last and v1.vy second-to-last.

i3: vh's store second-to-last, v0.vy last (as target), vh computed at top:
```
vh = rec >> 24;
v0.vx = ...; vv2 = ...; v0.vz = sz; vw = rec >> 16; v1.vx = vw & 0xFF; v1.vz = sz; v1.vy = vh; v0.vy = vv2;
```
That's essentially f5 but with v1.vz moved before v1.vy. Let me check f5: [vh; v0.vx; vv2; v0.vy; v0.vz; vw; v1.vx; v1.vy; v1.vz]. Different.

Let me try these three (i1-i3) plus variants where v0.vy is last.

Given budget overrun, I'll do 4 more tries then decide.

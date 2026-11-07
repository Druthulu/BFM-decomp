---
ts: 2026-11-06T04:21:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3aB3YIByKpvIVCH4h1jo
---
r1 duplicated the store (my awk didn't delete the original line because NR==53 in w4 isn't the store line). Bad. Ignore r1.

w7 same as w4 (14). The p reload still hoisted.

Let me think about the reload position differently. The reload `lw p,32(s1)` is needed for the shared store `((Unk*)p)->unk18 = v`. In the target, it's at 4944. In mine, 4930. What if I write the shared store differently so the p load is born later? E.g., inline the p load into the store expression in the merge block:
```
((Unkstruct_800B5CB8 *)((Unkstruct_800B5CB8 *)a0)->unk20)->unk18 = v;
```
But then the other arms would need their own p load. The merge block is shared; the arms set p and v. Hmm.

Wait, maybe the issue is the `<0x11` arm's p load is being scheduled early because the *store* it feeds is far. In the target, the p load feeds the shared store at the end (494c). The scheduler sees the store's dependence and schedules the load later (after the multiply). In mine, it schedules the load earlier. The difference is priority ordering — which is determined by sched1's heuristics, sensitive to the exact insn sequence (birth order).

The birth order differs between mine and target because of the earlier fences. Specifically, the fence after the 0xC00 store (line 59 in orig) and after the multiply (line 61). Without them, the RTL order of the block is: store(0x1A), lw obj->1C, mul..., lw p, add, sh. With them, same order. The fences don't change birth order; they just prevent reordering.

Hmm, but the target's schedule has p's load after the multiply. The scheduler's decision might be influenced by register pressure (it tries to minimize). 

Let me try a different C formulation for the multiply: use a temp for obj->1C:
```
s32 m = *(s32 *)(obj + 0x1C);
v = m * 3 * 32;
```
Adds a variable (s32 m) — could change priority. Or `v = *(s32*)(obj+0x1C) * 96;` (single multiply by 96 → sll? 96 = 3*32; the compiler would do sll 1, addu, sll 5? Actually *96 = *3*32, same). Let me try `* 96`.

Also try `v = *(s32*)(obj+0x1C); v = v * 3 * 32;` (two statements).

Let me also try moving the `v = v + 0x600;` before the p load (source), which is not target order but sched may reorder.

Actually, let me reconsider the whole thing. The remaining diff is essentially ONE insn position + the resulting register naming. Score 14. The target is 108 ins, mine 107 (the missing insn is just the position diff, both have the same insns? 107 vs 108 — one insn difference: target has an extra `lw`? No: the diff shows mine[88] lw a0 vs target nop, and target[92] lw v1 vs mine --. So both have one reload; the counts differ because the jump delay slot? Hmm, 107 vs 108: maybe the target has a nop that mine lacks.

Let me count the target: it has `nop` at 48dc, 48e4, 4928, 4934, 48dc etc. Mine might have fewer nops due to scheduling. Score 14 is COUNT (ins count differs by 1). The missing insn could be a nop.

To match, I need the exact schedule. This is the hard part: sched1 reproduction.

Given the time (item 4 started ~21:22, now maybe 21:45), I've spent ~23 min and ~10 tries. A WALL needs ≥20 min and ≥30 tries. Let me continue with more variants, focusing on the sched1 priority.

Ideas to shift the p load later:
1. Give the multiply chain a higher priority by making it longer: `v = *(s32*)(obj+0x1C) * 3 * 32;` is sll+addu+sll. If I add a dependency like `v = (*(s32*)(obj+0x1C) * 3) * 32;` same.
2. Reuse a temp so the p load's dest conflicts... 
3. Make the p load use the SAME variable as obj->1C? e.g., load obj->1C into `n` (reuse n), then `p = ...`. The n variable is dead in this arm; reusing it might change birth order/regs. Let me try:
```
n = *(s32 *)(obj + 0x1C);
v = n * 3 * 32;
p = ...;
v = v + 0x600;
```
Hmm, n is s32. The target's obj->1C load is into v1 and n is also v1 in the n<8 arm (disjoint). Using n here might make the obj->1C value live in n (v1) and the p load into another reg. But target has obj->1C in v1 and p in v1 too (disjoint: obj->1C dies at sll 4940, p born at 4944). So if n=obj->1C (v1), then p could reuse v1 after. That's exactly the target! In mine, the p load is born BEFORE obj->1C dies, forcing a different reg (a0). So if I make the p load depend on the multiply (born after), the register follows.

Let me try `n = *(s32*)(obj+0x1C); v = n*3*32; p = ...; v = v + 0x600;` — reusing n. Does that change anything? The obj->1C value goes into n's pseudo; p is separate. The p load is still independent and sched could hoist it before n's last use. Hmm.

4. Use a do-while around the store only, or around the whole arm.

5. Make the p load's value used by the multiply? no.

6. **Force the p load to be after by making the store's address depend on v**: the store is `((Unk*)p)->unk18 = v;` — the address p and value v. If instead we wrote the store with an offset derived from v? no.

7. Try `-fno-schedule-insns`? Not allowed (we can't change flags).

8. Reorder the C so the multiply is computed before the 0x1A store, and let sched reorder the store after. r1 was botched; let me do it correctly. Source:
```
v = *(s32 *)(obj + 0x1C) * 3 * 32;
((Unk*)*(s32*)(a0+0x20))->unk1A = 0xC00;
p = ((Unk*)a0)->unk20;
v = v + 0x600;
```
If the multiply is born first, sched1 might emit the chain first, then the store, then p. Target: store, chain, p. Not matching, but the register conflict might resolve (p born after the chain). Let me test.

Let me fix r1 correctly: in w4, line 53 is the store. Move it after line 59 (multiply). Let me use awk: skip NR==53, and after NR==59 print the store line.

Let me check w4's line numbers: 52 = `} else if`, 53 = store, 54-56 comments, 57? Wait w4 added 3 lines (do-while) before, shifting. grep earlier: line 59 = multiply, 60 = p, 61 = v+0x600. So line 53? Let me grep.

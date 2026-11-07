---
ts: 2026-11-06T20:32:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6B3QM9CWmmLuZGoETo9i
---
Interesting! p1b (barrier kept, launder removed) = 8 (ORDER). p2b (barrier removed, launder kept) = 6 (COUNT).

Neither is 0. So PARTIAL isn't immediately available.

Hmm, p2b = 6: with the launder kept and the barrier removed. So the launder fixes cluster 2 partially? Let me see the diff of p2b: 6 mismatches — the barrier cluster remains.

p1b = 8 (ORDER) with the barrier kept: the barrier cluster is fixed, and the launder cluster remains (8 ORDER mismatches).

So each lever fixes its own cluster. To get 0 we need both effects without the levers.

Let me look at p1b's diff to understand the launder cluster with the barrier kept.

Actually, let's think about the launder replacement more cleverly.

The launder's RTL effect: `a1 = asm(...)` — an insn that sets a1 to an opaque value, after the const. This:
1. Forces the constant to be materialized at its source position (the asm needs r in a register).
2. Acts as a sched2 barrier (volatile asm).

Real-C replacement for "force materialization": make r's value depend on something that must be computed at that point. What if r's value is assigned from `q` (the pinned a0)? E.g.:
```
register s32 q __asm__("$4") = s0;
s32 r = (s32)((u32)q & 0xFFF80000);
```
That's NOT the same value (q = s0 = a pointer, typically 0x80xxxxxx). No.

But wait — what if the target's actual intent is that the second arg is a *mask*? 0xFFF80000 is a mask. Hmm.

What if we compute r from the *address* in a value-preserving way? No.

Hmm, what about using a *compound literal* or a bitfield to hide the constant? E.g.:
```
struct { s32 a : 19; s32 b : 13; } s = { 0, -1 };
r = *(s32 *)&s;
```
Stack traffic.

What about an enum? `enum { M = 0xFFF80000 };` still a constant.

Hmm. What if the constant is loaded from a `static const s32` array? That would be a memory load (lw) — target has lui only.

OK. Let me think about sched2's barrier differently: maybe we can get the target order by making the const *depend* on the store's value. The store `unk2 = 7` has a REG_EQUIV note to the memory and const 7. If the const r depended on the store... no.

Alternatively, make the store depend on the const: the stored value 7 could be written as `7` where 7 comes from... hmm, `((Unk*)s0)->unk2 = 7;` — what if we write `((Unk*)s0)->unk2 = (s16)(r >> 19);`? r = 0xFFF80000 = -524288; r >> 19 (arithmetic) = -1. Not 7. `r >> 16` = -8. `-(r >> 16) - 1` = 7! Let me check: r = 0xFFF80000 as s32 = -524288. -524288 >> 16 = -8 (arithmetic). -(-8) - 1 = 7. So `unk2 = -((r >> 16) + 1);` = 7. But that's contrived and the compiler would constant-fold it (r is a known constant) → 7. Identity-ish and would be folded, so no dependency.

Right, any expression of a known constant folds.

What if r is NOT a known constant to the compiler? Then we'd need a real runtime source.

Hmm, what about making r come from the function's *parameter* a0 in a value-preserving way? a0 is s0 (the pointer). The constant 0xFFF80000 can't be derived from an arbitrary pointer without masking, which isn't value-preserving.

I think cluster 2 (the constant propagation/rematerialization) is a genuine wall: "combine/cse folds the 1-use constant into the call arg; only an opaque re-tie keeps it at source position". And cluster 1 is the dbr fill: "reorg fills the bnez delay slot with the join's xori; only an asm barrier stops the search".

But before walling, let me try a few more real-C ideas for cluster 1 and 2. Let me look at the target's source intent: the notes say the barrier is "cookbook-index L22 / §5a + the §34 zero-byte fence toolkit: reorg's eager filler otherwise COPIES this xori out of the join thread into the bnez delay slot above and redirects the branch one insn further on. stop_search_p halts that search on an asm insn, so the target's unfilled nop (idx 18) survives."

So the authors already knew this and used an asm fence. The question is whether a real-C equivalent exists.

Idea for cluster 1: make the xori NOT the first insn of the join thread by making the join start with a NOTE/barrier... In plain C, if the join block's first insn were something reorg can't copy, e.g., a *store* (stores are copyable? `insn_sets_resource_p (trial, &needed, 1)` — a store sets memory; `needed` includes the branch's needs; memory might be needed?).

What if we reorder the join: `((Unk*)s0)->unkDC = v ^ 1;` — then the join's first insn is the xori anyway (the store's source computed first).

Hmm, what if the store were before the xori: `((Unk*)s0)->unkDC = v; v ^= 1;`? Semantics: the target stores v^1 to unkDC. Writing `unkDC = v; v ^= 1;` stores the un-xored value — different semantics.

OK, what if we could make reorg's copy illegal by having the xori read a register that the branch's delay slot can't have? E.g., if the xori's operand were loaded in the then arm... The xori reads v0, which in the then path comes from the then arm's lw and in the else path from the else's lw. Reorg copies it into the bnez's delay slot for the then path.

What if v were a different pseudo in each arm and merged with a copy? Then the xori would read a phi result.

Hmm, what if the else arm's load went into a *different* register than the then arm's? It's the same variable v.

OK, let me try a few structural variants for cluster 1 (cheap):
- vJ: `v ^= 1;` → `v = (v + 1) ^ 1;`? changes value.
- vK: move the `v ^= 1;` INSIDE the else arm and duplicate it in the then arm? That changes code (2 xoris).
- vL: add an empty `if (0) { }` before the xori? folded.
- vM: `if (v) v = 1; else v = 0;` no.

Hmm, what about using a *function call* at the join? no.

Let me try the C label trick:
```
  join:
    v ^= 1;
```
with a real reference that survives. E.g., `if (v == 0x7FFFFFFF) goto join;`? adds a branch.

What about a `switch`? no.

What about `do { } while (0);` empty — probably deleted.

Let me test a couple and see.

Actually, maybe a smarter idea: use the *existing* `p` variable and a `goto` that's part of the natural flow? No.

Alternatively, accept the WALL for item 3. But a WALL requires best = lowest score of a lever-free body = 10 (we have 10). And ≥30 tries, ≥20 min. We're at ~12 tries, ~20 min (13:19 → ~13:40). I'd need 18 more scored tries. That's doable with cheap variants, but I should also consider that the expert's PARTIAL row could be better: PARTIAL requires score 0 keeping some kinds — not achievable here.

Hmm wait, actually re-read PARTIAL: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". So PARTIAL requires score 0. Not available (p1b=8, p2b=6).

So item 3 → WALL with best 10, if I can't crack it.

Before that, let me try a few more ideas quickly, especially the "goto label" and "empty do-while" and "conditional move" for cluster 1, and for cluster 2 maybe "assign r through a struct field" etc.

Actually — wait. For cluster 2, here's an idea: the launder forces materialization by making r's value opaque. What if we make r's *second set* via a real C operation that combine can fold but which happens before the store... no, folding removes it.

Another idea: make the constant *not* propagated by giving the pseudo a second use in the *store* that combine can't fold. E.g.:
```
s32 r = 0xFFF80000;
((Unk*)s0)->unk2 = 7;
```
What if the store's value is `(s16)((r >> 19) + 8)`? r>>19 = -1 → 7. Constant-folded.

Everything folds because r is constant.

What if r's declaration is `s32 r = 0xFFF80000;` and we take its address? `s32 *pr = &r;` → stack slot.

OK, cluster 2 seems a wall.

Let me try 3-4 more cluster-1 ideas and then wall it.

Idea A: put the xori inside a `do{}while(0)` with a *non-empty* body and a condition that can't be folded... e.g., `do { v ^= 1; } while (0);` — we tried; deleted.

Idea B: make the join a real basic block boundary by having both arms jump there. E.g.:
```
if (unkFC != 0) { v = unkDC; if (v == 0) { unk2 = 5; return; } }
else { v = unkDC; }
```
The then arm's `return` is a jump. The else arm falls through. What if we add `else { v = unkDC; }` plus an explicit `return` in the then arm after the if? The then arm already returns conditionally.

What if we restructure with a `goto`:
```
if (unkFC != 0) { v = unkDC; if (v == 0) { unk2=5; return; } }
else { v = unkDC; }
join:
v ^= 1;
...
```
and make something jump to join: the then arm's `if (v==0)` block does `unk2=5; return;` — no goto to join.

If we write `if (v != 0) goto join; unk2=5; return;` in the then arm — that's the same branch but now the branch target is `join` (a real label), so the join has a CODE_LABEL that is the branch target! Then reorg's fill: the bnez's thread would be... hmm, the branch at 217c would target the join label. The fill search from the thread (the join) — stop_search_p at the label? The search starts AT the thread; if the thread IS the label, stop immediately → no copy!

That's exactly what we want: the branch target is the join label, and the join label is the xori's block start. In the target, the bnez targets 2194 (a nop) not the join label (the xori). Hmm.

Wait, but this changes the C structure. Let's see: 
```
if (unkFC != 0) {
    v = unkDC;
    if (v == 0) { unk2 = 5; return; }
}
else { v = unkDC; }
v ^= 1;
```
vs
```
if (unkFC != 0) {
    v = unkDC;
    if (v != 0) goto join;
    unk2 = 5;
    return;
}
else { v = unkDC; }
join:
v ^= 1;
```
The RTL: bnez v -> join; then li 5; j epilogue; sh; else: lw; join: xori. The bnez targets the join label directly (which is the xori). Reorg might then put the xori in the delay slot? If the branch target IS the label before the xori, then the search starts at the label and stops (CODE_LABEL). Hmm, but reorg might still copy the target insn into the delay slot as the "target" of the branch (that's the point of a delay slot: the target executes). Actually, the standard MIPS delay slot: `bnez L; nop` then at L the xori. If reorg fills the delay slot with the insn AT L, it must redirect the branch past it (to L+4), which it did in mine.

The target's code: bnez -> 2194, where 2194 is a nop and 2198 is the xori. So the target's branch target is NOT the xori's insn but the nop before it.

Hmm, in the target, the label at 2194 corresponds to... the join? The else path: lw at 2190, then 2194 nop (load delay slot), then 2198 xori. So the label 2194 is after the else's lw. The bnez jumps there.

So the target's bnez target label is *after the else's load*, i.e., at the point where the else's load delay slot is. Hmm, interesting: the else's `lw` is at 2190 and its delay slot nop at 2194, and the branch target is 2194 (the nop). So the bnez jumps into the else's load delay slot! That's legal: the nop executes.

So the label is placed between the lw and its delay slot (reorg's dbr pass can put a label in a delay slot).

OK, this is deep reorg behavior. Let me try the goto variant and see what happens. It's cheap.

Actually, let me first try something simpler for cluster 1: since the target's delay slot is a nop, maybe we can make the xori un-copyable by adding a `volatile` access... no.

Let me try the goto restructure.

Also, for cluster 2, let me try one more: `s32 r = 0xFFF80000;` → declare r as `static`? no.

Let me test the goto variant.

---
ts: 2026-11-06T07:43:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9uLzRZoCcfFoyShVC2xC
---
Now I see: r79 is a global pseudo (allocno) with 4 refs, 26 live, conflicts ..., "dies in 2 places". In orig it conflicts with s5; in w1 it "prefers s5". r79 is likely the `w3c` pseudo or something global. Its priority 3076.

r77 is s5: in orig 4 refs / 116 live (crosses 4 calls) — this is twicep, kept live long by the keepalive. In w1: 3 refs / 44 live.

Wait, r77 has 4 refs in orig and 3 in w1 → the keepalive adds 1 ref to twicep. And its live length 116 vs 44. So twicep is a GLOBAL pseudo (crosses 4 calls? it's used at insn 37,40 which are after 4 calls; hmm "crosses 4 calls" — the function has 4 calls early). r77 in s5 both.

r79: 4 refs, 26 live, dies in 2 places. In orig conflicts s5; in w1 prefers s5. r79 might be w3c: `w3c = *(u32*)twicep; ... L.w3C = w3c; ... w3c = (u32)L.o1; gte_stsv(w3c)` — 4 refs (def, use in L.w3C, redef, use in gte_stsv), dies in 2 places. Yes, r79 = w3c.

In w1, r79 "prefers s5" (copy preference from the load? no) and doesn't conflict with s5 → it can get s5. In orig, r79 conflicts with s5 → gets a0.

The conflict arises because s5 (twicep, r77) is live across r79's range in orig, but not in w1. In w1, twicep (r77) dies at 44 (live length 44) — r79's range overlaps? r79 live 26; hmm.

So indeed, in orig, twicep stays live longer (live length 116) and conflicts with w3c. In w1, twicep dies at 44 (which is around insn 40) so no conflict, and w3c takes s5.

So the real C must extend twicep's live range past w3c's range. The target's s5 is saved/restored but has no use after insn 40 — yet r77 in the TARGET would have live length long enough to conflict. How? A use of twicep that emits no instruction but keeps the value live... 

What real C use of twicep after the GTE block emits no instruction? If the value is used in a way that's dead (DCE would remove it before allocation). If used in a comparison that's folded? No.

Hmm, maybe the original does use twicep after but the use is on a path that... no, straight-line.

Wait — maybe the natural C has twicep used in the `L.w3C = w3c;` line? Like `L.w3C = *(u32 *)twicep;` — that's a THIRD read at insn 59, which would emit `lw` (extra insn). Target has no extra lw; insn count is 132 in both. So no.

Unless... the third read replaces the second! What if the source is:
```
w3c = *(u32 *)twicep;   // load at 40
...
L.w3C = w3c;            // store at 59
```
vs.
```
w3c = *(u32 *)twicep;   // load at 40
...
L.w3C = *(u32 *)twicep; // would load again at 59
```
Target has one load at 40 and a store at 59 → the first form. So no third read.

Could the original pass twicep to one of the GTE macros? No.

Let me reconsider: maybe the natural C's r79 (w3c) does NOT get a0 by conflict avoidance but because its *priority* differs. In w1, r79 prefers s5 (copy preference) and gets s5. In orig, r79 conflicts s5. The difference in r77's liveness is caused by the keepalive. What if the natural C makes w3c's range NOT overlap s5's by making w3c born later? E.g., `w3c = *(u32 *)twicep;` moved later (after the v48/v50/v58 stores)? But target loads at 40, early.

What if w3c is split into two variables so that the loaded value's range is short? No, the target keeps it in a0 from 40 to 59.

What if the *loaded value* variable is declared u32 and the pointer variable separately (as I thought)? Then the loaded value's range is 40..59 (store), and the pointer's range 59..72. Both would want a0; the loaded one conflicts with s5? Still.

Let me look at where s5 dies in the natural target: insn 40. r79 (w3c) born at 40. local-alloc's rule: a register dying in the same insn as a birth can be reused. In target it does NOT reuse s5. Why? Maybe because the *load* `lw a0,0(s5)` has s5 as a source, and the REG_DEAD note is on that insn. When a qty is born at insn N and another dies at insn N, local-alloc's post_mark_life / regs_live_at determines conflict. It might depend on the exact birth/death indices (2N vs 2N+1). In target, w3c (r79) is a GLOBAL pseudo (it has conflicts listed, and .greg order includes 79) — so global-alloc decides it, not local-alloc! r79 is in the .greg order line ("79"). So global-alloc assigns r79. Global-alloc uses `regs_live_at` at block boundaries and conflicts. In orig, r79 conflicts s5 because s5 is live at r79's range... 

The .greg order line has only 79 — a single global allocno. So w3c is global because it "dies in 2 places" (used across blocks? no). Actually "dies in 2 places" makes it global (local-alloc refuses a pseudo that dies in several places: local-alloc.c:472). So w3c is global. Global-alloc assigns it. Its conflict with s5 depends on whether twicep (s5) is live across w3c's live range.

twicep (r77) is also global (s5, crosses 4 calls). In w1, r77's live length is 44 — its live range ends at insn 40. In orig, 116. w3c's range 26. If w3c's range is [40,59] and twicep ends at 40, do they conflict? At insn 40 both are live (twicep used, w3c defined) — global-alloc might consider them conflicting if their ranges overlap at insn 40. In w1, r79 "prefers s5" and doesn't conflict → global-alloc allowed the same reg (they're coalesced? "prefers s5" is a copy preference from `lw s5,0(s5)`? no).

Hmm. So to reproduce the target, twicep must be live past insn 40 in the *global* liveness. The target binary has s5 dead after 40, but the compiler's allocation decision in the original could still have had a longer live range due to a real use that got optimized away AFTER global-alloc? No, allocation is after optimization.

Unless the real use is one that produces no instruction because the value is already in a register and the use is in a context that's free. E.g., `w3c = *(u32*)twicep;` — what if the original wrote `w3c = *(u32*)twicep;` twice? The second load would be CSE'd (same address, no intervening store to *twicep? there are stores to L (stack), which may alias! `*(u32*)twicep` where twicep is a void* param; cse can't prove it doesn't alias the stack stores, so it would emit a second load). Not free.

What if the original used `twicep` in a context like `if (twicep) ...`? That's a test on a known non-null? Not provable, would emit a branch. No.

What if `L.w38 = *(u32 *)twicep;` and `w3c = *(u32 *)twicep;` are the two reads, and the original had `L.w38` and `w3c` as the same variable? No.

Let me look at the keepalive's exact placement: after the three gte_stsv, before `L.q2A = 0x13F;`. Maybe the original code at that point had a real use of twicep that the compiler turned into nothing because it's a *dead store to a struct field*? For example, `L.w38 = *(u32 *)twicep;` again (redundant store, same value) — the second store would be a redundant store to the same address; cse might delete it as redundant (same value already there) BUT the LOAD would remain. Hmm.

What if the original had `L.w3C = *(u32 *)twicep;` at that point AND the earlier `w3c` load is actually the same load moved? No.

Let me look at the P36 trace for this function to see what moves were tried and the best.

---
ts: 2026-11-06T21:08:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SXk2ZjJn8D1w0o628gUk
---
A and B change instruction count (146 vs 147). C still 4.

Interesting: the cast to `s16(*)[2]` produced 146 insns (one fewer), meaning cse shared the address (as I predicted). So no.

Let me think about how to raise e's n_refs without changing code. The launder gave e a def+use. What if I add a *use* of e that is folded into an existing instruction? E.g., use e in the lim address but with the symbol, so the code stays `lui at; addu at,at,a1`? If the lim address is computed as `(u8*)e + off` but e is REG_EQUIV symbol, cse/combine could fold e back to symbol → `lui at, sym; addu at,at,off`. That's exactly target's instruction (lui at, sym — not addiu!). But A/B produced 146 insns (one less), meaning cse merged the lim and condition addresses into one addu. That's the difference.

Hmm. So using e for lim causes address sharing.

What about adding a use of e that cse removes anyway but still raises n_refs at local-alloc time? local-alloc runs AFTER cse, so if cse removes the use, it won't count. So no.

What if the extra use is a real one that generates the same instruction? For instance, e is used as the base for the condition address: that's already 1 use. Could we use e for something that already references it, like the lim load, but prevent address sharing? Address sharing happens because both addresses are e+off and e+off+2 (same base). If lim used e+off and the condition used e+off+2, cse shares e+off. Target has them separate: lim = sym+off (via at), condition = e+off (via a0). The difference is that target's lim address uses the SYMBOL directly (lui at) whereas e is a full addiu pseudo. If cse folds e→symbol for the lim address, then lim address = sym+off (at), condition address = e+off (a0, since e is a separate pseudo not folded). So we need e to remain a pseudo (not folded to symbol) at the condition but be folded at the lim use.

REG_EQUIV enables folding. The launder's tied asm probably prevented folding e at the condition (the asm output made e non-equivalent), so the condition kept e in a reg. And the lim address (using symbol directly in source) stayed symbol. That's why the launder was needed: to keep e as a real pseudo (not eliminated as REG_EQUIV) so it occupies a reg.

Ahh. So the real issue: without the launder, `e = (s16*)D_801E8F78` is REG_EQUIV and cse/combine might substitute the symbol at its use, eliminating the register... but the diff shows e still gets a1 (lui/addiu a1). So e is materialized in mine too. The only difference is a0/a1.

OK so e is materialized. The launder raised e's priority. Let me reconsider: maybe there's a way to give e a 2nd set that's real and live.

What if e is assigned conditionally with the same value in both arms? e.g.
```
if (t < lim) { ... }
```
No.

What if we set e once, then in the else of the inner condition reassign e? 
```
if (t < lim) {
    if (A || B) idx = -1;
}
```
Could restructure as:
```
if (t < lim) {
    s16 v = load;
    if (v == 0) { idx = -1; }
    else { if ((f(v)&0xFF)==0) idx = -1; }
}
```
Still e used once.

Alternative: use e for BOTH the lim load and the condition but arrange so the lim load uses the SYMBOL via a separate expression, while e gets 2 uses elsewhere. Hmm.

Let me step back and look at what actual register each should get and whether a simpler change (e.g. removing the `pad[2]`) alters things. Let me test dropping pad, and a few structural changes.

Also: maybe change the order: `lim` computed from `D_801E8F78[idx][0]` where idx is s16. What if we introduce `s16 *e` and use `e[idx*2]` for lim — that would use e... no.

Let me try: declare `e` and use it in the condition twice with a *separate* pointer variable `e2 = e`? e2 is a copy; combine propagates. Might give e 2 uses.

Actually, let me try the simplest: `off` declared AFTER e in the declaration list, or e declared before off. Declaration order doesn't matter for RTL.

Hmm, let me look at this from the "target" perspective. The target binary was compiled from some C that had the launder (the orig.c). The task is to find a lever-free C body that produces the same object. Since the launder's effect is a 2nd set of e, we need a real 2nd set.

Real 2nd set idea that IS live: 
```
e = (s16 *)D_801E8F78;
off = idx * 4;
lim = D_801E8F78[idx][0];
if (t < lim) {
    if (*(s16 *)((u8 *)e + off + 2) == 0 || ...) idx = -1;
}
```
If we add, inside the `if (idx >= 0)` else branch, a use of e: e.g. `result = D_801EF140;` → `result = (void*)e;`? No, changes semantics.

Hmm, what about the `idx = -1` path: after that, idx<0 → else branch result = D_801EF140. e unused.

Let me reconsider: maybe the 2nd set doesn't need to be live; maybe local-alloc counts n_refs from the RTL including a set that flow later deletes? No, local-alloc is after flow.

What if we create a 2nd set of e in a branch that is taken, and the value is used in that branch only? For example:

```
e = (s16 *)D_801E8F78;
off = idx * 4;
lim = D_801E8F78[idx][0];
if (t < lim) {
    if (*(s16 *)((u8 *)e + off + 2) == 0 || (f(...) & 0xFF) == 0) idx = -1;
}
if (idx >= 0) { ... } else { ... }
```
Only one block uses e.

OK let me try a completely different lever: make `off` live LONGER so its priority drops below e's. off is born at insn 54 (right after idx load). If we could make off born earlier... it can't (needs idx). But we can make off's DEATH later — i.e., use off after the call or later in the block. That would change code though (add a use). Unless the use is folded.

Alternatively make off's n_refs lower: off has 3 refs (def + 2 uses). If one use is eliminated (e.g., cse folds the lim address), off = 2 refs → priority = 1*2*4/55 = 0.145 < e 0.47. But that changes code (146 insns).

Hmm, what if we keep off but the lim address uses idx directly instead of off: `lim = D_801E8F78[idx][0]` — cse creates off from idx*4 for this. It's the same.

What if we compute off differently so it's not CSE'd from the lim address? e.g. `off = idx << 2` (v3) — same result.

I think the cleanest is to raise e's refs. Let me look for a real 2nd set that produces identical code. 

Idea: use e in the lim load *and* the condition, but make the lim load address use e + off in a way that cse does NOT share with the condition because the lim load is a different mode/size? Both are halfword loads. Hmm.

Actually wait: in target, the lim load is `lh v1,0(at)` where at = sym + off (computed as `lui at,sym; addu at,at,a1`). The condition is `lh a0,2(v0)` where v0 = e + off = `addu v0,a0,a1`. So there are TWO separate address computations that both use off. If I write lim via e, cse sees both addresses as e+off and e+off+2, and shares e+off → one addu, saving an instruction (146). But target has two addu. Why? Because in target, e is a real pseudo (a0) but the lim address is sym+off using `at` — the compiler did NOT fold e into sym for the lim; instead the lim load was written with the symbol directly.

So to match target, source must write lim with the SYMBOL and the condition with e. That's the current win.c. The only issue is register priority.

Given that, the 2nd set is the way. Let me try: make e's assignment a compound that the compiler keeps as 2 insns but same result? E.g. `e = (s16 *)((u8 *)D_801E8F78 + 0);` — combine folds.

What about `e = &D_801E8F78[0][0];`? That's a symbol address; same.

Let me look at C0414 more carefully — dead reset. The dead reset works when the pseudo is used both before and after. Here e is used once. But what if we make e used before the reset AND the reset is after the call, with e used after? No.

New idea: instead of raising e, LOWER off's priority by giving off a longer live range without changing instructions. off is used at the lim address (insn 70) and the condition (insn 81). Its live range is 54→81. If we define off EARLIER — impossible. But we can make off's birth earlier by defining it at the top of the function from `idx`? idx isn't defined.

Hmm, what about `off` being s16 and computing it as `idx*4`? Let's see: `s16 off = idx*4;` then `off` is HI mode. `D_801E8F78[idx][0]` address uses off? The address needs SI. Might produce extra extend. Probably changes code.

Let me try a different approach: swap which variable is which. What if we name the pointer `off` and the offset `e`? No effect.

Let me try: increase off's qty length by using it in the `if (idx >= 0)` block somehow folded. No.

Let me try the do-while split (C0535): wrap the e assignment in `do { e = ...; } while(0)`. This splits the EBB and might change local-alloc's block boundaries! If e is in its own block, allocation differs. The moves log says do-while splits cse1 EBB. Let me try:
```
do { e = (s16 *)D_801E8F78; } while (0);
```
with `// !FAKE: do-while` comment. That's allowed. It might change the block structure and register allocation. Let me test.

Also test a dead reset: after the condition, `e = (s16 *)0;` — likely removed.

Let me test do-while variants and a couple more.

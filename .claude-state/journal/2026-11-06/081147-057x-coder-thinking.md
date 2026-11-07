---
ts: 2026-11-06T15:11:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1DmxIn9a6xbDezmrC97n
---
Target structure:
```
sra s0,v0,0x10       # t = (s16)a1
bnez s0,6f4          # if (t != 0) goto 6f4
  li v1,3            # (delay slot)
  ... t==0 path
6f4: beq s0,v1,70c   # if (t == 3) goto sel_054
  li v0,5            # delay
6fc: bne s0,v0,740   # if (t != 5) goto 740
700: nop
704: bne s0,v1,71c   # if (t != 3) goto sel_094
708: nop
70c: sel_054: lui v0,&D_801C3C94 ...
71c: sel_094: jal func_800291B4 ...
```
Interesting: there's a `nop` at 700 and 708 — because sched1 couldn't fill.

So the target's C is exactly:
```
if (t == 3) goto sel_054;
if (t == 5) {
    if (t != 3) goto sel_094;
sel_054: ...
```
With the launder, t is opaque, so `bne s0,v1,71c` is emitted.

Now, can plain C produce `bne s0,v1,71c` after `bne s0,v0,740`? The compiler knows t==5 on the fall-through of `bne s0,v0,740` (i.e., t==5). So `if (t != 3)` is constant true → no compare.

What if the `if (t != 3)` test is on a *re-loaded* t from memory? No.

What if we change `if (t != 3)` to compare something else that the compiler doesn't know but is equivalent? For example, compare `mode` or another variable? No, semantics.

What if we make the t==5 test compare a *copy* `u` and the t!=3 test compare `t`, where the compiler doesn't know t==5? E.g.:

```
t = (s16)a1;
...
if (t == 3) goto sel_054;
{
    s16 u = t;      // copy
    if (u == 5) {
        if (t != 3) goto sel_094;
        ...
    }
}
```
The compiler knows u==5 and u==t (cse equivalence), so it still knows t==5. Hmm.

What if we obscure the equivalence: `u = t;` then `if (u == 5)`. cse makes u and t equivalent. So `t != 3` folds.

What if `u` is derived through a cast that cse doesn't equate: `u = (s16)(t + 0);`? cse might fold t+0.

Hmm.

Alternative: use the loop/if structure to make the `t != 3` test a *switch* fallthrough. Consider:

```
switch (t) {
case 3: sel = &D_801C3C94; goto set_sel;
case 5: 
    if ((func_800291B4(0x40) & 0xFF) == 0) goto call_45F;
    sel = &D_801C3CD4; goto set_sel;
}
```
That's the semantically-equivalent version and gives different code (no t!=3 test). Not matching.

So we need to preserve the target's exact branch. Since the launder is needed for that, maybe there's a plain-C construct that keeps a compare the compiler can't fold.

Recall moves line 273: "flow knows cc==1 on the fall-through so the 2nd if(cc==one) folds (89 ins); real 2nd sets fold; a (cc&0xFFFF) mask keeps it but costs 1 andi (best 10)". So a mask `(t & 0xFFFF) != 3` might keep the test! But it costs an andi... unless the mask is free because t is already sign-extended? Hmm.

Wait — the target compares `s0` (t, the sign-extended s16) against `v1`=3. If we write `(t & 0xFFFF) != 3`, the compiler emits `andi` then compare — one extra ins. But maybe not: since t is s16, `t & 0xFFFF` might be optimized. Hmm, the wall says it costs 1 andi.

Alternatively `(u16)t != 3`? A zero-extension of t; comparing to 3. The compiler knows t=5 → folds.

Hmm, what about making the compare involve the *original* a1: `if ((s16)a1 != 3)`. The compiler knows t == (s16)a1? At the C level, t = (s16)a1; the compiler's RTL has t as a pseudo holding a sign-extended value. Does cse know `t == sign_extend(a1)`? Yes, there'd be an equivalence t ↔ (subreg/sign_extend a1). Then knowing t==5 might let it know (s16)a1 == 5. But the compare `(s16)a1 != 3` would be a re-derivation from a1 — cse's fold_rtx might substitute the known value of the *expression* sign_extend(a1) = 5 → fold. Risky.

Let me just test empirically:
f1: `if ((s16)a1 != 3) goto sel_094;`
f2: `if ((t & 0xFFFF) != 3) goto sel_094;`
f3: `if ((u16)t != 3) goto sel_094;`
f4: reorder: check t==5 first then t==3 inside.
f5: use a local copy with a cast.
f6: compare `t != 3` but with t re-assigned from a1: `t = (s16)a1; if (t != 3)`.
f7: `if (t - 3 != 0) goto sel_094;`
f8: `if (t > 3) goto sel_094;` (t=5>3, but also t=4,6.. would go — inside the t==5 block only t==5, so equivalent!) 

Oh! f8 is clever: inside `if (t == 5)`, `t > 3` is always true, and `t != 3` is always true. But would the compiler fold `t > 3` given t==5? It knows t==5 → folds. Hmm.

What about using a *signed/unsigned* comparison that the compiler's known-value logic misses? E.g. `(u32)t != 3`? t=5 → still folds maybe.

Let me think about what the launder's RTL does: `t` is redefined by an opaque set. Any plain-C construct that creates a *set* of t which the compiler can't evaluate. A value-preserving opaque set...

What about `t = func_800291B4(0x40) & 0xFF;`? No, changes semantics (but wait — look at the code: after sel_094, it calls `func_800291B4(0x40) & 0xFF`. Could we hoist that call before the test? That would change evaluation order/side effects — the target has the call at sel_094 only, and the test must decide whether to reach it. No.

Hmm, what about the `t` value coming from `a1` again through the stack? 

Let me consider a totally different structural approach that produces the same *branch* without the launder. The target's `bne s0,v1,71c` compares t against 3. What if we write the source so that the compiler *must* compare t against 3 for a legitimate reason, e.g., because the fall-through path (sel_054) is reachable with t==3 from somewhere else? 

Look: sel_054 is the t==3 path. If we move the `t==3` handling *inside* the t==5 block's fall-through... Actually here's an idea:

```
if (t == 5) {
    if (t == 3) goto sel_054;   // dead, but compiler folds to never
    goto sel_094;
}
```
Compiler folds `t == 3` to false → just `j sel_094`. No compare.

What if the compiler can't prove t==5 at that point because the `if (t == 5)` test is done on a *different expression* that equals 5 but isn't t? E.g.:

```
if (t + 0 == 5) { ... }   // folds to t==5
```

What about `if ((s16)(t & 0xFF) == 5)`. Hmm.

OK, empirical batch time. Let me also consider the register issue: target uses v1 for 3, mine uses v0. That's a separate allocation difference; fixing the branches might fix the registers too.

Let me write f1-f8 and score.

Also worth trying: `if (t != 3) goto sel_094;` replaced by a goto structure using the earlier `if (t == 3) goto sel_054;` label. Hmm.

Another idea: make the test a `switch` on t with cases 3 and 5 where case 5 falls through to case 3's body:

```
switch (t) {
case 3:
    goto sel_054;
case 5:
    if (func(...)...) ...
}
```
no.

Let me also try: `if (t == 3) goto sel_054; else if (t == 5) { if (t != 3) ... }` — same.

Let me run the batch.

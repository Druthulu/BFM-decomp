---
ts: 2026-11-06T15:20:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eQiFva6ougAq2YUN9yUK
---
It's 08:20, so item 2 has taken from ~08:08 to 08:20 = 12 minutes. Hmm, I need ≥20 min for a WALL. Let me continue trying until ~08:28.

Actually wait, let me reconsider the whole thing. Maybe there's a smarter approach I'm missing.

The target's redundant test is kept by the asm. Lever-free, we need a plain-C way to keep a redundant test. 

C0414's dead-reset: `p = expr; f(p); p = 0;` — the dead set invalidates cse's equivalence. The key: the dead set is AFTER the last use and deleted by flow (after cse). 

Apply here: the equivalence we need to break is "t == 5" recorded at the branch. A dead set of t between the branch and the test would break it — but t is used by the test, so a set between changes the value... UNLESS the set is `t = 5` (value-preserving) — but cse would know t==5 from that set too.

BUT: what if the set is `t = t;`? cse sees `(set t t)`. Does cse invalidate t's equivalence on a self-copy? It might just treat it as a no-op. We tested i1 (t=t) → 4, so no.

What about a set to a *different register that cse thinks is t's value*: e.g., `t = (s16)5;` — folds to 5.

Hmm, what about a dead set that flow deletes but cse can't fold: `t = 0;` immediately followed by `t = 5;`? k3 tested → 4. Hmm, why didn't that work? cse would process `t=0` (invalidate), then `t=5` (record const 5), then the test folds. Right.

What about `t = 0;` followed by a set of t that cse *can't* fold but that is 5 at runtime — the `a1|0x10000` trick (m5) folded. Hmm, cse is smart.

What if the restoring set is `t = (s16)(t_old)` where t_old is a *different variable* holding the old t? e.g.:
```
s16 u = t;      // before the branch (u == 5)
if (t == 5) {
    t = 0;      // dead set, flow deletes
    t = u;      // restore from u
    if (t != 3) ...
}
```
cse: t=0 invalidates; t=u — u is a variable whose value cse knows? u was set to t (==5 via the branch equivalence? the equivalence is on t; the copy u=t made BEFORE the branch means u's value isn't known until the branch... hmm, u == t and t == 5 on the fall-through, so u == 5). cse would equate u and t, and after t=0, t and u are no longer equal; `t = u` makes them equal again; then t's value = u's value = 5 → fold.

Hmm.

What if the dead set is of `u` (not t) to break the u↔t equivalence? Doesn't help; t is still 5.

OK. What if we break the equivalence by making the branch compare a *copy* and the test compare t?
```
s16 u = t;                 // u == t
if (u == 5) {              // cse records u == 5, and u == t → t == 5?
```
cse's jump equivalence on u; does it propagate to t via the u↔t equivalence? Possibly.

Let me test:
o1: 
```
        { s16 u = t;
        if (u == 5) {
            if (t != 3) { goto sel_094; }
        sel_054: ... } }
```
Hmm, the structure. Let me insert `s16 u = t;` before the `if (t == 5)` and change the condition to `u == 5`.

That's worth a test.

o2: same but the test compares `u`.

Also:
o3: make the t==5 test compare `(s16)(t + 0)`.

Let me also think about the *register* issue in g1: maybe use `if (a1 != 3)` where a1 is first copied: `s32 w = a1; if (w != 3)`. w is a fresh pseudo; gcc might allocate w to a caller-saved reg (v0/s0?) since its live range is short! That could put the compare in s0 or v0. The target compares s0 (which holds t). Hmm, if w lands in s0... but s0 holds t at that point (t is live for later uses). So no.

Hmm, unless t is dead at that point? t is used later (`D_80183478[t]`). So s0 must hold t.

Wait — actually, maybe not! In the target, at 704 the compare is `bne s0,v1` — s0 holds t. And t is used later at 740 (`addu at,at,s0` for D_80183478[t]). So s0 = t is live.

In g1, a1 is in s1 and t in s0. The compare uses s1 (a1). To match, the compare must be on s0 (t).

OK, let me test o1/o2 and then finalize.

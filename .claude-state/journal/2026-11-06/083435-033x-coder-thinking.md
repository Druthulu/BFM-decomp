---
ts: 2026-11-06T15:34:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_irLyXAqvFk08FlRjYiA8
---
Target: s0 = &D_800AF630; `addiu a0,s0,24` for both calls. Mine (c1): s0 = &D_800AF630+24; move a0,s0 both.

So target keeps the base in s0 and computes +24 per call. Mine folds the +24 into the constant (cse/combine) and shares the sum.

How to make combine keep base in s0 and add per use? The launder makes mb an unknown value, so cse can't fold `(const (plus sym 24))`. Plain-C: make mb's value opaque. Options:

1. Make mb a pointer to a struct/array and use `&((u8*)mb)[24]`? Same expression.

2. Declare mb volatile? `volatile u8 *mb` — that would change codegen differently (volatile loads). Not good.

3. Make mb come from an expression that cse can't fold: e.g. `mb = (u8 *)&D_800AF630 + (param_2 & 0)` — cse might fold &0? `(param_2 & 0)` folds to 0 at fold time. Use `(param_2 & 0x10000000)`? That changes value.

Hmm. What about using two different variables: `mb` for the base and compute `mb + 0x18` where mb is a parameter? The launder's role: "an unknown value after the first call keeps two adds off one call-crossing base". The unknown value is what matters.

C0414 dead reset: after the first call, `mb = 0;` — this makes mb's value known (0), not unknown. But it kills the cse class. Then we'd need mb back to the base for the second call — but we can't reload it without cse folding again. Unless... we set mb = 0 and then the second call uses a *different* variable `mb2` = &D_800AF630, and because the cse class was invalidated by mb=0, does cse still reuse the (plus sym 24) hash entry? The hash entry keyed by the expression is separate from register equivalence. Hmm.

Actually, let's think about how cse handles constant addresses: In cse.c, for a constant expression (SYMBOL_REF + const), it may create a register with that constant. There's code "cse_process_notes"/"cse_insn" that inserts the address into the hash table. On the second occurrence, `lookup` finds the hash entry and the register; if the register is still valid (`reg_invalid` check), it reuses it. The register holding (plus sym 24) was computed before the first call. Is it invalidated by the call? Only if the register is call-clobbered; regalloc chose s0 (callee-saved) precisely because cse wants it across the call.

The launder makes the input `mb` an unknown register value, so the second `mb + 0x18` is not the constant expression — it's a register + const, a different hash entry, and it must be computed (addiu). 

Plain-C equivalent: make mb's value unknown to cse at the second use. Ways:
- Assign mb from a function call result? e.g. `mb = (u8 *)&D_800AF630;` then the call func_8004914C is a function that could clobber memory but not mb (it's a local, passed by value). gcc knows mb's value is unchanged.
- Assign mb from an external variable: `extern u8 *D_800AF630_p; mb = ...` changes codegen.
- Use a variable that cse treats as opaque: `mb = (u8 *)&D_800AF630;` then between the calls assign mb from something opaque, but the second call must still pass the same address.

Idea: reuse the pointer variable for the base and pass `mb` where mb is computed as base+24 by a *separate* variable:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = (u8 *)&D_800AF630;
func_800491AC(mb + 0x18);
```
Let me just test. Maybe the re-set does invalidate the register equivalence for mb (the value &D_800AF630 in s0) but the sum hash entry is still valid... we'll see.

Also try:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = 0;              // C0414
mb = (u8 *)&D_800AF630;
func_800491AC(mb + 0x18);
```
The intermediate 0 might make the sum register invalid (since mb's reg equivalence changes). But the sum hash entry references the register holding (plus sym 24); setting mb=0 doesn't touch that register. Hmm.

What about making the second call's argument a different constant offset from a different symbol expression that combine folds to the same address? E.g. `func_800491AC((u8 *)&D_800AF630 + 0x10 + 8)` — cse folds constants at RTL level: (plus (symbol) 16) then +8 => (plus (symbol) 24). So same.

What about using a struct pointer with field access: `extern struct { u8 pad[0x18]; } D_800AF630_s;`... same address.

The moves file has a matching entry: line 44: "launder: p = *abase; p += 0x2D (self-reassign stales cse (plus p K) equiv, bump chain stays addiu)". This suggests self-reassign `p += K` stales the cse (plus p K) equivalence. Let's consider:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb += 0x18;
func_800491AC(mb);
```
Now the second call arg is mb (holding base+24), and target expects addiu a0,s0,24. If gcc assigns mb to s0 and computes mb+=24 into s0, then the call is move a0,s0 — not matching. But maybe gcc keeps base in s0 and computes the new mb into another reg? No, mb is the same variable.

Hmm, but wait — maybe with self-reassign, gcc keeps `mb` = base in s0 (for the first addiu) and the `mb += 0x18` becomes... it would overwrite s0. Then the second call is move. Not matching.

Alternative shape that keeps base in s0:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = (u8 *)&D_800AF630 + 0x18;   /* mb now sum */
func_800491AC(mb);
```
Here the first call needs mb+24 where mb=base. If gcc folds the first use to a constant (s0=base+24) then reassigns... hmm.

Let's just brute force a handful of variants and score them all with sc.sh (one line each). Cheap.

Variant list (replace the 3-line block):
A: re-set to base between calls.
B: mb += 0x18 then call mb.
C: two vars mb, mb2.
D: mb = 0 then mb = base then call.
E: declare mb as u8* and set `mb = (u8 *)&D_800AF630;` then first call `func_8004914C(mb + 0x18);` then `mb = (u8 *)&D_800AF630; func_800491AC(mb + 0x18);` (same as A).
F: keep mb = base; call `func_8004914C((u8 *)((s32)mb + 0x18));` and second same — the cast may produce a different RTL expression? Probably same.
G: Use an intermediate `u8 *mb2 = mb + 0x18;` no.

Let me think about what plain C produces the target exactly. Target: lui/addiu s0 = &D_800AF630; addiu a0,s0,24; call; addiu a0,s0,24; call. So the C-level shape is: a base pointer variable live across the call, and two independent `base + 24` computations. For gcc to compute +24 per call rather than fold into the constant, the base must not be a compile-time constant at the point of the addition. I.e., cse must treat mb as a runtime value.

So: make mb's initial value opaque to cse while still being &D_800AF630 at runtime. In plain C, one classic: `mb = (u8 *)&D_800AF630;` is constant. But if we get the address through a variable that cse can't see through... e.g., an extern array whose address is taken: cse knows array addresses as constants too.

What if we reuse `mb` from an earlier opaque computation? The function has other variables like param_1, param_2. E.g.:
```
mb = (u8 *)&D_800AF630;
```
Could we compute mb as `(u8 *)((s32)&D_800AF630 + (param_2 & 0x0))`? The `& 0` might not fold at tree level if param_2 is unknown? GCC folds `x & 0` to 0 always. `(param_2 * 0)` folds to 0. `(param_2 - param_2)` not folded (could). Hmm, `(param_2 & 0xFFFFFFFF)`? Identity, might fold. These are identity statements (launders) and not allowed anyway.

Hmm, but the C0414 dead reset is explicitly the sanctioned technique. Let me look at how it was used for this exact pattern. Moves line 332: "launder | func_8017BEBC | MATCH: C0414 dead reset (_pm2=0 after ReadRotMatrix; _a=0/_b=0 after func_8004974C) empties the &m2/&m3 cse class so global.c rematerialises addiu aN,sp,N per site (PARTIAL:barrier; 4 zero-byte sliders stay)".

So there, they had `_pm2 = 0` after a call to empty the cse class. In our case the base is a global symbol address. The class is `(plus (symbol_ref D_800AF630) 24)`. A dead reset of mb after the first call empties mb's equivalence, but does it empty the sum's class?

Actually maybe the right approach: after the first call, reset mb to 0, then re-assign mb to base, then second call. But the "class" of the sum may persist.

Let's just test. I'll generate variants with a script and score. Let me write a small generator.

Actually simpler: use sed to replace the block in c1.c. The block appears 3 times identically:
```
    mb = (u8 *)&D_800AF630;
    func_8004914C(mb + 0x18);
    func_800491AC(mb + 0x18);
```

For each variant I'll use python to do the replacement.

Let me write a generator script under .run/P40/T11/O05/ (allowed) that takes a body of replacement lines and generates variants. Actually simpler: write a python script that reads c1.c and produces variants.

Let me create gen.py.

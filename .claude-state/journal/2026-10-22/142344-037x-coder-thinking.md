---
ts: 2026-10-22T20:23:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_I3MtEUXHPacmS1SJg0OQ
---
In score-0, the address is materialized directly into `a1` three times (`set (reg:SI 5 a1) (plus fp 16)`) — cse folded the constant into the call-arg register at each use. No pseudo at all! That's why the target has `addiu a1,sp,16` in each delay slot. 

In c_struct, a pseudo r80 is created (single set) and local-alloc gives it s1, then a move a1,r80 per call.

So the difference: cse in score-0 keeps the constant (fp+16) as a constant and folds it into a1 at each call; in c_struct, cse creates a base register. Why? Because in c_struct the same constant appears in a *memory address* context (the movstr dest? or the final `*(Mat32*)(obj+0x34) = *(Mat32*)m` loads) and cse's `cse_insn` creates a base reg when it sees the constant used in multiple memory addresses...

Specifically: cse_insn has a block that, when a constant address (plus fp const) appears, may create a register for it ("record a base register"). It creates one when `n_uses >= 2`? In score-0 the constant is used 3 times in `set a1, plus` — but those are SETs of a1, not memory addresses; cse substitutes the constant into each. In c_struct, the constant fp+16 appears also as a *memory address* for the final loads (`lw v0,16(sp)`)? Those are direct mem refs with plus fp 16, 20, 24... Hmm, those are in both.

Actually the key: in c_struct, does the movstr use fp+16 as a *store address*? The movstr stores are `(mem (plus fp 16))`, `(plus fp 20)`, etc. Those are constant addresses; cse may create a base register for the *first* one (fp+16) because it's used both as a store address and as the call argument. Yes! In c_struct the movstr's dest store address is fp+16 (the first store), and the call arg is also fp+16 → cse creates one pseudo for fp+16 (single set) → local-alloc → s1.

In score-0, the movstr's dest stores are... also `(mem (plus fp 16))`. Hmm, then why no pseudo there? Because in score-0 cse did fold, and in c_struct it created a base. Difference: in score-0 the address fp+16 appears in the movstr stores AND in 3 `set a1` uses. In c_struct likewise. 

Hmm, but the score-0 output DOES have the same movstr stores (`sw v0,16(sp)`), and its call args are `addiu a1,sp,16`. So cse didn't create a base reg in score-0 but did in c_struct.

Difference in RTL: in score-0, the movstr was generated from scalar copies *before* cse? and in c_struct from a struct copy — maybe the movstr pattern differs: the struct copy uses `(mem:BLK)` with a pseudo address, which then forces a register, whereas the scalar-copy movstr (from loop.c?) uses constant addresses.

I'm going too deep. Practical approach: try C variants that produce the score-0 address behavior while keeping the block-move source. Since score-0's C is scalar copies (which give correct everything except the source base), what if I write the scalar copies but read the source through a *struct-typed pointer variable*:

```
Mat32 *s = &D_800AE620;
t0 = s->w0; t1 = s->w4; t2 = s->w8; m[0]=t0;...
```
cse will substitute s (constant address) into each load → lui per load (like n1). Unless reading via struct members makes cse create a base reg... The target has ONE lui. Hmm.

Alternatively, the real target C might use a *loop*:
```
int i;
for (i = 0; i < 8; i++) m[i] = ((int *)&D_800AE620)[i];
```
loop.c may unroll/optimize; the source base would be a biv in a register, and the dest stores would use an index → different code. Target has fully unrolled constant offsets, so probably not a loop.

Let me look at this from a different angle: maybe the target C is exactly:
```
m[0] = D_800AE620.w0; m[1] = D_800AE620.w4; m[2] = D_800AE620.w8; m[3] = D_800AE620.wC;
m[4] = *(int*)&D_800AE620.h10; ...
```
No.

What about the source being a *function argument*? No.

OK: another practical trick within real C: make the source address non-constant to cse by reading it from a struct member that the compiler can't prove... no.

Wait. What about `Mat32 m; m = D_800AE620;` (c_d4, 19) — same dest issue.

Let me examine what pseudo the c_struct movstr generates. Actually, let me test a targeted variant: keep the scalar-copy form (score-0 shape) but replace the pinned `src` pointer with a *struct pointer parameter copy* that cse cannot fold... Hmm, cse folds any pseudo with a constant value.

New idea: what if the source is copied via a *separate local Mat32* that is loaded from the global by a block move, then the scalar copies read from that local? That'd be: `Mat32 s = D_800AE620; m[0]=s.w0; ...` — the load from global is a block move into s (source base in a reg, one lui), then 8 loads from s to m (stack-to-stack). That adds 8 loads/stores → more insns. No.

Alternatively — maybe the answer is to accept the movstr but reduce the address pseudo's eligibility for local-alloc by making the address expression *not* fp+16 but something with 2 sets. E.g., declare m inside a nested block? The address would still be fp+16.

What if m is a struct with an offset such that the calls pass a pointer computed as `(char*)m + 0`? identity.

Hmm, what about making the movstr dest NOT m but a copy through the *call argument variable*:
```
int *mp = m;         // set 1 (after? before)
*(Mat32 *)mp = D_800AE620;
RotMatrixX(..., (void *)mp);
```
Here the dest address expression is `mp` (a pseudo) and the call args use the same pseudo mp. The movstr stores use `(mem (reg mp))`? If the movstr stores use mp as a base with offsets, then mp is a single-set pseudo used in memory addresses + call args → local-alloc gives it a reg (s1) → same as c_struct. Hmm.

Unless mp is set twice. What if:
```
*(Mat32 *)m = D_800AE620;
mp = m;
```
Then the movstr dest is the constant (fp+16) folded into stores; mp is set after. That's variant v2. cse may equate mp with fp+16 and fold it into the call args (like score-0!) — if cse prefers constants for `set a1, (const addr)` (it does fold constants into insns: cse_insn replaces a reg with its constant value if cheaper). In c_struct, why didn't cse fold the call args' fp+16 into a1? Because cse had already created a base register pseudo for fp+16 (due to the movstr dest store), and once a base reg exists, uses get rewritten to that pseudo.

If mp is set AFTER the movstr, then at the time cse processes the calls, mp has a known constant value (fp+16) and cse may substitute the constant directly into a1 (as in score-0) — giving addiu a1,sp,16 per call! That's exactly v2. Let me test v2. 

v2:
```
    int *mp;
    ...
        *(Mat32 *)m = D_800AE620;
        mp = m;
        RotMatrixX((int)*(short *)(obj + 0x10), (void *)mp);
        RotMatrixZ(...(void *)mp);
        RotMatrixY(...(void *)mp);
```
Cse processes linearly: the movstr stores with constant addresses; then `mp = fp+16` (set); then at each call, `set a1, mp` → cse replaces mp with its constant (a pseudo with a single set of a constant gets folded? cse's `cse_insn` records the constant in the table and substitutes it into later uses when the value is cheaper/valid; for a call argument, substituting a constant is fine).

Let me test this and a few siblings. Time to batch.

Also v4: same but with `Mat32 *mp` and calls `(void *)mp`.
And v5: `mp = (int *)m;` after copy with calls `(void *)mp`.
And v6: copy via d then mp after.
And v7: `*(Mat32 *)m = D_800AE620;` then `t0 = (int)m;`? no.

Let me write the generator and score.

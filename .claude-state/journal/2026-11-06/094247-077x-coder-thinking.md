---
ts: 2026-11-06T16:42:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3pBiW6tqrYAVwjdLs8Dd
---
Block1 (then): registers 77 (4 refs, 7 insns, dies 2 places) = p; 78 (2 refs, 4 insns) = f? Wait: 77 used 4 times/7 insns; 78 used 2 times/4 insns; 79 2/2; 80 2/2.

Hmm: p is 77 (4 refs), f is 78? f: `f = mem` (def), `f & mask` (use) = 2 refs across 4 insns. Yes 78=f.

Block2 (else): 81 (4 refs, 7 insns, dies 2) = q; 82 (4 refs, 6 insns) = g; 83 (2/2) = ?

Priority = floor_log2(n)*n*size/(death-birth). For p(77): n=4 → 8. For f(78): n=2 → 2. life: p from insn 36 to 50 (15), f from 39 to 45 (6). pri_p = 8/15=0.53, pri_f=2/6=0.33 → p wins v0. Target wants f in v0.

For q(81): n=4 → 8, life from 60 to 75 (15) → 0.53. g(82): n=4 → 8, life from 63 to 72 (9) → 0.89 → g wins v0. Target wants q in v0.

So in both arms, the *longer-lived* pseudo should win v0 in the target, contradicting priority. That's because the pins forced it (f=$2, g=$3). Hmm, wait: f pinned $2 and g pinned $3. In the then arm, f→v0; in the else, g→v1. So both arms' allocation was determined by pins.

Now we must reproduce with C. Hmm, what real C would give f=v0 and p=v1? f is the unkDC value; p is the unk20→u16. In the original source, maybe the order of operations differs, e.g., `self->unkDC = (f = ...) & mask`... 

Think about the *original* source (what Square wrote). Likely something like:

```c
if (flag == 0) {
    sp18 = self->unk20;
    self->unkDC &= ~0x80;
    self->unk100 = *(u16 *)(sp18 + 0x18);
} else {
    sp18 = self->unk20;
    self->unkDC |= 0x80;
    self->unk104 = *(u16 *)(sp18 + 0x18);
}
```
Hmm, that would produce a memory read-modify-write for unkDC (lw/ori/sw with a temp). The temp for `unkDC & mask` is a fresh pseudo with 2 refs.

Let me reconsider the target instructions:
then:
```
li a0,-129
lw v1,32(a1)     ; p = self->unk20
lw v0,220(a1)    ; f = self->unkDC
lhu v1,24(v1)    ; p = *(u16*)(p+0x18)
and v0,v0,a0     ; f &= mask
sw v0,220(a1)
j end
sh v1,256(a1)
```
The scheduler put the p load first, then f load, then the lhu. The register assignment f=v0, p=v1.

If the C were `self->unkDC &= ~0x80;` (read-modify-write) with no explicit f, the RTL would be `(set (mem) (and (mem) const))` and combine/expand creates a temp. The temp's refs: 2 (def and use). Its life is short (load to store). p has 4 refs and longer life. Priority: temp 2/2=1 vs p 8/15=0.53 → temp wins v0. That gives f_temp=v0, p=v1! Exactly the target.

Similarly in the else, `self->unkDC |= 0x80;` — the temp has 2 refs short life → wins v0, but target has q in v0 and g in v1. Hmm, that's the opposite: in the else, q must win v0.

Unless in the else, the RMW temp (g) is created later and q's birth is earlier... priority: q 8/15=0.53, g_temp 2/2=1 → g wins v0. But target q=v0.

Hmm. So the else's target allocation (q=v0, g=v1) is not what a RMW would give.

Unless in the else the source order is different: maybe `self->unk104 = *(u16*)(q+0x18);` is computed *before* the unkDC update? Instruction order in target else: lw q, lw g, lhu q, ori g, sw g, sh q. The lhu is between the two loads. If the C order were: q = self->unk20; g = self->unkDC; q = *(u16*)(q+0x18); g |= 0x80; ... that's the current order.

Let me compute priorities with the actual qty_death/birth. q's live range: birth at insn 60 (lw), death at 75 (sh). g: birth 63, death 72. Hmm.

Alternatively, maybe the else's q gets v0 because g is *pinned by the mask*? No.

Hold on — maybe the real source of the else arm used `q` for the unk20 pointer and `g` was not a variable: `self->unkDC |= 0x80;` — RMW temp. Then in local-alloc the temp and q compete: q 8/15=0.53 vs temp 2/life. Temp's life: lw at some point to sw; maybe 3 insns → 2/3=0.67 > 0.53 → temp wins v0. Still not q.

Hmm, what if the RMW temp is NOT a separate pseudo but the store is `(mem) = (ior (mem) const)`, and combine/expand uses a pseudo that is combined with q's register? Unclear.

Let me approach empirically: generate variants for each arm and score. Since score is a global count, a variant that fixes one arm should drop the score. Let me build a generator with arm variants and test all combinations? 3 self × ~6 then × ~6 else = 108 scores (~2 min). That's acceptable but let me be smarter: first fix the then arm with the else as is; then fix the else.

Since s13 fixed the base registers (a1 everywhere), use s13 as the base and vary arms.

Then-arm variants:
T1: current (p,f; p=v0,f=v1)
T2: field-direct `self->unkDC &= mask;` with p temp
T3: `p` split into t/v
T4: order: f load before p load
T5: `self->unkDC = self->unkDC & mask;` (same as T2)
T6: assign f then p:
```
p = self->unk20; f = self->unkDC; ...
```
already.
T7: `f &= mask; self->unkDC = f;` (split statement) — might change refs/life.
T8: `p = *(u16 *)(self->unk20 + 0x18);` (single expression, no p temp reuse) — creates p once from the memory load, with the address temp inline.

Else-arm variants:
E1: current
E2: field-direct `self->unkDC |= 0x80;` with q temp
E3: g assigned first
E4: q via single expression `q = *(u16 *)(self->unk20 + 0x18);`
E5: `g = self->unkDC | 0x80; self->unkDC = g;` (single statement)
E6: q computed first, then g.

Let me generate combinations of T variants (with E1) first.

Actually the score is a masked diff count; a partial fix may reduce it. Let me generate T1..T8 with E1 and score.

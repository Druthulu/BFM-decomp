---
ts: 2026-11-06T16:31:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PYfFvX955F273MUaYEql
---
Priority = floor_log2(refs)*refs*size / (death-birth). So lifetime matters: a shorter-lived qty gets higher priority (division by life). q in else: refs 2 (load + lhu), life from load to sh. g: refs 2, life from load to sw. g's sw is earlier than q's sh, so g has shorter life → higher priority → g gets v0 first. That's exactly mine. Target has q in v0, g in v1, opposite priority!

How did the original (pinned) get q=v0? Because g was pinned to v1, so q got v0 by default. So target allocation is purely a consequence of pins. To get q in v0 without pin, we need q to have priority over g. Make q's life shorter or refs higher.

Idea: reorder statements so that q's last use comes before g's? In target order:
```
lw v0,32(a1)   q load
lw v1,220(a1)  g load
lhu v0,24(v0)
ori v1,v1,0x80
sw v1,220(a1)
sh v0,260(a1)
```
g dies at sw (ins 5), q dies at sh (ins 6). So g shorter. Priority: g higher. Yet target q=v0 due to pin.

To make q higher priority: increase q's refs? refs affects floor_log2(n)*n: refs 2 → 1*2=2; refs 3 → 1*3=3; refs 4 → 2*4=8. So one extra reference to q could boost it. But the extra reference must not emit instructions... In the worked example C0535/C0414, they used `do { r = p + i; } while (0);` to add a ref (loop-weighted). Here no loop. A `do { q2 = q; } while(0)` adds a copy instruction. Hmm, "identity-statement launders do NOT count as a crack" — but that's about launders (identity address spellings) counting as cracks; adding a real ref via do-while is C0535 technique, but `do{}while(0)` needs `// !FAKE: do-while` and C0535 says it splits cse1 EBB... Actually C0535 is "do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item".

Alternatively reduce g's life: make g's load later? It's already. Or restructure so g is computed directly into the store: `self->unkDC = (self->unkDC) | 0x80;` — read-modify-write on memory! That's field-direct: no g temp at all. Then only q is a temp → q gets v0 naturally. But target has `lw v1,220; ori v1; sw v1,220` — that's exactly what a read-modify-write produces (a temp internally). And `self->unkDC |= 0x80;` uses an anonymous temp with 2 refs, but its allocation: with q also live, priority decides. Hmm.

Wait — maybe simpler: the original C in the src isn't necessarily the "natural" source. Let's think about what the actual original source probably was. This is a decomp; target bytes come from the original compiled code. The original source likely did:

```
if (flag == 0) {
    ...
    s = p->unk20;
    ...
    self->unkDC &= ~0x80;
    self->unk100 = *(u16*)(s+0x18);
} else {
    ...
    self->unkDC |= 0x80;
    self->unk104 = *(u16*)(q+0x18);
}
```

Hmm. But we must match exact register allocation, which is a compiler artifact.

Let me just try empirical variants. Candidate set:

1. pointer self + field-direct else (`self->unkDC |= 0x80`) and then-arm `self->unkDC &= ~0x80`, with q/p temps.
2. Keep current but else uses `g = self->unkDC | 0x80;` and reorder declarations.

Let me first test pointer self alone (candidate A) to see whether a1 propagates to else.

Actually wait. Maybe the cleanest: the else arm can reference self through a *different* expression that isn't cse-equivalent: e.g., `q = ((Unkstruct_8017EAD8_2 *)arg0)->unk20;` no.

Let's think about what makes the target's else arm use a1 while then arm uses a1. If self is a genuine separate pseudo, both use it. The simplest genuine separate pseudo without extra instructions: a copy whose source is not arg0 itself but something else that happens to equal arg0 — no.

Another angle: give the function's param a "copy" by assigning arg0 to itself? no.

What about declaring self as a `u32` and using `self` in the if condition? e.g. `if (flag == 0)`. Hmm.

Actually! Consider `self = (s32)arg0;` where self is declared as `Unkstruct_8017EAD8_2 *`? Pmode==SImode.

Try: `Unkstruct_8017EAD8_2 *self = (Unkstruct_8017EAD8_2 *)arg0;` and then `self->unkAA` etc. The pointer type may cause gcc to use a different reg class? No, same.

Hmm, but there's a subtlety: cse canonical prefers fixed hard regs (a0). For the pointer pseudo, cse would still equate with a0? The copy is `(reg:P self) (reg:SI a0)`? Mode mismatch Pmode=SI so no subreg. Should equate.

OK what about making the copy happen through a store? No.

Alternative: Prevent a0 from being the base in the else arm by having a0 dead at the branch. If a0's value is clobbered on the path to else, uses must go to a1. What can clobber a0 before the branch without emitting an instruction? The mask `~0x80` assignment emits `li a0,-129`. If we place `mask = ~0x80;` before the if, the li a0 appears before bnez. Target's li is after bnez (line: bnez at 2c2c; li at 2c34 which is the then block start). But could sched1 move the li into the branch delay slot or after? Actually the bnez delay slot is filled by `sw zero,28(a1)`. So no.

But what if the mask assignment is in the else arm too? i.e., compute mask in both arms:
```
if (flag == 0) { mask = ~0x80; ... } else { mask = ~0x80; ... }
```
Then in else arm, `li a0,-129` would appear, and then self uses would go to a1! But target's else arm has no li a0. Unless the else's li is cse'd away as redundant? cse2 could remove the second li? No, different block, but cse across blocks: the value of a0 (constant -129) at the join... The else arm doesn't use mask. The li would remain unless dead-code eliminated. If mask is used only in then arm, assigning it in else is dead code — gcc's dead code elimination at RTL (dce) would remove it. Then a0 is not clobbered in else → back to a0 base. Hmm.

Unless the else's mask assignment is used... no.

OK, alternative: use a different variable to clobber a0 in the else arm, but one that's genuinely needed and dead-code-proof. Hmm, no.

Let me reconsider: maybe there's a natural source where self is a *pointer parameter* in the actual original code, and the decompiled body used `arg0` as s32. The signature is `void func_8017EAD8(arg0) s32 arg0;` — K&R. In the original source, the parameter was probably `u8 *arg0` or a struct pointer, so the copy `move a1,a0` came from the compiler saving the param because... hmm no, a pointer param wouldn't be copied.

Wait, actually why does the target have `move a1,a0` at all? Because the original source likely had a local copy: e.g. `u8 *p = arg0;`. That copy is a pseudo → a1. And with `self` a real variable, the compiler kept it.

For a *pointer* copy, cse would equate it with a0 too... unless the pseudo was needed because of register pressure. Hmm.

Let me test empirically: pointer self. Also test `u8 *self = (u8 *)arg0;` with casts at uses. Let's just run a few candidates and look at the diffs.

Also fix the then-arm p/f swap. Let's create several candidates:

c1: pointer self (struct), current field accesses; declarations p,f order unchanged.
c2: pointer self + declare f before p.
c3: pointer self + declare g before q in else.

Let me write c1 and score.

Actually, hold on. Maybe simpler for p/f: in the then arm target has f in v0 (pinned $2). Without pin: p declared first gets v0 (as observed). To give f priority over p: f's life must be shorter or refs higher. f: load, and, store → refs 2 (def + use in and? Actually f used in `f & mask`, then result stored). Life from load to and. p: load, lhu (use), store sh. Life from load to sh (later). So f already has shorter life → higher priority → f should get v0! But mine gave p v0. Hmm, why? Because mask is a0 fixed; both p and f want caller-saved. Priority: f shorter → v0. But mine gave p=v0, f=v1. So my model is off. Maybe because p and f are in the same qty? No, different pseudos.

Wait, maybe the order of *birth*: p's birth is at its load insn; f's birth at its load. The qty priority divides by (death-birth). p: death at sh (ins 12/13), birth at lw. f: death at and, birth at lw. f shorter → higher priority. Unless... hmm.

Actually, note that in mine, the loads are: `lw v0,32(a1)` (p) and `lw v1,220(a1)` (f). If f had priority, it'd be assigned v0 first, and p v1. So mine contradicts. Unless the register *used in the load* is decided by local-alloc differently: each pseudo's assigned reg is used as the load destination. Yes.

Let me check qty priority computation: qty_n_refs counts references. For p: load (def) + lhu use + ... maybe also the address computation? p = self->unk20 is a load into p. Then `p = *(u16*)(p+0x18)` — p used in address, then redefined. In RTL, this is `(set p (mem (plus p 0x18)))`? That's 1 def + 1 use in the same insn, then sh uses it. Hmm.

f: `f = self->unkDC` def; `f & mask` use; store. refs 2.
p: def (load), use in address, def (lhu), use (sh) = refs 4? If n_refs counts both uses and defs: p=4, f=2 → floor_log2(4)*4=8 vs 1*2=2 → p higher priority → p gets v0. That explains mine!

And the pinned version had f pinned to v0, so p took v1.

To make f get v0 without pin: reduce p's refs. p is loaded then reassigned via `p = *(u16*)(p + 0x18)`. Split into two variables: `s32 t = self->unk20; s32 v = *(u16*)(t+0x18);` then t has refs 2 and v refs... v: def + sh use = 2. Hmm, then t and v both refs 2, life short. Which gets v0? t birth load, death lhu; v birth lhu, death sh. v is shorter → higher priority? v gets v0. But target wants f (the unkDC value) in v0 and p in v1. So we'd have f=?, v=? Three temps now: t (addr), v (loaded u16), f (unkDC). Target only 2 temps: v1 = loaded u16? Let's map target again:

```
li a0,-129          mask
lw v1,32(a1)        t = self->unk20
lw v0,220(a1)       f = self->unkDC
lhu v1,24(v1)       v = *(u16*)(t+0x18)  -> v1 (reuses t's reg!)
and v0,v0,a0
sw v0,220(a1)
j
sh v1,256(a1)
```
Note: t and v share v1 because t dies at the lhu. So the C could be `p = *(u16*)(p + 0x18)` with p in v1. Target: p in v1, f in v0.

So we need f priority > p priority. Options:
- Split p into two vars (t and v): then pseudos t (refs2, life 1), v (refs2, life 1), f (refs2, life 1). All equal-ish; ties by qty number: t created first gets v0. Bad (t=v0).
- Increase f's refs: add a use of f? e.g., `mask = ~0x80;` no. Use f in the store twice? Hmm.
- Reduce p's refs by writing it as two statements with an intermediate.

Actually simplest: declare and compute in a different order such that sched1/reg allocation differ. But priority is by refs.

What about: `f` gets an extra reference cheaply — e.g., `self->unkDC = f & mask;` and also use f in the then arm for something? no.

Alternatively make p's refs = 2 by loading it into a *separate* temp used once:
```
s32 t = self->unk20;
s32 v = *(u16 *)(t + 0x18);
```
t refs: def + use = 2. v refs: def + use(sh) = 2. f refs 2. Ties by qty number: t first, v second, f third → t=v0. Not good.

Hmm, what if we order f's declaration/creation before t? Pseudos are created at block entry in declaration order... but priority ties broken by qty number (creation order). If f declared first (lowest qty), and all refs equal, f gets v0! But the assignment order in C: we need the loads in target order (t load, f load). Declarations can be reordered independent of assignment order? The pseudo is created at the declaration (expand_decl at block start). If f declared before p but assigned after, the load order stays p then f, and f has the lower qty → v0. 

But is expand_decl creating pseudos at declaration for all locals? In gcc 2.7.2, `expand_decl` is called when a declaration is encountered (at block scope start), and it does `expand_decl_init` and assigns a pseudo via `assign_parm`? Let me check: for uninitialized locals, expand_decl may not create a register until first use (it calls `expand_decl` → for VAR_DECL, if TREE_STATIC... else `expand_decl_cleanup`... The pseudo is created in `expand_decl`? Actually `expand_decl` for an automatic var calls `layout_decl` and `expand_decl_init`; the register is created lazily in `use_variable` (get_reg). Hmm, in gcc, `expand_decl` does not allocate a reg for uninitialized scalars; regs are created on first reference via `expand_expr` → `get_reg`. So the pseudo number order = first-reference order in the C code, roughly.

But wait, if initialized at declaration (`s32 f = self->unkDC;`), the reg is created at the declaration point.

So to get f a lower pseudo number than p while emitting p's load first, we could:
```
s32 f = self->unkDC;   /* creates f first, emits load first though */
s32 p = self->unk20;   /* p load second */
```
That emits f load first — target has p load first. But sched1 might reorder? Both loads independent; sched1 tends to keep order. Hmm, but target order: `lw v1,32(a1)` then `lw v0,220(a1)`. If C emits f load then p load, we'd get f first. sched1 might reorder based on register pressure... risky but testable.

Alternatively, declare f in an earlier scope? e.g. at function top: `s32 f;` — no ref yet. To create the pseudo early without emitting code... `s32 f;` then `f = 0;`? That emits li.

Hmm, what about making the then arm:
```
mask = ~0x80;
f = self->unkDC;
p = self->unk20;
p = *(u16 *)(p + 0x18);
self->unkDC = f & mask;
self->unk100 = p;
```
This emits f load before p load. But target p load first. sched1 might swap. Let's just test variants empirically — scoring is cheap (~1s).

Actually, another thought: maybe use `mask` differently. Target `li a0,-129` is before the p/f loads. In C, mask=~0x80 assigned first → li first. Good, current code does that.

Let me set up a quick loop: write several candidate files, run sc.sh. Let me generate them with a small script? I can write files via Write tool individually, but many variants. Better: write a Python generator under the item dir that emits variants and runs sc.sh. That's allowed (scratch under item dir). But brief says one action per command; scripts are fine.

Let me first try the pointer-self idea + f-before-p ordering.

Let me write a generator gen.py that takes a few flags? Simpler: write candidates manually with Write (each is small). But many iterations... Let me write a generator producing a dozen variants from parameterized body.

Plan the body template:

```c
void func_8017EAD8(arg0)
s32 arg0;
{
    SELF_TYPE self;
    s32 mask;
    s32 flag;

    self = SELF_INIT;
    flag = SELF_CAST(self)->unkAA;
    ...
}
```

Variants:
- self type: s32 (current), or pointer struct.
- then: p/f decl order, assignment order, split temps.
- else: q/g decl order, field-direct.

Let me write a generator with explicit variant list. Actually, empirical data first: test pointer self quickly with a single edit.

I'll write win2.c with pointer self and see if a1 appears in else.

Note the struct type name Unkstruct_8017EAD8_2 — need to confirm fields. It's used in src; fine.

Let me write win2.c.

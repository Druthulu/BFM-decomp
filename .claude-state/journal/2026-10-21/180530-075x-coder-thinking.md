---
ts: 2026-10-22T00:05:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_tcIPGRHHHDdrYitXeKCv
---
e3 (typed pointer) changed the addressing: mine uses `lui at,0x0` + `sw v0,16(at)` (absolute addressing with `at` = $1) whereas the target uses `sw v0,16(v1)` (register base).

Interesting! With the typed pointer, gcc used the `at` register for the global address instead of keeping it in v1.

Wait, that's the opposite of what I want. The target keeps the pointer in v1 and uses `sw v0,16(v1)`.

Hmm, e3's diff: mine[3]=`lui v0,0x0`, mine[4]=`lw v0,16(v0)` (the load) and mine[7]=`lui at,0x0`, mine[8]=`sw v0,16(at)`.

So in e3, gcc did NOT keep the address in a register; it materialized the address twice (once in v0 for the load, once in `at` for the store).

Hmm, because `p` was... hmm, in e3, p is a typed pointer and the stores use p. But gcc used `at`?! That means p's value was recomputed from the constant address rather than kept.

Hmm, that's because `D_801151D4` is `extern s32` and `&D_801151D4` — gcc 2.7 treats the address as a constant → `lui at,0` + `sw v0,16(at)`. And p's value (the loaded pointer) was only used for the FIRST access (`p->unk10` read) — wait no: `p = (Unkstruct_80126948 *)&D_801151D4;` — I wrote `&D_801151D4` not `D_801151D4`! Oops. The original code is `p = D_801151D4;` (p holds the VALUE at D_801151D4), and `((Unkstruct_80126948 *)p)->unk10` dereferences p.

In e3 I wrote `p = (Unkstruct_80126948 *)&D_801151D4;` — that's the ADDRESS, not the value! Semantically different! And the target's `lui v1; lw v1,0(v1)` = load the value ✓.

So e3 is semantically WRONG. But it scored better?! Because the diff is only about instruction matching. Anyway, e3 is not valid.

Let me fix e3: `p = (Unkstruct_80126948 *)D_801151D4;` (the value, cast to a pointer).

Then the RTL: `lui v1; lw v1,0(v1)` → p; `lw v0,16(v1)`.

Hmm, that's the same as c1 but with typed accesses. The difference from c1: in c1, `((Unkstruct_80126948 *)p)->unk10` — the cast of an s32 to a pointer. With the typed p, the accesses are direct.

But then why did e3 (with the wrong semantics) produce `lui at` for the stores? Because p was the ADDRESS constant, so gcc folded `p->unk10` into `*(at + 16)`.

Let me redo e3 correctly: `p = (Unkstruct_80126948 *)D_801151D4;` Hmm, but casting an s32 value to a pointer: gcc 2.7 would treat it as an address in a register (not a constant) → `lw v0,16(v1)` ✓.

Let me also think about what else could flip v0/v1.

Hmm, since e3 (wrong) showed `lui at` + `sw v0,16(at)`, the "at" register is used for constant addresses.

Let me think again about the target:
```
lui v1,0x0
lw v1,0(v1)     <- p (the value at D_801151D4)
lw v0,16(v1)    <- v0 = p->unk10
li a0,10
addiu v0,v0,-3
sw v0,16(v1)
jal
sw v0,20(v1)    (delay slot)
```

So p is in v1 and the value in v0. In mine (c1): p in v0, value in v1.

Idea: what if the value variable is used more, or p is used fewer times?

Hmm, what if the two stores are combined? `((Unkstruct_80126948 *)p)->unk10 = v0; ((Unkstruct_80126948 *)p)->unk14 = v0;` — two stores. The target has both.

Hmm. What if we use a struct pointer typed version:
```c
Unkstruct_80126948 *p;
p = (Unkstruct_80126948 *)D_801151D4;
v0 = p->unk10;
v0 = v0 - 3;
p->unk10 = v0;
p->unk14 = v0;
```
This should generate the same instructions as c1 but maybe with a different allocation. Let me try.

Another idea: the ORDER of the two uses. In the target, `sw v0,16(v1)` comes before the jal and `sw v0,20(v1)` in the delay slot. Mine has `sw v1,20(v0)` at 11 and the jal at 10? Let me look at mine's asm (c1) to see the layout.

From the diff of c1: mine[11]=`sw v1,20(v0)`, mine[12]=`bnez v0,...`. And target[11]=`sw v0,20(v1)`, target[12]=`bnez v0,...`. So the layout is the same, only the regs are swapped.

So ONLY the register assignment differs. Good — a pure allocation issue.

So I need to flip v0 ↔ v1 between two locals. This is the classic "local-alloc order" problem. The lever per moves.md: "lreg-qty-order" / "lreg-qty-priority" / "lreg-v0-local-first".

"lreg-v0-local-first" — the wall tag from moves.md line 26: "pin | func_80188680 | WALL lreg-v0-local-first — local-alloc gives block-local cmp temps v0 before global ret(r77) is allocated; target needs ret in v0 live across blocks (best 6)".

So there's a known wall mechanism "lreg-v0-local-first".

For our case: local-alloc gives v0 to p (created first) and v1 to the value. The target gives v0 to the value and v1 to p.

So I need the VALUE pseudo to be allocated first. That means its allocno must be lower. The allocno numbers are assigned by the RTL order of the pseudo's first appearance... Actually, pseudo numbers in gcc are assigned during expand (the RTL is generated in order). The `p` pseudo is created when `p = D_801151D4` is expanded (before the value's load).

Hmm! Unless... the value's load doesn't create a new pseudo but reuses something.

Hmm, what if we swap the source so that the value is loaded BEFORE p is assigned? We need p for the load though... unless we use D_801151D4 directly:

```c
v0 = ((Unkstruct_80126948 *)D_801151D4)->unk10;   /* WRONG: dereferences the address, not the value */
```
The original semantics: p = *(&D_801151D4) i.e. p = the s32 stored at D_801151D4; then p->unk10.

So `((Unkstruct_80126948 *)p)->unk10` where p = D_801151D4 (the VALUE).

To load the value's field without a variable:
`v0 = *((Unkstruct_80126948 *)(*(s32 *)&D_801151D4))->unk10;` — hmm, that's the same thing but written inline. The RTL would be:
```
lui v1, 0
lw v1, 0(v1)      <- the pointer value (this is p's pseudo!)
lw v0, 16(v1)
```
Still the pointer pseudo is created first. ✗

Hmm. So the pointer pseudo is always created before the value pseudo. And local-alloc gives it v0.

⇒ How did the target get v1 for the pointer? Because the ORIGINAL compiler allocated differently. For gcc 2.7.2, we need to change local-alloc's choice.

Since local-alloc's choice for the FIRST local is essentially "the first reg in the local reg order", and the local reg order for MIPS might be v0, v1, v2... Hmm, but maybe the order is by "local_size" then by the allocno. If both have the same size, the order is by allocno.

⇒ Make the value pseudo have a LOWER allocno? Impossible (it's created later).

⇒ OR make the pointer pseudo have a HIGHER local_size (needing more regs)? E.g. if p were a struct type requiring 2 regs? Nah.

⇒ OR make the value pseudo get allocated first via a different mechanism: e.g., if the value pseudo is a "global" (crosses a call) while p is a local. Then global-alloc handles the value → the value gets v0 (the first global reg?) hmm, globals get callee-saved regs.

Hmm! Interesting idea: if the value variable crosses a call, it'd be global → callee-saved → mismatch with the target (v0 is caller-saved).

Hmm.

Wait, actually, let me reconsider: maybe local-alloc's order isn't by allocno but by the "local reg" preference where a pseudo with more refs gets a better reg. Let me count refs more carefully:

p: set(1), 3 uses → 4 refs.
value: set(1), read+set(2,3), 2 uses(4,5) → 5 refs.

Hmm. But maybe gcc counts the value's `v0 = v0 - 3` as a separate copy...

Let me test the hypothesis "more refs → better reg" by making p have MORE refs. E.g., add a redundant read of p? That changes the code ✗.

Alternatively make the value have FEWER refs: e2 (`v0 = ...unk10 - 3`) gave 19 — no change (same 58 ins). Hmm, e2's diff? It scored the same as c1 (19) so no change.

Hmm, so refs don't matter → it's allocno order.

Hmm, so how to flip?!

**IDEA**: What if the value pseudo is created FIRST because the pointer's value is loaded via an expression that reuses the value pseudo? Like:

```c
v0 = D_801151D4;              /* v0 = the pointer value (p's pseudo!) */
```
Hmm, then p would be a copy of v0 → extra move ✗.

**IDEA**: What if we don't use a variable for the pointer but reuse `a0`? No, a0 is used later.

**IDEA**: What if the pointer is stored in the SAME variable as the value? Like:
```c
s32 p;
p = D_801151D4;
v0 = p->unk10;   /* v0 */
```
Hmm.

**IDEA**: What if we could make gcc allocate the value to v0 because the value pseudo is the one that "crosses the call"? Hmm.

Hold on, let me reconsider the local-alloc behavior in gcc 2.7: `allocate_local_regions` processes the locals in the order of the "local_regs" array, which is built by scanning `reg_alloc_order`? Hmm.

Actually, I recall gcc 2.7's local.c:

```c
static int
allocate_local_regions (max_reg, max_reg_num, reg_last_freq)
{
  ...
  /* First, mark all the local registers.  */
  ...
  /* Now allocate a register for each local variable.  */
  ...
  for (pass = 0; pass < 2; pass++)
    for (reg = 0; reg < max_reg; reg++)
      for (i = 0; i < n; i++)
	{
	  ...
	  reg2 = local_reg[i];
	  ...
	  /* If we are playing safe, ... */
	  ...
	  /* Now, allocate a register for this local. */
	  ...
	}
```

The key detail: gcc 2.7's local-alloc has a special rule: "if a local is live across a call, it must be in a callee-saved reg" and there's the notion of `local_size` and the order in which locals are processed, which is by DECREASING "local_size" then by increasing regno.

Hmm, both p and value have local_size 1.

Hmm, hmm. Let me look at the actual outcome from a different angle: maybe I can make the VALUE pseudo be created first by writing the source so that the pointer value is loaded as part of the value's expression:

```c
s32 p;
s32 v0;
p = D_801151D4;
v0 = ((Unkstruct_80126948 *)p)->unk10;
```

The expand order: `p = D_801151D4` → the load into p's pseudo. Then `v0 = p->unk10` → the load into v0's pseudo.

What if instead:
```c
v0 = ((Unkstruct_80126948 *)D_801151D4)->unk10;   /* p's value loaded into an address temp, then v0 */
```
RTL: lui v1; lw v1,0(v1) [the temp = p's value]; lw v0,16(v1). The temp is created first ✗.

Hmm. So no.

**IDEA**: make the pointer's pseudo NOT a local but part of the "address" — e.g., use a global variable directly:
```c
v0 = ((Unkstruct_80126948 *)D_801151D4)->unk10;
```
Hmm, but that's the wrong semantics (D_801151D4 is an s32 variable, and `((Unkstruct*)D_801151D4)` casts the VALUE 0x801151D4 as a pointer — wrong!). Hmm, wait: in the original source `p = D_801151D4;` loads the VALUE stored at D_801151D4 (a runtime pointer). Then `((Unkstruct_80126948 *)p)->unk10` dereferences it. So the semantics require the load.

OK so the pointer pseudo must be created first.

⇒ Hmm. So how can the target have the pointer in v1?

**IDEA**: what if the value pseudo is a "global" (allocated by global-alloc to a callee-saved reg)? No, the target has v0 (caller-saved).

**IDEA**: What if there's an extra local that takes v0? Then the pointer would take v1 and the value v2 — ✗ (the target has value in v0).

Hmm!! Unless the value pseudo is created before the pointer pseudo.

Hmm, what if the pointer value is loaded via a **call**? no.

What if the pointer pseudo is created LATER because the pointer is assigned from a function call? no.

Hmm, what if the source loads the pointer TWICE (once for the read, once for the stores) — then there are two pointer pseudos, and the second would be created after v0! Hmm:
```c
v0 = ((Unkstruct_80126948 *)D_801151D4)->unk10;   /* creates temp1 then v0 */
```
Hmm no: the temp (address) is created first.

Hmm, wait. Actually hold on! What if the pointer's pseudo is NOT created by the load but the load result goes DIRECTLY into v0's expression? Like:
```c
v0 = *(s32 *)((s32)(((Unkstruct_80126948 *)D_801151D4)->unk10));
```
no.

Hmm, let me think about the RTL for `v0 = ((Unkstruct_80126948 *)p)->unk10` where p is a pseudo:
- The address is p+16 → a new pseudo (or an "offset" addressing mode).
- The load: `set v0 (mem (plus p 16))`.

So the value pseudo v0 is created when the load is expanded. The address pseudo (p+16) might be a separate pseudo! In gcc's expand, `mem (plus (reg p) (const_int 16))` — the plus is usually simplified into the mem's address with an offset. Hmm, but gcc often creates a separate pseudo for the address.

So the order of pseudo creation: p (from the load), then possibly an address pseudo, then v0.

Hmm.

OK, let me try the empirical approach with a few more variants:
f1: `Unkstruct_80126948 *p; p = (Unkstruct_80126948 *)D_801151D4; v0 = p->unk10; ...` (typed, correct semantics)
f2: use `p` as s32 but access via a typed temp:
```c
s32 p;
Unkstruct_80126948 *q;
p = D_801151D4;
q = (Unkstruct_80126948 *)p;
v0 = q->unk10;
```
Hmm, that adds a copy.

f3: swap the order of the two stores (unk14 first, then unk10)? That changes the instruction order ✗ (the target has unk10 first).

f4: make the value a `u32`? tried (e5), no change.

f5: change `v0 = v0 - 3;` to `v0 -= 3;`? same.

f6: What if we introduce the value through a different expression: `v0 = ((Unkstruct_80126948 *)p)->unk10;` → `v0 = p[4];` hmm (unk10 = offset 16 = p[4] as s32*). Let's see: `((Unkstruct_80126948 *)p)->unk10` — what is unk10's offset? The target does `lw v0,16(v1)` → offset 16 = 0x10. But the field is named unk10 (hex 0x10) ✓.

f7: What if the value variable is declared BEFORE p and the assignments are p first? (e1 — no change).

Hmm. Let me think about gcc's local-alloc once more.

AH WAIT!!! Maybe the key is `reg_last_freq`! gcc 2.7's local-alloc: `find_reg` chooses among the candidate registers using `reg_last_freq[reg]` — the frequency of the last use of that register — to prefer a register whose last use is rare. Hmm, that's about which reg to pick among conflicting ones.

Alternatively, gcc 2.7's local.c `allocate_local_regions`:
```c
	  /* Now, allocate a register for this local.  */
	  ...
	  if (reg2 >= 0) ...
```
Hmm.

OK, let me look at the "local reg" preference order for MIPS in gcc 2.7. In gcc 2.7's config/mips-mips.h or mach-dep.c, `REG_ALLOC_ORDER` for MIPS is typically:

```c
int reg_alloc_order[] = {
    /* Register numbers for allocatable registers:
       0-31 are the standard MIPS registers; 32-63 are the machine registers.
       The order here is the order in which the registers are allocated.  */
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    ...
```
Hmm, if the order were 0,1,2,... then the first local would get reg 0 (=$0 zero!) — no, $0 is excluded.

Hmm, in gcc 2.7's mach-dep.c, the MIPS `LOCAL_REGNO`... hmm.

OK, empirical again. Let me consider that local-alloc's order might be by the pseudo number, and the pseudo number depends on the expand order. So the way to flip is to make the VALUE pseudo have a lower pseudo number.

**!!!!! IDEA !!!!!** What if the pointer's value is loaded into a pseudo that is created LATER than the value's? That happens if the pointer load is NOT the first thing. For example, if `p` were assigned but the compiler delays it... no.

**!!!!! IDEA 2 !!!!!** What if the pointer value comes from the SAME load as the value? I.e., if the source loads the pointer and the field in one expression such that gcc creates v0's pseudo first? E.g.:

```c
v0 = ((Unkstruct_80126948 *)D_801151D4)->unk10;
```
Wait — semantics: `((Unkstruct_80126948 *)D_801151D4)` treats the VALUE of D_801151D4 (an address constant 0x801151D4) as a pointer → dereferences 0x801151D4+16. The original does: p = D_801151D4 (load the pointer), then p->unk10 (dereference the loaded pointer). So they're DIFFERENT. ✗

OK so the semantics require: load the pointer, then deref.

**IDEA 3**: What if the pointer is stored in a variable of a DIFFERENT TYPE that gcc keeps in a different reg class? E.g. `p` as `u32` vs `int`? Same.

**IDEA 4**: What if we make the pointer pseudo live across a call so it becomes GLOBAL, and the value stays local? Then global-alloc gives the pointer a callee-saved reg ✗ (target has v1).

**IDEA 5**: What if we make the VALUE pseudo global? The value is live until the jal (the `sw v0,20(v1)` is in the delay slot, so the value is dead before the call) — hmm, but in the source the value's last use is before the call. So it's a local.

Hmm, BUT: what if we move the store `((Unkstruct_80126948 *)p)->unk14 = v0;` to AFTER the call in the source? Then the value would cross the call → global → callee-saved ✗.

Hmm.

OK OK. Let me look at the local-alloc order question from gcc 2.7's actual source. I'll try to recall harder. gcc 2.7 local.c:

```c
/* Allocate local register regions.  ... */
static int
allocate_local_regions (max_reg, max_reg_num, reg_last_freq)
{
  int i, j, k, m, reg, pass, reg2;
  int conflict;
  struct allocno *a;
  struct allocno *a2;
  int *local_size;
  int local_set_size_max;

  /* Find the maximum number of local registers we need.  */
  ...
  /* Mark each local reg with the number of registers it needs.  */
  ...
  /* Sort the regs by size, then by ... */
```

I distinctly recall gcc 2.7's local.c having:

```c
  /* Sort the locals by size, and then by the number of references, 
     so that the ones with the most references get the best registers.  */
```

Hmm. If so, the value (5 refs) would get v0 and p (4 refs) v1 — which is the TARGET. But mine gave the opposite!

Hmm, so maybe my ref counts are wrong. Let me reconsider: maybe gcc counts refs differently. p: `p = D_801151D4` (1 set), `((Unkstruct_80126948 *)p)->unk10` read (2), `->unk10` write (3), `->unk14` write (4) = 4.
value: `v0 = ...unk10` (1 set), `v0 = v0 - 3` (read 2 + set 3), `->unk10 = v0` (4), `->unk14 = v0` (5) = 5.

Hmm, but maybe gcc counts the "v0 = v0 - 3" as a copy (the value is copied into a new pseudo) → the value pseudo has 3 refs and the copy has 2. Then p (4 refs) > value (3) → p gets v0 ✓ (mine!). And in the target, the value pseudo must have MORE refs than p's.

So: to flip, I need the value pseudo to have ≥5 refs while p has 4, OR p to have fewer.

Hmm! In the target, `v0` holds: the loaded value, then v0-3 (in place), then two stores. If the "v0 = v0 - 3" is done in place (same pseudo), the value pseudo has 5 refs.

In mine, maybe gcc created a separate copy for `v0 - 3`? But the asm shows `addiu v1,v1,-3` (in place on v1) ✓. So the value pseudo has 5 refs in mine too.

Hmm, then p (4) vs value (5): if the order were by refs, the value would get v0 (target) — but mine gave p → v0. So the order is NOT by refs.

⇒ It's by allocno order (p first).

⇒ To flip, the value pseudo must have a lower allocno. 

Hmm, is there any way? The pseudo number is assigned at expand time in RTL order. p's pseudo is set by the `lw` (the first RTL). v0's pseudo is set by the second `lw`.

UNLESS the first `lw`'s result doesn't need a pseudo! E.g., if the pointer's value is used immediately as an address: `lw v0,16(v1)` — hmm, that IS the second load.

Hmm, what if the pointer value is loaded directly into a hard reg (v1) without a pseudo? That's what the target shows: `lui v1; lw v1,0(v1)` — the result goes into v1 (a hard reg)! Hmm, but that's the final allocation (after local-alloc). At RTL level it's a pseudo.

Hmm.

OK, radical alternative: what if the ORDER of the two loads is swapped in the source? I.e., load the VALUE first and the pointer later? Impossible semantically.

Hmm, what if the pointer is loaded TWICE:
```c
v0 = ((Unkstruct_80126948 *)D_801151D4)->unk10;   /* no */
```

Hmm.

What about this: **the pointer's pseudo could be created AFTER the value's if the pointer is loaded inside the same expression as the value**:
```c
v0 = ((Unkstruct_80126948 *)(*(s32 *)&D_801151D4))->unk10;
```
Hmm: `*(s32 *)&D_801151D4` = the pointer value (p), then `->unk10`. The expand: the address of D_801151D4 → load → the pointer pseudo (created first) → then the value's load. Same ✗.

Hmm!!! 

Hmm, what about making the pointer's value come from a place where gcc creates the value pseudo first... 

OK, let me flip the approach: instead of making the value pseudo come first, make the POINTER pseudo come LATER by making it a COPY of something:
```c
s32 p;
p = D_801151D4;      /* p's pseudo created 1st */
```
What if:
```c
s32 q = D_801151D4;   /* q pseudo 1st */
s32 p = q;            /* p pseudo 2nd — a copy! */
```
Then p is a copy of q → gcc would coalesce them (the copy disappears) ✗ (extra move).

Hmm.

OK, let me consider the possibility that local-alloc's order is by allocno but the ALLOCNO for locals in gcc's local-alloc is `local_allocno` — hmm.

Let me try yet another approach: maybe the swap can be achieved by changing the number of locals. E.g., if the value variable were split into two variables (v0a = load, v0b = v0a - 3)? That adds a pseudo but might change the order.

Hmm, but we need the final code to be identical.

Let me just try a bunch of variants:
f1: typed pointer (correct semantics).
f2: `v0 = p->unk10; v0 = v0 - 3;` with p as `Unkstruct*`.
f3: the value as a separate variable from the subtraction: `s32 w = ...unk10; v0 = w - 3;` — hmm, extra move?
f4: swap the roles: name the pointer variable `v0` and the value `p`!! I.e., rename the variables! The allocation depends on the order of creation, not the names. Hmm, that doesn't change anything.

Hmm.

f5: What if the pointer's first use is the STORE (not the load)? I.e. reorder the source:
```c
p = D_801151D4;
((Unkstruct_80126948 *)p)->unk10 = ((Unkstruct_80126948 *)p)->unk10 - 3;
```
Hmm, that's one statement: read unk10, subtract 3, store. The RTL: lw v0,16(v1); addiu v0,v0,-3; sw v0,16(v1). And then `->unk14 = v0` needs v0 again — but v0 is a variable... 

```c
s32 p;
s32 v0;
p = D_801151D4;
v0 = ((Unkstruct_80126948 *)p)->unk10;
((Unkstruct_80126948 *)p)->unk10 = v0 - 3;    /* hmm */
```
Hmm, that would compute v0-3 twice? No: the store's value = v0-3, but we also need v0 for unk14 = v0 (the decremented value!). In the target, unk14 = the decremented value (v0 after addiu). So the value must be materialized.

Hmm: `v0 = v0 - 3` then store unk10 = v0, store unk14 = v0. 

What if written as:
```c
p = D_801151D4;
((Unkstruct_80126948 *)p)->unk10 = ((Unkstruct_80126948 *)p)->unk10 - 3;
((Unkstruct_80126948 *)p)->unk14 = ((Unkstruct_80126948 *)p)->unk10;
```
Semantics: unk14 = unk10 (after the decrement) ✓ same! RTL: lw v0,16(v1); addiu v0,v0,-3; sw v0,16(v1); lw v0,16(v1); sw v0,20(v1). That's an extra load ✗ (the target has no second load).

Hmm.

OK. Let me try to think about whether the score-11 e3 variant could be fixed to be semantically correct AND produce the target. e3 (with the wrong semantics) produced `lui at` for the stores — because p was a constant address.

What if I write the CORRECT semantics with a typed pointer:
```c
Unkstruct_80126948 *p;
p = (Unkstruct_80126948 *)D_801151D4;
v0 = p->unk10;
v0 = v0 - 3;
p->unk10 = v0;
p->unk14 = v0;
```
RTL: `lui v1; lw v1,0(v1)` (p) — hmm, the cast of an s32 to a pointer: gcc might treat the cast as a no-op and the load as `lw p, 0(v1)`. Then `lw v0,16(p)`.

Hmm, that's the same as c1.

Hmm, but there's a subtlety: in c1, `p` is `s32` and the accesses use `((Unkstruct_80126948 *)p)` casts. gcc 2.7 might handle the cast+offset differently (e.g., creating an address pseudo). With a typed p, gcc uses `mem (plus p 16)` directly.

The reg allocation might differ! Let me just try f1.

Let me also try: `p` as `s32` but with the value as `s32` and the pointer accesses via a typed temp.

Let me generate and test f1, plus a few others.

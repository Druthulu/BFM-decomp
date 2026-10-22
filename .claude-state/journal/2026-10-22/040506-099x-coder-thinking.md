---
ts: 2026-10-22T10:05:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_AagAxvRPMNofIzubXbk2
---
So x1 (114 insns) vs the target (115): the target has the extra "move s0,v0" (and the branch targets shift).

So the ONLY difference is the missing copy. If we can get "lui v0; addiu v0; move s0,v0", we score 0!

Now, how about this idea: what if p is assigned the address AND the address is *also* used by a load directly (so the constant is materialized in a caller-saved reg) — that's v09 (115 insns, load base v0). Hmm, v09's diff showed:
```
17  lui s0 | lui v0
18  addiu s0 | addiu v0
19  --      | move s0,v0
21  lui v0 | lhu v0,0(s0)
22  lhu v0,0(v0) | --
```
So in v09, ours has "lui s0; addiu s0" (p materialized into s0) and "lui v0; lhu v0,0(v0)" (the direct load) while the target has "lui v0; addiu v0; move s0,v0; lhu v0,0(s0)".

So in the target, the constant is materialized into v0 (a caller-saved temp) and copied to s0, and the LOAD uses s0.

Hmm, so in the target, the address's materialization happens in a caller-saved reg. Why? Because in the target, the pseudo holding the address is NOT live across calls — only its COPY (s0) is. That means the source variable's pseudo was short-lived.

For that, the source must be a separate variable that is used once (so the materialization is a temp) and the copy to p survives.

The copy survives iff the front end doesn't fold pb into the use. Since the front end folds constant-initialized locals...

Hmm, unless! What if pb's initializer is a constant but pb is used in a context where the front end CAN'T fold because the use is a *store* or a *call argument*?

Hmm, what about this: the front end's fold applies to the *use* of pb in `p = pb`. What if instead of a direct assignment, we do something that isn't a simple tree copy — e.g.:

```c
    p = pb;
```
vs
```c
    p = (u16 *)pb;
```
Hmm, the front end's fold of the VAR_DECL pb gives the ADDR_CONST; the cast folds → same.

What if the assignment is through a *conditional*:
```c
    p = pb ? pb : pb;
```
Folded.

What if it's `p = pb + 0;`? Folded (pointer arithmetic with 0).

Hmm, what if the use is in a *comma expression* or a *cast to a different type*: `p = *(u16 **)&pb;`? → memory ✗.

OK OK. Let me look at this from the "what does gcc 2.7's front end actually do" angle — let me find the fold in the c-type.c-like code. The papermario tree lacks c-type.c but has c-decl.c. Let me grep c-decl.c for "DECL_INITIAL" and "constant".

Actually! Hold on. Maybe the fold is NOT in the front end but in gcc's expand.c's `expand_expr` case VAR_DECL:

```c
    case VAR_DECL:
      ...
      /* If the variable is a local variable with a constant initializer
	 and it is not address-taken, expand the initializer at each use. */
```

I recall gcc 2.x's expand.c DOES have this:
```c
      /* Handle the case of a variable that is a constant: 
	 ... */
```

Since expand.c isn't available, let me test the hypothesis directly: does the fold happen for a variable whose initializer is a constant *expression* (not a plain constant)? If the fold requires TREE_CONSTANT(DECL_INITIAL), then an initializer that is NOT TREE_CONSTANT (e.g. a cast of a cast, or an ADDR_CONST with a non-constant offset) would not be folded.

Test: `u16 *pb = (u16 *)((u8 *)&D_800B99DC + 0);` — hmm, is (CAST (PLUS (ADDR_CONST) 0)) TREE_CONSTANT? In gcc, TREE_CONSTANT is true for ADDR_CONST and for INTEGER_CST; a CAST of ADDR_CONST is not TREE_CONSTANT (I think fold would simplify it, though).

Hmm, the front end's `fold` is applied to the initializer when it's stored. `fold` on (CAST (PLUS (ADDR_CONST D) (INTEGER_CST 0))) → (CAST (ADDR_CONST D))? then fold again → (ADDR_CONST D) — fold is applied repeatedly.

To defeat fold, use something fold can't handle: e.g. a cast to a *struct* type? no.

Hmm, what about the initializer being a *symbol* address with a *volatile* qualifier? no.

What about `(u16 *)(s32)&D_800B99DC`? fold: (CAST (CAST (ADDR_CONST))) → the inner cast to s32: fold of (CAST (ADDR_CONST)) in an integer context → gcc's fold DOES fold ADDR_CONST to an INTEGER_CST when the target type is an integer (that's how `(s32)&x` becomes a constant). So (INTEGER_CST addr) → then (CAST (INTEGER_CST)) → (INTEGER_CST addr) → then (CAST (INTEGER_CST)) to a pointer type → hmm, in gcc 2.7 an INTEGER_CST cast to a pointer type isn't a valid constant → it stays as a cast → NOT TREE_CONSTANT → the front end keeps it as an expression!

Hmm! But then the *value* is an integer constant, and casting it back to a pointer at runtime → the address would be materialized as an INTEGER_CST (lui/addiu with a literal) — NOT a symbol reference → the asm would have no relocation → different bytes but maybe the same instruction count? The score compares instruction streams — the target has R_MIPS_HI16 D_800B99DC relocations. The scorer masks relocations with "reloc-operand equality" — hmm, "compared, relocation-masked with reloc-operand equality". So if our insn is "lui v0,0x800B" (a literal) vs the target's "lui v0,0x0" with a HI16 reloc — the masked comparison might treat them as equal if the reloc operand matches... The masking replaces the reloc'd operand with a placeholder. Our literal 0x800B vs the target's placeholder → NOT equal → mismatch.

Hmm, v12 tried `(u16 *)(s32)&D_800B99DC` and got 5 — so it folded to the symbol anyway (the front end kept the ADDR_CONST).

OK, let me try a slightly different approach: TEST whether the front end folds an initializer that is a *volatile-qualified*... no.

Time check: I'm at ~2h20m. I still have 4 items (this one + 3 more). Let me stop the deep analysis for 8018483C, run a batch of ~15 plausible variants, and if nothing cracks, record the wall.

Batch for 8018483C (base = x1.c: `p = &D_800B99DC;`):
1. pb temp with p = pb (x3 = folded)
2. pb temp, p = pb, and pb used twice (the load direct)
3. p = (u16 *)(s32)&D_800B99DC (v12)
4. p = &D_800B99DC[0]
5. p assigned before the early return
6. p assigned after the early return but in a nested block
7. `u16 *pb = &D_800B99DC; p = pb;` with pb declared at the top (v2)
8. the address via a *pointer to pointer*: no
9. `p = (u16 *)((u8 *)&D_800B99DC);`
10. `p = &D_800B99DC[0];` with the load `*p`
11. the load through p but the assignment via a *volatile*? no.
12. p = &D_800B99DC with the decl order changed (p declared first)
13. two pointers: `u16 *pb = &D_800B99DC; u16 *pc = pb; p = pc;` (chained copies — the fold would kill them all)
14. `p = &D_800B99DC;` with `D_801E86BC = (*p & 1) + 3;` moved before? Hmm.

Hmm, most of these were tried. The most promising untried: p assigned BEFORE the early return (the value live across the branch) — the materialization might then be split: the constant into v0 in the preheader and the copy to s0 after the branch? Hmm, but the target has the materialization after the branch.

Hmm, wait: actually! What if the copy is a *loop* artifact: the notes' orig comment mentions "loop.md L4 preheader-copy". Hmm! The preheader of the loop! The pointer p is assigned before the loop; the loop's preheader might copy the preheader value into the loop's register. Hmm, but p is assigned before the loop in our source too.

Hmm, what if the ORIGINAL had the pointer assignment inside the *loop preheader* in a way that creates a copy? Hmm.

Let me think about "loop.md L4 preheader-copy" — the target's "lui v0; addiu v0; move s0,v0" is in the loop's preheader (the block before the loop). And gcc's loop.c might create a copy when the loop's "init" values are copied into the loop's registers.

So the copy might come from loop.c's preheader handling: if the loop is a "for" loop with an init statement, loop.c copies the init value into a register for the loop. Hmm! In our source the loop is `for (; i < 4; i++)` with the init elsewhere.

Hmm, what if the original source's loop had an init statement that assigned the pointer? e.g.
```c
    for (p = &D_800B99DC, i = 0; i < 4; i++) { ... }
```
Hmm! That would place the assignment in the loop preheader and loop.c would copy it... but the target's copy is in the preheader anyway.

Hmm, what about: the original had the pointer assignment in the loop's init or the preheader, and loop.c's "preheader copy" created the v0 → s0 copy.

Actually, the notes' comment says: "loop.md L4 preheader-copy: the target materializes &D_800B99DC into $v0 and then `addu $s0,$v0,$zero`." — so the previous agent thought loop.c's preheader copy was the mechanism. And they tried a "zero-byte re-tie fence" to keep the pseudos apart.

Let me look at loop.c's L4 (in the reference source) to understand when loop.c creates a preheader copy. Let me grep loop.c for "copy".

Hmm, time. Let me try a batch of variants around the LOOP structure:
a) the pointer assignment inside the for-init: `for (p = &D_800B99DC; i < 4; i++)`
b) the pointer assignment as the first statement of the loop body
c) `for (i = 0, p = &D_800B99DC; i < 4; i++)`
d) p assigned before the loop but the loop is a while loop
e) the pointer assigned inside the loop body (changes semantics)

Let me write these variants and test. Also variants where the address is used twice (v09-like) combined with the loop.

Let me write the batch now. Base: x1.c (which is the orig with the launder block replaced by `p = &D_800B99DC;`).

Let me look at x1.c's content around the loop to writethe variants.

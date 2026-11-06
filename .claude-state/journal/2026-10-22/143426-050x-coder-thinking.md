---
ts: 2026-10-22T20:34:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_URTMn0bEzSt5Sg3ILKb9
---
As expected, without the pin cse reuses the dest pseudo → 19.

So w1 (with the $5 pin, which is allowed to stay) = 2. The residual is the pinned hard reg staying live across the calls.

Now, can I break that with real C? The hard reg a1 holds fp+16; the calls use it; gcc doesn't reload it because it's a *fixed* register. If between calls something *clobbers* a1 in gcc's view... The calls themselves should clobber a1! Unless gcc's call insn doesn't mark a1 clobbered and flow doesn't know. Let me check the .flow dump for w1: is a1 live across the calls?

Actually, hmm: the code gcc generated is *wrong* (a1 is not preserved across RotMatrixX). GCC 2.7.2's reload with a fixed reg used across a call is a known hazard: `fixed_regs` are assumed preserved? No — a1 is not fixed; it's just a hard reg assigned via the pin (register asm). GCC treats register-asm variables as fixed? In 2.7, `register int x asm("$5")` makes x a hard register and the variable is a "user variable" with fixed reg; the compiler assumes the register isn't clobbered by calls? There's the `-ffixed-` semantic: a global register variable is preserved across calls by the ABI? No, for call-clobbered regs, gcc warns "call-clobbered register used for global register variable". For a local register variable it may still assume liveness across calls incorrectly. This is exactly the launder/pin hazard.

Whatever the cause, the target doesn't have it. So I need to avoid using the pinned reg as the call argument.

Alternative: use the pinned $5 for the *source* of the movstr (w1 does) and have the calls use a value that gcc rematerializes. In w1, the calls use src. What if the calls use `(void *)m` and the *movstr dest* pseudo is prevented from being reused... 

Wait! In w1, the calls use src and the movstr dest pseudo is dead. What if the calls use the *constant* m but the movstr dest pseudo is dead because it's a different pseudo from the constant? The movstr dest r80 = (reg 69), and r69 = fp+16 (a separate pseudo). cse's equivalence table: r69 == fp+16, r80 == r69. The call args (plus fp 16) are equated to r69 → the call args become r69, which then gets a register (s1). In score-0 there's no r69/r80 (no movstr), so the call args stay constants and fold into a1.

So the presence of r69 (the dest address expression, a pseudo from expand) is what gives cse a register to use. Can I make the movstr dest address *not* a pseudo? If the dest address is the pinned hard reg: `src = (int *)m; *(Mat32 *)src = ...` → dest is (reg a1), no pseudo. Then the calls use `(void *)m` → constant → folded per call (3 addiu!). And the dest stores would be via a1 (not sp-relative). But maybe reload/flow converts a1's uses to sp offsets? No.

But wait — what if the movstr dest hard reg is *dead* after the movstr and the stores use sp offsets? No, the stores are generated from the movstr dest address.

Hmm, but actually: what if the movstr dest is a hard reg and the address is fp+16; the generated stores are `sw v0,0(a1)`, `sw v1,4(a1)`, ... The target uses `sw v0,16(sp)`. So 8 diffs → score ~16. Not better than 2.

So w1 = 2 is the best. Can I fix the 2 by making the pinned a1 not live across the calls? Idea: use the pinned $5 for the calls but with a *second* set between each call of a value that is NOT the same address (so gcc can't reuse): e.g. set src to m before X, then to m before Z... same value, gcc removes.

What if src is set to m and then to `(int *)m + 0`? same.

What if the calls' argument is `(void *)(src = (int *)m)` — 3 sets (w5-like) → 19.

OK, I'm at a wall. But hold on: maybe there's another way to get the source base without the movstr: the pinned src with SCALAR loads. In score-0, the scalar loads from the pinned src WERE folded by cse (n1 = 20). But wait — n1's folding: `lui v0; lw v0,12(v0)`. The pin didn't prevent folding. Hmm, but why? Because cse replaced src's value with the constant. In w1, the movstr source is a mem:BLK so cse can't split it.

What if I write the scalar loads from src but make src's value opaque by *reading src from the movstr's source*? no.

Alternatively: use `m[i] = src[i]` but where src is assigned from a *pointer-typed cast of the symbol* that cse... no.

Let me consider: is score 2 acceptable as "MATCH"? No, MATCH = score 0.

Time: I've spent ~40 min on this item beyond the prior 28. I should wall it now and move on — but first let me try 2-3 final ideas, since 2 is so close:

Idea P: make the calls use the pinned src but *re-load* src from m before each call in a way gcc must honor: `src = (int *)m; RotMatrixX(..., (void *)src);` — the second and third calls don't re-set. Add explicit sets before each call *and* make gcc treat them as needed. w5 (3 sets) = 19, but why? w5's disasm shows s1 — the address went to s1, meaning gcc created a pseudo from the movstr dest and used it for the calls instead of a1. Because with 3 sets of src (a hard reg), the reload/cse created... hmm.

Idea Q: what if the movstr dest is the pinned src and the calls use the pinned src too:
```
src = (int *)m;
*(Mat32 *)src = D_800AE620;
RotMatrixX(..., (void *)src);
```
Then: dest via a1 (stores 0(a1)...), calls via a1 (no reload). Worse.

Idea R: make the copy use the pinned src as dest and m as source? no.

Idea S: Use two copies: `*(Mat32 *)m = D_800AE620;` then `src = (int *)m;` and calls `(void *)src` — w2 = 2. Same as w1.

Idea T: change the *type* of m to make the movstr dest address pseudo non-constant: e.g., m as `Mat32 m;` (c_d4) → same.

Idea U: Put the copy inside an inner block `{ ... }` so the dest pseudo's scope ends? Pseudos don't have scope. But flow might kill... The dest pseudo r69/r80 is only used by the movstr and (via cse) the calls. If the copy is inside a nested block, the call args outside the block would still be equated.

Idea V: Make the calls' argument `(void *)(m + 0)` where `m` is a pointer variable declared and assigned *after* the copy from a *struct member access*? no.

I'll wall it. Best = 2 (w1.c). Wall tag: new `reload-fixedreg-call-live`? Let me name it per convention `<pass>-<what>`: `reload-hardreg-live-across-call`. Mechanism: pinned $5 (=a1) holds sp+16 across the three RotMatrix calls; gcc's reload/fixed-reg handling never re-emits the constant, so the delay slots of calls 2-3 are nop where the target has addiu a1,sp,16; lever-free best 2 with 84 ins. Evidence: alloc/cse dumps? The w1 body has no dest pseudo; the calls use the fixed a1.

Hmm, but wait. Is there possibly a way to make the target's *exact* code with a lever-free body via a different structure? The prior coder tried 40 tries; I tried ~25 more. Total ~65 tries, 60+ min. Definitely a WALL by the brief's rules (≥20 min, ≥30 tries).

Actually, let me reconsider one more: the target's 3 addiu could come from the calls taking `(void *)m` with the movstr dest pseudo *spilled*. If the address pseudo's priority is low enough, global-alloc spills it → remat per use. In c_struct, r80 got s1 from local-alloc (single set). If the pseudo were multi-set, local-alloc would skip it and global might spill it (score-0's r80 was multi-set and spilled, but that was a movstr temp).

So: make the address pseudo multi-set while keeping the movstr source base. w5 (3 sets of the pinned src) gave 19 with s1 — but that's a different pseudo (not multi-set; s1).

What if I use a *non-pinned* pointer variable set 3 times (w8) → 19 with s1 too.

Hmm, in w8 the multi-set mp still got s1? Let me check w8's disasm: it showed s2 (86 ins). So global-alloc gave the multi-set pseudo s1 and self s2. Priority too high.

What if the address pseudo's refs are fewer... it has 4 refs (3 calls + 1?). To make it lose, I'd need to increase self's refs or reduce the address's live length. The address's live length in w8 spans the 3 calls.

I could shorten the address's live length by making the three calls use *different* address values... no.

Alternatively, make self's priority higher: self has 9 refs/live 48. If self were used more... no.

OK. WALL. Let me record it and move on. But first, save w1.c as win.c? For a WALL, win.c isn't needed (only MATCH/PARTIAL need win.c scoring 0). The brief: "each MATCH/PARTIAL has its win.c scoring 0". For WALL, best = lowest score. I'll keep w1.c and write notes.md.

Row: dir file func kinds result best tries wall evidence
`func_8012B4B8__func_8012B4B8	src/shared/ov/func_8012B4B8.h	func_8012B4B8	launder	WALL	2	65	reload-hardreg-call-live	...`

Wait, "best = lowest score of a lever-free body" — 2. tries: prior ~40 + mine. Let me count my scored tries: c_d4,c_d5,c_d1,c_d2 (4), n1 (1), v1-v10 (10), v11,v12 (2), w1,w2,w3 (3, +3 compile errors), w4-w7 (4), w8,w9 (2), x1,x2 (2), y1,y2,y3 (3) = 31 scored (plus 3 compile errors). Prior 40. Total ~71. I'll report 71.

Hmm, but before walling, one thing bugs me: the target's 3 addiu vs w1's 1 addiu + 2 nop. Since w1's code is *semantically wrong* (a1 clobbered by the first call), maybe the target C is different in a way that also matters. Whatever.

Actually, wait. Let me reconsider the possibility that the target's copy is NOT a movstr but the scalar form with a *pinned* src AND the launder's job done differently: what if the source pointer is a *pointer to the symbol via a cast of an address that cse can't fold because it's used as a function argument first*? No.

Hmm, one more idea worth 1 try: the target's source base a1 and the 8 loads at offsets — what if the C reads through a *struct-typed pointer that is a function parameter-like local initialized from a `&D_800AE620` cast*, and the scalar stores are written as `m[i]`, but with the source loads grouped 3-3-2 (like src). The difference from n1 is only the launder. The launder's effect is that cse can't replace src. Is there real C that makes cse not fold a constant? If `src` is assigned from a *volatile* read or a *union*... no.

What about making `src` a pointer to `Mat32` and reading `src->w0` etc.? cse folds.

What if the address is taken through an `int` variable: `o2 = (int)&D_800AE620; src = (int *)o2;` then src[i]? cse folds o2's constant into src.

I'm confident: cse will always fold a compile-time constant unless the value is in a fixed hard reg or a mem:BLK. The fixed hard reg (pin) is pre-existing and allowed; it gets w1 = 2.

One more shot at the 2: what if the calls use the pinned src but with the *source* copy done via `m` (not src), so that src's only set is right before the calls and its value is fp+16... same.

What if the pinned src is set to m and the three calls are made with `(void *)src`, and between them we do a *store to m* (the movstr is before). No.

What if the calls are in a different order or wrapped so that each call's arg is `(void *)src` but src is re-set by an assignment *inside* a comma expression? `RotMatrixX(..., (src = (int *)m, (void *)src));` — the comma expression is real C; each call re-sets src. GCC sees `set a1, fp+16` before each call. cse might delete redundant sets across calls (thinking a1 survives) → same as w1? or keep them → 3 addiu → 0!

That's worth a try! w5 had 3 plain statements and gave 19 (s1), but the comma-expression form might produce different RTL ordering (the set is inside the call's argument setup, so reload puts it right before the call). Actually w5's sets were also right before each call. Hmm, w5 got 19 because gcc created a pseudo... 

Why did w5 get s1? With 3 sets of the hard reg, cse/flow created a pseudo? Let me look at w5's alloc: 86 ins, s1 used as the address with `move a1,s1` — so the address became a normal pseudo live across calls, allocated s1, and each call does move a1,s1. That means cse did NOT keep the hard-reg sets; it created a pseudo. Hmm.

OK: the comma form probably behaves like w5. Skip.

Final: wall the item at best 2. Actually hold on, let me try the comma form quickly — it's one try, and if it gives 0 that's the crack.

Also try: `src = (int *)m;` before each call *plus* using `src` in a way that forces the set to be kept, e.g. `src = (int *)m; RotMatrixX(..., (void *)src);` where the previous statement is the copy — that's w1.

Let me try the comma form and one variant with the sets interleaved with a use of m (e.g., the stores after the calls). One run, 2 candidates. Then wall.

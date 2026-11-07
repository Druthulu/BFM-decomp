---
ts: 2026-11-06T06:25:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VgnOtGjIFn1GpnVusFXf
---
These items are 308 ins — big. The small ones (90, 96) are more tractable. Let me park item 1 for a moment and check the other small item func_80183534 (96 ins) — maybe it cracks quickly. But no: I should finish item 1 or wall it.

Actually, per the brief: budget 20-30 min per item; past 30 min stop and record a wall — a WALL needs ≥20 min and ≥30 scored tries. I've done ~8 tries in 20 min. Let me keep going but efficiently.

Let me reconsider the otz problem with fresh eyes.

Target insns:
```
301c: move s1,v0     <- otz = RotTransPers4(...)
3020: move a0,s1     <- arg
3024: jal func_801823D4
3028: li a1,-26
302c: move s1,v0     <- otz = func_801823D4(...)
3030: move a1,s0     <- arg q for AddPrim
```
Wait — 3028 `li a1,-26` is in the delay slot of jal func_801823D4. And 302c `move s1,v0` is after.

So otz's *second* set is also materialized (`move s1,v0` at 302c) — because otz is used later (AddPrim index and func_8012E28C arg) and it's a global pseudo in s1. Combine can't fold that into the AddPrim use? It could fold into `sll a0,s1,2`... but the AddPrim call needs a0 = the address, and otz is used at `sll a0,s1,0x2` (3060). Combine might fold (set otz v0) into the shift... it doesn't because otz has 2 uses (sll and move a0,s1 for func_8012E28C at 306c). Right.

For the FIRST otz value, there's only one use → folded.

So we need the first otz value to have 2 uses, or a block boundary.

IDEA: What if the first call's result is passed to func_801823D4 AND used in the `if (i != 11)` of the *next* iteration... no.

IDEA: What if we write the depth-sort as `otz = func_801823D4(otz, -0x1A);` but also keep the raw value for `func_8012E28C`? no.

IDEA: **two uses in the same statement**: e.g.
`otz = func_801823D4(otz, -0x1A) ;` no.

Hmm, what about `otz = func_801823D4(otz, -0x1A) + (otz - otz);`? folds.

What about `AddPrim(... + otz * 4, q)` where otz... no.

OK, what about making the arg to func_801823D4 be `otz` *twice* in a way that's real: `func_801823D4(otz, -0x1A)` → the second param is -0x1A. What if we compute -0x1A from otz? e.g. `-0x1A + (otz & 0)` → folds.

What about `func_801823D4(otz, otz - otz - 0x1A)`? fold.

gcc's fold() will simplify these.

Hmm, what about a **comparison that yields a constant but isn't folded**: e.g. `otz == otz` — fold gives 1. 

What about `otz != otz + 1`? fold.

What about a call to a *pure* function? no.

OK — different tactic: maybe I can accept a **different residual**: what if the arg copy is folded but we *add* an insn elsewhere to make 162? No — the diff would show different insns.

Let me try the block-boundary approach with a *real* loop that costs zero instructions: `do { ... } while (0)` costs 0 but gets merged. What if the do-while contains a `break`? no.

What about `while (0) { }`? nothing.

What about `if (0) { ... }`? nothing.

Hmm, what about `switch (i) { case 0: ...; break; ... }`? jump table.

Hmm what about a **`goto`**? e.g.
```
otz = RotTransPers4(...);
goto L;
L:
otz = func_801823D4(otz, -0x1A);
```
A label creates a CODE_LABEL insn; jump_optimize may merge blocks but a label referenced by a jump... with no actual jump, the label is deleted? If we do `goto L; L: ...` the jump is redundant and deleted.

What about `if (i != 11) goto L;` ... changes code.

Hmm.

OK. Let me try to find whether there's a way to make otz's first value have 2 uses where the second use is free because it merges into an existing instruction. Look at the loop-1 body:

```
q = (G4 *)func_80010A08(0x24);
c = ((Unk*)arg0)->unkEC;
q->rgb0 = q->rgb1 = c;
c2 = ((Unk*)arg0)->unkF0;
*((u8*)q+7) = 0x3A;
q->tag = 0x08000000;
q->rgb2 = q->rgb3 = c2;
if (i != 11) { v0p..v3p }
otz = RotTransPers4(...);
otz = func_801823D4(otz, -0x1A);
AddPrim(..., otz*4, q);
func_8012E28C(otz, zpush);
```
Target insns for the first part:
```
2f90 jal func_80010A08 ; li a0,36
2f98 lw v1,236(s3)
2f9c move s0,v0
2fa0 sw v1,12(s0)
2fa4 sw v1,4(s0)
2fa8 lw v1,240(s3)
2fac li v0,58
2fb0 sb v0,7(s0)
2fb4 lui v0,0x800
2fb8 sw v0,0(s0)
2fbc li v0,11
2fc0 sw v1,28(s0)
2fc4 beq s2,v0,2fe0
2fc8 sw v1,20(s0)
...
```
Hmm, `li v0,11` — i != 11.

What if otz's first value were used in the `if` test? The if comes before.

What if we move the `if (i != 11)` AFTER the RotTransPers4 call and compute the args from... no.

Hmm hold on! What if we restructure: compute v0p..v3p as now, but the call result is used in the if... no.

OK, let me try the LAST idea: use a **real loop** with a zero-cost branch. What about `do { ... } while (0)` but with the loop body containing a `break`? Hmm.

Actually — what about `for (;;) { otz = RotTransPers4(...); break; }`? A `for(;;)` loop with a break: the back edge is unreachable? gcc emits `b` to end or falls through; jump_optimize would remove the loop.

What about `for (j = 0; j < 1; j++)`? gcc can't prove j<1 at compile time? Actually it might unroll or delete... `j < 1` with j=0 → the loop runs once; gcc 2.7.2 probably doesn't do that optimization. But it costs: `move j,0; slt; bnez` = 2-3 insns. No.

OK — I'm now fairly convinced this residual (the otz copy) is a genuine "cse/combine-copy-fold" wall unless a free use exists.

BUT WAIT. Let me reconsider: the score is 3 with w2. The brief says MATCH = score 0. What about a **PARTIAL**? PARTIAL is for keeping some levers. Not applicable — we need all levers gone.

Hmm, hold on. Let me reconsider the problem once more. What if we make `otz` **two variables** — one for the raw value and one for the sorted value? Then:
- `s32 raw = RotTransPers4(...);` → set raw from v0
- `otz = func_801823D4(raw, -0x1A);` → arg copy a0 = raw
Combine folds (set raw v0) + (set a0 raw) → a0=v0. Same.

Unless raw is used twice! What if `raw` is ALSO used in the second loop? Hmm, in loop 2 the code is the same shape: `otz = RotTransPers4(...); RotTransPers(...)x3; otz = func_801823D4(otz, -0x1A);`. In loop 2, target has:
```
30d4 jal RotTransPers
30d8 sw v0,0(s0)      <- t->tag = v0?? hmm
30ec move s1,v0       <- otz = RotTransPers(...)
...
3140 move a0,s1
3144 jal func_801823D4
3148 li a1,-26
314c move s1,v0       <- otz = func_801823D4(...)
```
Wait, in loop 2 the RotTransPers calls: `otz = RotTransPers((s32)&pa[i], (s32)&t->xy0, &p, &flag);` at 30d4, and the result `move s1,v0` at 30ec — materialized! Why? Because there are 3 RotTransPers calls and otz is assigned 3 times; the last assignment's value is used by func_801823D4 and... the earlier two are dead. Hmm, `move s1,v0` at 30ec after the *first* call? Let me re-read:

```
30d4 jal RotTransPers
30d8 sw v0,0(s0)       <- t->tag = 0x06000000? no, v0=0x600 was before...
30dc lui v1,0x2aaa
...
30ec move s1,v0        <- otz = RotTransPers(...) (first)
30f0 addiu a1,s0,16
30f4 addiu a2,sp,40
30f8 move a3,s6
...
3124 jal RotTransPers (2nd)
3128 addu a0,s5,a0
312c addiu a0,s3,244
3130 addiu a1,s0,24
3134 addiu a2,sp,40
3138 jal RotTransPers (3rd)
313c move a3,s6
3140 move a0,s1        <- arg
3144 jal func_801823D4
```
So otz is assigned 3 times in loop 2; only the last value is used. Each earlier assignment's copy gets folded/dead. The final `move s1,v0` at 3140? No: at 3140 `move a0,s1` — so the last RotTransPers result went to s1 somewhere. Hmm, at 3138 jal (3rd RotTransPers), and 313c move a3,s6 is the delay slot, then 3140 move a0,s1. Where's the set of s1 from v0 for the 3rd call? It must be... hmm, `move a0,s1` reads s1 which was set at 30ec (first call). That can't be right.

Let me re-read: the calls are:
- otz = RotTransPers(&pa[i], &t->xy0, &p, &flag)  → jal at 30d4
- RotTransPers(&pa[(i+1)%12], &t->xy1, &p, &flag) → jal at 3124
- RotTransPers(arg0+0xF4, &t->xy2, &p, &flag) → jal at 3138
- otz = func_801823D4(otz, -0x1A) → jal at 3144

So the 3rd call's result is in v0 at 313c-ish. Then `move a0,s1` at 3140 — that would be the arg copy for func_801823D4, reading s1 = the 1st call's result? That's wrong semantically!

Hmm, wait: maybe the `move s1,v0` at 30ec is the 1st call's result stored to otz, and the 2nd/3rd calls' results are discarded... but then func_801823D4(otz) would use the 1st. Hmm, but the source says `otz = RotTransPers(...)` only for the first call:

```c
otz = RotTransPers((s32)&pa[i], (s32)&t->xy0, &p, &flag);
RotTransPers((s32)&pa[(i + 1) % 12], (s32)&t->xy1, &p, &flag);
RotTransPers(arg0 + 0xF4, (s32)&t->xy2, &p, &flag);
otz = func_801823D4(otz, -0x1A);
```
Yes! Only the first call's result is assigned. So otz = 1st result, and the other two are discarded. So `move s1,v0` at 30ec is otz = 1st call. And `move a0,s1` at 3140 is the arg copy. But between them are the 2nd and 3rd calls (which clobber v0 but not s1) — so otz must live across those calls → it's in a callee-saved reg (s1) and its set materializes because it's live across calls! Combine can't fold it because the arg copy is far away with calls between (combine only combines adjacent insns).

That's why loop 2's copy survives — otz is live across 2 calls.

So for loop 1, we need otz's value to be live across a call between the set and the use. In loop 1, there's no call between.

Hmm! Unless we restructure loop 1 to have a call between. What calls could be there? `func_80010A08(0x24)` (the packet alloc) is at the top. If the RotTransPers4 call came *before* the packet alloc... no, the call needs q.

Wait — actually, what if we move the `otz = RotTransPers4(...)` *before* `q = func_80010A08(0x24)`? Not possible (q is an out-param).

Hmm, but what about `func_801823D4` itself: it's called right after. If otz were live across it... no.

What if we reorder so that `otz = RotTransPers4(...)` comes before the `q->...` stores? The stores are before the call in the target.

Hmm.

So in loop 1 the raw otz value has exactly one use, immediately after the call. Combine folds. The asm blocked it.

Is there any *free* insn we could place between? The target has `move s1,v0` then `move a0,s1` adjacent. Combine folding them gives `move a0,v0`. So the target's two insns are exactly the unfolded pair.

Plain C can't express "keep the copy" when the value dies immediately — UNLESS the pseudo is in a callee-saved register for another reason. What if otz were used in the *next* iteration? no.

What if otz is declared `volatile`? A volatile variable forces a store/load.

Hmm, what if otz's first value is also used by the *loop's* exit test? e.g. change the loop to `for (; i < 12; )` → `while (i < 12)`. no.

OK — what about making the first otz value used twice by *swapping* the argument: `func_801823D4(otz, -0x1A)` — what if the second argument is `-0x1A` but we pass `otz` also as the second arg in a foldable expression... no.

Alright. Alternative: what if we don't assign the raw value to otz at all, but to a *different* variable that is used twice: e.g. `raw` used by func_801823D4 and by the *next* AddPrim... no.

Hmm, hold on! What about the `func_8012E28C(otz, zpush)` call at the end: it uses otz (the sorted value). What if we pass the RAW value there? Semantically wrong, and the codegen: `move a0,s1` at 306c uses the sorted value. In target, the raw value is in s1 at 301c... hmm, and the sorted value also in s1 at 302c. Both use s1.

Hmm interesting: if the raw value were also used at the end (after the sorted value's set), it would need another register.

OK, let me try a completely different approach to the item: maybe accept w2's 3 and try small variations that might shift the allocation so the raw set materializes. Actually no — the fold is structural, not allocation.

Let me check: is there any chance the fold could be prevented by making otz's first set a *different* register than the arg copy's source — i.e., if otz were a global allocno in s1 and the copy is a0 = s1, combine folds them into a0 = v0 ONLY if the set is immediately before. In target it IS immediately before (301c, 3020). And combine did NOT fold in the target (because of the asm insn).

So it's purely the asm's presence. The asm's RTL is an insn. Any plain-C insn between would add an instruction.

=> This looks like a genuine WALL for the otz part... unless a free use exists.

WAIT. What about the **`if (i != 11)`** — what if we move the `otz = RotTransPers4(...)` to *before* the if by restructuring the pointer selection into the call arguments? Then the call would be before the branch and the use after the branch → block boundary → no fold! And the codegen might be identical if the branch structure is preserved... but the target has the if/else computing v0p..v3p then the call after the join.

If instead we put the call in the arms, it duplicates. No.

Hmm, what if the call is *before* the if and the if only adjusts the args? Not possible.

What about moving the `q` stores after the call? That changes order.

Hmm, what if the *if/else* is moved after the RotTransPers4 call by making the call take pointers computed as... 

OK, let me try a slightly different idea: what if the else arm (`i == 11`) is restructured to share the call? No.

Let me now consider: maybe the *loop* itself can provide the block boundary if the call is at the end of the body and the use at the top of the next iteration. No.

Decision: let me try 3-4 more quick variants, then if none, record this item as... hmm. But wait — a WALL requires the *lever-free* body's best score, and the kinds must be gone. w2 has both kinds gone (no pins, no asm) and scores 3. So I could record WALL with best 3. But a MATCH would be better. The brief expects MATCH where possible.

Hold on, let me reconsider ONE more idea: the **dead-reset (C0414)**. If we do:
```
otz = RotTransPers4(...);
otz = 0;            /* dead reset */
otz = func_801823D4(otz, -0x1A);
```
That's wrong semantically (otz=0 then used).

What about a dead reset of a *different* variable to break cse? Not relevant to combine.

Hmm, what about making the arg copy read a **stack slot**? e.g. `p` is already a stack slot... 

OK WAIT. Actually — what about using `p` (the out-param) as the carrier? No.

Let me try: does `do { } while (0)` between the set and the use *inside* the loop body help? w1 said no (score 8, unchanged from w0). Right.

Let me try: `do { otz = RotTransPers4(...); otz = func_801823D4(otz, -0x1A); } while (0);` — both inside the same do-while → same block → fold. Probably 8.

Hmm, let me think about `REG_UNUSED`... 

NEW IDEA: What if the second call's argument is passed as `otz` but we make the *call itself* take the address of otz? No.

NEW IDEA: What if we declare otz as an array `s32 otz[1]` and use otz[0]? That makes it memory — extra lw/sw.

NEW IDEA: **Make the first assignment conditional in a way that's cheap**: 
```
if (i != 11) { ... } else { ... }
otz = RotTransPers4(...);
```
Hmm.

Actually, hold on! What about putting the RotTransPers4 call inside the `if (i != 11)` structure by *duplicating* only the call... no.

Hmm, what about `v0p` etc: the target computes them in the arms. What if we compute the call args with a `? :` inside the call? Then gcc emits the branch... Let me think: `RotTransPers4(i != 11 ? (s32)pa : arg0+0x84, ...)` — gcc would emit conditional branches around each arg — much worse.

OK, let me take the pragmatic path: try ~6 more variants quickly in a batch, then decide.

Batch:
1. w7: `s32 raw = RotTransPers4(...); otz = func_801823D4(raw, -0x1A);` inside the do-while (w2 shape).
2. w8: w2 + `otz = otz;` after the call.
3. w9: w2 but the call's arg written as `(s32)otz`.
4. w10: no do-while; instead `otz = RotTransPers4(...)` moved after a dummy `if (i != 11) { }` — no.
5. w11: `otz = RotTransPers4(...); if (otz == otz) { }`? test.
6. w12: `for (; i < 12; ) { ...; do { } while (otz == 0x12345678); }` — a real loop condition on otz → block boundary + 1-2 insns. Actually this is promising for the *structure*; the cost is the compare+branch. But maybe we could make the condition use `i` in a way that reuses an existing compare... e.g. `do { otz = ...; } while (i < 12);`?? Hmm! The loop condition `i < 12` is already computed at the bottom of the loop (`slti v0,s2,12; bnez`). What if we restructure the loop as:

```
do {
    otz = RotTransPers4(...);
} while (0);
```
no.

Hmm, what about making the whole loop body a `do { ... } while (i < 12)` — that IS the existing loop. Then the call's set and the use are both in the body.

OK, what if we split the body:
```
for (; i < 12; ) {
    ...q stores...
    if (...) {...} else {...}
    otz = RotTransPers4(...);
    ...
}
```
Hmm.

Let me try the real-loop-condition trick differently: what if the *last* part of the body is wrapped in a do-while whose condition is the loop's own? Too convoluted.

Let me try instead: `while (otz != otz)`? folds to 0.

Let me just run the batch of simple ones and see if any surprises.

Actually, hmm, let me reconsider ONE more time: what about assigning the call result to otz via a **compound statement with a comma**: `otz = (i, RotTransPers4(...));`? The comma with a side-effect-free `i` folds.

What about `otz = RotTransPers4(...) + i - i;`? fold (i - i = 0, x + 0 = x). gcc folds x + i - i? Not necessarily! `x + i - i` = (x + i) - i — reassociation is not done in general; fold() may not simplify this because it's not a pure algebraic identity at the tree level (integer arithmetic, no overflow concerns in gcc? It does fold some). Hmm, gcc's fold does: `(x + i) - i` → x? In fold(), for `MINUS_EXPR` with `PLUS_EXPR` operand, it calls fold with associate — I think it can simplify (a + b) - b = a. Let me test empirically: `otz = RotTransPers4(...) + i - i;` would add an addu/subu pair anyway if not folded. Not free.

What about `otz = RotTransPers4(...); otz = otz + (i - i);`? folds i-i=0 → x+0 = x.

OK, what about using a **volatile-free but opaque** value: e.g. a global variable `D_800B9A02`? `otz = RotTransPers4(...) + (D_800B9A02 - D_800B9A02)` — adds loads.

Enough. Let me run the batch.

Actually, WAIT. One more important idea: **the `q->xy` out-params**. The RotTransPers4 call's 5th-8th args are `&q->xy0..xy3` which are stored to the stack (sw v0,16(sp) etc). What if the call were structured so that otz is used in one of those address computations? no.

And another: what if `otz` is used as the value for `func_8012E28C`'s FIRST arg *before* the sort... no.

Let me run the batch now. I'll write a generator that produces several variants from w2 and score them.

Variants:
a) w7: `s32 raw = RotTransPers4(...); otz = func_801823D4(raw, -0x1A);` (raw declared inside the loop as a block-local, inside the do-while)
b) w8: `otz = RotTransPers4(...); do { } while (0);` — w1 = 8 already.
c) w9: `otz = RotTransPers4(...); otz = otz + 0;` — folds.
d) w10: `otz = RotTransPers4(...); if (otz) { }` — empty if.
e) w11: `otz = RotTransPers4(...); switch (otz) { }` — empty switch.
f) w12: `otz = RotTransPers4(...); (void)otz;`

Let me test d, e, f and a — 4 candidates.

Actually e (empty switch) would emit a compare and jump table — 2+ insns. Skip. Let me test a, d, f.

Honestly the odds are low. Let me think about the *expected* solution differently.

Hmm, hold on. Let me reconsider the item's kinds: launder,pin. The launder here is the otz re-tie. In the G14 examples, the launder crack for a re-tie was "do { } while (0) + a real 2nd set". The real 2nd set was often `v = (s16)v` (free when v is s16). 

Is there a "real 2nd set" of otz that's free? What if otz were declared as `u16` or `s16`? Then `otz = RotTransPers4(...)` sets a HImode reg (no extension needed since it's just a copy of the low half? Actually assigning s32 to s16 truncates: the RTL is a HImode set, which is a no-op move). Then using otz in `func_801823D4(otz, ...)` requires sign-extending the HImode to SImode: gcc emits sll/sra (2 insns). BUT if otz is u16, it's `andi` (1 insn). Hmm, but the target has no such insn.

Unless... the arg is used in a context where the extension folds? No.

What about `otz` used as `(s32)otz` — no.

Hmm, what if the value's range makes the extension fold? No.

OK, so what about a "real 2nd set" that's free: e.g. `otz = RotTransPers4(...); otz = otz & 0xFFFFFFFF;` — folds.

Hmm, what about a 2nd set via a *different* statement that combine removes: e.g. `otz |= 0;`? folds at tree.

The tree-level fold kills everything. UNLESS the operation is on a different type: e.g. `otz = (s32)(u32)otz` no.

Hmm, what about `otz = (s32)otz;` — folds.

So plain C can't add a free 2nd set.

FINAL IDEA: make otz's first value live across a call by *moving* one of the loop-1 calls. Look at loop 1's tail:
```
otz = func_801823D4(otz, -0x1A);
AddPrim(D_800A651C[...].a + otz * 4, q);
func_8012E28C(otz, zpush);
```
What if the source is restructured to:
```
otz = RotTransPers4(...);
AddPrim(...)? 
```
no.

Hmm, what about computing `q = func_80010A08(0x24)` AFTER the RotTransPers4 call? The call needs q's xy addresses.

What about `c = ((Unk*)arg0)->unkEC` after? The stores use it.

OK, I'll do the batch and then likely mark this item... hmm, but hold on! Let me reconsider the possibility of a **different `if` arrangement that creates the block boundary without extra insns**. 

The target's loop-1 body:
```
2f90 jal func_80010A08
2f98..2fc8 packet stores
2fc4 beq s2,v0,2fe0    (i != 11 → branch to else)
2fcc move a0,s5
2fd0 addiu a1,s5,8
2fd4 move a2,s4
2fd8 j 2ff0
2fdc addiu a3,s4,8     (delay slot)
2fe0..2fec else arm
2ff0..3010 stack args + call
3014 jal RotTransPers4
3018 sw s6,36(sp)      (delay slot)
301c move s1,v0
3020 move a0,s1
```
What if we move the RotTransPers4 call *into* the arms? It would duplicate the call (2 jals) — no.

What if the `if` were *after* the RotTransPers4 call? Then the args wouldn't be ready.

Hmm, what if we compute the args BEFORE the call with the if, and the call after — that's the current structure.

So no free block boundary.

=> Conclusion: this residual needs an opaque use (asm) or a call between. That's a WALL: "combine folds the call-result copy into the arg; no plain-C 2nd set survives (tree folds identities), and the loop-1 raw value has exactly one use with no call between".

Hmm, but wait. Before declaring a wall, let me look at how the OTHER 4 items fare — maybe they have the same pattern and one of them cracks with a known move. But the wall would apply to all.

Hmm, hold on. Let me reconsider ONE more time. The `do { } while (0)` trick works by creating a loop. What if we put the **func_801823D4 call inside a do-while whose *body* also contains the RotTransPers4 call** — no.

What if we put the RotTransPers4 call at the END of the do-while body and the func_801823D4 call *after* the do-while (w2, done) — the fold happens because jump merges the loop's exit block with the successor.

What if the do-while has a `break` at the end so the exit is via a jump? `do { otz = RotTransPers4(...); break; } while (0);` — the `break` becomes a jump to the end label, so the loop's exit is a real jump → block boundary! But jump_optimize would simplify `do { x; break; } while(0)` to just `x`. Hmm, the front end might even fold it.

What about `do { otz = ...; if (i >= 0) break; } while (0);`? adds a compare.

Hmm, what about `while (1) { otz = ...; break; }`? Same folding.

What about a `goto` out of the loop?

OK, let me test the `break` variant quickly — cheap.

Actually, thinking about it more: jump_optimize's `jump_optimize(insns, 0, 0, 1)` after cse2 removes unreachable code and merges blocks. A `break` inside a do-while(0) produces a jump to the loop end; since the loop body is unconditional, the jump is redundant and gets deleted, merging blocks.

Let me just test a few and move on. Time is 23:30ish.

Let me do a batch of 5 candidates:
b1: `do { otz = RotTransPers4(...); break; } while (0);`
b2: `do { otz = RotTransPers4(...); } while (i < 0);` (real branch, +1 insn)
b3: `s32 raw = RotTransPers4(...); otz = func_801823D4(raw, -0x1A);` inside do-while
b4: w2 + `(void)otz;`
b5: w2 with `otz` declared `volatile`? no.

Let me generate b1-b4 and score.

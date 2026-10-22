---
ts: 2026-10-22T09:21:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_eDc1gkoYt8l1aoHqeKjo
---
Target context:
```
    lui  v1,0x0        ; &D_80195AF6  (reloc)
    lhu  v1,0(v1)      ; newval = D_80195AF6[unk100].f0  -- wait this is the first branch's path
```
Hmm the second block:
```
    lui  a1,0x0        ; &D_80195AF6
    addiu a1,a1,0
    lui  at,0x0
    addu at,at,v0
    lh   v0,0(at)      ; newval load
    ...
    lui  v1,0x0
    lhu  v1,0(v1)      ; ??
    li   s1,1
    sh   a0,14(s0)
    sll  v0,v0,0x3
    addu v0,a1,v0
    lh   v0,4(v0)
```
So the target computes the address as addu v0,a1,v0 where a1 = &D_80195AF6 (pointer) and v0 = index*8.

In ours, it's addu v0,v0,a1. So the operand order in the tree differs: target (plus a1 v0) = pointer + scaled index.

Wait — in ours, a1 is also the pointer (the register pairs say mine->target v0->a1 x1, a1->v0 x1 — hmm that suggests register allocation differences too, but the diff shows only one instruction differing, so maybe the pair report is about the whole function).

Hmm, "register pairs (mine -> target, count): v0->a1 x1, a1->v0 x1" means one insn where mine has v0 where target has a1 and vice versa — that's the same single addu insn. OK.

So we need the add to be (plus ptr idx). Why does gcc produce (plus idx ptr) in ours?

Because in our source, the expression is `((u8 *)p + off + 4)` where off = unk100 * 8. The tree: (plus (plus p (mult unk100 8)) 4) → the load uses base (plus ...) with offset 4 → (plus (plus p (mult ...)) 4) folds to (plus p (mult unk100 8)) with offset 4? Actually the address = p + unk100*8 + 4, so gcc folds constant 4 into the load offset, giving address (plus p (mult unk100 8)).

Now, gcc 2.7 combine has a rule: `(plus (mult x 8) p)`? no wait, we have (plus p (mult x 8)). Combine converts (mult x 8) into (sll x 3) and then... the target has (plus a1 (sll v0 3)). Ours has (plus (sll v0 3) a1).

So combine swapped the operands when converting mult→shift? In gcc 2.7.2 combine.c, there is code:

```
	  /* Recognize (plus (mult x 2^n) y) and convert to (plus (lsh x n) y)? */
```

Hmm, but ours has plus p (mult x 8) and it produced plus (sll x 3) p — swapped!

Wait maybe not: maybe the source's `p` in our body is `D_80195AF6_t *p = D_80195AF6;` and the expression `((u8 *)p + off + 4)`. The plus tree is (plus (plus p off) 4). off is a variable holding unk100*8 → (mult unk100 8). Combine: (plus (plus p (mult x 8)) 4): first, (plus p (mult x 8)) — gcc's combine has a rule to convert (plus (mult x 2^n) y) into ((set (reg) (plus (lsh x n) y))) — I believe there's a specific "optimize_multiply_add" style. In gcc 2.7 combine.c:

```
	    case PLUS:
	      ...
	      /* If we have a multiplication by a power of two in a sum, ... */
```

Actually gcc 2.7.2 has in combine.c a block:

```
	  /* Recognize a multiply of a sum ... */
```

Rather than guess: gcc 2.7.2's combine.c contains this well-known code:

```
	      /* If we have (plus (mult x 2^n) y), convert to (plus (lsh x n) y) */
```
Hmm, in that case the shift is the FIRST operand of the plus — matching what we see in ours. And the target has the shift SECOND: (plus p (lsh x 3)).

So the question: how does the target get (plus p (shift))? Because in the original source, maybe the index was computed as `unk100 * 8` and the address was `p + off` where off was a *variable* whose value gcc treats... hmm, ours also has off as a variable.

Difference: in the target, `sll v0,v0,0x3` uses v0 which came from `lh v0,256(s0)` (the unk100 load). So the index is loaded into v0 and shifted in place, then added. In ours presumably the same but the plus tree order differs.

So how could the tree be (plus p (shift))? If the source expression were `(u8 *)p + (unk100 * 8)` — that IS (plus p (mult x 8)) — and combine converts mult→lsh. If the conversion keeps position: (plus p (lsh x 3)) → addu v0, a1, v0 — wait but the dest... In our case we got (plus (lsh) p) → addu v0,v0,a1.

Hmm! Maybe the difference is that the *order of operands* in the source matters: `(u8*)p + off` where off is a variable → tree (plus p off) where off is a reg (mult computed separately into a reg). Then combine: (plus p (reg holding mult)) — the multiply is a separate insn: `sll v0,v0,3` then `addu`. The plus tree (plus p v0) → addu v0,a1,v0 = target!

But ours has addu v0,v0,a1 → tree (plus v0 a1)?? That would mean the source was `(u8*)p + off` with p as second operand... i.e. our source computes `off + p`? Hmm, our source: `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` → (plus (plus p off) 4) → after folding, (plus p off) where off is reg.

Unless... the difference is `p` is `D_80195AF6_t *p = D_80195AF6;` and the cast `(u8*)p` — hmm.

Wait, maybe the swap comes from combine's commutative canonicalization: gcc 2.7's combine has this in the PLUS case:

```
	      /* If we are adding a constant to a register... */
```

Honestly, let me get empirical: dump the RTL of our candidate and look at the tree, then try alternative spellings and see which yields (plus a1 v0).

But an important clue: the target's earlier block does `lui a1; addiu a1,a1,0` for &D_80195AF6 and uses `addu at,at,v0` for the newval load — i.e. (plus at v0)?? no: `addu at,at,v0` = at = at + v0 where at = &D_80195AF6 (re-materialized) and v0 = unk100. So the newval load address is D_80195AF6 + unk100 (element size 2 → *2? hmm f0 is s16 so element size 2: index*2 = unk100*2, but the asm shows just addu at,at,v0 with no shift... interesting! `D_80195AF6[unk100].f0` where the struct is 2 bytes? but later `*8` for the other array. So D_80195AF6 is an array of 2-byte structs, and D_80195AF6[unk100].f0 is at offset unk100*2 — but the asm shows no shift, so maybe the compiler used byte addressing: D_80195AF6 is `s16[]`? but the source says D_80195AF6_t *p = D_80195AF6; D_80195AF6[unk100].f0 with struct type. Hmm, then offset would be unk100 * sizeof(struct). If sizeof is 2 then the multiply by 2 becomes... a shift by 1 would appear. It doesn't. Unless the struct is 1 byte? Odd.

Wait, look: `lui at,0x0; addu at,at,v0; lh v0,0(at)`. Hmm, at = at + v0 (byte offset = unk100). Then lh v0,0(at) loads s16 at that byte offset. So D_80195AF6_t has size 1?! And the second use: `sll v0,v0,0x3; addu v0,a1,v0; lh v0,4(v0)` → offset = unk100*8 + 4, loading s16 at +4. So D_80195AF6 elements are 8 bytes, and the first load should be at unk100*8! But it's at unk100*0...

Hold on: the first block (else-if arm) is a different code path: `s16 newval = D_80195AF6[unk100].f0;` in the *first* branch arm (the `if (D_801E4BBC == 1)` arm) — that one is the earlier asm (the `lh a0,256(s0)`... hmm).

Let's re-read the objdump segment. Lines shown start at index 60 of the function's instruction list:

```
slt v0,v0,v1
bnez v0,...
nop
lh a0,256(s0)      ; unk100
li s1,1
sh a1,14(s0)
jal func_80181D30
move a1,zero
j ...
nop
lui a1,0x0         ; &D_80195AF6  -> arm 2 start
addiu a1,a1,0
lui at,0x0         ; &D_80195AF6 again
addu at,at,v0      ; + v0 (index?) 
lh v0,0(at)        ; newval
lh v1,14(s0)
move a0,v0
slt v0,v0,v1
bnez v0,...
nop
lh v0,256(s0)      ; unk100 again
lui v1,0x0         ; &D_80195AF6?? 
lhu v1,0(v1)
li s1,1
sh a0,14(s0)
sll v0,v0,0x3      ; unk100 * 8
addu v0,a1,v0
lh v0,4(v0)
```

Hmm interesting: the `newval >= CAST_SIGN(...)` test comes first (slt v0,v0,v1; bnez) then the body. But in the objdump the order is: load newval, compare, branch. Fine.

Wait the sequence "lh v0,256(s0)" appears twice; and "lui v1,0x0; lhu v1,0(v1)" — that's a different global (16-bit load).

Anyway: in the target's second arm, `lui at; addu at,at,v0` computes &D_80195AF6 + v0 where v0 = unk100?? But that would be element index * 1. Hmm — maybe D_80195AF6_t is a struct of size... the later access uses *8. So the first access `D_80195AF6[unk100].f0` should be at unk100*8. But asm shows addu at,at,v0 with no shift!

Unless v0 at that point already holds unk100*8 — i.e. the compiler computed unk100*8 once and reused it! Look: `lh v0,256(s0)` earlier loads unk100... Hmm, in the arm-2 path: "lui a1; addiu a1,a1,0; lui at; addu at,at,v0; lh v0,0(at)". Here v0 = unk100*8? But then where is the shift? The shift `sll v0,v0,0x3` appears later, in the taken branch. So v0 at the `addu at,at,v0` must be unk100 (not *8) — inconsistent with the later *8.

Unless D_80195AF6_t.f0 is at offset 0 and sizeof(D_80195AF6_t) == 1?? But then *8 later...

Hmm, wait: maybe the later `sll v0,v0,0x3; addu v0,a1,v0; lh v0,4(v0)` computes address &D_80195AF6 + unk100*8 + 4 → the load `*(s16 *)((u8 *)p + off + 4)` where off = unk100*8. And the earlier `addu at,at,v0` where v0 = unk100*... no shift. So sizeof(D_80195AF6_t) must be 1? But then `D_80195AF6[unk100].f0` = byte offset unk100 → lh at that byte. But f0 is s16 → aligned? Whatever. Then the second access uses off = unk100*8 explicitly (the source says `off = unk100 * 8`), consistent.

So the source of the original probably was:

```c
} else {
    D_80195AF6_t *p = D_80195AF6;
    s16 newval = D_80195AF6[unk100].f0;
    if (newval >= ...) {
        s1 = 1;
        ...->h = newval;
        off = unk100 * 8;
        D_801270C8 = *(s16 *)((u8 *)p + off + 4);
        ...
```

So in the target, the address tree for the last load is (plus p (plus (mult unk100 8) 4))?? and gcc produced sll + addu ptr-first.

And the first load `D_80195AF6[unk100].f0` produced `addu at,at,v0` = (plus at v0) — pointer first! Great, that's consistent: pointer + index.

In ours, the second load produced (plus v0 a1) = index first. Why? Because `off` is a variable: the multiply is computed into a separate insn (sll v0,v0,3) and then (plus p off)? That would still be pointer first...

Unless our source's tree is different: our source says `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` with off = unk100*8 (s32). Hmm.

Hold on, maybe the difference is that in ours, `p` is not a plain pointer but the *laundered* value... no, v1.c removed the asm, so p = D_80195AF6.

Hmm, but maybe in ours the compiler reuses `v0` (which held unk100) — the shift result is in v0 — and then the add: (plus p v0) should still be pointer-first in the tree.

Wait — maybe gcc's combine, when it sees (plus p (mult x 8)) where it converts the mult to a shift, produces (plus (lsh x 3) p)? And in the target the multiply was already in a register (because off is a separate variable assigned before) so the tree was (plus p off_reg) → pointer first.

In ours, is `off` a separate variable? Yes: `off = unk100 * 8;` then used. So the tree should be the same... unless gcc's combine reassociates `(plus p (plus (mult x 8) 4))` hmm.

The difference could be the cast: `((u8 *)p + off + 4)` — off is s32 (signed). Pointer + signed int → gcc computes (plus p off) with sign extension. In the target maybe off was `u32`? The notes tried "off declared u32" (v7) → still 1.

Hmm, the notes tried 11 spellings, all score 1. So the operand order is stubborn.

Since the score is 1 (one insn), maybe there's a smarter approach: use the "R5 commutative swap" move mentioned in delever_search: "the commutative swap" is a move family that swaps commutative operands! That's exactly our need. The search engine has move families: "REG on the caller-saved bank → the commutative swap, the temp inlined/introduced, the initializer split". So the engine knows a C-level move that swaps commutative operands. What is it? Probably something like `x = a + b;` vs `x = b + a;` in the C source. But the notes tried "the sum spelled as an integer addition (u32)p + (u32)off" and "with the operands the other way round" → 1.

Hmm, but the swap may need to happen at a different level: maybe the swap must be on the *load* address where the constant 4 is folded, i.e. the tree (plus (plus p off) 4). Hmm.

Alternatively use the search engine itself! `tools/delever_search.py --run --only <fn>` — the guided beam search that hill-climbs. It might find the swap. But it writes to the tree? "--run" runs the search; "the oracle writes candidates into the real source path" — dangerous (writes into src/). It says the engine writes candidates into the real source path — but with `--only`? Hmm, risky: constraint says never write src/. There's `--try` (no writes) and `--run` (writes?). The brief says use `delever_search.py --try <TU> <fn> <file> --body`. So no --run.

OK let me get the RTL dump for our candidate and for the target? We don't have the target RTL, but we can compare our candidate's RTL tree across passes to find which pass creates (plus v0 a1) instead of (plus a1 v0). If it's combine's canonicalization, then all spellings fail (as observed). If it's some pass that depends on a specific tree shape, maybe another spelling avoids it.

Since the notes claim 11 tries, and the wall requires 30 tries, I need 30 tries here. I can generate many variants programmatically.

Actually — wait. Big idea: the swap might come from **combine's "commutative operand swap" rule that puts the operand with the smaller/harder reg first**. In gcc 2.7.2 combine.c there IS this code (I'm now recalling concretely):

```c
	  /* If we have a commutative operation and one operand is a constant
	     and the other is not, put the constant in the second operand.  */
```
and separately in `combine_insns`:
```c
	      /* Simplify (set (cc) (plus (reg) (const))) */
```

Hmm, but there's also this famous gcc behavior in `simplify_rtx`/`simplify_binary`:

```c
	  /* If we are adding a constant to a register, ... */
```

I recall gcc 2.7.2's combine.c has a function `simplify_rtx` with a case for commutative ops:

```c
	    case PLUS:
	      ...
```

OK, empirical route it is. Let me dump our candidate's RTL and see the tree right after expand/after combine.

Let me set up the dump. I'll write my own dump script in my shard (adapted from T10's dump.sh) that:
1. runs --try --keep to get the scratch dir (with the spliced TU .c),
2. copies the spliced TU to my shard dir,
3. runs cc1_dumps_tu.sh with DUMP_ROOT under my shard.

But the spliced TU is 171KB and the dumps of a 5000-line TU could be big. Let me check disk space first and dump only what's needed: cc1_dumps_tu.sh uses a fixed set of -d flags (all passes). That will produce big files (maybe 50-100MB total). Disk has ~4GB free. Risky but I'll delete right after. Alternatively I can compile only the function standalone? That changes semantics.

Better: use the dump and grep just the function's section, then delete the dump dir.

Actually simpler: I don't need full dumps. I want to know the tree form of the add. Let me instead do a *targeted* experiment: write a tiny test TU? No — the tree depends on the real context.

Hmm, but actually maybe I can figure it out by looking at the difference between the two loads:
- load 1: `D_80195AF6[unk100].f0` → `addu at,at,v0` (ptr + idx)
- load 2: `*(s16*)((u8*)p + off + 4)` → `addu v0,a1,v0` (ptr + idx) in the TARGET but (idx + ptr) in ours.

So within the SAME function, the target does ptr-first for both, while ours does idx-first for the second. So the shape of the expression differs between the two loads in ours.

In our source, load 1 is `D_80195AF6[unk100].f0` (pointer arithmetic with index → (plus p idx)). Load 2 is `((u8 *)p + off + 4)` where off = unk100*8 → (plus (plus p off) 4).

So the difference: the multiply by 8. Combine converts (plus p (mult x 8)) → hmm, but off is a variable so the mult is a separate insn...

Unless gcc's combine *does* reassociate: our source's off is `s32 off` assigned `unk100 * 8`; but combine may substitute off's value back into its use (off = mult unk100 8) and then combine (plus p (mult x 8)) into (plus (lsh x 3) p)?? — putting the shift FIRST, i.e. swapping! And in the target, the same substitution should apply... unless the target's off was of a type where substitution didn't happen, or the multiply was computed as a separate insn and kept.

Hmm! Interesting: In the target, load 2's address = ptr + idx*8 + 4, and the multiply became `sll v0,v0,0x3` in the same place, with the add ptr-first. So the tree was (plus p (shift)) in the target too. So why does ours become (plus (shift) p)?

Maybe because of the `+ 4` folding: (plus (plus p (shift x 3)) 4) → combine may distribute: (plus (plus (shift) p) 4)... hmm no.

In the target: `addu v0,a1,v0; lh v0,4(v0)` — the address = ptr+shift with load offset 4. Same shape as ours presumably.

OK. Empirical: dump the RTL.

Actually, maybe easier: try MANY C spellings quickly, since scoring is 1s. The notes' 11 tries were probably hand-written; let me generate a systematic set of ~40 variants:

Variants for load 2:
a) `*(s16 *)((u8 *)p + off + 4)`
b) `*(s16 *)((u8 *)p + off) + 4`? no.
c) `((s16 *)((u8 *)p + off))[2]`? no, byte offset.
d) `*(s16 *)((u8 *)p + (off + 4))`
e) `*(s16 *)((u8 *)p + off + 4)` with off as u32 / unsigned
f) off as u32 vs s32 vs int
g) `D_801270C8 = *(s16 *)(p + off/2 + 2)`? changes arithmetic.
h) use `p` typed as u8* from the start: `u8 *pb = (u8 *)p;` then `*(s16 *)(pb + off + 4)`.
i) `off` computed as `unk100 << 3` (shift instead of mult) — notes tried v5 (as *8 spelled as <<3) → 1.
j) `off` inline: `*(s16 *)((u8 *)p + unk100 * 8 + 4)` — notes v3 tried index inlined → 1.
k) `D_801270C8 = *(s16 *)((u8 *)p + 4 + off)` (constant first)
l) `*(s16 *)((u8 *)p + off) ` with off = unk100*8+4 (fold the 4 into off): then address = (plus p off) with off = mult+const. Combine: (plus p (plus (mult x 8) 4)) → the +4 might fold into the load offset anyway.

Hmm (l) is interesting: if off = unk100*8 + 4 then the address is (plus p off) where off=(plus (mult x 8) 4) → combine folds (plus p (plus (mult x 8) 4)) → (plus (plus p (mult x 8)) 4) → the constant 4 folds into the load displacement. Order might differ!

Let me just do the dump — it's more informative and will guide all 30+ tries. But dumps are expensive in disk/time. Let me check size: the TU has 5000 lines; dumps of all passes could be ~100-300MB. Let me try with a targeted approach: run cc1 with only some -d flags? cc1_dumps_tu.sh is fixed. I can write my own compile line with only -dr (rtl) and -dc (combine)? Actually pass dump flags: -dr = RTL, -dc = combine? Let me check gcc 2.7 dump flags: -dr (rtl after expand?), -dc (final?), -ds (after scheduling), -dj, -dl (loop), -dg (global), -df (final), -dc... In gcc 2.7, -dc is "combine", -df is "final". The script includes -df (final RTL) — that's the tree dump per pass. Hmm, in gcc 2.7.2 the dump flags are: -d[a-z] where letters correspond to passes: 'a' = flow analysis, 'b' = CSE, 'c' = combine, 'd' = ... hmm.

In gcc 2.7.2, `dump-rtl` options: -da (flow graph), -db (jump), -dc (combine?), -dd (delay?), -de (expand?), -df (final), -dg (global), -dh (?), -di (inline), -dj (jump2), -dl (loop), -dm (...), -dn (?), -do (?), -dq (?), -dr (rtl), -ds (sched), -dt (cse2), -dT (tree?), -du, -dv (flow2), -dw (?), -dD, -dJ (jump2?), -dL (loop?), -dR (rtl?), -dS (final?).

Since cc1_dumps_tu.sh already exists and works, but writes all passes → big. Let me just run it and check size, then extract the function's sections with rtl.sh-like awk and delete.

Actually, wait. Before investing in dumps: maybe I should check the simplest hypothesis — that the operand order is decided by which operand is "born" first / by sched. Note the target's insn sequence:

```
lh   v0,256(s0)     ; unk100
lui  v1,0x0
lhu  v1,0(v1)
li   s1,1
sh   a0,14(s0)
sll  v0,v0,0x3
addu v0,a1,v0
lh   v0,4(v0)
```
So v0 = unk100*8 in v0, a1 = pointer. The add is `addu v0,a1,v0`.

In gcc, when the tree is (plus a1 v0) and a1 is a hard reg (a1 was assigned by global/local alloc as $a1), the output is "addu v0,a1,v0". Ours is "addu v0,v0,a1" = tree (plus v0 a1).

I recall gcc 2.7's combine has this specific code (now I'm fairly sure, from combine.c in gcc 2.x):

```c
	  /* If we have a PLUS of two registers and one of them is the
	     "constant" 0 ... */
```

No. Let me look at it from a totally different angle: what if the swap comes from **reload** (reload.c)? In reload, when an operand is in a hard register, the insn is rewritten; there's code in reload.c that swaps commutative operands to put the "reload" operand in the second position... Hmm! Actually yes: in reload.c, there's a function that handles `plus` with a memory operand: for commutative operations, the memory operand must be first (e.g. `lw a0, 0(a1)` — base last). reload rewrites (plus (mem) (reg)) etc.

But here both operands are registers.

OK, dumps. Let me do it. Steps:
1. cp the spliced TU from the score scratch to my shard: but --keep's dir gets removed? The keep option prints the candidate object path; the dir .run/P36/engine/score/.../p3/ contains cand.o and the .c. It stays (the T10 objfn.sh does `mv` to keep). I'll copy the .c to my shard dir.
2. Run cc1_dumps_tu.sh on it with DUMP_ROOT=.run/P40/T11/RM2/dumps.

Note cc1_dumps_tu.sh uses `-Isrc/shared` etc. and the file's own dir. It should work since it was designed for --try scratch copies.

Let me do it and watch disk. df first.

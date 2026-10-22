---
ts: 2026-10-22T00:50:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_mPUOrPGoi4hrvy4KWnjl
---
Excellent! Full target listing for func_8014C308 (39 ins):

```
0:  lhu v0,0(a1)
1:  nop
2:  beqz v0,6abc (+0x94)
3:  move v0,zero
4:  lw v0,88(a1)
5:  nop
6:  beqz v0,6abc
7:  move v0,zero
8:  lhu v0,94(a1)
9:  nop
10: beq v0,a2,6ab8 (+0x90)
11: li v1,0x8000
12: lw v0,92(a1)
13: nop
14: andi v0,v0,0xc100
15: bne v0,v1,6abc
16: move v0,zero
17: lh v0,174(a1)
18: andi v1,a3,0xffff
19: and v0,v0,v1
20: bnez v0,6ab8 (+0x90)
21: li v1,9
22: beq a2,v1,6abc
23: li v0,1
24: li v1,17
25: beq a2,v1,6abc
26: li v1,41
27: beq a2,v1,6abc
28: li v1,10
29: beq a2,v1,6abc
30: nop
31: lw v0,376(a0)
32: nop
33: xor v0,v0,a1
34: j 6abc
35: sltu v0,zero,v0
36: move v0,zero
37: jr ra
38: nop
```

Wait, ins 3 `move v0,zero` — this is the delay slot of the `beqz` at ins 2! The delay slot always executes, so `move v0,zero` executes even when the branch is taken → v0=0 → returns 0 ✓. Clever: the `return 0` is materialized in the delay slot.

Similarly ins 7 `move v0,zero` (delay of beqz at 6), ins 16 `move v0,zero` (delay slot of bne at 15), ins 36 `move v0,zero` (delay slot of j at 34)? Hmm, ins 34 `j 6abc` with delay slot ins 35 `sltu v0,zero,v0`. Hmm, so ins 36 `move v0,zero` is the delay slot of `jr ra` at 37 ✓ (the standard epilogue: `move v0,zero; jr ra`? no wait, that sets v0=0 always!). Hmm, ins 36 `move v0,zero` then ins 37 `jr ra` — but then the return value would always be 0! That can't be.

Unless the layout is: ins 36 `move v0,zero` is the delay slot of the branch at ins 15/20... no, ins 36 is right before `jr ra` at 37.

Hmm, the branch at 20 goes to +0x90 = 6ab8 = ins 35 (6ab8 - 6a28 = 0x90 = 36 ins → ins 36!). Let me recompute: function start address = 6abc - 0x94 = 6a28. ins i is at 6a28 + 4i. +0x90 → 6ab8 → (6ab8-6a28)/4 = 0x90/4 = 36 → ins 36 ✓. And +0x94 → 6abc → ins 37 ✓ (jr ra).

So: ins 36 = `move v0,zero` is the "return 0" block (jumped to by ins 10 and ins 20), and ins 37 = `jr ra`, ins 38 = nop (delay slot).

And the final path: ins 31 `lw v0,376(a0)`, 33 `xor v0,v0,a1`, 34 `j 6abc` (→ins 37 jr ra) with delay slot ins 35 `sltu v0,zero,v0`. ✓ (returns 1 if x != a1).

So the structure is clear:
- `return 0` → `move v0,zero` in the delay slot of the branch (ins 3, 7, 16) or in the shared block (ins 36).
- The "return 1" (four compares): `li v0,1` at ins 23 (delay slot of ins 22 beq) and the branches go directly to `jr ra` (ins 37). The value $2=1 is set once at ins 23 and stays live.

Note: ins 18 `andi v1,a3,0xffff` — the (u16) cast of arg3 → v1! And ins 11 `li v1,0x8000` — the constant 0x8000 also in v1! So v1 is used for the 0x8000 const, the u16 mask temp, and the four compare constants. Interesting: v1 is reused.

So in the target: v0 = $2 used for the loads/values and the result; v1 = $3 for constants/temps.

Now, the source C (orig.c) uses v0 (pinned $2) as the result variable and v1 as the const temp. The target's v1 usage: `li v1,0x8000` (const 0x8000 for the mask compare), `andi v1,a3,0xffff` (u16 mask temp), `li v1,9/17/41/10`.

Hmm, in the source: `if ((*(s32 *)((u8 *)arg1 + 0x5C) & 0xC100) != 0x8000)` → the const 0x8000 in v1 ✓; `(u16)arg3` → andi v1,a3,0xffff ✓ (v1 reused).

And the const temps 9/17/41/10 in v1 ✓ (the same variable v1 reused, as in the source).

Now, the crucial difference from the lever-free candidate: in the target, `li v0,1` (the result) is set ONCE at ins 23, before the compares, and the result register is $2. In the lever-free version, the const temp took $2 and the result was materialized at the return.

So the mechanism to reproduce: the result variable must live in $2 and be set before the branches.

Hmm! New idea: what if the "result 1" is not a variable but the return of the whole function computed as a phi — i.e. gcc's "return value" pseudo is $2 and gcc scheduled its set early? For gcc to set $2=1 early and keep it, the RTL must have the RESULT_DECL set early.

In C:
```
if (mask_test) {
    if (arg2 == 9) return 1;
    ...
}
```
each `return 1` → `move RESULT_DECL, 1` → gcc's cse/combine might merge the four into one set before the branches if the blocks are merged (jump threading). That's the classic gcc 2.7.2 pattern:

```
   li v0,1       <- in the delay slot
   ...
```
Hmm, actually gcc 2.7.2 for `if (a==1) return 1; if (a==2) return 1;` typically generates:
```
   li v1,1
   beq a0,v1,LABEL
   li v1,2
   beq a0,v1,LABEL
LABEL:
   move v0,zero    ?
```
no...

Honestly, empirical iteration is the way. The lever-free candidate vA_consts produced 41 ins with the const temp in v0. The notes say the v0 pseudo died. But maybe with a different source shape (e.g. `return 1` literal in all four arms) gcc produces `li v0,1` early — vH_lit1 was tried (score 17/18).

Let me look at the existing candidates to see what was tried and their scores. Let me score them all now (13 candidates) in 2 batches.

Actually, let me think about what would place `li v0,1` early in a lever-free body. If the C is:

```
s32 res = 1;                 /* decl with init */
if (arg2 == v1) return res;
```
gcc: res is a local; `res = 1` → `li res,1`; `return res` → `move RESULT_DECL,res` ×4. combine: substitute 1 → `move RESULT_DECL,1` ×4 → the four return blocks each `li $2,1` → but they're jumps to the epilogue... The target has ONE `li $2,1` at ins 23 (delay slot of the first beq) — that's a jump-threading artifact: the four `move $2,1` blocks got threaded so that the set is done once before the first branch.

Wait, actually here's the thing: if all four return blocks are `li $2,1; jr ra` and they jump to a common epilogue, gcc would place `li $2,1` in each... unless jump threading merges them into one block, giving ONE `li $2,1` before the `jr ra`. But the target has the `li $2,1` BEFORE the branches (ins 23) rather than in the merged return block (ins 37 area). Hmm, but ins 36 is `move v0,zero` (the return-0 block) and ins 37 `jr ra`. If the merged return block had `li $2,1`, it'd be between ins 36 and 37 — but ins 36 is `move v0,zero` and the branches to +0x94 (ins 37) skip it? No — a branch to ins 37 skips ins 36 ✓. So the "return 1" block would be at ins 37+ — but there's only `jr ra` at 37 and nop at 38. So no `li $2,1` block exists; the value was set at ins 23 (early) ✓.

So gcc put the set EARLY — which is what the scheduler does when the set's result is needed only at the return: gcc's "jump threading" moves the `move $2,1` into the predecessor's delay slot? Specifically, gcc 2.7.2's combine does "jump threading" through a block that just sets a register and jumps: it moves the set into the predecessor branch's delay slot! That's the classic MIPS "li in delay slot" pattern.

So: if the four returns are `move $2,1; jr ra` (each a separate block or one shared), gcc threads the `li $2,1` into the delay slot of the branch that reaches it. In the target, the four branches (ins 22,25,27,29) all branch to the `jr ra` (ins 37). The set was threaded into the delay slot of ins 22 (the first branch to that block) — but then ins 25/27/29's paths need $2=1 too: they fall through from ins 23's `li $0,1` ✓ (since the delay slot executes on the fall-through path too). Yes! The `li v0,1` at ins 23 is in the delay slot of ins 22's beq: it executes ALWAYS (both taken and not-taken paths) → so all subsequent paths have $2=1 ✓. Beautiful — that's the ROM's trick.

So the ROM's C is exactly:
```
res = 1;   /* or the value 1 set before the compares */
if (arg2 == 9) return res;
...
```
where gcc placed `li res,1` in a delay slot and threaded.

Hmm, but if gcc threaded the set into the delay slot of the FIRST branch, it must have deleted the set from the return block — that requires the value to be set before all uses.

For this to happen lever-free, gcc must NOT fold the constant into the copies... but threading the set early requires the copy to be deleted and the set hoisted. Hmm, in the target the set is `li $2,1` — writing the HARD reg $2 directly, so the RESULT_DECL ($2) got the constant.

OK let me stop theorizing and start experimenting. The empirical loop: write candidate, score, look at the diff.

Experiment set for item 1 (lever-free; the result must be in $2 and set early; the const temp in $3):

C1: `s32 res = 1;` (init at decl) + 4 `return res;`
C2: `res` assigned as `res = 1;` before the compares, with `res` declared first (order).
C3: The four returns use `return res;` but res is `s16`? Hmm, s16 res=1 → the value would be sign-extended (li v0,1 is fine, but the HImode copy might add instructions).
C4: Use `res` in the final path: `return res & (x != a1);` — hmm, the final path's `sltu v0,zero,v0` would become `andi`? `1 & cmp` folded to cmp. But it might prevent the fold of res's constant... Actually the fold substitutes the constant into the copy and deletes the set; the "use in the final path" doesn't prevent that (both uses get the constant). Hmm, but maybe combine's subst only applies to copies, and the `&` use is not a copy → then the set survives (as `li res,1`) but then res is a pseudo needing a register → it gets $2? And the copies `move $2,res` → hmm, the copies would be folded to `li $2,1`?? Then we'd have both `li res,1` and `li $2,1` → extra instruction.

Hmm, but what if res ends up allocated to $2 and the copies coalesce → the copies vanish, the set `li $2,1` survives early ✓✓. That's the target! So C4 could work if the fold doesn't happen.

Wait, but even in the target, the four returns must return the value 1 — via `return res` where res=$2=RESULT_DECL's reg → copies coalesce.

So the recipe: make `res` NOT foldable into the copies, and let reload1's coalesce put res in $2.

How to prevent folding? Make res's set a non-constant RTL. E.g. `res = 1;` is a constant. What if res is set via a copy from another pseudo: `s32 res2 = 1; res = res2;`? combine: res2's set is a constant → subst into res's set → res = 1 → then subst into the copies → fold. Hmm, combine's subst is transitive within a pass? It does one pass but the sets are processed in order.

Alternatively: make res's value depend on a runtime value that's guaranteed 1 but not constant-folded: e.g. `res = (arg3 == arg3);` — gcc folds `x == x` to 1? For non-volatile ints, gcc does fold `x == x` → 1? I believe gcc folds x==x to 1 (it's valid for integers). Hmm.

`res = (arg2 - arg2 == 0);`? folded.

`res = (u32)(a1 - a1) ? 0 : 1;`? folded.

What about a value from memory: `res = *(volatile u8*)&one;` — a load, not `li`. No.

What about `res = 1;` but with res being a `short`? then the value is HImode; the copy to the RESULT_DECL would need an extension → extra instructions.

Hmm.

What about making the value not a constant but still `li $2,1` — e.g. `res = 1 & mask` where mask is 0xFFFF... any AND with a constant folds.

What if res's set is the result of a comparison of two runtime values that are always equal but gcc can't know: e.g. `res = (*(s32*)(arg0+0x178) == *(s32*)(arg0+0x178));` — gcc would fold (same expression) → 1 → constant. Hmm, but that would also add a load.

What about `res = (arg3 & 0) != 0;`? gcc folds `x & 0` → 0 → `0 != 0` → 0. no.

Hmm, how about: the four returns return a value that is NOT 1 but the ROM shows `li v0,1`... it must be 1.

OK here's another thought: maybe combine doesn't fold because the pseudo `res` is live across a CALL — no calls here.

Alternatively: maybe the fold doesn't happen because the RESULT_DECL copy is `move RESULT_DECL, res` and res's set is in a different basic block with a label between them? combine handles labels fine.

Hmm, hold on. Let me reconsider the actual gcc 2.7.2 behavior with a simple test case. I can test directly by compiling a small C file with the project's gcc and looking at the assembly! Is there a gcc wrapper? tools/cc1_dumps.sh / cc1_dumps_tu.sh. The project builds with a specific toolchain (gcc 2.7.2 for mips). I can compile a small C file with the same flags to inspect the assembly — that's a fast iteration loop without the whole scoring machinery!

How to compile? The build's pipeline is in recipes. Let me find the compiler command: probably `mips-linux-gnu-gcc` or a wrapper in tools/bin. Let me look at the recipes file to get the exact pipeline.

That would be a great iteration loop: write a small C file with the function, compile with the same flags, and objdump... but objdump is denied by the permission classifier! Hmm. But the assembly output can be produced with `-S` (gcc -S) → a .s file I can read with cat! That works.

Let me find the compile command. Check tools/delever_oracle.py for the pipeline/recipes, and find the recipes file (probably config/recipes.json or build/...json).

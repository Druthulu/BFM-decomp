---
ts: 2026-10-22T00:49:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_zv9S6skAXwGjXUckdk1E
---
Now let me reconstruct the target (39 ins) and mine (41 ins).

Target (from diff):
```
0: ...
1: ...
2: beqz v0, +0x94      (return 0 path → 0x94? hmm)
```
Wait, target's `beqz v0, 6abc (+0x94)` at ins 2 and 6, `bne v0,v1,+0x94` at 15, `bnez v0,+0x90` at 20.

So target:
- ins 0-1: setup
- ins 2: beqz v0, RET0 (+0x94)   [the first `*(u16*)(arg1+0) == 0` test]
- ins 3-5: ...
- ins 6: beqz v0, RET0
- ...
- ins 10: beq v0,a2, +0x90  (the `*(u16*)(arg1+0x5E) != arg2` test)
- ins 11-14
- ins 15: bne v0,v1, +0x94 (the `& 0xC100 != 0x8000` test)
- ins 16-19
- ins 20: bnez v0, +0x90  (the `(*(s16*)(arg1+0xAE) & arg3) == 0` test → if nonzero jump to +0x90)
- ins 21: li v1,9
- ins 22: beq a2,v1, +0x94
- ins 23: li v0,1     (delay slot of ins 22!)
- ins 24: li v1,17
- ins 25: beq a2,v1, +0x94
- ins 26: li v1,41
- ins 27: beq a2,v1, +0x94
- ins 28: li v1,10
- ins 29: beq a2,v1, +0x94
- ins 30: ??? (the final comparison `*(s32*)(arg0+0x178) != arg1`)
- ins 31: ...
- ins 32: ...
- ins 33: ...
- ins 34: j +0x94
- ins 35: ...
- ins 36: jr ra? 
```
Hmm, target[34:35] is `j 6abc` and mine[36:37] is `j 6ac4`. Note: 0x94 = ins 23.4... let's compute: function starts at 6ac4-0x9c = 6a28. So +0x94 → 6abc, +0x9c → 6ac4.

Target ins 34: `j 6abc` (+0x94). Interesting: so after the final comparison, the code jumps to +0x94 which is... ins 23? 6abc - 6a28 = 0x94 = 148 bytes = 37 instructions. So +0x94 is ins 37 in the target (39 ins). Hmm, so ins 37 is at 6abc.

So the target's last instructions:
- ins 34: j +0x94 (jump to ins 37)
- ins 35: (delay slot) something
- ins 36: jr ra
- ins 37: li v0,1 ??? 

Hmm, that doesn't work either. Let's think: the target's epilogue at +0x94 = ins 37: `li v0,1`? and +0x98 = ins 38: `jr ra`, +0x9c = ins 39 (nop padding)? Total 39 ins: indices 0..38, addresses 6a28 + 4*i. ins 37 → 6a28+148 = 6abc = +0x94 ✓. ins 38 → 6ac0 = +0x98 = `jr ra`. And the function's end at +0x9c = 6ac4 (ins 39 would be the nop in the delay slot... but that's beyond 39 counted? Actually 39 ins means indices 0..38; `jr ra` at index 38 has a delay slot at index 39 → the function is 40 ins? Hmm, mine has 41 ins and ends with `j`/`li` pair.

Hmm, let me redo: mine[36:37] = `j 6ac4` replaced target[34:35] = `j 6abc`. So mine ins 36 is `j` and target ins 34 is `j`. Mine: 41 ins (0..40). Target: 39 ins (0..38).

In the target, ins 34 = `j 6abc` (+0x94). In mine, ins 36 = `j 6ac4` (+0x9c).

Since the alignment is by similarity, the target's ins 30-33 correspond to mine's ins 31-35 or so.

Let's think about the actual semantics: the C code is:

```
if (*(u16*)(arg1+0) == 0) return 0;
if (*(s32*)(arg1+0x58) == 0) return 0;
if (*(u16*)(arg1+0x5E) != arg2) {
    if ((*(s32*)(arg1+0x5C) & 0xC100) != 0x8000) return 0;
    if ((*(s16*)(arg1+0xAE) & arg3) == 0) {
        v0 = 1;
        v1 = 9; if (arg2 == v1) return v0;
        v1 = 0x11; if (arg2 == v1) return v0;
        v1 = 0x29; if (arg2 == v1) return v0;
        v1 = 0xA; if (arg2 == v1) return v0;
        return *(s32*)(arg0+0x178) != arg1;
    }
}
return 0;
```

Target: `v0` (the return value 1) lives in $2. The four compares use $3 (v1) for the constants. `li v0,1` is at ins 23 in the delay slot of the FIRST beq — meaning the compiler hoisted `v0=1` into the delay slot of the first branch (since v0 is dead until then... no, v0 is used in the return).

Wait: `li v0,1` in the delay slot of `beq a2,v1,RET` at ins 22 — the delay slot of a branch is executed regardless; so li v0,1 always executes when reaching ins 22. Then if the branch is taken, it returns with v0=1. If not taken, v0=1 is dead (overwritten later at the return). But the other three compares branch to RET without setting v0! Unless RET+0x94 sets v0... 

Hmm: the other branches (ins 25, 27, 29) go to +0x94 too. So they need v0=1 at +0x94. But +0x94 is a single instruction (ins 37) before jr ra at ins 38. If ins 37 is `li v0,1` then all four branches land there with v0=1 ✓. And the `li v0,1` at ins 23 (delay slot) is a SECOND set of v0=1 — redundant? But maybe it's needed for the fall-through path.

Hmm wait, but the branch at ins 22 goes to +0x94, and li v0,1 at 23 is its delay slot, so it's executed anyway. Then ins 24-29 continue with the other compares, and at ins 30+ the final computation `*(s32*)(arg0+0x178) != arg1` produces a value in v0 and then `j +0x94`?? That would overwrite v0=1. Contradiction. Unless the final path jumps elsewhere.

Let me reconsider: maybe ins 34 `j 6abc` is on the path where the result is 1 (v0 already 1 from ins 23) — no...

Alternatively the +0x94 block is:
```
37: li v0,1     <- hmm
```
Hmm, wait. Let's reconsider: maybe the target's ins 30-33 are the final comparison and `li v0,0/1`:
```
30: lw v0,0x178(arg0)     (load)
31: bne v0,arg1, ...      hmm
32: ...
33: ...
34: j +0x94
35: (delay slot) li v0,1  ??? 
36: ...
37: ...
38: jr ra
```
Hmm, mine[31:33] = `j 6ac4` + `li v0,1` were DELETED (mine has extra j+li). So mine has `j` then `li v0,1` where target has just one instruction (target[31]).

Wait — "delete mine[31:33] target[31:31]" means mine has 2 extra instructions at 31-32 replaced by nothing; then "replace mine[36:37] target[34:35]" — so target ins 34 = `j 6abc` and mine ins 36 = `j 6ac4`. Since mine[33:36] == target[31:34] (equal block), the mapping is mine[i] ↔ target[i-2] for i≥31.

So:
mine[30] == target[28]? Hmm no. Let's carefully reconstruct: the diff opcodes:
- replace mine[2:3] target[2:3]
- replace mine[6:7] target[6:7]
- replace mine[10:11] target[10:11]
- replace mine[15:16] target[15:16]
- replace mine[20:30] target[20:30]
- delete mine[31:33] target[31:31]
- replace mine[36:37] target[34:35]

Between these, equal blocks: mine[0:2]==target[0:2], mine[3:6]==target[3:6], mine[7:10]==target[7:10], mine[11:15]==target[11:15], mine[16:20]==target[16:20], mine[30:31]==target[30:31], mine[33:36]==target[31:34], mine[37:41]==target[35:39].

So target[30:31] == mine[30:31]; target[31:34] == mine[33:36]; target[34:35] == mine[36:37] (`j`); target[35:39] == mine[37:41].

So the target's last 4 instructions (35-38) equal mine's last 4 (37-40), and the target's ins 34 is the `j`.

Now the semantics of mine (41 ins): the final return is `return *(s32*)(arg0+0x178) != arg1;` which needs a comparison. Mine's structure (from the diff at 20-30):
```
20: bnez v0, 6ac4 (+0x9c)   ; the & test → jump to epilogue
21: move v0,zero
22: li v0,9
23: beq a2,v0, 6aa4 (+0x7c)
24: li v0,17
25: beq a2,v0, 6aa4
26: li v0,41
27: beq a2,v0, 6aa4
28: li v0,10
29: bne a2,v0, 6aac (+0x84)
30: (equal block) mine[30]==target[30]
31: j 6ac4 (+0x9c)
32: li v0,1
33-35: == target[31:34]
36: j 6ac4
37-40: == target[35:39]
```
Hmm, mine[31] `j 6ac4` + mine[32] `li v0,1`: that's the `return v0` (v0=1) path: since v0 was set to 1 earlier (`v0 = 1`), gcc's return sequence is `j epilogue` with `li v0,1` in the delay slot? Actually mine[21] is `move v0,zero`... hmm mine's structure has v0=1 set where?

Anyway. Mine's layout: `+0x7c` (ins 23,24,25...?) Hmm, 6aa4 - 6a28 = 0x7c = 124 bytes = 31 ins. So mine ins 31 = +0x7c. So mine[31] `j 6ac4` is at +0x7c. And the branch at mine[23] `beq a2,v0,6aa4` targets +0x7c = the `j 6ac4; li v0,1` block — i.e. the "return 1" block: `j epilogue` with `li v0,1` in the delay slot! And +0x9c (6ac4) is the epilogue `jr ra`.

Wait, but if `j 6ac4` is at +0x7c and the delay slot is `li v0,1`, then jumping to the "return 1" path sets v0=1 in the delay slot then jumps to epilogue. That's the classic gcc pattern for `return 1` in a shared block.

In the target: the four compares branch to +0x94 (6abc). And the target has `li v0,1` at ins 23 (delay slot of ins 22 `beq a2,v1,+0x94`).

Hmm, so target's "return 1" block at +0x94 = ins 37: what is it? Since target[35:39] == mine[37:41], and mine's last 4 ins are the epilogue: `jr ra` + delay... Let me figure out mine's last instructions: mine[37:41] = 4 ins. Given mine[36] = `j 6ac4` (jump to epilogue at +0x9c = ins 39 in mine? 6ac4 - 6a28 = 0x9c = 156 bytes = 39 ins → mine ins 39 = +0x9c). mine has 41 ins (0..40): ins 39 = `jr ra`, ins 40 = delay slot nop. And mine[37:39] = 2 ins before `j`: probably the final comparison (lw + sltiu/bne).

Hmm, so mine[36] `j 6ac4` then mine[37],[38] are the final comparison?? No — a `j` + delay slot means ins 37 is the delay slot of the jump. So mine[37] = delay slot of `j 6ac4` — but then the final comparison must be before... 

Hmm, but the comparison result is in v0, and the jump to the epilogue at 6ac4 passes v0 through. Then ins 37 (delay slot of j) is a nop? But mine[37:41] == target[35:39] (4 ins) — so target[35] = mine[37] = delay slot.

OK, so target:
```
34: j +0x94      (ins 36 in mine)
35: (delay slot) = mine[37]
36: = mine[38]
37: = mine[39] = jr ra? 
38: = mine[40] = nop
```
Wait, but +0x94 = ins 37 in target (since 6abc = 6a28+0x94 → (0x94/4)=37). So target ins 37 = `jr ra`? and ins 38 = nop (delay slot). Then what is at +0x94 = ins 37 = `jr ra`?? But the branches go to +0x94 = `jr ra` — then v0 must already be 1 when branching! Yes!! That's consistent: the branches at ins 25,27,29 to +0x94 = `jr ra` need v0=1 already set... but v0=1 was set only at ins 23 (delay slot of ins 22) — which executes before ins 24-29, since ins 23 is in the delay slot of ins 22 and always executes. So v0=1 is set once (ins 23) and remains live for the rest. Then the branches at 25,27,29 to `jr ra` (ins 37) return v0=1 ✓. And the branch at 22 also goes to jr ra ✓ (v0=1 set in its delay slot).

And the fall-through path (arg2 not in the set): the final computation `*(s32*)(arg0+0x178) != arg1` overwrites v0 with the comparison result, and then `j +0x94` (ins 34) jumps to `jr ra` (ins 37) with the delay slot ins 35.

So the target's structure is:
```
ins 20: bnez v0, +0x90   (if (*(s16*)(arg1+0xAE) & arg3) != 0 → jump to +0x90 = ins 35)
ins 21: li v1,9
ins 22: beq a2,v1, +0x94 (=jr ra)
ins 23: li v0,1          (delay slot)
ins 24: li v1,17
ins 25: beq a2,v1, +0x94
ins 26: li v1,41
ins 27: beq a2,v1, +0x94
ins 28: li v1,10
ins 29: beq a2,v1, +0x94
ins 30: (load final value)
ins 31: (compare)
ins 32: ?
ins 33: ?
ins 34: j +0x94
ins 35: (delay slot, = ins 35 also the +0x90 target!)
ins 36: 
ins 37: jr ra
ins 38: nop
```
Hmm wait, +0x90 = ins 35 = 6ab8. And ins 20's branch goes to +0x90. And the +0x90 block is 1 instruction before jr ra at ins 37 (0x94). So ins 35 = something like `move v0,zero` (return 0) then fall through to jr ra ✓. That's the "return 0" path! Since the C code's `return 0` after the inner block.

And mine[20] `bnez v0, 6ac4 (+0x9c)` = jump to the epilogue directly, and mine[21] `move v0,zero` — so mine has an extra `move v0,zero` (ins 21) and jumps directly to jr ra (ins 39).

So the target differs from mine: target keeps the "return 0" as a separate block at +0x90 with `move v0,zero` (1 ins) followed by jr ra, and mine merges.

Wait, mine[21] `move v0,zero` == target[21]? No: replace mine[20:30] target[20:30] covers ins 21-29. The mapping inside the replace is given line by line (mine[20+i] | target[20+i]) since both ranges have length 10. So:
mine[21]=`move v0,zero` ↔ target[21]=`li v1,9`
mine[22]=`li v0,9` ↔ target[22]=`beq a2,v1,+0x94`
mine[23]=`beq a2,v0,+0x7c` ↔ target[23]=`li v0,1`
mine[24]=`li v0,17` ↔ target[24]=`li v1,17`
mine[25]=`beq a2,v0,+0x7c` ↔ target[25]=`beq a2,v1,+0x94`
mine[26]=`li v0,41` ↔ target[26]=`li v1,41`
mine[27]=`beq a2,v0,+0x7c` ↔ target[27]=`beq a2,v1,+0x94`
mine[28]=`li v0,10` ↔ target[28]=`li v1,10`
mine[29]=`bne a2,v0,+0x84` ↔ target[29]=`beq a2,v1,+0x94`
mine[30]==target[30] (equal) — after the last compare.

So mine's structure differs: mine uses v0 (pinned $2) for the constants and v0=1 return value; the target uses v1 ($3) for constants and v0 ($2) for the 1.

Key structural difference: in mine, the return-1 value shares the register with the constants (both pinned to $2 — wait no, mine has v0 pinned $2 and v1 not pinned). Hmm, mine[22] `li v0,9` — so mine's constants are in v0 ($2, pinned) and v0=1 also in $2. That's because v0 is pinned to $2, so the const temp takes $2? But then v0=1 also needs $2 — they conflict, so mine reuses the same register sequentially: v0=1 (ins 21? no...).

Hmm mine[21] `move v0,zero`?? That's odd. Then mine[22] li v0,9. So mine's v0 holds 9, 17, 41, 10 sequentially, and the "return 1" is materialized at mine[32] `li v0,1` in the delay slot of `j +0x9c` at +0x7c. Right: mine's "return 1" block at +0x7c is `j 6ac4; li v0,1` — the return value 1 is set in the delay slot. But the branch at mine[23] goes to +0x7c which sets v0=1 then jumps to epilogue.

In the target, the constants are in v1 ($3) and the return-1 value is in v0 ($2) — a separate register, set ONCE at ins 23 (the delay slot of the first beq), and the branches jump to `jr ra` directly.

So the lever-free question: can gcc produce this without the pin? The notes say: gcc folds the constant 1 into the return copies (combine), so v0 pseudo dies, $2 stays free and the const temp takes $2 → `li v0,9` instead of `li v1,9` and the four returns need a shared block (`j RET` + `li v0,1` in the delay slot) → 41 ins.

To match the target we need:
- the constant temp in $3 (v1)
- the value 1 in $2 (v0), set once, before the first compare's delay slot
- the four branches to `jr ra` (the shared epilogue), with v0 already 1.

In lever-free C, `return 1` in four separate places → gcc creates a pseudo for the constant 1 (or folds). The pin was used to force $2.

How to get a hard $2 without a pin? We need the value to be live across the whole block and to be the return value... In gcc 2.7.2, the returned value is the RESULT_DECL pseudo, which prefers $2 (v0) — "prefers v0". The issue was that gcc folded the const 1 into copies.

Trick: make the returned value not a constant but derived so that a pseudo holds it: e.g. `return (s32)(arg3 & 0) + 1;`? That changes semantics? arg3 & 0 = 0 so it returns 1 — but the ROM's instruction is `li v0,1`, so any expression must compile to that.

What if we write `v0 = 1;` where v0 is a local variable, then `return v0;`? Then the local v0 is a pseudo; gcc would fold `v0 = 1` into the return copy (combine) → same as const.

The target's structure — the const 1 is set in the delay slot of the first branch, i.e. it's a live value across 3 branches and 4 compares. For gcc to keep a separate pseudo for the value 1 across that region, the value must be live (used in 4 returns) → gcc creates ONE pseudo for the return value, and the four `return`s copy from it to the RESULT_DECL... but with the same value 1 in all four, combine/const-fold merges them into the RESULT_DECL directly, so the pseudo dies.

To defeat the folding: make the four return values differ syntactically but be the same value? E.g. `return 1;` vs `return 1u;`? Or use a variable set once: `one = 1;` then `return one;` — gcc would propagate the constant into the copies (combine) and delete `one`.

Alternatively, express the value in a way that isn't a constant: e.g. `return (s32)(1 & ~0);`? Still constant.

Hmm — but the note said gcc's combine folds the constant 1 into the return copies so the v0 pseudo dies and $2 becomes free for the const temp. The difference in the target: the value 1 lives in $2 (a hard reg? no — $2 IS v0, a normal register!). Wait: v0 = $2. The pin was `register s32 v0 __asm__("$2")` — pinning to $2 is the same as the default preference for a return value (v0)! So why did the pin matter?

Because the const temp (v1) would take $2 if the return pseudo dies. With the pin, the return pseudo is forced to $2 and the const temp gets $3.

Hmm, but the return value in the target is `li v0,1` at ins 23, i.e. $2. And the constants are in $3.

So lever-free we need: the return-value pseudo to be a real pseudo (not const-folded) so it gets $2 via preference, and the const temp to get $3.

How to prevent const folding of the return value into the copies? Give the four returns the value via a variable that gcc can't fold... but gcc's combine will do it.

Alternative: make the returned value depend on something, e.g. the value 1 comes from a computation `1` but the ROM has exactly `li v0,1` once.

What if we restructure the C so that the four returns are actually ONE return of a variable that is set to 1 in a branch? Like:

```
s32 res;
if (arg2 == 9) res = 1;
else if (arg2 == 0x11) res = 1;
...
else res = (*(s32*)(arg0+0x178) != arg1);
return res;
```
Then res is a pseudo with 5 sets → gcc allocates it in a register (probably $2 or $3), and the `li 1` would be materialized once (or four times?) — if res is in a register, the compiler would set it in each branch: `li res,1` per branch (4 times) — not matching.

The target has ONE `li v0,1` and the branches jump to a shared `jr ra`. That's the classic "one set, many uses" shape — which requires the value to be computed before the branches (as in the original C: `v0 = 1;` before the compares, then `return v0` four times). And that's exactly the original C (with v0 pinned). Lever-free, gcc's combine folds v0=1 into each return copy (const propagation), so the set disappears.

To keep the set, the value must be non-constant at the compiler's view. E.g. set v0 = 1 via a variable that is loaded from memory? That would produce a load, not `li`.

Hmm, what about using a comma expression / assignment inside a condition that gcc can't fold? Or making the value `1` come from an expression like `(s32)(arg3 - arg3 + 1)`? gcc folds that too.

What about a value of type `s32` computed as `1` but through a `volatile`? Volatile would force a load/store — not matching.

Hmm, but maybe the key: the four returns in the target all jump to the SAME `jr ra` at ins 37, with v0=1 set once. In gcc, `return v0;` where v0 is a local variable set once before → gcc's combine will copy v0 into the RESULT_DECL at each return... Actually gcc's RTL for `return x` where x is a local: the RESULT_DECL is a pseudo; each return does `move RESULT_DECL, x`. If x's value is a constant, combine replaces RESULT_DECL with the constant (i.e., `li v0,1` at the return point). Here the target has ONE li v0,1 before the branches — meaning the RESULT_DECL pseudo itself was assigned 1 once (a single set) — that happens when gcc sees `return v0` with v0 = 1 constant: the RESULT_DECL gets the constant 1 via a single set (jump threading / tail merging). Indeed: gcc's `combine`/`cse` can convert "return 1" in 4 places into a single `li v0,1` hoisted before the branches — that's exactly the "jump threading through the shared return block" behavior. So gcc CAN produce the target shape when the value is constant, but then it may also fold into the copies.

The notes say gcc folds the constant into the copies and the const temp takes $2. But wait — if gcc hoists `li v0,1` before the branches (as the target has), then the RESULT_DECL pseudo would be $2 (prefers v0) and the const temp would get $3 — exactly the target! But gcc instead folded the constant into the copies and dropped the pseudo, giving `li v0,1` at each return? Hmm, mine (lever-free candidate, vA_consts) shows `li v0,1` at mine[32] in the delay slot of `j +0x9c` — one occurrence, in the shared "return 1" block, plus the constants in v0.

Interesting: in mine, the const temp got $2 and the return value got... mine[32] `li v0,1` — that's $2 as well (same reg, but at different times). Hmm, in mine the const temp is v0 ($2) and the return 1 is also $2 (later). So gcc reused $2.

So in the target, two different values are live simultaneously: the const temp ($3) and the return value ($2). In mine, the const temp (v0) and return value (v0) share $2 sequentially — because the return value's pseudo was folded into the copies and only materialized at the return point.

How to get gcc to keep the return value as a live pseudo assigned once before the branches? The C would need something like:

```
s32 ret;
ret = 1;
if (arg2 == 9) return ret;
...
```
gcc: `ret = 1` → a set of the pseudo ret to 1 (const). Then `return ret` → copies. combine replaces the copy's source with the constant → the set becomes `li v0,1` at the return point (each of the 4 returns gets its own li, or jump-threading merges them). But the notes said: gcc folds the constant 1 into the return copies so the v0 pseudo dies → the const temp takes $2. Hmm, but then the li v0,1 would appear at the return block, not before the branches.

Wait, in mine[31:33] there is `j 6ac4; li v0,1` — one shared block, consistent with jump threading of 4 returns into one. But the li is at the return block, whereas the target has it BEFORE the branches (delay slot of the first beq). That's the key difference!

So the target's shape: the value 1 is materialized once, early, and the branches just jump to the epilogue with v0=1. That's the shape gcc produces when the RESULT_DECL pseudo has ONE set (assigned before the branches) — i.e., when gcc does NOT fold the constant into the copies but keeps the pseudo.

When does gcc keep a pseudo for the return value with one set? If the returned value is assigned once and the returns are in different blocks, gcc's "jump threading" (in combine) can move the set before the branch: i.e., `move RESULT_DECL, ret` where ret = 1 → combine substitutes the constant → `move RESULT_DECL, 1` → and then the four copies become `li v0,1` in each return block... but jump threading merges them into one block with a single li. Hmm, the target has the li BEFORE the first branch, in the delay slot.

The delay slot position is characteristic: the compiler scheduled the `li v0,1` into the delay slot of the first beq because it's free there (the value is dead until the branch is taken). That means gcc kept the set of RESULT_DECL (=1) as an instruction before the branch chain, and the value was already known to be 1... 

Actually here's a cleaner hypothesis: the source C was something like:
```
v0 = 1;               /* the result var */
if (arg2 == v1) return v0;
```
where the compiler assigned the RESULT_DECL from v0 once? Hmm.

Whatever the mechanism, the practical question: is there a C spelling (lever-free) that makes gcc produce: const temp in $3, one `li v0,1` before the branches, four branches to the shared epilogue?

Since the return pseudo prefers $2 (v0) and the const temp would then get $3 (v1) — the const temp must NOT be given $2. In mine, the const temp got $2 because the return pseudo died (folded). So we need the return pseudo to survive as a real pseudo with one set.

How to keep a pseudo alive: make the value non-constant at RTL level but compile to `li v0,1`... e.g. `ret = 1;` where ret is later reassigned? No.

Alternative: the value 1 comes from a comparison: e.g. `ret = (arg3 == arg3)`? gcc folds. `ret = (s32)(some_load != 0)`? That adds instructions.

Hmm what about the classic trick: use `volatile`? no.

Alternatively make the return value the result of a function returning 1? no.

Hmm. Think about gcc 2.7.2's combine: it does "subst" of constants into copies and deletes the source set if the pseudo is dead. The RESULT_DECL is the destination of the copy; its value is the return value. combine looks at the copy `move RESULT_DECL, ret` where ret has a single set `move ret, 1`. Then combine can substitute: RESULT_DECL gets the constant 1 → the set of ret is deleted and RESULT_DECL is set to 1 at the copy point.

In the target, the RESULT_DECL is set to 1 ONCE, before the branches, and the four returns are just jumps to the epilogue. That's what happens when the four copies of RESULT_DECL are merged: i.e., jump-threading merges the four `return` blocks into one, and then the single `move RESULT_DECL, 1` (or `li v0,1`) is placed in the merged block. But the target has it in the delay slot of the FIRST branch — i.e. the merged return block's `li v0,1` was scheduled INTO the delay slot of the branch that jumps to it. That's exactly what gcc's delay-slot scheduling does: the `li v0,1` is moved into the delay slot of the `beq` that jumps to the return block, since the delay slot is otherwise empty. That's the classic "return 1" pattern:

```
   beq a2,v1, RET
   li v0,1        <- delay slot
   ...
RET:
   jr ra
```
YES! This is the standard gcc 2.7.2 pattern for a shared "return 1" block: the constant is loaded into the delay slot of the LAST branch that jumps to the block (or the first?). Here it's the first branch (ins 22) — but the other three branches (25,27,29) also jump to RET, and their delay slots contain the next `li v1,17` etc. So the `li v0,1` was scheduled into the delay slot of ins 22 (the first one) and the others' delay slots were taken by the const loads.

Hmm, so gcc put the return-value set into the delay slot of one of the branches. This is standard: the merged return block has `li v0,1; jr ra`, and gcc's final scheduling hoists `li v0,1` into the delay slot of a branch that falls into the return block... but branches that jump TO the return block can't have the delay slot executed on the taken path — well, delay slots always execute, so it's fine.

Hmm, but which branch gets it? The one at ins 22 — the first. But wait, if the li is in ins 22's delay slot, then it's executed on every fall-through too, which is fine (dead there).

So the target shape = gcc's normal output for:
```
v0 = 1;   /* one set */
if (arg2 == v1) return v0;   /* 4 returns sharing a block */
```
where the ONE set is scheduled into the delay slot of the first branch. And mine (lever-free) has the same shape except the constant temp got $2 instead of $3 — because the v0 pseudo died and gcc folded.

So the real difference: TARGET has the const temp in $3 and the return value in $2. MINE has the const temp in $2 and the return value materialized at the return block ($2 too).

Key: in the target the const temp (v1) is live across ALL FOUR compares (it holds 9, then 17, then 41, then 10 — it's reassigned each time, so its live ranges are separate). Hmm, actually the same pseudo reused for 4 constants (v1 = 9; v1 = 17; ...) — in the C source, v1 is one variable reassigned. That's why in the target it's one register $3 with 4 sets.

In mine, the const temp also is one variable (v1?) — hmm, in mine the constants are in v0 (which is the pinned var) — so in mine the compiler used the PINNED variable for the constants?! Wait no: in the candidate vA_consts, maybe the const temps are separate. Let me look at vA_consts.c.

Actually wait. In the ORIGINAL (pinned) source, there are two variables: v0 (pinned $2) = the return value, and v1 = the const temp. In the target: v0=$2 (return), v1=$3 (const). ✓ consistent.

In the lever-free candidate (vA_consts?), the compiler assigned: const temp → $2, return value → also $2 (materialized at the return block). So the const temp took $2 because the return pseudo died early.

So the question: how do we keep the return pseudo alive so it gets $2 (preferred) and the const temp gets $3?

In gcc, the RESULT_DECL prefers $2. If the RESULT_DECL is set by a copy from a pseudo `v0` which is set to a constant 1, combine may fold. But if the pseudo `v0` is set to 1 in a way that keeps it as a pseudo (e.g. `v0 = 1;` where v0 is a local) — the C source DOES that (v0 = 1). And gcc still folded it.

Hmm, "the v0 pseudo dies" — but in the target the value is also 1. Both target and mine have `li v0,1` once. The difference is WHERE (delay slot of the first beq vs. the return block) and the const temp's register.

Wait — actually maybe in the target, `li v0,1` at ins 23 IS the set of the RESULT_DECL pseudo... no, `li v0,1` writes a real register. If RESULT_DECL (a pseudo) is copied to $2 at the end, we'd see `move v0,zero`/`li v0,1` at the return. Hmm, in the target the epilogue is just `jr ra` at ins 37 (no move). So the RESULT_DECL was assigned $2 directly (the pseudo was allocated to $2, i.e. "prefers v0" → allocated in a hard reg v0), and the set `li v0,1` happened once before the branches.

So in the target, RESULT_DECL = a hard-reg pseudo in $2 with one set of 1 — meaning combine did NOT fold the constant into the copies; instead the pseudo got a single set and jump threading merged the returns, and the set was scheduled into a delay slot.

In mine, RESULT_DECL also would be in $2 with `li v0,1` at the return block (mine[32]) — that's the same pseudo set but scheduled at the return block instead of before the branches! And the difference in const temp register ($2 vs $3)...

Hmm wait. If in mine the RESULT_DECL is in $2 with its single set at the return block (ins 32), and the const temp needs a register across the whole compare chain, then the const temp can't use $2 (occupied by RESULT_DECL? no — RESULT_DECL's set is at the return block, after the compares; live range of RESULT_DECL pseudo from the return block to the end...). Actually if RESULT_DECL is a hard-reg pseudo in $2 whose set is at the return block, then $2 is not live during the compares → the const temp can take $2 → `li v0,9` etc. That's mine.

In the target, the RESULT_DECL's set is BEFORE the compares (ins 23), so $2 is live from ins 23 to the end → the const temp can't use $2 → takes $3 ✓.

So the crux: get gcc to place the RESULT_DECL's single set BEFORE the compare chain (in a delay slot), rather than at the merged return block.

Why does gcc put it at the return block in mine? Because the return blocks were merged into one and the set was placed there; in the target, the set was placed in the delay slot of a branch leading to the return block.

Hmm, actually the difference may be that in the target the returns were NOT merged into a shared block: instead, each `return v0` is a jump to the epilogue where the value is already in $2 (RESULT_DECL allocated to $2). I.e., in the target, the value 1 is set BEFORE the branches (ins 23) — the C is literally `v0 = 1; if (...) return v0;` and gcc did NOT copy v0 into RESULT_DECL at each return but rather kept the value in $2 throughout, with RESULT_DECL = $2 (the pseudo for the return value being the same as v0? no...).

Actually here's a cleaner reading: gcc's RTL for `return v0` is `move RESULT_DECL, v0`. With RESULT_DECL hard-allocated to $2 and v0 also... if v0 is allocated to $2 as well, the copy becomes a no-op (jump threading: `move $2,$2` deleted) and v0's set `li $2,1` stays where it was (before the branches) ✓. That's the target! And in mine (lever-free), v0 gets a different register ($3?) and RESULT_DECL gets $2, so the copy `move $2, v0` exists at each return → merged return block with `li v0,1` (the copy of the constant) at the return.

Hmm, in mine the copy `move $2,v0` would appear... mine[32] is `li v0,1` (not a move) → combine replaced the copy with the constant since v0's set is a constant → the copy `move $2, 1` becomes `li $2,1` at the return block ✓. And the source set `li v0,1` (v0's set) was deleted as dead. So combine killed v0's early set and materialized the constant at the return.

In the target, v0's early set survived because the copy was deleted (v0 and RESULT_DECL in the same reg $2).

So: to reproduce the target lever-free, we need v0 (the local holding 1) to be allocated to the SAME register as RESULT_DECL ($2), i.e. gcc must allocate the local `v0` to $2 (v0 is its preferred reg for... hmm, locals don't prefer v0).

Since RESULT_DECL prefers v0 ($2), and the local v0 is a separate pseudo, gcc's global-alloc would assign the local to $3 (or whatever) and RESULT_DECL to $2. Then the copy `move $2,$3` remains. For the target we need them merged.

BUT: with the pin `register s32 v0 __asm__("$2")`, the local v0 is FORCED to $2, and RESULT_DECL prefers $2 — but a pseudo can't be in a hard reg that's already... they can share $2 if their live ranges don't overlap! The local v0's live range ends at the copies (the returns), and RESULT_DECL's live range starts at the copies. Since the returns jump to a shared epilogue... hmm, but the live ranges overlap at the copy points.

Hmm, whatever: gcc allowed it (that's the observed target).

So lever-free, how can we get a local to be allocated to $2 = the same reg as RESULT_DECL? If the local is the RESULT_DECL itself — i.e. the returned expression's value lives in $2.

Alternative: make the return value a local that is ALSO the return: e.g.
```
s32 v0;
v0 = 1;
if (arg2 == v1) return v0;
```
GCC: `return v0` → `move RESULT_DECL, v0`. If v0 is allocated $2 and RESULT_DECL also $2, the copy is deleted.

For gcc to allocate the local v0 to $2, the local needs a preference for $2. gcc 2.7.2 doesn't have "prefer v0" for locals generally... but it does for certain patterns? Hmm.

Alternative approach: eliminate the local and write the expression so the RESULT_DECL itself holds 1 from the start:
```
if (arg2 == v1) return 1;
```
→ 4 `return 1`s → each `move RESULT_DECL, 1` → jump-threaded into one → `li $2,1` at the return block. Not the target.

So the target fundamentally needs the constant to be set before the branches, and $2 to be live across the branches. What C produces that? "v0 = 1; ... return v0;" with v0 in $2.

Hmm — maybe the trick: make the returned value a variable that gcc keeps in $2 because it IS the RESULT_DECL: i.e. the value assigned to the result variable is later returned...

What about using a compound assignment or a conditional expression that gcc puts in the return register? Like:
```
return (arg2 == 9) ? 1 : (arg2 == 0x11) ? 1 : ...
```
That would produce compares + branches differently.

Alternatively: think about what makes gcc keep a value in a register across a branch: it must be live at the merge point. In the target, $2=1 is live across ins 24-33 (three branches and the final computation). Its use is the four returns.

Consider this C:
```
s32 v0 = 1;
if (arg2 == v1) return v0;
if (arg2 == v1) return v0;
if (arg2 == v1) return v0;
if (arg2 == v1) return v0;
return *(s32*)(arg0+0x178) != arg1;
```
where v1 is the const temp. gcc: v0's set `li v0,1` (pseudo), then four `move RESULT_DECL, v0`. combine: RESULT_DECL copies get the constant → v0's set dead → the four returns each become `li $2,1` → merged → the return block has `li $2,1; jr ra` — mine.

Hmm, that's what mine does. So the target must have been produced by a source where the copies were NOT const-folded — i.e., where the value in $2 is a pseudo that gcc allocated to $2 and the RESULT_DECL copy was elided.

When does gcc elide `move RESULT_DECL, v0`? When v0 and RESULT_DECL are the same register after allocation (coalescing). RESULT_DECL prefers $2 (v0). So if v0 (the local) is allocated to $2 as well, coalescing merges them and the copy disappears → the target.

How to make gcc allocate a local to $2? Options:
- The local is used as a call argument? no.
- The local's value is the function's return value AND the function returns it directly: `return v0;` where v0 is the only assignment... that's the same.

Hmm! What if the local IS the return value via a pointer/struct? no.

What about gcc's "hard reg" preferences: in gcc 2.7.2, the RESULT_DECL is a pseudo with a "preference" for the return register. Regular locals have no preference, so global-alloc picks by priority/order.

Hmm, but wait: what if there is no local at all, and the value 1 is produced by the same pseudo that the RESULT_DECL uses...

Alternative idea: make the four `return` statements return the SAME variable that is also the loop... no.

Let me think about a completely different C shape that yields the target:

```
s32 res;
...
res = 1;
switch (arg2) {
case 9: case 0x11: case 0x29: case 0xA: return res;
}
return *(s32*)(arg0+0x178) != arg1;
```
Switch → the compiler generates a jump table or comparisons; the ROM has 4 compares (not a jump table), so no.

What about:
```
s32 res = 1;
if (arg2 == 9 || arg2 == 0x11 || arg2 == 0x29 || arg2 == 0xA) return res;
```
→ gcc generates 4 compares with branches to a shared return ✓ (that matches the target's structure: 4 `li v1,const` + `beq` to the same block). With `||`, gcc creates a chain of compares and branches, each jumping to the return block. The const temp v1 reused ✓.

Now the value: `res` is a local. Same problem.

Hmm, but maybe with `||` gcc's structure differs enough: the branches to the "return res" block: `move RESULT_DECL, res` in the block → combine → `li $2,1`. Same.

So the crux is unavoidable: gcc 2.7.2 folds the constant.

UNLESS the value is not a compile-time constant to gcc but still compiles to `li v0,1`. E.g.:
- `res = 1;` then `res += 0;`? folded.
- `res = (s32)(1);` folded.
- `res = arg3 & 0;`? folded to 0.
- `res = (arg3 == arg3) ? 1 : 1;`? folded.
- Something involving a load: `res = *(u8*)&some_const_1`? That's a load — the target has `li v0,1` not a load. But masking? The masked diff masks relocations but not load vs li.

Hmm. But wait — maybe I have the causality backwards. Maybe the target's `li v0,1` at ins 23 is NOT the return value but the pinned pseudo v0, and the RESULT_DECL copy is `move v0, v0`?? No...

Let me reconsider: maybe the target's ins 23 `li v0,1` is the set of the LOCAL v0 (pinned to $2 in the original source!) and the returns are `move RESULT_DECL, v0` → but RESULT_DECL is also $2 → coalesced → deleted → so the returns are just jumps ✓✓. That is: with the pin, v0 ($2) and RESULT_DECL ($2) coalesce and the copy is elided, and v0's set (`li $2,1`) survives at its original position (ins 23, delay slot of the first beq, scheduled there by the scheduler since it's dead until the return).

So the pin's role: force the local into $2, coalescing with RESULT_DECL.

Lever-free equivalent: we need a local that gcc allocates into $2 (the same reg as RESULT_DECL) — then the copies elide and the set survives early.

How can a local get $2 in gcc 2.7.2? Hmm, gcc 2.7.2 has a "REG_PREFER" for locals? There's the "user_prefer" for some patterns. Not in 2.7.2.

Alternative: Make the local's live range identical to RESULT_DECL's and hope for coalescing... but RESULT_DECL gets $2 (preferred) and the local gets $3.

Hmm, unless the local IS the RESULT_DECL. In C, you can't assign to the result decl. BUT: consider a function whose return value is assigned from a variable — `return x;` where x is a parameter! Parameters are in $a0-$a3, not $2.

What about a local declared with the SAME name... no.

Hmm, what about making the value flow through a function-call return? e.g. `res = func();` no.

Alternative trick: the value 1 could be produced by an expression whose RESULT is a pseudo that gcc allocates to $2 — e.g. the RESULT_DECL of a nested expression. Consider:

```
if (cond) { s32 t = 1; if (arg2 == v1) return t; ... }
```
no.

New idea: what if the return value comes from a comparison that yields 1, e.g. `return (arg3 != 0) ? ...`? no.

OK, radical alternative: maybe use `do { } while(0)` tricks or `&&`/`||` folds to shape the code so that gcc produces the same instruction sequence with the value in $2 via a different route.

Wait. Let's reconsider the mine diff: mine has the const temp in $2 (v0) — that's because in mine the local v0 (holding 1) was allocated $3 and the const temp v1 got $2? Let's check the candidate vA_consts.c to see the source shape. Let me read it.

Actually let me check what the register pairs said: "register pairs (mine -> target, count): v0->v1 x3" — 3 instructions where mine uses v0 and target uses v1 (the const loads li v0,9/17/41/10 → target li v1,9/...). So indeed mine's const temp = v0 ($2) and target's = v1 ($3).

Now: in mine, the local holding 1 (call it `res`) is allocated where? The return value materialization `li v0,1` at the return block ($2 = RESULT_DECL). And the local `res` was folded away.

So we need the local `res` (holding 1) to be in $2 (or the RESULT_DECL to be in $3 and the local in $2 with the copy coalesced... no: the copy `move RESULT_DECL, res` with res=$2 and RESULT_DECL=$3 would be `move $3,$2` — not deleted).

So the local must be in $2 = RESULT_DECL's reg.

Ways to get a pseudo into $2 in gcc 2.7.2:
1. Hard-reg pin (excluded).
2. The pseudo IS the RESULT_DECL: i.e. the value returned is directly an expression whose RTL is a pseudo in $2. E.g. `return res;` — the copy is `move RESULT_DECL, res` — two pseudos. Hmm.

BUT: what if res is a *parameter*? Parameters live in $a0..$a3 — but with a "register" preference... no.

3. What if the value 1 is loaded into $2 by the compiler as the RESULT_DECL set — i.e. the RESULT_DECL's set happens early because the function has a single exit path?? What if the C is written so that all returns are ONE return at the end?

```
s32 res;
if (...) { ... res = 1; ... }
else res = ...;
return res;
```
Then the RESULT_DECL gets its value at the end (a copy from res), which is a phi. Not the target (the target has 4 separate `jr ra` paths? Actually the target's four branches all go to ins 37 `jr ra` — a single shared epilogue! And the final path also does `j +0x94` → ins 37. So the target has ONE epilogue, all paths converge ✓.

Hmm! So maybe the target's structure is: all paths converge to a single `jr ra`, with the value in $2 set on each path. But there's only ONE `li v0,1` (ins 23) — set before the four branches. So the four "return 1" paths share that.

OK here's another thought — what if the value 1 comes from the `res` variable being assigned in a place where gcc keeps it in $2 because it's the ONLY value in $2...

Honestly, maybe a simpler approach: use the C0505 catalog moves: "temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse". These are the allowed real C moves. The prior coder tried many.

Since a MATCH requires byte-identical output, and this is a pin-wall item (the G08 coder concluded a wall after 13+ tries), my realistic goal is to try a reasonable number of new moves, and if nothing cracks, record a WALL with the mechanism (evidence = gcc pass + mechanism). The brief requires ≥20 min and ≥30 scored tries for a WALL.

But hmm, "best" for a WALL = the lowest score of a lever-free body (17 for item 1 currently). If I find something better (e.g. 12), that's a better row.

Given the budget (20-30 min per item, 5 items), and that each scoring run takes ~10-20 s, I can do maybe 30-60 tries per item. Let me check how long one --try takes.

Let me now think about what other lever-free moves might work for item 1:

Idea A: Make the returned value 1 come from an expression that gcc materializes into $2 early and keeps live: e.g.
```
s32 res;
res = 1;
if (arg2 == v1) return res;
```
Test what gcc does. Already tried (that's basically the source).

Idea B: Use `&&`/`||` folds: e.g. `if ((arg2 == 9 || arg2 == 0x11 || arg2 == 0x29 || arg2 == 0xA)) return 1;` — the "return 1" as a literal. The notes said tried (vH_lit1).

Idea C: Change the order of the four compares or the const reuse: e.g. use four separate const vars (tried: vE_4temps).

Idea D: Make the return value non-constant to gcc but `li v0,1` in the ROM: e.g. `res = (s32)(1u)`? same.

Idea E: Use `arg2` itself: The ROM's compares are `beq a2, v1`. In mine, the const temp is v0.

Idea F: What if the local `res` is declared as a `u8`? Then `res = 1` is a zero-extended const (and 0xff) — the target has `li v0,1` (a full 32-bit li). A u8 local would need `li v0,1` + mask? no: `li v0,1` then use as u8 → the HImode copy. That would add instructions. Notes say "v0/v1 widths s16/u16" tried.

Idea G: Use a struct/union? Not in the catalog list.

Idea H: The key insight might be: the target's `li v0,1` is in the delay slot of the FIRST beq. In mine, the `li v0,1` is in the delay slot of the `j` at the return block. If gcc put the constant set earlier (before the compares), the const temp would then need $3 (since $2 is live). So the goal: make gcc emit the return-value set BEFORE the compare chain.

Why would gcc do that? If the return value is set at the top of the function and used in multiple exits (i.e. a variable assigned early and returned in several places) — then gcc's RTL has the set early, and the copies at the returns are `move RESULT_DECL, res`. combine then folds the constant into the copies and DELETES the early set (since res becomes dead) — that's the mining. But if combine does NOT fold (e.g. because res is not a constant but a copy chain), the early set survives and the copies remain `move $2,$3` — extra instructions.

Hmm, so we need: early set + copies elided by coalescing.

Coalescing: gcc's combine deletes a copy if src and dst are the same register after allocation — but combine runs BEFORE register allocation in gcc 2.7.2 (combine is a RTL pass, before regalloc). So combine can't see the allocation. The copy elimination happens in reload/regalloc? Actually gcc 2.7.2's local-alloc/global-alloc can coalesce? There's "coalesce" in the reload pass (reload1 has a coalesce step? "reload1" does "coalesce" — yes, reload1.c has a coalesce pass that merges a copy's src and dst regs when possible). So the copy `move RESULT_DECL, res` can be coalesced at reload time if RESULT_DECL ($2, hard) and res can be allocated to $2.

So: if res is allocated to $2, reload1 coalesces the copy → the set `li $2,1` (res's set, after allocation res→$2) stays at the early position ✓✓✓. That's exactly the target.

But then the const temp must go to $3 — since $2 is live from the early set to the returns.

So the question becomes: how to make gcc allocate the local `res` to $2 (RESULT_DECL's reg) lever-free?

In gcc 2.7.2, global-alloc assigns hard regs; RESULT_DECL prefers $2 ("prefers v0" per the notes). The local res has no preference. BUT: reload1's coalesce works the other way too: it can move res into $2 if the copy allows.

Actually here's the thing: since RESULT_DECL is $2 and there's a copy `move $2, res`, coalesce can try to put res in $2 (if $2 is free there). $2 is free before the early set? The early set is `li res, 1` — if res is allocated to $2, that set becomes `li $2,1` and the copy is removed. Coalesce in reload1 does exactly this: "coalesce" merges the copy with the src if the src's live range allows and the dst is a hard reg.

But in mine, combine already replaced the copy with the constant (`move $2, res` → `move $2, 1` → `li $2,1`), and deleted res's set. So the key is to prevent combine from folding the constant into the copy.

How to prevent combine from seeing the constant? Make the set of res NOT a constant: e.g. `res = 1;` → constant. What if the value is set by a copy from another pseudo whose value isn't constant... but we need `li $2,1` in the output.

Hmm, what if the set is `res = 1;` but res is `volatile`? That forces memory traffic (store/load) — no.

What if the copy source is the RESULT_DECL itself? Impossible in C.

What if there is no copy at all: the return statement's expression is directly a variable → `return res;` — that IS the copy.

OK so how did the ORIGINAL (with pin) avoid the folding? Because with the pin, res is a HARD REG pseudo ($2) — combine handles hard regs differently: the copy `move RESULT_DECL, res` where res is a hard reg $2 and RESULT_DECL is a pseudo... combine can't fold a constant into it? It can: `move RESULT_DECL, $2` → it would substitute $2's value (1) → same folding. Hmm, but the observed target keeps the early `li $2,1`.

Wait — maybe with the pin, res IS $2 and RESULT_DECL is also $2 → the copy `move $2,$2` is deleted at RTL level (self-copy) → no folding opportunity → res's set survives ✓✓✓. YES! That's the mechanism: the pin makes res a hard reg $2; the return statement's copy `move RESULT_DECL, res` — combine sees res = $2 (hard reg) and RESULT_DECL (pseudo). It can't delete the copy (different), but it can still substitute the constant 1 into it → `move RESULT_DECL, 1`. Hmm, but then the early set would be deleted and the constant materialized at the return.

Unless... the RESULT_DECL is allocated to $2 as well, and the copy `move $2, $2` is deleted in reload1's coalesce — but combine would have already folded the constant.

Hmm, but the observed target has the early `li $2,1`. So combine did NOT fold. Why? Because combine's "subst" of a constant into a copy requires the source to be a pseudo with a single set of a constant, and it checks that the source is dead after. Here res ($2) is used by 4 copies; combine can substitute the constant into all 4 copies and delete the set — that's what happened in mine.

Unless the fold was blocked because the source is a HARD REG (hard regs aren't deleted by combine in 2.7.2?). combine's optimization "subst" handles constants; for hard reg sources, combine does not delete the set of a hard reg (it can't remove the insn that sets $2? it can - `li $2,1` could be deleted if $2 is dead... but combine generally doesn't delete hard-reg instructions? It does sometimes).

OK. Empirically: with the pin, the early set survives. Without, it doesn't.

So: can I make the "res" pseudo a hard reg WITHOUT a pin? Yes! By making it a FUNCTION PARAMETER? no, params are $a0-$a3. By making it... hmm, "hard reg" for a local only via register asm (excluded).

BUT: what about making the value flow through a call? no.

Alternative: avoid the copy entirely by having the function's return value BE the constant expression evaluated early — impossible.

Alternative: give gcc a reason to keep the early set: e.g. if the early value is ALSO used elsewhere (not just returned) → then it's live across the compares and gcc keeps it in a register; but then it's not the RESULT_DECL, so the copies remain → extra `move` instructions. Unless the copies are coalesced at reload time (res→$2 = RESULT_DECL's reg). Coalesce in reload1: for `move $2, res`, it can allocate res to $2 if $2 is free in res's range... but $2 is occupied by RESULT_DECL (live from the copy to the end) — hmm, RESULT_DECL's live range: from the copy to the function end (the return value). res's live range: from the early set to the copy. These OVERLAP? The copy is at the copy point; RESULT_DECL is live from there on. res is live from the early set to the copy. They don't overlap! So res can be in $2 before the copy, and RESULT_DECL in $2 after → coalesce ✓.

So the question is whether gcc's global-alloc/local-alloc would choose $2 for res. It competes with the const temp. Priority: RESULT_DECL (pri ~?), the const temp, res.

Hmm — but here's the thing: if combine folded the constant, res's set is deleted, so no coalesce opportunity.

The trick must therefore be to make the early value NOT a constant to gcc. What if the early value is the result of a comparison? e.g. `res = (arg3 != 0);` no — ROM has `li v0,1` exactly.

Hmm, what if `res` is set to 1 via a variable that gcc treats as unknown at compile time but is 1 at runtime? Impossible without a load.

WAIT. What about the ROM's `li v0,1` — could that be the RESULT_DECL set placed early because the function's single exit point is at the end and the value is a PHI? Hmm, in the target, the four branches go to ins 37 = `jr ra` — but is that really the function's single exit? The `li v0,1` at ins 23 sets $2 = 1 for the paths that return 1. The final path computes a different value in $2. So $2 is a PHI-ish merge: different values on different paths → the merge point (ins 37) just does `jr ra` with $2 set differently per path. That's fine in MIPS without a phi (each path sets $2 before the jump).

So on the "return 1" path: $2 = 1 set at ins 23 (early, in the delay slot of the first beq). On the final path: $2 = comparison result.

So the target's C is exactly:
```
res = 1;                        /* early set, in $2 */
if (arg2 == 9) return res;
if (arg2 == 17) return res;
if (arg2 == 41) return res;
if (arg2 == 10) return res;
return (*(s32*)(arg0+0x178) != arg1);
```
and gcc (2.7.2) — WITHOUT the pin — would produce the same, IF res were allocated $2 and the copies coalesced.

Since the notes say gcc instead folds the constant, maybe there's a way to make the constant fold not happen: e.g., if the four returns are in the same basic block or the value has multiple uses...

What if `res` is ALSO used in the final path? e.g. no.

What if res is assigned in the middle of the block and there are other uses?

Alternatively: what if we express the early value as `res = 1;` but ALSO modify res later in a way that's dead? e.g. `res = 1; ... res = 2; return res;`? That changes semantics (the four returns must return 1).

Hmm what if the early set is `res = 1;` and the four returns return `res`, and additionally there's a use of res in the final path that keeps it live — e.g. `return res & (*(s32*)(arg0+0x178) != arg1);`? That changes semantics: the ROM's final path returns the comparison result (0/1), and the four paths return 1. If res=1 always, `res & cmp` == cmp ✓ SAME SEMANTICS! And it gives res a second use → combine can't fold res's constant into the copies? Hmm, combine CAN still substitute the constant 1 into the copies and delete the set (it's still a constant with multiple uses — combine substitutes constants into all uses, that's normal constant propagation). Hmm.

Actually, combine's "subst" of a constant into a copy is a standard optimization; it would still fold.

Unless the value is not a constant but gcc's RTL treats it as a "pseudo set by a comparison". Hmm.

Let me consider: maybe the real difference is that in mine the const temp took $2 and the return value materialized at the return block — maybe the ORDER of allocation matters: gcc allocates the const temp first (it's born earlier) and gets $2.

What if we could make the const temp's priority lower so it goes to $3, leaving $2 for the return value? The const temp is used 4 times (4 sets). Hmm.

Alternatively — what if we make the const temp NOT a register at all: e.g. compare arg2 against literals directly: `if (arg2 == 9) return res;` — gcc would generate `li v1,9` (needs a temp) or `li at,9`? It would use a temp pseudo for the constant. Same.

Hmm, what if the constants are compared via `arg2 - 9 == 0`? gcc would do `addiu v0, a2, -9; beqz v0` → different instructions. No.

OK, let me consider the possibility that the win comes from a completely different source shape: what if the four compares are in a `switch`? ROM has 4 compares → switch would use a jump table (no).

What if the source is:
```
switch (arg2) {
case 9: case 0x11: case 0x29: case 0xA: return res;
}
```
gcc with 4 sparse cases → compares + branches ✓ but the order of the compares might be sorted by value (9, 10, 0x11, 0x29) — the ROM order is 9, 0x11, 0x29, 0xA → NOT sorted → so not a switch (or a switch with the original order? gcc sorts cases in a jump table; for sparse cases it does compares in value order usually). The ROM order 9, 17, 41, 10 is the SOURCE order → so the source is 4 separate ifs ✓ (as in orig.c).

OK so the shape is fixed; the issue is purely allocation.

New idea: make the const temp's live range overlap the return value differently... The const temp (v1) is set to 9, then 17, then 41, then 10 — 4 sets, so its live range is disjoint segments. In the target it's $3.

The return value res: live from ins 23 to the returns. It's live at the same time as the const temp → they need different registers ✓ (target $2 and $3).

In mine: res died (folded) → only the const temp needs a register → $2. And the RESULT_DECL gets $2 at the return block.

So the whole game is preventing the constant fold. In gcc 2.7.2, `combine` does "subst" — but importantly, combine only substitutes a constant into a copy if the copy's source is a pseudo whose definition is a single set of a constant AND the pseudo is not... Hmm, and there's a condition: "if the source is used in a non-copy context, don't substitute" — no, substitution is allowed for all uses; the set is deleted only if all uses are substituted.

Hmm, so with 4 copies, all substituted, set deleted.

BUT: gcc 2.7.2's combine might refuse to substitute if the constant's mode differs or if the pseudo is "used in a phi". Alternatively, if the pseudo is set in a block and used in another block (cross-block), combine's "subst" doesn't cross basic blocks? Actually combine works on the whole function (RTL is a single instruction list with labels), so it can.

Hmm, but there IS a known gcc behavior: constants are propagated within a basic block by cse, and combine does cross-block propagation too.

What if the four returns are in DIFFERENT basic blocks (they are — each `if` creates a block)? Then the early set is in the entry block, and the copies are in 4 exit blocks. gcc 2.7.2's combine does propagate constants across blocks (that's how it optimizes `x=1; if(...) return x;`).

Hmm.

What if the early set is in a DIFFERENT basic block than the uses? E.g. the `res = 1;` inside an `if` block whose scope ends... no, that's the same.

Alternatively, what if the value is set in the function's ENTRY block and the uses are in exit blocks — same thing.

Let me just try things empirically! The compiler is right there. Candidate experiments for item 1:

E1: `res` used twice: `res = 1; ... return res;` plus in the final path `return res & (...)`. (semantically same)
E2: `res` as u8/s16.
E3: res assigned via `res = 1;` in a nested block scope `{ s32 res = 1; ... }` (scope change).
E4: `res` declared with init at decl: `s32 res = 1;`.
E5: the const temp as separate vars per compare (tried).
E6: `res` used as an argument to a call? no calls here.
E7: `res` marked as `volatile`? no.
E8: `res` assigned in a for-loop init? no.
E9: return `res` via `return res + 0;`? folded.
E10: `res` as an array element? `s32 res[1]; res[0]=1; return res[0];` — the load would add instructions. no.

E1 is interesting: with res used in the final path, the constant propagation would substitute 1 into the final path's `res & cmp` → `1 & cmp` → folded to cmp. Hmm.

Alternative idea: make the "1" value come from the comparison of a *pointer*: e.g. `res = (s32)(p != 0)` where p is a known-nonzero pointer? gcc folds pointer comparisons to constants? `p != 0` where p = &something → gcc may fold to 1. That'd be `li $2,1`? It'd be a constant → same.

Hmm, what about `res = (s32)(u32)(ptr - ptr)`? = 0.

What about making res's set be a copy from a pseudo: `s32 res2 = 1; res = res2;` → res2 folds.

I think the fold is robust. The pin's real function is to make the value a hard reg.

Given the difficulty, maybe the WALL conclusion stands (const-fold-return). But before giving up, maybe try:
- Using the `res` variable in a way that gcc keeps it in a register: e.g. `res` is the address of something? no.

Hmm, here's one more idea: **make the returned value a variable that gcc's global-alloc gives $2 because it's the FIRST global allocated**. Global-alloc assigns hard regs by priority; the RESULT_DECL has "prefers v0" → $2. The const temp might get $3 anyway if the RESULT_DECL is alive across it (in the target, the RESULT_DECL's live range is short: from the copy to the end; but the const temp is live in the middle). Hmm, in the target, $2 is occupied by res (the early set) across the whole compare chain, and the RESULT_DECL ($2) is live only at the end. So $2's occupancy comes from res.

OK. Alternatively: maybe the trick is that the value 1 should NOT be a separate variable at all — what if the four returns return the constant 1 directly, and the ROM's early `li v0,1` is actually the RESULT_DECL set done early by jump threading?

Let's test empirically: write candidate `if (arg2 == 9) return 1; ...` (vH_lit1 exists) → score? It was tried: all 17/18.

Alright, let me consider the possibility that the target comes from a DIFFERENT source shape where the value 1 is in $2 because of the way the ROM's final comparison is computed. Hmm.

Actually — WAIT. Let me reconsider the mine diff once more. Mine[21] = `move v0,zero` and mine[22] = `li v0,9`. The `move v0,zero` at mine[21]! Why would there be a `move v0,zero` right after `bnez v0, epilogue`? Because in the lever-free candidate, the code sets v0=0 somewhere (maybe `return 0` path: the `move v0,zero` is the RESULT_DECL=0 for the `return 0` path) — hmm, but that's at the end. Actually mine[21] `move v0,zero` is the "return 0" set hoisted?? Interesting: in mine the `move v0,zero` (result = 0) is at ins 21 right after the branch — that's the fall-through path of `bnez v0` (the `return 0` at the end of the function, i.e. `if (...) {...} return 0;`). Wait no: the structure is `if ((*(s16*)(arg1+0xAE) & arg3) == 0) { ... }` then after the block `return 0`. The `bnez v0, epilogue` at ins 20 jumps to the epilogue when the mask is nonzero (the `return 0` path). So the fall-through (mask == 0) enters the four compares. And `move v0,zero` at mine[21]?? That would be the `return 0` value set — but that's on the branch path, not the fall-through.

Hmm, unless the compiler duplicated it. Whatever.

Note the target has NO `move v0,zero` in that region: the target's ins 20 is `bnez v0, +0x90` where +0x90 = ins 35 which is presumably `move v0,zero` — i.e. the target puts the `return 0` set at the jump target (a separate block), while mine puts it... hmm, mine[21] `move v0,zero` right after the branch — that would be executed on the fall-through path, which is wrong semantically!

Unless mine's ins 21 `move v0,zero` is the RESULT_DECL=0 for the final `return 0` — but it's placed before the compares, on the fall-through path... that would be a compiler bug. More likely: gcc placed the "return 0" set in the fall-through because the block layout is: [test]; bnez -> epilogue-with-0; fallthrough: move v0,zero?? no...

Hmm, I bet mine's structure is: `bnez v0, +0x9c` (epilogue: jr ra) — and the `move v0,zero` at ins 21 is on the fall-through path, i.e. the "return 0" path is the fall-through?! But the fall-through enters the four compares...

Hmm, wait. Maybe the four compares come AFTER and the `return 0` at the end of the function is at the very end (ins 37-40: the final comparison and `j +0x9c`).

Let me not over-analyze; better to see the actual target listing. I really want it.

Idea for getting the target listing: `tools/delever_search.py --try` prints the diff; but if my candidate's instruction count is very different (e.g. 20 ins), the diff would cover most of the target. E.g. write a trivial candidate `s32 func_8014C308(...) { return 0; }` → the diff will show mine[0:2] vs target[0:38] — the diff prints each target instruction in the replaced region! That gives me the target listing.

Let me do that: write a stub body and score it, capturing the full output. The output prints lines "mine[i] | target" for the replaced region — the target side is shown as the mnemonic column. Let me try.

That's a great trick. Let me do it for each item: write a stub candidate `t0_stub.c` returning 0, score it, and read the target listing from the diff.

The diff output format: for each opcode, it prints the aligned instructions: `mine[i] mnem | target_mnem`. In the "replace" region of unequal lengths, it prints max(len) lines with "--" for missing. So yes, I get the full target listing.

Let me do that now for item 1.

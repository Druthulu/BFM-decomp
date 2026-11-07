---
ts: 2026-11-06T12:23:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8nv1dB5FJypeSzTIXYVo
---
Excellent! b2 (launder+pins+barriers, no keepalive) is only 3 mismatches: `addiu t4,t4,±2` vs `addiu v0,t4,±2`, and `sh t4,2(v1)` vs `sh v0,2(v1)`.

So the difference: `var_v0_3 = pos + 2` is computed into t4 (pos's own reg) in mine, vs v0 in target. In target, var_v0_3 is a separate temp v0. In mine, gcc coalesced var_v0_3 with pos (var_v0_3 = pos + 2, then pos dies → reuse pos's reg).

Why does target keep them separate? Because pos is kept alive by the keepalive! The keepalive makes pos live to the end, so var_v0_3 can't reuse t4 → gets v0.

So I need a real C reason for pos to stay live past the store, or another way to prevent coalescing var_v0_3 with pos.

Hmm — but wait, the keepalive is removed here and the score is 3; the target's var_v0_3 is in v0. If pos were live after, gcc would give var_v0_3 a different reg. Real C: use `pos` after the store in a way that has no effect... that's a keepalive by another name. The brief says a keepalive macro/asm is forbidden; a real use must be semantically meaningful.

What real C could use pos after? The function returns 1 at the end. Nothing else uses pos.

Alternative: prevent the coalescing by making var_v0_3 not a simple copy of pos's value... In target, var_v0_3 is `addiu v0,t4,±2` — it's computed from t4 into v0. For gcc to do that, var_v0_3 must not be able to share pos's register.

Alternatively, make pos and var_v0_3 different pseudos that conflict: e.g., compute var_v0_3 before pos dies in another way.

What if we write `b4b[1] = pos + 2;` directly (no var_v0_3 variable)? Then the store `sh` would take pos+2 computed into a temp; gcc might compute `addiu t4,t4,2; sh t4,2(v1)` (modifying pos) — same.

What if the source uses pos AFTER the store in a real way? For instance, return `pos` instead of 1? No, return value must be 1 (target: li v0,1 at d58).

Hmm, what about using pos in the tail computations: the tail computes D_80126720/22/24 from arg0's fields. No pos.

Could we make pos's last use be after the store in a way that's dead but not deletable? A dead use would be a "keepalive" (fake). The brief: "identity-statement launders do NOT count as a crack" and no new levers. A dead use of pos is a keepalive — a row kind that must be gone. So no.

So we need var_v0_3 in v0 by allocation priority, not by liveness. The REG-caller diff is about which caller-saved reg. var_v0_3 could be allocated v0 because v0 is free at that point (it is, after the branch?). In mine it reused t4. local-alloc's copy preference: `addiu t4,t4,2` reuses the source register (a tie), which is preferred.

Hmm, what if var_v0_3 is used differently: in target, `addiu v0,t4,2` is in the delay slot of the j (branch), and `sh v0,2(v1)`. The `addiu` at cf8 is the delay slot of `j d14`. In mine, `addiu t4,t4,2` at the same place.

So the only issue is the destination register. gcc's local-alloc ties the `addiu` result to its input if the input dies (pos dies after). Target has pos live (keepalive) → separate reg.

Real C alternative: make pos NOT die there. What if pos is used to compute something later that's part of the real output? E.g., the tail D_80126720 computation could use pos? No, changes values.

Hmm, what if we reorder: compute `b4b[1] = var_v0_3` where var_v0_3 was computed EARLIER (before the D_801152AA store) and pos is used in between? No.

What if pos is used twice: `var_v0_3 = pos + 2;` and also `var_v0_3 = pos - 2` in the other arm — those are the two arms, each uses pos once.

Wait, actually pos is used in both arms: `pos + 2` and `pos - 2`. Only one executes. In target, both use t4.

Hmm, what if the source computes something with pos in both arms and then uses pos again after the if — like `b4b[1] = var_v0_3` and then... no.

Alternatively: make var_v0_3 a s16? It's already s16. `var_v0_3 = pos + 2;` with var_v0_3 s16 → the addiu result is truncated? The target shows addiu (no truncation) because the store sh truncates. Fine.

What if var_v0_3's type is s32? Target: `addiu v0,t4,2; sh v0,2(v1)`. With s16, gcc emits addiu then sh (no sll/sra since the store truncates). Same.

Hmm, what if we can make pos live past by using it in the tail in a semantically-neutral but REAL way? E.g., `D_80126724 = ... + (pos - pos)`? That's an identity statement launder — explicitly not a crack.

OK, what about making var_v0_3 and pos conflict via a different path: if the value stored is `b4b[1] = var_v0_3` and var_v0_3 is used in BOTH arms (assigned in both) — it is. 

Let me think about gcc local-alloc: for `set (reg var_v0_3) (plus (reg pos) 2)`, the tie is preferred (var_v0_3 gets pos's reg if pos dies at this insn). pos's last use IS this insn in both arms. So tie → t4.

To prevent the tie, we need pos to be live after. Real C: use pos after the store. Is there any real computation needing pos? The original code returns 1 and computes globals from arg0. What if the `D_801152AA` store used pos? No.

Hmm, hold on — maybe there's another way: prevent the tie by making the `addiu` NOT the last use of pos: e.g., compute `var_v0_3 = pos + 2` in the arm, but ALSO reference pos in the other arm's computation of something... they're exclusive.

What if we restructure to a single expression after the if:
```
if (a1s & 1) { b4b = ...; D_801152AA = 0xFFF; var_v0_3 = 2; }
else { ...; var_v0_3 = -2; }
b4b[1] = pos + var_v0_3;
```
Then pos's use is at the final add, and pos dies there; the add's result is stored directly. Target: addiu v0,t4,2 then sh v0 — with var_v0_3 as a constant ±2, `pos + var_v0_3` would be addiu. The tie: `pos + 2` result could tie to pos. Same issue.

What if we use pos in the address computation... no.

OK, alternative: make pos's live range longer by making the D_801152AA store depend on pos? Not allowed.

Hmm, let me reconsider: maybe the answer is a different placement — the target's var_v0_3 in v0 could be because var_v0_3 is used in a different block (the store is after the join), so it's live across the join and can't tie to pos (pos dies in one arm). Wait, in target the store `sh v0,2(v1)` is at d14, the join point. The addiu is in the arm. var_v0_3 is live across the join. In mine, the addiu t4 is also in the arm and the store at the join uses t4. So same structure. The tie happened in mine because pos dies at the addiu.

Since pos must die at the addiu in real C (no keepalive), the tie is unavoidable... unless var_v0_3's assignment is placed where pos isn't dead, e.g., compute var_v0_3 = pos ± 2 BEFORE the branch (both arms computed? no).

Wait, what if we compute BOTH `pos+2` and `pos-2` before the if, then select? That'd be two addiu, target has one.

Hmm.

Alternatively: what if pos is not a variable at all, and the expression is `arg2 ± 2`? Then arg2's last use is the addiu; arg2 is a param... In target, pos = arg2 was pinned to $12 (t4) and the addiu reads t4. If we use arg2 directly, gcc would... let me test: replace `pos` with `arg2` in b2 (drop the pos pin). Actually b2 keeps `pos` pinned $12. If we drop pos and use arg2, arg2's home might be t4 anyway? Let me test: the `(s16) arg2` uses earlier read a2 directly (target: sll v0,a2,0x10). Hmm, in target, `(s16)arg2` reads a2 (the incoming), while pos (=arg2 pinned t4) is a separate pseudo! Because pos was pinned, gcc made a copy: move t4,a2, and used a2 for the s16 casts. So pos is a separate value from arg2 (same value, but the pin separated them).

So in real C: `s32 pos = arg2;` — copy propagation merges pos with arg2 (same value), so the `(s16) arg2` and `pos+2` would both read a2. But target reads t4 for pos+2 and a2 for (s16)arg2. The pin made them separate.

Hmm! So the pin is essential for the pos/arg2 split. But pins are allowed to stay (not a row kind for this item). Great, so keep the pos pin.

Then the only remaining issue is var_v0_3 tying to pos (t4) instead of v0.

Since the keepalive is the thing that prevented it... maybe another real C construct prevents it. What if var_v0_3 is assigned in a way that's not a direct tie: e.g., `var_v0_3 = pos + 2;` — tie. What about `var_v0_3 = 2 + pos;`? Same.

What if var_v0_3 is used BEFORE it's stored, e.g., in a comparison? No.

What if the store is `b4b[1] = var_v0_3;` and then var_v0_3 is used in the tail? No.

Hmm, let me look at what local-alloc does: the tie is `qty[var_v0_3].n_ties`... Actually the rule: "if the output is a register and the input dies, prefer the same register". pos dies at the addiu in both arms (since it's the last use). 

Wait — is pos's last use in each arm? pos is used in arm A (+2) and arm B (-2). Each arm has its own addiu. At the addiu in arm A, pos is NOT dead globally (it's used in arm B, a different block). But local-alloc works per basic block: within arm A's block, pos's last use is that addiu → tie. That's the tie.

In target, pos was live past (keepalive at the end) → not dead → no tie → v0.

Real C that makes pos live past the arms in the same block? No.

Could we make the addiu's result NOT tie by using a different operation? E.g., `var_v0_3 = pos + 2` where pos is s32 and var_v0_3 is s16 — maybe gcc emits `addiu` then the tie still.

What if the expression is `(s16)(pos + 2)` assigned to s16 var? Same.

What if we use `var_v0_3 = pos + 2; b4b[1] = var_v0_3;` vs `b4b[1] = pos + 2;` — the latter has no var; gcc would compute into a temp (v0?) because the store's value operand can be a register; it might compute addiu t4,t4,2 then sh t4. Let me test that.

Let me also test with var_v0_3 declared but assigned via a different type.

Actually — what about making the store happen AFTER the join with the addiu computed in the arm as target does, but var_v0_3 used in a comparison... no.

Let me just try a few variants and score. Time is a concern; but this item is close (3). Let me push a bit.

Variant c1: b2 with the pos keepalive replaced by a real use... hmm.

Variant c2: in b2, change `var_v0_3 = pos + 2;` to `b4b[1] = pos + 2;` in each arm (drop var_v0_3 and the store after).

Variant c3: make var_v0_3 an `s16` assigned `(s16)(pos + 2)`.

Variant c4: swap: compute `var_v0_3 = pos + 2;` but use pos in the D_801152AA store? no.

Let me look at b2's full source to edit. b2 = orig minus keepalive line. Let me create c2 from b2 by replacing the two var_v0_3 assignments and the store.

b2 lines:
```
    if (arg1 & 1) {
        b4b = D_801909C4;
        D_801152AA = 0xFFF;
        var_v0_3 = pos + 2;
    } else {
        b4b = D_801909C4;
        D_801152AA = -0xFFF;
        var_v0_3 = pos - 2;
    }
    b4b[1] = var_v0_3;
```
c2:
```
    if (arg1 & 1) {
        b4b = D_801909C4;
        D_801152AA = 0xFFF;
        b4b[1] = pos + 2;
    } else {
        b4b = D_801909C4;
        D_801152AA = -0xFFF;
        b4b[1] = pos - 2;
    }
```
That duplicates the store into both arms (2 stores instead of 1 + addiu in arm + join store). Target has one store at the join. Might still produce the same code after jump2/merge? Unlikely.

Better: keep the join store but compute var_v0_3 with a non-tie operation. Hmm.

What if var_v0_3 = pos + 2 is computed in the arm, but pos is ALSO used after the join in the address of the store: `b4b[1] = var_v0_3;` no.

Let me think about the target again: var_v0_3 in v0. v0 is the return register. In target, the branch arms:
arm1 (a1s&1 != 0, i.e., taken): 
```
ce4 lui v1; ce8 lw v1 (D_801909C4)
cec lui at; cf0 sh v0(4095), D_801152AA
cf4 j d14
cf8 addiu v0,t4,2
```
So var_v0_3 = v0. The li v0,4095 is at ce0 (delay of beqz) and used at cf0. Then v0 is overwritten by addiu at cf8 (delay slot of j).

arm2:
```
cfc lui v1; d00 lw v1
d04 li v0,-4095
d08 lui at; d0c sh v0
d10 addiu v0,t4,-2
d14 sh v0,2(v1)
```

In mine (b2), the addiu writes t4. So gcc tied.

Real C that avoids the tie: make pos live after the addiu within the block. In arm1, after `var_v0_3 = pos + 2`, the block ends (jump to join). pos is dead.

Unless pos is used in the join block! The join block is `b4b[1] = var_v0_3;` then the tail. If the join block used pos (e.g., `b4b[1] = var_v0_3 + pos - pos`), that's a launder.

Hmm.

What if pos is used in the JOIN block legitimately: e.g., `b4b[1] = var_v0_3;` where b4b = D_801909C4... no pos.

Could pos be used in the tail globals? D_80126720 = (arg0->unk4 + arg0->unk6) >> 1. No.

I think this item may be a WALL at score 3, keeping launder+pins+barriers (PARTIAL). But b2 still has barriers! b2 kept barriers, dropped keepalive → score 3. So PARTIAL:barrier,launder (keeps barrier+launder, drops keepalive). Hmm, but a PARTIAL should ideally keep the minimum. b1 (launder only, no barriers/keepalive) = 11. b2 (launder+barriers) = 3. b3 (launder+keepalive) = 12.

So best PARTIAL so far: PARTIAL:barrier,launder with score 3. But PARTIAL requires win.c scoring 0. It doesn't (score 3).

So currently we have no score-0 body. We need either a full MATCH or a PARTIAL that scores 0.

Let me try to get 0 by keeping keepalive? The original (all levers) scores 0 presumably. So orig.c scores 0 with all three kinds. A PARTIAL keeping all three is just orig — that's not a crack (result would be PARTIAL:barrier,keepalive,launder = the original, which is pointless but technically "scores 0 keeping only those levers"). Hmm, that's a degenerate PARTIAL. The intent of PARTIAL is to crack some of the kinds.

Given the constraint "Items that already have a results.tsv row are done" and the goal is to crack, I should try harder for a full MATCH, but the time budget is 20-30 min/item. I've used ~25 min on item 1. Let me try 3-4 more quick variants on the tail, then decide.

Variant: keep the keepalive's effect with a REAL use of pos. What real use could pos have? Hmm... `pos` = arg2, the position. What if the D_801152AA value depends on... no.

OK here's another thought: instead of preventing the tie, maybe make the addiu target v0 by having v0 preferred. In gcc 2.7.2, if the destination pseudo is used as a call argument or... no.

What if var_v0_3 is declared `s16` and assigned `pos + 2` but then stored via a different path that makes gcc sign-extend: target has no extension.

Let me try variant c3: make the store use `var_v0_3` in both arms via the join, but declare var_v0_3 as s32 (was s16). `addiu v0,t4,2; sh v0` — with s32 var and sh store, gcc emits addiu then sh. Same tie though.

Let me try the "compute var_v0_3 before the if" idea:
```
var_v0_3 = pos + 2;
if (arg1 & 1) { ... } else { var_v0_3 = pos - 2; }
```
No.

Try: make both arms compute and store, i.e., move the store into each arm, but keep a single store? No.

Alternatively, restructure the if to a conditional expression:
```
b4b = D_801909C4;
D_801152AA = (arg1 & 1) ? 0xFFF : -0xFFF;
b4b[1] = pos + ((arg1 & 1) ? 2 : -2);
```
That changes the code shape a lot.

Let me try a different trick: make var_v0_3's birth later than pos's death by computing `pos + 2` where pos is read through a variable that stays live... 

Actually, what about making pos live past the arms by using it in the SECOND arm as well? It already is used in both arms. local-alloc per-block: in arm1, pos dies; in arm2, pos dies. No.

What if the two arms are merged (not separate blocks)? E.g., use a computed delta:
```
var_v0_3 = pos + ((arg1 & 1) ? 2 : -2);
```
gcc would emit a branch anyway.

Hmm, let me try one more thing: the keepalive could be replaced by using pos in the RETURN value: `return pos ? 1 : 1;`? That's a fake. `return 1 + (pos - pos)`? identity launder.

What about `return (pos, 1);`? comma operator with pos — dead use, fake.

OK, alternative: maybe a MATCH is achievable with a completely different top shape. Recall b2 still has the launder and pins. The item's kinds are barrier,keepalive,launder — pins may stay. So a MATCH requires removing launder+barriers+keepalive. b1 (launder only) = 11. Removing the launder entirely gives the 21-score candidates. So the launder is worth a lot.

Can we replace the launder with a real second set? The launder creates a1v = arg1 in a1 while arg1 lives in t3. We tried `a1v = arg1 & 1` and `arg1 &= 1` — both merged differently.

Hmm, what about `a1v = arg1 & 0xFFFF` with the first test `if (!(a1v & 1))`? That's a real computation (andi). But target has `andi a1,a1,1` — with a1v = arg1&0xFFFF, the test would be `andi v0,a1v,1` or combined `andi a1,a1,0xFFFF` then `andi v0,a1,1`? gcc's combine might fold `(arg1 & 0xFFFF) & 1` into `arg1 & 1`! Yes! combine/simplify would turn `(x & 0xFFFF) & 1` into `x & 1`. Then a1v's value... if a1v is only used in that test, it disappears entirely and we're back to the plain shape.

Unless a1v is used elsewhere too.

What if the launder is replaced by a real second set that the later code uses: e.g., a1v = arg1 & 0x8001? Hmm.

Let me revisit: the fundamental need is TWO live values: arg1's copy in t3 (later tests) and a1v in a1 (first test). Both derive from arg1. Real C: two variables from one param, both live, one of which is arg1&1 (computed in place) and the other is arg1.

`a1s = arg1` merges (same value). `a1v = arg1 & 1` doesn't merge with arg1, but then arg1 stays live and a1v goes to v0.

The launder's trick: a1v is a NEW value (opaque) that gcc believes is unrelated to arg1, yet it's used only for `&1`. So gcc must keep arg1 AND a1v.

Real C: a1v must be a value not provably equal to arg1 but with the same low bit. E.g., a1v = (arg1 << 16) | 1? That changes bits.

Wait: `a1v = arg1 & 1` gives exactly bit 0. gcc computes it. The issue is the register (v0 vs a1) and the missing t3 copy. With `a1v = arg1 & 1`:
- gcc sees arg1 live (later uses), a1v born at the andi. The andi can write a1 if arg1's pseudo dies there — it doesn't. So andi → v0. Then arg1 stays in a1... but the observed code had arg1 in t4 with a param move. Interesting.

What if we could make arg1's later uses read a SEPARATE copy that gcc must materialize because the copy is of a value that's "used" differently... 

IDEA: what if the later tests use `arg1` but arg1 is passed through a cast to a different type that gcc can't merge: e.g., the later tests use `(u32)arg1`? No-op.

What about `((s16 *)&arg1)[0]`? Taking the address of a param forces a stack slot — no.

What about `*(s16 *)&arg1`? Same, address taken.

Hmm.

Let me try the "real 2nd set" pattern from the catalog in reverse: they did `pv = *p; pv &= mask` (a real second set with a mask). Here the analog: `a1v = arg1 & 1` is already a real second set. The catalog's cracks kept the code shape because the mask op was part of the original target code. Our target's andi IS a real second set — the target's andi is exactly `a1v = arg1 & 1`. So maybe the source should be:

```
a1v = arg1 & 1;
if (!a1v) ...
```
and the target's `move t3,a1` should come from arg1's later uses... but gcc merges.

Unless the later uses are of a variable assigned from arg1 with a REAL second set too. What real op on arg1 preserves bits 15 and 0 and is a move? None.

Hmm hold on — maybe the later uses don't need arg1's value at all! Look at the later tests:
```
if (arg1 & 0x8000) { b4[0] = p[0]; b4[2] = p[2]; }
...
if (arg1 & 1) { ... }
```
What if we compute `m = arg1 & 0x8001` once (a real second set) and use `m & 0x8000`, `m & 1`? Then target's t3 could be... no, target's t3 holds the full arg1 and the tests are `andi v0,t3,0x8000` and `andi v0,t3,0x1`.

The target's t3 value is arg1 (full). It's used only in those two andi tests. Since only bits 15 and 0 matter, any value with the same bits 15/0 works. So a REAL second set that preserves those bits and compiles to `move`... `arg1 & 0x8001` compiles to `andi`, not move.

But what if we use `a1s = arg1 & 1` for the last test and `a1s2 = arg1 & 0x8000` for the other? Then target would have those andi's... but target has `andi v0,t3,0x8000` where t3 is the full value. If t3 held `arg1 & 0x8001`, the andi would still be `andi v0,t3,0x8000`! Because `(x & 0x8001) & 0x8000 == x & 0x8000`. So if we write:

```
s32 a1s = arg1 & 0x8001;
if (!(arg1 & 1)) ...
...
if (a1s & 0x8000) ...
if (a1s & 1) ...
```
then gcc: a1s = andi(arg1, 0x8001) — one insn but opcode andi, whereas target has move t3,a1. Mismatch in the opcode (andi vs addu). Unless gcc recognizes `andi` with 0x8001... no, it emits andi.

Hmm, but wait: what if the mask is 0xFFFFFFFF... no.

What if a1s = arg1 & 0x8001 but gcc's combine folds the later andi's: `(arg1 & 0x8001) & 0x8000` → `arg1 & 0x8000` (using arg1 directly!). Then a1s disappears and the tests read arg1 → arg1 stays live → andi v0. Worse.

OK. I'm fairly convinced a full MATCH here is hard. But maybe there's a trick with the `(s16)` casts. Let me look at the target's first test again: `andi a1,a1,1`. The input a1 is the INCOMING param register. For that, gcc must not have moved the param. In target, the param's home is a1 and the copy t3 exists for later uses because the asm clobbers a1.

What if we make a real C that clobbers a1 before the later uses? A CALL! If we add a call... no, no calls allowed (changes code).

Alright — what about accepting PARTIAL with score 0? We need a win.c scoring 0 that keeps only some kinds. b2 scores 3. Can I get b2 to 0 by keeping the keepalive? b2 + keepalive = orig = 0 (all kinds). A PARTIAL:barrier,keepalive,launder isn't a crack.

Hmm, what about keeping only the keepalive (drop barriers+launder)? b3 (launder+keepalive, no barriers) = 12. Let me try keepalive only (no barriers, no launder): that's b1 minus launder... Actually b1 = launder+pins, no barriers/keepalive = 11. Keepalive only = orig minus barriers minus launder. Let me test that and a few combos to see if any single-kind-kept body scores 0.

Actually the meaningful PARTIAL would be "keep only the launder" if it scored 0. b1 = launder+pins (pins allowed) = 11. Not 0.

So no PARTIAL at 0 unless we keep 2 kinds. PARTIAL:barrier,launder requires 0 — b2 = 3. Close but no.

Given the 30-min budget, let me spend a few more tries on the b2 tail (score 3), since that's the closest.

Idea for the tail: make pos live past the addiu via a real use in the join block. What if the store is `b4b[1] = var_v0_3;` and then `b4b[1] = b4b[1];`? identity.

What if the tail D_80126720 computation uses `pos`? The value is (unk4+unk6)>>1. Could we write it as `((unk4 + unk6) >> 1) + (pos - pos)`? identity launder.

Hmm. What if pos is used in a REAL comparison that's part of the logic? The function's logic doesn't need it.

Alternatively, prevent the tie by making var_v0_3's assignment not a simple plus: e.g., `var_v0_3 = pos + 2 - 0`? folds.

What about `var_v0_3 = 2 + pos;`? The plus is commutative; gcc canonicalizes.

What if we use `var_v0_3 = pos + 2;` where pos is a POINTER? `(s32)((u8*)pos + 2)`? That would be addiu of the pointer, then the store truncates. gcc's pointer arithmetic on u8*: `pos_p + 2` → addiu. Then `b4b[1] = (s32)var_p;`. Hmm, the tie: pointer arithmetic addiu with the base dying — same tie.

What if the addition is done via an index: `var_v0_3 = ((s32 *)pos)[0]`? no, that's a load.

Let me try making var_v0_3 s16 and pos s16? pos is s32.

Try: declare `var_v0_3` as `s32` (not s16) and store to b4b[1] (s16 array). Target: addiu v0,t4,2; sh v0. With s32 var, same.

Try: compute the store value directly from pos in each arm but store at the join via b4b[1] = var_v0_3 where var_v0_3 is assigned `(s16)(pos + 2)`: maybe the cast forces a different pseudo? `(s16)(pos+2)` then store to s16: gcc would emit addiu then (no truncation needed for sh). Same tie.

Hmm, what about the ORDER: in target, the addiu is in the DELAY SLOT of the jump (cf8 after j cf4). In mine, `addiu t4,t4,2` is also there (insn 125 in the diff: mine addiu t4,t4,2 vs target addiu v0,t4,2). So the position matches; only the reg.

What if I add a real second use of var_v0_3 in the join block that forces it to be a different pseudo... e.g., `b4b[1] = var_v0_3;` and then `temp_v1 = b4b[0];` uses the stored value? No.

Let me think about local-alloc's tie more carefully: the tie happens when `reg_qty[REGNO(reg)]` ... the "copy" preference: in local-alloc.c, `qty_phys_copy_sugg` — a tie is suggested when the insn is a copy or when the output register can be the same as an input that dies. For a 2-address insn like addiu (dst, src, imm), if src dies, the allocator prefers dst = src. To break it, make src NOT die in the block.

So pos must be live after the addiu within the same basic block. The arm block: `b4b = D_801909C4; D_801152AA = 0xFFF; var_v0_3 = pos + 2;` then j. If we add another use of pos AFTER var_v0_3 in the same block, pos isn't dead → no tie. A real use after: is there one? The block only has those statements.

What if we reorder: `var_v0_3 = pos + 2; D_801152AA = 0xFFF;` — pos still dies at the addiu.

What if the arm ALSO uses pos in the b4b assignment: `b4b = (s16 *)(pos - pos + (s32)D_801909C4)`? launder.

Hmm.

What if the whole structure changes so that pos's last use is in the JOIN block (after the if)? E.g.:

```
if (arg1 & 1) {
    b4b = D_801909C4;
    D_801152AA = 0xFFF;
    var_v0_3 = 2;
} else {
    b4b = D_801909C4;
    D_801152AA = -0xFFF;
    var_v0_3 = -2;
}
b4b[1] = pos + var_v0_3;
```
Then pos's last use is at the join addiu; pos dies there → tie again (addiu dst could be pos's reg). Target wants v0. Hmm, same.

But wait — in this shape, `pos + var_v0_3` at the join: the result goes to the store; gcc would compute `addiu v0,t4,2`? The tie: pos dies at this insn → dst = t4. Same.

Unless... hmm.

What if pos is used in the store address: `b4b[1] = var_v0_3;` no.

I think the tie is unavoidable without extending pos's liveness, which is a keepalive. So the wall is `lreg-copy-pref-dying-base`? "local-alloc copy preference ties a dying base reg to another pseudo (G24)" — that's for a load base. Our case: the dying base pos is tied by the addiu. Hmm, the tag `lreg-qty-priority` or `lreg-copy-pref-dying-base` could fit. Actually the existing tag `lreg-copy-pref-dying-base` is about local-alloc's copy preference with a dying base. Here pos dies at the addiu and the result ties to it. I'd tag it `lreg-tie-dying-pos`? There's also `lreg-dead-hardreg-reuse`.

Wait, the moves list line 25: `keepalive | func_8017BF14 | WALL lreg-tie-dying-pin — c1 ($4 pin) dies at c1<<16; local-alloc ties sll temp to a0, target v0; mny keepalive cracked by do-while ref weight`. That's EXACTLY our situation: a dying value ties to the temp, target v0, and the keepalive was cracked by "do-while ref weight"!

So the move: replace the keepalive with a do-while(0) to add ref weight. In our case, we need pos to be "live" past the addiu so the tie doesn't happen. The keepalive's asm use made pos live. A do-while(0) adds loop_depth refs but doesn't extend liveness... Hmm, in func_8017BF14 the keepalive was on a different var (mny) and cracked by do-while ref weight — a priority trick.

Let me look at that recipe: `do-while ref weight`. C0535: do{}while(0) splits cse1 EBB and adds REG_N_REFS += loop_depth. If we wrap the tail computation in a do-while(0), it affects priorities.

In our case, the tie is local-alloc's; REG_N_REFS affects local-alloc's qty priority (the order of allocation), not the tie. Hmm, but the tie is a separate mechanism.

Wait, maybe I can make pos live past by a do-while structure: e.g.,
```
do {
    if (arg1 & 1) { ... var_v0_3 = pos + 2; }
    else { ... var_v0_3 = pos - 2; }
    b4b[1] = var_v0_3;
} while (0);
```
Inside the loop body, the if arms are still separate blocks; pos dies in each arm. No.

Hmm, but the loop note might change the EBB structure so the arms... no, the arms remain blocks.

Let me instead try: `var_v0_3 = pos + 2;` inside a do-while, then the store outside — the loop end might make pos live through the loop's back edge? No back edge (while(0) is false; gcc still emits a loop note with a fake back edge?). With do{}while(0), gcc creates a loop with one iteration; the back edge is conditional on 0 → gcc's loop analysis may treat it as a loop; liveness computed on the CFG with the back edge could make pos live at the loop end... but the back edge goes to the top, and pos isn't used at the top. Liveness would extend pos's range to the loop top if used after the loop, but it's not.

Hmm.

Let me look at C0535 to understand.

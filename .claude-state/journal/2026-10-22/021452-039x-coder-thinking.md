---
ts: 2026-10-22T08:14:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_MeKeNsvvq2QvsDTx5lpL
---
Still the copy died. So the copy and use ended up in the same block, or cse propagated.

Hmm. In c5, the copy `u = t` is in the entry block and the use `t = u - 1` is in the else block. But gcc's flow analysis might have determined that u is dead in the else... no, u is used there.

Hmm, but why did the copy die? Because gcc's `pass_jump` (jump optimization) ran before cse and merged/reordered? Or because gcc's front-end generated the blocks differently.

Hmm. Actually! Maybe the issue is that the `if (t == 0) {...} else {...}` with the else containing the use: the block structure is: entry → (t==0) → t0block; entry → (t!=0) → elseblock. The copy is in the entry block, the use in the else block. cse processes blocks in order: the entry block first. When cse sees `u = t` in the entry block, it records reg_equiv_content[u] = t. Then in the ELSE block, when it sees the use of u, does cse substitute? cse's reg_equiv_content is a global array that persists across blocks within the function! So cse would substitute u→t in the else block.

Hmm, but in my t10 test, the copy survived! Let me re-look at t10:
```c
int t10(int t) { unsigned u; u = t; if (t) { t = u - 1; } return t; }
```
→ `move v0,a0` survived. Hmm! So in that case the copy survived across a block boundary.

Difference from c5: in t10, the copy's source `t` is a PARAMETER (hard reg a0)! And cse's make_regs_eqv refuses to equate a pseudo with a HARD register! That's the rule I remembered. So the copy survived because the source was a hard reg.

In c5, the source `t` is a pseudo (the loaded value) → cse propagated it.

Hmm! But wait, in t10 the copy `move v0,a0` was in v0 (the same reg as a0? no: `move v0,a0` = `or v0,a0,$zero` — a copy from a0 to v0). Then `beqz v0` and `addiu v0,v0,-1`. So u got v0 and t (the param) stayed in a0. Interesting.

OK so the hard-reg rule is real: a copy from a hard register survives cse.

Now, in the target 80182ED4, the copy's source is the loaded value (a pseudo). So how did the target's copy survive cse? Because the RHS was `(plus t (reg 0))` → not a reg copy → cse's make_regs_eqv doesn't apply (it only handles reg-reg copies). ✓ Consistent.

So: to keep the copy, the RHS must not be a reg-reg copy at cse time.

Back to that. Hmm.

BUT WAIT!!! Now I have a new idea: what if the copy's SOURCE is a HARD REGISTER at cse time? The hard regs at cse time: the parameters (a0) and... the loaded value is a pseudo.

Hmm, what if the copy's source is a CALL RESULT? At cse time, a call's result is in v0 — but gcc represents it as a pseudo assigned from the call insn. Hmm, but the RTL of a call is `(set (reg ret) (call ...))` — and cse's make_regs_eqv for a call result... The G02-style: after the call, the result is in a pseudo. A copy from it → cse propagates.

Hmm.

What about a copy from a hard register that the compiler itself put there? Like after a call, `v0` holds the result. If the C is `u = f();` then u is the call result directly.

Hmm.

OK, so what other RTL forms are "not a reg copy" but fold to a plain copy?

Let me revisit the LIST of possible RHS forms at cse time:
1. `(reg t)` — plain copy → cse propagates ✗
2. `(plus t (reg 0))` — pin ✗
3. `(zero_extend:HI t)` → andi (or a copy if combine can prove the high bits) ✗
4. `(sign_extend:HI t)` → sll/sra ✗
5. `(mem ...)` → a load ✗
6. `(const)` ✗
7. `(plus t (const 0))` → tree-folded before RTL ✗
8. `(and t (const 0xffffffff))` → folded ✗
9. `(mult t 1)` → folded ✗
10. `(if_then_else ...)` → a branch ✗
11. `(float:SI t)` → FPU ✗
12. `(sign_extend:SI t)` where t is a QImode reg → hmm! This is the "convert QImode to SImode" case. If the conversion is FREE in gcc (because the reg's high bits are already correct), the RTL might be `(set u (reg t))` → a plain copy ✗. But if gcc emits `(sign_extend:SI (reg t))` and combine can't fold it → sll/sra ✗.

Hmm.

13. **`(set u (reg t))` where the copy is in a block where t is a HARD register** — the hard-reg rule.

So the ONLY way is #2 (the pin) or #3/#4 with a known-range source.

Hmm, hold on! What about #13 in a different form: **what if the copy's source is a parameter?** In 80182ED4, the only parameter is arg0. But hmm... what if we could make the LOADED value flow through a parameter? No.

Hmm, BUT: what about the SECOND function argument? In the else arm there's no call.

Hmm hmm.

OK WAIT. Let me reconsider the target. Maybe the `or v1,v0` ISN'T `u = t`!

What if the target's source is:
```
} else {
    u = t + zr;
    t = u - 1;
}
```
but with `u` being... hmm, what if `u` is not a variable but a **function argument**? No.

Hmm, hold on! What if the copy `or v1,v0` is the result of `t = u - 1` where `u` is a variable that was assigned EARLIER (before the branch) from a hard register?!

In the target, v0 = the lh result. Hmm.

What if the ORIGINAL (unpinned) source had `u` assigned from the field BEFORE the if? Like:
```
u = ((Unkstruct_80182ED4 *)arg0)->unk84;    /* lh */
if (u == 0) { ...; t = 0x1E; }
else { t = u - 1; }
```
→ `lh v0` ; `beqz v0` ; ... ; `addiu v0,v0,-1`. No copy.

Hmm.

OK OK OK. Let me look at this from yet another angle: **what if the copy's RHS is a plus with a hard register that is NOT zero, and the target's `or v1,v0` is actually `addu v1,v0,$zero`**... no, the bytes say `or`.

Hmm, hold on! Let me reconsider: maybe gcc's mips "move" pattern is `(set (reg) (reg))` → `or rd,rs,$zero` AND ALSO gcc generates `(plus x (reg 0))` for a copy in some cases (like `emit_move_insn` with a "move" pattern).

**IDEA**: what if the copy is generated by gcc's **reload** (a reload from the stack)? `lw v1, off(sp)` ✗.

**IDEA**: What if the copy is a **`memset`/`memcpy`** ✗.

**IDEA**: What if the copy is the **`(set (reg) (reg))` after a call-clobber**? no.

Let me try yet another approach: **let me look at how the sibling item in another shard (func_8017FBCC, WH1) was handled** — it had the same structure ("combine-copy-merge — combine folds then-block copy v1=v0 into v0=v1-1; pre-test copy: cse canonical v1 rewrites the test; only v0+$0 keeps it"). So WH1 concluded: only v0+$0 keeps it. That's the same conclusion.

Hmm, but WH1's item is "pre-test copy" (the copy before the test) vs ours "then-block copy".

Hmm, "combine folds then-block copy v1=v0 into v0=v1-1" — so in their case the copy was in the THEN block (like ours) and combine folded it.

OK so both other shards hit the same wall. It's likely a genuine wall for this pattern.

**BUT**: my brief says these items were walled before with too few tries, and asks for new moves. Let me consider the PARTIAL option? No.

Let me think about the "hard register" rule once more, since it's the only thing that saved t10.

**!!!!! BIG IDEA !!!!!**: What if the copy's source is a hard register because the value was just loaded into a hard register by a **`volatile` load**? Hmm, no — a volatile load's result is still a pseudo.

**!!!!! BIGGER IDEA !!!!!**: What if the copy's source is the result of a **function call** — the result is in v0 (a HARD register) right after the call! In gcc's RTL after expand, a call is `(set (reg pseudo) (call ...))` — hmm, but actually gcc 2.7 models calls as `(call (reg f) (args))` with the result in a pseudo assigned via a SET. Hmm, in older gcc the call's return value was in the pseudo directly (the call insn's output). cse's make_regs_eqv on a call result: gcc's cse has special handling for calls.

Hmm, in our target there's no call in the else path.

Hmm, what if we introduce a call? The target's else arm has no call, so adding one changes the asm. ✗

OK. So the copy's source must be a pseudo. ✗

**FINAL IDEA**: What if the copy is not `u = t` but `u = t` where the copy is written as a **conditional expression**:
```
u = t ? t : 0;
```
→ gcc generates a branch or a "move" sequence. Hmm, gcc 2.7 might generate `(set u (cond (reg t) (reg t) (const 0)))` → the mips backend would emit a branch. ✗

**FINAL IDEA 2**: `u = t` where u is declared with a DIFFERENT but same-size type that gcc converts with a no-op RTL that isn't a plain copy. E.g., u is `unsigned` and t is `int` → gcc's convert_to_mode(SImode, int) → the same mode → plain copy ✗.

**FINAL IDEA 3**: What about `u = t` where t is `int` and u is `unsigned long`? Different sizes → the value would be converted... on 32-bit, long is 32-bit → same ✗.

OK. Let me now consider the possibility of a different overall SHAPE that produces the target's asm without a copy.

Target:
```
lh v0,132(s0)
bnez v0,8134
<delay slot> move v1,v0
...
8134: addiu v0,v1,-1
8138: sh v0,132(s0)
```

What if the `or v1,v0` is the target of a **"move" that gcc emits for a copy in a different context**, e.g. the copy of a value into a callee-saved register? no.

Hmm, what if the `or v1,v0` is the result of the `addiu` being computed differently...

What if the C is:
```
} else {
    u = t;
    t = u - 1;
}
```
where `u` is declared as `s32` but the copy is `u = t` where **t is `unsigned` and u is `int`** — same ✗.

Hmm, what if the copy is `u = t` and the SUBTRACTION is `t = u - 1` where 1 is a `char`? ✗

Hmm, hold on. Let me revisit the "hard register" rule and check WHICH side matters:
```c
  if (regno >= FIRST_PSEUDO_REGISTER && orig_regno < FIRST_PSEUDO_REGISTER)
    return 0;
```
This says: if the DEST (regno) is a pseudo and the SOURCE (orig_regno) is a hard reg → don't equate. So a copy FROM a hard reg is not propagated. ✓ (t10 confirmed).

What if the copy is TO a hard reg? Then `regno < FIRST_PSEUDO_REGISTER` → the condition is false → it proceeds → equated. So no.

So: the source must be a hard register.

**In 80182ED4, is there any hard register holding unk84 at that point?** The hard regs at cse time: a0-a3 (args), v0-v1 (return values), and... the loaded value is in a pseudo.

Hmm, BUT: what if the value is loaded via a **`volatile` load into a hard reg**? No.

Hmm, what if the value comes from a **function call**? Not in the else path.

Hmm, what if the value comes from a **parameter**? The parameters are arg0 (the struct pointer).

WAIT!!! What if we could get the value unk84 into a0 through a **call**?! Like, what if the else arm calls a function that returns unk84? There's no such function.

Hmm, but hold on: what if we call `func_80133784`? No.

OK — completely different: **what if the `or v1,v0` in the target is NOT a copy of unk84 but the copy of the RESULT of something in the if-branch?** No: v0 at 80d8 = the lh result.

Alright. Let me consider the possibility of the **`-` hard register trick**: `(plus t (reg 0))` — what if the C is `u = t + zr` where `zr` is a variable that gcc's RTL gives as `(reg 0)`...

Hmm, in gcc, is there any C construct that yields a hard register ZERO operand in a plus?

**`t % 1`?** → 0. **`t / 1`?** → t. **`t & ~0`?** folded.

**A `switch` with only one case?** gcc might generate `beqz` comparisons with consts.

**`t ? t : t`** → folded.

**`sizeof`** → const.

Hmm, what about **`t + (0 ? 1 : 0)`** → folded to t+0 → folded.

What about **`t + '\0'`** → const 0 → folded.

What about a **bitfield**? no.

What about `t + (int)(char)0`? folded.

Hmm, what about a **`volatile const s32 z = 0;`**? → a load ✗.

OK, I'm fairly convinced 80182ED4's `or v1,v0` requires the pin.

BUT WAIT — one more: what if the copy's SOURCE is a hard register because the value is a **constant that gcc puts in a hard reg**? no.

Hmm, hmm. What about the SECOND `lh`? no.

**LET ME RECONSIDER THE PROBLEM**: maybe the score-6 diff isn't only about the copy. Let me look at the whole picture: the target is 42 ins, mine 40. The only differences are the copy (`move v1,v0` vs nothing) and the addiu's source.

Hmm, so we need exactly the copy.

**NEW THOUGHT**: what if the copy's source is a hard register because it's the result of a **compare**? E.g., `(set (reg) (eq ...))` → a 0/1 value. Not our value.

**NEW THOUGHT 2**: What if we make `t` itself come from a hard register by declaring it as a **parameter of an inner block**? no.

**NEW THOUGHT 3**: What if we use `__builtin`? no.

**NEW THOUGHT 4 — THE BIG ONE**: What if we split the copy into TWO copies, one of which is from a hard register? E.g.:

```
u = t;      /* pseudo source → cse propagates */
```
Hmm.

**NEW THOUGHT 5**: What if we use the fact that cse runs per basic block, and make the copy's SOURCE a pseudo that's live in a DIFFERENT block where it's a hard reg? no.

**NEW THOUGHT 6**: What if the copy is `u = t` where `t` is a pseudo that cse has ALREADY been forced to keep because of the "reg_equiv_content" chain?

Hmm, here's a thought: cse's make_regs_eqv has this logic (gcc 2.7 cse.c, I'm now fairly sure):

```c
      /* If we are setting a reg to a reg, and the reg is dead after
	 this insn, ... */
      ...
      /* If the source reg is a pseudo that is not live, and the dest
	 is live, we may want to reverse the copy: set the source to the
	 dest instead.  */
```
Hmm! "reverse the copy": if the source is dead and the dest is live, gcc can rewrite the source's definition to the dest instead — keeping the copy!

In our case: `u = t;` — after the copy, t is dead (t is redefined at the addiu... hmm, but the addiu reads u, not t). Actually after `u = t`, t is dead (its next definition is the addiu's destination). And u is live (used by the addiu). So "the source is dead and the dest is live" → gcc could reverse the copy → the copy survives!

But empirically the copy died. So cse didn't reverse it. Hmm. Maybe the rule requires the source to have no uses after (t has none) AND the dest to be used more than once?

Hmm, in the G02 wall note: "iVar1 outlives t -> canonical; cmp/store of t rewritten to iVar1" — that's the reverse-copy case! iVar1 (the dest) outlives t (the source) → iVar1 becomes canonical → t's uses are rewritten to iVar1 → the COPY SURVIVES as `iVar1 = t`?? Hmm, "cmp/store of t rewritten to iVar1 (s-reg)" — so t's uses read iVar1, and iVar1 = t (the copy) stays. And then "target keeps t in v0" — i.e. the target has t in v0 and iVar1 elsewhere. So in that wall case, the copy survived but in the WRONG registers.

So the reverse-copy case DOES happen. In our case, u (dest) outlives t (src) → u should become canonical → the copy survives! But it didn't.

Difference: in the G02 case, t had USES after the copy (cmp/store of t) which got rewritten to iVar1. In our case, t has NO uses after the copy. So the "rewrite t's uses" doesn't apply, and cse just propagates u→t (since t's value is available at u's use).

Hmm, so: if t HAD a use after the copy, the reverse-copy would happen and the copy would survive!

**IDEA**: What if we give `t` a use after the copy that is harmless? Like:
```
u = t;
t = u - 1;
```
t's uses after the copy: the addiu's DESTINATION (not a use). Hmm.

What if:
```
u = t;
w = t;         /* hmm */
```

Hmm, what if the structure is:
```
} else {
    u = t;
    t = u - 1;
}
```
What if we add a use of t after the copy:
```
} else {
    u = t;
    t = u - 1;
    /* t used later: unk84 = t */
}
```
`unk84 = t` IS a use of t after the copy! But it's after the addiu redefines t. Hmm, the addiu kills t's old value.

So: what if the copy's SOURCE has a use after the copy that reads the OLD value? Like:
```
} else {
    u = t;
    t = u - 1;
}
```
The old t's value is used by... nothing.

What if we restructure:
```
} else {
    u = t;      /* copy */
    v = t;      /* another use of t (old value) */
    t = u - 1;
}
```
Hmm, `v = t` is another copy → also cse'd... and v is unused → DCE removes it. But at cse time, v = t is a copy → and t has uses after (v's copy and u's use) → hmm.

Hmm, this is getting silly. But hold on — the G02 note says the reverse-copy happened and the result was "cmp/store of t rewritten to iVar1 (s-reg); target keeps t in v0" → the wall was about the REGISTERS, not the copy's existence. So the copy survived there.

In our case, if we add a use of t after the copy, cse might make u canonical and rewrite t's uses to u → the copy survives → but then the register allocation might differ (u in a callee-saved reg, etc.).

Hmm, what use of t could we add that's harmless AND doesn't add instructions?

The natural one: the STORE `unk84 = t`! But that stores the NEW t.

Hmm, what if we restructure so that t's old value is stored somewhere... no.

What if:
```
} else {
    u = t;
    t = u - 1;
}
```
becomes
```
} else {
    u = t;
    t = u - 1;
    t = t;      /* identity — a launder! forbidden */
}
```
✗ (identity launder).

Hmm. What about the natural C: what if `t` is used in the STORE and the copy is of the FINAL value?

```
} else {
    t = u - 1;   /* u = t before */
}
```

Hmm.

Let me think about the G02 case concretely: "cse make_regs_eqv (cse.c:840): iVar1 outlives t -> canonical; cmp/store of t rewritten to iVar1 (s-reg); target keeps t in v0". So they had code like:
```
t = <something>;
iVar1 = t;        /* the copy */
... uses of t (cmp/store) ...
```
and cse rewrote the cmp/store of t to read iVar1, and the copy `iVar1 = t` stayed. Then iVar1 got an s-reg (callee-saved) while the target wanted t in v0. So the copy survived!

So the reverse-copy happens when the SOURCE has uses after the copy. In our case, t's old value has no uses after the copy.

**So: give t's old value a use after the copy.** Where? In the else arm, after `u = t`:
```
u = t;
t = u - 1;
```
What if instead:
```
u = t;
t = u - 1;
```
Hmm.

What if the else arm is:
```
u = t;
w = t;      /* use of the old t */
t = u - 1;
```
and w is used later? Extra insn ✗.

Hmm, what if the use of t after the copy is the COMPARISON in the branch? Like:

```
t = unk84;
if (t != 0) {
    u = t;       /* the copy is INSIDE the then-block */
    t = u - 1;
}
```
Here, the use of t (the branch test) is BEFORE the copy. Hmm.

What about:
```
t = unk84;
if (t == 0) { ...; t = 0x1E; }
else {
    u = t;
    t = u - 1;
}
```
The test is before the copy.

Hmm, so the test use is before. What if we restructure so the copy comes FIRST and the test after?
```
t = unk84;
u = t;         /* copy */
if (u == 0) { ...; t = 0x1E; }   /* the test uses u */
else { t = u - 1; }
```
Now: the copy `u = t`; then u is used in the test and in the else arm. t's uses after the copy: NONE (t is redefined in the if-branch as 0x1E and in the else as u-1). Hmm, still no use of t's old value.

Hmm. cse's rule might be about the DEST outliving the SRC.

Hmm, let me look at the actual gcc 2.7 cse.c code. I'm now motivated to find it. Maybe I can find gcc 2.7.2's source online knowledge... Let me recall the code of make_regs_eqv in gcc 2.7.2:

```c
static int
make_regs_eqv (reg, orig_reg, insn)
     int reg, orig_reg;
     rtx insn;
{
  int regno = reg;
  int orig_regno = orig_reg;
  rtx copy;
  HOST_WIDE_INT temp1;
  int temp2;
  rtx x;
  rtx y;
  int insn_code;
  int opt_for_cc;
  int equiv;

  /* Don't attempt to equate the two registers if one is a
     hard register and the other is not.  */

  if (regno >= FIRST_PSEUDO_REGISTER && orig_regno < FIRST_PSEUDO_REGISTER)
    return 0;

  /* If we are setting a register to a register and the register is
     not dead, and the source register is dead, then we can
     substitute the source for the destination.  */

  ...
```

Hmm, I recall there IS a block like:

```c
      /* If this is a copy of a pseudo-reg, and the pseudo-reg is
	 not live, we can delete the copy and change the pseudo-reg's
	 definition.  */
```

and

```c
  /* If the source is a pseudo-reg that is dead, and the destination
     is live, we may want to substitute the destination for the
     source in the source's definition.  */
```

This is the "reverse copy" that the G02 note mentions.

OK — PRACTICAL PLAN: let me test empirically in my harness whether adding a use of the source's old value after the copy keeps the copy. Test cases:

```c
int q1(int t) { unsigned u; u = t; t = u - 1; return t; }            /* known: dies */
int q2(int t) { unsigned u; u = t; if (t) { t = u - 1; } return t; }  /* known: survives (hard reg src) */
int q3(int t) { unsigned u, v; u = t; v = t; t = u - 1; return t + v; }
int q4(int t) { unsigned u; u = t; t = u - 1; if (t) return t; return 0; }
```
Hmm q4: after the copy, t is redefined. no.

Let me test the case where the source has a use after the copy:
```c
int q5(int t) { unsigned u; u = t; t = u - 1; return t + u; }   /* u used after */
```
Hmm, u is used after → u's live range extends → u outlives t → maybe the reverse-copy applies! Let me test q5. In our function, could we use u after? The else arm is the last thing before the store. Hmm: `unk84 = t` — we could write `unk84 = t` and also use u? No.

Hmm, but WAIT: in the target, is u used after the addiu? No (v1 is dead after 8134). So u does NOT outlive t in the target. So the reverse-copy rule (dest outlives src) doesn't apply to the target either!

So in the target, the copy survived NOT because of the reverse-copy but because the RHS was `(plus t (reg 0))`.

Hmm. OK.

So what if the copy's source is used after the copy in OUR version, making the reverse-copy fire? Then the copy survives but the asm differs (the extra use).

Hmm.

Let me try yet another thing: maybe the copy survives if the source's live range ends right at the copy (dead after) AND the dest is used once. That's our case → dies.

OK, let me try to settle this by finding the actual cse.c. Let me check if pip/gcc source is available offline... no network probably. Let me check if the project has a copy of the gcc 2.7.2 source somewhere (maybe in .run/ or a submodule).

Let me search the project for cse.c.

Actually, hold on! Let me revisit the HARD-REG idea once more, because t10 showed it works.

**In the target, the copy's source is the lh result (a pseudo).** BUT what if in OUR version, we make the lh result go into a hard register by...

**!!!! IDEA !!!!**: What if the copy's source is a hard register because the value was just produced by a **`jal` whose result we use**? The call result in gcc 2.7: after expand, the call is `(call (reg f) args)` and the result is assigned to a pseudo via a separate SET insn: `(set (reg pseudo) (call ...))`. Hmm, actually gcc 2.7 emits the call with the destination being the pseudo: `(set (reg D.0) (call ...))`. So the result IS in a pseudo. Then cse's make_regs_eqv on a call result: gcc's cse has special handling — in cse.c, `case CALL_INSN: ... reg_equiv_content[regno] = 0` etc.

Hmm. But in gcc 2.7, the CALL_INSN's output is a pseudo, and the "hard reg" rule doesn't apply.

Hmm, but hold on: in gcc 2.7, the call's result pseudo is assigned from the call insn, and cse treats it as "reg_equiv_content[regno] = 0" (unknown). Then a subsequent copy `u = callresult` → cse's make_regs_eqv(u, callresult) → both pseudos → equated → propagated. ✗

OK.

Let me now consider: maybe I should look at how OTHER shards cracked a "copy must survive" case with a *different* mechanism. Let me grep moves.md for "copy" to find successful copy-preservation moves.

Let me grep moves.md for "copy".

That's cheap and might reveal the trick. Let me do it.

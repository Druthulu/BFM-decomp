---
ts: 2026-10-22T01:01:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_vvlZLgRK17UBX8uMJWFD
---
Now I have the target's full listing. Let me note the key region (the vol computation):

```
	sra	$6,$2,16            ; ax = (s16)x
	bgez	$6,$L58
	move	$5,$6
	subu	$5,$0,$6
$L58:
	li	$4,0x66660000        ; magic M
	ori	$4,$4,0x6667
	li	$2,0x000000a0        ; 160
	subu	$2,$2,$5            ; 160 - |x|
	sll	$3,$2,7             ; (160-|x|)*128
	subu	$3,$3,$2           ; (160-|x|)*127
	mult	$3,$4              ; * M
	mfhi	$9
	#nop
	addu	$2,$6,160          ; |x| + 160
	mult	$2,$4              ; * M
	sra	$3,$3,31
	sra	$4,$9,6
	subu	$5,$4,$3
	sra	$2,$2,31
	mfhi	$6
	#nop
	#nop
	sra	$3,$6,3
	subu	$6,$3,$2
	li	$2,0x00000010       ; 16
	bne	$6,$2,$L62
	sll	$6,$6,8
$L62:
	li	$6,0x0000000f       ; 15
	sll	$6,$6,8
	li	$4,0x0000093e       ; 2366
	ori	$5,$5,0x3000
	or	$5,$5,$6
	jal	func_8002D4C8
	andi	$5,$5,0xffff
```

So the structure is clearer now:
- $5 = vol = ((160 - |x|) * 127) / 160 computed via magic division: mult $3,$4 where $3 = (160-|x|)*127... hmm, `sll $3,$2,7; subu $3,$3,$2` = (160-|x|)*127. Then `mult $3,$4` (M), mfhi $9. Then `sra $4,$9,6; subu $5,$4,$3` where $3 = sra $3,31 (sign). So $5 = ((hi(M*n))>>6) - (n>>31) = n/160 (signed division by 160 with the "add" correction). Good: $5 = vol.
- Then the second division: `addu $2,$6,160` = |x|+160, `mult $2,$4` (M), `mfhi $6`, `sra $3,$6,3`?? Hmm, `sra $3,$6,3` — that's >>3, not >>5. Hmm, division by 20 needs shift 5. Whatever — it's x = (x+160)/20 with a different magic path. Hmm, `sra $3,$6,3` then `subu $6,$3,$2` where $2 = sra $2,31 (sign of the numerator). So x = (hi(M*n)>>3) - (n>>31)? That'd be division by 8-ish... Hmm, maybe the compiler used a different magic. Never mind.

Key: the tail order in the target:
```
$L62:
	li	$6,0xf
	sll	$6,$6,8
	li	$4,0x93e
	ori	$5,$5,0x3000
	or	$5,$5,$6
	jal	func_8002D4C8
	andi	$5,$5,0xffff
```

So the `li $4,0x93e` (a0 = the first arg) comes BEFORE the `ori $5,$5,0x3000` (which computes vol|0x3000 = the second arg's first op).

In my cand03, the order was: ori, li, or. So I need: li, ori, or.

Now, what does the source look like in the target? The original source (with the launder):
```
{
    s32 flg = 0x3000;
    func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF);
}
```
So the ori IS the arg expression's first op. And the li $4,0x93e comes before it in the schedule.

So in the target, the constant's li was scheduled BEFORE the ori. That's the natural MIPS arg order? Hmm, in gcc, for `f(a0const, a1expr)`, the args are evaluated in reverse (a1 first) but the CONSTANT's materialization `li $4,0x93e` happens in `convert_arg_registers` — which is called AFTER the other args are expanded? Hmm, but it came first in the schedule.

Wait — maybe the reason is the SCHEDULER, not the LUID: the ori (a1's chain) is part of a long chain feeding the call; the li is independent and can go anywhere in the group. sched1 fills the "call group" in LUID order but the LUID of the li might be earlier than the ori's if the ori was expanded as part of the arg expression AFTER the constant.

Hmm, but in my cand03, the ori is a separate statement (earlier LUID) → it goes first.

So: if I make the `vol | flg` part of the CALL EXPRESSION again (as the original), the ori's LUID would be at the arg expansion (after the constant's li LUID if the constant is converted first).

So the fix: keep the expression `((vol | flg) | x) & 0xFFFF` in the call, AND create the "2nd set" of vol in a way that doesn't change the value and doesn't add an instruction.

Hmm! But wait: cand04 (vol2 = vol copy) failed. Because the copy was folded.

Hmm, but hold on: does the "2nd set" even matter now? cand03 already achieves the chain order (the mults, the a3→a2 register) — score 2 with everything matching except the li position. So maybe the 2nd set isn't needed at all: maybe the launder's ONLY effect was on the scheduling of this tail!

Let me reconsider: cand01 (launder simply removed) gave score 29 with the chain in a different order (mults swapped, a3 vs a2). cand02 (early `vol = vol | 0x3000`) gave score 7: chain matched, but the ori was early (at 80) and the li later... wait no. In cand02 the diff showed the ori at 80 vs the target's 84 and mine's li at 84 vs the target's 83. And the target had an extra sll at 80 (which was actually the `sll $6,$6,8` from the x chain).

Hmm, cand02's diff:
```
replace mine[79:81] target[79:81]
   79  bne a2,v0,988 | bne a2,v0,98c
   80  ori a1,a1,0x3000 | sll a2,a2,0x8
insert mine[84:84] target[84:85]
   84  -- | ori a1,a1,0x3000
replace mine[84:85] target[85:86]
   84  or a1,a1,a3 | or a1,a1,a2
```
Hmm, cand02's mine had 110 ins vs target 111 — so cand02 had a different structure (the extra insn was missing). In cand02, the ori was at 80 and the or at 84 (4 slots later).

Now with cand03 (late compound assign), the ori is at 83 and the li at 84; the target has li at 83, ori at 84.

So in cand03 the structure is right except the li/ori swap.

So: I want the li $4,0x93e BEFORE the ori $5,$5,0x3000, with the or after.

If I move the `vol = vol | flg;` back INTO the call expression (as in the original source) while keeping a real 2nd set of vol elsewhere... The 2nd set must not add instructions.

Hmm! What about this: the target's launder creates the 2nd set of vol. What if I create the 2nd set with the `flg` variable itself?

```
{
    s32 flg = 0x3000;
    vol = vol | flg;      /* 2nd set */
    func_8002D4C8(0x93E, (vol | x) & 0xFFFF);   /* ori is now just vol|x */
}
```
This is cand03. The ori is a separate statement → earlier LUID.

Alternatively:
```
{
    s32 flg = 0x3000;
    s32 v2 = vol | flg;      /* 2nd set of a NEW var; the ori stays in the expression */
    func_8002D4C8(0x93E, (v2 | x) & 0xFFFF);
}
```
Here the ori (vol|flg) is a separate statement → same LUID issue.

Hmm, what if the 2nd set is created WITHOUT any op — e.g. by an assignment that gcc keeps as a real copy? Like `vol = vol;`? Folded.

OK, alternative approach: maybe I don't need a "2nd set" at all — maybe cand01's problem (the chain order) is fixable another way, and the only thing the launder really does for the tail is the LUID ordering.

Actually WAIT. Let me re-examine: maybe with the original expression (ori inside the call), the LUID order would be li then ori naturally, and the chain order problem in cand01 could be fixed by a different lever (e.g. the register a3→a2 and the mult order).

Let me test cand05 = original expression restored + the launder removed but with the "2nd set" done via a compound assign that keeps the ori in the expression...

Hmm, what if:
```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
...
{
    s32 flg = 0x3000;
    func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF);
}
```
and the 2nd set of vol is created by an EARLIER neutral statement that gcc keeps... we tried the copy (cand04) — folded.

Hmm, what if the 2nd set is created by assigning to vol a value that is *semantically equal* but not folded — e.g. `vol = (s32)(u16)vol;`? vol ≤ 127 so (u16)vol == vol. But the truncation is a no-op that gcc folds (vol's range is 0..127 → (u16)vol == vol → folded).

What about `vol = (s32)(s16)vol;`? Same.

Hmm, what about making the 2nd set on a DIFFERENT variable that the expression uses: e.g.
```
s32 v2;
...
v2 = vol;                     /* copy */
...
func_8002D4C8(0x93E, ((v2 | flg) | x) & 0xFFFF);
```
That's cand04 (score 29) — the copy got folded (so the chain order was wrong).

Hmm, why did the copy get folded but `vol = vol | flg` (a real op) not? Because the copy is a no-op → gcc's RTL copy propagation removes it.

So the 2nd set needs a real op. But a real op on vol (like |0x3000) puts the ori at that statement's position (early).

UNLESS the real op is placed at the RIGHT place (late) and the expression keeps the ori... but the ori IS the op.

Hmm, so: what if the real 2nd-set op is something else that is value-neutral but not folded, placed early, e.g. `vol = vol + (0 & vol);`? Folded.

What about `vol = vol ^ 0;`? folded. `vol = vol * 1;`? folded. `vol = vol - 0;`? folded.

`vol = vol | (0x3000 & 0);`? folded.

Hmm. What about a 2nd set that changes a DIFFERENT variable used in the expression? E.g., the `x` variable:
```
x = x << 8;     /* 2nd set of x */
```
x already has multiple sets.

OK, let me reconsider the whole thing. What if the real lever is:

The launder's effect in the target is (a) the chain order (the mults) and (b) the tail order (li before ori).

With cand03 (compound assign at the flg block), I got the chain order right but the tail wrong. What if I keep cand03's structure but make the constant's li come earlier by changing the call to use a variable that holds the constant?

Hmm, alternatively: what if I put the `vol = vol | flg;` statement AFTER the call... no.

What if the flg OR is folded into the constant differently: e.g. instead of `vol = vol | flg` (which produces `ori $5,$5,0x3000`), what if I write the expression as `(vol | x) | flg`? Then the ori would come after the or. The target has ori then or. No.

Hmm, think about WHY the target has `li $4,0x93e` before `ori $5,$5,0x3000`.

In the target, the ori computes a1 = vol|0x3000 — it is the first op of the SECOND argument's expression. The li computes a0 = 0x93e — the FIRST argument.

For the li to be scheduled first, its LUID must be earlier. In gcc's RTL, the constant arg's li is created in `convert_arg_registers` during expand_call — that happens AFTER the arg expressions are expanded (they're separate gimple statements expanded earlier). So the li's LUID should be LATER than the ori's.

Unless the arg expression's ops were NOT expanded earlier — i.e. the whole `((vol|flg)|x)&0xFFFF` was expanded as part of the call! That happens if the expression is "simple" enough to be expanded inside the call's arg conversion — no, expand converts call args that are not constants into registers via expand_expr at the call site? Actually in expand_call, for each arg, `convert_arg_to_registers` is called; for a non-constant arg, it may just pass the pseudo (the gimple temp). The gimple temps for the subexpressions were created by gimplification: `D.x = vol | flg; D.y = D.x | x;` — two statements. Their RTL is expanded in statement order (before the call).

So the ori's LUID < the li's LUID. Contradiction with the target!

...UNLESS the ori in the target is NOT from the arg expression but from a separate gimple statement whose RTL was expanded AFTER the call's conversion? Impossible.

Hmm, unless the ori is from a statement in a DIFFERENT BLOCK that got scheduled into this position? No, the ori is in the same block as the call.

WAIT. What about the LAUNDER's asm? `__asm__("" : "=r"(vol) : "0"(vol));` — the asm's output is a new pseudo V. The expression `vol | flg` uses V. The asm insn is in the RTL (pri 1). The ori consumes V.

Now, the LUID of the ori is still earlier than the li.

So the ONLY way the li comes first is by PRIORITY, not LUID. sched1: the call group is scheduled; among ready insns, higher priority first. The li (a constant, single-set) gets a BIRTH BOOST (it's born at the call, single-set, no dependencies → boosted to be scheduled ASAP). The ori depends on vol (a long chain) — its priority is that of the chain (low). So the li wins!

In my cand03, the ori is a separate statement: it's ALSO single-set-ish but it's part of a chain... hmm, but then why does the ori come first in cand03?

In cand03, the ori (vol|flg) is a separate gimple statement, expanded BEFORE the call. So its LUID is earlier AND it's ready earlier (once vol is ready). The li is born at the call (later LUID). Both are in the call group? sched1's "call group" includes the call and its arg setup insns. The ori is not part of the call group (it's a separate statement before the call) — but sched1 can still schedule it into the group region.

Hmm. So in cand03 the ori got scheduled before the li. In the target, the ori is inside the arg expression → also a separate statement...

WAIT. No! In the target, the source is `func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF);` — gimplification creates temps D.a = vol|flg, D.b = D.a|x, and the call uses D.b. So D.a's statement is before the call. Its RTL ori has an earlier LUID than the li. So the ori should come first — but the target has the li first!

Unless... the ori in the target is NOT D.a's ori but the FINAL `or $5,$5,$6` is D.b's op, and the `ori $5,$5,0x3000` is... hmm, what if the ori is part of the LAST op?

Hmm, what if the source in the target is different from what I assume? The current src has the launder; the target = the current src's compilation. So the target's ori comes from `vol | flg`.

OK so in the target: ori (LUID early) is scheduled AFTER the li (LUID late). That means PRIORITY won over LUID. The li must have a higher priority than the ori.

The birth boost: in gcc's sched1, `insn_birth_priority` — an insn that is "born" (single set) gets a priority boost of `INSN_BIRTH_PRIORITY`? Hmm, but the li is born at the call and the ori earlier.

Hmm, actually maybe the opposite: gcc's sched1 has a rule that an insn whose *only* purpose is to set up a call argument and which is a constant...

Let's look at the actual difference between cand03 and the target once more:
- cand03: [x-chain: sll,li,sll] then [ori] then [li $4,0x93e] then [or] then [jal] [andi]
- target:  [x-chain: sll,li,sll] then [li $4,0x93e] then [ori] then [or] then [jal] [andi]

Hmm wait, in the target the x-chain is:
```
	li	$6,0x0000000f		# 15
	sll	$6,$6,8
$L62:
	li	$4,0x0000093e		# 2366
	ori	$5,$5,0x3000
	or	$5,$5,$6
	jal	func_8002D4C8
	andi	$5,$5,0xffff
```
and before that:
```
	li	$2,0x00000010		# 16
	bne	$6,$2,$L62
	sll	$6,$6,8
```
So: $6 = x (the /20 result), the bne checks x != 16, and the delay slot does sll $6,$6,8 (x<<8). If x == 16, jump to L62 where $6 = 15 and sll $6,$6,8 → 0xF00.

So the x-chain in the target is: [li $6,15 / sll $6,$6,8] at L62, then [li $4,0x93e], [ori], [or], [jal], [andi].

Note the block L62 is a separate basic block (the branch target). So the target has TWO blocks: the fallthrough block (bne + delay sll) and L62 (li 15, sll).

Interesting! In the target, the `li $4,0x93e` is in the L62 block (the x==16 case)! And the ori/or/jal are also in L62? Hmm, that can't be: the call must happen in both paths.

Hmm, looking at the target's listing again:
```
	li	$2,0x00000010		# 16
	.set	noreorder
	.set	nomacro
	bne	$6,$2,$L62
	sll	$6,$6,8
	.set	macro
	.set	reorder

	li	$6,0x0000000f		# 15
	sll	$6,$6,8
$L62:
	li	$4,0x0000093e		# 2366
	ori	$5,$5,0x3000
	or	$5,$5,$6
	.set	noreorder
	.set	nomacro
	jal	func_8002D4C8
	andi	$5,$5,0xffff
```
So the block after the bne is: li $6,15; sll $6,$6,8; then L62: the call. So the compiler DUPLICATED the call block: one copy for the x==16 path (with $6=15<<8) and the fallthrough copy (with $6 = x<<8 from the delay slot)...

Hmm no. Look: the bne jumps to L62 (skipping the li 15/sll). The fallthrough executes li $6,15; sll $6,$6,8 — that OVERWRITES $6 with 15<<8?! That would be wrong for the x != 16 case.

Hmm, unless the code is:
```
	bne $6,$2,$L62      ; if (x != 16) goto L62
	sll $6,$6,8          ; delay slot: x = x<<8  (only if x == 16?? no)
```
Hmm, the delay slot executes in both cases. So $6 = x<<8 always. Then if x != 16 → jump to L62 (skipping li 15 / sll). If x == 16 → fall through: li $6,15; sll $6,$6,8 → $6 = 0xF00. Then L62: the call.

Yes! That's it: the branch is INVERTED in the listing: `bne $6,$2,$L62` means "if x != 16, jump to L62" (skipping the override). The fallthrough (x == 16) does li 15, sll 8. ✓.

So the L62 block contains: li $4,0x93e; ori $5,$5,0x3000; or $5,$5,$6; jal; andi (delay).

So in the TARGET, the call block (L62) contains the li $4,0x93e BEFORE the ori $5,$5,0x3000.

Now, the ori is in the SAME block as the call. In the RTL, the ori (from D.a = vol|flg) is in the same block as the call. Its LUID is earlier than the li's.

But the scheduler put the li first. Why? Priority! The ori is at the END of a long dependency chain (vol = division chain) → low priority. The li (a constant, no deps) → high priority (birth boost / ready).

In cand03, the ori is also at the end of a chain (vol|flg) → low priority. So why did the scheduler put the ori first in cand03?

Because in cand03, the ori is a separate statement whose LUID is before the call's, and the call group in sched1: the group's members are scheduled in LUID order? Hmm, but in the target the ori (earlier LUID) came after the li (later LUID).

Hmm, unless in the target the ori is NOT a separate statement but part of the call's arg setup (i.e., the arg expression was expanded AT the call). That would give the ori a LUID after the li.

When does gcc expand an arg expression at the call? In `convert_arg_to_registers`, if the arg is a "simple" expression (not a MEM), gcc may expand it there. Hmm, but the gimple temps are already there.

Alternatively: gimplification may have kept `vol | flg` as an expression in the call (not creating a temp) if it's "cheap" — gimple folding creates temps for non-trivial expressions in the arg list. `vol | flg` where vol is a variable and flg a constant: gimplify_rtx_…, for a BIT_IOR_EXPR of a var and a constant, it creates a temp D.a = vol | 0x3000.

Hmm, so it IS a separate statement.

I'm going in circles theoretically. PRAGMATIC APPROACH: I have the target's asm. Let me try variants and compare their asm via the delever_search diff. I need the li before the ori.

Variant ideas that change the LUID/priority relationship:
(V1) Compute the second arg into a temp BEFORE the x-chain? No, that changes the ori position.

(V2) Make the ori NOT depend on the long chain: e.g. `vol | flg` where vol is... no.

(V3) Give the `li $4,0x93e` a dependency-free earlier position: it's already independent.

(V4) Hmm! What if the priority difference comes from the ori being in a chain vs the li being in the CALL GROUP? In sched1, the call group (the call + its arg setups) is scheduled as a unit. The li is part of the call group (it's the arg setup for a0). The ori is NOT part of the call group (it's a separate statement) — but it can be scheduled into the group if it's ready.

In the target, the ori IS in the call group (sched1 decided to include it, since it's ready and part of the chain). Hmm.

Actually here's a cleaner hypothesis: **sched1 fills the call group with the arg-setup insns; the ori is in the group only if it's ready.** In the target, the ori was placed after the li within the group, meaning the group's order was [li, ori, or] — by LUID? If the li's LUID < the ori's LUID, then the li was created FIRST.

When is the li created first? If the constant arg is converted to a register BEFORE the other arg's expression is expanded. In expand_call:
```c
  /* Expand the arguments... */
  for (i = 0; i < nargs; i++) ...
```
Hmm, in gcc's expand_call, the args are processed via `init_cumulative_args` which sets up the arg registers, and then for each arg `convert_arg_to_registers` is called in order 0..n-1. The expression args are already expanded (they're gimple temps → RTL pseudos). The constant arg's li is created in convert_arg_registers → LUID at the call.

So the li's LUID > the ori's LUID. So the target's order (li before ori) is NOT by LUID → it IS by priority.

So: in the target, the li has HIGHER priority than the ori. In cand03, the ori has higher priority than the li (or equal priority + earlier LUID wins).

What raises the li's priority? The birth boost. What lowers the ori? Its chain.

Hmm, in cand03 the ori is a separate statement — maybe as a separate statement it gets a different priority than when it's in the call group.

Hmm, wait. Actually maybe in cand03 the ori is NOT part of the call group, and it's scheduled BEFORE the group (as a regular insn), while in the target the ori IS in the call group (sched1 pulls it in because it's ready and needed by the call). In the group, the order is by LUID... which would still put the ori first (earlier LUID).

Hmm, unless within the group sched1 orders by "priority then LUID" and the li has higher priority.

OK — empirical time. Let me try a batch of variants, each cheap (one compile ~20-30 s). Let me try 4 variants at once (4 Bash calls in parallel — but they may conflict on the scratch dir! The scratch is per-pid: `scratch_dir = RUN/"score"/f"{alias}__{fn}"/f"p{os.getpid()}"` — different pids → different dirs. And the tag includes the pid. So parallel runs are safe (different pids).

Let me define the variants:

V-A (cand05): keep the ori in the call expression, and create the 2nd set of vol by a compound assign that is value-neutral but not folded...

Hmm, what if the 2nd set is: `vol = vol | flg;` but placed INSIDE the call expression as a statement-expression? Not allowed (stmt-expr is a GNU extension but plain C-ish? The house rules say real C moves only; the C0505 catalog doesn't include stmt-exprs. Also the original source uses stmt-exprs for launders. Avoid.)

V-B (cand05): the ori as a separate statement BUT with the constant materialized earlier:
```
{
    s32 flg = 0x3000;
    s32 c = 0x93E;
    vol = vol | flg;
    func_8002D4C8(c, (vol | x) & 0xFFFF);
}
```
Hmm, `c` is a constant → folded into the call → the li is created at the call (same as before).

V-C: reorder the statement so that the x-chain comes AFTER the ori? No.

V-D: Make the ori depend on x instead: `vol | flg` → hmm.

V-E: What if I write the second arg as `(vol | x) | flg` and put `vol = vol | flg`...

Hmm, let me think about V-F: keep cand03's structure but make the FIRST argument non-constant so it's expanded earlier?! No, we need the li EARLIER.

V-G: Make the li part of the same statement as the ori — e.g. assign the constant to a variable first:
```
{
    s32 flg = 0x3000;
    s32 c93e = 0x93E;
    vol = vol | flg;
    func_8002D4C8(c93e, (vol | x) & 0xFFFF);
}
```
The gimple: D.c93e = 2366 (a statement before the ori statement) → the li is expanded at THAT statement → earlier LUID than the ori! And since c93e is a local temp used once, gcc's RTL would be `li v?,2366` then `move a0,v?` — hmm, 2 insns. Unless the copy is coalesced into a0 (very likely: gcc coalesces the li's dest with a0 since a0 is only written by the copy). Actually the li would be `li a0,2366` directly (the pseudo is copied to a0, and the copy is coalesced) → 1 insn, but with an EARLIER LUID!

That's promising! But will gcc fold the constant D.c93e = 2366 into the call arg at gimple time? gcc's gimplifier folds constants: `D.c93e = 2366; f(D.c93e)` → the call's arg becomes the constant 2366 directly (gimple folds a constant temp into its use) → the statement D.c93e = 2366 disappears → the li is created at the call again. Hmm. gimple folding does propagate constants (fold_stmt / SSA propagation). Likely folded.

To prevent folding, the value must not be a compile-time constant... but 0x93E is.

Hmm, unless I use it twice (so it's not foldable) — but then it needs a register → +insns.

OK, let me think about the priority route instead: how to make the li's priority higher or the ori's lower?

The ori's priority: it depends on vol (the division chain) and on flg. Long chain → the ori inherits a low priority.

The li: single-set constant → birth boost.

In cand03, the ori ALSO depends on the chain... so it should also be low priority. Yet it came first. So the difference must be LUID-based (sched1 prefers earlier LUID among equal priority).

So in the target, the li's priority > the ori's priority. Hmm, that means in the target, the ori has a LOWER priority than in cand03. What could lower it? The launder! The asm (pri 1) is the ori's input → the ori's priority = the asm's priority (1) → very low → scheduled late!

YES! That's it. The asm has priority 1 (per cookbook §373), and the ori consumes the asm's output → the ori inherits priority 1 → it's scheduled LAST (after the li).

So to reproduce: the ori must inherit a LOW priority. In plain C, what has low priority? An instruction whose priority is low — e.g. an instruction with a long dependency chain... Hmm, the asm's priority is 1 (the minimum).

In cand03, the ori depends on vol (the division chain, priority = the chain's priority ~ some value). And the li (birth-boosted) — hmm, but then the li would also win in cand03.

Hmm, priorities: in sched1, `insn_priority` computes a priority from the insn's dependencies (waiting time). The li has no deps → priority 0 + birth boost. The ori has a dep on the long chain → high "waiting" number? In gcc's sched, higher priority = scheduled earlier. The priority is computed as the "critical path length" — an insn whose result is needed late gets a high priority.

Ugh. The asm's priority 1 is the LOWEST (scheduled last). The ori's consumer is the call.

OK. Since the ori inherits from the asm (pri 1), the ori is scheduled very late — after the li. In cand03, the ori inherits from the vol chain (higher pri) → scheduled earlier.

So to reproduce the target's order, the ori must have a very low priority — i.e. its input must be a "low-priority" insn.

In plain C, how do we get a low-priority insn feeding the ori? The asm is the classic way (but that's a launder — forbidden).

Alternative: the ori could be scheduled late because of the *block structure*: in the target, the ori is in the same block L62 as the call. Hmm.

Hmm, hold on. Let me reconsider. Maybe the difference is simpler: in the target, the ori is in the block AFTER the branch (L62) while the li is also in L62. Both in L62. In cand03, maybe the ori is in the FALLTHROUGH block (before the bne) and the li in L62?

Look at cand03's structure: the ori is a separate statement `vol = vol | flg;` placed in the source AFTER the `if (x == 0x10) x = 0xF;` block. In the source:

```
x = (x + 0xA0) / 0x14;
if (x == 0x10) { x = 0xF; }
x = x << 8;
{
    s32 flg = 0x3000;
    vol = vol | flg;
    func_8002D4C8(0x93E, (vol | x) & 0xFFFF);
}
```
The `if (x == 0x10) x = 0xF;` creates a branch; gcc's if-conversion/reorg duplicates the tail. In the target, the structure is: bne $6,$2,$L62 / sll $6,$6,8 (delay) then the L62 block with li 15, sll 8 (the x==16 override), and L62: the call.

Hmm, in the target, the x==16 override block (li 15; sll 8) comes BEFORE the call block, and the call block (L62) is shared. So gcc created: block A: [bne → L62; sll] ; block B: [li 15; sll; fallthrough to L62]; block L62: [li $4; ori; or; jal].

So the call is in a SEPARATE block (L62), reached from both paths.

In cand03, the structure might be: the ori statement is in block A or B, and the call block is separate. Then the ori would be scheduled in its own block (before the branch), not in L62!

Hmm, but the diff showed mine[83] = ori and mine[84] = li, mine[85] = or, all adjacent — so in mine the ori IS adjacent to the li and the or, i.e. in the same block as the call. Hmm, so mine has [ori][li][or] in the call block, and the target has [li][ori][or].

Hmm OK. So both have the call block with 3 insns; the order differs.

So it's a scheduling priority/LUID thing within the same block.

Let me try to think about which C construct would give the ori a lower priority...

What if the ori is NOT the first op of the arg, i.e. the arg expression is `((vol | flg) | x)` where the ori comes first — same.

What if I make the ori depend on x as well, e.g. `vol = vol | (flg & x)`? That changes the semantics (no).

What if the ori depends on a LONGER chain? E.g., if the `vol | flg` came after a longer dependency. Hmm, in the target, the ori's input is the asm's output (pri 1).

Alternatively: what if the ori is scheduled late because its RESULT is needed late (the call is far away)? Both cases have that.

You know what? Let me just try a bunch of variants empirically and look at their asm. To see a candidate's asm I need the .s of the spliced TU. I can get that with --keep + objdump (denied)...

Hmm! But wait: I can get my candidate's asm through the delever_search diff output (which shows changed blocks). If I get the score to 0, done. Otherwise I iterate.

Alternatively: I can compile my candidate's body spliced into the TU myself via cc1_dumps_tu.sh — but that needs a spliced TU file (the whole src with my body). I can't create that (179KB file, and copying requires reading it).

Hmm, actually — can I? The Write tool can write large files but I'd have to reproduce 179KB of content in my message. No.

BUT: cc1_dumps_tu.sh takes a .c FILE. What if I make a small .c file that #includes the original? The TU is a .c file, not a header. I could create a .c file with:
```
#include "../../../../src/ov_SC06_030/ov_SC06_030_jr_8017F65C.c"
```
That would include the whole TU but with the ORIGINAL function (not my body). Unless I #define the function name to something else and provide my own definition... e.g.:

```c
#define func_8017FE9C func_8017FE9C_orig
#include ".../ov_SC06_030_jr_8017F65C.c"
#undef func_8017FE9C
<my body>
```
That's clever! The macro renames the original function; then my body defines func_8017FE9C. But the original TU might have other references to func_8017FE9C (calls) — those would be renamed too, creating a duplicate symbol? No: the renamed one is func_8017FE9C_orig and calls to it go to the renamed version; my new function would be unused but still compiled. The asm of my function would be emitted with the name func_8017FE9C. Then I can read its asm from the .s!

But the includes: the file must be in a directory where its relative includes resolve ("-I$(dirname $tc)" and "-Isrc/shared"). The TU includes "../shared/..." relative to its own dir. If my wrapper file is in a different dir, the relative include would break. The script adds -I<dirname of tc> and -Isrc/shared. The TU's includes are like "../shared/engine_types.h" → resolved relative to the includer's directory (the TU's dir) — but with -I flags, "../shared/x.h" relative to my wrapper's dir → .run/P40/T11/G15/../shared → wrong. But -Isrc/shared might save it if the includes are like "shared/..." Hmm, the script adds -Isrc/shared and the comment says: "-Isrc/shared on the cpp line: a TU's `#include "../shared/..."` resolves from any directory one level under src/". So a TU one level under src/ → its "../shared" = src/shared. My wrapper would need to be one level under src/ too — but I can't write under src/.

Hmm. But: the wrapper could be placed in my shard dir and use -I flags... The script's extra flags are fixed: -Iinclude -I<dirname tc> -Isrc/shared. If my wrapper is at .run/P40/T11/G15/foo.c, then "../shared/x.h" → .run/P40/T11/G15/../shared → .run/P40/T11/shared → doesn't exist. But cpp also searches the -I paths: for `#include "../shared/engine_types.h"`, cpp tries <dir of includer>/../shared/... then the -I dirs: "include/../shared", "<tc dir>/../shared", "src/shared/../shared" (no). Hmm, "../shared" relative to "src/shared" = "src/shared/../shared" = src/shared ✓? No: the -I dir is "src/shared", so "../shared/engine_types.h" relative to that = "src/shared/../shared/engine_types.h" = "src/shared/engine_types.h" ✓!!

So if the TU's includes are spelled "../shared/foo.h", then -Isrc/shared makes them resolve as src/shared/foo.h.

So a wrapper .c in my shard dir that #includes the TU by ABSOLUTE path would work: `#include "/home/musashi/bfm-decomp/src/ov_SC06_030/ov_SC06_030_jr_8017F65C.c"`. Then the TU's own "../shared/..." includes resolve via -Isrc/shared ✓ (as long as they're spelled that way).

But careful: the wrapper also needs the same macros/defines (the script passes -D__GNUC__=2 etc.). ✓ (the script passes them).

This gives me a way to see MY candidate's asm! Very useful. But it's a lot of machinery. Let me first check the simpler path: maybe the wrapper trick also lets me dump the TARGET (the current src) — I already have the target's asm from the dump.

Hmm, wait. Actually the simplest: I already have the target's asm. For my candidates, the delever_search diff tells me the score and the diff blocks. That's usually enough to iterate.

Let me now think about the tail more cleverly.

IDEA: What if I make the ori's priority low by putting the `vol | flg` op AFTER a long chain — e.g., make the ori depend on x (the /20 division chain) as well? The expression is `(vol | flg) | x` — the ori doesn't depend on x.

Hmm, what if I reorder to `(x | vol) | flg`? Then: or $5,$5,$6 (x|vol) first, then ori $5,$5,0x3000. The target has ori then or. No.

IDEA: What if the ori comes from a separate statement placed AFTER the call's constant... impossible.

IDEA: use the `x` chain to delay the ori: since the target's ori is in the block L62 (after the branch), and the x-chain is in the predecessor blocks, maybe in cand03 the ori is in the predecessor block (before the branch) and gets scheduled there, while in the target it's in L62.

Hmm! That's a thought: in the target, the ori is in L62 (the call block) — so it was PULLED into the call block. In cand03, if the ori is in the predecessor block, it would be scheduled there — but the diff shows mine[83]=ori adjacent to mine[84]=li and mine[85]=or (the call's or). So mine's ori is in the call block too, just before the li.

Hmm, so in mine the ori is also in the call block but scheduled before the li.

OK so within the call block, the order differs: [ori][li][or] vs [li][ori][or].

The li and the ori are independent (the li is a0, the ori is a1). The or depends on the ori. So the order [li][ori][or] vs [ori][li][or] — both are valid topological orders.

sched1 orders by priority then LUID. Since the target has the li first, the li must have higher priority OR the same priority and earlier LUID.

Since the li is born at the call (later LUID than the ori), the li must have a HIGHER priority.

What gives the li a higher priority? In sched1, the "birth boost": `insn_birth_priority`? Hmm, in gcc's sched1 there's `priority` computed from `insn_cost` and the "waiting" chains. A constant load (li) that feeds a call arg has a short "birth" and gets boosted.

Hmm, but in cand03, the ori comes first. Both are in the call block.

AH WAIT. Maybe the difference is that in cand03, the ori is a SEPARATE STATEMENT (its own gimple), so it's in the RTL as a standalone insn with an earlier LUID and possibly a "block-level" priority; while in the target, the ori is part of the call's ARG EXPANSION — i.e., gcc expanded the arg expression INSIDE the call (convert_arg_to_registers → expand_expr of the arg's rvalue). In that case the ori's LUID is after the li's.

When does gcc expand an arg expression inside the call? When the arg is not a simple pseudo! `convert_arg_to_registers` → for a non-MEM arg that isn't a register, gcc calls `expand_expr` on it → the expression is expanded AT THE CALL. But wait, gimplification should have created temps for the subexpressions...

Unless gimplification left the whole expression as ONE rvalue in the call arg (gimple calls can have expressions as args? No — gimple calls have simple args only).

Hmm, but this is the OLD-style gimplifier (gcc 2.7). In gcc 2.7's gimplify_call_expr:
```c
	  /* Expand the argument to a temporary if it is not a simple
	     variable... */
```
It creates a temp for complex args.

OK, radically different approach: EMPIRICAL. I have the target's asm. Let me try variants and just look at their asm via the wrapper trick (which gives me full listings, much better than diffs). Actually, the diff is enough if I'm careful.

Let me try the most promising variants for the tail order:

T1: `vol = vol | flg;` moved OUT of the block, placed right after the vol computation (cand02 style) but with the flg var declared later... no, cand02 gave the ori at 80 (too early).

T2: Keep cand03 but change the order of the two statements in the block:
```
{
    s32 flg = 0x3000;
    func_8002D4C8(0x93E, (vol | x) & 0xFFFF);   /* no */
}
```

T3: Use the original expression `((vol | flg) | x) & 0xFFFF` AND create the 2nd set of vol via a compound assign that is value-neutral and NOT folded:
```
vol = vol | 0;     /* folded by gcc? */
```
Hmm, `vol | 0` — gcc folds (x|0) == x for integers? In gcc's fold, `(x | 0)` is simplified to x only if x is not... Actually GCC does fold `x|0` → x. Yes.

T4: `vol = vol & ~0;` → folded.
T5: `vol = vol - 0;` → folded.
T6: `vol = vol + 0;` → folded.

Hmm, what about a 2nd set that gcc keeps but is cheap and doesn't change the value: `vol = (s32)(short)vol`? folded by range info.

What about making the 2nd set on a variable whose value is used in the expression, e.g. `flg`:
```
{
    s32 flg = 0x3000;
    flg = flg | vol;    /* hmm, changes semantics */
}
```

T7: What if the "2nd set" is on `x`? x already has 2+ sets.

Hmm, let me step back and ask: does cand03 even NEED the 2nd set? cand03 = the compound assign `vol = vol | flg` — the 2nd set IS the ori op. What if instead I keep the ORIGINAL expression (ori inside the call) and get the chain order by a different means?

The chain order difference (cand01 vs cand03): in cand01, the chain was:
```
lui a2,0x6666; ori a2,a2,0x6667; addiu a0,a3,160; mult a0,a2; ...
```
vs the target:
```
lui a0,0x6666; ori a0,a0,0x6667; li $2,0xa0; subu $2,$2,$5; sll $3,$2,7; subu $3,$3,$2; mult $3,$4; mfhi $9; ...
```
Hmm interesting, the target has `li $2,0xa0; subu $2,$2,$5` (160 - |x|) then `sll $3,$2,7; subu $3,$3,$2` (*127) then mult. And then a SECOND division: `addu $2,$6,160; mult $2,$4; ...`.

In cand01, the chain was: addiu a0,a3,160; mult a0,a2; ... i.e. the mult came before the *127 computation (sll/subu). So the target computes the numerator (160-|x|)*127 BEFORE the mult, and mine computed the mult of (160-|x|) directly.

So in the target, the FIRST mult is of the *127-scaled numerator, and the second mult is of (|x|+160) for the /20 division. The target's order: mult $3,$4 (the vol numerator) FIRST, then mult $2,$4 (the x numerator). Wait, in the target listing:

```
	mult	$3,$4      ; (160-|x|)*127 * M
	mfhi	$9
	#nop
	addu	$2,$6,160  ; |x|+160
	mult	$2,$4      ; * M
```
So the vol's mult is first, then the x's mult. And the magic M ($4) is set up before both.

In cand01 (mine):
```
	lui a2,0x6666
	ori a2,a2,0x6667
	addiu a0,a3,160    ; 160-|x|
	mult a0,a2         ; (160-|x|)*M   ← the mult of the UNSCALED numerator!
```
So mine multiplied (160-|x|) by M directly — meaning the *127 scaling was folded into the magic?! Hmm, no: mine's chain had `mult v1,a2` later (v1 = 127 * M?). Hmm, in cand01's diff, mine[69] = mult v1,a2 (v1 = 0x7F * M?). Hmm.

Anyway: the target's chain has the vol mult (of the scaled numerator) FIRST, then the x mult; and in mine the order was reversed, plus a register difference.

Why? Because in the target the vol chain (with the launder) has a different priority/LUID relationship with the x chain.

Hmm, in the target, the vol computation is BEFORE the x computation in the source (vol is computed first, then x = (x+0xA0)/0x14). So the vol mult should naturally come first. In cand01, the x mult came first. So the launder affected the ORDER between the two independent chains!

With the launder, the vol chain's result is consumed by the asm; the asm (pri 1) delays the vol chain's consumer... but the vol chain itself is still early in the source.

Hmm, the two chains are independent (vol's chain and x's chain). Their relative order in the schedule depends on priority: the x chain's result is used by the branch (bne) which is on the critical path; the vol chain's result is used later. So the x chain gets a higher priority → scheduled first → in cand01 the x chain came first.

In the target, the vol chain came first. Why? Because the vol chain's END (the asm) has priority 1 (very low) → the vol chain is DOWN-weighted (its priority is inherited from its consumer?) → hmm, that would push it later, not earlier.

Hmm, in gcc's sched1, an insn's priority is based on the "waiting chain" toward its consumers. A low-priority consumer (the asm, pri 1) → the vol chain's priority is low → scheduled LATER. But the target has the vol chain FIRST. Contradiction.

Ugh, unless the launder's asm output V is consumed by the ori (in the arg expression) — and the arg expression is at the call. Hmm.

Hmm, hold on, maybe the real difference in cand01 was NOT the launder but something else. Let me re-look at cand01's diff:

```
replace mine[56:64] target[56:62]
  56  sra a3,v0,0x10        | sra a2,v0,0x10
  57  bgez a3,930           | bgez a2,930
  58  move a1,a3            | move a1,a2
  59  negu a1,a3            | negu a1,a2
  60  lui a2,0x6666         | lui a0,0x6666
  61  ori a2,a2,0x6667      | ori a0,a0,0x6667
  62  addiu a0,a3,160       | --
  63  mult a0,a2            | --
```
So mine has a3 where the target has a2, and the magic in a2 vs a0.

And the target's chain (from the .s dump):
```
	sra	$6,$2,16
	bgez	$6,$L58
	move	$5,$6
	subu	$5,$0,$6
$L58:
	li	$4,0x66660000
	ori	$4,$4,0x6667
	li	$2,0x000000a0
	subu	$2,$2,$5
	sll	$3,$2,7
	subu	$3,$3,$2
	mult	$3,$4
	mfhi	$9
	#nop
	addu	$2,$6,160
	mult	$2,$4
	sra	$3,$3,31
	sra	$4,$9,6
	subu	$5,$4,$3
	sra	$2,$2,31
	mfhi	$6
	#nop
	#nop
	sra	$3,$6,3
	subu	$6,$3,$2
	li	$2,0x00000010
	bne	$6,$2,$L62
	sll	$6,$6,8
```
So the target: $6 = ax (the |x|), $5 = vol, and the magic is in $4.

Wait: `sra $6,$2,16` → $6 = ax; `move $5,$6` / `subu $5,$0,$6` → $5 = |ax| (in $5, not $6!). Then `subu $2,$2,$5` → $2 = 160 - |ax|. So the absolute value is in $5 and the signed value in $6.

Hmm, and the diff said mine[56] sra a3 vs target sra a2 — so the target's ax is in a2 = $6 ✓ and mine's in a3 = $7.

So in the target, ax is in $6 and in mine $7. And the magic: target $4 (a0), mine $2 (a2).

OK. So in cand01, the register allocation differs and the chain order differs.

Now here's the thing: cand03 already fixed ALL of that (score 2). So the compound-assign 2nd set gave the right chain.

So the remaining problem is ONLY the li/ori order. Let me think about what else could produce that.

Let me look at the target's asm once more for the call block:
```
$L62:
	li	$4,0x0000093e		# 2366
	ori	$5,$5,0x3000
	or	$5,$5,$6
	.set	noreorder
	.set	nomacro
	jal	func_8002D4C8
	andi	$5,$5,0xffff
```
Note: the andi $5,$5,0xffff is in the jal's DELAY SLOT. So the andi comes after the jal in the instruction stream (but in the delay slot).

Now mine (cand03): [ori][li][or][jal][andi]. Since mine[85] = or a1,a1,a2 (equal to target[85]) and the diff showed no difference at 86+, the andi is in the delay slot in both.

So the ONLY difference is the li/ori swap.

Hmm, since the call group contains [li a0][ori a1][or a1][jal][andi], and the ori is a1's setup...

IDEA: What if in my candidate the ori is scheduled in the PREDECESSOR block (before the branch) and the diff alignment coincidentally put it at 83? No, the or (a1's second op) must follow the ori in the same block, and the jal too. If the ori were in a different block, there'd be a branch between. The diff showed 83,84,85 contiguous with no branch → same block.

OK, let me try the empirical approach with several variants and check the score. Let me try:

V1: cand03 but with the flg-block's ori replaced by an expression where the constant comes first:
```
{
    s32 flg = 0x3000;
    s32 c = 0x93E;
    vol = vol | flg;
    func_8002D4C8(c, (vol | x) & 0xFFFF);
}
```

V2: cand03 with the ori statement moved after the x-chain but with `x` used first:
```
{
    s32 flg = 0x3000;
    vol = vol | flg;
    func_8002D4C8(0x93E, (x | vol) & 0xFFFF);
}
```
(then the ori would be after the or — wrong order, but let's see how the scheduler responds; maybe it produces [li][or][ori] — no.)

V3: Make the second arg's expression start with the constant-ish op...

V4: What if the ori is delayed by making it depend on the x chain? E.g. `vol = vol | (flg & 0x3000)`. No.

Hmm, V5: What if I add the flg to x instead: `((vol | x) | flg)` — no.

V6: What if the second arg's expression is `(vol | flg)` and x is ORed in a separate statement? Like:
```
{
    s32 flg = 0x3000;
    vol = vol | flg;    /* 2nd set */
    x = x | vol;       /* hmm, changes semantics: x|vol vs (vol|x) — same! */
    func_8002D4C8(0x93E, x & 0xFFFF);
}
```
Hmm, but x is used earlier (x = x << 8). Reassigning x changes x's value... `x = x | vol` — but the arg is `(vol|x)&0xFFFF` — semantically the same as ((vol|0x3000)|x)&0xFFFF? Yes if the ori is applied to vol first. Hmm, but the ORDER of the ors changes the insn order: the target has ori then or. With this version: `vol = vol|flg` (ori) then `x = x|vol` (or a1,a1,a2 → hmm, the or would be `or $5,$5,$6` with $5=vol? no, x|vol = or x,vol → `or $2,$2,$5`? The register assignment would differ.

Hmm. Let me think about V7: keep cand03's structure but ALSO make the constant's li part of an earlier statement in a way gcc keeps.

Hmm, what about making the first argument a variable that's assigned from a NON-constant expression that folds to 0x93E? E.g. `s32 c = 0x900 | 0x3E;` → folded to a constant.

What about `s32 c = 0x93E + 0;`? folded.

OK so a constant's li is always created at the use point.

THEREFORE: the li's LUID is always at the call, AFTER the ori's LUID (if the ori is a separate statement). So for the target's order, the ori must NOT be a separate statement earlier in the block — it must be expanded at the call!

When is the arg expression expanded at the call? If the arg is a single rvalue that gcc expands inline: e.g. if the arg is `vol | flg` where vol and flg are SSA temporaries, gimplification creates D.a = vol|flg (a statement) — hmm.

BUT: what if the expression is `vol | 0x3000` where the constant is folded INTO the expression: then gimplify creates D.a = vol | 0x3000 (a statement). Still a statement.

Hmm, unless gimplification's "fold" of the call's args happens at RTL expansion: expand_call → for each arg, `convert_arg_to_registers` → if the arg is not a pseudo, `expand_expr` it AT THE CALL. In gcc 2.7, the RTL for a gimple call arg is a pseudo (reg) — so no expansion at the call.

Hmm, so the ori is always a separate statement with an earlier LUID. So the target's order MUST be priority-driven.

=> The li has higher priority than the ori in the target.

What raises the li's priority? The "birth boost" (insn_birth_priority): in gcc's sched1, there's a concept where an insn that is "born" (has a single set) and is ready gets boosted. Hmm, but the ori is also single-set in the sense that it's the only def of a1 at that point (a1 is set by the ori and then by the or → 2 sets; but the ori's output pseudo is a1 → a1 has 2 sets → NOT single-set → no birth boost). And the li: a0 is set once (the li) and used once → single-set → birth boost → higher priority → scheduled earlier!

In cand03, the ori is a separate statement whose result is `vol` (a variable) → vol has 2 sets (division, ori) → the ori is not single-set either. Hmm, so both should behave the same.

UNLESS: in cand03, the ori is in a different BLOCK (the predecessor block) — then the scheduler's block ordering (the "cross-jump" / block reordering) matters, not the priority within the block.

AH, that's likely it! In cand03, the source order is:
```
x = (x + 0xA0) / 0x14;
if (x == 0x10) { x = 0xF; }
x = x << 8;
{
    s32 flg = 0x3000;
    vol = vol | flg;
    func_8002D4C8(0x93E, (vol | x) & 0xFFFF);
}
```
The `if (x == 0x10) x = 0xF;` creates a branch; gcc's reorg/if-conversion splits the tail into two blocks (the x==16 path and the fallthrough), and the call block is duplicated or shared. In the TARGET, the structure is: [bne → L62][sll] / [li 15; sll] / L62: [li $4][ori][or][jal]. So the target has the call in a shared block L62 reached from both paths.

In cand03, maybe the structure is: [bne → L][sll] / [li 15; sll] / L: [ori][li][or][jal]. Same structure, just the order inside.

OK whatever. Let me just try things. Since each try is cheap, let me try 4 variants in parallel:

cand05: cand03 + the constant as an early local variable:
```
s32 c93e = 0x93E;
...
func_8002D4C8(c93e, (vol | x) & 0xFFFF);
```
(declared at the top of the function, assigned at the top) — the front end will fold it, but let's see.

cand06: cand03 but with the second arg's expression reordered as `(x | vol) & 0xFFFF`:
```
vol = vol | flg;
func_8002D4C8(0x93E, (x | vol) & 0xFFFF);
```
The or would be `or $5,$5,$6`? hmm: x|vol → the arg = x | vol → the or would be `or $5,$6,$5`? Register order might differ. But the target has ori then or with $5=$5|$6. If the arg is x|vol, the compiler would emit `or $5,$6,$5`?? Hmm, or it might keep the commutative form. Let's try — cheap.

cand07: cand03 but the flg-block's ori is `vol = vol | 0x3000;` and the flg variable removed (i.e. the constant inline). Similar to cand03 (flg is a constant 0x3000 → same).

cand08: cand03 but with the x-chain's `x = x << 8` moved before the `if`:
```
x = (x + 0xA0) / 0x14;
x = x << 8;
if (x == 0x10) { x = 0xF; }   /* wrong semantics */
```
No.

Hmm. Let me think about the "priority" angle again: to make the li's priority higher relative to the ori...

What if the ori is NOT needed until later? E.g. if the ori's result feeds the `or` which feeds the call — same.

What if the ori is in the block but its result is used by the or in a LATER block? No.

Hmm, what if I could make the ori a "late" insn by making the call's second arg a variable assigned in the previous block? E.g.:
```
{
    s32 flg = 0x3000;
    vol = vol | flg;
    x = x | vol;        /* hmm */
    func_8002D4C8(0x93E, x & 0xFFFF);
}
```
Then the ori is in the previous block (scheduled there) → wrong.

Honestly, maybe the simplest: try to make the ori EARLIER-equal-priority... hmm, I need it LATER.

Hmm, wait! What about the DELAY SLOT? Look at the target:
```
	jal	func_8002D4C8
	andi	$5,$5,0xffff
```
The andi is in the delay slot. In mine, the same (since the diff didn't complain about 86+).

Let me look at the actual difference in the instruction stream once more. Maybe the difference isn't the ORDER but the register! Let me recheck: mine[83] = ? and mine[84] = li a0,2366; target[83] = li a0,2366 and target[84] = ori a1,a1,0x3000.

Yes, it's the order.

OK, let me try the "different block structure" idea: what if I restructure the source so that the tail block contains the call with the constant FIRST in the source? Like:

```
{
    s32 flg = 0x3000;
    s32 arg = (vol | flg) | x;
    func_8002D4C8(0x93E, arg & 0xFFFF);
}
```
Here: D.arg = (vol|flg)|x → the ori is a separate statement (before the call) → same LUID problem.

What about:
```
func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF);
```
(the original expression, ori inside the call) — with the 2nd set created by...

Hmm, hmm. What if the 2nd set of vol is created by the `x = x << 8` statement?? No, that's x.

What if I create the 2nd set of vol via a compound assign that keeps the value but is a real op placed EARLY, and then the ori in the expression is a SECOND op? E.g.:
```
vol = vol | 0;      /* folded — no */
```

What about `vol = vol & 0x7F;`?? vol ≤ 127 so vol & 0x7F == vol semantically, but gcc doesn't know vol ≤ 127 (it might, via VRP: vol = ((160-ax)*127)/160 where ax is unknown → vol could be negative?). gcc's VRP might not prove it → the andi is a real op (1 extra insn). ✗ (adds an insn).

Hmm, but hold on: what if the extra andi is exactly what the target has somewhere? No, the target has no andi on vol.

OK, let me try yet another approach: make the ori the LAST op before the call by putting the whole second-arg expression in a way that the ori is generated at the call. E.g. use a comma/assignment inside the arg:

```
func_8002D4C8(0x93E, (vol = vol | flg, (vol | x) & 0xFFFF));
```
That's a comma expression — the assignment inside creates a statement... in gimple, the comma expression is expanded into a sequence of statements, with the assignment before the call. Same.

OK, pragmatic: let me try a batch of 6 variants and see if any hits 0. Let me think about which variants could plausibly flip the order:

The order flip = the li before the ori. Since the li is created at the call, the ori must be created after the li. The only way: the ori is created during the call's arg expansion.

In gcc 2.7's expand_call, args that are not MEMs and not pseudos get expanded via expand_expr at the call. When is an arg a raw expression rather than a pseudo? In the OLD RTL (gcc 2.x), the call's args are RTXs; after gimplification, the args are typically REG pseudos (from the gimple temps). But if gimplification folded the expression into the call arg... In gimple, `f(0x93E, D.a)` where D.a is a temp.

Hmm, so the ori (D.a = vol|flg) is a separate gimple statement.

UNLESS gimplification created the temp as part of the CALL's argument list without a separate statement — which happens for "cheap" expressions? gimplify_call_expr:
```c
	  /* Expand the argument to a temporary if it is not a simple variable
	     or constant... */
	  if (is_gimple_reg(t))
	    arg = t;
	  else
	    {
	      gimple_seq_add_stmt (pre_p, gimple_build_assign (make_tmp_var (TREE_TYPE (t)), t));
	      arg = gimple_build_temp (rhs);
	    }
```
So yes, a separate statement.

CONCLUSION: the target's [li][ori] order is priority-driven, not LUID-driven. And I can't reproduce a priority difference easily...

Hmm, unless the priority difference comes from the ori being in a DIFFERENT BLOCK in the target! Look at the target: the ori is in block L62 together with the li. Hmm.

Wait, wait. Let me re-read the target's asm once more:

```
	li	$2,0x00000010		# 16
	.set	noreorder
	.set	nomacro
	bne	$6,$2,$L62
	sll	$6,$6,8
	.set	macro
	.set	reorder

	li	$6,0x0000000f		# 15
	sll	$6,$6,8
$L62:
	li	$4,0x0000093e		# 2366
	ori	$5,$5,0x3000
	or	$5,$5,$6
	.set	noreorder
	.set	nomacro
	jal	func_8002D4C8
	andi	$5,$5,0xffff
```

Hmm, so the structure is:
- block1: `bne $6,$2,$L62` / delay `sll $6,$6,8` — if x != 16 → L62; else fall through.
- block2 (fallthrough): `li $6,15; sll $6,$6,8` — x == 16 case.
- L62: the call.

Wait, that's inverted from what I said: the bne jumps to L62 when x != 16 (skipping the override), and the fallthrough (x == 16) does the override. ✓ (as I said).

Now: in mine (cand03), the structure is presumably the same but with [ori][li][or] in L62.

Hmm, since the ori is in L62 in both, and L62 is the block with the call...

Hmm, in mine, the ori is a separate statement that comes BEFORE the call in the source, so it's in the same block L62 (the tail block). Its LUID is before the call's li. But the scheduler put it before the li anyway (consistent with LUID).

In the target, the ori is also a separate statement (D.a = vol|flg) with an earlier LUID, but the scheduler put the li first.

So in the target, the li has higher priority than the ori. The launder (asm, pri 1) makes the ori's priority LOW (its consumer chain... hmm, the ori CONSUMES the asm's output; the ori's priority comes from its own dependences, not its consumer).

Hmm, in gcc's sched1, `insn_priority` uses "waiting" chains: an insn's priority is computed from its successors. The asm (pri 1) is the ori...

Honestly: the asm's PRIORITY is 1 (per §373: `pri(asm) = 1`, always). An insn with priority 1 is scheduled LAST. So in the target, the ASM would be scheduled last?! But the asm is between the vol computation and the ori. If the asm is scheduled last, the ori (which depends on the asm) must be after it → the ori would be at the very end. But the target has the ori right before the or and the jal. Hmm, and the asm emits no bytes → invisible. So the asm is scheduled at the END (after the jal?!) — impossible since the ori depends on it...

Hmm, unless the asm's LUID is between the vol computation and the ori, and the ori is right after it in the LUID order, so the asm+ori pair is scheduled together at the position determined by the chain.

OK. I've spent a lot on this. Let me try the empirical route with several variants, and let me use the wrapper trick to see my candidate's asm directly — that's much more efficient than blind iteration. Let me build the wrapper:

File: .run/P40/T11/G15/func_8017FE9C__.../probe.c
```c
#define func_8017FE9C func_8017FE9C_orig
#include "/home/musashi/bfm-decomp/src/ov_SC06_030/ov_SC06_030_jr_8017F65C.c"
#undef func_8017FE9C
<my body>
```
Then run cc1_dumps_tu.sh on it and read the .s for func_8017FE9C.

Risks: the TU might have other definitions with the same name, or the rename might break something (e.g. a table of function pointers). Also the file has `#include "common.h"` etc. Let me check the TU's includes.

Actually, simpler: the TU's function is at line 3018 in a 3000+ line file. My body replaces the definition. The wrapper approach renames the original and adds mine. The TU might reference func_8017FE9C elsewhere (calls) → those become calls to the renamed one. Fine for asm inspection.

Let me check the includes of the TU and whether it has a function-pointer table.

Actually, even simpler: does the TU's .c include another .c? Let me check the first 20 lines of the TU.

Let me do that, and in parallel try a couple of variants.

Actually, wait. Let me reconsider the problem from the "what does the launder do" angle once more, because there might be a much simpler lever-free spelling.

The launder: `__asm__("" : "=r"(vol) : "0"(vol));` — in the RTL this becomes:
```
(set (reg V) (reg vol))   ; the asm input
```
plus an asm insn. The asm output V is a NEW pseudo. So vol has 2 sets? No: vol is SET by the division and READ by the asm. V is SET by the asm and read by the ori. So it's a copy: vol → V.

So the target's chain is: division → vol → (asm copy) → V → ori.

In plain C, `s32 v2 = vol;` gives the same RTL shape: (set v2 vol). But gcc's copy propagation (in `flow`) removes such copies when profitable... but NOT always! Copy propagation in pass_flow only propagates if the source is not "expensive" and the copy is a simple reg-reg move. It usually removes them.

Hmm, but in cand04 the copy was removed (score 29 = the same as cand01). Hmm.

BUT: what if the copy is made "expensive" so it survives? E.g. if the copy is a "pseudo" that is used in a way that prevents coalescing...

Hmm, alternatively: the asm copy's KEY property is that it has PRIORITY 1 (so it's scheduled late, and its consumer too).

Hmm, what if instead of a copy we use a real op that produces the same value but isn't folded — e.g. `v2 = vol | 0`? folded. `v2 = vol + vol - vol`? gcc folds.

`v2 = vol ^ (vol - vol)`? folded.

What about `v2 = (s32)(u32)vol;`? folded.

`v2 = vol * 1;`? folded.

Hmm, what about using a volatile? `v2 = *(volatile s32 *)&vol;` — that's a memory read (adds a load). ✗

What about making the copy survive because vol is used TWICE (so the copy can't be folded into the single use)? E.g.:
```
vol = ...;
s32 v2 = vol;
... use vol somewhere ...
... use v2 in the expression ...
```
Hmm, then the copy might survive as a real insn (an extra insn!). The target has no extra insn.

OK OK. Let me look at the target's asm ONE more time for evidence of the asm's presence:

Between the division chain and the ori, is there anything? Looking at the target:
```
	subu	$5,$4,$3        ; vol = ...
	sra	$2,$2,31
	mfhi	$6
	#nop
	#nop
	sra	$3,$6,3
	subu	$6,$3,$2
	li	$2,0x00000010
	bne	$6,$2,$L62
	sll	$6,$6,8
```
The `#nop`s are delay-slot fillers. The asm (0 bytes) would be in the RTL but emit nothing — in the .s, an asm with no instructions emits nothing (it's a "no-op" asm). But the .s might show it? No.

Note: in the target's listing there's NO `move $5,$5` (the asm's copy) — because the asm's output coalesced with the input (the "0" tie), so no move was emitted. ✓.

So the target's asm copy is invisible in the .s but affects scheduling.

Now: the target's tail:
```
$L62:
	li	$4,0x0000093e
	ori	$5,$5,0x3000
	or	$5,$5,$6
```
$5 = vol (from the division) → `ori $5,$5,0x3000` → $5 = vol|0x3000. So the asm's copy (vol→V) was coalesced: V and vol are the same register ($5). So the asm is invisible.

So the ONLY effect of the asm is scheduling (priority 1 for the asm, which is scheduled LAST — but since it's coalesced with vol's register, its position doesn't matter much; but the DEPENDENCY structure changes: the ori depends on the asm (pri 1) → the ori is scheduled after the asm → and since the asm is pri 1 (last), the ori is pushed late?!

Hmm, if the asm is scheduled last (after the jal!), then the ori would be after the jal → impossible (the ori feeds the call). So the asm must be scheduled before the call. Since the asm has priority 1 (the lowest), it would be scheduled as late as possible — just before the call. And the ori (its consumer) right after.

So the asm's position = right before the ori, i.e. at the end of the block! And the ori right after it. And the li (a0's setup) before the asm.

So the target's order [li][ori][or] is: the li first, then the asm+ori.

In cand03, the ori is at 83 and the li at 84 — the opposite.

Hmm, so in the target the li is BEFORE the ori, meaning the li was scheduled before the "last-scheduled" asm. But the asm is pri 1 (last)... yet the ori comes after the li. So the li (higher priority) was scheduled before the low-priority asm+ori. ✓ Consistent!

And in cand03, the ori (a normal insn, higher priority than the li?) got scheduled before the li.

Hmm, so the ori in cand03 has a HIGHER priority than the li? While in the target the ori (downstream of a pri-1 asm) has a LOWER priority.

So the lever is: make the ori have a low priority. In plain C, an insn's priority is low if... hmm.

What has low priority in gcc's sched1? The priority is computed as:
```
priority = insn_cost + (waiting time)...
```
Actually gcc's sched1 computes for each insn a "priority" = the length of the longest path to a "critical" insn, roughly. Hmm, but also `insn_birth_priority`?

Let me think about the "birth boost" idea from moves.md: "sched1-birth-boost: sched1 boosts the single-set la s3 (birthing) past the jal". So a single-set insn gets boosted.

In the target, the li (a0 = 0x93e) is single-set → boosted → scheduled early. ✓
In cand03, the ori is single-set? The ori sets $5 (a1) which is also set by the `or` → 2 sets → not boosted. Hmm.

Then why is the ori before the li in cand03?

Because the ori has a "waiting" chain: it's part of the vol chain... hmm, its input (vol) is ready early, so the ori is ready early, and it has an earlier LUID.

In the target, the ori's input is the asm (pri 1) → the ori's priority is derived from the asm → low.

Hmm, so the difference is really the asm's priority.

Can I make a plain-C insn have a very low priority? What if the ori depends on a long chain of cheap ops? Priority in sched1 ≈ the "birth" priority minus the waiting...

Alternatively — maybe the whole difference can be sidestepped: what if the ori's position is determined by the LUID and I can make the li's LUID EARLIER by making the constant's arg a value that's NOT a literal but computed in an earlier statement, without adding an instruction?

E.g.: `func_8002D4C8(0x93E, ...)` → what if the first argument is `(s32)(0x93E)`? Same constant.

What if the first arg is `2366`? Same.

What if the first arg is a variable assigned from a constant at an EARLIER point (top of the function)? The front end folds it (constant propagation) — but maybe NOT if the variable is assigned in a way that isn't folded... e.g. if the assignment is inside a branch? Hmm.

What about `s32 c93e = 0x93E;` at the top of the function and then `func_8002D4C8(c93e, ...)` — gcc's gimple SSA would propagate the constant (D.c93e = 2366 is a constant definition → propagated into the use → the use becomes the constant → the definition is removed). So no.

What if the constant is derived from a runtime value that provably equals 0x93E? e.g. `s32 c93e = 0x93E & 0xFFFF;` → folded to the constant.

Hmm, what if it's `s32 c93e = (s32)(s16)0x93E;` → 0x93E fits in s16 → folded.

OK so the li's LUID is always at the call. Then the order must be priority-driven: the li must beat the ori.

Since in the target the ori is low-priority (downstream of the asm), maybe I can achieve a low-priority ori in plain C by making the ori depend on a LONG chain that ends right before the call. E.g., if the ori's input (vol) is computed by a long chain that is itself late-scheduled... but vol's chain is early in the source.

Hmm, what if I MOVE the vol computation later in the source (e.g. after the x chain)? Then the vol chain would be scheduled later and the ori would come after the li!

But wait, in cand01 (no launder) the vol chain came AFTER the x chain (the x mult first) — the wrong order. Hmm, but that's about the chain order, not the ori.

Hmm, hmm. But hold on: in cand03 the chain order was right (the vol mult before the x mult) — because the 2nd set (the ori as a separate statement) changed the chain's structure. Hmm, why would the ori statement change the ORDER of the two chains?!

Because in cand03, the ori statement is a separate statement AFTER the x computation in the source:
```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;    /* chain 1 */
x = (x + 0xA0) / 0x14;                /* chain 2 */
if (x == 0x10) x = 0xF;
x = x << 8;
{ s32 flg = 0x3000; vol = vol | flg; func_8002D4C8(0x93E, (vol | x) & 0xFFFF); }
```
vs cand01 (no ori statement):
```
vol = ...;   /* chain 1 */
x = ...;     /* chain 2 */
...
```
In cand01 the chain order was x-mult first; in cand03 the vol-mult first. Hmm, what changed? The `vol = vol | flg` statement (a consumer of vol) — it makes the vol chain's result have a consumer EARLIER (before the call) → boosting the vol chain's priority → scheduled first!

AH, that's the mechanism: the ori statement (early consumer of vol) boosts the vol chain.

In the target (with the launder), the asm is an early consumer of vol → same boost. ✓

So the launder's role: an early consumer of vol that (a) boosts the vol chain's priority (so the vol mult comes before the x mult) and (b) creates the "last-scheduled asm" effect that delays the ori.

Hmm, for (b): in the target, the ori is delayed to after the li. In cand03, the ori is a separate statement (LUID before the call) so it lands before the li.

What if the ori were ALSO boosted to be earlier? no, we want it later.

Hmm! What if I make the "early consumer of vol" be something OTHER than the ori itself? E.g.:
```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
vol2 = vol;      /* the early consumer: a copy */
```
but the copy is folded (cand04) → no boost.

What if the early consumer is a real op whose result is used later, e.g.:
```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
volx = vol | flg;    /* the ori: a real op, early consumer */
```
then use `volx` in the expression. That's cand03 with the ori as a separate statement placed EARLY (right after the vol computation) — but that was cand02, which gave the ori at 80 (too early) — the ori was scheduled right after the vol chain (early), not at the call.

Hmm! In cand02, the source was:
```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
vol = vol | 0x3000;      /* early */
x = (x + 0xA0) / 0x14;
...
func_8002D4C8(0x93E, (vol | x) & 0xFFFF);
```
and the ori landed at 80 (before the x chain!) — because the ori was early in the source and ready early.

In cand03, the ori is late in the source (right before the call) → it landed at 83 (just before the call). The target has it at 84 (after the li at 83).

So the difference between cand03 and the target is just ONE slot: whether the li or the ori comes first within the call's setup group.

Since both are in the call group and the ori is the a1 setup and the li the a0 setup...

AH WAIT!!! Maybe that's it: in the target, the arg setup order is a0 then a1 (the ori is a1's first op). In cand03, the ori is NOT part of the call's arg setup (it's a separate statement whose result feeds the arg) — so it's not in the group. Hmm, but it's adjacent in the block.

Hmm, but if the ori were part of the arg setup (expanded at the call), the group order would be a0's li then a1's ori. ✓ TARGET!

So the target's ori IS expanded at the call (part of the arg setup group). That means in the target, gimplification did NOT create a separate temp for `vol|flg` — the arg expression was passed as a compound expression to the call!

When does that happen? In gcc 2.7's gimplify_call_expr, for each arg:
```c
      if (TREE_CODE (t) == VAR_DECL) ... 
      else { create a temp assign }
```
Hmm. But there's a special case: if the arg is a "simple" expression that can be expanded in place? I recall gimplify_call_expr has:
```c
	  /* If the argument is a constant, we can just use it. */
```
and for non-trivial args it creates temps.

Hmm, but hold on: maybe the arg IS a temp (D.a), and D.a's RTL was expanded as a separate statement, but the SCHEDULER put it in the group.

Hmm, but the LUID...

You know what? There's another possibility I haven't considered: THE ORDER OF THE STATEMENTS IN THE BLOCK. In cand03, the ori statement is the last statement before the call, so its LUID is just before the call's LUID. The li is created at the call. So the LUID order is [ori][li]. The scheduler, when scheduling the call group, takes the insns in LUID order → [ori][li].

In the target, the LUID order must be [li][ori]. So the ori has a LUID after the call's expansion. That means the ori was expanded at the call → the arg was a raw expression.

Hmm, is it possible that in the ORIGINAL src (with the launder), the gimplifier produced `f(0x93E, D.b)` where D.b = D.a | x and D.a = vol | flg? Then D.a's ori would have an earlier LUID than the li. ✗.

So in the target the ori must be part of the call's arg expansion. Which means the arg was `(vol | flg) | x` as a raw expression at the RTL level.

When gcc's RTL has a raw expression as a call arg: in gcc 2.7's expand_call, `convert_arg_to_registers` handles args that are not MEMs: it may call `expand_expr` on the arg → the expression is expanded AT THE CALL (with a LUID after the li if a0 was converted first).

And how does an arg stay a raw expression in the RTL? In the old gimplifier, `gimplify_call_expr` calls `gimplify_expr` on each arg → for a BIT_IOR_EXPR it creates a temp...

BUT: there's the "expand_expr" path for args whose value is a "CONSTANT" or when `TREE_CODE (arg) == VAR_DECL`...

Hmm, hold on: what about the & 0xFFFF? The target's expression is `((vol | flg) | x) & 0xFFFF`. The final andi is in the jal's delay slot. The andi is a separate insn (in the delay slot) — it's part of the arg's expansion at the call!

So the arg's expansion at the call produced: ori, or, andi. So YES — the whole second-arg expression was expanded AT THE CALL. So the arg was a raw expression in the RTL.

How?! In gcc 2.7's RTL for a call, the args are RTXs. After gimplification, the args should be REG pseudos...

UNLESS: gimplify_call_expr has this behavior: for an argument that is a "simple" expression, it can keep it in the call. Let me recall the actual gcc 2.7 code:

```c
  /* Perform the argument promotions ... */
  for (i = 0; i < nargs; i++)
    {
      tree arg = args[i];
      ...
      if (TREE_CODE (arg) == VAR_DECL && ...)
      ...
    }
```
Hmm, in gcc 2.7's gimplify_call_expr:
```c
	  /* Expand the last argument... */
```
I really don't remember.

BUT — here's the thing — the gimplifier creates temps, and then expand turns each temp's definition into RTL statements. The order of expansion = the order of the gimple statements. The temp for the whole arg expression is assigned BEFORE the call statement. So the arg's RTL ops (ori, or, andi) would be expanded at the temp's definition statement, i.e. BEFORE the call — with LUIDs before the li.

Hmm, unless gimple created the temp in the "call statement" itself. In the old gimplifier, temps assigned in the call's argument list... hmm, actually! gimplify_call_expr creates the temps and adds the assignments to `pre_p` (before the call) or `post_p` (after). If the assignment is added to post_p?? No.

Hmm, hold on, what if the args are evaluated AFTER the call in gimple's ordering? No.

OK, empirical again! Let me test the hypothesis "the arg expression is expanded at the call" by trying a source where the second arg is a SINGLE simple expression that gcc would keep in the call. E.g. if the second arg were `vol` (a simple var) — then no ori.

Alternatively, maybe the key is that in the target, `vol` is not a variable but a PSEUDO from the asm (the asm's output), and the expression `V | 0x3000`...

AH WAIT!!! THAT'S IT! The asm's output V is a PSEUDO (an RTL register), not a gimple variable! When gcc expands the asm statement, the output pseudo V is created. Then the gimple expression `vol | flg` where vol is the asm's output temp → hmm.

Hmm, but the gimple-level code is the same regardless.

Hmm, unless the asm's output pseudo is used DIRECTLY in the expression at the RTL level: the asm statement in gimple is `V = asm(...)` where V is a gimple temp. The expression `V | flg` is a separate gimple statement D.a = V | flg → a temp → expanded before the call.

I'm stuck on theory again. PRAGMATIC: let me try the wrapper/probe trick to see MY candidate's asm, then try variants until the tail matches. But even better: let me consider that maybe a completely different spelling of the arg would make gcc expand it at the call.

Hmm, hold on, hold on. Let me revisit: maybe the difference is NOT the arg expansion but the fact that in the TARGET, the ori is the ONLY op in the arg's expression besides the `or` and the `andi`...

Let me count the target's arg-setup insns: li $4 (a0), ori $5 (a1), or $5 (a1), andi $5 (a1, delay slot). So the a1 arg = ((vol|0x3000)|x)&0xFFFF → 3 ops (ori, or, andi). In cand03, the a1 arg = (vol|x)&0xFFFF → 2 ops (or, andi) + the separate ori statement.

So in the target, the arg expression has 3 ops; in cand03, 2 ops + 1 separate.

Now, WHY does the target's arg expression have the ori inside? Because in the target, the source is `((vol | flg) | x) & 0xFFFF` — with flg a variable! And in cand03, the source is `(vol | x) & 0xFFFF` (the ori was moved to a separate statement).

Hmm, so in the target, the arg expression `((vol | flg) | x) & 0xFFFF` contains the ori — and gcc expanded it AT THE CALL (3 ops with LUIDs after the li).

In cand01 (the original expression restored, launder removed): the arg expression was also `((vol | flg) | x) & 0xFFFF` → the same 3 ops at the call → the same order [li][ori][or][andi]! But cand01's diff showed the chain order problem (the mults swapped and the registers a3 vs a2), NOT the tail order. So cand01's tail was FINE (matching the target) — the problem was the vol chain's order/register.

So: if I can fix cand01's chain problem while keeping the original arg expression, I get 0!

So the two levers are independent:
- The tail order needs the ori inside the arg expression (the original source).
- The chain order needs the "boost" (an early consumer of vol) — which the launder provided.

In cand03 I got the chain right but the tail wrong. In cand01 the tail is right but the chain is wrong.

So I need BOTH: the original arg expression AND an early consumer of vol (other than the ori).

The early consumer must not add an instruction and must not change the value...

Hmm! What about the `x` variable? No.

What if the early consumer is a use of vol in a DEAD statement? Like `if (vol == 0x1234567) { }`? That's a real comparison (adds insns). ✗

What about `vol = vol;`? folded.

Hmm, what if the early consumer is vol's use in a store to a dead local? e.g. `dead = vol;` — a store (insn). ✗

Hmm. What about the ORDER of the chains: maybe I can get the vol chain first by other means — e.g. by making the x chain's result depend on vol? No.

Let me look at the chain difference more concretely. cand01's chain (mine):
```
	sra	a3,v0,0x10       ; ax (in $7)
	bgez	a3,...
	move	a1,a3
	negu	a1,a3
	lui	a2,0x6666       ; magic in $6
	ori	a2,a2,0x6667
	addiu	a0,a3,160      ; 160-|x| in $4
	mult	a0,a2           ; (160-|x|)*M
	mfhi	a3
	mult	v1,a2           ; 127*M?? 
	...
```
vs the target:
```
	sra	a6,v0,16
	bgez	a6,...
	move	a5,a6
	subu	a5,$0,a6
	li	a4,0x66660000    ; magic in $4
	ori	a4,a4,0x6667
	li	a2,0xa0
	subu	a2,a2,a5        ; 160-|x| in $6
	sll	a3,a2,7
	subu	a3,a3,a2        ; *127
	mult	a3,a4
	mfhi	a9
	#nop
	addu	a2,a6,160
	mult	a2,a4
	...
```
Differences: (1) the target computes (160-|x|)*127 explicitly (sll+subu) then mults by M; mine multiplies (160-|x|) by M directly — meaning in mine the *127 was folded into the magic? No... In mine: `addiu a0,a3,160` (160-|x|), `mult a0,a2` — that's (160-|x|)*M, not ((160-|x|)*127)*M. So mine's division was of (160-|x|) by ... hmm, and then `mult v1,a2` = 127*M.

So in mine, gcc distributed differently: vol = ((160-|x|)*127)/160 was transformed by gcc into 127 - (|x|*127)/160? and then... hmm, mine's chain has `mult a0,a2` = (160-|x|)*M and `mult v1,a2` = 127*M.

Hmm! In mine: the second division is by 20: (|x|+160)/20 → numerator (|x|+160) * M(20). But mine's chain doesn't show addu $2,$6,160 before a mult... Actually the diff's later part showed mine[69] = mult v1,a2 (v1 = 127?) and mine[74] = mfhi t1, mine[75] = sra v0,t1,0x6, mine[76] = subu a1,v0,v1 → the /160 division with the "add" correction (t1 = hi(127*M)>>6 - 127 = -127 hmm).

So mine computes: vol = 127 - ((160-|x|)*M >> 6) ... i.e. gcc rewrote (160-|x|)*127/160 = 127 - (|x|*127)/160 differently: hmm, mine's `mult a0,a2` = (160-|x|)*M and `mfhi a3` → hi((160-|x|)*M); `sra v0,a3,3`?? Hmm, mine[71] = sra v0,a3,0x3 → >>3; `subu a3,v0,a0` where a0 = sra a0,0x1f (sign) → so mine's vol = (hi((160-|x|)*M)>>3) - sign. That's a division by 8-ish??

I think mine computed a DIFFERENT algebraic form: maybe gcc transformed ((160-|x|)*127)/160 into (127*(160-|x|))/160 = 127 - 127*|x|/160 hmm.

Honestly, the difference in the chain comes from gcc's algebraic simplification of the division, which depends on the *value ranges* known at the point of optimization. The launder (asm) makes vol OPAQUE → gcc can't do the algebraic rewrite → it computes the division the "direct" way (mult of the scaled numerator). THAT's the launder's real role here: it prevents gcc from rewriting the division!

Wait, but the asm's output is only used in the ori; the division itself is computed before the asm. Hmm, but the asm makes the value opaque for the LATER optimization passes (cse/gcse/cse2) — the rewrite of the division happens in... hmm, the division expansion happens in expand (before the asm? no, the asm is after the division in the source, so the division is expanded first).

Hmm! So the division's expansion (mult by M) happens at the tree→RTL expansion of the vol statement, BEFORE the asm. So the asm can't change how the division is expanded!

Unless the rewrite happens in a later pass (cse2/gcse) — the "combining" of the multiply. gcc 2.7 has a pass that rewrites (x*c)/d? That's not typical.

Hmm, but the difference between cand01 and the target's chain is REAL: the target computes the *127 scaling explicitly (sll+subu) while cand01 folds the 127 into the magic division.

In cand01, the source is `vol = ((0xA0 - ax) * 0x7F) / 0xA0;` — identical in both! So the difference must come from a later optimization pass that the launder blocks. Which pass? The candidate passes: cse, gcse, cse2, jump, flow, loop, sched1, sched2, local_alloc, global_alloc, reload.

Hmm, the division expansion: gcc expands `(a*b)/c` where b=127, c=160 by... In gcc's expand, `expand_divmod` handles the division by a constant: it computes the magic and turns the division into a mult. The numerator (0xA0-ax)*0x7F is computed first (as a mult by 127 → sll+subu). Then the division by 160 → mult by M.

In cand01, gcc apparently rewrote it as: the division of (160-|x|)*127 by 160 → hmm, cand01's chain has `addiu a0,a3,160; mult a0,a2` — it multiplied (160-|x|) by M (0x66666667), which is the magic for 160. But then the numerator would be (160-|x|), not (160-|x|)*127. So the *127 got... hmm, the result `subu a1,v0,v1` with v1 = 127*M's high part...

Hmm, I bet gcc used the identity: (160-|x|)*127/160 = 127 - (|x|*127)/160 hmm, no: (160-x)*127/160 = 127 - 127x/160. So gcc computed 127x/160 = (127x)*M>>38 hmm.

Mine: `mult a0,a2` where a0 = 160-|x|... hmm, that's not 127x.

I give up on understanding the algebra. The empirical fact: cand01's chain differs from the target's; the launder blocks the rewrite. In gcc, the rewrite might be done by "combine" (the RTL combiner) — combine can rewrite `(x*c)/d` patterns! Or by cse2.

Since the asm (launder) sits between the division and its use, the value is opaque to the later passes → the division stays as expanded.

So to reproduce this lever-free, I need the division's VALUE to be opaque to the later passes — but without an asm!

How? By making the value's provenance "dirty": e.g., if vol is used in a way that prevents the combine/cse2 rewrite. The rewrite (whatever it is) presumably rewrites the RTL pattern (mult by 127; mult by M) into a shorter form. If the pattern isn't there (because the *127 multiply was already folded), no rewrite.

Hmm! So maybe: if I write the expression so that the *127 multiply is NOT a simple sll+subu pattern that combine can fold into the magic division... e.g. write it as `(0xA0 - ax) * 0x7F` (which is what it is) — combine turned `sll $3,$2,7; subu $3,$3,$2` (i.e. x*127) into a folded form (x*M).

So combine folded the *127 into the division! I.e., (x*127)/160 → (x*M)>>... using the identity 127/160 ≈ ... hmm, that changes the value! Unless it's exact: 127/160 = 0.79375. Hmm, the magic division for /160 computes floor((n*M)>>38) roughly with corrections. The compiler might have used a different magic for the combined n = x*127 case: the magic for /160 applied to (x*127)...

Actually gcc's combine has a "division by constant" simplification where it can fold a multiply into the magic constant: (x*127)/160 → since 127 and 160 are both constants, (x*127)/160 = x*127/160 = (x*127*M)>>38 → the magic for 127*... hmm, combine might compute a magic for the combined factor 127*M/2^k.

In the target, this fold did NOT happen (the sll+subu is still there). Why? Because the launder made the value opaque → combine couldn't rewrite it.

So the lever-free way to block combine: make the *127 multiply not a "simple" pattern. E.g., write the multiply differently so combine can't fold it: e.g. `(0xA0 - ax) * 0x7F` → what if I write `0x7F * (0xA0 - ax)` (operand order swapped)? Combine might still fold. What if I write it as a variable: `s32 m = 0x7F; vol = ((0xA0 - ax) * m) / 0xA0;`? Then the multiply is by a register → combine can't fold the constant into the magic → the sll+subu stays!

Hmm, but a multiply by a variable 0x7F: gcc would compute it as `mult` (not sll+subu) — 3 insns (mult, mflo, mfhi) — different from the target's sll+subu. Hmm, unless gcc knows m == 127 (constant propagation) → back to sll+subu.

Hmm. What if m is `volatile`? That adds a load. ✗

Hmm, what if the multiply is by a value that gcc knows is 127 but expressed in a way that blocks the fold? Like `x * 0x80 - x`? That changes the source form: `vol = ((0xA0 - ax) * 0x80 - (0xA0 - ax)) / 0xA0;` → gcc would fold it back to *127. Hmm.

OK, what about the OTHER part: maybe the difference is not combine but the fact that in the target, the value of `vol` is used by the ASM (an opaque use) — and combine's rewrite is triggered by the USE pattern.

Let me try a cleaner approach: since the target's chain computes ((160-|x|)*127) with sll+subu and then mults by M, maybe I can get that by making the *127 multiply un-foldable. Options:
(a) `s32 m = 0x7F;` — gcc constant-propagates → same.
(b) Compute the numerator in a variable that is used twice? no.

Hmm, what about: the division `(a * 127) / 160` — gcc's expand emits: t = a*127 (mult by 127 → sll+subu since 127 = 128-1); then the division by 160 → mult by M. Then combine might rewrite the whole thing. In the target, the rewrite didn't happen.

What if I split the expression across statements:
```
s32 num = (0xA0 - ax) * 0x7F;
vol = num / 0xA0;
```
Then combine sees: t = num*127 (a separate set) and the division of num. Would combine still fold? The pattern (set t (mult a 127)) + (set vol (div t 160)) — combine's division folding looks at the dividend's definition; if the dividend is a mult by 127, it can fold. Probably still folds.

Hmm, what if the dividend's multiply is by 127 but expressed as a MULT by a constant that gcc expands to `mult`? e.g. `num = (0xA0 - ax) * 0x7F;` — gcc expands *127 to sll+subu (since 127 = 2^7-1). If instead I write `num = (0xA0 - ax) * 0x7D + (0xA0 - ax) * 2;`?? silly.

Alternatively, block combine by making the numerator's value "used" elsewhere? Hmm.

OK, let me now think about what the launder blocks and find the SIMPLEST C equivalent. The launder makes `vol`'s value opaque AFTER the division statement. The passes that could rewrite the division are those that look at the division's operands: expand (already done), combine (RTL), cse2, gcse.

Combine's "divide by constant" folding: gcc's combine has `simplify_const_multiply`? Hmm.

Actually, maybe the rewrite isn't combine but gcc's expand itself: gcc's expand for `(x*127)/160` might do the "fold the multiply into the division" optimization at the tree level (in the front end's fold/build, or in `expand_divmod` which handles `DIV_EXPR` whose dividend is `MULT_EXPR` by a constant!).

YES: gcc's expand_divmod has code that handles the case where the dividend is a multiplication: it can compute the magic for the combined constant! Specifically, `expand_mult_const` / the "divide by constant with a multiplied dividend" optimization: gcc's expand.c has:

```c
  /* If we are dividing by a constant, see if we can simplify ... */
  if (TREE_CODE (dividend) == MULT_EXPR && ...)
```
Hmm, in gcc 2.7's expand_divmod:
```c
  /* If this is a division by a constant, ... */
  ...
      /* Try to simplify the dividend: if the dividend is a multiplication
	 by a constant, we can fold that constant into the magic number. */
```
Hmm, I recall gcc's `expand_mult_const` and the `sdiv_by_const`... There IS an optimization in gcc: for (x * c1) / c2, gcc computes a magic for c1/c2 when c1 and c2 are constants (this is the "magic number" for the ratio). This is done in expand_divmod:

```c
	  /* If the dividend is a multiplication by a constant, fold that
	     constant into the divisor's magic number.  */
```
That's exactly it! And this happens at expand time — BEFORE the asm! So the asm couldn't block it...

Hmm, but the target shows the *127 NOT folded. So in the target, gcc did NOT fold 127 into the magic. So the fold is not automatic — it depends on something.

Hmm! Maybe the fold happens only if the division's result is used in a certain way, or gcc's fold requires the dividend's mult to be by a constant AND the division to be signed...

Wait, maybe the difference is the VALUE RANGE: in the target, `ax` is opaque (the asm makes... no, ax is pinned to $5 by the `register` pin!). Hmm, ax is pinned: `register s32 ax __asm__("$5");` — so ax is in $5. In the target, ax is in $6 per the listing? Hmm, the listing shows `sra $6,$2,16` → ax in $6, and `move $5,$6; subu $5,$0,$6` → |ax| in $5.

But the pin says `register s32 ax __asm__("$5")` — so ax should be in $5! But the target has ax in $6 and |ax| in $5. Hmm, so the pin isn't respected? The pin declares `ax` as $5 — the listing shows `sra $6,$2,16` (ax = x sign-extended, in $6) then `move $5,$6` — so ax is copied to $5 (the |ax| computation). Hmm, so the "ax" variable (pinned $5) holds |ax|? Since `ax = x; if (x<0) ax = -x;` → ax = |x|. And the pin says ax is $5 ✓ — so $5 = |ax| ✓ and $6 = the sign-extended x.

OK so the pin is respected.

So in the target, `ax` (=|x|) is in $5 and the magic in $4.

Now, in cand01, mine had: sra a3 (=ax, but the pin says $5!?) — mine[56] = sra a3,v0,0x10 → so in cand01 the sign-extended x is in $7 and the pin was VIOLATED? Hmm, the pin is on `ax` (the variable), and in cand01 mine[59] = negu a1,a3 → |x| in $5 (a1) ✓. So the pin is respected (ax = |x| in $5) but the sign-extended x is in $7 in mine and $6 in the target.

OK. So the differences in cand01: the sign-extended x is in $7 vs $6, the magic in $6 vs $4, and the chain structure (the *127 folded vs not).

Hmm, the magic in $6 vs $4: in the target the magic is in $4 (a0) — but a0 is used for the call args later... The magic is dead after the divisions.

OK. Let me now try to think about which single change flips the *127 fold. Since the fold happens in expand (before the asm), the difference must be in the TREE-level form of the division. But the source is IDENTICAL in cand01 and the target (the only difference is the asm after the vol statement).

WAIT. Unless the fold is a LATER pass (combine, after the asm). Let me check gcc 2.7's combine.c: it has `simplify_const_multiply`... and there's the classic optimization in combine: "fold a multiply into a division's magic number" — hmm, combine works on RTL patterns: it can see `(set A (mult B 127))` followed by `(set C (div A 160))` — but in RTL, the division by a constant is already expanded into the magic mult sequence! So combine can't fold 127 into it.

Hmm, so the RTL for `((160-ax)*127)/160` after expand is:
```
(set t1 (mult (sub 160 ax) 127))   ; or sll+subu after combine
(set t2 (mult t1 M))
(set hi (mult_hi t1 M))  ; etc
```
And gcc's combine might simplify `(mult t1 M)` + `(mult_hi t1 M)` — no folding of 127.

Hmm, so where does the difference come from? In cand01 the chain was:
```
	addiu	a0,a3,160      ; 160-|x| in $4
	mult	a0,a2           ; (160-|x|) * M  ($6 = M)
```
So the RTL had `mult (160-|x|) M` — the *127 is MISSING! So the dividend was (160-|x|), not (160-|x|)*127. So the 127 WAS folded into the division → this IS a tree-level/expand-level rewrite!

And in the target: `sll $3,$2,7; subu $3,$3,$2; mult $3,$4` → the dividend is (160-|x|)*127 explicitly.

So in the target, gcc did NOT fold 127 into the magic; in cand01 it DID. The only difference is the asm after the statement!

=> The fold must happen in a LATER pass than expand — or the expand-time fold is conditional on something the asm affects.

AH, I bet I know: gcc's expand_divmod folds the multiply into the magic ONLY IF the multiply's result is used ONLY by the division. In the target, `vol` is used by the asm and then the ori — but the DIVIDEND (the *127 product) is used only by the division. Hmm.

Hmm, alternatively: gcc's expand_divmod folds the dividend's mult into the magic when the dividend is `x * c` with c a constant AND the division is signed AND ... the result is used in a context that...

Hmm, but the difference is the asm AFTER the division statement. How can that affect the division's expansion?!

Unless the fold happens in a LATER pass: e.g. gcse or cse2 or "combine" — but combine can't undo a magic expansion...

Hmm, wait. Maybe the fold is in the front end (tree-level) or in expand: gcc's expand_divmod:

```c
  /* If we are dividing by a constant, then we can optimize ... */
  ...
  /* If the dividend is a multiplication by a constant, then we can
     fold that constant into the magic number ... */
```
Hmm, but if that's in expand, the asm (which comes later in the source) can't affect it.

UNLESS the tree-level optimizer (tree-ssa-math-opts / fold) already rewrote `(x*127)/160` into a form with a single division by 160 — and THAT depends on... no, it's before the asm too.

Hmm, so how can the asm change the division's expansion?! It CAN'T. So the difference must be elsewhere.

Let me recheck: maybe cand01's chain difference is not about the *127 but about a different algebraic form. Let me carefully re-read cand01's diff:

```
replace mine[56:64] target[56:62]
  56  sra	a3,v0,0x10        | sra	a2,v0,0x10
  57  bgez	a3,930           | bgez	a2,930
  58  move	a1,a3            | move	a1,a2
  59  negu	a1,a3            | negu	a1,a2
  60  lui	a2,0x6666         | lui	a0,0x6666
  61  ori	a2,a2,0x6667      | ori	a0,a0,0x6667
  62  addiu	a0,a3,160       | --
  63  mult	a0,a2            | --
delete mine[66:67] target[64:64]
  66  mfhi	a3               | --
replace mine[69:73] target[66:71]
  69  mult	v1,a2            | mult	v1,a0
  70  sra	a0,a0,0x1f        | mfhi	t1
  71  sra	v0,a3,0x3         | addiu	v0,a2,160
  72  subu	a3,v0,a0         | nop
  73  --                    | mult	v0,a0
replace mine[74:77] target[72:78]
  74  mfhi	t1               | sra	a0,t1,0x6
  75  sra	v0,t1,0x6         | subu	a1,a0,v1
  76  subu	a1,v0,v1         | sra	v0,v0,0x1f
  77  --                    | mfhi	a2
  78  --                    | sra	v1,a2,0x3
  79  --                    | subu	a2,v1,v0
```
Note: the diff pairs are shifted by the unequal block sizes, so the pairing within a replace block is NOT reliable (difflib aligns positionally within the block, but the blocks' contents may be offset).

Given the target's true listing (from the .s dump) for the region 56-78:
```
56 sra $6,$2,16
57 bgez $6,$L58
58 move $5,$6
59 subu $5,$0,$6
60 li $4,0x66660000
61 ori $4,$4,0x6667
62 li $2,0xa0
63 subu $2,$2,$5
64 sll $3,$2,7
65 subu $3,$3,$2
66 mult $3,$4
67 mfhi $9
68 nop
69 addu $2,$6,160
70 mult $2,$4
71 sra $3,$3,31
72 sra $4,$9,6
73 subu $5,$4,$3
74 sra $2,$2,31
75 mfhi $6
76 nop
77 nop
78 sra $3,$6,3
79 subu $6,$3,$2
80 li $2,0x10
81 bne $6,$2,$L62
82 sll $6,$6,8
83 li $6,0xf
84 sll $6,$6,8
85 L62: li $4,0x93e
86 ori $5,$5,0x3000
87 or $5,$5,$6
88 jal
89 andi (delay)
```
Hmm, the .s has #nop lines which the masked diff might skip or count (the -z flag keeps nops). Anyway.

And cand03 (mine) matched the target for 56..82 except the tail. Great.

So cand03's chain = the target's chain. So cand03's `vol = vol | flg;` (a separate statement) somehow produced the target's chain (with the explicit *127).

Hmm! But cand03 also has the ori as a SEPARATE statement, which is what broke the tail. Hmm, but wait: cand03's ori statement is `vol = vol | flg;` where flg = 0x3000 → the ori is `ori $5,$5,0x3000`. And the target's ori is also `ori $5,$5,0x3000` — but in the target it's in the call's arg setup.

So: the chain difference (the *127 fold) is caused by the EXTRA USE of vol (the ori statement) — because with an extra use, gcc's expand/cse doesn't fold the 127?!

Hmm, that's plausible! The fold "127 into the magic" might require the dividend to have a single use. In the target, the dividend (160-|x|)*127 has ONE use (the division). In cand01, also one use. Hmm.

Ugh, whatever — empirically cand03 gives the right chain.

So the question remains: how to get the ori into the call's arg setup while keeping the chain right?

IDEA: What if the extra use of vol is NOT the ori but something else — e.g., a use of vol in a DEAD expression that gcc keeps?

Hmm, what if the extra use is `vol` used in the call's arg expression via a DIFFERENT spelling that doesn't change the emitted code? E.g.:

```
func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF);
```
plus an extra use of vol that emits nothing: e.g. `if (vol == vol) {}`? That emits a branch. ✗

What about using vol in a way that gcc folds away but counts as a use? E.g. `x = x ^ (vol - vol);` → folded to `x = x` → the use disappears. ✗ (the fold happens at the tree level, so the use is gone before expand).

Hmm! But the ORDER matters: the tree-level folding happens BEFORE expand. So any tree-level-foldable use won't survive.

What survives to the RTL and counts as a use but emits no instruction? A copy that combine doesn't remove. Hmm, combine removes reg-reg copies.

Hmm, what about a use in a "volatile" context? That emits a store. ✗

OK, so maybe the answer is: the extra use IS the ori, and I need to find a spelling where the ori is emitted as part of the call's arg setup but the chain is right.

What if the ori is in the arg expression AND the chain is right because of the extra use (the ori inside the expression counts as a use of vol, just like in cand03)?! In cand01, the arg expression was `((vol|flg)|x)&0xFFFF` — the ori inside — so vol HAS an extra use (the ori). Yet cand01's chain was wrong!

Hmm!! So cand01 (ori inside the expression) has vol with 2 uses (the ori) but the chain is wrong; cand03 (ori as a separate statement) has the chain right.

So the difference between cand01 and cand03 is not the number of uses but WHERE the ori is.

Hmm, so what makes the chain right in cand03? In cand03, the ori is a separate gimple statement → the vol chain's result has a use in a separate statement → hmm.

Ohh, maybe this: in cand03, the ori statement `vol = vol | flg` is a separate statement, so the vol value flows: division → vol → (ori) → vol. The gimple/RTL has vol with 2 sets. And the "fold 127 into the magic" rewrite might require the division's result to have a single use/set. In cand03, vol (the division result) has 1 use (the ori) — same as cand01.

I'm clearly unable to derive it. EMPIRICAL.

New plan: let me try combinations:
- cand09: the ori inside the arg expression (original) + an extra statement that uses vol in a way that emits an instruction but is otherwise harmless? That would add an insn. ✗

- cand10: `vol = vol | flg;` as a separate statement, but with the call written as `func_8002D4C8(0x93E, (vol | x) & 0xFFFF);` (cand03) — that's cand03 (score 2).

So I need to move the li before the ori in cand03.

Hmm, what if I change the arg order in the CALL: `func_8002D4C8(0x93E, ...)` → what if the constant arg is written as a variable that is a PARAMETER? no.

What if the constant 0x93E is spelled as a NEGATIVE constant or something that changes the li's form? The target has `li $4,0x93e` = `addiu $4,$0,0x93e`? In the .s it's `li $4,0x0000093e` → gcc's li expands to `addiu $4,$0,0x93e` (since 0x93e fits in the addiu immediate). Hmm, the .s shows `li` because the .s is pre-psx-finalization? The objdump showed... we don't know. Anyway.

OK, let me try: what if the first argument is written as `0x93E` but the SECOND arg expression is written to be evaluated FIRST in a way that... ugh.

NEW IDEA: what if I write the call as `func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF);` (ori inside) AND add the extra "use" of vol as a separate statement that is value-neutral but NOT tree-folded...

What about using vol in the `x` computation? Like `x = (x + 0xA0) / 0x14;` → hmm.

What about making the ori statement use a DIFFERENT variable so that the ori is inside the expression AND there's an extra statement:
```
{
    s32 flg = 0x3000;
    s32 v2 = vol;         /* extra use; a copy — folded? */
    func_8002D4C8(0x93E, ((v2 | flg) | x) & 0xFFFF);
}
```
cand04-ish (score 29) — the copy was folded, so the chain was wrong. Hmm, but cand04's chain was wrong in the SAME way as cand01? Yes (score 29 = same as cand01).

Hmm, so the copy didn't survive. What if the copy is not a copy but a real op with a value-preserving trick...

What about `s32 v2 = vol | 0;`? Folded at the tree level.

What about `s32 v2 = (s32)(u8)(vol & 0xFF);`? Adds insns.

Hmm, what if the extra use is in a place where the value doesn't matter but the instruction is the SAME as one the target has? Like...

AH WAIT. What about this: the target's chain has `sll $3,$2,7; subu $3,$3,$2` = (160-|x|)*127. What if I write the source as:

```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
```
vs
```
vol = (0xA0 - ax) * 0x7F / 0xA0;
```
(same thing).

What if I write it as `vol = ((0xA0 - ax) * 127) / 160;`? Same.

Hmm, what if the target's chain is what you get when the division is UNSIGNED or when the operands are known non-negative? E.g. `vol = ((u32)(0xA0 - ax) * 0x7F) / 0xA0;` — an unsigned division has a different magic (and no sign correction)! But the target's chain HAS the sign correction (sra $3,$3,31; subu $5,$4,$3). So it's signed.

OK, let me try the empirical route with a batch of variants around cand03's tail. Let me think about what could make the li come first...

IDEA!!! What if the constant argument is materialized by a SEPARATE STATEMENT that gcc keeps because it's used TWICE — no.

IDEA!!! What if I put the constant in a variable that's a PARAMETER-like thing...

IDEA!!! What about making the first argument a variable initialized at the declaration:
```
s32 c93e = 0x93E;   /* at the top of the function */
```
gcc's tree-level: D.c93e = 2366 (a constant) → propagated → folded. ✗

IDEA!!! What if the first argument is computed from something runtime-dependent that always yields 0x93E? E.g. `0x93E & 0xFFFF`? folded.

Hmm, what if the first arg is `2366` but written as a float? No.

Let me try yet another angle: maybe I can make the ori LATE by making it depend on the x-chain (which is scheduled later). E.g. `vol = vol | (flg & x)`? changes the value. Hmm: `vol | flg` where flg = 0x3000 constant...

What if the ori is `x = x | vol`?? Then the ori (as an "or" with a register) would depend on x. Hmm, the target has `ori $5,$5,0x3000` (immediate) — so the constant must be in the ori.

What if the source is `((vol | flg) | x)` where flg is a VARIABLE (not a constant)? Then the compiler would load flg from the stack (or keep it in a register) → `or $5,$5,$4` instead of `ori`. ✗ (the target has the immediate).

Hmm, so flg must be a constant 0x3000 in the source.

OK, let me try the probe approach: build the wrapper file to see my candidate's full asm, so I can iterate on the tail with full information. Actually the diff gives me enough for the tail (2 insns swapped).

Let me think about it ONE more time, but from the "what does the launder do to the call's arg setup" angle:

In the target, the arg setup is: li $4,0x93e; ori $5,$5,0x3000; or $5,$5,$6; andi $5,$5,0xffff.

The `ori $5,$5,0x3000` — in the target, $5 = vol (the division result). The ori consumes the ASM's output (coalesced with vol into $5).

The LUID order: the asm is a statement between the vol computation and the call. So the asm's LUID < the ori statement's LUID < the call's LUID. And the li (created at the call) has the call's LUID.

So the ori should be BEFORE the li by LUID. But the target has it after!

=> The scheduler reordered them by PRIORITY. The ori (downstream of the asm) has LOW priority; the li has HIGH priority (birth boost).

So: to reproduce, the ori must have low priority. In plain C, the ori's priority is high (it's a normal insn).

Hmm, so how do I make a plain-C op have a low priority?

In gcc's sched1, the priority is computed as:
```
priority = ... (the "waiting" chain)
```
Specifically, `sched1` computes `insn_priority` via `init_priority` and then `increase_priority` — the priority of an insn is boosted by the "dependency chain" lengths toward its successors. An insn whose successor is a "low priority" insn...

The ASM's priority is hardcoded to 1 (INSN_CODE < 0 → pri 1). Its successor (the ori) inherits... hmm, in gcc's sched, `priority` of an insn = the max over its successors of (successor priority - 1) or something. So the ori would inherit a low priority from the asm.

So to reproduce: the ori must have a low-priority predecessor. What plain-C insn has a low priority? An insn with a long dependency chain? No — a long chain makes the EARLY insns high priority (they're on the critical path).

Hmm, actually, low priority = scheduled late = "not urgent". An insn whose result is needed far in the future.

Hmm, alternatively: maybe the ASM's presence isn't about priority but about the "birth": the asm is a NEW SET of the value (V). The ori consumes V (2 sets of the value: vol and V). Hmm.

Honestly, maybe the priority difference comes from the fact that in the target, the ori is in the CALL GROUP (sched1 pulls the arg-setup insns into the call group and schedules them together, in the group's LUID order but with the group's own ordering rules). Within the call group, sched1 orders by LUID. So the li (later LUID) would be after the ori. ✗.

OK, radically different: maybe the ORDER in the target's .s is not the LUID order but the RESULT of sched2 (the second scheduling pass) or the "reorg" pass. The .set noreorder/nomacro markers indicate where the assembler fills delay slots. The li $4,0x93e is OUTSIDE the noreorder region → it's in the "normal" region.

Let me try a totally different tactic: BRUTE FORCE over source variants. Let me enumerate plausible variants and test them in parallel batches of 4:

V1: cand03 with the arg written as `(vol | x) & 0xFFFF` but the ori statement using `flg` declared as a non-constant? no.

V2: cand03 but with the constant as `0x93E` replaced by `(s32)0x93E`: no change.

V3: cand03 with the ori statement moved to just after the vol computation (cand02) but the arg written as `((vol | flg) | x)` — i.e. combine cand02's early ori with the original arg expression?? But then vol would be ORed twice: `vol = vol | 0x3000` then `(vol | 0x3000) | x` → the ori appears twice. ✗ (extra insn).

V4: cand03 with the `x = x << 8;` statement moved AFTER the flg block? Semantics: x is used in the call → the arg expression would use the pre-shift x. ✗

V5: cand03 with the `if (x == 0x10) { x = 0xF; }` block restructured as a ternary/if-else:
```
x = (x == 0x10) ? 0xF : x;
```
This changes the block structure → maybe the tail block's contents get scheduled differently!

V6: cand03 with the whole tail as:
```
{
    s32 flg = 0x3000;
    vol = vol | flg;
    x = x | vol;      /* hmm, changes the or's operands */
    func_8002D4C8(0x93E, x & 0xFFFF);
}
```
Hmm, the target's `or $5,$5,$6` = a1 |= a2 where a2 = x. If I write `x = x | vol`, the compiler would emit `or $2,$2,$5` (x in $2?) hmm, the register allocation would change.

V7: The "x = x << 8" moved into the flg block:
```
{
    s32 flg = 0x3000;
    x = x << 8;
    vol = vol | flg;
    func_8002D4C8(0x93E, (vol | x) & 0xFFFF);
}
```
This changes the block structure (the x<<8 might merge into the branch block).

Let me try V5 and V7 and a couple more. Each test ~30 s. Let me run 4 in parallel.

Hmm, wait. Before brute-forcing, let me reconsider ONE more time...

AH WAIT!!! I think I've got it! Look at the target's tail block L62:
```
$L62:
	li	$4,0x0000093e
	ori	$5,$5,0x3000
	or	$5,$5,$6
```
The `li $4,0x93e` — what if this is NOT the call's arg setup but rather... hmm, it IS (a0 = the first arg).

Hmm, but notice: the ori is `ori $5,$5,0x3000` — the DESTINATION is $5 = a1. And the `or $5,$5,$6` also writes $5. So a1 is written twice (ori, or) — consistent with the arg expression being expanded at the call (the arg's ops write a1 directly).

And the li writes $4 = a0.

In gcc, when a call's arg is expanded at the call, the ops write the arg register directly (a1). So the ori at the call = the arg expression expanded at the call ✓.

So in the target, the arg expression WAS expanded at the call. That happens when the RTL arg is a raw expression.

When does gimplification keep a raw expression as a call arg? In gcc 2.7's gimplify_call_expr:

```c
	  /* If the argument is a constant, ... */
	  ...
	  /* Perform the argument promotions.  */
	  ...
	  /* Expand the argument to a temporary if it is not a simple variable
	     or constant.  */
```
Hmm, but maybe: gimplify_call_expr has this code:

```c
	  if (TREE_CODE (arg) == VAR_DECL ...)
	    ...
	  else
	    {
	      ...
	      /* Save the computation into a temporary and use that.  */
	    }
```
So a compound expression → a temp. Hmm.

BUT!!! What if the arg expression is `(vol | flg) | x` where the temps vol and flg are gimple temps, and the whole thing was folded by the front end into a simpler form?

Hmm, what if the front end folds `((vol|flg)|x)&0xFFFF` into a single expression and gimplify_call_expr's "is_gimple_reg" check... The arg is an expression → a temp is created → the temp's assignment is a statement → expanded before the call.

So the ori should be a separate statement. ✗ contradiction with the target.

UNLESS: gimplify_call_expr puts the temp's assignment in the "pre" sequence BUT the call's arg is the temp's SSA name → in RTL, the temp is a pseudo → the ori is a separate RTL insn before the call. ✗.

So how does the target have the ori at the call?!

Hmm, unless the "call group" in sched1 pulled the ori into the group (sched1's "call group" logic moves the arg-setup insns adjacent to the call). YES! sched1 has a "call group" concept: it groups the call with its argument setup instructions (the ones that set the arg registers) and schedules them together, in the group's LUID order... hmm, but that would keep the LUID order [ori][li].

Hmm, but maybe within the group, sched1 reorders by priority: the li (birth-boosted, single-set) vs the ori (2 sets). Hmm! The birth boost: the li's dest $4/a0 is set once and used once → single-set → boosted. The ori's dest $5/a1 is set twice (ori, or) → not single-set → not boosted. So the li has a higher priority → scheduled first ✓✓✓

THAT'S IT! The birth boost explains it.

Now, in cand03, the ori is a separate statement whose dest is a variable (vol, a pseudo) — hmm, and then `vol` is used by the `or` (the arg's op). So the ori's dest pseudo is set once and used once → single-set → boosted → scheduled early ✓ (that's why the ori came first in cand03).

So: in cand03, the ori (writing a fresh pseudo) is single-set → boosted → early. In the target, the ori writes a1 directly (2 sets: ori + or) → not boosted → later.

So the lever: make the ori write a1 DIRECTLY (i.e., be part of the call's arg expansion) so that a1 has 2 sets → no boost → the li (single-set, boosted) comes first!

So I need the arg expression to be expanded at the call: `func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF)` — which is cand01's expression! But cand01's chain was wrong.

Hmm, so with cand01's expression, is the ori expanded at the call? cand01's diff showed the tail region matched (the diff for cand01 only showed the chain region 56-85 + the branch targets). Let me check: cand01's diff had blocks at 56-85 — the region 79-85 was in the "replace mine[78:82] target[79:83]" and "replace mine[84:85] target[85:86]" — hmm, cand01's diff showed:
```
replace mine[78:82] target[79:83]
  78  bne a3,v0,988 | bne a2,v0,98c
  79  sll a3,a3,0x8 | sll a2,a2,0x8
  80  li a3,15        | li a2,15
  81  sll a3,a3,0x8  | sll a2,a2,0x8
replace mine[84:85] target[85:86]
  84  or a1,a1,a3     | or a1,a1,a2
```
So in cand01 the region 79-85 matched the target's structure (the li 0x93e was NOT in the diff, meaning cand01's li was at the same index as the target's — the target's li is at 83 and cand01's at 83 too!). Wait, the diff showed "replace mine[84:85] target[85:86]" → mine[84] = or a1,a1,a3 ↔ target[85] = or a1,a1,a2. So the target[83] = li a0,2366 = mine[83] (equal!) ✓.

So in cand01 the TAIL IS CORRECT (the li before the ori)! Only the chain (56-82) differs.

So: cand01 = correct tail, wrong chain. cand03 = correct chain, wrong tail.

I need both. The difference between cand01 and cand03:
- cand01: `func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF);` — the ori is part of the arg expression → expanded at the call → a1 has 2 sets → no boost → the li first ✓. But the chain is wrong.
- cand03: `vol = vol | flg;` as a separate statement → the chain is right (the vol value has 2 sets: the division's result and the ori's) but the tail is wrong.

So the chain's correctness depends on vol having 2 sets (or an extra use). And the tail depends on the ori being expanded at the call.

So I need: vol to have 2 sets (an extra use) AND the ori to be at the call.

The extra use must be value-neutral and emit no instruction... OR the extra use could BE the ori at the call, with vol having 2 sets by another means!

Hmm: in cand01, vol (the division result) has ONE use (the ori). In cand03, vol has 2 sets (division → vol; ori → vol) and 1 use each.

What made the chain right in cand03? Perhaps: vol's value is used twice (the ori reads it once, and the arg reads vol again) — no, in cand03 vol has ONE use (the ori), and the new vol (the ori result) is used by the arg.

Hmm! So in cand03, the div result has 1 use, and the ori result has 1 use. In cand01, the div result has 1 use (the ori). Same!

So the difference isn't the use count. It's something else. Hmm.

What else differs? In cand03, vol (the variable) is REASSIGNED: `vol = vol | flg`. So the variable vol has 2 sets. In cand01, vol has 1 set.

And the chain's algebraic rewrite (the 127 folding) might be blocked when the variable has 2 sets! Hmm, why?

Hmm, alternatively the difference could be the ORDER of the ori statement vs the x-chain in the source:
- cand01: the ori is inside the arg expression (evaluated at the call, AFTER the x chain).
- cand03: the ori statement is after the x chain too (right before the call). Hmm, same relative order.

Hmm! But in cand03, the ori is a separate statement → the arg expression is `(vol | x) & 0xFFFF` → 2 ops (or, andi) + the ori statement.

Hmm, what if the chain difference is caused by the vol variable having 2 sets → gcc's "combine" can't rewrite the division because the division's result has a second set? That doesn't make sense either (the second set is AFTER the division).

Wait, maybe the rewrite is a TREE-level thing: gcc's tree optimizer (fold/build) rewrites `(x*127)/160`... and the tree optimizer works on SSA where vol has 2 defs → the division's use is in the ori statement... hmm, in cand01 the division's use is also in one place.

Hmm, hold on. Maybe the rewrite is: gcc's optimizer rewrites `((160-ax)*127)/160` into `127 - (ax*127)/160` (using the range info that 160-ax ≥ 0? no...). And this rewrite requires the division to be USED ONCE in a "simple" way.

In cand01: the division's result is used by the ori (inside the arg expression) — once.
In cand03: the division's result is used by the ori statement — once.

Same. Hmm!!

OK, let me look at the actual difference in the chains once more. In cand03 the chain matched the target. In cand01 it didn't. The ONLY source difference is the position/spelling of the ori.

Hmm, what if the difference is the ORDER OF THE x-CHAIN vs the ori statement in the source?
- cand03 source order: vol computation → x computation → x<<8 → ori statement → call.
- cand01 source order: vol computation → x computation → x<<8 → call (with the ori inside the call's arg).

In cand03, the ori statement is a separate gimple statement between the x<<8 and the call. In cand01, no statement there.

What if the presence of an extra statement between the x-chain and the call changes the SCHEDULING of the two chains? Hmm, in cand03 the ori statement depends on vol (the division) → it's a consumer of the vol chain → the vol chain gets a "consumer" that is EARLIER (before the call) → the vol chain's priority is boosted (its result is needed sooner) → the vol chain is scheduled EARLIER (before the x chain) ✓✓✓

That's the mechanism! The launder (asm) is likewise an early consumer of vol → boosting the vol chain.

And in cand01, vol's only consumer is the ori at the call (the last thing) → the vol chain isn't boosted → the x chain (needed by the branch) goes first.

So: I need an early consumer of vol that (a) doesn't add an instruction, and (b) doesn't change the arg expression's expansion (so the tail stays right).

Hmm! What if the early consumer is the ori statement AND the arg expression still expands at the call? The ori statement's result would be a new variable → the arg expression would read that variable → the arg's ops at the call would be `or` and `andi` (2 ops, with a1 written twice: the `or` and the `andi` — hmm, the andi writes a1 too!). Hmm, in cand03 the arg expression is `(vol|x)&0xFFFF` → the ops are `or $5,$5,$6` and `andi $5,$5,0xffff` → a1 is written twice → the or is NOT single-set → no boost → hmm, but the ori statement (writing the vol variable) IS single-set → boosted → scheduled early. That's cand03's problem: the ori (a separate statement) is boosted and lands early.

So in the target, the ori is part of the call group and is NOT boosted (a1 has 2+ sets).

Hmm, so I need the ori to be at the call AND vol to have an early consumer.

IDEA: what if the ori at the call is `ori $5,$5,0x3000` (writing a1 directly) and there's ANOTHER early consumer of vol that emits nothing?

An early consumer that emits nothing... hmm, what if the early consumer is the ori itself but the ori is at the call? Then vol's consumer is at the call (late). ✗

Hmm, what if the early consumer is a use of vol in the x computation? Like `x = (x + 0xA0) / 0x14;` — no vol.

What if vol is used in a comparison that's folded away? Tree-level folding removes it.

What if vol is used in a `volatile` store? Adds a store.

What if vol is used in an asm? That's the launder. ✗

Hmm, what if the early consumer is a use of vol in a statement whose RESULT is dead but which gcc keeps as a "set" with no consumer... e.g. `vol = vol;`? Tree-folded.

Hmm, what about a use of vol in a CONDITION that's provably true? Folded.

Hmm, what about a use of vol in a computation whose result is used but which produces the SAME code as another op? E.g.:

`x = (x + 0xA0) / 0x14;` — what if we change this to `x = (x + 0xA0 + (vol - vol)) / 0x14;`? Tree-folded (vol-vol = 0). ✗

What about `x = (x + 0xA0 + vol * 0) / 0x14;`? folded.

Hmm, what about using vol in a way that changes the code but is compensated? Like `x = (x + 0xA0) / 0x14;` → the /20 division.

Hmm hold on, what about this: use vol in the SECOND argument expression but in a way that the ori at the call is the only op... e.g.:

`func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF);` — the ori reads vol at the call (late consumer).

What if instead: `func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF);` AND the vol chain is boosted by the PINNED ax? Hmm, the pin on ax ($5) is already there.

Hmm, what if the boost could come from a different direction: the vol chain's priority depends on its consumer's priority and the "distance". What if the x chain's priority were lowered instead, so the vol chain comes first? E.g., in cand01, the x chain is boosted because its result feeds the branch. What if the branch were further away (e.g. the x computation moved later in the source)?

In cand01, the source order is: vol computation, then x computation, then the branch. The x chain is later in the source but its consumer (the branch) is early in the block.

What if I move the x computation AFTER the vol computation... it already is. What if I move the x computation to AFTER the call? No (x is used in the call).

Hmm, what if the x computation is moved to BEFORE the vol computation? Then the vol chain would be later in the source → the x chain first. ✗ (wrong direction).

What if the vol computation is moved to just before the call (later in the source)? Then the vol chain is late in the source but its consumer (the ori at the call) is right after → the vol chain would be scheduled late (after the x chain)? Hmm, but the chains are independent; the source order matters for the scheduler's tie-breaks.

Hmm! Interesting: what if I move the vol computation to just before the call:
```
x = (x + 0xA0) / 0x14;
if (x == 0x10) x = 0xF;
x = x << 8;
vol = ((0xA0 - ax) * 0x7F) / 0xA0;    /* moved down */
{ s32 flg = 0x3000; func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF); }
```
Then the vol chain is immediately before the call → its consumer is the ori at the call → the vol chain is "late" in the source but its result is needed immediately → it might get scheduled before the x chain? Hmm, the x chain's result is needed by the branch which is before the vol chain in the block.

Hmm, but the source order of the x computation matters for the block structure. Moving the vol computation after the x<<8 means the vol chain is in the same block as the call, scheduled just before it → AFTER the x chain. ✗ (we want the vol mult before the x mult).

OK so we need the vol chain EARLIER. Its consumer must be early.

Hmm, what if the vol computation is duplicated?? No.

Hmm, let me reconsider: what boosts the vol chain in the target? The asm. What else could boost it? In cand03, the ori statement (a separate statement, right after the x chain, before the call). Hmm, in cand03 the ori statement comes AFTER the x chain in the source, so it's not "early" in the source. Yet the vol chain was boosted relative to the x chain.

Hmm, is that really the mechanism? Alternatively: in cand03, the ori statement is a separate statement → the vol chain's result has a "user" that is a simple statement → gcc's scheduler computes the vol chain's priority as "needed by the ori which is needed by the call" — the same as the x chain's ("needed by the branch"). Hmm.

Hmm, but the x chain's consumer (the branch) is EARLIER in the block than the ori's consumer (the call) → the x chain is more urgent → x first. But cand03 gave the vol mult FIRST. So the vol chain was MORE urgent in cand03. Why?

Because in cand03, the vol chain's result (vol) is used by the ori statement, and the ori statement is a separate statement whose LUID is BEFORE the call's LUID. So the vol chain's result is needed at an earlier point (the ori statement) than the x chain's result (needed at the branch, which is... hmm, the branch is also before the call).

Ugh. Scheduling priorities in gcc are computed on the "critical path" through the block.

OK. PRAGMATIC BRUTE FORCE. Let me enumerate source variants that keep the ori INSIDE the arg expression (so the tail is right) and add an early consumer of vol in various forms:

E1: `vol = ((0xA0 - ax) * 0x7F) / 0xA0;` then later `x = x << 8;` and the call with the original expression. (cand01 — chain wrong)

E2: Add an early use of vol in the flg block BEFORE the call:
```
{
    s32 flg = 0x3000;
    s32 t = vol | flg;      /* early consumer: t is used in the arg expression */
    func_8002D4C8(0x93E, ((t | x) & 0xFFFF));
}
```
Hmm, this is cand03-like: the ori writes t (a fresh pseudo) → single-set → boosted → early. ✗ (probably like cand03).

Hmm! But wait: in cand03 the problem was the ori landing at 83 instead of 84. What if the ori lands at 83 but the LI lands at 82? Hmm, the li is created at the call, so it's after.

E3: What if the ori writes a1 directly by being part of the arg expression, and the EARLY consumer of vol is a *separate* op that writes a register which is then... hmm.

AH WAIT!!! IDEA: What if the early consumer of vol is the ORI ITSELF but placed in the source early, AND the arg expression uses the ori result... no.

Hmm, what about this: the early consumer is a use of vol in the SECOND argument expression, but the expression is arranged so that the ori is the FIRST op of the expression (writing a1) AND the expression is evaluated early because...

Hmm, hmm. What if the call is written with the arg expression such that gcc evaluates it BEFORE the constant? Like using a comma expression:
```
func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF);
```
The gimplifier creates a temp for the whole expression → the temp's assignment is a separate statement BEFORE the call → the ori is a separate statement. ✗ (cand01's tail was right though!).

Hmm!! Wait a moment. In cand01, the tail WAS right (the li before the ori). So in cand01, the ori IS at the call (not a separate statement). So the gimplifier did NOT create a separate temp for the arg expression — it expanded it at the call!

Why? Because gcc 2.7's gimplify_call_expr keeps the expression in the call if it's "simple enough"? Let's look at cand01's chain: the ori is at the call (the arg expanded at the call) ✓.

Hmm, so when does gcc expand the arg at the call vs. create a temp? Maybe: if the expression's operands are all "simple" (vars/constants) and the expression is a single operation, gcc might fold it into the call arg. The expression `((vol|flg)|x)&0xFFFF` has 3 ops → the gimplifier would create temps for each subexpression...

Hmm, but cand01's tail shows the ori, or, andi all writing a1 — that's the "expanded at the call" pattern.

Hmm, actually, WAIT. Maybe not: maybe in cand01 the ops are separate statements but the scheduler moved them all into the call group (adjacent to the call). The ORDER within the group: [li][ori][or][andi] — the li first. If the group is ordered by priority, the li (single-set, boosted) beats the ori (writing a1 which is also written by the or → 2 sets → not boosted).

And in cand03, the ori is a separate statement writing a FRESH pseudo (vol) → single-set → boosted → it beats the li → [ori][li][or].

Hmm, but in cand03 the ori is a separate statement — would it even be in the call group? It's adjacent in the block.

OK, so the KEY difference: in cand01, the ori writes a1 (a multi-set register) → not boosted → the li (boosted) comes first. In cand03, the ori writes a fresh single-set pseudo → boosted → comes first.

So I need: the ori to write a1 (be part of the arg expression) AND vol to have an early consumer.

What if the early consumer is a use of vol in the arg expression at a DIFFERENT position? Hmm.

What if there are TWO uses of vol in the arg expression: `((vol | flg) | x) & 0xFFFF` — one use.

Hmm, what if the expression is `((vol | flg) | (x + vol))`? No, changes the value.

Hmm. What if the early consumer of vol is the x-chain? Like `x = (x + 0xA0) / 0x14;` — what if x's computation were `x = ((x + 0xA0) / 0x14) ...` hmm.

Hmm, what if the vol computation's result is used by the PINNED ax? no.

WAIT!!! What about the `x` variable?! Look at the target's chain: the x division is `(x + 160)/20` and vol = ((160-|x|)*127)/160. Note that |x| = ax (pinned $5).

What if the vol computation used `x` in a way that... no.

Let me think about "early consumer" differently: maybe it's not about consumers but about the ORDER of the two chains' LUIDs. In the target, the vol chain's LUIDs are all before the x chain's LUIDs (the vol statement comes first in the source) AND the vol chain is boosted. In cand01, the vol chain's LUIDs come first but the x chain is scheduled first.

Hmm, so in cand01, why is the x chain first? Because the x chain's result is needed by the BRANCH (which is in the same block, right after the chains) while the vol chain's result is needed by the ori at the call (later). The scheduler prioritizes by "how soon is the result needed" → the x chain first.

In the target, the vol chain is first — because the asm (the consumer of vol) is EARLY (right after the vol computation) → the vol chain's result is needed sooner → the vol chain is prioritized ✓.

In cand03, the ori statement is right before the call — hmm, that's LATER than the branch. Yet the vol chain came first. Hmm, so my "consumer position" theory is shaky.

Hmm, unless in cand03 the vol chain is boosted because the ori statement is a separate statement with a SIMPLE structure...

Whatever the mechanism, let me use the empirical finding: cand03's chain = target's chain. cand01's tail = target's tail. I need a hybrid. The hybrid must have:
(1) vol with an extra use that lands the vol chain first (cand03's effect), and
(2) the ori as part of the call's arg expression writing a1 (cand01's effect).

Hybrid idea: use vol TWICE in the arg expression? Like `((vol | flg) | x) & 0xFFFF` — one use.

Hybrid idea 2: What if the ori writes a1 (arg expression) but the extra use of vol is in the x-chain region as a no-op that survives? E.g.:
```
x = (x + 0xA0) / 0x14;
if (x == 0x10) { x = 0xF; }
x = x << 8;
{
    s32 flg = 0x3000;
    func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF);
}
```
plus an early consumer of vol... e.g. what if `x = x << 8;` becomes `x = (x << 8) | (vol & 0);`? Folded.

Hybrid idea 3: What if the extra use of vol is in the FIRST argument?! `func_8002D4C8(0x93E | (vol & 0), ...)` — folded.

Hmm, what if the extra use is in a place where gcc keeps the op because it's not foldable but is FREE (reuses an existing instruction)? E.g. what if the ori is computed twice but the second one is CSE'd away at the RTL level (cse) but not at the tree level? Hmm! Tree-level folding would fold `vol | flg | flg`? no: `((vol|flg)|flg)` — tree folding might not simplify that (it's a valid simplification but gcc's fold might not do it). Then at the RTL level, cse would find the two `ori` ops identical and merge them → one instruction!

So: `func_8002D4C8(0x93E, ((vol | flg) | flg | x) & 0xFFFF);` — hmm, that changes the value? (vol|flg)|flg = vol|flg ✓ (idempotent). And the tree-level might not fold it, but the RTL cse would (the two ori ops are the same → one is redundant → cse removes it). But cse runs BEFORE the scheduler, so the result would be ONE ori writing a1 (2 sets) ✓ AND the tree-level sees vol with 2 uses → maybe the chain boost ✓.

Hmm, but the tree-level might fold (x|flg)|flg → x|flg (gcc's fold does handle OR with the same operand? `fold` has `x | x` → x for integers? Yes! fold_binary for BIT_IOR_EXPR: if the operands are identical, it's not folded (x|x != x in general for floats; for integers gcc's fold does NOT fold x|x → x because of the sign... hmm, actually gcc does fold `x|x` → x only in some cases).

Risky but worth a try!

Hmm, but hold on: does the tree-level "2 uses of vol" even matter? In cand03, vol has 2 SETS (the division and the ori) — that's what "2 sets" means. In the hybrid, vol would have 1 set and 2 uses. Different!

Hmm, what made cand03's chain right? Possibly the 2 SETS of vol (the variable being reassigned) → gcc's tree-level SSA has 2 definitions of vol → the division's result has 1 use, the ori has 1 use.

In the hybrid (ori inside the arg expression), vol has 1 set, 1 use.

Hmm, so the hybrid's vol has 1 set. Then the chain might be wrong.

OK, let me try to think about what the 2 SETS do for the chain. With 2 sets, gcc's tree optimizer can't propagate the division's result into the ori (it must, actually — the ori reads the division's result directly). Hmm.

Alternatively, maybe the chain difference is caused by the "combine" pass being able to rewrite the division when the result has a single use! With 2 uses (or 2 sets?), the rewrite is blocked.

In cand01: vol (the division result) has 1 use (the ori inside the arg expression). In cand03: also 1 use (the ori statement). Hmm!! Same.

WAIT. Unless in cand01 the division's result has 1 use but in cand03... hmm.

Hmm, hold on. Let me reconsider: maybe in cand01 the difference isn't about vol at all, but about the fact that in cand01 the arg expression `((vol|flg)|x)&0xFFFF` is a single expression, so gcc's tree optimizer sees the whole thing and rewrites the division algebraically (e.g. distributing the multiply). In cand03, the ori statement separates vol from the arg expression → the tree optimizer can't see the division's result flowing into the arg expression in the same way?

Hmm, in cand03 the division's result flows into the ori statement whose result flows into the arg expression. Also a single flow.

OK, ENOUGH THEORY. Time check: I'm ~50 minutes into item 2 (started ~18:45, now?). The rule: past 30 min → record a wall. Hmm! But the developer said: "a WALL needs at least 20 min and at least 30 scored tries on that item; fewer is not an attempt, so keep trying new moves until both hold (stop at 30 min)". So I should keep trying until 30 min (of wall time for the item) — hmm, "stop at 30 min" means the budget is 30 min per item. But the rule also says a WALL needs ≥20 min AND ≥30 scored tries.

Hmm, so for item 2: I should do ≥30 scored tries if I'm going to record a WALL, and the wall time should be ≥20 min, stopping at 30 min.

But wait — the budget: "Budget 20-30 min wall per item (date at start/end); past 30 min stop and record a wall."

So: 30 tries in 30 minutes = 1 try/minute. Each --try takes ~20-30 s. So ~60 tries in 30 min. OK, feasible if I batch them in parallel.

But also: I should not spend 30 minutes on item 2 if I have 6 more items. Hmm, the developer's rule is explicit: a WALL needs ≥20 min and ≥30 tries. If I get a MATCH earlier, great.

Let me plan: for item 2, try the hybrid variants. If no MATCH by ~20-30 min with 30+ tries, record a WALL.

Let me be smart about the variants. Key hypothesis: I need vol to have 2 sets (a reassignment) AND the ori to be part of the arg expression writing a1.

Hybrid: assign the ori result to a variable that is then used in the arg expression, but where the ori writes a1 directly?? Impossible: if the ori writes a temp, the arg's ops write a1.

Hmm, unless: `func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF)` where the ori is in the expression, AND an extra statement `vol = vol | 0;`?? Folded.

Hmm, what about: the extra statement could be a REASSIGNMENT of vol that is value-neutral but not folded:
- `vol = vol | 0x3000;` — changes the value (but then the arg expression's ori would be redundant → the tree optimizer might fold `(vol|0x3000)|0x3000` → `vol|0x3000` → so the arg's ori disappears → the arg's ops = [or, andi] → and the separate ori writes the vol temp (single-set, boosted) → cand03-like. ✗

- `vol = vol & 0xFFFFFFFF;` → folded.

Hmm, what about a reassignment that the tree optimizer keeps but the RTL coalesces:
`vol = vol | flg;` where flg = 0 — folded.

What about a reassignment with a DIFFERENT variable:
```
s32 flg = 0x3000;
vol = vol | flg;       /* 2nd set */
func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF);   /* the ori is redundant but maybe not folded */
```
The tree optimizer: (vol|flg)|flg — does gcc's fold simplify x|y|y → x|y? gcc's fold_binary for BIT_IOR_EXPR: it checks for identical operands → `if (operand_equal_p (arg1, arg2, 0)) return arg1`? I believe gcc's fold DOES have that for BIT_IOR_EXPR/AND/XOR (for integers, x|x = x). Yes! In fold_binary:
```c
    case BIT_IOR_EXPR:
    case BIT_AND_EXPR:
    case BIT_XOR_EXPR:
      /* Handle (a OP a) as a.  */
      if (operand_equal_p (arg1, arg2, 0))
	return arg1;
```
Yes, that's real. So it folds. ✗

OK, so how about the OTHER direction: make the ori in the arg expression write a1 AND give vol a 2nd set via a different variable that the arg expression uses:
```
{
    s32 flg = 0x3000;
    s32 t = vol | flg;    /* 2nd set of t, but vol still has 1 set */
    func_8002D4C8(0x93E, ((t | x) & 0xFFFF));
}
```
= cand03-like (the ori writes t → single-set → boosted). ✗

Hmm, so the fundamental tension: the ori must write a1 (multi-set) to be late, but then it's the only consumer of vol.

Hmm, unless the ori writes a1 AND there are 2 uses of vol in the expression:
`((vol | flg) | (vol | x))`? changes the value? (vol|flg)|(vol|x) = vol|flg|x ✓ SAME VALUE! And the tree optimizer: does it simplify? (a|b)|(a|c) → a|(b|c)? gcc's fold might do that (there's an associativity rule for OR). Hmm, gcc's fold does have "simplify (a|b)|(a|c)"? I don't think so for integers (it's valid: a|b|a|c = a|b|c ✓). gcc's fold might not.

But if it doesn't fold, the RTL would have 2 ori ops → 2 instructions ✗ (the target has 1).

Hmm, and cse might merge them? They're not identical (one is vol|flg, the other vol|x) → no merge. ✗

OK, let me flip the approach: what if I keep cand03 (the separate ori statement) and try to make the LI come first by other means? The li is `li $4,0x93e` — a0's setup. In cand03, the ori (single-set, boosted) comes before it.

What if the ori's dest is NOT single-set? In cand03, the ori writes `vol` (the variable) → the vol pseudo is set by the ori only (the division wrote a different pseudo, the div result) → so the ori IS single-set → boosted.

What if the ori wrote a pseudo with 2 sets? E.g. if the ori wrote the SAME register as something else... e.g. if the ori wrote `x`?! Like `x = x | vol`?? Hmm, then the ori would write x (which is also written by the x-chain → multi-set → not boosted → late!). But the target's ori is `ori $5,$5,0x3000` (a1 = vol|0x3000) — the dest is a1, not x.

Hmm, but what if the ori writes a variable that has 2 sets? E.g.:
```
s32 flg = 0x3000;
vol = vol | flg;    /* vol's 2nd set */
```
vol's pseudo (the ori result) is single-set. But the VARIABLE vol now has 2 sets (the division's result + the ori). Hmm, at the RTL level, the division's result is a different pseudo than vol's assignment? In gcc's RTL, `vol = division` is a copy (the div result pseudo → vol pseudo) unless coalesced. So the ori writes the vol pseudo, which is also written by the division's copy → 2 sets → NOT single-set → NOT boosted → LATE!

Hmm! But then cand03's ori should have been late... but it was early (at 83, before the li at 84). Hmm, but "late" relative to what? The li (a0's setup) — the li is also possibly multi-set? a0 is set by the li only → single-set → boosted → should be FIRST. But in cand03 the li came second!

Hmm, so the li was NOT boosted, or the ori was boosted.

Ugh.

Let me get empirical data instead of theorizing: let me look at cand03's actual asm (via the wrapper probe) and compare with the target's. That will show me the block structure and maybe the scheduling details. Actually the diff already showed the block structure is the same.

Time is ticking. Let me consider the practical path: I've spent ~55 min on item 2 (including the reading). The budget says 20-30 min per item; I'm over. But the developer's rule says a WALL needs ≥30 tries and ≥20 min. Hmm, and "stop at 30 min".

Hmm, tension: the brief says "Budget 20-30 min wall per item (date at start/end); past 30 min stop and record a wall." I've exceeded 30 min on item 2 already (started ~18:45, now ~19:35?). Let me check the time.

Let me check the time and decide. If I'm over 30 min for item 2, I should record a WALL — but the rule says a WALL needs ≥30 scored tries. I've done 5 tries (cand01-04 + orig). Hmm, I need 30 tries to record a wall. That's another ~15 min. Hmm.

Hmm, but honestly: the more valuable outcome is a MATCH. Let me spend a bit more on item 2 with a focused set of variants (targeting the tail order), and if it doesn't crack, do enough tries to record a legitimate wall.

Let me check the time first.

Actually, let me reconsider the priority issue once more, because I have a new idea:

What if the li (a0's setup) is boosted in the target because a0 is set ONLY by the li — and in cand03, a0 is ALSO... no, in cand03 a0 is set only by the li too.

Hmm, unless in cand03 the li is NOT the arg setup but something else. Hmm, `func_8002D4C8(0x93E, ...)` → a0 = 0x93e.

Hmm, so in both cases a0 = the li (single-set).

So the difference must be the ori's priority. In the target, the ori (writing a1, 2 sets: ori + or... plus the andi = 3 sets) → not single-set → no boost → late ✓. In cand03, the ori writes vol (single-set? the vol pseudo is written by the division's copy AND the ori → 2 sets → not single-set → no boost → should be late ✗).

Contradiction again. So the boost theory fails for cand03.

Alternative: the ori in cand03 is a SEPARATE STATEMENT, and sched1 handles separate statements differently: it's scheduled as part of the block's normal instruction stream (not the call group), so it can be placed anywhere. The call group = [li][or][andi][jal]. Hmm, but the diff showed the ori at 83, the li at 84, the or at 85 — so the ori is BEFORE the call group.

If the ori were scheduled as part of the normal stream, it would be placed as early as possible (its priority is high because it's ready) → before the call group ✓ (cand03).

In the target, the ori is INSIDE the call group (because it's part of the arg expression) → the group is [li][ori][or][andi][jal] → ordered by LUID within the group: li (LUID at the call... hmm, the li is created during the call's expansion, and the ori's LUID is earlier).

Hmm, if the group is ordered by LUID, the ori would come first. ✗

OK, the group order might be by priority: [li (boosted)] then [ori] then [or] then [andi]. ✓ That works if the li is boosted and the ori isn't.

And in cand03, the ori is outside the group → placed before the group ✓.

So the mechanism holds IF the ori is in the call group (arg expression) and the li is boosted.

So the requirement is: the ori must be part of the arg expression (the original source), and the chain must still be right.

So the question reduces to: how to make the chain right while keeping the arg expression intact?

The chain difference: the target computes (160-|x|)*127 explicitly (sll+subu) then mults by M; cand01 folds the 127 into the division.

What causes the fold? Let me hypothesize it's the TREE-level optimizer (fold/build) or gcc's expand: for `(x*127)/160`, gcc's expand_divmod can fold the multiply into the magic: it computes a magic for the division of (x*127) by 160 using the "multiply by 127 then divide" identity: since 127 and 160 are both constants, (x*127)/160 = x*(127/160) — but that's not exact for integers... EXCEPT gcc can use a different magic: the division of x*127 by 160 = floor(x*127/160) — with a magic for 127/160 (i.e., M' = ceil(2^k * 127/160) etc.). YES: gcc's expand_divmod does exactly this: "If the dividend is a multiplication by a constant, we can use a magic number for the combined operation."

So gcc expanded the division as: magic M' for the ratio 127/160 applied directly to x.

And the target did NOT do that — it computed the numerator explicitly. WHY?

Because gcc's expand_divmod only does the "fold the multiply into the magic" when the multiply is by a constant AND the division is signed AND... the multiply's result is not used elsewhere. In both cases it's used once.

Hmm! BUT: maybe gcc's expand_divmod does this fold only when the multiplication is `x * 127` where x is the dividend — and the "0x7F" in the source is `(0xA0 - ax) * 0x7F` → MULT_EXPR(MINUS(0xA0, ax), 0x7F) → the dividend is a MULT by a constant → the fold applies.

So why doesn't it apply in the target?!

AH, maybe because of the PINNED `ax`! The pin `register s32 ax __asm__("$5")` — hmm, that's in both.

Hmm, what if the difference is that in the target, the dividend's multiply is NOT by a constant at the tree level? In the target's asm: `sll $3,$2,7; subu $3,$3,$2` = x*127 — the multiply was expanded as sll+subu, i.e. gcc did NOT fold it into the magic.

Hmm, so in the target, the multiply by 127 was expanded normally (sll+subu) and the division by 160 used the standard magic M = 0x66666667 (for /160) — the "combined" magic for 127/160 would be different (e.g. 0x517CC1B7 or similar).

In cand01, the magic was 0x66666667 too! (lui 0x6666 / ori 0x6667). Hmm! So cand01 also used M = 0x66666667 = the magic for /160, NOT a combined magic for 127/160.

Hmm! So the difference isn't the magic constant. Let me re-examine cand01's chain:
```
60 lui a2,0x6666      ; M
61 ori a2,a2,0x6667
62 addiu a0,a3,160    ; 160 - |x|  (in $4)
63 mult a0,a2         ; (160-|x|) * M
64 ?                  (equal to target[62])
65 ?                  (equal to target[63])
66 mfhi a3            (deleted)
```
Hmm, so mine: mult (160-|x|)*M. And the target: mult ((160-|x|)*127)*M. So in mine, the dividend was NOT multiplied by 127 → so gcc folded the 127 into... the MAGIC? But the magic is the same 0x66666667.

Hmm, how can (x*127)/160 be computed with the magic for /160 applied to x? Because 127*x/160 = x*127/160; using M=0x66666667 (magic for /160): hi(x*M)>>6 ≈ x/160. That's not x*127/160.

Unless the extra ops (the equal region) do something. Mine's chain:
```
mult a0,a2      ; (160-|x|)*M
[64] mflo a0?    (equal to target[62] = li $2,0xa0 — hmm, "li $2,0xa0" can't be equal to mine[64])
```
Hmm, the equal region mapping: mine[64],[65] ↔ target[62],[63] = [li $2,0xa0; subu $2,$2,$5]. So mine[64] = li $2,0xa0 and mine[65] = subu $2,$2,$5 (the same insns but in different registers: mine uses $2 for 160-|x| and $5 for |x|; the target uses $6 and $5).

Hmm interesting: the target has `li $2,0xa0; subu $2,$2,$5` at 62-63 and `sll $3,$2,7; subu $3,$3,$2` at 64-65. And mine[64],[65] = those same two insns (li $2,0xa0; subu $2,$2,$5).

So mine's chain: [lui a2][ori a2][addiu a0,a3,160][mult a0,a2][li $2,0xa0][subu $2,$2,$5][mfhi a3 (deleted)]...

So mine computed BOTH (160-|x|) in $4 (for the mult) AND (160-|x|) in $2 (for the andi?) — hmm, mine[64],[65] = li $2,0xa0; subu $2,$2,$5 = a SECOND copy of (160-|x|)!

So in mine, the numerator (160-|x|) is computed twice: once in $4 (for the mult) and once in $2. And in the target, the numerator is computed once in $2 and then scaled by 127 in $3.

So mine's division is of (160-|x|) [not scaled] — where did the 127 go?!

`mult a0,a2` = (160-|x|) * M, then `mfhi a3` → hi. Then mine[69] = mult v1,a2 (v1 = 127? * M) and mine[70] = sra a0,a0,0x1f (sign of the low part), mine[71] = sra v0,a3,0x3, mine[72] = subu a3,v0,a0, mine[74] = mfhi t1, mine[75] = sra v0,t1,0x6, mine[76] = subu a1,v0,v1.

So mine: a1 = ((hi(127*M)>>6) - 127) ... and the vol = (hi((160-|x|)*M)>>3) - sign.

Hmm, so mine computes vol = ((160-|x|)*M >> 35) - sign — that's a division by 2^35/M ≈ ... M = 0x66666667 → 2^38/M ≈ 160? Let me compute: the standard magic division: q = hi(n*M) >> s where M = ceil(2^(32+s)/d). For d=160: M = 0x66666667, s=6 → hi(n*M)>>6.

Mine: hi((160-|x|)*M)>>3 — that's s=3, which corresponds to d = 2^35/M = 34359738368/1717986919 = 20.0 → d=20!! So mine computed the division by 20, not 160!

So in mine, the expression became: vol = something/20 and x = something/20? Hmm, mine's first mult is of (160-|x|) with M (s=3 → /20).

So mine's chain computes: (160-|x|)/20?? and the target's chain computes ((160-|x|)*127)/160 AND (|x|+160)/20.

Hmm, so in mine, the *127 and the /160 were combined into a /20-ish computation?! That doesn't make sense unless gcc rewrote the whole expression.

AH, I bet I know what happened: gcc's tree optimizer rewrote `((0xA0 - ax) * 0x7F) / 0xA0` algebraically using the range of ax! E.g., if ax ∈ [0, 0x9F] (from the earlier check `(L.sxy[0]+0x9F)&0xFFFF < 0x13F`), hmm.

Actually, the standard identity: (160 - ax)*127/160 = 127 - ax*127/160 = 127 - (ax*127)/160. Hmm, that's still /160.

But mine's chain has a /20 division (s=3). Hmm, and the x computation is (x+160)/20 (s=5 → magic for /20 is 0x66666667 with s=5? Let me verify: 2^37/20 = 1717986918.4 → M = 0x66666667, s = 5. And for /160: 2^38/160 = 274877906944/160 = 1717986918.4 → M = 0x66666667, s = 6.

The target's chain: `sra $4,$9,6` → >>6 → the /160 division ✓ (with the "add" correction). And `sra $3,$6,3` → >>3?? for the second division. Hmm, >>3 would be d = 2^35/M = 20.0 with s=3: 2^(32+3)/20 = 2^35/20 = 1717986918.4 → M = 0x66666667, s=3 ✓. So the target's second division uses s=3 (i.e., the magic for /20 but with a smaller shift — gcc's "add" variant uses s = log2 stuff).

And mine's FIRST mult (160-|x|)*M with s=3 → also a /20-style division. So in mine, the FIRST division (which should be /160 with s=6) became a /20-style computation (s=3) of (160-|x|)!

So mine computed (160-|x|)/20?? and the target computed (160-|x|)*127/160.

Hmm! So in mine, the expression ((0xA0-ax)*0x7F)/0xA0 was rewritten to involve a /20 division?! That means gcc REWROTE the expression using the relation between 127 and 160?? Hmm: 127/160 = 0.79375.

OHHH!!! I GET IT! gcc rewrote `(160 - ax) * 127 / 160` as `127 - ax * 127 / 160`... no. Hmm, how about: gcc rewrote it as `(160-ax)*127/160` = `((160-ax)*127)>>7 / (160>>7)`?? no.

Hmm, alternatively: maybe gcc's rewrite uses the fact that x is an integer and 127 = 160-33? Hmm.

Wait, maybe I have the mapping wrong. Let me re-map mine's chain to the target's more carefully using the equal regions:

diff opcodes (cand01):
1. replace mine[56:64] target[56:62]   → mine 56-63 (8), target 56-61 (6)
2. equal mine[64:66] target[62:64]
3. delete mine[66:67] target[64:64]
4. equal mine[67:69] target[64:66]
5. replace mine[69:73] target[66:71]
6. replace mine[74:77] target[72:78]
7. replace mine[78:82] target[79:83]
8. replace mine[84:85] target[85:86]

So: target[62],[63] = mine[64],[65]; target[64],[65] = mine[67],[68]; target[66..70] ↔ mine[69..72]; target[72..77] ↔ mine[74..76]; target[79..82] ↔ mine[78..81]; target[85] ↔ mine[84].

Target (from the .s):
56 sra $6,$2,16
57 bgez $6
58 move $5,$6
59 subu $5,$0,$6
60 li $4,0x66660000
61 ori $4,$4,0x6667
62 li $2,0xa0
63 subu $2,$2,$5
64 sll $3,$2,7
65 subu $3,$3,$2
66 mult $3,$4
67 mfhi $9
68 nop
69 addu $2,$6,160
70 mult $2,$4
71 sra $3,$3,31
72 sra $4,$9,6
73 subu $5,$4,$3
74 sra $2,$2,31
75 mfhi $6
76 nop
77 nop
78 sra $3,$6,3
79 subu $6,$3,$2
80 li $2,0x10
81 bne $6,$2,$L62
82 sll $6,$6,8
83 li $6,0xf
84 sll $6,$6,8
85 li $4,0x93e
86 ori $5,$5,0x3000
87 or $5,$5,$6
88 jal
89 andi

So target[66] = mult $3,$4 (the vol numerator * M) ↔ mine[69] = mult v1,a2. Hmm, so mine's mult v1,a2 corresponds to the target's mult $3,$4 — and mine's v1 = the vol numerator (160-|x|)*127 in mine?! But mine[62] = addiu a0,a3,160 (160-|x| in $4) and mine[63] = mult a0,a2 → that's a DIFFERENT mult (the /20 one for x?).

Ugh, the diff alignment is confusing. Let me just say: mine's chain has an extra mult and a different arrangement.

I'll stop analyzing. PRAGMATIC PLAN for item 2:

Try a set of variants combining the two effects:
(a) The arg expression keeps the ori inside (cand01's tail) + vol has a 2nd set via a statement that gcc keeps.

Which statement keeps a 2nd set of vol without adding an instruction? What if the 2nd set is `vol = vol | flg;` AND the arg expression uses the ORIGINAL vol... but then the value changes (the arg would OR 0x3000 twice → the tree optimizer folds it → the arg's ori disappears) ✗.

Hmm, what if the 2nd set is on a DIFFERENT variable that the arg expression uses in a value-preserving way:
```
{
    s32 flg = 0x3000;
    s32 t = vol;             /* copy — folded */
    ...
}
```
✗ (cand04).

Hmm, what if the copy is NOT folded because it's a "s16" copy (HImode)? E.g. `s16 v2 = vol;` — but that truncates the value → the arg would need the s32 value.

Hmm, what about `u16 v2 = (u16)vol;` and then `vol` used... no.

OK, ALTERNATIVE IDEA: maybe I can get the chain right by a completely different route: change the SOURCE expression for vol so that gcc produces the target's chain directly, without needing the launder's boost!

The target's chain: (160-|x|)*127 computed explicitly, then /160 with the magic.

In cand01, gcc folded the 127 into the magic (producing a different chain). Hmm, actually did it? The magic was the same 0x66666667 in both. So no folding of 127 into the magic.

So what else differs?! Let me look at the target's chain again:
- `li $2,0xa0; subu $2,$2,$5` → 160-|x| in $2
- `sll $3,$2,7; subu $3,$3,$2` → *127 in $3
- `mult $3,$4; mfhi $9` → hi((160-|x|)*127*M) in $9
- `sra $4,$9,6; subu $5,$4,$3` where $3 = sra $3,$3,31 (sign of the low product) → $5 = (hi>>6) - sign = the /160 division ✓ → vol in $5 ✓ (and $5 is the pinned ax register! coincidence? ax = |x| was in $5 earlier... hmm, the pin says ax is $5, and the vol ends up in $5. So the vol REUSES ax's register → ax is dead by then ✓.)

- Then the second division: `addu $2,$6,160` ($6 = the sign-extended x) → x+160 in $2; `mult $2,$4`; `mfhi $6`; `sra $3,$6,3`; `subu $6,$3,$2` where $2 = sra $2,$2,31 → x = (hi((x+160)*M)>>3) - sign.

Hmm, >>3 for /20: the magic for /20 with the "add" variant: gcc uses M = 0x66666667 and s = 3?? Let me verify: for d=20, gcc's magic with the add indicator: M = ceil(2^(32+3)/20) = ceil(34359738368/20) = 1717986918.4 → 1717986919 = 0x66666667, s=3 ✓. Yes! (2^35/20 = 1717986918.4.) And for d=160: 2^(32+6)/160 = 274877906944/160 = 1717986918.4 → same M, s=6 ✓. Great, consistent.

So the target: vol = ((160-|x|)*127)/160 via M with s=6, and x = (x+160)/20 via M with s=3.

Now cand01's chain: mine[62] = addiu a0,a3,160 → (160-|x|) in $4; mine[63] = mult a0,a2 → (160-|x|)*M; mine[64],[65] = li $2,0xa0; subu $2,$2,$5 → (160-|x|) again in $2; mine[66] = mfhi a3 (deleted); mine[67],[68] = ? (equal to target[64],[65] = sll $3,$2,7; subu $3,$3,$2) → so mine[67] = sll $3,$2,7 and mine[68] = subu $3,$3,$2 (the *127 in $3) — WAIT, that means mine ALSO has the sll+subu (*127)!

Hold on: the equal region "mine[67:69] target[64:66]" means mine[67] = target[64] = sll $3,$2,7 and mine[68] = target[65] = subu $3,$3,$2. But the registers might differ (the masked comparison masks register fields? NO — the masked diff keeps register fields! `shape()` zeroes them but `masked_word` keeps the word with only the immediate masked. So a register difference WOULD show as a difference. Since these are "equal", the registers match: mine[67] = sll $3,$2,7 and mine[68] = subu $3,$3,$2.

So cand01's chain also has the *127 computed explicitly! Then what differs?

mine:
56 sra $7,$2,16       (ax sign-extended in $7)
57 bgez $7
58 move $5,$7        (|x| in $5 — the pin ✓)
59 negu $5,$7
60 lui $6,0x6666      (M in $6)
61 ori $6,$6,0x6667
62 addiu $4,$7,160    (160-|x| in $4)   ← DIFFERENT from the target's li $2,0xa0; subu $2,$2,$5
63 mult $4,$6         ((160-|x|)*M)
64 li $2,0xa0
65 subu $2,$2,$5      (160-|x| again in $2)
66 mfhi $7            (hi of the first mult — DELETED in the target)
67 sll $3,$2,7
68 subu $3,$3,$2       (*127)
69 mult $3,$6          (the vol numerator * M)
70 sra $4,$4,0x1f
71 sra $0,$7,0x3
72 subu $7,$0,$4
73 (?)
74 mfhi $9
75 sra $0,$9,0x6
76 subu $5,$0,$3
77 (?)
78 bne $7,$0,...
79 sll $7,$7,0x8
80 li $7,15
81 sll $7,$7,0x8
84 or $5,$5,$7

Hmm, so cand01 has an EXTRA mult (mine[63] = mult $4,$6 of (160-|x|)*M) and an extra mfhi (mine[66]) — and the target has 2 mults total while mine has 3?!

The target: mult $3,$4 (vol numerator) and mult $2,$4 (x+160). Mine: mult $4,$6 (160-|x|), mult $3,$6 (vol numerator), and the x one... mine[74] = mfhi $9 → hmm.

So mine has an EXTRA mult of (160-|x|)*M. What is that for? It computes hi((160-|x|)*M) → then `sra $0,$7,0x3; subu $7,$0,$4` (mine[71],[72]) → $7 = (hi>>3) - sign → that's the /20-style division of (160-|x|)!! And then the x division...

So mine computes an EXTRA division: (160-|x|)/20. And the vol = (hi(vol_num*M)>>6) - sign (mine[74-76]).

So mine computes BOTH (160-|x|)/20 AND the vol. The target computes only the vol and (x+160)/20.

So in cand01, gcc computed an extra division of (160-|x|) by 20. WHY?

Because of the EXPRESSION: `vol = ((0xA0 - ax) * 0x7F) / 0xA0;` and `x = (x + 0xA0) / 0x14;`. gcc's optimizer might have CSE'd/rewritten...

Hmm! Actually: in cand01 the vol's numerator is (160-|x|)*127 and the division by 160 uses M with s=6 ✓ (mine[75]: sra $0,$9,0x6 where $9 = mfhi (mine[74]) = hi(vol_num*M)) ✓. So mine ALSO computes the vol correctly. The EXTRA mult/mfhi (mine[63],[66] and the sra/subu at 71-72) is an extra division of (160-|x|) by 20 — which is SPURIOUS! Where does that come from?

OH!!! I bet it's the ORDER of evaluation and the fact that in cand01, the arg expression `((vol|flg)|x)&0xFFFF` — no...

Hmm, an extra computation of (160-|x|)/20. Hmm, 20 = 0x14 = the divisor of the x computation! So gcc computed (160-|x|)/20 and (x+160)/20 — two divisions by 20. But the source has only ONE /0x14.

Unless gcc's rewrite: `(160-ax)*127/160` → hmm. 127 = 160 - 33. Hmm: (160-ax)*127/160 = (160-ax) - (160-ax)*33/160 = (160-ax) - (160-ax)*33/160. Hmm, 33/160 no.

Hmm, what about: (160-ax)*127/160 = 127 - ax*127/160. Hmm.

Whatever the reason, mine has an extra computation. In the target it's absent.

AH, I THINK I'VE GOT IT: **the x division's numerator**: in the target, `addu $2,$6,160` = x + 160 where $6 = the sign-extended x. But in the source, `x = (x + 0xA0) / 0x14;` where x = (s16)L.sxy[0] — the SIGNED x (not |x|). ✓ the target uses $6 = the signed x ✓.

And mine[62] = addiu a0,a3,160 where a3 = $7 = the signed x → also x+160 ✓.

Hmm, so both compute (x+160) and the vol.

OK, so mine has an EXTRA (160-|x|)*M mult. Hmm, where does (160-|x|) come from in the x division? In mine, the x division's numerator should be x+160 = $4 (from mine[62]: addiu $4,$7,160) — and mine[63] = mult $4,$6 = (x+160)*M ✓ THAT's the x division! And mine[71],[72] = sra $0,$7,3; subu $7,$0,$4 → $7 = (hi>>3) - sign = the x division result ✓.

And mine[64],[65] = li $2,0xa0; subu $2,$2,$5 → (160-|x|) in $2 → mine[67],[68] = *127 → mine[69] = mult $3,$6 = the vol numerator * M → mine[74] = mfhi $9 → mine[75] = sra $0,$9,6 → mine[76] = subu $5,$0,$3 → $5 = vol ✓.

So mine has everything the target has, PLUS one extra mult+mfhi? No wait: mine[63] = mult $4,$6 is the x division's mult; the target's x division mult is at target[70] = mult $2,$4 where $2 = x+160 (from target[69] = addu $2,$6,160). So both have the x division's mult.

Mine: [62] addiu $4,$7,160 (x+160), [63] mult $4,$6 (x+160)*M, [64] li $2,0xa0, [65] subu $2,$2,$5 (160-|x|), [67] sll $3,$2,7, [68] subu $3,$3,$2 (*127), [69] mult $3,$6 (vol num)*M, [66] mfhi $7 (the x division's mfhi — DELETED in the diff?!).

Hmm, "delete mine[66:67] target[64:64]" means mine[66] (mfhi $7) has no counterpart in the target. But the target must have an mfhi for the x division: target[75] = mfhi $6 ✓. So the target's x-division mfhi is at 75 while mine's is at 66. OK, so it's just a scheduling difference, not an extra insn!

So the totals: mine 110 ins, target 111 — the target has ONE MORE instruction. Which one? The nop! target[68] = nop, target[76],[77] = nop, nop. Mine has fewer nops? The diff showed "replace mine[74:77] target[72:78]" = mine 3 insns vs target 6.

OK whatever. The KEY structural difference: the ORDER of the two chains: mine does the x chain first (the x+160 mult at 63), the target does the vol chain first (the vol mult at 66) and the x chain after (70).

So the vol chain must come FIRST. In cand03 it did ✓.

So: how to get the vol chain first while keeping the ori inside the arg expression?

The vol chain's priority: it's boosted if its consumer is "soon". Hmm, in cand03 the vol chain came first.

Hmm, hmm. What if the difference is the ORDER OF THE STATEMENTS: in cand03, the ori statement is AFTER the x chain; in cand01, the ori is inside the call's arg expression (also after the x chain). Hmm, same.

WAIT!!! Maybe it's about the fact that in cand03, vol is REASSIGNED (2 sets) and gcc's tree-level optimizer then computes the vol chain differently (e.g. the division's result is used by a statement that is a separate gimple → the "range"/"expansion" differs).

Honestly, let me just try the hybrid variants empirically. I'll do a batch of 4:

H1: cand03 but with the arg expression keeping the ori: `vol = vol | flg;` AND `func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF)` → the tree optimizer folds the double-or → the arg's ori disappears → probably = cand01 but with vol having 2 sets. Worth trying! (The fold might not happen if the tree optimizer's simplification of x|y|y isn't implemented.)

H2: `vol = vol | flg;` (2nd set) + the arg expression `(vol | x) & 0xFFFF` (cand03) — with the `flg` variable replaced by the literal (cand03 variant with flg = a literal). Same.

H3: The arg expression as in cand01 but with vol's 2nd set created by a statement placed BEFORE the x chain:
```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
vol = vol | 0;    /* folded */
```
✗.

H4: What about giving the vol chain a boost by making the x chain LATER: e.g., move the x computation AFTER the vol computation but keep the source order such that the x chain's consumer (the branch) is later? Hmm.

H5: What if the ORDER of the two chains in the source is swapped:
```
x = (x + 0xA0) / 0x14;      /* the x chain FIRST in the source */
if (x == 0x10) { x = 0xF; }
x = x << 8;
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
{ s32 flg = 0x3000; func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF); }
```
Then the vol chain is right before the call → the vol chain is LATE → ✗ (we want it early).

Hmm, but wait: is that right? In the target, the vol chain is early (before the branch). The vol computation is the FIRST statement in the source (before the x computation). And in cand01 (same source order), the x chain came first. So the source order doesn't determine it; the priority does.

The vol chain's priority is boosted by... in the target, by the asm (an early consumer). In cand03, by the ori statement?? which is late in the source. Hmm, that doesn't work either.

Hmm, hold on! Maybe in cand03 the vol chain came first for a completely different reason: the vol VARIABLE has 2 sets → gcc's tree optimizer computed the division differently (e.g., the tree-level "expansion" produced a different RTL form). Specifically: with 2 sets of vol, the division's result has one use (the ori) — the same as cand01. Hmm.

WAIT. Actually, maybe not! In cand01, the ori is inside the arg expression: `((vol | flg) | x) & 0xFFFF`. In cand03: `vol = vol | flg;` then `(vol | x) & 0xFFFF`.

In cand01, the TREE form is: vol = div(...); D.a = vol | 0x3000; D.b = D.a | x; D.c = D.b & 0xFFFF; call(0x93E, D.c).
In cand03: vol = div(...); vol = vol | 0x3000; D.a = vol | x; D.b = D.a & 0xFFFF; call(0x93E, D.b).

Structurally the same except the assignment target (a new SSA name vs the same variable).

At the TREE level, in cand03 vol has 2 definitions (SSA) → the division's result is used once, the ori's result is used once. In cand01, the division's result is used once too.

The RTL differs how? In cand01, the ori is in the arg expression. Hmm, but at the tree level both are the same shape.

Hmm, unless the tree optimizer's rewrite (the algebraic simplification of the division) happens in cand01 but not cand03 — because in cand03, the division's result feeds a REASSIGNMENT of vol, and the optimizer...

I really need to stop. PRAGMATIC: try H1 (double-or, hoping the tree optimizer doesn't fold it) and a few others.

Actually, WAIT. Let me reconsider H1: `vol = vol | flg;` + the arg `((vol | flg) | x) & 0xFFFF`. If the tree optimizer folds the double-or, the arg becomes `(vol|x)&0xFFFF` → the arg's ops = [or, andi] and vol has 2 sets → the chain might be right (like cand03) but the tail might be cand03-like too (the ori as a separate statement → early).

Hmm, what if the tree optimizer DOESN'T fold it? Then the arg's ops = [ori, or, andi] (writing a1 three times) → the tail would be right ✓ and the chain might be right (if the 2 sets of vol matter).

Let me try H1. Also try:

H2: `vol = vol | flg;` and the arg `((vol | 0x3000) | x) & 0xFFFF`? Same as H1 with a literal.

H3: Reverse: keep the arg as in cand01 (`((vol|flg)|x)&0xFFFF`) and add a 2nd set of vol via an assignment to a DIFFERENT variable that the arg expression uses in an idempotent way: `((vol | flg) | (flg | x))`? Hmm, that changes the ops.

Let me just try H1 and also a variant where the ori statement is `vol = vol | flg;` placed AFTER the x chain (cand03) but the arg expression ALSO contains `| flg` (H1).

Let me write H1 (cand05) and H2 (cand06) and score both.

Also, I should think about time. Let me check the time now.

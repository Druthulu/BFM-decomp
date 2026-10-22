---
ts: 2026-10-22T04:40:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_nh9yu9CQvBWG3pLCZppo
---
Excellent data! For nopin (the lever-free local-result form):

- r74: pri 11428, refs 4, live 7, conflicts v0,sp — this is the local `result`?? It "conflicts v0" — hmm, it has no hard reg (global allocno). refs 4, live 7 → pri = 2^floor(log2 4)=4 → 4*4*10000/7 = 22857? No: pri = floor(log2 refs)*refs/live*1e4 = 2*4/7*1e4 = 11428 ✓.
- r80, r82, r84: pri 10000, refs 2, live 2 → these are the call-result pseudos? They have hard reg v0 ($2). Hmm, they show hard v0 — three of them (the three calls! each call's return value). Right: the three calls to func_80149290 (void) and func_80133784 (int). Actually only func_80133784 returns a value... but the "call result" pseudos for all three calls exist (r80, r82, r84 = the 3 call results). The one used is the third.
- r73: pri 7500, refs 3, live 4, "conflicts sp, prefers v0" → this is the RESULT_DECL (prefers v0). Hmm, pri 7500 = 1*3/4*1e4.
- r75, r76: pri 5000, refs 2, live 4, 2 bytes → the buf1/buf2 pointers (short arrays).
- r77: s0, refs 4, live 11, crosses 1 call, pointer → param_1 in s0.
- r72: s0, refs 3, live 9, crosses 1 call → the RESULT_DECL? or `ret`?

Hmm, where's the local `result`? And where's `ret`?

The .greg order line: "74 73" → the global allocnos are r74 and r73. r73 got... it says hard "-" (a global allocno's hard reg prints as "-" per the docstring). The order line lists which allocnos global allocation handles: 74 and 73.

So r74 (pri 11428, refs 4, live 7) and r73 (pri 7500, refs 3, live 4) are the two global (non-local) allocnos. One of them is the local `result` (in $3 = v1) and the other is the RESULT_DECL (in $2 = v0).

Given the code: mine[27] `move v1,zero` (result=0), mine[32] `sltiu v1,v0,1` (the boolean → v1 = result!), mine[33] `move v1,zero`, mine[34] `move v0,v1` (the copy to the RESULT_DECL).

So `result` (the local) is in v1 ($3) and the RESULT_DECL in v0 ($2). So r74 (higher pri 11428) = the local `result` and r73 (pri 7500) = the RESULT_DECL? But the order line "74 73" means 74 is allocated first (higher pri) → 74 gets the preferred reg first? Hmm.

But r74 "conflicts v0,sp" → it conflicts with v0 (i.e., v0 is not available to it) → so r74 got v1 ($3) ✓ (the local `result`). And r73 "prefers v0" → got v0 ($2) ✓.

Hmm wait, but why does r74 conflict v0? Because the RESULT_DECL (r73) prefers v0 and they overlap? Or because the call-result pseudos (r80/r82/r84) have hard reg v0 already (local allocnos with hard regs are pre-assigned!).

Right: r80/r82/r84 are LOCAL allocnos with hard reg v0 (call results are hard-reg copies). They conflict with everything live at the same time. r74 (the local `result`) is live from ins ~25 to ~33, and the call result r84 is live [24..26] → they overlap → r74 conflicts with v0 → r74 gets v1.

And r73 (the RESULT_DECL, pri 7500) is live [27..epilogue]... but it got v0 ($2) — but wait, the local `result` (r74) is live until the return (ins 33) and the RESULT_DECL starts at 27 → they overlap → r73 should conflict with v1 too. It got v0 because v0 was free in [27..] (the call result died at 26) and r73 prefers v0.

So to get the target:
- The local `result` must get v0 ($2), and the call result must go to v1 ($3) with the copy `move v1,v0`.
- The RESULT_DECL must also be v0 (to coalesce the final copy).

Currently: r74 (local result) conflicts v0 because the call-result pseudo r84 holds v0.

To flip: the local `result` (r74) must have HIGHER priority than the call-result pseudo (r84, pri 10000) so it takes v0 first, and r84 then takes v1.

r74: pri 11428 (refs 4, live 7) — ALREADY higher than 10000! But r84 (the call result, pri 10000, hard reg v0) is a LOCAL allocno with a hard register → it's pre-assigned and can't be displaced!

Hmm, the call result's hard reg v0 comes from the call's return register. Local allocnos with hard regs are assigned before global allocation, and the global allocnos avoid their hard regs where they conflict.

So: r84 (call result) is hard-assigned v0 ($2). The local `result` r74 conflicts with v0 in [24..26] → gets v1.

For the target, the local `result` must NOT conflict with v0 → its live range must NOT overlap the call result's live range [24..26] — but then the tests on the call result would use $2 (no copy). Contradiction?!

Unless the call result's live range in the target is shorter: in the target, the copy `move v1,v0` happens at ins 24, so the call-result pseudo (r84) is live only [24..24] and the COPY pseudo (r85?) is live [24..26] in v1.

So in the target: the call's hard-reg result is copied into a pseudo in $3. That means the pseudo that holds the call result is NOT the hard reg v0 → it's a local allocno allocated to v1 by local allocation (or global).

Why would gcc not coalesce the call result with the hard reg? Because in the pinned version, the hard reg v0 was reserved... Actually in the pinned version, the pseudo `result` (pinned $2) conflicts with v0 for its whole live range, so the call result pseudo couldn't take v0 → got v1 → the copy `move v1,v0` was needed.

In the lever-free version, the call-result pseudo takes v0 directly (no copy).

So the difference-maker is whether the call-result pseudo can take the hard reg v0. The call-result pseudo is a local allocno with hard reg v0 (from the "call" insn's output constraint). GCC decides to use the hard reg for the pseudo if possible.

Hmm, so how do we force the call result to be copied into a pseudo in another register, lever-free?

In the .lreg table, r80/r82/r84 have hard v0 and are the call results. Their live range is [24..26] (live 2, refs 2). If the local `result` (r74, pri 11428) were allocated FIRST (global allocation order), it would take v0 and the call results would be forced elsewhere. But the order line says "74 73" — r74 IS first. Yet r74 "conflicts v0" — the conflict comes from the local allocnos' hard regs (the call results already have v0).

Hmm, in gcc's local/global allocation, hard-reg-holding local allocnos are assigned first, and the global allocnos are then allocated avoiding their hard regs. So the call result keeps v0 regardless of the global allocnos' priority.

BUT: gcc has a "reload"/"allocate" order where hard-reg local allocnos can be spilled if needed... The conflict graph: the call result (r84) has hard reg v0 and is live [24..26]; the local `result` (r74) is live [25..33] → they conflict → r74 can't use v0 → v1.

So, to get the target, we need the call-result pseudo to NOT have the hard reg v0, i.e. the call's result value must be copied out of v0 into another register. In gcc, this happens when the pseudo's copy preferences force it.

How about this: the call result is used in a context requiring a different register — e.g. if the call result is compared with a 64-bit value? no.

Alternative: what if the value returned by the call is assigned to a variable of a different type (e.g. `unsigned short`), forcing a conversion copy? Then the call result stays in v0 and the converted value is in another reg — but the conversion needs extra instructions (mask/sign-extend). The target's copy is a plain move with no conversion.

Hmm, but what if the type change is a no-op conversion that gcc still materializes as a copy? E.g. assigning an `int` to an `unsigned int` — gcc folds it (same representation).

What about `long`? On mips1-gnu, long = 32 bits = int. `long ret = func_80133784(...)` → the conversion int→long is a no-op in 32-bit → no copy.

What about the call being made through a function pointer with a different return type? The call's return type affects the "call" insn's output. Hmm: if the function pointer's return type is `unsigned short`, gcc would zero-extend → extra insn.

Hmm.

What about the call result being USED in a place that isn't the return reg? E.g., the value is stored to memory then loaded? Adds insns.

OK here's another thought: in the target, the copy `move v1,v0` might not be a "call result copy" at all — it might be the copy of `ret` into a variable because the variable `ret` is a different pseudo from the call result. In the ROM's original source, maybe there were TWO variables: `ret` (the call result) and then `ret` copied... Hmm, but the pinned source is my best guess of the original.

Wait, actually: maybe the original source was such that the call result was assigned to a variable `x` and the test used a DIFFERENT variable. Like:

```
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) { ... }
```
vs
```
x = func_80133784(...);   /* x is a char/short? */
```

Hmm. Let's think about what makes gcc NOT coalesce the call result into the hard reg: if the pseudo holding the call result has a copy preference from another pseudo. E.g.:

```
ret = func_80133784(...);
t = ret;      /* copy */
if (t != 0) ...
```
gcc's cse/copy-propagation merges them (as we saw: w1/w2 gave 9, same as nopin → the copy was propagated).

To defeat copy propagation, the copy must be to a pseudo that is later MODIFIED. E.g.:

```
ret = func_80133784(...);
t = ret;
ret = 0;          /* dead reset — breaks the equivalence */
if (t != 0) ...
```
We tried (w1) → score 9, same as nopin → the copy was still propagated (the dead reset didn't survive, or cse ran before DSE).

Hmm, the moves file says the DEAD-RESET trick worked for func_8018A180 (addresses). Different context.

What if the reset is NOT dead? e.g. `ret` is used after the reset:
```
ret = call();
t = ret;
ret = 0;
if (t != 0) { ... } 
```
`ret` is not used after → dead. To make it non-dead we'd need a use of ret → extra code.

Hmm.

What about a different way to break the copy: make `t` a different TYPE so the copy isn't a plain copy:
- `s16 t = ret;` → the copy would be `move v1,v0` + sign-extend (sll/sra) — extra insns. Unless... the extension is done on USE: gcc 2.7.2 might keep the value in v0 and extend at the use site! I.e. `t` (s16) = the low half of ret; the use `t != 0` requires the sign-extended value... gcc would emit `sll v1,v0,16; sra v1,v1,16` — extra insns. Hmm, but the target's andi v1,v1,0x8000 suggests the test is on the 16-bit value! `andi v1,v1,0x8000` — masking 0x8000 is exactly what you'd do with a 16-bit type!

Hmm!! Interesting: `andi v1,v1,0x8000` on a 32-bit value is the same as on the low 16 bits. But if `ret` were s16, the andi would be on the sign-extended value (same bits for bit 15).

But careful: with `s16 ret`, the comparison `ret != 0` on a sign-extended s16: the target does `beqz v1` (full 32-bit test). If ret were s16 and the value had bit 15 set, the sign-extended value would be nonzero → consistent.

Hmm, but gcc would need the sign-extension (sll/sra = 2 insns) → the target has none. Unless gcc keeps the value in the low half and only sign-extends when needed... the test `ret != 0` on an s16: gcc compares the 16-bit value with 0 → `beqz v1` works if v1's upper bits are garbage? No, gcc would sign-extend first (since the value is used as a 16-bit signed). Hmm, actually gcc 2.7.2 for `s16 x; if (x != 0)` where x is loaded from memory (short) → it sign-extends on load. But here the value comes from a call (32-bit) → truncation.

Let's just try: `s16 ret = func_80133784(...)` → the truncation produces `move v1,v0; sll v1,v1,16; sra v1,v1,16`? or `move v1,v0; andi v1,v1,0xffff`? That's 2-3 extra insns vs the target's 1. The score would be worse (more mismatches) but the SHAPE might be closer. Actually no: the score counts mismatched instructions; extra insns are bad.

Hmm, but hold on! What if the call result is assigned to a `u16`/`s16` variable and the uses are only `!= 0` and `& 0x8000`? gcc's RTL: the pseudo holds a 16-bit value (QI mode) → in RTL, a 16-bit pseudo is stored in a register with garbage/zero in the upper bits. gcc would do the truncation: `move v1,v0` + `andi v1,v1,0xffff` (for u16) or with s16 the sign-extension might be deferred.

The target's ins 26 is `andi v1,v1,0x8000` — if `ret` were u16, gcc would have already masked the value with 0xffff → an extra andi. Not matching.

OK so the types don't work.

Let me think about the call result copy differently: in the target, the copy `move v1,v0` is at ins 24, right after the call (ins 22-23) and before the test. What if this copy comes from gcc's handling of the CALL's return value when the call is in a "delay slot" context? No.

Alternative: what if the copy comes from the value being used in TWO different blocks? no.

Hmm, what if the function's call result is stored to a variable `ret` that is ALSO used in the `else` path? no.

New idea: what if we make the call result's pseudo conflict with v0 by ANOTHER pseudo that is live across the call and in v0? E.g. a pseudo that is live across [24..26] in v0 — but the call result itself occupies v0 there.

Hmm, the fundamental issue: gcc assigns the call result to the hard reg v0 and copies only when the pseudo can't be in v0.

When does gcc NOT coalesce a call result with v0? When the pseudo has multiple "copy preferences" or when the value is used in a way requiring a different reg.

AH WAIT. What about the ORDER of the two calls? The third call's result... Hmm.

What if the call result is assigned to a variable whose address is taken? Then it'd be in memory.

Hmm, what about `volatile`? Volatile would force memory traffic. No.

Let me reconsider: maybe the copy `move v1,v0` in the target is not a copy of the CALL result but the copy of the call result into the pseudo `ret`, and the reason gcc didn't coalesce is that the call result pseudo r84 was allocated to v1 by LOCAL allocation because... the call's return value pseudo in gcc 2.7.2 has a hard reg preference (v0) — but if another pseudo conflicts...

Honestly, the pinned case shows: the pinned `result` ($2) conflicts with v0 → the call result got v1 → copy. So the mechanism "reserve $2" is what we need, lever-free.

Lever-free way to reserve $2 for the whole function: a pseudo live across the whole function that gets $2 — but a pseudo live across a CALL must be in a callee-saved reg. Hmm, BUT: what if the pseudo is live across the call but its value is dead after the call? No, then it's not live across.

Hmm, what if the pseudo is live across the call but the call doesn't clobber it because... no, all calls clobber caller-saved regs.

Wait — what if the pseudo is live across the call but gcc keeps it in a caller-saved reg anyway because the value is PROVABLY dead before the call? no.

Alternatively: reserve $2 for the whole function using a pseudo that's live from the function start to the end but whose value is only needed... hmm, the RESULT_DECL! In the direct-return form (win.c), the RESULT_DECL r73 is live [27..epilogue], pri 7500, and prefers v0 → it gets v0 ✓ (no conflict with the call result which died at 26).

So in the direct-return form, $2 is used by the RESULT_DECL from ins 27 on, and the call result uses $2 before that. The copy `move v1,v0` doesn't appear.

For the copy to appear, the call result must be in a pseudo that is NOT v0 → the call result pseudo must conflict with v0.

What if the RESULT_DECL were live BEFORE the call? Then it would conflict with the call result's v0 → the call result would be forced to v1 → the copy appears! But the RESULT_DECL live before the call = live across the call → callee-saved. Hmm, but the RESULT_DECL is a pseudo that gcc gives a hard reg preference to (prefers v0) — it's not a normal local.

Hmm! What if the RESULT_DECL is set BEFORE the call? E.g.:

```
int result = 0;   /* set before the call */
ret = call();
if (ret != 0) { if (ret & 0x8000) result = X; }
return result;
```
Here `result` is a local (not the RESULT_DECL) — live across the call → callee-saved. BUT what if gcc's "return slot" ... no.

Hmm, but what if the RESULT_DECL itself is set before the call: `return` before the call? Like:

```
if (param_1 == 0) return 0;    /* hmm, changes semantics */
```

Hmm. What about a `goto`? Or:

```
int result = 0;
if (something) result = 1;
ret = call();
...
```
The RESULT_DECL is only set at the `return result;` — after the call.

OK, alternative: what if the function's result is set BEFORE the call in the sense that the RESULT_DECL is defined early? In gcc, the RESULT_DECL is defined at each `return` statement. If there's a `return` statement BEFORE the call in the source, the RESULT_DECL is defined there → live across the call → callee-saved? The RESULT_DECL is special: gcc prefers to keep it in v0 and copies at the return. If the RESULT_DECL is defined before the call and used after, gcc would keep it in a callee-saved reg (since it's live across the call) — that changes the prologue (adds sw s1). The target's prologue only has s0 and ra. So no.

Hmm, so how did the ORIGINAL ROM code get the call result into $3 while the value stayed in $2?

Maybe the original source had the call result assigned to a variable of a DIFFERENT type than int! Let's think: if `ret` were `unsigned short` (u16):
- `ret = func_80133784(...)` → the call result (32-bit) is truncated to 16 bits → gcc: `move v1,v0` + `andi v1,v1,0xffff`? That's 2 insns; the target has 1 (just the move).

Unless gcc 2.7.2 does the truncation lazily: the pseudo `ret` is a 16-bit (QI/HImode) pseudo; the copy from the call result (a 32-bit pseudo in v0) to the 16-bit pseudo requires zero-extension of the upper bits... but if the pseudo is used only in 16-bit operations (andi 0x8000, beqz), gcc might keep the value unextended and only mask where needed. Actually gcc's RTL for a 16-bit pseudo: `move v1,v0` (the copy) then the mode change happens via `zero_extend`/`sign_extend` ops which in a register are usually optimized away by gcc if the uses are all 16-bit ops (since the upper bits are don't-care for HImode uses). gcc 2.7.2's `move` insn with different modes → it would insert the extension as a separate insn... but combine might fold `move v1,v0` + `andi v1,v1,0xffff` into just the andi (using v0 directly)! Then the copy would vanish. Hmm.

But the target's ins 26 `andi v1,v1,0x8000` operates on v1 — so v1 holds the value. And ins 24 `move v1,v0` copies. So v1 = the 16-bit value (or the 32-bit value).

Honestly, maybe the original ROM code was:
```
ret = func_80133784(1, buf1, (int)buf2);
```
where `ret` is declared as `s16`!? And the compiler emitted `move v1,v0` (the truncation copy) and then `andi v1,v1,0x8000` (the mask test on the 16-bit value) and `beqz v1` (test of the 16-bit value → but for a signed 16-bit value, `beqz` tests the full register; if the value is negative (bit 15 set) the register isn't zero... but the upper bits could be garbage → gcc would sign-extend → `sll/sra`. Hmm, but if `ret` is UNSIGNED short (u16), the value is zero-extended → gcc needs `andi v1,v1,0xffff`? Or it could keep it as a 16-bit pseudo where the upper bits are don't-care, and the test `ret != 0` → `beqz v1` would be wrong if the upper bits are garbage → gcc would mask.

Hmm, unless the call result's upper bits are known... no.

OK, let me flip to empirical mode: try a bunch of type variants for `ret` (s16, u16, unsigned char, unsigned short) and see the scores. Cheap: 4 tries.

Also try: `ret` as `int` but the call result assigned via a cast to a different type: `ret = (s16)func_80133784(...)` hmm same.

Also: the "u8" idea — `unsigned char ret` → the call result truncated to 8 bits → `move v1,v0; andi v1,v0,0xff`?

Let me also try the reverse: make `result` (the value holder) a u8 (the notes mention "u8 boolean body" for the other item).

Let me now think about what else could produce the `move v1,v0` copy.

IDEA: What if the call result is compared against 0 using an unsigned comparison that gcc implements with `sltiu`? no.

IDEA: What if there are TWO uses of the call result in different blocks, one of which is the delay-slot andi? no.

IDEA (promising): What if the call result is assigned to a variable that is ALSO assigned elsewhere (a "re-tie")? From the moves file: "launder | func_8017E780 | MATCH — the t re-tie keeps the unk20 load OUT of sched1's call+argsetup group" and "func_80180054 — six re-ties on xa/xb materialise moves that cse merges". A "re-tie" = assigning the same value to a variable twice (e.g. `v = a; v = b;`) which creates a real move.

So: a re-tie on `ret`: e.g.
```
ret = func_80133784(...);
x = ret;
```
is a copy that cse merges (as we saw). But a re-tie like `ret = func_80133784(...); ret = ret;`? dead.

Hmm, what about `t = ret; t = ret;`?

Honestly, the cse merge of `t = ret` is the blocker. The moves file says: "launder | func_8017E204 | MATCH — the copy through an s16 temp escapes cse2's equivalence class, so v1 keeps its own register instead of being merged with v0 (G06)". So an s16 temp escapes cse! That's the trick: `s16 t = ret;` → the copy through an s16 temp survives cse (different mode → different equivalence class).

But the s16 truncation costs extra insns... unless the temp is used in a way that the truncation is free. Hmm. In func_8017E204 it worked.

For our case: `s16 t = ret;` → the RTL: ret (SImode) → t (HImode): gcc emits `move v1,v0` + sign/zero extension? In gcc 2.7.2, converting SImode to HImode on a register: it does `move` then the upper bits are undefined for HImode... gcc 2.x requires the value in a register for HImode to have the upper bits as garbage? No — in gcc, a HImode pseudo holds the value in the low 16 bits; the upper bits are undefined. So the copy `move v1,v0` suffices for a HImode copy (the truncation is implicit). Then the uses: `t != 0` → for an unsigned short, the test `beqz v1` requires the upper bits to be zero → gcc would need `andi v1,v1,0xffff` (zero-extension) → extra insn. For a SIGNED short, `t != 0` → the sign-extension is needed for correctness (the value is negative → nonzero) → `sll/sra` or `sra`+`sll`.

Hmm, but the target's `beqz v1` tests the full register — for the target's semantics, `ret != 0` on the FULL 32-bit value. So `ret` is 32-bit.

Hmm, so an s16 temp changes the semantics of the test (e.g. ret = 0x00010000 → the truncated t = 0 → beqz taken, but the full test would say nonzero). Since we need bit-exact code, the semantics must match the ROM's: the ROM tests the full 32-bit value.

Hmm, wait. Actually does it? The ROM's `beqz v1` after `move v1,v0` tests the full 32-bit call result ✓ and `andi v1,v1,0x8000` tests bit 15 ✓. So `ret` is 32-bit.

OK so, the copy `move v1,v0` must be a plain 32-bit copy that survives cse. What breaks cse's copy propagation for a 32-bit copy? From the moves: "func_8017DE84 | WALL cse-copy-merge — the v1 re-tie materialises a real move (v1=mode) that cse merges in plain C". So cse merges re-ties of the same mode.

What made cse NOT merge in the MATCH cases? "func_8017E204: the copy through an s16 temp escapes cse2's equivalence class". "func_80181E64: s16 v and the store reads v: the HImode copy t = v escapes cse". "func_8003DF8C: u16 i; u16 j: the HImode copies of arg0/arg1 escape cse".

So HImode copies escape cse. The cost: the truncation. But maybe in our case the truncation is FREE if the value's upper bits don't matter!

Think: `s16 t = ret;` — hmm, but then the uses of t are 16-bit.

Alternatively `u16 t = ret;` — the truncation requires zero-extension for the `!= 0` test → `andi`.

Hmm, but what if the test is done on the 32-bit value and only the MASK test uses the 16-bit value? E.g.:

```
ret = func_80133784(1, buf1, (int)buf2);
t = (s16)ret;                  /* the copy through an s16 temp */
if (ret != 0) {
    if ((t & 0x8000) != 0) {    /* the mask test on the truncated value */
```
But `t & 0x8000` for s16 → the sign bit of the 16-bit value = bit 15 of ret ✓ (same as the ROM's andi 0x8000). And the sign-extension of t for the `& 0x8000` test: `t & 0x8000` on a signed short → gcc sign-extends t to 32 bits then ANDs with 0x8000 → the extension insns (sll/sra) would appear... unless gcc optimizes `t & 0x8000` to a 16-bit andi (it can: the result only needs bit 15 → `andi v1,v1,0x8000` on the HImode value in the register works if the value is in the low half ✓ — gcc's RTL for `t & 0x8000` with t in HImode: the AND is done in HImode → `andi v1,v1,0x8000` ✓ (the upper bits of the register are garbage but the AND in HImode only affects the low 16 bits; then the result is compared != 0 → the comparison is in SImode → needs the upper bits zero → gcc would zero-extend the HImode result → `andi v1,v1,0x8000` in HImode then compare → hmm, comparing a HImode value with 0: gcc emits `beqz v1`?? For a HImode comparison, gcc 2.7.2 emits `beqz` on the register if it knows the upper bits are zero (it does, if the value was zero-extended) — but with garbage upper bits it must mask.

This is getting really deep. Let me just TRY it: several variants with u16/s16 temps and see the scores. The score will tell me.

Also try: `if (ret != 0)` and the mask test on the SAME variable but with the copy trick.

Let me generate a batch:
x1: `s16 t = ret;` then `if (ret != 0) { if ((t & 0x8000) != 0) {...} }` (t declared at top)
x2: `u16 t = ret;` same
x3: `unsigned short t = ret;`
x4: `t = ret;` where t is `int` but declared AFTER the call (block scope) → higher pseudo number → wins the tie?
   (w3 was this but had a compile error — the block after the return. Let me fix: the block must not come after a return... Actually the error was probably "return outside function"? No — I put the block after the `return result;`... let me look at w3: PRE + BODY + "    {\n int t; t = ret; ret = 0;\n" + MID + "    }\n}\n" — MID ends with "return result;\n}\n" so there's an extra closing brace → syntax error. My generator bug.)
x5: `t = ret;` with t declared at top and used, but `ret` also used (so cse can't remove the copy?): `if (ret != 0 && (t & 0x8000) != 0)` — hmm, semantics: t == ret so equivalent. But then cse would substitute t→ret and the copy dies.

Let me also try the "two variables" idea where the second variable is assigned in a way that cse can't merge: e.g. `t = ret + 0;`? folds. `t = ret; t = t;`?

Hmm, what about `t = ret;` where `ret` is later modified NON-dead: e.g.
```
ret = call();
t = ret;
ret = 0;
if (t != 0) { if ((ret & 0x8000) != 0) ... }  /* WRONG semantics */
```
no.

OK also: maybe use the value `ret` twice in the mask test to force 2 refs...

Let me just try the s16/u16 temp variants and the fixed block-scope variant. Also the "u8 boolean" idea from the notes (for the other item).

Let me write these.

Also — IMPORTANT alternative: maybe the whole approach should be different: instead of forcing the call result into $3, note that the score is the number of mismatched instructions. The current best is 6. Maybe some other structure gives a smaller residual even without the copy. E.g. if the code had the same insn count and only the register difference, the score would be ~6 (the diff region). Since the score counts mismatched insns, a perfect-but-for-registers body scores high.

Let me check the scoring: "score 6 (COUNT)" = 6 instructions differ. Our target: mine has 39 ins vs 40 → 4-5 differ in the region + the j offset.

So the goal remains: get the copy.

Let me try the variants now.

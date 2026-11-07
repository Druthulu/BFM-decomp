---
ts: 2026-11-06T16:28:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cfoZ7sHQ87266S1W4KGX
---
Cross-jump merged the two tails: both arms now branch to 2bb8 which is the shared `jal func_801822A4; move a0,s3` block. The target has the then-arm falling through to the join at 2bb8 and the else-arm branching directly to 2bb8 with a `j 2bb8` from the then-arm... Actually target:
- then arm: `beqz v0, skip(2bc8)`, `j 2bb8` (join to call)
- else arm: `beqz v0, skip(2bc8)` then falls through to 2bb8 call.

So target has an extra j+nop (2ba8/2bac in target) because the then arm must jump over the else arm's tail. Mine merged: both branch to a shared call block placed after both, eliminating the jump. So cross-jump merged the two "beqz -> skip; fallthrough call" tails.

To defeat cross-jump with real C: make the two arm tails not identical in RTL. Target itself has them not identical! In target, then-arm ends with a jump to join (2ba8) and else-arm falls through. So the target's structure is: then arm does its test, jumps over else arm to shared call; else arm tests and falls to shared call.

Hmm, so how does target arise naturally? This looks like:
```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
} else {
    if (d >= 0x201) goto skip;
}
call;
```
Which naturally gives both arms branching to skip, with call after else arm. Mine matches that structure but cross-jump merged the arms' tails (the beqz to skip + fallthrough into call). Target did NOT merge. The asm was preventing merge.

Cross-jump (jump2?) find_cross_jump compares the ends of the two arms. The asm made the RTL tails differ. Real C alternatives to make RTL differ:

1. In the then arm, use a different comparison form that still yields `slti v0,v1,81; beqz`. E.g. `if (0x51 <= d)` — same. Or write `if (d - 0x51 >= 0)`. That changes RTL (sub + sge?) but may produce same insns? `slti v0,v1,81` for d<0x51... target has slti v0,v1,81 with beqz (branch when not <81, i.e. d>=0x51). d is v1 = s16 0xDC - D_801C7748. Hmm.

2. Insert a real statement in one arm that's not identity — but that adds instructions.

3. Restructure so the merge can't happen: put the call in one arm? No, target calls once shared.

Wait — cross-jump merges the *tails*: the two `beqz ...; nop` + fallthrough. find_cross_jump compares instructions from the end. In target, then-arm's tail is `j 2bb8; nop` and else-arm's tail is `beqz v0,2bc8; nop`. These differ because the then arm has its own j. Why? Because in target the call block is placed after the else arm and the then arm needs to jump to it. Both arms end with a jump to the same call block, but then-arm's final insn is j while else's is beqz... The merge algorithm tries to make both arms jump to a shared block: it merged mine so both beqz to shared block then call. Target: it did not merge, so the then arm jumps to 2bb8 (the call) and else falls through into 2bb8. This is the natural "then arm before else arm, call after" layout... and cross-jump would normally merge them to the layout mine has. So what in target's RTL prevented it?

Maybe in the target, the then arm's `goto skip` structure differs: perhaps the original source used something like:
```
if (unk70 == 0) {
    if (d < 0x51) { call; return; }
} else {
    if (d < 0x201) { call; return; }
}
goto skip;   /* or fall to skip */
```
Hmm that would duplicate the call.

Actually look at target insns again:
```
2b8c lh v0,112(s3)
2b94 bnez v0,2bb0
2b98 slti v0,v1,513        <- delay slot, else arm compare (computed before branch taken)
2b9c slti v0,v1,81         <- then arm compare
2ba0 beqz v0,2bc8          <- then: if d>=0x51 -> skip
2ba4 nop
2ba8 j 2bb8                <- then: jump to call
2bac nop
2bb0 beqz v0,2bc8          <- else: if d>=0x201 -> skip
2bb4 nop
2bb8 jal func_801822A4
2bbc move a0,s3
2bc0 j 2bf4                <- return (join epilogue)
2bc4 nop
2bc8 skip: ...
```
So target layout = then arm placed first, jumps forward to call which sits after else arm. Mine = merged: call block after both arms, both branch to it.

For cross-jump not to merge: find_cross_jump looks for matching insns at the ends of two blocks and merges identical suffixes. In target, then-arm ends `j 2bb8; nop` and else-arm ends `beqz v0,2bc8; nop`... these end sequences: [j, nop] vs [beqz, nop]. The suffix after merge candidate: the shared part is `nop` then... The blocks both eventually reach `jal; move`. find_cross_jump merges blocks when the tail instructions are identical (comparing from end of each block). Then-block tail: nop(j's delay), j; else: nop, beqz. Not identical → no merge. Then why did mine merge? In mine, both blocks end with `beqz v0, X; nop` → identical, so merge.

So in target, the *then* arm's RTL has an unconditional jump at its end (goto skip/join arrangement), while in mine (from C) both arms end in a conditional branch. The natural C that produces target: 

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    call; return;   // ← then arm returns, doesn't fall to join
} else {
    if (d >= 0x201) goto skip;
}
call; return;
```
That duplicates the call. No.

Alternative: target may come from source where the then arm is an `if` whose fall-through path continues, and the else is... hmm.

Actually maybe the natural C is:
```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
} else if (d >= 0x201) {
    goto skip;
}
func_801822A4(param_1);
return;
```
Same as mine.

What differs? The asm made then-arm RTL longer. Maybe the original had a statement in the then arm that got optimized to nothing at insn level but left RTL: e.g. `(void)d;` no. A barrier is exactly that.

But our task: find a real-C spelling (no barrier) that produces target's unmerged layout. Since target's layout is the "natural" one for a `goto`-based structure where the then-arm ends with `goto join`, maybe restructure:

```
if (unk70 == 0) {
    if (d < 0x51) goto do_call;   // forward to call placed after else
} else {
    if (d < 0x201) { ... }
}
```
Hmm: `if (d < 0x51) goto call;` then fall to... skip? That gives then-arm: slti (d<0x51), bnez call; else-arm: slti(d<0x201), beqz skip (fall to call). Wait:

```
if (unk70 == 0) {
    if (d < 0x51) goto docall;
} else {
    if (d >= 0x201) goto skip;
}
docall:
    func_801822A4(param_1);
    return;
skip:
```
Then-arm ends with `bnez v0, docall; nop` (branch taken to call). Else-arm ends with `beqz v0,skip; nop`, falls to docall. Then the call is placed after else arm. Then-arm: slti;bnez to call. But bnez to docall which is immediately after else arm — needs to jump over else arm. In RTL, the then-arm block ends with a conditional branch to docall. Else-arm ends with conditional branch to skip. These end sequences differ ([bnez,nop] vs [beqz,nop]) → cross-jump won't merge? Possibly cross-jump can still merge because after the branches the destination blocks differ... find_cross_jump works on the tails of two blocks preceding the same join: it compares block A and block B backwards to find a common suffix. Here A ends bnez->docall, B ends beqz->skip; no identical suffix, so no merge. That could produce target's layout? Let's check target: then-arm has `beqz v0,2bc8` (skip) then `j 2bb8` (call). That's branch-if-≥0x51-to-skip, then unconditional jump to call. Which corresponds to `if (d >= 0x51) goto skip; goto docall;`?? Or `if (d >= 0x51) goto skip;` then falling to a separate block holding the call that's after the else arm. That's what mine had before merge; cross-jump merged them.

So the source structure is mine's, and only the RTL difference prevented merging. Hmm.

But maybe there is a different C structure that yields a different RTL tail: e.g., the then arm doing `return` after the call vs goto. Wait what if the source is:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    func_801822A4(param_1);
    return;
} else {
    if (d >= 0x201) goto skip;
    func_801822A4(param_1);
    return;
}
```
Cross-jump merges the two identical call+return tails into one — that's exactly a cross-jump merge producing mine's layout (both branch to shared call). Interesting! In that case target's layout has the call placed after the else arm, reached by a jump from then arm... which is the "not merged" version. Hmm.

Let me think about what find_cross_jump does: it finds two blocks with matching ends and merges the matched part into one, redirecting both to it. It also requires the blocks be "the same" length? Actually find_cross_jump (jump.c) compares i1 and i2 backwards until mismatch; if the matched length > threshold it merges.

Let me read jump.c find_cross_jump.

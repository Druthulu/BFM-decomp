---
ts: 2026-10-22T01:04:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_UChaodGmArcOE1mx258w
---
cand05 (H1): score 2! Same as cand03 — so the tree optimizer DID fold the double-or (the chain is right, the tail wrong). Same residual presumably.

cand06: score 29 (the double-or in the expression was folded, chain wrong).

So cand05 = cand03 in effect.

The tail problem persists: the ori (a separate statement writing a single-set pseudo) is boosted → scheduled before the li.

I need the ori to write a1 (multi-set). Since the tree optimizer folds the double-or, I can't have both.

Hmm! What if the ori is in the arg expression (writing a1) and the "2nd set" is created by a statement that the tree optimizer keeps AND that doesn't produce an extra instruction...

What if the 2nd set is `vol = vol | 0x3000;` (a separate statement) and the arg expression uses `vol` with the ori REMOVED, but I make the arg expression's ops write a1 in a way that... that's cand03. The problem is cand03's ori writes the vol pseudo (single-set).

Hmm! Wait: in cand03, is the ori's dest really single-set? The ori writes the `vol` variable. At the RTL level, `vol` (the variable) is a pseudo that was written by the division's copy AND by the ori → 2 sets → NOT single-set → no boost. Hmm, but the division's copy may be coalesced with vol (the copy removed) → then vol is written only by the ori (1 set) → boosted.

Hmm. In the target, the ori's dest is a1 which is written by the ori AND the or → 2 sets → not boosted.

So if in cand03 the ori's dest (the vol pseudo) had 2 sets, it wouldn't be boosted. To force 2 sets on the vol pseudo, vol must be written twice by different insns — e.g. the division's copy (which could be coalesced away) plus the ori.

Hmm, the division's copy: `vol = ((0xA0-ax)*0x7F)/0xA0` — the division's result is copied into vol. If gcc keeps that copy (a separate `move`), then vol has 2 sets. But the copy is coalesced (the division's result and vol are the same register) → 1 set.

Hmm, in the TARGET: vol (the division result) is in $5, and the asm copies it to V (coalesced, same reg). So the asm's output pseudo V = $5 = the same as the division's result?! Then the ori reads $5. Hmm, so V and the division's result are the SAME register → the asm is a no-op copy.

So in the target, the "chain" is: division result ($5) → asm (coalesced) → ori reads $5.

OK so what made the target's ori NOT boosted? The ori's dest a1 is written twice (ori + or). In cand03, the ori's dest is the vol pseudo, written once (the division's copy coalesced) → boosted.

So to match: the ori must write a1 → it must be part of the arg expression → cand01's form. But cand01's chain is wrong.

=> I need the chain right WITHOUT the extra statement. The chain's rightness in cand03/cand05 comes from... the 2 sets of vol? In cand05, vol has 2 sets (the division and the ori statement) — and the chain is right.

Hmm, so what if I keep the ori in the arg expression (cand01) and give vol a 2nd set in a way that doesn't emit an instruction but keeps the tree optimizer from folding...

IDEA: `vol = vol | 0x3000;` where the SECOND use in the arg expression is `vol | 0x3000` — folded. What if the second use is a DIFFERENT but equivalent expression that the tree optimizer can't fold, e.g. `((vol | 0x3000) | x)` vs `((vol | flg) | x)` where flg = 0x3000 — the fold happens because flg == 0x3000 == the literal.

What if the 2nd set uses a value that's NOT 0x3000 but is later masked? E.g.:
```
vol = vol | 0x3000;
... arg: ((vol & 0xFFFF) | x) & 0xFFFF   /* the mask makes the value-preserving */
```
Hmm: vol|0x3000 then &0xFFFF → (vol|0x3000)&0xFFFF = (vol&0x3000... hmm, (vol|0x3000)&0xFFFF = (vol&0xFFFF)|0x3000. And the original arg was ((vol|flg)|x)&0xFFFF = ((vol&0xFFFF)|0x3000|x)&0xFFFF = (vol&0xFFFF)|0x3000|(x&0xFFFF) ✓ (since 0x3000 and x's low bits are within 0xFFFF).

So:
```
vol = vol | 0x3000;
arg = ((vol & 0xFFFF) | x) & 0xFFFF
```
Hmm, the extra `& 0xFFFF` would add an insn. ✗

Hmm.

Alternatively, use a 2nd set that preserves the value EXACTLY and isn't folded:
- `vol = vol + 0;` → folded (tree).
- `vol = vol * 1;` → folded.
- `vol = vol - 0;` → folded.
- `vol = vol / 1;` → folded.
- `vol = vol % 1;` → folded (0).
- `vol = vol << 0;` → folded.
- `vol = vol >> 0;` → folded.
- `vol = ~(~vol);` → folded.
- `vol = (s32)(s16)(s32)(s16)vol;` → folded?

Hmm, what about `vol = vol | (0x3000 & 0);` → folded.

What about `vol = vol ^ 0x0;` → folded.

Hmm. What about a 2nd set with a value-preserving op that the tree optimizer keeps: e.g. `vol = vol | (x & 0);` — folded.

Hmm, what about using the SIGN: `vol = vol * (x - x + 1);` folded.

OK, what about making the 2nd set on a variable of a DIFFERENT type where the conversion is kept? E.g. `vol2 = (u8)vol;` — that truncates (vol ≤ 127 so it's the same value) — but it adds an andi insn ✗.

What about `vol2 = (s16)vol;` — a sign-extend pair (2 insns) ✗.

Hmm. What about a 2nd set where the value is preserved but the op is FREE because it reuses an existing register operation? Hmm.

DIFFERENT ANGLE: maybe the chain's rightness in cand03/cand05 doesn't come from vol's 2 sets but from the fact that the ori statement is BETWEEN the x chain and the call, i.e. the block structure changes. Let me test: what if I keep cand01's arg expression (ori inside) but add a DEAD statement between the x chain and the call — e.g. `vol = vol | 0x3000;` — that IS cand05 (which folded to cand03's behavior).

Hmm, so cand05 (which has both the 2nd set AND the ori in the arg expression) = score 2 (chain right, tail wrong). The fold removed the arg's ori. So the arg's ops = [or, andi] → a1 written twice → hmm, then the `or` (not the ori) is the arg's first op and it writes a1 (2 sets: or + andi) → not boosted → should be late... but the ORI (the separate statement) was boosted and went early.

So the fix: make the separate ori statement's dest multi-set OR remove it while keeping vol's 2 sets.

IDEA: what if the separate statement is `x = x | vol;`? No...

IDEA: what if the separate statement writes a variable that is ALSO written later? E.g.:
```
{
    s32 flg = 0x3000;
    vol = vol | flg;    /* the ori: dest = vol */
    ...
}
```
vol is written by the division's copy and by the ori. If the copy is coalesced → 1 set.

What if the division's result is assigned to vol via an explicit copy that gcc keeps? E.g. `vol = ((0xA0 - ax) * 0x7F) / 0xA0;` — gcc's RTL: the division's result pseudo → copied to vol's pseudo. Coalescing merges them (both are dead after) → 1 set. Unless the division's result has another use (it doesn't).

Hmm, what if the division's result is used twice? E.g.:
```
vol = num / 0xA0;
```
where num is a separate variable:
```
s32 num = (0xA0 - ax) * 0x7F;
vol = num / 0xA0;
```
Then num's copy to the division's dividend... hmm.

Let me think about what makes the ori's dest multi-set in a way that doesn't add instructions: if the SAME variable is written twice with different values:
```
vol = vol | flg;    /* write 1 */
vol = vol | flg;    /* write 2 — the tree optimizer folds this */
```
✗

```
vol = vol | flg;
x = x | vol;   /* hmm */
```

What about: the ori's dest is `x` (which is written multiple times)?
```
{
    s32 flg = 0x3000;
    x = x | (vol | flg);   /* hmm, x is written here → x has more sets */
    func_8002D4C8(0x93E, x & 0xFFFF);
}
```
Hmm, but then the arg is x (not (vol|x)) and the value: x_new = x | vol | flg — but the original is (vol|flg|x)&0xFFFF ✓ the same (modulo the mask). But the ori's dest would be x → the ops: `or $2,$2,$5` (x|vol) then `ori $2,$2,0x3000` — the ORDER is or then ori, but the target has ori then or. ✗ (unless the scheduler reorders; the ops are dependent so no).

Hmm, unless I write `x = (vol | flg) | x;` → then the ori comes first ✓ and the or second ✓, and the dest is x (multi-set: x is written by the x chain and by this) → the ori writes x... hmm, but the ori writes the TEMP (the intermediate (vol|flg)), not x. The temp is single-set → boosted ✗.

ARGH.

Hmm, ok: what if BOTH the ori and the or write x directly? That happens if the expression is expanded at the call.

So: the ori must be at the call (expanded there). And vol must have an extra early consumer that doesn't emit.

Hmm, what if the extra consumer is the ORI ITSELF but the ori is at the call → the consumer is at the call (late) ✗.

Hmm, what if the vol chain's boost in cand03/cand05 comes from something else entirely — like the fact that vol's variable is written twice (the tree-level 2 sets) → the tree optimizer's rewrite (the algebraic one) is blocked? Then ANY 2-set version of vol would work, even if the ori is at the call.

So: what if the ori is at the call AND vol has a 2nd set created by a statement that doesn't emit an instruction...

What if the 2nd set is created by the PINNED ax? no.

WAIT!!! What about `ax`?! The pin: `register s32 ax __asm__("$5");` and `ax = x; if (x<0) ax = -x;`. Hmm, ax has 2 sets already.

Hmm, what about making VOL's 2nd set come from the SAME statement that computes it? Like `vol = (((0xA0 - ax) * 0x7F) / 0xA0) | 0;` → folded.

What if the division's result is assigned to vol and ALSO to another variable (a copy)? E.g.:
```
s32 vol;
s32 vol2;
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
vol2 = vol;
```
The copy vol2 = vol: at the RTL, a copy (may be coalesced). If coalesced, no extra insn ✓ and vol's pseudo... hmm, the copy's dest is vol2's pseudo. If vol2 is unused (dead), the copy is removed entirely ✗.

What if vol2 IS used in the arg expression? Then the arg's ops would read vol2's register... `((vol2 | flg) | x)` — the ori's dest is a1 ✓ (at the call) and vol2 = a copy of vol (coalesced → the same register as vol's division result, no extra insn if coalesced!). And vol2 has 1 set (the copy) → hmm, and vol (the division result) has 1 set.

Hmm, but that's the same as cand01 structurally (the ori at the call) — the chain would be wrong again.

Unless the copy's presence (vol2 = vol) creates the "2 sets" effect at the tree level? vol2 is a new SSA name; vol has 1 def. Hmm.

OK, let me try to directly test the hypothesis "the chain's rightness depends on vol having 2 defs (tree-level)". Test: cand01's form but with vol reassigned in a way that the tree optimizer keeps and that emits NO instruction.

Is there such a thing? `vol = vol | 0x3000;` emits the ori. `vol = vol;` folded.

Hmm, what about a 2nd def via a PHI-like path: e.g.
```
if (cond) vol = vol | 0x3000; else vol = vol | 0x3000;
```
→ folded to one.

What about `vol = (vol + 0x3000) - 0x3000;`? The tree optimizer folds (x+c)-c → x ✓ folded.

What about `vol = (vol ^ 0x3000) ^ 0x3000;`? folded (xor with the same constant twice).

What about `vol = vol | (0x3000 & ~0x0)`? folded.

What about `vol = (s32)((u32)vol | 0x3000u)` — same as |0x3000 → emits the ori.

Hmm, so any real op emits.

BUT WAIT: maybe I can have the ori emitted ONCE and serve BOTH purposes! I.e., the ori statement emits the ori (the target has exactly one ori), and the arg expression uses the ori result. That's cand03. The problem is only the ori's POSITION (before the li instead of after).

So the real question: in cand03, why does the ori (writing the vol pseudo) get scheduled before the li (writing a0)?

If the ori's dest were multi-set, it'd be late. The vol pseudo is written by: the division's copy (coalesced) and the ori. If the coalescing does NOT happen (because the division's result is used by the copy AND the copy is not coalesced for some reason), the vol pseudo would have 2 sets → not boosted → late ✓.

How to prevent the coalescing of the division's result into vol? If the division's result has 2 uses! E.g.:

```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
```
Hmm, the division's result has 1 use (the copy to vol).

What if:
```
s32 num = (0xA0 - ax) * 0x7F;
vol = num / 0xA0;
```
Then num is used once (the division) → coalesced.

What if num is used twice:
```
s32 num = (0xA0 - ax) * 0x7F;
vol = num / 0xA0;
... some other use of num ...
```
The other use would emit an insn ✗.

Hmm, hmm.

Alternatively: make the division's result used by the ori directly (no copy): i.e. `vol = ... | 0x3000` — hmm.

What if the source is:
```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
vol = vol | 0x3000;
```
The RTL: div_result → copy to vol_pseudo1 → vol_pseudo1 → ori → vol_pseudo2 (same pseudo as vol_pseudo1? since vol is the same variable, the RTL uses ONE pseudo for vol across both assignments! In gcc's RTL, a variable is a single pseudo (or a stack slot). So: div_result → vol (a copy), then vol → ori_dest → vol (a copy back!).

So the ori writes vol, and the copy back also writes vol → 3 sets on vol's pseudo? Hmm: sets on vol: [the copy from div_result], [the ori result], [the copy back to vol]. So vol has multiple sets → NOT single-set → not boosted → LATE ✓!!

Hmm! But cand03's ori landed EARLY (at 83, before the li at 84). So the boost theory fails again, OR the "boost" isn't about sets.

Hmm, alternatively, maybe the ori's early position in cand03 is due to its LUID (it's a separate statement before the call) and the call group's members are scheduled as a unit, so the ori (outside the group but adjacent) stays before.

In the target, the ori IS in the group → the group's order [li][ori][or][andi] — determined by the group's LUID order? The li's LUID (at the call) vs the ori's LUID (the arg expansion at the call): if the arg is expanded AFTER the constant's conversion → the li's LUID < the ori's LUID → [li][ori] ✓.

So the group order = LUID order, and the li is created first because in expand_call the args are converted in order (a0 first!) and the a1 arg's expression... hmm, but the a1 arg's expression would have been expanded earlier as a separate statement (unless it's expanded at the call).

Ugh, circular again. BUT: the key takeaway is that the target's ori is part of the call's arg expansion. In cand03 the ori is a separate statement. So I need the ori INSIDE the arg expression.

And the chain needs vol's "2 sets"...

AH WAIT!!! What if I do this:
```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
...
{
    s32 flg = 0x3000;
    vol = vol | flg;          /* the ori: writes vol (multi-set) */
    func_8002D4C8(0x93E, (vol | x) & 0xFFFF);
}
```
= cand03. The ori writes vol (which has 2-3 sets) → should not be boosted. Yet it's early.

Hmm, so maybe the ori's early position in cand03 is NOT about the boost but about the fact that it's a separate statement with an earlier LUID, and it's NOT part of the call group, so it's scheduled in the normal stream (as early as possible).

In the target, the ori IS in the group → it's scheduled within the group → after the li.

So the requirement stands: the ori must be part of the call's arg expression.

And the chain requirement: vol must have 2 tree-level defs.

COMBINATION IDEA: what if the ori is in the arg expression AND vol has a 2nd def that is a DEAD statement (no emitted code)? At the tree level, a dead assignment `vol = vol | 0x3000;` would emit the ori... unless the value is later overwritten! E.g.:

```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
vol = vol | 0x3000;      /* dead: vol is reassigned below */
...
{
    s32 flg = 0x3000;
    vol = vol | flg;      /* hmm, this changes the value */
}
```
Hmm, if the ori is at the call (the arg expression), then vol's value at the call is the division's result ✓, and the earlier `vol = vol | 0x3000` would be a DEAD assignment (overwritten) → gcc's DCE removes it → no insn ✓ but also no 2 sets at the RTL level (the tree-level 2 defs might still affect the tree optimizer's rewrite!).

Hmm! But wait, in cand05 the arg expression's ori was folded, so the arg's ops were [or, andi] and the separate statement's ori was emitted → cand03-like.

I want: the arg expression to KEEP its ori (not folded) AND a separate 2nd def of vol that is dead (removed at the RTL level but maybe affecting the tree optimizer).

How to avoid the fold of the double-or? Use DIFFERENT expressions that are equal but not syntactically identical: e.g. `vol | flg` (flg = 0x3000) in the arg expression and `vol | 0x3000` in the dead statement → the tree optimizer's CSE would see them as the same expression (0x3000 == flg after propagation) → hmm.

Use `vol | 0x3000` in the arg and `vol | (0x1000|0x2000)` in the dead statement → the tree optimizer folds 0x1000|0x2000 = 0x3000 → same.

Hmm, use `(vol | flg)` in the arg where flg is a variable that's 0x3000, and the dead statement is `vol = vol | 0x3000` — after constant propagation flg = 0x3000 → same expression → CSE'd → the dead one is removed (DCE) ✓ and the arg's ori stays ✓!!! And vol has 2 tree defs → maybe the chain's rewrite is blocked ✓.

Wait, but in cand05 the dead statement `vol = vol | 0x3000` was NOT dead (the arg expression used vol afterwards) → it wasn't removed, and the arg's double-or was folded.

Now: if the dead statement is overwritten before use:
```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
vol = vol | 0x3000;       /* DEAD (vol is reassigned? no!) */
```
Hmm, vol is NOT reassigned later — the arg expression uses vol (the division's result). So `vol = vol | 0x3000` is NOT dead — it changes vol's value! ✗

Unless the arg expression uses a DIFFERENT variable:
```
s32 vol;      /* the division result */
s32 vol2;
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
vol2 = vol | 0x3000;    /* hmm, this is a use of vol → not dead */
```

Hmm, I need: a dead write to vol that the tree optimizer keeps, without changing the value used later. E.g.:
```
vol = ((0xA0 - ax) * 0xA0 ...
vol = vol | 0x3000;     /* dead */
vol = ((0xA0 - ax) * 0x7F) / 0xA0;   /* recompute?? */
```
✗ (recomputing emits the division twice).

Hmm. What about:
```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
vol = vol | 0x3000;         /* dead-ish */
... the arg expression uses a DIFFERENT variable with the original value:
```
The original value is lost.

Hmm! Unless the arg expression uses the pre-or value via a copy:
```
s32 vol;
s32 vol2;
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
vol2 = vol;             /* the copy (coalesced, no insn) */
vol = vol | 0x3000;     /* dead (vol is not used afterwards) → removed */
... arg: ((vol2 | flg) | x) & 0xFFFF
```
Hmm! Here: vol2 = vol (a copy, coalesced → no insn), then vol = vol|0x3000 (dead → removed at the RTL level, but at the tree level it exists → vol has 2 defs ✓). And the arg expression uses vol2 → the ori is at the call ✓.

Hmm, but wait: vol = vol|0x3000 is dead only if vol isn't used later. vol2 was assigned BEFORE, so vol's later value is unused → the assignment is dead → the tree optimizer's DCE removes it → vol has 1 def again ✗ (at the tree level, after DCE, vol has 1 def).

Hmm! But the tree optimizer's DCE happens in the SSA passes, which might be AFTER the rewrite I care about. The rewrite (the algebraic simplification of the division) — when does it happen? If it's in the early tree optimizer (tree-ssa-math-opts or fold), the order matters.

This is getting really deep. Let me just TRY things empirically — that's cheaper than theorizing. I have ~13 min left on item 2's budget (until 19:17), then I need to decide (wall or keep going; the developer's rule says a wall needs ≥30 tries; I've done 6).

Hmm, the 30-try requirement is expensive. Let me think about the time budget: 7 items × 30 min = 3.5 hours. That's a lot but the task says 20-30 min per item.

Given the developer's rule (a WALL needs ≥20 min AND ≥30 scored tries), and my remaining items, I should aim to crack as many as possible quickly and, for walls, do 30 tries.

Let me continue with item 2 with a batch of variants. Let me try 4 at once:

V-a: cand01 + a dead 2nd set:
```
            vol = ((0xA0 - ax) * 0x7F) / 0xA0;
            vol = vol | 0x3000;
            x = ...
            { s32 flg = 0x3000; func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF); }
```
= cand05 (score 2). ✗ (already tried)

V-b: cand03 with the ori statement BEFORE the x chain:
```
            vol = ((0xA0 - ax) * 0x7F) / 0xA0;
            vol = vol | 0x3000;      /* early */
            x = (x + 0xA0) / 0x14;
            ...
            { s32 flg = 0x3000; func_8002D4C8(0x93E, (vol | x) & 0xFFFF); }
```
Hmm, wait — the value: vol already has 0x3000 → the arg (vol|x)&0xFFFF ✓ same value! And the ori is early in the source → scheduled early (worse).

Hmm, cand02 was exactly this (with `vol = vol | 0x3000` early) → score 7. ✗

V-c: cand03 but with the ori statement AFTER the call?? ✗

V-d: cand03 but the flg block restructured so the ori is inside the call's arg expression and the 2nd set is on `x`:
```
            x = (x + 0xA0) / 0x14;
            if (x == 0x10) { x = 0xF; }
            x = x << 8;
            { s32 flg = 0x3000; func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF); }
```
= cand01 ✗

Hmm.

NEW IDEA: What if the fix for the tail is to make the LI not a "single-set boosted" insn? I.e., give a0 TWO sets so the li isn't boosted! How? If a0 is set by something else before the call... e.g. `a0` is the first argument; if the first argument were a VARIABLE (not a constant), gcc would load it into a0 — and the load would be a separate insn.

Hmm, but the target's a0 = 0x93e via `li $4,0x93e`.

What if the first argument is `0x93E` but written such that gcc uses 2 insns (e.g. `li $4,0x93e` is 1 insn; if it were a bigger constant it'd be lui+ori)? ✗ (the target has 1 insn).

Hmm, so the li is single-set in the target and boosted → first ✓. And in cand03, the ori is also boosted and comes first. Two boosted insns → the tie is broken by LUID → the ori (earlier LUID) first ✗.

So I need the ori to NOT be boosted → it must write a multi-set register → it must be part of the arg expression (writing a1).

=> I MUST have the ori at the call. => The chain must be fixed differently.

So: what makes the chain right? In cand03/cand05, vol has 2 tree defs. In cand01, 1 def. The difference in the chain: the vol chain's ORDER relative to the x chain.

Hmm, what if I fix the chain by making the x chain LATER instead? E.g., in cand01, the x chain is scheduled first because its consumer (the branch) is early. What if the x computation were moved AFTER the branch... hmm.

Actually, hold on! What if I move the vol computation AFTER the x computation but keep the ori at the call? Then:
```
x = (x + 0xA0) / 0x14;      /* the x chain first in the source */
if (x == 0x10) { x = 0xF; }
x = x << 8;
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
{ s32 flg = 0x3000; func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF); }
```
The vol chain is now right before the call → its consumer (the ori at the call) is very close → the vol chain would be scheduled LATE (after the x chain) ✗.

Hmm, but the x chain's consumer (the branch) is right before the vol computation → the x chain is urgent → x first ✗.

OK so the vol chain needs an EARLY consumer (before the branch).

What if the vol computation is moved to the TOP of the function (before the if)? Then it's in a different block... the vol chain would be in the entry block → scheduled early ✓✓! And its consumer (the ori at the call) is late → hmm, but the chain's LUIDs are early.

Hmm! In the target, the vol computation IS early in the source (before the x computation) but the x chain got scheduled first in cand01. So the source position isn't enough; the priority is.

Ugh. What determines the priority? In gcc's sched1, the priority is computed by `init_sched` → `init_priority` → for each insn, `priority = ...` based on the "dependency chain" and the "birth" of the value. Specifically, gcc's sched1 computes the priority as the number of insns on the longest path from this insn to the end of the block (roughly), plus adjustments.

The vol chain's path to the end: the vol chain → ori → or → jal = 3 insns after. The x chain's path: the x chain → branch (2 insns). So the x chain is SHORTER to the end → higher priority → scheduled first ✓ (cand01).

In the target, the vol chain → asm → ori → or → jal. Hmm, the asm adds an insn but doesn't shorten the path. So the vol chain should still be lower priority ✗.

Hmm, but the asm has priority 1 (the lowest) — so the asm is scheduled LAST-ish, and the vol chain (which must precede the asm) is scheduled before it → the vol chain is pulled EARLY (to leave room for the asm at the end)?! Hmm, that's plausible: the asm's low priority means everything feeding it gets scheduled early to satisfy the asm's dependency while the asm itself goes late.

Hmm, whatever the mechanism: in cand03, the ori statement (which is the vol chain's consumer) is a separate statement → the vol chain's path to the end is shorter → hmm, but the vol chain came FIRST in cand03.

Hmm, in cand03 the vol chain's path: vol chain → ori → (the arg's or) → jal = 3. The x chain's path: x chain → branch = 2. So x should be first ✗ (but the vol chain was first).

So the path theory fails too.

What differs between cand01 and cand03 for the vol chain? In cand03, the vol variable is written twice. Hmm, so the vol chain's result (the division) feeds a copy into vol (a pseudo) which then feeds the ori. So the chain is: div → copy → ori. One extra insn. In cand01: div → ori.

Hmm, and the target: div → asm → ori.

So both cand03 and the target have an extra insn between the div and the ori, while cand01 doesn't! And in cand03/target the vol chain comes first.

So the extra insn (the copy/asm) makes the vol chain's path longer (4 vs 3) → LOWER priority → should be later ✗. Hmm, opposite.

OK, alternative: maybe it's about the "birth": in cand01, the division's result is used directly by the ori → the division's result pseudo is born and dies quickly. In cand03, the division's result is copied to vol (an extra pseudo). Hmm.

Honestly, maybe the real mechanism is the "birth boost" of the CONSTANT: the magic M = 0x66666667 is a constant (single-set). In the target, the M's lui/ori are scheduled early (before the vol chain) ✓ (target[60],[61] = lui/ori). In cand01, mine[60],[61] = lui/ori too ✓. So the M's boost is the same.

Hmm, the ORDER difference: target: [lui][ori M][li 160][subu][sll][subu][mult vol][mfhi]... vs cand01: [lui][ori M][addiu 160-|x|][mult (160-|x|)*M][mfhi][li 160][subu][sll][subu][mult vol*M]...

So in cand01, the x+160 (addiu) and its mult come first, then the vol's numerator. In the target, the vol's numerator comes first.

Both chains are ready at the same time (independent). The tie-break: LUID order (the vol chain is first in the source in both!) — hmm, in cand01 the source has vol first too! But the x chain won.

Unless in cand01 gcc REORDERED the source (the tree optimizer reassociated the expressions!). Hmm! In cand01, the vol's expression might have been rewritten by the tree optimizer into a form that depends on the x chain: e.g. vol = 127 - (ax*127)/160 hmm.

AH, that's a thought: maybe the tree optimizer rewrote the vol expression in cand01 (using the relation between 160-ax and x) into something involving the x chain, creating a dependency → the x chain must come first!

Specifically: the tree optimizer might have rewritten `((0xA0 - ax) * 0x7F) / 0xA0` into `127 - (ax * 127) / 160` (valid when 0 ≤ ax ≤ 160 — and the code checks ax < 0x9F+1 = 0xA0 ✓✓✓ THE RANGE IS KNOWN!).

YES! The condition `((L.sxy[0] + 0x9F) & 0xFFFF) < 0x13F` doesn't directly give ax ≤ 160, but `x = (s16)L.sxy[0]` and the check `(u16)(x + 0x9F) < 0x13F` implies x+0x9F ∈ [0, 0x13E] → x ∈ [-0x9F, 0x9F] = [-159, 159]. So |x| ≤ 159 < 160 ✓✓.

So gcc CAN prove 0 ≤ 160-|x| ... hmm, |x| ≤ 159 → 160-|x| ≥ 1 ✓. And then (160-|x|)*127/160 = 127 - |x|*127/160 (exact? (160-a)*127/160 = 127 - a*127/160; with integer division, floor((160-a)*127/160) vs 127 - floor(a*127/160): these are equal iff ... (160-a)*127 = 160*127 - a*127 → floor((160*127 - a*127)/160) = 127 + floor(-a*127/160) = 127 - ceil(a*127/160). And 127 - floor(a*127/160) differs by 1 when a*127 % 160 != 0. So the rewrite isn't exact ✗ — gcc wouldn't do it.

Hmm. But cand01's chain had an EXTRA mult of (160-|x|)*M... and the vol = (hi(volnum*M)>>6) - sign. So the vol was computed the same way as the target ✓. The extra mult (160-|x|)*M with >>3 — that's a /20-style division of (160-|x|)!

Hmm! What would compute (160-|x|)/20? Nothing in the source!

Hmm, unless the diff alignment misled me and mine[63] = mult $4,$6 is actually the x division (x+160)*M. Yes, that's what I concluded (mine[62] = addiu $4,$7,160 = x+160). OK so no extra division. Good.

So the ONLY difference is the ORDER of the two chains (and the register allocation: the magic in $6 vs $4, the ax in $7 vs $6).

And the register difference: mine has ax's sign-extended value in $7 and the magic in $6; the target has the sign-extended x in $6 and the magic in $4. Hmm, the target's $4 (a0) holds the magic — but a0 is the call arg register! Later the li $4,0x93e overwrites it ✓ (the magic is dead by then).

So the target's allocation gives the magic $4 and the signed x $6; mine gives the magic $6 and the signed x $7. Both are "spilled to callee-saved"? No, $4/$6/$7 are all caller-saved. The difference is the local-alloc order.

Hmm, and the target has the vol in $5 (the pinned ax's register) — since ax is dead after |ax| is computed ✓.

So in cand01, why did the magic get $6 and the x $7? Because the chains are ordered differently, the allocation differs.

OK. So: to fix cand01's chain, I need the vol chain to be scheduled BEFORE the x chain. The vol chain's result is consumed by the ori at the call; the x chain's by the branch.

In cand03, the ori statement (between) made the vol chain first.

What if I insert a statement between the vol computation and the x computation that uses vol in a way that's dead? E.g.:

```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
if (vol == 0x7FFFFFFF) { vol = 0; }    /* dead in practice, but emits a compare+branch! */
```
✗ (emits insns).

Hmm.

What if the extra use of vol is in the x computation itself?! E.g.:
```
x = (x + 0xA0) / 0x14;
```
→ what if it were `x = (x + 0xA0 + (vol & 0)) / 0x14;` → folded ✗.

What about `x = (x + 0xA0) / 0x14;` → `x = (x + 0xA0) / (0x14 + (vol - vol));` folded ✗.

Hmm, what about making the vol computation's RESULT used by the x computation in a value-preserving way? Hmm: x = (x+160)/20 — no vol.

Hmm, what about this: what if I change the vol expression so that it doesn't need the "boost" — i.e., write the vol computation so that gcc's expansion matches the target's directly? The target's chain computes (160-|ax|)*127 explicitly. In cand01, gcc ALSO computed it explicitly (sll+subu) ✓ — the difference was only the ORDER of the chains and the register allocation.

So maybe I can fix the order by a small change: e.g., making the x chain's computation happen EARLIER in the source (before the vol computation) — then the x chain's LUIDs are earlier → the x chain first ✗ (we want vol first).

Or making the vol computation's LATER... no.

Hmm, what about the SCHEDULER's tie-break: when two chains are ready, sched1 picks by priority; if equal, by LUID. The vol chain is first in the source → earlier LUIDs → if the priorities are equal, the vol chain goes first. In cand01 the x chain went first → the x chain had a HIGHER priority.

The x chain's priority is higher because its consumer (the branch) is closer to the end? or because the branch is a "jump" with high priority?

Hmm, what if I could make the x chain's consumer later? E.g. the branch `bne $6,$2,$L62` — the x chain feeds it. If the x chain's result were used later...

Hmm, what if the `if (x == 0x10) x = 0xF;` were restructured so that the comparison happens later? E.g. `x = (x == 0x10) ? 0xF : x;` — the same.

OK, let me try a few things in parallel and stop theorizing. Variants to try (all keeping the ori inside the arg expression = cand01's tail):

V1: cand01 + the x computation moved AFTER the vol computation? It already is.

V2: cand01 with the `if (x == 0x10) { x = 0xF; }` written as `if (x == 0x10) x = 0xF;` (no braces) — no change.

V3: cand01 with the vol expression written as `vol = (0xA0 - ax) * 0x7F / 0xA0;` (precedence change) — the same tree.

V4: cand01 with the vol expression written as `vol = ((0xA0 - ax) * 127) / 160;` (decimal) — the same.

V5: cand01 with the x computation written as `x = (x + 0xA0) / 20;` (decimal) — the same.

V6: cand01 with the vol computation moved to the TOP of the else-block (before the RotTransPers call) — then the vol chain is in the entry block → scheduled early? Hmm, but the vol computation depends on ax (which depends on L.sxy[0], which depends on RotTransPers) → so it can't move before the call.

V7: cand01 but with `x = (x + 0xA0) / 0x14;` changed to use the vol in a value-preserving way that creates a dependency between the chains: e.g. `x = (x + 0xA0) / 0x14;` → hmm.

Hmm, V8: what about giving the x chain a LATER consumer by restructuring the if:
```
if (x == 0x10) { x = 0xF; }
x = x << 8;
```
→ the branch compares x (the /20 result) — the branch is right after. What if I write:
```
x = x << 8;
if ((x >> 8) == 0x10) { x = 0xF00; }
```
Hmm, that changes the code (the target does `li $6,15; sll $6,$6,8` = 0xF00 ✓ interesting!). The target's block: [li $6,15; sll $6,$6,8] → x = 0xF00 ✓. And the source is `x = 0xF; x = x << 8;` → 15<<8 = 0xF00 ✓.

Hmm, so writing `x = 0xF00;` directly (instead of 0xF then <<8) might change the code: the target does li 15 + sll 8 (2 insns) — so the source must be `x = 0xF; x = x << 8;` ✓ (as is).

OK, let me try a DIFFERENT strategy for the chain: what if the vol chain's boost comes from the launder's "asm" being a separate EARLY statement — and I can emulate that with a plain-C statement that uses vol early and emits nothing?

Emits nothing = the value is used in a way that's optimized away at the RTL level but not at the tree level. Hmm: what if vol is used in a comparison with itself: `if (vol != vol) { }` → the tree optimizer folds `vol != vol` to false → the whole statement disappears → vol's use disappears at the tree level → but the tree-level DSE/rewrite order might matter!

Specifically: if the tree optimizer's algebraic rewrite of the division happens BEFORE the DCE of the dead comparison, then the comparison's presence would block the rewrite (the rewrite requires the division's result to have a single use!).

That's plausible! gcc's rewrite of `((160-ax)*127)/160` might require a single use of the division's result. With an extra use (even a dead one), the rewrite is blocked.

But the dead comparison would be removed by the tree DCE (which runs early — the "fre" pass or tree-ssa). Hmm, if the rewrite happens in the same pass as the DCE, the order within the pass matters.

Let me just TRY: cand07 = cand01 + `if (vol == vol) { x = x; }`? Hmm, that's silly. Let me use something that gcc folds late...

Hmm, simpler: what about `vol = vol | 0;`? — folded at fold-time (early) → the use disappears.

What about a use that survives to the RTL but emits nothing? Hmm.

What about `x = (x + 0xA0) / 0x14;` and the extra use of vol inside the SAME expression: `x = (x + 0xA0 + vol - vol) / 0x14;` — folded early.

Hmm.

What about the pinned ax? `ax` is a variable with 2 sets. What if I make the vol computation use `ax` twice, e.g. `vol = ((0xA0 - ax) * 0x7F) / 0xA0;` — one use.

Hmm, what if I add a use of the VOL in the x computation: `x = (x + 0xA0) / 0x14;` → hmm, what if x's computation used vol in a value-preserving way that gcc can't fold but that doesn't emit extra insns... impossible.

OK, let me try the "extra use" idea with the tree-level DCE timing:

cand07: cand01 + a dead use of vol placed right after the vol computation:
```
            vol = ((0xA0 - ax) * 0x7F) / 0xA0;
            if (vol == 0x12345678) { x = 0xF; }    /* dead-ish */
```
Hmm, that emits a compare + branch ✗ (the target has no such insns).

Unless the branch is folded away: `if (vol == vol)` → folded at fold-time → gone.

Hmm.

Let me step back and consider: maybe the chain difference in cand01 vs the target is NOT about vol's uses but about the LAUNDER's effect on the TREE optimizer: the asm statement in the middle of the function acts as a BARRIER for the tree optimizer's reassociation! gcc's tree optimizer (in the pre-SSA or SSA passes) may not do algebraic rewrites across an asm statement (asm = "opaque" for the optimizer). Hmm, actually gcc's tree optimizer DOES handle asms (they're just statements), but some optimizations are disabled around volatile asm. A NON-VOLATILE asm with a "0" tie: gcc treats it as a normal statement with an output.

Hmm, but the tree optimizer's rewrite of the division wouldn't be blocked by a later asm anyway.

Hmm, unless the rewrite is in the RTL "combine" pass, which CAN be blocked by an asm (combine doesn't look across asm insns? it does).

Honestly, the empirical difference: cand01's vol chain is scheduled after the x chain; the target's before. Let me try to find a C-level way to reorder the two chains.

IDEA: swap the order of the two computations in the source AND swap the roles so that the vol computation comes first in the source and is needed earlier...

Hmm, hold on: what if the ORDER of the chains in the schedule is determined by the ORDER of their "birth" (the LUID of their first insn) and the priorities are equal? Then in cand01, the vol chain's first insn should be earlier (the vol statement is first) → the vol chain first ✗ (it's second). So the priorities differ.

The x chain's priority is higher because of the branch? Let me test: what if I move the x computation to AFTER the vol computation AND the branch... it already is.

What if I put the x computation's RESULT use later: e.g. restructure so that the comparison `x == 0x10` happens after more code? The structure is:
```
x = (x + 0xA0) / 0x14;
if (x == 0x10) { x = 0xF; }
x = x << 8;
{ ... call ... }
```
What if I write:
```
x = (x + 0xA0) / 0x14;
x = x << 8;
if ((x >> 8) == 0x10) { x = 0xF00; }
{ ... call with x ... }
```
Hmm, that changes the emitted code (the target computes x<<8 in the delay slot and 15<<8 in the other block). ✗ probably.

Hmm OK. Let me try yet another thing: maybe the priority difference comes from the fact that in cand01, the x chain's result (x) is used by the branch which is in the same block, while the vol chain's result is used by the ori at the call. What if I make the vol chain's result used by something in the same block, earlier?

What if the vol computation's result is used in the x computation's EXPRESSION in a value-preserving way? Like:
`x = (x + 0xA0) / 0x14;` → hmm, what if x's computation used vol: `x = ((x + 0xA0) / 0x14) + (vol - vol);` → folded ✗.

What about: `x = (x + 0xA0) / 0x14;` and then `if (x == 0x10) { x = 0xF; }` — what if instead the vol is involved in the comparison: `if (x == 0x10 && vol == vol)` → folded ✗.

Hmm hmm.

Let me try: what if the vol chain is boosted by using vol in the CONDITION of the if? E.g.:
```
if (L.flag >= 0 && ... ) {
    ...
    vol = ((0xA0 - ax) * 0x7F) / 0xA0;
    ...
}
```
no.

OK. Time check: 19:07. I've used 20 min on item 2. Let me do a couple more quick experiments in parallel (cheap) and then decide.

Quick experiments (batch of 4):
E1: cand01 with the vol computation moved AFTER the x computation (so the vol chain is last in the source but its consumer is at the call) → tests whether the source order drives it.
E2: cand01 with the x computation moved BEFORE the vol computation (i.e. the x chain first in the source) → the opposite.
E3: cand01 with the vol computation's expression spelled `vol = (0xA0 - ax) * 0x7F / 0xA0;`.
E4: cand01 but with `ax` NOT pinned?? (the pin is a lever of another kind — the row kind is launder, so pins may stay; but removing the pin is "removing a lever" — allowed? The constraint says "levers of other kinds the def already had may stay, never added" — removing is allowed I think, but it changes the match. The target HAS the pin ($5 = |ax|). So the pin must stay to match.)

Let me do E1, E2, E3.

Hmm, E1/E2 are cheap and informative. Let me also think of E5: what if the vol computation is moved into the `if` block's condition area...

Let me run E1, E2, E3 in parallel.

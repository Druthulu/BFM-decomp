---
ts: 2026-10-22T01:07:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_hSvgx0ZSmMctgpxzCSrT
---
P1 (score 6, 39 ins) vs target (40 ins):

The difference: the target has `move v1,v0` (ins 24) — the call result copied into $3 (v1) — then the tests on v1. P1 keeps the call result in $2 (v0) and tests it there.

So the target's `ret` variable is in $3 (v1) while the RESULT_DECL/return value is $2. In P1, `ret` stayed in $2 (v0) — because the RESULT_DECL wasn't needed yet, so $2 was free for ret.

To reproduce: the call result must be copied to $3. In the target, `ret` is in $3 because $2 is reserved for the RESULT_DECL (the return value). Hmm, but the RESULT_DECL's set is late (ins 29-33) — so $2 is free at ins 24 in the target too. Yet the target copies $2 → $3.

Why would gcc copy the call result to $3? Because the call result's pseudo is in $2 (the call's return register) and the copy to a variable happens when the variable is a separate pseudo that gets allocated $3. In our compile, the variable `ret` was coalesced with the call result pseudo ($2) — the copy was elided.

So the target wants a COPY: `move v1,v0` — i.e. the "ret" variable is a distinct pseudo allocated to $3, and the copy from the call result ($2) is NOT elided.

Why is the copy not elided in the target? Because the call-result pseudo and `ret` are different pseudos that got different registers. In ours, they got the same ($2) and the copy was coalesced away.

How to force the copy? If the value is used in a way that prevents coalescing... e.g. if `ret` is used TWICE (the target uses v1 twice: `beqz v1` and `andi v1,v1,0x8000` — but that's still one live range).

Hmm, in ours (P1), the ret value is used twice too (ret != 0 and ret & 0x8000) but it stayed in $2.

The difference: in the target, $2 must be reserved for the RESULT_DECL. In ours, the RESULT_DECL's set is at ins 29+ — after the ret's uses — so $2 is free at ins 24 → the ret pseudo gets $2.

So again: the same "live range" story. In the target, the RESULT_DECL is allocated $2 from the start (its pseudo is live from the beginning? the RESULT_DECL's live range in gcc = from the function entry to the return (it's live-out on all paths). Yes! The RESULT_DECL is live from the function entry (it's the return value, live-out) → $2 is reserved from ins 0 → so the call result (which is also in $2 as the call's return reg) must be copied out to $3 ✓✓✓.

In ours, gcc must have decided the RESULT_DECL is NOT live at the entry (because it's set on all paths later) → so $2 was free → the ret pseudo took $2 and the copy was elided.

Hmm! Why would the RESULT_DECL be live from the entry in the target but not in ours? Because in the target, the RESULT_DECL is set... hmm. Actually gcc's RESULT_DECL live range: it's live-out of the function; gcc's local-alloc/global-alloc computes the live range of the RESULT_DECL as [where it's set .. function end] — it's set at the return points. Hmm.

But the target's structure: the return value is computed in $2 at ins 29-33 and $2 = 0 in the delay slots. So the RESULT_DECL is set at several points.

Hmm, so why is $2 reserved at ins 24 in the target?

Because of the CALL at ins 22: the call's return value is in $2 (v0). After the call, $2 holds the result. If the RESULT_DECL were also $2, there'd be a conflict... no.

Hmm, let me think about the target's ins 20-24:
```
20: li a0,1
21: addiu a1,sp,16
22: jal func_80149290       (the call)
23: move a2,s0              (delay slot)
24: move v1,v0              (the call result copied to v1)
```
Interesting: the delay slot of the call at ins 22 is `move a2,s0` — the third argument setup. And then `move v1,v0` after the call.

In P1 (mine), ins 22 = the call, ins 23 = `move a2,s0`?, and ins 24 = `beqz v0` — so the call result stayed in $2.

So the target copies the result to $3. Why? Because the source's `ret` variable is a separate variable from the call's return pseudo, and gcc didn't coalesce them.

In ours, gcc DID coalesce (the copy `move v0,v0`... wait, the copy would be `move $3,$2`; the coalesce merged them).

Coalescing happens in reload1: it merges the copy's src and dst when possible. To prevent it, the copy's src ($2, the call result) must be live elsewhere or the dst must be constrained.

Hmm! Here's the thing: in the target, the RESULT_DECL is $2 and the call result is also $2 (hard reg) — so the copy `move $3, $2` can't be coalesced because $2 is a hard reg holding the call result, and $3 is the variable's reg.

In ours, the variable `ret` got $2 — meaning the call result pseudo (a pseudo after the call) was allocated $2 and coalesced with `ret`.

So: to get the copy, the `ret` variable must NOT be allocated $2. What makes gcc allocate $2 to the call-result pseudo? The call's return value pseudo prefers $2 (the call's return register).

Hmm, in the target the call result ALSO is in $2 (ins 24 copies $2 → $3). So in the target, the call result pseudo is in $2 AND the `ret` variable is in $3, with a copy between. In ours, the copy was elided by coalescing.

Why didn't the target coalesce? Because in the target, the RESULT_DECL is also in $2 and lives across... hmm, coalescing `move $3,$2` would require moving the call result to $3 — the call result pseudo is a pseudo (not hard), so it CAN be moved to $3 — but then the copy would be `move $3,$3` — hmm, the coalesce would assign the call-result pseudo to $3 and delete the copy. That's what happened in ours.

To prevent that, the call result pseudo must be forced to stay in $2 — e.g. if it's live across something that needs $2, or if it has a preference.

Hmm, what if the source keeps the call result in a variable AND the RESULT_DECL is set from that variable? Then the RESULT_DECL ($2) would conflict with the call result ($2)... hmm, but the target does exactly that: the RESULT_DECL is $2 and the value returned is computed later.

So in the target: after the call, $2 = the call result; the code copies it to $3; then $2 is reused for the RESULT_DECL's computation (ins 29+). So $2's liveness: [call result] then [result value]. Fine.

In ours: the call result stayed in $2 through ins 24-27 (the tests) and then $2 was reused for the byte load (ins 29) ✓ (the same register, sequentially). The only difference is the copy `move v1,v0` at ins 24 and the tests on v1.

So the target wants: the call result copied to $3 and the tests on $3. The copy is what makes the difference.

How can I force a copy? Ideas:
(a) Use the call result in TWO places where one use is in a different context... no, coalescing doesn't care.
(b) Make the call result's value also used by the RESULT_DECL? no.
(c) Prevent coalescing by making the variable's live range overlap with the call result's? Coalescing happens because the copy's src is dead after the copy (the call result pseudo dies) and the dst is live. Coalesce would move the src into the dst's reg. If the src's reg ($2) is needed by something else in the src's live range... hmm, the src is dead right after the copy.

Hmm, coalesce in reload1: "coalesce" merges the copy's operands when the copy is `move r1, r2` and r1 is dead afterwards (or r2 is dead). It requires the reg to be available.

In the target, the copy was NOT coalesced. Why? Because $2 (the call result) is the call's hard return register? Hmm — in gcc, the call's result is a pseudo that prefers $2 (the return register), but it's not hard.

Hmm, but hold on: maybe the target's `ret` variable is $3 because the RESULT_DECL is $2 and the RESULT_DECL is live from the function entry (live-out) — so $2 is occupied from ins 0 → the call result pseudo can't take $2 → it takes $3?! But the call result IS in $2 at ins 24 (the copy source) — that's the call's return register (hard). Hmm: the call returns in $2 (hard); the pseudo for the call result is then copied... in the target: `move v1,v0` — so the pseudo (call result) was assigned $3 and the copy from the hard $2 remains ✓✓. That's it: the call result pseudo got $3 (because $2 was reserved for the RESULT_DECL), and the copy from the hard $2 → $3 remains ✓.

So: in the target, $2 is reserved (the RESULT_DECL) from the start of the function → the call-result pseudo takes $3.

In ours, the RESULT_DECL is NOT reserved early → the call-result pseudo takes $2 → the copy is elided.

So the question: why is the RESULT_DECL reserved from the entry in the target?

In gcc, the RESULT_DECL's live range: it's live-out → live from the point where it's defined. gcc's local-alloc/global-alloc treat the RESULT_DECL as live across the whole function if it's set on some path... Hmm, in gcc 2.7.2, the RESULT_DECL pseudo's live range = [the earliest set .. the end]? Typically gcc gives the RESULT_DECL a live range spanning from the first assignment to the end, and hard reg $2 is then reserved from that point.

In the target, the RESULT_DECL's first set is... ins 28 `move v0,zero` (in a delay slot) — that's at ins 28, not the entry. Hmm, but the call-result pseudo is used at ins 24 — before ins 28. So $2 could be free at ins 24 ✗.

Hmm, unless the RESULT_DECL's live range in gcc 2.7.2 is the WHOLE function (from the entry) because it's live-out on every path. In gcc, a pseudo that is live-out of the function is marked as live at the entry (the "live at entry" concept) — the RESULT_DECL is set on all paths, so it's not live IN, but its live range starts at the first set.

Hmm, but gcc's `live_at_entry` / the global-alloc "prefer v0" note from the previous coder's analysis: "the call-result pseudo (refs 4, live 7 -> pri 11428; 'prefers v0', it is the call's hard-reg copy) outranks the RESULT_DECL (refs 3, live 4 -> pri 7500, also 'prefers v0')".

So in ours, the call result took $2 (higher priority). In the target, the RESULT_DECL took $2.

The allocation priority: the RESULT_DECL's priority must be raised, or the call result's lowered. The previous coder says: "Raising the RESULT_DECL's priority (more refs / shorter live) is not reachable without changing the ROM's instruction count".

Hmm! But wait — what if the RESULT_DECL has more refs in a different spelling? E.g. if the source has MORE return statements (each `return X` is a ref of the RESULT_DECL). In the target, there are 3 return paths: `return 0` (twice) and `return (byte != 0x15)`.

Hmm, the notes say P1/P2 (direct returns) gave 6.

What if the source has MORE returns (e.g. 4-5 return statements)? That raises the RESULT_DECL's refs → higher priority → $2 ✓. But it also adds instructions (each return path might add a `move v0,zero`)... unless they're merged.

Let me think about the target's return structure:
- ins 25 `beqz v1,+0x88` → ins 34 `move v0,zero` (the return-0 block) — so the "ret == 0" path jumps to ins 34.
- ins 27 `beqz v1,+0x8c` → ins 35 `lw ra` — with the delay slot ins 28 `move v0,zero` → so this path sets $2 = 0 and jumps to the epilogue.
- ins 32 `j +0x8c` with the delay slot `sltiu v0,v0,1` → the final path.

So there are 2 distinct "return 0" paths (ins 34 and ins 28) and one value path. Interesting: the `move v0,zero` at ins 28 is in the delay slot of the beqz at ins 27 (the mask==0 test), and the `move v0,zero` at ins 34 is the shared return-0 block.

So the source might be:
```
ret = func_80133784(1, buf1, (int)buf2);
if (ret == 0) return 0;              /* → the shared return-0 block (ins 34) */
if ((ret & 0x8000) == 0) return 0;    /* → the delay-slot zero (ins 28) */
return *(u8*)(buf2+6) == 0x15;
```
Hmm, the two return-0 paths have different shapes (one jumps to a shared block, the other sets $2=0 in the delay slot) — that's just gcc's scheduling.

The RESULT_DECL's refs: 3 return statements → 3 refs.

To raise the RESULT_DECL's priority above the call-result pseudo, we could add more return statements (more refs) — e.g. splitting the final path:
```
if (ret == 0) return 0;
if ((ret & 0x8000) == 0) return 0;
if (*(u8*)(buf2+6) == 0x15) return 0;
return 1;
```
Hmm, that changes the instruction count (the last part: `lbu; xori; sltiu` vs `lbu; xori; sltiu`?). Let's see: `return *(u8*)(buf2+6) == 0x15` → lbu, xori, sltiu ✓. The alternative `if (byte == 0x15) return 0; return 1;` → lbu, xori(?), beq/bne + li... different ✗.

Hmm. What about adding a redundant `return 0;` path? That changes the code ✗.

Alternatively, LOWER the call-result pseudo's priority: fewer refs. The call result is used twice (ret != 0 and ret & 0x8000). If the source used it ONCE:
```
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) {
    if ((ret & 0x8000) != 0) { return byte != 0x15; }
    return 0;
}
return 0;
```
That's P1 (ret used twice).

What if the source combined the tests: `if (ret != 0 && (ret & 0x8000) != 0)` — ret still used twice.

Hmm, what if the mask test used a COPY: e.g.
```
ret = func_80133784(...);
if (ret == 0) return 0;
tmp = ret & 0x8000;      /* an extra copy → an extra instruction ✗ */
```
✗.

OK, so how do we make the call-result pseudo land in $3 instead of $2?

Alternative: make the "ret" variable's live range longer/shorter, or add another variable that competes for $2/$3.

Hmm, what if we introduce a dummy variable that takes $2 (e.g. another live variable at the call) — then the call result would go to $3 and the copy would remain ✓!! But an extra variable might add instructions.

Hmm! What about the `param_1` (a0)? It's copied to s0 (ins 2 `move s0,a0`) and used at ins 11 `move a0,s0` — so param_1 is in s0 ✓ (already).

What about `s0` being reused: ins 12 `addiu s0,sp,24` — s0 is reused for buf2's address! So s0 changes.

Hmm. What if we make the call result used in a way that requires $2 to be preserved? no.

Let me think about the "prefers v0" note: the call-result pseudo prefers $2 because it's the call's return register (gcc gives the call result a preference for the return reg). The RESULT_DECL also prefers $2.

Priority comparison: the call result: refs 4, live 7 → pri 11428; the RESULT_DECL: refs 3, live 4 → pri 7500. So the call result wins $2.

To flip: increase the RESULT_DECL's refs (more return statements) or decrease its live range, or decrease the call result's refs.

The call result's refs = 4 (the copy + 2 uses + ...?). Hmm.

What if the source stores the call result into a variable and then uses the VARIABLE only once, e.g.:

```
ret = func_80133784(1, buf1, (int)buf2);
if (ret == 0) return 0;
if ((ret & 0x8000) == 0) return 0;
return *(u8 *)((char *)buf2 + 6) == 0x15;
```
ret is used twice (the test and the mask). Hmm.

What if the mask test used a different variable:
```
ret = func_80133784(...);
if (ret == 0) return 0;
mask = ret & 0x8000;      /* an extra copy → extra insn ✗ */
```

Hmm. What about using `ret` in a compound condition that gcc folds: `if (ret != 0 && (ret & 0x8000) != 0)` — ret used twice.

Hmm, what if the source used the call result DIRECTLY in the comparison without a variable?
```
if (func_80133784(1, buf1, (int)buf2) != 0) { ... }
```
then the call result would be used twice (the test and the mask) — but with a copy to a temp? gcc would create a temp for the call result (since it's used twice) → the copy `move v1,v0` might appear ✓✓! Let's think: the source `if (f(...) != 0 && (f(...) & 0x8000) != 0)` would call f twice ✗. But:
```
ret = f(...);
if (ret != 0 && (ret & 0x8000) != 0) return ...;
```
same as before.

Hmm, so the copy `move v1,v0` in the target comes from the "ret" variable being a separate pseudo from the call result. In ours, they're the same pseudo (coalesced). Coalescing happens because the copy is `move ret_pseudo, call_result_pseudo` and reload1 merges them.

To block the coalesce: the call-result pseudo must be live at the copy point in a way that prevents it from moving... Hmm, actually the coalesce tries to assign the call-result pseudo to the same reg as `ret` ($2 → coalescing into $2?) — wait, in ours, `ret` got $2 and the call result got $2 → the copy was removed.

In the target, `ret` got $3 and the call result $2 → the copy remained.

So the question is why `ret` got $2 in ours. Because $2 was free. And in the target, $2 was taken by the RESULT_DECL (or something else).

So: if I can make the RESULT_DECL's priority higher than the call result's, `ret` would get $3 ✓ and the copy would remain ✓.

How to raise the RESULT_DECL's priority? More refs (more return statements) or a shorter live range. The notes say it needs an instruction-count change. Hmm.

BUT: what about the live range? The RESULT_DECL's live range = [first set .. end]. In the target, the first set is at ins 28 (`move v0,zero` in the delay slot) — hmm, in ours (P1) the first set is also early-ish.

Hmm, what if the RESULT_DECL's live range were SHORTER (starting later)? Then its priority goes UP (pri = refs*10000/live). E.g. if the RESULT_DECL's live range starts at ins 29 (the byte load) instead of ins 25, its live would be 40-29 = 11 vs the call result's live 7 → worse. Hmm, pri = refs/live? The note says the call result: refs 4, live 7 → pri 11428; the RESULT_DECL: refs 3, live 4 → pri 7500. Hmm, 4/7 = 0.57, 3/4 = 0.75. Doesn't match "11428" vs "7500"... those numbers look like (refs*10000 + something). Whatever: the RESULT_DECL has fewer refs and a shorter live range but a LOWER priority. Hmm, so maybe priority = refs (weighted) and the "live" is a tiebreak.

Actually the classic gcc priority formula: pri = refs * 10000 / live_range... For the call result: 4 refs, live 7 → 4*10000/7 = 5714; hmm, 11428 = 8*10000/7. For the RESULT_DECL: 7500 = 3*10000/4 ✓ (3 refs, live 4). So the call result has 8 refs (not 4) → 8*10000/7 = 11428 ✓. So the call result has 8 refs, the RESULT_DECL 3.

So to flip: the RESULT_DECL needs pri > 11428 → refs/live > 8/7. With live 4 → refs ≥ 5 (5/4 = 1.25 > 1.14 ✓). With live 3 → refs ≥ 4.

So: the RESULT_DECL needs MORE refs (more return statements) or a shorter live range.

The RESULT_DECL's live range: from its first set to the function end. If the source has a SINGLE return at the very end, the RESULT_DECL's live range = [end, end] → live 1 → pri = 3*10000/1 = 30000 ✓✓!! But a single return changes the code shape drastically ✗ (the target has 3 exits).

Hmm, but the live range is measured in instructions. The RESULT_DECL's live range in the target = from ins 28 (the first set) to ins 39 → live ~11? But the note says live 4 for the RESULT_DECL in ours.

Hmm, this is deep. Let me try empirically: what if I write the source with an extra `return 0;` path to raise the RESULT_DECL's refs, in a way that doesn't change the instruction count? E.g.:

```
ret = func_80133784(1, buf1, (int)buf2);
if (ret == 0) {
    return 0;
}
if ((ret & 0x8000) == 0) {
    return 0;
}
return *(unsigned char *)((char *)buf2 + 6) == 0x15;
```
That's 3 returns (the same as P1). P1 had: `if (ret != 0) { if (...) return ...; return 0; } return 0;` — 3 returns too.

Hmm, so 3 returns = 3 refs. To get 5 refs, we'd need 5 return statements → more instructions ✗.

Alternatively, shorten the RESULT_DECL's live range: the live range starts at the first set of the RESULT_DECL. In the target, the first set is ins 28 (the `move v0,zero` delay slot) — hmm, but that's AFTER the call result's use at ins 24-27. So even in the target, the RESULT_DECL's live range starts after the call result's death. So $2 was free at ins 24 in the target too!

Hmm, so why did the target's `ret` get $3?!

Unless the RESULT_DECL's live range in gcc includes... hmm. Actually, maybe gcc's RESULT_DECL live range starts at the function entry because the RESULT_DECL is "live at entry" when the function's return value is used... no, it's a return value (live-out).

Hmm, alternatively: maybe in the target, `ret` ($3) is a LOCAL pseudo and the call result pseudo is $2 because of the "prefers v0" preference (the call result prefers the return register $2!). And in ours, the copy was coalesced so `ret` and the call result shared $2.

So the difference is the COALESCE, not the allocation priority! In the target, the coalesce did NOT happen. Coalesce in reload1 requires: the copy's src (the call result pseudo) is not live after the copy, and the dst (ret) is not live before the copy, and the reg assignment is compatible.

In ours, the coalesce merged them. Why not in the target? Because of the RESULT_DECL's live range overlapping $2? Hmm: if the RESULT_DECL is allocated $2 and its live range starts at ins 28, then at ins 24 $2 is free ✗.

Hmm, unless in the target the RESULT_DECL's live range starts EARLIER (e.g. at the entry). When would that be? If the RESULT_DECL is set on a path that... hmm.

OK, let me think about it via the "delay slot" evidence: the target's ins 28 `move v0,zero` is in the delay slot of the beqz at ins 27 — that's a RESULT_DECL=0 set. And ins 34 `move v0,zero` is another one (the shared return-0 block). And the final path sets $2 at ins 29-33.

Hmm, so $2 is written at ins 28, 29, 31, 33, 34 — the RESULT_DECL is $2 ✓.

And $2 is read at ins 24 (the call result), 25 (beqz v1 — no, that's v1), 26 (andi v1)...

Hmm, $2 at ins 24 is the call result (hard reg). The call result pseudo would be a copy of the hard $2 → hmm, in gcc, a call's result is a pseudo with a preference for the return register; the pseudo is set by the call itself (the call writes $2 = the result) — so the pseudo is "hard reg $2" at that point (the call's RTL has the result in $2 directly? In gcc 2.7.2, the call insn's output is a pseudo, and the call pattern writes the return value into that pseudo — the pseudo prefers $2).

So the call result pseudo prefers $2 → it gets $2 unless $2 is taken. And `ret` (the variable) is another pseudo → gets $3. And the copy `move $3,$2` remains ✓ — that's the target!

But in OURS, the copy was elided → meaning `ret` got $2 too and the call result pseudo also $2 → they were coalesced. Coalescing `move $2, $2`... hmm, coalesce merges the two PSEUDOS into one reg: the call result pseudo → $2 and ret → $2 → the copy becomes `move $2,$2` → deleted ✓.

So in the target, the coalesce was blocked. Why? Because in the target, the call result pseudo was NOT allocated $2 (it was $2 by preference?) hmm — the copy `move v1,v0` has $2 as the SOURCE → so the call result IS in $2 ✓ and `ret` is in $3. So the coalesce would have wanted to move the call-result pseudo to $3 (to match ret) — but the call result pseudo PREFERS $2 (the return register preference), and reload1's coalesce doesn't move a pseudo out of its preferred hard reg? Hmm, it might (coalesce assigns the dst's reg to the src).

Hmm, actually reload1's coalesce works the other way: it tries to make the copy's dst and src share a reg by changing the ALLOCATION of one of them. If the src (the call result pseudo) prefers $2 and the dst (ret) got $3, coalesce would try to give the src $3 — but the src prefers $2 and its preference is a strong constraint? In gcc, "prefers" is a soft preference (reg_preferred_class), and the coalesce respects it partially.

Hmm, in ours, `ret` got $2 → so the coalesce went the other way: the call result pseudo got $2 (its preference) and ret got $2 too.

The difference must be in the ALLOCATION ORDER: in ours, the call result pseudo was allocated $2 first, then `ret` was allocated... also $2? That can't be — two pseudos can't share $2 if their live ranges overlap. Unless they were coalesced ✓ (that's the point).

So in ours: the call result pseudo → $2 (preferred), and `ret` → $2 via coalescing (the copy deleted).
In the target: the call result pseudo → $2, `ret` → $3, the copy kept.

So the coalesce happened in ours but not in the target. What blocks a coalesce? reload1's coalesce requires that the copy's src and dst have the SAME mode and that the copy is not needed for correctness. It also requires that moving the src into the dst's reg doesn't conflict with the src's other uses/live range.

AH, here's a thought: in the target, the call result pseudo's live range might overlap with something else that occupies $3... no. Hmm, the other way: the coalesce would move the CALL RESULT pseudo to $3 (ret's reg) — but the call result pseudo is the destination of a CALL's output: in gcc, a call's output pseudo CAN be any reg, but the "prefers v0" hint... Hmm, in reload1's coalesce, the call's output pseudo is "hard" in the sense that it must be $2 (the return register) — because the call pattern writes the result into $2 and the pseudo is tied to it? In gcc 2.7.2, the call's output is a pseudo with a hard reg preference; reload may need to move it → it emits a copy from $2 to the pseudo's reg. So if the call result pseudo were allocated $3, we'd see `move v1,v0` right after the call ✓✓ — WHICH IS EXACTLY THE TARGET!

So the target's `move v1,v0` is the reload copy from the call's return register $2 to the pseudo's allocated reg $3!

And in ours, the call result pseudo was allocated $2 → no copy needed ✓.

So the question: why did the target's call-result pseudo get $3 and ours $2? Because in the target, $2 was taken by the RESULT_DECL (which prefers $2) at that point, while in ours $2 was free.

So the RESULT_DECL's live range in the target must overlap ins 24 — meaning the RESULT_DECL is live from the function entry!

When is the RESULT_DECL live from the entry? If the function's return value is live-out on all paths — hmm, in gcc, the RESULT_DECL pseudo is live-out of the function; the "live at entry" concept applies to it only if it's used before being set (impossible).

Hmm, but gcc 2.7.2's global-alloc: the RESULT_DECL gets a preference for the return register; if the RESULT_DECL's live range conflicts with the call result pseudo's preference, the tie is broken by priority.

The previous coder's analysis said: the call-result pseudo (refs 8, live 7 → pri 11428) beats the RESULT_DECL (refs 3, live 4 → pri 7500) → the call result takes $2.

So to flip it: increase the RESULT_DECL's refs (more returns) or decrease its live range.

The RESULT_DECL's live range = 4 in ours. Hmm, that's already short. Its pri = 3*10000/4 = 7500. To beat 11428 we need refs/live > 1.14. With live 4 → refs ≥ 5 (5*10000/4 = 12500 ✓). So ONE more return statement would flip it!

Can I add a return statement without changing the instruction count? Hmm, the target has 3 exits. But the RESULT_DECL's refs count all the sets of the RESULT_DECL, which might be more than the number of return statements (each `return 0` in a different block = 1 set each).

Hmm, what if the source has 4 return statements but gcc merges them into the same code? E.g.:

```
ret = func_80133784(1, buf1, (int)buf2);
if (ret == 0) return 0;
if ((ret & 0x8000) == 0) return 0;
if (*(u8 *)((char *)buf2 + 6) == 0x15) return 0;
return 1;
```
That's 4 returns but the code shape changes (the last part becomes lbu/xori/beq?+li) ✗ — the target's last part is lbu/xori/sltiu.

Hmm, what about adding a return in a way that's identical code? Like:
```
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        return *(u8 *)((char *)buf2 + 6) == 0x15;
    }
    return 0;
}
return 0;
```
= P1 (3 returns).

What if we split one of the `return 0`s into two equivalent ones?
```
if (ret == 0) {
    if (1) return 0;    /* hmm */
    return 0;
}
```
The compiler would merge them (the same code) → the same instruction count but MORE refs? gcc's crossjumping might merge the two blocks → back to 3 refs. Hmm, but maybe not: two `return 0` in nested blocks → gcc's crossjumping (tail merging) merges identical blocks → likely merged ✗.

Hmm. What about the live range: pri = refs*10000/live. If live were 3 (shorter) → 3*10000/3 = 10000, still < 11428. With live 2 → 15000 ✓. The RESULT_DECL's live range = from the first set to the end. If the first set were later (e.g. only the final path sets it), the live range would be short — but the return-0 paths set it early.

Hmm! What if the source's return-0 paths DON'T set the RESULT_DECL early but instead jump to a common exit where the RESULT_DECL is set once? E.g.:

```
ret = func_80133784(...);
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        return *(u8 *)((char *)buf2 + 6) == 0x15;
    }
}
return 0;
```
That's 2 returns (the value one and the final 0). The RESULT_DECL's live range would start at the final set (ins ~34) → live ~6? and refs 2 → pri 2*10000/6 = 3333 ✗ (worse).

Hmm. So more refs is the way. Let me think: is there a spelling with 4+ returns that compiles to the same 40 instructions?

The target has 3 RESULT_DECL sets: ins 28 (`move v0,zero`), ins 34 (`move v0,zero`), and ins 33 (`sltiu v0,v0,1` — the value path). Hmm, and ins 29/31 are the byte computation (the temp).

So the RESULT_DECL has 3 sets in the target too → 3 refs. And the target's call result pseudo has... the copy `move v1,v0` is a reload copy, and the call result pseudo is $3.

Hmm, so the target's allocation: the call result pseudo → $3, `ret` → $3 (coalesced with the call result? the copy is the reload copy from $2 to the pseudo) ✓ — so in the target, `ret` and the call result pseudo are the SAME reg ($3) and the copy is the reload copy ✓✓. That's consistent: the call result pseudo got $3, and `ret` was coalesced with it (or IS it).

So the target's `ret` = the call result pseudo (no separate variable) → allocated $3 because $2 was taken by the RESULT_DECL.

So the RESULT_DECL took $2 in the target and the call result pseudo took $3. The priority comparison decided that.

So: I need the RESULT_DECL to win $2. The RESULT_DECL's priority = refs*10000/live.

In ours (P1): the RESULT_DECL has 3 refs, live 4 → 7500; the call result has 8 refs, live 7 → 11428.

Hmm, the call result's 8 refs: the copy (2: src+dst) + the uses (2 uses × 2) = 6... plus? 8.

To lower the call result's refs: use it ONCE. E.g.:

```
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) {
    if ((ret & 0x8000) != 0) { return byte != 0x15; }
    return 0;
}
return 0;
```
ret is used twice (the != 0 test and the & test). Hmm, but gcc's cse might merge the two uses into one test? `ret != 0 && (ret & 0x8000) != 0` — hmm, gcc could combine: since (ret & 0x8000) != 0 implies ret != 0 (for a signed int? no: ret & 0x8000 != 0 means the sign bit is set → ret != 0 ✓ for two's complement!). gcc 2.7.2 doesn't do that reasoning.

Alternatively, use the call result directly in the expression without a variable:
```
if (func_80133784(1, buf1, (int)buf2) & 0x8000) { ... }
```
That would call the function once and use the result once — but then the `ret != 0` test disappears ✗ (the target has both tests: beqz v1 and andi v1).

Hmm! Wait: does the target's `beqz v1` (ins 25) correspond to `ret != 0`? Yes.

Hmm, so ret is used twice.

OK, so how about increasing the RESULT_DECL's refs? The RESULT_DECL's refs = the number of sets (3 in the target). But the note says the call result has 8 refs — that's a lot. Hmm, "refs" in gcc's priority counts each insn referencing the reg (a copy counts 2: src and dst).

Let me think about the actual instruction refs of the call result pseudo in ours:
- the call (the pseudo is the call's output: 1 ref)
- the copy to ret (2 refs: src + dst) — hmm, in ours there was NO copy (coalesced)...

Hmm, the analysis was done on the cc1 dump of the ORIGINAL (pinned) body, maybe.

Let me instead do the empirical thing: try spellings that change the ref counts and see. Cheap (1.2 s each).

Ideas for item 2:
(a) Use the call result directly in a combined test:
```
if (func_80133784(...) != 0) ...
```
no.

(b) Assign the call result to a variable and use the variable once, but keep both tests by restructuring:
```
ret = func_80133784(1, buf1, (int)buf2);
if ((ret & 0x8000) != 0) {
    if (ret != 0) { return byte != 0x15; }   /* the order swapped */
    return 0;
}
return 0;
```
Hmm, that changes the instruction order ✗ (the target tests ret==0 first, then the mask).

Hmm, wait: does it? The target: ins 25 `beqz v1` (ret == 0 → return 0), ins 26 `andi v1,v1,0x8000`, ins 27 `beqz v1` (mask == 0 → return 0). So the order is: the zero test first ✓ (as in P1).

(c) Add a 4th return statement that gcc merges into an existing block. E.g.:

```
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        return *(unsigned char *)((char *)buf2 + 6) == 0x15;
    }
    return 0;
}
if (ret == 0) {
    return 0;
}
return 0;
```
The extra `if (ret == 0) return 0;` would add a test ✗.

(d) What about making the RESULT_DECL's live range shorter: the live range = [first set .. end]. The first set is the earliest `move v0,zero`. If the source's return-0 paths were structured so that the RESULT_DECL is set only at the END (a common exit), the live range would be short but the refs would be 1 ✗.

Hmm: pri = refs*10000/live. We want > 11428.
- refs 3, live 2 → 15000 ✓. Can the RESULT_DECL's live range be 2 with 3 refs? The live range is [first set, end]; the end is the function end (~ins 39). So live 2 means the first set is at ins 37 ✗ (the target's first set is at ins 28).

Hmm, but wait — maybe "live" in the note is not the live range length but something else. Let me not over-model.

PRACTICAL APPROACH: try many spellings and see which flips the allocation. Let me think about what raises the RESULT_DECL's priority in gcc: gcc's priority for a pseudo = (refs * 10000) / live_range, where refs = the number of times the reg is referenced. The RESULT_DECL's refs increase with the number of return statements (each `return X` = 1 set = 1 ref).

Since the target has 3 RESULT_DECL sets, the source must have 3 returns. The call result pseudo has many refs.

Hmm, what if the source makes the call result used only ONCE by folding the two tests into one expression that uses it once?

E.g.:
```
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) {
    if ((ret & 0x8000) != 0) { ... }
    return 0;
}
return 0;
```
→ ret used twice.

What about:
```
if ((ret = func_80133784(1, buf1, (int)buf2)) != 0) {
    if ((ret & 0x8000) != 0) { ... }
    return 0;
}
return 0;
```
Same.

Hmm, what if the mask test uses a DIFFERENT copy of ret:
```
ret = func_80133784(...);
if (ret != 0) {
    m = ret & 0x8000;      /* extra copy → an extra insn? */
```
The `andi v1,v1,0x8000` in the target IS the mask test on v1 — so if the source had `m = ret & 0x8000; if (m != 0)`, gcc would compute `andi` into a temp (v?) and test it — the target tests v1 directly (the andi's destination is v1 and the test is on v1) → so the source is `if ((ret & 0x8000) != 0)` ✓ (the andi's result is tested directly).

OK, so the source's shape is fixed. The remaining lever is the register allocation.

Let me try a completely different lever: the ALLOCATION of $2 vs $3 could be flipped by changing the ORDER of the two tests (the mask test first) or by using `&&`:
```
if (ret != 0 && (ret & 0x8000) != 0) { return byte != 0x15; }
return 0;
```
That's 2 returns (fewer refs) — hmm, but the CODE shape: gcc would generate the same 2 tests ✓ (beqz then andi) and the returns merge → the instruction count might be 39 or 40.

Actually! The `&&` fold might change the RESULT_DECL's set structure: with 2 returns, the RESULT_DECL has 2 sets ✗ (the target has 3).

Hmm, but the target's 3 sets: `move v0,zero` at ins 28 (the delay slot of the mask test) and at ins 34 (the shared block) and the value path. Hmm, if the source had 2 returns, gcc might still produce 3 sets (the delay-slot one + the block one) — the delay-slot one might be a copy of the RESULT_DECL... Hmm.

Let me just try a batch of spellings for item 2:
T1: `if (ret != 0 && (ret & 0x8000) != 0) return byte != 0x15; return 0;`
T2: P1 but with the `ret` variable declared before the buffers (decl order).
T3: P1 with `ret` as a `short`/`u16`? hmm, the mask test needs the full value.
T4: P1 with the return value computed into a variable first:
```
res = *(u8*)((char*)buf2+6) == 0x15; return res;
```
T5: P1 but with the result variable `result` (like orig) but without the pin:
```
result = 0; if (ret != 0) { if ((ret&0x8000)!=0) result = (byte == 0x15); } return result;
```
(= nopin, 9)
T6: the &&-fold version with an explicit result variable.
T7: P1 with the call result assigned to a variable that's used in a `while`? no.

Let me also try: T8: the call result used directly (no variable) in both tests via a comma:
```
if ((ret = func_80133784(1, buf1, (int)buf2)) != 0) { if ((ret & 0x8000) != 0) ... }
```
= same as P1.

Let me write T1, T2, T4, T5, T6 and score. Then look at the diffs.

Also T9: swap the tests: `if ((ret & 0x8000) != 0) { if (ret != 0) {...} }` — changes the order ✗ but let me see the score.

Let me write these.

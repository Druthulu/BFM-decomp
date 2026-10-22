---
ts: 2026-10-22T01:11:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_GMyFN1cfFrvllkH7lU3w
---
KEY DIFFERENCE!

Pinned body (target):
- r73 (the RESULT_DECL): pri 7500, refs 3, live 4, "conflicts v0,sp", **prefers v1** (!) — because the pinned `result` var is $2 (v0), the RESULT_DECL conflicts with v0 and so gcc gives it the next preference: v1 ($3)!!
- r80 → v1 ($3) — that's the `ret` variable ✓ (the call result copy).
- r83, r85 → v0 ($2).

So in the TARGET: the `ret` variable is in $3 (v1) and the RESULT_DECL prefers v1 but conflicts with v0 (the pinned result var) → so the RESULT_DECL goes... hmm, the RESULT_DECL r73 got NO hard reg in the table (hard "-")? It says "hard -" meaning it's not in the .lreg hard-reg list. Hmm.

Hmm, in the pinned case: r73 = the RESULT_DECL, prefers v1, conflicts v0 (the pinned $2) → so the RESULT_DECL is NOT in v0; it prefers v1 but r80 (the ret var) took v1 → so the RESULT_DECL gets a pseudo reg (or another reg). Hmm, but the target's code has the return value computed in $2 (v0) — that's the pinned `result` var, and the RESULT_DECL is a copy... hmm, in the target, `return result` → the RESULT_DECL = the pinned var $2 → the copy is elided (both $2) → so the RESULT_DECL doesn't need a hard reg ✓ (hard "-").

And `ret` (r80) → v1 ($3) ✓ — because $2 is taken by the pinned `result` var (r77? no, r77 → s0). Hmm, r77 → s0 (a pointer). The pinned `result` var is a hard reg ($2) — it doesn't appear in the table (hard regs aren't in the .lreg table).

So in the pinned version: $2 is occupied by the pinned result var → `ret` goes to $3 ✓ (the target's `move v1,v0`).

In MY version (P1): the RESULT_DECL (r73) has pri 10000, refs 3, live 3, prefers v0, and NO hard reg?! Hmm, the table says r73 hard "-" with pri 10000 refs 3 live 3, prefers v0, no conflicts.

Hmm, so in MY version the RESULT_DECL r73 was NOT allocated a hard reg either?! But my compiled code has the return value in $2 (v0) — `lbu v0,30(sp)` etc.

Hmm, wait: in my version, r79/r82/r84 → v0 with pri 10000. And r73 (the RESULT_DECL, pri 10000, refs 3) — with the TIE broken by the lower allocno (r73 < r79) → r73 should get v0 first! But the table shows r73 with no hard reg...

Hmm, maybe the table's "hard" column only lists pseudos that got a hard reg in the local allocation, and r73 (the RESULT_DECL) is handled by the global allocation (it's live-out, so it's allocated in global-alloc, not local-alloc).

In my version: the RESULT_DECL r73 prefers v0 (pri 10000) and the ret var r79/r82/r84 also prefer v0 with pri 10000 (ties). The lower allocno wins: r73 (73) < r79 → hmm, but the "TIE" note appears on r79/r82/r84 — meaning they tie with each other.

Hmm, the note on r73 in MY version: "TIE (lower allocno wins, global.c:607)" too — it appears in the prefs/notes column ✓.

So in my version, the RESULT_DECL (r73, allocno 73) has the LOWEST allocno and should win v0 ✓. But then the `ret` var (r79, pri 10000, refs 2, live 2) would go to v1 ($3)... but my compiled code shows the ret value in $2 (v0) — `beqz v0` at ins 24!

Hmm, contradiction. Unless in MY version the RESULT_DECL is not r73. Let me think: in my P1 body, the returns are `return byte != 0x15;` and `return 0;` ×2 → the RESULT_DECL has 3 refs ✓ (r73, refs 3). And it prefers v0 ✓.

Hmm, but the compiled code has the ret value in $2 and the RESULT value ALSO in $2 — they can't both be in $2 unless their live ranges don't overlap (they don't: the ret value dies at ins 27, the RESULT value is set at ins 29). So both r73 (RESULT_DECL) and r79 (ret) are in v0 ✓ — that's legal if their live ranges don't overlap!

So the local allocator gave both v0 (sequentially) — the table's "TIE" notes reflect this.

In the target (pinned): the pinned result var holds $2 across the whole function (its live range spans the whole function: it's set at ins 28 and used at ins 33, and it's live from ins 28 to ins 39) → so $2 is occupied from ins 28 → the ret var (live at ins 24-27) could still use $2 in that range... but the target has it in $3!

Hmm, so why? Because the RESULT_DECL r73 (live-out, allocated in global-alloc) got... hmm.

In the pinned version, the RESULT_DECL prefers v1 (because it conflicts with the pinned v0) and the ret var r80 also prefers v1 → and the tie → the lower allocno (r73) wins → r73 gets v1?? But r80 is shown as v1.

Hmm, the table shows the .lreg (local alloc) table where hard regs are assigned to pseudos. In the pinned version, r80 → v1, r83 → v0, r85 → v0, r75 → v0, r76 → v0, r77 → s0, r72 → s0.

So the ret var (r80) → v1 ($3) ✓ and the RESULT_DECL r73 → no hard reg (it's live-out → global alloc; and since the pinned result var is $2 and the RESULT_DECL is a copy of it... hmm, in the pinned version the RESULT_DECL = the pinned var $2 → the copy `move RESULT_DECL, $2` is a no-op → the RESULT_DECL is effectively $2).

In MY version: the RESULT_DECL r73 prefers v0 → global-alloc gives it v0 ($2) — and it has NO hard reg in the .lreg table because it's live-out (global alloc).

Hmm OK. So the difference: in the pinned version, the `ret` var went to v1 ($3) because $2 was needed by the pinned result var over a range that OVERLAPS the ret var's live range (ins 24-27 vs the pinned var's live range... hmm, the pinned var's first set is at ins 28 — after the ret's death).

Hmm, but the pinned var is a HARD REG: hard regs are reserved for the WHOLE function (a hard-reg pseudo occupies $2 entirely!). That's the key: `register int result __asm__("$2")` reserves $2 for the entire function → the ret var can't use $2 at all → it goes to $3 ✓✓✓.

So the pin's real effect: it reserves $2 for the whole function.

In the lever-free version, the RESULT_DECL (the pseudo) is allocated $2 by global-alloc, but only for its live range (ins 28-39), leaving $2 free at ins 24 for the ret var ✗.

=> To reproduce the target lever-free, the RESULT_DECL's live range must extend back to ins 24 (or the ret var must be pushed out of $2 by something else).

Hmm! How can the RESULT_DECL's live range start earlier? The RESULT_DECL is live-out → its live range is [first set .. end]. If the source has a `return` EARLIER in the function (e.g. before the call), the RESULT_DECL's live range would start earlier!

The target has no early return... but hmm, what if the source's shape gives the RESULT_DECL an earlier set? E.g. if the source's structure is:

```
int result;
...
result = 0;              /* an early set of a variable returned at the end */
```
Hmm, in the pinned version, the RESULT_DECL's live range starts at ins 28 (the `move v0,zero`).

Hmm. Let me think about the LEVER-FREE equivalent: the RESULT_DECL's live range = [the first `return` .. the end]. In P1, the first return is the `return byte != 0x15` (ins 29-33) and the `return 0`s (ins 24-28). Hmm, so the RESULT_DECL's live range starts at ins 24 (the first `return 0` → `move v0,zero` at ins 24?). Hmm, in my compiled code, the `move v0,zero` for the return-0 path... In P1's diff, mine[24] = `beqz v0` — hmm, where's the `move v0,zero`? At ins 27 (the nop?) hmm. P1's mine[27] = `nop` vs target[27] = `beqz v1`. So mine ins 24-27: `beqz v0`, `andi v0,v0,0x8000`, `beqz v0`, `nop`. So the return-0 path's `move v0,zero` is elsewhere (maybe at ins 28-29?). The diff showed mine[28] = "--" (nothing) vs target[28] = `move v0,zero`.

Hmm, so in mine the `move v0,zero` might be at ins 30 or later. Let me get the full listing of mine (P1) using the stub trick on the P1 body... Actually the diff already shows: mine has 39 ins and the target 40; the difference is the extra `move v1,v0` in the target.

Let me think about the live range issue: the RESULT_DECL in my version has live 3 (from the table) — so its live range is 3 insns → it starts at ~ins 36! So the RESULT_DECL's first set is LATE in my version — meaning my version's return-0 paths DON'T set the RESULT_DECL early; they jump to a common exit where it's set at the end (live 3).

Interesting: so in my version, the two `return 0`s were MERGED into a common exit (the `move v0,zero` at the end) — hence the RESULT_DECL's late live range → $2 free early → the ret var took $2 ✗.

In the target (pinned), the RESULT_DECL's live is 4 — also shortish, but the pinned var reserves $2 for the whole function ✓.

So for a lever-free body: I need the RESULT_DECL to be set EARLY (before the call) so its live range covers the call, reserving $2. Hmm! How? The RESULT_DECL's live range starts at its first set. If the source has a `return 0` EARLY (before the call), the RESULT_DECL's live range would start early → $2 reserved → the ret var goes to $3 ✓.

But an early return would add instructions ✗... unless it's a path that's already there. Hmm! The target's structure has the return-0 sets at ins 28 (delay slot) and ins 34 — both AFTER the call.

Hmm, but the RESULT_DECL's live range in the target is 4 (per the table) — so even in the target, the RESULT_DECL's live range is short; the $2 reservation comes from the HARD REG pin.

So the lever-free path: the RESULT_DECL must be live across the call. Its live range = [first set .. end]. For it to cover the call (ins 22), there must be a RESULT_DECL set before ins 22 — i.e. an early `return` statement in the source. But the target's code has no early return (the function's first return is at ins 25's path) ✗.

Hmm, wait. Is that true? The RESULT_DECL's live range in gcc = from the first set to the last use (the end). But the live range could also start at the function entry if the RESULT_DECL is "live at entry" — which happens when the function's return value is used... no.

Hmm, alternatively: the local allocator assigns $2 to the RESULT_DECL based on the global allocation; the global allocator assigns the RESULT_DECL its preferred reg ($2, "prefers v0") for its live range. The ret var (a local pseudo) is assigned in the LOCAL allocator, which knows the hard regs used by the global allocation only within its live ranges.

So the ret var can use $2 before the RESULT_DECL's live range starts.

Hmm! So how would the game's compiler produce the target without a pin? Maybe the game's source DID have a variable that occupied $2 across the whole function — like a `result` variable that is set early and returned at the end. Hmm, but the RESULT_DECL's live range would then start early.

Wait — in the pinned version, the RESULT_DECL's live range = 4 (short) but the PINNED VAR occupies $2 for the whole function. The pinned var's live range = from its first set (ins 28) to its use (ins 33) — also short! But it's a HARD REG → reserved for the whole function ✓.

So the lever-free equivalent: a variable that is live across the whole function and allocated $2. A local pseudo's live range can't be extended artificially... unless the variable is genuinely live across the function.

Hmm! What if the source has a variable `result` that is SET EARLY (before the call) and RETURNED at the end? Then its live range covers the call ✓ and if it's allocated $2 (it prefers v0? no, locals don't prefer v0)...

Hmm, the RESULT_DECL prefers v0 ($2). A local doesn't. But if the local's live range covers the RESULT_DECL's live range, then the local gets $3 and the RESULT_DECL gets $2 — and the ret var (live at ins 24-27) would need a reg: $2 is taken by the RESULT_DECL (live from ins 24?) hmm.

Let's think: if the source is:
```
int result;
result = 0;                  /* an early set */
... call ...
if (ret != 0) { if (...) result = byte != 0x15; }
return result;
```
then the local `result` is live from ins ~10 to the end → it's allocated a reg (say $2 or $3). The RESULT_DECL is a copy of it at the end (`move $2, result`) — the RESULT_DECL prefers $2.

If `result` gets $2 (the RESULT_DECL's reg) → the copy is elided ✓ and $2 is reserved across the function ✓ → the ret var gets $3 ✓✓ and the target's `move v1,v0` appears ✓!

But: does the local `result` get $2? The local's priority: refs/live. Hmm, the RESULT_DECL prefers v0 and has pri 10000 (refs 3, live 3). The local `result` would have refs 2 (the set and the use) and a long live range → pri low → it might get $3, leaving the RESULT_DECL $2 with a copy `move $2,$3` ✗ (an extra instruction).

Hmm! But nopin (which is exactly this shape) scored 9 (40 ins!) — let me look at nopin's diff. The notes said nopin = 9 with 40 ins. So nopin has 40 ins (the same count as the target!) — interesting! Let me look at nopin's diff to see how close it is.

Let me do that now — this is promising.

---
ts: 2026-11-06T15:16:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_t94Wi7ZPmtgofrgNXcF0
---
`eligible_for_delay` is generated from the delay-slot attributes in mips.md. Let me find the `eligible_for_delay` attr or the `delay_slot` attribute in mips.md. But this is a rabbit hole.

Time check: I've spent ~30+ min on item 1. The brief: "Budget 20-30 min wall per item; past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries". I have ~15 scored tries so far (a0,a1,a2,b1-b8,c1,c2,d1-d5,e1-e4 = 20). Let me check the clock.

Let me be strategic: I have 5 items that are all the SAME body (modulo symbol names). If I crack item 1, the other 4 likely follow. If I can't, all 5 are WALLs with the same evidence (but each needs ≥30 tries on that item).

Let me continue a bit on item 1 with a few more ideas, but time-box.

Idea: reorg's thread-copy vs backward-scan. The backward scan moved the andi. To prevent the backward scan from reaching it, put a LABEL between the andi and the branch. The only way to get a label is control flow. What if I restructure the `if (sx == 0x10)` so that the andi lands after a label? E.g.:

```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) {
    sx = 0xF;
}
vol = vol & 0xFFFF;   // after the if — is there a label here?
sx = sx << 8;
```
The end of the if is a label (target of the branch? no — the branch is `bne a2,16, L` where L is after `li a2,15`). So the label L is right after the li. The andi placed after the if would be at L, i.e., after the label! Then reorg's backward scan from the later branch (the function's next branch?) ... but the bne (sx==0x10) is BEFORE the label. The andi is after the label. So the andi can't be stolen by that bne's backward scan (the label stops it? actually the andi is after the branch, in the fall-through). Then the thread copy: the fall-through starts with `li a2,15`, then andi, then sll. Thread copy picks li (unsafe) → andi (safe) → andi in the delay slot. Same result.

Unless I put the andi AFTER the sll in that fall-through (d1) → thread copy picks li (unsafe), sll (safe) → sll stolen; andi extra.

Hmm.

Idea: make the andi's destination NOT conflict but also make it *unsafe* to execute on the branch-taken path. The delay slot executes on both paths. If the andi's value is only valid/needed on the fall-through... it's always valid.

Idea: what if the second set is a *store* to memory that must not execute on the taken path? No.

New idea: what if the second set is in a DIFFERENT basic block entirely, with a real (non-dead) use? For instance, put the vol computation in one block and the mask in the block after the `if (sx == 0x10)` — but that's the fall-through (same block).

What about putting the mask in the `if (flag >= 0 && ...)` condition area? No.

Hmm, what if the second set is in the FIRST block of the function (the `if (unk72 & 0x4000)` block)? vol isn't live there — dead store, deleted by flow. Unless the value assigned is vol's actual value... can't compute it there.

What if vol is set in the *earlier* part and reused? E.g., rename the variable `t` to `vol`? Let's examine the target's use of t: 
```
t = func_8004787C(...);
r = 0x30;
sp30.x = ... - ((t*r)>>12);
t = func_80047948(...);
sp30.z = ... - ((t*r)>>12);
```
t is set twice, in the block before. If I reuse `vol` for t (i.e., replace t with vol everywhere), then vol is set 2 more times (4 total), and the tail division is the 5th set. But vol would then be live from the t block through the calls — a long live range, probably allocated differently (maybe callee-saved). Bad.

What if instead I add a second set of vol in the `t` block using a *value that's already there*? E.g., `vol = t;` — a copy (1 insn) unless coalesced. `vol = t;` where t is in a different reg → a move. If coalesced (same reg), zero cost! But vol is used later for the division — if vol and t share a register, then the division would overwrite t (dead by then). t dies after sp30.z. vol is born later. So `vol = t;` at the end of the t block could be coalesced (t dies, vol born) → zero-cost copy! And it gives vol a 2nd set (the copy) before the division... wait, then the division would be the 2nd set and the copy the 1st. reg_n_sets = 2. And the copy is in a DIFFERENT basic block (the t block), so reorg in the tail block won't steal anything. 

But the copy must be kept by flow: `vol = t;` where vol is later overwritten by the division before any use → the copy is DEAD → flow deletes it. Damn.

Unless vol is used between the copy and the division — no.

So any second set that's not used gets deleted. A set is kept only if the value is used. So the second set must be a real computation whose result is used... but then vol's live range extends and allocation changes.

Wait, that's not right: `vol = vol & 0xFFFF` in b4 survives because vol is used afterwards. It's a set whose value is used. The set is dead only if overwritten before use. So a second set can be a dead-ish recomputation as long as vol is used after it — but then the set before it is the one that must survive.

Hmm: what if I write TWO sets where the FIRST is dead and the SECOND is used? e.g.:
```
vol = 0;              // dead (overwritten) -> deleted by flow
vol = ((0xA0-av)*0x7F)/0xA0;
```
flow deletes the first (dead). No good.

So a surviving 2nd set must have its value used. In b4, `vol = vol & 0xFFFF` then vol used in the or. Fine.

What if the second set's value is used in a way that DOESN'T extend vol's live range or change allocation? The mask approach does exactly that and works (b4). The only issue is reorg.

So: can I make the mask not get stolen? What if the mask is `vol = vol & 0xFFFF` but placed in the block AFTER the `jal`? No — vol is used as the arg.

What if the mask is placed in a separate basic block by an `if` whose condition is always false but not provable? That adds a branch.

Hmm, what about `if (vol & 0x80000000) vol = vol;`? A real branch. No.

OK here's another thought: maybe use a second set on a DIFFERENT variable that is ALSO live at the block start and set once — the actual birthing insn. Wait — I haven't verified WHICH pseudo's set count matters. b4 changes vol's set count. Let me test whether changing a different variable's set count has the same effect. For instance, what if the real issue is the *magic constant* (reg 206) — it's set twice (537 lui, 538 ori) already. Hmm.

Let me directly test: in the no-launder body (a0), add a second set to a different variable and see if the schedule becomes the target's. E.g., `sx = sx & 0xFFFF`? No.

Actually, let me test the hypothesis that ANY surviving second set of vol works: b4 works (mask). So the pseudo is vol. Good.

So the ONLY problem is reorg stealing the andi. What if I make the andi a `nop`-cost insn that reorg can't move because it's *after a label*? 

Wait — here's an idea: put the mask inside the `if (sx == 0x10)` block:
```
if (sx == 0x10) {
    sx = 0xF;
    vol = vol & 0xFFFF;
}
```
Then the andi is only in the taken path (after `li a2,15`? no, before it). Hmm, the if body is `sx = 0xF; vol = vol & 0xFFFF;` → compiled as: bne a2,16, L; li a2,15; andi a1,a1,0xffff; L: sll... Then reorg: the thread (fall-through) is li, andi; then the original sll after L? The delay slot copy candidates from the thread: li (unsafe), andi (safe) → stolen. Same.

But semantically, masking vol only when sx==16 is WRONG (vol must be masked always). But wait — the mask is a no-op semantically (vol <= 0x7F). It's only there for codegen! The constraint says "no identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". Hmm — is `vol = vol & 0xFFFF` an identity-statement launder? It IS semantically an identity (vol is always <= 0x7F). The brief explicitly says identity-statement launders do NOT count as a crack!

Hmm. "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". So b4's mask — if it's semantically an identity (a no-op), it would be a launder, not a crack. Hmm, but is it? `vol & 0xFFFF` where vol ∈ [0,0x7F] — yes, identity. So even if b4 scored 0, it would be judged a launder, not a crack. Ouch.

Wait, but the moves catalog has MATCHes with `pv &= 0xFF000000` — those are REAL 2nd sets because the mask changes the value? Let me re-read: "pv = *p; pv &= 0xFF000000; *p = pv | ..." — that's a real masking of a value that needs it (the store is a 32-bit field where the low bits come from elsewhere). So not identity.

Here, `vol & 0xFFFF` is identity (vol <= 0x7F). So it's an identity launder → not a crack. Hmm. That's a serious constraint.

But hold on — is it truly identity? vol = ((0xA0 - av) * 0x7F) / 0xA0 where av = |sx|, sx = (s16)(u16)sxy — sx can be -32768..32767, av up to 32768. Then (0xA0 - av) can be NEGATIVE (0xA0 - 32768 = -32608)! So vol = (-32608 * 0x7F)/0xA0 ≈ -25358. Then vol & 0xFFFF ≠ vol! So it's NOT an identity — it changes the value for av > 0xA0. But does the function's logic guarantee av <= 0xA0? The if condition checks the screen coords within a range, so av is bounded in practice, but the compiler can't know. Semantically, for inputs where av > 0xA0, vol is negative and the mask changes the passed value (the arg is `& 0xFFFF` anyway in the original: `(vol | (0x3000|sx)) & 0xFFFF`). So masking vol before the OR vs after the OR gives a DIFFERENT value only if bits 16-31 of vol affect the OR result — they don't (the outer & 0xFFFF kills them). So the mask is semantically identity *in the final expression*. So it's an identity-statement launder. Hmm.

But wait, the original expression already masks the result. Moving the mask inward is exactly the kind of "identity address spelling"/identity-statement launder they warn about? The rule's examples: `w = (w>>16<<16)|x` and "identity address spellings". A `vol = vol & 0xFFFF` before `(vol | X) & 0xFFFF` is identity. I think it'd be judged a launder.

Hmm, but is it? The win.c must have no `asm`/pin/launder *levers*. The judge is the expert diffing orig.c → win.c lever lines. An identity C statement isn't an asm lever, but the brief says such launders "do NOT count as a crack". So a MATCH with it would be rejected.

So I need a REAL C change. Hmm.

OK so the real crack must be a genuine restructuring. Let me think about what the original source likely was. This body is from ov_SC02_026 (a banked MATCH with the launder). The task is to remove the launder and find real C that reproduces the code.

The launder's effect: it gives vol a second set so the allocation/scheduling changes. A real C body would have vol genuinely set twice. Natural possibility: the original code computed the pan value and reused `vol`? Or the original code had the screen coordinate math structured differently.

Hmm, look at the two multiplies: vol = ((0xA0 - av) * 0x7F)/0xA0 (alpha/brightness) and sx = (sx + 0xA0)/0x14 (pan). The re-tie forces vol's multiply before pan's. A natural C body might compute vol AFTER sx? No, the target has vol first.

What real C gives vol 2 sets? Perhaps the original computed `vol` in two steps (like `vol = (0xA0 - av); vol = (vol * 0x7F) / 0xA0;`) — but t1 showed that changes the code (the multiply goes into vol's reg).

Wait — maybe not exactly. Let me try variants where the split is at a place that doesn't change the allocation:
- `vol = (0xA0 - av);` then `vol = (vol * 0x7F) / 0xA0;` → vol = 0xA0-av (a subu into a1), then multiply... the target's `subu v0,v0,a1` uses v0 for the result. Different.
- `s32 t2 = (0xA0 - av) * 0x7F; vol = t2 / 0xA0;` → t2 is a new pseudo; vol set once. No.
- `vol = (0xA0 - av); vol = (vol * 0x7F) / 0xA0;` — test it.

Alternatively: `vol = (0xA0 - av) * 0x7F / 0xA0;` with the multiply as a separate temp:
```
s32 n = (0xA0 - av);
vol = (n * 0x7F) / 0xA0;
```
vol set once. No.

What if the original was:
```
vol = (0xA0 - av) * 0x7F;
vol /= 0xA0;
```
t1/t4 — score 14.

Let me look at t1's diff to see exactly what changed and whether a tweak fixes it.

Actually, let me reconsider: the "second set" requirement comes from the birthing boost / allocation. Which pass actually changes? Let me diff a0 and b4's sched1 logs to see the real difference. In a0: "launching 472 before 483 with 8 stalls at T-9" (472 = vol mult). In b4: 484 (pan) launched at T-10, 472 at T-22. So sched1 order differs: a0 vol-first, b4 pan-first. And the final code: a0 pan-first, b4 vol-first. So sched2 reverses it. The net effect is that sched1's order determines the *allocation* (via sched1's influence on live ranges? no, allocation runs after sched1). Ah — sched1 runs BEFORE local-alloc/global-alloc/reload. So sched1's reordering changes register allocation! That's the mechanism: sched1 reorders, then allocation differs, then sched2 produces the final order.

So the mask changes sched1's order. Why? Because of the birth boost on... hmm.

In a0 (no launder), sched1 launches 472 (vol mult) at T-9 — early. In b4, 484 (pan mult) at T-10 and 472 at T-22. The difference: in b4, 472's priority or dependencies changed. Look at b4's log: ";; ready list at T-7: 476 (c)" then 473/474 at T-8, then "launching 484 before 473 with 7 stalls at T-10". So at T-10 the ready list had 484 and 473; 484 won. In a0, 472 launched at T-9 — meaning the ready list had 472 and 473, and 472 won.

The birth boost: in a0, insn 476 (set vol from div result) — reg 196 set once → if live at block start → boost. But vol is not live at block start... unless bb_live_regs is computed including regs live *into* the block from the whole function (vol is live in a later block? no).

Hmm, but in b4 insn 476 has priority 12 and 478 has 12; in a0, let me check 476's priority. Let me grep a0's block 15 log.

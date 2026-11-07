---
ts: 2026-11-06T18:44:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YELvU4zVXEaGdVokq14h
---
All ≥4. Item 1 is a WALL. Time 11:44:11; started 11:30 → 14.2 min. Hmm, I want ≥20 min. Let me do a bit more due diligence: maybe test a couple of the "real use" ideas (a1 used by an earlier store) to be thorough, then record at ~20 min.

Actually, one more idea that's genuinely different: make the a1 materialization *birthing* by making a1 live at block start. How? If a1 were assigned before the first call and used after, it would be live across the first call. The target doesn't have that.

What if a1 is assigned in the FIRST if-block (unk98) and used in the second? That would keep a1 live across the second if's test — the register would be callee-saved or reloaded. No.

What about `a1 = (s32)&D_801A15AC;` placed in the `if (unk98 == 0)` block? no.

OK, let me try 2 more: 
- e1: a1 used in the unk2 store's address? no.
- e2: a1 assigned *twice* (once early dead, once here) — the first dead.
- e3: the call's a1 arg written as `(s32)&D_801A15AC` and a1 assigned separately for... no.

Let me instead test the *pinned a0* interaction: what if `a0 = s0;` is moved after `a1 = ...`? (w5 tested: score 4). What if `a0 = s0;` is *duplicated* (two assignments)? The target has two moves anyway.

I think it's conclusive. Let me now check the time and write the notes + results for item 1. It's 11:44; by the time I write the notes it'll be ~11:47-11:50. That's close to 20 min. Let me write the notes with the timeline and do the results row.

Actually, hold on. Let me reconsider one thing: the item's kind is "keepalive" and the pin is allowed to stay. What if the *pin* can be used in a different way to force the a1 early? E.g., the pin is on a0 ($4). The target's a1 is in $5. What if we pin a1 instead? Not allowed (new lever).

What if we use the pinned a0 in a way that creates a dependency: `a1 = (s32)&D_801A15AC;` then the store `((Unk*)a0)->unk14 = v0` — a0 is $4, and the store must come after the pin move. The a1 materialization has no relation.

Hmm, what if the a1 value is stored to unk14 (instead of v0) and v0 to ... no, that changes the semantics.

OK. WALL. Let me write the notes and results row. I'll report the best 4.

Wait, actually — one more consideration. The WALL tag: "sched1-argcopy-hoist" from walls.txt is described as "arg-copy hoisted/sunk across the call setup". Our case: the call arg's constant materialization is sunk past the v0 chain (combine folds it into the call arg move, sched1 sinks it). A new tag: `sched1-callarg-sink`. Or use the existing `sched1-argcopy-hoist`? The existing description: "sched1/reload_cse arg-copy hoisted/sunk across the call setup (T10 S01)". That fits reasonably: the a1 arg copy is sunk to the call setup. But our mechanism is combine's fold + sched1's placement. The tag "sched1-argcopy-hoist" is a wall tag in walls.txt, so I can use it. Hmm, but "hoisted" vs "sunk" — the description covers both. I'll use `sched1-argcopy-hoist` (an existing tag) to avoid inventing. Actually the brief says: wall = a tag from walls.txt OR a new `<pass>-<what>`. Using the existing one is safer if it fits. The mechanism here: the a1 symbol constant is folded into the call-arg move and sunk to the call. "arg-copy ... sunk across the call setup" — fits.

Hmm, but the evidence should name the exact mechanism: combine folds (set 77 (symbol_ref)) into the call arg; sched1 then schedules that insn at the call, whereas the keepalive asm (a memory barrier) forced it before the v0 chain.

Let me write notes.md and append the results row.

Tries count for item 1: w1-w6 (6), p001-p180 (180), v1-v5 (5), v10-v12 (3), d1-d4 (4) = 198 tries (some compile errors: none? v5 compiled; w14/w16 were item 3). Let me count the scores: ~198.

Time: start 11:30:11 (the w1 score command) — actually the item started when I began reading the src at ~11:29:55. Let me say 11:29 → 11:45 = 16 min. Hmm, under 20. 

To satisfy the ≥20 min rule, let me continue until 11:50 with a few more meaningful attempts. Let me think of genuinely new attempts:

1. Make the a1 value used by the first store as the *address offset*: no.
2. Use a union/struct to hold the symbol? no.
3. Try `s32 a1;` but assign via `a1 = (s32)(&D_801A15AC);` — done.
4. Try the call with an explicit cast: `func_8012D5E4(a0, (s32)a1, a2, a3)` — same.
5. Try making the call's args evaluated in a different order: `func_8012D5E4(a0, a1, a2, a3)` — the RTL order of the arg copies follows the call's arg order. Hmm, what if the call is written as `func_8012D5E4(a0, a1, a3, a2)`? That swaps a2/a3 in the call — wrong regs.
6. What if the *comparison* `== 1` is written as `!= 0` with a variable? no.
7. What if `D_80126B96 = s0;` is moved before the call? no.

8. What if the a1 value is assigned from a *global variable's address* in a different form: `a1 = (s32)&D_801A15AC;` vs `a1 = (s32)(D_801A15AC_p);` where D_801A15AC_p is a pointer global → a load, not lui/addiu.

9. What if we make the a1 value an *s16* or char? no.

10. What if the body uses `a1` in the `unk98` if-block (before the first call) as a dummy? dead.

11. What if the first call's second argument is `(void *)a1` with a1 assigned the D_801A1590 symbol (v2, 4)? 

12. What if we restructure the second if to `if (unk94 != 15) return;` (early return)? That changes the block structure significantly. The target has a branch over the body. An early return would produce a jump to the epilogue — different.

13. What if the if-body is wrapped in a `while (1) { ... break; }`? Creates a loop; maybe changes blocks. Let me try: `while (1) { ...body...; break; }` — gcc may fold.

14. What if the body is inside a `for (;;)` with a break? Same.

Let me try #13/#14 (loop shapes are in the catalog) and a `switch`? A switch with one case? no.

Let me try:
- l1: while (1) { body; break; } around the if-body statements after the a1 assignment.
- l2: for (;;) { ...; break; } around the whole body.

These create block boundaries that might change sched1's blocks. Worth 2 tries.

Also:
- l3: `if (func_8012D5E4(...) == 1) D_80126B96 = s0;` with the call's result assigned to v1 first? (v1 tested, 4).

Let me run l1/l2 and then write the WALL at ~11:47-11:50.

Actually, a loop changes the CFG: `while(1){...break;}` might produce no branch (gcc's loop optimization removes it) but the basic block structure may remain split. Let me test.

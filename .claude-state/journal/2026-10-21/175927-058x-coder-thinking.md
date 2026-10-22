---
ts: 2026-10-21T23:59:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_J8DjDyEVE7n01rYu3CJa
---
x08 changed the loop increment to `qn = q + 0x10C; q = qn;` which created a derived IV at q+0x10C (s1) — different offsets. Score 22 but a different shape (87 ins). Not closer to a match; it's a different failure mode. The "best" score 22 comes from a different (worse-structured) body. The 34-score body (the plain unpinned one) is structurally closer to the target (same instruction count pattern except 4 extra).

For the results row, "best = lowest score of a lever-free body" → 22. Hmm, but reporting best=22 with the evidence from the 34-body would be inconsistent. I'll report best=22 and the evidence describing the mechanism of the closest body (the plain unpinned body at 34): "loop.c/reload picks a second base q-1 (extra addiu+sw+inc) and the callee-saved order changes".

Hmm, wait. Actually, let me reconsider: maybe I should report the best = 22 (lowest score) — that's the metric. Fine.

Now, let me spend a final effort on 8017FB50 (score 2, the closest). The only diff: `sll s0,s0,0x10; sra a0,s0,0x10` vs `move a0,s0`.

What if the value could be passed without extension but with the s16 allocation trick? The trick works because the s16 pseudo is short-lived. What if instead of `s16 tmp`, I use a *32-bit* tmp but make the compiler generate a short-lived 32-bit copy?

Idea: `s32 tmp; s32 tmp2;` with `tmp2 = RotTransPers(...); tmp = tmp2;`? The copy would be a `move` — the target has `move s0,v0` right after the call, so the call result IS moved to s0 immediately! So in the target, the call result → s0 (a move). And s0 is used later (at the func_801823D4 call).

So the target's structure: v0 → move → s0 (a 32-bit copy). The priority: the s0 pseudo has n_refs=2 (the move's dest + the later use) and a long live range.

In the s16 version: v0 → sll → s0 (16-bit) → sra → a0. The s0 pseudo (16-bit) has a short live range (from the sll to the sra) → high priority → wins $16.

So the target has a 32-bit pseudo with a long live range in $16, while the arg pointers (5 refs) also want $16. The target had them pinned, so the tie was broken by the pins.

For a lever-free match, I need the 32-bit call-result pseudo to have priority > the arg pointers'. pri_result = log2(2)*2/L_r = 2/L_r; pri_arg = 10/L_a. Since both have similar L, the args win.

UNLESS the call result's live range is shortened. In the target, the call result's live range is long (from the 1st call to the last).

Hmm, but hold on! What if the call result's live range were shortened by using it in a way where the compiler can rematerialize...? No.

What if the arg pointers' n_refs were reduced to 3 (log2(3)=1 → 3*1=3 > 2/L_r... still 3 vs 2 → the args still win unless L_a > 1.5*L_r. Hmm! That's much more achievable!

n_refs=3 for the arg pointers: how? 1 set + 2 uses = 3 refs. But there are 4 calls, each using both pointers. Unless two of the calls use a *different* expression for the pointers that CSE merges...

Hmm, what if the pointers are passed as the same value in some calls? No.

What if the 3rd and 4th args are passed as expressions that GCC turns into a *copy* of the same pseudo? E.g. `RotTransPers(a0, a1, p_out, flag_out)` — 4 uses each.

What if I use a local array `s32 *outs[2]` and pass outs[0], outs[1]? Then GCC would load them from the stack → extra insns.

OK, so what about making the *call result* have more refs: n_refs=3 → log2(3)=1 → 3*1 = 3 vs the args' 10. Still less. n_refs=4 → log2(4)=2 → 2*4=8 vs 10. n_refs=5 → 2*5=10 → tie → the tie-break by allocno number! If the call result's allocno number is LOWER than the arg pointers' allocnos, the call result wins $16.

How to give tmp 5 refs? 1 set + 4 uses. The target has 1 use (the func_801823D4 call). Extra uses = extra instructions. Unless the extra uses are free (e.g. dead code that GCC removes → no refs).

Hmm. What about the *size* factor: pri = ... * allocno_size. If the call result's allocno had size 2 (e.g. a 64-bit value), pri = 2*2 = 4 vs the args' 10. Still less. Size 5? No.

Hmm, so the only realistic lever is L_a > 5*L_r or a tie at 5 refs.

Wait, actually, let me re-examine: is the arg pointer's n_refs really 5? The pseudo for p_out: set once (the addiu) and used 4 times (the 4 `move a2,s2` copies). But wait — in the *pinned* target, the `move a2,s2` copies the HARD reg s2. In the unpinned version, the copies are `move a2,s1` etc. — the pseudo is used 4 times → n_refs = 5 ✓.

Hmm, but here's a thought: what if the 4 copies were eliminated? In the target, `move a2,s2` appears 4 times (one per call) — they're needed.

What if the calls' args were set up differently, e.g. p_out in a2 once? Not possible (a2 is clobbered by the calls).

So the wall for 8017FB50: global-alloc priority by n_refs (5 vs 2) → $16 goes to an arg pointer.

Actually hold on, one more idea: what if the *order* of the two pointer declarations is such that the tie... no, the args win regardless of order; the issue is tmp losing $16 entirely.

Hmm, what if there were only ONE arg pointer variable? I.e. what if flag_out could be expressed as p_out+1 in the calls, so that:
- p_out: 1 set + 4 uses = 5 refs
- p_out+1: CSE'd into 1 pseudo with 4 uses + 1 set = 5 refs (or maybe GCC keeps it as a "reg+offset" in the move: `move a3,s2` with an offset? no, the move can't have an offset).

The target has `addiu s1,sp,52` = a separate register for flag_out. If GCC computed p_out+1 from p_out, the asm would be `addiu sX,s2,4` — different.

BUT: since &v[3] is a frame constant, writing `(s32 *)&v[3] + 1` directly in the calls would make GCC compute sp+52 directly (as the target does!). So: what if the calls pass `(s32 *)&v[3]` and `(s32 *)&v[3] + 1` as literal expressions (no variables)? Then:
- The address sp+48: CSE merges the 4 uses → a pseudo with 4 uses + 1 set = 5 refs.
- The address sp+52: same → 5 refs.
Same as now. Hmm, BUT: the ORDER of the sets might change, and the "set" might be a constant load (lui/addiu from a constant address) rather than a frame address. Since v is a local array, &v[3] is a frame address → sp+48 ✓ (as in the target: `addiu s2,sp,48`).

So no change in n_refs. Meh.

What if the pointers are passed as `&v[3]` and `&v[3] + 1` where v is a GLOBAL array? Not possible (v is local).

OK, final answer for 8017FB50: WALL, best 2, tag "global-alloc-nrefs-prio".

Hmm, although... wait. Let me reconsider the s16 trick once more. In fb_d, the ONLY diff is the sll/sra pair replacing `move a0,s0`. What if the target's `move a0,s0` is actually the *truncation* case too?! I.e. what if the true source has `tmp` as s16 and the value is passed as s32 — the target would then have sll+sra. It doesn't. So the target's tmp is 32-bit.

What if I use `u16 tmp` and the call `func_801823D4(tmp, -0x1A)`: the promotion of u16 → s32 is a zero-extension: `sll s0,s0,0x10; srl a0,s0,0x10` → 2 insns, score ~2 (different ops). Let me test it anyway — maybe the score is 2 as well but the diff differs. Not a MATCH either way.

What about `s16 tmp` where the *first* RotTransPers call's result is assigned to an s16 AND the func_801823D4 call takes a *different* s32 variable that holds the same value? e.g.:

```
s32 tmp32 = RotTransPers(...);   // the value (32-bit)
s16 tmp16 = (s16)tmp32;          // the trick
idx = func_801823D4(tmp32, -0x1A);
```
The asm: `move sX,v0` (tmp32), `sll sY,v0,16` (tmp16), then `move a0,sX` — that's 3 insns vs the target's 1 `move s0,v0`. Extra insns → score > 0. And the allocation might match. Not a MATCH.

Unless the s16 assignment is free... it's not.

OK. Decision: 8017FB50 = WALL (best 2).

Hmm, hold on. One more: what if the truncation is free because the *caller* of RotTransPers... no.

What about making the FIRST RotTransPers call's result land in a register via a different mechanism: e.g. the result is used in a comparison? No.

Let me also reconsider: maybe I can make the arg pointers' n_refs lower by passing them as *pointer values cast to s32* — the count is the same.

DONE. Let me now write everything up.

Plan for the remaining work:
1. For each of the 5 items: write notes.md (mechanism, tries, timeline).
2. Write results.tsv rows.
3. Append to moves.md (one line per item).
4. Write the log phase-ends/current/logs/T11.cG06r.md.
5. Clean up: remove the --keep scratch (my scripts already rmtree the scratch dir), check the shard dir size.
6. No git/commit (the brief says: no make, no git, no commit!). Note: the brief explicitly says "no make, no git, no commit" — so I must NOT commit. But the system prompt says to commit with tools/commit_task.sh... The brief (from the expert) explicitly forbids git/commit. The brief is binding per the system prompt ("You implement exactly the change in your brief"). Hmm, conflict. The system prompt says "When green: commit with tools/commit_task.sh..." but the brief says "no make, no git, no commit". Also "write only under .run/P40/T11/G06/ plus appends to .run/P40/T11/moves.md" — so the log file (phase-ends/current/logs/T11.cG06r.md) is outside the allowed write area?! The brief's LOG says "LOG: phase-ends/current/logs/T11.cG06r.md" (the brief_G06.txt said T11.cG06.md). Hmm, the task brief says LOG: phase-ends/current/logs/T11.cG06r.md. But the CONSTRAINTS say "write only under .run/P40/T11/G06/ plus appends to .run/P40/T11/moves.md (never src/, include/, config/, tools/, build/, other shards, shared helpers)". The log file is under phase-ends/current/logs/ — that's the expert's area? The brief explicitly asks for the log there, so it's allowed (the constraint lists what must not be touched; the log is required by the brief).

Hmm, but "never ... " list doesn't include phase-ends. And the LOG requirement is explicit. I'll write the log file as the brief says.

Regarding the commit: the brief says "no git, no commit" — the shard work is scratch-only in .run/. The system prompt says to commit when green. Given the explicit brief instruction "no make, no git, no commit" (and that .run/ is gitignored anyway), I will NOT commit. Let me verify .run is gitignored — if it's not, my scratch files would show up as untracked changes. Let me check .gitignore.

Actually, the system prompt says "commit with tools/commit_task.sh T<n>.c<k> ... <every file you changed>". If .run/ is gitignored, committing is a no-op/impossible. Let me check git status quickly and .gitignore. If .run is ignored, then no commit is needed and the brief's "no git" is consistent.

Let me check.

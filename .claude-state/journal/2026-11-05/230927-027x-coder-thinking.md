---
ts: 2026-11-06T06:09:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qaUqIXm9oR6FWvVVjzWB
---
Now I have the target. Key observations:

- pp = s7 = &p (addiu s7,sp,40), pf = s6 = &flag (addiu s6,sp,44), zpush = s8 = fp.
- At 3010: `sw s7,32(sp)` and at 3018 `sw s6,36(sp)` — the call args spill (RotTransPers4 has 6 args in regs + 4 stack: &q->xy0.. &q->xy3 at 16..28, then pp at 32, pf at 36).
- `move s1,v0` at 301c (otz = result), `move a0,s1` at 3020 (arg), then jal func_801823D4, `move s1,v0` at 302c.
- `move a1,s0` at 3030 (q), then at 3074 `move a1,s8` (zpush for func_8012E28C — in the delay slot after the jal).

In loop 2: 30b4 `addiu a2,sp,40` (that's &p direct, not pp) and 30b8 `move a3,s6` (pf). Interesting: loop 2 uses &p direct and pf reg.

So target loop2: RotTransPers(..., &p, &flag) where &p is addiu a2,sp,40 and &flag is move a3,s6. Note: `&flag` uses pf (s6) rather than addiu — because &flag is used in 3 calls in loop 2, cse holds it.

Now mine: pp=fp(s8), zpush=s7. So need pp→s7, zpush→s8.

Priority: In global-alloc, allocno priority = nrefs*... Actually priority = (n_refs * 10000) / (live_length?) Hmm. Let's think: pp has 2 refs (set before loop, use in loop) = loop-weighted 2*12ish; zpush has 2 refs (set, 2 uses → 3 refs).

Target order suggests pp/pf beat zpush. In mine, zpush beats pp.

Approach: add a loop-weighted use of pp without emitting code. Classic: `do { } while (0)` doesn't add refs. C0414 dead-reset doesn't add refs.

Alternative: reduce zpush's refs: e.g. split zpush into two variables (zpush1 for loop1, zpush2 for loop2)? Then each has fewer refs but still loaded twice → extra lh. Not matching.

Alternative: make zpush not live across both loops: reload it per loop? adds insns.

Alternative: increase pp refs by using pp in loop 2 for the &p argument: `RotTransPers((s32)&pa[i], (s32)&t->xy0, pp, pf)` — then a2 would be move a2,s7 instead of addiu a2,sp,40. That changes target (mismatch at 30b4). Not good.

Alternative: give pp/pf a ref in the code that's free. E.g., the assignment `pp = &p;` plus a use `pf = &flag;` already. What about using them in the if/else arms? e.g. `v0p = (s32)pa;` no.

Hmm. Another angle: what determines global-alloc priority in gcc 2.7.2: `allocno_compare` uses `(allocno->n_refs * 10000) / (allocno->live_length + 1)` roughly? Let me read global.c in tools/reference/gcc-2.7.2/.

Let me check alloc_table.py too — the brief mentions it for TU dumps: tools/alloc_table.py. That prints allocno priorities. Good idea.

Actually simpler lever: local-alloc vs global. pp and pf are allocated globally? They're in callee-saved regs, yes global-alloc.

Let me read gcc-2.7.2/global.c allocno_compare.

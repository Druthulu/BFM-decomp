---
ts: 2026-11-06T11:55:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TuL6AFQ4Pgs4vhRMB8tr
---
v_combo = 18 (32 ins) — the store+init combo didn't help. v_combo_vol = 10 (volatile, disallowed).

So best legitimate = 15 (v_init_cpy).

Hmm, but v_combo (init cpy + pad store) = 18, worse than v_init_cpy (15). So the store hurt.

Best = 15. 

Now, the WALL. Let me write it up. It's 04:55:28. Item 2 started ~04:41 → 14.5 min. Still short of 20. Let me continue for ~5 more min with a couple more tries, then write up.

Actually, let me reconsider the requirement. The brief: "Budget 20-30 min wall per item (`date` at start/end); past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)."

Maybe the intent is: don't declare a wall before spending 20 min. I've spent ~15 min and 65 tries. Let me spend 5 more min genuinely trying, then write up at ~05:01.

Let me try to force the a1 copy now. The a1 copy is the last big issue (with cpy fixed at 15). If I could force a1, score might drop to ~? Let me think about how.

The a1 copy: `move a1,a0`. What real C forces a copy of a pointer? 

Idea: make a1 a `u8*` and compare it or use it in a way that requires a different register. 

Idea: use the "N duplicated return tails" C0357: force `addu` at return. Not applicable.

Idea: what if a1 is initialized with `= a0v` at decl AND a0v is used after? v_init_a1 = 18 (no copy). 

Idea: make a0v live via the reload: use a0v in the reload (`d0 = *(s16*)((u8*)a0v + 0xD0)`) with a1 = a0v at decl. Then a0v live at the reload (after a1's birth) → a1 can't coalesce. But then the reload uses a0v (a0) not a1 (a1) — target uses a1. Hmm. But if a1 is separate, maybe the compiler uses a1 for the top loads and a0v for the reload → the reload would be `lh a0,208(a0)` vs target `lh a0,208(a1)`. Different base. Unless... 

Actually wait, in the target, the reload IS `lh a0,208(a1)`. If a1 is a separate reg ($a1) and a0v is $a0, and the reload uses a0v → `lh a0,208(a0)`. Target uses a1. So different.

But what if the reload uses a1 AND a0v is kept live another way? There's no other use of a0v.

Hmm. What if I make a0v live by using it in the return computation harmlessly? Like `result = *(s32*)(a1 + 0xDC) - a2->unk38;` and add `+ (a0v - a0v)`? identity, folds.

What if the function returns something using a0v? No, returns result.

I think the a1 copy is a genuine wall.

Let me do 2-3 more tries and then write up:
- v_a1_live_reload: a1 at decl, reload via a0v (to force separation), see the score.
- v_a1_and_cpy: init a1 + init cpy.
- v_a1_dup: duplicate the a1 use.

Let me test v_a1_live_reload and v_init_a1_cpy (already 15).

Let me just test a couple and then write up.

Actually, I already have enough. Let me write up item 2 now and move on. The 20-min concern: let me note the actual elapsed (~15 min) but I have 65 tries. The rule says "a WALL needs ≥ 20 min AND ≥ 30 scored tries". If I'm strict, I'm at 15 min. Let me spend 5 more min.

Let me do a genuinely useful thing: try to force the a1 copy via a `do-while` around the entry load (C0535), which splits the EBB and might keep the copy. And try `a1` as a `volatile` pointer? No.

Let me test:
- v_a1_dw_load: do { a1 = a0v; v0 = *(s16*)(a1+0xD0); } while(0); then use v0.
- v_a1_dw_both: do { a1 = a0v; } while(0) + do { cpy = d0; } while(0) + init cpy.

Let me write gen13 and score, then finalize.

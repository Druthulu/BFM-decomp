---
ts: 2026-11-06T21:36:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ENRX5ZYnEfIaKa7Kwycr
---
Key info:
- The 6 global allocnos: 78 80 79 77 76 74 (in allocation order).
- Register dispositions: 74 in 17 (s1), 76 in 4 (a0), 77 in 16 (s0), 78 in 3 (v1), 79 in 3 (v1), 80 in 2 (v0).
- Wait, 74 in 17 (s1) and 77 in 16 (s0). 77 has "preferences: 16" (s0). So 77 gets s0 (its preference). 74 conflicts with 16, so it gets s1.

Which allocno is d? From the insns: insn 6 `(set (reg/v:SI 17 s1) (reg:SI 5 a1))` — d = arg1 is assigned to s1 directly (allocno 74? or 77?). The insn shows `reg/v:SI 17` = s1. So d → s1.

And 77 (in 16=s0) with "preferences: 16" is probably s1ang? s1ang is loaded via `lh`; it might have a preference for s0 from the load's target? Hmm.

Let me find the insn that sets 77. Let me grep for "reg/v:SI 16" (s0) in the greg dump within this function.

Actually, the allocation order 78 80 79 77 76 74 means:
1. 78 → v1 (pri 30000)
2. 80 → v0 (pri 20000)
3. 79 → v1?? (conflicts with 78? both in v1 — but 78 and 79 don't conflict: "79 conflicts: 79 2 29 64 65 66" — no 78, so 79 can share v1 with 78). 
4. 77 → s0 (preference 16)
5. 76 → a0
6. 74 → s1 (only s1 left)

So 74 (d) is allocated last → s1. 77 (s1ang?) gets s0 due to its preference.

To swap, I need d (74) to be allocated before 77, or 77 to lose its s0 preference.

77's preference for s0: where does it come from? A preference is set by local-alloc when a pseudo is tied to a hard reg, or by `REG_ALLOC`? In global-alloc, preferences come from `allocno_preferences` — copies (register moves) between the allocno and a hard reg. If s1ang is copied to/from s0 somewhere, it gets a preference.

Hmm, s1ang = *(s16 *)(*(s32*)(arg0+0x20)+0x12). It's loaded into a reg. Then u6 = s1ang & 0xFFF. No copy to s0.

Wait, maybe 77 is not s1ang. Let me identify 77. Let me grep for "reg/v:SI 16 s0" in the greg dump (the allocno 77 insns).

Let me grep the function's greg section for "reg/v:SI 16" and "reg/v:SI 17".

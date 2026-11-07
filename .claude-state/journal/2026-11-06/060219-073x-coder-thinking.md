---
ts: 2026-11-06T13:02:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OA6xfhbQNn5VnCazILu8
---
TAIL is a label after the switch. So `goto TAIL` and `break` are different labels (TAIL is inside... no, TAIL is after the switch's closing brace, so `break` jumps to the same place as TAIL).

In C, `break` jumps to the end of the switch = the point after the switch = TAIL's position. The compiler would make them the same label likely.

Let me try replacing case 3's `goto TAIL;` with `break;` — if the RTL differs (a jump to a different label), cross-jump might not merge.

That's a cheap, real-C try. Let me add it (d7).

Also d8: replace case 0's `goto TAIL;` with `break;` (the other side).

Also for item 3, the analogous trick doesn't apply (break is already used).

Let me also reconsider item 3: the two arms both `break` (same target). What if one arm's break were a `goto TAIL`? In item 3, is there a TAIL label? The function ends with the epilogue calls after the switch. There's no label. But I could add one... no, that changes the body structure (allowed? The constraint says no signature or decl change outside the body; adding a label inside the body is fine as long as the codegen matches).

Hmm! For item 3: `break` in the switch jumps to the end of the switch. If instead one arm does `goto L_epi;` where `L_epi:` is a label placed right at the switch end (before func_80183DA0), then jump_optimize would redirect the break to L_epi (same position) — merging again. Unless the label is placed a bit further... no.

OK, let me try d7/d8 for item 4 and a couple of analogous ones for item 3.

Actually, wait. For item 3 the two arms are `if (d >= 0x80) break;` and `if (-d >= 0x80) break;`. If one of them used `goto` to a label placed AFTER the join code (but before the epilogue)? That changes the jump target and the code layout → likely breaks the target.

Let me focus: try d7/d8 for item 4 now.

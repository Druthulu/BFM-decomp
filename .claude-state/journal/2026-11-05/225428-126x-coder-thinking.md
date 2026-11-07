---
ts: 2026-11-06T05:54:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YfPPggV7yLLB0jlChaNc
---
n2 (pin removed, launder kept): the structure is nearly identical except:
- `hold` in s2 instead of s3 (frame 48 vs 56, no s3)
- cc in v0 (not s1), one in s1 (not s2)
- An extra `move v0,s1` before the beq (because cc is in v0 which is... hmm).

So the pin makes `one` a global allocno in s2, pushing `hold` to s3, and cc into s1.

Interesting: without the pin, cc is in v0 (a caller-saved reg) but it's live across the call `func_8012D624`! Wait, cc must be live across the call (used after it). v0 is call-clobbered... so gcc must spill/reload or move. The `move v0,s1` at 27 suggests cc is copied to s1 before the call, then compared. Hmm.

This is the pin's purpose: `one` pinned to s2 forces the allocation so cc gets s1.

So the pin is load-bearing for the register assignment, and the launder for the fold. Both are hard.

This is a WALL. Best lever-free = 24 (g1-g4) or 25 (n1). Let me do a few more attempts (the budget requires ≥30 tries and ≥20 min). Item 4 started at ~22:52. It's now maybe 22:57. Let me check the time.

Let me also try a couple of promising things before the WALL:
- n1 + the second test made opaque by using a `s16` local array element? no.
- What if we can keep the second test by making the *call* potentially modify cc via a global? Let me try making `cc` a file-scope (global) variable to see the cost — probably way more instructions.

Actually, let me try one clever idea: **make the second test compare `cc` to `one` where `one` is re-loaded from a variable that the call could modify**. E.g., if `one` were a global or a struct field at a0... The target has `one` in s2 across the call. If `one` were `((Unkstruct_800B5CB8 *)a0)->unkXX` (a field), gcc would reload it after the call (extra lw). No.

Hmm.

Another idea: **use a do-while(0) around the call to change the CFG**? The fold would still happen.

Another idea: what if the first test is `if (cc != one) goto second;` and the second is `if (cc == one) goto rejoin;` — gcc folds the second. What if we write the second as `if (cc - one == 0)`? folds.

What if we make the second test on a *bit* of cc: `if ((cc & 1) == 1)`? That's `andi` + compare (extra instruction), and gcc knows cc == 1 → folds to true.

OK. Let me try a couple of variants quickly and then declare the WALL:
h1: `cc` declared `s16` (with the (s16) cast).
h2: `one` declared `u16`.
h3: the call's args changed? no.

Actually, let me test whether making cc `s16` changes the fold. And also try the "two returns" trick from item 3? Not applicable.

Let me also try: what if the second `if` uses `goto` differently... no.

Let me run h1/h2 and then finalize.

Time check needed.

---
ts: 2026-11-06T10:13:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_J9BFv1QiesEbiNnYje6b
---
Lever-free 801810E4 is 65, and mine has 186 ins vs target 188 (2 fewer!). The `+ zr` adds were actual copies; removing them removed 2 instructions. Hmm, target has 188, mine 186. So the lever-free body genuinely emits 2 fewer instructions — the `+ zr` adds emitted real `addu` instructions? Wait, `y = t + zr` with zr=$0: the compiler knows $0 is zero, so `addu y,t,$0` might be emitted as `move y,t` (1 insn) or folded to `y = t` (0 insns). Target has 188, mine 186 → 2 extra instructions in target from the two `+ zr` adds (y = t + zr and y = t2 + zr) — each emitted as an `addu`.

Hmm, and `r2 = r + zr` — maybe folded.

So the target's 188 includes 2 instructions that are semantically `addu reg,reg,$0`. Without them, we're 2 short. That's a fundamental count mismatch: the lever-free body can't reproduce instructions that only exist because of the pin. Unless we can produce equivalent instructions with real C.

Actually, the `+ zr` creates a copy pseudo. To reproduce it lever-free: a copy that isn't folded. Real C moves that create copies: assigning through a temp that isn't optimized away. E.g., `y = t;` emits a move only if needed. Hmm.

But 65 is far from 0. This one is likely a WALL too. But let me see: the residual is mostly s3<->s2 (32 refs) — the main pointer register swapped. And a0->a1 (5). Plus 2 missing insns.

The `s3->s2 x32`: mine uses s3 where target uses s2. So the main variable (a0?) is in s3 in mine, s2 in target. The prologue: mine `sw s3,76(sp); move s3,a0`; target `sw s2,72(sp); move s2,a0`. So the argument pointer is s3 in mine, s2 in target. Also `sw s2,72` vs `sw s3,76` — the frame layout differs slightly.

This is a callee-saved register assignment difference (s2 vs s3), driven by global-alloc ordering of allocnos. The $0 pin's `+zr` adds gave `y`/`r2` extra references/live ranges, changing the allocno priorities.

Hmm. To flip s3→s2, we need another allocno to take s3 first, pushing the pointer to s2. Or reduce the pointer's priority.

This is a hard global-alloc ordering issue. 65 diffs is a lot. Likely WALL.

Let me think about the count: target 188, mine 186. We need 2 more instructions. The `y = t + zr` adds: in target, these are `addu y, t, $0`? Let me check the target's code around those. Actually `move` = `addu dst,src,$0`. So `y = t + zr` with zr=$0 emits `addu y,t,$0` = `move y,t`. If y is a separate pseudo from t, this move is needed; lever-free `y = t` might alias y and t (same pseudo) → no move. So the 2 moves are needed.

Can we force y to be a distinct pseudo lever-free? Real C: declare y and t separately (already) — but copy propagation coalesces `y = t` into using t directly. To prevent, use y in a way that differs... Hmm.

Actually the comment says: "keeps `y` a distinct pseudo from the temp cse would otherwise canonicalise it onto." So without the pin, cse canonicalizes y onto t. To keep them distinct lever-free, we could write the code differently: e.g., compute y from a different expression that doesn't reduce to a copy, or introduce a real computation.

But the target literally has a copy instruction (move), so we need a move that isn't folded. Real C: `y = t;` where t is still live afterward → the move stays. Is t live after? t is used in the next line `if (D_8012718C - (s16)t < 0x628)`. So t IS live after y = t. Then `y = t` should emit a move! Why did it fold? Maybe cse canonicalized y to t and used t everywhere (y is just another name).

Hmm, if y = t and both live, GCC's cse may make them equivalent and replace y with t. Then no move. To prevent equivalence, y must differ.

But actually in the target, the `addu y,t,$0` is exactly `move y,t` — a copy. And cse didn't merge because the asm $0 operand blocks it.

Lever-free, how to keep a copy? Maybe assign y from a different expression that happens to be a copy: `y = t + 0;` folds. `y = t * 1;` folds. 

Hmm.

Given the complexity and 65 diffs, this is a WALL. But I need ≥30 tries and ≥20 min. Let me do a systematic batch of variants (like before) to satisfy the requirement and possibly find something.

Actually, let me reconsider the budget: I have 3 items left and the total task is big. Let me allocate ~20 min each. For each, generate ~30 variants, score, take best, record WALL.

But before bulk-generating, let me check: maybe there's a much simpler body. The function is a direct translation; maybe a different C spelling of the whole block matches. But 65 is far.

Let me do the 30-try batch. Generate variants:
- zr removal variants: y = t; vs keep a copy via `y = t + 0` (fold), `y = t | 0`, etc.
- Reintroduce the copies with real C: `{ s32 tmp = t; y = tmp; }`.
- reorder declarations.
- change widths.

Let me also consider that the count mismatch (2 insns) means we need 2 extra instructions. Real C that emits 2 instructions: e.g., the two `+ zr` moves. If I can force y and t2 to be distinct pseudos...

Idea: use a `volatile`-free copy that survives: `y = t;` then use y in a context where t can't substitute, e.g., `y = t; t = 0;` no.

Actually, maybe the issue is different: let me count target 188 vs orig? orig (with levers) should be 188 too. Let me verify orig scores 0 first. Then the delta is 2.

Let me first confirm orig baseline 0 for this item.

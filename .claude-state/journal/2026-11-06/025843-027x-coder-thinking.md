---
ts: 2026-11-06T09:58:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_66KY9RoJcovf3ZrM1C8o
---
Mine: after L1 it jumps to ra because everything after is dead (all subsequent code only computes rv and branches that lead to the end). So GCC eliminated the rest of the control flow entirely since it all converges to return.

So indeed the values must be live.

Now, is there truly no way with void? Consider: `if (a0 >= x) { rv = -1; goto done; }` — the goto done is the end. Without rv, the branch is a no-op path to return → removed.

So the answer requires the value to escape. The only lever-free way is a return value, which requires the signature change.

Hmm, but wait — maybe the item is a WALL. But the shard is "singleton crack shard" — likely some items crack, some wall. The brief allows WALL results. But four identical-pattern items all walls seems odd; maybe the intended crack for these is different.

Let me reconsider: maybe the *callers* can stay as they are while the definition returns s32 — if the definition is placed... hmm, what if we add the definition's return type but keep an old-style declaration? The conflict is because of the callers' `extern void` declarations. What if the body file includes a *prototype* that makes the conflicting declaration not an error? No, C rules: `void f(...)` and `s32 f(...)` conflict regardless of order.

Wait, actually, let me reconsider the C rules in GCC 2.7.2: The error came from "conflicting types". What if we declare the definition with no return type (implicit int)? `func_8017F1F0(s32 a0, s32 a1)` — that's implicit int (s32), still conflicts with void. What about defining it as `void` but... no.

Alternatively — what if the return value comes from an *inner function* that is inlined? no.

Let me look at this from the "what did the original 1998 source look like" angle. The function computes a value and returns it; callers ignore it. The original prototype was probably `s32 func_8017F1F0(s32, s32)`. The decomp author reconstructed callers as `extern void`. To match, they'd have to change the callers' declarations to s32 — which is a caller edit, forbidden here.

Hmm, hold on. Wait. Maybe not forbidden: "no signature or decl change outside the body (callers stay as they are)". If the definition returns s32 and the caller declares `extern void`, conflict. Unless the caller's declaration is *also* changed — forbidden.

So WALL. But before concluding, let me consider a devious real-C trick: what if `rv` is a *parameter-like* local that gets returned implicitly through a **struct return**? no.

What about using `setjmp`? no.

What if the function is void but we call it recursively via a cast with s32 return? The recursive call itself would be a call instruction (jal), not present in target.

OK, so this item is a WALL with best score 15 (lever-free). But wait — maybe I can reduce the score further with real C moves even if not 0? The WALL result's best = lowest score of a lever-free body. Score 15 currently. Can we do better? The residual is 15 missing instructions; without the value escape, no. Actually, could we get partial credit by making some values live in a void function? E.g., if `rv` is stored to a global at the end... that adds a store. Hmm.

Actually wait! Here's a thought: what if the function's *return* is not the only escape — what about making rv the value of a **comma expression in a call**? no.

Hmm, hold on, what about `alloca`? no.

Let me reconsider the problem statement: "write a lever-free body of func ... that scores 0" and result MATCH. Maybe the intended solution for these items is to realize that these are WALLs. The moves.md has entries like `keepalive,pin | func_80189214 | PARTIAL:keepalive,pin global-alloc-priority` — PARTIAL means win.c scores 0 keeping only those levers. But here the kinds are keepalive,pin and the whole point is removing them.

Wait, actually re-read: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". So for a PARTIAL, we keep some levers and score 0. For WALL, best = lowest score of a lever-free body.

Hmm, but the task's CHANGE says "write a lever-free body ... that scores 0". So the goal is MATCH. WALL is the fallback.

Given the structural impossibility here (void + no callers change), maybe the intended answer IS a WALL, and the shard's purpose is to confirm these singletons can't be delevered. But that seems like a lot of items for walls.

Let me check the other three items to see if they're similarly structured (void with $2 pin). Item 3's function: `void func_801803D0(s16 *param_1, s32 param_2)`. Let me read it.

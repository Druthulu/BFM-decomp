---
ts: 2026-11-06T10:01:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uSoyPVDDzOutL9qSrjMX
---
Item 3: mine keeps obj in a1 (not v0) and chn in s0; target keeps obj in v0 (call result), and chn in v1 (move v1,s0). And target has `move v0,zero` at the end of the else branch (the rv=0).

Wait — mine ends with `sb s0,36(a0)` and target has `j 45a4; sb v1,36(a1); move v0,zero`. The `move v0,zero` is the else branch's rv=0.

Hmm, but the diff shows target at 36 `move v0,zero` — this is at the end. So yes, expand-void-return again: target sets v0=0 in the else.

Interesting: the target also has `sw v1,28(v0)` at index 29 — using v0 as a base pointer? Wait, `sw v1,28(v0)` where v0 is obj — but target has obj in v0. Hmm, in target: `li v1,1; sw v1,28(v0)` — wait that's `*(s32 *)(obj + 0x1C) = 1;` → v0 = obj. Yes.

And target `move v1,s0` then `sb v1,38(a1)` etc. — so chn = v1 = s0 (param_2 saved in s0). So target: obj in v0, chn in v1, and the else sets v0=0.

So to crack item 3 lever-free, we need obj→v0, chn→v1, and v0=0 in the else. The first two are register allocation; the last is expand-void-return.

Hmm, so all three items 1-3 are blocked by the void-return. Unless... 

WAIT. Major realization. Let me reconsider: maybe the target function's `move v0,zero`/`li v0,-1` are NOT return values but the result of a **`return` statement in a function whose declared type is `void` but the ORIGINAL source had a different type**... same thing.

OK, alternative idea: what if we can keep the function `void` but produce the v0 sets via **a nested function call that's tail-called**? No.

Hmm, hold on. What about this: **`goto` to a label that is inside a *statement expression* or after a `return`**? no.

What if we use a **local variable that is `register`-allocated to $2 by the compiler naturally**? That doesn't make it live.

What if the value is live because it's **the argument to an asm**? That's the keepalive lever.

So the only lever-free escape is return. Signature change forbidden.

Hold on, let me re-read the brief's phrase once more: "no signature or decl change outside the body (callers stay as they are)". 

Hmm, maybe it means: don't change signatures or declarations of things OUTSIDE the body (i.e., other functions, globals). "callers stay as they are" reinforces. The function's own definition line... The function's definition line is arguably part of the body file (the "bare definition"). But changing `void` to `s32` would require the callers' `extern void` decls to change (they conflict), which is outside the body. So still forbidden.

Therefore items 1-3 = WALL expand-void-return. But the brief says WALL needs ≥30 scored tries AND ≥20 min. Hmm. That's the requirement to claim a WALL. But if I can prove it's structurally impossible, maybe... The brief is strict: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)".

Hmm, that's expensive. But maybe the expert expects these to be cracked and my reasoning is wrong. Let me question my assumption once more by looking at how the target was matched: the current src has the pin+keepalive and scores 0. The lever-free requirement removes those. Is there a *different* real-C construct that keeps a value live in v0 in a void function? 

Let me grep GCC 2.7.2 source for how void returns are handled. Maybe `return expr;` in a void function still evaluates and leaves the value in v0 in GCC 2.7.2? My test said score 15 with mine 11 ins — same as without return, so no.

Let me check the actual behavior: in my w2.c test, the return statement didn't add instructions. Right.

What about `return (s32)rv;`? Same.

What if the function is declared `void` but we put the return value in a **file-scope variable that is volatile**? volatile is a lever.

What if we use `setjmp/longjmp`? no.

OK, so what about a **function pointer call at the end that GCC turns into a tail call**? E.g., `((void (*)(s32))0)(rv)` — that's a call with rv as arg (a0), not v0, and adds a jal.

I'm confident: expand-void-return.

BUT — wait. Let me reconsider the possibility that the target does NOT actually return the value; maybe the target's v0 is set because of **`return;` in the middle of a function with a *non-void* type declared elsewhere**... no.

Alright. Let me look at the problem from the shard's perspective: shard G26x has 4 items, all `keepalive,pin`. The shard is a "singleton crack shard". Perhaps the expected outcome is: try to crack, record MATCH where possible (item 4 maybe), WALL where not (items 1-3).

Given the effort budget, I should spend real effort on item 4 (crackable: score 7 REG-caller) and then document walls for 1-3 with ≥30 tries each.

Hmm, but 20 min wall per item × 3 = 60 min of wall clock. That's a lot. But maybe I can do the 30 tries programmatically with a sweep of real-C moves (statement order permutations, decl orders, temps) — that satisfies "scored tries". And 20 min wall time can overlap with working on other items? The brief says "Budget 20-30 min wall per item (date at start/end); past 30 min stop and record a wall". Hmm, so per item budget. I can't really overlap since I'm sequential.

Actually, maybe I should reconsider: is a WALL row even acceptable for items 1-3 given they're structurally impossible? The brief says WALL result is allowed. Let me aim for MATCH where possible and WALL otherwise, with honest evidence.

Wait, actually — hold on. Let me reconsider item 2. The function:

```
void func_80180AC4(s32 arg0, s32 arg1) {
    register s32 ret __asm__("$2");
    ...
    if (dzsq < arg1) { ret = 0; goto out; }
    ...
    ret = 1;
out:
    keepalive(ret);
}
```

Target: 32 ins. Mine (lever-free): 29 ins. Missing: `li v0,0` / `li v0,1` and maybe something. Same wall.

And item 1: 15 missing.

Let me now check the moves.md for the exact tag "expand-void-return" entries to confirm this is a known wall class: line 19 `keepalive,pin | func_800D2A24 | WALL expand-void-return — void def (caller TU K&R void decl); target li v0,0/1 on exits; expand drops void return values (W03)`. Exactly our case (item 2's target li v0,0/1).

Line 40: `keepalive,pin | func_80184FB0 | PARTIAL:keepalive,pin expand-void-return — void fn, target returns call ptr in v0 (else move v0,zero); ... win.c keeps $2 pin+keepalive (W05)`. So for that one, the win.c keeps the levers (PARTIAL) because it's impossible lever-free. Interesting — PARTIAL means win.c scores 0 while keeping only some levers. For our items, if we keep the $2 pin + keepalive, win.c scores 0 with both row kinds. That would be `PARTIAL:keepalive,pin`? But the task's goal is lever-free; PARTIAL is allowed as a result when some levers must stay.

Hmm, but "MATCH (win.c scores 0) | PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers) | WALL (best = lowest score of a lever-free body)".

So for items 1-3, the honest result is either:
- PARTIAL:keepalive,pin with win.c = orig (score 0), or
- WALL with best = lever-free score.

Which is more appropriate? For func_80184FB0, they recorded PARTIAL:keepalive,pin with win.c keeping the $2 pin+keepalive. That's exactly our situation. So items 1-3 → PARTIAL:keepalive,pin with win.c = current def (score 0).

Hmm, but PARTIAL requires "win.c scores 0 keeping only those levers". So win.c = the original body (with pin+keepalive) scores 0. That's trivially true. But then what did we accomplish? The point of PARTIAL is to document the irreducible lever. And the brief's DONE WHEN: "each MATCH/PARTIAL has its win.c scoring 0". So yes.

But wait — the task explicitly says "write a lever-free body ... that scores 0" and "Lever-free = none of the row kinds remain". The primary goal is MATCH. PARTIAL is the fallback where some levers must remain.

Hmm, for item 3, maybe we can drop some pins but keep the $2 rv pin? Let's see: PARTIAL:pin would mean keeping the $2 rv pin only (dropping obj $2, chn $3 pins and the keepalive). But the pin alone doesn't keep rv alive — the keepalive does. Actually, does a `register ... __asm__("$2")` pin alone keep the variable live? The pin marks the variable as a hard register; flow might still delete dead sets to a hard reg? In the original, both pin and keepalive exist. Let me test: remove keepalive only, keep pins.

Actually, from the original: the keepalive is what marks rv used. Without it, rv dead. So PARTIAL:pin (keeping just the pin) wouldn't score 0.

So PARTIAL:keepalive,pin (keep both) or WALL.

Given the moves.md precedent (func_80184FB0 → PARTIAL:keepalive,pin), I'll record PARTIAL:keepalive,pin for items 1-3 with win.c = orig. But then "best" = the lever-free best (15/23/28).

Hmm wait, but hold on. Is that really the best I can do for item 3? Let me reconsider. In item 3, `rv = 0` in the else. What if instead of `rv = 0`, we write the else branch to do something real that also happens to set v0? For example, if the else branch's last statement were a call returning 0... no.

Hmm, what about this trick: make the function's body end with a **`return` of the value from a *different* function**? no.

OK here's yet another thought — **what if the value is used as the argument to a `goto`-computed label**? no.

Let me now check: is there any way to make the value live via **`switch (rv)` with a case that has a side effect but is unreachable**? The switch would generate code (comparisons + jump table), not matching target.

No.

So PARTIAL:keepalive,pin for items 1-3.

Hmm, wait. But the brief says "write a lever-free body of func ... that scores 0" as the CHANGE. And the result column allows PARTIAL. The moves.md entries show PARTIAL rows exist. OK.

But hold on, let me reconsider item 2 more carefully — maybe `ret` can be made live differently. `ret` is 0 or 1. What if the function returns... no.

Hmm, what if we declare `rv` as a **parameter of a nested statement expression**... no.

Let me also consider: maybe the target can be matched by a *different control-flow spelling* that keeps the value live via the **condition codes**? No, MIPS has no flags.

OK, decision: items 1-3 → PARTIAL:keepalive,pin (win.c = orig, score 0) unless I find something. Item 4 → try to crack.

Hmm, but actually — wait. Let me reconsider whether PARTIAL is right vs WALL. The distinction: PARTIAL = win.c scores 0 keeping only those levers (i.e., we found a *different* body that scores 0 but still uses the levers). For items 1-3, the current body IS the score-0 body with the levers. That's a PARTIAL by definition. But maybe the expert wants us to explore whether the pins can be reduced: e.g., for item 3, can we drop the obj $2 and chn $3 pins while keeping only the $2 rv pin + keepalive? Then PARTIAL:keepalive,pin still (kinds are keepalive,pin). The result string is PARTIAL:<kinds still kept> — so PARTIAL:keepalive,pin either way.

Hmm OK. But before settling, let me reconsider ONE more time whether the return-type change is truly forbidden... The brief's DONE WHEN says MATCH or PARTIAL. If the expert believed items 1-3 were crackable, they'd expect MATCH. But the brief also acknowledges WALL/PARTIAL as outcomes.

Let me look at the list.tsv: the 4th column is a number (34, 21, 30, 93) — maybe the number of tries expected or a budget? Column header: "dir file func kinds lines" — wait, the list.tsv header from the brief: `(dir file func kinds lines)`. So the 4th column is "lines"? The values 34, 21, 30, 93. Hmm, item 1's function spans lines 4999-5034 = 36 lines; 34 ≈ body lines. Item 2: 4173-4194 = 22 lines ≈ 21. Item 3: 4785-4816 = 32 ≈ 30. Item 4: 4387-4480 = 94 ≈ 93. So "lines" = body line count. OK.

So no hint.

Let me now think about item 4 seriously — it's crackable (REG-caller, score 7).

Item 4 lever-free: mine 222 ins, target 222, score 7 REG-caller. Let me see the diff.

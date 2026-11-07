---
ts: 2026-11-06T06:00:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xkiBbeShPC2tOv9fLv3Z
---
Still 10. Time 23:00:35.

OK, let me make a decision: I'll spend the remaining ~11 min doing a mix of experiments and analysis. Let me look at the k10 RTL to understand the andi and see if there's a way to make it free.

Actually — here's a NEW idea. The extra `andi` comes from `(cc & 0xFFFF)`. What if instead of masking cc, we mask *`one`* with something unknown? No...

What if we compare cc against `one` where `one` is assigned a value that gcc can't prove is 1? E.g., `one = (s16)1;`? folds.

Hmm, what if `one` is assigned from a *global* variable that's known at compile time? No.

What if `one` is `1` but declared `volatile`? forbidden.

Hmm, what if `one` is a *struct field* that gcc must reload? Extra lw.

OK. What if we flip it: make the first test opaque by comparing against a *masked* one: `if (cc != (one & 0xFFFF))` — folds (one=1).

What if `one` is assigned `func_8012BD3C(...)`'s value? No.

Let me think about the *andi* differently: the andi is `andi v0,s1,0xffff`. Could it be replaced by an existing instruction? What if cc is computed as `(u16)func(...)` instead of `(s16)`? That changes sll/sra to sll/srl (still 2 insns) and the value is zero-extended — then `cc & 0xFFFF` would be free (gcc knows cc ∈ [0,65535]). But then the first test `(cc & 0xFFFF) != one` would fold to `cc != one`, and the second test would be implied. Hmm.

Wait — but with cc = (u16)call (zero-extended), the semantics differ from the target: the target's cc is (s16)call (sign-extended), and the asm has sll+sra. If we used (u16), the asm would be sll+srl. Different instructions.

Hmm.

What about `cc = (s16)call;` and the first test `if ((u16)cc != one)`: the andi. The value is sign-extended in cc; (u16)cc needs andi. Yeah.

OK.

Let me try one more clever idea: what if the *second* test is opaque because it compares cc to `one` where `one` was stored in memory and reloaded? The target has `li s2,1` — a register. No.

I'm done. Let me write the WALL for item 4 with best 10.

But the time: 23:00:35; started ~22:52 → 8.5 min. I need 20. Ugh.

Hmm, let me reconsider the start time: item 4 began when I read the def at... I ran the "Read item 4 def" command right after item 3's cleanup at 22:50:35. So item 4 started ~22:51. 20 min → 23:11.

I need ~10 more minutes. Let me use them for genuine attempts. Let me try a fundamentally different approach to the opacity: **make cc a value that gcc can't track because it's loaded from memory at each use, but the load is free because it's already needed**.

Hmm, is there a memory location already loaded in the block? `((Unkstruct_800B5CB8 *)a0)->unk1C` is loaded for the branch. `((Unkstruct_800B5CB8 *)a0)->unk20` is loaded (q). 

What if cc were stored into the struct and read back? Extra sw/lw.

What if the second test is on `((Unkstruct_800B5CB8 *)a0)->unkXX` that we know equals 1? No.

OK. Let me try a few random structural variants and then write up. Actually, let me try the `&&` fold idea:

```c
if (cc != one) goto second;
func_8012D624(...);
if (cc == one && one == 1) goto rejoin;
```
folds.

What about `if (cc == one) { goto rejoin; }` written as `if (!(cc != one))`? folds.

What about making the second test use a *different variable* holding cc: `t = cc;` before the call, then `if (t == one)` after. gcc knows t == cc.

Hmm, unless t is HImode: `s16 t = cc;` — t == cc (same value).

What if t is `u8`? `t = (u8)cc;` then `if (t == one)` — the first test on cc doesn't imply t == one... wait, we need the SECOND test to survive. If the second test is on t (u8) and the first on cc, then gcc knows cc == 1 → t == 1 → folds.

If the first test is on t (u8) and the second on cc: the first test t == 1 (t = (u8)cc) doesn't imply cc == 1 → the second survives! And the cost: the `t = (u8)cc` is an andi (extra).

Same as k10 (1 extra insn).

Hmm, BUT: what if `t` is the *store value* somewhere... no.

What if the u8 conversion is free because cc's value is already a byte? No.

OK. Let me accept.

Let me spend the remaining time checking my other items' win.c files still score 0 (sanity) and preparing the log. That's useful work, and then I'll write the item 4 WALL at ~23:11.

Actually, I realize I should double-check the FRESH requirement for items 1-3: the src might have changed since I copied orig.c. Let me diff my orig.c against the current src for each item. If the src moved (earlier batches banking), I need to regenerate. Let me check.

For item 1: src/md_MAIN_033/md_MAIN_033.c lines 205-238. My orig.c was copied from it. Let me diff.
For item 2: src/ov_SC01_005/...:4558.
For item 3: src/ov_SC03_001/...:8054.
For item 4: just copied.

Let me do these diffs (they're quick).

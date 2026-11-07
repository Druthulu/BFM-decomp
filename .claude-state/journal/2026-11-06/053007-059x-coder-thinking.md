---
ts: 2026-11-06T12:30:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tNdQrlneZbR7e88Nqyqs
---
Target:
```
2214: li v1,1        (n=1 path)
2218: move v0,v1     <- cnt = n copy (v0)
221c: beqz v0,2278
2220: move s1,zero   (i=0 in delay slot)
2224: move s2,v0     <- lim = cnt copy (s2)
```
So: n in v1, cnt in v0, lim in s2. Three registers. `cnt = n + zr` → move v0,v1; `lim = cnt + zr` → move s2,v0.

Without the pin (s4), mine: `beqz v1`, `move s2,v1` — 2 regs.

Real C to get 3 copies: need the compiler to keep n, cnt, lim in separate registers. Plain copies coalesce. 

The `+ zr` trick: `n + 0` where 0 is an opaque reg → `(plus (reg n) (reg 0))` — not a reg-reg copy, so local-alloc doesn't merge; it assembles to `addu v0,v1,zero`.

Real C alternative: an expression that gcc can't fold to a copy but still compiles to `addu dst,src,zero`. Candidates:
- `cnt = n + 0;` — folded.
- `cnt = n | 0;` — folded.
- `cnt = n ^ 0;` — folded.
- `cnt = n * 1;` — folded.
- `cnt = n - 0;` — folded.

What about using a variable that is 0? `s32 zero = 0; cnt = n + zero;` — gcc propagates the constant 0 and folds. Unless `zero` is not known to be 0... it's a local const.

What if zero is a global that's known 0 at runtime? e.g., `extern s32 D_something; cnt = n + D_something;` — that would load the global (extra lw) — mismatch.

Hmm. The pin `zr = $0` is the standard trick precisely because C has no zero-register operand.

Alternative real C: get the copies through DIFFERENT computations that produce n. E.g., `cnt = n;` then `lim = cnt;` and use `cnt` in a way that prevents coalescing, like a loop... 

Hmm, what about the RC-12 doc: "docs/gcc-2.7.2-map/regalloc.md". The comment mentions cse.c make_regs_eqv head-promotion. Let me look for a real-C route: maybe using a different variable type for cnt (e.g., u32) or a cast.

What if `cnt` is s16? Then `cnt = n` truncates (sll/sra) — extra insns.

What if `cnt` is u32? `cnt = n;` same.

Hmm. What about making `lim` a different expression: `lim = cnt + zr` → `lim = cnt;`. Both coalesce with cnt.

What if lim is computed as `lim = cnt * 1`? folded.

The real question: can we get `move v0,v1` and `move s2,v0` with plain C? 

Idea: make n's value come from a different pseudo that's not a constant. The n is set in if/else to constants 3/2/1. Then `cnt = n` — coalescing makes cnt == n. But if n is used later too (it isn't), coalescing might fail.

What if we use n twice: `cnt = n;` and later `... n ...`? n isn't used later.

What if the beqz tests a DIFFERENT variable derived from n: `if (cnt != 0)` where cnt = n. If we instead write `if (n != 0)` for the guard and `lim = n` for the bound, then the guard uses n and lim is a copy of n. Still coalesced.

Real C for the v0 copy: maybe `cnt = n & 0xFFFF`? Extra andi.

Hmm, what about `cnt = n + i` where i is 0 at that point? i is assigned `i = 0;` AFTER cnt. If we move `i = 0;` before and write `cnt = n + i;` — gcc knows i==0? i is a local assigned 0; gcc propagates → folds.

What about `cnt = n + (s32)i;` with i being s16 and 0... folds.

OK, the pin is likely needed. But maybe the pin can be replaced by a real-C construct that creates an opaque 0: e.g., a variable that's not provably 0 to gcc, like reading a byte from a table? Adds a load.

Alternatively — maybe the pin's effect can be reproduced by a different allocation: if `cnt` and `lim` are used in ways that prevent coalescing, e.g., `cnt` used before and after... The beqz uses cnt; lim is used in the loop condition. Since cnt is used in the guard and lim in the loop, they have different live ranges: cnt dies at the guard; lim is born after. So `lim = cnt` at 2224 — cnt is dead there, so coalescing lim with cnt is possible. In target, cnt is in v0 and lim in s2: the move s2,v0 exists because lim must live across the call (callee-saved s2) while cnt is in a caller-saved v0. If lim were coalesced with cnt, lim would be in v0 — but then it must survive the call at 2250 (jal func_8017E1D4), and v0 is call-clobbered! So lim MUST be in a callee-saved reg (s2). Hence the move s2,v0 is forced by the call, not by coalescing. Hmm, but then plain C should also produce `move s2,v1` (as mine does).

Right — mine has `move s2,v1` (lim from n's v1). The only difference: mine lacks the `move v0,v1` (cnt copy) and tests v1 instead of v0. So the issue is just the cnt copy for the guard.

Why does target need cnt in a separate v0? Because `cnt = n + zr` is a plus, not a copy, so local-alloc doesn't merge cnt with n. Then the beqz tests cnt (v0), and lim = cnt + zr copies from v0.

Real C: we need `cnt` to be a value distinct from n. What if `cnt` is computed as something gcc can't fold but that's semantically n? 

Hmm, what about: `cnt = n; if (cnt != 0)` — gcc coalesces cnt with n. What if we use `n` in the if directly and `cnt` only for lim? Then cnt = n coalesces with n (n dies at cnt=n), and lim = cnt coalesces too → lim in v0? Then the move to s2 for the call.

Let me test a few variants:
- t1: `if (n != 0) { lim = n; ... }` — no cnt at all.
- t2: keep cnt = n but test n.
- t3: `cnt = n & 0xFF;`? changes value if n > 255 (n is 1..3) — semantically safe here! n is 1,2,3 (or 1). So `cnt = n & 0xFF;` is equivalent. But it emits `andi v0,v1,0xFF` instead of `move v0,v1` — opcode mismatch.
- t4: `cnt = n * 1`? folded.
- t5: `cnt = (s32)(s16)n`? n is s32 with small values; (s16)n for 1..3 is the same. Emits sll/sra — mismatch.

Hmm.

What about getting the copy via a different mechanism: `cnt` is a `volatile`? No (memory).

What about `cnt = n;` where n is declared `register`? no.

Let me look at the s4 diff more: target also has `move s2,v0` and mine `move s2,v1`. So both have the lim move. Only the cnt copy (1 insn) is missing.

Can we create a real second set for cnt that compiles to `addu v0,v1,zero`? That's a copy. C copy → coalesced. Unless the copy is forced by a hard-register conflict...

What if `cnt` is used in a call argument? No calls.

What if `cnt` is used across a call? No call between.

Hmm, what if we make `cnt` used AFTER the loop (so its live range overlaps lim's)? The target's cnt dies at the guard. If cnt were live longer, the guard would still test it. But an extra use of cnt would be a keepalive (fake).

What if `n` is used after cnt = n? n is a local; if n is used after, n and cnt can't coalesce. But n isn't used after — adding a use is fake.

Hmm, unless there IS a legitimate later use: no.

What if we restructure so cnt is computed differently: e.g., 
```
if (D_8011511A != 0) { ... n = 3 or 2 } else { n = 1; }
cnt = n;
i = 0;
if (cnt != 0) {
    lim = cnt;
```
What if we inline n into cnt's computation: `cnt = (D_8011511A != 0) ? ((t-2<2)?3:2) : 1;`? That changes the codegen a lot.

OK, maybe the pin can be replaced by a real-C opaque copy using the "pointer reuse" trick: e.g., `cnt = *(s32 *)&n;`? Taking the address of n forces a stack slot → lw from stack. Mismatch.

What about `cnt = (s32)(u32)n;`? no-op.

Hmm, what about `cnt = n + (i = 0);`? i=0 is a constant → folds.

What about `cnt = n + (s32)D_800B9A02 * 0;`? folds.

Honestly, the `$0` pin might be the only way (the comment says "RC-12 opaque copies ... plain `cnt = n;` coalesces the pair away"). This suggests the pin is a known-needed lever. The item's kinds include "pin", so the goal is to crack it — maybe impossible → WALL.

But let me check the other levers first: maybe with barriers/keepalive removed the pin becomes removable, or vice versa. The combined s5 (all removed) = 10.

Let me look at s2 (barrier [4] removed) = 4 and s3 (memory barrier) = 4 and s1 (keepalive) = 8.

Strategy: crack what's crackable, keep the rest. If I can crack 2 of 3 kinds → PARTIAL.

Let me examine s2's diff (barrier removal, 4).

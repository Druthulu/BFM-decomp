---
ts: 2026-11-06T15:36:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2C7GgWHw6EtoQ0CATVIC
---
So without the launder:
- mine: `andi v0,v0,0x8000; beqz v0,...` and the second `if (s0 != 0)` is folded away (missing insn at 464).
- target: `andi s0,v0,0x8000; beqz s0,...` and an extra `beqz s0,...` at the end.

So s0 must be a real variable in $s0 and the dead re-test must survive.

The dead re-test: after the inner if, `if (s0 != 0)` — the compiler knows s0 != 0 in that path? Actually if s0 == 0 we skip the block, then `if (s0 != 0)` is false — so the test is not dead, it's needed for the else path. Wait: line 181 `if (s0 != 0) { ... }` then line 191 `if (s0 != 0)`. If s0 == 0, the first if is skipped and the second is also false. If s0 != 0, both true. So the second test is redundant (it's implied by the first). The target KEEPS it (dead re-test). Plain C folds it.

The asm's opaque re-set of s0 makes the compiler unable to know s0's value at line 191.

Real-C 2nd set: `s0 = s0 & 0x8000;` (value-preserving) — this would make cse unable to... well, cse would know s0 & 0x8000 is still the same value (s0 is already 0/0x8000). Hmm, but the re-test `if (s0 != 0)` after `s0 = s0 & 0x8000` — cse/flow may still fold since s0's value is known nonzero in the branch. Actually the branch `if (s0 != 0)` at 181 means in the true-arm s0 != 0 is known; flow records that. A 2nd set `s0 = s0 & 0x8000` — flow can compute s0 is still nonzero (0x8000 & 0x8000 = 0x8000). Hmm.

What about `s0 = (u16)s0;`? Same issue.

Let me just test a batch:
- b1: `s0 = s0 & 0x8000;` (no asm)
- b2: `s0 = (u16)s0;`
- b3: `s0 = (s16)s0;`
- b4: dead-reset style: `s0 = s0 | 0;`? folds.
- b5: `s0 = (s0 != 0);` → s0 becomes 1/0; then `if (s0 != 0)` same. But the target's andi sets s0 = 0x8000, and later uses? s0 is only used in tests. If s0 becomes 1, the codegen might differ (the andi result 0x8000 vs 1). The test `if (s0 != 0)` would be `bnez`. Target's andi is 0x8000 then beqz — consistent with s0 holding 0x8000. So b5 changes the value.

Hmm, what about the pattern from func_8017D73C: `n = (s16)n` at both sites. Here s0's value is 0 or 0x8000 — `(s16)s0` gives 0 or -0x8000 (0xFFFF8000). `if (s0 != 0)` still works. The andi would be... the target's `andi s0,v0,0x8000` gives 0x8000. If s0 were s16, the assignment `s0 = call() & 0x8000` where s0 is s16 → the andi produces 0x8000 then truncated? Hmm.

Let me just try several. Also try moving the launder's effect: a "real 2nd set" that cse can't fold because it's an expression with a different known value... e.g. `s0 = s0 + 0;` folds.

Alternatively use the dead-reset technique: set a *different* variable to 0 to break the cse class of s0? s0's class is s0 itself. Hmm.

Another idea: make the re-test read a *different variable* that is a copy of s0 made inside the if, e.g.:
```
if (s0 != 0) {
    ...
    hit = s0;   // copy
}
if (s0 != 0) ...
```
No.

Actually, think about what the target's dead re-test looks like: `beqz s0, e10` at the end. The compiler kept it because the asm re-defined s0. A real 2nd set that keeps s0's *value* opaque: `s0 = s0 & 0xFFFF;`? cse can fold. Hmm.

What about assigning through a *function-like* op that gcc can't fold: e.g. `s0 = (s32)(u16)s0;` — combine might fold. Let's test empirically: I'll write a gen script for item 2 with variants and score them all.

Let me look at the full function first to understand s0's type/decl and whether there are other uses.

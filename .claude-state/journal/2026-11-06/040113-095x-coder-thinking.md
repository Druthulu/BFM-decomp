---
ts: 2026-11-06T11:01:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oaI9Ig9TkOfkchUUqnHU
---
The big function has 6 levers per the comment: struct array, pin $2 (register n), two `3 + zr` RC-12 opaque copies, `__asm__("")` in the loop, and the memory barrier.

Kinds: barrier,pin. So we must remove:
- `register s32 zr __asm__("$0")` (pin) and the `n = 3 + zr` (which is an asm-derived opaque copy — a launder/pin).
- `__asm__("")` in the loop (barrier).
- `__asm__ __volatile__("" ::: "memory")` (barrier).
- The `aD800B9A02 __asm__("D_800B9A02")` — that's an asm-label alias (symbol name, not a codegen lever; per the worked example, it's allowed to stay: "Kept the TU-idiom extern asm-label alias ... (symbol name, not a codegen lever; was in orig body)").

So we need real-C replacements for:
1. `n = 3 + zr` (both sites) — the opaque $0-add copy.
2. The loop `__asm__("")`.
3. The memory barrier before D_801151D0 = ot.

These are documented as load-bearing. The task is to find lever-free equivalents.

Hmm, the comment says lever 3/4: BOTH `n = 3` sites must be `n = 3 + zr` so the value survives the noop-move deletion and stays cross-jumpable so reorg copies it into the delay slot. A real-C alternative: `n = 3;` (plain) — the comment says making both plain gives a `nop` in the delay slot; making one plain gives 145 ins.

So a lever-free body would score >0 unless a different C shape produces the same. This is exactly the "cse-opaque-copy" wall class (func_80181E64, func_800D0D7C: "the plain copy is dissolved by cse/combine; no plain-C spelling survives").

Given the twins already walled, these two are likely walls too, but let me try the obvious lever-free bodies and see the scores.

Let me build the lever-free base:
- Remove `register s32 zr __asm__("$0");`
- `n = 3 + zr;` → `n = 3;` (both)
- Remove the loop `__asm__("");`
- Remove the memory barrier.
Keep the aD800B9A02 asm-label alias.

Score it. Then try variants:
- `n = 3;` vs different spellings (e.g., a variable assigned 3 then used; `n = 3; n = n;`?).
- The loop barrier: try a do-while or a different shape.
- The memory barrier: try reordering statements.

Let me build and score.

Note: the two big items differ: func_8018B238 calls func_8018B478 directly; func_80187EA0 calls func_801880E0 via a cast. Also different globals.

Let me start with func_80187EA0.

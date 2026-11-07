---
ts: 2026-11-06T10:17:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_T66AZGBO52zF8Nn80gaH
---
div (r77) occurrences:
- insn 20: def (1 ref)
- insn 55 (sign-ext): uses r77 (ashift at 222) and defs r77 (1 use + 1 def = 2 refs)
- div at ~347/350: 2 occurrences (div:SI and mod:SI — the division emits both div and mod) = 2 refs
- div at ~392/395: 2 refs
Total = 1 + 2 + 2 + 2 = 7. Matches.

Interesting: each `q = diff / div` produces BOTH a div and a mod (for the `q == 0` check? no, the mod is emitted because gcc computes the remainder too? Actually the `(div:SI ...)` and `(mod:SI ...)` both appear — that's how gcc expands division (it computes both quotient and remainder). So each division = 2 refs of div.

So div has 7 refs. To get 8, I'd need one more occurrence. 

Hmm, what if we make the sign-extension explicit in a way that adds a ref? E.g., `div = (s16)(div & 0xFFFF);`? The `& 0xFFFF` might be folded.

What about `div = (s16)div; div = div;`? no-op.

Hmm.

What if we use the remainder somewhere? No.

Alternatively, reduce a's refs. Let me count a (r76):
- insn 17: def (1)
- insn 57: and (use+def = 2)
- bne (use)
- subu (use)
- addiu (use)
- addiu (use)
Let me grep.

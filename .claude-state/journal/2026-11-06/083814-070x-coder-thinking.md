---
ts: 2026-11-06T15:38:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cGkis2wvM2D1HzXUsRJ0
---
b2 (u16 n): the extra `andi a0,a0,0xffff` at 96 is the truncation. Everything else matches! So if I can make the truncation free... 

Hmm, `n = (u16)n;` emits `andi a0,a0,0xffff`. The target has no such insn. But wait — the target's `move a0,s1` at 92 and then `sll v0,a0,7` twice. If n's value were known to be a u16 already, the cast would be free. n = t = d/128, d = unk102 - unk100 (s32 fields?). Unknown.

What if instead of truncating, we use a value-preserving 2nd set that emits nothing? 

b1 (s16): `sll v0,a0,0x10; sra v0,v0,0x9` replaces `sll v0,a0,0x7` — the sign-extension merged with the shift (sll 16 then sra 9 = (n<<16)>>9 = (n<<7)>>0? Actually sll 16, sra 9 = (n << 16) >> 9 = sign-extended n << 7. So it's the same value for the multiply. But the count is 2 vs 1 → 557 vs 556.

Hmm. So the real 2nd set must emit NOTHING.

What C statement is a real second set that gcc keeps but emits no insn? The launder asm. Alternatives: an assignment that's later folded away entirely, leaving the RTL set but no instruction... e.g. `n = n & -1;`? folds in the tree.

What about assigning n from itself via a different variable that's dead? E.g.:
```
s32 n2 = n;   // copy
n = n2;       // ?
```
folds.

Hmm. What about the C0414 dead-reset: `n = n + 0;` no.

Think: cse folds `d - n*128` to rem because both use the same n. What if the *second* expression uses a different variable that holds n's value? E.g.:

```
n = t;
rem = d - n * 128;
...
if ((d - n * 128) < 0) rem = -rem;
```

If I introduce a copy `s32 n2 = n;` and use n2 in the test: `if ((d - n2 * 128) < 0)` — cse would know n2 ≡ n and fold. Unless n2 is a *separate* live value... cse merges copies.

What if the test uses `rem` computed differently... no, the target recomputes.

Let me look at the target's RTL to see exactly. In the target, after the first rem computation, there's a second computation `sll; sll; subu`. The duplicated sll (two sll) suggests reorg duplicated the sll into the delay slot of the bgez: `sll v0,a0,7` then `bgez v0,...` with the delay slot being another `sll v0,a0,7`? That's odd. Let me look at the actual target assembly around there.

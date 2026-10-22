---
ts: 2026-10-22T01:05:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Afa3OrRH5yDjZLP6qE6G
---
I see! In ysame, the do-while is INSIDE the `if (diff < 0x10) {` block (after the test), whereas in z8 the do-while is BEFORE the test.

So the placement matters: the do-while must be *after* the comparison (inside the if body), i.e. exactly where the asm was.

Wait, no: in the source, the asm was:
```
if (diff < 0x10) {
    __asm__("" : "=r"(diff) : "0"(diff));
    return 1;
}
```
So the asm is INSIDE the if body (after the test). My generator inserted the replacement at the asm's position → inside the if body ✓ (ysame). My hand-written z8 put the do-while BEFORE the test → wrong.

So ysame (the do-while + the re-computation, both inside the if body) = 0. And it's fully value-preserving:
- if branch: `if (diff < 0x10) { do{}while(0); diff = *(s16 *)(s1 + 0xA) - sum; return 1; }` — the re-computation is the same expression → the same value ✓ (dead, but faithful).
- else branch: `if (diff < 0x10) { do{}while(0); diff = sum - *(s16 *)(s1 + 0xA); return 1; }` ✓.

Hmm, but the re-computation *inside* the if body is dead (diff isn't used after) — GCC would remove it... but the do-while's CFG effect is what blocks the fold. And the re-computation provides the "fresh set" of diff.

Hmm, is the re-computation value-preserving? Yes — it recomputes the same value (from the same memory, no intervening store) ✓.

So the clean crack for func_8018656C:
```
if (diff < 0x10) {
    do { } while (0);  // !FAKE: do-while
    diff = *(s16 *)(s1 + 0xA) - sum;   /* the same value: a real 2nd set */
    return 1;
}
```
Hmm, the re-computation reads memory again — at runtime it re-loads the field (the same value, no side effects) ✓.

Let me write the win.c for func_8018656C with ysame's structure, and verify.

Note: the earlier win.c I wrote had the do-while BEFORE the test (wrong). Let me rewrite it properly.

Also note for the *other* items (D9D8, EF0C), the placements were at the asm's position ✓ (the generator did it right).

Let me write the correct win.c for func_8018656C.

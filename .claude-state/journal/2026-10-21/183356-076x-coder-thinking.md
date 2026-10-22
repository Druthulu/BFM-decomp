---
ts: 2026-10-22T00:33:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_IpEEVuEXFZzj7D3swoax
---
The target's structure:
- 1520: `beqz s4,159c` (if n == 0 → skip loop 1) — n is in s4.
- The loop 1 body: 1538-1598.
- 159c: `beqz s4,1618` (if n == 0 → skip loop 2) — the second loop's test.
- ...
- 1618: the third loop's test presumably.

So the target has THREE `beqz s4` tests (one per loop), with s4 = n.

In my c1 (lever-free), the residual showed:
- mine[30] `beqz s4,1694` vs target[30] `beqz s4,159c`
- mine[61] `beqz s4,1694` vs target[61] `beqz s4,1618`

So mine has only TWO `beqz s4` instructions (at 30 and 61), both jumping to the SAME address 1694, while the target has three, jumping to different addresses (159c and 1618).

So in my version, GCC *merged* the three `if (n != 0)` tests: since n is the same variable and doesn't change, GCC knows that if n != 0 then the second and third tests are also true → it eliminated the redundant tests (2 of the 3)!

That's exactly what the lever prevents: the asm makes n *opaque* after the first loop, so GCC can't know n is still != 0.

So the plain-C fix: make the *value* of n differ (or be unknown) between the loops. In plain C: recompute n before each loop from a source GCC can't fold!

E.g.:
```
n = 0x14;
if (unk70 >= 2) n = 0x10;
...loop 1...
n = 0x14;                     /* real 2nd set */
if (unk70 >= 2) n = 0x10;     /* recompute */
...loop 2...
```
Hmm, but that's still *known* (n is 0x14 or 0x10, and the test `n != 0` is still redundant if GCC can see the recomputation). GCC would compute n again and know it's nonzero → the test would be folded again.

Hmm! But wait: would GCC fold "if (n != 0)" where n = 0x14 or 0x10? It knows n is nonzero in that path → yes, it would eliminate the test.

Unless the recomputation is *opaque*: e.g. n's value comes from something GCC can't fold. Hmm.

But hold on: in the *target*, the first loop's test `beqz s4,159c` exists (the test for loop 1) and the second `beqz s4,1618`. So the target has all three tests. In my c1, the first test exists (at ins 30) but the other two were folded (because n is known nonzero).

Hmm wait, actually let me re-read: mine[30] `beqz s4,1694` vs target[30] `beqz s4,159c`. Both have a beqz at 30 — the *first* loop's test. But the *target address* differs: 159c vs 1694. In the target, the branch at 1520 goes to 159c (the second loop's test) — i.e. if n == 0, skip loop 1 AND skip loop 2? No wait: 159c is the second loop's `beqz s4,1618` test. So in the target, if n == 0, we jump to 159c (the 2nd loop's test), which then jumps to 1618 (the 3rd loop's test). So all three loops are skipped via a chain.

In mine, the branch at 30 goes to 1694 — which is probably the *third* loop's test or the end. So my version has: test1 → jump to 1694 (skipping loops 2 and 3 entirely, since GCC knows n != 0 after the first test... wait, if n == 0, then the first loop is skipped and loops 2,3 are also skipped since n is still 0 → GCC merged the three tests into one!). And the second `beqz s4` at mine[61] is the *third* loop's test? Hmm, mine has 2 beqz: at 30 and 61.

So in mine: test at 30 (loop 1's), and a test at 61 (probably loop 3's? or loop 2's). Anyway, GCC merged some.

So the fix: make the loops' trip counts *independent* variables, so that each test is needed! E.g. use a *different* variable for each loop:
```
n1 = 0x14; if (unk70 >= 2) n1 = 0x10;
... loop 1 uses n1 ...
n2 = 0x14; if (unk70 >= 2) n2 = 0x10;
... loop 2 uses n2 ...
```
Hmm, but GCC would see that n2 is the same expression as n1 → it can still merge the tests (CSE makes them equivalent).

Hmm, but if the recomputation is *real* (a second set), GCC's value numbering would make n1 and n2 equivalent → the tests merge again.

Unless the recomputation is *opaque*. Hmm.

What if the trip count for loops 2 and 3 comes from a *different source* that GCC can't relate? E.g. what if the trip count is derived from a *pointer difference* or from the loop's own array size? E.g.:

The arrays: D_80189324, D_8018934C, D_80189374 — each 20 entries (0x14 = 20 elements, i.e. 20 u16 = 40 bytes; the loop reads 4 u16 per iteration and i goes 0,4,8,...,16 → 5 iterations = 20 elements). And n = 0x14 (20) or 0x10 (16) — the *element count*!

So the trip count could be expressed as: the number of elements = 20 or 16, and the loop advances i by 4 (elements). Hmm, the loop condition is `i < n` where i counts elements and n is the count (20 or 16).

Idea: express n as the *size* of the array: e.g. `n = (sizeof(D_80189324) / sizeof(u16))` → 20 (a compile-time constant) → then the `unk70 >= 2` case gives 16. Hmm.

What if we express the trip count differently for each loop such that GCC can't merge the tests? E.g. loop 2's count = 0x14 - (unk70 >= 2 ? 4 : 0)? Still the same value → merged.

Hmm. But wait — do we even need the *value* to differ? The lever's effect is that n is *opaque*, so GCC can't prove n != 0 for loops 2 and 3. To get the same code, we need GCC to NOT prove n != 0 in loops 2 and 3.

Since n = 0x14 or 0x10 (both nonzero), GCC proves it. To defeat that, n must be a value GCC can't bound. E.g. n = something that could be 0.

What if the trip count is *derived* from a value that could be 0? E.g. what if the trip count is computed as a difference of pointers, or read from memory?

Hmm! Here's an idea: what if the trip count for loops 2 and 3 is read from a *global*? Is there a global holding the count? The original game code probably had a variable. Hmm, the decompiler chose 0x14/0x10 from the field unk70.

What if we compute the count as:
```
n = 0x14;
if (unk70 >= 2) n = 0x10;
```
and for loops 2/3, recompute it *from a source GCC can't fold*, e.g.:
```
n = (0x14 - ((unk70 >= 2) ? 4 : 0));
```
Same value → merged.

Hmm, what if the count is computed via a *pointer*:
```
n = (u32)((u8 *)&D_80189374[20] - (u8 *)&D_80189374[0]) / 2;   /* 20 */
```
A constant → merged.

So: to defeat the merge, the trip count must be *unknown* at the loop-2/3 tests. The only plain-C way: read it from memory (a global) or from a function call.

Is there a global that could hold it? Hmm, what about using the *field* unk70 directly in the loop condition?! I.e., instead of computing n = 20 or 16, write the loop condition directly in terms of unk70:

```
i = 0;
do {
   ...
   i += 4;
} while (i < (unk70 >= 2 ? 0x10 : 0x14));
```
Hmm! That's a *recomputation* of the trip count from the field, and it's not a variable — but the value is still known to be nonzero → GCC would fold the `if (n != 0)` test... but wait, in the C source the `if (n != 0)` test exists as a separate statement. If I inline the count into the loop condition, the *test* `if (n != 0)` disappears from the source → the target's `beqz s4` before each loop would be missing.

Hmm, but the target's structure is: `beqz s4, <next loop's test>` — the test is a real branch. In the C source, `if (n != 0) { do {...} while (i < n); }`.

To get the target's shape in plain C, each loop's `if (n != 0)` test must be *emitted* → the count must be opaque (unknown) at that point.

Hmm, what if the count is read from a *global* that the game uses? Let me look for a global near the arrays: D_80189324, D_8018934C, D_80189374 — these are the three tables. The count 20/16 is the table size in elements. Hmm, in the original game, the count probably came from a *variable* (e.g. a global count). The decompiler derived 0x14/0x10 from the target asm.

Since the target asm has the count in a register (s4) and the tests are real branches, the original code must have had an opaque count. But the decompiler reconstructed it as 0x14/0x10 (a known value) — and then needed the lever to restore the branches.

So plain C with a known count → the branches vanish → mismatch.

Can we make the count opaque in plain C? Ideas:
- Read it from a global: is there a global variable that holds a count used here? Let me look at the surrounding code in the TU (the seed function func_8017FAC0 in ov_SC02_026) — maybe it has a similar structure with a different (opaque) count. Let me check the sibling function to see how the count is derived there! That's a great idea: the sibling might use a variable that's opaque.

Let me look at func_8017FAC0 in src/ov_SC02_026/ov_SC02_026_jr_8017C180.c.

Actually, the comment says "Adapted from the byte-matched sibling func_8017FAC0". Let me look at its loop structure.

That's worth 2 minutes.

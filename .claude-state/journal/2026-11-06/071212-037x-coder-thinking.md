---
ts: 2026-11-06T14:12:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AmeFiRyXn4XzTytuiuI5
---
Very relevant: func_8017F6B0 (WALL lreg-qty-priority): "t3 (2 refs/5, pri 4000) takes a2 before the a0-copy (5/27, 3703); the keepalive's asm on t3 and on off kept t3 live to insn 71 (pri 1666) and the addr temp live past the t4 load (t4->v1); no real-C use survives past the store (best 4)".

And func_8017DD04 WALL greg-ref-count: "global-alloc: mlo (5 refs) loses a2 to c80/cFF (12 stores); keepalive adds 6 refs; pin $10 keeps ob's const address in t2...; lever-free 297=297 permuted, 36 tries".

So these are known walls. But my task is to try. The item here is keepalive with two asm statements that add refs. The prior walls suggest it's hard.

Let me reconsider. Maybe there IS a real-C crack. The key: i and dst tie at 11 refs; dst wins on shorter live range. If I can make i's live range SHORTER (not refs higher), i would win.

Global allocno live_length is measured in insns across the whole function. i: born at `i=0` (block 3), dies at last use in loop (block 17). dst: born at `dst=src+n` (block 14), dies at `dst++` (block 17). So dst's live length is much shorter. To make i shorter: declare i inside the do-while? Then i=0 inside the loop, but target has `move $10,$0` before the `blez` guard (outside the do-while) — actually target asm:
```
	lh	$3,-4($13)
	lh	$2,-2($13)
	mult	$3,$2
	move	$10,$0        # i = 0
	lw	$9,0($13)     # src = arg0->data
	mflo	$12          # n
	sll	$2,$12,1
	blez	$12,$L129
	addu	$11,$9,$2    # dst = src + n
```
So i=0 is before the blez, in the block with the mult. If i is declared inside the do-while, its init would move inside the loop (after the blez), changing codegen. Unless... the loop is entered only once? No.

Hmm. So i must be initialized before the guard, giving it a long live range.

What if I restructure so i's death is earlier? i is used in `i++` and `slt` at the end. Can't avoid.

What about dst: can I shorten dst's life further? dst born at `dst = src+n` (in block 14 before the blez). If dst were born inside the loop, its life would be shorter but codegen changes.

Alternatively, raise i's refs with real C. Ideas:
- Use i as the array index in the store: `*(dst + i) = out`? No, dst already advances.
- Change `dst++` to `dst += 2`? same.
- Write `src[i]` instead of `*src`? changes addressing (adds shift).

Hmm, what about the loop condition: `while (i < n)`. What if I write `while (n > i)`? Same RTL (slt operands swapped maybe, generating `slt $2,$12,$10`? no, `n > i` -> slt with operands (i, n)? Actually gcc canonicalizes). Might produce identical code but the ref count for i is the same.

What about `i = i + 1` written as `i += 1` — same.

What about using i in a redundant but real way that the optimizer keeps? E.g., the `if (out == 0 && px != 0) out = 0x8000;` — unrelated.

Hmm. Another angle: lower dst's refs by one. dst appears in: `dst = src + n` (set), `*dst = out` (use), `dst++` (use + set). If I combine `*dst = out; dst++;` into `*dst++ = out;`, the RTL is the same two insns but maybe refs counted the same. Actually in RTL: `*dst++ = out` generates `(set (mem (dst)) out)` and `(set dst (plus dst 2))`. Same 2 occurrences. No change.

What if I use `dst[i]`? no.

Alternative: eliminate `dst` entirely by deriving it from `src`: `src[n] = out`? Then dst is computed each iteration (adds instructions). No.

Hmm, what about making `n` the loop counter and comparing differently? E.g., `for (i = 0; i != n; i++)` -> bne instead of slt; target has slt, so no.

What about splitting i into two pseudos? e.g., a separate counter used for the condition. That adds a reg.

Let me reconsider the problem from the global-alloc priority formula. Let me read global-alloc.c (it might be named global.c in 2.7.2). Let me find it.

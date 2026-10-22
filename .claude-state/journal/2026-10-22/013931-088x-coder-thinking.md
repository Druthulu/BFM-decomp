---
ts: 2026-10-22T07:39:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_0rxaXmokZU4cQTEha4wC
---
Item 7: func_8017E4DC. The launder is at the end of the while loop:
```
        rp += 1;
        q += 4;
        __asm__("" : "=r"(q) : "0"(q));  // !FAKE: launder
        i++;
        off += 8;
```
So `q` gets a 2nd set → kills the sched1 birth boost on q's birth (q = D_801AAD6C) → the loop's address computation isn't hoisted/strength-reduced?

The lever-free replacement: a real 2nd set of q. q is a `s16 *`. Options:
- `q = q;` → cse removes.
- A compound: `q += 0;` → folded? `q + 0` → folded to q (hmm, but for POINTERS, `q + 0` might not be folded! gcc's fold for `p + 0` → p ✓ it is folded).

Hmm. What about the G11 recipe: `q &= 0xFFFF;`?? That changes the pointer's value ✗ (it would truncate the pointer).

Hmm. What about `q = (s16 *)((s32)q + 0);`? folded.

What about a real 2nd set via a mode change: `q = (s16 *)(s32)q;` — same mode.

Hmm. What about the "dead reset" trick? `q = 0;` after the use — but q is used in the next iteration (q += 4 and q[3] = 0). So a reset would break the loop ✗.

Hmm. What is the launder's role here? Let me look at the target's assembly for the loop.

The loop:
```
    while (i < 4) {
        q[3] = 0; q[2] = 0; q[1] = 0;
        *(s16 *)((s32)D_801AAD6C + off) = 0;
        func_8012C51C(rp, arg0);
        rp += 1; q += 4;
        [launder q]
        i++; off += 8;
    }
```
The launder gives q a 2nd set → the q pointer's induction variable isn't strength-reduced (loop.c) — i.e., the target computes the addresses manually rather than using loop.c's IV.

Hmm! The comment on the moves.md for similar items: "pin | func_8017ED28 | MATCH — for+switch(case 0: continue) rewrite of goto body; single biv p (q spelled p + 10) (W02)".

So the recipe might be: write the loop so that there's a single induction variable, spelling q as an offset from a base.

Let me look at the target's assembly to see what the loop looks like.

Let me disassemble the target function.

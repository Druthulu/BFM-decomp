---
ts: 2026-10-22T13:08:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_PVijCMsFYK7vfEOuu8LG
---
Now I can see the target's second block:

```
14fc: lhu s2,26(sp)      ; bx = out.vy
1500: lhu s1,24(sp)      ; ay = out.vx
1504: lui v0, hi(D_800B9A02)
1508: lhu v0,0(v0)       ; aD800B9A02
150c: move a2,zero
1510: sw zero,32(sp)     ; prim.attr = 0
1514: sb s3,44(sp)       ; prim.r = white
1518: sb zero,45(sp)
151c: sb zero,46(sp)
1520: addiu s4,s2,-93    ; by = bx - 0x5D
1524: addiu s0,s1,123    ; ax = ay + 0x7B
1528: addiu s2,s2,-87    ; bx = bx - 0x57
152c: sll a1,v0,0x2      ; the index computation
...
153c: addiu s1,s1,117    ; ay = ay + 0x75
1540: sh s1,36(sp)       ; prim.x0 = ay
1544: sh s4,38(sp)       ; prim.y0 = by
1548: sh s0,40(sp)       ; prim.x1 = ax
154c: jal GsSortLine
1550: sh s2,42(sp)       ; prim.y1 = bx
```

WAIT!!! This is the SECOND block (corner 1's continuation? hmm). Let me re-read: this shows `lhu s2,26(sp)` (out.vy) and `lhu s1,24(sp)` (out.vx) — the corner-1 loads — and then the addiu's: by (s4 = s2-93), ax (s0 = s1+123), bx (s2 = s2-87), ay (s1 = s1+117) — and the stores: sh s1,36(sp) (prim.x0 = ay), sh s4,38(sp) (prim.y0 = by), sh s0,40(sp) (prim.x1 = ax), sh s2,42(sp) (prim.y1 = bx).

So THIS is the corner-1 block (the first prim), not the second! And the order of the addiu's is: by, ax, bx, ay ✓ (the source order).

Hmm, so where's the SECOND block (with the ax/by launders)? Let me look further in the target. The second block would re-use ax/by (prim.x0 = ax; prim.y0 = by; prim.x1 = ay; prim.y1 = bx).

Note the target's addresses: 14fc is in the middle. Let me look at more of the target (the next 40 lines).

Interesting: the target's corner-1 block has the addiu order by, ax, bx, ay ✓ = the source order. And my compile gives ax, by, bx, ay.

Hmm, and the target's ay+0x75 (117) is at 153c — AFTER the index computation (the sll/addu chain) — i.e., it's scheduled late ✓ (my compile had it earlier).

So the differences are: (a) the order of the by/ax addiu's, (b) the position of the ay+117 addiu.

Both are SCHEDULING differences (sched1/sched2) driven by the priority of the pseudos (the S2 boost).

So the levers (the launders) affect the scheduling. And my g1's type changes (u32) changed the scheduling to be closer (score 6) — but introduced the lh loads and the andi.

Hmm! Interesting: so the type change altered the scheduling in the right direction for some parts.

Let me look at the remaining 6 mismatches for g1 again:
1. mine[63-64]: lh vs lhu (the loads) — 2 mismatches.
2. mine[75] addiu s1,s1,117 deleted / inserted at mine[80] — the scheduling of ay+117 (1-2 mismatches).
3. mine[85] andi s4,s4,0xffff (the extra andi) — 1 mismatch.
4. The branch target offset (a consequence).

So if I fix the loads (lhu) and the andi, I'd be close.

**FIXING THE LOADS**: the loads are `lhu` in the target (unsigned 16-bit extension). With ay/bx as s16, GCC chose lhu (in the original). With ay/bx as u32, it chose lh (the sign extension is needed for the 32-bit value).

Hmm, so I need ay/bx to stay 16-bit BUT ax/by to be 32-bit. h1 = ax/by u32 + ay/bx s16 → 37 ✗. Hmm, why so bad? Let me look at h1's diff.

Hmm, maybe because ax/by as u32 changes the stores (`sh` of a 32-bit reg ✓ same) and the arithmetic.

Let me look at h1's diff to learn.

**FIXING THE ANDI**: the (u16) cast on the pinned by → the andi can't be removed. What if by is NOT 32-bit but the 2nd set is on a different variable? Hmm.

Hmm, hold on! What if by's 2nd set is `by = (s16)by;` with by as **s32**? → 2 insns (sll+sra) ✗.

What if by is **u32** and the 2nd set is `by = by & 0xffff;`? → the andi (same) ✗.

Hmm, what if the 2nd set on by is a *copy from another 16-bit variable*? E.g., what if the source kept a copy: `by2 = by;` hmm, that's a move ✗.

Hmm, what if the 2nd set of by is a *reload from the prim struct*? `by = prim.y0;` → a load (lhu) ✗ (an extra insn, but hmm — the target has `sh s4,38(sp)` (prim.y0 = by) and later the second block stores prim.y0 = by again → the target's second block might reload it? Let me look at the target's second block!

Let me dump more of the target.

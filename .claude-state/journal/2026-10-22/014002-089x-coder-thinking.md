---
ts: 2026-10-22T07:40:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Vy6sQtu8EUe3C6UK8ZZq
---
The target's loop:
```
271c: move s3,zero        ; off = 0 (s3)
2720: move a0,s4          ; rp (s4) = D_801850BC
2724: sh zero,6(s0)       ; q[3] = 0
2728: sh zero,4(s0)       ; q[2] = 0
272c: sh zero,2(s0)       ; q[1] = 0
2730: lui at,0x0          ; the D_801AAD6C address
2734: addu at,at,s3       ; + off
2738: sh zero,0(at)       ; *(s16*)(D_801AAD6C + off) = 0
273c: jal func_8012C51C
2740: move a1,s1
2744: addiu s4,s4,20      ; rp += 1 (Rec_80int = 20 bytes)
2748: addiu s0,s0,8       ; q += 4 (s16* → 8 bytes)
274c: addiu s2,s2,1       ; i++
2750: slti v0,s2,4
2754: bnez v0,2720
2758: addiu s3,s3,8       ; off += 8 (in the delay slot!)
```
So the loop has 4 induction variables: s4 (rp), s0 (q), s2 (i), s3 (off).

The launder on q gives q a 2nd set → hmm, what does that change? The comment says "q's second set". Maybe without the launder, loop.c would strength-reduce q differently (e.g. use a single IV with offsets) → different registers.

Hmm, q is a pointer that's incremented by 8 each iteration; loop.c's IV would be s0 ✓ (it's already an IV). Hmm.

Maybe the launder prevents loop.c from noticing that q and off are related (q = D_801AAD6C + i*8 and off = i*8) → the target keeps both (s0 and s3).

Hmm, if cse noticed q = base + off, it might rewrite the q[3]/q[2]/q[1] stores to use s3 (off) instead of s0 → different code. The launder's 2nd set breaks that.

So the lever-free replacement: keep q and off as separate (don't let cse unify them). In plain C, how?

Option: make `off` a separate variable not derived from i... it already is.

Hmm, the risk is that gcc's cse/GVN notices `q = D_801AAD6C + 8*i` and `off = 8*i` and unifies them.

Hmm. Alternatively, write q's uses with an explicit offset so that q isn't used as a base...

Let me think about what plain-C changes give q a 2nd set:
- `q = q;` → removed by cse.
- `q += 0;` → folded.
- `q = (s16 *)((s32)q);` → folded.

Hmm, what about a compound assign that preserves the pointer: `q |= 0;` → for pointers, `q | 0` → folded? gcc folds `p | 0` → p? Hmm, maybe not! Pointer arithmetic with `|` is unusual; gcc's fold might not handle it (it would treat it as an integer op). If `q |= 0;` survives as an RMW, that's a real 2nd set of q ✓ (and the emitted instruction would be `or`/`move`?). Hmm, on MIPS `q | 0` → `move`? Hmm, gcc would emit `or q, q, zero`? Hmm, MIPS doesn't have an "or" with 0 optimized to a move? gcc would emit `move` (or `or reg,reg,$zero`). That would ADD an instruction ✗ (the target has 92 ins).

Hmm. Unless gcc folds it.

Let me try a few:
cand01: plain drop.
cand02: `q |= 0;` (hmm, a pointer | int — gcc warns but compiles? "invalid operands to binary |" for a pointer and int → gcc allows it with a warning in C? `q | 0` where q is a pointer → error: invalid operands. So no.)
cand02: `q = (s16 *)(q + 0);` → folded.
cand03: the loop rewritten as a `for` loop.
cand04: `q` used via an index: `*(s16 *)((s32)q + 6) = 0;` etc. — spelling the stores with explicit offsets (avoiding q[3], q[2], q[1]) → maybe the target's stores are `sh zero,6(s0)`, `sh zero,4(s0)`, `sh zero,2(s0)` ✓ (offsets 6, 4, 2 from q) — the C is q[3], q[2], q[1] (s16 elements → byte offsets 6, 4, 2 ✓).

Hmm.

Let me think about the launder's actual effect. Let me just try cand01 (plain drop) and see the diff — that tells me what the launder does.

Let me create the item dir files and scorecand01.

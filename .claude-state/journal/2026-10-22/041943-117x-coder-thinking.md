---
ts: 2026-10-22T10:19:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_0FAOKoqK3RloX5m3rOwL
---
Still 14. I've done 30 tries on this item (14 + 16). Time on this item: ~25 min ✓.

Let me now do the last item: 8017D81C (best 20).

Notes: Target (89 ins): `li v1,-1664` (x), `li a1,-3712` (y), `li a0,-848` (z) are materialised at insns 18-20 — right after `move s1,zero` (17) and BEFORE the first store (`li v0,104` = D_80192CF0 = 0x68 at 21) — and each is reused by every store of that value (x: 4 stores, y: 3, z: 3).

The lever: orig.c laundered the three constants:
`__asm__ __volatile__("" : "=r"(x) : "0"(x));` and `__asm__ __volatile__("" : "=r"(y), "=r"(z) : "0"(y), "1"(z));` (plus the $a0 pin on z — another row's lever, it stays).

The residual: lever-free (v1): 89/89 ins but 20 mismatches. Ours materialises x into $v0 and y into $v1 at their FIRST USE (insns 39-40, just before `D_80192CE0 = x`), the target materialises them at their ASSIGNMENT (18-19, in $v1 and $a1).

Mechanism: `x = -0x680;` is a constant holder. cse forwards the constant into its uses, so the pseudo holding it is BORN at the first use, and the `li` is emitted there. The launder READS x at the assignment point, so the pseudo is born there.

Wall tag: cse-const-holder.

Idea for a lever-free crack: make the constant live across the point where it's assigned — e.g. declare x/y/z at the top of the function and assign them early... but the notes say v2 (init at declaration) → 19 and the frame grows.

Hmm! Interesting: v2 = 19 (better than 20). The notes say "v2 x and y initialised at their declaration (so they are live across the call) — 19, and the frame grows to 40 bytes (x/y take callee-saved regs): the assignment must stay after `func_8001C2C4(v)`."

So the assignment must stay after the call (semantically: the values depend on a call's result).

Hmm. The target: the constants are materialized at insns 18-20, right after "move s1,zero" (17) and BEFORE the first store. And the call `func_8001C2C4(v)` — where is it? Before insn 18? Let me look at the target asm.

Let me dump the target asm for func_8017D81C and the current best candidate (v2 = 19).

The key insight: in the target, the three constants are materialized as $v1, $a1, $a0 (i.e. in specific registers) right after the "move s1,zero". Hmm, $a0 and $a1 — those are argument registers! And $v1.

Hmm, and the launder's asm outputs are "$=r"(x), "=r"(y), "=r"(z)" — the asm's output registers would be chosen by gcc: v1, a1, a0? Hmm.

So the target's shape: three constants materialized early (right after the "move s1,zero" at 17), in v1/a1/a0.

Our v1: the constants are materialized at their first use (insns 39-40) in v0/v1.

So we need the constants materialized early, in those registers.

Why would the constants be materialized early in the target? Because the launder's asm READS them at the assignment point → the pseudos are born there → the li's are emitted there.

Without the asm, gcc's cse forwards the constant to its uses → the pseudos are born at the first use.

Hmm! But: what if the constants were assigned in a way that the pseudo is born at the assignment — e.g. if the variable were *modified* after the assignment? Then cse couldn't forward the constant (the reg_equiv would be invalidated by the second set!) — per §195-I: "ANY second SET of a pseudo in the address's equivalence chain kills the fold".

Hmm! So: if x is assigned twice (e.g. `x = -0x680; ... x = -0x680;`)? That's an identity → not allowed. But hmm, what if the assignment is a *legit* re-assignment? Not in this function.

Hmm. What about the ordering: the target's constants are materialized at insns 18-20, i.e. right at the start of the block after the call. And in ours they're at the first use.

Hmm, what if the values are used in a way that requires them to be live earlier? E.g. if the first store of x happens early...

Let me look at the target asm and the def. Let me read them.

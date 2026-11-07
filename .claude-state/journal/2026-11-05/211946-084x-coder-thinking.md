---
ts: 2026-11-06T04:19:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FotrEKsSCB51ZCdrGeeW
---
w9 (p load after add) = 14, same. w8 = 18, worse.

Let me look at w9's diff — maybe the p load is now after addiu but the register is still a0.

Actually the remaining diff in w4 was: p register a0 vs target v1 (6 occurrences), and the p reload position (one insn). In w9, same score.

Maybe the key is the register allocation: target p = v1, mine a0. If p were in v1, the reload position might also match. Why does mine allocate a0 to p? Because a0 is free at that point (the switch's a0 value is dead). In target, v1 is used for p and v0 for v. In mine, v0 for v and a0 for p.

Hmm, in the target, `v` is v0 and `p` is v1. In mine, `v` is v0 and `p` is a0. The p pseudo could take a0 (caller-saved) or v1. Global alloc assigns based on priority; p is used twice (store, and the final store). In target, p got v1; in mine a0. The difference may be the *number of references* or the live ranges. In target, p has two separate live ranges (two loads), each short. In mine likewise.

Could the do-while around p's load (w5) change the live range to prefer v1? It didn't change score.

Let me look at the target's `==0` arm: at 48f4 lw v1,32(s1) — p in v1 there too. Mine w4: 48f4 lw a1,32(s1)? Let me check w4's disassembly around there. In w4 diff, mine[55] lw a0,32(s1) vs target lw v1. So p is a0.

Maybe the register choice is influenced by the earlier `move a0,s1` / calls: in the target, at 4950 `move a0,s1; jal func_80129350`, a0 is the call arg. The p value is dead by then. In mine, same.

Hmm, why v1? Global alloc's order: it allocates pseudos by priority. p (used in the store) vs v (used in the store). Both are short. The target gives v0 to v and v1 to p. Mine gives v0 to v and a0 to p.

What if the p variable is declared/assigned such that it gets a higher priority? E.g., p used 2+ times. In the `n<8` arm, p is used once. Hmm.

Maybe the issue is that the *v* variable and *p* variable are declared at function scope (s32 n, v, p). The target may have had them in a different declaration order or scope. "decl order" is a catalog move! Let me try changing the declaration order of n, v, p. Global alloc priority is influenced by the pseudo's regno (allocation order for equal priorities is by regno). The order of declaration affects pseudo numbers. Let me try permutations: p, v, n; v, p, n; etc.

Currently: `s32 n; s32 v; s32 p;` → n, v, p. Try `s32 n; s32 p; s32 v;` → p gets a lower regno than v, which might make p allocated first → v1, and v → v0? Let's test. Also other orders.

Let me create variants with different decl orders (from w4 to keep the good part).

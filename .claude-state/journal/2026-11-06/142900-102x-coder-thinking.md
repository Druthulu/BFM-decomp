---
ts: 2026-11-06T21:29:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7BFaK1uw5FGbCwsTvNlh
---
Item 4: the pin forces `n` into s0. Without the pin, n gets v1 (a caller-saved temp). Target uses s0 for n (the modulo computation). So the pin is load-bearing: n must be s0.

Why s0? `n` is used in the modulo-by-4 computation (q - (q/4)*4). It's a short-lived temp. The target keeps it in s0. Without the pin, it's in v1.

This is a local-alloc/global-alloc choice. n is defined and used within a block (no calls between? there's no call inside the modulo sequence). So local-alloc. The target's s0 suggests... hmm, why would a local temp get a callee-saved reg s0? Because s0 might be free and local-alloc prefers caller-saved? Actually local-alloc picks the first free reg in order 0..N; caller-saved come before callee-saved in reg_alloc_order? No, order is 0,1,2,...,16,17,... So v0/v1 (2,3) come before s0 (16). So a local temp would get v0/v1 first. But target has n in s0!

That means n is NOT local-alloc; it's global-alloc, OR the pin forced it. Without the pin, n gets v1 (local). With the pin, n is in s0.

Wait, the target has n in s0 because of the pin. To crack, we need real C that makes n (or the temp) land in s0. That's odd — why s0? Maybe because s0 is otherwise unused and the value is live across the two rand() calls? Let me check: the two modulo sequences are separated by `rand()` calls. Is n live across a call? Let's see:
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
m = (q - n) << 16;
if ((rand() & 1) == 0) m = -m;
```
n is used entirely before the second rand(). So n is block-local, not across a call.

But the target has n in s0. Hmm. Unless `q` (from rand()) is in v0 and n reuses v1 normally. Target: `move s0,v0; addiu s0,v0,3; ...` — n in s0.

Wait, maybe the target's s0 is NOT n but a different variable, and n is something else. Let me look: target lines 68-72:
```
move s0,v0       # n = q
addiu s0,v0,3    # n = q+3
sra s0,s0,2      # n >>= 2
sll s0,s0,2      # n <<= 2
subu s0,v0,s0    # n = q - n
```
So s0 = n. Yes.

Why would n be in s0? Perhaps because `q` and `n` and `m` are all live, and local-alloc runs out of caller-saved regs? But it's a small block. Or global-alloc handles it because n crosses a block boundary? The `if (q < 0) n = q + 3;` creates a branch, so n is defined in two branches and used after the merge → n crosses basic blocks → GLOBAL-alloc!

So n is a global allocno. Global-alloc assigns callee-saved regs to allocnos that cross calls or when caller-saved are exhausted. n doesn't cross a call, but global-alloc still allocates it. The order/preference determines s0 vs v1.

Without the pin, global-alloc gives n v1 (caller-saved, cheaper). Target has s0 (callee-saved). Hmm, that's unusual — why s0?

Maybe because the target was compiled with the pin forcing s0, and that's it. Without the pin, v1.

To make n land in s0 via real C: the pin is a hard-reg steer. Without it, we need the allocator to choose s0. That seems hard unless we change the code structure.

BUT: maybe the pin is *redundant* if we restructure the modulo computation. The `if (q < 0) n = q + 3;` is a manual sign-correction for the modulo. We could use a different formulation that avoids the branch, e.g., using unsigned or a cast. But that changes the code.

Alternatively, the target's `move s0,v0; addiu s0,v0,3` suggests the branch `if (q<0)` was converted to a conditional move (move/addiu both to s0). Actually the target has BOTH `move s0,v0` and `addiu s0,v0,3` — that's the branch structure: if q<0, s0=q+3 else s0=q. Wait, but it's a single basic block? The branch might be if-converted.

Hmm. Actually target:
```
move s0,v0        # else: n = q
addiu s0,v0,3     # then: n = q+3
sra s0,s0,2
```
Two instructions writing s0 without a branch — that's a conditional select without branch (MIPS has no cmov in 2.7). So maybe there IS a branch between them not shown (the diff only shows the replaced lines). Let me look at the actual target.s.

Let me read target.s around the modulo.

Actually, the key question: can real C make n go to s0? Options:
1. Make n live across a call (then global-alloc must use callee-saved). But the target's n is NOT across a call.
2. Change the declaration/type so the allocator prefers s0.

Hmm. Actually, maybe the pin's effect is not just register choice but the *allocno priority*. The pin makes n a hard-reg pseudo, which reserves s0. Without it, n competes and gets v1.

Let me look at the target.s to see if there's a branch and what s0 is. Let me read the region.

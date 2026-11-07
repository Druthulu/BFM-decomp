---
ts: 2026-11-06T16:57:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uDzPgQIq4nNaVn8urR7i
---
No REG_ALLOC_ORDER, so `reg_alloc_order[i] = i` — register numbers ascending. MIPS register numbering: 0=zero, 1=at, 2=v0, 3=v1, 4=a0... 16=s0, 17=s1... So find_free_reg picks the LOWEST-numbered free register. For n, the free registers include v1(3), a0(4), a1(5)... and s0(16). It picks v1. That's why n=v1.

So local-alloc naturally picks v1. The target has s0 because the pin forced $16.

To make n land in s0 via real C, n must be allocated by *global* alloc (not local), i.e., live across a basic block boundary or a call. A pseudo live across a call gets a callee-saved register via global alloc (or local-alloc with accept_call_clobbered=0 → call_used_reg_set excluded → s-regs only, and find_free_reg picks the lowest s-reg = s0!).

So: make n live across a call. Then local-alloc (if the pseudo is block-local but crosses a call) will use only callee-saved regs → s0 (lowest). That matches target!

How to make n live across a call with real C without changing the instruction stream? We need n's *use* to be after a call. The target's own RTL: does n cross a call? In the target, n = s0 and the target's n is used at `subu s0,v0,s0` at 8ea4, BEFORE the jal at 8ea8. So no.

Hmm. But wait — maybe in the target's RTL, n is a single pseudo spanning BOTH computations and the call between them! The target's s0 holds n from 8e94 to 8ea4 (comp 1) and 8ecc to 8edc (comp 2). Between them there's `jal rand` (8ea8, sign) and `jal rand` (8ec0). If n is ONE pseudo (one variable n) live from 8e94 to 8edc (across the calls), local-alloc would give it s0. And its value in between is overwritten (m uses it at 8ea4/8eac). Hmm, but the value n is dead after 8ea4 and redefined at 8ecc. If the allocator treats n as one quantity spanning 8e94-8edc, it crosses calls → s0.

In mine, n is v1 in BOTH computations (v1 at 8e94 and 8ecc). So mine also treats n as one pseudo but gives it v1 — because local-alloc considers n's live range within the block, and the two uses... if n were live across the calls, it couldn't be v1 (call-clobbered). Since mine uses v1 across the jal calls, n's live range must NOT cross the calls: n dies at 8ea4 and is reborn at 8ecc.

Hmm, so how is n live in the target? The target's s0 is also used for the first modulo temp (8df0-8e04) and m. So s0 is a busy register.

I think the pin's effect: the pinned pseudo n (hard reg $16) exists in the RTL; the pin makes the *same* pseudo live from the first assignment to the last use (a register variable declared at function scope, and the compiler treats the variable as one pseudo with two sets — but local-alloc can still split at the dead point).

Hmm, with a `register s32 n __asm__("$16")` the pseudo is a hard register, and the two computations share it. The hard-register pseudo is live across the calls in the RTL (it's one pseudo with two sets, and the liveness analysis sees n as live from set 1 to use 1, dead, set 2 to use 2 — unless the compiler doesn't kill it). Since it's a hard reg, it's always "live" anyway.

OK, practical approach: make n cross a call in the RTL. Options:
(a) Move the `m = (q - n) << 16` computation after the sign rand (source order), so n's use is after the call.
(b) Add a use of n after the call that's deleted later.

Let me try (a) with a sign variable. But the instruction order may change. Let's just test it.

Variant A:
```
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
s32 sgn = rand() & 1;
m = (q - n) << 16;
if (sgn == 0) m = -m;
```
Hmm, `s32 sgn` needs a declaration. We can reuse `t`? t is used. Let me add a variable `s32 sgn;` — that's a decl change inside the body (allowed; signature unchanged).

Wait, but "no signature or decl change outside the body" — inside the body is fine.

Let me test variant A for both computations.

Actually, simpler: since `m` is already declared, we could compute m after the sign rand using a nested expression:
```
m = (q - n) << 16;
```
No.

Let me think about whether the target's RTL could have the sub after the call and sched1 hoisted it. If so, variant A would match. Let's try.

Actually wait. There's another possibility that's much simpler: the target's n (s0) is live across calls because the pin's pseudo is *function-scope* and the two computations' n are the SAME pseudo (no split). Without the pin, the compiler might still use one pseudo for n, but local-alloc splits it because it's dead between? Local-alloc doesn't split; reload/global does. Hmm, local-alloc assigns one hard reg per pseudo per block; if the pseudo is one allocno with n_calls_crossed=0 (because liveness shows it dead across the calls), it gets v1.

Liveness: n is set, used, dead; set again, used. The two live ranges are separate; `reg_live_length` sums them. `qty_n_calls_crossed` counts the calls crossed by any live range: if n is dead at the call, 0. So v1.

To make n cross a call, the live range must include a call. Option (a) does that.

Let me test variant A.

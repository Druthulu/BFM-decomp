---
ts: 2026-11-06T16:26:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qLPrrZsBOGKmBgwyB82L
---
The orig.c is 36 lines vs the src's 36 lines but the last 3 lines differ because the sed range ended. Actually sed 150,185 gives 36 lines and orig.c is 36 lines... wait diff says lines 37-39 extra in orig.c. So orig.c has 39 lines. My sed range cut it off. Let me diff properly using awk extraction of the function.

Actually simpler: the orig.c content matches src def except my range was too short. So SAME body. Fine — the orig.c is current.

Let me now think about the target vs what a lever-free body produces.

Target: 
- ret (the return of func_801638A0) goes to v1 (`move v1,v0` at 34c) and then `andi v0,v1,0x8000`. So ret is in v1, m in v0.
- pin $3 for ret (v1) and pin $2 for m (v0).

Interesting: the target actually uses v1 for ret and v0 for m, which is... the pins say ret $3 (v1) and m $2 (v0). So the pins match the target. Removing them lever-free means we need allocator to naturally put ret in v1 and m in v0.

Wait — hold on. ret's pin is $3 = v1. Target has `move v1,v0` then uses v1. Yes.

So the question: can plain C get ret into v1 and m into v0? Let me think about local-alloc: v0 is the call return; `ret = func_801638A0(...)` - the result comes back in v0 and then copied to v1? Actually target does move v1,v0 right after the call. In the orig.c the call result is assigned to `ret` which is pinned $3 (v1), so gcc inserts move v1,v0. Without pin, ret would naturally be v0 (the call's return register) and no move. Then `m = ret & 0x8000` would be computed into another reg.

Hmm. So the target requires a copy from v0 to v1. That means ret must be a different pseudo than the call result. In plain C, `ret = func(...)` gives ret = call result in v0 naturally. To force a copy... hmm.

Wait, but why does target do move v1,v0? Because ret is used multiple times? `ret == 0` test and `m = ret & 0x8000`. With ret in v0 and then andi into... Let's see: if ret is v0, then `if (ret==0)` beqz v0; then `m = ret & 0x8000` → andi v0, v0, 0x8000 (reusing v0). But target: beqz v1, andi v0,v1,0x8000. Hmm, the target has ret in v1 and m in v0.

How does gcc naturally do this? If we write:

```
s32 ret = func_801638A0(...);
if (ret == 0) {
} else if (ret & 0x8000) { ... }
```

Without m variable, `ret & 0x8000` could be done directly in v0: `andi v0,v0,0x8000`. But target does `andi v0,v1,0x8000` — so ret lives in v1 across the test. That happens if ret is needed after... no, ret isn't used after.

Hmm, actually target moves v0->v1 and then tests v1. This is what gcc does when the call result pseudo is being copied into a pseudo that is live across... Actually with `ret` assigned then compared, gcc would keep it in v0 and test v0. The `move v1,v0` implies the call result and the variable are separate, e.g.:

```
if (func_801638A0(...)) ...
```
No.

What if the source is `s32 ret = func(...); if (ret) { if (ret & 0x8000) ... }`. Then cse/combine might... Hmm.

Actually consider: the call returns in v0. Then `move v1,v0` could be because v0 must be free for the andi result. Local-alloc: ret pseudo = v1 because v0 is used by m's andi? Let's think: local-alloc assigns hard regs per basic block. The call insn returns to a pseudo (say r80). Then ret is a copy r80->ret. If ret and the call result are different pseudos, gcc's copy propagation would usually coalesce... unless ret is live in multiple blocks or used in a way that blocks coalescing.

Actually the target's shape: beqz v1 (ret), andi v0,v1,0x8000, bnez v0. So ret = v1, m = v0. Both computed in the same block. In local-alloc, each pseudo gets a hard reg; the call result comes in v0 (hard return reg). If `ret` is a copy of the call result, gcc usually makes ret = the call result pseudo directly (expand assigns the call result to a pseudo, then the assignment target might be a copy). Actually in gcc 2.7.2, a function call's return is moved into the target pseudo directly if types match? The call insn is `(set (reg v0) (call ...))`? No — the call sets the return register, then there's a move from the return register to the pseudo. That's how it works: `(set (pseudo) (reg 2))` after call. So the pseudo gets its own hard reg in local-alloc; it can be v0 by copy preference (local-alloc has copy preference to tie the pseudo to the return reg). So naturally ret would be v0, no move.

So target's `move v1,v0` means ret was NOT tied to v0 — ret got v1. Why? Because... hmm, maybe because of the m pseudo. Local-alloc qty priority: m and ret. Actually let's look at the moves database: this is a "pin" kind item. The pin was needed because plain C gives a different allocation.

Hmm, this is going to be hard. Let me first just run the tool to see what a lever-free body scores. Let me check bin/dt.sh usage and the delever_search.py.

Actually the brief says the workflow: `delever_search.py --try <TU> <fn> <file> --body` (score 0 = MATCH). And bin/dt.sh <itemdir> <body> [tail].

Let me check the tools.

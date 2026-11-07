---
ts: 2026-11-06T08:52:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IJV5MssKuQyIPkP1aBO6
---
Only one section; but my sed printed dispositions right after the header — that's the .greg file (I grep'd greg). The dispositions in greg: 72 in 17?? That's a later stage? Hmm, greg's dispositions are the *final* assignment after global-alloc. 72 in 17 = $s1 — but the final code uses a3 for the copy. This looks like a *different* function with the same name? No...

Hold on — maybe the "Register dispositions" section at the top of the function's greg dump reflects a different (earlier?) allocation because this TU has multiple functions and the dump interleaves. Hmm, "72 in 17" could be a pseudo in a *later* function that reuses register numbers. The greg dump for func_8017F6B0 is at 19486; the dispositions I grabbed may be from a different function section near it.

I'm going too deep. Let me step back and use empirical scoring with the insight that c1 achieved t3 live 6 (pri 3333) but the final allocation still gave t3 a2. Why? Because the a0-copy r72's live length also changed? r72 3703 > 3333, so r72 should be allocated first. Unless r72's allocation is blocked from a2 by r79 or others live at a2... In c1's register summary, are there other pseudos with pri > 3333 that take a2? r75/r76 4000 take a0/a1. Then r72 (3703) takes a2, then t3 (3333) takes a3. But the final code shows t3=a2. So something else happened.

Maybe the a0 copy is NOT a local-alloc pseudo (it crosses the call) → global-alloc handles it AFTER local-alloc, so t3 (local) gets a2 regardless. Yes! That's it. In w1, the a0 copy got a3 because local-alloc gave a2 to t3 and a3 was free. Global-alloc then placed the copy in a3. For the copy to get a2, local-alloc must leave a2 free: t3 must be allocated AFTER... no, local-alloc runs first and assigns a2 to t3 if t3 has a free a2 at its turn. t3's allocation doesn't depend on the global copy.

So to leave a2 free for the global copy, t3 must NOT take a2 — it must take a3 (or v1). Since local-alloc assigns ascending, t3 takes the first free reg. For t3 to get a3, a2 must be occupied (live) during t3's range by a local pseudo, OR t3 must be restricted (crosses calls? then call_used_reg_set excludes...).

Hmm, but in the target t3 IS in a3. Which local pseudo took a2 in the target? Maybe none — maybe t3's priority is such that it's allocated after another pseudo that takes a2. In w2 (t3 keepalive), the dump showed r77 (t3, 3/18) in a3 and r72 in a2 (global). Wait, but local-alloc assigns t3 (r77) BEFORE global. If a2 was free at t3's turn, it would take a2. It took a3, so a2 was taken by another local pseudo at that time, or a2 was in `used` due to regs_live_at.

In w2's lreg register summary: r77 = 3 refs/18 insns (t3 with keepalive) — its live range spans insns 39..71 (18 insns). During that range, other pseudos live at a2? The a0 copy r72 is global (not in regs_live_at? global pseudos are live too, and local-alloc's find_free_reg uses regs_live_at which includes global pseudos' live ranges!). YES — regs_live_at includes ALL pseudos (global ones too), since local-alloc's masks are built for all registers. Hmm, but then in w1, the a0 copy r72 (global) is live during t3's range, and if r72 had been assigned a2 by global... but global runs after local, so no.

Hmm, but `used` includes regs_live_at for hard regs only? No, regs_live_at is a HARD_REG_SET — it holds *hard* registers live at each insn (for pseudos already assigned). During local-alloc, previously assigned local pseudos' hard regs are marked. So a2 is taken only if a local pseudo got a2 earlier.

So in w2, which local pseudo got a2? The dispositions in w2's lreg: let me look at the right section. Earlier I read w2's lreg at 23770: ";; Register 72 in 6." — that's the .lreg dump's per-register assignment lines (local-alloc's result for ALL pseudos including globals? The lreg dump prints "Register N in M" for regs local-alloc assigned AND global? The .lreg dump is the local-alloc pass; it prints dispositions for all pseudos it handled. r72 was printed as in 6 (a2) — so local-alloc DID assign r72! That means r72 is a local pseudo (not global) in w2 (t3 keepalive). But in w1, r72 also printed "in 7" (a3). So r72 is local in both. Then the earlier "crosses 3 calls" line was from the .greg dump section, not lreg (I was reading across section boundaries — the .lreg file might contain a global-alloc summary at the end of each function? The line "Register 72 used 5 times across 46 insns; crosses 3 calls" came at offset ~24000, after the RTL — maybe that's from the *next* function or a second pass dump inside .lreg?).

Hmm, "crosses 3 calls" with 46 insns doesn't match this function (single call, 47 insns). Could be another function in the TU with the same pseudo number... no, "Register 72" is per-function. Whatever.

Key: r72 is local and allocated by local-alloc, so the allocation order is by priority, and in w2 r72 (3333) came before r77 (1666) → r72 a2, r77 a3. In w1 r77 (4000) came before r72 (3703) → r77 a2, r72 a3.

So the fix IS lowering t3's priority below r72's. In c1, t3's live became 6 → pri 3333 < 3703. But the final code still had t3=a2! Why? Let me check c1's actual allocation lines. Maybe r72's live length changed too in c1 (27 → ?). The lreg summary I printed for c1 showed r72 5/27 (3703) and r77 2/6 (3333). So r72 should win. Unless the *qty order* tie-break... no, 3703 > 3333.

Let me look at c1's lreg assignment lines properly.

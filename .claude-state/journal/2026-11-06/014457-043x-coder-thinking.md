---
ts: 2026-11-06T08:44:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WbDmNuOsDljtxU7QUICV
---
Now I understand w2! The keepalive `"r"(off)` was compiled as an asm operand using **r84** (the off*4 address temp), not `off` itself. So the asm keeps r84 (the address temp, pri 12000) live across the stores until insn 61. That extends r84's live range from 10 to 12 insns (pri 12000 → 11666), and importantly r84 is live ACROSS insns 42..59 (the stores and the t4 load).

Consequences: r84 (in v0) is live across the t4 load (insn 56), so t4 cannot take v0 → t4 gets v1! That's the target's t4=v1. And r77 = t3 got a3 because... with r84 live in v0 across t3's range, the allocations: r84 v0, r78 (t4) v1 (can't use v0 since r84 lives across it), then t1 a0, t2 a1, t3 a2? But dispositions say 77 in 7 (a3). Hmm, and r72 in 6 (a2). So r72 (a0 copy, 3333) got a2 before r77 (1666)? But r77's pri in the dump is 1666 (3 refs/18 insns). Why 3 refs and 18 insns for t3? t3 (r77) has uses at insn 39 (set), 51 (store) → 2 refs, live 5. The dump says r77: 3 refs across 18. That means r77 is NOT t3 — it's a pseudo used 3 times. Looking at insn 39, r77 = the D_801A546C load = t3, and it's stored at insn 51. So refs=2, live=5... but dump says 3/18.

Hmm wait, the dump at 23734 says "Register 77 used 3 times across 18 insns in block 0". But the RTL shows r77 in insns 39 (set) and 51 (use). Unless r77 also appears elsewhere (e.g., in the second keepalive on t3? No, w2 kept only the off keepalive; the t3 keepalive was removed). Wait — w2 was created by `grep -v 'keepalive.*r"(off)'` — removing the OFF keepalive, keeping the T3 keepalive! Let me recheck: I made w2 = orig minus the line matching 'keepalive.*r"(off)' → keeps t3 keepalive. And w3 = orig minus t3 keepalive → keeps off keepalive.

So w2 = t3 keepalive kept! That explains r77 (t3) being 3 refs/18: the asm uses t3 and extends its live range across the h updates. And the asm operand is r84? No wait, the asm at insn 61 uses (reg:SI 84) — r84 is the off*4 temp. Hmm, the asm in w2's dump is at line 4347 of the source. Let me check which line the t3 keepalive is: orig lines... In orig.c, the off keepalive is at line 19 and t3 at line 22. The asm in the dump references source line 4347 of the TU. In src, line 4347 is the off keepalive (I saw `__asm__ __volatile__("" :: "r"(off));` at 4347). Hmm! So w2 kept the OFF keepalive, not t3. Let me verify: grep -v 'keepalive.*r"(off)' removes lines containing `keepalive` and `r"(off)`. The off line is `__asm__ __volatile__("" :: "r"(off));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus9)` — contains keepalive and r"(off)" → removed. So w2 keeps the t3 keepalive. But the asm at insn 61 has operand (reg 84) and source line 4347. Hmm, 4347 in the TU is the off keepalive... unless the TU line numbers shifted? No, w2 body is spliced over the original body at the same location.

Wait, maybe I mixed up: in orig.c, line 19 is `__asm__ __volatile__("" :: "r"(off));`? Let me count: orig.c starts at TU 4330. Lines: 4330 void, ..., 4347 is the off keepalive (as seen in src Read: 4347 was off keepalive), 4351 t3 keepalive. So insn 61's source line 4347 = off keepalive, with operand r84 (off folded into off*4 = r84, and the asm's "r" constraint bound to the CSE'd value).

So w2 = t3 keepalive kept, and the off keepalive removed? But then the asm at 4347 shouldn't exist! Unless the splice didn't happen as I think. Let me recheck w2.c content.

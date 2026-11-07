---
ts: 2026-11-06T06:11:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_H0hKhKIQL9RzeDSdV60K
---
This is the OLD .greg dump? It says "72 in 17, 73 in 16" — so the param r72 got $17 (s1) and r73 (loop ptr) got $16 (s0). But this dump shows hard reg 16 in the conflict set of r72! "72 conflicts: ... 4 5 16 29" — r72 conflicts with hard reg 16. Why?

Because the source has `register u16 *s2 __asm__("$18")`?? No — wait, this dump has `(reg/v:SI 16 s0)` in insn 44 and `Hard regs used: ... 16 17 18 19 20 21 31`. Hard regs used includes 16..21. Hmm.

Wait — this could be the dump of the *original* TU (the copy at .run/P36/engine/score/.../p3/ov_SC03_029_jr_8017FF7C.c). That TU is the candidate spliced TU. Does it still contain the pin? I removed the pin in win.c. Unless the .c file kept something.

Hold on, look: `;; Register dispositions: 72 in 17 73 in 16 74 in 19 75 in 20 76 in 21 ... 80 in 18`. And `Hard regs used: 2 3 4 5 16 17 18 19 20 21 31`. If the candidate had no pin, why is hard reg 16 "used" as a conflict for r72?

Hmm, `register u16 *s2 __asm__("$18")` — in my win.c I replaced it. Let me check the t.c content. Maybe the TU's function body wasn't replaced correctly... but the score changed from 0 to 74, so it was replaced.

Wait, maybe this dump is stale — the dumps dir `dmp` I created now from t.c, which I copied from the p3 scratch of the --keep run. That should be the candidate. But dispositions show 72 in 17, 73 in 16 — matches my score (a0 in s1, loopptr in s0).

Now the question: why does r72 conflict with hard reg 16? Because r73 (the loop pointer) was already assigned $16? No — conflicts are computed before allocation. Conflicts with hard registers come from actual hard-reg references in the RTL.

Hmm, `Hard regs used: 2 3 4 5 16 17 18 19 20 21 31`. Those could be the results of global allocation (the dump after allocation). Conflicts listing "16" for r72... In global.c, when scanning, a conflict between an allocno and a hard reg is recorded if the hard reg is live at the same time. Since r73 gets $16... but conflicts are computed before assignment.

Wait, maybe hard reg 16 appears in the RTL as a genuine hard-reg reference from a previous function? No, this is one function's dump.

Let me check: is this greg dump possibly from a *different* function's section? The alloc_table said "func_801804A0 (cand)". The section begins ";; Function func_801804A0".

Hmm — so where does hard reg 16 come from in the RTL? Maybe the function uses `$16` somewhere else in the body... In the original src, the pin is `$18`. Hmm, but in the candidate body, maybe there's another pin (kinds said launder,pin — one pin). Let me grep t.c for __asm__ and $16.

Actually — maybe the conflicts with 16 come from a *call*: global.c records conflicts with call-clobbered regs; $16 is not call-clobbered.

Wait, actually. Let me reconsider: maybe r73 is not the loop pointer. Dispositions: 72→17, 73→16, 74→19, 75→20, 76→21, 80→18. Six callee-saved: $16..$21. r72 = param a0. r73..r76, r80 = other locals (s3, s4, s5, ent, loopptr).

The conflict line for r72 lists hard regs 16 among 2,3,4,5,16,29. Note "29" = sp. These are probably the *initial* live hard regs: at function entry, the params are in a0-a3 ($4,$5), and $sp. Hmm, $16?

I bet this is because in the *spliced TU* the function body is inserted into a file where the original function is still... no.

Hmm, let me just look at the beginning of the .greg dump for hard reg 16 references. Let me grep for "reg/v:SI 16" occurrences before the "Register dispositions".

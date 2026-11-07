---
ts: 2026-11-06T05:43:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ssJ54GWSJoE9mmXc6LD4
---
Score 22, mine 89 vs target 95 insns (6 short). Frame: mine 72 vs target 56 (mine saves more registers: s1 too).

The target reloads the a[]/b[] values from the stack after the calls; mine keeps them in registers, causing extra register pressure (s1 saved) and fewer insns.

Wait — mine has 89 insns (fewer) but a *bigger* frame (72 vs 56). Because it keeps values in registers (s0, s1) instead of reloading.

Hmm, why doesn't gcc reload? The calls func_8014FFDC(e, a, out) and func_80150150(e, b) take `a` and `b`. After the calls, `a` and `b` may be modified. gcc must reload. Unless gcc's cse considers the stack slots unchanged because... hmm.

Wait, maybe the issue is the *order*: the calls are before the `if (r6 == 0) b[2] = 0x7fff;` and the `if (r5|r6)`. The target reloads a[0], a[2], a[4] in the store arms. Mine keeps them in registers.

Actually, maybe mine DOES reload but from a different frame slot? No, the diff shows mine using a1 directly.

Hmm, let me look at the full candidate and target listings to understand.

Actually, the key: the barriers are at the START of each arm (before the stores). The memory clobber invalidates cse's knowledge, forcing reloads of a[0..4]/b[0..4] from the stack. Without the barrier, cse forwards the values from the earlier stores (kept in registers across the calls).

But wait — the calls could modify a/b, so cse shouldn't forward. Unless the calls don't actually get a pointer to a/b that aliases... `func_8014FFDC(e, a, out)` passes `a` — the callee could write to it. cse's `invalidate_for_call` invalidates all memory. So the values should be reloaded regardless of the barrier!

Hmm, unless gcc knows func_8014FFDC's prototype? It's `extern s32 func_8014FFDC(s32 e, void *a1, void *a2);` — no const info. So the call clobbers memory.

Let me look at mine's actual code around the arms.

Let me dump both.

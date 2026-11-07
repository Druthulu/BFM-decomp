---
ts: 2026-11-06T11:51:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_obNBh3tjIY1ctsUmpbrG
---
The .sched dump is 63k lines (multiple functions?). Hmm, the whole TU. Let me grep for the function name and the loop body. Actually the sched dump format uses RTL with insn numbers. Let me search for the function and find the srl.

Wait, grep found nothing for "srl.*0x10" — the RTL dump uses `(lshiftrt:SI ...)` not assembly. Right.

This is getting expensive. Let me think differently.

The residual is a single sched1 ordering. Let me consider what the launder does at the sched1 level: the launder is an asm insn that *uses* wz. In sched1 (gcc 2.7.2 sched.c), asm insns are barriers? An asm with a register operand is a normal insn. Its position affects the "birth" (birth is the first insn where a register is set... actually `birth` = the insn that sets the register, `death` = last use).

Removing the launder changes the death of wz's register and priorities.

Since I can't easily control sched1 with C, maybe a real-C change can alter the birth order of the two loads: the target loads zz (-4) before xx (-8). Mine loads xx first. Wait — but v7 (source swapped) gave the same result. So sched1 reorders to xx first regardless? That suggests sched1's order is driven by something else.

Hmm, in the target, the order is zz then xx. In mine, xx then zz. The source order is xx then zz in both (v2) and swapped in v7. Both give xx first. So sched1 prefers xx first in mine, and zz first in the target. The difference must come from the launder.

What does sched1 use? Priority = insn's "priority" = (depends on birth/death). sched.c computes priority from REG_N_SETS/REG_N_REFS? Actually sched1's `priority` function uses `INSN_PRIORITY` = insn's "cost" from REG_N_REFS... Let me look at sched.c's priority.

Alternatively: maybe it's not sched1 but the *order of the two loads in the RTL* before sched, and sched1 keeps them. In v7 (swapped source), the RTL order would be zz then xx... but the result was still xx first. Unless the compiler folded/canonicalized.

Hmm wait, v7's diff was identical. Maybe my v7 replacement didn't apply? I asserted `old in s`. It did apply. So the RTL order swapped but sched1 reordered back.

So sched1 has a strong preference. The launder changes it.

What if I add a real-C *use* of wz between the loads and the srl, mimicking the launder's effect? The launder is after `mny = wy + dy;`. Its effect: wz is used there. But wz is also used in box[0].vz/box[1].vz stores (before). Hmm, the launder extends wz's live range past those stores.

Actually the launder's purpose ("zero-byte re-tie") is to force wz into a register at that point. Since box[0].vz = wz stores are before, the value is used. The launder makes it live longer.

Real-C equivalent: a use of wz after `mny = wy + dy;` that doesn't change the code. E.g., `box[4].vz = wz;`? But that's assigned later anyway (box[4].vz = wz at line 2850, after gte calls). Hmm, the target's box[4..7] assignments happen after the gte ops.

What about `box[0].vz = wz; box[1].vz = wz;` moved after? No.

Hmm, what if I write the box stores as `box[0].vz = box[1].vz = wz;`? no.

Let me look at what the launder does more concretely: without it (v2), the code is 793 insns (same count) with one insn displaced. With it, 793. So the launder is *nearly* free.

What if I replace the launder with a real C statement that forces wz to be live at that point without emitting code? For example, use wz in the computation of `my`: `my = (wy >> 16) + dy;` — no. Or `mny = wy + dy;` — no.

What about a use like `if (wz == 0x1234) ...`? adds code.

What about assigning wz to a variable that's later overwritten? e.g. `box[2].vz = wv;` uses wv, not wz.

Hmm, what about making the launder's effect via a *dead* use that the compiler eliminates: e.g., `wz = wz;`? The compiler removes it.

Hmm.

Let me consider a different approach: the srl `wv = wz >> 16`. In the target it's at fdc, right after the loads. What if I compute wv from a *separate load* (s2 did that: `wv = part->zz >> 16;`) — still 3. cse merged the loads presumably.

What if `wv` is computed as `(wz >> 16)` but written *before* `wz` is loaded... impossible.

Let me look at the actual sched1 priorities. Maybe I can find in the dump the priority numbers. Let me look at the sched dump for the relevant loop. First find the function and the region. The dump is 63k lines; let me find the loop body by searching for "lshiftrt:SI" near "-4" ... hmm.

Let me search for the RTL pattern: `(mem:SI (plus:SI (reg:SI ...) (const_int -4)))`. Hard.

Alternative: use the .lreg dump to see the register assignment, and .sched to see the order.

Honestly, maybe I should consider this residual as a sched1-birth-order wall (there's an existing tag `sched1-birth-order`). The best lever-free (v2) is 3. That's a WALL with best 3, tag sched1-birth-order.

But wait — v2 removes only the launders and keeps the barrier → PARTIAL:barrier with score 3 (not 0). A PARTIAL requires score 0. So no PARTIAL. So the item would be WALL with best 3.

Hmm, but before walling, let me try a few more C moves on this single sched1 ordering. 30 tries needed for a WALL. I have: v1,v2,v3,v4(dup),v5,v6,v7,s1,s2,s4 = 9 scored.

Let me think about sched1's behavior. In sched.c, the priority of an insn is computed from `REG_N_REFS` of the registers it sets/uses? Let me look at the priority function.

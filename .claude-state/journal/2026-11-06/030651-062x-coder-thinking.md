---
ts: 2026-11-06T10:06:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VLoLhMQDyF5Vwh7V4uB5
---
Now I can map:
- r74 = d (set from a1 at insn 6; used in the divs at 339/382; sign-extended at insn 55 via ashift+... actually insn 55 sets r74 from sign_extend(subreg(r74))).
- r75 = s1ang (insn 20: set r75 from the load; used at insn 57 `and r77 = r75 & 0xFFF`, dies there).
- r76 = u5 (insn 52: `and r76 = r99 & 0xFFF` where r99 is the ratan2 result; used in the subus).
- r77 = u6 (insn 57: and of r75).
- r78 = iVar4.
- r79 = q.
- r80 = t.

So the globals: r74 (d), r75 (s1ang, local), r76 (u5), r77 (u6), r78 (iVar4), r79 (q), r80 (t).

Alloc table globals order: 78 80 79 77 76 74. So r78 (iVar4) first, r80 (t), r79 (q), r77 (u6), r76 (u5), r74 (d). And r75 (s1ang) is local → s0.

Target: d (r74) → s0, u6 (r77) → s1.

For d to get s0: s0 must be free when r74 is allocated (last in the global order). s0 is taken by r75 (s1ang local). So d gets s1.

For the target, either:
(a) s1ang (r75) got s1 (local-alloc), leaving s0 for d, OR
(b) s1ang got a caller-saved reg (not possible, crosses call).

If (a): local-alloc must give r75 s1. Since r75 is the only local qty crossing the call, it gets the first callee-saved in REG_ALLOC_ORDER. Let me check the MIPS REG_ALLOC_ORDER: maybe it's [2..7, 16..23, 24..27, 8..15...]. If so, the first callee-saved is 16 (s0).

To make r75 get s1, 16 must be unavailable at r75's live range. 16 is unavailable if some hard reg 16 is live there — i.e., if some other qty has 16.

What if `d` (r74) is allocated s0 by local-alloc BEFORE s1ang? d is global, so no.

Hmm, unless d is ALSO local. Is it possible for d to be local? d is set at insn 6 (block 0) and used in blocks 6,7,9 → global. Unless we restructure so that all d uses are in block 0.

What if we compute the division quotient *before* the branches? The divisions are in the if/else arms because of the `if (iVar4 >= 0)`. Hmm, what if we write:
```
q = iVar4 / d;
if (iVar4 >= 0) { if (q == 0) q = 1; }
else { if (q == 0) q = -1; }
```
Then there's ONE division, in block 0 (before the branch)! But the target has TWO divisions (one in each arm) at 394c and 398c. So no.

Hmm.

What if d is used in only ONE block? The target has 2 divisions.

OK so d is definitely global. So the target's allocation must be (a): local-alloc gave s1ang s1.

How? Let me look at REG_ALLOC_ORDER in the reference mips.h and whether s1 might come before s0. Let me check.

Actually — wait! Maybe the target's s1ang is NOT s1ang. Let me re-examine: in the target, `lh s1,18(v0)` loads s1ang into s1, then `andi s1,s1,0xfff` makes u6. So both s1ang and u6 are in s1.

What if in the target, s1ang is NOT a separate qty: the andi writes u6 in place, and s1ang is DEAD. If s1ang and u6 are tied into ONE qty, then that qty is global (u6 used in later blocks). Then local-alloc doesn't handle it; global-alloc does. Its priority: refs? The combined qty... Then the order would be different.

But the nopin dump shows s1ang as a separate local qty (r75) and u6 as r77. So in the nopin source they're separate. Maybe in the ORIGINAL, they were the same qty (tied by local-alloc's combine_regs when may_save_copy). Hmm, combine_regs ties a usedreg and setreg when "may_save_copy" (copy insn or input/output must share). For `andi r77 = r75 & 0xFFF`, does the input and output "must share"? The MIPS andsi3 pattern might be `(set (match_operand:SI 0 "register_operand" "=d") (and:SI (match_operand:SI 1 "register_operand" "d") ...))` — "=d" and "d" means output and input can be the same class but not forced. If the constraint were "0" for the input, they'd be tied. Let me check the mips.md andsi3 pattern in the reference.

If the input is tied to the output ("0"), local-alloc would combine r75 and r77 into one qty! Then s1ang+u6 would be a single global qty. But the nopin dump shows them separate (r75, r77) — so they weren't combined. Why? Because combine_regs refuses when the qty crosses a call or... Hmm.

Wait, maybe the andi3 pattern is:
```
(define_insn "andsi3"
  [(set (match_operand:SI 0 "register_operand" "=d,d")
        (and:SI (match_operand:SI 1 "register_operand" "%d,d")
                (match_operand:SI 2 "uns_arith_operand" "d,K")))]
```
The "%d" means commutative. Not tied.

Hmm.

OK let me try yet another idea: make s1ang's qty have more refs so its priority is higher than... no, it's alone.

Actually, WAIT. Let me reconsider: local-alloc processes ALL qtys (not just those crossing calls) in priority order. Qtys that don't cross calls get caller-saved regs. But some qtys might be assigned callee-saved regs if caller-saved are exhausted. The order: qtys sorted by priority. The high-priority ones (r78: 30000) get v0, v1, a0, etc. When it reaches s1ang (2857), which regs are free in its live range? Caller-saved regs are excluded because it crosses a call. So it gets the first callee-saved: s0.

Unless... some high-priority qty took s0 earlier! A qty that doesn't cross a call can still be assigned a callee-saved reg if it has a *preference* for one, or if caller-saved are full. Hmm.

Wait — actually, look at the nopin alloc table: r72 (v0), r81 (v0), r85 (v1), r88 (a0), r92 (v1), r95 (a1), r99 (v0), r100 (v1), r101 (v0), r102 (v0), r104 (v0), r106 (v0). So caller-saved regs are assigned to the local non-crossing qtys. s1ang (r75) got s0.

To make s1ang get s1, s0 must be taken. What if a high-priority local qty is given s0 because its caller-saved regs are exhausted? The caller-saved set for MIPS: v0,v1,a0,a1,a2,a3,t0-t9 = 2,3,4,5,6,7,8-15,24,25. Plenty.

Hmm. What if we make a qty *cross a call* and have higher priority than s1ang, so it takes s0? We'd need another variable live across the call, used after, in block 0 only. But then that variable adds instructions.

Wait — maybe there IS one in the original: the `arg0` pointer! In the target, arg0 is used for loads before the call. After the call, is arg0 used? Let me check the target asm after the jal: no, arg0 (a0) isn't used after. So no.

Hmm, but in the source, `s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);` — arg0 is used before the call. OK.

What about `arg1`? d = arg1 before the call.

Hmm.

Let me reconsider: maybe the target's s1ang was assigned s1 because REG_ALLOC_ORDER for the MIPS has s1 before s0?! Let me check the reference mips.h REG_ALLOC_ORDER.

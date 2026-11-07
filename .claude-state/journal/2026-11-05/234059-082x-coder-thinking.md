---
ts: 2026-11-06T06:40:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZZ3GGn73gfnn3fIerdhX
---
Now I see the tail RTL:
```
insn 84: t (73) = zero_extend(mem[a0+2])
insn 90: r96 = t << 2
insn 94: r98 = mem[r96 + D_801D0A3C]
insn 96: a0 = r72
call insn 98: (call (mem (reg 98)))
```
So t is dead at insn 90 (REG_DEAD). t is NOT live at the call. 

So why does r73 conflict with v0? Because... the call insn's clobber/use? t isn't live there.

Hmm, "73 conflicts: ... 2 29" (v0 and sp). Where does t conflict with v0?

Ah — maybe at insn 94: `(set (reg 98) (mem (plus (reg 96) ...)))` — no t.

Hmm, so maybe r73 is NOT t. Let me re-check: r73 is used 13 times across 14 insns, dies in 3 places, live at the start of block 4.

t = r73 appears in insns 42, 45, 54, 104, 59, 73, 77, 80, 84, 90 = ~10 mentions.

Hmm, "13 times". Close enough with the double-counting.

Conflict with v0: where? In global.c, a pseudo conflicts with a hard reg if the hard reg is live at the same time. v0 ($2) is live where? At the call (clobbered) — but t isn't live there.

Hmm, maybe the conflict arises because of the *call*: at the CALL insn, gcc marks all call-clobbered hard regs live; t is live... no.

Wait — maybe t is live at the call because of the REG_DEP_ANTI chain? No, those are scheduling deps, not liveness.

Hmm, let me reconsider: maybe r73 is not t but the *pointer* reg 79? No, 79 is block 1.

Alternatively, the conflict could come from `(reg:SI 4 a0)`... no.

Honestly, maybe the conflict with $2 comes from the very first insn: t's live range starts at insn 42. Hmm.

Let me look at the target's alloc table for the same: with the pin, r73 doesn't exist. Let me check the w3-equivalent (pin removed, launder kept)? That's not what I have.

Hmm, let me just check the .greg dump of my candidate for the "73 conflicts" line and think.

Actually — maybe simpler: the conflict is with the *hard reg $2* because the call insn at the end has `(use (reg:SI 4 a0))` and the call clobbers v0... and gcc's global_conflicts marks hard regs live at CALL insns for the whole function? Let me look at the code: in global.c, `note_stores (PATTERN (insn), mark_reg_clobber)` marks clobbered regs live; a CALL_INSN's pattern has `(clobber (reg 31 ra))` plus the call itself clobbers... In gcc 2.7.2, `CALL_INSN` clobbers are represented by `(clobber (reg ...))` for ra only, but there's special handling: `mark_reg_clobber` on a call marks the caller-saved regs live? Let me check: in global.c's global_conflicts, for CALL_INSN there's:

```
	      if (code == CALL_INSN)
		{
		  /* A call clobbers all call-clobbered regs */
		  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
		    if (call_used_regs[i]) SET_HARD_REG_BIT (hard_regs_live, i);
		}
```
Something like that. Then any pseudo live AT the call conflicts with all caller-saved regs. t is not live at the call (dies at insn 90).

Hmm, but flow's live analysis: is t live at the call? insn 84 sets t, insn 90 uses it (REG_DEAD there). So no.

Unless... the REG_DEP_ANTI chain `(insn_list:REG_DEP_ANTI 73 ...)` in the call — no.

OK, alternative: maybe the conflict is with the *return value* register: the call returns into v0 and... no.

Let me try yet another approach: just test whether making `t` a block-local in the middle changes things — that's the "split" variant (16).

I'm now at ~20 min on item 3 with ~22 tries. Let me do one more batch of ~10 variants to reach 30+ and then record the best (17) as a WALL.

Hmm, wait. Actually, hold on. Let me reconsider the problem from the top. The target's t is $2 everywhere. In my candidate, t is $3.

What if the issue is simply that the *global* allocno t has a lower priority than some local? No: t is FIRST in the alloc order (27857), so it gets the first free reg. The first free reg for a global allocno... hmm, but "conflicts v0" means $2 is excluded. Then t gets $3. And the local temps (r76 ST_REGS etc.) take $2.

So if I remove the conflict, t takes $2 and everything follows.

Let me find the source of the conflict precisely: grep the .greg dump for the conflict list and then look for what makes v0 live at t's live range. 

Alternative quick test: does the conflict disappear if the tail is `D_801D0A3C[unk2](a0)` (direct, no t)? v_direct = 16 (41 insns). Let me check whether that one has t in v0 in the middle... The score 16 with 41 insns means something else differs.

Let me look at v_direct's residual — if the middle block now matches (t in v0) and only the tail differs (41 vs 42 insns), that's a good sign!

Let me check.

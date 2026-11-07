---
ts: 2026-11-06T20:08:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7BTgN8ldR6PRoIOEwx0D
---
`n_non_fixed_regs` is a global from global-alloc? Let me grep in the tree. It's probably defined in global.c/regs.h. `n_non_fixed_regs` = number of regs not fixed = max_reg_num? Let me grep all reference.

Actually, let me take the empirical route. The difference is only the hoist. Candidate fixes:

1. Make the loop have more instructions so the threshold condition fails? insn_count grows → less hoisting. But that changes code.

2. Reduce `m->lifetime` — lifetime is the length of the live range: from the hoist point to the last use. If the constant pseudo is used once early in the loop, lifetime small. It is used once.

3. `savings` — for a CONST_INT insn, savings = 1 (or 2 if loop). Hmm.

4. Increase n_non_fixed_regs → threshold bigger → hoist more likely. Not helpful.

Wait — the hoist happened in mine but not target. The difference: in target the pin occupies $2, so... n_non_fixed_regs is the same. Hmm, unless the pinned reg affects `loop_has_call`? No.

Wait, maybe the difference isn't loop.c at all: in the target, `li v0,-1024` might be *inside* the loop because loop.c moved it but then reload/regalloc put it back? No, hoisting is permanent.

Alternatively in target the constant was NOT hoisted because its pseudo got `$2` — a *fixed* hard register — and loop.c refuses to move insns that set a hard register? Let me check: move_movables scans `if (GET_CODE (PATTERN (p)) == SET && GET_CODE (SET_DEST...) == REG && REGNO >= FIRST_PSEUDO_REGISTER)`? Let me look at the scan loop in find_movables. Actually at that stage, no hard regs are assigned yet (pre-reload). The pin makes a *pseudo* with a REG_USERVAR? The pinned variable is `register s32 v0 __asm__("$2")` — a user variable pinned via asm, which gcc models as a variable with a fixed hard reg? In gcc 2.7.2, `register int x __asm__("$2")` sets DECL_RTL to a hard register (or a pseudo with reg_renumber set later?). Actually GCC handles explicit register variables by making the DECL_RTL a REG with that hard regno. So uses of `v0` in the C source directly reference hard reg $2. And the -1024 store doesn't involve v0... 

BUT: in target, the `li v0,-1024` writes v0, which is the pinned register! Because the store `sh v0,10(v1)` uses v0 as the temp, and the pinned v0 variable is *not live* at that point (it was last used for the call result). GCC can use $2 as a scratch since the pin only reserves it while live? Actually a register variable's hard reg is reserved for the whole function? In gcc, explicit register variables reserve the hard reg globally (can't be used for other pseudos) — the wall tag "global-hardreg-reserve" says exactly that: "the pin's hard-reg pseudo reserves a reg for the whole fn". So v0 would be reserved... but target uses v0 for the -1024 constant, so it's NOT reserved.

Hmm, in the pinned orig (score 0), the body compiles to exactly the target: `li v0,-1024` inside the loop. So with the pin, the constant pseudo got v0 and stayed inside the loop.

Wait, maybe with the pin the loop.c hoist DID happen but to v0? No, the target shows li v0 inside the loop.

OK, empirically: the pin makes the constant land in v0 and stay in the loop. Why? Possibly because the pinned v0's uses make the -1024 insn *not* loop-invariant: cse/loop sees that v0 is set by the call result... no, different pseudos.

Hmm, unless: `v0 = func_8012C588(...)` — with the pin, the call result is written directly into hard $2. Then `*p = v0`. Then the store `sh -1024` also writes $2. loop.c might treat insns setting hard registers specially: it can't hoist an insn that sets a hard register because the hard reg is live across the loop boundary? Actually the constant's pseudo after the pin is still a fresh pseudo, not $2. The register allocator later assigns it $2. So loop.c decision is independent.

Unless the pin affects the *number of insns* or the loop structure. Hmm.

Wait, maybe the pin changed `n_non_fixed_regs`! n_non_fixed_regs is defined... let me grep.

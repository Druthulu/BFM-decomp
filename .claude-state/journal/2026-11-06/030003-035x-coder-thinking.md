---
ts: 2026-11-06T10:00:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sEYcrjqKbFATGqdmzYCK
---
Item 2: without the pin, `d` (divisor) and `s1ang` swap registers: target wants d in s0 and s1ang in s1; mine gives d in s1 and s1ang in s0. Also the prologue order differs (sw s0 / move s0,a1 / sw ra).

The pin forces d into $16 = s0. Without it, local-alloc picks s1 for d.

We need to steer d to s0 by real C. The keepalive on u5: "anchor u5 before the (s16)d cast" — i.e., without it, sched1 reorders `d = (s16)d` before the ratan2 result? Let's see after fixing the pin.

Strategy: use C0505 catalog moves. The register priority in local-alloc is determined by REG_N_REFS and live length. To make d (divisor) get s0 over s1ang, we need d to have higher priority than s1ang.

Wait, target: d in s0, s1ang in s1. Mine (no pin): d in s1, s1ang in s0.

s0 and s1 are the callee-saved registers available. Allocation order: local-alloc/global-alloc assign by reg_n_refs (higher refs get lower-numbered? Actually allocation order is by qty). In gcc, `reg_alloc_order` for s0..s7 is typically s0 first. The pseudo with higher priority gets s0.

So to get d into s0, d must outrank s1ang. d is used in the divisions (2 uses: in each branch of the if/else... actually `q = iVar4 / d` appears twice → 2 uses) plus the assignment `d = (s16)d` and `d = arg1` → maybe 4 refs. s1ang: defined once, used in `u6 = s1ang & 0xFFF` → 2 refs.

Hmm. The sibling cracks in moves.md: "keepalive | func_8014DD8C | WALL greg-pri-refs — each keepalive = +1 ref (var_s2 vs var_s3, arg0 vs arg2 priority)". And "pin | func_8017D924 | WALL lreg-v0-local-first".

Let me think about the C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse.

Since d is a divisor live across the jal, and it's `(s16)arg1`, we could write `s16 d = arg1;`? That changes width — the target does `move s0,a1` then `sll/sra` (sign extend) — wait, target: at [14] `lh s1,18(v0)` (s1ang load), and the `sll s0,s0,0x10; sra s0,s0,0x10` at [19-23]? Let me look at the target disassembly to understand.

Actually let me get the full target asm. I'll use --keep on the current src (scores 0) to dump. But it's a header TU; --keep gives the object of includer 0. Let me do that.

Actually, the --explain output already tells me a lot. Let me look at the target instructions around the prologue:

mine[2:2] insert target[2:5]: sw s0,16(sp); move s0,a1; sw ra,24(sp)
mine[3:6] delete: move s1,a1; sw ra,24(sp); sw s0,16(sp)

So target prologue: ... sw s0,16(sp); move s0,a1; sw ra,24(sp) → d is moved into s0 right at the start.
mine: move s1,a1; sw ra; sw s0 → d into s1.

Then [14]: mine lh s0,18(v0); target lh s1,18(v0) → s1ang.

Then target [19-23]: sll s0,s0,0x10; andi s1,s1,0xfff; bne s1,a0,...; sra s0,s0,0x10
mine [20-23]: andi s0,s0,0xfff; bne s0,a0,...; sra s1,v1,0x10

Hmm interesting: mine has `sll v1,s1,0x10` at [17] deleted. So target: d (s0) is sign-extended with sll/sra, and s1ang (s1) masked with andi.

So the key: swap register roles of d and s1ang.

How to steer? In gcc 2.7.2, local-alloc allocates pseudos in order of `reg_qty` priority: higher REG_N_REFS first (actually it's `qty` sorted by `refs` and `deaths`). The order among s0..s7 is fixed. The pseudo with higher priority gets s0.

d: refs? d = arg1 (1 def), d = (s16)d (def+use), then used in 2 divs → total maybe 4-5 refs.
s1ang: def, use in andi → 2 refs.

But mine gives d→s1 and s1ang→s0, meaning s1ang outranked d?! That seems odd. Maybe because d is live across the jal call and gets a lower priority (calls clobber caller-saved; callee-saved allocation). Hmm.

Actually in global-alloc, a variable live across a call must be callee-saved. Both are. Priority = refs/live-length. Hmm.

Maybe d is allocated to s1 because s0 is taken by s1ang first due to the ordering of allocation (s0 assigned to whichever qty comes first in the sorted list). And the sort might be by `n_refs` then by... Let me look at gcc 2.7.2 global.c / local-alloc.c for the ordering.

Alternatively, an easier lever: change when d is defined. If d = arg1 is moved later (after s1ang), maybe allocation changes. The comment says the keepalive anchors u5 before the (s16)d cast. Let me focus first on the register swap, then the scheduling.

Hmm, this is getting deep. Let me consider the C0505 catalog and the moves.md examples: "func_80184D28 | MATCH — keepalive replaced by return v0" and "func_801810F8 | MATCH: obase set right after pbase and used for the first load too (sched1 then keeps la before the store)". And "func_8014DD8C | WALL greg-pri-refs — each keepalive = +1 ref (var_s2 vs var_s3, arg0 vs arg2 priority); param copies + hoisted var_s3 reach 11 but sched1 reorders prologue".

So for register priority, adding refs to a variable helps. We could add a *use* of d that doesn't emit code? No, that's a keepalive (forbidden). Real C uses emit code.

Alternatively, reduce s1ang's priority: e.g., don't use a separate s1ang variable — compute u6 directly from the load? But then the load's target register might change.

Hmm, what if we change `s1ang` to be used more or less. Or declare it in a narrower scope.

Let me look at the target asm fully to understand the intended source. Let me dump it.

Let me use --keep with the header TU. It'll use includer 0. Let me run and objdump.

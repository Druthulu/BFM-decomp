---
ts: 2026-11-06T22:30:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7Dj60FJh722CYPjjZ5zV
---
r75 = s1ang (the loaded sign_extend value), and r77 = u6 = s1ang & 0xFFF. And r74 = d. So s1ang is split into two pseudos: r75 (the load, live across the call!) and r77 (the &0xFFF). Because the load happens before the ratan2 call and the value is used after the call, r75 is live across the call, making it block-local in block 0? Wait, r75 "2 refs across 7 insns in block 0" — actually it's live across the call and used in block 0 at insn 69.

Hmm, r75 is assigned $s0 by local-alloc because it's "block-local" (all refs in block 0) and it crosses a call so it needs a callee-saved reg. It takes $s0 (first free callee-saved).

Then r74 (d) conflicts 16 → gets 17. r77 (u6) prefers 16 (preference from the copy/and?) → gets 16.

So in w0: d=$s1, s1ang=$s0 (the r75 part), u6=$s0 (r77). Wait but the final asm showed `subu v1,a0,s1` where s1 was u6? Let me re-check: mine line 25: `subu a1,v1,s0`: iVar4 = u5 - u6; u6 in s0. Yes so u6=s0. And the cast `sra s1,v0,0x10`: d=s1. And r75 (s1ang raw) also s0 — it's dead after insn 69, so u6 can reuse s0. Good.

Target: d=s0, u6=s1, and r75 (s1ang raw) = ? In the target/pin version, r75 gets s1 (from pin table: r75 s1). So s1ang raw=s1, u6=s1, d=s0.

So the goal: d must get $s0, which requires r75 (s1ang raw, live across the call) to not take $s0. In the pinned version, d is hard-pinned $s0, so r75 goes to s1, then u6 prefers s1... and s1ang gets s1. 

Without pin, local-alloc gives r75 (block-local across a call) $s0 first, and global d can't have it.

How to make d get $s0 without a pin? Options:
1. Make s1ang (r75) not block-local-across-call, or make it not need a callee-saved reg, so it doesn't take $s0. E.g., move the s1ang load to after the ratan2 call → its live range no longer crosses the call, so local-alloc can give it a caller-saved reg ($v0/$a0/...). Then d could take $s0.

But moving the load after the call changes instruction order — the target has the load before the call (lw before ratan2 call). So that would break the match.

2. Make the load's value flow differently: keep the load before the call but make the pseudo global (not block-local) so global-alloc handles it. If s1ang is used across blocks, it's global. Currently r75 is only block 0. If we make the s1ang value live into another block, it becomes global. But it's dead after u6 = s1ang & 0xFFF... unless we move the &0xFFF computation into a later block or use s1ang later.

3. Reduce d's conflict: r74 conflicts 16 due to r75. If d's live range started after r75's end... d = arg1 at entry, used in div later. d is live across everything. Can't.

4. Give r77 (u6) different preference so it doesn't take s0? Doesn't matter; r74 still conflicts r75.

5. Make r75 global by using s1ang after the call in a second place? Hmm.

Actually, better: the target has s1ang raw in s1 (callee-saved), which is what local-alloc gives when s0 is taken. So we need $s0 reserved for d. Without a pin, the only way global-alloc gives d $s0 is if no local-alloc pseudo occupies s0 during d's live range.

Alternative: make d itself block-local? No, d is used in multiple blocks.

What if we make the divisor d be used such that local-alloc... no, local-alloc only handles block-local.

Alternative: make r75 (s1ang raw) global by moving the `u6 = s1ang & 0xFFF` into a separate basic block? E.g., compute u6 after the `if (u6 == u5) return 0;`? No, needed for the compare.

Hmm. What if s1ang raw is used twice: the load result used both for u6 and elsewhere after the call, making it global? But the target doesn't do that.

Wait — but maybe the target itself (the real compiled target) had s1ang raw in $s1 because of the pin. The pin reserves s0 from the start (a hard-reg variable live from entry?). Actually `register s32 d __asm__("$16")` creates a pseudo hard-assigned to $s0, live from its def to end. So local-alloc can't use $s0 for r75, and global sees $s0 occupied.

Lever-free, to get d in $s0 we need the same effect via real C. Options:

A. Make s1ang raw (r75) not cross a call. If the ratan2 call is moved after the s1ang use... but the target order is: load s1ang, then compute ratan2 args, call, then d cast, then u6. Actually the target asm order: let me look at the full target asm to know the exact order.

Let me dump the target asm. The build object disassembly is available somewhere; delever_search compares with build/. Let me use the diff output or objdump the object. Let me find the object.

Actually easier: dt.sh prints target lines in the diff. But only differing lines. Let me get the target function's full asm from the build object.

Let me find the object file for func_8012B8E4. Probably build/... Let me grep.

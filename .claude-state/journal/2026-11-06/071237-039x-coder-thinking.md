---
ts: 2026-11-06T14:12:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zQ5kLL6cLD0S5LMFph5O
---
Tie-break by allocno number (lower first), which follows pseudo regno order = declaration order. So if priorities are exactly tied, declaration order decides. But i and dst priorities likely differ by live_length.

OK let me just get empirical numbers. Set up scratch TU dump for c1.

Actually, maybe I don't need c1; let me compute live_length from the target dump. But live_length is in the .greg dump (global-alloc dump) or .flow. Let me check the .flow or .greg dump for the register info: it prints "Register N used M times across K insns" — the K is the live span? In the lreg dump, "Register 160 used 14 times across 41 insns" — that's reg_live_length maybe (41 insns). And 162: "used 11 times across 37 insns". Hmm, but i lives from block 3 to 17, which is more than 41 insns? The function has ~240 insns but i is only live in part.

Actually flow.c prints: "Register %d used %d times across %d insns; ..." where the second is reg_live_length. So with asm: i n_refs=14, live_length=41; dst n_refs=11, live_length=37. Priority i = floor_log2(14)*14/41 = 3*14/41=1.024. dst = 3*11/37=0.892. So i wins. 

Without asm: i n_refs=14-? Let me compute what the asm adds. Each asm reg occurrence adds loop_depth refs. The i asm is in block 14 (do-while body, loop depth 2?). If loop_depth=2, +2 refs -> i=12. The src asm in block 14? No, src asm at insn 312 is in block 3? Block 3 is first insn 36 last 161 — that's the whole setup. Hmm, insn 312 is in block 14? Block 14 first 325. No, insn 312 < 325. Which block has insn 312? Blocks: 3 (36-161), 4 (163-166), 5 (170-190), 6 (192-217), 7 (220-228), 8 (232-234), 9 (246-268), 10 (270-444), 11, 12 (283-291), 13 (296-321), 14 (325-379). So insn 312 is in block 13 (296-321). Block 13 is the setup before the loop (n=..., i=0, src=..., asm src, dst=...). Loop depth there? Block 13 is inside the outer while (depth 1), so the src asm adds +1 ref. Hmm but the comment said +2.

Wait, insn 312's asm is the src one. And insn 329 is the i one, in block 14 (the do-while body, depth 2), so +2. So:
- src: 15 refs with asm -> 14 without (if +1).
- i: 14 with asm -> 12 without (if +2).

Hmm, then without asm: i=12, live 41; dst=11, live 37. Priority i = 3*12/41 = 0.878; dst = 3*11/37 = 0.892. dst slightly wins -> dst gets t2. That matches the observed c1 result! Great, the model fits.

So I need i priority > dst priority: floor_log2(i_refs)*i_refs/41 > 3*11/37 = 0.8919.
- With i_refs=12: 3*12/41=0.878 < 0.892.
- With i_refs=13: floor_log2(13)=3, 3*13/41=0.951 > 0.892. 

So adding just ONE real ref to i (making 13) would flip it! And the ref must be weighted appropriately.

But careful: live_length might also change if I add a use. Adding a use of i inside the loop doesn't extend live_length (already spans the loop). Adding a use outside could extend it.

How to add exactly one real ref to i in the loop without emitting new code? The ref count comes from RTL occurrences weighted by loop depth. If I add a use of i inside the do-while, it adds 2 refs (loop depth 2). That would make i=14, priority 3*14/41=1.024 > 0.892. 

But the use must not emit an instruction. A dead use gets deleted by flow/dead-code elimination. Unless the use is part of an existing instruction.

Hmm — could I write the condition as `while (i < n)` but ALSO use i in the loop body in a way that folds into existing code? 

Idea: replace `dst` with `dst` computed from `src` and `i` in a way that reuses an existing instruction. E.g., the target has `addu $11,$9,$2` (dst = src + n*2). If I instead write the store as `*(u16 *)((u8 *)src + i * 2 + n * 2)`... no.

Idea: change the loop to use `i` as the offset for the load: `px = src[i]`? That would emit `sll` + `addu` each iteration — extra instructions. But wait — what if `src` is also indexed? No.

Hmm, what about this: the target loop increments both dst and src by 2 and i by 1. What if I express the increments differently, e.g., `src = dst - n` ... no.

Let me think about "real C" moves that add a reference to i without adding an instruction:
1. `i++` -> the RTL `(set reg160 (plus reg160 1))` has reg160 appearing twice in one insn? REG_N_REFS counts occurrences? In flow.c, `mark_regs_live_at_end`/`propagate`... Let me check how refs are counted: line 2067 `reg_n_refs[regno] += loop_depth;` inside a loop over SET_SRC/... Let me read around 2050-2075.

---
ts: 2026-11-06T08:42:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_53eSupvM0V1Z91KJj6IJ
---
pri = floor_log2(refs) * refs * size / (death - birth) * 10000, where size = qty_size (number of regs in the pseudo, usually 1; but for multiword it's more).

w1: r72 refs 5, size 1, death-birth 27 → 2*5*1/27 = 3703. r77 refs 2, size 1, death-birth 5 → 1*2/5 = 4000. Tie-break: lower qty number first (qsort leaves nothing to chance, sorted by qty number ascending on ties). So order: 4000s first: 75,76,77 (ascending), then 72.

w2: r72 refs 5, death-birth 30 → 3333; r77 refs 3, size 1, death-birth 18 → floor_log2(3)=1, 1*3/18 = 1666. So r72 before r77: r72 gets a2 (the first free after v0,v1,a0,a1) and r77 gets a3.

So target needs r72's pri > the competing pseudo's pri that would otherwise take a2.

Options:
1. Shorten r72's live range (death-birth) to ≤ 24 → 2*5/24 = 4166 > 4000. How? death is the last use; birth is the def. The def is the param copy at insn 4. Can't shorten.
   - Unless refs increase: refs 6 → 4444 with live 27. Still < 5000 but > 4000. A 6th use!
2. Add another real pseudo with pri between 4000 and 3703? impossible (needs > 3703 and < 4000).
3. Lower t3's pri below 3703 by increasing its death-birth. Needs ≥ 6 → 3333. 

So either a 6th ref on r72, or t3's span 6.

A 6th ref on the a0 copy without an extra instruction: is there a C expression that makes gcc use the a0 copy twice in one insn? For instance, `h[0] = h[0] + ((Unkstruct*)a0)->unk6;` uses a0 once. If we write `((Unkstruct*)a0)->unk6` for h[0] and `((Unkstruct*)a0)->unkE` for h[2]... already counted.

What about `func_8012C51C(sp10, (s32)a0)` — one use. If we write `func_8012C51C((s32*)sp10, (s32)((Unkstruct*)a0))` — still one use.

Hmm: what if the call's second arg is `(s32)a0 + 0`? combine folds to same, refs +? The pseudo appears twice in the RTL but cse/combine may reduce.

What about using the a0 copy as the address of sp10? no.

Maybe the trick is to change t3's live span. death-birth = 5 counts insns from def to death inclusive? Let's verify with t0: r74 refs 2, death-birth 10 (lw at 24, sw at 42; insns 24,29,34,39,42 = 5... hmm that's 5 not 10). Wait r74 = t0: lw at insn 24, store at 42. Insns between: 24,29,34,39,42 = 5. But table says live 10. Hmm, so "across 10 insns" is not insn count; it's maybe (death - birth) in insn UIDs? insn numbers 24→42, difference 18; no.

Let me recompute: pri r74 = 2000. refs 2 → floor_log2=1, 1*2/size?/live. If live=10: 2/10 = 2000. Yes. So death-birth = 10. What is 10 here? Maybe death and birth are "insn sequence numbers" not insn uids: sched1 assigns sequence numbers to insns; the lreg dump prints "across N insns" using `REG_N_LIVE_LENGTH`? In gcc 2.7.2, `reg_n_info[].live_length` is set in flow.c: `REG_LIVE_LENGTH (i) = ...` computed as the number of instructions between birth and death (counted in insn uid? no, in `insn_number`). flow.c's `flow_analysis`/`find_basic_blocks` computes live_length as the difference of insn numbers: `REG_LIVE_LENGTH (reg) = ...` Let me check: in flow.c `allocate_for_propagate`? Actually `reg_live_length` is computed in `life_analysis`: for each block, uses `REG_LIVE_LENGTH (i) = ...`. Hmm.

The alloc table says r74 "used 2 times across 10 insns" (w1 lreg line). The number 10 likely = insn_number(death) - insn_number(birth), where insn_number counts all insns including notes! Notes are insns too. Between insn 24 and 42: notes at 29? no. Hmm insn uids are 24 and 42 → difference 18.

Let me check flow.c's live_length computation.

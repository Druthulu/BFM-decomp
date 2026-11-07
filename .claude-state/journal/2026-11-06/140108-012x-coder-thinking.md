---
ts: 2026-11-06T21:01:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pr9QOYZmvUDX91AmRs1a
---
So priority = floor_log2(n_refs)*n_refs*size / live_length, higher first. The first allocated gets the first free reg. What's the reg order for GENERAL_REGS in the MIPS? Likely $2,$3,$4,...? Let's check the machine description. Actually for the block, free regs exclude those live at block start. v0/v1 both free.

In the block: the load pseudo (u16, size 2), 1 ref, live length maybe 2-3. The sub pseudo (s32, size 4), 2-3 refs, live length maybe 5. Priority: sub higher → allocated first → gets first free reg. Which is v0 presumably. But mine gives sub v1. Hmm. Unless the copy-sugg pass ties the load pseudo to v0 first (sugg pass allocates copy suggestions before the priority pass). In the sugg pass, the load pseudo could be suggested to v0 because of the addiu's matching constraint? `addiu` is `=r,r` maybe with 'I' immediate — the constraint might allow matching. Hmm.

Wait, the sugg pass: `qty_phys_copy_sugg` comes from `combine_regs` with `may_save_copy` = move insn (SET_DEST == r0 && SET_SRC == r1). For `lhu` (zero-extend load) the destination and source (mem) aren't both regs, so no copy sugg. But then the sub `addiu v1,v0,-256`: dest pseudo (sub result), src load pseudo — both regs! Is this a "move"? No, it's an add with an immediate; SET_SRC is PLUS not a REG. So may_save_copy false. But `win = combine_regs(r1, r0, 0, ...)` ties them anyway (a non-copy suggestion): "qty_phys_sugg". So load and sub are combined into one qty? combine_regs merges the two regs into one qty if their live ranges don't conflict... Actually combine_regs combines REGs that can share a register: it makes them equivalent in a qty. If they're combined, they'd get the same register! But in mine they don't share.

combine_regs only combines if the death of r1 is at this insn (or no conflict). The load dies at the addiu, so they can combine → same reg. That would give them the same register. In mine, they didn't combine... because the load also has another use? Let me look at my generated code again: `lhu v0,88(s0); nop; addiu v1,v0,-256; sll v0,v1,0x10; sh v1,88(s0); bgez v0`. Hmm wait, the `sll v0,v1` — v0 is the destination of sll, and it's the same v0 as the load. So the load's pseudo got v0 and was reused for the sll result. That means combine_regs tied the load to the *sll* output rather than the addiu output! Because `sll v0,v1,0x10` — dest v0, src v1 (the sub) — no. Hmm, the sll output v0 is a new pseudo; why would it share with the load? Because after the load dies at addiu, local-alloc can reuse v0 for the sll output (register reuse by find_free_reg since load died).

Actually, the sll pseudo (the `(t<<16)` value) is a new pseudo that is born after the load dies; find_free_reg gives it v0 (first free). And the sub gets v1 because it was allocated first? No wait — if the sub had higher priority it would get v0, and the sll would get v1.

Hmm, unless the sll pseudo has higher priority than the sub. Let's compute: sub: refs = 2 (sll, sh), size 4, live length ~5. sll: refs 1 (bgez), size 4, live 2. sub pri = floor_log2(2)*2*4/5 = 1*8/5=1.6→16000. sll pri = 0*... = 0 (floor_log2(1)=0). So sll pri 0. Sub 16000 > 0. So sub should be allocated first and get the first free reg.

Then what's the first free register? Maybe not v0! In the block, `s0` is live (a0 copied to s0 — actually s0 is a fixed hard reg live at block start), `s1` live. ra? The block start live set includes s0, s1, ra (saved). v0 and v1 are free. The register order in GENERAL_REGS for MIPS... let me check the md file: `#define REG_ALLOC_ORDER` or the `regs` order in `find_free_reg` uses `reg_class_contents[class]` scanned from 0 upward, so $0,$1,...,$31. $0 is fixed, $1 is... at = $1 is in GENERAL_REGS? In the MIPS md, GENERAL_REGS likely includes all integer regs except $0? Order by register number: $1 (at) comes before $2 (v0)! Hmm, but $1 (at) is reserved/fixed? In GCC MIPS, $1 is `fixed_regs`? Typically `$1` is not used by the compiler (fixed). And $2, $3...

So first free could be v0 ($2), then v1 ($3). Fine.

But wait — maybe the block also contains the pseudo for the *store address* etc. Not relevant.

So the sub should get v0. But it got v1. Unless the sll pseudo's `qty_size` is bigger... size for sll output is 4 (SImode), n_refs 1 → floor_log2(1)=0 → priority 0. No.

Hmm, but `floor_log2 (qty_n_refs) * qty_n_refs` for n_refs=1 is 0. So sub priority 16000. It should be first.

Unless the load and sub ARE combined by combine_regs (sugg), and the combined qty gets a suggested register from... the tie's copy suggestion. If combined, they'd share a register. They don't in my output (load v0, sub v1). So not combined.

Wait, maybe I misread the assembly: `addiu v1,v0,-256` — could v0 be the load and v1 the sub. Yes.

Hmm, so why v1? Perhaps because at the point of allocation, v0 is live at block start! Is v0 live at block start? The block is the `if` body; before it, `lhu v0,28(s0); slti v0,v0,8; beqz v0` — v0 is used in the branch and dies at the beqz. So not live after.

Hmm, but wait: which basic block? `if (...) { block1 }` then `block2`, etc. Actually the `if` contains three sub-blocks. Block1: the 0x58 update. v0 dies at beqz. So v0 free.

Let me reconsider: maybe the first free register is not v0. Let's check the actual register order in the MIPS machine description. In GCC 2.7.2 mips.md: 
```
#define REG_ALLOC_ORDER ...
```
Actually let me grep. But easier: in mine, v0 got used by the load (the load pseudo is likely allocated in the sugg pass or it's the first free). The load's priority: refs 1 → 0. It got v0 anyway because at its allocation time v0 was free and the higher-priority qtys were allocated elsewhere... no, higher priority first would take v0.

Unless the priority ordering is reversed! `qty_compare` returns `pri2 - pri1`; qsort ascending by this comparator → descending priority. Then the allocation loop goes i=0..next_qty-1, so the highest priority is allocated FIRST → gets the lowest-numbered free reg. Hmm.

But wait: in the *small case* (next_qty == 2), the code does `if (qty_compare(0,1) > 0) EXCHANGE(0,1)` — puts the best in qty_order[0]. OK.

Hmm, so the highest priority gets v0. So the sub should have v0.

Unless... the load and sub are combined into a single qty by combine_regs, AND the sll also? If load+sub are combined, they'd both be one qty → same register. Not what we see.

OK, let me stop theorizing and get the actual dump. Let me use the cc1 dump tools to see the pre-alloc RTL. The brief says tools/cc1_dumps_tu.sh + tools/alloc_table.py (TU dumps). Dumps must go under my item dir and be deleted. Let me check tools/alloc_table.py --help and cc1_dumps_tu.sh.

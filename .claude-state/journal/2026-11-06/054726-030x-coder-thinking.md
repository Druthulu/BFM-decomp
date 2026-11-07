---
ts: 2026-11-06T12:47:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3g6QJNmNWEmjdK3gVntr
---
Only difference: the offsets in the loads. Target loads all at `0(at)`, mine at 0,4,8,12,16(at). So the target's block move recomputes the base for each word from v0 (lui+addu each time, offset 0), mine uses one base + offsets.

This is the classic difference: target's block move has each load as a separate symbol+offset... Actually target: `lui at,0x0; addu at,at,v0; lw v1,0(at)` five times. The reloc is on the lui (`lui at,%hi(sym)`) and the addu adds v0. So each load's address = sym_hi + v0 + 0. Mine: first at 0, then 4,8,12,16 — because gcc used a single base register and offsets.

This suggests the target's block move was emitted with 5 *separate* address expressions (each `D_801AFBD8[i]`, `D_801AFBDC[i]`, ...), i.e. 5 separate loads where each address is computed independently from symbol + v0. Since the symbol base is the same, offset would be 0 for the first, 4 for the second... unless the offsets are folded into the *symbol* differently: D_801AFBDC is a distinct symbol in the target? No — objdump relocs are masked. In the target, `lui at,0x0` with a reloc; if the symbol were D_801AFBDC the reloc operand differs but masked_diff masks reloc operands... hmm, "relocation-masked with reloc-operand equality" — actually it compares reloc operand equality? Let me not worry: both show 0x0 in the dump.

Actually the key: mine computes offsets 4,8,12,16 from one base; target recomputes from v0 each time with offset 0. That means in the target source, each load is `D_801AFBDC[a1*5]` etc. — i.e. five separate array reads at the SAME index, where each symbol is a distinct extern. Then each address = symbol + v0. Since D_801AFBDC is a distinct symbol (not D_801AFBD8+4), the offset stays 0.

But wait — then how did the fifth load end up with a nop and a single movstrsi template? Hmm, if it's five separate scalar loads, the nop after the fifth lw would be a load-delay nop that sched can't fill... but we saw sched fills it in w0 (the scalar version) with lhu.

Unless: the fifth `lw v1,0(at)` at 94a8 followed by nop at 94ac — in target. In w0 (scalar), mine put lhu at that slot. Hmm.

So how does target get the nop? Because the barrier is there in orig! The orig with barrier scores 0. So target = orig with barrier. The whole point: we must reproduce this without the barrier.

Two problems to solve:
1. the offset 0 vs 4/8/12/16 (i.e., 5 separate symbol-based loads vs one base + offsets).
2. the nop.

With the struct-copy I solved the nop (inside template) but got offsets 4..16. To get offsets 0 for all five, I need the source struct to have 5 fields each with a distinct... no.

Alternative: keep 5 scalar loads from 5 distinct symbols (as orig does) — that gives offset 0 each — and find a real-C way to produce the nop.

Wait, in w0 (barrier removed, scalar loads) the instruction listing showed: `lw v1,0(at)` at 24 then `lhu v0,16(sp)` at 25. Let me check the offsets in w0's loads: from the earlier diff only 3 lines differed, so w0 has all loads at 0(at) and matches except the nop/order. Good — so scalar version gives the right offsets.

So problem: only the nop+order. Target: lw; nop; sw; lhu; lhu; nop; addu. Mine (w0): lw; lhu; sw; lhu; nop; addu.

Hmm wait, mine in w0: 
24 lw v1,0(at)
25 lhu v0,16(sp)
26 sw v1,32(sp)
27 lhu v1,6(a2)
28 nop
29 addu

Target:
24 lw v1,0(at)
25 nop
26 sw v1,32(sp)
27 lhu v0,16(sp)
28 lhu v1,6(a2)
29 nop
30 addu

So sched1 moved the lhu above the sw. If instead the sw came immediately after the lw with a dependency... The sw depends on the lw (v1). The lhu doesn't depend on the sw. sched fills the load delay slot with an independent insn. Target has nop → scheduler didn't fill, because in the orig the barrier blocked movement.

How to make the lhu not schedulable into that slot with plain C?
- Make the lhu depend on the sw's value? The lhu reads sp10[0] (16(sp)); the sw writes 32(sp). If I make the sw's *source* be something the lhu produces... no.
- Make the lhu depend on v1 (the loaded t)? If the first RMW reads a value that somehow depends on t, then it can't be hoisted above the lw's delay slot... but then it would be after the sw anyway. Actually we need: lhu v0,16(sp) must come after sw v1,32(sp) AND not fill the delay slot.

Hmm: if lhu depended on the lw result (v1), sched would put it after lw... and could still fill the slot? No — a load can't fill the delay slot of another load if it depends on it (the result isn't available). Actually the delay slot of a load: you can put anything there EXCEPT an insn that uses the loaded register. A dependent insn cannot go in the slot, so the nop remains. But then after the nop, the sw v1 (which also depends on v1) comes... 

Wait but the order is lw, nop, sw, lhu. The sw uses v1 (the load result) and is placed after the nop. So sched placed sw immediately after the delay slot. If lhu also used v1, it couldn't fill the slot either; then sched would place... hmm, which one first? sw or lhu.

Hmm, how to make lhu v0,16(sp) depend on t without changing the result? `((u16*)sp10)[0] + (t & 0)` — that's an identity launder, forbidden.

Alternative: maybe the nop can be produced by the block-move template while keeping the five *distinct symbol* loads. What if the block move source is a struct whose five words are at distinct symbol addresses? Not possible with a struct.

Hmm, but wait: maybe the target's block move is not from a struct but the original source is 5 scalar loads and the barrier. Since orig scores 0, that IS the current representation. So to be lever-free we need another route.

Alternative route: make the fifth word's load/store a block move by itself? A 4-byte block move wouldn't produce a nop.

Another route: `do { sp10[4] = t; } while (0)` — no effect on scheduling (single insn).

What about making `t` load and `sp10[4]` store part of a struct assignment of ONE word? No nop.

Hmm, think about sched1's behavior more carefully. sched.c builds dependence edges. It schedules backward from the end of the block. The load-delay slot filling: sched has `maybe_bb`... Actually in GCC 2.7.2, the delay slot filling is done by sched1 (it models the delay). The rule: an insn can be placed in the delay slot of a load if it doesn't reference the loaded register.

The target's nop exists because the barrier split the BB into two EBBs: sched ran on the first EBB ending with the asm; the last insn of the first EBB is the `sw v1,32(sp)`? Hmm no: barrier is after `sp10[4] = t`, so EBB1 ends with sw v1,32(sp); EBB2 starts at lhu. So the load and store are in the same EBB; the scheduler within EBB1 has lw, then sw (dependent) → must leave a nop. Then EBB2 starts fresh.

So we need: the lhu to be in a different EBB than the lw/sw, AND the EBB1's schedule leaves a nop.

How do you split an EBB in plain C without an asm barrier? C0535: do{}while(0) splits cse1 EBB — that's for cse, not sched. Does sched1 use EBBs (extended basic blocks) that end at labels/jumps? sched1 in 2.7.2 schedules each basic block. A `do{}while(0)` compiles to a branch that is removed... Hmm.

Actually C0535 says do{}while(0) splits cse1's EBB (cse.c uses extended BBs where a label splits). Not sched.

Let me think differently. What if the *order* in source makes sched produce the target? In mine, sched filled the delay slot with lhu. If the lhu were not yet available (i.e., its input not ready) at that point... The lhu reads sp10[0] which was stored at insn 18. It's ready.

What if I reorder the source so that sp10[0]'s store happens later? But target has stores at 18-21.

Alternative: make the first RMW a read-modify-write of sp10[0] where the "read" happens... hmm.

OK, let me consider: maybe the answer is to make the fifth load part of a 20-byte block move AND get the offsets right. Mine gives offsets 4,8,12,16 — 5 words from one base. Target has 5 loads each at 0(at) with a fresh lui+addu. If the struct copy source were... hmm, what if the struct type has 5 fields but I write the copy as 5 separate loads? Then no template.

Wait — actually maybe I should check: are the target's five `lui at` relocs distinct symbols? If masked_diff masks the reloc *operand* (symbol name), then target could have lui/addu/lw 0 for each of D_801AFBD8..E8 (5 distinct symbols) — and mine's offsets 4..16 come from one symbol. The diff shows those as different words (0x8c240004 vs 0x8c240000), so yes.

So: to get offset 0 five times, the loads must come from five distinct symbols. To get the nop, need the block-move template. Contradiction? Unless the block move reads from a struct that is *composed* of... no.

Hmm, unless: what if the fifth word is a block move of 20 bytes from a struct at D_801AFBD8 but the struct is declared with a base symbol that is... no.

Let me reconsider: maybe target's 5 loads at 0(at) with lui each time is what gcc emits for a 20-byte struct copy when the source is 5 separate symbols? No.

Alternatively, maybe target's block move source is `(Rec5*)((u8*)D_801AFBD8 + idx)` — no, same base.

Wait. What if the target's source for the block move is a 5-element struct array indexed by a1*5... e.g. `struct { s32 v[5]; } *tab = ...` Hmm.

Let me test what actually generates lui/addu/lw 0 five times: a 20-byte copy from a *symbol with unknown alignment*? The address computation `lui at,%hi(D_801AFBD8)` then `addu at,at,v0` then `lw 0(at)` — that's the standard "symbol + register" addressing, which gcc uses when it can't use a 16-bit offset (because the base is a symbol in the middle of the 32-bit space, so it loads hi and adds). It's used per-access when the address is `symbol + var`. If the same address is used 5 times with offsets, gcc would compute the base once (in a register) and use offsets — that's what mine did. But gcc computed lui+addu *each time* in mine too (5 times!), just with offsets 4..16. Interesting: mine repeats lui+addu per load but with different offsets. That's move_by_pieces: for each piece it emits a load with an address expression `base + offset`, each expanded independently → lui+addu+lw off(at).

So the difference is only the offsets, i.e. whether the source is one symbol (offsets 4,8,...) or 5 distinct symbols (all 0). Since target has all-0 offsets, the target's block move source must be a 20-byte object whose 5 words each come from a distinct symbol... impossible for a struct copy.

Hold on. Maybe target is NOT a block move. Maybe target is 5 separate scalar loads from 5 distinct symbols, and the nop comes from something else. Let me test: what if I write the 5 scalar loads but store them into sp10 via `*(s32*)...`? That's what orig does and it gave w0 = score 3 with only the nop difference. So orig's shape gives correct offsets (0 each). Good.

So the only problem is the nop. Let me think about how to force the scheduler to not fill that delay slot with the lhu.

In sched.c, the delay-slot filling happens as part of scheduling: the scheduler is free to place any ready insn after the load. To prevent the lhu from being scheduled there, it must have a dependence on something in between or not be ready.

What if the first RMW's load (lhu v0,16(sp)) has a *memory dependence* on the sw v1,32(sp)? Both access sp. In GCC, alias analysis: sp10 is a local array; the store to sp10[4] and the load of sp10[0] are both "in a symbol" (stack slot). If one is MEM_IN_STRUCT (or varying) and the other not, the dependence might be kept. Hmm, in orig they're the same object.

Alternatively — the anti-dependence: `((u16*)sp10)[0] = ((u16*)sp10)[0] + ...` is a read-modify-write. If instead I write `sp10[0] += ...` no.

New idea: the lhu is the FIRST insn of the second EBB in the target. What creates an EBB boundary in plain C? cse's EBB = a basic block plus its successors while they have a single predecessor... Labels split EBBs. A `goto`/label in C creates a label → splits EBB for cse (that's C0535: do-while creates a label that splits cse's EBB). But sched1 in 2.7.2 — does it use basic blocks (one per label) or EBBs? sched.c: `schedule_block` per basic block, and it computes `large_region`... Actually 2.7.2 sched.c builds "extended basic blocks" (EBB) — there's `sched_analyze` and `compute_dominators`... Let me check the reference source: tools/reference/gcc-2.7.2/sched.c. Let me grep for EBB.

Actually, the movables: the barrier is an ASM_INPUT_VOLATILE with memory clobber. In sched.c, `sched_analyze_insn` treats a volatile asm as a barrier for memory (sets `sched_mem_barrier`?) Let me look.

Let me grep sched.c for asm handling.

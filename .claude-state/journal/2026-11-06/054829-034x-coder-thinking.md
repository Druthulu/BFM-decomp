---
ts: 2026-11-06T12:48:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NpPaIssWQbuN3PPSUdid
---
Where does the `nop` insn come from? In 2.7.2 mips, there's `#define TARGET_SCHED_...`? Let me grep mips.h for "DELAY" and "TARGET_SCHED".

Actually maybe the mechanism: `define_delay` for loads? mips.md line 121 says can't describe load delays. Then the nop after a load is emitted by the *scheduler* as an actual `nop` insn because of a dependence edge: sched.c may add an artificial edge from a load to the next insn? Hmm no.

Alternative: the nop is emitted at assembly output time by `mips_final_prescan_insn`? It only emits comments. Hmm, but the object has a real nop (0x00000000). The assembler with `.set noreorder`? The output uses `#nop` comments? No, `#` in mips asm starts a comment... and `'#' Print nop if in a .set noreorder section` at line 3556. Hmm, in mips_asm it prints "\n\tnop" if in noreorder.

OK, let me step back: empirically, sched1 fills or leaves the slot, and the difference matters. Rather than reverse-engineer, use the empirical lever ladder.

Key insight from walls: "dbr-delay-fill — reorg steals ..." etc. For this item the wall would be "sched1 fills a load-delay slot the target leaves as nop" = wall tag `sched1-load-delay-fill` (already in walls.txt, from G18 func_80180610).

But maybe a real-C move works. Let me think about what makes the lhu not schedulable into the slot:

Option A: give the lhu a dependence on the fifth load. In target, lhu v0,16(sp) reads sp10[0], and sp10[0] was stored from x. If x were derived from t... no.

Option B: make the fifth store (`sp10[4] = t`) a *memory* the lhu must order after — i.e., same object with alias analysis forcing an order. sched's dependence: store to sp10[4] (32(sp)) vs load from sp10[0] (16(sp)). Both MEM in the same symbol (sp10) but different offsets — sched's alias check `true_dependence` uses alias sets; for a stack slot, two different offsets are different alias sets (each scalar is its own alias set), so no edge. If sp10 were accessed as an *array with variable index* (varying), then a store to a varying address vs load at varying address → anti/true dependence kept! That's the "in_struct/varying" lattice the src comments talk about (§37 /s-DEP).

So: if the load of sp10[0] and the store to sp10[4] are both MEM_VARYING (i.e., through a pointer with unknown offset), sched would keep them ordered. But in the target, is there an ordering edge? Yes! The target has sw v1,32(sp) BEFORE lhu v0,16(sp). So the source order is preserved by some dependence. With plain C the sched moved lhu before sw (filling the slot) → no dependence in the compiler's view. To create one: make the store's address and the load's address alias-ambiguous.

Idea: access sp10 through a `s32 *p` pointer for the store: `p[4] = t;` where p = sp10. Then p[4] is varying? No, p[4] with constant index is still fixed offset, but through a pointer — gcc knows p points to sp10 (it's a local), and the offsets differ, so still no alias.

Use a variable index: `sp10[4] = t` → if I write `*(s32*)((u8*)sp10 + k)` with k = 16... that's an identity launder, forbidden.

Hmm. What about using the RMW itself to carry the dependence: `((u16*)sp10)[0] = ((u16*)sp10)[0] + ...` — a load and store to the same address. The store to sp10[4] (32(sp)) comes before the lhu (16(sp)). If instead the RMW's load were of sp10[4]... no.

Option C: Reorder source so that the fifth load/store comes AFTER the first RMW. No — target order is fixed.

Option D: Make the fifth store's value come from a load that sched can't move the lhu above because of the load's own delay... no.

Option E: Make the lhu *not ready*: its address depends on something computed after. Its address is sp+16 (constant). Hmm.

Option F: Make the lhu not exist as a separate insn: the RMW `((u16*)sp10)[0] = ((u16*)sp10)[0] + ((Unk*)obj)->unk6` compiles to lhu v0,16(sp); lhu v1,6(a2); addu; sh. What if the first lhu were replaced by a use of the *original x value*? No, that changes the code... well, it's semantically the same but the target has a lhu.

Option G: Use a union/struct so the whole 20-byte block is copied and the RMW reads through the struct → then offsets 4..16 problem returns. Unless... hmm, but what if the block move is from 5 *distinct symbols*? 

Wait! Maybe I'm wrong that target's block is a struct copy. Let me reconsider: maybe target's 5 loads at 0(at) with a lui+addu each is just what gcc emits for `sp10[0]=D_801AFBD8[i]; sp10[1]=D_801AFBDC[i]; ...` where each D_xxx is a separate symbol. That's orig's shape. And the nop is due to the barrier. So target = orig.

So the question is purely: how to make sched1 leave the nop with plain C. 

Let me look at what sched1 actually does here. sched1 schedules backward, building the block. It fills the load delay slot if it can. To leave a nop, the next insn (in final order) must depend on the load, or no other insn is ready.

Order in source: lw t; sw sp10[4]; lhu sp10[0]; lhu obj->unk6; addu; sh.

In target: lw; nop; sw; lhu; lhu; nop; addu.
Interesting: there's another nop at 29 (after lhu v1,6(a2) at 28, before addu at 30). That second nop is a load-delay nop for the `lhu v1,6(a2)` load, which sched could not fill because addu uses v1 and the next insn (lhu v0,16(sp) at 27) is before. Wait order: 27 lhu v0,16(sp); 28 lhu v1,6(a2); 29 nop; 30 addu v0,v0,v1. Yes, addu depends on both; nothing else available → nop. Mine also has that nop at 28.

So in mine, sched moved lhu v0,16(sp) to 25 (the slot) and sw to 26. Then 27 lhu v1,6(a2), 28 nop, 29 addu.

For target, sched placed sw at 26 (after the slot). Why would sched prefer sw before lhu? Because in the target's block, the barrier forces lhu to stay after it, and sw is before the barrier. So the order is forced.

Plain C: sched picks based on priority. Both sw and lhu are ready at that point. The scheduler's priority favors... in mine it picked lhu into the slot. If lhu had a dependence on the sw, sched would be forced to put sw first, and then the lhu would come after — and the slot would remain nop (since lhu depends on sw which is not yet... wait, if lhu depends on sw, then lhu must be after sw, so the slot can't be filled by lhu; nothing else → nop). That gives exactly the target!

So: create a dependence between the store to sp10[4] and the load of sp10[0]. How, in plain C, without changing semantics? Make them the same memory object in a way the compiler must consider aliasing. E.g., make sp10 a union? Or read sp10[0] through a pointer that could alias sp10[4].

Real C: 
```
s32 *q = sp10;
...
sp10[4] = t;
((u16 *)q)[0] = ((u16 *)q)[0] + ...;
```
gcc still knows q == sp10 exactly.

What about using the *obj* pointer to alias? No.

Different approach: make the fifth store depend on the load of sp10[0]? i.e. reorder the RMW's parts:
Actually here's a thought: the RMW reads sp10[0] and writes sp10[0]. The store to sp10[4] is in between. If the compiler treats the array as an aggregate whose stores/loads are all "varying" (MEM_VARYING), then all accesses to sp10 alias each other → order preserved.

How to make sp10 accesses varying? In GCC, a MEM is marked varying when the address isn't a constant offset from a base... Actually `MEM_VARYING` means "the address is not fixed" — set by `mark_reg_pointer`? In sched.c, `true_dependence`/`anti_dependence` take `varying` flags. For stack slots, each is fixed.

If sp10 were accessed via a pointer whose base is a register that is not known to be sp... e.g., `s32 *p = sp10;` — gcc knows p = &sp10[0], so p[4] is fixed offset.

Hmm, but what if the pointer comes from a *parameter*? Like passing sp10 to a helper? No.

What if I use the obj pointer arithmetic: `*(s32 *)((u8 *)sp10 + 0x10)`? gcc folds it → same as sp10[4].

OK alternative approach: avoid the sched problem entirely by making the fifth load+store a movstrsi template, but keep offsets 0 by... hmm, what if the struct copy source is a struct with 5 fields but declared as a *union with the 5 externs*? no.

Hmm wait. Let me reconsider the offsets. In mine (struct copy), the 5 loads are `lw 0,4,8,12,16(at)`. Target has all 0. What if the struct type has 5 fields but the copy is done as 5 separate struct-typed assignments each of 4 bytes? no template.

What if I make the source a 20-byte struct located at D_801AFBD8 but each field accessed... no.

Actually — what if the target's five loads at 0(at) are a *block move* where the address expression is `symbol + reg` and gcc's move_by_pieces emits the address for each piece as `XEXP(addr,0)` recomputed... In move_by_pieces, each piece's address is `copy_addr` computed by plus_constant on the original address. If the original address is `(symbol_ref) + v0` (a PLUS with a register), then plus_constant adds to the register part? No, it adds to the constant part: `(plus (symbol_ref) (reg))` + 4 → `(plus (symbol_ref) (plus (reg) 4))`? Hmm, plus_constant on `(plus sym reg)` with 4 gives `(plus (plus sym 4) reg)`? Actually plus_constant distributes into the last operand... it would produce symbol+4+reg, which then can't be a lui/addu with offset 0 — it'd be lui hi(sym+4), addu, lw 0(at). That's exactly all-zeros offsets! Because each piece's address is a *symbol at a different offset* → the hi/lo split gives `lui at,%hi(sym+4)` then `addu at,at,v0` then `lw 0(at)`.

Hmm! But mine produced offsets 4,8,... which means gcc used the same base and put the offset in the lw's 16-bit field. That happens when the address is `(plus (reg) (const))` where reg holds the symbol base — i.e., gcc loaded the symbol base into a register once (via lui/addu with v0) and then used offsets. In mine, the address is `sym + v0` where v0 is the index... gcc's address generation: it computed `at = hi(sym) + v0` then `lw off(at)`. For offsets it used 4,8,... So it kept the base in `at` per piece.

In target all are 0 with a separate lui each. That means each piece's address is a different symbol_ref (D_801AFBD8, D_801AFBDC, ...) plus the same v0 register → lui %hi(each sym); addu; lw 0. That's 5 DISTINCT symbols.

So the target is definitely 5 distinct extern symbols with 5 scalar loads (orig's shape). Which brings us back: target = orig shape; we only need the nop.

So the struct-copy route is a dead end for offsets (unless a struct of 5 externs... impossible).

OK so let's focus: how to force the order sw(sp10[4]) before lhu(sp10[0]) in plain C, or equivalently prevent the lhu from filling the load's delay slot.

Idea: make the lhu's address computation depend on the store's data. E.g. write the RMW as operating on a pointer variable that is assigned after the store:
```
s32 *pp;
...
sp10[4] = t;
pp = sp10;
((u16*)pp)[0] = ...
```
gcc: pp = sp10 is a copy; sched would still move the lhu up (the copy is cheap). Actually a register copy insn `move pp, sp` might be placed... sched could hoist the copy too.

Idea: make the lhu read a value that was stored by the sw? No.

Idea: use the *same* stack slot for both: i.e., write the fifth word to sp10[4] and read sp10[0] — different slots. What if instead the code stores t into sp10[4] via a u16 store? no.

Hmm, let me reconsider the problem: maybe I don't need the nop in that spot. What if there's a different lever-free body that produces the same 47 instructions but with a different route: e.g. the RMW part could use the loaded value... no, target is fixed.

What about making the fifth `lw` a *volatile* load? Volatile loads are not reordered across... hmm, a volatile load followed by lhu: sched treats volatile MEM as a barrier-ish? In sched.c sched_analyze_2, `MEM_VOLATILE_P` sets `sched_mem_barrier`? Let me check: line 1957 `if (code != ASM_OPERANDS || MEM_VOLATILE_P (x))` — that's for ASM. Let me look at sched_analyze_2 for volatile mem handling.

Actually in cse/flow, volatile is a lever (launder-ish?) but "volatile" as an access qualifier changes semantics... It's used in the src already (pbh volatile). Is `volatile` a lever kind? Kinds list: pin, barrier, launder, keepalive, instruction, gte-lever, asm-body. `volatile` is not in AB_KINDS... but "no new lever of any kind" — a volatile read is a codegen lever arguably. But it's used in the def already (pbh) in other items. Hmm, risky. But hold on: the barrier here is a `__asm__ __volatile__("" ::: "memory")` = "barrier". A `volatile` load isn't a barrier kind per the census? The census (lever_census.py) probably classifies `volatile` mem as... let me check AB_KINDS: {"pin","barrier","launder","keepalive","instruction","gte-lever","asm-body"}. Hmm, a volatile load would likely be "barrier" if the census treats MEM_VOLATILE as a barrier. Let me check lever_census.

Let me grep lever_census for barrier/volatile.

---
ts: 2026-11-06T11:42:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CyRjetsddliNGvo1Kaor
---
So removing the barrier alone (keeping launder) → 23, 75 ins. Wait, that's different from what I expected. So the barrier IS load-bearing (it causes the reload), and the launder is also load-bearing (it keeps the copy). Both are needed for the target. Hmm, but d1 has 75 ins and 1 load? Let me check d1's diff. Actually 75 ins is more than 71 — let me look.

Hmm wait: earlier v3 (launder removed, barrier kept) = 70 ins, 6. d1 (barrier removed, launder kept) = 75 ins, 23.

So both levers are load-bearing. And removing both = w1 with u16 = 75 ins 23; the u16 change recovered the copy? Let me check: w1 vs d1. w1 = both removed + u16 → 23, 75. d1 = barrier removed, launder kept, s32 → 23, 75. Hmm, so u16 compensated for the launder removal? Both give 75 ins.

Wait, that suggests: with the barrier removed (1 load), the launder's copy is needed and u16 sVar3 restores it.

So the residual now is the 1-load vs 2-load issue plus the register allocation.

Let me see d1's and w1's diffs.

Actually, let me focus: the target needs 2 loads. The barrier is the only thing causing the reload. Real C: need a memory invalidation between the first read and the second read, with no emitted code.

Options:
(1) A store to a varying address (PLUS, non-QI) with MEM_IN_STRUCT on the first load → invalidates only in-struct entries. But the store must be deleted from the output.

Wait — actually, we don't need the store to be deleted by cse; it could be deleted by *flow* which runs after cse. If cse keeps the store, the code has an extra `sh`/`sw`. If flow deletes it as dead, no code. A dead store: store to a location never read → flow's dead store elimination deletes it (with `flag_delete_dead_code`? flow's `delete_dead_code` runs at -O). But the store must be to a varying address (pointer+offset) to trigger nonscalar invalidation. A store to a local variable accessed via a pointer... e.g.:

```
u16 dummy;
u16 *dp = &dummy;    // varies? (plus (reg fp) (const)) — reg+const = PLUS
*dp = 0;             // store, MEM not in struct, address PLUS, HImode → nonscalar=1, all=0
```
This would invalidate in-struct memory entries only. And the first load must be MEM_IN_STRUCT.

But then the store to *dp generates `sh zero, off(fp)` — flow would delete it if dummy is never read (dead store). Does flow delete dead stores to stack slots? `flow.c`'s `delete_dead_code` handles dead stores to pseudos... Actually flow's dead code elimination removes insns whose only effect is a dead store. For a stack slot never used, yes likely deleted.

Hmm, but wait: the first load must be MEM_IN_STRUCT for the invalidation to hit it. Currently `*(u16 *)(p + 0xAE)` is NOT in-struct. Making it in-struct: access via a struct pointer: `((struct S*)p)->field` → MEM_IN_STRUCT. But then the address is the same; cse's table entry has in_struct=1. Then the nonscalar store invalidates it. Then the second load (from the same address, whether in-struct or not) is a fresh load → reload. 

But careful: the second load must also not be forwarded from anything. After invalidation, it's a fresh load. Good.

And the emitted code: the struct-member load compiles the same (lhu). The store must be deleted.

That's the G21x technique ("struct-member u16 load ... cse invalidates at the nonscalar store"). Promising!

But wait — the store must be between the first and second loads in program order, and it must be deleted. Let me think about what store to use. In G21x's case, the store was already in the source (a real store to ptr[3]) — the trick was to make the *load* in-struct so the existing store invalidates it.

Here there's no store between. Hmm.

Alternative (2): make the *second* load not cse-equal to the first by using a different memory mode/address that still emits lhu. E.g., first read as `*(u16*)`, second as `*(s16*)` — but lhu vs lh. Target uses lhu both.

Hmm, what about reading the second one as part of a *bitfield*? Same lhu.

Alternative (3): the first read could be from a *union* with a different mode... no.

Alternative (4): what about `bb` being pinned to $3 (v1)? In the target, the first load is in v1 and the second in a1. If cse forwards, it reuses v1. 

Alternative (5): use the `&&`/`||` fold to create a separate basic block. The C is `if (lo != c80 || (hi = bb >> 8) != 0x80)`. The `||` creates a branch. cse follows into the body... The second load is in the body. cse's table crosses.

Hmm, wait. Actually let me reconsider: does cse really forward across the branch into the if body? The diff shows w1/d1 with 1 load, so yes.

Alternative (6): Put the second read inside a `do{}while(0)` block (C0535). Let me just try it — cheap.

Where exactly? The if body:
```
if (...) {
    do {
        sVar4 = ratan2(...);
        store;
        return 1;
    } while (0); // !FAKE: do-while
}
```
The do-while creates a label at the end of the block; the block ends with `return 1` so the label is after... hmm, `return` makes the while condition unreachable. Actually with a return inside, the do-while's back-edge is dead; the compiler still emits the label/jump structure at -O0? At -O1, jump optimization removes unreachable code but the label might remain.

Better: put the do-while around the *first* read and compare:
```
do {
    bb = *(u16 *)(p + 0xAE);
    lo = bb & 0xFF;
} while (0); // !FAKE: do-while
if (lo != c80 || ...) { ... }
```
Hmm, but bb is used inside the if. The do-while(0) would emit a label; cse's table isn't flushed at labels though...

Let me check how cse handles a basic block end at a label: `cse_end_of_basic_block` determines the block end; the table persists between blocks. So a do-while doesn't flush.

Hmm, but C0535 says it "splits cse1 EBB" and cracked a sched1-birth-order item — that was about sched1, not cse memory.

Alternative (7): Make the second read happen *after a call*. The call ratan2 is the one taking the reads. But what if we restructure: compute sVar4 with the *first* read's value, and then the store... no, the target clearly does 2 loads.

Hmm, what if we introduce a call before the second read that gets... no.

Alternative (8): Use `flow-known-value`? no.

Let me look at this from the source-structure angle: what real C would naturally produce 2 loads? If the two reads were of *different variables that alias* — e.g., one through a `u16 *` and one through a struct member. cse hashes by address expression; if the address expressions differ (e.g., `(reg)` vs `(plus (reg) (const_int 0))`) they might not match! 

Idea: read the second via `p[0xAE/2]`? p is s32 → `*(u16*)(p + 0xAE)`. Same.

What if the second read is `*(u16 *)((u8 *)p + 0xAE)`? fold.

What if the second read uses a *different base variable* that holds the same pointer: `s32 q = p; ... *(u16*)(q + 0xAE)`. cse would know q == p (copy propagation in cse) and substitute.

Unless q is computed in a way cse can't fold: `s32 q = p + 0;` folds; `q = (s32)((u8*)p)` folds.

Hmm, what if q is loaded from memory (e.g., a global)? That adds a load.

Alternative (9): Make the first load's value used *only* in a context where cse marks the memory expression as non-recordable... 

Hmm, what about the store to the *same* location: `*(u16*)(p + 0xAE) = bb;`? cse processes the store: it invalidates memory (nonscalar if the address varies — p+0xAE is PLUS → nonscalar=1; and in_struct if the MEM is in-struct). Since the first load is not in-struct, the entry survives. Then cse might delete the store as redundant (storing the value just loaded). Does cse delete such a store? In cse_insn, for a store whose src is a register that's equivalent to the memory value... There's a specific check: "If the source is a constant or in memory, and the dest is memory, and they're equal, delete." Let me look at the store-to-memory handling in cse_insn.

Let me grep for "sets[i].dest_hash" / the store logic.

Actually, let me take an empirical approach: try a bunch of candidate real-C tricks and score them. Ideas:
- T1: make the first read a struct member + a dead store via a pointer between.
- T2: self-store.
- T3: dead store to a local via pointer.
- T4: do-while around the if body.
- T5: read the second value through a union.

Let me look at the struct type available: Unkstruct_80126948 is used for D_801151D4. For p, what struct? Let me check if there's a struct covering offset 0xAE. Let me grep for the type of p in the TU. `void *a0`, p = (s32)a0. I can define a local struct type? Adding a struct definition inside the function is allowed (real C). E.g.:

```
struct S { char pad[0xAE]; u16 f; };
...
u16 bb = ((struct S *)p)->f;
```
But p is s32; cast `(struct S *)(s32)p`. Hmm, a local struct decl in the function body — allowed (no decl change outside the body).

Let me test T4 first (cheap), then T1.

Actually wait. Before the struct trick, let me test whether a store between the loads (which would be deleted by flow) yields the reload. Even simpler: what does a real store do to cse? Let me try:

```
bb = *(u16 *)(p + 0xAE);
lo = bb & 0xFF;
*(u16 *)(p + 0xAE) = bb;   // self store
if (...) { ... }
```
If cse deletes the self-store, we get the invalidation for free? Actually if the store is in-struct... the store's MEM is not in-struct → nonscalar invalidation removes in-struct entries only; the load entry is not in-struct → survives. Hmm. Unless the store invalidates `all`. The store address `p + 0xAE` is PLUS → not all. So no invalidation of the non-in-struct entry.

But the *exact* address invalidation: at the end of cse_insn, for a MEM dest with `!writes_memory.all && !cse_rtx_addr_varies_p(dest)` → invalidate(dest). Here the address varies (p is a pseudo? after allocation it's a hard reg but during cse it's a pseudo/reg — cse_rtx_addr_varies_p checks if the address is a register with a known constant... Actually at cse1 time, p is a pseudo-reg (or the parameter's reg). `cse_rtx_addr_varies_p` returns true if the address involves a register that isn't a constant). So the exact invalidate is skipped, and nonscalar invalidation only removes in-struct entries.

So the self-store doesn't invalidate the load entry unless the load is in-struct.

Therefore T1: make the first load in-struct AND add a nonscalar store (which must be deleted).

Where to put the store so it's deleted? A store to a local `u16 dummy` via pointer... would flow delete it? Let's just test empirically whether the code has an extra `sh`.

Alternatively: make the *existing* store (`*(u16 *)(iVar5 + 0x12) = ...`) be the nonscalar store — but it's after the call.

Hmm wait, actually! What about the *first* load being in-struct and the store being... there's no store before. 

Hmm, hold on, maybe there's another path: `invalidate_from_clobbers` — the asm barrier was a `clobber` of memory: `asm volatile("" ::: "memory")` becomes `(clobber (mem:BLK (scratch)))` → note_mem_written with addr SCRATCH → everything. That's the barrier.

Real C clobber of memory: a function call (non-const) invalidates everything. So if a call occurred between the loads, we'd get the reload. 

IDEA: what if we compute `bb` via a call? No.

IDEA: reorder the ratan2 call. The second read is an argument to ratan2. What if we split: first call ratan2 with something else... no.

Let me look at the actual target again: the two loads are at 32d4 and 32f0. Between them: li, andi, bne, srl, beq, move. No call.

So the barrier is the only way. Therefore real C cannot produce this without a memory clobber... unless the in-struct + varying-store trick, with the store deleted.

Let me test the in-struct + self-store idea empirically. Actually, better: in-struct first load + a store to a local via pointer.

Wait, actually — simpler: in-struct first load + a store to `*(u16*)(iVar5 + 0x12)` moved before the second read? No, the target's store is after.

Hmm, but what about a store to a *global* through a pointer variable? That would be `sw` — extra code.

OK let me think about whether flow deletes dead stores to stack slots. In gcc 2.7.2 flow.c, `delete_dead_code` (in flow.c) removes insns that are `set (mem) (reg)` where the mem is dead... Actually dead store elimination is in `flow.c`'s `mark_set_1` / `delete_dead_code`? There's `insn_dead_p` used by `delete_dead_code` in flow.c, which handles `(set (reg) ...)` dead regs and `(set (mem) ...)` where the memory is a stack slot that's never used? I recall flow's dead code elimination deletes dead stores to pseudo-registers only... Let me check.

Actually, there's a simpler known trick: a store to a *local array element* that is never read. E.g.:
```
u16 dummy[2];
u16 *dp = dummy;
dp[0] = bb;
```
The address is `dp + 0` = PLUS → nonscalar. The store is `sh` to the stack. flow might delete it.

Let me just try it and look at the insn count.

Let me also consider: instead of a dummy store, use a *real* store that the target has but reordered? No.

Let me run experiments. T1: struct-member first load + dead store.

Actually, first let me test whether a dead stack store survives at all: add `u16 dummy[2]; dummy[0] = bb;` and see the insn count.

Let me write these variants. I need to be careful with C89 (declarations at block start).

Variant t1:
```
case 0x53: case 0x73:
{
    u32 bb;
    s32 c80 = 0x80;
    s32 lo, hi;
    u16 dummy[2];
    u16 *dp = dummy;
    bb = *(u16 *)(p + 0xAE);
    lo = bb & 0xFF;
    *dp = bb;
    if (lo != c80 || (hi = bb >> 8) != 0x80) { ... }
```
But bb is u32 → extra andi. Keep bb as u32 per the original (pin $3).

Hmm, actually with the pins: bb pinned $3. c80 pinned $2, hi pinned $2. Let me keep them.

Let me try with a dead store and see the insn count first (does the store survive?).

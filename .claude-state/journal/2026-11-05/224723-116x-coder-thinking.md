---
ts: 2026-11-06T05:47:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bwAfJquEt95hNgNqS18v
---
`assign_stack_local(BLKmode, 0, 0)` rounds the frame to BIGGEST_ALIGNMENT but adds 0 bytes. Not 16.

Hmm. Let me look at the family's orig .frame again: vars=16. And nobar: vars=0. Let me check if the *unused* 16 bytes are actually a spill slot from `alter_reg`. To see, I can check the reload dump (`-dR`?) for "spill" or check `reg_renumber`. Simpler: look at the .lreg dump for a pseudo with no hard reg. The .lreg dump lists regs; the .greg shows the allocation. Let me look at the orig greg dump around the asm for a pseudo marked "no reg".

Actually, maybe the 16 bytes are the *outgoing args* misattributed. The .frame comment's `vars` = var_size = MIPS_STACK_ALIGN(get_frame_size()). If `current_function_outgoing_args_size` is 16, that goes in the args field, not vars.

Let me look at the orig .s function again: `.frame $sp,16 # vars=16, args=0`. So var_size=16.

Let me find what allocates 16 bytes by checking the reload dump for the function. The dumps include `.greg` (global alloc), `.lreg`, `.sched`, `.sched2`, `.dbr`, `.rtl`, `.combine`, `.cse`, `.cse2`, `.flow`, `.jump`, `.jump2`, `.loop`. No reload dump (`-dR` not included).

Alternative: run cc1 with `-dR`? Not available via the script. Hmm.

Actually, let me test the hypothesis directly with the probe: the probe t5 (with the clobber) had frame 16. Let me vary the body to see when the frame appears. Variants: clobber in the middle → 16; clobber at end → 0. So the clobber's *position* matters. What if the clobber is between the two uses of `*q`? It is (after the store, before the p2 load). What if I remove the `*p2` store? etc.

The 16 bytes likely come from a reload spill of the `*q` value or the address. With the clobber, cse can't forward, so the value is reloaded — maybe a pseudo needs a stack slot.

Hmm, wait: maybe the 16 bytes are from the **`(mem:BLK (scratch))` clobber being turned into a stack slot by reload**. In reload1, `find_reloads` on a `(clobber (mem:BLK (scratch)))` — a CLOBBER of MEM is not reloaded normally. But the MIPS machine description may match `(clobber (mem:BLK (scratch)))`? Unlikely.

Let me look at the probe's `-dg` (greg) dump for the clobber and check whether a stack slot pseudo appears. Actually, let me check the probe's `.lreg`/`.greg` for a reg with no allocation. Hmm.

Time is limited. The practical question: is the family a WALL? Almost certainly yes (the comment itself says the fences are what keep the parts from CSE-ing). But I must try ≥30 lever-free bodies per item. Let me generate 30+ variants per family item and score them. Since the three are near-identical, I can use the same candidate set.

Let me design candidates that might beat the cse cache:
1. Recompute q after the store: `q = (u16 *)&(*(u16 *)&D_800B9A02);` again before the p2 block — cse propagates the same value, no help, but try.
2. Use a `u16 qv = *q;` variable and reassign `qv = *q;` after the store — cse forwards.
3. Use `volatile`? Not allowed.
4. Make the second use read via a different expression: `*(u16*)((u8*)&D_800B9A02 + 0)`.
5. Make `*q` a struct member: declare `extern struct { u16 v; } D_800B9A02;` — but the symbol is defined elsewhere as s16; changing the extern type is a decl change outside the body? The brief says "no signature or decl change outside the body". The extern decls are *inside* the function body (block scope), so changing them is inside the body. Hmm, but D_800B9A02 is a shared symbol; its type must match the global definition. The TU's global decl is `extern s16 D_800B9A02;` (from engine_types?). The header declares `extern s16 D_800B9A02;` inside the function. If I change it to a struct type inside the body, that's a type mismatch with the TU's declaration — but C allows different declarations in different scopes? The linker just needs the symbol. GCC would emit the same symbol. Semantically, `struct {u16 v;}` has the same layout as s16. This is a "type pun" inside the body.

Hmm, but is that a "launder"/lever? It's a real C move (type change). The C0505 catalog includes "s16/u8 widths". A struct type change might count as a lever (it's not in the catalog). Risky.

6. Use `u16 *q` vs `s16 *q`.
7. Make the store QImode? no.
8. Reorder the three parts.
9. Compute `*q` once into `s32 idx` and use `idx` for all uses — that's what the compiler does anyway.
10. Use `p + *q*4` vs a local `u8 *base = p + *q*4;`.
11. Split the function into blocks.

Given the cse wall, most won't crack. But let me try the promising one: make the load in_struct. How? If we access `D_800B9A02` through a *struct pointer* variable: `S *sp = (S*)&D_800B9A02; ... sp->v` — the load is `(mem:HI (reg sp))` with MEM_IN_STRUCT_P true (struct member access). Then the nonscalar store would invalidate it (p->in_struct && nonscalar) → reload! And the codegen: `sp->v` where sp = &D_800B9A02 → the compiler folds sp to the symbol address → `lhu v0,0(a2)`. Same instruction. This could be the crack!

But wait: MEM_IN_STRUCT_P for `sp->v`: the expression is `(mem:HI (reg sp))` built with MEM_IN_STRUCT_P = 1 because it's a struct member. Then `elt->in_struct` = MEM_IN_STRUCT_P(inner_dest)... for a *load*, the entry's in_struct comes from `hash_arg_in_struct` (set when hashing an expression containing an in-struct MEM). So p->in_struct = true. Then invalidate_memory with nonscalar → invalidates it → the second use reloads. 

But also the *first* use (for `ptr = D_800AE7BC[*q].f0`) happens before the store; that's fine.

However: would this struct-typed load also change the codegen of the first part (e.g., the `*q*4` computation)? Possibly not.

Let me try this on the family. Also, the frame artifact remains (target vars=16). Hmm, but maybe with the struct load, the register pressure changes and the spill slot appears? Unlikely to match exactly.

Actually, wait. Let me reconsider the frame: maybe the 16-byte frame IS a spill slot for the `*q` value! With the clobber, cse can't reuse `*q`, so the compiler must keep it... no, it reloads.

Hmm, let me look at the target's spill: the 16 bytes are unused. In reload, `alter_reg` allocates a slot for a pseudo with no hard reg. Which pseudo? Maybe the pseudo holding the address of D_800B9A02 (q). With the clobber, the address pseudo's liveness... it's used 3 times.

Let me try the struct-member idea and see the score. If it gets close (score 2 for the frame only), then the frame is the remaining wall.

Let me build the family candidate generator. The three items differ only in offsets (0x20/0x18 for 75820, 0x30/0x28 for 758FC, 0x40/0x38 for 759D8) and ptr index (2/3/1) and struct type names. Let me generate per item from the orig body with transformations.

Let me write a generic generator that takes the orig body and produces variants by string replacement. First, let me set up orig.c for all three (already copied earlier? I copied orig.c for 75820 and nobar; for 758FC and 759D8 I copied orig.c and nobar.c in the loop earlier). Let me verify and then write the generator.

Let me check the freshness: orig.c vs src (G08c note). I copied them at ~22:12. src hasn't changed. Let me diff to confirm.

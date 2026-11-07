---
ts: 2026-11-06T05:21:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Xkjg800Tjzg9DBhajsYw
---
GCC 2.7.2 cse has a `write_data` structure with bits (PUSH, FIXED, SCALAR, etc.) — "writing at a fixed address invalidates only variable addresses", "writing in anything else at variable address invalidates everything". A store through a pointer (`(mem:SI (reg))`) is at a variable address → invalidates everything. So cse SHOULD invalidate the *q load. Yet the candidate reused it (a0 computed before the store).

Hmm, but the reuse is of the *address computation* which happened before the store at insn 3cf4-3d00. Was it before the store? Yes: `sll a0,v0,2` at 3cf4, store at 3d24. The load `lw v1,24(a0)` at 3d28 uses a0. So the *q load at 3cec is used to compute a0 before the store. That's legal: the value *q was loaded before the store; computing an address from it before the store is fine. The question is whether the *load of 24(a0)* is correct: if the store changed *q, then a0 is stale. But the compiler computed a0 before the store, using the pre-store *q — that would be a miscompile!

Unless the compiler *knows* the store can't alias D_800B9A02 because `ptr` is derived from `D_800AE7BC[*q].f0` and... no.

Wait, let me re-read the source:

```
q = (u16 *)&(*(u16 *)&D_800B9A02);
ptr = D_800AE7BC[*q].f0;
old = ptr[2];
ptr[2] = (old & 0xff000000) | (*(u32 *)(p + *q * 4 + 0x20) & 0xffffff);
__asm__("" ::: "memory");
p2 = *(u32 **)(p + *q * 4 + 0x18);
*p2 = (*p2 & 0xff000000) | (old & 0xffffff);
```

Without the barrier, `*(u32*)(p + *q*4 + 0x20)` and `*(u32**)(p + *q*4 + 0x18)` use *q. The compiler loads *q once (3cec), computes `p + *q*4` once (a0), then uses a0+0x20 and a0+0x18. But between them there's a store through ptr. cse should invalidate the *q value after the store... but the *value* of *q is used to compute the address a0 BEFORE the store for the first use (a0+0x20 at 3d10 `lw v0,32(a0)` is before the store at 3d24? Let me check order:

candidate:
```
3d00: addu a0,a0,t2      # a0 = p + *q*4
3d04: lui at, D_800AE7BC
3d08: addu at,at,v0      # v0 = *q*12 (the index)
3d0c: lw a2,0(at)        # ptr
3d10: lw v0,32(a0)       # *(p+*q*4+0x20)  -- BEFORE store
3d14: lw a1,8(a2)        # old = ptr[2]
3d18: and v0,v0,t0
3d1c: and v1,a1,a3
3d20: or v1,v1,v0
3d24: sw v1,8(a2)        # store
3d28: lw v1,24(a0)       # *(p+*q*4+0x18) -- AFTER store, uses a0 from pre-store *q
```
So the compiler computed a0 = p + *q*4 using the pre-store *q and used it after the store. That IS a miscompile *if* the store could change *q (D_800B9A02). Hmm! Unless the compiler proved it can't. 

Could GCC prove `ptr[2]` doesn't alias D_800B9A02? `ptr = D_800AE7BC[*q].f0` — ptr is loaded from a global array; no. But maybe cse's write_data: the store is `(mem/s:SI (plus:SI (reg) 8))` — a struct member at a variable address → invalidates all memory. Then the *q load at 3cec would be invalidated. But the address a0 computed from *q was already computed before the store and is a *value* in a register, not a memory ref; cse invalidates memory refs, not register values. So the register a0 (computed from *q pre-store) survives the store. Then using a0 after the store is... semantically wrong only if *q changed, but the compiler doesn't know it did, and reusing a *computed address* is exactly as wrong as reusing the value. Hmm, but the source's second use `*(p + *q*4 + 0x18)` re-reads *q. If the compiler reuses a0, it assumes *q unchanged. So cse must have decided the *q load is not invalidated by the store.

So cse's write_data says: the store at a variable address invalidates "everything" — including the *q load. Then why reuse? Maybe because the *q load is from a *fixed address* (D_800B9A02, a symbol) and the store is at a variable address → "writing in anything else at variable address invalidates everything". So it should invalidate. 

Unless the store's address is `(plus:SI (reg) (const_int 8))` and cse's classification sees the base reg as a "pointer to a struct"? Hmm, `(mem/s:SI ...)` — MEM_IN_STRUCT_P might make cse treat it as a scalar struct member write and only invalidate "scalar variables"? The bits: FIXED (fixed address), SCALAR (scalar variable), STRUCT... Let me read the write_data logic in cse.c.

Actually, this is the known wall from moves.md: "cse-fixed-global-cache — cse keeps a global pointer load in a reg across a nonscalar store; target reloads (G18x)". That's exactly this! `cse-fixed-global-cache`. So this is a known WALL tag. The barrier was used to force the reload; without it, cse caches the global across a nonscalar store. Great — so func_80175820/758FC/759D8 are likely WALL `cse-fixed-global-cache`, and the family is the same.

But wait, the wall tag exists, meaning some other shard already hit this and walled. Good. But we still must try ≥30 lever-free bodies and 20 min per item. Hmm, that's the requirement. Let me be efficient: generate a bunch of candidate variants programmatically and score them with sc.sh (one line each). 30 candidates per item is doable with a script.

But before that, let me reconsider the frame issue: the target also has a 16-byte frame from the clobber. Even if cse were fixed, the frame remains. So a lever-free body can never score 0 for these — the frame alone is a 2-insn diff. So WALL is certain for 75820/758FC/759D8 (and probably all 5).

Hold on, is the frame really from the clobber? Let me verify by checking the *candidate with clobber but no asm*... we can't have a clobber without asm. The evidence: orig (clobber) frame 16, noasmclob frame 0, nobar frame 0. So yes: the memory clobber creates the 16-byte frame.

Let me understand why: in `expand_asm_operands`, `(clobber (mem:BLK (scratch)))`. Then in `sched`/`reload`, the `(mem:BLK (scratch))` might cause `assign_stack_local`. Let me grep reload1.c / local-alloc for scratch/mem:BLK. Actually, let me check `sched.c` or `reload1.c` for BLKmode stack temp. Hmm.

Actually — I recall now: in GCC, `(mem:BLK (scratch))` as a CLOBBER in a PARALLEL is handled by `find_reloads`? No, clobbers of MEM are handled by `reload`? Hmm, actually `(clobber (mem:BLK (scratch)))` is the standard way to say "asm clobbers memory" and it should be harmless.

But the 16-byte frame... Let me look at the final .s for a stack slot. Actually, maybe the frame is `get_frame_size()` including `current_function_outgoing_args_size`? The .frame says args=0.

Let me look at the MIPS machine description: maybe `(clobber (mem:BLK (scratch)))` matches a pattern that requires a stack temp? Unlikely.

Hmm, let me look at the `-dl` (lreg) or `-dL` dump for `stack`. Actually, let me grep the orig .s for the frame's stack slot: the frame is 16 but no access. Let me search the *combine* or *cse2* dump for `(mem:BLK`.

Actually, this doesn't matter for the wall decision. What matters: no lever-free body can produce a 16-byte unused frame. Let me confirm by checking the other items' frames: does every barrier body have a 16-byte frame? func_80150170: target frame 56, nobar frame 72. Hmm, that one is different (target smaller). Let me check its .frame comment. Actually for 80150170, the target has arrays a[8],b[8],out[8] = 24 bytes + padding; frame 56 = 24 + ra/s0/s1 (12) + ... = 40? Hmm 56. Nobar 72.

Wait, maybe for 80150170 the asm's 16-byte frame adds to 40 → 56? Let's see: nobar frame 72 = locals 24? Hmm, 24 + 12 saved + 8 pad = 44 → 48? Not 72.

Let me compute: nobar has `addiu sp,sp,-72`, saves s0 at 56, ra at 64, s1 at 60. So frame 72, with saved regs at 56-64 (3 words) and locals a=16,b=24,out=32 (40 bytes). 40 + 12 = 52 → rounded to 56? But it's 72. So there are 16 extra bytes of something. Hmm, 72 = 40 + 32. 

Target frame 56: saved regs at 40,44,48; locals a=16,b=24,out=32. So 40 bytes locals + 12 saved = 52 → 56 (aligned). So target is "tight": 40+12+4 pad = 56.

Nobar 72: 40 locals + 12 saved = 52, but frame 72 → 20 extra. Hmm, 72-52 = 20. Or maybe locals are bigger: out at 32, and out[8] = 8 bytes → 40. Hmm.

Maybe the nobar version spills something to the stack (extra 16 bytes). Let me look at the nobar .s for stack accesses. Actually the nobar candidate disassembly showed only sp adjustments and the arrays. Let me look for `lw`/`sw` with `(sp)` in the nobar function asm: I saw `lwl v0,35(sp)`, `lwr v0,32(sp)` (the memcpy from out), and the arrays. Those are the locals. Nothing else.

So where does 72 come from? Maybe `out` is 8 bytes but placed at 32, and there's an 8-byte pad. 32+8=40; saved regs 56,60,64 → frame must cover 68 → 72. Ah, the saved regs are at 56-64, so the frame is at least 68, rounded to 72. Why are saved regs at 56 instead of 40? Because the *local area* was allocated as 56 bytes (0..55) instead of 40. So there's 16 extra bytes of locals in the nobar version too!

Hmm, so both have 16 extra bytes; the target has them at 40-55 and the saved regs at 40-48?? Wait target: locals a=16,b=24,out=32..39; saved s0 at 40, s1 at 44, ra at 48 → frame 56 (48+4 rounded to 56? 52→56). So target locals end at 40, saved regs 40-51, frame 56.

Nobar: locals a=16,b=24,out=32..39, saved regs at 56,60,64 → there's a gap 40-55 = 16 bytes. So nobar has 16 extra *unused* bytes at 40-55, and target has none!

So the frame difference is: nobar has 16 unused bytes, target doesn't. Interesting — reversed from 75820.

Hmm, so for 80150170, the asm *removes* 16 bytes of unused stack. That suggests the 16 bytes are a *temp slot* allocated by the expansion, and the asm's presence frees it... no.

Wait, maybe the 16 bytes are the *outgoing args* area: nobar frame 72 includes args=16? Let me check the .frame comments for 80150170 orig and nobar. Let me dump.

This is getting deep. Let me step back and think about the task strategy.

The task: 5 barrier items, find lever-free bodies scoring 0, else WALL. Given the evidence that the barrier asm creates compiler artifacts (16-byte frames, clobber barriers), these are likely all walls. But the brief demands ≥30 scored tries and ≥20 min per item for a WALL. That's 2.5 hours of work. The budget says 20-30 min wall per item. So 5 items × ~25 min = ~2 hours.

I should do this systematically: for each item, generate ~30+ plausible lever-free variants (real C moves from the catalog), score them all with sc.sh, take the best, and record. Then move on.

But wait — maybe some of these CAN crack. The moves.md shows barrier items cracked by semantic moves (e.g., "||-fold of the two return-0 tests"). For func_80180D38, the barrier is in an early-return branch; maybe removable by restructuring. For func_80150170, the barriers are inside if/else arms and the barrier forces reloads of the stack arrays — that might be crackable by making the values not be in registers (e.g., using different expressions or reordering). For the 75820 family, the cse-fixed-global-cache wall is known.

Let me be systematic per item, starting with 80150170. Let me first check its .frame comments to understand the 16 bytes.

Actually, let me reconsider the 16-byte frame in 75820: the target has `.frame $sp,16` and nobar `.frame $sp,0`. And in 80150170 the nobar has 16 extra bytes vs target. So the asm's memory clobber affects the frame in both directions. This strongly suggests the clobber creates/frees a temp slot during expansion.

Let me find the source of the 16-byte temp: in `expand_asm_operands`, `free_temp_slots()` at the end. The asm's clobber might cause a temp slot allocation *somewhere* due to `force_reg` or `protect_from_queue`. Hmm.

Actually — maybe it's the `(clobber (mem:BLK (scratch)))`: in `sched.c`, the scratch mem might be `assign_stack_local`? Let me grep sched.c / reload1.c / local-alloc.c for BLKmode or scratch.

---
ts: 2026-11-06T05:19:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8T6ilFwgVkqZdWSitkw7
---
Wait, in the greg dump the asm is insn 55 and the next is insn 59. There's no stack slot. But notice: `(clobber (mem:BLK (scratch)))` — the scratch. In greg, the asm insn is not a real instruction; it's removed before final. The frame size is set in `final()` from `get_frame_size()`.

Let me look at the nobar greg dump's function to see if there's any stack pseudo. Both have none, so frame should be 0 for both. Yet .s says 16.

Hmm, unless... the `subu $sp,$sp,16` is NOT a frame adjustment but the *asm expansion in the .s*: look at the .s again:

```
 #APP
 #NO_APP
	lhu	$2,0($6)
	#nop
	sll	$2,$2,2
	lw	$3,D_8011F7A8+24($2)
	subu	$sp,$sp,16
	lw	$2,0($3)
```

The `subu $sp,$sp,16` is placed 3 insns after #NO_APP. If it were the prologue adjustment, sched1 could move it down but only within the block/region; the asm acts as a barrier. It was moved below the asm, meaning sched moved the prologue `subu sp,sp,-16` after the asm. And the epilogue `addu sp,sp,16` is at the end. So it IS the frame adjustment (prologue) that got scheduled late. Frame=16.

So why frame 16? Let me check `get_frame_size` semantics. In function.c, `get_frame_size()` returns `frame_size`. frame_size is set in `assign_stack_local_1`... and also `current_function_outgoing_args_size` is separate.

Hmm, wait: maybe the frame is 16 because of `-fgnu-linker`? no.

Let me check the *target* object for the other family members: do they also have this mid-function sp pair? If so, all 3 family items are the same wall.

Actually, let me step back and think about the task design. The shard is "singleton crack shard G21x (scratch-only)". 5 items, all barrier. The brief says "Lever-free = none of the row kinds remain: no pin, launder, barrier, keepalive macro or asm; no new lever of any kind." And WALL is allowed with evidence. The moves.md shows many barrier items cracked with moves like "||-fold of the two return-0 tests", "field-direct &= and --", "goto loop", "store subtract direct", etc. So barriers CAN be cracked when the barrier is a semantic crutch, but here the barrier might be load-bearing for codegen.

For func_80175820 family, the barrier sits between the `ptr[2]` store and the `*q` reload. The barrier forces the reload of the global D_800B9A02. But we showed the nobar version DOES reload the global (insn at 3d44: `lhu v0,0(t1)`) — wait, in the nobar candidate, at 3d44 it's `lhu v0,0(t1)` where t1 = &D_800B9A02. So it reloads. Good. The differences are register allocation: target uses `a2` for the global address (loaded once), candidate uses t1/t2. And the frame 16.

Wait, actually, the target computes `la $6,D_800B9A02` ONCE (in .s line 4110) and reuses $6 for all three `lhu $2,0($6)`. The candidate (nobar) also loads from t1 three times but computes t1 once too. Hmm, both compute once. The candidate object showed `lui t1; addiu t1` and `lui t2; addiu t2` — t2 is D_8011F7A8. The target uses `a2` for D_800B9A02 and computes D_8011F7A8 addresses with `lui at; addu at,at,...` each time.

So the register allocation differs: target keeps the D_800B9A02 address in a2 (caller-saved, long-lived) and re-materializes D_8011F7A8 base; candidate keeps D_8011F7A8 base in t2 (callee-saved!) and D_800B9A02 in t1. Wait t1/t2 are caller-saved. Hmm, in the candidate asm: `lui t1; addiu t1` (D_800B9A02), `lui t2; addiu t2` (D_8011F7A8). Both t1/t2 caller-saved. So it keeps both addresses live. Target keeps only a2 for D_800B9A02 and uses `at` (assembler temp) for D_8011F7A8 each time.

Why? In the target (with asm barrier), the asm's memory clobber means the D_8011F7A8 base pointer must be re-materialized after the asm (cse killed it), so it doesn't keep it in a reg across. In the candidate, cse keeps the base in t2 across the whole function.

Hmm, but the candidate DOES reload the value `lhu v0,0(t1)` after the store, so cse invalidated the *value* but not the *address*. The address of a global is a constant, so cse can keep it.

In the target, the address is also constant; it keeps D_800B9A02's address in a2. But it recomputes D_8011F7A8's address each time because... register pressure? It needs `at` anyway.

The core difference: target uses `lui at; addu at,at,v0` (recompute per use) vs candidate `lui t2; addiu t2; ... addu a0,a0,t2`. These differ in register allocation and the presence of the frame.

The 16-byte frame: hmm, could the frame be because the target function has `args=16`? Let me re-read: `.frame $sp,16,$31 # vars= 16, regs= 0/0, args= 0, extra= 0`. It says vars=16.

WAIT. Maybe the 16-byte "vars" is the **asm's memory clobber forcing the compiler to reserve a slot for `(mem:BLK (scratch))`**? In reload, a `(mem:BLK (scratch))` clobber... Actually! In `reload1.c`, `(scratch)` is `(const_int 0)`? Let me check `find_reloads` for SCRATCH. Hmm.

Actually, maybe the answer is in `get_frame_size` / `assign_stack_local` and the `-dg` dump. Let me search the greg dump for "frame" — nothing. Let me search the *final* .s of the nobar for `.frame`: 0. So the only difference is the asm.

I'll test the minimal hypothesis once more but with the asm placed *between a store through a pointer and a load from a global*, in a function with an extern struct array. Actually, let me test whether `__asm__("" ::: "memory")` in a function that has an **uninitialized local pointer used before** causes a frame. My minimal test had no locals. Let me add locals similar to the real function: `u8 *p = ...; u16 *q; u32 *ptr; u32 old; u32 *p2;` with an extern array.

Actually — I have a better idea: take the real orig.c body and change ONLY the asm to `__asm__("");` (no memory clobber) and see the frame. That isolates the clobber. If frame 0 → clobber causes it. If frame 16 → the asm statement itself (any asm) causes it.

Let me do that via dt.sh quickly (it scores, but I want the frame). Use hdump? dt gives score + diff. Let me just run dt.sh and see the first diff lines (frame).

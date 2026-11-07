---
ts: 2026-11-06T03:59:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LFgg8uc4H0CMMeXixKcN
---
exp_equiv_p compares generic rtx; MEM falls to the generic loop comparing XEXP only (and mode), ignoring in_struct. So MEM_IN_STRUCT_P does NOT distinguish entries for matching. So that trick won't work.

Back to: how to prevent load forwarding. Options:
1. Different mode: make the second load a different mode (e.g., SI load of 0x2E then truncate?) Target is lh (HI). A 32-bit load would be `lw`, different insn. No.
2. Make the second access address not rtx_equal: e.g., compute the address via a variable that cse can't equate: `s32 off = 0x2E; x2 = *(s16*)((s32)s0 + off);` cse folds constant off. No.
3. Use a different base register that cse can't equate: e.g., `s32 base = (s32)s0;` then `*(s16*)(base + 0x2E)` — cse's copy propagation equates base with s0? At the RTL level, `base` is a pseudo assigned from s0; cse's canon_reg replaces base with s0 in the address (copy propagation). Yes.
   But what if base is derived through a non-copy, e.g., `s32 base = (s32)s0 + 0;`? combine folds.
4. A store that invalidates: not present.
5. The load's value must be dead before the second use, so cse can't keep it: cse replaces the second load with a reference to the first pseudo; the pseudo is still live (used by subu at 77d4 and later). No.
6. Prevent cse from recording the first load at all: e.g., the first access is inside a context where `do_not_record` is set — e.g., an asm (banned), or a volatile load. Volatile is the natural mechanism. Is volatile banned? The brief says no lever of any kind; volatile isn't in the C0505 catalog. Hmm.

Wait, maybe the original source didn't have cse fail; maybe the target's second `lh` comes from reload because the value was in a *hard* register that got clobbered? Let's see: if cse forwarded, it would produce a copy. But maybe in the original, the first load's result was in a pseudo that local-alloc assigned to a call-clobbered register across the call func_80182654? No, the call is before both loads.

Let me reconsider: maybe the two loads are genuinely different C expressions with different *signedness* producing the same lh? No: u16 → lhu.

Hmm wait: `*(s16 *)((s32)s0 + 0x2E)` produces lh. What if the second is `*(s16 *)((s32)s0 + 0x2E + 0)`? same.

What about the first access being `*(u16*)(...)` sign-extended by a cast: `(s32)*(u16*)(s0+0x2E)` → lhu + sll/sra? Target first load is lh (77cc) so no.

Let me look at the original target's first load: 77cc lh v0,46(s0) then subu a0,a0,v0. Yes signed.

Hmm, what if the two accesses use different *pointer variables* that are provably different? cse canonicalizes.

Alternative: maybe the second load is from a pointer that the compiler thinks is a different object due to a cast through a `struct` with a different mode... no.

Let me look at the actual original ROM function: maybe the function in the ROM is at a different address and the current source's barrier was introduced because the "NEEDED DIFFERS (P36 rung B tus10)" — the P36 campaign. Perhaps the barrier is genuinely needed and this is a WALL (cse-load-forward). But the brief wants me to try real C; if not possible, WALL with evidence.

Before giving up, consider the "do-while(0)" EBB split (C0535): cse1 works per extended basic block; a do-while(0) creates a new basic block boundary? Actually cse's basic blocks are from the CFG; a do-while(0) with a branch that is always... hmm, GCC may create a NOTE_INSN_LOOP_BEG and cse_check_loop_start, which splits the EBB and flushes the table? Let's check: cse.c `cse_check_loop_start` — it invalidates memory and resets the table at loop start? If a do-while(0) forces a loop-start note, cse would flush the load table, so the second load can't be forwarded!

The moves.md shows do-while(0) used to split cse1 EBB (C0535: "do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item"). And item 1 above used do-while to fix order.

So: wrap the first diff block (or the second x2 block) in do-while(0). If cse treats the loop start as a new EBB and invalidates memory, the load won't be forwarded. Let's test!

Try c1 = nopin with the x2 block wrapped:
```
    do {
        s32 x2 = *(s16 *)((s32)s0 + 0x2E);
        *(u16 *)((s32)s0 + 0xE) += (x2 << 6);
    } while (0);  // !FAKE: do-while
```
Or wrap the first diff block. Let's try both.

Actually cse_check_loop_start: at a loop start, cse saves the table and invalidates? Let me read.

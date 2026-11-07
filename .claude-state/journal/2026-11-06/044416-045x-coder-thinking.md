---
ts: 2026-11-06T11:44:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_P5M7x6jira2LEpWESmFz
---
The self-store survives (74/75 ins). cse doesn't delete it.

Hmm. So a store always emits code here.

Let me reconsider. Maybe the target's 2 loads don't need a memory invalidation. What if the second read is a *different* expression that cse can't equate — e.g., reading through a pointer variable loaded from memory? 

Wait, actually — let me reconsider the whole thing. What if the target's second load comes from the *pinned* `bb` variable? In the target, `bb` is pinned $3 (v1). The first load goes into v1. Then `lo = bb & 0xFF` → andi a0,v1,0xff; `hi = bb >> 8` → srl v0,v1,0x8. The second read `*(u16 *)(p + 0xAE)` — cse would replace it with v1 (bb). But the pin makes bb a hard reg v1, which is clobbered by the ratan2 call at 3304! The second read's value is used as call args before the call... hmm, but cse's substitution: it would replace the second load with v1 only if v1 still holds it. Between the compare and the call, v1 is... at 32e8 `srl v0,v1,0x8` uses v1; then beq; then at 32f4 the reload.

Wait — maybe cse does NOT forward because the pinned bb (v1) is a hard register and the call clobbers it? No, the read is before the call.

Hmm, but cse's invalidate_for_call is at the CALL_INSN. The second load is before it.

Hmm, but hold on: in the target, the load at 32f0 is in the same basic block, before the call. cse would have v1 = (mem p+0xAE). It would replace the load with v1 if v1 is still live and unmodified. v1 is not modified between. So cse WOULD forward... unless the memory entry was invalidated.

Unless the pinned variable makes cse treat it differently: a hard-reg variable's value... cse records `(reg v1) = (mem ...)`. Then the second load `(mem ...)` is looked up → found equivalent to v1 → replaced. So it would forward.

So the barrier IS needed for the reload.

OK so we need a memory clobber in real C. The only real-C memory clobbers are calls (non-const) and stores. A call adds a call insn. A store adds a store insn.

UNLESS: the store is to a location whose value is provably dead AND flow deletes it. flow didn't delete the stack store. What about a store to a *pseudo* (a local variable that's never read)? That's the same stack store.

Hmm, what about a store that cse deletes because the value is already there? We saw self-stores survive.

What about a store that combine/flow deletes? The store `sh v1,16(sp)` survived. Hmm.

Wait — maybe the target's original C had a real store that IS in the output, and the barrier was only for... no, the target's code has no store before.

Alternative: a *call* whose result is used but which the compiler turns into... no.

Hmm, wait. What about `alloca`? no.

What about making the second read happen after the ratan2 call? Restructure: 
```
sVar4 = ratan2(a, b);   // uses the reloaded value?
```
No.

Let me reconsider: maybe there's another way to make cse not record the first load: make the first load's MEM `do_not_record` — i.e., volatile or... `do_not_record` is set for volatile MEM, and for `RTX_UNCHANGING_P`? Let me check lines 1900-1980: hash_rtx sets do_not_record for volatile; also for ASM_OPERANDS, and for `MEM` with `MEM_VOLATILE_P`. What else? Let me look at 1940-1980.

Also `cse_insn` sets `sets[i].src_volatile = do_not_record` when the source is volatile. A volatile load is not recorded → the second load is a fresh load! And volatile doesn't change the emitted code (same lhu). But volatile is a lever (new kind). Hmm, is it? The brief's kinds list: barrier, launder. A volatile qualifier is a real C qualifier, but it's clearly a "barrier" kind lever. It'd be a new lever of kind barrier. Prohibited.

Hmm.

Wait, maybe there's a legitimate real-C reason for the second load: if the first read and second read are of *different* objects that alias, cse's memory entry for one doesn't cover the other. What if the first read is `*(u16 *)(p + 0xAE)` and the second is `*(u16 *)((s32)p + 0xAE)` — same.

What if the second read is through a *different base variable with a different type*, e.g. `u8 *bp = (u8 *)p; ... *(u16 *)(bp + 0xAE)`? cse substitutes bp = p (copy). Same.

What if bp is `volatile`? lever.

What if the second read is `((u16 *)p)[0x57]`? 0x57*2 = 0xAE. cse canonicalizes to the same address.

What if the first read uses a *different offset arithmetic*: `*(u16 *)(p + 0xAF - 1)` → folds.

OK, what about making the second read a *different mode* but still lhu? The mode of the MEM is HImode regardless of signedness. Same.

Hmm, what if the first read is of a *32-bit* value and then masked? `u32 v = *(u32*)(p + 0xAC); bb = v >> 16;` — that's a lw, different code.

What if the first read is `*(u16 *)(p + 0xAE)` and the second is `*(u16 *)(p + 0xAE)` but through an lvalue of a union member with a different mode... no.

OK, let me look at this from a totally different angle: maybe the double load in the target comes from the *launder*, not the barrier, and the barrier's role is something else. Let me test: remove the barrier (d1) = 23, 75 ins. Let me check d1's disassembly — how many loads? 75 ins. Let me look.

Actually, I realize I should check whether d1 has 2 loads. If d1 (barrier removed) has 1 load, then the barrier is the reload cause. Let me verify with --keep.

Actually, let me instead consider a cheaper approach: maybe I can make the target's structure arise from a *function call* that the compiler doesn't inline. Wait — what about the `D_80188614[...]` indirect call in the 0x41 arm? It's a call. If the second load were after it... no.

Hmm, let me look at the C again:
```
case 0x53:
case 0x73:
    {
        ...
        bb = *(u16 *)(p + 0xAE);
        lo = bb & 0xFF;
        if (lo != c80 || (hi = bb >> 8) != 0x80) {
            sVar4 = ratan2(...);
```
What if I move the `bb` read *into* the condition? `if ((*(u16*)(p+0xAE) & 0xFF) != c80 || ((*(u16*)(p+0xAE) >> 8) = ...)` no.

What if the two reads are naturally separate because the first one is `bb` (pinned $3) and cse can't substitute a hard-reg because of... hmm, but it can.

Let me actually test the hypothesis that the barrier is the reload cause by checking d1's load count. Let me disassemble d1.

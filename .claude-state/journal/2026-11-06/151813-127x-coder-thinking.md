---
ts: 2026-11-06T22:18:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EvKzTqmESg0DXv2SYUyi
---
The glob p*.c also matched prev_win.c (which scores 0 — it's the pinned original!). The best permutation is p20 = 10. So no permutation reaches 0. (And I must be careful: prev_win.c is not lever-free.)

So the constant-pair ORDER residual (3) persists. i2/o4 = 3 is the best lever-free.

Let me try one more idea: since the constant is used in both stores, maybe compute the second store's low part from a different expression that doesn't reuse the same constant, forcing a second materialization at a different time. E.g., in the otp store, write `((u32)pkt & 0xFFFFFF)` vs `((u32)pkt % 0x1000000)`. That would create a separate constant qty maybe scheduled differently. But the target has one `lui a1` pair used twice (both ands use a1). If we split the constants, we'd get two materializations → extra insns → mismatch.

Alternatively, delay the mask by making it depend on `otp`: e.g., `(*otp & 0xFF000000) | ((u32)pkt & ~(*otp & 0xFF000000))` — wrong semantics.

Hmm, what about the C0414 dead-reset trick: add `m24 = 0;` after use to break cse? That would add a dead store deleted by flow; but the constant's materialization position is a sched1 matter, not cse.

Actually — maybe the issue is the *EBB split* itself. In i2, the do-while splits the block; sched1 schedules each EBB. The mask's birth is in EBB1 (used by the packet store). The target (pinned) had a different EBB structure (the pins don't split EBBs). So the mask's schedule in the target came from the *unsplit* EBB, while i2's comes from EBB1.

But v0 (unsplit) had the mask at the target's position (no mask mismatch in v0's diff!) but the register swap. So:
- v0: mask correct, registers wrong (13).
- i2: registers correct, mask 3 off (3).

Can we get both? We need the EBB split for local-alloc but not affect the mask's schedule. The do-while splits for sched1 too. Is there a splitter that affects local-alloc but not sched1? Hmm.

Actually, does the do-while split for local-alloc or for sched1? Local-alloc allocates per basic block. The do-while creates a NOTE_INSN_LOOP_BEG/END but does it create a new basic block? A `do{}while(0)` compiles to a loop with a single iteration; expand may emit a jump. If it creates a basic block boundary, local-alloc allocates the parts separately.

The mask schedule difference: in i2, the mask is in the EBB before the loop; the loop boundary might have changed the *order* of the sxy insns relative to the mask.

What if we use a different construct that splits the block at the same place but doesn't create a loop: e.g., a label + goto? A `goto` to the next statement creates a basic block boundary (LABEL_REF). E.g.:
```
    goto Lskip;
Lskip:
    otp = ...;
    *otp = ...;
```
A label creates a basic block boundary in flow/sched1? A label with a jump to it creates a new block. But an unconditional goto to the immediately following label might be optimized away by jump.

Or use an `if (x) {...}` with a condition that's a variable known nonzero? Not guaranteed.

Alternatively, use a `switch` with one case? Creates a jump table/branch → extra insns.

What about a `for (;;) { ...; break; }`? Similar to do-while.

Hmm, what about splitting with a label used by a `goto` from elsewhere (a real branch)? The code has early returns, not gotos.

What if we add a `goto` that jump-optimizes into the same structure but leaves a block boundary? Unlikely.

OK, alternative: accept 3? A score of 3 is not 0. But maybe I can fix the mask by adjusting the *packet store* expression order to change the constant's first-use UID. Let me try moving the packet store's mask to a variable computed after the otp address:
```
oidx = ...;
otp = ...;   // move the address computation BEFORE the packet store
*(u32*)pkt = ...;
*otp = ...;
```
That changes the instruction order (the target computes otp after the packet store). But maybe sched1 reorders it back? The otp address is used at the end; sched1 could keep the packet store first. Let me test: move the `otp = ...` line before the packet store (inside/outside the do-while).

Actually j2 wrapped oidx+otp+store and got 13. Let me try moving the otp assignment before the packet store while keeping the do-while around the store:
```
oidx = ...;
otp = ...;
do { *(u32*)pkt = ...; } while(0);
*otp = ...;
```
This gives the otp address early (its insns might move), changing the mask's schedule. Test.

Also:
```
oidx = ...;
do { otp = ...; } while(0);
*(u32*)pkt = ...;
*otp = ...;
```

Let me try a few.

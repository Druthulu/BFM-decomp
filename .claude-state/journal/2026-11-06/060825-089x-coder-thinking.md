---
ts: 2026-11-06T13:08:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3TQCXIAf11r0dQrgCc1U
---
Mine:
```
64 jal rand
65 sb s0,258(s1)     <- delay slot
66 andi v0,v0,0x1
67 andi s0,s0,0xff
68 slt
```
Target:
```
64 sb s0,258(s1)
65 jal rand
66 andi s0,s0,0xff   <- delay slot
```

So in mine, dbr put the `sb` into the jal's delay slot and moved the andi after. In the target, the sb is before the jal and the andi is in the slot.

To get the target: the sb must be *before* the jal in the RTL, and the andi must be the insn right after the jal.

In source: `CAST_WIDTH(u8, arg0, 0x102) = c;` then `if (((rand() & 1) < (c & 0xff)))`. So the sb is already before the call in source. The scheduler (sched2/dbr) moved the sb into the delay slot.

Hmm: mine has sb in the delay slot, meaning reorg chose it. The target has the sb before the jal.

What if I make the store's address depend on the call result? No.

What if I put the store and the compare closer/farther?

Idea: compute the andi *before* the store: `u8 m = c & 0xff; store; if (rand()&1 < m)` — then the andi is before the store (target has it after). No.

Idea: make the store depend on the andi: e.g. `CAST_WIDTH(u8, arg0, 0x102) = c;` and then `if ((rand() & 1) < CAST_WIDTH(u8, arg0, 0x102))` — a reload, wrong.

Idea: make the compare's `c & 0xff` use a value that is the *stored* value, e.g.:
```
u8 c = ...;   // u8
store c;
if (rand()&1 < c)   // no andi needed -> a4 = 12
```
Target needs the andi.

Idea: keep `s32 c` and write the compare as `(c & 0xff)`, but insert a *dependency* between the store and the andi so sched can't reorder: e.g. `CAST_WIDTH(u8, arg0, 0x102) = c;` then `if (rand()&1 < (CAST_WIDTH(u8, arg0, 0x102) - 0 + ...))` no.

Hmm, what about: the store must be *before* the jal in the target. In mine, dbr moved the sb into the jal's delay slot (which is legal). To prevent, the sb must not be eligible — e.g. if the sb's address register were clobbered... 

Idea: make the store's value a *separate* pseudo from the compare's operand so the scheduler's ordering changes. E.g.:
```
s32 c = ... + 1;
CAST_WIDTH(u8, arg0, 0x102) = c;
if ((((s32(*)())rand)() & 1) < (c & 0xff)) {
```
That's what we have.

What if the compare uses a *different* variable: `u8 cc = c; ... if (rand()&1 < cc)`? That's a2 (3).

What about changing the order of `rand()` and the andi in source: `s32 r = ((s32(*)())rand)();  if ((r & 1) < (c & 0xff))`? The jal would then be earlier.

Hmm, target: sb, jal, andi(delay), andi v0, slt. The `andi v0,v0,1` is after the call (v0 = result). So `rand() & 1` is computed after the call, as expected.

In mine: jal, sb(delay), andi v0, andi s0, slt.

The difference is only whether the sb goes in the delay slot or the andi does. reorg picks the insn from the *following* block for the delay slot. The sb is right after the call in RTL (source order: store, then call? no!).

Wait — in source, the store comes BEFORE the call. So RTL order: lbu, addiu, sb, jal. Then reorg moves the sb into the jal's delay slot? That's moving an insn from before the jal to after — that's `dbr`'s "fill from the preceding insn" (fill_simple_delay_slots moving an insn from before the branch to the delay slot). Yes, dbr does that when the insn can be moved down.

In the target, the sb stays before the jal and the andi (from after the call) goes into the slot. So the target's dbr filled from the *following* insn instead.

Why? Because the barrier (asm) was between the store and the call in the source: `store; asm; if (rand()...)`. Hmm, the asm is between the store and the call → dbr can't move the sb past the asm → so it fills with the andi from after.

So: I need a barrier-ish thing between the store and the call... or make the sb unmovable into the delay slot.

What makes an insn ineligible for a delay slot? `eligible_for_delay` in mips.md checks: not a jump/branch/call, and (I think) for stores it's allowed. But reorg's `fill_simple_delay_slots` for a call: it tries to fill from the insns *after* the call (the "next insn" path) and also from before via `fill_eager_delay_slots`? For a `jal`, the delay slot insn executes before the call; moving an insn from before the call to the delay slot is valid.

Hmm, the target's dbr chose the andi. Mine chose the sb. The difference: the barrier prevented the sb from being a candidate.

Real-C alternative: make the store's value depend on something so it can't be moved? No.

What if I put a *real* statement between the store and the call that becomes an insn and sits in the delay slot? Then the andi wouldn't be in the slot.

Hmm, target's delay slot = andi s0,s0,0xff. 

What if the source computes the mask BEFORE the call: `s32 m = c & 0xff; store; if (rand()&1 < m)`. Then RTL: andi, sb, jal, andi v0, slt. dbr might move the sb into the slot still, or the m-andi (which is before). Target has andi in the slot and sb before the jal.

Actually, if I write:
```
u8 m = c;             // andi
store c;
if (rand()&1 < m)
```
then RTL: andi, sb, jal. dbr would fill the slot with the sb (moving it after) or... The target has sb before jal. Hmm.

What if I write:
```
s32 m;
store c;
m = c & 0xff;
if (rand()&1 < m)
```
Then RTL: sb, andi, jal. The target: sb, jal, andi. dbr moved the andi INTO the delay slot (from after). That matches if the source order is sb, andi, jal!

Wait — target: sb at 64, jal at 65, andi at 66 (delay slot). The andi is in the delay slot, i.e. it executes before the call. If the source is `store; m = c & 0xff; if (rand()&1 < m)`, the RTL order is sb, andi, jal, and dbr could keep it as sb, andi-in-slot, jal. That's exactly the target!

So the move: compute the mask as a separate statement between the store and the call. Let me try:

```
CAST_WIDTH(u8, arg0, 0x102) = c;
if ((((s32(*)())rand)() & 1) < (c & 0xff)) {
```
→
```
s32 m;
CAST_WIDTH(u8, arg0, 0x102) = c;
m = c & 0xff;
if ((((s32(*)())rand)() & 1) < m) {
```

The andi would be a separate insn born right after the sb. dbr fills the jal's delay slot with it. 

Let me try that plus variants.

Similarly for item 5 later.

Let me test.

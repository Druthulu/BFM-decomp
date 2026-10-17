---
ts: 2026-10-17T16:51:11.643Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm recognizing this as the classic compiler pattern for decrementing a struct field guarded by a nonzero check — loading the halfword, branching if zero, then subtracting one, consistent with code like `if (x->a != 0) x->a--;`.

For the second case, I'm considering whether the delay-slot move comes from the taken or fallthrough branch, since MIPS instruction reordering can pull a safe instruction from either side when the register is dead on the other path. That points toward a structure like `s16 v = *(s16*)(arg0+0x10A); if (v != 0) { ... }`, where the conditional body manipulates that same field.

I'm also working out why `v1 = v0 + $0` becomes a real move instruction rather than being simplified away: since the hardware zero register isn't treated as a constant in RTL, CSE and combine don't collapse the addition with zero, so it survives as a genuine `addu` copy. This suggests the original source has an actual explicit assignment generating that copy, not just an optimizer artifact.

I should instead trace the actual RTL rather than keep guessing — maybe the pattern is a signed 16-bit field being read, decremented, and stored back, with the sign-extension happening through a separate copy. Let me try writing out a few candidate source variants, like using a separate s16 local variable for the field, and see which one reproduces the register reuse pattern.

I recall there's a gcc2 quirk where copies survive when source and destination have different promoted modes, like a short variable promoted to int. I should just try a few variants empirically and write a generator to test them systematically.

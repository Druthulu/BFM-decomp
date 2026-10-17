---
ts: 2026-10-17T11:38:23.459Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm realizing the key issue is that gcc keeps the base address in a register s2 rather than folding it into symbol constants, since all accesses are offsets from that register. I need to figure out what C pattern would make gcc hold the symbol address in a register like this, likely because the address is reused across multiple accesses.

Actually cse's find_best_addr can swap a constant symbol address for a cheaper register+offset form, so the compiler kept &D_8011F7F0 itself in s2, not &arr — meaning the base symbol is a different struct, with the observed fields sitting at negative offsets from it. That suggests the real layout might be an array where s2 points to a later element, like `&array[1]`, and the negative offsets reach back into earlier elements.

For a constant address to stay in a register instead of being folded, the base itself can't be a known compile-time constant — it would need to come from something like a pointer load. But since the target uses lui/addiu, cse must be treating the symbolic constant as cheaper than a register-plus-offset form, or vice versa, depending on how find_best_addr in cse.c weighs symbolic addresses against register-relative ones on MIPS.

I'm trying to figure out what source pattern makes gcc emit `addiu v0, s2, -72` (base computed from a register) versus `lui/addiu` for a pure constant. Maybe the original code computes an address like `&D_8011F7A8[index]` where the index itself isn't a simple constant, forcing the compiler to keep the base in a register rather than folding it entirely.

Given limited time, I'll test a couple of cheap variants directly: declaring the array as an extern global and setting base to arr plus an offset, or using a struct pointer with fields at specific offsets, to see which produces the matching instruction pattern.

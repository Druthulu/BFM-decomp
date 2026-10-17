---
ts: 2026-10-17T13:49:14.600Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
With pin5 and the launder resolved against s2/b, I still need to handle pin4, likely combining s2/b with direct calls at count 9. Now I'm thinking through the trickier case of scopes pinned to $a0, where the address needs to be loaded fresh each call — considering passing the shared address with differing param types, or splitting the pair into separate calls, and also checking what func_8004914C returns.

I'm wondering whether its return value feeds into anything, but it's declared void, so that's not it. Another angle: maybe CSE's substitution breaks if the pseudo holding the symbol gets invalidated between calls, such as if a user variable pointing to the address gets reassigned afterward — though that seems to mirror the same pattern already ruled out. I'm also considering whether the symbol address includes an offset, like a base plus some fixed displacement, and whether two different symbol/offset combos could still produce matching bytes after relocation, depending on how the linker treats the whole object during comparison.

Thinking more concretely about gcc 2.7's cse_insn logic for MIPS: when CSE evaluates the cost of a symbol constant versus keeping it in a register, the constant cost model and invalidation rules around CALL_INSNs become relevant, but it's unclear if that alone breaks the equivalence. I'm also considering whether a jump-following optimization or a conditional that later gets folded away (post-CSE, during jump passes) could effectively split the two calls into separate basic blocks for CSE purposes.

Stepping back, I wonder if the two calls actually used different hard register arguments originally, possibly matching Psy-Q GTE macros like SetRotMatrix/SetTransMatrix rather than general function calls, which would explain the pattern without needing CSE to do anything unusual.

Maybe the first call lacks a prototype entirely, so argument promotion differs and the compiler treats it differently for CSE purposes. Or maybe the register crossing happens because the call sequence itself introduces a side effect — like if the address is passed through a volatile cast, making it not memory-equivalent for CSE to collapse across the call boundary.

Maybe two different symbols pointing to the same linked address could explain the identical bytes — but that seems unlikely since the ROM bytes would differ unless both resolved to the exact same address after linking. With about 30 minutes left for S08, I think it's worth testing this double-symbol theory directly.

I'm also considering whether a CSE-defeating structure could be at play: if the compiler evaluates a condition that CSE later folds to a constant true, the jump itself might get eliminated before the label does, since CSE computes block boundaries early and only removes the label afterward if it becomes unreferenced. That could explain the surviving label despite the condition being provably true.

I should also check if the two calls actually take addresses of different struct fields, like separate matrix setters, and look at sibling source files for comparable patterns involving pinned `$a0` scopes to see if this case matches a known idiom.

Reusing `av` as the volume result eliminates both `pin $5` and the launder, scoring 0, leaving only `pin $4`. Next I'll check how other lever-free bodies call that pair.

---
ts: 2026-10-17T12:34:14.533Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm trying the h2=25 mismatch and abandoning that path, then exploring whether a switch-with-single-default or a genuine if-construct could create an EBB boundary that disappears before scheduling to get a cse-opaque base.

I'm now considering that cse flushes its hash table every 1000 instructions, which wouldn't apply here since the function is small, and also wondering whether a base derived from a call's return value, a wider-mode pseudo, or an extern struct pointer could evade cse's equivalence tracking.

Thinking about which hash-table entries cse actually records — a base register holding a symbol_ref gets folded through subsequent plus operations, but if that base is stored across mode boundaries, like a short or a 64-bit value truncated down to 32 bits, the constant equivalence might not survive the subreg lookup, potentially leaving extra instructions that get optimized away inconsistently.

I'm wondering if this is a "lever" since it doesn't match the known forbidden patterns, though an identity cast through a wider type feels suspiciously similar to the forbidden identity-expression case. Trying to reconstruct genuine original source, I'm considering whether the structure accessed is actually a 16-byte light struct with position fields and color bytes, which would explain the exact byte offsets being referenced.

Working through the byte layout, I'm matching fields vx, vy, vz, r, g, b against a GsF_LIGHT struct and confirming the function call passes light index and address to a flat-light setter, meaning the array is likely three such light structs. I'm puzzled why some fields are stored through a register-relative pattern while others use absolute addressing within the same block, and testing the theory that the original source simply assigned each field directly before calling the setter function, with the compiler choosing different addressing modes for different fields of the same struct.

I can't pin down the original spelling for sure, so I need to look elsewhere—maybe at where the target's load-address instructions and stack stores are ordered relative to the first call argument setup, since the prologue scheduling in gcc 2.7.2 for MIPS might explain the difference in instruction order between my version and the target.

I'm wondering if this is really about sched1 versus sched2 behavior: in the target, the base register must have been unknown to the first scheduling pass, while cse never attached a REG_EQUAL note to a constant source, which would change how later passes treat that pseudo.

I'm also considering whether cse simply skipped the insn entirely — maybe it's inside a block cse doesn't traverse, or loop invariant hoisting moved it without copying over equivalence notes. Another possibility is that the insn containing the base computation isn't a simple single set that cse recognizes — if it's a PARALLEL with multiple sets or has a CLOBBER, cse's requirement of exactly one set wouldn't hold, so the equivalence would never be recorded, pointing me toward checking local-alloc's REG_EQUIV handling next.

CLOBBER rtxes also trigger mark_set_1, incrementing reg_n_sets for pseudos. I'm now tracing where expand emits clobbers before setting a pseudo piecewise — likely multiword DImode assembly or structure-returning expansion, where a target register gets clobbered then filled piece by piece.

But for a simple pseudo holding a full-width union/struct field, storing the whole word is just a single move with no clobber, so that path wouldn't double-count n_sets — I need to find a case with partial-field stores or multiword emission instead.

With a two-field struct in DImode, setting the pointer field becomes a store into a SImode subreg of the DImode pseudo. CSE's handling of subreg destinations is special — it only records an equivalence for the subreg under certain conditions — and once the DImode pseudo gets allocated to two hard registers, that subreg field access could interact with reload or clobber tracking in a way that produces the extra set.

I'm also checking whether cse tracks equivalences for a SUBREG destination differently than a plain REG destination, since that affects whether sched and cse can both reason about the base address correctly. If subreg-set bases aren't recorded, cse's fold_rtx might still resolve the SUBREG expression through its hash table, though this needs testing — and I'm wondering if using a smaller SImode-sized struct instead of a DImode pair avoids the register-pair prologue mismatch entirely.

Maybe an 8-byte struct local gets placed in a DImode pseudo instead of memory, depending on alignment rules. Another possibility is a `long long` variable holding a sign-extended pointer value, where the extension gets expanded into separate low/high subreg sets with a clobber, and the dead high half could get deleted by flow analysis later.

Flow can't tell partial liveness of a DI pseudo though—a subreg set is only dead if the whole register is dead, so that sign-extension insn probably survives. If I instead model it as a struct with one field actually used, the pseudo would still get allocated as a register pair, and the prologue's regs_ever_live check would force both registers saved regardless. I'm now wondering whether forcing a second set via an extra CLOBBER changes flow's dead-code count enough to avoid this.

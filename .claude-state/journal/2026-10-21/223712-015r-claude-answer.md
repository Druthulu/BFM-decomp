---
ts: 2026-10-22T04:37:12.103Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: afdda1e6f94a02c83
model: claude-opus-5-5[1m]
effort: medium
turnId: cd022f12-1132-4c64-8c07-d6fff960e650
usage: {input: 10, cacheRead: 430707, cacheWrite: 2379, output: 1048}
---

Yes, m2c was our main first-draft tool all through matching, and it's still a submodule at `tools/m2c`. It just doesn't help T11.

**How we used it.** `tools/decompile.py` runs m2c on a function's disassembly to produce a C draft, optionally given our existing types so its output uses them. Agents started from that draft, or from Ghidra's output if that was closer. Then they edited it until the compiled bytes matched. About ten other tools also call it, including the declaration repair and signature tools.

**"Perfect C for small functions" is half true.** On short, simple functions m2c's draft often matches as-is or after small tweaks. But as functions grow, its drafts drift further from the original. We measured this when building the actor struct (`docs/actor-struct.md`): on functions m2c got structurally wrong, 50 to 98% of the instructions mismatched. Giving it the real struct changed nothing (0 better, 10 the same, 2 worse), because those misses are limits of the decompiler itself, not missing types. It also often drops function arguments. That's partly why T7 found so many pins were really missing parameters.

**Why it can't do T11's work.** Every function in T11 already has correct C that matches. What's left is the last step: getting the same bytes without a pin or barrier. That depends on how gcc 2.7.2 picks registers and orders code. m2c reads the assembly and writes C that means the same thing. It doesn't try spellings and compile them against the target bytes, which is what the coders do. A fresh m2c draft would typically land back at the same wall, or further from it.

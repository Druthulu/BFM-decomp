---
ts: 2026-10-17T13:54:04.831Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2ab9a444ea3aa2ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd53509-0294-4563-a878-c510da735377
---
I'm reconsidering why the field load got reloaded — the store to the struct offset likely invalidated cached memory references with matching or varying addresses, forcing the compiler to re-fetch the field rather than reuse the earlier loaded value.

I'm now puzzling over why the D pointer symbol wasn't similarly invalidated: unless its address is somehow treated as non-constant to CSE (perhaps loaded through an intermediate register rather than a direct symbol reference), the symbol-based memory access should be considered address-invariant. I suspect the actual RTL represents the D address as a split high/low pair where the register holding the high part gets treated differently during CSE analysis.

I'll settle for best 11 on S11 (removing the a1 solo) and spend about 12 minutes on it, then move on to S15.

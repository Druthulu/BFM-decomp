---
ts: 2026-10-17T10:34:28.245Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: 50f5af05-e353-44b9-ba7b-703e4f789154
---
I'm tracing register usage differences between my disassembly and the target—block 2's load register and the subu operand reuse look like the main divergence, though most of the tail lines now line up except for one register mismatch at line 56.

Local allocation runs before global allocation, so e2 likely got v0 locally since it's confined to the tail block, while d/diff got a0 through global allocation. I'm testing whether making e2 reuse the pseudo for `a` (which is already global and maps to a0 in the target) would fix the mismatch, since both variables are s32 and could plausibly share a register.

I also notice block 2 scheduling differs — the D load gets hoisted earlier in mine than in the target. This is likely because in the target, v1 is still busy with a sign-extension operation until later, blocking the hoist, whereas in mine the load landed in a1 which was free to move up. That suggests the D load, being a global value used across branches, should actually be assigned v1 instead.

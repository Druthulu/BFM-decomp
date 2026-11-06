---
ts: 2026-10-22T20:52:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xLzT5eqsHMWN2I1cSsaZ
---
gen_o3 has u16 ay, u16 bx; gen_n1 has u32 ay, u32 bx plus `by = (u16)by;`.

The residual in gen_o3: the ORDER of `addiu s4,s2,-93` (by = bx - 0x5D) and `addiu s1,s1,117` (ay += 0x75) relative to other insns. Specifically:
- mine has addiu s4,s2,-93 at insn 73; target at 72.
- mine has addiu s1,s1,117 at 75; target at 79.

So in the target, `by = bx - 0x5D` comes *earlier* and `ay += 0x75` *later*. This is a scheduling (sched1) ordering within the block. The source order is:
```
bx = out.vy;
ay = out.vx;
by = bx - 0x5D;
ax = ay + 0x7B;
bx = bx - 0x57;
{ op launder }
ay = ay + 0x75;
prim.x0 = ay; ...
```
The target wants by's addiu earlier and ay's later.

Since sched1 decides, the lever-free fix is a source reorder. But the prior coder already tried gen_o1..o4 (order variants?) and gen_* variants.

Let me see the target's insns 60-90 and mine's to understand the order. Let me print both disassemblies around there. The target.txt has the target; let me generate the candidate's disasm and compare with awk. Actually dt.sh's diff tells me the positions. Let me view the target lines 60-90 from target.txt and the candidate's from cand.sh.

target.txt line numbers correspond to insns? It's the disassembly with 238 lines for 207 insns (relocations add lines). Let me just look at the target's block.

---
ts: 2026-10-22T21:13:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hHU0dyPltvSlKPtZYmw2
---
Let me disassemble both the candidate object and the target build object for the function. The target build object: build/... let's find it.

Actually, this is a lot of setup for one item. Time budget: 20-30 min per item, 5 items. Let me be efficient: I mostly need to reason about the crack, and the dt.sh diff tells me the score. I can iterate with candidate bodies and dt.sh output (tail 30 gives me the diff detail). That's enough.

For this item, hypothesis: cross-jump merges arm3's tail with arm1's. Wait — look at the diff again: mine[47] is `bnez v0,14a0` where target has `beqz v0,146c`. So the branch at 47 differs: mine's third arm test branches differently.

Let's reconstruct: the if-chain. Conditions:
- cond1: (u16)(v0-0x2C1)<0x2BF && v1>=-0x35F && (u16)(v2-0x581)<0x77F
- cond2: (u16)((u16)v0+0x5FF)<0x5FF && (u16)(v2-0x681)<0x3FC
- cond3: v2 < 0x380

Arm1 body: unk20=0x71, unk22=0x600, unk24=0, unk2E=0, unk30=-0x50
Arm2 body: unk20=0x2AA, unk22=0x800, ...
Arm3 body: unk20=0x71, unk22=0x600, unk24=0, unk2E=0, unk30=k(-0x50)
Arm4 body: unk20=0x2AA, unk22=0x600, unk24=0, unk2E=0, unk30=0

So arm1 == arm3 exactly. Cross-jump merges them: the target (ROM) has both.

Actually in mine: the `beqz v0,14a0` at 47 — after cond3's test (v2<0x380), if true branch to arm3, else fall to arm4. In mine arm3's tail is merged so it jumps to the shared block.

The clean plain-C fix: make arm3's stores differ in RTL from arm1's. Options that keep the same instructions:

Option A: In arm3, use `k` for other stores too? No, changes.

Option B: In arm1, replace `= -0x50` with a literal expression that isn't a plain constant... e.g. `= k2` where k2 is another variable set to -0x50. But then arm1's RTL differs from arm3's — cross-jump won't merge; but the target's arm1 also must produce the same insns.

Hmm, but actually a cleaner idea: since arm1 and arm3 are identical, why did the ROM keep them separate? Because the original source probably had the barrier... no, the ROM is compiled from the original game source which had no asm. So the original source must have had something that makes them differ — e.g. the arm3 store is `unk30 = -0x50;` but with different spelling, or the arms have different statement order in the original.

Look at the target: arm3 has li v0,-80 at slot 52 (before sh zero,36 and sh zero,46) — that's scheduling. What does arm1 look like in the target? Let me get the target disassembly to see the whole thing. I'll disassemble the build object.

Let me find build object.

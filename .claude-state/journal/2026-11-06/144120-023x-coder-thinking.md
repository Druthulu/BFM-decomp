---
ts: 2026-11-06T21:41:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Z1AADMHaE27lOSn8hY82
---
The target is the tree's own bytes under build/. I can find the built object for the TU. But maybe easier: use the objdump of target from the tool. Let me look at line ~780-800 and the oracle for how target is read; but rather than reading whole tool, I can run `tools/cc1_dumps_tu.sh`? That's for dumps.

Alternative plan: reason about qty priority. The two qtys in question:
- oidx = g.otz << 2 (SImode), refs: used in two index expressions → but each use is `oidx + (tag<<14)`. In RTL, the address computation may fold: `addu v0, oidx_reg, tag_reg`. So oidx referenced twice? In mine, oidx is a0 at 163-168 (lw a0,20(sp); sll a0,a0,2; addu v0,a0,v0) and then at 182 addu a0,a0,v0? Wait mine 182-184: addu a0,a0,v0; addu a0,a0,v1; lw v0,0(a0). Here a0 is the base address D_800A6614 (lui a0/addiu a0 at 176-177), v0 is tag<<14? Hmm.

Let me reconstruct mine tail from the diff:
- 159: lw v1,0(a3)   [tag raw? no, this is base+0xA3D2 load? "lw" not "lhu"]
Hmm lw v1,0(a3): a3 could be pointer to D_800AF630? no.

I need the full listing. Let me objdump the candidate .o and get the target from build. Let me find the target object: search build/ for the TU object.

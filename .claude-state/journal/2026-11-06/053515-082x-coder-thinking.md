---
ts: 2026-11-06T12:35:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zg8TAKdzF8bGw2j0j2jT
---
Target 118-132:
```
118 beqz v0,b6c        ; if (arg1 & 1)
119 li v0,4095          ; delay slot: 0xFFF
120 lui v1,0x0          ; b4b = D_8017E918
121 lw v1,0(v1)
122 lui at,0x0          ; D_801152AA address
123 sh v0,0(at)         ; D_801152AA = 0xFFF
124 j b84
125 addiu v0,t4,2       ; var_v0_3 = pos + 2
126 lui v1,0x0          ; else arm
127 lw v1,0(v1)
128 li v0,-4095
129 lui at,0x0
130 sh v0,0(at)         ; D_801152AA = -0xFFF
131 addiu v0,t4,-2
132 sh v0,2(v1)         ; b4b[1] = var_v0_3  (in the else arm!)
```
So the target stores `b4b[1] = var_v0_3` inside the else arm (132) — no wait, 132 is after 131 (addiu v0,t4,-2) which is the else arm's value, so `sh v0,2(v1)` at 132 is the shared store placed in the else arm's tail (the join falls through).

In mine, the shared store is at a different place (130: sh a0,2(v1)).

So in mine, the store `b4b[1] = var_v0_3` got merged/placed differently. And mine is 154 ins (2 fewer) — the target has the D_801152AA store duplicated per arm? Both arms store `sh v0,0(at)` (123 and 130) — the target has it in both arms (2 stores). Mine apparently has 1 (moved to a join) → 1 insn fewer, and the `lui at,0x0` for the address also merged.

So the barriers' role: keep `D_801152AA = 0xFFF;` in its arm (prevent sinking/merging to a common tail). Real-C fix: hmm, the two stores have DIFFERENT values (0xFFF and -0xFFF) so they can't be merged into one store... but the *address* computation (lui at) can be merged, and the store can't move across arms.

Wait, if the stores have different values, they can't be merged. So what got merged? Let me look at mine's actual code. Let me dump mine (bb.c) around 110-135.

Let me get bb's object.

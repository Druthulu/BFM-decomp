---
ts: 2026-11-06T04:20:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5Ls2SAGJiRu2MbhOSxwD
---
The p register is a0 vs target v1 everywhere (all six stores). So the primary remaining difference is the register allocation of p: a0 vs v1. And the one reload position.

Why does target use v1 for p? Let me think about global_alloc priorities. The function has these pseudos: obj (s2), n/v/p, and the model pointer values. In target, `p` is v1. In mine, a0.

The target also uses v1 for the loop counter in the n<8 arm? No: target n<8 arm uses v1 for n (addiu v1,v0,1; sll v0,v1,1). Hmm, in target, v1 holds n in that arm. And p is also v1 (different arms, disjoint live ranges). So v1 is reused across arms.

In mine, p is a0; n is v1 in the n<8 arm? Mine's 48a8: sll v0,v1,0x1; addu a0,v0,v1 — wait mine uses v1 for n and a0 for the v computation. So in mine, p=a0 conflicts with the `v` temporary in the n<8 arm? They're in different arms, so no.

Global alloc: a0 is caller-saved and free; v1 is caller-saved too. The allocation order/priority decides. p's priority is based on refs and loop depth. 

In target, p gets v1; mine a0. Since both are caller-saved and neither is pinned, the difference is priority ordering relative to other pseudos. In mine, some other pseudo took v1 first, pushing p to a0. In target, v1 was free for p.

Which pseudo takes v1 in mine? In the `<0x11` arm, mine's v chain: sll v0,v1,0x1; addu v0,v0,v1; sll a0,v0,0x5 — here v1 = obj->1C value, v0 = v. a0 = v*32 (the second sll dest, because v's chain reuses v0 then a0?). Wait mine: `sll v0,v1,1` (v0 = x*2), `addu v0,v0,v1` (v0 = x*3), `sll a0,v0,5` (a0 = x*96) — so the multiply result is in a0, and then addiu a0,a0,1536; sh a0,24(a1). So mine uses a0 for the multiply result and a1 for p. Hmm, that was the earlier nopin. In w4, p is a0 (diff shows lw a0,32(s1); sh v0,26(a0)).

Let me disassemble w4 to see the `<0x11` arm registers.

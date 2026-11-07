---
ts: 2026-11-06T10:02:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qdTvxvMSoV7AWoys5gcc
---
Mine's case-1 loop at 2d74:
```
move a2,zero    ; ?
move a1,zero    ; f = 0
lui a0, D_801AECD8
...
2d88: (loop)
...
slti v0,a1,5
bnez v0,2d88
addiu a0,a0,4
```

Wait, this is the loop for case 0 (i0 counter), not case 1! Case 0's loop: `for (i0 = 0; i0 < 5; i0++) { if (...D_801AECD8[i0]...) c0++; }`. Mine at 2d74 has a2=0 (c0?), a1=0 (i0), a0=giv.

Target case 0 loop is at ~2d??. Hmm, the diff indices 132-153 correspond to case 1's loop (target 2ea4-2ee0). Let me look at mine around that address. Mine's case 1 loop should be near 2e?? too. Let me dump mine 2e90-2ee0.

Actually the diff shows mine[132] `move a1,zero` vs target[132] `move v1,zero` — at target address 2ea4 (`move v1,zero`). So mine at that point is `move a1,zero` (f=0), and mine[135] `lui v1,0; addiu v1,v1,0; lw v0,0(v1)` — so mine's giv is v1, f is a1. And i1 is a0 (both have `move a0,zero`? not in diff so same). So mine: f=a1, i1=a0, giv=v1. Target: f=v1, i1=a0, giv=a1.

So only f and giv swap: f should be v1, giv a1; mine has f a1, giv v1.

The keepalive added a ref to i1, which changed... hmm, the note says the counter gets $a0 (same in both) and the giv gets $a1. Without the keepalive, giv gets v1.

So we need the giv's priority to drop below f's? Or f's to rise? Global-alloc assigns caller-saved regs by priority. Currently f (a1) and giv (v1) — target wants f (v1) and giv (a1). Since a1 > v1 in the allocation order (global-alloc assigns in order of reg number? REG_ALLOC_ORDER). Let me check GCC 2.7.2 mips REG_ALLOC_ORDER: probably {2,3,4,5,...} v0,v1,a0,a1,... Hmm, if higher priority gets earlier regs, then giv has higher priority than f in mine (gets v1 which comes before a1). Target gives giv a1 and f v1, so in target giv has LOWER priority than f.

The keepalive adds refs to i1 (the counter), not the giv or f. How does that flip giv vs f? Because the giv is derived from i1 (`D_801AECD8[i1]`), strength reduction creates a giv pseudo; maybe the refs of i1 propagate to the giv? Hmm.

Alternatively, the note says the keepalive lifts the counter's priority above the giv's. That's about i1 vs giv. But target has i1 in a0 and giv in a1 — a0 is before a1, so i1 > giv. In mine, i1 is in a0 too... wait, mine has `move a0,zero` for i1? The diff didn't show mine[133] or [134], so they match: mine also has i1 in a0. Hmm, then i1 vs giv isn't the difference.

Wait, let me recheck. Mine: `move a1,zero` (f=0) at 2ea4-equivalent; then mine[135] lui v1 (giv base). But where's `move a0,zero` (i1=0)? In target it's at 2ea8. The diff replaces mine[132:133] and mine[135:138]; so mine[133], [134] match target[133], [134]. Target[133] = `move a0,zero`, target[134] = `li a2,5`. So mine also has `move a0,zero; li a2,5`. Good.

So mine: f=a1, i1=a0, giv=v1, limit a2=5.
Target: f=v1, i1=a0, giv=a1, limit a2=5.

So the swap is f vs giv: f should get the lower reg v1, giv the higher a1. In mine f gets a1 (higher) and giv v1 (lower).

Wait, which is "higher priority" in global-alloc? It assigns the highest-priority pseudo to the first available reg in REG_ALLOC_ORDER. Let me check the MIPS REG_ALLOC_ORDER in gcc-2.7.2. Let me grep.

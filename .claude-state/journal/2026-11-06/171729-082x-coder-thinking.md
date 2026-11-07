---
ts: 2026-11-07T00:17:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wZzfwjGl6gKhCZ6omxRm
---
Target registers:
- a0 (param) = s2
- tp = s3
- s4 (the `s4 = *(s32*)(a0+0x1C)` variable) = s4
- v1 (func result) = s0
- s1 (the `s1 = r2 - ...`) = s1
- r2/r3 etc = v0/v1/a0/a1 temps

Interesting: the variable named `s4` is in $s4, `s1` in $s1. So the decomp author named them after their registers.

So target: a0=s2, tp=s3, s4var=s4, v1var=s0, s1var=s1.

Mine: from the pairs (s1->s2 x4, s4->s3 x4, s2->s1 x3, s3->s4 x2): mine's s1=target's s2 (a0), mine's s4=target's s3 (tp), mine's s2=target's s1 (s1var), mine's s3=target's s4 (s4var).

So mine: a0=s1, tp=s4, s1var=s2, s4var=s3.
Target: a0=s2, tp=s3, s1var=s1, s4var=s4.

So it's two swaps: (s1,s2) and (s3,s4).

The pin forced tp=s3. Lever-free, tp=s4 (mine). And a0=s1 vs target s2, etc.

The allocation order (global): r78, r91, r85, r76(tp), r73, r72(a0?), r80, r75, r74.

Let me map:
- r74 (pri 212, refs 2, live 94, pointer, crosses 3 calls) = a0 (the parameter, live the whole function). 
- r76 (5714, refs 8, live 42, pointer, crosses 2) = tp.
- r72 (1428, refs 4, live 56, crosses 5) = s4var? or s1var?
- r80 (1428, refs 3, live 21, crosses 1) = ?
- r75 (606, refs 2, live 33, crosses 3) = ?

Target: a0=s2, tp=s3, s1var=s1, s4var=s4.

Hmm, so a0 (r74, last in order, pri 212) got s2. tp (r76) got s3.

If the order is 78,91,85,76,73,72,80,75,74 and callee-saved regs are assigned in that order... Let me think about which allocnos need callee-saved:
- r76 (tp): crosses 2 calls → callee-saved.
- r72: crosses 5 → callee-saved.
- r80: crosses 1 → callee-saved.
- r75: crosses 3 → callee-saved.
- r74 (a0): crosses 3 → callee-saved.
- r78: conflicts v0,sp; does it cross calls? Not stated → no. Can use v1/a*.
- r91: conflicts v0,sp, pref HI_REG → a constant, short.
- r85: prefers v0.
- r73: prefers a0.

So the callee-saved order: r76, r72, r80, r75, r74.

With 5 callee-saved allocnos and s0-s7 available (s0 is taken by v1var? no, v1var is local-alloc r? hmm).

Hmm, in the target: s0=v1var, s1=s1var, s2=a0, s3=tp, s4=s4var. So s0-s4 used.

v1var (r? local) got s0 via local-alloc. Then the globals: s1, s2, s3, s4.

Hmm, if local-alloc gave s0 to v1var, then the global order r76(tp), r72, r80, r75, r74 → s1, s2, s3, s4, s5?

Target: tp=s3. So tp is NOT first. Hmm.

Unless the global order differs in the target (pinned) body. With the pin, tp is a hard reg (not an allocno), so the order is r78, r91, r85, r73, r72, r80, r75, r74 → and the callee-saved: r72, r80, r75, r74 → s1, s2, s3, s4?

Hmm, target: s1=s1var, s2=a0, s3=tp(pinned), s4=s4var.
So r72→s1 (s1var), r80→s2 (a0)? But a0 is r74 (last). Hmm.

I'm confusing the mapping. Let me map by live lengths:
- a0: live 94 (the whole function) → r74 (live 94, pointer). ✓
- tp: live 42 → r76. ✓
- s4var: `s4 = *(s32*)(a0+0x1C)` — born early, used in `if (s4 & 1)` → live 56? → r72 (live 56).
- s1var: `s1 = r2 - (r2/256)*256` → live 33? → r75 (live 33).
- v1var: `v1 = func_8012913C(kind)` → live 21 → r80 (live 21)? But v1var is s0 in the target.

Hmm, v1var = s0. Is s0 from local-alloc? r80 is a global allocno (in the .greg order). Hmm.

Wait, maybe v1var is r80 (live 21, crosses 1 call) and got s0 via global-alloc? But s0 is usually taken by local-alloc first.

Hmm, let me look at the .lreg for the final assignment. Let me grep "Register N in".

Let me do it quickly.

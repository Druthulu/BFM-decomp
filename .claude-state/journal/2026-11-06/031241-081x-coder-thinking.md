---
ts: 2026-11-06T10:12:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qj07rcX2M3JTEiAxrfZD
---
In g1, r75 (s1ang) is now GLOBAL with pri 6363, refs 7, live 22. And r74 (d) pri 5185, refs 7, live 27. So s1ang (6363) > d (5185) → s1ang gets s0, d gets s1. STILL WRONG (we want d=s0).

Ah, because making s1ang global gave it MORE refs (7) → higher priority than d.

So the target wants d > s1ang. d's pri 5185. s1ang must have pri < 5185. In g1, s1ang got refs 7 (because it's used 5 times in later blocks) → 6363.

Hmm. So making s1ang global makes it outrank d.

For d to outrank s1ang: d pri 5185; s1ang must be < 5185. In the original (nopin), s1ang is local with pri 2857 (would be < d). If s1ang were global with pri < 5185...

s1ang global with refs 3 (load + andi + one use) and live ~20 → pri = 1*3/20 = 0.15 → 1500 < 5185. Then d gets s0! But s1ang would need to be used in a later block only once (refs 3), not 5.

Hmm, but the target's s1ang IS used multiple times (as u6). Unless s1ang and u6 are separate: s1ang (global, refs 3) and u6 (global, refs 5). Then s1ang pri ~1500 < d 5185 → d gets s0, then u6 (pri?) gets s1, s1ang... hmm, 3 callee-saved regs. But the target uses only s0, s1.

Wait, if s1ang and u6 are tied (same register, in-place andi), then they share. In g1, s1ang IS u6 (masked in place), refs 7.

Hmm, so the target's s1ang/u6 has refs... let me compute from the target asm: s1ang load (def), andi (use+def), subu (use), addiu +0x1000 (use), addiu -0x1000 (use), plus the bne (use) = ~6-7 refs. So global pri would be ~6000 > d 5185. That contradicts the target unless d's pri is higher.

d's pri 5185 (refs 7, live 27). For d to beat s1ang (6363), d's live length must be shorter: e.g., live 22 → 7*2.8/22 = 6363... Hmm, d refs 7 live 27 → floor_log2(7)=2, 2*7/27 = 0.5185 → 5185.

If d's live were 22 → 2*7/22 = 0.636 → 6363, tying s1ang. Tie-break: lower allocno number wins. d is r74, s1ang r75 → d wins (lower) → d gets s0! Interesting.

So if d's live length were 22 (instead of 27), d would tie/beat s1ang and get s0 (tie-break lower allocno).

Hmm, but that's in g1's structure (s1ang global). In the nopin, s1ang is local so it doesn't compete in global-alloc.

So there are two paths:
A) Keep s1ang local (nopin) and make local-alloc give it s1 — impossible without another local-crossing qty.
B) Make s1ang global (g1) and make d outrank it — need d's pri > s1ang's.

For B: in g1, d pri 5185, s1ang 6363. We need d > 6363. d's live = 27, refs 7. If we shorten d's live range to ~22, pri = 6363 (tie, d lower allocno wins). Or increase d's refs. 

But g1 also lost an instruction (74 vs 75). Let me figure out why. If I can fix g1's instruction loss AND adjust d's live range, we might get 0.

Actually, wait: in g1, the s1ang global has refs 7. But the target's `andi s1,s1,0xfff` is in-place, so s1ang and u6 are the same qty — consistent.

Let me look at g1's asm to find the missing instruction. Let me read the .s or the alloc's lreg. Actually, the score said 74 vs 75. Let me look at the g1 asm from the dump.

Let me grep the g1 .s for the function. The includer is ov_MAIN_012. Hmm, the function name in the .s might be mangled. Let me look at the .lreg or just use --keep on g1 and objdump.

Actually, simpler: use --try --keep on g1 and objdump.

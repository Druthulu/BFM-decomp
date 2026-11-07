---
ts: 2026-11-06T10:02:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1TdPqbbzOjqhBuGwRoeP
---
The .greg dump shows the RTL AFTER local allocation. Pseudos 74,76,77,78,80 are the globals. 74 conflicts with many (it's live across the call). 76 conflicts with 74,77,78,80,2,16,29. 77 prefers 16 (s0)! 78 prefers 3,5. 80 prefers 2 (v0).

The order: 78 80 79 77 76 74. So 78 first (gets first pick of callee-saved = s0?), then 80, 79, 77, 76, 74.

Hmm, but 79 has conflicts only 79,2,29,64,65,66 — it doesn't conflict with 74/76/77/78/80, so it can take any. 79 prefers 3,5 (caller-saved v1,a1). 

Wait, the callee-saved registers available are s0..s7 (16..23). The order assigns: 78 → s0? But 78 conflicts with 74,76,77 — and 74/76/77 come later. So 78 gets s0. Then 80 conflicts with 74,76 (and itself) — 80 gets s1? Then 79 conflicts with nothing among globals → s2? Then 77 conflicts with 74,76,78,80 → s3? Then 76 conflicts with 74,77,78,80 → s4? Then 74 conflicts with all → s5?

That doesn't match the target (s0 and s1 for d and s1ang).

Hmm wait, but the "Hard regs used: 2 3 4 5 16 17 31 64 65 66" — 16=s0, 17=s1 are used. So only s0 and s1 are used as callee-saved. But the order says 6 regs to allocate among the callee-saved bank. Yet only s0,s1 are used? The others (78,80,79,77) must have been allocated to caller-saved regs (they don't cross calls) — right! The .greg order lists all globals, but only those crossing calls MUST be callee-saved; others get caller-saved (v0,v1,a0,a1). The preferences guide.

So which of 74,76,77,78,80 cross the call? 74 conflicts with 4,5,2,3 (caller-saved) — hmm, conflicts with 2,3,4,5 means it can't use those? No: conflicts with hard regs 2,3,4,5 means those hard regs are live at the same time (because of other pseudos?). Hmm, actually the conflict list includes hard regs that the pseudo conflicts with.

Look: 74 conflicts: 74 76 77 78 80 2 3 4 5 16 29 64 65 66. So 74 conflicts with s0 (16)! That means s0 is live during 74's range — because some other pseudo is in s0. Hmm, but s0's occupant is a pseudo.

Wait, I think the .greg dump is AFTER local-alloc, so pseudos that got hard regs (like 75→16=s0) are shown as hard reg 16. "Register dispositions: ... 75 in 16 ..." — yes! Pseudo 75 was assigned s0 by local-alloc. And 74 conflicts with 16 (s0) because 75 (=s0) is live across 74's range.

Hmm, but 75 crosses a call? The alloc table said r75 crosses 1 call. If 75 crosses a call, local-alloc wouldn't assign it a callee-saved reg... actually local-alloc CAN assign a callee-saved register if the variable is live across a call? No — local-alloc only assigns registers that don't conflict with calls; if a pseudo crosses a call, local-alloc gives it a callee-saved register only if... Actually in gcc, local-alloc assigns caller-saved regs only for pseudos not live across calls; for those live across calls it uses callee-saved if possible (it knows which regs are clobbered).

So pseudo 75 got s0 from local-alloc. What is pseudo 75? "75 in 16" (s0). The alloc table row r75: hard s0, pri 2857, refs 2, live 7, crosses 1 call. So r75 is a pseudo that local-alloc put in s0. That's probably s1ang!

And r74 (d) is global with pri 5185, and it conflicts with 16 (s0 taken by r75) → must use s1 (17). That explains d→s1, s1ang→s0.

So the KEY: local-alloc assigns s1ang (r75) to s0 BEFORE global-alloc considers d (r74). To flip, we need local-alloc to NOT give s1ang s0, or to give s1ang s1.

Why does local-alloc give s1ang s0? Local-alloc's allocation order is by qty priority too. s1ang has refs 2, live 7. It gets s0 (the first callee-saved). Hmm.

Alternatively, make s1ang NOT cross a call (then local-alloc would give it a caller-saved reg like v1). But in the target, s1ang is in s1 (callee-saved) and IS live across the call.

Hmm wait — target: `lh s1,18(v0)` at 38f0 before jal, `andi s1,s1,0xfff` at 3908 after. So s1ang lives across the call, in s1 (callee-saved). And d in s0 (callee-saved).

So target: both in callee-saved, d in s0 (lower), s1ang in s1.

In the target's compilation (from the original source), how did this happen? The original source likely had a different structure. Our reconstructed source (with pin) forced d=s0.

To get d=s0 naturally: local-alloc must not take s0 for s1ang, OR s1ang must get s1.

Idea: Make s1ang's local-alloc priority lower than... hmm, local-alloc assigns in qty order; the first qty needing a callee-saved reg gets s0. If s1ang is the only local pseudo crossing a call, it gets s0.

Idea: Make d ALSO a local pseudo crossing a call with higher priority, so local-alloc gives d=s0 and s1ang=s1. But d is defined at the top and used at the divs; it's live across the call, so local-alloc COULD assign it. Why didn't it? Because... local-alloc processes each basic block; a pseudo defined in block 0 and used in blocks 7,9 (the div blocks) has a live range spanning multiple blocks → global. Local-alloc only handles pseudos with lives within one basic block? Actually local-alloc handles pseudos that die in the same block where they're born (and don't span blocks). d is used in multiple blocks → global.

Hmm, so how can d be local-alloc'd? If d's uses were in the same block as its definition — not possible (divisions are in different blocks).

Alternative: get s1ang to s1. Local-alloc assigns s0 to the first eligible qty. If we make s1ang's live range shorter or its refs lower... it's already refs 2 live 7. Hmm.

Actually, wait: local-alloc's choice of s0 vs s1 depends on which hard regs are free at the pseudo's live range. If some other hard reg is live during s1ang's range, it can't use it. E.g., if s0 were occupied during s1ang's live range by another variable, local-alloc would pick s1.

Alternatively — maybe there's an easier route: change the C so that `s1ang` is NOT a separate variable but is folded. But the target has a separate load into s1.

Hmm, let me reconsider. The target's register choice might come from a different variable structure. Let me look at what the original source might be. The dedup comment says h_exact hash. This is a shared header body. The original game's source (unknown) produced d=s0, s1ang=s1.

Let me look at the sibling function in another overlay that has the same body but maybe *without* a pin (if some overlay's TU was matched without a pin). The dedup.us.yaml lists members. Maybe a member TU has a hand-written version. Let me search for this exact function in other overlays: grep for `s1ang` in src/.

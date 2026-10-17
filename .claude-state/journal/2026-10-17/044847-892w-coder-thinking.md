---
ts: 2026-10-17T10:48:47.371Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm working through birthing_insn_p's logic: when a register is set live at block end with only one definition, its priority gets boosted to maximum. I'm trying to reason out whether that means it gets scheduled first or last given the backward scheduling direction used here.

Looking at tie-break behavior with INSN_LUID, I'm testing the hypothesis empirically against the known source order output: it seems the insn with the greater luid gets chosen first in the ready list and ends up placed later in the block, which seems backwards from what I'd expect for critical-path priority. I'm now digging into how `priority()` actually computes INSN_PRIORITY by recursing over LOG_LINKS to figure out whether it measures distance from block start or end.

Then I check "birthing" status for each register: j is set twice so it doesn't get the priority boost, while k, t3v, pb, m24, and mhi are each set once and live at block end, so they all get boosted to max priority. Since j isn't boosted but still ends up appearing first in the target output, I'm uncertain about the actual scheduling direction, so I decide to stop theorizing and just test directly against the desired output ordering.

Maybe the source order places `t3v = m*4` differently in the block, before or after the `j`/`k` assignments, and cse later reuses `m`. I'm also considering whether t3v's computation originally lives inside the loop body and gets hoisted into the preheader by the loop optimizer instead of appearing in the original source order.

I'm wondering if the issue is that cse links `k` to `m` as a copy, letting `k*4` substitute for `m*4` inside the loop — so to break that link, `k` would need to derive from something other than a direct copy of `m`, maybe from a sign-extended comparison variable instead.

With cse-follow-jumps active, the extended block merges these equivalence classes: sign_extend(i), c3, and m all become linked, and the head would naturally be c3 since it lives longest. But if c3 were truly in that class, the output would resolve to s8 rather than v1 — yet both our version and the target use v1, so c3 must not actually be joining m's class here.

Something later must be converting the k register back to m before the shift instruction executes, since the final assembly reads v1 despite the RTL computing t3v from k.

I need to trace which pass does this — maybe the insn I saw at 2885 is a REG_EQUAL note or a separate instruction (2879 setting k, 2885 computing t3v with the shift and mult note). I should check the register allocation dump for the t3v instruction and the scheduling pass output.

I've confirmed that `birthing_insn_p` boosts every single-set preheader leaf except j (set twice), ordering the rest by luid. I also noticed flow's RTL has t3v reading k while the final asm shows v1 reading m, so I'll trace which pass rewrites this to see if it determines the refs.

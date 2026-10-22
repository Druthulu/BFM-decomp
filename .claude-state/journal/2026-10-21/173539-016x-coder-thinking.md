---
ts: 2026-10-21T23:35:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_9SXnObwc3FLbafSP2prc
---
Interesting. The target has `addiu a1,sp,24` at insn 4 and `addiu a0,sp,24` at 15, whereas mine (a1, launder removed) has `sw s0,32(sp); addiu s0,sp,24; move a1,s0`.

So the launder was there to keep the sp+24 value in a register (s0) so that... hmm no. Actually the target computes `addiu a1,sp,24` directly for the 2nd arg, and `addiu a0,sp,24` for the 1st arg. So p0 = sp10 (sp+16?) and p1 = sp10+4 (sp+24). Hmm wait sp10 is u16[6] = 12 bytes. Let me think about the stack layout: target insn 4: `addiu a1,sp,24` — so the array base is sp+24? and a1 = sp+24, a0 = sp+24? Both?

Actually insn 15: `addiu a0,sp,24`. Hmm both a0 and a1 = sp+24? That would be p0 = p1 = sp+24? No — p0=sp10, p1=sp10+4.

Wait, look at the ordering: in mine, insn 4-6: `sw s0,32(sp); addiu s0,sp,24; move a1,s0`. So mine computes s0 = sp+24 and a1 = s0. In target: `addiu a1,sp,24` at position 4, and there's an `insert` of `sw s1,36(sp)` at 11 and `addiu a0,sp,24` at 15.

Hmm, but wait, target position 4 is `addiu a1,sp,24`? That means target's first call arg register setup differs. Actually the diff alignment: "replace mine[4:7] target[4:5]" then "insert mine[11:11] target[9:10]". So target[4] = `addiu a1,sp,24` corresponds to mine[4:7] = sw s0,32(sp); addiu s0,sp,24; move a1,s0.

Hmm, so target: a1 = sp+24 computed directly. And later target[15] = `addiu a0,sp,24`.

Wait, that's weird: both a0 and a1 = sp+24? But p0=sp10 and p1=sp10+4 should be sp+16 and sp+20 or whatever. Unless the array sp10 is at sp+24 in the target, and p0=sp10+... hmm.

Hold on. Let's reconsider: maybe in the target, p0 and p1 are different: the first call is func_800D20C0(p0, p1, 1) → a0=p0, a1=p1, a2=1. In target, a1 = sp+24 is set at insn 4, a0 = sp+24 at insn 15?? That can't both be right unless... hmm, actually maybe the diff isn't precise. Let's look: mine[16] `move a0,s0` vs target[15] `addiu a0,sp,24`. In mine, a0 = s0 = sp+24 (from insn 5). So a0 and a1 both = sp+24 in mine! Because p0 = sp10 and p1 = sp10+4 — but gcc CSE'd them?

Hmm, wait. sp10 is `u16 sp10[6]`, and `sp10[2]=0; sp10[1]=0; sp10[0]=0;` writes sp+0..6. Then p0 = sp10 → sp+offset_of_sp10. p1 = sp10+4.

Actually maybe the stack layout differs: gcc chose to place sp10 at sp+24. Then p0 = sp+24, p1 = sp+28. But mine has a0=s0=sp+24 and a1=s0=sp+24 — that means a1 got the wrong value! No wait, `move a1,s0` where s0=sp+24 → a1 = sp+24 = p0?? That's wrong semantically.

Hmm, unless the layout: p1 = sp10+4, and... no.

Wait, maybe I mis-read. Let me re-read: "replace mine[4:7] target[4:5] 4 sw s0,32(sp) | addiu a1,sp,24; 5 addiu s0,sp,24 | --; 6 move a1,s0 | --". So mine insn4 = `sw s0,32(sp)` (save s0), mine5 = `addiu s0,sp,24`, mine6 = `move a1,s0`.

Hmm, but where's `move a0,s0` before? mine16 = `move a0,s0` — that's the a0 for... hmm, at mine16.

OK this is getting complicated. Key insight: mine computes sp+24 into s0 once and reuses for both a1 (insn 6) and a0 (insn 16). Target computes `addiu a1,sp,24` (insn 4) and `addiu a0,sp,24` (insn 15) separately.

So the target has a0 = a1 = sp+24?? Both the same value! So p0 and p1 are the SAME address in the target! That means the launder was actually wrong: the target's real code passes the same pointer twice? Or p0 = sp10 and p1 = sp10+4 but they're at sp+24 and sp+28...

Hmm, but target says both sp+24. Unless... let me check: maybe target insn 4 `addiu a1,sp,24` is for a different call. Let me get the full disassembly of the target function.

Let me find the target asm. Where is it? Probably in build/ or a dumps dir. delever_search compares with "the function in build/". Let me find the target asm file.

Let me check tools/delever_search.py for how it gets the target.

Actually simpler: there might be a target dump. Let me look for build/ asm.

Let me look at the .run/P40/T10/func_80181F4C worked example and the G10/tgt.txt (16k) which might have target disassembly.

Let me check tgt.txt.

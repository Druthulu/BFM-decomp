---
ts: 2026-11-06T22:29:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fH7r2yH6TnN3nwvCuATh
---
So r74 = d (9 refs, 27 insns, crosses 1 call). r77 = s1ang (5 refs, 10 insns). r75 = 2 refs 7 insns block 0 (local-alloc candidate, crosses 1 call) — got s0.

Wait, r75 crosses 1 call and is in block 0 only, but local-alloc can still allocate block-local pseudos (single block). Which pseudo is r75? Let's find in the greg dump. Actually in the alloc table for w0, r75 hard=s0, and it's "2 refs, 7 live, blk 0, crosses 1 call". In the pinned version, r75 gets s1 (and r74=d is pinned s0). So r75 is a block-local pseudo assigned s0 in w0.

Hmm, in the target (pin version), the pin reserves s0 for d from the start, so local-alloc's r75 cannot take s0 → takes s1. Then s1ang r77 gets...? In pin table: r77 hard `-`, prefers s1, conflicts v0,s0,s1,sp — hmm.

Wait in the pin version: r75=s1, r77 prefers s1 but conflicts s1 → so r77 gets...? The table shows r77 `-`, but the final code target has s1ang in s1! And r75 in pin has s1. Both in s1? They must have non-overlapping ranges... but r75 is 2 refs across 7 insns in block 0, and s1ang (r77) lives from block 0 onward. Hmm, maybe r75's live range is before s1ang's definition (block 0 first insn 4, and s1ang defined at insn ~10).

Actually the target code: at entry `move s0,a1`? and `lw ... ; sra s1,s1,...`? Let me look at the target asm (build object). Let me check the target disassembly in the diff: target `sra s0,s0,0x10` for d cast. Hmm wait, that's d=(s16)d where d is the arg1 copy. Target line 22 is `sra s0,s0,0x10` — so before that there's `move s0,a1`? Hmm, and s1ang in s1: `subu v1,a0,s1` uses s1 as u6 = s1ang & 0xFFF. So s1ang in s1.

But wait, where is r75? r75 is likely the `*(s32 *)(arg0+0x20)` pointer temp or `u5`? Let's see: r75 2 refs in block 0. In the pinned version r75=s1 and s1ang=s1? Then s1ang would conflict. Unless s1ang is r76? Let me map: pinned .greg order 78 80 79 77 76. r77 = 5 refs/10 = s1ang (same refs as w0's r77). r76 = 5 refs/14. r74 is absent from pin's .greg (pinned → r101 s0 with pri 40000? no, r101 s0 pri 40000 is the pin pseudo). Hmm, r101 in pin table = s0 pri 40000, refs 4, live 2 — that's the pin? Actually the pinned `d` pseudo is hard-assigned s0; the alloc table lists r101 s0. But d has 9 refs... Hmm, r101 4 refs 2 live in block 0 — that looks like a different temp.

Let me not over-analyze the table; better to look at the actual .greg dump. Let me grep the .greg dump around our function for "Register 74" and assignment info.

Actually the greg dump (w0.i.greg) shows global allocation order and the regs chosen. Let me look.

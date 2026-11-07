---
ts: 2026-11-06T10:03:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_syvlU38bzySYpQAfioVR
---
Line 230: `;; 8 regs to allocate: 74 78 75 77 76 79 72 73` — the allocation ORDER. r74 first, then 78, 75, 77, 76, 79, 72, 73.

r74 conflicts: 73 74 75 76 77 78 79 2 3 29. Here 2=v0, 3=v1, 29=sp. So r74 conflicts with v0 ($2) and v1 ($3)! Wait, it lists 2 and 3. So r74 conflicts v0 AND v1. Then how did r74 get v1 in the final? 

Hmm, the final has t in v1. But conflict says v0 and v1 both. Unless r74 is not t.

Wait, in the orig matching body, the order was `74 76 77` (3 regs). r74 conflicts v1,a0,s0,sp and prefers v0 → gets v0.

In lever-free, r74 conflicts v0,v1,a0,sp? line 233: `74 conflicts: 73 74 75 76 77 78 79 2 3 29` → yes v0,v1,sp. So r74 can't take v0 or v1! Then r74 must get something else... but the final code shows t in v1.

Hmm, maybe r74 is not t. Let me map. The "8 regs to allocate: 74 78 75 77 76 79 72 73". These are allocnos: 72 (s0, pointer, crosses calls), 73 (pri 4000, conflicts v0,sp, prefers a0), 74 (pri 10000, 4 refs live 8), 75 (pri 2500, 2 refs live 8), 76 (3 refs live 6), 77 (5 refs live 21), 78 (5 refs live 5, gets a1), 79 (2 refs live 3).

Which is t? t has 4 refs, live 8 → r74. tb has 2 refs, live 8 → r75.

But r74 conflicts v0 AND v1. So it can't be either. Then t got... v1? Contradiction.

Unless the conflict line "2 3" means something else: maybe those are allocno numbers 2 and 3, not hard regs! In global-alloc's dump, "conflicts" lists both hard regs and allocnos by number. Hard regs are 0..31; allocnos are numbered from 32 up (FIRST_PSEUDO_REGISTER = 32). Here we have 2,3,29 → hard regs v0,v1,sp. And 72-79 are allocnos. OK so r74 conflicts v0,v1,sp.

But the final assignment put t in v1. So maybe r74 is NOT t.

Let me reconsider: maybe t is r75 (2 refs, live 8)? But t has 4 refs. Hmm, "used 4 times across 8 insns" — the .lreg line said "Register 74 used 4 times across 8 insns in block 2; dies in 2 places". And "Register 75 used 2 times across 8 insns in block 2". 

Hmm, "dies in 2 places" for r74 — t is set twice, so it dies at each set. Yes t = r74 (4 refs = 2 defs + 2 uses, dies in 2 places).

But r74 conflicts v0,v1,sp and can't take either... yet t is in v1 in the final. So the conflict computation includes r75 (allocno) which... no, allocnos aren't in the conflict list as hard regs.

Wait, maybe the final assignment I observed (t=v1) is wrong. Let me re-check the nopin dump: line 52 `lw v1,76(s0)`, 54 `sh v1,6(s0)`, 55 `lw v1,80(s0)`, 59 `addiu v0,v1,-8`. So t is v1 in both defs. And tb: 53 `lw v0,84(s0)`, 58 `sh v0,14(s0)` → tb=v0.

But r74 conflicts v0,v1. If r74=t, it can't be v1. Contradiction → so t is NOT r74.

Let me reconsider: maybe r74 is `tb`?? tb: 2 refs, but r74 has 4 refs. Hmm.

Or maybe r74 is a different variable entirely: `p`? p = arg0->unk20, used many times. `cnt`? cnt used 4 times (load, slti, andi, compare...). cnt = ((Unkstruct*)s0)->unk1C; used at `cnt < 0x20`, `(cnt&7)==0`, and `s0->unk1C = s0->unk1C + 1` (that's a reload). Hmm, cnt might be 4 refs live 8 in block 2? No, cnt is used in block 0.

Actually the function's block numbering: block 0 is entry, block 1 is `if(cnt&7)==0` body? The table says r74 blk 2. Hmm.

I think I'm overanalyzing. Let me just look at the final .s of the lever-free compile to map pseudo→reg via the .lreg dump "Register 74 in 16" style lines. Search the lreg dump for "74 in".

---
ts: 2026-11-06T23:52:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xHLpLbzsX6WWGUp4XW0a
---
It iterates in reg_alloc_order (or regno order). So the first allocno to be processed gets the lowest-numbered free eligible reg.

So allocation order determines who gets s0 vs s3 etc. And within a single allocno, find_reg picks the lowest available.

In target: cnt→s0, file→s1, val→s2, mode→s3, base→s4. But that's suspicious: exactly in order of... maybe it's not global-alloc; maybe these are *local* allocs? No.

Hmm wait. Maybe those aren't all separate allocnos in the order shown. Let me check with alloc_table.py. Actually, let's think differently: maybe the regs were assigned by priority order:
- cnt: refs? cnt is used at 1158 (slti), and set once. Actually `cnt = func_80029504()` then used in `cnt < 5` and `cnt >= 0x2A8`. 3 refs, live from 1108 to 11b4 (~45 insns). pri = floor_log2(3)*3/45 = 1*3/45 = 0.067
- file: 5 refs? file is set from D_800D34AC, then possibly overwritten in 4 ifs, used in `file >= 0 && cdFileLocTable[file]`. live 10b4..1230 (~100). floor_log2(5)*5/100 = 2*5/100=0.1
- val: set 10ac, overwritten in ifs, used in compare and store. ~8 refs? live 10ac..1224 (~110). 3*8/110=0.22
- mode: set 10ec, 10f4; used 1208(bltz), 1268(arg), 1278(bnez). ~5 refs, live 10ec..1278 (~90). 2*5/90=0.11
- base: set 10d8; used 10 refs, live 10d8..12ac (~110). 3*10/110=0.27

Hmm base highest → should get s0. But target has base in s4. So maybe global-alloc didn't assign these at all — maybe local-alloc did! Because... hmm.

Wait. Actually maybe with the pin, the ordering changed. The pin reserves s3 for mode. base then can't get s3. If base is allocated FIRST (highest priority), it would take s0! But target has base in s4. So base is NOT first.

Unless local-alloc allocated these. local-alloc assigns block-local pseudos only. base spans the whole function, so no.

Hmm, unless base is NOT a global allocno because... it's used only in blocks? It's set in block 1 and used in many blocks. Global.

Let me actually dump the allocation table. tools/alloc_table.py. Let me check its usage.

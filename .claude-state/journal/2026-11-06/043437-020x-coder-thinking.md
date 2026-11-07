---
ts: 2026-11-06T11:34:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zp6Vmdei1kcrwXBscQhx
---
Interesting. So mine vs target: target has `li v1,8; sb v1,3(v0)` at position 50-51, and later `move v1,s2`. Mine has sb v1,3(v0) at 59 with li v1,8 at 57 — i.e. the `p[3]=8` store got scheduled later (after p+=8, vx=x, p[7]=0x38) in mine; target has it early.

Also target computes the first packet's tag update with `and a0,v0,a1` ... hmm, that's the last block? Let me get the actual target disassembly to understand. Let me dump the target function. There's a tool? bin/dt.sh compares with build. I could objdump the baseline object. There is tools/alloc_table.py and cc1_dumps_tu.sh. Simpler: the target .s in asm/nonmatchings/800/func_80015B6C.s. Let me read it (that's project file, allowed).

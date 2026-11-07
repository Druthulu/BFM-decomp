---
ts: 2026-11-06T04:37:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ixAz5q60glNnJaOLumS3
---
In the combine dump for func_801810A4 (line 23348+), the insns are:
- 230: (set (reg:SI 115) ...) — a load?
- 232: (set (reg:HI 116) ...) — a halfword load?
- 234: (set (mem/s:HI (plus (reg 115) ...)) ...) — a store!
- 237: (set (reg:SI 117) ...)
- 241: (set (mem/s:HI (plus (reg 117) ...)) ...) — another store

Hmm, these are different insns than I expected. Block 13 from 230 to 243 contains two stores (234, 241). This looks like the `==0` arm or another. Wait, the block trace shows the schedule: 241, 237, 234, 232, 230. 

Actually, I'm confused about which block is the `<0x11` arm. Let me search the combine dump for the p load insn: `(set (reg/v:SI ...) (mem/s:SI (plus ... 32)))` in the func_801810A4 section. Let me grep for "const_int 32" near mem/s:SI in the combine dump after 23348.

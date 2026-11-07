---
ts: 2026-11-06T11:35:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LRmSCwvtlAjZ6zTVjexK
---
Now I understand target. Key parts:

- s1 = x, s2 = y. w_ and h_ spilled to 16(sp)/24(sp) (because they're used later).
- After p += 8:
  ```
  3844 li v1,8 ; sb v1,3(v0)      p[3]=8
  384c li v1,56 ; sb v1,7(v0)     p[7]=0x38
  3850 move a0,s1                 a0 = x (vx)
  3858 move v1,s2                 v1 = y (vy)
  385c.. stores c1..c3, then 0xC..0xE, 0x14..0x16, 0x1C..0x1E
  388c sh a0,8(v0)                vx
  3890 sh v1,10(v0)               vy
  3894 lw t1,16(sp)               w_
  3898 lw a2,0(v0)                tag2 = *p
  389c addu s1,s1,t1              x += w_
  38a0 sh s1,16(v0)
  38a4 sh v1,18(v0)
  38a8 sh a0,24(v0)
  38ac lw t1,24(sp)               h_
  38b0 and a2,a2,a3
  38b4 addu s2,s2,t1              y += h_
  38b8 sh s2,26(v0)
  38bc sh s1,32(v0)
  38c0 sh s2,34(v0)
  38c4 lw v1,16380(s0)
  38c8 and a0,v0,a1               pmask
  38cc and v1,v1,a1
  38d0 or a2,a2,v1
  38d4 sw a2,0(v0)
  38d8 lui a2,0xe100 ; ori a2,a2,0x200   tag2 = 0xE1000200 (AFTER the tag store!)
  38dc lw v1,16380(s0)
  38e0 addiu v0,v0,36
  38e4 and v1,v1,a3
  38e8 or v1,v1,a0
  38ec sw v1,16380(s0)
  38f0 sb t0,3(v0)   t0=1
  38f4 lw a0,0(v0)
  38f8 ori a2,a2,0x200
  38fc sw a2,4(v0)
  ...
  ```
Interesting: the final `li`/`lui+ori` for 0xE1000200 happens at 38d8/38f8, after the tag store; that's because tag2 = 0xE1000200 is set after the barrier in source. So the source order with barrier after pmask store is what makes `tag2 = 0xE1000200` (li/lui+ori) appear between the `sw 0(v0)` and the `sw 4(v0)`.

Note the target's `tag2 = *(u32*)p` load at 3898 (a2) and and at 38b0; and `tag2 = 0xE1000200` at 38d8. With the pin $6, tag2 lives in a2? Hmm pin $6 = a2. Yes! tag2 is pinned to $6 = a2. mFF pinned $7 = a3. Good, so pins explain a3/a2 usage.

Now mine (lever-free, barriers/launders removed) got the first block's stores reordered: `li v1,8; sb v1,3(v0)` was at 59 (after p+=8, vx=x, p[7]) instead of early. And vx/vy copies used s1/s2 directly? Mine: `sh s1,8(v0)` at 50 — i.e. vx is s1 (x), no `move a0,s1` copy. Target has `move a0,s1` because vx is used later (p+0x18) after x changed... but target also has `move v1,s2` for vy, and vy used at 0x12/0x1A. Actually vy = y, and y changes later; vx=x used at 0x18 (after x += w_), so vx must be a copy.

Wait target stores `sh a0,8(v0)` = vx and `sh a0,24(v0)` = vx at 0x18. And `sh v1,10/18(v0)` = vy. Mine at 50: sh s1,8(v0); and later sh s2,10... then at 76 sh v1,18? Hmm mine seems to have vx in s1? No — mine[50] `sh s1,8(v0)` means vx is s1... but then x+=w_ modifies s1. Hmm, maybe mine computed differently: perhaps mine has vx as s1 and x in another reg.

Let me look at mine's disassembly to compare. Get the candidate object with --keep, then objdump. Run dt.sh doesn't support --keep. Use the python directly with --keep and the item tu/fn. Command: /usr/bin/python3 tools/delever_search.py --try src/800.c func_80015B6C <body> --body --keep. It prints candidate object path. Then objdump it. Need to cd to repo root? The tool probably uses REPO path internally (absolute). Run from anywhere? It does REPO = ... let me just run with absolute script path.

---
ts: 2026-11-06T01:30:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tzl7nymrbD5vvelPhslN
---
Now the target layout. zero block at 17d0..1808:
- move a0,s0
- jal func_80185D3C; li a1,1
- sll v0,v0,0x10
- bnez v0, 17f8 ; move a0,s0
- jal func_8012B178; lui a1,0xfffd
- jal func_8012CBA4; move a0,s0
- 17f8: jal func_8012B200; move a0,s0
- 1800: li v0,29
- 1804: sh zero,244(s0)
- 1808: sw v0,28(s0)
- 180c: epilogue

dec block: 17bc..17cc:
- lw v0,28(s0)
- nop
- addiu v0,v0,-1
- 17c8: j 180c
- 17cc: sw v0,28(s0)

Interesting: so dec's store is in the delay slot of `j 180c`; zero falls through to 180c after `sw v0,28(s0)`. Without barrier, cross-jump merges zero's tail `sw v0,28(s0)` (at 1808) with dec's tail? They're both `sw v0,28(s0)` but in dec it's a delay-slot instruction after j. Hmm mine had `j 1800` at 114 and the target has nop at 114... let me dump mine.

The residual said mine[114] = j 1800 target = nop; and target insert at 116: j 180c; sw v0,28(s0). So mine's zero block ends with `j 1800` (to zero's li v0,29? no 1800 is li v0,29) with delay slot nop, then falls... Actually mine's structure differs: mine at 114 is `j 1800` and then at 116 nothing, meaning mine jumped to 1800 and target has 116: j 180c, 117: sw. Hmm confusing.

Let me dump mine. Use delever_search --try --keep and objdump the scratch object. Let me check --keep output format.

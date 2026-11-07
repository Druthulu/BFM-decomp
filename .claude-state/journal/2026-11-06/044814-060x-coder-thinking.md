---
ts: 2026-11-06T11:48:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_M1YPyMjFnFzH7QzMBOkw
---
v2's residual: an insn moved by 1 (lw a1,-4(s1) scheduled one slot earlier in the target). ORDER score 3.

Target:
```
61: lw a1,-4(s1)
62: ?
63: srl a2,a1,0x10
```
Mine:
```
61: (something)
62: lw a1,-4(s1)
65: srl a2,a1,0x10
```

Let me get more context. Let me look at the target disassembly around that point and mine. Let me use --keep.

Actually the diff only shows 3 lines, so only this one insn is displaced. Let me see the surrounding lines with more tail.

Hmm, dt.sh tail 200 gave only 4 lines of diff. The diff tool shows minimal context. Let me get the full listing of mine and target around insn 55-70. Let me use --keep and objdump, plus the target object.

The TU is ov_SC03_103_jr_8017C294. Target object: build/src/ov_SC03_103/ov_SC03_103_jr_8017C294.o. Let me disassemble around func_8017D174.

Actually the insn numbers in the diff are indices in the function. Let me dump both and compare lines 55-70.

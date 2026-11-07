---
ts: 2026-11-06T22:30:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7Zh48ksguU9swndqviVE
---
The target is read from the build object under build/ — a scratch object built from the tree. Hmm, "the function's instructions are read out of that scratch object ... run's baseline object under build/". So the target asm comes from the current build, which is the original (matching) bytes. So build/ov_SC03_099/ov_SC03_099.elf maybe? Actually the scratch object is built during the run. 

Simpler: I can get the target asm by compiling the pinned version (which scores 0) and objdump it. The pinned version IS byte-identical to target. So dump prev_win.c's .s (we already have dump_pin/pin.s). Let me read the target .s for our function.

Actually pin.s is from cc1 (gcc -S), which shows the target-equivalent assembly. Let me look at it.

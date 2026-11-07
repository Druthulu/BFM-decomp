---
ts: 2026-11-06T12:24:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nTEPP2VfRgEqjeAoUtA6
---
The ov_SC01_009 asm — check where it is: maybe asm/ov_SC01_009/ doesn't exist because it's banked? The banked src means it matches. But there must be an asm for comparison in build/. The dt.sh compares with the function in build/ — build/ contains the compiled banked object. Hmm: "compares with the function in build/". So the target is the built object from src (which is byte-identical), not an asm file.

So to see the target disasm I can dump the built object. Where is it? Let me check for a build dir. Actually since src currently matches, the "target" is src compiled. Then the diff is mine vs the current src compile. And the residual is what removing the levers costs.

I could get the target's asm by compiling src and dumping. Let me find the built object: build/src/ov_SC01_009/ov_SC01_009_jr_8017BE9C.o?

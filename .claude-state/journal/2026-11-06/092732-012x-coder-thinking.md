---
ts: 2026-11-06T16:27:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ksxKzRwN0yC3Si5FMiAp
---
Key region:

```
2b8c: lh v0,112(s3)      ; unk70
2b94: bnez v0,2bb0       ; if unk70 != 0 -> else arm
2b98: slti v0,v1,513     ; delay slot! d < 0x201 computed (belongs to else arm)
2b9c: slti v0,v1,81      ; then arm: d < 0x51
2ba0: beqz v0,2bc8       ; if !(d<0x51) goto skip
2ba4: nop
2ba8: j 2bb8             ; then arm falls to join at 2bb8 (call)
2bac: nop
2bb0: beqz v0,2bc8       ; else arm uses delay-slot slti d<0x201
2bb4: nop
2bb8: jal func_801822A4
```

Interesting: the target's structure has the two comparison chains with different branch targets: then arm does `beqz v0, skip` and then `j join`; else arm does `beqz v0, skip` and falls through to join.

Cross-jump merges the two tails. Mine without barrier: 197 ins vs 201 = 4 fewer. Let me dump mine to see what merged. Use cc1_dumps or simpler: build with delever and diff. dt.sh shows diff tail. Let me get a full diff by running delever_search with more tail lines.

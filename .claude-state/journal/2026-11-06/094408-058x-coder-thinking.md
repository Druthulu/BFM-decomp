---
ts: 2026-11-06T16:44:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cGMDJqp2cMrOSTAZNRxR
---
Confirmed: in w4, the then arm's branch 413 is the NORMAL form `(ne v0 0) (label_ref 440) (pc)` (branch-if-true to docall), while the else arm's branch 431 is the INVERTED form `(ne v0 0) (pc) (label_ref 452)` (branch-if-false to skip). The emitted insns are identical (bnez? no—). Wait: normal form with NE → "bne v0,0,label" = bnez to docall. But the disassembly showed `beqz v0,2bc8` (skip) then `j 2bb8` (docall), not `bnez v0,docall`.

Hmm, the RTL has branch 413 to label 440 (docall), and 421 jump to 452 (skip). So: if v0 != 0 (d<81) goto docall; else jump skip. But the disassembly showed:
```
2b9c slti v0,v1,81
2ba0 beqz v0,2bc8   (skip)
2ba8 j 2bb8 (docall)
```
That's the opposite! `beqz v0,skip; j docall`. Hmm — the RTL says bnez v0,docall; j skip. But the emitted is beqz skip; j docall. These are logically equivalent but different instructions!

Wait, maybe I misread the label refs: 413 is `(if_then_else (ne v0 0) (label_ref 440) (pc))`. In branch_zero: operands[0]=NE, operands[2]=label 440 (not pc) → normal jump → "bne v0,0,440". Hmm. But the disassembly shows beqz to skip.

Unless the RTL at jump2 is later changed by dbr (delay slot) or the .s differs. But the object disassembly is ground truth and it matches target. Let me look at the .s dump to see. Actually maybe I mixed up: the jump2 dump's insn 413 might be for the *then* arm but the then arm's `goto docall` ... hmm.

Wait, maybe the label 440 "docall" is actually at the position of... In the dump: 431 is the else branch (ne v0 0) (pc) (label 452). 440 is "docall" label after 433. 443 move a0; 445 call; 447 jump 487 (epilogue).

So the code: then arm: slti 81; bne v0,0,docall; j 452(skip). else arm: slti 513; bne v0,0,(pc) else 452.

Hmm, the emitted: then arm `slti 81; beqz v0,skip; j docall`. That's `if (v0==0) goto skip; goto docall` — i.e., inverted. But the RTL 413 is normal `(ne v0 0) (label 440) (pc)` = if v0!=0 goto docall. These are logically the same: if v0==0 → fall through to j 452 (skip); if v0!=0 → goto docall. So RTL: bne v0,0,docall; j skip. The emitted insns: beqz v0,skip; j docall. Different instructions!

But wait — maybe the disassembly I read was from p4's cand.o which corresponds to w4, and the dump w4b is from the same TU. Both should agree. Unless dbr/reorg reorders and the disassembly line at 2ba0 is `beqz v0,2bc8` — target's. And the target.s also has that. So the final assembly is beqz+j, while the jump2 RTL says bne+j. Something's off: maybe I mis-assigned which arm is which. Let me look at the labels: 452 is the skip label. 413: `(if_then_else (ne v0 0) (label_ref 440) (pc))`. Label 440 = "docall". So branch to docall when v0!=0. In assembly that's `bnez v0,docall`. Then 421 jump to 452 (skip).

But the disassembly shows `beqz v0,2bc8` (skip) then `j 2bb8`. That's the reverse. So the dump and the object disagree?? Unless the .s in dumps_w4b is different — let me check the .s. Maybe the jump2 dump isn't the final RTL; the .s is. Let me grep the .s for the region.

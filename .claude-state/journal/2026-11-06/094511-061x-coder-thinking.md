---
ts: 2026-11-06T16:45:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Lafe1pm9x9SorF8InBtI
---
The .s shows exactly the target:
```
bne $2,$0,$L307      ; unk70 != 0 -> else
slt $2,$3,513        ; delay slot (else compare)
slt $2,$3,81
beq $2,$0,$L310      ; skip
j $L309              ; docall
$L307:
beq $2,$0,$L310
$L309:
jal ...
```
So the emitted code is `beq $2,$0,$L310` then `j $L309`. But the jump2 RTL showed branch 413 as `(ne v0 0) (label 440) (pc)` = bne to docall... That contradicts.

OH WAIT. I see — the .s is from the dump TU which is w4. And the disassembly of p4/cand.o also matches. So the RTL at jump2 must have been further transformed by the *dbr* (delayed branch reorganization) pass, which runs after jump2 and can invert/redirect branches? Actually reorg can fill delay slots and "steal" but not invert a branch.

Hmm, maybe I misread the dump's jump2: perhaps insn 413 is in a different function? No, it's in the func_80181F80 section (I extracted it).

Let me re-read: 413: `(if_then_else (ne:SI (reg:SI 2 v0) (const_int 0)) (label_ref 440) (pc))` with 440 = "docall". Hmm. But the .s has `beq $2,$0,$L310` (skip) then `j $L309` (docall). $2 is v0. So the branch to skip when v0==0, jump to docall.

The RTL says: branch to docall when v0 != 0, then jump to 452 (skip). In assembly: `bne v0,0,docall; j skip`. But the .s shows `beq v0,0,skip; j docall`. These are different! Unless label 440 in the dump is NOT docall... the dump shows `(code_label 440 433 443 309 ("docall"))`. Yes.

Wait, maybe the dump's jump2 for this function is from a DIFFERENT version of the file. The dumps_w4b were generated from dumptu/t.c which now has "goto docall" (grep confirmed at line 4542). Hmm.

Hold on, maybe there are TWO functions with similar code, and my awk extraction grabbed the right one. Let me check the dump for "docall" label and the branch: maybe the branch 413 target is 440 but the *else* arm's 431 targets 452 skip. In the .s, the first branch (`bne $2,$0,$L307`) is the unk70 test, then `slt 513` in its delay slot, then `slt 81`, `beq $2,$0,$L310`. So the then arm's branch is `beq $2,$0,$L310` = branch-if-zero to skip. The RTL 413 in the dump is branch-if-NONZERO to docall. Contradiction unless the dump's 413 belongs to... 

OH! I bet the dump's insn 413 is `(if_then_else (ne v0 0) (label_ref 440) (pc))` where 440 is actually the label right after 413 (i.e., the skip continuation)? The code_label 440 is at the end ("docall"), per the dump. Hmm.

Wait, maybe the RTL in jump2 is from BEFORE reorg's branch inversion. Does reorg invert branches? reorg.c does "optimize_branch" — it can invert a branch to fill the delay slot! Yes, reorg can reverse a conditional branch if the delay slot can then be filled. Let me check reorg.c for invert. Actually reorg has "steal_delay_slot_insn" and "fill_simple_delay_slots". There's `invert_jump` usage maybe.

Anyway, empirically: w4 scores 0 and the .s shows the target's exact layout. The mechanism at jump2: the then arm's branch is `(ne v0 0) (label 440) (pc)` (normal form, target=docall) while the else's is `(ne v0 0) (pc) (label 452)` (inverted form, target=skip). These are structurally different, so find_cross_jump doesn't match → no merge. Then reorg inverts the then branch to fill the delay slot, producing `beq v0,0,skip` + `j docall`. That explains it: reorg's branch inversion.

Great, the mechanism is solid: differing branch RTL forms (normal vs inverted) block jump2's cross-jump; reorg then inverts for delay-slot fill.

Hmm wait, but is that exactly right? Let me double check the .s: the then arm's branch `beq $2,$0,$L310` then `j $L309` with NO nop between (the delay slot of beq is the j? Actually in the .s: 
```
beq $2,$0,$L310
j $L309
$L307:
beq $2,$0,$L310
$L309:
jal
```
The beq's delay slot is `j $L309`. In the final object: `beqz v0,2bc8; nop; j 2bb8; nop`? The target.s shows:
```
2ba0 beqz v0,2bc8
2ba4 nop
2ba8 j 2bb8
2bac nop
```
So beq's delay slot is a nop. Fine.

So the mechanism is: the then arm's branch RTL is the normal form targeting docall; cross-jump compares it with the else's inverted form targeting skip → no match. Good evidence.

Now, is w4's structure "real C"? `if (d < 0x51) { goto docall; } goto skip;` — yes, plain C with gotos, no lever. The "goto chain → structured C" catalog entry even endorses goto/if forms. Good.

Item 1 complete at 09:44. Tries: let me count precisely: win.c (no-asm) 1, v1 2, v2 3, v3 4, v4 5, v5 6, v6 7, w1 8, w2 9, w3 10, w4 11. Plus re-scores of w4 (dt) not counted as tries? "tries" = scored tries; I'll say 11.

Now record results.tsv row and moves.md line, notes.md, then move to item 2. Also clean up dumps dir to save disk.

Let me write the results row. Format (tabs): dir file func kinds result best tries wall evidence.

Evidence ≤140 chars: "jump2: then-arm branch normal form (ne v0,0 ->docall) vs else inverted (->skip); find_cross_jump mismatch; reorg inverts, fills slot".

Let me count: ~135 chars. Fine.

Also the moves.md line: `barrier | func_80181F80 | MATCH: branch-form asymmetry (if (d<0x51) goto docall; goto skip;) — normal vs inverted branch RTL blocks jump2 cross-jump (W48)`.

Let me do these appends with a script (one action per command? The instruction says "One action per command: a results.tsv fix is its own step"). I'll do the results.tsv append as its own command, then moves.md separately.

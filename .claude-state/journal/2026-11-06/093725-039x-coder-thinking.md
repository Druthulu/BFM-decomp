---
ts: 2026-11-06T16:37:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ldAsEwK6qT3mW0xUPS0x
---
At jump2: the then arm is [412 slti 81, 421 jump 523]. The branch is gone — it was merged at jump1? No, v1.jump1 had branch 413 present. So at jump2, insn 413 (branch) was deleted and replaced: the then arm's jump 421 now targets 523, and the shared branch 431 tests v0. That's cross-jump of the unconditional jump 421: find_cross_jump(421, JUMP_LABEL(421)=523? no, in jump1, 421 jumps to 440 (docall)). Hmm, in jump1 the jump 421 target was 440 (docall label). At jump2 the label 440 is NOTE_INSN_DELETED_LABEL, and jump 421 targets 523 (a new label before the else's branch). So cross-jump created a new label 523 at the position of the else's branch (newlpos) and redirected jump 421 there. Then the then arm's branch 413 was... deleted? It should still be there: then arm would be [slti; branch skip; jump 523] — but 413 is gone. Because after do_cross_jump, the code from last2 onward is shared and the then arm's copy of it (branch 413) is deleted (it was the matched suffix: last1..e1 and last2..e2 removed).

Wait, the matched suffix was: last1 = branch 413? and last2 = branch 431, and the matched range is from last1 to e1 and last2 to e2. e1 = the jump 421, e2 = ? Hmm.

Actually in do_cross_jump(insn=421, newjpos, newlpos): the code between last1..e1 (then arm: branch 413 ... jump 421) and last2..e2 (else arm: branch 431 ... e2) are made identical by redirecting. Hmm.

Whatever. The merge matched [branch 413] with [branch 431] and made then jump to a shared copy of the branch.

To prevent: the two branches must differ, OR the then arm's last-but-one insn must differ from the else's last insn.

The else arm's last insn is the branch 431. The then arm's last insn before the jump 421 is branch 413. So matching requires rtx_renumbered_equal_p(branch413, branch431).

They are `(if_then_else (ne:SI (reg:SI 2 v0) (const_int 0)) (pc) (label_ref 452))` — identical.

Real C to change one: the comparison result register. What if the else arm's comparison is expressed as `if (d >= 0x201)` but assigned to a variable first: `s32 t2 = d >= 0x201; if (t2) goto skip;`? Post-reload, the result still goes to v0 and the branch is the same.

What if the else arm's test is on a `u8`/`s16` temp that gets its own register? Extra insns.

Hmm what if the then arm's condition is `if (d >= 0x51) goto skip;` and we add a *second* condition that's folded, e.g. `if (d >= 0x51 && d >= 0)` → folded by fold? maybe emits same.

Actually! What about using a different branch instruction: `if (d > 0x50) goto skip;` — is that slti 81? `d > 0x50` → `slti v0,v1,0x51` then beqz. Same. What about `if (d >= 0x51)` where d is `s32` vs the else `if (0x201 <= d)`? Both fold to the same canonical RTL `(lt (reg) (const_int))`.

Maybe make one comparison use `sltu` semantics but same instruction? `sltiu` differs.

What about making one arm's branch a `beq` on a comparison that's `(eq (reg) (const_int 0))` instead of `(ne (reg) (const_int 0))`? That happens if the C is `if (!(d >= 0x51))`... hmm, `if (!cond) goto` vs `if (cond) goto`. For `if (d < 0x51) goto docall;` the branch is on (ne v0) to docall... not skip.

Actually, target's then arm branch: `beqz v0,2bc8` = branch to skip when v0==0 where v0 = (d<81). So `if (!(d < 0x51)) goto skip` = `if (d >= 0x51) goto skip`. Standard.

Now, if I write the then arm as `if (d < 0x51) { } else goto skip;`, the RTL might be `(if_then_else (eq (reg v0) (const_int 0)) (label_ref skip) (pc))` — a beq instead of bne! Wait no, the branch_zero pattern in MIPS is `(if_then_else (ne reg 0) (pc) (label_ref L))` or the reverse depending on codegen. Let's see: mine has `(if_then_else (ne (reg v0) (const_int 0)) (pc) (label_ref 452))` = branch to 452 when v0==0. For `if (d < 0x51) {} else goto skip;`, GCC might produce `(if_then_else (ne reg 0) (label_ref after) (pc))` = branch when true to the empty block. Hmm, if the empty block is empty, the branch would be inverted: branch to skip when false. Same pattern probably.

Let me think about what makes rtx_renumbered_equal_p differ: register numbers are renumbered away. Constants compared. So if one branch's comparison register is a different pseudo/hard reg, they'd still be equal after renumbering? rtx_renumbered_equal_p treats register numbers as equal if the same in both? Let me check: it's used to compare two insns with different register allocation? Actually rtx_renumbered_equal_p compares RTXes where register numbers may differ? Let me read.

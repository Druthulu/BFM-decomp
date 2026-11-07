---
ts: 2026-11-06T13:18:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fHBO5wMA7p5KWU32WTm6
---
So for unconditional jumps (simplejump_p): find_cross_jump(insn, JUMP_LABEL(insn), 1). e2 = the label insn itself. The walk: i2 = PREV_INSN(label) skipping notes/labels → the insn before the label = the jump(s) that jump to the label? Wait, e2 is the CODE_LABEL at TAIL. i2 = PREV_INSN(label) → the insn before the label. In the layout, before TAIL label is case4's code (the last arm). Hmm, but the merge happened between two jumps to the same label via the jump_chain loop (line 1993, minimum 2).

Actually the merge: case1's tail ends `j TAIL`? No wait — case1's tail is `if (unk1C < 0x10) goto TAIL; goto HITSTUN;`. So case1's tail ends with `j HITSTUN`, not TAIL. And case3's body also ends with `j HITSTUN`. Both jump to HITSTUN. So the jump_chain loop compares the two `j HITSTUN` insns with minimum=2.

Then find_cross_jump(j1, j2, 2): i1 = prev_nonnote_insn(j1) = the `nop` (delay slot? at post-reload/dbr, the delay slot may already be filled with nop as a real insn). i2 = PREV_INSN(j2) skipping notes/labels = nop. Match (nop==nop), minimum→1. Then slti match, minimum→0. Then sw match, →-1. addiu match... etc. It walks all the way back until a mismatch or a label. It would merge the whole counter tail.

But hold on: the delay slot. Before dbr_schedule? Cross-jump runs BEFORE dbr_schedule (line 3142 vs 3167). At that point, does each jump have a nop delay slot? No! Delay slot filling happens in dbr_schedule later. But the target listing shows `beqz v0,a20; nop` and `j a70; nop`. The nops after branches in the object are inserted by dbr_schedule (or are they already there?). At post-reload pre-dbr, a jump insn is just `j label` with no delay insn; the nop appears in the final assembly. Hmm, but the mask diff operates on the final object (after dbr). Fine.

So cross-jump at that point compares j1 vs j2 (both `j HITSTUN`), then backward through slti, sw, addiu, lw... The target's original source prevented this. 

How? The RTL difference must be in the compared suffix. At post-reload, all pseudos are hard regs. The two copies in the target use identical hard regs (v0, s0). So the RTL is identical... unless the ORIGINAL source produced a different *instruction* that later got transformed to the same bytes by dbr/reorg? Hmm, but the comparison happens before dbr.

Wait, maybe the difference is in the delay-slot nop! At cross-jump time (before dbr), there are no delay nops. The `nop` insns I see in the target between lw and addiu (load delay) — those ARE real insns at cross-jump time? The load-delay nop between `lw v0,28(s0)` and `addiu v0,v0,1` is inserted by...? On MIPS, the assembler inserts nops for load delays at assembly time (the `.set noreorder` is used and gcc emits nops explicitly? In gcc 2.7.2 MIPS, the scheduler (sched2, pre-reload?) and `dbr_schedule` insert nops for load delays: the MIPS port has a `MACHINE_DEPENDENT_REORG`? Actually the MIPS md has `HAVE_POST_DELAY`? The nops in the object between lw and its use are emitted by the assembler unless .set noreorder. The build pipeline likely uses .set noreorder. Hmm.

But the diff tool masks nops? No: "objdump -drz so runs of nops are NOT collapsed". The nops are in the object.

Key: cross-jump compares insns including these load-delay nops (they're real insns if gcc emits them). Either way, both copies have the same.

So how did the original avoid the merge? Maybe the original had the two copies using *different hard registers* in one position. Since renumbered_equal maps registers consistently within an insn, and it's called per insn pair, a difference like copy A: `lw v0, 28(s0)` vs copy B: `lw v1, 28(s0)` would still match (renumber v0↔v1). But if the same insn has a constraint like `sw v0, 28(s0)` in A vs `sw v0, 28(s1)` in B... renumber maps s0↔s1 within that insn — fine. Consistency is per-insn.

For an insn where the renaming is inconsistent: `slti v0,v0,16` in A vs `slti v0,v1,16` in B → A's v0 would have to map to both B's v0 and v1 → inconsistent → MISMATCH! And the final machine code would differ (slti v0,v1,16 vs slti v0,v0,16) — different bytes. Unless... hmm no.

BUT: consider the case where the same hard reg appears twice in A and two different regs in B, and in the final code B's instruction is `slti v0,v0,16` — meaning B's two pseudos both became v0. But at post-reload there are no pseudos... unless reload created spill/reload copies? No.

Hmm wait — maybe cross-jump at that stage sees pseudos that reload did not eliminate? No, reload_completed means all pseudos replaced.

Let me reconsider: is it possible the target's two copies were NOT merged simply because the pass only merges when `jump_back_p` etc.? For unconditional jumps the jump_chain loop requires both jumps to be in the chain of the same label. They are. Hmm.

Unless the two `j HITSTUN` jumps are not in the same jump_chain because one was converted to a conditional? Look at target: case1 at 0x95c `j a70` (TAIL), and case3 at 0x9dc `j a70`. Wait! Let me re-read the target disassembly:

At 0x940 (case1 tail): lw;nop;addiu;sw;slti;beqz a20;nop; j a70. So the tail ends with `j a70` (TAIL), not `j HITSTUN`! The `beqz v0,a20` branches to HITSTUN (a20). So the code is: if (unk1C < 0x10) goto TAIL (j a70); else falls to HITSTUN? No: `beqz v0,a20` = if !(unk1C<16) goto HITSTUN; then nop; j a70 = goto TAIL. Yes! So the structure is `if (unk1C < 0x10) goto TAIL; goto HITSTUN;` compiled as beqz to HITSTUN then j TAIL.

So the converging jumps are the two `j TAIL` (a70) jumps! Both jump to TAIL. Cross-jump compares them: minimum 1 first (find_cross_jump(insn, JUMP_LABEL(insn)=TAIL label, 1)), then the jump_chain loop with minimum 2.

Both `j a70` jumps are in the jump_chain of the TAIL label. So they get compared with minimum=2. Backward: nop (delay? not yet), slti? Wait the insn before `j TAIL` is the delay-slot nop? At cross-jump time no nops yet; the insn before `j TAIL` is `beqz v0, HITSTUN`. Then the walk: i1 = prev_nonnote_insn(j TAIL) = beqz (conditional jump insn). i2 = prev of the other j TAIL = beqz. Both JUMP_INSNs, same pattern? The beqz targets differ: both target HITSTUN (a20)! Same label → rtx_renumbered_equal_p matches. minimum 2→1. Next: slti, match → 0. Next: sw match → -1. etc. Merge.

Hmm, so still merges.

Unless the two beqz insns have different JUMP_LABELs. In the target both are beqz v0,a20 — same.

OK so how?! Maybe the original source had *different code* in one copy that compiles to the same bytes only after dbr fills delay slots? At cross-jump time, the delay slot insns aren't there. Could the original have had a *conditional* difference: e.g. case1's tail written as `if (unk1C >= 0x10) goto HITSTUN; goto TAIL;` → slti; bnez? Let's see: `x >= 16` → slti v0,x,16; beqz v0, TAIL... Hmm that gives beqz to TAIL and fallthrough to HITSTUN? That produces different branch structure: slti; beqz v0,TAIL; nop; j HITSTUN. Different bytes (j HITSTUN instead of j TAIL). The target has j TAIL. So case1 and case3 both have the same branch direction.

Hmm, unless one copy in the ORIGINAL source was written differently but *jump optimization* canonicalized it to the same RTL. Then cross-jump would merge anyway (same RTL).

Wait, maybe I'm wrong that both target copies end with `j a70`. Let me look again at the target region 0x940-0x95c:
```
940: lw v0,28(s0)
944: nop
948: addiu v0,v0,1
94c: sw v0,28(s0)
950: slti v0,v0,16
954: beqz v0,a20
958: nop
95c: j a70
960: nop
```
and case3 at 0x9c0-0x9dc:
```
9c0: lw
9c4: nop
9c8: addiu
9cc: sw
9d0: slti
9d4: beqz v0,a20
9d8: nop
9dc: j a70
9e0: nop
```
Identical. Both jumps to a70.

So find_cross_jump would compare them. The jump_chain for label a70 (TAIL): which jumps target TAIL? Many: case0 at 0x91c j a70, case1 at 0x95c, case2 at 0x990 j a20 (HITSTUN), case3 at 0x9dc, case4 at 0xa28 j a70... The merge picked case3's copy as the survivor and retargeted case1's `j a70` to `j 9a4` (the tail start). Yes.

So why didn't the original merge? The answer must be a difference in the RTL that is invisible in the final bytes... OR the merge DID happen in the original too but at a different place? No, the target clearly has both copies.

Hmm! Wait. Maybe the original source had different *register allocation* in one copy such that the final bytes are the same but the RTL differs in a way that renumbered_equal rejects... but the final bytes are identical, so at post-reload the RTL must be identical (same insn codes, same hard regs). UNLESS the two copies' RTL differ in a non-register field that doesn't affect encoding: e.g., REG_EQUAL notes (not compared), or a MEM alias set, or... the *jump label target* is the same.

OR the two copies were in different *sections*? No.

OR: cross-jump ran, but the two copies were separated because at that moment one of the jumps wasn't `simplejump_p` (e.g., it was a conditional). Hmm.

OR: the merge is prevented by a *barrier* in the RTL that is zero-byte and real-C-generated. What RTL insns emit zero bytes and are not USE/CLOBBER? A CODE_LABEL (zero bytes). We discussed: a label in the stream between the compared insns. Let's revisit with the walk direction and minimum:

find_cross_jump(j1, j2, 2):
- i1 = prev_nonnote_insn(j1). If the insn before j1 is a CODE_LABEL (in j1's stream), then `--minimum` → 1 and break. last1=0 → no merge. 

So a CODE_LABEL immediately before one of the two `j TAIL` jumps prevents the merge entirely! And labels emit zero bytes!

How to get a CODE_LABEL between the beqz and the `j TAIL` in one copy, generated by real C and used (so not deleted)?

Source: 
```
if (unk1C < 0x10) {
    L_TAIL1:  goto TAIL;
}
goto HITSTUN;
```
A label before `goto TAIL` must be referenced to survive. What if it's referenced by a goto from the *other* arm... which would change code.

Hmm, what if the label is referenced by a jump that is *conditional and falls through to the same place*? e.g.:
```
if (unk1C < 0x10) { if (0) ... }  
```
no.

What about using a `switch` with a case label? Case labels are CODE_LABELs! In C, a `switch` generates a jump table or comparisons. But a switch with one case and default... hmm, could generate labels.

Alternatively, `goto` labels referenced by a jump that jump_optimize threads away *later* (at the same pass or after)? The cross-jump runs in the same jump_optimize call; if the label is still referenced at cross-jump time but its jump gets deleted before the cross-jump phase... order matters.

Hmm, this is getting deep. Let me look at how the project's other cross-jump MATCHes were cracked — e.g. func_8014F74C: "invert the `!= 0x1D` guard so the two `return ret` collapse into one return block; jump_optimize then picks bne-to-return + move delay slot as the target" — that's a different direction.

And func_80180100: "field-direct &= and -- on s0->unkAC (no temps), dead pad[2] dropped". That's about a launder/pin.

Let me grep moves.md for "crossjump" MATCHes (not walls).

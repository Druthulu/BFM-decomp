---
ts: 2026-11-06T13:16:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AV5mZx8gBdCHIPruf6w9
---
No rtl.c. So rtx_renumbered_equal_p implementation not available. But I recall: in gcc 2.7.2, `rtx_renumbered_equal_p` uses a local array `int reg_map[FIRST_PSEUDO_REGISTER]` initialized to -1 at the start of each call, and it's recursive. So consistency is per-insn call. So a single insn with two regs in one copy mapping to two different regs in the other must still be a consistent bijection *within that insn*. 

Consider the compare insn: (set (reg v0) (lt (reg v0) (const 16))) — the same reg appears twice in one insn. If copy B has (set (reg rZ) (lt (reg rY) (const 16))) with rZ != rY, then the map rY→? and rZ→? — but copy A's single reg must map to both → inconsistent → unequal! And final code: if rY and rZ are both allocated v0 (because rY dies at this insn? Actually the compare reads rY and writes rZ; if rY is dead after, local-alloc can assign both v0? No — local-alloc assigns a hard reg to a pseudo based on its live range; two pseudos whose live ranges overlap can't share. Here rY is live until the compare, rZ born at the compare — their live ranges are adjacent (rY's last use is in the compare, rZ defined in the compare). local-alloc's block_alloc processes in order and can give the same reg if not simultaneously live (qty_phys_copy etc.). Actually in the target, the addiu writes v0 and the slti reads AND writes v0: `addiu v0,v0,1; sw v0,28(s0); slti v0,v0,16`. So the slti's dest and src are the SAME v0. In RTL, if dest and src are different pseudos that both get v0, we'd need `move v0, v0`? No: slti v0, v0, 16 with dest pseudo Z and src pseudo Y both assigned v0 → the instruction becomes slti v0,v0,16 — perfectly fine, no move needed! local-alloc can assign Z to v0 even though Y is live up to this insn, as long as Y is not live after. Local-alloc's qty handling: at the start of the insn, Y is live; Z is born. combine_regs may tie them (copy? no). But block_alloc assigns registers greedily by death: a qty dies at its last use, freeing the reg for the next qty. Since Y's last use IS the slti and Z is defined by the slti, local-alloc typically assigns the same hard reg (that's the "local-alloc reuses a dead hard reg" behavior — and the wall tag lreg-dead-hardreg-reuse says the opposite can happen too).

How to get a distinct pseudo Z for the slti dest from real C? The compare result is a condition code pseudo in RTL: (set (reg:SI Z) (lt (reg:SI Y) (const_int 16))). Z is created by the compare expansion. In C, `if (x < 16)` — x is the pseudo Y, and Z is the cc pseudo. Hmm, so there's already a separate pseudo. In copy A the same structure exists. So both copies: Y and Z.

So how did they become equal? Because both copies have the same structure: (set Y1 (plus (mem) 1)), (set (mem) Y1), (set Z1 (lt Y1 16)), (if_then_else ...). renumbered_equal within each insn maps Y1↔Y2 etc. Consistently across insns? Each insn compared separately, so no cross-insn consistency needed. Thus any consistent per-insn renaming works.

To break it we need an insn where the mapping is inconsistent within that insn. E.g., make the compare use a different pseudo than the one stored: (set Z (lt W 16)) where W is a copy of Y. Then W is defined by a move: (set W Y). If local-alloc gives W = v0 (same as Y, since Y dies there), the move becomes `move v0,v0` → deleted (if gcc deletes noop moves) → identical code! And at jump2, the extra move insn breaks the cross-jump (pattern differs: copy insn vs nothing). 

So the C: 
```
p->unk1C += 1;
{ s32 t = p->unk1C; if (t < 0x10) goto TAIL; }
```
But cse would forward `p->unk1C` from the store into t (cse after combine sees the store and the load, and forwards). Unless we prevent cse. Hmm. cse would replace (mem 28(p)) with Y → t = Y → move Y,Y? Actually `t = p->unk1C;` after `p->unk1C = Y` — cse's store forwarding: cse records the stored value for the MEM and substitutes the load with Y. Then t is just Y (a copy which may be deleted at expand? no, expand already happened; cse replaces the reg with Y via canon_reg, deleting the move). So it'd be identical again.

What if we use a `do{}while(0)` between the store and the load? That splits the EBB for cse, so cse won't forward across the block boundary... Actually cse's store forwarding is within an EBB; a block boundary at the end means the store's value isn't forwarded into the next block (unless cse's global mode with reg availability — the stored value isn't in a reg across blocks). Hmm, but the load would then actually reload from memory → extra lw insn. No good.

Alternatively, make the move not fold: use a *different mode* temp, e.g. `u16 t = p->unk1C; if (t < 0x10)`: this inserts a zero-extend (andi 0xffff) → different code (target has none). No.

Hmm, what about using the value in a way that gcc keeps a copy but the allocator eliminates: e.g. `if (p->unk1C < 0x10)` where the loaded value is already in a pseudo... 

Let me step back and look at how the original source might have differed. The target keeps both copies. Consider: maybe the original source for case 1 was:
```
if (++p->unk1C < 0x10) goto TAIL;
goto HITSTUN;
```
and case 3:
```
p->unk1C++;
if (p->unk1C < 0x10) goto TAIL;
goto HITSTUN;
```
`++p->unk1C < 0x10`: expand produces (set (mem) (plus (mem) 1))? No: pre-increment on a memory location: gcc computes in a register, stores, and the value of the expression is the new value. Same RTL.

Alternatively, one copy could use `if (p->unk1C++ < 0x10)`? Post-increment compares the OLD value → different code (slti on the pre-add value). Target compares the new value (addiu then slti on v0). So no.

What if one copy used a pointer alias for the load/store, e.g. `s32 *u = (s32 *)(param_1 + 0x1C); u[0] += 1; if (u[0] < 0x10)`? The MEM address would be `(reg u)` in both the load and store. cse would propagate u = param_1+0x1C if u is a simple add... cse's canon_reg substitutes registers that are known equal. An address computed by `leasiu` gets a REG_EQUAL note? If u is a local pointer assigned once, cse records (reg u) == (plus (reg p) (28))? cse does record equivalent expressions for address computations via `(set (reg u) (plus ...))` → yes, cse's make_regs_eqv would substitute u with the plus expression at each use. Then RTL identical again.

Unless... the use is across a basic block boundary? No.

Hmm. OK, maybe the difference is in the store/load *width* or the insn sequence that produces the same bytes via different RTL: e.g., `p->unk1C = p->unk1C + 1` vs using a `u32` temp: the add might be in DImode? No.

Let me consider that the answer is a WALL for item1. But before that, let's try the empirical lever-free exploration: there are standard move families. We have a budget of 20-30 min and ≥30 scored tries for a WALL. We can generate ~30 variants quickly with a script: variations of the two copies (temp for compare, pointer alias, do-while placement, reordered statements, etc.) and score each via sc.sh. That's the pragmatic approach. If none scores 0, WALL with best.

But hold on: maybe the whole function isn't only about the cross-jump. Removing the barrier gives 23; if we can't restore both copies, no MATCH. The other 22 mismatches are just branch offset shifts caused by the length drift (all the `j a54` vs `j a70` differences). Once the length matches (196 ins), those offsets likely align. So the ONLY thing needed is keeping both copies.

Let me look at how the target's two copies differ in RTL by checking the cc1 dumps of the CURRENT source (which has the barrier) — the barrier itself makes the RTL differ, so no info. But the original source from which the binary was built... The target has both copies, so whatever source produced it had unequal RTL. Since our job is to find *a* source that does, any zero-byte RTL difference works.

Zero-byte RTL differences that survive to jump2 but vanish at allocation:
(a) A copy/move insn that becomes move r,r and is deleted.
(b) A pseudo that is coalesced into another.
(c) An insn with a REG_EQUAL note difference? No, patterns compared.
(d) Different but equivalent patterns that produce the same final code: e.g., `(set (reg) (plus (reg) (const)))` vs `(set (reg) (plus (const) (reg)))` — canonicalized by fold? If not canonicalized, the same machine code! e.g. `x + 1` vs `1 + x`? fold canonicalizes commutative ops to put constants second. Hmm. What about `x - 1` vs `x + -1`? fold canonicalizes.
(e) A `(set (reg) (reg))` that becomes a no-op move — (a).
(f) A `(clobber ...)`? no.

Does gcc 2.7.2 delete `move r,r`? Let me check final.c / toplev pass order. In 2.7.2 there's `delete_noop_moves` in final.c? Let me grep the reference dir (no final.c!). Files: we have regclass, reload, reorg, sched, cse, combine, flow, global, local-alloc, loop, caller-save, recog, expr, stmt, calls, toplev, varasm, integrate, unroll, fold-const, c-convert, c-typeck, convert, emit-rtl, expmed, optabs, basic-block.h, hard-reg-set.h, loop.h, regs.h, rtl.h.

No final.c, no rtl.c, no insn-emit. But regs.h/rtl.h have macros.

Hmm. Let's check local-alloc.c: when two qty's get the same hard reg, the move between them becomes redundant and is deleted later by `regclass`? Actually the pass that deletes no-op moves in 2.7.2 is `final()`? I believe there's a function `delete_noop_moves` in final.c. Since final.c isn't in the reference set, can't confirm. But empirically, gcc at -O2 does delete `move a,a` on MIPS (I'm fairly confident; the MIPS md has a `movsi` pattern and the final pass calls `delete_noop_moves` in `final_start_function`? Hmm.)

Actually! A cleaner idea from the moves table: func_8017D508 WALL jump2-crossjump-arms — "the two identical branch arms are byte-identical 8-insn blocks; jump2 cross-jump renames regs so const-vs-var stores do not differ". And func_80184E8C WALL jump2-crossjump-fallthrough. And func_80180A38 WALL. So cross-jump with real C is a known WALL family in this project. Item1 may well be a WALL.

But note item 4 has THREE barriers, item 5 has THREE, item 3 one, item 2 one. Those barriers are scheduling barriers, not cross-jump, and do-while may replace them. Let's prioritize: items 2,3,4,5 have sched barriers where do{}while(0) or statement reordering often works (C0535). Item 1 is cross-jump, likely WALL.

Time budget: 20-30 min per item. Let's be systematic and quick.

Let me do item 2 next? Or continue item1 with a quick batch of ~10 candidates (temp/pointer/order variants), then decide.

Actually, let me think once more about item1. There's a known zero-byte trick for cross-jump: make one copy's *last* insn before the converging jump differ by using a `do{}while(0)` — no, notes are skipped.

Wait, actually: look at the walk again. i2 = PREV_INSN skipping NOTEs and CODE_LABELs. i1 = prev_nonnote_insn (skips NOTEs but NOT labels). If i1 is a CODE_LABEL → minimum--, break. If i2 is a CODE_LABEL it's skipped. Hmm.

What if the two copies are separated by a label in one of them? E.g., in case 3, the target's source has a label at the end of the tail (the shared TAIL label is elsewhere). If we insert a label (via a goto target) between the compare and the jump... A CODE_LABEL in i1's stream: i1 = prev_nonnote_insn → returns the CODE_LABEL (labels are not notes) → `if (GET_CODE (i1) == CODE_LABEL) { --minimum; break; }`. minimum starts at 2 → becomes 1 → no merge (needs ≤0). And a CODE_LABEL emits zero bytes! 

But can real C place a label there without changing code? A label is generated for a goto target. If we add a label at the end of one copy and a goto to it from... the code would need to jump there, but if the label is the target of a goto that's the *fallthrough*, the goto becomes a no-op? Hmm, a label that's only targeted by a jump from elsewhere adds a branch. But if we make a label the target of a *forward* goto that is optimized into fallthrough... 

Simplest: add a label at the end of the case-3 copy and a `goto` to it from just above? Like:
```
p->unk1C += 1;
if (p->unk1C < 0x10) goto TAIL;
goto HITSTUN;
L_DUMMY: ;   // unused label
```
An unused label: does gcc emit a CODE_LABEL rtx for an unreferenced label? GCC deletes unused labels (delete_insn / `if (LABEL_NUSES==0) delete`). In jump_optimize, unused labels are removed early (`delete_unreferenced_labels`). So no.

What if we make it referenced but the reference is optimized away? e.g.:
```
if (0) goto L;
```
fold removes it at the tree level before RTL → no label.

Hmm. A label with a real goto that's redundant: 
```
p->unk1C += 1;
if (p->unk1C < 0x10) { goto TAIL; }
L: goto HITSTUN;
```
`goto L` where L is the next insn: expand emits a jump to the label; jump_optimize's `jump_to_next_insn` deletes the jump insn (it's a jump to the immediately following label → deleted as redundant). But the CODE_LABEL remains (it's referenced by... nothing after the jump is deleted; the label becomes unreferenced and is deleted too). Hmm, order matters: in jump_optimize, `delete_unreferenced_labels` runs? If the jump is deleted first, the label becomes unused and may be deleted in a later pass (jump_optimize runs multiple times). At jump2 (the pass doing cross-jump), is the label still there? 

The pass order (toplev.c): ... combine, ... jump_optimize (jump2) then cse2? Let me check toplev.c pass order. Actually cross-jumping happens in jump_optimize, which is called: after expand? no. Let me grep toplev.c.

Alternatively: a label that's the target of a jump from the OTHER copy? That would be cross-jump's own doing.

Hmm, but there's a subtlety: `if (unk1C < 0x10) goto TAIL;` — the label TAIL is at the end. In case 3, the code falls through to `goto HITSTUN`. What if we write:
```
if (p->unk1C < 0x10) goto TAIL;
L_H: goto HITSTUN;
```
with `L_H:` referenced by a goto elsewhere in the function that currently goes to HITSTUN? E.g., change another `goto HITSTUN` (from case 2) to `goto L_H;`. That label is then used, sits right before `goto HITSTUN`, and the machine code: the extra label is zero bytes; the jump from case 2 targets the same address as HITSTUN (since L_H: goto HITSTUN is a jump, the label's address is the jump insn, and HITSTUN is elsewhere). Wait, L_H labels the `goto HITSTUN` jump insn. A jump to L_H jumps to that jump (extra jump-around-jump, which jump_optimize would thread). Hmm.

Better: place the label at the very end of case 3's tail but make it a target of a jump that already exists. Actually, we want a CODE_LABEL in the i1 stream of copy A (or i2 of copy B) between the compare and the converging jump. Let me look at which pair merges. The merge is between case1's tail and case3's body, converging at... The merged copy is case3's (later one) and case1 jumps to it. In mine: case1 at 0x940 has `j 9a4` (jump to case3's copy). Wait, but case1's tail is `if (unk1C<0x10) goto TAIL; goto HITSTUN;` and case3's identical. Cross-jump merged the whole tail: case1's `if(...)` branch bnez 9a4? Hmm at 0x930: `bnez v0,9a4` — that's case1's `if ((unk1C & 3) == 0)`. Hmm no, 0x930 is `bnez v0,9a4` where v0 = unk1C & 3; if nonzero skip the call → jumps to 9a4, which is the counter tail. In target it jumps to 0x940 (case1's own tail). So the merge was of the *counter tails*: case1's tail (at 0x940) got replaced by a jump to case3's tail (0x9a4), and the code that branched to case1's tail (0x930 bnez) was retargeted to 9a4 directly.

So the cross-jump merged e1 = case1's tail stream (ending in `goto HITSTUN`) with e2 = case3's. e2 = JUMP_LABEL of some jump = HITSTUN (a20). The converging jump is `j a20`? Wait, the tail ends with `goto HITSTUN` = j a20 (the HITSTUN label). Both copies end with `j HITSTUN`. Cross-jump of the two `j HITSTUN` jumps: find_cross_jump(insn, JUMP_LABEL(insn), 1, ...) at line 1978 — minimum 1! Hmm, with minimum=1, one matching insn (minimum-- → 0) suffices. The two jumps both target HITSTUN. Then it compares backward: slti (match, minimum 0), then sw, addiu, lw, nop... it would merge a LOT. But minimum for jump-to-label case is 1, and there's a check that the target is not a "cross-jump of jumps"? Anyway.

Since minimum=1 for two jumps to the same label, a single zero-byte CODE_LABEL difference breaks it (minimum-- → ... hmm, if i1 is a label, minimum-- makes it 0, then break; then `minimum <= 0 && last1 != 0` — if last1 was set by a previously matched insn, it still merges! Because the label decrements minimum to 0 and breaks. Hmm: minimum starts 1; first iteration compares the insns before the jumps: if they match (slti), minimum → 0, last1 = slti. Second iteration: i1 = label → --minimum → -1, break. Then minimum <= 0 and last1 != 0 → MERGE (the suffix from last1 to e1). So a label only reduces the matched suffix by one insn; it doesn't prevent the merge unless it's the FIRST comparison.

Hmm wait, in the loop the label check happens after `i1 = prev_nonnote_insn(i1); i2 = PREV_INSN(i2) skip notes/labels`. So if i1 is a label at the first step, minimum-- → 0, break, last1 = 0 → no merge. So the label must be immediately before the converging jump, i.e., between the last insn of the copy and the `j HITSTUN`. But in the source, the converging jump is `goto HITSTUN;` — a label right before it means `L: goto HITSTUN;` and L is placed after `if(...) goto TAIL;`. So:

```
if (p->unk1C < 0x10) goto TAIL;
L_HIT: goto HITSTUN;
```
with L_HIT used as a jump target from somewhere. Then the code is: slti/beqz ...; L_HIT: j HITSTUN. The label is immediately before the j. Then find_cross_jump between the two `j HITSTUN`s: i1 = prev_nonnote_insn(j) = CODE_LABEL L_HIT → minimum-- (1→0), break, last1=0 → no merge. 

But we need L_HIT to be a real, used label (else deleted). And a jump to L_HIT must exist. Where? We could change case 2's `goto HITSTUN` to `goto L_HIT`. But then case 2's code jumps to L_HIT which is a jump insn; jump_optimize's jump threading (`jump to a jump`) will redirect it to HITSTUN and delete/keep the label? If the label becomes unreferenced, it's deleted. Hmm.

Alternative: make the label the target of the `if` inside the same block: 
```
if (p->unk1C < 0x10) goto TAIL;
L_HIT: goto HITSTUN;
```
with L_HIT reached by fallthrough only → unreferenced.

We need a reference that survives. What if we invert: 
```
if (p->unk1C >= 0x10) goto L_HIT;
goto TAIL;
L_HIT: goto HITSTUN;
```
Here L_HIT is referenced by the conditional branch. The code: slti v0, 16; beqz v0, TAIL? Hmm let's see: `if (x >= 16) goto L_HIT;` → x<16 → slti; then `goto TAIL` → j TAIL; then `L_HIT: goto HITSTUN` → j HITSTUN with label. Machine code: slti v0,v0,16; beqz v0, L_HIT_addr; nop; j TAIL; nop; L_HIT: j HITSTUN; nop. That's 6 insns (slti, beqz, nop, j, nop, j) vs target 4 (slti, beqz, nop, j HITSTUN). Extra j + nop. Not byte-equal.

Hmm. Unless the branch target's block gets merged: the `goto TAIL` and `L_HIT: goto HITSTUN`... no.

OK, what about the label being the target of a jump that is *identical* to another and gets threaded to the same place, keeping the label? jump_optimize's `jump_to_next_insn` / `redirect_jump` deletes labels only when unreferenced. If two jumps target L_HIT, threading redirects them to HITSTUN and then the label dies. Unless threading doesn't happen because L_HIT is not immediately a jump? L_HIT: goto HITSTUN is a jump-to-jump; jump_optimize does thread those (`if (JUMP_LABEL insn is a JUMP_INSN, redirect`) — yes, `jump_optimize` has "thread jump to jump" logic.

Hmm. What if the label is at the end of the block and the jump after it is not a plain goto but a return? No.

Alternative zero-byte approach: the `lw v0,28(s0); nop` — the nop is a load delay. The target's copy has `lw; nop; addiu`. Interesting: the nop between lw and addiu is because the addiu uses v0 (load delay). So the RTL has lw then addiu. 

What if in one copy we write the load and add differently, e.g. `p->unk1C = p->unk1C + 1` vs `p->unk1C += 1`? Both same.

What if one copy uses `(p->unk1C)++` and the other `p->unk1C = p->unk1C + 1`, and the RTL differs in the MEM's alias set or in a REG_EQUAL note? Patterns are compared, notes not (except REG_EQUAL special case).

Hmm, what about the *volatile* qualifier on one copy? `*(volatile s32 *)&p->unk1C += 1` — volatile MEM: the RTL pattern is the same (MEM rtx); does rtx_equal_p compare the volatile flag? The MEM rtx has MEM_VOLATILE_P in its attributes (rtl.h: MEM_VOLATILE_P is a bit in the rtx's `volatil` field, part of the rtx union — actually in gcc 2.7.2 MEM_VOLATILE_P is `XWINT(rtl, 1) & 1`? It's stored in the rtx as a flag). rtx_equal_p for MEM compares the address expression only, I think — `case MEM: return rtx_equal_p(XEXP(x,0), XEXP(y,0))`. So volatile wouldn't matter. But volatile also affects optimization (no cse, no combine of loads/stores) → code differs (extra reloads). No.

Hmm, what about making the *store* in one copy go through a different MEM but the same address: `((Unkstruct_800B5CB8 *)p)->unk1C` vs `((Unkstruct_800B5CB8 *)(p + 0))->unk1C` — same.

Wait, what about a *different struct type* with a different alias set: the MEM's address is the same but the alias set differs. rtx_equal_p doesn't compare alias sets, but `rtx_renumbered_equal_p`? Probably also just the address. Hmm, but cse uses alias sets, and the scheduling might change. Risky.

Let me now consider the possibility that the target's two copies came from *different expression trees that fold to the same RTL* — impossible, if RTL is the same they'd merge. So the original source must have had a genuine RTL difference that vanished at allocation. The most plausible: a copy that local-alloc coalesced (move r,r) or a pseudo pair that got the same hard reg in a non-consistent way.

Specifically: consider the compare. In the target, `slti v0,v0,16`. If in one copy the C is:
```
iVar1 = p->unk1C + 1;   // iVar1 is the function-wide variable!
p->unk1C = iVar1;
if (iVar1 < 0x10) ...
```
and in the other copy:
```
p->unk1C += 1;
if (p->unk1C < 0x10) ...
```
The function has a variable `iVar1` used elsewhere (case 0, 2, 4). In copy A, iVar1 is live across... hmm, it's dead after. cse would still equate iVar1 with the stored value. But maybe cse's value numbering treats them the same and makes them the same pseudo → still equal.

Alternatively: use a variable that is live elsewhere in the function, e.g. reuse `iVar1` for the increment in one copy. If iVar1 is live from an earlier block (it's dead there), the allocator must give it a reg consistent with its other uses (v0 elsewhere?). Hmm, iVar1 in case 0 is the call result, in v0. Then in case1's tail, if we set iVar1 = p->unk1C + 1, iVar1 is live from the call result (dead) to this use — local-alloc might assign v0. Then the compare uses iVar1. RTL: (set (reg iVar1) (plus (mem) 1)); (set (mem) iVar1); (set cc (lt iVar1 16)). Same as before, just the pseudo is a named one. renumbered equal → merge.

The difference must be STRUCTURAL. 

New idea: make one copy's compare use a *memory* operand instead of the register: `if (p->unk1C < 0x10)` — if cse does NOT forward the stored value, the compare would reload → extra lw. Not allowed.

New idea: swap the store and compare order? `if (p->unk1C + 1 < 0x10)` and store after? Code differs (slti before sw). No.

New idea: use a *different* comparison operator that yields the same slti: `if (p->unk1C < 0x10)` vs `if (0x10 > p->unk1C)`. fold canonicalizes to the same.

Hmm, unless... fold doesn't canonicalize in 2.7.2? It does (swap_commutative_operands / canonicalize).

What about `if (!(p->unk1C >= 0x10))`: fold_truthop? It becomes (lt ...). Same.

OK, maybe use a completely different route for the second copy that yields the same 8 instructions: a `do { ... } while (0)` changes nothing at jump2 (notes skipped) — right.

What about `while (0) { }`? Same notes.

What about a `switch`? No.

Let me try the empirical approach now: generate variants and score. Variants for the case3 tail:
1. temp for compare: `iVar1 = p->unk1C + 1; p->unk1C = iVar1; if (iVar1 < 0x10) goto TAIL;`
2. temp + do-while around the if.
3. pointer alias for unk1C.
4. post-increment in one copy... code changes.
5. compute via `+= 1` vs `= p->unk1C + 1`.
6. `if ((s32)(p->unk1C) < 16)`.
7. reorder: store then compare (already).
8. use `!` form.
9. swap case order? no.
10. put the tail in a helper? no.

Given cse's power, most will fold. Let me just try ~8 quickly.

Actually WAIT. Important insight: cse runs BEFORE jump2? Let me check the pass order in toplev.c. If cse2 runs *after* jump2, then RTL differences introduced by C-level constructs that cse would fold might still be present at jump2! Let me check toplev.c pass order.

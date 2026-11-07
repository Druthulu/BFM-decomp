---
ts: 2026-11-06T21:53:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xuEbwnwtzvLiMoDCUurA
---
Key checks that return 0:

- `use_crosses_set_p (src, INSN_CUID (insn))` when not all_adjacent. Our insns ARE adjacent (i1=copy, i2=li, i3=beq) — `all_adjacent` when succ? For i1 with succ=i2: next_active_insn(i1)==i2 and next_active_insn(i2)==i3 → all_adjacent true → the use_crosses_set check is skipped.

- `REG_NO_CONFLICT` note on dest in i3 or succ → return 0! Interesting: if the copy insn has a REG_NO_CONFLICT note for dest, combine refuses. REG_NO_CONFLICT comes from -fno-conflict... probably not available in C.

- `find_reg_note (i3, REG_NO_CONFLICT, dest)`.

- "Don't extend the life of a hard register unless..." — for src being a hard register with ! REG_USERVAR_P. Our src is a pseudo.

Hmm.

- `FIND_REG_INC_NOTE (i3, dest)` — if dest is incremented in i3 (post-inc addressing) — not applicable.

- `reg_used_between_p (dest, succ, i3)` — only when !all_adjacent.

So combine will merge adjacent copies. The only real blockers: REG_NO_CONFLICT notes, volatile, asm.

Wait — what about the `all_adjacent` requirement: i1 = copy, i2 = li v0, i3 = beq. But is `li v0,1` really between? Yes.

Hmm, but combine also tries i1=li (105) and i3=beq (108) as a 2-insn combination. For the copy (95) to be combined with the beq, we need i1=95, i2=?, i3=108.

Actually maybe the merge happened differently: combine might have merged the sign-extend sequence and the copy in a different order. Whatever — the outcome: no move.

So the answer: with plain C, a reg-reg copy adjacent to its use WILL be combined away. The only way to keep it is a block boundary or a non-copy RTL.

Block boundary: the copy must be in a different basic block than the compare, and combine must not cross labels. So: put the copy at the end of the ELSE arm... but it must also execute on the then path.

UNLESS: we restructure so the then arm jumps to the copy's label, i.e., the copy is at a label that is a jump target — that IS the join. Combine doesn't combine across a code_label? Actually combine's try_combine can combine i1 = the last insn before a label and i3 = the insn after? No: combine works on consecutive insns with prev/next, and CODE_LABELs between them break adjacency? `next_active_insn` skips labels and notes! Let me check: next_active_insn skips CODE_LABEL, NOTE, BARRIER. So combine can combine across labels?? There's a check: `if (GET_CODE (insn) == CODE_LABEL) ...`. Hmm, in try_combine, it uses `prev_nonnote_insn` which does NOT skip labels. So a CODE_LABEL blocks.

So if there is a code_label between the copy and the compare, combine can't merge. In the target's RTL, the join label (63c4) is exactly at the copy — before it, not between.

Hmm, but what if the label is between the copy and the compare? I.e., the copy at the end of the else arm, then label, then compare? Then the then arm would jump to the label (skipping the copy) — wrong value.

Unless the copy is BEFORE the label and executed by both paths... only if it's at the end of both arms. Which duplicates it.

Hmm, what about the block structure: the then arm sets iVar2=1 and jumps to the join; the else arm falls through to the join. What if we place the copy at the end of the else arm AND in the then arm (before its jump)? Then the join has only the compare. Extra insn in the then arm: `move v1,a0` — but wait, in the then arm iVar2=1 is a constant, so `iv2c = iVar2` folds to `li v1,1`... Let me think: would combine fold `li a0,1; move v1,a0` into `li a0,1; li v1,1`? Or would it merge to `li a0,1` and use a0 in the compare? Since the then arm's copy is in a block that ends with a jump, and the compare is in the join block, combine can't merge across the jump. So it would keep `move v1,a0` in the then arm. That's 1 extra insn vs target. Total 57 ≠ 56.

Unless the target's then arm... target insn 21 is `li a0,1` and then 22 `j 63c4` with delay 23 `move t3,zero`. So the then arm has 2 insns; ours would have 3. No.

OK so different tactic: make the copy NOT a reg-reg copy in RTL but still emit `move`. 

What about `iv2c = (int)iVar2` where iv2c is a *different machine mode* variable that still lives in a register... 

What about using a `union` with an int and a pointer? no.

Hmm, think about `move` — the MIPS `move` is `or rd,rs,zero` (or addu). In the target, the copy is a pseudo-pseudo copy that after allocation became `move v1,a0`.

What if the copy comes from an *address computation*? no.

New angle: maybe I can avoid needing the move by making the compare's operand a *different pseudo that is allocated to v1* naturally. The compare is `beq v1,v0`. What if instead of iv2c being a copy, the comparison is between a variable that naturally lands in v1? The register allocation of `one` is pinned to $2; the other operand must be v1. Mine has a0 (iVar2). Why a0? Because cse folded iv2c into iVar2, and iVar2 was allocated a0.

So the question reduces to: get a second variable (distinct from iVar2) holding the same value, allocated to v1, without an extra instruction. That's impossible without a copy instruction... unless the value is *recomputed* into v1 — which costs instructions.

Hmm, unless the value could be born in v1 and copied to a0 for the later use. The later use is `sll v0,a0,0x3` for r. What if we restructure so that iv2c (in v1) is the "primary" and iVar2 is derived from it? Then the copy is `iVar2 = iv2c` and iVar2 is used later. Combine would merge `iVar2 = iv2c` into the later use? The later use is at insn 42 (`sll v0,a0,0x3`), far away (after the join, the store block). Combine can merge a copy into a use if within 3 insns and adjacent... The copy at the join, the use at 42 — many insns between. So it might survive!

But the compare `beq v1,v0` would use iv2c=v1 directly (no copy needed). And the copy `iVar2 = iv2c` would be placed... where? At the join, right after? The target has the copy at 27 and iVar2 used at 42. In the target, the copy is `move v1,a0` (v1 = a0), i.e., iv2c = iVar2, with iVar2 = a0 born in the else arm.

If we invert: iv2c is born in the else arm (`iv2c = t + 1`), then iVar2 = iv2c at the join. Then:
- else arm: `sra v0; andi v0,0xf; addiu v1,v0,1` — but target has `addiu a0,v0,1` (iVar2 in a0). Our version would compute into v1 instead of a0. Then the then arm `li v1,1` instead of `li a0,1`. Then the join `move a0,v1`. Then the compare `beq v1,v0`. Then later `sll v0,a0,0x3`.
- Instructions: same count! But registers differ: target has iVar2 in a0 and iv2c in v1; ours has iv2c in v1 and iVar2 in a0 — SAME! Because the copy is between them either way, and local-alloc assigns. The only difference is which one is born where — but both are "born" in the else arm (t+1) and then-arm (1).

Wait, actually in the target: the else arm computes `addiu a0,v0,1` (a0 = iVar2) and then the join copies to v1. In my inverted version: the else arm computes `addiu v1,v0,1` (v1 = iv2c), the join copies to a0 (iVar2). The insn sequence would be identical in structure but the roles swapped — the same machine code! Since both produce: addiu X,v0,1 ... move Y,X. The allocator decides which is which. So the target's `move v1,a0` would become `move a0,v1` — DIFFERENT bytes (move v1,a0 = or v1,a0,zero; move a0,v1 = or a0,v1,zero).

Hmm, unless the allocator assigns the born-in-else value to a0 anyway (it's the one used in the later sll... no, in my inverted version iVar2 = the copy target, used later).

Risky. But here's the thing: would combine merge `iVar2 = iv2c` into the compare? The compare uses iv2c, not iVar2. So no merge for the compare. Would combine merge the copy into the *later* use (sll at 42)? The insns between are far (the stores). Combine only combines up to 3 insns. So the copy survives!

But then, would the register allocator coalesce iVar2 with iv2c? iVar2 is live from the copy to insn 42; iv2c is live from the else arm to the compare. They overlap? iv2c dies at the compare (insn 29); iVar2 is born at the copy (27) and dies at 42. They overlap between 27-29, so they conflict → separate registers. Good.

But which gets a0 and which v1? Local-alloc preferences... The one born in the else arm (iv2c) has a longer live range; iVar2 shorter. Hmm.

Also, the compare `beq v1,v0` — v1 must be iv2c's register.

This is worth testing. But it requires restructuring the source:
```
if ((short)iVar4 == six) { iv2c = 1; iVar2 = iv2c; uVar5 = 0; }  // hmm
```
Wait, the then arm: iVar2 = 1; then at the join, iVar2 = iv2c — but iv2c must be 1 on the then path too. So the then arm must set iv2c = 1.

```
if ((short)iVar4 == six) { iv2c = 1; uVar5 = 0; }
else { t=...; iv2c = t + 1; param_2 <<= 4; }
iVar2 = iv2c;
one = 1;
if (iv2c != one) uVar5 = 0;
```
But then the target's then arm `li a0,1` would become `li v1,1`, and the join `move a0,v1`. The target has `li a0,1` + `move v1,a0`. So the registers are swapped → not matching. Unless the allocator puts iv2c in a0 (since it's the long-lived one?) and iVar2 in v1. Hmm, actually maybe! Because `iv2c` is live from the else arm through the compare, and iVar2 from the join to 42. Allocation could give a0 to the one born earlier.

Actually, wait. Let's look at the target's register assignment again: iVar2 = a0 (used later in sll), iv2c = v1 (short-lived). v0 = one (pinned). t2 = t3? etc.

Hmm, the copy in the target: `move v1,a0` = iv2c = iVar2 where iVar2 is the *source*. So iVar2 was in a0 before the copy.

In my inverted version the copy is `iVar2 = iv2c`, which would be `move a0,v1` if iv2c is in v1. The bytes differ.

Unless the register allocator, seeing iVar2 = copy of iv2c, assigns iv2c = a0 and iVar2 = v1 → `move v1,a0`! That would happen if the copy prefers... hmm, local-alloc coalescing: iVar2 dies at 42, not at the copy. Copy preference: local_alloc gives the copy a preference to use the same reg, but they conflict.

Honestly, testing is cheap. Let me think about what the C should look like to be natural:

```
{
    int iv2c;
    if ((short)iVar4 == six) { iVar2 = 1; iv2c = iVar2; uVar5 = 0; }
    else { t = ...; iVar2 = t + 1; iv2c = iVar2; param_2 <<= 4; }
    one = 1;
    if (iv2c != one) uVar5 = 0;
}
```
This has the copy in each arm. In the then arm, `iv2c = iVar2` where iVar2=1 → folds to `li v1,1`; that's an extra insn in the then arm. Unless combine merges `li a0,1` + `move v1,a0`... In the then arm, the block ends with a jump, so combine within the block could merge `li a0,1` and `move v1,a0`? They're adjacent; combine merges a copy into... it would produce `li a0,1` + `li v1,1`? That's not fewer insns, and combine only applies profitable combos.

So 57. Not good.

OK, let me step back and consider the *actual* target RTL. The target was compiled from source with the launder asm. In the target's RTL at combine time:

```
iv2c = iVar2        (copy, pseudo)
asm("" : "=r"(iv2c) : "0"(iv2c))    -- actually this is an asm_operands insn with an output operand
one = 1
if (iv2c != one)
```

Hmm, actually the asm with "=r" output and "0" input: the input is tied to the output's register. GCC's expand of an asm with a tied operand: it typically creates the input in the same pseudo... The output iv2c is a new pseudo? The launder's effect: the value is copied into a *fresh* pseudo (the asm output), and the input is the old value in the same register (tied). So the RTL is:

```
(insn (set (reg:SI N) (reg:SI iv2c)))   ; the tie copy
(insn (parallel [(set (reg:SI N) (asm_operands ... (reg:SI iv2c)))]))
```

So there IS an explicit copy insn before the asm, and the asm is opaque → combine can't merge. After allocation, that copy becomes `move v1,a0`? Hmm, the asm's output is in a register tied to the input... The asm is empty and emits nothing; the copy insn is what emits `move v1,a0`.

Wait, but then the copy `iv2c_new = iv2c` is adjacent to the asm which uses iv2c — combine can't combine because the asm is between... Actually the copy is i1 and the asm is i2 (not combinable), and the compare is i3: combine tries i1,i2,i3 — can_combine_p(i2) returns 0 because the asm's SET_SRC is ASM_OPERANDS → "If SET_SRC is an ASM_OPERANDS we can't throw away these CLOBBERs" → return 0. So the copy stays.

So the target's move is literally the asm's tied-operand copy. To reproduce in real C, we need a copy that combine can't fold: a copy whose destination is used in an insn that combine can't see into, OR a copy separated from the use by a code_label.

Alternatively, maybe we don't need that exact move: maybe there's another way to make the allocator produce a move v1,a0. What if the compare's operand is a *copy of iVar2 that combine can't merge because the copy's destination is a HARD register* (pinned)? Not allowed to add pins.

Hmm, what about a copy whose source is a hard register that's a user variable... 

OK here's another thought: the "1-field struct alias" trick used in the twin (for the store). Could a similar alias trick make the copy opaque? E.g., `struct { int v; } s; s.v = iVar2; iv2c = s.v;` — that's a memory store/load (sw/lw), not a move.

What about a *union* of int and struct? Same memory.

What about making iv2c a `volatile`... no.

What about taking the address and... no.

Hmm, what about using an existing pin: `one` is `register int one __asm__("$2")`. The pin means `one` is hard reg $2. What if we do the copy into a variable that is *tied* to a hard register through a real C construct... that's a pin.

Let me reconsider: is the `launder` kind really only about the asm at line 41? Yes. The body has other pins (allowed to stay). But adding a pin is forbidden.

Alternative: maybe the comparison can be restructured to use a *different* variable that the compiler must copy. Hmm.

Wait wait. Let me re-read the target:

```
24 andi v0,v0,0xf
25 addiu a0,v0,1
26 sll a1,a1,0x4
27 move v1,a0
28 li v0,1
29 beq v1,v0
```

What if the copy isn't `iv2c = iVar2` but the tied asm copy `iv2c_new = iv2c`? Either way it's a copy from a0 to v1.

Now, could we get this shape via the *pinned* `one`? `one = 1` is `li v0,1`. The compare is beq v1,v0.

Hmm, what if we compare `iv2c` against a *literal* 1 rather than the pinned one? Then combine might fold differently. But `one` is pinned $2 and the target uses v0 for the 1.

Let me try yet another angle: what if the copy is `iv2c = iVar2` but the *compare* uses a different variable derived from iv2c such that combine can't fold both? e.g.:

```
iv2c = iVar2;
one = 1;
if (iv2c - one != 0) uVar5 = 0;   // no, changes code
```

Hmm.

What about making the copy dead-looking and re-created? 

Let me test the "inverted" idea empirically — maybe the allocator gives the same registers. Actually here's a cleaner variant of the inversion that keeps the C natural:

```
{
    int iv2c;
    if ((short)iVar4 == six) { iVar2 = 1; uVar5 = 0; }
    else { t = ...; iVar2 = t + 1; param_2 = param_2 << 4; }
    one = 1;
    iv2c = iVar2;
    if (iv2c != one) uVar5 = 0;
}
```
This is the current shape (copy after li). Combine merges. What if I move the copy BEFORE `one = 1` (already is) — no difference.

What if the copy is `iVar2` → `iv2c` but I use `iv2c` in the compare through a second copy? no.

Let me look at how combine decides to combine i1=copy into i3=beq. In try_combine, after `can_combine_p(i2...)` and `can_combine_p(i1...)`, it requires the substitution to be profitable and `i2dest` dead... Let me read the part about when i2 is not used in i3: "If I2DEST is not used in I3, we can still combine if..." — combine has the "i2 feeds i3" requirement? Not strictly; combine can combine i1 into i3 while i2 remains, but it must be that i2 doesn't clobber i1's source or dest. Then the result is a 2-insn combination of i1 and i3 (i2 stays). Combine's `newi2pat` handles this.

So yes, combine does that.

Hmm, but combine's profitability: combining i1 (copy) and i3 (compare) deletes i1 — 1 insn saved. Always profitable.

So the only way: a label between them, or a non-combinable insn between them, or the copy's dest used after i3.

**Copy's dest used after i3**: combine requires i3's use of dest to be the last use; if dest is used later, can_combine_p for i1... hmm, actually combine CAN still substitute the first use and keep the copy (it checks `i1dest` usage). Let me look: in try_combine, after combining, if the dest of i1 is used later, it emits `i1` again? There's code: "If I1's destination is used elsewhere, we must copy it back" — `if (! dead) ... add the insn back`. Combine has `i1dest` and checks `find_reg_note (i1, REG_DEAD, i1dest)`.

If iv2c were used a second time later, combine would keep the copy... but we can't add a use.

Hold on — maybe we CAN add a use at zero cost: what if the second use replaces something? Look at the tail: `r = (uint)(iVar2 << 3) | c6b;`. If instead we used `(iv2c << 3)`, then iv2c is used later (at insn 42) instead of iVar2! Then:
- The compare uses iv2c (copy at 27, compare at 29).
- iv2c used again at 42.
- iVar2 would then be dead after the copy... but iVar2 is also used... hmm, if iVar2 is used nowhere else, then the copy `iv2c = iVar2` could be coalesced/merged: iVar2 dies at the copy → combine/local-alloc merges them. Bad.

Unless iVar2 is still used elsewhere... it isn't.

Hmm.

OK, let me think about the "code_label between copy and compare" option once more. Is there a C construct that places a label between two adjacent statements with no runtime cost? A label is generated for any branch target. If there's a branch target right after the copy, that means some branch jumps there — which would cost an insn.

What about a `switch` with a case? no.

Hmm, what about the `do { } while (0)` — the empty body generates a label? An empty loop gets deleted.

What about `if (0) { }` — deleted.

Let me reconsider the sign-extend approach but with a value whose sign bit combine can't prove. What if the copy is `iv2c = (s16)(iVar2 << 16 >> 16)`? Identity launder.

What if we make iVar2's computation different in the else arm such that its range is unknown to combine at the join? The range knowledge comes from the insns in the else block (andi). Combine at the join sees `iv2c = sign_extend(subreg(iVar2))`. To fold, combine must know iVar2's sign bit. It uses `nonzero_bits (iVar2)` which uses reg_last_set... at the join, reg_last_set for iVar2 is the addiu in the else block. Combine's `nonzero_bits` looks at REG_NONZERO notes? In combine, `subst` uses `reg_nonzero_bits[REGNO]` — computed by... hmm, there's `reg_nonzero_bits` in combine.c maintained per-block from the last set. It found the addiu's known range? The addiu's source is `v0 = andi(x,0xf)`, and combine would have to chase through the block boundary.

The observed w2 result shows combine folded it (no sll/sra in the output). So it could.

Unless the value is loaded from memory: `lh` gives unknown high bits... but then combine folds sign_extend(subreg(lh)) into the lh itself (which is already sign-extended) → the "copy" would be the load's result. Not a move.

Hmm.

Let me look at this from the "what other items did" angle. The moves.md entries for launder mention "reassignment kills the cse sym class". Let me look at func_8018C2D8's actual diff to understand the mechanism.

Actually, maybe a simpler idea: the launder forces iv2c into a register *distinct from iVar2's*, and the move is the copy. What if we achieve the same with a variable that the compiler must keep separate because it's live across the `one = 1` pinned assignment? No.

What if iv2c is used in a context that forces a copy: e.g., an *address* operand? no.

Hmm, let me reconsider the problem statement: the launder line is `__asm__ __volatile__("" : "=r"(iv2c) : "0"(iv2c));`. The mechanism: anti-coalescing. The notes say "without it `iv2c = iVar2` folds into iVar2 (no `move v1,a0`), and sched puts `sw v0,-4(t0)` two insns late."

Wait — the notes say TWO effects: (1) the move, (2) the sched placement. The p1 test (launder restored) scored 2 with only the store placement left. So with the do-while on the store (q1), score 0.

So we need both the move and the schedule. The do-while keepalive (`do { puVar3[-1] = uVar1; } while (0);`) is already in the body and is a "keepalive" kind... wait, is the do-while keepalive counted as a kind? The kinds row is `launder` only, and the notes say "keepalive gone, launder kept" — the keepalive asm was replaced by the do-while. The do-while is allowed (C0535).

OK so I need the move.

Let me try the s16 idea but with the sign-extend source being a *variable whose value combine can't bound*: what if I copy iVar2 into a `short` in the ELSE arm (where combine knows the range... hmm).

What about making the sign-extend happen on a value loaded from the stack? no.

Alright, let me try a completely different real-C trick: **make the copy's destination a different mode variable that is compared in a way that requires both**:

```
int iv2c;
...
iv2c = iVar2;
one = 1;
if (iv2c != one) uVar5 = 0;
```
What if `iv2c` is declared as `unsigned` and `one` as int: compare `iv2c != one` → unsigned compare, combine might not substitute? It would still substitute a copy.

What if `iv2c` is `unsigned char`? Then `iv2c = iVar2` is a truncation (andi) — extra insn.

Hmm what about a *pointer* cast: `iv2c = *(int *)&iVar2`? identity.

Let me try to look at how the actual target RTL looks — maybe the move isn't the tied asm copy but something else. Actually, we can test: what does a body with the launder produce in the .combine dump? The prev_win.c IS the target-matching body (score 0). Let me dump it and look at the RTL to see exactly what the launder expands to, and where the move comes from. That tells me what to reproduce.

Let me run hdump.sh on prev_win.c.

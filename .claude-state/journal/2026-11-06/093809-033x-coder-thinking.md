---
ts: 2026-11-06T16:38:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1r6mDqfM7aAUJUlddQ8v
---
andsi3 operand 0 constraint is "=d,d" — '=' and 'd', so the tie loop is allowed. Operand 1 is "%d,d" (commutative). So tying should be possible.

Hmm, so why didn't 75 tie with 77 in r16? Wait — maybe it DID tie and the output is different than I think. Let me check: in r16.s, `andi $2,$3,0x8000` — if 75 tied to 77 ($3), it would be `andi $3,$3,0x8000`. It's $2. So no tie.

Hold on. Maybe the issue is `reg_qty[sreg] == -1`: reg 75 is `reg/v:SI 75` — a user variable that might be used in multiple blocks? It's only in block 2. Hmm.

OR maybe `find_regno_note (insn, REG_DEAD, ureg)` fails because ureg=77's REG_DEAD is on the insn but... the RTL shows the REG_DEAD note on insn 65. Hmm.

Wait, maybe the tie loop is skipped for this insn because of `insn_code_number >= 0` — recog_memoized. Should be 92 (andsi3).

Let me look at the -dl dump more carefully: the lreg dump prints the RTL AFTER local-alloc (with pseudo numbers still). The qty assignment info is in the "Register X in N." lines. For block 2: "Register 75 in 2." and "Register 77 in 2." — those lines just say which block.

Hmm, let me check whether there's a way to see the tie decision: maybe the .lreg dump's "Register 77 used ... in block 2" and then after allocation, the .greg dump. Let me instead just check the win0 (base) .s: no move, both in $2. In base, 74 and 75 tied.

Difference between base and r16: in base, the andi input is 74 (the ret pseudo), which is the same qty as the copy target. In r16, the andi input is 77 which is the u16 holder, and 75 is m. Hmm, both pseudo.

OH WAIT. I see it: in r16, reg 77 is used at insn 57 (zero_extend) which is a *different* insn, and 77's last use is insn 65. But `reg_qty[77]` — is 77 local to block 2? "Register 77 used 2 times across 4 insns in block 2" — yes.

Hmm, let me look at the actual local-alloc code path for the andi. Maybe `insn_n_operands` for andsi3 with the K alternative: the tie loop iterates i=1,2. For i=1: r1 = operand 1 = (reg:SI 77) with constraint "%d,d". must_match_0 = -1 (no operand must match). n_matching_alts = 1? (the '%' constraint). Then r0 = operand 0 = (reg/v:SI 75). r1 = reg 77. may_save_copy = (SET_DEST == r0 && SET_SRC == r1) → SET_SRC is the AND expr, not r1 → false. Then combine_regs(77, 75, 0, ...). Conditions pass... then `find_regno_note (insn, REG_DEAD, 77)` → true → tie.

Unless `reg_meets_class_p (75, qty_min_class[reg_qty[77]])` fails. qty_min_class for 77 is GR_REGS. 75's class is GR_REGS. Fine.

So it SHOULD tie. But the output says otherwise. Let me double check the r16.s `andi $2,$3,0x8000`: maybe $2 there is m and $3 is ret; if m tied to ret, both $3. So no.

Wait... maybe 77 is not the ret pseudo in the andi; let me re-read: `(insn 65 64 69 (set (reg/v:SI 75) (and:SI (reg:SI 77) ...)))`. Yes 77.

Hmm, unless the tie loop DID tie 75 to 77 but then the ALLOCATION gave the tied pair $2 and the move `move $3,$2` is for a different pseudo... Let's see: if 75 tied to 77, then both are one qty; the copy insn 53 `(set 77 v0)` gives that qty a copy suggestion v0; allocation gives it $2; then `move $2,$2` deleted; andi `$2,$2`; branch `beq $2`. That's the BASE shape, not r16.

So in r16 no tie. Puzzling. Let me look at the lreg dump directly for the tie info. Actually, maybe the -dl dump is *before* local-alloc? The dump flags: -dl = dump after local-alloc. Hmm.

Wait, maybe the reason is that in r16 the andi insn was NOT recognized with andsi3 at the tie time — maybe it was `and:SI (reg:SI 77)` where 77 is... no, insn_code 92 = andsi3.

Hmm, let me look at combine_regs's condition again: 
```
if ((ureg >= FIRST_PSEUDO_REGISTER && reg_qty[ureg] < 0)
```
ureg=77. If reg_qty[77] < 0 → return 0! When is reg_qty[77] set? reg_is_set is called for the insn that sets 77, i.e., insn 53, AFTER insn 53's tie loop. So by insn 65, 77 has a qty. Unless... reg 77 is a `reg/v` (user variable) — hmm, `reg_qty` might be -1 for registers that "die more than once" or cross blocks. But 77 is local to block 2.

Hmm wait, actually there's a subtlety: `reg_qty[ureg] < 0` includes -1 and -2. If 77's qty is -2 (not born) at insn 65... that can't be.

Let me just add a debug? No, can't rebuild gcc.

Alternative: maybe the tie DID happen between 75 and 77, and then local-alloc's *second phase* (the one that assigns and can "break" ties?) ... no.

Let me instead check the base dump: does the base andi tie? In base, 74 dies at insn 61 and 75 is set. If tied, both $2. The base .s showed `beqz $2` and `andi $2,$2` — consistent with a tie OR with independent allocation both $2 (74=v0 via copy suggestion, 75=v0 via... it's the same). Actually even without a tie, 75 could get v0 if allocated after 74 died (the allocator's find_free_reg uses regs_live_at, so a reg freed at the insn can be reused). Indeed local-alloc allocates per-block with live ranges: 75's live range starts at insn 61, and 74's ends at 61; they can share v0 even without an explicit tie? No — local-alloc allocates a hard reg only if it's not live over the qty's live range; 74 and 75 don't overlap, so 75 could get v0 either way. So the tie is not the deciding factor.

Then in r16, why did 77 get $3 rather than $2? Because 78 (the zero_extend result) was allocated $2 and 78 is live across insn 57-59; 77 is live 53-65. 77's range covers 78's, so 77 can't be $2. So 77 got the next free: $3. And 75 (m, born at 65) then took $2 (freed after 78's death at 59 and... wait 78 dies at 59, so $2 is free at 65 → m gets $2).

So the HImode case works by luck: the zero_extend pseudo occupies $2.

Now, for the SImode case, we need another pseudo occupying $2 across ret's live range. What could that be? A value that's live at the same time and prefers/gets $2. The `m` pseudo is born later. The `sp28`? It's in another block.

Hmm, what about the call's argument? No.

What if we introduce a SImode temp that holds something in $2 across the call-result region? For instance, if the source computes an unrelated value before the call and uses it after. But that changes the instruction stream.

Alternatively: make the branch test a SImode value that requires a pseudo in $2. E.g., keep ret SImode for the andi but test a zero-extended HImode copy... that's exactly r16's extra insn. The extra insn is the problem.

Wait, in r16 the sequence is:
```
move $3,$2
andi $2,$3,0xffff
beq $2,$0,$L22
andi $2,$3,0x8000     <- delay slot
```
The target is:
```
move $3,$2
beq $3,$0,$L22        (well, beqz $3)
andi $2,$3,0x8000     <- delay slot
```
So if the zero_extend pseudo 78 didn't exist, ret 77 would get $2 (copy suggestion) and we'd lose the move. So we need a pseudo in $2 that is NOT the ret.

Idea: make the *branch* operand a separate SImode pseudo that is zero-extended from a HImode copy... that's 78, and it costs an insn.

Alternatively, can the zero_extend insn be *deleted* by a later pass (combine/cse2) while keeping the register allocation? No — allocation is after combine.

Hmm, what if the zero-extend is a no-op because the HImode value is known zero-extended? Not in gcc's model.

New angle: maybe make the branch test an SImode pseudo that is set from ret via a copy (move) and lives in $2... extra insn again.

What about making `m` itself the branch operand? Target branch is on v1 = ret. If the branch tested m (v0)... no.

Let me reconsider: maybe the target source isn't `if (ret==0)` but something like `if (ret >= 1)`? For a signed value, `ret == 0` → beqz. For `ret < 0`? no.

Hmm, let me look at the *flow* dump or the original .rtl to see the exact source-level tree. Actually, the target bytes are the pinned build; the pinned build's source is what we have. The pins were added artificially, so the "natural" source for the target may not exist. These are "singleton crack" attempts.

Let me reconsider the problem from the angle of: what makes ret get $3 naturally? In r16, the zero_extend 78 in $2. What if we make a pseudo that occupies $2 and is *free* (no extra insn)? For example, a value that's already in $2 from a previous call! The call before (func_80146E98) returns in v0 and its result is tested. If the result pseudo is still live at the second call... no, it's consumed by the branch.

What about the first call's result: `if (func_80146E98(a0) != 0)` — the result is used and dies at the branch.

Hmm, what about a value loaded into v0 before the second call that survives the call? Impossible (call clobbers v0).

What if the second call's result is used twice via two different pseudos where one is HImode... 

Wait, actually! What about making the branch test an SImode value that is *the result of an andi* — e.g., `if ((ret & 0xFFFF) == 0)`? That would be `andi $2,$3,0xffff` (same extra insn) but then the branch tests $2 and m=... hmm: target branch tests $3.

OK, what about the opposite: the target's `beqz v1` — maybe the branch operand is HImode but gcc emitted beqz without extension because the value is known to be in range. In gcc 2.7.2, comparing `(reg:HI) == 0`: there's a pattern `branch_zero` for SImode; for HImode, `cmp_0`? The zero_extend we saw (insn 57, zero_extendhisi2) came from the tree level: `(u16)ret == 0` promotes to SImode. If instead we write the comparison to avoid promotion... In C, all comparisons promote to int. So no.

Hmm, but what if ret is a *pointer*? no.

Let me try a completely different idea: **`m` in a different block**. The tie/allocation is per block. What if the andi is in a different basic block than the branch? The target has them adjacent with the branch's delay slot. Same block.

What if the branch and the andi are in different blocks due to a do-while(0) wrap? C0535: do{}while(0) splits cse1 EBB. Let me consider wrapping the andi in a do-while(0) or something to change blocks. But the target has beqz and andi adjacent, so the andi must be in the branch's delay slot — same block, right after.

OK here's another idea: **the call result is used by the andi and the branch tests a copy** — but with the copy in the *other* direction such that the branch's copy gets $3. Let me think:

```c
s32 t = func(...);   // t = v0
s32 ret = t;         // ret gets $3 if t occupies $2 across
if (ret == 0) {}
else if ((m = ret & 0x8000) != 0) ...
```
Here t must be live across the copy. It is live until the andi only if the andi uses t. But the andi uses ret. So t dies at the copy → tie.

What if the andi uses BOTH? `m = (ret & 0x8000) | (t & 0)`? An extra and.

What if `m = ret & 0x8000` and separately `t` is used in the test: `if (t == 0)`. Then the branch tests t ($2), not ret ($3). Target tests $3.

Hmm.

What if ret = t + 0 where the 0 is a *variable*? `s32 z = 0; ret = t + z;` → add, not move. No.

OK, what about a **union/bitfield** trick: `s32 ret` but assigned via a union member of type u16? E.g.:

```c
union { u16 h; s32 w; } u;
u.w = func(...);
ret = u.w;   // ??? 
```

Hmm.

Let me step back and consider the value of continuing. The item is a "pin" kind; I have ~25 more minutes. Let me try a few more empirical shapes and then declare a wall if none crack.

More shapes to try:
1. `s32 ret; u16 h; h = func(...); ret = h;` — HImode holder then zero-extend to ret → adds andi.
2. `u16 ret; s32 m;` with `if (ret == 0)` — done (r16, 7).
3. `u16 ret` with the branch written as `if ((s32)ret == 0)` — same.
4. Add a dummy live value in v0: e.g., use the call result in a second expression that combines with the andi in one insn. Like `m = (ret & 0x8000) != 0 ? ...`.
5. What if `m` is `s32` and ret is `u16` but the branch is on `m`... no.
6. What if we make the call result assigned to a HImode AND SImode pair via a union read twice?

Idea 6 concretely: 
```c
union U { s32 w; u16 h; };
union U u;
u.w = func(...);
ret = u.w;      // SImode copy from u.w
if (ret == 0) ...
else if ((m = u.h & 0x8000) != 0) ...
```
Hmm, u.w and u.h share a pseudo. The andi on u.h would be HImode and read the same pseudo; the branch on ret (SImode copy). If the copy survives (u.w live at the andi), ret gets $3, u.w=$2; andi `andi $2,$2,0x8000` reads $2 — target reads $3. No.

What if the andi reads ret and the branch reads... 

Actually, hold on! Let me re-examine: is it possible that in the target, the andi's input v1 is the *zero-extend* result? I.e., the target's `andi v0,v1,0x8000` where v1 is a pseudo that equals ret... The target has NO zero_extend insn. So v1 is the raw value.

What if the target's source tests the raw call result (v0) but the copy is to v1, and the andi reads v1: that's exactly the current C with ret=v1, m=v0.

So we need: a pseudo P (ret) with a copy suggestion to $2, but $2 is taken by another pseudo Q that lives across P's range; and the andi reads P and m takes $2 after Q dies.

Q must exist naturally. In r16, Q = zero_extend result. In SImode, what natural pseudo could occupy $2 across the call-result range? 

What about the `m` pseudo if it were *defined before* the branch? If m = ret & 0x8000 is computed BEFORE the test (statement order: m first, then if), then:
- RTL: (set m (and ret 0x8000)); branch on ret.
- Then m is born before the branch and lives to its own test. ret is live across the andi (used by the branch). ret and m overlap → m can't share $2 with ret.
- Allocation: ret has the copy suggestion to $2; m has no suggestion. Order: m's priority vs ret's. If ret is allocated first → ret=$2, m=$3 → andi $3,$2,0x8000; branch beqz $2. Not target (target: move $3,$2, beqz $3, andi $2,$3).
- If m is allocated first → m=$2 (first free), ret=$3 (copy suggestion taken) → move $3,$2; branch beqz $3; andi $2,$3,0x8000. TARGET! But the order of insns: target has the andi in the branch's delay slot, i.e., AFTER the branch. If the source computes m first, the andi would be before the branch. Hmm, unless the scheduler (sched1) moves it into the delay slot? No, dbr fills delay slots; sched1 reorders before the branch. Actually the andi could be moved after the branch by sched1 if it's independent? The branch on ret and the andi writing m: the andi reads ret, and the branch reads ret. sched1 could order the branch before the andi (since the andi is independent of the branch's outcome) — that's exactly the "sched1-birth-order" class. Hmm, but the target has andi in the delay slot which is a natural fill.

Let me just try it: m computed before the if.

Actually wait, in the target the andi is in the delay slot of beqz — the delay slot is filled by dbr (reorg) from the fall-through. If sched1 orders the branch before the andi, the andi becomes the fall-through insn and dbr fills the delay slot with it. That's plausible!

Let me try:
```c
ret = func(...);
m = ret & 0x8000;
if (ret == 0) {
} else if (m != 0) { ... }
```
Allocation: ret and m overlap at the andi (ret used at the andi and the branch, m born at the andi). ret live 53..branch; m live andi..bnez. Overlap → different regs. Which gets $2? Priority: ret refs = def + andi + branch = 3, live ~6; m refs = 2, live ~4. ret higher → ret=$2 first → m=$3. That's the wrong direction. But the copy suggestion might change it: qty_sugg_compare puts copy-suggested qtys first → ret gets $2. Hmm.

To make m get $2: give m a copy suggestion too? Or make m's priority higher.

Alternatively, make ret's copy suggestion NOT to $2... 

Hmm, let's just test it empirically; gcc's behavior may surprise.

Also try: m computed before, with m declared first, and with m as the branch test (but the target branches on ret).

Let me also try the reverse: `if (ret == 0) {} else if ((m = ret & 0x8000) != 0)` with `m` declared `s32` and the andi hoisted.

Let me write a batch.

Also another idea: introduce a `s32 q = 0;` used across? e.g. `s32 q; q = 0; ... m = ret & q;` — changes code.

Another idea: the branch `if (ret == 0)` — what if it's `if (!ret)` vs `if (ret)`? Same.

Another: what if the zero test is `if (ret <= 0)`? For the target beqz... no, `ret <= 0` would be blez.

Another: `if (ret < 1)` → slti + beq? no.

Let me batch:
- w2_hoist.c: m = ret & 0x8000 before the if.
- w2_hoist_mfirst.c: decl m first + hoist.
- w2_hoist_t.c: with a temp.
- w2_u16_hoist.c: ret u16, m computed before.
- w2_u16_hoist_mfirst.c.

Let me also consider the "do-while(0)" trick to split the EBB for the andi.

Let me generate and score.

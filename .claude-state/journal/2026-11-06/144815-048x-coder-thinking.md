---
ts: 2026-11-06T21:48:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TvJQJdj7uwnFb48ZmUjy
---
So combine runs after cse2 and after flow analysis. So the sign_extend trick works: cse can't see through the sign_extend, combine later folds it into a copy.

In my w2 I wrote `{ s16 tmp; tmp = (s16)iVar2; iv2c = tmp; }`. Result: no move. Why? Possibilities:
(a) The sign_extend was folded at RTL expansion (expand_convert) because GCC knew the range → plain copy → cse propagates.
(b) cse propagated `iv2c = tmp` (plain copy) and then... yes.

The sign_extend gets folded at expand if `(s16)iVar2` where iVar2 is known non-negative and < 32768 — expand_expr uses `convert_modes`/`expand_expr` which may call `optimize_bit_field`... Actually the key in func_80182ED4: t came from a struct field load `unk84` (s32), unknown range, so the sign_extend was real at RTL. Then combine folded it because the compare... hmm, "the sign extension folds away (t is a sign-extended s16 already)" — the *use* was `t = u - 1` where the sign-extend folded because... whatever.

So I need an RTL sign_extend of a value whose range GCC doesn't know. iVar2's range IS known (1..16). So the sign_extend will be folded at expand.

What if I make the temp copy from a value whose range is unknown? The copy must equal iVar2's value though.

Alternative: use a *different mode conversion* that isn't foldable: e.g., copy through a float? no.

Alternative: prevent GCC from knowing the range. Where does iVar2 come from? `t = param_2 >> 0x10 & 0xf; iVar2 = t + 1;`. If we restructure to hide the range... e.g., compute `t` as `(param_2 >> 16) & 0xf` (known 0..15) — that's what it is. GCC's nonzero_bits knows andi 0xf → bits 4..31 zero → t+1 ≤ 16, sign bit clear. So (s16) folds.

What if the copy is `(s16)` of a value where the sign bit is unknown? We could use a value that is *conditionally* the same: no.

Different idea: **make the copy use a pointer-to-s16 alias read**? memory.

Hmm. Let me think again about cse's copy propagation. In cse.c 2.7.2, how does `iv2c = iVar2` get eliminated? cse_main builds equivalence classes via `make_regs_eqv`. Uses of iv2c are replaced by the class's canonical reg (iVar2) if `reg_eqv_table` says so. For that, cse must see the copy insn and the use in the same EBB.

If we split the blocks with something jump1 won't merge... In the join block, the copy and use are adjacent. jump1 merges blocks that end with a jump to the immediately following label? Actually jump1's "jump to next instruction" deletion + block merge. If our do-while creates:
```
L1: iv2c = iVar2;
    ...
    (jump to L2)  ; deleted since L2 is next
L2: one = 1;
    if (iv2c != one) ...
```
jump1 deletes the jump, merging blocks. So the EBB split doesn't survive jump1.

Hmm, but C0535 says do{}while(0) splits cse1 EBB and cracked sched1 items — in those cases the split mattered for *scheduling* (sched1 works on EBBs; the split changes scheduling), not for cse copy propagation... Right: C0535 is about sched1 birth order, where a block boundary changes the schedule. For cse propagation, jump1 merges first, so no.

So to defeat cse's copy propagation in the same EBB, we need a non-copy RTL. Options:
1. sign_extend that isn't folded at expand.
2. A copy involving a hard register (pin) — forbidden.
3. Reassign iv2c later (stales the class) — cse's reg_eqv: after a second set of iv2c, the equivalence class for iv2c is invalidated from that point; uses after the second set see the new value. But our use is right after the first set.

Wait — the W02 note "reassignment kills the cse sym class" means: writing a variable twice kills its equivalence so the earlier value stays in a register.

Hmm, what if we write:
```
iv2c = iVar2;
...
```
No.

4. Make the use not directly of iv2c but of something else that requires the copy... 

Actually! What about `uVar5`? The target's `move v1,a0` — v1 = iv2c. Then `beq v1,v0` with v0 = one (li v0,1). 

Could we instead get the target code by comparing iVar2 against a *different* variable and having iv2c be the pinned one? Hmm.

Let's step back. Maybe there's a simpler real-C source of the copy: the compare `if (iv2c != one)`. What if we write it as `if (iVar2 != one) uVar5 = 0;` where `one` is a pinned $2 variable assigned 1 — no copy at all. That's the lever-free form (score 5).

What real C produces `move v1,a0` here? A copy whose source is still live and whose dest is used once.

The most natural C: assign to a variable of a *different type* requiring a conversion. What conversions compile to a single `move`? Converting between types of the same mode — which cse sees through... unless the conversion is a NOP_EXTRACT/SUBREG.

Hmm! What about a **union/bitfield**: `iv2c = (int)(unsigned char)iVar2;` → andi. no.

What about making iv2c a `short` **parameter-like**? no.

Another thought: **what if we make the copy's destination used in a way that forces a distinct register, e.g., by making the copy happen in a conditional arm so local-alloc can't coalesce?** Coalescing: local_alloc merges quantities when the source dies at the copy. iVar2 is live after (used in `sll v0,a0,0x3`), so no coalesce. So if cse leaves the copy alone, it stays.

So the only enemy is cse. Let me verify with a dump: run hdump.sh for w2 to see the RTL after cse. Actually easier: use the cse dump and grep for the copy. But maybe I can test the hypothesis cheaply: write a body where the copy source's range is unknown.

Can I make iVar2's range unknown while producing the same code? E.g., compute `iVar2` via a variable declared with a type that hides the range... The code `t = param_2 >> 0x10 & 0xf; iVar2 = t + 1;` — the target emits `sra v0,a1,0x10; andi v0,v0,0xf; addiu a0,v0,1`. If I write `iVar2 = (param_2 >> 16 & 0xf) + 1` same.

What if the copy is `iv2c = iVar2 & 0xff`? extra andi.

OK here's another idea: **make the copy 64-bit?** no.

**Use a struct assignment**: `struct { int v; } s; s.v = iVar2; iv2c = s.v;` — memory store/load, 2 insns.

**Use a pointer with a cast through void**: identity.

Hmm, what about the classic "s16 variable" trick but applied to a value with unknown high bits: we could make the copy `iv2c = (s16)iVar2;` where iv2c is `int`. If expand folds the sign-extend because of known range... let me verify empirically what RTL is produced. Use cc1 dumps via hdump.sh on includer 0 and look at the cse dump.

Actually — hold on. Let me reconsider. Maybe expand does NOT fold (s16) conversions based on range; the folding happened because `iv2c = tmp` (the second copy) was propagated by cse and then combine folded `tmp = (s16)iVar2` into the compare? Let's look at w2's actual asm to see what happened.

Let me dump w2's candidate asm using my dis.py with --keep... my dis.py needs the candidate object. Let me get it via delever_search --keep (direct call, no rotation) and then run dis.py.

Alternatively use `.run/P40/T10/dis.sh`-like: my own script. Let me just run delever_search --keep and then dis.py with the object.

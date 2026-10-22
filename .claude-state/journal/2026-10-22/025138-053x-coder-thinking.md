---
ts: 2026-10-22T08:51:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_mchoR18M5HUN69Q4YquK
---
This is a goldmine. Key facts:

**K3 — Hard-reg scan order: plain regno order: $v0,$v1,$a0..$a3,$t0..$t7,$s0..$s7,$t8,$t9,$fp. First fit wins.**

**K8 — Local vs global split: local-alloc handles only pseudos with REG_BASIC_BLOCK >= 0 && REG_N_DEATHS == 1 (single-block, dies once). global.c has NO coalescing.**

**K5 — Two-pass frugality + preferences: global.c:900 find_reg: pass 0 excludes regs not in regs_used_so_far ("never allocate a register for the FIRST time in pass 0") and regs someone else prefers; pass 1 opens fresh regs. Copy preferences (set_preference) can override the scan-order winner within the class.**

So for the global q (r73): the scan order is v0, v1, a0, ... First fit. v0 is used by the local pseudos (the call result, the value) — but "regs_used_so_far"! In pass 0, gcc only allocates regs that are already used ("regs_used_so_far"). Hmm.

The conflict sets: r73 conflicts {73, 76, 29} — no v0, no v1! So the scan would pick... v0 ($2)? But the preference "4" (a0) overrides the scan-order winner (K5: "Copy preferences can override the scan-order winner within the class").

So the preference is decisive! If I remove the preference, r73 would get v0 or v1 (per the scan order and conflicts).

Wait, but why did it get a0 and not v0/v1? Because the preference (4) overrides. If the preference were absent, the scan order would give v0 ($2) — but v0 is used by the local val/const pseudos... but the conflict set says r73 doesn't conflict with v0. Hmm, but "regs_used_so_far" in pass 0: v0 IS used (by locals) → it's a candidate. Hmm.

Hmm, so which reg would r73 get without the preference? The scan: v0 first. Is v0 excluded? r73's conflicts don't include 2 (v0). Hmm, but the .greg conflict list is the *global* conflict info; the hard regs occupied by local pseudos are also considered ("regs_used_so_far" + local allocation). Since v0 is used by the local const/val in the arm blocks and by the call result, and r73 (q) is live in blocks 40/71/98... the local v0 uses are in blocks 19/50 (the pre-branch blocks) and r73's blocks are 40/71/98 — disjoint! So v0 might be free for r73.

But the target has q in v1 and val in v0. If r73 got v0, the val pseudo (r76) would then get... v1? and the target needs val in v0. Hmm.

So even without the preference, we'd get q in v0, val in v1 — the wrong way round (but maybe the same score of 4).

So the real question: how to get the q global allocated v1 AND val allocated v0?

The order of allocation: "5 regs to allocate: 73 74 76 83 72" — the allocno order (by priority). r73 (q) first (pri 10000), r74 (ptr) second (10000), r76 (val) 6000, r83 (st) 6000, r72 (arg) 4444.

In the target (pinned), the order is "74 76 83 72" — 4 globals: so in the pinned version, the globals are 74(?), 76, 83, 72. Since q is hard $3, the pseudo r73 (q) doesn't exist; the val pseudo became r74? Hmm, in the pinned version: "74 conflicts: 72 74 83 2 29; 74 preferences: 4" → r74 prefers a0 → r74 → a0. And "76 conflicts: 76 3 29" → r76 conflicts with v1 → r76 → v0. "83 conflicts: 72 74 83 2 29" → r83 → v1.

Hmm, so in the pinned version: r74 → a0, r76 → v0, r83 → v1, r72 → s0.
And in the lever-free: r73 → a0, r74 → a0, r76 → v0, r83 → v1, r72 → s0.

So the pinned version has ONE FEWER global: in the lever-free version there's an extra global r73 = q. In the pinned version, the q pseudo doesn't exist (q is hard $3).

Now: in the pinned version, r74 (the ptr? or val?) → a0 (preference 4 = the call-arg copy). r76 → v0 (conflicts with v1 → so it's the "val" pseudo? hmm, in the pinned version r76 conflicts with 3 (v1) — that means r76 is live in a block where v1 is used... hmm, v1 = the const/st.

Wait, in the pinned version, is the *val* pseudo r76? "76 conflicts: 76 3 29" → r76 conflicts with v1 → so r76 is live where v1 is used → r76 = the val pseudo? Hmm, but the val pseudo is defined in the arms and used in the join; v1 is used in the pre-branch blocks (the const/st) — hmm, and the pinned version's q is hard $3, so v1 ($3) is used by the const 0x9000 AND the slt result in the pre-branch blocks, AND the switch value in the entry block.

Ugh, the block-granular conflict: the val pseudo r76 is live in blocks 19, 40, 50, 71, 98 (defined in the arm, used in the join) → it overlaps with the blocks where v1 is used (19, 50) → conflict → r76 can't be v1 → r76 → v0 ✓ (matches: val in v0).

In the lever-free version, r76 (val) conflicts {73, 76, 29} — NO v1! Why? Because in the lever-free version, the *q* pseudo r73 is defined in blocks 40 and 71 (after the branch) and the val pseudo r76 also in 40/71... hmm, but the conflict list for r76 doesn't include 3 (v1). Hmm, so in the lever-free version, r76 (val) does NOT conflict with v1, but in the pinned version it DOES.

Interesting. What changed? In the lever-free version, the *q* pseudo r73 occupies the blocks 40, 71 — hmm.

Hmm, wait. Maybe in the lever-free version, the val pseudo is NOT r76. Let me re-map using the .rtl dump (lever-free):
- r72 = arg
- r74 = ptr (loaded in entry, used in the arms as the call arg)
- r75 = st (u16)
- r83 = the zero-extended st (SI) — the switch value
- r84 = const 1, r85 = const 2
- r77 = the call result (case 2), r80 = the call result (case 1)
- r78 = const 36864 (case 2), r79 = the slt result (case 2)
- r81 = const 36864 (case 1), r82 = the slt result (case 1)
- r73 = q (defined in blocks 40 and 71)
- r76 = the value (const 3 in block 40, const 4 in block 71)

So the globals: r72 (arg), r73 (q), r74 (ptr), r76 (val), r83 (the switch value). 5 globals ✓.

Conflicts:
- r73 (q) conflicts {73, 76, 29}: with r76 (val) and sp. Not with v0/v1/a0. Because q is live in blocks 40, 71, 98 and v0/v1/a0 (as locals) are used in blocks 19/50 (pre-branch) → disjoint → no conflict. ✓ (This confirms: v1 is NOT blocked for q!)
- r74 (ptr) conflicts {72, 74, 83, 2, 29}: with arg, the switch value, v0, sp. ptr is live in blocks 19, 50 (the arm pre-branch blocks) → v0 is used there (the call result) → conflict with v0 ✓.
- r76 (val) conflicts {73, 76, 29}: with q. val is live in blocks 40, 71, 98 → v0 (the value's reg) hmm.
- r83 (switch value) conflicts {72, 74, 83, 2, 29}: with arg, ptr, v0.
- r72 (arg) conflicts {72, 74, 83, 2, 3, 4, 29}: with v0, v1, a0 ✓ (arg is live everywhere).

So in the lever-free version, r73 (q) has NO conflict with v0, v1, a0! Its allocation is decided by: (a) the preference (4 = a0) and (b) the scan order (v0 first) and (c) the "regs_used_so_far" rule (pass 0 only reuses dirty regs).

In pass 0, gcc only allocates regs in regs_used_so_far (regs already used by the function). v0 is used (the call result/val), v1 is used (the const/st), a0 is used (the call arg). So all three are candidates. The scan order: v0, v1, a0. But wait — a0 won, not v0. Because the *preference* for a0 overrides the scan order (K5).

So if I can remove the preference (or make it v1), q gets v0 or v1.

But we need q → v1 AND val → v0. The allocation order is r73 (q) first, then r74, r76 (val), r83, r72. If q takes v0 (scan order), then val (r76) would take v1? But the target has val in v0! Conflict.

Hmm, so we need q → v1 and val → v0. Since q is allocated FIRST (higher priority), q takes the first free reg in the scan order... which would be v0 unless v0 is excluded.

How is v0 excluded for q? The conflict set of r73 doesn't include 2 (v0). Hmm. But the *local* allocation: local-alloc gave the val pseudo r76 → hmm, r76 is global (it's in the alloc list).

Hmm, wait: in the lever-free version, which pseudo got v0? The dispositions: 76 in 2 (v0). So r76 (val) → v0. And r73 (q) → a0 (preference). And r83 → v1, r74 → a0, r72 → s0.

If the preference for r73 were absent, the scan (v0, v1, a0) would give r73 → v0 — but v0 is taken by r76 later... since r73 is allocated first, r73 → v0, and r76 (val) would then get v1? But r76's conflict set doesn't include 3 (v1) → r76 → v1 → but the target needs val in v0. So the val would be in v1 and q in v0 → 4 mismatches (the value's li and the store's value reg).

Hmm. So we need q → v1 and val → v0: the allocation order must place q after val, OR the preference must force q → v1 while val → v0.

The preference route: if q's preference were v1 ($3) instead of a0 ($4), then q → v1 (preference overrides) and val → v0 ✓✓✓. That would be a MATCH!

So the lever: make the copy that creates the preference go into v1 instead of a0.

What creates the copy into a0? Let me think: which insn copies the q pseudo into a0? In the RTL before allocation, the store's address needs a reg. The copy is `(set (reg:SI 4 a0) (reg/v:SI 73))`. That's a "copy" created by... expand (for the address) or reload.

Hmm! Per the doc: "Copy preferences (global.c:1538 set_preference, from moves to/from hard regs — param copies, retval copies, pinned-var copies)". A move to a hard reg creates the preference.

Which move? The address copy. In MIPS's mips.md, the `sh` instruction pattern requires the address in a register; when the address is (plus (reg pseudo) (const_int 2)), the "address_operand" pattern can handle it directly (the "mem:HI (plus ...)" alternative). Hmm, but then no copy.

Hmm, but the *reload* pass: for the store's mem operand, reload needs the address in a reg → it creates a reload (not a plain copy). But the preference mechanism (set_preference) is about *copies*, and reload's reload_inp isn't a copy... unless the reload became a copy.

Hmm, but the .greg dump's "73 preferences: 4" means q prefers a0. Let me instead check the *pinned* version: q is hard $3, so no preference. The ptr (r74) prefers 4 — from the call-arg copy `(set (reg:SI 4 a0) (reg/v:SI 74))` ✓ (that's a real copy: the arg copy).

So for r73 (q), the preference to a0 must come from a similar copy. What copy of q into a0? The store's address!

In MIPS's expand, the address (plus (reg r73) 2) for the `sh`: mips.md has:
```
(define_insn "sh"
  [(set (mem:HI (match_operand:HI 0 "address_operand" "=m"))
        (match_operand:HI 1 "register_operand" "=h"))]
```
and "address_operand" for HI includes (plus (register) (const_int))? In mips.md:
```
(define_operand_address "address_operand" "HI"
  (const_int 0)
  (symbol_ref ... )
  (plus (register) (const_int 0)))
```
Hmm, and for the "plus" case, expand would compute the address into a register → a copy to a hard reg chosen by expand (which reg? expand uses a "scratch" — for MIPS, expand's `expand_expr` for a PLUS with a constant creates a new pseudo reg, not a hard reg). Hmm.

Whatever the mechanism, the copy goes to a0. Hmm, and per the doc, the *reload* reg identity = the first wholly-unused call-clobbered reg in regno order → a1 would be the first wholly-unused call-clobbered ($5)... but a0 was chosen. Hmm, so it's not a spill-reload.

Hmm, wait. Maybe the copy into a0 comes from *reload* but as an "output reload" or from the *call* in the join block: the call `func_80178BF8()` clobbers a0-a3! The base value (q) is used in the delay slot AFTER the call → so the value must survive the call → it must be in a callee-saved reg OR reloaded after the call. Hmm! In the target, the base is $3 (v1) which is call-clobbered — but the delay-slot store executes before the call, so no problem.

Hmm OK. Let me find the actual copy. I can look at the .jump dump? No, that's before reload. Hmm, is there a dump between reload and global alloc? The .greg dump's RTL is post-alloc. Hmm.

Alternative: use `-dL` (the local-alloc dump = .lreg) which shows the local allocation, and the .greg for globals. The copy itself is in the RTL.

Let me look at the .greg dump's RTL for the JOIN block in the lever-free version to see the copy's form (post-alloc, so the copy is gone, but its effect shows).

Better idea: the RTL right after reload can be obtained from the .sched dump? No, sched is after alloc.

Hmm, what about the "-dq" reload dump? We saw the file list didn't include one. Let me check gcc 2.7's dump flags: maybe it's -dA? Let me try -dA on the candidate and see the file names (it may produce many files, but the TU is big; the dumps would be large but I can delete after).

Hmm, the risk: -dA might produce enormous dumps. The TU is 8000 lines; the .rtl dump was 1MB. All dumps maybe 20MB. Acceptable.

But actually, is knowing the copy's origin enough? What I need is a C-level lever to change the copy's target reg from a0 to v1.

IDEA: What if the store's address base is *also* used as a call argument? Then the copy would be a call-arg copy → a0 (same).

IDEA: What if the address copy is avoided because the pseudo is *already* in a hard reg? That's the pin.

Hmm, IDEA: what if the pointer is used in the join block in a context where the copy goes to a *specific* reg, like the `slt`? no.

Let me look at the problem from the "how does the ORIGINAL game code look" angle: the target has the base in $3 = v1 with the const 0x9000 also in v1 — meaning the original compiler reused v1 for both the const and the pointer. This is characteristic of a compiler that assigned the pointer to v1 freely.

Hmm! What if in the ORIGINAL source, the pointer was used in a way that made it a *local* pseudo? E.g., if the original source had the stores INSIDE the arms and the join was different? But the target's asm has the stores in the join.

Hmm, hold on! What if the original source's structure was:

```
switch (st) {
case 2: if (f() > 0x9000) return 0; val = 3; break;
case 1: if (f() > 0x9000) return 0; val = 4; break;
default: return 0;
}
q = arg->unk64;    // hmm, one load
```
→ 1 load, not 2. The target has 2 loads. So no.

What if the original source was:
```
case 2: if (...) return 0; q = arg->unk64; val = 3; break;
case 1: if (...) return 0; q = arg->unk64; val = 4; break;
```
That's the current source. OK.

So the original compiler (the one that made the game) assigned the q pseudo to v1. Our gcc 2.7.2 assigns it a0 because of the copy preference.

Hmm, so how do we remove the copy preference? What if the store's address is expressed so that no copy into a0 is created? E.g., if the base offset were 0: `((Unkstruct_801815AC_3 *)q)->unk2` — hmm, unk2 is at offset 2.

What if we made a *different* struct type where the field is at offset 0? The struct layout is fixed by the target's data layout (unk2 at 0x2, unk34 at 0x34). Can't change.

Hmm, but the *address* used for the store could be `q` itself (offset 0) for a *different* field. Not possible.

Hmm, what if the store were `*(u16 *)q = ...`? That's offset 0 → the address is just the pseudo → maybe no copy needed? But then we'd store at offset 0, not 2. The target stores at offset 2 (unk2) and 0x34 (unk34). Can't change.

Hmm, what if the store were `(u16)(q + 2)`... same.

OK, so what creates the a0 copy? Let me hypothesize it's the *reload* of the address into a reg, and per the doc, the reload reg = "the first wholly-UNUSED call-clobbered reg in regno order" — a1 ($5) is unused... but a0 is used (the call arg). Hmm, so the reload would pick a1, not a0. Unless the reload reg choice is different for this kind.

Hmm, hold on: maybe the copy into a0 is not a reload but comes from the *call* `func_80178BF8()` — no.

Let me look at the *pinned* version's .greg RTL for the join block: if the pinned version has NO copy for the address (base = $3 hard), then... yeah.

Let me try to see the pre-allocation RTL. Idea: use `-dA` (all dumps) and look for a "reload" dump file. GCC 2.7's dump file ids (from gcc/dump.c in 2.7): DUMP_CSE, DUMP_CSE2, DUMP_CSE3, DUMP_COMBINE, DUMP_COPY, DUMP_EXPAND, DUMP_FLOW, DUMP_FLOW2, DUMP_GLOBAL, DUMP_JUMP, DUMP_JUMP2, DUMP_LOCAL, DUMP_LOOP, DUMP_RTL, DUMP_SCHED, DUMP_SCHED2, DUMP_SCCP, DUMP_TOP, DUMP_WHIRL... and the flags: -dA = all, -dB = combine, -dC = cse, -dD = flow, -dE = expand?, -df = ..., -dg = global, -dh = ..., -di = ..., -dj = jump, -dk = ..., -dl = local, -dm = sched, -dn = ..., -do = ..., -dp = ..., -dq = ..., -dr = rtl, -ds = flow2, -dt = ..., -du = ..., -dv = ..., -dw = ..., -dx = ..., -dy = ..., -dz = ...

The flags in cc1_dumps_tu.sh: -dr -ds -dj -dl -dg -df -dc -dS -dL -dR -dt -dJ -dd. Given the produced files: rtl, flow, jump, lreg, greg, combine, cse, cse2, dbr, sched, sched2. So -dS = sched, -dL = lreg(local), -dR = ?, -dJ = jump2, -dd = dbr.

So -dR might be "reload"! Let me check: in the dumps_c1 listing: c1.i.combine c1.i.cse c1.i.cse2 c1.i.dbr c1.i.flow c1.i.greg c1.i.jump c1.i.jump2 c1.i.loop c1.i.lreg c1.i.rtl c1.i.sched c1.i.sched2. No "reload" file, but -dR was passed. Hmm, -dR might map to "regmove" or something. The doc mentioned "-dR" in the S103 note? The note says "-dt (the SECOND cse pass, .cse2) and -dJ (the post-reload jump pass, .jump2)".

Hmm, in GCC 2.7 the dump flags include:
-dA all, -dB combine, -dC cse, -dD flow, -dE ?, -df ?, -dg global, -dh ?, -di ?, -dj jump, -dk ?, -dl local, -dm ?, -dn ?, -do ?, -dp ?, -dq ?, -dr rtl, -ds flow2, -dt cse2, -du ?, -dv ?, -dw ?, -dx ?, -dy ?, -dz ?, -dR regmove? -dS sched, -dT ?, -dJ jump2, -dL local, -dM ?, -dP ?, -dF ?, -dG ?, -dH ?, -dK ?, -dN ?, -dO ?, -dQ ?, -dU ?, -dV ?, -dW ?, -dX ?, -dY ?, -dZ ?

Let me check gcc 2.7's dump.c... I recall the reload dump in GCC 2.7 doesn't exist. Hmm. But there's "-dq" for "reload" in some versions? We saw -dq produced nothing (the file list was the same). Hmm, wait, when I ran rdump.sh with -dq -dr, the output files were: c1.err c1.i c1.i.rtl c1.s. So -dq produced no file → -dq isn't the reload dump.

Let me try -dA and see which files appear. If there's a reload dump, great.

Actually, better idea: let me use the .lreg (local-alloc) dump, which prints the local allocation *and* the RTL? Hmm.

Alternatively: since local_alloc runs BEFORE global_alloc (per the doc's pass order: flow → combine → sched1 → local_alloc → global_alloc → reload → sched2 → dbr) — wait!! The doc says the pass order is: local_alloc → global_alloc → reload! So RELOAD runs AFTER global alloc!

Hmm! That changes my understanding: the "preference" (73 prefers 4) is created during global_alloc itself (set_preference from moves to/from hard regs). The copies to hard regs at that point are the *call-arg copies* and *param copies* — created by expand.

So `(set (reg:SI 4 a0) (reg/v:SI 73))` — a copy of q into a0 — must exist BEFORE global_alloc, i.e., created by expand! Why would expand copy q into a0?

AH — I bet it's the *call* `func_80178BF8()`! No, q isn't an arg.

Hmm, what else? The store's address! In expand, the store's address (plus (reg r73) 2) → expand creates a copy into a hard reg for the address? MIPS's mips.md "address_operand" for HI:
```
(define_operand_address "address_operand" "HI"
  (const_int 0)
  (symbol_ref ...)
  (plus (register) (const_int 0)))
```
Hmm, and there's a rule that the "plus" form requires the register to be a hard reg? Hmm.

But wait: the doc's pass order has reload AFTER global_alloc. So the address copy can't come from reload. It must come from expand.

In expand, when a memory reference's address is (plus (reg pseudo) const), expand's `expand_expr` for PLUS creates a new pseudo (not a hard reg). Hmm, but then the *pseudo* would be a different allocno — and the target's asm `sh v0,2(v1)` shows the base is a hard reg with the offset folded. So the "plus" must have been folded into the store instruction by mips.md's pattern.

Hmm, so where does the a0 copy come from?

Hmm, maybe the a0 copy is not for q at all! Maybe "73 preferences: 4" doesn't mean what I think. Let me reconsider: maybe the dump's format is ";; %d preferences:" listing the *pseudos that this pseudo is connected to by copies*. So "73 preferences: 4" = pseudo 73 is copy-connected to pseudo 4?? But pseudo 4 doesn't exist in this function...

OR the format is ";; %d preferences: %d" = (pseudo, preferred reg). For r74 (ptr) → 4 (a0) = the call-arg copy ✓ (that's real: `(set (reg:SI 4 a0) (reg/v:SI 74))`).

For r73 (q) → 4 (a0). So there IS a copy of q into a0 somewhere pre-global-alloc.

Where? AH WAIT. I bet it's this: the store `((Unkstruct_801815AC_3 *)q)->unk2 = val;` — the address is (plus (reg r73) 2) — hmm. But hold on: what about the *second* store `->unk34 = 0` at offset 0x34: the address is (plus (reg r73) 0x34).

Hmm, what if MIPS's expand handles (plus (reg) (const_int)) for a memory operand by creating a copy into a hard reg? In mips.md (gcc 2.7):

```
(define_insn "sh"
  [(set (mem:HI (match_operand:HI 0 "address_operand" "=m"))
	(match_operand:HI 1 "register_operand" "=h"))]
  "TARGET_SH"
```
and
```
(define_operand_address "address_operand" "HI"
  (const_int 0)
  (symbol_ref ...)
  (plus (register) (const_int 0)))
```
Hmm, with (const_int 0) as the offset constraint — the offset must be 0! Then the store `sh v0,2(v1)` has offset 2, so the address must be (plus (reg) 2) — hmm, that contradicts "const_int 0".

Hmm, in GCC 2.7 mips.md I believe:
```
(define_operand_address "address_operand" "HI"
  (const_int 0)
  (symbol_ref ...)
  (plus (register) (const_int 0)))
```
Hmm, but there's also the "unspec" form. The generated asm `sh v0,2(a0)` has the offset folded, which mips.md supports via:
```
(define_insn "sh"
  [(set (mem:HI (plus (register) (const_int 2))) ...
```
Hmm no.

OK, empirical again: let me look for the a0 copy in the pre-global-alloc RTL. The .jump dump is pre-reload and pre-alloc! But wait, the doc says reload runs after global alloc, so the .jump dump (jump pass) is way before. Hmm, but the .jump dump would show the RTL before expand? No, expand runs before jump.

Order in gcc 2.7: flow → ... → expand → jump → loop → cse2 → flow2 → combine → ... → sched → local_alloc → global_alloc → reload → ... Hmm, the doc's slice says: flow → combine → sched1 → local_alloc → global_alloc → reload → sched2 → dbr.

So the .jump dump is before local_alloc → it shows the RTL with pseudos (pre-alloc). But the .rtl dump (from flow) is even earlier.

The .jump dump would show whether the a0 copy exists before allocation! Let me grep the .jump dump for the function section.

The dumps_c1 dir has c1.i.jump. Let me extract the func_801815AC section and look for copies into a0.

Let me do that.

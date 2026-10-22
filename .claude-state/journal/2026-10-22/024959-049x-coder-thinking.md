---
ts: 2026-10-22T08:49:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_pVkWrTgjljmrNxYuNsC5
---
w1: base still a0, and the store order swapped. Score 4 still.

So the reload picks a0 regardless of the call position.

Hmm. So the reload's reg choice is a0 for the address. What determines it? In GCC 2.7's reload.c, the address reload's reg is chosen to be the same as ... hmm.

Let me look at MIPS's reload: In reload.c, `reload_inp[j].out_reg` selection: `choose_as_reload_operand`. But for a MEM address reload, there's also the concept of the "reload being a copy of the address into a reg". GCC 2.7's reload.c `reload_inp` for the address: `inp = operand_index (insn, i)`, `inp->r = MEM`, and the reload is a "reload_inp" of type INPUT_ADDRESS. The reg choice: `choose_as_reload_operand`.

In GCC 2.7's choose_as_reload_operand:

```c
  /* Find a reload register.  */
  ...
  /* If the reload is for a hard reg, ... */
  ...
  for (i = 0; i < (int) regclass->n_regs; i++)
    {
      r = regclass->regs[i];
      if (! TEST_HARD_REG_BIT (regclass->regs, r))
	continue;
      if (reload_inp[j].r == r) ...
      /* Avoid a register that is live at the reload point... */
      if (reg_occupied[j] ...)
      ...
    }
```
Hmm, but there's ALSO this in GCC 2.7's reload.c:

```c
      /* If this is a reload of a pseudo that is not the destination of the
	 insn, and the destination is a hard reg, prefer the same reg. */
```
Hmm! That could be it: for `sh v0, 2(base)`, the "reload" of the address might prefer the same reg as... no, the destination is memory.

Hmm, but wait: in GCC 2.7's reload.c there's a rule I definitely remember:

```c
	  /* If the register is used by the insn itself, don't use it. */
```
and
```c
	  /* Prefer a register that is not used elsewhere in the function
	     (to avoid needing to save it). */
```

Honestly, a0 is used as a call arg reg in this function, and v1 is used for the const/st. Both are "used". Hmm.

Alternatively, maybe the choice comes from the *class order* in MIPS: GR_REGS order in mips.md for gcc 2.7:

```
(define_reg_class "general" "GENERAL_REGS"
  (0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31)
  (0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31))
```
Hmm, then the first allocatable hard reg is $2 (v0). But reload picked a0.

Wait, maybe reload picked a0 because v0 and v1 were "live" at the reload point in the *whole-function* sense (regs_ever_live)? v0 is live (the value), v1 is live (the const/st). a0 is live too (the call arg). Hmm, but the reload is at the join block, where v1 is dead.

GCC 2.7's reload.c has `reg_occupied` (per-block) and a global `regs_ever_live`? Hmm, there's `reload_inp[j].r` and the concept of "reload_inp[j].in_reg" vs "out_reg" and the "dependent reloads".

There's also this in GCC 2.7's reload.c choose_as_reload_operand:

```c
      /* Don't use a register that is live across a call in this block... */
```
Hmm, the join block has a call (func_80178BF8) after the store! So a reload in a block with a call must use a CALL-CLOBBERED reg (since the reload value must survive the call? no, the store is before the call).

Hmm! Actually, in GCC 2.7's reload.c, when a reload is in a block that contains a call, the reload reg must be a call-clobbered reg (or the value is reloaded after the call). Since the store is before the call, the address value must live across the call? No, the second store (in the delay slot) is after the call!

In the target: `sh v0,2(v1); jal func_80178BF8; sh zero,52(v1)` — the second store is in the delay slot, i.e., AFTER the call. So the base register v1 must survive the call → v1 is call-clobbered ($3) → the value must be reloaded after the call! Hmm, but the target shows `sh zero,52(v1)` with v1 = the same reg as before the call. If v1 were call-clobbered, the value would be lost after the call. So gcc must have reloaded it... but there's no reload after the call in the target!

Hmm, the delay slot instruction executes BEFORE the call takes effect (the delay slot is part of the call). So `sh zero,52(v1)` executes before the call. So the base is used before the call effectively. OK, so no issue.

So in the target, the base is $3 = v1, which is call-clobbered, and it's used before the call.

Now for the lever-free version: the base is a0 ($4), also call-clobbered. Both fine.

So why a0? Reload's reg choice. Since the reload's value is used before the call, a call-clobbered reg is fine.

Hmm, so the choice of a0 over v1 must come from reload's "preferred" list.

Let me try an experiment to find out: make a0 *live* across the join block so the reload can't use it. How? a0 is the first arg reg. If the function had a call in the join block with an argument... the target's join call has no args.

Hmm, alternatively: make the pointer's *reload* happen where a0 is occupied. Hmm.

Alternatively, maybe the reload reg choice depends on the *first* reload in the function: GCC's reload allocates reload regs in order; the first reload gets the best reg. Are there other reloads in this function? The `lw v1,100(s0)` loads are direct (no reload). The const 36864 → a pseudo → local_alloc → v1 (not a reload). The call args → expand copies (not reloads).

Hmm, so the q address reload is likely the only one. It got a0.

Let me look at MIPS-specific reload rules. In GCC 2.7's reload.c, `choose_as_reload_operand`:

```c
  /* Try to find a reload register that is not live at the insn. */
  ...
  for (i = 0; i < (int) regclass->n_regs; i++)
    {
      r = regclass->regs[i];
      if (! TEST_HARD_REG_BIT (regclass->regs, r))
	continue;
      if (reload_inp[j].r == r)
	continue;
      if (reg_occupied[j] ...)
	continue;
      /* If the register is live at this insn, skip it. */
      ...
      /* Prefer registers that are not used in the function at all. */
```
Hmm.

You know what? There's a much better way to find out: gcc 2.7's reload.c has a debug dump? We saw the dump files: no reload dump. Hmm.

OK. Let me try instead to make the *whole approach* different: what if the pointer q is NOT used as an address in the join, but the stores are done through a *dereference of a dereference*? no.

Hmm, let me reconsider: maybe the base reg in the target is not "q's reg" but rather the *reload* reg, and in the target the reload didn't happen because q was hard $3.

What if we make q hard $3 *without* a pin?! E.g., by making q a *function parameter*? Not allowed (signature change). By making q a *global variable* (file-scope)? Then q would be in memory → different code.

Hmm, what about `register` keyword? Explicitly forbidden ("no `register` vars").

What about making q an *asm-constrained* var? Forbidden (no __asm__).

Hmm, so the pointer must be a normal pseudo, and its reg is decided by global_alloc (using the preference) → a0.

To change the preference, the reload's reg must change. What determines it? Let me test with a cheap experiment: add a dummy *use* of a0 in the join block? Not possible without changing code.

Hmm, what about this: the reload reg choice might depend on the *number of reloads* and the "reload priority". If a SECOND reload existed earlier in the function and took a0, our address reload might take v1 (the next in the class order). What earlier reload could exist? A reload of a value into a reg for a call argument! E.g., if the call `func_8012BD14(ptr)` had its argument as a *pseudo* that needed a reload... hmm, the call arg copy is `(set (reg:SI 4 a0) (reg/v:SI 74))` — that's expand's copy into a0, not a reload.

Hmm, but wait: what if the call argument were a *memory* operand? e.g. `func_8012BD14(arg->unk64)`? Then expand would need to load the value into a0 → a RELOAD! And that reload would take a0 (the arg reg) — same reg. Hmm.

What if the call argument were something requiring a reload into a *different* reg? Hmm.

OK, alternative: maybe I can shift the reload's reg by making the *address expression* more complex so that the reload is of an "address" that needs a *scratch* reg chosen differently.

Hmm, let me try a different experiment first: check whether the reload's reg choice is affected by the *order of the pseudo definitions* — e.g. what if the join block's store were the only use of q (i.e. the second store used a different spelling)? Hmm.

Time check: it's been ~35 min on item 1. I need to be careful about the budget: 3 items, 20-30 min each. Let me limit item 1 to ~50-60 min total, then move on.

Let me try a few more high-value experiments for item 1:

X1: What if the *value* val is a `u16` and the store is `q->unk2 = val` — tried (v07/v08: s16/u8 val) — score 4.

X2: What if the q pointer is loaded ONCE before the switch and the arms use it? Different shape.

X3: What if the arms' `q = arg->unk64` is written as `q = ptr;`? — that's a copy, and ptr is reloaded? No: `q = ptr` would use the stale ptr (loaded before the call) → the asm would be a move, not a reload → different insns (the target has `lw v1,100(s0)` in the arms). But hmm, interesting: if the source said `q = ptr;` then... the target's arms do a reload, so no.

Hmm wait, actually! What if the source is `q = ((Unkstruct_801815AC_2 *)arg)->unk64;` but the *ptr* variable is used in the arms for the call. What if the call's argument were `arg->unk64` (reloading) instead of `ptr`? Then the call arg copy would be `(set (reg a0) (reg r74))` hmm, same.

X4: What if we could make the *reload* happen for the LOAD instead of the store? I.e., if the load's destination pseudo q were... no.

X5: What if the pointer were used in the join block by a *comparison* first? e.g. `if (q) {...}` — changes code.

Let me look at this from the "what would the original game source look like" angle. The target asm:

```
lw a0,100(s0)     ; ptr
lhu v1,2(a0)      ; st
...
jal func_8012BD14
li v1,0x9000
slt v1,v1,v0
bnez v1,default
lw v1,100(s0)     ; q reload
li v0,3
sh v0,2(v1)
jal func_80178BF8
sh zero,52(v1)
```

Note: `lw v1,100(s0)` — the reload of q right after the branch, in v1. And the const 0x9000 was in v1 earlier (dead by then). So the ORIGINAL compiler allocated v1 to both the const and q. This is the same "reuse" pattern as the pin.

For plain C to reproduce: the q pseudo must be allocated $3 by global_alloc. Given the preference mechanism (reload copy → a0), the only way is if the reload copy goes to v1.

Hmm! Unless the *preference* is absent and the reg order picks v1 before a0. Is the class order v0,v1,a0? If v0 and v1 were both "occupied" (v0 by the value/result, v1 by the const/st live in the function), then a0 is the first free. So without the preference, a0 would still be chosen. So the preference isn't decisive either.

Hmm, so both mechanisms point to a0.

To get v1, the reload's reg must be v1, which requires v0 and v1 to be unavailable at the reload point... but v1 IS the target's choice! So the reload must pick v1 while v0 is unavailable.

In the target (pinned), there's no reload at all.

Hmm, so how could a lever-free version have the base in v1? The reload's reg choice is what it is: a0 (because v0 and v1 are live-ish?). Hmm, but v1 is NOT live at the join block. Unless the reload's "occupancy" check is function-wide (regs_ever_live), in which case v1 (used by the const) is excluded and a0 (used by the call arg) is also excluded... but a0 was chosen! So the check isn't function-wide for a0.

Hmm, wait. Maybe the reload's reg choice prefers a0 because of the *call argument* connection: the reload is in the same block as a call (func_80178BF8) — and for a reload in a block with a call, GCC 2.7 requires the reload reg to be... hmm.

Honestly, let me look at GCC 2.7's reload.c source. I might find it in the repo's docs or in a research report. Let me search the repo for "choose_as_reload_operand" or "reload.c" mentions in the cookbook/research.

Actually! The project has research reports and a cookbook. The brief says to grep cookbook/INDEX.md and rules/INDEX.md for the task's subjects. Let me grep for "reload" in cookbook and research indexes. That might contain the exact mechanism (e.g. C0162 was mentioned in moves.md: "sched2-unit-blockage — r3000 memory-unit blockage(load,store)=2 wedges the wq srl; zero-byte re-tie absorbs it (C0162)").

Let me grep the cookbook index for "reload" and "preference".

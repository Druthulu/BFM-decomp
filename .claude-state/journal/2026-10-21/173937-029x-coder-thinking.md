---
ts: 2026-10-21T23:39:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_rLXx6eP25xBD7sbmx6BZ
---
Interesting! In mine the c1 constant load is at 2748 (right before its uses) and it does `sh v0,20(s0); sh v0,36(s0)` — and importantly, note the ORDER: mine stores 0xA0 at 28,44; -0x78 at 22,30; -160 at 20,36; 0x78 at 38; then `sb v1,42(s0)` (the 12th byte) at 275c.

Target order: 0xA0 at 28,44; -0x78 at 22,30; 0x78 at 38 (2754); c1 at 20,36 (274c,2750) — wait target: 2748 li v0,120; 274c sh v1,20(s0); 2750 sh v1,36(s0); 2754 sh v0,38(s0); 2758 sb a2,42(s0); 275c jal AddPrim; 2760 sh v0,46(s0).

Mine: 2748 li v0,-160; 274c sh v0,20; 2750 sh v0,36; 2754 li v0,120; 2758 sh v0,38; 275c sb v1,42; 2760 jal; 2764 sh v0,46.

So the difference: target's -160 was hoisted to position 60 (early, `li v1,-160` at 2714) and the last byte load is in a2.

Key: in the target, c1's value is loaded early (2714) because it was pinned to $3, and $3 was free. In mine, c1 shares v0 with the constants, so it can only be loaded at 2748 (after the other v0 constants are dead).

So the fix: make c1 use a different register than the constants. The natural way: make c1's live range *not* overlap the constants' live ranges? Impossible in one BB — hmm, actually they're all in the same BB and the ranges are sequential. Local-alloc can share a reg between pseudos with disjoint live ranges within a BB! c1's range: set at its assignment point → but in the target the load is hoisted early, meaning local-alloc assigned c1 a register that was free.

Hmm, wait. Why did mine put `li v0,-160` at 2748 rather than earlier? Because in the *pre-scheduling* IR, c1 = -0xA0 is set right before its uses, and c1 shares v0 with the constants which are live until their uses. If c1 had its own register ($3), the load could be hoisted earlier (sched1 would hoist `li v1,-160` since it's independent).

So: how to get c1 into $3 (v1)?

Idea: give c1 a *separate* register by making its live range overlap-free... no, we need a different color.

Better idea from the moves catalog: "u16 var + ..." Hmm.

Think about the priority order in local-alloc. The byte-load pseudos: 12 of them, each 1 set + 1 use, but note the last one has a long live range (its store is far away). Actually the 12th byte pseudo in mine got v1 — meaning it was considered a distinct allocno needing a different reg than v0 (its live range overlaps others? no...).

Hmm, in mine the 12th byte load got v1 because at that point v0 was occupied by the constants? But the load is at 271c and the store at 275c — the range spans the constants' live ranges, so it conflicts with v0 → assigned v1.

So the ordering of allocation: local-alloc assigns by priority. c1 (live range long: from set to 2 uses spanning constants) got v0 first. Then the 12th byte pseudo conflicts → v1. Others (byte pseudos 1-11, short ranges, disjoint) can share v0.

Now, in the target: c1 pinned to $3. The 12th byte pseudo got a2 ($6) instead of v1! Why a2 and not v1? Because in the target, when the 12th byte pseudo was allocated, $3 was taken by c1 and $2 (v0) was taken by... hmm, and $1 (at) was used for the D_800A651C address, $4-$7 args. So v1 ($3) — why not? Because c1 has $3 pinned; the 12th byte pseudo could have had $3 except it's occupied by the pinned c1. And $4,$5,$6,$7: $4 (a0) holds a0 arg → a0 is live (s1) but the pseudo a0 is used for the call at 275c... Actually a2 is used for `lw a2,28(s1)`. $4 = a0 is used for the AddPrim call at 275c (a0=s2) — a0 is live across the whole function (arg a0 → s1 copy). $5 (a1) is used as the arg `addiu a1,s0,12` for the AddPrim call at 275c, and it's set at 2708 (addiu a1,s0,12) so live from 2708 → conflicts. $7 (a3) = tp value? and $6 (a2) free.

So the 12th byte pseudo got $6 because $2 (v0) was occupied by the constants in that range, $3 by pinned c1, $4 by a0, $5 by a1, and $6 was the first free.

OK so to reproduce without pin: I need c1 to get $3 and the 12th byte pseudo to get $6, and the constants to get $2.

This is a delicate allocation puzzle. Options:

Option A: Make c1 a *different* pseudo with higher priority than the constants so that c1 takes $2 and the constants take $3 — no, we need the opposite.

Option B: Reduce the number of conflicting pseudos so that after c1 takes $2... no.

Option C: Give c1 a long live range that *starts* before the constants and *ends* after, so that c1 conflicts with the constants' ranges; then whichever gets allocated first takes $2. We want the constants to get $2 and c1 to get $3. The constants (0xA0, -0x78, 0x78) each have 2-3 refs; c1 has 3 refs. Priority tie-break: local-alloc's priority function:

In GCC local-alloc.cc:
```
static int
allocno_priority (int n, allocno *a, reg_or_regclass_t rtx, reg_or_regclass_t reg)
{
  int reg_class_size = regclass_num_regs[reg_class];
  int size = 1;
  int weight = 0;
  ...
  weight += REG_FREQ (reg) * 4;   /* frequency */
  weight += REG_LIVE_LENGTH (reg) * 2;  /* live range length */
  ...
}
```
Actually I recall:
```
  /* Compute the number of references to the pseudo.  */
  ...
  weight += REG_N_REFS (reg) * 2;  ?
```
Not sure. But there's a tie-break by allocno number (order of creation) for equal priority.

Hmm, but here's a cleaner idea: in the target, the constants 0xA0, -0x78, 0x78 all got $2 — they don't conflict with each other. And c1 got $3. In mine, c1 got $2 (allocated first, higher priority) and the constants got... wait, the constants in mine ALSO got v0! Look: `li v0,160`, `li v0,-120`, `li v0,-160`, `li v0,120` — all v0! And c1 = the -160 one, also v0. So in mine, c1 and the constants share v0, meaning their live ranges do NOT overlap in the IR (they're sequential). Right! In the pre-schedule IR, c1's range is set→use,use, and the constants are set→use,use, sequential, so all share v0.

And the 12th byte pseudo conflicts with v0 (because it's live across all of them) → got v1.

In the target (with pin), c1 was forced to $3, so the constants could keep v0.

So the challenge: make c1 conflict with the constants' allocno (so it needs a different color), while the constants get $2 and c1 gets $3.

c1 conflicts with the constants if their live ranges overlap. c1's range overlaps 0xA0's if c1 is set before 0xA0's last use, e.g. if c1 = -0xA0 is set BEFORE the 0xA0 stores. Then c1 (live from that point through its 2 uses) overlaps 0xA0's range (set→2 uses) if the 0xA0 uses come after c1's set. Then one of them takes $2 and the other $3.

If c1 is set first (before 0xA0 stores) and c1 has higher priority (longer live range), c1 takes $2 → wrong. We want the constants to take $2.

Hmm, but which takes $2? Priority decides. If the constant 0xA0 has higher priority than c1 → 0xA0 takes $2, then c1 must take a different reg: $3 (if free) — but also the 12th byte pseudo needs a reg, and it wants the same.

But careful: the ordering of allocation is by priority; the 12th byte pseudo (long range) has high priority too (long live range). In the target it got $6 — the last of the free ones. Hmm, in the target, why didn't the 12th byte pseudo get $3 (v1)? Because $3 was pinned to c1. So it got $6.

So in an unpinned version, we need:
- c1 → $3
- 12th byte pseudo → $6
- constants & other bytes → $2

That means: the 12th byte pseudo must be allocated AFTER c1 (lower priority than c1) and must conflict with $2, $3, $4, $5. But the 12th byte pseudo's live range is long (spans everything) → high priority → would be allocated before c1, taking $2.

Hmm, but in mine, the 12th byte pseudo got $3 (v1) and c1 got $2. So indeed the byte pseudo was allocated after c1? Or c1 was allocated first and took $2, then the byte pseudo conflicted and got $3.

Wait, but the 12th byte pseudo has a longer live range than c1 in mine? In mine c1's range: set at "c1 = -0xA0" (in source, right before its uses) → uses. The 12th byte's range: set at the load (source position 12th byte store area) → use at sb 42.

Source order: the 12 byte stores come first (positions 1..12 of the byte group), then `*(u8*)(p+0xF)=8`, `*(u8*)(p+0x13)=0x3A`, then the s16 stores. So the 12th byte load (for 0x2A) is at source position 12 and its use is right there. Hmm, then why is its store 275c (way later) in the output? Because scheduling moved the load early? No — the load is at 271c which is source position 12 (right after 11th) and the store is at 275c.

That's weird — the store `sb v1,42(s0)` (12th byte, p+0x2A) got scheduled very late, after all the s16 stores. Because the source order is: byte stores for 0x10,0x18,0x20,0x28,0x11,0x19,0x21,0x29,0x12,0x1A,0x22,0x2A — the 12th is 0x2A=42. Then 0xF=15, 0x13=19. Then s16 stores. So the 12th byte store (42) should come before the s16 stores in source. But in the output it comes after (275c). So the scheduler moved the *load* early? No, the load is at 271c which is in the middle of the byte group.

Wait, look at the target: 2710 `lw v0,28(s1)` (11th byte load), 2718 `sb v0,34(s0)` (11th store: 0x22=34), 271c `lw a2,28(s1)` (12th load), 2720 li v0,8, 2724 sb v0,15(s0) (the 0xF store!), 2728 li v0,58, 272c sb v0,19 (0x13), 2730 li v0,160, 2734/2738 sh 28,44, 273c li v0,-120, 2740/2744 sh 22,30, 2748 li v0,120, 274c sh v1,20, 2750 sh v1,36, 2754 sh v0,38, 2758 sb a2,42 (the 12th byte store!), 275c jal AddPrim, 2760 sh v0,46 (the 0x2E store).

So the 12th byte store was delayed until 2758 — after all the s16 stores. Why? Because in the source, the 12th byte store is the last of the byte group and the s16 group follows; the scheduler (sched1) reordered the s16 stores before the 12th byte store? That seems odd but it's what the target does, and my unpinned version reproduces it too (sb v1,42 at 275c). OK so the scheduler does that in both.

The long live range of the 12th byte pseudo (load at 271c, store at 275c) is due to the *scheduler* moving the load up? Actually, the load must be at 271c in the output because it was scheduled there, but the live range in local-alloc is computed on the pre-sched IR... Hmm, but local-alloc runs after expand and before sched? Order in GCC: expand → local-alloc? No: the RTL pipeline is: expand, ... , cse, ..., regmove, ..., sched (sched1), ..., reload, ..., local-alloc? Actually local-alloc (IRA-free classic) runs late, after reload. Hmm, in older GCC (this looks like GCC 4.x/5.x for MIPS), the order is: expand, jump, cse, ..., sched1, ..., reload, ..., local-alloc? No: local-alloc comes before reload? Let me recall: `expand` → `jump` → `cse` → `cse2` → `sched1`? Hmm.

Order in gcc (RTL passes, from pass.def): expand, ..., cse, ..., sched (sched2?), ..., local-alloc, ..., reload? Actually I believe: expand → ... → cse → cse2 → ... → sched1 → ... → local-alloc? no.

The classic order: expand, shrink-wrap, ..., cse, ..., sched1, ..., split-loops, ..., regmove, ..., local-alloc, ..., reload, ...

Hmm no. From GCC's pass.def (older): after expand comes "jump", "loop", "cse", "cse2", "gcse", ..., "sched1"? Hmm, "sched" (sched2) is later.

Honestly, in the classic pipeline: expand → cse → ... → sched1 → ... → local-alloc? No — local-alloc is after reload? Let me think: reload needs register assignments, so local-alloc must come before reload. And sched1 (the pre-register-allocation scheduler) comes before local-alloc. So order: expand → cse → cse2 → sched1 → local-alloc → reload → ... → final scheduling (sched2).

So the live ranges that local-alloc sees are post-sched1. That's why the 12th byte pseudo has a long live range (sched1 moved the load up but left the store late).

Given that, priorities are computed on post-sched1 live ranges. The 12th byte pseudo has a long range → high priority → allocated early → should get $2! But in mine it got $3 and c1 got $2.

Hmm, so c1 has even higher priority. In mine, c1's set was at 2748 (right before uses) — a short range! And yet c1 got $2 over the long-range byte pseudo. So priority isn't purely live-range length. In GCC's local-alloc, the priority is:

```
  /* Compute a priority for the allocation.  */
  ...
  weight = 0;
  /* Frequency is a major factor.  */
  weight += REG_FREQ (reg) * 4;   ??? 
```
Hmm. Let me recall the actual code (gcc/local-alloc.cc, function allocno_priority):

```
static int
allocno_priority (int n, allocno *a, reg_or_regclass_t rtx, reg_or_regclass_t reg)
{
  int reg_class_size = regclass_num_regs[reg_class];
  int size = 1;
  int weight = 0;

  /* Unless regs are live at the start of the function, there is a
     good chance we can assign a reg to an allocno whose live range
     is short.  */
  ...
  /* Add the number of references to the pseudo.  */
  weight += 2 * REG_N_REFS (reg);  /* ??? */
  ...
```

I recall the priority formula in local-alloc:
```
  weight += REG_LIVE_LENGTH (reg) * 4;
  weight += REG_FREQ (reg) * 4;   /* hmm */
  weight += REG_N_REFS (reg);
```
Not sure. But the empirical result: c1 (3 refs, short live length) got $2 over the byte pseudo (2 refs, long live length). And the constants 0xA0 (3 refs) also share $2 with c1.

Hmm, if c1 (3 refs) and 0xA0 (3 refs) both got $2, and they don't conflict, then ties are broken by... they can share since no conflict.

Key question: in the target, the constants got $2 and c1 got $3. If c1 has the same priority as 0xA0, the tie-break (allocno order) put 0xA0 first, so 0xA0 got $2, c1 got $3 — but wait, they don't conflict, so c1 could also take $2. Unless in the target they DO conflict: c1 pinned to $3. The pin forces it.

Hmm OK. So without the pin, c1 and 0xA0 don't conflict → c1 gets $2 as well (as in mine).

So the crucial insight: I need c1's live range to CONFLICT with the constants' ranges, and I need the constants to be allocated first (higher priority or earlier tie-break), so c1 goes to $3.

How to make c1 conflict with a constant? Overlap their live ranges. E.g., set c1 = -0xA0 BEFORE the 0xA0 stores, so c1's live range (set → 2 uses later) overlaps 0xA0's range (set → 2 uses). Then one of them needs a second color. If the constants are allocated first (higher priority: 0xA0 has 3 refs like c1; tie-break by allocno order = order of appearance in the RTL?), then 0xA0 gets $2 and c1 gets $3.

But careful: c1's range also overlaps -0x78 and 0x78's ranges → then c1 conflicts with all of them, and the constants would all be in $2 (fine, they don't conflict with each other), c1 in $3. 

And the 12th byte pseudo must get $6, i.e. it must be allocated after c1 and conflict with $2,$3,$4,$5. Hmm. In mine, the 12th byte pseudo got $3 (v1) — it conflicted with $2 (taken by c1+constants). If c1 takes $3, then the 12th byte pseudo needs $4 or $5 or $6. $4 (a0) is live? a0 is used at the AddPrim call (a0=s2 at 2764) and at the start (move s1,a0). The pseudo a0 is live from function entry to the call → conflicts. $5 (a1): a1 is set at 2708 (addiu a1,s0,12) and used at the call → live from 2708 to 275c; the 12th byte pseudo's range is 271c-275c → overlaps → conflict! So $5 is out. $6 (a2): a2 is set at 2688 (move a2,zero for the func_8005A600 call) and used at the call — dead after. So $6 is free → the 12th byte pseudo gets $6 = a2. 

So the plan works if c1 conflicts with the constants and c1 is allocated after them.

But wait: in the target, c1 is in $3 and the 12th byte in $6 — consistent with my analysis. 

Now, will c1 (set before the constants, live until its 2 uses) conflict with 0xA0 (set and used twice)? Sequence in source with c1 set early:

```
c1 = -0xA0;              // set c1
*(s16*)(p+0x1C) = 0xA0;  // set 0xA0, use
*(s16*)(p+0x2C) = 0xA0;  // use
*(s16*)(p+0x16) = -0x78; // set, use
*(s16*)(p+0x1E) = -0x78; // use
*(s16*)(p+0x14) = c1;    // use c1
*(s16*)(p+0x24) = c1;    // use c1
*(s16*)(p+0x26) = 0x78;  // set, use
*(s16*)(p+0x2E) = 0x78;  // use
```
Here c1's range: from set to its uses (spanning 0xA0 and -0x78 ranges). 0xA0's range: set→use,use, entirely inside c1's range → conflict. -0x78's range also inside → conflict. 0x78's range: set after c1's last use → no conflict with c1 (but conflicts? c1's range ends at its last use which is before 0x78's set) → 0x78 can share $2 with the others.

But the scheduler may reorder: sched1 might sink the `c1 = -0xA0` constant load to just before its uses, shrinking its range. In the target, `li v1,-160` was hoisted EARLY (position 60). Hmm, that's because c1 was in $3 which was free, so sched1 hoisted it.

Priority: c1 now has 3 refs and a LONG live range (spans 0xA0/-0x78 stores) → high priority → allocated FIRST → gets $2 → wrong!

Ugh. Priority favors the long range. So c1 would take $2 and the constants get $3+.

Unless... in the target, c1 is pinned so it doesn't matter. Hmm.

Alternative: give the constants higher priority than c1. The constants 0xA0 (3 refs: 1 set + 2 uses) and -0x78 (3 refs) vs c1 (3 refs). Tie → break by allocno order (creation order). If c1 is created later in the RTL than the constants, the constants win $2. In RTL, the constants appear in program order (sched1 output order). So if the constant stores come BEFORE c1's set in the final RTL, the constants are earlier allocnos → they get $2 first (if priority ties) → c1 gets $3.

But c1's live range is longer → priority might exceed the constants'.

Alternatively, make c1's live range short but conflicting. Conflict requires overlap. A short range that overlaps: c1 set right before 0xA0's second use? E.g.:

```
*(s16*)(p+0x1C) = 0xA0;
c1 = -0xA0;
*(s16*)(p+0x2C) = 0xA0;   // 0xA0 still live
*(s16*)(p+0x14) = c1;
*(s16*)(p+0x24) = c1;
```
Then c1's range is short (from its set to its uses) but overlaps 0xA0's range (0xA0's second use is after c1's set). Conflict! And c1's live range is short → low priority → the constants (which also have 2 uses each) get $2.

Hmm, but priority = f(refs, live length). 0xA0: 2 uses, live length spanning 2 stores. c1: 1 set + 2 uses = 3 refs, short length.

Ugh, uncertain. Empirical iteration is the way: I have ~1s per candidate, so I can try dozens of variants.

But hold on. There's a much more important question: does the target's exact instruction order (the `li v1,-160` at position 60, and the sb a2 at 2758) even arise? The scheduler behavior depends on register allocation. If c1 gets $3, sched1 might hoist the li -160 early like in the target. But sched1 runs BEFORE local-alloc... so how does the target's early `li v1,-160` arise if the register assignment happens after sched1?

Hmm! That breaks my pipeline assumption. In the target (built from src with the pin), the `li v1,-160` is at 2714 — early. If sched1 ran before local-alloc, the constant's position would be decided by sched1 regardless of the register. So why is -160 early in the target but late in mine?

Because the register allocation happened BEFORE scheduling in this build? Maybe the build uses a different pass order, e.g. with -fno-schedule-insns? Or the constant propagation/other pass rewrote it.

Actually, more likely: in the target, the pin `register s32 c1 __asm__("$3")` makes c1 a hard reg, so the RTL uses $3 for c1 from the start. Then in the RTL, c1's set is `li $3,-160`? And sched1 (or the RTL expansion) hoisted it? Hmm.

Alternatively the difference: in mine, c1 shares $2 with the constants, so the RTL has `li $2,-160` placed at its source position; then after local-alloc... no, local-alloc is after sched1, so sched1 had already placed it. But the constant's *position* doesn't depend on the register.

Hmm, but the *number of instructions* differs (91 vs 90) and positions differ. So something differs in the pre-alloc pipeline: in the target, the c1 value is loaded early — meaning in the target's RTL (pre-sched1), the `li -160` was placed early. Why? Because of the *pin*: with a hard register, GCC's RTL for `c1 = -0xA0` might be... hmm, no.

Let me look at it differently: maybe the difference is cse! In the target, `li -160` might be CSE'd/hoisted. Hmm.

Wait, maybe the difference: in the target, the constant -160 is loaded into $3 and $3 is used for something else? No.

Alternatively, the ordering difference comes from reload/regmove: after local-alloc, if c1 gets $2 and shares with the constants, then a "move" might be needed... but reload is after local-alloc, and it may insert moves. The extra instruction in mine (91 vs 90) might be a regmove.

I think the more productive approach: iterate empirically over many body variants. Let me think about what C-level variations can produce the target asm.

Let me reconsider: In the target, the sequence at 2710-271c:
```
2710: lw v0,28(s1)     ; 11th byte load
2714: li v1,-160       ; <- c1 loaded here (early!)
2718: sb v0,34(s0)     ; 11th byte store
271c: lw a2,28(s1)     ; 12th byte load
```
And the li v1,-160 is interleaved in the middle of the byte group! That's typical of a scheduler that moved the constant load up (it's independent) into a slot. Then the -160's uses are much later (274c, 2750).

In mine, `li v0,-160` at 2748, right before the uses. So in mine the scheduler did NOT hoist it (or couldn't because $2 was busy — scheduling happens before allocation though!).

Unless... the allocation happened BEFORE sched1? Let me check: in the target, the -160 is in $3 and hoisted; in mine, -160 is in $2 and not hoisted. If the register were chosen by local-alloc after sched1, the hoisting decision couldn't depend on the register... unless the hoisting was blocked by a conflict: in mine, the li would be at $2 which conflicts with the byte load v0 at that point (live range conflict) → the scheduler (pre-alloc) works on a machine-independent RTL where the conflict is between the pseudo c1 and pseudo byte12. In the target, c1 is $3 (hard reg) — no conflict with the byte pseudos at all (they're in $2). So the scheduler could freely hoist c1's li.

So the pipeline must be: register allocation BEFORE the final scheduling? Or: the RTL is scheduled (sched1), and the pre-alloc scheduler treats c1 as a pseudo; in the target (pinned to $3), c1's pseudo is a hard reg → no conflict with the byte pseudo ($2) → sched1 hoists the li. But in mine, c1 is a pseudo → conflict with the byte pseudo (both want regs) → the scheduler keeps them ordered → li stays near its uses.

Yes! That's consistent: sched1 runs before local-alloc, and c1-as-pseudo conflicts with the byte-12 pseudo (long range) in the scheduler's view, blocking the hoist. Once c1 is in a distinct hard reg ($3), the scheduler can hoist it.

But in the unpinned candidate, the hoisting is blocked because c1's pseudo conflicts with the byte pseudo in the scheduler. To get the target's early `li`, c1 must be conflict-free w.r.t. the byte pseudos at that point... but then it also doesn't conflict with the constants...

Hmm, but wait: in the target, c1 is $3 and the constants are $2, so c1 doesn't conflict with the constants either. In the unpinned version, c1 shares $2 with the constants (no conflict) but conflicts with the byte-12 pseudo (whose range is long). Actually in the *scheduler's* view, the conflict is with whichever pseudo has an overlapping live range. Byte-12's range (load at 271c → store 275c) is long. c1's range (set → 2 uses) is medium. They overlap → conflict → ordering constraint.

In the target, c1 is hard-reg $3 so no conflict → free to hoist.

So to reproduce, I'd need c1 to be in a different register *before* scheduling. That's not possible without a pin... unless the register allocation is done by IRA before scheduling. GCC has IRA (integrated RA) which does global allocation before reload and final scheduling; with IRA, allocation happens before sched2 (final) but after sched1. Hmm.

OK — maybe this build uses IRA? With IRA, the allocation is global and happens after sched1 (pre-RA sched). Then the final scheduling (sched2) sees hard registers. In the target, with the pin, c1 is hard $3 from the start.

So in the unpinned version, IRA/global-alloc would assign c1 to some reg. The question remains how to steer IRA to put c1 in $3.

With IRA, priorities are computed globally: a pseudo with more uses and longer live range gets a higher priority. Hmm, IRA's live range priority: `ira_compute_live_ranges` and the "cost"/priority of an interval = sum over its references of a weight, plus the number of hard regs used.

In IRA, allocation order is by priority (interval priority), and the cost of assigning to a reg.

The key mechanism in the target: the constants 0xA0/-0x78/0x78 and the byte pseudos all in $2, c1 in $3, byte-12 in $6. With IRA this is a global assignment.

If I use the catalog move "u16/s16 widths" to change the pseudo's live range, IRA's priority for c1 changes.

Let me now consider: is there a simpler formulation? What if c1's value is used in a way that gives it MORE refs, e.g. computed from something? No, c1 must be exactly -160 (li -160).

Alternative: what if the -160 constant is not a variable but written directly as a literal in the two stores: `*(s16*)(p+0x14) = -0xA0; *(s16*)(p+0x24) = -0xA0;` — then the two uses are separate pseudos (each 1 set, 1 use) and there'd be two `li` instructions, unless CSE merges them. The target has ONE `li v1,-160` used twice → the target has a single pseudo with 2 uses. So we need a variable (like c1) — or CSE merging the two li's into one (CSE can merge constants! `li $2,-160` twice → CSE would reuse). But cse would then produce two uses of one pseudo — which is what we want, and cse's behavior is what the "launder" moves fight with.

Hmm! But careful: if I write the literal twice, cse may merge them into one pseudo (yes, cse handles constants: two identical `li` with same reg → the second becomes a copy or the value is reused). Then that pseudo has 2 uses and 1 set — like c1. Then the allocation question is the same. But the source-level difference (no variable) might change the RTL enough to allocate differently.

That's a promising, simple lever: replace the c1 variable with the literal -0xA0 written twice, letting cse merge.

Wait, but with a literal in C, GCC's RTL: `li $2,-160` for each store; cse2/cse would merge them into one `li` and the second use becomes a reg-reg copy or a shared reg. Actually cse's `cse.c` handles "equivalent" insns: the second `li $2,-160` would be replaced by a reg copy (or the value's reg reused). Since the first li's reg may be dead by then, cse might just reuse the same reg. This may produce exactly `li v1,-160` + 2 uses, with the pseudo's live range spanning the two stores.

Hmm, but which register? The merged pseudo would be allocated by IRA like c1. Same problem.

OK, let me stop theorizing and start experimenting. The previous attempt tried many variants (all 11+). Let me look at what all those variants were, to avoid repeating. Let me diff each candidate against orig quickly, in bulk, using a python script that prints a compact summary of the changes.

Actually the diffs are informative. Let me dump diffs for k*, m*, r*, u* (I saw m01-m03, u01-u03, w01). Let me view the rest compactly.

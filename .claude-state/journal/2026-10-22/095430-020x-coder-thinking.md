---
ts: 2026-10-22T15:54:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6FSttA0v7bfC2GnfkpO1
---
The dump files are big (multi-thousand lines, includes all the includers? no, one TU with many functions). Let me grep the sched dump for the actual function's address computation. Actually better: find the `addiu` that computes sp+16 in the .s output and see its register. The final .s file: grep the function body in cst.s.

But really, I want to know where the &m pseudo comes from. Let me look at the .s for func_8012B4B8 and compare with the target.

Actually, we know the candidate's insns from the diff. What I need is which pass turned `(plus sp 16)` into a pseudo. Let me grep the .sched (pre-sched1?) / .lreg dumps around the function. The function is likely near the top. Let me grep for "sp" + "16" and the pseudo creation.

Better approach: use grep for `(reg:SI 30)` etc. Hmm.

Alternative pragmatic approach: try to *avoid* the copy-dest address being cse-visible by making the copy destination a separate local and then... no.

New idea: make the *calls* use a pointer expression that is not the same as the copy's dest, yet the same address, in a way cse can't merge. For example, pass `(void *)(m + 0)` — merged. Pass `(void *)((int)m + 0)` — merged. Pass `(void *)((char *)m + 0)` — merged.

What if we pass `(void *)(m + (obj & 0))`? Not semantically identical shape and adds instructions.

Hmm. Alternatively, make the copy dest *not* m but a pointer whose value is loaded... 

Wait wait. Let me reconsider: maybe the target's C doesn't have a block move at all, and instead the 8 loads are from a *register* source obtained without the launder via a real second set. Look at the moves: "launder->pv=*p; pv&=mask split; real 2nd set" etc. For a constant address, "self-reassign stales cse (plus p K) equiv". E.g.:

```
src = (int *)&D_800AE620;
src = src;    // dead? eliminated
```
No.

Hmm, but here's a thought: the target's copy source base is a1 and the *three calls* use a1 for `addiu a1,sp,16`. So a1 is reused. In the with-launder version, the pin is $5 = a1 and score 0. So the launder+pin version emits exactly the target. The lever-free requirement is only that no launder/asm remains. We can keep the pin $5? The pin is a separate kind (`pin`), not the row kind. But the pin alone (without launder) doesn't keep the address (cse folds). Right, w1 had the pin and still folded.

So we need a real C 2nd set or a construct that makes cse's equivalence for the constant address stale. Known move: "p = *abase; p += 0x2D (self-reassign stales cse (plus p K) equiv)". That's about `p` being reassigned.

Here the address is a symbol_ref constant. cse's `find_best_addr` folds a constant address into the MEM. The only way to stop that is to make the base not a constant expression at the point of the loads. E.g., compute the base from a volatile read? No volatile allowed? Volatile is real C but would change codegen.

What about: `src = (int *)&D_800AE620;` then `src = (int *)((int)src & ~0);`? That's an identity launder (forbidden: "identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack").

What about a real computation: the address D_800AE620 — can we derive it from something? No.

OK so the struct copy path is the real-C way. We need to fix the &m hoist.

Let me examine what creates it. Let me grep the .s file for the function and look at the full sequence, then grep .sched/.lreg for the insn that sets the &m pseudo.

Actually, here's a cleaner hypothesis: the block move (expand_block_move) uses `copy_addr_to_reg` for the *destination* when the destination is a MEM and the source is a MEM? In GCC 2.7.2 mips.md's `move_block_from_reg`/`expand_block_move`... The MIPS expand_block_move uses:
```
if (GET_CODE (orig_dest) == MEM ...) 
```
It computes `dest_reg = copy_addr_to_reg (XEXP (dest, 0))` when ... hmm. For a small constant length it calls `move_by_pieces` which uses `(mem (plus (reg) (const)))` recursively.

But the diff shows the stores in the copy use sp offsets (identical to target), so the dest base was NOT materialized in the copy. Then `addiu s1,sp,16` is a separate insn, hoisted before the copy by sched1? Its position [9] is before the copy loads [10..]. Hmm, sched1 doesn't create instructions; it reorders. So the addiu existed in the CSE output. And in the target, that addiu doesn't exist; instead each call has its own addiu a1,sp,16.

So cse created the &m equivalence because the address sp+16 appears in the copy's dest MEM and in the calls. In w1, the copy dests are sp+16, sp+20, ... (8 distinct addresses) so no single sp+16 address used 3+ times → cse didn't create the reg.

Wait, but even in w1, the address sp+16 appears in the calls 3 times. cse's find_best_addr decides based on cost: `(plus sp 16)` is "cheap" if the offset fits, so it should rematerialize. But maybe cse creates a reg when the same address appears in a MEM that is *stored to* (dest) and then loaded... Hmm.

Let's test the hypothesis differently: make the copy destination a *different* stack slot than the calls' argument. E.g.:
```
int tmp[8];
*(Mat32 *)tmp = D_800AE620;
m[0]=tmp[0]; ... // no, extra copies
```
No.

What if the copy is done *after* the three calls? Semantically wrong (matrix must be initialized).

What if the copy destination address is `m` but the calls pass `m` via a *variable* that is set to m *after* the copy:
```
int *mp;
*(Mat32 *)m = D_800AE620;
mp = m;
RotMatrixX(..., (void *)mp); ...
```
Then the copy's dest address (sp+16) and mp's value (sp+16) — cse would still equate them (both constant). But the *first* use of the address sp+16 in a pointer context is the copy dest; cse might still create the reg. Let's just test.

Alternatively, force the calls to not see the same address by giving the copy a *union member* name and the calls another member — tried (d5), same.

Let me try the two-stage approach: copy into m via a *pointer to a different type* so the dest MEM address is sp+16 but the calls use `(void*)m` — same.

Hmm, let me look at the actual RTL: find the REG_EQUAL/REG_EQUIV for sp+16 in the cse2 dump near the function. Let me grep for `(plus:SI (reg:SI 29` with `(const_int 16)` in cse2 and see the surrounding insn with a REG_EQUAL. The function is probably a specific region. Let me find the function's insn range in the .s: use the .s file to see the function start. Actually, let's grep the .lreg dump for a note "REG_EQUIV" with 16 and a pseudo.

Let me do a targeted grep: in .cse2, lines with `(const_int 16)` near `reg:SI 29`. That gives many. Instead, let me look at the .sched dump (after sched1) or the .s file.

Actually the simplest decisive check: does the target's compiler also see sp+16 in the copy? We can't dump the target. But we know the target's C must have had *something*. The target code has: `addiu a1,sp,16` before each call, and the copy's stores at 16(sp), 20(sp), ... So in target's RTL, the address sp+16 was never in a pseudo.

Consider: maybe the target's C uses *two different arrays*: e.g. `short sVar1`... no.

Or maybe the target's C is:
```
RotMatrixX(..., m);   // m passed as array -> decays to address
```
and the copy dest uses `m` — same.

Alternatively, the target's C copy might be written as element stores from a *struct pointer* variable that is *reassigned* between calls? Hmm.

Let me step back and consider the register-allocation angle: mine has self in s2 because &m occupies s1. What if I make self a hard-reg pin ($17 = s1)? That's a new lever (pin) — forbidden to add.

What if I change the *declaration order* so that local-alloc assigns s1 to self? The allocator's priority/order may change. If self gets s1 and &m gets s2, then we'd have s2 saved instead of s1 — still different from target (which has no &m reg at all). The diff would still show an extra save/restore and the addiu. Not 0.

So we must eliminate the &m pseudo.

Let me try: what if the copy is split into two `*(Mat32 *)` copies of a *smaller* type? No.

What if the copy destination is a *volatile* pointer? no.

Hmm — what if we make the copy *source* the thing that's on the stack and the dest the global? No, we need to load from the global.

What if we use a struct assignment from the global to a *local struct that is m* but pass `&m` by *different expressions* with different offsets that cse treats separately: e.g. call 1 with `(void*)m`, call 2 with `(void*)(m+0)`, call 3 with `(void*)((int*)m)`. All same RTL.

OK, RTL inspection is warranted. Let me find in the .cse2 dump the function's part. First find the function start in the .s file to know which insns. Actually .cse2 has insn numbers; the function body is a contiguous range. Let me grep for `D_800AE620` in cse2 (line 15468) and print ±60 lines. That's where the copy is. Then look for the &m address creation.

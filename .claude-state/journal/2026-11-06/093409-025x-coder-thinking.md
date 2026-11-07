---
ts: 2026-11-06T16:34:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tQipFYZI8BCIwRffodoU
---
The RTL: 
- insn 53: `(set (reg/v:SI 74) (reg:SI 2 v0))` — the copy from v0 to reg 74 (ret).
- insn 61: `(set (reg/v:SI 75) (and:SI (reg/v:SI 74) 32768))` — m.

In local-alloc, reg 74 has copy preference to v0 (the move), and reg 75 (m) is defined at 61, after 74 dies (insn 61 has REG_DEAD 74). The tie loop: at insn 61, operand 0 is reg 75 (output), and reg 74 dies → tie 75 to 74's reg. But 74 gets v0 first via the copy pref, so 75 ties to v0. And 74's own tie at insn 53: 74's source is v0 (hard reg) dying; tying a pseudo to a hard reg at a move? The tie loop considers "operand 0 with some operand that dies" — for insn 53, operand 0 = reg 74, operand 1 = reg v0 (hard, dies). Can it tie a pseudo to a hard reg? Let me read the tie code.

The target: 74 (ret) in $3, 75 (m) in $2. So the natural path needs 74 to NOT get v0.

What if we split the copy: `ret = t;` where t is a separate pseudo (reg 76?) and t is used later... 

Alternatively: introduce a second pseudo between the call and ret so the copy-pref is on that pseudo. E.g.:

```c
t = func(...);
ret = t;
```
RTL: (set t v0) then (set ret t). If t dies at the second, local-alloc ties ret to t, t to v0 → all v0. Still one move deleted.

What if t doesn't die: use t in the andi? `m = t & 0x8000` and test ret. Then:
- (set t v0), t used at the andi and... ret = t copy with t live after? t's last use is the andi, which is after the copy. So t is live across the copy → the copy can't be tied (t doesn't die at it) → ret gets another reg (v1!) and t keeps v0. Then the andi: m = t & 0x8000 → output v0 (t dies there) → andi v0,v0,0x8000. But target reads v1. Damn, the andi would read t.

Unless the andi uses ret AND t is live later for another use. Where? 

Hmm, what if the C is:
```c
t = func(...);
ret = t;
if (ret == 0) {
} else if ((m = ret & 0x8000) != 0) {...} else {...}
```
and t is used in the else arm as a call argument? No, else calls func_80146E90((s32*)a0, 0x20).

What if t is used in the tail? func_80163408(a0, 0x2C, 0x80, 0x200) — no.

Hmm.

What if the order is: the andi comes from `ret` but there is ALSO an earlier use of t that keeps it live across the copy... impossible, t is defined at the call.

OK here's another thought: what if we make `m`'s definition use a *different* value that is live in v0, so that m gets v0 by copy preference? E.g., introduce a copy `m = t` (t = call result, v0) somewhere after the test? But the andi must produce m...

Wait, the target has m computed by andi from v1. So m's input is v1, output v0. If m had a copy preference to v0 from another copy, that wouldn't change the andi.

Let me think about `qty_sugg_compare`: qty 74 has a copy pref to v0. If some other qty ALSO has a copy pref to v0 with higher priority, it gets v0 and 74 gets the next reg. Which other qty could have a copy pref to v0? The `m` pseudo if we make `m = <v0 value>`. But the andi's output is a new definition of m; a copy pref applies per-qty, not per-def. If m has a copy from v0 somewhere, then m prefers v0.

How about this C:
```c
s32 t, ret, m;
t = func(...);      // t = v0 (copy from v0)
m = t;              // m copy pref v0
ret = t;            // ret copy pref v0
if (ret == 0) {} else if ((m = ret & 0x8000) != 0) ...
```
Now t, m, ret all have copy prefs to v0. qty_sugg_compare ranks by number of suggestions (all 1 copy sugg?) then priority. The allocation order: which gets v0? The one with highest pri (refs*size/life). t has refs: def + used at m=t + ret=t = 3 refs, life longer. m has 2 refs. ret has 2 refs. So t wins v0. Then ret and m get other regs. Hmm, ret would get v1, m v2 maybe. Then the andi output would be v2 not v0.

But wait: m is redefined at the andi. In local-alloc, per block, qty m's live range spans from `m = t` to the test? If m = t is in the same block... The copy `m = t` could be tied/deleted.

Hmm.

Let me look at the target's actual behavior more: m is v0 and ret is v1, with m defined by andi from ret. So m's qty must have a preference for v0 that beats ret's. And ret must prefer v0 too but lose.

Actually — maybe simpler: ret's copy preference is what gets it v1? No, preference only suggests v0.

Let's look at the tie loop to see if tying can assign m to v0 *because* ret is v0 and m dies... no, m is the output.

Actually, in the natural build, how did m get v0? Let me check the lreg dump's register allocation lines near block 2. The lreg dump prints "Register 74 in 2." etc. Then after allocation, the .sched or .greg dump shows reg names. Let me check base.i.greg for the block.

Actually, the natural build result we know: beqz v0 (ret=v0), andi v0,v0 (m=v0). So both in v0.

For target: ret=v1, m=v0. m=v0 likely by tying with ret? No, ret=v1. m=v0 because... the andi's output could be tied to the input? No, andi is not a move.

So in the target, m got v0 as a free register (local-alloc picks the first free reg). Wait, why would local-alloc pick v0 for m instead of v1? Let me look at find_free_reg: it has a preference order — it tries `regs_live` etc. Hmm, actually in local-alloc, when no preference, it calls `find_free_reg` which tries registers in a specific order: `reg_alloc` — it prefers registers not used in this block? Let me read the code around find_free_reg to see the order. Actually the order is: first try registers that are call-clobbered? Or it uses `alloc_reg` order 0..FIRST_PSEUDO. For MIPS, $2 would come before $3.

But if ret got v1 by preference... no, ret's preference is v0.

Hmm wait. Maybe in the target the allocation order is: m allocated FIRST (higher priority than ret), gets v0 (first free); then ret allocated, its copy pref v0 is taken → gets v1 (next free). That matches! So m has higher priority than ret in the target.

m: refs 2 (def at andi, use at bnez), life ~4 insns.
ret: refs 2 (def at call copy, use at branch and andi) — wait ret is used at the branch (56) and the andi (61): 2 uses + 1 def = 3 refs.

Priority = floor_log2(refs)*refs*size/(death-birth)*10000. ret: refs 3, m: refs 2. ret > m. So ret wins. In the natural build ret won and got v0.

For m to win, m needs more refs or shorter life. What if m is used more? In the target, m is used only at the bnez. Hmm.

Unless ret has fewer refs: e.g., ret is used once (the branch) and the andi uses a different value. But the andi reads v1.

Hold on! Maybe the target's andi input v1 is NOT ret but a *different* variable that got v1. What if the C is:

```c
s32 t = func(...);
if (t == 0) {}
else if ((m = t & 0x8000) != 0) ...
```
Then t = call result (v0), used at branch and andi. Natural: t stays v0, andi v0,v0. Same as mine.

What if `t` is copied to `ret` and the andi uses `ret`, but `ret` is NOT the branch operand? Then branch on t (v0), andi v0,v1? No, the branch tests v1.

Hmm.

OK, let me try the "priority" angle: make ret have fewer refs than m. If the test is `if (m == 0)`... no, target tests ret.

What if ret's def and uses are arranged so local-alloc's qty has fewer refs? qty_n_refs counts REG_DEAD notes? 

Alternatively, make m's live range shorter: m defined at 61 and dies at 65 → life 4. ret defined at 53, dies at 61 → life 8. ret has 3 refs, m 2. ret pri = floor_log2(3)*3*4/8 = 1*3*4/8 = 1.5 → 15000. m pri = floor_log2(2)*2*4/4 = 1*2*1 = 2 → 20000. WAIT: m = 20000 > ret = 15000! So m has HIGHER priority in the natural build too!

Hmm, but the natural build put ret in v0 first? Let me recheck. If m has higher priority, m gets allocated first. m has no copy pref. find_free_reg gives it... the first free reg. In block 2, live at start: 29 30 72. Free: v0, v1, a0-a3, t0-t9... The first free in alloc order — let me check find_free_reg's order. If it picks v0 for m, then ret's copy pref v0 is taken → ret gets v1, producing the TARGET! But our natural build gave ret=v0 and m=v0 (tied). So m must have been allocated differently — probably via the tie with the dying ret: the tie loop runs BEFORE allocation? Let's check the order in block_alloc: the scan loop ties registers first (REG_DEAD), then qty ordering and allocation. Yes! The tie loop assigns `qty_phys_reg` for tied quantities. At insn 61, reg 75 (m) is output and reg 74 (ret) dies → tie 75 with 74. Then in allocation, they're the same qty? "We can tie operand 0 with some operand that dies in this insn." So 75 is tied to 74's register. Then whichever reg 74 gets, 75 shares.

So the tie at the andi forces m into ret's reg. In the target they're different regs (v1 and v0) — so the target did NOT tie. Why not? Tying happens for insns where "operand 0 is an output that is a register not earlyclobber" and there's an operand that dies. For the andi (andsi3), operand 0 = output, operand 1 = input ret. Tying is allowed only if the insn is "suitable": the comment says suitable insns have at least two operands and operand 0 is an output not earlyclobber, and we can tie with an operand that dies. But there's a condition: the tied operands must have the same mode? andsi3 is SI both. Hmm.

Let me read the tie loop conditions in local-alloc.c.

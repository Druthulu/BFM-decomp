---
ts: 2026-11-06T12:10:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JHVhuZdJT8NfD9wGoKK5
---
Same residual: li a0 at 31 (mine) vs 30 (target). The li a0 needs to move one slot earlier.

Let me see what's at mine[30]. Let me disassemble v_both_argfirst. Actually, from the both_dw disassembly, mine[30] = lui v0,0x20 (unk14 value). So the li a0 is after the lui.

To move li a0 before lui v0,0x20... 

What if the unk14 value computation (lui v0,0x20) is scheduled later because it depends on something? 

Idea: make unk14's value a variable computed from the call's result? No.

Idea: what if I reorder the source so `unk14 = 0x200000` comes AFTER the 0x18 store, but ALSO the sched puts li a0 first? v_both_perm1 (0x18 then unk14) = 2. Same residual? Let me check.

Hmm, all variants give the same li a0 at 31. 

Let me think about sched2's priority. The li a0 (for the jal at 37) vs lui v0,0x20 (for sw at 32). The lui is needed sooner. sched2 prioritizes by the longest path. 

Actually, maybe the target's order is because the barrier (an insn) is between the store and the tail, and sched2's region includes the barrier. The barrier is an insn with no dependencies; sched2 might schedule the tail differently around it.

Hmm. Without the barrier (do-while), the region structure differs.

Let me try: put the do-while around the store, and also a `do{}while(0)` (empty) right after, before the tail. That might mimic the barrier's position. Let me try:
```
do { CAST_WIDTH(0x10) = v; } while (0);
do { } while (0);
unk14 = ...
```
The empty do-while creates a loop note/label after the store, like the barrier. Let me test.

Also: `do { } while (0);` between the store and the tail.

Let me test v_both_emptydw.

Also, let me try: the empty do-while AFTER the tail? No.

Let me test.

Actually, the do-while around the store already creates a boundary. Adding another might not help.

Let me try a different idea: make the li a0 the FIRST thing in the tail by computing it in a separate statement right after the store. E.g.:
```
do { CAST_WIDTH(0x10) = v; } while (0);
aa = 0x980;   // li a0? no, aa is a temp
```
Hmm.

What if I make the call's first arg a variable `aa` set right after the store, before the tail stores? Then the li for aa might be scheduled first. v_both_argfirst set aa=0x980 before the tail (before unk14). It gave 2 (same). Let me check its mine[30].

Actually, v_both_argfirst also has li a0 at 31. So even with aa set before unk14, the li is scheduled after lui v0,0x20.

Hmm. The sched2 prioritizes the lui.

Let me try making the unk14 value NOT a simple constant: `unk14 = 0x200000` → `unk14 = 0x100000 * 2`? folds. Or `unk14 = 0x200000 + 0`? folds.

What if unk14's value is read from the struct and OR'd? No, changes semantics.

Hmm. Let me try: `((Unkstruct_800B5CB8*)a0)->unk14 = 0x200000;` with unk14 being s32. What if I use a different width store? The target is `sw` (s32). 

Let me try the empty do-while and a few more, then accept the wall.

Time: 05:09:50. Let me test.

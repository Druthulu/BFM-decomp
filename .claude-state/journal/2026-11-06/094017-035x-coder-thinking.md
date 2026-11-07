---
ts: 2026-11-06T16:40:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_39Mgi0zWqKV17JX3kT6T
---
w2_hoist: ret=v0, m=v1. andi v1,v0. So ret got $2 (copy suggestion) and m got $3. Order: andi before branch, as expected.

To flip, m must get $2. Give m a copy suggestion to $2 too, with higher priority? Hmm, or make ret's copy suggestion weaker.

Actually, here's a thought: qty_sugg_compare sorts copy-suggested qtys FIRST. ret has a copy suggestion ($2), m has none → ret first. If m also had a copy suggestion (to any reg), both are in the "copy sugg" group; then priority decides; m's priority could exceed ret's if m has more refs.

How to give m a copy suggestion? A copy `m = <something>`. E.g., `m = ret; m = m & 0x8000;`? That's two statements: `m = ret; m &= 0x8000;` — the second is a real redefinition. Hmm: 
```c
m = ret;
m &= 0x8000;
if (ret == 0) {} else if (m != 0) ...
```
RTL: (set m ret) — copy suggestion from ret's reg (unknown at that point, but it's a pseudo-pseudo tie: m could tie to ret!). At insn (set m ret) with ret dying? ret is used later (branch) so ret doesn't die → no tie → m gets a copy suggestion to ret's eventual reg. But ret's reg is a qty not yet allocated; qty_phys_copy_sugg records the *register number* only for hard regs. For pseudo-pseudo, combine_regs TIES them if the source dies; if not, it returns 0 with no suggestion (the "pseudo-pseudo" path only ties). So no suggestion.

Hmm.

What about `m = func(...)` copy from the call result? The call result is hard v0 → m gets a copy suggestion to $2! But then m would be the call result and the test/branch would be on... Let's think:

```c
s32 m;
m = func(...);     // m has copy sugg $2
ret = m;           // copy from m; if m dies here, ret ties to m ($2)
if (ret == 0) ...
```
If m is live after (used at the andi), ret doesn't tie. But then the andi would use m, not ret.

What if:
```c
s32 t, m, ret;
t = func(...);   // t copy sugg $2
ret = t;         // ret copy sugg? pseudo-pseudo: t is live (used at andi) -> no tie, no sugg
m = t;           // m copy from t (pseudo) -> no tie, no sugg
if (ret == 0) {} else if ((m = ret & 0x8000) != 0)
```
Hmm.

What if m is assigned the call result directly and ret is a *HImode* copy for the branch? We need the branch on $3.

Let me think about qty_sugg_compare more: it ranks by sugg1 vs sugg2 where sugg = num_copy_sugg ? num_copy_sugg : num_sugg * FIRST_PSEUDO_REGISTER. So a qty with 1 copy suggestion beats any qty with normal suggestions. And among copy-suggested, fewer suggestions first, then priority.

If ret has 1 copy sugg ($2) and m has 1 copy sugg ($2) too, they tie on sugg; then priority decides. ret: refs 3 (def, branch, andi), life ~8. m: refs 2, life 4. ret pri higher → ret gets $2 first. Unless m's live range is shorter. Hmm, ret pri = floor_log2(3)*3*4/8*10000 = 1*3*4/8=1.5→15000. m = floor_log2(2)*2*4/4 = 1*2*1=2→20000. m > ret! So if both have copy suggestions, m would be allocated FIRST and get $2!

So: give m a copy suggestion to $2, and keep the andi before the branch (hoist), with ret and m overlapping. Then m gets $2, ret gets $3 → move $3,$2, andi $2,$3? Wait, if m is allocated $2 and ret $3, the andi `m = ret & 0x8000` → `andi $2,$3,0x8000`, and the branch tests ret $3. And the ORDER: if the andi is before the branch, the target wants it after (delay slot). But sched1 might reorder... Actually target has beqz before andi. If the RTL has andi then branch, sched1 could reorder to branch then andi? The branch depends on ret; the andi writes m (no dependency with the branch). sched1 might move the branch earlier. Let's test.

How to give m a copy suggestion to $2? `m = func(...)` makes m the call result. But we need ret too. Hmm.

What if: `m = func(...); ret = m;` where m is live at the andi... no, m is redefined.

Alternative: m = the call result, ret = m copy, and the andi uses ret into m? Then m's copy suggestion from the call; ret's copy suggestion from m (pseudo-pseudo, no sugg). Hmm.

Let me think again: we want BOTH ret and m to have copy suggestions to $2. The natural way: both are copies of the call result:
```c
s32 t = func(...);
s32 ret = t;   // ret copy sugg $2? pseudo-pseudo: t dies? 
s32 m = t;     // 
```
If t is live at both copies, no tie, no suggestion (pseudo-pseudo path gives no suggestion). So no.

Direct hard-reg copies: only the call result gives one.

Hmm, what about a *second call* whose result feeds m? No.

OK, alternative: give m a copy suggestion via a hard reg other than $2, but that doesn't help.

Let me reconsider: maybe make ret's copy suggestion go away, so m (no sugg) still gets... no, without ret's sugg ret would still be first by priority and take $2.

Hmm, what if ret is NOT a copy of the call result at all, but a *parameter-like* value? The call result must go somewhere.

What if the call result goes to m (copy sugg $2), and ret is computed from m by a non-copy (e.g., ret = m | 0? combine folds). Or ret = (s32)m + 0? folds.

What if ret = m (copy) and m is live across (used at the andi), so no tie; ret gets... its own reg. Which? The copy from a pseudo gives no suggestion; allocation order: m has copy sugg $2 → m first → m=$2. Then ret (priority lower) → first free $3! → `move $3,$2` for ret=m. Then branch on ret $3. Then andi: we need it to read $3 (ret) and write $2 (m). But m is $2 and m is live until the andi (it's the input of the copy at ret=m and then redefined at the andi). Wait: `m = ret & 0x8000` writes m; m's old value (the call result) is used at `ret = m`. So m's live range: call → ret=m (dies there, since m is redefined later? REG_DEAD at ret=m only if m isn't used between). Then m is born again at the andi. So m dies at ret=m; ret is born there. Tie possible! At insn (set ret m), m dies and ret is set → combine_regs ties ret to m → both $2, no move. Damn.

Unless m is used after ret=m (before redefinition): e.g., `m = func(); ret = m; if (ret==0) ... else if ((m = ret & 0x8000))` — m is used at ret=m only. If we add a use of m between, e.g., the branch tests m: `if (m == 0)` → branch on $2, not target.

Hmm, what if m is used in the andi: `m = ret & 0x8000` uses ret. If instead the andi is `m = m & 0x8000` (m from the call) and the branch tests ret... then:
```c
m = func(...);      // m = v0
ret = m;            // copy
if (ret == 0) {} else if ((m = m & 0x8000) != 0) ...
```
The andi reads m ($2) → `andi $2,$2,0x8000`. Target reads $3. No.

Ugh.

OK let me reconsider the target's semantics once more. Maybe the branch is NOT on the call result but on a *different* SImode variable that happens to equal it. What if the original C was:

```c
s32 ret = func(...);
...
if (ret == 0) { ... } 
```
and the move v1,v0 is the call result copy that survives because of a REG_UNUSED or because the variable is used in two blocks. Let me test: what if `ret` is used in the switch blocks (live across the whole if)? Then ret crosses into other blocks. Global-alloc would assign a callee-saved reg, not $3. Unless... hmm, but the target has $3.

What if ret is used in the *same block* after the andi? There is no such use in the target.

Let me try yet another angle: the **first call** structure. Target:
```
bnez v0,36c
move a0,s0     (delay)
```
The first call result is tested. Mine has `bnez v0,368` with a different target — just an offset shift.

OK. Given the difficulty, maybe the natural answer is a WALL: "sched1-birth-order" or "lreg-copy-tie". The target's move v1,v0 requires the call-result copy to survive; lever-free it always ties/allocates $2. But w1_r16 showed it CAN survive via the zero-extend pseudo — just with one extra insn.

Wait! Actually — what if we make the zero_extend insn *not needed* by having the branch test a value gcc knows is zero-extended, while still occupying $2? What if the branch tests the HImode ret via `if ((ret & 0xFFFF) == 0)`? That generates `andi $2,$3,0xffff` (78) then beqz $2 — same extra.

Hmm, what if the extra `andi 0xffff` is combined with the andi 0x8000 by combine? They're in different paths.

What if the test is `if (ret == 0)` where ret is `u16` but we write `if ((u16)ret == 0)` — same.

What if ret is `s16` and the test `if (ret == 0)`: sign-extend → sll/sra (2 insns). w1_s16 was 106.

What if ret is a *pointer-sized* union... 

New idea: make the zero_extend pseudo serve BOTH as the branch operand and the andi input, so no extra insn: `m = (u16)ret & 0x8000`? Hmm.

Actually, here's a cleaner idea: what if `ret` is `s32` and the branch tests `(u16)ret == 0` — this creates a zero-extend pseudo Q ($2) and the branch tests Q. Then the andi `m = ret & 0x8000` reads ret ($3). Target: `beqz $3` tests ret, not Q. So the branch would be `beq $2,$0`. Not target. But wait — would gcc optimize `(u16)ret == 0` to `ret == 0`? No, it can't.

Hmm, but what if the zero-extend is `andi $2,$3,0xffff` and the branch tests $2... target tests $3. No.

OK so we need the branch on the *raw* ret while a pseudo occupies $2.

What about a pseudo that occupies $2 and is NOT an extra instruction: the **call's argument setup**? No, args are a0/a1.

What about the *sp20 address* pseudo? `addiu $5,$sp,32` uses $5 (a1), not $2.

What about `sp28`? Another block.

What if we add a variable that is loaded before the call and used after (across the call)? That would be a global/callee-saved reg, not $2.

Hmm, what about a pseudo defined right after the call and used before the branch, like a comparison temp? The branch itself is a compare — gcc 2.7.2 uses branch_zero with the reg directly.

What about `if (ret == 0)` → maybe gcc creates a comparison pseudo if we write `if ((ret == 0) != 0)`? Probably folded.

What if the condition is `if ((ret & 0xFFFFFFFF) == 0)`? Folded.

What about a **bitfield extraction**: `if (ret == 0)` vs `if (ret != 0)`. Hmm.

What about `if (ret == 0u)`? same.

Let me try: `if ((s32)(ret) == 0)`. same.

What if the branch condition is a compound: `if (ret == 0 || ret == 0x12345)`? That adds instructions.

Hmm, let me look at the problem from the "original source" angle. This is a game function from 1998. The decomp's C is likely close to the original. The original compiled with the same gcc. So the original source must have produced the target. The decomp team's C (with pins) is a rewrite. The original probably had something like:

```c
s32 ret;
...
ret = func_801638A0(...);
if (ret == 0) {
} else if ((m = ret & 0x8000) != 0) {
```

and that gave the target in the original. So there IS a natural shape. But our reproduction gives ret=$2. Unless the original had a different variable structure, e.g., `ret` used later.

Hmm wait, maybe the original source had the empty `if (ret == 0) {}` as something else, like a switch or a `goto`. Let me look at the target control flow again:

```
350: beqz v1, 384     ; ret == 0 -> 384 (tail)
354: andi v0,v1,0x8000
358: bnez v0, 37c     ; m != 0 -> stores
35c: nop
360: move a0,s0
364: jal func_80146E90
368: li a1,32
36c: jal func_80146CA0
370: move a0,s0
374: j 494 (epilogue)
378: nop
37c: sw zero,44(s0)
380: sw zero,36(s0)
384: ...
```

Note: the else arm at 360 does func_80146E90 then falls into 36c (func_80146CA0) then jumps to the epilogue. And 37c is the m-arm, falling to 384. And the ret==0 path goes directly to 384.

Hmm, interesting: the `bnez v0,37c` jumps forward to the m-arm, then falls to 384. So the m-arm is laid out after the else arm. That's the natural layout for if/else-if/else with the else being a return.

So the C shape is as we have.

Let me look at the *sched1* dump of the target? We don't have the target's dump (ROM). 

OK here's another thought: what if `ret` is used by the andi and the branch, and the branch is `if (ret == 0)` BUT the source declares `ret` as `s32` and ALSO assigns it from the call in a way that gives a second REG_DEAD... 

Let me look at what `qty_phys_copy_sugg` does when the copy source is a hard reg and the destination pseudo is later given another suggestion. In win0, 74's copy sugg = $2; allocation gives 74 = $2 and the move is deleted. In the target, 74 must get $3.

What if we add a *second* copy suggestion to 74 (e.g., another move from $3)? Not possible in plain C.

What if the call's return value pseudo is tied to a *different* hard reg via the call pattern? No.

Hmm, what about using a **different call** whose return register is $3? No, MIPS returns in $2.

What if the value is a **float/double**? The function returns s32.

What if the call is cast to return a `s16` (call-site cast)? `((s16 (*)(u8*, s32))func_801638A0)(...)` — the return type s16! Then the call result in $2 is truncated... The call_value pattern would produce a HImode value? A function returning s16 in gcc 2.7.2: the return value is in $2 with the caller treating it as HImode. Then `ret = (s32)(s16)call(...)` → sign extension (sll/sra). Extra insns.

What about a call-site cast to `u16`? zero-extend → andi 0xffff. Extra.

Hmm, what about a call-site cast to a *pointer*? no.

OK, let me look at the moves file for the exact wall tags about copy suggestions: "global-copy-pref", "lreg-tie-dying-pin", "lreg-copy-pref-dying-base". There's a wall tag "lreg-copy-pref-dying-base" (G24). Maybe our case is a new wall: local-alloc's copy suggestion gives the call result $2 and the andi ties m to it.

But wait — the andi tie isn't the issue; the issue is ret getting $2. If ret got $3, the andi output m would take $2 (first free) → target! So the crux is ret's copy suggestion.

Actually! Here's an idea: what if the andi is in a DIFFERENT basic block than the copy? Then the tie/allocation is per-block; ret's copy suggestion is in block A; in block B, ret is live at start (allocated globally, not locally). Hmm, ret would be global. Global-alloc would give it a reg... $3 maybe? Let's think: if the code is:

```c
ret = func(...);
if (ret == 0) {
    ...
} else {
    if ((m = ret & 0x8000) != 0) {...} else {...}
}
```
Then ret is live across blocks 2→3/4, so it's global. The copy suggestion from the call in block 2: global-alloc uses copy preferences too (global.c has copy pref). global.c would give ret $2 (call result copy pref)... Actually global-alloc's copy preference might also tie to $2. Hmm.

But the target's ret is $3 — global-alloc assigns caller-saved $2/$3 based on priorities. Let's test the nested-if shape. In the target, the branch on ret and the andi are in the SAME block (delay slot), so ret is local there... but the copy could be in the same block anyway.

Hmm, the target: beqz v1 and andi are in block 2 (same as the copy). So ret is block-local.

Let me try the nested if shape anyway (it changes block structure):
```c
ret = func(...);
if (ret != 0) {
    if ((m = ret & 0x8000) != 0) {...} else {...}
}
```
This is semantically the same but with an explicit nesting. The empty if(ret==0){} might be compiled differently. Actually the current C `if (ret==0) {} else if (...) {} else {...}` should compile the same.

Hmm OK. Let me look at the original source style of this game: many functions use `if (ret != 0) { ... }`. 

Let me try a batch of structural variants:
- nested if
- switch on ret? no
- `if (ret) { ... }` 
- early return: `if (ret == 0) goto tail;` with a label.

Actually, `goto` might change the CFG and allocation. Let me try:

```c
ret = func(...);
if (ret == 0) goto L;
if ((m = ret & 0x8000) != 0) { stores } else { calls; return; }
L:
func_80163408...
```
Same CFG.

Hmm.

Let me try to see if maybe the pins are actually removable with a totally different approach: the `m` variable could be a `u16` and the branch on ret SImode... 

Wait wait wait. Let me re-read w1_r16's output: 
```
move $3,$2
andi $2,$3,0xffff
beq $2,$0,$L22
andi $2,$3,0x8000
```
The target:
```
move $3,$2
beq $3,$0,$L22
andi $2,$3,0x8000
```
What if we could get the `andi $2,$3,0xffff` DELETED by flow/cse? It's needed for the branch. But what if the branch used $3 and the andi $2... 

What if the C is: `if (ret == 0)` where ret is u16, and the comparison is written as `if ((u16)ret == 0)`... same.

Hmm, what if the comparison is on a *different* HImode variable that holds the same value? Like:

```c
u16 ret;
s32 t;
t = func(...);
ret = (u16)t;    // HImode copy -> move $3,$2? 
if (ret == 0) ...
```
The zero-extend still appears.

What if `ret` is u16 and we compare `if (ret != 0x8000 && ret == 0)`? no.

What if the test is `if (ret < 1)`? HImode unsigned < 1 → still needs extension? gcc might use `beqz` if it knows... For `(unsigned)ret < 1`, that's `ret == 0`; same extension.

Hmm, what about `if (ret == 0)` where ret is a HImode value that came from a **zero-extending load**? gcc knows loads zero-extend? Actually MIPS lbu/lhu zero-extend. If ret came from `*(u16*)p`, gcc knows the upper bits are zero (from the load pattern). Then the comparison uses beqz directly! But our value comes from a call, not a load.

Unless... we store the call result to a stack slot and reload it as u16! That would be a store+load (extra insns). No.

OK, I think this item may be a wall. But let me try a couple more things: the `s32` ret with an artificial second use that keeps it live but costs nothing... 

What about making `m` the call result and `ret` a HImode copy used for the branch? 
```c
s32 m;
u16 ret;
m = func(...);      // m = $2 (copy sugg)
ret = (u16)m;       // HImode copy: move $3,$2? m is live at the andi -> copy survives; ret gets $3
if (ret == 0) ...   // zero-extend of ret -> andi $?,... extra
```
Extra insn again.

What if ret is SImode and m is the call result, and the andi uses m:
```c
s32 m, ret;
m = func(...);     // m=$2
ret = m;           // copy; m live at andi? the andi uses ret, so m dies at the copy -> tie
```
No.

What if the andi uses m and the branch uses ret, and m is live across the copy? 
```c
m = func(...);
ret = m;            // copy
if (ret == 0) {} else if ((m = m & 0x8000) != 0) ...
```
m is used at the andi (m = m & 0x8000), so m is live across the copy → ret gets its own reg. Allocation: m has copy sugg $2 → m=$2; ret no sugg, lower priority → $3. → `move $3,$2`. Branch on ret $3 → beqz $3. Andi `m = m & 0x8000` reads m $2 → `andi $2,$2,0x8000`. Target reads $3. Damn, off by the andi's input.

Unless the andi's input is ret: `m = ret & 0x8000` and m is ALSO live across the copy for another reason. What other reason? If m is used between the copy and the andi... 

Hmm, what if the branch tests m and the andi uses ret? Target tests $3=ret.

I keep hitting the same wall: the andi's input must be the same value as the branch's operand (both $3), and that value must be a copy from $2 with $2 occupied.

So: P (ret) = copy of the call result, P live across the branch and the andi, P dies at the andi. Q occupies $2 across P's range. Q must be live from before P's birth (the copy) to at least the andi, and Q must not be P.

What natural value is live from the copy to the andi and lives in $2? In r16 it was the zero-extend result (78) — but 78 is defined AFTER P (57 after 53) and dies at the branch (59), so it occupies $2 during P's range [53,65]. Yes.

So we need a pseudo Q defined after the copy, before/at the branch, living until at least the branch, that gets $2.

If Q is a *zero-extension of P used by the branch*, we get the extra insn. But what if Q is something that's needed anyway?

What about the branch's comparison pseudo in a different shape: e.g., `if (ret >= 1)` might create `slt` — extra.

What about the *and's output* as Q if the andi were moved before the branch by sched1? We tried the source-hoisted version: ret=$2, m=$3 (ret won). Because ret had the copy suggestion and m didn't. To flip, m needs a copy suggestion or higher priority.

m's priority (refs 2, life 4) = 20000; ret's (refs 3, life 8) = 15000. So m > ret! If both had equal suggestion status, m would be allocated first and take $2. The problem is ret's copy suggestion puts it in a higher sugg class.

So: can we *remove* ret's copy suggestion while keeping the move? If ret's copy from the call isn't a direct hard-reg move... e.g., if the call result first goes to a temp t (copy sugg $2 on t), then ret = t (pseudo-pseudo: if t dies, tie; if t lives, no sugg but also no move?).

Hmm, let's think: 
```c
s32 t, m, ret;
t = func(...);     // t: copy sugg $2
ret = t;           // pseudo-pseudo copy: if t dies here -> ret ties to t; else no suggestion, no tie
m = ret & 0x8000;
if (ret == 0) {} else if (m != 0) ...
```
For ret to not tie at `ret = t`, t must be live after. But t isn't used after. Unless t is used in the andi — then the andi reads t.

Alternatively, t is live because it's used at `m = t & 0x8000` (the andi reads t $2, not target).

Hmm.

What if the order is: `m = t & 0x8000; ret = t;` — then t dies at ret=t, tie.

OK, so what if we *split* the call result: 
```c
t = func(...);
m = t & 0x8000;    // andi from t; t dies? t still used by ret=t below
ret = t;           // copy
```
RTL order: andi, then copy. The andi's output m ($?) and t. Then ret = t. t dies at the copy → ret ties to t. Hmm.

What if `ret = t` comes first but t is live due to a *later* use in a different block? The switch blocks? Then t crosses blocks → global. Hmm.

Let me look at this from yet another angle: maybe use `m` as the *call result holder* and `ret` as a HImode-free SImode copy where the copy survives because m is used at the andi AND the branch uses ret:

```c
s32 m, ret;
m = func(...);        // m: copy sugg $2
ret = m;              // copy; m live (andi uses m)
if (ret == 0) ...     // branch on ret
else if ((m = ret & 0x8000)) ...   // andi uses ret, writes m
```
m is used at `ret = m` and at the andi (as output only). Is m live across the copy? m's last use before the redefinition is at `ret = m`. So m dies there → tie ret to m → both $2. Hmm.

What if m is used at `ret = m` AND at the andi's input? Then the andi reads m: `m = m & 0x8000` — reads $2.

I keep going in circles. Let me look at whether there's a way to make the andi's input and the branch's operand be two DIFFERENT pseudos that both get $3 (non-overlapping). For example:

```c
s32 a = func(...);     // a = $2
s32 b = a;             // b = $3 (a live later)
if (b == 0) ...        // beqz $3
else if ((m = a & 0x8000))  // andi $2,$2 -- no
```
No.

```c
s32 a = func(...);
s32 b = a;
if (b == 0) ...
else if ((m = b & 0x8000))   // andi reads b $3
```
Here b = a copy; a must be live across the copy for b to get $3. If a is NOT used later, tie. Unless a is used later somewhere with no insn... no.

OK. Let me now consider that the item is genuinely a wall and the budget says a WALL needs ≥20 min and ≥30 scored tries. I have ~25 scored tries so far (13 + 5 + a few). Let me count: batch1 = 13, batch2 = 5, plus win0 and orig = 2. Total 20. I need ≥30 scored tries before declaring a wall.

Let me do a few more creative batches (10+ candidates), then decide.

More ideas:
A. Use `volatile`? no.
B. Use a struct field for m.
C. Use `s32 ret = func(...)` (init at decl).
D. `u32 ret`.
E. `s32 ret; ... ret = func(...); if (ret < 0) {} else ...` no.
F. Try `if (ret) { if ((m=...)) ... else ... }` nested.
G. Try `switch (ret) { case 0: break; default: ... }`.
H. Try the andi with a different mask spelling: `m = ret & (1 << 15);` or `m = ret & 0x8000u` — same.
I. Try `m = ret & 32768;` same.
J. Try `m = ret >> 15 & 1;` — different (srl).
K. Try `m = ret & 0x8000; if (ret) { if (m) ... }`.

Let me also reconsider: maybe the target's ret isn't the call result copy but the result of `func_801638A0` cast... 

Actually — NEW IDEA: what if `ret` is a **u32/s32 bitfield** or the AND result? Consider:

```c
s32 ret = func(...);
if (ret == 0) {}
else if ((m = ret & 0x8000) != 0) ...
```
What if we write the condition as `else if (ret & 0x8000)` (no m variable)? Then andi output could be a temp that... same as w1_nom (8).

Let me look at the *first* function call result handling in the target for a hint:
```
330: move a0,s0
334: jal func_80146E98
338: move a0,s0
33c: bnez v0,36c
340: move a0,s0
```
The call result v0 is tested directly, no copy. Good.

What if the ret copy in the target comes from `ret = func(...)` where `ret` is **u32** and the branch `if (ret == 0)`... same.

Let me try the call-site return-type cast angle: `((s32 (*)(u8 *, s32))func_801638A0)((u8*)a0, (s32)sp20)`. That might change how the return is copied. Probably not.

Hmm, actually let me reconsider the possibility that the target source declares ret as `s32` but the call is `ret = func(...)` and the ORIGINAL had a **`register` keyword**? The original 1998 code wouldn't use `register` (Square didn't). 

Let me look at the actual function's neighbors in md_MAIN_041 for style. Maybe the original source pattern is visible in similar functions in the repo (other main functions with this shape). Let me grep for a similar shape: "if (ret == 0) {" in src/md_MAIN_041.c.

Actually, let me look at func_800CB2C8 (mentioned in moves: "stmt order raw=t before the if keeps both copies (move v1,v0 / move v0,v1); do-while(0) around raw=t splits the EBB so the lbu qty takes v1 and t v0 (G22)"). That's a cracked similar item! Let me read its body.

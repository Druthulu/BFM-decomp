---
ts: 2026-11-07T00:00:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pSwR37HnddqMIJu63k9h
---
Same priorities. So the reg order is fixed at base 1518 > mode 1204.

Now, the decisive question: can I flip it with identical code? q05 proved that dropping a base ref flips it but changes the code at that site.

Hmm, but wait — q05 dropped a ref in block 2+ (the 5th if). What if instead I drop a ref at a site where the re-spelling DOES merge? That requires cse to know base's value. Where does cse know it? Only within the same extended basic block as the set. base is set in block 0. The only uses of base in block 0... none.

Hmm, unless I move base's set INTO the block where a use is. E.g., set base later, right before the first if? That changes the code (the lui/addiu moves).

Hmm.

Alternatively, ADD a ref to mode via a spelling that gets folded but still counts? Folded = deleted before local-alloc.

Hmm, what about this: mode's refs is 5. What if one of mode's *sets* is split into two? E.g., `mode = -1;` → could the frontend emit it as two sets? No.

What if mode's live range is shortened by 18 insns through reordering the *statements after the set*? live_length counts the span from the first to the last reference. Both ends are fixed.

Hmm, hold on: what if the last reference moves earlier in the RTL? `if (mode == 0 && (res & 1))`. What if I compute `mode == 0` into a variable earlier and use it later? That changes code.

What if I move the whole `if (mode == 0 && ...)` block BEFORE `if (file >= 0 && ...)`? Changes code order.

OK. Let me now consider: maybe the live_length can be shortened by moving the FIRST reference later. What if `mode = -1;` is moved AFTER the `st = func_8002F648()` call? It already is (line 970 after 969). What if before? line 968-ish? That would extend.

Hmm, what if `mode = -1` is moved to right before the `if (func_8002F658()...)` (line 1000)? But then the intervening `if (st != ...)` block sets mode=0 — the compiler would need mode=-1 before that. Actually! Look at the C:

```
st = func_8002F648();
mode = -1;
if (st != X) {
    mode = 0;
    if (st != 0) func_8002F620();
}
cnt = func_80029504();
if (base->unkA3D8 == 0x300B && ...) { ... }
...
if (func_8002F658() != val || mode >= 0) { ... }
```

mode's first ref is `mode = -1` at line 970. Its span: from there to the last use at line 1016. live 83.

If I could make the compiler move `mode = -1` later... it can't, the if needs it.

BUT: what if I restructure the mode logic so the set is in the if/else?
```
if (st != X) {
    mode = 0;
    if (st != 0) func_8002F620();
} else {
    mode = -1;
}
```
Then mode has 2 sets in different blocks. The RTL: the then-arm sets 0, the else sets -1. sched1/reorg would put `li s3,-1` after the branch... but the target has it in the DELAY SLOT of the beq. reorg fills delay slots from the target or fall-through. If the else block is the fall-through, `li s3,-1` could be the delay slot! Hmm, actually in the current target, `beq v0,v1,1100` jumps to 1100 (the join) when st==expected. The fall-through (10ec) has `li s3,-1` then `beqz v0,...` — wait no.

Let me re-read the target:
```
10e8: beq v0,v1,1100      ; if (st == expected) goto join
10ec: li s3,-1            ; delay slot: mode = -1
10f0: beqz v0,1100        ; if (st == 0) goto join
10f4: move s3,zero        ; delay slot: mode = 0
10f8: jal func_8002F620
10fc: nop
1100: (join) jal func_80029504
```
Hmm interesting: `beq v0,v1,1100` — if st == expected, go to join (skipping mode=0). Otherwise fall through: `li s3,-1` (delay slot), `beqz v0,1100` (if st == 0, join), `move s3,zero` (delay slot), then call.

Wait, that's weird: `move s3,zero` executes in the delay slot of beqz, so mode=0 happens BEFORE the branch is resolved but after. If st==0, we jump to join with mode=0? But the C says mode=0 should be set when st != expected, and then if st != 0 call. If st==0, mode=0 and no call. Yes matches: beqz v0 → join (with mode=0 set in the delay slot).

So `li s3,-1` is in the delay slot of the FIRST beq (executed when st != expected). That's reorg moving `mode = -1` from... hmm, in the C `mode = -1` is before the if (unconditional). But the assembly only sets it on the fall-through path (st != expected). If st == expected, we jump to join WITHOUT setting mode=-1? That would be wrong!

Wait: beq v0,v1,1100; delay slot li s3,-1. The delay slot ALWAYS executes. So `li s3,-1` executes regardless. OK good.

So `mode = -1` is unconditional, in the delay slot. Consistent with the C.

Now if the C were if/else, mode=-1 would be in the else block, and reorg could still fill the delay slot with it only if the else is the fall-through path. The else (st == expected) is the BRANCH TARGET, not the fall-through. So `li s3,-1` would be at the target, not the delay slot. The target code would differ. So the if/else restructure is out.

OK. So mode's first ref is fixed at the delay slot.

Hmm hold on, actually — what if we can make the *live_length* shorter by noting that flow computes live length including or excluding... Let me just look at flow.c's computation to see if there's any freedom.

Actually, I wonder: maybe live_length is computed AFTER sched1 (dbr). The .lreg dump is after local-alloc, which is after sched1. sched1 could move the `li s3,-1`! In the RTL before sched1, `mode = -1` might be placed differently. flow computes reg_live_length BEFORE sched1 (flow runs before combine/sched). So the RTL order at flow time matters.

In the C, `mode = -1;` is a statement right before the if. So the RTL order at flow time: mode=-1 right before the branch. Span from there to the end.

Hmm, what if I move `mode = -1;` EARLIER in the C (e.g., at the top)? Then live grows. Worse.

What if I move it LATER? Can't.

OK. Let me accept the reg order as a WALL for item 1 and record it. But wait — I should double check whether the *combination* p14 + something could give 0. p14 = 14. The only residual is the swap. 

Hmm, actually — one more idea! What if I can make `mode` and `base` NOT both callee-saved-needed? E.g., if `base` doesn't cross calls... it does.

What if `base`'s priority is LOWERED by making it live longer: e.g., if base were set EARLIER and used LATER... 

Oh wait! Here's a thought: what if base's live_length increases because I move `base = D_800AF630;` to the top (before the `file =` computation)? It's already before file. Hmm, but the RTL position: the set is at 10d8, AFTER the file/val loads (sched1 sank it). At flow time (pre-sched), the set might be first. Let me check the .lreg/flow dump for where base is set.

Actually, live_length 158 for base in a 161-insn function: that means base is live from insn ~1 to ~159. So it's already essentially the whole function.

Hmm, 158/161. To get pri < 1204: 24/live < 0.1204 → live > 199. Impossible.

To get pri base < 1204 with refs 7: 14/158 = 886. So refs 7 needed.

Hmm.

OK, one more idea for dropping a base ref without changing code: what if base's *set* is not counted because base is initialized at declaration? No, `u8 *base = D_800AF630;` still has a set.

What if base is a parameter? It's not.

Hmm, what if I use `D_800AF630` directly in the FIRST if (block 0's successor)? We showed cse doesn't merge there.

Hmm, wait, actually let me reconsider: does cse know base's value in block 2? Let me test empirically: replace ONE base use with the symbol and check if the code is identical (score). q05 (5th if) gave a changed code at that site. What about the first if (q01, score 21, 162 insns — worse, extra insns). Hmm, q01 gave 162.

Hmm, q02 (2nd if): score 9, 160 insns — code changed at that site (lui v1). Same for all.

So no.

Alright. What about ADDING a ref to mode that survives but produces the SAME code? Impossible — an extra ref produces an extra insn.

Hmm, unless the extra ref replaces an existing one in a way that keeps the count... no.

OK, wait. Let me reconsider the whole thing. What if I make mode's live range shorter by making `mode`'s LAST use earlier via a *different spelling* that emits the same code but references mode earlier? E.g., the last use is `if (mode == 0 && (res & 1))`. What if I hoist `mode == 0` into a variable? That changes code.

Hmm.

Actually, hold on. Let me reconsider the live_length: 83. What if I can REDUCE it by making the first reference later — by making `mode = -1` not reference mode? Impossible.

What if `mode` is assigned via a different mechanism: e.g., `mode = ~0;`? same.

OK, I'm now fairly confident this is a genuine `global-pri-bank-order` wall for the pin. And the launder IS cracked by p14.

So the lever-free best is 14 (p14). Since the launder is gone in p14 (lever-free!) and it scores 14, the best lever-free body = 14.

Wait, but "best = lowest score of a lever-free body" — p14 is lever-free (no pin, no launder) and scores 14. Can I do better? The residual is only the reg swap. 14 is the best I can get with the swap.

Hmm, but maybe a body could score lower (fewer diff points) with the same swap? The score 14 counts the register-pair differences. 10 + 5 = 15 occurrences... score 14. A different body might have a lower count but still not 0. Not useful.

Now, should I record WALL with tag global-pri-bank-order? Yes.

But hold on — before that, let me reconsider one more idea for the reg order: what if I change the TYPE of `mode` such that its allocno mode changes (e.g., HImode) making `allocno_size`... no, changes code.

What about making `mode` a `u32`? Same.

Hmm, what if mode's `-1` and `0` values... no.

OK wait, actually, here's one more REAL idea: what if I make the *copy* (q/p) construction change base's live range? No.

Hmm, what about making base's refs 7 by merging the `unkA3DE` read with the `unkA3D8` read in the first if? E.g., the first if reads unkA3D8 and unkA3DE. What if I read both via ONE base expression? They're different fields; the RTL has 2 loads. base refs 2. Could I write `*(s16*)(base + 0xA3D8)` and `*(s16*)(base + 0xA3DE)`? Same 2 refs.

What if I use a pointer `p2 = (s16*)(base + 0xA3D8)` and read p2[0], p2[3]? That's a new variable and changes the address form (the target uses `addu at,s4,at` for each). Hmm, if p2 = base + 0xA3D8 is computed once and reused, the code would change (fewer addu). No.

OK. WALL it is. Actually hold on, let me reconsider ONE more time whether the swap could be avoided by a completely different C variable layout, e.g., if `file`/`val` were swapped or if a different variable took s3.

The order is: 144, 79, 76, 78, 74, 75, 72, 73, 77. The ones that need callee-saved and take s1..s4: 74, 75, 72, 73. 

What if r74 (val) didn't need a callee-saved reg? Then 75, 72, 73 would get s1, s2, s3? No: 74=val, 75=file, 72=base, 73=mode. If val took a caller-saved reg (possible if it doesn't cross calls — it does cross 6), then order would be file→s1, base→s2, mode→s3. But target has file=s1, val=s2, mode=s3, base=s4. So base must be s4.

Hmm, so with val crossing calls, we need 4 callee-saved regs: s1,s2,s3,s4 = file,val,?,?.

OK so the only way is mode before base.

Alright, let me also consider: what if the target's original had `mode` as a *pointer* or something with size 2? No.

Decision: item 1 WALL, tag global-pri-bank-order, best 14 (p14), tries: I've scored p01-p30 (30), q01-q07 (7), A-F (6), G,H,X (3), win.c (1) = ~47 tries. Good, ≥30.

Wait, but hold on. Before I settle: the task says "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". For item 1, we can't score 0 at all. So WALL.

Hmm, but actually — let me reconsider the possibility that a body could score 0 with the regs swapped by making the *code* use the swapped regs. No, the target is fixed.

Let me do one final check on the reg order: maybe a body where `base` is spelled as a `struct` pointer and `mode` as something else changes priorities slightly. Let me try a couple:
- mode as `s32 mode;` but base declared as `Unkstruct_80010178 *base` (fewer casts, same refs).
- mode used with `u32` type.

Eh, the priorities are determined by refs/live which won't change.

Hmm, one thing that WOULD change priorities: if `mode`'s live_length could drop below 65 by *removing an intervening statement*... no.

OK actually, hold on. Let me reconsider `live_length` = 83 for mode. The function is 161 insns. mode is referenced at insn ~34 (set), ~36 (set), ~120 (bltz), ~130 (arg), ~133 (bnez). live_length is the count of insns in the live range = from 34 to 133 = 99, but reported 83. Hmm, maybe it excludes the insns where it's dead in some blocks.

If I could move the last use from 133 to 115... no.

What if the first set moves from 34 to 52? The RTL at flow time: `mode = -1` is emitted where the C statement is. Between `st = func_8002F648()` and the if. That's ~insn 34. If I move the `mode = -1;` statement *later in the C source*, e.g., after `cnt = func_80029504()`? But the if needs it. Unless... hmm, what if I restructure:

```
st = func_8002F648();
if (st != X) { mode = 0; if (st != 0) func_8002F620(); }
else mode = -1;
```
No, discussed.

Hmm, what if `mode = -1` is moved after the first if but the first if's mode=0 is moved... no.

OK. Let me also try: `mode = (st == X) ? 0 : -1;` — no, the call.

I'll finalize item 1 as WALL. Actually wait, wait. Let me reconsider the DELAY SLOT observation once more. `li s3,-1` is in the delay slot of beq. In the RTL (pre-sched), where is `mode = -1`? If the C is `mode = -1; if (st != X) {...}`, the RTL order is: mode=-1, then the branch. So the first ref is right before the branch (~insn 34).

What if I write it as `if (st == X) { } else { mode = 0; ... }` with mode=-1 before... same.

Alright, WALL.

Hmm, hold on, actually. One more: what if mode is declared as `s32 mode` but I use `mode = -1` where -1 is stored as... no.

Hmm, what if I add a ref to mode by passing it to func_8002F620? No, that changes the call.

OK. Let me now record item 1 and move on. But before that, let me do a couple more targeted tries to be thorough (and satisfy "30 scored tries" comfortably). I have ~47. Fine.

Actually — hmm, wait. Let me reconsider `allocno_n_refs`. It's the number of references. What if I make the `mode >= 0` test reference mode TWICE in the RTL while emitting the same instruction? E.g., `if (func_8002F658() != val || (mode >= 0 && mode >= 0))` — combine would fold. Hmm, `mode >= 0 && mode >= 0` → cse/combine simplifies. 

What about `mode >= 0 || mode >= 0`? Folded.

OK, done. WALL.

Actually, hmm, hold on. Let me reconsider whether the *swap* is really the only residual and whether a slightly different body could make mode=s3 by having base take s4 for a different reason. What if I introduce a *fifth* callee-saved allocno that outranks base and takes s3, pushing base to s4... and mode to s5! No.

What if an allocno takes s3 and dies, and mode... no.

What if base's priority is raised ABOVE... no, that's the current state.

Alright. Let me also double-check: is `file` really s1 and `val` s2 in the target? Yes (s1=file, s2=val).

FINAL for item 1: WALL global-pri-bank-order, best 14.

Hmm, wait. Actually, let me reconsider one thing: what if I make `base` NOT cross calls? If base didn't cross calls it could use a caller-saved reg... but it must be live across calls (it's used after calls). Hmm, unless I recompute base after each call — that changes code.

OK. Moving on. Actually, hold on — let me reconsider the problem from the standpoint of "maybe the target's original C had `mode` as the FIRST-declared variable and base...". No, decl order doesn't matter.

Let me now check the time. I started item 1 at 16:44. Let me check the time now.

Actually, let me be efficient and set up items 2-4. But first record item 1's result and moves line.

Wait, actually — I realize I should double-check one more promising idea for the reg order: the `allocno_compare` TIE handling and the note "duplicate the statement after an if/else join into both arms — one insn of live length splits it". 

Hmm, that's about splitting ties.

And "A block with exactly THREE quantities is allocated in BIRTH order". 

Hmm.

OK, also: what about making mode's live_length shorter by moving the `if (mode == 0 && (res & 1))` test... 

Let me just check: what if `res` is declared differently so that the `mode == 0` test is merged? no.

Right, let me move on. Time management: 4 items, ~20 min each.

Let me record item 1 now.

Actually, one more consideration: maybe I should spend a few more tries on the reg order because a WALL here loses the crack. But the evidence is strong: pri 1518 vs 1204 with no lever-free way to change either without changing code.

Hmm, but actually — WAIT. I just realized: q05 dropped a base ref and flipped the regs, but changed the code at that site. What if I instead drop a base ref by removing the SET's ref through a *copy* that cse merges? E.g., introduce `u8 *b2 = base;` and use b2 in one place — that ADDS a ref to base and creates a copy. No.

What if the base SET could be eliminated? If base were assigned from another variable that's already in a register... there's no such variable.

Hmm, what if base is used to compute the file index? Like `file = ...` uses base? No.

OK, final: WALL.

Hmm, hold on, actually let me reconsider: what if instead of dropping a base ref, I make base's live_length LONGER by moving its set earlier in the RTL. Currently base is set in block 0 at ~insn 29 (after file/val loads at flow time?). Let me check the .lreg/flow dump: base's live 158 out of 161 means it's live almost from the start. Its set is at ~insn 3? Then live 158 is from 3 to 161. To get live >199 impossible.

OK. WALL. Let me record.

Actually, hmm, wait. Let me reconsider the live_length more carefully. pri = floor_log2(8)*8/158 = 3*8/158 = 0.1519 → 1518. And mode: floor_log2(5)*5/83 = 2*5/83 = 0.1205 → 1204.

What if base's refs were 8 but live 158... fixed.

What if mode's refs were 5 but live 65... need to cut 18.

Hmm, what if I move the `mode = -1;` statement to AFTER `cnt = func_80029504();`? Not semantically possible.

BUT WAIT — what if I make the first *set* of mode happen later by changing which value is set first? E.g.:
```
mode = -1;
if (st != X) { mode = 0; ... }
```
What if instead:
```
if (st != X) { mode = 0; ... } 
mode = (st != X) ? mode : -1;   // ugly
```
No.

OK, truly moving on.

Let me now record item 1: results row + moves line + notes.

Result row: `func_800CFE60__resident	src/resident/resident.c	func_800CFE60	launder,pin	WALL	14	47	global-pri-bank-order	<evidence>`

evidence ≤140 chars: "global-alloc pri: base r72 3*8/158=1518 > mode r73 2*5/83=1204; base takes $s3, mode $s4; pin-free launder cracked by `*q=val; p=q;` (161 ins, 14)"

Let me count: that's about 140. Let me trim.

Moves line: `launder,pin | func_800CFE60 | WALL global-pri-bank-order — base pri 1518 > mode 1204; launder side cracked by store-before-copy (`*q=val; p=q`) leaving only the $s3/$s4 swap (G23x)`

Now let me write these. Then item 2.

Actually, let me first check the time to keep the log honest.

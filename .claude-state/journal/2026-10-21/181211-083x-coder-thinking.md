---
ts: 2026-10-22T00:12:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_2P5BYGrMJB1CLCs1t3l4
---
Interesting: in e2, there are now 5 pseudos: r73 (v0, pri 6666, refs 4, live 12), r78 (v0, pri 5000, refs 3, live 6, 2 bytes), r75 (v1, pri 3333, refs 2, live 6).

Hmm, so in e2 the value got split into two pseudos (r78 and r75), and r75 got v1. Hmm, and the table says r73 → v0 and r78 → v0 and r75 → v1 — the "hard" column is from the .lreg dump (local-alloc's initial choice) which may be overridden.

Hmm, this is the standalone TU's dump, and the allocnos might differ from the real TU's.

Hmm, r73 (refs 4, live 12) — that's the POINTER (p). It gets v0. To flip, the pointer's priority must be < the value's.

So: pointer pri 6666 (refs 4, live 12). Value: pri 5000 (refs 3, live 6).

To make the value's priority > 6666:
- refs 4, live 6 → 13333 ✓
- refs 3, live 4 → 7500 ✓

How to get the value's refs to 4? The value's refs: set(1) + 2 uses (the two stores) = 3.

**IDEA**: what if the value is ALSO used in the comparison `== 0`? No.

**IDEA**: What if the stores are done as `((Unkstruct_80126948 *)p)->unk10 = v0;` and `((Unkstruct_80126948 *)p)->unk14 = v0;` — 2 uses. What if we add a third use that is free? Hmm.

**IDEA**: What if the value's live could be ≤ 4? The value's live = 6 (def → last use). In the RTL: the load (def), the addiu, the store, the store → 4 insns. Hmm, why 6? Because the load's pseudo r78 might be the LOAD's result (before the subtraction) and the addiu creates r75 (the copy).

Hmm! So in e2: r78 (refs 3, live 6) = the loaded value? Hmm.

Let me re-think for c1 (the original source with `v0 = v0 - 3`):
- r73 (refs 4, live 12): the pointer.
- r77 (refs 3, live 6, 2 bytes): the value.

Hmm, "2 bytes" — hmm! What if r77 is a 2-byte pseudo? Hmm, what 2-byte thing is in this function? Hmm, `(*(s16 *)&D_800B9AAC) = 0x7FFF;` — a 16-bit store! But that's in the if-branch (after the calls) and wouldn't be a local with live 6.

Hmm, the "2 bytes" might be the alloc_table's way of showing local_size.

OK, let me think about what would give the value 4 refs. In c1:
```c
v0 = p->unk10;    /* set */
v0 = v0 - 3;      /* read + set */
p->unk10 = v0;    /* read */
p->unk14 = v0;    /* read */
```
If v0's pseudo has 5 refs, pri = 2*5/6 = 16666 > 6666 → the value would get v0 FIRST ✓. But the table says the value has 3 refs.

So gcc must be creating a copy: the "v0 = v0 - 3" creates a NEW pseudo (r77) with set+2 uses = 3 refs, and the original load pseudo (r73?) has refs: set(1) + read(2) = 2. Hmm, but r73 has 4 refs.

Hmm, r73 refs 4 live 12 = the pointer (set + 3 uses) ✓.

So where's the load's pseudo? It should have 2 refs (set + read) — hmm, but it's not in the table. Maybe it was coalesced with the pointer? Hmm, no.

Hmm, the table has only 4 pseudos for c1: r74, r73, r77, r72. And r74 = the global (a0's copy, refs 17), r72 = another global. So the locals are r73 and r77 only. So the load's pseudo and the subtraction's copy are the same (r77) — gcc did `set r77 = mem; set r77 = r77 - 3` (in place) → refs: set(1) + read(2) + set(3) + read(4) + read(5) = 5. But the table says 3.

Hmm, unless the tool's "refs" for locals comes from a different source (the .lreg dump's "Register N references" lines). Hmm.

OK, empirical again. The key question: does raising the value's priority flip the allocation? Let me test with a variant that definitely changes the value's refs: e.g. use the value 3 times.

Hmm, what if the two stores were written to use a temp:
```c
v0 = p->unk10;
v0 = v0 - 3;
p->unk10 = v0;
p->unk14 = v0;
```
Hmm.

**NEW IDEA to add a ref for free**: the value `v0` is used in the comparison `if (... == 0)`? No, that's the call's result.

**NEW IDEA**: what if the value is stored to unk10 and unk14 and the ORDER of the two stores swapped? The target has unk10 first. Hmm, but what if the source order is unk14 then unk10 and the SCHEDULER reorders them to unk10 first? The scheduler generally preserves memory order (it can reorder independent stores, but gcc's sched might). Hmm! Actually gcc's sched1 CAN reorder two stores to different addresses? It usually keeps them in order (they may alias). Hmm, risky.

Hmm, let me think about the priority lever differently: **the pointer's live is 12; the value's is 6.** What if I could make the pointer's live 18+? The pointer's live = from its def to its last use.

The pointer's def is the load at the top; its last use is the store `sw v0,20(v1)`.

What if the pointer were ALSO used in the LAST statement of the function without changing the code? Hmm, no.

What if the pointer's load happened EARLIER in the RTL — i.e., before the frame setup? It does (in the scheduled code). But in the RTL (pre-scheduling), the load is after the prologue. Hmm, the live length is computed on the pre-scheduling RTL? Then the pointer's live = from the load to the last use.

Hmm, 12 insns apart. The function's first 12 RTL insns: prologue (addiu sp, sw s0, move s0,a0, sw ra), then the load (lui, lw), then the value's load, li a0, addiu, sw, sw. Hmm, that's about 11-12 ✓.

So the pointer's live ≈ the distance from the load to the last store ≈ 11-12.

To make it 18: insert 6 more insns between the pointer's load and its last use — but those insns would appear in the code ✗.

⇒ The only lever is the value's refs.

**How to add a ref to the value for free?**
Hmm! What if the value is used in the second store via an expression that reads it twice? E.g.:
```c
p->unk14 = v0;
```
Hmm.

What about making the FIRST store write `v0` and the second write `v0` — 2 uses. A third use would need a third store ✗.

Hmm, what if the value's live is shortened instead? The value's live = 6: def (the load) → last use. The insns in between: li a0, addiu, sw, jal?, sw. Hmm, in the pre-schedule RTL: lw v0; (addiu v0); sw v0; sw v0 → live ~4. Hmm, the table says 6.

Hmm, maybe the value's live includes the `li a0,10` (the call arg) and the jal.

Hmm, what if the call `func_8013D13C(10)` were moved EARLIER in the source (before the stores)? Then the value's live would... hmm, the value must be computed before the call? No! The source could be:

```c
p = D_801151D4;
v0 = p->unk10;
v0 = v0 - 3;
p->unk10 = v0;
p->unk14 = v0;
if (func_8013D13C(10) == 0) {...}
```
The call is after the stores ✓ (current). If the call were BEFORE the stores:
```c
p = D_801151D4;
v0 = p->unk10;
v0 = v0 - 3;
if (func_8013D13C(10) == 0) {
    p->unk10 = v0;    /* hmm, changes semantics: the stores would only happen in the then-branch */
    ...
}
```
✗ semantics.

OK. Hmm.

Let me try yet another idea: **the pointer's refs could be reduced from 4 to 3** if the pointer's SET is merged. What if the pointer is loaded as part of a larger expression? Hmm.

Hmm, what if the pointer is assigned in a way that gcc doesn't need a separate set pseudo — e.g., `p = D_801151D4;` where D_801151D4's load goes directly into p's pseudo (that's already the case: 1 set).

So the pointer: 1 set + 3 uses = 4 refs. pri = 2*4/live.

⇒ The value needs pri > 2*4/12 = 0.667 (normalized). Value: floor(log2(refs))*refs/live > 0.667. With refs 3: 1*3/live > 0.667 → live < 4.5 → live ≤ 4.

So: if the VALUE's live were ≤ 4, it would win. The value's live is 6.

Hmm, what if the value's live were shorter because the value's def is LATER? The value's def = the load of unk10. Its last use = the second store.

In the RTL: 
```
load v0        <- def
addiu v0,v0,-3
sw v0,16(p)
sw v0,20(p)
```
live = 4! Hmm, but the table says 6. Hmm, maybe REG_LIVE_LENGTH counts differently (e.g., including the li a0 and the jal because the pseudo's live range in the flow graph is measured in a different unit).

Hmm. Whatever.

Let me try a variant that shortens the value's live by removing the intermediate: hmm.

**RADICAL IDEA**: What if the pointer's live is extended by keeping the pointer alive across the call — making it a global? Then global-alloc gives it a callee-saved reg ✗ (the target has v1).

Hmm, BUT WAIT: what if the pointer's live is extended but the extension doesn't cross a CALL? The call is right after the stores. Hmm, the pointer's last use is the store before the call.

Hmm.

OK. Let me try the reverse: give the value 4 refs by making the source use it 3 times WITHOUT changing the code. Hmm... 

**IDEA!!!**: What if the two stores are written with a common subexpression that gcc's CSE turns into one store? no.

**IDEA!!!**: What if the value is stored via a compound literal... no.

**IDEA!!!**: What if the subtraction is written as `v0 = v0 - 3;` but the FIRST store uses the pre-subtraction value? ✗ semantics.

Hmm, hmm. What about the `li a0,10` — the call argument 10. Hmm.

OK, let me try to think about what gcc counts as a "ref" for the value pseudo: maybe REG_N_REFS counts the number of times the pseudo is referenced in the RTL. For `set v0 = mem; set v0 = v0 - 3; set mem2 = v0; set mem3 = v0`:
- set v0 = mem: 1 (the dest)
- set v0 = v0-3: 1 (dest) + 1 (src) = 2
- set mem = v0: 1
- set mem = v0: 1
Total = 5.

But the table says 3. So gcc must have created a copy pseudo for `v0 - 3`:
- r_A = load: set(1) + read(1) = 2 refs
- r_B = r_A - 3: set(1) + read(2) = 3 refs ✓ (this is r77!)
- and r_A is... hmm, it should be in the table with 2 refs. But the table doesn't show a pseudo with 2 refs.

Hmm! Unless r_A was coalesced/eliminated. Hmm.

OK, since the value's pseudo (r77) has 3 refs and live 6 → pri 5000, and the pointer (r73) has 4 refs, live 12 → pri 6666.

**What if the value's pseudo had 4 refs?** Then pri = 2*4/6 = 13333 > 6666 ✓.

How to get 4 refs on the value pseudo (the one holding v0-3)? It has: set(1), use(2), use(3). A 4th ref: hmm.

What if the source were:
```c
v0 = ((Unkstruct_80126948 *)p)->unk10;
v0 = v0 - 3;
((Unkstruct_80126948 *)p)->unk10 = v0;
((Unkstruct_80126948 *)p)->unk14 = v0;
```
vs
```c
v0 = ((Unkstruct_80126948 *)p)->unk10 - 3;
((Unkstruct_80126948 *)p)->unk10 = v0;
((Unkstruct_80126948 *)p)->unk14 = v0;
```
In the latter (e2), the table shows r78 (refs 3, live 6) AND r75 (refs 2, live 6, hard v1). So e2 split into: r75 = the loaded value (2 refs: set + read), r78 = the result (3 refs: set + 2 uses).

Hmm, so in e2 there are 3 locals (r73 pointer, r78, r75) and the allocation was r73→v0, r75→v1, r78→v0?? The table shows "hard" for r73=v0, r78=v0, r75=v1. Hmm, the "hard" for r73 and r78 are both v0 — that's from the .lreg dump where maybe one was later reassigned.

Hmm, confusing. But e2's code = 58 ins like c1, and the score was the same, so the allocation was the same (pointer in v0).

Hmm OK.

**Let me try: make the value's pseudo have 4 refs by adding a use that's free.** 

What about: `((Unkstruct_80126948 *)p)->unk14 = v0;` → what if written as `((Unkstruct_80126948 *)p)->unk14 = (v0, v0);`? That's a comma expression → gcc evaluates v0 twice → 2 refs! And the code: the comma expression's value is the second operand → `set mem = v0` — hmm, gcc might generate the same code but with an extra ref!

Hmm, `v0, v0` — gcc's expand would evaluate v0 (no side effect) then v0. The RTL would be `set mem = v0` with v0 read... hmm, the comma operator creates a temporary: `set tmp = v0; set tmp = v0; set mem = tmp`. gcc would fold the temps → probably 1 read.

Hmm, but the REF COUNT might increase before folding! The alloc table's refs come from the final RTL though.

Hmm.

OK, you know what? Let me try the "explicit temp" approach that adds refs:
```c
s32 p;
s32 v0;
s32 w;
p = D_801151D4;
v0 = ((Unkstruct_80126948 *)p)->unk10;
w = v0 - 3;
v0 = w;
((Unkstruct_80126948 *)p)->unk10 = v0;
((Unkstruct_80126948 *)p)->unk14 = v0;
```
Hmm, `w = v0 - 3; v0 = w;` → gcc would coalesce w and v0 (the copy) → same code, but the copy might add refs to v0 (read + set). Hmm! v0's refs: set(1), read(2), set(3), read(4), read(5) = 5 → pri 2*5/live. And the copy pseudo w: set(1), read(1) = 2 refs.

Hmm, that's the same as the original.

Hmm, so the original source's `v0 = v0 - 3` already gives v0 5 refs (in the source's RTL). But gcc's actual pseudos differ.

OK, I need to stop the analysis paralysis. Let me do a broad automated sweep: generate ~30 variants with different structural spellings and score them all. Let me focus on plausible ones:

1. `v0 = v0 - 3;` → `v0 -= 3;`
2. `v0 = v0 - 3;` → `v0 = v0 + (-3);`
3. pointer as `char *`
4. pointer as `void *`
5. pointer as `u32`
6. value as `u32`
7. `p->unk10` vs `*(s32*)((u8*)p+0x10)`
8. the stores in the reverse order
9. the value's subtraction as `v0 = v0 + (-3);` with the value as `u32`
10. p as `s32` with the value as `int`
11. using a local `w` for the subtraction
12. `v0 = 3 - v0`? no, semantics.
13. the call spelled differently: `if (func_8013D13C(10) == 0)` vs `if (((s32 (*)(s32))func_8013D13C)(10) == 0)` — the current source has the cast. Hmm! What if the cast were removed? `func_8013D13C` is declared as `extern s32 func_8013D13C(void);` — calling it with an argument would be an error in C89? gcc allows it with a warning. The target has `li a0,10` + `jal func_8013D13C`. The cast `((s32 (*)(s32))func_8013D13C)(10)` is what the source has. Removing the cast: `func_8013D13C(10)` — hmm, the declaration says (void), so passing an arg is a mismatch → gcc 2.7 might still pass it. The generated code: the arg is set up ✓ same. But the CALL's target address: the cast version calls the same address ✓.

Hmm, that's about the call, not the regs.

OK. Let me write a sweep script with many variants and let it run. That's the efficient path: one script, N compiles, print scores.

Let me write a generic sweeper: it takes a list of (name, body) and scores them, printing only the best. I'll write the variants inline in a python file for this item.

Actually — hold on. Let me reconsider the problem once more. 

**AH!!! WAIT!!!** What about the `s0` copy of `a0`?! The target: `move s0,a0` — a0 is copied to s0 at the start. That's a "copy" of the parameter. In gcc, a0's pseudo (r74, pri 40000/30000) is a GLOBAL (crosses 11 calls) → global-alloc → s0 ✓.

Hmm, and r72 (pri 750, live 40, crosses 11 calls) → also a global → s1? But "Hard regs used" doesn't include $17. Hmm, so r72 is in... hmm.

OK, whatever.

Hmm, let me look at the problem from the standpoint of: WHAT IF the value pseudo were GLOBAL and the pointer LOCAL? Then the value (global) would get a callee-saved reg ✗.

WHAT IF BOTH were globals? Then global-alloc assigns by priority: the pointer (pri 6666) and the value (pri 5000) → the pointer gets $16, the value $17 ✗ (target: caller-saved).

Hmm.

OK, let me just do the broad sweep. Let me write it.

Actually, WAIT. One more idea, and I think it's a good one: **what if the pointer is used 3 times but the FIRST use is the load and the pointer's pseudo could have a lower priority if its live were longer... what if the pointer were loaded EARLIER, before the function prologue?**

In the RTL, the prologue is inserted by the "prologue" pass at the function start, and the pointer's load is in the body. The live length is computed on the RTL after the prologue insertion? Hmm.

What if the pointer's load were in the "entry block" — it already is.

Hmm, the live length is in RTL insns. The pointer's def is at insn ~5 (after the prologue) and its last use at ~16 → live 12.

Hmm! What if the prologue were LONGER (more saves)? E.g., if the function saved more callee-saved regs, the insns between the pointer's def and its use would grow → the pointer's live would grow! But that changes the code ✗.

OK, sweep time. Let me write ~20 variants.

Hmm, but honestly, the chance any hits is maybe 20%. And I have 4 other items. Let me cap this at one sweep round.

Let me write the sweep with these variants (all preserving semantics):
1. v0 -= 3
2. v0 = v0 + (-3)
3. pointer char*, accesses via (char*)
4. pointer void*
5. pointer u32
6. value u32
7. stores reversed (unk14 then unk10) — semantics differ! (the target's order) — skip
8. w temp for the subtraction
9. `v0 = p->unk10; v0 = v0 - 3;` with p as Unkstruct* (f1, tried)
10. the call without the cast
11. `v0 = ((Unkstruct_80126948 *)p)->unk10;` with the subtraction written as `v0 -= 3;` and p as u32
12. the value as `long`? (32-bit)
13. `v0 = ((Unkstruct_80126948 *)p)->unk10 - 3;` with the value as u32
14. the pointer assigned with `p = (s32)&D_801151D4;`? no, wrong semantics.

Hmm, the semantics-preserving space is small. The register assignment is determined by (a) the pseudo creation order and (b) the priority. The priority of the value = f(refs, live).

**KEY INSIGHT ATTEMPT**: the value's pseudo needs pri > 6666 → with refs 3, live ≤ 4.

The value's live is 6 = (def to last use). The def is the load. The last use is the second store.

Hmm, what if the value's live were measured from the ADDU (the subtraction) rather than the load? In c1, the value pseudo r77 (3 refs) is likely the post-subtraction value (set + 2 uses). Its def = the addiu. Its last use = the second store. Between them: the first store + (li a0, jal) → live 6.

To shorten: if the value's def (the addiu) were closer to the last use. Hmm, the addiu is right before the stores in the source.

Hmm, the live is 6 but the source order gives: addiu, sw, sw → 3. Hmm, so 6 suggests the jal and li a0 are counted (the call is between? no, the call is AFTER the stores in the source).

Hmm, wait: the source is:
```
p = D_801151D4;
v0 = p->unk10;
v0 = v0 - 3;
p->unk10 = v0;
p->unk14 = v0;
if (func_8013D13C(10) == 0) {...}
```
So the value's last use is the 5th statement; the call is after. Live should be ~4-5.

Hmm, REG_LIVE_LENGTH is measured in the flow graph: the live range spans the insns from the def to the last use, counting ALL insns in between (including the `li a0,10` if it's before... no, the li a0 is for the call which comes later).

OK. 6 might include the load, addiu, sw, sw = 4 plus 2 more (the lui/lw? no, those are before).

I'm going in circles. Let me just run the sweep and see.

Let me write the sweep script with ~12 variants for 80180480.

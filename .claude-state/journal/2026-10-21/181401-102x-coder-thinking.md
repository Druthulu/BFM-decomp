---
ts: 2026-10-22T00:14:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_RO0YDA5fUGtA1ObPzBhR
---
Score 20, 89 ins = 89 ins ✓ (the count matches!).

The residual: the target materializes x (-1664) into v1 and y (-3712) into a1 EARLY (insns 18-19), and reuses them for the 4 x-uses and 3 y-uses. In mine, the constants are materialized at each use (li v0,-1664 etc.) — hmm, mine has `li v0,-1664` at 39 and `li v1,-3712` at 40 and multiple stores.

Hmm, mine has 89 ins too, so the same count but a different distribution: mine materializes x twice? Hmm.

Let me look: mine[39] = `li v0,-1664`, mine[40] = `li v1,-3712`, mine[42] = `sw v0,0(at)`, ... mine[51] = `sw v1,0(at)`.

So mine materializes x into v0 (at 39) and y into v1 (at 40), then uses v0 for the x-stores and v1 for the y-stores. Hmm, so mine ALSO reuses them ✓ but with different regs (v0/v1 vs v1/a1) and later (39-40 vs 18-19).

The target: x → v1, y → a1, z → a0. And they're materialized at 18-20 (early).

So the residual is (a) the position (early vs late) and (b) the register choice (v1/a1 vs v0/v1).

Hmm! The launder forced x into a reg at the top. Without it, gcc materializes the constants at the first use (39-40).

Hmm, so how do I get them materialized early without the launder? The "birth boost" (sched1) would schedule the `li` early if it were a "birthing" insn. Hmm.

Hmm, the target's x → v1 and y → a1: a1 is a CALLER-SAVED reg! And the function has calls (func_8001C2C4 at 13, func_800233CC in the loop). So a1 would be clobbered by the calls... but x/y are used before the loop (the stores at 43-54) and the loop is after. Hmm, but the `li a1,-3712` at 19 is before the `jal func_8001C2C4`? No: the jal is at 13, before 19. OK so a1 is set at 19 and used at 45-46 (before the loop's call) ✓.

So the target allocates y to a1 and x to v1. Hmm, and z to a0 (the pin).

Hmm, this is a register-allocation + scheduling issue. The launder forced the values into registers early (the asm's outputs are hard regs chosen by gcc: v1, a1, a0 — hmm! interesting: the asm's output regs are v1, a1, a0 = exactly the target's regs ✓).

So the launder's asm outputs got v1, a1, a0. Hmm, the asm with 3 outputs (x, y, z) — gcc allocated them v1, a1, a0 (a0 for z because of the pin).

Without the launder: gcc materializes the constants at their uses: x → v0 (the first use's reg), y → v1.

To reproduce: I need the constants materialized early into v1/a1/a0.

Hmm! What if the constants are used EARLIER? Hmm.

Hmm, what if the values are passed to a function? no.

Hmm, what if the stores are reordered so that the x/y stores come first? Hmm, the target's order: the `li`s at 18-20 (before the D_80192CF0 store at 21-23) — so the x/y/z materializations are before the FIRST store (D_80192CF0 = 0x68).

Hmm! So in the target, the li's are hoisted to the top of the block, before all the stores. That's the "birth boost" (sched1) hoisting the constant materializations to the top ✓ (constants are cheap to rematerialize; the birth boost puts them early).

Hmm, so in the target, the x/y/z `li`s are at the top (18-20) — hoisted. In mine, they're at 39-40 (at their first use).

Hmm, so gcc did NOT hoist them. Why? Because in mine, the constants are materialized by the STORES (each store's value is a constant → gcc materializes it into v0 at the store). Hmm, and gcc's CSE... hmm, mine has `li v0,-1664` ONCE and reuses v0 for the 4 x-stores ✓ (so cse did unify them).

Hmm, so mine's structure: the li's at the first use, and the target's: the li's at the top.

The difference: the ORDER. The target's li's are before the D_80192CF0 = 0x68 store (insn 21-23). Mine's are at 39 (after the other stores).

Hmm! So in the target, the x/y/z materializations are EARLIER than the other stores. In mine, later.

Since the values x, y, z are assigned in the source BEFORE the stores (x = -0x680; y = ...; z = ...; then the stores), the "birth" of the constants is at their assignment. So gcc's birth boost would schedule the li's EARLY ✓ (the target). But in mine, gcc scheduled them LATE (at the first use).

Hmm! Why? Because the "birth boost" is demoted when... hmm, "a second identical assignment demotes sched1's birthing boost". Hmm.

Hmm, in mine, the constants are used 4/3/3 times. Hmm.

Hmm, hold on: in mine, are the li's really at 39? The diff says: "replace mine[39:41] target[41:42]: 39 li v0,-1664 | li v0,573; 40 li v1,-3712 | --". So mine[39] = `li v0,-1664` and mine[40] = `li v1,-3712` — hmm, and the target[18-19] = `li v1,-1664; li a1,-3712`.

So in mine, the li's are at 39-40 and in the target at 18-19 (and the target's 39-40 region has `li v0,573` etc.).

Hmm, and the regs: mine v0 (x) and v1 (y); the target v1 (x) and a1 (y).

Hmm! So both the position and the regs differ. Hmm.

Hmm, the position difference: the target's li's are at 18-20, right after the `jal func_8001C2C4` (13) and `lui s0` (15-16) and `move s1,zero` (17). Hmm, so the li's are at the top of the "post-call" region.

In mine, the li's are at 39-40, after several stores.

Hmm! So in the target, x/y/z's materializations are hoisted to just after the call — that's the classic "the value is computed early, before the block's stores".

In mine, the constants are materialized at their first USE (the D_80192CE0 = x store).

Hmm, why? Because in mine, the x value is a CONSTANT propagated into the stores: gcc's "constant propagation" (cse) forwards the constant to each use, and the materialization happens at the first use. Hmm, but the target has the materialization early — which requires the value to be a PSEUDO (a variable) rather than a forwarded constant.

AH, that's the key! In the target, x is a PSEUDO (a register holding the constant) — materialized once, used 4 times. In mine, gcc's cse forwarded the constant to the stores, and the materialization is at the first use, and it's hoisted only to there.

Hmm, but mine also has ONE `li v0,-1664` reused 4 times ✓ — so cse did create a pseudo. Hmm.

So the difference is just the position (39 vs 18) and the reg (v0 vs v1).

Hmm! The position: the target's `li v1,-1664` is at 18 — right after `move s1,zero` (17) and before `li v1,-1664`... hmm, and the D_80192CF0 store (21-23).

So in the target, the constants are materialized BEFORE the first store (D_80192CF0 = 0x68, whose value 0x68 = 104 is `li v0,104` at 21 ✓ — hmm! So the target's `li v0,104` is at 21 and the `li v1,-1664` at 18 — so the x/y/z materializations are BEFORE the 0x68's materialization!

Hmm, so the ORDER of the materializations: v1(-1664)=x, a1(-3712)=y, a0(-848)=z, then v0(104)=0x68, v0(11), v0(874), v0(1), v0(500), v0(657), v0(573)...

So x, y, z are materialized FIRST, then the other constants in source order. In the source, x/y/z are assigned first (x = -0x680; y = -0xE80; z = -0x350;) and then the stores (D_80192CF0 = 0x68, etc.).

So the target's order = the source order of the ASSIGNMENTS (x, y, z, then the stores' values) ✓✓✓.

And in mine, the order is: the stores' values first (0x68 at 21... hmm, mine[21] = `li v0,104`? the diff shows mine[18:18] is missing the target's li v1 and li a1 — so mine[18] = the target's 20 = `li a0,-848` (z, the pinned one!) and mine[19] = the target's 21 = `li v0,104`.

So in mine, z's materialization is at 18 (early ✓ — because z is pinned to a0 and the pin forces it early?) and the x/y materializations are at 39-40 (late).

In the target: x (v1) at 18, y (a1) at 19, z (a0) at 20.

So the target's x and y are materialized early (18-19) and mine's late (39-40).

Hmm! Why is z early in mine? Because the pin (a0) forces it? Hmm, or because z's use (D_80192CE8 = z) is at 47 hmm.

OK, so the difference: the x and y materializations are early in the target.

The launder forced them early (the asm's outputs are hard regs, and the asm is scheduled at the top with priority 1).

Without asm, gcc schedules the constant materializations at their first use (39-40) — hmm, but why is z's at 18 in mine?

Hmm! Because z is PINNED to a0 → the pin forces the value into a0 early (the assignment `z = -0x350` must be in a0, and the assignment is at the top of the source). Hmm, but the pin is on z, so `z = -0x350` → `li a0,-848` at that point (early ✓).

And x, y are ordinary variables: their assignments (x = -0x680) would be at the top too, but gcc's CONSTANT PROPAGATION forwards the constants to the uses, so the materialization happens at the first use (39-40) instead of at the assignment ✓ (that's gcc's "constant propagation into the use" — the assignment is dead).

So to get the target's shape, the x/y values must NOT be constant-propagated — i.e., they must be in a register from the assignment. That's what the launder does (it makes the asm output a hard reg, so the constant is materialized into a reg at the asm).

Hmm! How to prevent the constant propagation in real C? Hmm.

**IDEA**: If x is used in a context that isn't a simple store, the constant might not be forwarded. Hmm.

**IDEA**: The target's x → v1 and y → a1. Hmm, a1 is a caller-saved reg — so the values are materialized into regs and used before any call ✓.

Hmm, what if x and y were passed to a function? no.

**IDEA (promising!)**: What if x and y are assigned from something that isn't a compile-time constant, but the same value? E.g. `x = -0x680;` hmm.

Hmm, what if the assignment is `x = -0x680 - 0;`? Folded.

Hmm, what if x is a VOLATILE variable? Then the value is loaded from memory ✗ (extra insns).

Hmm, what if x is assigned in a way that gcc can't fold, e.g. `x = -(0x680);`? Same.

Hmm, what about the "declaration order" dial: if x and y were declared LATER... hmm.

Hmm, what about the ORDER of the assignments: what if x, y, z were assigned AFTER the first stores? Hmm, then the materialization would be later ✗.

Hmm, what if the values were assigned via a `const` array? hmm.

OK, what about the classic: **the "two sets" trick**! If x is assigned TWICE, the constant propagation might not forward... hmm.

Hmm, actually, hold on. Let me reconsider: maybe gcc's constant propagation ISN'T the mechanism. Let me look at what mine produces: `li v0,-1664` at 39 and then `sw v0,0(at)` at 42, 44, 46, 48 — so the value is in v0 and reused ✓. So there IS a pseudo for x (materialized once at 39). The question is just why it's at 39 instead of 18.

39 is where the FIRST USE is (D_80192CE0 = x, the store at 42-43). Hmm, and the materialization is at 39 (a few insns before). So gcc placed the materialization at the first use.

In the target, it's at 18 — before all the stores.

So the difference: the target's x pseudo is materialized EARLY (at the top of the block) — the classic "constant hoisting" (sched1's birth boost hoists a constant's materialization to the top of the block if it's cheap). Hmm, but mine didn't.

Hmm! Why? Because in mine, the x pseudo's "birth" is at the first use (39) — i.e., the assignment `x = -0x680` was constant-propagated away, so the pseudo is created at the use.

In the target, the pseudo's birth is at the assignment (early) → the materialization is hoisted to the top ✓.

So the difference IS the constant propagation. In the target, x's assignment survived (the pseudo is born at the assignment).

How to keep the assignment alive in real C? Hmm: if x is used in a way that requires the variable (not the constant)... e.g. if x's ADDRESS were taken? no.

Hmm! **What if the value is used in TWO DIFFERENT WAYS** — e.g. one use as an int and one as a pointer? Hmm.

**What if the assignment is to a variable that is also incremented?** Hmm.

Hmm, what about: `x = -0x680;` then later `D_80192CE0 = x;` — the propagation.

Hmm, what if x were assigned a NON-constant expression that folds to the same value? E.g. `x = -0x680 + 0;` → folded at the front end.

Hmm, what if x is assigned from a variable that's constant: `x = c;` where `c` is a const int? Hmm, gcc folds that too.

Hmm, what if x is assigned from a global that's const? no.

Hmm, hmm. What about the "set count" dial: "a second identical assignment demotes sched1's birthing boost". Hmm, that's the opposite.

Hmm! What if x is assigned TWICE (e.g. `x = -0x680;` and later `x = -0x680;`)? Hmm, an identity statement (banned-ish).

Hmm, what about this: the launder forces the value into a hard reg. What if we could get the same by making x a **call argument**? no calls.

Hmm, what about the "**&&**" fold? no.

OK, hmm. Let me look at the target once more: x → v1, y → a1, z → a0. Hmm, interesting: a1 and a0 are ARGUMENT registers. And v1 is a caller-saved temp.

Hmm! What if the ORIGINAL game code passed these values to a function?! Hmm, no call in the target's region.

Hmm, hmm. What if the launder's asm outputs were allocated a1, a0, v1 — gcc's asm output allocation prefers the regs that the values will be used in...

OK. Given the time, let me try a couple of quick experiments for this item:
(a) Move the x/y/z assignments to the very top (before `p = D_80192D28;` etc.)? Hmm, the source order: v = func_8012C1B8(); ...; func_8001C2C4(v); p = D_80192D28; s1 = 0; x = -0x680; y = -0xE80; z = -0x350; <launders>; D_80192CF0 = 0x68; ...

The target's li's are at 18-20, i.e. AFTER the call at 13 and after `lui s0` (15-16) and `move s1,zero` (17). So the materializations are in the middle of the block, not at the very top ✓ (consistent with the source order x,y,z after s1 = 0).

So in the target, the materialization happens at the ASSIGNMENT's position (early) ✓ — i.e., the assignment survives (the pseudo is born there).

So the fix: prevent the constant propagation of x and y. Hmm.

**IDEA**: what if x and y are assigned from an expression that gcc can't fold to a constant but that produces the same value? E.g.:
- `x = -0x680;` → the constant.
- What about `x = -1664;`? same.
- `x = (s32)-0x680;`? same.

Hmm, what if x is assigned the value of ANOTHER variable that holds a constant? e.g. `s32 c = -0x680; x = c;` → gcc folds c's value into x (cse) ✗.

Hmm, what if the assignment is through a pointer: `*(s32 *)&x = -0x680;`? Hmm! That would force the value into memory ✗ (an extra store/load).

Hmm, what about the "temp introduced" dial: R8 (a temp introduced). Hmm.

Hmm, what about: x is used in a `+=`? `D_80192CE0 = x;` hmm.

Hmm, hold on! What about the ORDER: the launder is between the assignments and the stores. What if the "birth" of the x pseudo is at the assignment because x is USED in the launder? I.e., the launder's input "0"(x) reads x → so x's pseudo is live at the asm → the pseudo is born at the assignment and dies at the asm → the materialization is at the assignment (early) ✓.

Without the launder, x's only uses are the stores (later) → the constant propagation kills the assignment.

So the question: how to make x's pseudo live at the assignment point without asm?

**IDEA**: make x's value USED in a way that doesn't fold, e.g. a comparison that gcc can't fold. Hmm: `if (x == -0x680) {}` — gcc folds it (x is a constant) ✗.

**IDEA**: use x in a context that requires a register: e.g. `func_something(x)` — a call! The function has calls: func_8001C2C4(v) is BEFORE the assignments. Hmm, and the loop's func_800233CC(p, 0x40) is after the stores.

Hmm! What if we MOVE a call to after the assignments and pass x to it? That would change the code ✗.

**IDEA**: the pin! z is pinned to a0 and its materialization IS early (mine[18] ✓). So the PIN has exactly this effect (the value is forced into a register at the assignment). But pins are banned ("no register vars").

Hmm!! But wait — the pin on z is ALREADY in the def (another row). The brief says "no register vars" in the CONSTRAINTS: "no signature or decl change outside the body (callers stay as they are); no `register` vars, no `__asm__`". Hmm! So I can't ADD a register var. But the existing one (z) stays.

Hmm, so the pin's mechanism (forcing a value into a register early) is exactly what's needed for x and y. And we can't use pins.

Hmm. Hmm! But maybe there's another way to force a value into a register early...

**IDEA**: what if x and y are used by a computation that isn't foldable, e.g. `D_80192CE0 = x;` where the store's value is a constant that gcc can fold... hmm.

**IDEA (promising!)**: what if the values are stored to the globals via a POINTER? E.g. `*(s32 *)&D_80192CE0 = x;` — hmm, that's the same.

Hmm, what if x is used as an index or in an arithmetic expression that folds: `D_80192CE0 = x + 0;` → folded.

Hmm.

**IDEA**: what if the value is used in a `switch`? no.

Hmm. What about the R6/R8 dials: "a single-set temp inlined" / "a temp introduced". Hmm.

**IDEA (the "const holder" census!)**: I saw `const_holder_census.py` in .run/P36/engine/! "control: a holder whose value is not a literal, and one written twice, are not constant holders". So there's a "constant holder" concept: a variable that holds a constant. And the census is about "holders" — variables whose value is a constant. Hmm! The R-family might have a rule about constant holders: "a holder written twice is not a constant holder" — hmm!

So: if x is assigned TWICE (or assigned a value that isn't a literal), gcc treats it as a non-constant holder → the pseudo survives → the materialization is at the assignment ✓.

Hmm! So: `x = -0x680;` written twice? That's an identity statement (banned-ish).

Hmm, but "a holder whose value is not a literal" — so if x's value is NOT a literal, the pseudo survives. E.g. if x = -0x680 is written as something gcc can't fold...

Hmm! What if x is assigned from a literal but through a cast that gcc keeps? Hmm.

Hmm, what about: `x = -0x680;` → what if it's `x = (s32)(-0x680);`? Folded.

Hmm, what about the "**init at decl**" dial: `s32 x = -0x680;` — the initialization at the declaration. Hmm! That might change the propagation: a variable initialized at the declaration and used later... hmm, gcc would still propagate the constant.

Hmm.

OK, time check: I'm deep into the session. Let me now be pragmatic:

Given the time, I'll do ONE more experiment for this item (the "holder written twice" idea is banned; let me try "init at decl" for x and y) and then do the bookkeeping for all 7 items.

Actually, hmm, wait. Let me reconsider: the launder makes x's pseudo live at the assignment. What if x is USED at the assignment point in a way that keeps it in a register but folds to nothing? Hmm, "identity-statement launders" are banned.

Hmm, what about a do-while(0) trick: `do { r = x; } while (0);` — hmm, that's a copy (an extra insn) ✗. Hmm, but the T10 example did exactly that: "do { r = p + i; } while (0);" to add a ref. Hmm, but it adds an insn (the add). Hmm, in the T10 case the add was needed anyway.

Hmm.

OK, let me try the "init at decl" variant (x and y declared with initializers) — that's a legit C0505 dial and it might change the propagation (a variable with an initializer at the declaration is a "constant holder" too, hmm).

Let me write v2:
```
    s32 x = -0x680;
    s32 y = -0xE80;
    register s32 z asm("a0");
    ...
    z = -0x350;
```
Hmm, but z is pinned and assigned in the body; keep it.

Hmm, and the decl order: x, y, z are declared with the others.

Let me try it.

Hmm, and also try: what if the assignments are moved to the TOP of the function (before `v = func_8012C1B8();`)? Then the materialization would be at the top of the function (before the call) — the target has it AFTER the call ✗.

Let me just do v2 (init at decl) and then wrap up. I MUST do the bookkeeping now.

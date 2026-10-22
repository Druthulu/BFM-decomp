---
ts: 2026-10-21T23:47:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_feZ5kRSRNkrM84p5NHxL
---
This one is more complex. The launder:
```
    {
        u16 *pb = &D_800B99DC;
        __asm__("" : "=r"(pb) : "0"(pb));  // !FAKE: launder
        p = pb;
    }
```
The comment explains: the target materializes &D_800B99DC into $v0 and then `addu $s0,$v0,$zero`. A plain `p = &D_800B99DC` is coalesced straight into $s0. The zero-byte re-tie fence keeps the two pseudos apart.

Target insns 17-19:
```
17 lui v0,0x0   ; HI16 D_800B99DC
18 addiu v0,v0,0  ; LO16 D_800B99DC
19 move s0,v0
```
So &D_800B99DC is materialized into v0 and then copied to s0. s0 is then used at insn 22 `lhu v0,0(s0)`, 32, 38, 63, 87 — s0 is the pointer used across calls (it crosses calls!). So the target has TWO pseudos: a short-lived one (v0) and the call-crossing one (s0).

In our C, `p = &D_800B99DC` → gcc coalesces into s0 directly → we'd get `lui s0; addiu s0,s0,0` and no `move s0,v0`. That's the difference: the target has the extra `move s0,v0` and uses v0 for the materialization.

So the fix: make gcc materialize the address into a temp register (v0) and then copy it to s0. How?

The launder creates a copy: pb is a pseudo (the asm output = a hard reg? no, "=r" with "0" input → a copy of the same value). Hmm: `__asm__("" : "=r"(pb) : "0"(pb))` forces pb into a register. Since pb's value is the address of a global, gcc materializes it (lui/addiu) into some reg (v0) and then the asm copies it to another (the "0" constraint means the output is the same register as the input? No: "0" means the output operand 0 uses the SAME register as input operand 0. So the asm's output register == the input register. So it's a no-op that just forces pb into a register.

Hmm, so the asm forces the address into a register. Without it, gcc's local-alloc would coalesce the address into s0 directly (since p is used across calls, it needs a callee-saved reg).

The target: v0 = address (short-lived, used for the copy) then s0 = address. So the C must have the address computed into a temp and then copied into p.

Hmm — so the real C would be something like:
```
u16 *pb = &D_800B99DC;   // pb is a temp
p = pb;                   // the copy
```
But gcc would coalesce pb into p (copy propagation) → one register.

The launder breaks the coalescing (the asm's output is a hard reg → the copy p = pb becomes a real copy `move s0,v0`).

Hmm! So this is the "copy" case. The C0505 catalog says: "A copy dies to cse's canon_reg or the local-alloc tie unless its destination changes MODE (the width)". Hmm.

To get `move s0,v0` from real C: we need a copy that gcc doesn't coalesce. gcc's local-alloc coalesces copies when possible (that's its job). A copy of a global address into a pseudo...

Options:
1. Make the copy's destination have a different mode (e.g. cast to a different pointer type)? "unless its destination changes MODE (the width)". E.g. `p = (u16 *)pb;` — the mode is the same (pointer). What about copying through a `char *`? Hmm.

2. Use the value twice: `p = pb; ... use pb again` → pb stays alive → 2 registers.

Hmm! Look at the target: v0 is used ONLY for the address materialization and the copy (insns 17-19), then v0 is reused at 22. So pb is short-lived.

3. What if the address is used in a way that requires a temp, e.g. `p = &D_800B99DC;` where p is a *parameter*? no.

4. The classic: make the copy have a different "allocno priority" so local-alloc doesn't coalesce. E.g. if p (the destination) is used across calls (needs an $s reg) and the source temp is short-lived, gcc's coalescing might still merge them... but the target shows they're NOT merged.

Hmm, why doesn't gcc coalesce in the target? Because the original game compiler is not gcc. gcc coalesces.

So we need to defeat gcc's copy coalescing. §145(b) again: "ANY second SET of a pseudo in the address's equivalence chain (in-place `p += K`, `p = r;` copy, or an asm re-tie) kills the fold".

Hmm, what if we give the address expression two sets so that the "copy" is not coalesced? E.g.:
```
u16 *pb = &D_800B99DC;
pb = pb;    // no
```

Alternatively: what if the address is loaded rather than computed? E.g. `p = *(u16 **)&D_800B99DC_ptr`? no.

Hmm, what about: the target's `lui v0; addiu v0,v0,0; move s0,v0`. This is what gcc produces when the address is materialized in a caller-saved register and then copied to a callee-saved one. gcc's local-alloc: when a value is live across a call, it goes to an $s reg; the "copy" from the computation reg to the $s reg.

Actually, gcc would produce exactly this if the address were computed by an expression whose result must be in a specific register, and then copied. Hmm, when does gcc emit `lui v0; addiu v0,v0,0; move s0,v0`? When the address expression's pseudo is a separate pseudo from p, and the copy p = addr can't be coalesced.

Coalescing is blocked when:
- The two pseudos have different live ranges/priorities? local-alloc's coalesce prefers to merge copies when the regs are compatible.
- When the source is used more than once (ref count > 1) — then the source can't be merged.

Hmm! So: if the address is used TWICE (once to copy into p, once elsewhere), the source stays in a register. E.g.:

```
u16 *pb = &D_800B99DC;
p = pb;
... use p ...
```
and pb used again later? In the target, is the address used again? insn 22 `lhu v0,0(s0)` uses s0. So the address is only used via s0 after the copy. So the source temp v0 dies right after the copy.

So in the target, the source pseudo is used exactly once (the copy) and still not coalesced. Hmm, that's the classic "copy not coalesced" case. gcc's local-alloc usually coalesces such copies. But here the copy is `p = pb` where pb = &GLOBAL.

Hmm, why wouldn't gcc coalesce? Because p is live across a call and pb is not: local-alloc's coalescing would move pb's value into p's reg... Actually local-alloc DOES coalesce copies when the source is dead after. The result would be `lui s0; addiu s0,s0,0` (no move). But the target has the move!

Unless... the move is not from a coalescing failure but from something else. Let me reconsider: maybe the original C was:
```
u16 *pb = &D_800B99DC;
p = pb;
```
where `pb` is a *global* pointer? Hmm.

Or maybe the original C computed the address TWICE, e.g.:
```
p = &D_800B99DC;
```
where the address is materialized in v0 because of a *volatile* or a different use.

Alternatively, maybe the original C was:
```
u16 *pb = &D_800B99DC;
*q = *pb & 0xFFF;    // pb used here
p = pb;              // and copied
```
Hmm.

Let's think about what gcc does with:
```
u16 *p = &D_800B99DC;
```
where p is used across calls: gcc's local-alloc would put p in an $s reg, and the address materialization (lui/addiu) would be done INTO that reg (coalesced) → `lui s0; addiu s0,s0,0`. That's the "coalesced straight into $s0" the comment mentions.

To get the extra `move s0,v0`, we need the address materialized in a caller-saved reg first.

When does gcc do that? If the address expression's pseudo is created by cse (a common subexpression) and then copied. E.g., if the address is used twice: once in a caller-saved context and once copied into p.

Hmm, in the target, v0 is used at insn 18-19 and then at 22 (`lhu v0,0(s0)`) — v0 is reused. So the address pseudo in v0 died at 19.

So: gcc materialized the address into v0 (a caller-saved reg) and copied it to s0. This is what happens when the copy cannot be coalesced.

What blocks coalescing in gcc 2.7.2's local-alloc? Looking at local-alloc.c's `coalesce_cost` / `collect_phi_args`... The relevant function: `local_alloc`'s `coalesce_cost` and the rule that a copy is not coalesced if the destination is a "hard" reg or if the source's mode differs.

Another classic blocker: **the source pseudo is a CSE pseudo with a different allocno** — hmm.

OK, alternative approach for this item: maybe there's a different lever-free spelling that yields `lui v0; addiu v0,v0,0; move s0,v0`.

What if the pointer is assigned from a *volatile* global pointer variable? no.

What if we use TWO pointer variables where one is used at a place that requires a caller-saved reg? Hmm.

What about the C0505 move "A copy dies to cse's canon_reg or the local-alloc tie unless its destination changes MODE (the width)". So changing the destination's MODE prevents the coalescing! E.g.:

```
u16 *pb = &D_800B99DC;
p = (u16 *)pb;    // same mode
```
Hmm, MODE of a pointer is always the same (Pmode). Unless we cast to a different pointer type — still Pmode.

Hmm, "destination changes MODE" might mean e.g. copying an s32 into a u16 (different modes). For pointers, no.

What if instead of a pointer copy, we use an integer copy?
```
s32 pb = (s32)&D_800B99DC;
p = (u16 *)pb;
```
Then the copy pb → p changes mode (SImode → Pmode)! And the integer pb would be materialized in v0 (`lui v0; addiu v0,v0,0`) and then `move s0,v0`!! That's exactly the target!

Hmm, but would gcc's `move s0,v0` be a plain move? Yes: `p = (u16 *)pb` where pb is an s32 in v0 → `move s0,v0` ✓ (both 32-bit).

But: would gcc keep pb in v0 (caller-saved) or fold it? pb is used once → it would be coalesced into the copy → `lui s0; addiu s0,s0,0` again. Hmm! Coalescing of a mode-converting copy isn't possible (different modes) — but gcc would then just materialize the address directly into s0 with lui/addiu (since the conversion is a no-op, gcc's simplify_rtx would fold (plus (hi)(lo)) → hmm).

Hmm, actually, for `p = (u16 *)(s32)&D_800B99DC`, gcc would fold the cast away: the address is Pmode; casting to s32 and back is a no-op → gcc folds it → same as before.

Hmm. But maybe not! In gcc 2.7.2, casting a pointer to an integer and back: the RTL would be a MEM with a specific mode... `(u16 *)(s32)X` where X is a symbol address: the conversion to SImode produces (mem (symbol_ref) SImode)? For an address cast, gcc creates a MEM with the address in a register: `(mem (plus (symbol_ref) (const 0)) SImode)`? Hmm, actually gcc's convert to integer mode of a pointer creates a "view" — the address is loaded as a word. But for a *symbol address* (not a memory location), gcc's `convert_to_mode` on a pointer produces a MEM of the address? Hmm, in RTL, an address isn't a value; casting a pointer to an integer yields (mem (addr) SImode) — a memory read! That would emit an actual load. ✗ (the target has no load).

Hmm. But gcc has an optimization: `pointer_mode` conversions of addresses are folded (fold_convert in fold-const.c handles (set (mem (symbol_ref) SImode)) → the constant address). Yes! fold-const.c's `fold_convert` has:
```
	    case INTEGER_MODE:
	      ...
	      /* Only do this if the mode is the same size... */
```
Hmm, there's a known gcc behavior: `(s32)&x` where x is a global → gcc folds it to the constant address only if the address fits in 32 bits (it does). Then `p = (u16 *)(s32)&D_800B99DC` → the constant → gcc materializes it. Then the copy might still be coalesced.

OK, this item is more involved. Let me set up the item dir and get the baseline score first, then experiment.

Let me check the item dir and the current score of orig.c (should be 0).

Actually, let me think about the structure more. The relevant part:

```
    i = 0;
    q = &D_801E87B2;
    {
        u16 *pb = &D_800B99DC;
        __asm__("" : "=r"(pb) : "0"(pb));
        p = pb;
    }
    r = &D_8018F078;
```

Target:
```
15 lui s3,0x0 ; HI16 D_801E87B2
16 addiu s3,s3,0
17 lui v0,0x0 ; HI16 D_800B99DC
18 addiu v0,v0,0
19 move s0,v0
20 lui s2,0x0 ; HI16 D_8018F078
21 addiu s2,s2,0
```

So s3 = &D_801E87B2, s0 = &D_800B99DC, s2 = &D_8018F078. And the D_800B99DC one is materialized via v0 + move.

Interesting: the other two (q and r) are materialized directly into their $s regs. So it's specifically the D_800B99DC one that goes through v0.

Why? Because in the original C, p (= &D_800B99DC) is used across calls (it's the loop's pointer, live across func_80049CAC etc.), while q and r are also live across calls... hmm, q is used in the loop (`*q = ...` and `func_80049CAC((s32)q - 2, ...)`) — also live across calls. Hmm.

So all three are live across calls. But two are materialized directly into $s regs and one goes through v0.

The difference: the asm-laundered pb. The asm forces the address into a register (v0, a caller-saved reg since the asm's output reg can be a caller-saved one — actually with "0" the input and output are the same reg, and gcc picks a reg for it: it picks v0 because the value is short-lived? no, the asm output is pb which is then copied to p).

So the asm forces a COPY: pb (in v0) → p (in s0). The copy is not coalesced because the asm output is a hard reg.

Without the asm: `p = &D_800B99DC` → coalesced into s0.

So we need a copy that gcc won't coalesce. Options:
(a) Make the source have 2+ uses so it can't be merged. E.g.:
```
u16 *pb = &D_800B99DC;
p = pb;
... and use pb somewhere else ...
```
But the target shows v0 (the source) is used ONLY for the copy (v0 is immediately reused at 22). So the source must be dead after the copy. If the source had 2 uses, gcc would keep it in a reg — but it could still be v0 if the second use is early. Hmm, but the target's v0 dies at 19.

Hmm, so the source is used once and still not coalesced. gcc's local-alloc coalescing: a copy `p = pb` where pb is dead after the copy → local-alloc would prefer to merge (coalesce) them, giving `lui s0; addiu s0,s0,0`.

Unless the copy is not recognized as a copy at the RTL level! E.g., if the copy goes through a MEM (store+load) or through a conversion.

Hmm. OR: the coalescing is prevented by the ALLOCNO PRIORITY: local-alloc's coalesce_cost considers priorities. But typically a dead source is merged.

Hmm hmm. What if the source pb is a **global** variable (not a local)? Then `p = g;` where g is a global holding the address → the copy would be `lw` not `move`. ✗

What if pb is a local that is ALSO used later, but in a way that lets gcc reuse v0? E.g. if pb is used again much later, gcc would keep it in a callee-saved reg (since it's live across calls) → s0-ish → then the copy p = pb... hmm, then p and pb would both be $s regs.

OK, let me think about the "asm-free" way to get `lui v0; addiu v0,v0,0; move s0,v0`:
- A "volatile" copy? no.
- A copy through a union? no.
- A copy where the destination is used in a context that forces a different reg class?

Hmm, what about: **the destination p is assigned in a place where gcc has a register constraint**? no.

What about the C0505 "statement order" move: if `p = pb;` is moved to a different position, the coalescing might change? Hmm.

What about the possibility that the address is materialized by a DIFFERENT expression that gcc can't fold into the destination — e.g., an address computed via a pointer arithmetic on a global: `p = (u16 *)&D_800B99DC + 0;`? Folded.

Hmm, what if the address is taken from a global POINTER variable: `p = D_800B99DC_ptr;` → a `lw` load. ✗ (the target has lui/addiu).

What if we make the address come from a **struct member of a global**: `p = &((struct S *)D_80000000)->field;` — no.

OK: what about the "**second set**" trick on the address pseudo (§145(b))? If the address expression has 2 sets, then the copy p = addr can't be coalesced (because the source pseudo has 2 sets → it's not a simple copy).

Hmm, e.g.:
```
u16 *pb = &D_800B99DC;
p = pb;
```
The address expression (symbol_ref D_800B99DC) has 1 set. If we add another set of the address, e.g.:
```
u16 *pb = &D_800B99DC;
p = pb;
pb = &D_800B99DC;   // hmm, identity
```

Hmm.

Let me look at this from a different angle: what if the real C used a *different* form for p's assignment, e.g. p is assigned inside the loop or p is a parameter?

Hmm, let me look at what the def looks like in the src and how the launder was introduced. The comment says: "loop.md L4 preheader-copy: the target materializes &D_800B99DC into $v0 and then `addu $s0,$v0,$zero`. A plain `p = &D_800B99DC` is coalesced straight into $s0. The zero-byte re-tie fence (cookbook §34) keeps the two pseudos apart, so the short-lived one lands in $v0 and the call-crossing one in $s0 = the extra move."

So the target's `move s0,v0` (they call it addu) is a COPY. And the comment says a plain `p = &D_800B99DC` is coalesced straight into s0.

So the question: how to get a non-coalesced copy in real C?

**IDEA**: What if p is not assigned from a temp but the temp is assigned FROM p, and the roles are reversed? I.e. maybe the original C had:
```
u16 *pb = &D_800B99DC;
p = pb;
```
Hmm, same.

**IDEA**: What if the destination is a *different* pointer type and the copy is a MODE change? Pointers are all Pmode.

**IDEA**: What if the copy is a "bit-field" or a struct assignment? no.

**IDEA (promising!)**: What if the copy's SOURCE is used again LATER but in a way that dies quickly? Hmm.

**IDEA (promising!)**: gcc's local-alloc doesn't coalesce a copy when the destination pseudo is in a different basic block or has a different "live range" that would extend the source's range across a call. AH — THAT'S IT!

The source pb (v0) is live from its definition to the copy. If the copy is IMMEDIATELY after, the source's range is short (no call inside) → coalescing would extend p's live range back to pb's definition — that's fine and cheap... but gcc's coalescing might not be worth it.

Hmm, but actually, the real reason might be simpler: **the address pseudo (the lui/addiu computation) is a separate pseudo from p**, and the lui/addiu is a "const" pseudo (D_800B99DC is a global symbol → the address is a `symbol_ref` → gcc materializes it with lui/addiu into a reg). If p = pb where pb = symbol_ref, then the copy `p = pb` coalesces pb and p, giving `lui s0; addiu s0,s0,0`.

To break it: make the source pb have TWO sets. Then p = pb is a copy from a 2-set pseudo → local-alloc can't coalesce a pseudo with 2 sets into another (the "reg_equiv" chain would be broken).

So: `pb = &D_800B99DC;` ... `pb = something;` ... `p = pb;`?? That changes the value.

Hmm, what if:
```
u16 *pb = &D_800B99DC;
p = pb;
```
→ coalesced.

```
u16 *pb = &D_800B99DC;
pb = pb;    // identity, second set
p = pb;
```
Hmm, gcc would fold pb = pb (no-op) — actually the frontend would keep it as a gimple assignment, and the RTL would have 2 sets of pb. Then the copy p = pb might not coalesce. But that's an identity statement (banned-ish).

Hmm. But hold on — what about the "dead-reset" trick in reverse? Here we want to PREVENT a coalescing.

Let me think about §145(b) again: "ANY second SET of a pseudo in the address's equivalence chain (in-place `p += K`, §145(b)'s `p = r;` copy, or an asm re-tie) kills the fold".

Hmm, so a copy `p = r;` gives p a second set. That's the direction we have (p = pb).

OK let me think about what the ORIGINAL GAME CODE might have been. The target has `lui v0; addiu v0,v0,0; move s0,v0`. In MIPS asm from an old compiler, this pattern arises when the address is computed into a temp and then copied to a callee-saved reg. E.g. the original C might be:

```
u16 *p = &D_800B99DC;   // p is a local
```
compiled by an old gcc: the address is put in a temp (because the symbol's address needs lui/addiu) and then moved to the allocated reg for p. Because the OLD compiler (or the original one) didn't coalesce.

So the target reflects a compiler that doesn't coalesce copies of symbol addresses. Modern gcc coalesces.

Hmm, so maybe this item is genuinely hard. But wait — the def has a launder, and we must remove it while keeping score 0.

Let me think about what else could produce the v0+s0 pattern.

**IDEA**: What if the address is used TWICE in the C, once as `p` (long-lived) and once elsewhere? Then the source pseudo has 2 uses and can't be coalesced into p... but then the source needs a register that's live across calls → it'd be an $s reg, and the copy would be `move s0,sX` — giving TWO $s regs. Hmm, the target has s0 = the pointer and v0 = a short-lived copy. If the source had 2 uses, the target would show the source in an $s reg.

Hmm, unless the second use of the source is BEFORE the copy and short-lived... e.g.:

```
u16 *pb = &D_800B99DC;
x = *pb;          // first use
p = pb;           // copy
```
Hmm, but the target has `lhu v0,0(s0)` at 22 — the load happens through s0, not through a separate v0.

Hmm OK.

**ANOTHER IDEA**: what if p's assignment is `p = (u16 *)((u8 *)&D_800B99DC + 0);`? no.

**IDEA**: what if the destination p is declared as a *different type* such that gcc treats the copy as a no-op conversion but still allocates separately? Hmm.

**IDEA (promising!)**: What if `p` is assigned from a **volatile-qualified** something? no.

**IDEA (promising!)**: What if we introduce the copy through a *struct assignment* or an array element? e.g. `tab[0] = pb;` → memory. ✗

**IDEA**: What if the copy is `p = pb;` where pb is a **parameter** of an inlined... no.

Hmm. Let me look at the problem from the "what does gcc 2.7.2's local-alloc do" angle. Actually, maybe the key is not the copy at all! Let me re-read the target:

```
17 lui v0,0x0   ; HI16 D_800B99DC
18 addiu v0,v0,0
19 move s0,v0
```

What if this is NOT a copy but the result of gcc's handling of the ADDRESS of a global where the address is computed in a temp because of the `lui`/`addiu` pair needing a register pair? On MIPS, `lui v0, %hi(D_800B99DC); addiu v0,v0,%lo(D_800B99DC)` — a single register. gcc's "mips_split_symbol" or the address materialization: for a global symbol address, gcc generates `lui reg, %hi(sym); addiu reg, reg, %lo(sym)` into ONE reg. So there's no inherent need for two regs.

BUT: gcc 2.7.2's mips backend has "mips_avoid_branch_divide" / the "address_cost" thing... Hmm. Also, there's the "reload" issue: the %hi/%lo pair must be in the same register, and reload might need a scratch.

Hmm, actually! Here's a thought: the OTHER two globals (D_801E87B2 → s3, D_8018F078 → s2) are materialized directly into their $s regs: `lui s3; addiu s3,s3,0`. So the same pattern works fine without a v0 temp. The only difference for D_800B99DC is the extra `move s0,v0` — i.e., the copy.

So the target HAS a copy for that one. The original C must have had a copy that the original compiler didn't coalesce.

Since gcc coalesces, how do we PREVENT coalescing in gcc 2.7.2? local-alloc's `coalesce_cost`:
```
  /* Unless we have a register, ... */
  if (reg != 0) ...
  /* This is a copy between two pseudos: ... */
  ...
  cost = ...;
  if (COSTS_TERSE) ...
```
and there's the rule in local-alloc.c:
```
      /* Don't attempt to coalesce a pseudo with a hard reg if ... */
```
and:
```
  /* Handle the case of a copy between two different modes: ... */
```

Also there's a well-known blocker: **a copy whose source is a "CONST" pseudo**? Hmm.

Another known blocker: if the copy's destination is used in a context where the reg is "call-clobbered"... no.

Hmm, what about the classic: **local-alloc will not coalesce a copy if the source is a "reg_equiv" chain member with multiple sets**, or if the source's live range crosses a call (then it'd have to be in an $s reg and the dest too).

WAIT!!! What if the SOURCE (pb) is live across a call, and the DESTINATION (p) is a different thing? Then the copy `p = pb` is a copy from an $s reg to another $s reg → `move s0,s1` — but the target's move is from v0.

Hmm, v0 is a caller-saved reg, so the source's live range does NOT cross a call. So the source is short-lived: defined at 17, copied at 19, dead.

So gcc has: source pb (short range, no calls inside) → copy → dest p (long range, crosses calls).

gcc's local-alloc coalescing: it would try to merge pb and p. Merging means p's reg = the reg that holds the address, and the address materialization (lui/addiu) goes directly into that reg. Since p needs an $s reg (crosses calls) and the materialization can be done into any reg, the merge is natural → `lui s0; addiu s0,s0,0`.

Why would gcc NOT merge? Because of the **live range crossing a call**: if pb and p are merged, then the value (the address) is live from pb's definition across the call — fine, it's in an $s reg. That's exactly what the "coalesced" version does. So gcc merges.

To prevent the merge, we need the source to be live across a call (so it must be in an $s reg) while the dest is a different $s reg — but then the source would be an $s reg, not v0. ✗

OR we need the source to have 2+ sets (so it's not a simple copy) — but then the source's live range extends, and the value at the copy is the SECOND set.

Hmm! What if the source is set TWICE, with the second set right before the copy?

```
u16 *pb = &D_800B99DC;    // set 1 (dead by then?)
...
p = pb;
```
Hmm.

OK, radically different: what if we don't need a copy at all — what if we can produce the v0+move pattern from an expression that gcc computes into a temp? For example, an expression like `p = (u16 *)((u32)&D_800B99DC)`? Folded.

What about `p = &D_800B99DC;` where D_800B99DC is declared as an ARRAY of u16 and we take the address of an element: `p = &D_800B99DC[0];` → same.

What if the address is of a *struct field* of a global: `p = &((S *)0x80000000)->f;` — that would be a computed constant, not a symbol reloc. The target has HI16/LO16 D_800B99DC relocs, so the expression must be exactly &D_800B99DC.

Hmm! What if we write `p = (u16 *)&D_800B99DC;` vs `p = &D_800B99DC;`? Same.

OK. What about the "**init at decl**" move: `u16 *p = &D_800B99DC;` instead of a separate assignment? Then there's no copy at all → `lui s0; addiu s0,s0,0` (no move). ✗ (we need the move).

Hmm, so we NEED a copy that gcc won't coalesce.

**AH WAIT — IDEA!** What if the copy is a copy of a *value that is not a constant address* but a computed pointer, e.g.:

```
u16 *pb = &D_800B99DC;
p = pb;
```
The address is a symbol_ref → gcc's copy is `p = symbol_ref` → coalesced.

But what if p's value is not directly the symbol but requires an "addiu"? e.g.
```
u16 *pb = &D_800B99DC;
p = pb - 0;
```
no.

**IDEA**: what if the copy is done through a `char *` cast — a MODE change! Pointer → pointer is same mode. But what about copying into an *integer* variable and then to the pointer? The int→pointer conversion in gcc creates a MEM (a load) or a register move? For a *pseudo* holding a pointer converted to SImode: gcc's convert_to_mode on a pointer → (mem (addr) SImode) — hmm, that IS a load, but for a register value gcc uses a "view" with a different mode, and on MIPS a register is 32 bits so the conversion is free (same size) → the RTL is just the same reg with a different mode → the copy is `move s0,v0` and the materialization is `lui v0; addiu v0,v0,0`!!

Hmm! Interesting. But gcc's fold would simplify the conversion back.

Hmm, but actually there's a subtlety: `(s32)&D_800B99DC` on a 32-bit target: the pointer is 32 bits, so the conversion is a no-op and gcc folds it → the address is still a symbol_ref. But the *assignment* `s32 pb = (s32)&D_800B99DC;` makes pb an SImode pseudo whose value is a symbol_ref address. Then `p = (u16 *)pb;` → converting back to Pmode. gcc's fold: (convert (symbol_ref)) → hmm, the conversion of an address to SImode is NOT a no-op in RTL: an address is not a value. gcc represents it as (mem (symbol_ref) SImode)? No — for a *global symbol*, the address is (symbol_ref D_800B99DC) and the "value" of that address in SImode would be a load — but gcc has fold-const's `fold_convert`:
```
	case INTEGER_MODE:
	  if (GET_CODE (x) == MEM && GET_MODE (x) == mode) ...
	  ...
	  /* Only do this if the address is a constant... */
```
Hmm, in gcc's fold-const.c, `fold_convert` for pointer→integer:
```
	    case INTEGER_MODE:
	      if (POINTER_SIZE == GET_MODE_SIZE (mode)
		  && (GET_MODE (x) == mode
		      || GET_MODE (x) == VOIDmode ...))
		{
		  /* ... */
		  if (GET_CODE (x) == SYMBOL_REF || GET_CODE(x) == LABEL_REF ...)
		    return x;   /* the address IS the value */
		}
```
Hmm, actually YES: gcc's fold-const has:
```
	case INTEGER_MODE:
	  if (POINTER_SIZE == GET_MODE_SIZE (mode)
	      && ...)
	    {
	      rtx addr = XEXP (x);
	      ...
	      if (GET_CODE (x) == MEM ...)
	      ...
	    }
```
There's a known gcc behavior: `(s32)&global` yields the address as an integer constant on 32-bit targets (gcc folds it to a CONST). So the s32 pb would hold a CONSTANT (the address 0x800B99DC) → then `p = (u16 *)pb` → the constant address → gcc would emit lui/addiu into p's reg → coalesced, and no v0. ✗

Hmm.

OK, let me get empirical. Let me set up the item and try a few things. But first, let me check the baseline: does the current src score 0? And what does the score look like without the launder?

Let me create the item dir files (tu, fn, kinds exist already). Let me check.

Let me write a candidate without the launder and score it to see the residual.

Candidate x1: remove the whole `{ u16 *pb = ...; asm; p = pb; }` block → `p = &D_800B99DC;`.

Let me write and score.

---
ts: 2026-10-21T23:52:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_OKMWL6VOnZPk0471qIQN
---
Same. gcc still coalesces.

Time check: I need to be efficient. Let me think about the gcc 2.7.2 mechanism for real, using the reference source which is available. Let me grep local-alloc.c for the coalescing decision. This is worth ~2 tool calls.

In gcc 2.7.2's local-alloc.c, the function `coalesce_cost` and where copies get coalesced. Let me grep for "coalesce" in the reference tree.

Actually, the relevant mechanism might be in `global.c`'s `set_preference` or in local-alloc's `find_reg`:

```c
/* Return a hardware register for a pseudo... */
static int
find_reg (reg, regno)
```
and:
```c
	  /* If this is a copy, ... */
```

Hmm. But maybe the real blocker is in **cse.c's `canon_reg`**: the copy `p = pb` is forwarded when pb's value is "simple". cse's canon_reg:

```c
rtx
canon_reg (reg, x)
{
  ...
  /* If we have a copy of a constant, ... */
  ...
  if (GET_CODE (x) == REG && GET_MODE (x) == GET_MODE (reg) ...)
```

Hmm.

**ANOTHER APPROACH — use the gcc reference source to find how to get a non-coalesced copy.** In gcc 2.7.2's local-alloc.c there's a well-known comment about "the copy is not coalesced if the source is not a simple copy" — hmm.

Honestly, let me look at the C0037 "giv-init fence" note: `asm("":"=r"(ba):"0"(ba)); dst = ba;` — the fence is an asm. The def's comment says the agent used the "zero-byte re-tie fence (cookbook §34)".

So the project's own answer for this shape is the asm fence. And the question is whether a real-C alternative exists.

Let me look at the "giv-init" mechanism: `loop.c:5556 if (reg != result) emit_move_insn` — the giv-init move exists when the init is NOT coalesced. In the target, `move s0,v0` is a GIV INIT! The doc row 10 says: "the giv-init `addu dst,base,$zero` exists only when the init is not coalesced (§34 fence)".

**A GIV!** So p is a GIV (generalized induction variable) in loop.c's terms — i.e., p is a pointer that's loop-invariant but assigned in a way loop.c treats as a giv. Hmm, or q/r are givs.

Hmm: "Each separately-incremented pointer is a biv". Our p is not incremented.

Hmm, but loop.c's giv-init: for a "derived" giv (like `p = base + 0`), loop.c creates the init with `emit_iv_add_mult` and then `if (reg != result) emit_move_insn` — a copy!

So: if p is a DERIVED giv (p = base + 0 where base is something), loop.c creates the init as a copy! And the "§34 fence" keeps the two apart.

So the real-C way: make p a derived giv! E.g., p = q + something? Hmm, but the address must be &D_800B99DC.

Hmm, what if p is derived from ANOTHER pointer: e.g. `p = pb + 0`? That's a derived giv: base = pb, offset 0. loop.c would then create the giv init as `p = pb + 0` → with a copy `move s0,v0` if not coalesced!

Hmm, but `pb + 0` folds to pb.

What if p = pb + 0 where pb is a pointer variable? The giv would be "derived" with a constant offset 0. loop.c's `emit_iv_add_mult` would emit `p = pb` (a move) if reg != result.

Hmm, interesting! But is p a loop-carried value in a loop? Our p is assigned in the preheader, not in the loop. So loop.c wouldn't treat it as a giv.

Hmm, unless p is assigned INSIDE the loop! Then loop.c's giv machinery kicks in: p = &D_800B99DC inside the loop is a loop-invariant assignment → loop.c's "hoist invariant" or "create a giv".

And the "preheader copy" in the def's comment matches: the giv init is emitted in the preheader, with a copy.

So: put `p = &D_800B99DC;` INSIDE the loop! And the preheader uses of p (the `*p & 1` load at 22) would then be... hmm, they'd be a use of an uninitialized p. Unless the preheader use is also inside the loop.

Let me look at the target's preheader again: insn 22 `lhu v0,0(s0)` — the `*p & 1`. If the `*p&1` statement is inside the loop (invariant → hoisted to the preheader by loop.c), the hoisted version would use the giv's register s0. ✓

And the ORDER: the preheader would contain: q's materialization (from the source, before the loop), then the hoisted stuff (p's giv init, the *p&1, D_801E86C0 = D_800B99D8) in the loop-body order, then r's materialization (source, before the loop)?

Target order: s3 (q), v0/s0 (p), s2 (r), *p&1, D_800B99D8 load, store.

If q and r are assigned before the loop (source order q, r) and p inside the loop, the preheader would be: q, r, [hoisted p, *p&1, D_801E86C0] → order q, r, p — but the target has q, p, r. ✗

Unless r is also inside the loop! Then: q (before), [hoisted p, *p&1, D_801E86C0, r] → order q, p, *p&1, ..., r. Target: q, p, r, *p&1. ✗ (r before *p&1).

Hmm! Target order: q, p, r, then *p&1, then D_800B99D8.

So p and r are both materialized before the *p&1. If p, r were both hoisted from the loop, their order would follow the loop body order: p, r, *p&1, D_801E86C0 — matching the target IF the loop body order is: p = &D_800B99DC; r = &D_8018F078; D_801E86BC = (*p & 1) + 3; D_801E86C0 = D_800B99D8; ... and q = &D_801E87B2 is BEFORE the loop.

Hmm! But in the current def, the order is q, p, r, then *p&1, D_801E86C0 — the SAME order. So if I move p, r, *p&1, D_801E86C0 into the loop body (keeping q before the loop), the hoisted order would be p, r, *p&1, D_801E86C0 ✓ matching the target's preheader order (q, p, r, *p&1, ...).

And crucially, loop.c's giv/hoist machinery might create the COPY for p (a giv init) but not for r! Why? Because p is "derived" and r isn't? Hmm, both are simple address assignments.

Hmm, but maybe: the copy for p comes from the fact that p is used in the preheader (the *p&1 load, hoisted) — no...

OK, let me just TRY it: v3 = move `p = &D_800B99DC;`, `r = &D_8018F078;`, `D_801E86BC = (*p & 1) + 3;`, `D_801E86C0 = D_800B99D8;` into the loop body, keeping `q = &D_801E87B2;` before the loop.

Hmm, wait: but the hoisting of `*p & 1` requires p to be set. If p's assignment is in the loop and gets hoisted, fine.

But hmm, there's a subtlety: loop.c might not hoist `D_801E86BC = (*p & 1) + 3;` (a store to a global — loop.c's invariant hoisting does handle stores to globals? It might, since the store is invariant... but a store to a global that might alias the loop's stores — gcc 2.7.2 has no TBAA, so loop.c might refuse to hoist the store. Hmm, but the store to D_801E86BC and the loop's store to *p and *q and *r — those are different addresses, but without TBAA gcc can't prove it. Hmm, but the target has it in the preheader!)

Hmm, so maybe the *p&1 store was NOT hoisted; it was in the preheader in the source. And the p materialization + copy is the "preheader copy" from loop.c of the p assignment... but p is assigned in the preheader in the source.

ARGH.

Hmm, hold on. Let me reconsider: what if the p assignment is in the loop AND the *p&1 store is in the preheader? Then p's value is used before the assignment — the C would be wrong but gcc would compile it (with p uninitialized in the preheader). Hmm, but then the preheader's `lhu v0,0(s0)` would use an undefined p → gcc would allocate p's reg... The target's preheader load uses s0 which is also the loop's p. If p is assigned in the loop, then in the preheader p is undefined; gcc would use a different reg or the same. Hmm, that would probably NOT match (the target has s0 in both).

Hmm, hmm. But actually — wait! What if the C is:

```
    p = &D_800B99DC;     /* preheader */
    D_801E86BC = (*p & 1) + 3;
    D_801E86C0 = D_800B99D8;
    for (...) { ... }
```
and the copy `move s0,v0` comes from loop.c's "copy_movables"/"hoist" of the loop's live-in values? Hmm, loop.c's `loop.c:1652/1810 move_movables hoist-at-loop_start` — from §34's note: "an explicit `u32 pv = uVar1;` before `p = base;` replaces loop.c's `move_movables` hoist-at-loop_start (`loop.c:1652/1810`) with source order".

**move_movables!** loop.c's `move_movables` hoists moves to the loop start! Hmm.

OK, enough theory. EMPIRICAL: let me try 3 variants and score them. I'll write them one at a time.

v3: p, r, *p&1, D_801E86C0 assignments moved inside the loop (q stays before).

Let me write v3.

Actually hmm, wait. Before that, let me reconsider the ordering constraint. The target's preheader order: q(s3), p(v0,s0), r(s2), *p&1, D_800B99D8.

With v3 (p, r, *p&1, D_801E86C0 inside the loop): loop.c hoists the invariant statements in body order: p, r, *p&1, D_801E86C0 → preheader: q, p, r, *p&1, D_801E86C0 ✓ ORDER MATCHES.

And maybe the hoisted p assignment becomes a giv init with a copy.

But will loop.c hoist the STORE `D_801E86BC = (*p & 1) + 3;`? The loop body stores to *q, *p, *r, and to globals (D_801E86C0, D_8018F076). Without TBAA, gcc 2.7.2's loop.c invariant hoisting: it checks whether the store's target could alias the loop's memory writes. If it can't prove non-aliasing, it won't hoist. Hmm. But the *q = *p & 0xFFF store and *p = *p + c0 store are in the loop. The hoisted store to D_801E86BC — gcc would need to prove it doesn't alias. It probably CAN'T → no hoisting → the store stays in the loop. ✗

So v3 would put the *p&1 store in the loop, mismatching the target.

Hmm! So the *p&1 store is in the preheader in the source, and p is assigned in the preheader.

OK so what if ONLY the p assignment is inside the loop?
```
    q = &D_801E87B2;
    r = &D_8018F078;      ← hmm, order
    D_801E86BC = (*p & 1) + 3;   ← uses p before the loop: undefined!
```
✗ semantics.

Hmm, so p must be assigned before the *p&1 use.

OK, so within the preheader, p is assigned and used. The copy must come from gcc's handling.

Let me now consider: what if the p assignment is a "derived" giv because p is derived from ANOTHER pointer? E.g.:

```
    u16 *pb = &D_800B99DC;
    p = pb;
```
That's the copy (coalesced).

What if instead: `p = &D_800B99DC;` where the address is derived from a global POINTER VARIABLE? ✗ (load).

Hmm, hmm. What about: the target's `lui v0; addiu v0,v0,0; move s0,v0` — what if `v0` is not a copy source but the RESULT of the address computation in a "reload scratch"? In gcc 2.7.2's reload.c, when a pseudo's reg_equiv is a symbol_ref AND the pseudo is allocated a hard reg, reload emits the address into the hard reg directly. BUT if the pseudo's reg_equiv is a symbol_ref and the pseudo is a "CONST" pseudo used in a context that requires a specific hard reg...

AH WAIT!!! Here's a REAL gcc-2.7.2 mechanism: **reload's "reload_in_non_pseudo_reg"**! When a pseudo's value is needed in a HARD register (e.g. because the pseudo is used as a call argument and gcc wants it in $a0), reload emits the materialization into a scratch reg and then moves it to the hard reg.

In the target, is &D_800B99DC passed to a call? NO. Hmm.

But hold on — what about the "3-qty sort bug" and local-alloc's register choice? Hmm.

OK, radical simplification: let me look at the gcc-2.7.2 source for how a symbol address gets into a pseudo. Actually, let me try the DIRECT experiment: what if p's address is used TWICE in a way that requires two registers — e.g. p is used in the preheader (before any call) and p is live across calls. gcc would allocate p to an $s reg (s0) — and the preheader use would read s0. ✓ (target: `lhu v0,0(s0)`).

The materialization `lui v0; addiu v0,v0,0; move s0,v0` vs `lui s0; addiu s0,s0,0` — the difference is just WHERE the address is first built. In gcc, when a CONST pseudo (reg_equiv = symbol_ref) is allocated s0, reload emits the lui/addiu INTO s0. To get the scratch+move, the pseudo's reg_equiv must be a PSEUDO (not a symbol_ref) — i.e., a copy.

So: we need p's reg_equiv to be a pseudo. That means the address must be computed into a pseudo and then copied. In C, that's `p = pb;` where pb is a pseudo holding the address. And cse forwards it (canon_reg) making p's reg_equiv = the symbol_ref.

**To block canon_reg's forwarding, the source pseudo must have MORE THAN ONE SET** (canon_reg only forwards a reg with a single set — "if the reg has only one set in the block").

So: pb must have 2 sets, and the SECOND set is the one copied to p. And the first set must not be dead-folded.

Hmm, so:
```
u16 *pb;
pb = &D_800B99DC;     /* set 1 */
pb = <something else>;  /* set 2 — must have the same value! */
p = pb;
```
The 2nd set must yield the same address but be a different expression → an "identity address spelling" (banned?) Hmm.

ALTERNATIVELY: the 2nd set is a copy: `pb = pb;`? Dead/identity.

Hmm, what if set 1 is used somewhere? Like:
```
u16 *pb;
pb = &D_800B99DC;
D_801E86BC = (*pb & 1) + 3;    /* use of set 1 — but this is a load, and the load's address is (mem (reg)) after find_best_addr... */
p = pb;                        /* the copy of set 1 */
```
That's v2, which didn't work. Hmm — but in v2, cse's canon_reg could still forward because pb's value is used in the MEM's address... hmm, find_best_addr would have replaced the MEM's address with a REG — which reg? If pb's reg_equiv = symbol_ref, then find_best_addr looks for a reg holding the address...

Hmm, in v2, the result was still `lui s0; addiu s0,s0,0` — so pb and p were both coalesced into s0 and the load used s0 (as in the target: `lhu v0,0(s0)` ✓). But no copy.

So cse's canon_reg DID forward pb's value to p (pb has 1 set). To block it, pb needs 2 sets.

So the question is: can I write a C where pb has 2 sets, the second set's value is the same address, and the assignment is not an "identity"?

Hmm! What about this: pb is assigned the address, then pb is assigned a DIFFERENT address, and then the copy uses the second? No — the value must be &D_800B99DC.

Hmm, what if the copy is `p = pb` and pb's 2 sets are:
set1: `pb = &D_800B99DC;`
set2: `pb = &D_800B99DC;` — identity.

OR: the "2 sets" could come from a *loop*! If the assignment is inside a loop, the pseudo has 2 sets (one per iteration)? Hmm, in RTL, a loop body assignment is ONE set in the loop body (the loop is a single BB in the RTL). Hmm, but loop.c's "copy_movables"...

OK OK. Let me now consider: maybe the "2 sets" can come from a DIFFERENT pseudo in the chain. §145(b): "ANY second SET of a pseudo in the address's equivalence chain (in-place `p += K`, §145(b)'s `p = r;` copy, or an asm re-tie) kills the fold".

Hmm, "kills the FOLD" — different thing.

Let me try yet another thing: what if the C is
```
u16 *pb = &D_800B99DC;
u16 *pc = pb;      /* copy 1 */
p = pc;            /* copy 2 */
```
Two copies in a chain — cse forwards both. ✗

What about a copy through a DIFFERENT pointer type: `p = (u16 *)pb;` — same mode.

What about copying into a `s32` (integer) and back:
```
s32 ib = (s32)pb;   /* mode change! */
p = (u16 *)ib;
```
The mode change might block the forwarding! And on MIPS, int→pointer is a no-op (same size) → the copy would be `move s0,v0`!! And the address materialization `lui v0; addiu v0,v0,0` into v0!! ✓✓✓

But: (s32)pb — pb is a pointer to a global; casting a pointer to s32 gives the address as an integer. gcc's fold-const would fold `(s32)&D_800B99DC` to a CONST (the address 0x800B99DC) since the target is 32-bit! Then ib = 0x800B99DC (a constant) and p = (u16 *)ib → the constant address → gcc materializes it → `lui s0; addiu s0,s0,0` (coalesced, no copy). ✗ Hmm, and the reloc would still be HI16/LO16 D_800B99DC? No! A folded constant would be `li`/`lui` with an absolute constant, not a symbol reloc. The target has the D_800B99DC reloc. ✗

Hmm. Unless gcc doesn't fold it.

What about a mode change to a SMALLER int: `u16 ib = (u16)pb;` — that truncates the address. ✗

Hmm.

What about the destination changing mode in the OTHER direction: the source is an int and the destination a pointer:
```
u16 *p;
p = (u16 *)0;   /* no */
```

OK, what about a copy where the SOURCE is a `void *`? Same mode.

Hmm, what about a copy through a struct member? e.g.
```
struct { u16 *p; } s;
s.p = pb;   /* a MEM store */
p = s.p;    /* a MEM load */
```
→ memory traffic. ✗

Hmm.

OK, let me try the "2 sets via a loop-invariant" idea in a DIFFERENT form: what if p is assigned the address TWICE with the two assignments being *different expressions* that yield the same address but where one is a *pointer arithmetic*:

```
pb = &D_800B99DC;
pb = pb + 0;      /* hmm, folds */
```

Or:
```
pb = (u16 *)((u8 *)&D_800B99DC + 0);
```
folds.

OK. Let me step back and consider the possibility that the copy is NOT the issue, but the REGISTER is: maybe the target's `lui v0; addiu v0,v0,0; move s0,v0` is what gcc produces when the symbol address is needed as a "base" for a MEM (find_best_addr) AND the pseudo holding it is live across calls.

In our x1/v2, gcc produced `lui s0; addiu s0,s0,0` — the address materialized directly in s0. In the target, the address is materialized in v0 and copied to s0.

Difference: in the target, the address pseudo's reg_equiv is a symbol_ref and the pseudo is s0 → gcc's reload would emit lui/addiu into s0 directly. So the target's shape implies the pseudo's value came from ANOTHER pseudo (a copy).

=> We need a non-coalesced copy. And in gcc, the classic non-coalesced copy is when the SOURCE is a hard reg — i.e. an asm. OR when the source is a pseudo whose value is a "CONST" that...

hmm, hold on: what about a copy from a pseudo that is a CALL RESULT? no.

What about a copy from a pseudo whose reg_equiv is a symbol_ref but which is ALSO used in a MEM (so find_best_addr gave it a reg)? In v2, pb was used in the MEM `*pb` — the MEM's address became (mem (reg)) where the reg is... hmm, and the result was still direct.

Hmm, in v2 the load was `lhu v0,0(s0)`? Let me check the actual diff: the diff showed only 3 hunks, so yes, everything else matched, including the load at 22. So in v2, pb and p both became s0, and the load used s0. So cse forwarded.

OK. Let me try ONE more idea, the "loop-invariant inside the loop" (v3) since the def's comment explicitly mentions loop.md L4 preheader-copy. If the p assignment is inside the loop, loop.c's machinery (which the def's author clearly knew about) would create the preheader copy.

But the *p&1 use is in the preheader... Hmm, unless the *p&1 use is ALSO in the loop and gets hoisted — and the store's hoisting might work if gcc can prove non-aliasing. Hmm, `D_801E86BC` is a global (s32) and the loop writes `*p` (u16), `*q` (u16), `*r` (s16), `D_801E86C0` (global s32), `D_8018F076` (global u16). Without TBAA, gcc 2.7.2's loop.c won't hoist a store to a global if the loop writes memory. Hmm, but maybe it will if the store is to a global and the loop's writes are... no, it can't prove it.

Hmm, BUT: gcc 2.7.2's loop.c DOES hoist loop-invariant statements including stores to globals in some cases (it checks `cse->` alias info... in 2.7.2 there's no TBAA, so loop.c's `may_alias` analysis is very conservative).

Hmm, so the *p&1 store is likely in the preheader in the source.

So: p is assigned in the preheader, used in the preheader, and the copy is a mystery.

Hmm, hold on!!! What if p's assignment in the source is NOT `p = &D_800B99DC;` but something like:

```
p = &D_800B99DC;
```
where the compiler needs to materialize the address ONCE for the preheader load and once for the loop's p (which is a different value in gcc's view because the load's address is a MEM (mem (symbol_ref)) and the loop's p is (plus (symbol_ref) (const 0)))?

In the target: `lhu v0,0(s0)` — the load's base is s0, the same reg as p. So they're the same value.

OK, let me just try v3 and a couple of others quickly, and if they fail, declare a WALL for this item with the mechanism evidence (which is valuable: "the target's `move s0,v0` is a non-coalesced copy of a CONST address pseudo; gcc-2.7.2's cse canon_reg forwards the copy, so no lever-free C spelling was found in N tries").

Actually, WAIT. One more idea that I think is quite promising: **the "3-qty sort bug"!** §34: "For a block with ≤3 local register quantities, the unrolled comparison switch compares fixed qty numbers but exchanges order slots — when pri(q1) is highest the third compare re-fires and undoes the first swap, so 3-qty blocks allocate in qty-CREATION order, not density order."

Hmm! That's about ORDER, but our issue is a COPY. Hmm. But hold on: what if the copy's absence/presence is due to which pseudo is allocated to which reg? No, the copy is a separate insn.

Hmm, OK. Another idea: what if we add a "decoy quantity" to the block (the §34 fix) so the allocation changes? That's an asm (banned).

Let me try v3 (p assignment inside the loop) — 1 test. And in parallel think.

Actually, let me reconsider the source order issue: what if p's assignment is inside the loop AND the `*p & 1` use is also inside the loop, and gcc hoists BOTH? The store hoist might be refused, but the LOAD (`*p & 1`) hoist would happen (loads are hoistable if the address is invariant and no aliasing issue for loads... a load can be hoisted only if the memory isn't written in the loop — but the loop writes *p! So the load can't be hoisted either!). ✗

So the *p&1 load in the preheader means p's assignment and the load are both in the preheader in the source (the load can't be hoisted from a loop that writes *p).

OK, so both are in the preheader. The copy is unexplained by loop.c.

FINAL IDEA before I try v3: **what if the source's p assignment is `p = &D_800B99DC;` and there's ANOTHER variable that holds the same address and is used in the preheader, e.g. the preheader load uses a DIFFERENT variable?**

Target: `lhu v0,0(s0)` — the load's base is s0. If the preheader load used a different variable (say pb) and pb's value were also &D_800B99DC, then we'd have two vars with the same address: one in s0 (the loop's p) and the load's base also s0 — so they were coalesced. Hmm, so no.

OK. Let me try v3 quickly (p assignment inside the loop, keeping the *p&1 in the preheader — semantically wrong but let's see the codegen), and v4 (both p assignment and *p&1 inside the loop).

Hmm, v3 with the use-before-def would give p an undefined value in the preheader → gcc might allocate a different reg → likely a bigger mismatch. Cheap to test though.

Hmm, let me think about which is more likely to produce the copy...

Honestly, let me reconsider the problem from the "how did the ORIGINAL GAME CODE look" angle once more. The target's `move s0,v0` is a copy of the address. In the original game source, there might have been:

```
u16 *p = &D_800B99DC;
```
with the compiler (the ORIGINAL one, maybe gcc 2.7.2 too! the game is from 1998-2000, and gcc 2.7.2 was current) producing `lui v0; addiu v0,v0,0; move s0,v0`.

WAIT A MOMENT. What if the original game compiler IS gcc 2.7.2 and the difference is the OPTIMIZATION LEVEL or the code shape? The project's compiler is gcc 2.7.2 (psx). The target is the original game binary — which was compiled with a DIFFERENT compiler (maybe gcc 2.7.2 for Windows/PSX from a different vendor, or the "mips psx" gcc from SNES/PSX dev kits).

Hmm, so the target's shape (`lui v0; addiu v0,v0,0; move s0,v0`) is what the ORIGINAL compiler did. Our gcc 2.7.2 does `lui s0; addiu s0,s0,0`. The difference is a copy that the original compiler kept and ours coalesces.

The original compiler probably had a copy because the C had a copy! E.g. the original game source:

```
u16 *p;
p = &D_800B99DC;    /* hmm */
```

Hmm, OR the original source had p as a *global* or a struct field, and the copy is a struct member load? no.

Hmm, what if the original source had:
```
D_801E86BC = (*p & 1) + 3;
```
with p a pointer that was set in a PREVIOUS function? no, p is local.

Hmm, what if the original source was:
```
u16 *p = (u16 *)&D_800B99DC;
```
and the original compiler emitted the copy because the initializer's value had to be built in a temp (for the lui/addiu pair) and then moved to the allocated reg? THAT's plausible: a naive compiler that materializes the constant into a temp and then copies it to the variable's register. gcc-2.7.2 (ours) coalesces it away.

So the target is from a compiler that doesn't coalesce. We need to reproduce that with OUR gcc.

The only way: make the copy non-coalescible. In gcc 2.7.2, local-alloc's coalescing is blocked when the copy is between a pseudo and a pseudo where the source's "allocno" has a different priority... Hmm.

AH WAIT!!! What about **local-alloc's rule that a pseudo with n_times_set > 1 cannot be coalesced**? Hmm, actually, in gcc's local-alloc, the "reg_equiv" of a pseudo with multiple sets is not a simple copy.

So: p = pb where pb has 2 sets. The 2nd set must produce &D_800B99DC. What if the 2nd set is a *different* assignment of the same address but the FIRST set is used?

```
u16 *pb;
pb = &D_800B99DC;         /* set 1: used by the preheader load */
D_801E86BC = (*pb & 1) + 3;
pb = &D_800B99DC;         /* set 2 */
p = pb;                   /* the copy */
```
Hmm, but then pb's 2nd set is an identity assignment (and pb's 1st set is used). This is icky but let me TEST whether the mechanism even works (as a diagnostic). If it produces the `move s0,v0`, then I know the mechanism, and I can look for a legitimate formulation.

Let me do this diagnostic test (v4).

Hmm, hold on. Before that, let me reconsider: is there a legitimate C construct where a pointer is legitimately assigned twice?

**YES!!! What about a pointer that is REUSED for two purposes?** Like:
```
u16 *pb;
pb = &D_800B99DC;
D_801E86BC = (*pb & 1) + 3;
pb = &D_800B99DC;  /* NO */
```

Hmm. What about the C0505 "pointer reuse" move: a pointer variable reused for different addresses. E.g.:

```
u16 *pb;
pb = &D_800B99DC;
... use pb ...
pb = &D_801E87B2;    /* reused for q! */
q = pb;
```
Hmm! Then q's value = pb's 2nd set. And the ORDER in the target: q's materialization (s3) comes FIRST (insn 15-16), then p's (17-19). Hmm, so q's address is materialized before p's. If q = pb (the 2nd set) and the source order is q, p, r... hmm.

Let's think: what if the C is:
```
u16 *pb;
pb = &D_801E87B2;
q = pb;              /* q's materialization: s3 */
pb = &D_800B99DC;    /* pb's 2nd set */
p = pb;              /* the copy: move s0,v0 */
r = &D_8018F078;
```
Then: pb has 2 sets. The first set's value is materialized (lui/addiu) — where? It's used only by the copy q = pb → coalesced → `lui s3; addiu s3,s3,0` ✓ (target 15-16!). The second set → materialized into v0 and copied to s0 ✓ (target 17-19)!!!

And r → `lui s2; addiu s2,s2,0` ✓ (20-21)!

THIS FITS PERFECTLY! And it's a "pointer reuse" move (C0505 catalog!) — a pointer variable reused for two different addresses.

Hmm, but is the ORDER right? Source: q's assignment first, then p's. Target: s3 (q) materialized at 15-16, p at 17-19. ✓

And the *p&1 load at 22 uses s0 ✓ (p's reg).

Wait, but why would the FIRST set (pb = &D_801E87B2) be coalesced into s3 while the SECOND set (pb = &D_800B99DC) is not? Because the second set is followed by a copy `p = pb` where p is live across calls, while the first set is followed by `q = pb` where q is... also live across calls (q is used in the loop). Hmm! Both q and p are live across calls. So why would one coalesce and the other not?

Hmm. Unless the difference is: the first set's copy `q = pb` — pb's value is a symbol_ref; cse's canon_reg forwards it → q = symbol_ref → coalesced. The second set's copy `p = pb` — same thing! cse would forward again. ✗

Hmm, cse's canon_reg: it forwards a reg's value to its uses if the reg has one set. With 2 sets, canon_reg can't forward the whole reg (it tracks per-set?). Hmm, actually canon_reg in gcc works on the "reg_equiv" chain: after the first set, the reg's value is known; after the second set, it's known again. cse's canon_reg substitutes uses with the reg's reg_equiv *at that point*. So a use right after set2 would get set2's value. Then the copy p = pb → p = (symbol_ref) → forwarded → coalesced. Hmm.

So cse would still forward. Hmm.

BUT: the whole point of the "second set" in §145(b) is that cse's forward scan is invalidated at the second set. Hmm, "cse's forward scan invalidates the equivalence at the second set" — that's the DEAD-RESET mechanism (§373) which DID work for my item-2 case!

In item 2, the dead-reset `p1 = 0;` invalidated the equivalence so that the second use of `sp10+4` was recomputed. So cse's forward scan DOES get invalidated at a second set. That's because invalidate() deletes the hash entry for the pseudo, so the recorded equivalence is lost and the use after the second set re-derives the value.

So for our case: if pb has 2 sets, then after the 2nd set, cse can't forward pb's value to p → p = a real COPY of pb! ✓✓✓

And then local-alloc: pb (2 sets) is a real pseudo; p is a copy of it. pb's live range: from set2 to the copy (short) → pb gets a caller-saved reg (v0) and p gets s0 → `lui v0; addiu v0,v0,0; move s0,v0` ✓✓✓

And the FIRST set: `pb = &D_801E87B2; q = pb;` — hmm, at that point pb has 1 set (so far) → cse forwards → q = symbol_ref → `lui s3; addiu s3,s3,0` ✓.

Hmm, but wait: with pb having 2 sets in the function, cse's forward scan at the FIRST set's use... The first use (q = pb) comes right after set1, so cse forwards set1's value (a symbol_ref) → q = symbol_ref ✓ → coalesced into s3 ✓.

Then set2 (pb = &D_800B99DC) → invalidate → then p = pb is a real copy ✓.

But hold on: would cse forward set2's value at the copy? The invalidation at set2 removes the hash entry; then the copy `p = pb` — cse's canon_reg looks up pb's reg_equiv... After the second set, pb's reg_equiv is the new value (symbol_ref D_800B99DC) — hmm, cse would forward that too!

Hmm. But §373's dead-reset worked: after `p1 = 0;` the value 0 was forwarded (and the dead store deleted). The KEY effect there was that the *address expression* was re-derived.

Hmm, in §373's case: `p1 = sp10+4; f(p1); p1 = 0; g(sp10+4);` — the reset's VALUE (0) is forwarded to any later use of p1 (none). And the second use of `sp10+4` was recomputed because cse's forward scan was invalidated (the equivalence for the address expression was deleted at the reset).

So the invalidation deletes the CACHED equivalence of the *expression* `sp10+4`, not of the variable.

For our case: after set2 (pb = &D_800B99DC), the cached equivalence of the expression "&D_800B99DC" is invalidated. But the copy `p = pb` uses pb, whose value is a REG (not the expression). cse's canon_reg would forward pb's reg_equiv = the symbol_ref → p = symbol_ref → coalesced. Hmm.

Unless the reg_equiv of pb is NOT the symbol_ref but a "reg" (pb is a real pseudo whose value came from a copy). Hmm.

OK, this is a deep rabbit hole. The dead-reset trick is proven to work in item 2; let me just TRY the analogous things here empirically:

v4: 
```
    u16 *pb;
    ...
    pb = &D_801E87B2;
    q = pb;
    pb = &D_800B99DC;
    p = pb;
    r = &D_8018F078;
```
Hmm, but this changes q's assignment (adding a copy) — the target shows q's materialization as `lui s3; addiu s3,s3,0` (no extra move) so q = pb must coalesce. Risky but let's test.

v5 (simpler, single variable with 2 sets):
```
    u16 *pb;
    pb = &D_800B99DC;
    p = pb;
    pb = &D_800B99DC;   /* identity */
    p = pb;             /* hmm */
```
✗.

v6: what if the "2 sets" are created by a DEAD RESET on the address expression, like item 2?
```
    p = &D_800B99DC;      /* p's value = the address */
    D_801E86BC = (*p & 1) + 3;
    p = 0;                /* DEAD RESET — invalidates cse's equivalence for the address */
    ... loop uses p ...
```
✗ — p would be 0 in the loop. Semantically wrong. But hmm! What if the reset is followed by a re-assignment:
```
    p = &D_800B99DC;
    D_801E86BC = (*p & 1) + 3;
    p = 0;                /* dead reset: invalidates the cached equivalence */
    p = &D_800B99DC;      /* re-assign: now p's value is a REAL copy (not forwarded) */
    ... loop uses p ...
```
Hmm! The re-assignment after the reset: cse's forward scan is invalidated, so the second assignment's expression is re-derived → p = a new pseudo (not the cached one) → p is a real pseudo with a copy!

Hmm, but would gcc then emit `lui v0; addiu v0,v0,0; move s0,v0`? The re-assignment's value would be a fresh materialization into a reg, then... hmm, p IS that reg (the assignment is direct) → `lui s0; addiu s0,s0,0`. ✗ unless the copy survives.

Ugh.

OK, let me just run a batch of experiments. Time is ticking (I've used ~25 min on this item). Let me test v4 and v6 in one go? I can only score one file per bash call, but I can chain with &&.

Let me write v4 and v6, then score both in one bash call with &&.

v4:
```
    i = 0;
    pb = &D_801E87B2;
    q = pb;
    pb = &D_800B99DC;
    p = pb;
    r = &D_8018F078;
```
Hmm, but pb is a new local — this changes the local count in the preheader block (which might trigger the 3-qty sort bug or other allocation changes). Hmm. And the target's preheader has s3, s0, s2 + s4 + others.

Hmm, wait. Actually, hold on! What if instead of a NEW variable, I reuse p itself:
```
    i = 0;
    q = &D_801E87B2;
    p = &D_800B99DC;     /* set 1 */
    r = &D_8018F078;
    D_801E86BC = (*p & 1) + 3;
    D_801E86C0 = D_800B99D8;
    p = &D_800B99DC;     /* set 2 (identity) — a second set */
```
Hmm, the second set is after the *p&1 use. Then p has 2 sets and the loop uses set2's value. Would the copy appear? The 2nd set's value is a fresh materialization (because cse's cache was invalidated by set2? no — set2 is a new set, and cse's forward scan would forward the cached equivalence of "&D_800B99DC" to set2's value → p = symbol_ref → coalesced).

Hmm, so an identity 2nd set doesn't create a copy.

The DEAD RESET (item 2 style) works because it INVALIDATES the cache:
```
    p = &D_800B99DC;      /* set 1: cached */
    D_801E86BC = (*p & 1) + 3;
    p = 0;                /* dead reset: invalidates the cache for the address */
    p = &D_800B99DC;      /* set 2: re-derived → a REAL copy? */
```
Hmm, but gcc would then see p = 0 (dead) and p = &D_800B99DC. The second assignment's value: cse re-derives the address → the pseudo for the address is NEW → p = that pseudo → a copy? or coalesced?

In item 2, the dead-reset's effect was that the two ADDRESS USES were not unified (two separate addiu's). Here, the effect might be that the preheader's `*p` (using set1) and the loop's p (set2) are different values → but they're the same address... and the loop's p would be a separate materialization → `lui s0; addiu s0,s0,0` (in s0) and the preheader's use would be... hmm, the preheader's `*p` uses set1's value → also a materialization → 2 materializations → 4 insns. ✗ (the target has 3).

Hmm. But hmm, what if the ORDER is: the loop's p is set2 (in s0) and the preheader's load uses set1 (in v0)?! Then: `lui v0; addiu v0,v0,0` (set1, in v0) and `lui s0; addiu s0,s0,0` (set2) — that's 4 insns, but the target has `lui v0; addiu v0,v0,0; move s0,v0` = 3. ✗

OK, so the copy is essential: the materialization happens ONCE.

Right — so the target has ONE materialization (into v0) and ONE copy (to s0). The preheader's load uses s0 (the copy's destination). So the source (v0) is dead after the copy.

Therefore: the value is materialized into a temp and copied. For gcc NOT to coalesce, the copy's source must be a pseudo with 2+ sets (so cse can't forward) or a hard reg.

Hmm! What if the source has 2 sets where the FIRST set is the one that's live at the copy?! I.e., the copy copies set1's value, and set2 comes AFTER:
```
    pb = &D_800B99DC;    /* set 1 */
    p = pb;              /* the copy of set1 — but cse forwards set1's value since pb has 1 set so far */
```
✗ (cse forwards based on the sets seen so far).

Hmm, so cse always forwards a copy of a single-set-so-far pseudo.

=> The only way to have a non-forwarded copy is if the SOURCE has 2 sets BEFORE the copy, with the 2nd set being the copied one. And the 2nd set must produce the same address without cse forwarding it (i.e. the 2nd set's expression must be re-derived, not the cached one).

The dead-reset does exactly that: `pb = 0;` (invalidates the cache) then `pb = &D_800B99DC;` (re-derived → a fresh pseudo, NOT the cached one).

So:
```
    pb = &D_800B99DC;     /* set 1 */
    pb = 0;               /* dead reset: invalidates the cache */
    pb = &D_800B99DC;     /* set 2: re-derived → a fresh pseudo P2 */
    p = pb;               /* the copy: p = P2 (not forwarded? hmm) */
```
Hmm, but cse would still forward set2's value (P2) to p... unless the copy is "p = pb" where pb's reg_equiv = P2 (a REG, not a constant!). AH, that's the point! After the invalidation, set2's value is a REG (P2, the fresh pseudo holding the address), NOT a symbol_ref. So pb's reg_equiv = P2 (a pseudo). Then the copy p = pb → p's reg_equiv = P2 (a pseudo) → NOT a constant → reload must materialize P2 into p's reg → P2 is a real pseudo → it gets a reg (v0) and is copied to s0 ✓✓✓!!!

Hmm, wait, but P2 would be a pseudo holding the symbol address; if P2's reg_equiv is a symbol_ref (a CONST pseudo), then reload materializes it into v0 and copies to s0? Hmm, reload would see p's reg_equiv = P2 (a pseudo) → p is not a CONST pseudo → p needs a real register with the value of P2 → P2 also needs a register → P2's reg_equiv = symbol_ref → P2 is a CONST pseudo → reload materializes P2 into P2's reg (v0) and then copies v0 → s0 ✓✓✓ EXACTLY THE TARGET!

So the recipe is:
```
    p = &D_800B99DC;   /* set 1 */
    ... 
    p = 0;             /* dead reset: invalidate */
    p = &D_800B99DC;   /* set 2: re-derived */
```
Hmm, but wait: with the dead reset, the preheader's `*p` use must use set1 or set2? If the reset is before the *p&1 use, then the use uses set2's value. Hmm, and then the materialization of set2 is in v0 and copied to s0 — and the *p&1 load uses s0 ✓.

So:
```
    i = 0;
    q = &D_801E87B2;
    p = &D_800B99DC;
    p = 0;                     /* dead reset */
    p = &D_800B99DC;           /* re-assign: re-derived */
    r = &D_8018F078;
    D_801E86BC = (*p & 1) + 3;
    ...
```
Hmm, but `p = 0` then `p = &D_800B99DC` — the middle statement is a dead store (flow deletes it) and the third is a re-assignment of the same value. The "identity" concern: `p = &D_800B99DC;` twice with a `p = 0;` in between. Hmm, that's 2 extra statements. The first assignment's value is dead (p is overwritten) → flow would delete the FIRST assignment too! Then we'd be back to a single assignment. Hmm!! Flow deletes dead stores: `p = &D_800B99DC` (set1) is dead because p is overwritten at set2 without being read. So flow deletes set1 → only set2 remains → p = symbol_ref → coalesced. ✗

Hmm! Unless set1 is USED (by the *p&1 load) — then set1 is not dead, and the reset `p = 0` is dead (deleted), and set2 is a re-assignment.

But then: the *p&1 load uses set1's value (the cached symbol_ref → forwarded → materialized into s0?) hmm. And set2 (after the load) is re-derived (fresh) → a second materialization → 4 insns. ✗

Hmm, unless the ORDER is: set1, load, reset, set2, loop. Then:
- set1: p = &D_800B99DC (cached, forwarded) → p's reg_equiv = symbol_ref
- load: *p → uses p → s0
- reset: p = 0 (dead → deleted)
- set2: p = &D_800B99DC → re-derived → a fresh pseudo P2 → p = P2
- loop: uses p → P2's reg...

Hmm, so we'd have TWO materializations (one for set1's s0 and one for P2) → 4+ insns. ✗

Unless set1 and set2 share the same reg and gcc reuses... hmm, but the addresses are the same value; the two materializations are `lui s0; addiu s0,s0,0` and `lui v0; addiu v0,v0,0` → 4 insns. ✗

Hmm. So we need set1 to be dead-but-not-deleted...

OK, what if the reset is the LAST thing (like item 2)? In item 2:
```
p1 = sp10 + 4;      /* set 1 */
call1(sp10, p1, 1);  /* use */
p1 = 0;             /* dead reset */
call2(sp10 + 4);     /* the address expression re-derived */
```
Here the KEY was that the second use was the raw EXPRESSION `sp10+4` (not a variable), and the reset invalidated the cached equivalence of that expression → the second use re-derived it → a separate addiu.

For our item: the analogous form would be:
```
p = &D_800B99DC;     /* set 1: p's value = the address, cached */
D_801E86BC = (*p & 1) + 3;    /* use of p */
p = 0;              /* dead reset: invalidates the address's cached equivalence */
... loop uses p ...
```
but then p = 0 in the loop ✗ (semantics).

Hmm, what if the reset is followed by a re-assignment FROM THE SAME EXPRESSION but the re-assignment's value is the re-derived pseudo, and the FIRST assignment is dead (deleted by flow)? Then we're back to one assignment. ✗

Hmm, what if the first assignment is NOT dead because it's used in the preheader load, and the re-assignment after the reset is what the loop uses? Then 2 materializations. ✗

Hmm. Unless... the re-derived pseudo P2 IS the same as the first materialization? No, the invalidation kills the cache.

OK OK. Let me flip it: what if the reset invalidates the cache and the SECOND use is the raw expression, and the FIRST use is a variable?

```
p = &D_800B99DC;      /* set 1 */
D_801E86BC = (*p & 1) + 3;    /* uses p (set 1) */
p = 0;               /* dead reset: invalidates */
... the loop uses &D_800B99DC directly?  ✗ (the loop uses p)
```
Hmm, what if the LOOP uses the raw expression `*(u16 *)&D_800B99DC` instead of p?! Then:
- the preheader load uses p (set 1) → p's value = the address, materialized into... s0? (p is live across the loop? no! if the loop doesn't use p, p is dead after the load → p gets a caller-saved reg → v0!)

OHHH. Interesting! If p is used ONLY in the preheader load, p is dead after → p gets a caller-saved reg (v0) → `lui v0; addiu v0,v0,0` and the load `lhu v0,0(v0)`?? Hmm, the target has `lhu v0,0(s0)`. ✗ (the load's base is s0).

Hmm. But wait: with the dead reset, the loop's use of the raw expression would be re-derived → materialized into a reg that crosses calls → s0 → `lui s0; addiu s0,s0,0`?? and the preheader's p → v0. Then the target order would be `lui v0; addiu v0,v0,0` (p) then `lhu v0,0(v0)`... but the target has `lhu v0,0(s0)` and the s0 materialization BEFORE (17-19). ✗

OK. Let me now just TEST the most promising thing I can construct and stop theorizing. Options ranked:

A) v4: pb reused for two addresses (pointer reuse, C0505): pb = &D_801E87B2; q = pb; pb = &D_800B99DC; p = pb; r = &D_8018F078;
B) v6: p = &D_800B99DC; p = 0; p = &D_800B99DC; (dead reset + re-assign) — the first assignment is dead → deleted. Probably ✗ but cheap to test.
C) v7: p = &D_800B99DC; D_801E86BC = (*p&1)+3; p = 0; p = &D_800B99DC; (reset between the use and the loop) — 2 materializations, probably ✗.

Let me test A and B. Both are cheap.

Hmm, for A: I worry that adding a new local (pb) changes the allocation. But let's see.

Actually, WAIT. Let me reconsider A more carefully, because it might be exactly right!

In A:
```
pb = &D_801E87B2;    /* set 1 */
q = pb;              /* copy 1 — pb has 1 set so far → cse forwards → q = symbol_ref → coalesced into s3 ✓ */
pb = &D_800B99DC;    /* set 2 — pb now has 2 sets */
p = pb;              /* copy 2 — pb has 2 sets → cse CANNOT forward (the reg_equiv chain is invalidated at set 2?) */
```
Hmm, at copy 2, cse's forward scan: pb's current value (set 2) is known → it would forward. The invalidation happens for the *previously cached* equivalence. Hmm.

Hmm, but cse's canon_reg for a reg with multiple sets: canon_reg is called on USE sites and looks up the reg's reg_equiv via `cse->equivs` hash, which is invalidated at each set (update_stmt → invalidate → the hash entry is deleted). So after set 2, the hash entry for pb is deleted; but then the SET itself re-records the equivalence (update_stmt records the new value). So a use right after set2 WOULD be forwarded. ✗

Hmm!! So cse forwards p = pb.

Unless the copy is not to a variable but the value is used directly.

OK, I need to stop theorizing. Let me look at the actual gcc 2.7.2 source for the ONE thing that matters: how to get a non-coalesced copy. Let me grep local-alloc.c for "coalesce".

Let me look at the reference source: tools/reference/gcc-2.7.2/local-alloc.c.

Let me grep for the coalescing decision. This is worth one call.

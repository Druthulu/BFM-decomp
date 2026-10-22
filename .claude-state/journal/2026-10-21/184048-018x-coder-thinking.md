---
ts: 2026-10-22T00:40:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Lym3hg2DfwjmreeAaF1Z
---
The --try output gives the mnemonic diff. That's my feedback loop.

Now let me write orig.c for item 1 and score it. Then I'll design candidate lever-free bodies.

Let me write the files. Use Write tool.

For item 1, orig.c content = the function text (lines 3584-3610).

Note the body uses `__asm__` launders. The lever-free version must remove them.

Let's think about item 1's mechanism. The comment says the launder is NEEDED: cse unifies the 6 `&buf` uses into one pseudo with >2 refs → local-alloc remat path (needs reg_n_refs==2) never fires → address parked in an extra callee-saved register (+3 ins, frame 0x70).

Key insight: remat fires when reg_n_refs == 2. With 6 uses, if we can reduce the number of references to any single pseudo to 2, remat fires.

Idea: use several distinct pointer variables, each used exactly twice:
```
s32 *p1 = (s32*)&buf;   // used at 2 sites
s32 *p2 = (s32*)&buf;
s32 *p3 = (s32*)&buf;
```
But cse would unify p1,p2,p3 (same value &buf) into one pseudo again... unless the assignment happens at different times with intervening assignments. Actually cse might keep them separate if there are stores to memory between? No, &buf is a constant address.

Hmm. cse unifies addresses of the same object. But wait: key (3) says "If the FIRST site is the un-laundered one instead, its (plus $sp,0x38) pseudo survives in the cse table and every later laundered site's asm INPUT unifies with it". So even asm-laundered later sites unify with the first. Meaning cse unifies addresses across statements.

So the crux: any way to get 6 uses of the same stack address to be materialized as rematerializable (reg_n_refs==2) — i.e. the address pseudo must have exactly 2 refs, meaning 2 uses. Hmm, with 6 call sites each passing &buf, there are 6 refs minimum unless some uses get folded differently.

Alternative: maybe we can make the address a *variable* (not an address constant): e.g.
```
s32 *pb = (s32 *)&buf;
```
and then use `pb` at all sites. Then cse: pb is a variable holding &buf. cse would copy-propagate the value &buf into pb's uses? cse does "make_regs_eqv" and forward constants. The comment says the asm INPUT unifies with the surviving pseudo — meaning cse forwards the address. If we store the address into a variable and pass the variable, cse's copy propagation might forward &buf into the uses, re-unifying.

Unless the variable is volatile! `volatile s32 *pb` — a volatile read at each use prevents cse forwarding, and each use loads from memory → that would add loads (spill). Not good.

Alternative: what if the address is not constant across sites? E.g. &buf, &buf+0? Not useful.

Hmm, but wait: maybe the extra callee-saved parking is due to a different reason and there's a way to make the 6 uses not need a register at all — e.g. materialize the address into each call's a1 argument directly (addiu a1,sp,0x38 at each site) — that's what the target does! The target (63 ins) has 6 call sites each with `addiu a1,$sp,0x38`? That would be 6 addiu = 6 ins. Hmm, but the comment says the target launders only the LAST site and the rest are laundered. And the target's asm presumably has the address in a callee-saved reg? Let's count 63 ins.

Actually, wait. Let me reconsider: maybe the target computes the address once into a register? No — key (2) says the address is parked in an extra callee-saved register when un-laundered (+3 ins, frame 0x70 vs target frame 0x68). So in the target, the address is NOT parked in a callee-saved register. With 6 uses of the same address, gcc must materialize it per use: 6 × (addiu a1,sp,0x38) = 6 insns. Hmm, but the first site is `func_8012EA90(a0, ang, &buf)` where &buf is arg3 → a2 = sp+0x38.

Hmm, and the comment says: "If the last site is laundered too, its asm output pseudo does not coalesce into $a1 and you get a spurious addiu $v0,$sp,0x38 / move $a1,$v0 (+1 ins)". So at the last site, the address pseudo coalesces into a1 → the addiu is directly a1: `addiu a1,sp,0x38`.

So in the target, likely all 6 sites have `addiu aN,sp,0x38` — no register parking. And the laundered sites are the *asm* ones: `__asm__("":"=r"(_m):"0"(_m))` with _m = &buf. The asm output can't coalesce to a1... hmm but the comment says only the LAST site un-laundered is fine, others laundered.

Hold on. Reread key (2): "Plain &buf everywhere makes cse unify all six into one pseudo with >2 refs, so local-alloc's remat path (which needs reg_n_refs==2) never fires and the address is parked in an extra callee-saved register (+3 ins, frame 0x70). Fix: launder the address through an empty asm at every site EXCEPT the last."

So the target has 6 distinct address pseudos (each with 2 refs?), no — with asm launder, each site's asm output is a distinct pseudo. The asm output pseudo has 1 ref (the use). Hmm, reg_n_refs==2 maybe counts the asm operand + use.

The target likely: at each of 5 laundered sites, `addiu a1,sp,0x38` then the asm ties it; and the last site has `addiu a1,sp,0x38`.

Hmm, but wait — with the asm launder at a site, gcc must materialize the address into a register before the asm. The asm output pseudo then gets coalesced with the input pseudo (tie "0"), and that pseudo is used as the call argument → coalesced into a1. So each site has `addiu a1,sp,0x38` in it. 6 sites × addiu = 6 insns, plus 5 asms cost 0 bytes.

So the target = 6 addiu's of sp+0x38 (one per site) and the address never parked.

Now the plain-C version: cse unifies → 1 pseudo with 6 refs → gcc parks the address in a callee-saved register (e.g. s0) → 1 addiu + 6 moves (or the reg is loaded once) → that's the +3 ins? Hmm +3 ins with 6 uses... if address parked in s0: 1 addiu s0,sp,0x38 + 6 × move a1,s0 = 7 ins vs 6 addiu = 6 ins → +1. Not +3.

Hmm, +3 maybe: the callee-saved reg also needs save/restore (sw ra, ... ; lw ra) = +2 ins plus +1 = +3. And frame 0x68 → 0x70 (+8 = 1 more saved reg). Yes! That matches: parking in a callee-saved reg adds 2 (sw/lw) + 1 (the addiu) + maybe.

So lever-free target: each of the 6 sites must materialize sp+0x38 independently, no register parked.

How to prevent cse from unifying 6 identical address constants in plain C?

Option A: Make the 6 addresses distinct expressions that still print as addiu sp+0x38. Hmm, cse would canonicalize (plus &buf, 0) → &buf.

Option B: Use a *different* base object each time but same address? Impossible.

Option C: Prevent cse unification by making the address depend on a volatile or on something that changes. E.g.:
```
s32 *pb = (s32 *)&buf;
... use pb at site1 ...
pb = (s32 *)&buf;  // re-assign
... use pb at site2 ...
```
cse might treat each assignment as a new set but the value is the same constant → it might still unify the constant.

Hmm, but cse's job is to find common subexpressions; for addresses it uses "find_best_addr" and canonicalizes. But if between the two uses there is a *store* to memory that could alias the address... cse is conservative about aliasing! Key insight: if we store to some global variable between the uses, cse may invalidate the address equivalence (since the store might alias the stack address? no, globals vs stack — gcc's alias analysis knows a global can't alias a local whose address hasn't escaped... but it HAS escaped, so it could alias!).

Hmm, actually if &buf escapes (passed to functions), gcc must assume the callee could write to it. But that's about the store to buf, not to the address pseudo.

Actually cse's reg_equiv for a constant address: the address pseudo's value is a constant (frame offset). Two uses of the same constant address unify always... unless cse has "invalidated" the pseudo due to a memory store between them? In gcc's cse.c, `reg_equiv` for a reg is invalidated when a store might alias. A constant address of a local variable that's escaped: stores through unknown pointers could alias it! But &buf itself as an address value isn't memory — reg_equiv holds a constant (frame offset) which is not invalidated by stores, I think. Actually cse.c does invalidate reg_equiv entries on store if the reg's value is a memory address? Hmm, in gcc's cse.c there's a mechanism: "if (reg_equiv_contents[reg].rt_pointer == 1)" — entries that are pointer-valued get invalidated by stores of unknown type? There IS such logic in GCC's CSE: `invalidate_hard_reg_eq` and the `reg_equiv` invalidation on `set_mem` with `MEM_VOLATILE`? Let me recall: cse.c has "cse_record_store" which invalidates equivalences for registers whose contents are addresses of memory that the store might hit? There is code:

```c
/* If we are updating a memory location, then any register that contains
   an address of that location ... */
```
Actually, in gcc/cse.c there's `record_store` → `invalidate_refs` for MEM refs, and for regs there's "if (reg_equiv_contents[reg].rt_pointer == 1) ... invalidate". Yes! GCC's CSE has:

```c
      if (reg_equiv_contents[reg].rt_pointer == 1)
        {
          /* This is a pointer to the memory location.  */
          ...
        }
```
Hmm. I recall in cse.c `record_store`:
```c
  /* If we have a dead set, then we can delete it... */
  ...
  if (MEM_VOLATILE_P (mem)) ...
```
And there's the `reg_equiv` invalidation for stores where the stored value's address... Let me recall the actual comment in cse.c:

```c
/* Record that we are storing the value VAL into the memory location specified by MEM.
   ... */
static void
record_store (regset eqs, rtx mem, rtx val, bool call_preserved, struct cse_env *cse_env)
{
  ...
      /* If we are storing into a register, see if we have a memory location
	 that is aliased ... */
```
And:
```c
	  /* If this is a store to a memory location, then invalidate
	     any equivalences involving registers that point into it.  */
```
Hmm.

Given moves.md history, there IS a known lever: "launder->real 2nd set" and "pointer reuse". And "cse-const-addr" walls where cse forwards the const address.

Also note: the moves.md entry for G09 `func_8002AC00 | WALL sched1-birth-boost — sched1 boosts the single-set la s3 (birthing) past the jal; ... launder = 2nd s3 set`.

Interesting pattern in G11: `func_8018AA98 | MATCH: pv &= 0xFF000000 (compound assign) = a REAL 2nd SET of the pinned pv, kills the sched1 birth boost of the pv load; plain pv = pv & mask (a new temp) does NOT (11 left)`.

So: creating a real 2nd SET of a variable is a lever. In our case: cse unifies the address across sites. If we make the address pseudo have 2 sets... Hmm, an address constant doesn't have sets.

Alternative approach: what if we avoid the address being a constant at all? E.g., pass a pointer to a pointer? No, signature must stay.

Alternative: What if `buf` is not a local but... it must be (frame 0x68 with vars 0x10..0x60).

Hmm, what about using `&buf` at only ONE site and passing a copy elsewhere? No, all 6 sites pass &buf.

OK here's another thought: the target's asm is 63 ins. If cse unifies the 6 sites into one pseudo, gcc parks it in a callee-saved reg → that's the plain-C result. To avoid that, we need the pseudo to have ≤2 refs.

What if we split the address into two pseudos of 2-3 refs each? Like:
```
s32 *pb = (s32 *)&buf;   // pb used at sites 1,2
```
then a second variable `pc = &buf` used at sites 3,4, etc. But cse will unify the *values* — pb and pc both = &buf. cse's copy propagation would replace pb's uses with pc or vice versa, giving one pseudo again.

Unless: the re-assignment is a "real 2nd set"! Like the `pv &= mask` trick: a compound assignment creates a new set of the pseudo. For pointers:
```
pb = (s32 *)&buf;  // set 1
pb = (s32 *)&buf;  // set 2 (second assignment)
```
Two assignments to pb of the same value: cse may treat the second as redundant... but gcc's cse won't remove a redundant store to a local whose address escaped? It might, since pb is a local var (address taken? if we take &pb it escapes; otherwise not).

Hmm, actually if pb is a plain local not escaping, `pb = &buf; pb = &buf;` — the second store is redundant and removed. And the uses of pb would be forwarded to the first value.

Different approach: make the value not a constant so cse can't unify. E.g. compute the address as `&buf` but through an arithmetic that yields the same address: `((s32*)((char*)&buf + 0))`. cse folds +0 away.

What about the "2-use join" mentioned: "cse: single-set const addr r73 folded into lone use lbu 73(sym) even past a 2-use join label; s1 never held (W01)".

Hmm.

Let me reconsider: maybe the answer lies in the *number of refs*: reg_n_refs==2 → remat. If the address pseudo has exactly 2 refs, gcc rematerializes it at each use (that's what "remat path" means: re-materialize the address instead of parking it). But with 6 uses, the pseudo has 6 refs... unless cse creates ONE pseudo but local-alloc counts "reg_n_refs" differently.

Hmm wait, re-read: "Plain &buf everywhere makes cse unify all six into one pseudo with >2 refs, so local-alloc's remat path (which needs reg_n_refs==2) never fires".

So if we could make cse unify only PAIRS (2 refs each), remat fires and each pair's address is rematerialized at its 2 uses → 6 addiu total, no parking. That's exactly the target!

So: how do we get cse to unify 2 uses at a time rather than all 6?

Idea: use different *base objects* that happen to be at the same address? No.

Idea: use a chain of variables where each variable holds the address and is assigned twice, so cse's reg_equiv for each is invalidated...

Idea: use the address of a member at different offsets? No.

Hmm, but wait: maybe it's about the *order* of unification. cse processes statements in order; when it sees `&buf` at site 1, it creates pseudo P1 with reg_equiv &buf. At site 2, it finds the same value and makes regs_eqv(P2, P1) → P2 and P1 become one pseudo with 6 refs.

To break this, make the value at site 2 not equal to the value at site 1 as far as cse is concerned. But the value must be the same address...

UNLESS: the addresses are not literally the same object! E.g., if `buf` were a union of two structs at the same address: `&buf.u1` and `&buf.u2` — cse would still fold both to the same frame address.

What if buf is at different offsets? No, must be same address.

OK alternative: what if we make the address depend on a value that changes, e.g.:

```
s32 *pb = (s32 *)&buf;
...
pb = pb;   // ?
```
no.

Hmm, what about using `__builtin_alloca`? no.

What about making the address come from a struct field: e.g. have a local struct variable `holder` with a pointer field, and set `holder.p = &buf;` then pass `holder.p`. That's still a copy of the constant; cse forwards.

What if we make it truly opaque in C without asm? Options:
- `volatile` local: `volatile s32 *pb = &buf;` then use `pb` — the *value* is still a constant; cse may still copy-propagate volatile var reads? A volatile variable read must happen, so the value comes from memory: `lw a1, pb(sp)` — that's an extra load, changing ins count. Target wouldn't have that.

Hmm, but hold on: maybe the target DOES have loads. Let me look at the actual target asm! I need it. Let me find the baseline object for this TU and disassemble func_8018A180.

The baseline object path: oracle.baseline_path(rec["obj"]). Let me find the object for the TU src/ov_SC06_029/ov_SC06_029_jr_801898CC.c. Perhaps in build/. Let me search build/ for that .o.

Let me look at how oracle.recipes work — there's a recipes file listing TUs → obj. Let me grep for the TU in .run/P40 recipes or config.

Let me find it: tools/oracle.py load_recipes.

Simplest: search build/ for files named ov_SC06_029*.

Let me check.

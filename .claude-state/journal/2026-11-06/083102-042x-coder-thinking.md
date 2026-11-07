---
ts: 2026-11-06T15:31:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AC3p6bqhI2kVudkOIcGF
---
Interesting! In the cse dump (after cse1), insn 21 is `(set (reg/v:SI 73) (reg:SI 2 v0))` — that's raw = call result, reg 73. Then insn 26: `(set (reg:SI 80) (and:SI (reg/v:SI 73) 24576))` — the andi uses reg 73 (raw). So cse kept raw's use as raw!

Wait, but where's flags? The `flags = raw` copy seems gone... and `ret = 0` — hmm, reg 76 is ret (=0). Let me search for the flags variable's insn (the copy). It seems cse deleted the copy `flags = raw` and replaced flags' uses with reg 73. But then the andi uses 73 and the later uses also 73. So one pseudo, allocated to s1 → the andi reads s1. Right.

So cse1 deletes the copy `(set flags raw)` and replaces uses with raw. In the orig (with asm), the asm prevents this.

Now: the register allocator then assigns reg 73 to $s1 because its live range crosses the calls. The target has TWO pseudos: the andi on the call result ($v0) and later uses on a copy ($s1).

To get the target, we need cse to NOT delete the copy. cse deletes a copy when the destination's value is equivalent to the source. The only way is if something makes flags ≠ raw.

IDEA: What if `flags` is assigned the call result *directly* and `raw` is a copy used for the test? i.e.:

```
flags = call();
raw = flags;
if ((raw & 0x6000) != 0x2000) ...
```
Then cse sees `raw = flags` and replaces raw's uses with flags → same merge. Unless...

IDEA 2: Make the copy *after* the first use in source order (so cse processes the andi before the copy):
```
raw = call();
if ((raw & 0x6000) != 0x2000) {...}
flags = raw;
```
Then cse processes the andi with raw alone → andi on raw (v0). Then the copy `flags = raw` — but it's in the join block after the if. cse deletes it and replaces later uses with raw → raw becomes live from the call across the calls → $s1. But the andi insn already references reg 73 (raw), which is allocated $s1. Hmm — the andi would read s1, not v0, because the same pseudo reg 73 is used. Unless the copy remains and flags gets its own pseudo.

So we need the copy to survive. The copy survives only if cse can't prove equivalence.

IDEA 3: Make flags a genuinely different value that the later code compensates for: e.g., `flags = raw;` but then use `flags` in the condition as `(flags & 0xE000)` with an extra operation... The target's second block: `andi v0,s1,0x8000` and `andi v1,s1,0x6000`. So flags must be raw's exact value in $s1.

IDEA 4: Make `raw` NOT a register (e.g., memory) so the copy to a register is real? That changes codegen.

IDEA 5: Use two separate calls? No.

IDEA 6: The value could be stored in a struct member? No, changes memory.

IDEA 7: Use a *function call* to copy: no.

IDEA 8: Make raw's live range end at the andi by using it in a way cse can't rewrite: what if the andi is on a *subexpression* involving raw and a variable that cse can't relate, e.g. `(raw | 0)`? folds.

Hmm, what about the dead-reset applied to a *different* pseudo to break the equivalence *before* the andi... Actually cse1's delete of the copy happens when? Let me look at cse.c: it deletes a set if the src is the same as the dest's known value (the "if (rtx_equal_p (src, dest))" delete). The copy `(set 73 73)`? No: cse's `canon_reg(SET_SRC)` rewrites the src to the canonical reg, and if the dest is also the canonical reg, the set becomes `(set r r)` → deleted.

So cse replaces the dest reg (flags) in `(set flags raw)` with raw? No, it canon_regs the SRC (raw) to the qty's first reg. Hmm, then it may substitute the dest too.

The key is the qty: after `(set flags raw)`, flags joins raw's qty (if insert_regs with modified=1). Then in later insns, both are canon'd to the qty's first reg. The first reg is raw (inserted first). So `(set flags raw)` becomes `(set raw raw)` → deleted, and uses of flags become raw. Yes.

So to prevent: make flags NOT join raw's qty. insert_regs with classp: `if (GET_CODE(classp->exp) == REG && GET_MODE(classp->exp) == GET_MODE(x))`. If modes differ, no join. So if `flags` were a different mode than `raw`... e.g. raw is SImode and flags... the call returns s32. If I declare flags as `long`? same. 

What if flags is declared `s16` but the value is sign-extended? The copy `flags = raw` with flags HImode: the RTL would be `(set (reg:HI flags) (subreg:HI raw))` and uses of flags would sign-extend. Codegen changes.

Hmm, but the target's second andis are on s1 with SImode.

IDEA 9: give raw a mode change so it doesn't join: e.g. use a `u32 raw` and `s32 flags`? Both SImode (u32/s32 → SImode). 

IDEA 10: What if we avoid the copy in C but force the value into $s1 by making it live across the calls via a different variable that is *not* a copy: e.g. recompute from memory? No.

IDEA 11: Maybe restructure so the *call result* itself is used later, and the first test uses a *separate local copy*. I.e., swap roles:

```
raw = call();          // call result, global $s1 (live across calls)
if ((raw & 0x6000)...) // hmm target's first andi is on $v0
```
No.

Hmm, wait. Let me reconsider the target's actual dataflow. Target:
```
jal call
move s1,v0     <- copy
andi v0,v0,0x6000   <- andi on the return value register
```
$v0 is a hard register (return value). In gcc RTL, the call sets hard reg v0; then `(set pseudo_flags (reg v0))`; then the andi on `(reg v0)` directly. So the target's andi reads the *hard reg* v0, meaning the first test was compiled on the call's return value expression directly — not on a pseudo!

That's a big hint: the target's C may be `if ((func_8012CBA4(a0) & 0x6000) != 0x2000)` where the call result is used in an expression (hard reg v0), and separately `flags = <call result>` stored for later. But you can't call twice. Unless:

```
flags = ((s32 (*)(s32))func_8012CBA4)(a0);
if ((<expr> & 0x6000) ...)
```
No, one call.

OR: `raw = call(); if ((raw & 0x6000)...)` where raw is a *local* pseudo that the allocator assigns to v0 — which happens if raw's live range doesn't cross calls. And `flags = raw` where flags is global → s1. The copy `move s1,v0` is real.

So the target has raw local and flags global, exactly as I thought. The launder keeps the copy.

Since cse1 deletes the copy, maybe another approach: keep the copy but make cse *not* delete it by having the destination be used *before* the copy in the block? Hmm.

What about `raw` being written twice? E.g.:

```
raw = call();
flags = raw;
if ((raw & 0x6000) ...)
```
cse merges.

What if we add a second set of raw *between* the copy and the andi that is a no-op for the value but opaque... circular.

New angle: the project's known crack for this exact family. This function's comment says "8 no-barrier variants tested (temp var, `register` pin on either side, inverted test, subtract-form compare): all land on the identical 3-insn permutation." So the original author tried the obvious ones and gave up. This is a hard one.

But the moves list shows many such "re-tie" launders cracked by "real 2nd set". The real 2nd set for flags: since flags' uses only mask 0xE000, we could set `flags = raw & 0xE000` — tested b2: score 12 (with ret unfixed). Let me combine b2 with the ret fix and see the diff.

Actually wait: b2 changed the first test? No, the first test is on raw. b2's flags = raw & 0xE000; then `m = flags & 0x8000` → combine folds to raw & 0x8000? Let me look at b2's diff.

Let me test combined variants: ret=0 + flags variants. Let me restructure gen.py: variants c1.. with the ret fix always, and flags fix varying.

Actually simpler: create c-variants = a7 (ret fix) plus flags changes. Let me modify gen.py: for VAR starting with 'c', apply ret=0 and the flags substitution.

c1: flags = raw & 0xE000
c2: flags = raw & 0xFFFF
c3: flags = (s16)raw? no.
c4: two-stage: `flags = raw; m = flags & 0x8000;` hmm.

Let me think about what a "real 2nd set" that emits nothing could be for flags. If flags ∈ any value, no free value-preserving op exists. BUT: we don't need flags to be the exact value; we need the *uses* to compute the same masks. The uses are `flags & 0x8000` and `flags & 0x6000`. If flags = raw & 0xE000, both uses are equivalent. The extra andi might be folded by combine into the existing andis (since `(x & 0xE000) & 0x8000` = `x & 0x8000`). Then no extra insn, and the first test (on raw) unaffected. But then flags ≡ raw again after folding? The folding happens in combine (after cse1). cse1 runs first: `(set flags (and raw 0xE000))` is not a copy, so flags does NOT join raw's qty. The andi test on raw stays on raw. The later `(and flags 0x8000)` stays on flags. Then combine may fold `(and (and raw 0xE000) 0x8000)` → `(and raw 0x8000)` — if it does, flags becomes dead and the register allocation changes.

b2 scored 12 (better than 14) but not 0. Let me see its diff.

Let me look at b2 diff.

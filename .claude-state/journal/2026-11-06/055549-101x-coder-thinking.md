---
ts: 2026-11-06T12:55:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_H5Tw4gtirSQOlX3Y99ek
---
Interesting! In c1's asm, the copy loop uses:
```
$L208:
	lhu	$2,0($5)      ← src = $5 (a1!)
	addu	$5,$5,2
	addu	$8,$8,1
	sh	$2,0($4)      ← dst = $4 (a0)
```
So src = $5 = a1, dst = $4 = a0. And the `ba` computation: `addu $4,$3,$4` — ba goes into $4 = a0 (dst's pin!) — the pin on ba ($5) was NOT honored?!

Hmm wait: `register u16 *ba __asm__("$5");` — with `ba = (u16 *)(tmp + (u8 *)dp);` gcc should emit `addu $5,$3,$4`. It emitted `addu $4,$3,$4`.

Hmm, unless the asm("$5") pin is ignored because... Let me check the target:
```
ff8: addu a1,v1,a0    ← ba = a1 ($5) ✓ pin honored
ffc: move a0,a1       ← dst = ba
```
So the target honors the pin. In c1, the pin isn't honored — because of the launder asm removal? The launder `__asm__("" : "=r"(decoy) : "r"(ba))` *reads* ba, so ba must be materialized in $5 at that point. Without it, gcc sees `ba = X; dst = ba;` and with `dst` also pinned to $4, gcc can... hmm, but ba is a hard-reg variable; `ba = X` MUST set $5.

Unless gcc's `register asm` handling in 2.7.2 only pins the variable when it's used in an asm or when... Actually, `register int x __asm__("$5")` in gcc makes the variable's rtl a hard register; every assignment writes it. But with optimization, gcc can eliminate a dead store to a hard register? No, hard regs aren't eliminable... but the *variable* `ba` is a hard reg (reg:SI 5) and `dst = ba` → `set (reg 4) (reg 5)`.

Hmm, c1's asm shows `addu $4,$3,$4` — that's assigning to $4, so the variable ba is NOT in $5. So the pin was lost.

OH! I bet the issue: in c1, I removed the launder asm and the keepalive. The launder had `"r"(ba)` as input, which forced ba into $5 at that point. Without it, gcc's `global_alloc`/`local_alloc` treats the hard-reg variable... 

Actually in gcc 2.7.2, `register asm` variables: if the variable is a hard reg, `DECL_RTL` = (reg:SI 5) and assignments go there. But there's an optimization: `expand_assignment` with a hard-reg destination → the value may be copied. Hmm, but the emitted code must set $5.

Wait — maybe the pin is honored but then the *copy* `dst = ba` is a `set $4 = $5`, and gcc's copy propagation (local-alloc) coalesced... you can't coalesce two hard regs.

Unless c1's output corresponds to a DIFFERENT part: maybe `ba` was computed into $4 because gcc decided `ba` and `dst` are the same and replaced ba's uses with dst's... but ba is a hard reg.

Hmm, hold on. Let me reconsider: maybe gcc 2.7.2's `register asm` variables are only pinned if used in asm statements (a documented behavior: "the register asm is not honored unless the variable is used in an asm"). Actually, the gcc docs say: "The only supported use for this feature is to specify registers for input and output operands when calling Extended asm" — using it for a plain variable is not guaranteed. In gcc 2.7.2, `DECL_RTL` is set to the hard reg but `optimize` may... 

Given the evidence: with the launder asm reading ba, the pin is honored; without, it's not.

So removing the launder breaks the ba pin. Lever-free, we must keep ba in $5 — but the pin is a *lever of kind pin*, which the row says may stay... but the pin's effect depends on the asm.

Hmm! But wait: does the row kinds list include "pin"? No: kinds = keepalive,launder. So pins may stay. But if the pin only works because of the asm, then...

The brief's rule: "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added". So keeping the pin declaration is fine; the question is whether it takes effect.

So I need a lever-free way to make `ba`'s pin effective. Options:
- Use ba in a context where the hard reg matters, e.g. pass ba to something? no.
- Make ba's assignment "used" so gcc can't fold it.

Hmm, what if we make `dst = ba;` where dst is pinned $4 → gcc must copy $5 → $4... but it doesn't.

Wait, maybe the real issue is different: maybe gcc DID emit `addu $5,...` and then `move $4,$5`, and the *copy* was removed because... the target has `move a0,a1`. Mine has no move. So mine computed ba directly into a0.

Let me test directly: does `ba`'s pin survive if I keep a real use of ba? E.g., after `dst = ba`, add nothing... Hmm.

Alternative: give `ba` a second use so the hard reg matters: e.g. use ba in the loop? The C's loop uses dst, not ba.

What if we write `dst = ba;` and also `src = ba;`? no.

Hmm, what about writing the copy loop with `ba` instead of `dst`? No — the target has both.

Let me look at how gcc treats `register asm` variables in 2.7.2: in `stor-layout.c`/`decl.c`, if DECL_ASSEMBLER_NAME... Actually the feature: `register int x __asm__("$5")` sets `DECL_RTL` to a hard reg in `make_decl_rtl` (varasm.c): 
```
  if (TREE_CODE (decl) == VAR_DECL && DECL_REGISTER (decl)) ... 
```
Hmm, in 2.7.2 make_decl_rtl: 
```
#ifdef SET_DECL_RTL
...
  /* If the declaration has a name and is a register, ... */
```
Actually the asm register spec is handled in `decl.c`/`c-decl.c`? Let me grep for "DECL_RTL" with asm in the source. Simpler: test empirically.

Actually, since the pins may stay, maybe the cleanest path: keep the launder-like *effect* via a real C construct that reads ba. E.g.:

```
ba = (u16 *)(tmp + (u8 *)dp);
dst = ba;
```
What if we write `dst = (u16 *)ba;`? no.

Hmm, what about making `dst = ba` conditional: `if (ba) dst = ba;`? Adds a branch.

What if `dst` is assigned inside the loop's init: `for (dst = ba; ...)`? no.

Let me test whether the pin works when ba has a second use, e.g.:
```
ba = (u16 *)(tmp + (u8 *)dp);
dst = ba;
... loop uses dst ...
```
and after the loop, nothing uses ba.

Try: add `src = ba;`? That changes code.

Alternatively: maybe I can drop the `ba` variable entirely and write `dst = (u16 *)(tmp + (u8 *)dp);` — then dst is computed into $4 directly (which is what mine does) and no `move a0,a1`. But the target has `addu a1,...; move a0,a1` — because of the pin on ba.

Hmm, the target's `move a0,a1` is 1 insn; mine has `addu a0,v1,a0` (1 insn). Total insn count: mine 158, target 159 — exactly 1 short (the move). And the other diffs are renames/order.

So: to get the target, we need ba in $5 and dst = ba.

Since pins may stay, the question is how to make gcc honor the ba pin lever-free. If the launder asm's `"r"(ba)` was what honored it... maybe any *use* of ba in a context where gcc needs the value would do. `dst = ba` IS such a use. So why doesn't it?

Hmm, maybe the pin IS honored but gcc then does copy-propagation: `set (reg:5) X; set (reg:4) (reg:5)` → local-alloc/regmove could replace the uses of reg 5 with reg 4 if reg 5 dies... there's a pass `regmove`? Not in 2.7.2. But `cse` could propagate: after `set (reg 5) X`, the value of (reg 5) is X; then `set (reg 4) (reg 5)` → cse replaces with `set (reg 4) X` and if reg 5 is dead, deletes the first set! YES — cse1 does exactly that: a hard reg that is set and then copied, with the hard reg dead after, gets forwarded (reg 5 is a hard reg, but cse tracks hard regs too, invalidated only by calls/branches...).

So cse deleted the `addu $5,...` because $5 was dead after the copy. In the target, the launder asm read $5, so $5 was live → not deleted.

Lever-free alternative to keep $5 live: make ba's value used later, i.e. a second real use of ba. What could that be? In the target, after `dst = ba` the loop uses dst only.

Hmm, what if we write the loop using `ba` instead of `dst` in one place? Like `tv = *src; *dst = tv; ...` where dst is ba... no.

Alternatively: prevent cse from deleting the store to $5 by making the copy `dst = ba` not immediately foldable... 

What if `dst` is assigned INSIDE the loop start: `do { dst = ba; ... }`? Hmm, that would emit the copy each iteration.

What about declaring `dst` before and assigning `dst = ba` — already.

What if the value assigned to ba is not a simple expression cse can forward? E.g. `ba = (u16 *)(tmp + (u8 *)dp);` — cse forwards the whole expression.

Hmm, what if we make `ba`'s assignment happen in a different block than `dst = ba`? If the copy loop block is separate from the ba computation... they're sequential in the same block.

Wait — but cse1 operates per EBB; a block boundary (do-while(0)?) might stop the forwarding. Let me try wrapping: 
```
do { ba = (u16 *)(tmp + (u8 *)dp); } while (0);  // !FAKE: do-while
{
    register u16 *dst __asm__("$4");
    dst = ba;
    ...
}
```
Cheap test.

Also try: `dst = ba;` with the loop inside a do-while(0).

Let me try several:
- i1: do-while around the ba assignment
- i2: do-while around `dst = ba;`
- i3: `dst = ba; src = base;` reorder (put src's copy after dst)
- i4: keep the launder as a real C construct: hmm.

Let me test i1-i3.

Also the c36/dcount swap: the keepalive asm on (c36,dcount) — with it, c36 → v0, dcount → v1. Without, mine has dcount → v0, c36 → v1. Since `df = c36 - dcount`, and the target has c36=v0, dcount=v1.

In the target: `lw v1,0(a0)` (dcount) then `li v0,36` (c36) then `subu v0,v0,v1`. Hmm, c36 (the constant) is in v0 and dcount in v1.

Mine: `lw v0,0(a0); li v1,36; subu v1,v1,v0`. So dcount v0, c36 v1.

A simple swap: swap the assignment statements (`c36 = 0x24;` before `dcount = *dp;`)? I tried h1 — no change (still 18).

Maybe `df = c36 - dcount` → write it as `df = -dcount + c36;`? Hmm, that changes the subu operand order → `subu v0,v1,v0`? The target: `subu v0,v0,v1` where v0=c36, v1=dcount. If I write `df = c36 - dcount`, gcc assigns... the allocator picks.

What if `c36` is used first: `tmp = (c36 - dcount)`... same.

Let me try `df = -(dcount - c36);`? That's not real C equivalence... it is (arithmetically), but ugly.

OK let me first test the ba/cse idea.

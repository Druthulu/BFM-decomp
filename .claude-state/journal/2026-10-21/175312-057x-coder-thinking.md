---
ts: 2026-10-21T23:53:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_sa0nohYuUvW6Nq4x4oag
---
The target for func_800D0D7C (51 insns). Key features:
- `or a3,v1,v0` → now = D_80078EB0 | (D_80078EB1 << 8) in a3 ($7). So `now` is in $7 (a3).
- `move a2,a3` → r = now + zr → a2 ($6) = a3. So `r = now + zr` compiles to a MOVE (because zr=$0, so it's just a copy). So the pin $0 is needed to produce `move a2,a3` rather than gcc reusing a3.
- `move t0,a0` → h = arg0 + zr → t0 ($8) = a0.
- `addiu t0,a0,1` → h = arg0+1.

So the pin produces copies. Without the pin (using plain `r = now;`), gcc would just use a3 directly (no move) → mismatch. Hmm. But maybe we can get the copies another way: e.g., `r = now + 0;` → gcc folds to `r = now` (no move). Hmm.

How to get `move a2,a3` in real C? The classic trick: make the value's live range overlap so gcc must copy. E.g. `r = now;` where `now` is used later — the copy appears if `now` is still live. But in the target, a3 (now) IS used later: `andi v1,a3,0xff00` at cd4 and cf0. So `now` stays in a3 and `r` is a copy in a2. That happens naturally if `r` is assigned from `now` and both are live.

So: `now` is a variable (in a3) and `r` is a variable (in a2), and `r = now + zr` — the `+ zr` is what forces the copy! Without the `+ zr`, `r = now` would be coalesced (r and now share the reg) — no, they're both live so gcc would need a copy anyway... Actually if `r = now` and both are live afterwards, gcc's copy propagation would make r's pseudo = now's pseudo → no copy, and r would be in a3. Then `move a2,a3` wouldn't exist.

Hmm! So we need r to be a DIFFERENT pseudo from now. `now + zr` forces that (the addition creates a new value). But `now + 0` → gcc folds to now → same pseudo.

Hmm. So how to write it in C without a pin?

Option: `r = now + zr` where zr is a variable that's always 0 but not a constant → e.g. `zr` is a global `extern s32 zr;` with value 0? Then `now + zr` → gcc loads zr → not a copy.

Option: use `now | 0`? folds.

Hmm. What about making r's definition come from a different expression that yields the same code: `r = now + zr` with zr being a *local* variable assigned 0? `s32 zr = 0; r = now + zr;` → gcc folds to now → same pseudo.

Hmm. But wait: what if `zr` is a local variable that gcc can't prove is 0? Like `s32 zr; zr = 0;` — gcc's flow knows it's 0 → folds.

Hmm. So how did the ORIGINAL source produce `move a2,a3`?

Maybe the original was:
```c
u32 r = now;   /* where now is a local */
```
and gcc did NOT coalesce because... hmm.

Actually: think about `h = arg0 + zr;` → `move t0,a0`. Here h = arg0 (a copy). Then later `h = arg0 + 1` → `addiu t0,a0,1`. So h is a variable (t0) assigned arg0 first, then arg0+1. The copy `move t0,a0` exists because h is multi-set!

AH, that's the key: h has 2 sets (arg0, then arg0+1) → the first set is a copy from a0 into t0. Similarly r has 2 sets (now+zr, then the branch arms) → the first set is a copy from a3 into a2.

So the `+ zr` may be irrelevant! The copy comes from the multi-set nature. But the CURRENT source uses `r = now + zr` — with `zr` pinned to $0, gcc computes `now + 0` → does that produce a copy? gcc would optimize `x + 0` → x, making r's pseudo = now's pseudo → no copy → r would be in a3. But the pin makes `zr` a hard reg $0 so `now + $0`... hmm, gcc's combine would still fold `plus now, 0` → now. Unless the register variable $0 prevents folding (a reg with a fixed value isn't known to be 0 at compile time — gcc treats `$0` as a hard reg whose value is unknown! Actually $0 is the zero register; gcc 2.7's combine might not know that).

So: `r = now + zr` with zr=$0 → gcc keeps `adddu a2,a3,$0`? But the target shows `move a2,a3` (or a2,a3 = addu with $0 → "move" encoding). YES: `move a2,a3` in MIPS is `addu a2,a3,$0` (or `or a2,a3,$0`). objdump prints `addu`/`move`? The encoding 0x00e03021 = `or a2,a3,$0`? Let me decode: 0x00e03021: opcode 0 (special), rs=0 ($0), rt=6 (a2), rd=7 (a3), funct=0x21 (or). So it's `or a2,a3,$0` — the "move" form! objdump prints "move" for `or rd,rs,$0`.

So the target has `or a2,a3,$0` — a real $0 addend. That's exactly the "$0 zr pin" pattern! So the pin IS what generates it, and the target genuinely has an `or reg,reg,$0` instruction.

Hmm, so the original source had something like `r = now + zr` where zr is a variable that gcc believes is 0 but is NOT a compile-time constant...

Hmm, but the original source wouldn't have had `register s32 zr __asm__("$0")`. The FAKE pin was added by the project to reproduce the target. So the original source had something else that produces `or a2,a3,$0`.

What C produces `or rd,rs,$0`? A bitwise-or with 0: `x | 0` → gcc folds to x. Hmm.

What produces `move`? `or rd, rs, $0` is also produced by a plain register copy! gcc 2.7's "move" is `or rd,rs,$0`. And a plain copy `a2 = a3` would be emitted as `or a2,a3,$0` too!

YES! In MIPS gcc, a register-to-register move is `or rd, rs, $0` (for non-SImode) — and objdump prints it as "move". Hmm, actually objdump prints `move` for the `or rd,rs,$zero` pattern. So `move a2,a3` = `or a2,a3,$0` — a normal copy!

Hmm, but then the `sll v0,v0,0x8` at cac is `sll v0,v0,8` — that's the `D_80078EB1 << 8`.

OK so `move a2,a3` is just a copy. And `move t0,a0` is a copy of arg0.

So the pin `$0` may be unnecessary IF the copies arise naturally.

Let's test: rewrite without the pin:
```c
s32 func_800D0D7C(s32 arg0, s32 arg1) {
    extern u8 D_80078EB0;
    extern u8 D_80078EB1;
    u32 now;
    u32 r;
    s32 h;
    now = D_80078EB0 | (D_80078EB1 << 8);
    r = now;
    h = arg0;
    ...
}
```
Would gcc produce `move a2,a3`? If r and now are separate pseudos both live → yes, a copy. But gcc's cse would propagate now into r, making them the same value → r's pseudo = now's pseudo → both in a3, no copy. Hmm.

Unless `now` is used after r's assignment in a way that keeps them distinct... they'd still be coalesced.

Hmm, but the original source might have had the +0 written as an addition of a variable that's zero. Like `r = now + zero;` where `zero` is a local `s32 zero = 0;` — folded.

Hmm, what if the original had `r = now + zr` where zr is a *macro* for 0? Then gcc folds it and r == now (same pseudo) → no copy. But the target HAS a copy. So in the target, r and now are distinct pseudos.

Wait — are they? Let's look: a3 holds `now` (or a3 holds r?). The insns:
```
or a3,v1,v0        <- now = D_80078EB0 | (D_80078EB1<<8)
move a2,a3         <- a2 = a3
andi v0,a2,0xff
andi v1,a1,0xff
sltu v0,v0,v1
bnez v0, ce0
move t0,a0         <- t0 = a0
subu v0,a2,a1
andi v0,v0,0xff
andi v1,a3,0xff00
...
ce0: subu v0,a1,a2
...
cf0: andi v0,a3,0xff00
cf4: or a2,v1,v0      <- a2 = ...
```
So a2 = r, a3 = now. They're distinct. And `now` is used at cd4/cf0 (`now & 0xFF00`).

So r and now are distinct pseudos. Why? Because `r = now + zr` with zr unknown-to-gcc-0? With zr = $0 hard reg, gcc can't fold `now + $0`? Actually combine would fold `plus now, 0` only if the addend is a constant 0, not a register. A register addend $0 is not folded by combine (it doesn't know $0 is zero at RTL level — actually gcc 2.7 might have a pattern). So `now + zr` → `or a2,a3,$0`? Hmm, the add of $0 with `add` instruction would be `addu a2,a3,$0` = 0x00e03021? Let me decode 0x00e03021: bits: opcode=0, rs=0b00000 (bits 21-25 = 0), rt=6 (bits 16-20 = 6), rd=7 (bits 11-15 = 7), shamt=0, funct=0x21 (or). So `or a2,a3,$0` — that's "move". If it were `addu`, funct would be 0x21? No: addu = funct 0x21, or = funct 0x25. Let me redo: MIPS SPECIAL funct: 0x20=add, 0x21=addu, 0x25=or. So funct=0x21 → addu. And 0x00e03021: let me recompute the fields. 0x00e03021 = binary: 0000 0000 1110 0000 0011 0000 0010 0001.
- opcode (31-26) = 000000 = SPECIAL
- rs (25-21) = 00111 = 7 → $7 = a3
- rt (20-16) = 00000 = 0 → $0
- rd (15-11) = 00110 = 6 → $6 = a2
- shamt (10-6) = 00000
- funct (5-0) = 100001 = 0x21 = addu

So `addu a2,a3,$0` — an add with a zero addend! That's the classic "add with $0" which gcc uses for a copy when the source is a general register (it uses `addu` or `or`).

Hmm, actually a plain copy in gcc MIPS is `or rd,rs,$zero` (funct 0x25). Here we have addu (funct 0x21) with a $0 addend — that's the "+ zr" pattern, NOT a plain copy.

Compare with `move t0,a0` at cc8: 0x00804021 → funct = 0x21 = addu, rs=0 (a0), rt=0 ($0), rd=8 (t0). So `addu t0,a0,$0`.

And the disassembly prints "move" for `or rd,rs,$0`? Hmm, objdump prints "move" for `or $rd,$rs,$zero` (funct 0x25) and also for `addu rd,rs,$zero`? GNU objdump for MIPS prints "move" when the instruction is `or rd,rs,$0` (bitwise or with zero) AND ALSO for `addu rd,rs,$0`? Actually objdump's MIPS printing: for SPECIAL funct 0x21 (addu) with rs==0, it prints "move". Yes! GNU objdump prints "move" for addu rd,rs,$zero. Let me confirm: in binutils opcodes/mips.c, there's a check: if the instruction is `addu`/`or` with one operand being $zero, print "move". I believe for MIPS, `move` is printed for `or $rd,$rs,$0` and for `addu $rd,$rs,$0`? Hmm.

Given the target has `addu a2,a3,$0` (a 3-operand add with $0), that's the "+ zr" pattern — i.e. the PIN IS GENUINE for this instruction! The original source must have had an addition of a zero-valued expression that gcc kept as an add.

Hmm, but wait: `move a2,a3` — if it were a plain copy gcc would emit `or a2,a3,$0` (funct 0x25) not `addu`. objdump prints "move" for both, but the WORD differs and the scorer compares words! So the target's word 0x00e03021 = addu with $0.

So the target really has `addu a2,a3,$0` — an add with a zero addend, which gcc only emits if the source C had an addition whose addend gcc couldn't fold to a constant.

So the original source likely had: `r = now + zr;` where zr is a variable known to be 0 at runtime but not at compile time. E.g., a global variable? Or... hmm.

Hmm, but the project marked this pin as "!FAKE: pin $0 — NEEDED DIFFERS". The FAKE pins are the ones the project added because the real source didn't have a `register` asm. So the real source had SOMETHING that yields `addu rd,rs,$0`.

What C yields `addu rd,rs,$0`?
- `x + 0` → folded.
- `x + z` where z is a variable with value 0 → gcc loads z, no.
- `x | 0` → folded to x → `or`? no, folded.
- Hmm, `x + 0` where 0 is `0L`? same.

Hmm, what if the value 0 comes from a *cast*? e.g. `(s16)0`? folded.

Hmm, what about the possibility that the addend is $0 because the original source used a variable that gcc placed in $0? No.

WAIT. Maybe the original had a *different* structure: `r = now + zr` where `zr` was `s32 zr = 0;` — no.

Hmm, let me reconsider: maybe the original source had the pin-free equivalent: `r = now + 0;` but with `now` being a `u32` and 0 an `int` → `now + 0` → gcc's combine: `plus (reg) (const_int 0)` → folds to the reg. So `r` and `now` become the same pseudo → one register, no add.

Unless the fold doesn't happen because `r` and `now` have different types! E.g. `now` is u32 and `r` is s32? Hmm, `r = now + 0` with r being s32: the value is the same bits.

Hmm, what if `r` is a *different* width, e.g. u16? Then r = now + 0 would truncate → an extra operation.

Hmm, let's look at the target more: after `move a2,a3` (a2 = now), `andi v0,a2,0xff` → r & 0xFF. So r is 32-bit.

Hmm OK, so how do we get `addu a2,a3,$0` in real C?

IDEA: `r = now + zr` where zr is a **volatile** global or a function's return? e.g. `r = now + f()` — no, that'd be a call.

IDEA: `now` is a `u32` and `zr` is `s32` → the addition is SI, fine.

IDEA: What about `r = now + (s32)0`? folded.

Hmm. What if `zr` is a *parameter* or a variable that gcc treats as unknown but happens to be 0 at runtime? The source would need such a variable. Looking at the source: `u32 dead[2];` — an unused array! Interesting: `dead[2]` is declared but never used. Maybe in the ORIGINAL source, `dead` was used as the zero source!

Hmm: `dead[2]` is a local array, never referenced. gcc would allocate it on the stack (frame). If the original had `r = now + dead[0];`... no, dead[0] is garbage.

Hmm. Actually maybe `dead[2]` is a leftover from the project's reverse-engineering.

OK, let me think about "or" instead: maybe the target's `addu a2,a3,$0` could come from a *bitwise or* with 0? `or a2,a3,$0` is funct 0x25 → different word. The target word is funct 0x21 = addu. So it's an addition.

Hmm, so the original had an addition with a zero addend.

Hmm! What about `r = now + zr` where `zr` is declared as `s32 zr = 0;` at FILE scope (a global)? Then gcc can't fold it (it's a global whose value is unknown at compile time... well, a global initialized to 0 IS known to be 0 at compile time! gcc 2.7 would constant-fold `now + zr` where zr is a const global with value 0? gcc 2.7 doesn't do that for non-const globals; `int zr = 0;` is a global with an initializer — gcc 2.7's alias/const analysis: a global with an initializer and never modified is not const (it's not `const` qualified), so gcc would LOAD it at runtime: `lw a0, zr; addu a2,a3,a0`. ✗ (extra insn).

Hmm.

What if `zr` is a `const s32 zr = 0;`? gcc folds it.

Hmm.

OK, so how about: the addition's addend is a REGISTER that happens to be $0 in the final allocation. I.e., the original code was `r = now + z` where z is some variable, and gcc allocated z to $0 (the zero register)? gcc never allocates a variable to $0.

Hmm. So the $0 addend must come from the pin.

Wait, unless... the original source is `r = now + zr` where `zr` is a `register` variable pinned to $0 — meaning the ORIGINAL source DID have a register asm! And the "FAKE: pin $0" marker means the project's pin is a guess, and the task is to find the real source. But maybe the real source had exactly this!

Hmm, but the constraint says "no register vars, no __asm__" for my win.c.

Hmm. So the $0 addend must be produced by real C.

What real C produces `add rd, rs, $zero`?
- `x + y` where y is in $0. 
- A copy where gcc chose `addu` instead of `or`: gcc's MIPS `move_reg` pattern is `(set (reg) (reg))` → `move reg, reg` which expands to `or %d0,%d1,%zero`? Actually gcc's mips.md defines:
```
(define_insn "move"
  [(set (match_operand:SI 0 "register_operand" "=d,d")
	(match_operand:SI 1 "register_operand" "0,d"))]
  "addu\t%0,%1,%zero")
```
YES! gcc's MIPS "move" instruction IS `addu %0,%1,%zero`. So a plain register copy compiles to `addu rd,rs,$zero` = the word 0x00e03021!

So `move a2,a3` IS a plain copy. The objdump "move" printing matches.

So the copies are normal. The pin $0 is NOT needed for a copy — it's needed for... hmm, wait. Then why is there a pin at all?

With the pin, `r = now + zr` where zr=$0 → gcc computes `now + $0` → since $0 is a hard reg, gcc emits `addu a2,a3,$0` — the same encoding as a copy! So the pin makes `r = now + zr` look like a copy `r = now`.

WITHOUT the pin, `r = now` → also a copy (if r and now are distinct pseudos) → `addu a2,a3,$0` — the SAME encoding!

So the question is whether r and now remain distinct pseudos without the pin. With `r = now + zr` (zr=$0 hard reg), they're distinct because the addition creates a new value. Without the pin (`r = now`), gcc's copy propagation would merge them → r and now become the same → the copy disappears → r would live in a3 and the `move a2,a3` wouldn't appear.

So the lever: force a copy without a pin.

Trick: make `r` and `now` distinct by type or by an intervening operation. E.g.:
```c
now = D_80078EB0 | (D_80078EB1 << 8);
r = now + 0;   /* folded */
```
Hmm.

What about: `r = now;` but with `now` declared as a *different type* than r, e.g. `u32 now; s32 r;`? Then `r = now` — same bits, but gcc might keep them as distinct pseudos due to type? In gcc 2.7, the pseudo types are the same (int). Hmm.

What about making the assignment go through a `u16`? no.

What about: `r = now & 0xFFFFFFFF;` → folded.

Hmm, what about making `now` a variable that's assigned TWICE? E.g.:
```c
u32 now;
now = D_80078EB0 | (D_80078EB1 << 8);
r = now;
```
Hmm.

Alternatively: what if `r` is assigned from `now` but `now` is ALSO modified later? No, `now` isn't modified.

Hmm. In the target, `now` (a3) is used AFTER r is assigned (at cd4, cf0: `now & 0xFF00`). And `r` (a2) is also live. So both live → gcc must keep two registers. Does gcc copy-propagate r = now? YES, gcc's cse would substitute now's value into r's uses, making r dead → then a2 wouldn't exist.

BUT: cse's copy propagation happens in the `cse` pass with `cse.c: propagate_copy` — it substitutes a register into its copies if the source is not modified. Since `now` isn't modified, r would be replaced by a3's value.

Hmm, but with the pin, `r = now + zr` where zr is a hard reg $0: cse would substitute now into r?? `r = now + $0` — the value isn't just now (from cse's perspective, adding $0 is not a copy since $0 might not be zero at the RTL level... well gcc knows $0 is zero? Hmm, in gcc 2.7 the hard reg 0 is HARD_REGISTER_ZERO? For MIPS, gcc uses $0 as the zero register but the RTL may treat reg 0 as a normal register. In gcc 2.7 for MIPS, `$0` is not a special "zero" pseudo; the machine description has "zero" patterns? Hmm.

Anyway, with the pin, `now + zr` is an add → cse can't propagate → r stays distinct.

WITHOUT the pin, we need another way to keep r distinct from now.

Options:
(a) Make `now` be modified after r's assignment — impossible semantically.
(b) Make r's value not a simple copy: e.g. `r = now + zr` where zr is a real variable with value 0 at runtime.
(c) Make `now` an expression whose value is recomputed.

Hmm, (b): where would a zero-valued variable come from? The source has `u32 dead[2];` — an unused array. Maybe in the original, `dead` was used! But its value is garbage.

Hmm, what about `arg0`/`arg1`? `r = now + arg1`? No, semantics differ.

Hmm, hold on. Let me reconsider: maybe the original source was:

```c
r = now + 0;
```
and gcc did NOT fold it because... `now` is `u32` and `0` is `int` → the addition is done in SI mode; `plus:SI (reg) (const_int 0)` → combine folds. Yeah.

What if the source were `r = now + zr;` where `zr` is a `s32` LOCAL that is never assigned (uninitialized)? Then gcc uses an uninitialized value — undefined but the original source might have had `int zr = 0;`... folded.

Hmm hmm.

WAIT. What if the original source had the addition of a *char* variable or something that's 0?

Let me look at the whole original function's context. Let me look at the source file around line 852 for comments that might explain the pin. The project added the pin with "!FAKE: pin $0 — NEEDED DIFFERS (P36 rung B tus10)". Let me look for nearby comments about this function.

Let me read lines 820-880 of the file.

Also let me look at the header comment for func_800D02D0 (lines 214-275) to see the style.

Actually, let me look at the "moves.md" entry for similar: "pin | func_8017E1D4 | MATCH — $0 zr pin: s16 flag2/3/4 copies (HImode copy a0 = u keeps the move); $18 w pin: ot = inner call split from the return (ot +2 refs > w in greg) (G02)".

So there, the $0 pin was cracked by using s16 copies so the move is kept. The mechanism: instead of `x + zr` (which with the pin gives an add-with-$0 = a move), they used a different C spelling that yields the same move instruction.

In our case: `r = now + zr` with zr=$0 → `addu a2,a3,$0` (a copy!). We need real C to produce a copy of now into a2. That's just `r = now` — but then cse propagates.

Hmm, unless cse does NOT propagate because of the `& 0xFF00` uses of now... no, propagation substitutes the value.

Hmm, but hold on: would cse really merge them? Let's test empirically! Write:
```c
r = now;
```
and see the score. Actually, let's think about what gcc 2.7's cse does: it has `propagate_copy`? Actually gcc 2.7's cse.c does have copy propagation via `find_duplicate_insn` → if the insn is a copy `(set (reg) (reg))` and the source reg is not modified later, then subsequent uses of the dest are replaced by the source. Yes, cse.c does that.

BUT: the copy `r = now` happens where `now` is live across the copy and used later. cse would substitute now for r. Then r's pseudo is dead → r's register = now's register = a3. And then the code would use a3 where a2 was expected → the target's `move a2,a3` missing and `andi v0,a2,0xff` becomes `andi v0,a3,0xff`.

Hmm. So how to prevent the propagation?

IDEA: Use a `volatile`? No (barrier lever, and kinds=pin only; adding a barrier would be a new lever — not allowed).

IDEA: Make the copy go through a *wider* type so the value differs in representation. E.g. `r` is `u32` and `now` is `s32`? no.

IDEA: Make `now` a value that gcc recomputes. Hmm.

IDEA: What if the assignment is `r = now + 0` where `now` is u32 and 0 is a *long*? Then the addition is in DI mode → gcc would convert... hmm, on MIPS32 long is 32-bit. `now + 0L` → SI. Folded.

IDEA: use `r = now * 1;` → gcc folds mult by 1 → copy. Hmm, but does gcc's combine fold `mult by 1`? YES → copy → then cse propagates.

IDEA: `r = now / 1`? folds.

IDEA: What if `now` is assigned AFTER r? No.

IDEA: What if `now` is a *volatile* global? no.

Hmm, IDEA: make `now`'s value used in a way that requires it to be in a specific place... 

BIG IDEA: What if we make `now` an expression used TWICE, and r assigned from a temp:
```c
now = D_80078EB0 | (D_80078EB1 << 8);
r = now;
```
vs
```c
r = (D_80078EB0 | (D_80078EB1 << 8));
now = r;   /* hmm, then now = r, and cse propagates r into now's uses */
```
Hmm.

Hmm, what if `now` is used in a place where it must be recomputed... 

OK, let me look at the ACTUAL original source! This is a decompilation project; maybe there's a reference implementation or the original game's source in the repo (e.g. in .run/P35 or research). Hmm, we shouldn't read research/. But maybe the original PSX source is available? Unlikely.

Let me instead look at the src file's comments around this function — the project may have documented the pin's purpose.

Let me read lines 820-880.

Actually, let me reconsider: maybe there IS no need to prevent cse propagation, because the two are used differently. Let me look at the target again:

```
or a3,v1,v0        ; a3 = now
move a2,a3         ; a2 = r   (copy)
andi v0,a2,0xff    ; r & 0xFF
andi v1,a1,0xff
sltu v0,v0,v1
bnez v0,ce0
move t0,a0         ; t0 = h = arg0
```
and later `andi v1,a3,0xff00` (now & 0xFF00) and `andi v0,a3,0xff00`.

So `now` (a3) and `r` (a2) are both live across the branch. If cse merged them, we'd see a3 used for both.

Now: is there a C form where the copy is preserved? What if `now` is assigned in a way that makes gcc treat it as "modified" — e.g. `now` is set to a value and then r = now, and `now` is used in the branch... 

AH WAIT!!! What about the possibility that `now` is not a variable at all in the original, but the *value* `now` is used in two places and gcc CSE'd it into a3 (a common subexpression)! I.e.:

```c
r = D_80078EB0 | (D_80078EB1 << 8);
...
r = ... 
```
Hmm. Let's think: if the original source were:

```c
u32 now = D_80078EB0 | (D_80078EB1 << 8);
u32 r = now;
```
gcc computes the OR into a3 (a temp for the expression), then copies to... hmm.

Actually, maybe the original is:
```c
now = D_80078EB0 | (D_80078EB1 << 8);   /* now = a3 */
r = now + zr;                            /* r = a2 (copy) */
```
and the ORIGINAL had `zr` as a **macro** `#define zr 0`? Then `now + 0` folds and r == now → same pseudo. Hmm.

Alternatively the original might have had:
```c
r = now;
```
and gcc DIDN'T propagate because `now` is `u32` and `r` is `s32`?? Let's think: `now` is u32, `r` is u32 in the current source. If `r` were s32 and now u32... the pseudo types are all `int` in gcc 2.7 (SI). So no.

Hmm, BUT: what if `r` and `now` have different live ranges such that gcc's cse propagation is blocked? cse propagates a copy into subsequent uses of the destination until the source is modified. `now` is never modified after its definition. So r's uses all become now's uses. Then r is dead.

Hmm, unless `now` is modified! Look at the source: `now` is never modified. But what if the ORIGINAL source modified `now`?? No, the target shows now unchanged (a3 & 0xFF00 used twice).

Hmm, hmm. What if the ORDER is different: what if `now` is assigned AFTER `r`? Like:

```c
r = D_80078EB0 | (D_80078EB1 << 8);   /* r = the OR value */
now = r;    /* hmm */
```

Let's think about the target's structure:
```
or a3,v1,v0      ; a3 = D_80078EB0 | (D_80078EB1<<8)   [the "now" value]
move a2,a3       ; a2 = a3
```
The `or` computes into a3 directly (not into a2). So a3 is the "now" pseudo and a2 is "r".

Alternatively, maybe the original source is:
```c
now = D_80078EB0 | (D_80078EB1 << 8);
r = now;   /* r gets a copy because ... */
```
and gcc did NOT propagate because `now` is USED in the branch arms after r's redefinition. But cse propagation is about the VALUE of now, not its register.

Hmm, unless gcc's cse doesn't propagate when the copy is "not a simple copy"? 

AH WAIT. What if the original source was:
```c
r = now & 0xFFFFFFFF;   /* u32 mask -> folded */
```
no.

What about:
```c
r = now | 0;    /* or with 0 → gcc: (set (reg) (ior (reg) (const_int 0))) → combine folds ior with 0 → copy */
```
folded.

Hmm.

OK, RADICALLY DIFFERENT IDEA: what if `now` is a **function parameter** or the original code used a struct/array? Hmm.

What if the original source had the two variables swapped in meaning? Like:
```c
u32 r = D_80078EB0 | (D_80078EB1 << 8);   /* r = a3 initially */
u32 now = r;                                /* now = a2?? */
```
Hmm, that gives a3=r, a2=now. Then `andi v0,a2,0xff` would be `now & 0xff` and `andi v1,a3,0xff00` would be `r & 0xff00`. In the source, `r & 0xFF00` is used in the branches (`r = ((r - arg1) & 0xFF) | (now & 0xFF00)`), and `r & 0xFF` is used in the comparison. So the variable used with &0xFF00 is `now`, and the one with &0xFF is `r`. Target: a2 (=r) is used with &0xff ✓ and a3 (=now) with &0xff00 ✓. So a3=now, a2=r ✓ as I had.

So the original: `now` computed first into a3, `r` a copy in a2.

Hmm, so how do we get a copy that survives cse?

IDEA!!! What if `now` is assigned inside the FIRST if-condition... no.

IDEA: What if the source is:
```c
now = D_80078EB0 | (D_80078EB1 << 8);
r = now;
h = arg0;
```
and cse propagates r→now... but then a2 wouldn't exist.

Hmm, BUT: does it matter? Let's just TRY it and see the score. Empirical! Maybe gcc's cse doesn't propagate here (e.g., because `now` is used inside a branch and the copy is in a different block). Actually! cse propagation happens within basic blocks; `r = now` is at the top and r's uses are in different blocks (the if/else arms). gcc's cse (2.7) does propagate across blocks? The `cse` pass in gcc 2.7 processes the whole function but propagation across basic blocks is limited (the "cse2" pass does more). Hmm! Actually gcc 2.7's cse.c `propagate_copy` does work across basic blocks within the same "life range"? I recall gcc 2.7's cse has a `copy` table with `equiv` handling.

Let's just TEST: write the candidate without the pin and see.

Also `h = arg0 + zr` → `move t0,a0`: h is multi-set (arg0, then arg0+1) so the copy is natural. ✓ So for h, removing the pin should be fine: `h = arg0;`.

So the candidate:
```c
s32 func_800D0D7C(s32 arg0, s32 arg1) {
    extern u8 D_80078EB0;
    extern u8 D_80078EB1;
    u32 now;
    u32 r;
    s32 h;
    u32 dead[2];
    now = D_80078EB0 | (D_80078EB1 << 8);
    r = now;
    h = arg0;
    if ((r & 0xFF) >= ((u32)arg1 & 0xFF)) {
        r = ((r - arg1) & 0xFF) | (now & 0xFF00);
    } else {
        r = ((0x3C - (arg1 - r)) & 0xFF) | (now & 0xFF00);
        h = arg0 + 1;
    }
    if (((r & 0xFFFF) >> 8) >= ((u32)h & 0xFF)) {
        r = ((((r & 0xFFFF) >> 8) - h) << 8) | (r & 0xFF);
    } else {
        r = ((0x18 - (h - ((r & 0xFFFF) >> 8))) << 8) | (r & 0xFF);
    }
    return (s16)r;
}
```

Let me score that. Let me also try `r = now + 0;` variants later.

Let me set up the item dir and write orig.c + c1.c.

Note: for a non-header TU, the body is spliced into src/resident/resident_jr_800D00E4.c, replacing the function definition. The body must be the function definition only (with the externs inside the body, as in the source).

Let me write andscore.

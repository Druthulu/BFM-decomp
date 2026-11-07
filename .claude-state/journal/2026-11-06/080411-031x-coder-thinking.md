---
ts: 2026-11-06T15:04:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Y1LUTPbv95WxvqVdFj7W
---
Line 134 is key: "WALL cse-copy-merge — target `move v1,v0` is `plus v,$0`: a hard-reg addend combine cannot fold, so cse keeps the copy; a C-level zero is a constant -> combine folds -> cse propagates (best 2)". Hmm.

Line 151: "const-fold-return — combine folds the const 1 into the return copies".

So const folding by combine is the issue. Our case: combine folds `s0 << 10` where s0 has a known value 0 → `move a0,zero`. Wait, actually the shift by constant 10 of 0: combine uses `simplify_shift_const`? Hmm.

Actually, maybe the folding happens in flow: `s0` is a constant (0) and the shift is folded by flow's constant propagation. The launder makes s0 a variable.

Plain C alternative to make s0 opaque: the moves catalog shows "real 2nd set" and "u16/s16 widths", "init at decl", "do-while". 

Hmm. What if s0 is declared `s16` and assigned 0? Then `s0 << 10` — gcc would need to sign-extend, maybe emits `sll a0,s0,0xa`? Let's think: if s0 is s16 in a register, gcc must sign-extend before shift? Actually HImode in register, `s0 << 10` promotes to int: sign extend then shift. But since s0=0 known, folds anyway. However, moves line 97: "loop counter declared s16 + t0--; while (t0 >= 0) (HImode add: no SImode copy class, sll reads v0)". That cracked a launder where the issue was a copy class, not const folding.

Let me just test some candidates empirically — that's fastest. Candidates:
1. s0 declared s16 (with s0=0).
2. move s0 = 0 assignment into a do-while(0) block.
3. compute a0 = s0 << 10 via `a0 = (s0 + 0) << 10`? no.
4. `a0 = s0 * 1024`? no.

Actually, wait. Another idea: make `s0 = 0` happen in a way that its constantness is lost — e.g., `s0 = 0; ...` then a call in between? What if we move `s2 = (s32)D_8019B538;` after `a0 = s0 << 10;`? That doesn't matter for const-prop.

Hmm, what if we initialize s0 from the loop itself: change to a `while` that assigns at the bottom... 

Let me think about the actual target more: the launder is at a specific point (after s2 load, before a0 shift). What if we replace it with a *real* operation on s0 that is value-preserving but opaque to combine? E.g., `s0 = s0 + (s2 - s2)`? folds. `s0 = s0 ^ (s2 ^ s2)`? folds maybe not! gcc can't know s2==s2? Actually it can.

What about `s0 = s0 & ~(s2 - s2)`? folds.

What about `s0 = s0 | (s2 & 0)`? folds.

Hmm, gcc 2.7.2's folding is limited. Something like `s0 = s0 * (s2 - s2 + 1)`? combine might fold.

Actually there's a classic: `x = x - x;` folds to 0.

Hmm. What about making s0 = 0 not provable: `s0 = 0; s0 = s0 << (s2 & 0);` — the shift count is 0 at runtime but gcc may not know s2&0 = 0? It should fold s2&0 to 0.

Try `s0 = s0 >> 1;` → 0. folds.

OK, empirical testing is better. But each test is a compile (~a second). Let me generate candidates quickly.

Candidate A: s0 declared s16.
Candidate B: `do { s0 = 0; } while (0);` around init.
Candidate C: compute a0 via a temp `s32 t = s0; a0 = t << 10;` (probably folds).
Candidate D: `a0 = s0 << 10;` after a dummy `s0 = s0 + (s1 - s1);`? hmm.
Candidate E: change the loop to use a pointer or different shape.

Wait, actually — maybe a much simpler idea: the target's pre-loop sll might be the *same* statement as the loop-bottom one if the loop is rotated differently. What if we write the shift at the *end* of a `while` loop with the counter starting at -1?

```
s0 = 0;
a0 = s0 << 10;
do { ... a0 = s0 << 10; } while (s0 < 4);
```

What if instead:
```
s0 = 0;
do {
   ...
   s0 = s0 + 1;
   a0 = s0 << 10;
} while (s0 < 4);
```
and use a0 before assignment on first iteration? Not valid C semantics but gcc would produce garbage.

Alternative: write it as:
```
s0 = 0;
do {
    a0 = s0 << 10;
    ...
} while (++s0 < 4);
```
Hmm — `a0 = s0 << 10` at loop top with s0 unknown inside loop (well, after first iteration s0 is known? gcc doesn't do that). But then only one sll in the loop; the first iteration's sll would be at the top, and gcc would still const-fold the first entry? No — at loop top, s0 is a loop variable; gcc's cse could know on the first iteration s0=0 and propagate? Typically gcc's constant propagation at loop top doesn't know the entry value unless it unrolls. But cse/combine might have reg_known_value from the init propagated into the loop? In a do-while, the loop body executes with s0=0 on entry; gcc's reg_known_value analysis (via reg_equiv or reg_known_value) is flow-based and would know s0=0 at the top of the loop only if it can prove the loop-carried value is 0... it can't, since s0 increments. So at the loop top s0 is not known constant. Then `a0 = s0 << 10` at loop top stays sll. And reorg may steal it into the bnez delay slot for the back edge, but the first iteration's sll would be... hmm, the loop top insn executes on first entry too, at the position 1f68-ish. But target has TWO sll: one before the loop (1f68) and one in the delay slot (1fa8). If a0 = s0<<10 is at the loop top, there's one static sll at the top; reorg can't steal it into the delay slot because the delay slot is at the bottom and stealing from the top means moving an insn from the branch target to the delay slot — that's legal if the target insn is the first of the target block and safe. If stolen, the top no longer starts with sll, and the delay slot has it. That gives: at 1f68 (loop entry falls through from prologue) — the first iteration would NOT execute the sll because it was stolen to the delay slot! That would be wrong (a0 used before set in first iteration). Actually reorg wouldn't steal it because a0 is used in the loop before being set on the first path. Hmm, the loop body uses a0 at `a1 = a1 + a0` after the sll, so a0 must be set. So reorg can't steal from the top.

So target's two sll: pre-loop + loop-bottom. This is the loop-carried form. Confirmed.

Therefore we must make the pre-loop `a0 = s0 << 10` not fold. 

Let me think about gcc 2.7.2 internals: The fold of `s0 << 10` with s0=0 probably happens in `combine` or in `cse`'s `simplify_binary_operation`? Actually gcc 2.7.2 has "flow" pass doing constant propagation of registers with REG_EQUAL/REG_KNOWN_VALUE... In 2.7.2, the relevant pass is `combine` (combine_regs?) or `cse`'s `fold_rtx` which uses reg_known_value. `fold_rtx` in cse.c folds constants. cse records reg_known_value for registers set to constants, and fold_rtx substitutes them. So cse's fold_rtx sees s0's known value 0 and folds the shift to 0.

To defeat cse's fold_rtx: make s0 not have a single known constant value, e.g., a second set somewhere. The classic "real 2nd set" trick! If s0 has two sets (one being 0), cse's reg_known_value for s0 is only set if... Actually cse sets reg_known_value from `set` insns it processes; if there are multiple sets with different values, it invalidates. The launder was an asm set (unknown value) → reg_known_value for s0 invalidated.

So: give s0 a second set with a non-constant value that is nonetheless 0 at runtime, placed *after* `s0 = 0` and before the shift, and ensure gcc doesn't fold that second set's expression to 0.

What non-constant expression is 0 at runtime? `s0 = s0 & 0;` → folds to 0. `s0 = s0 * 0;` folds. Hmm.

We need something cse can't prove 0 but is 0. E.g., `s0 = s1 - s1;`? cse knows s1-s1 = 0 → folds. `s0 = s1 ^ s1`? folds.

What about `s0 = (s32)(u16)(s1 - s1)`? folds.

What about `s0 = (s1 & 0)`? folds.

What about using a *loaded value* known to be zero? E.g. a global that is 0? Not safe semantically (it's a game's data).

Hmm, what about a value derived from a function argument? Not zero.

What about making the *initial* value come from the loop's previous... 

Alternative: restructure so that the pre-loop sll's operand is genuinely not a constant: use the loop-carried variable itself! E.g., unroll the first iteration:

```
s0 = 0;
a0 = s0 << 10;
do { body; s0++; a0 = s0<<10; } while (s0<4);
```
→ replace with:
```
s0 = 0;
a0 = 0;         // constant
do { ... }
```
no.

Hmm, but what if we compute a0 differently: `a0 = s0 << 10;` where s0 is initialized from a value the compiler can't fold: e.g., `s0 = 0;` but then `s0 = (s0 + 0x1000) - 0x1000;`? combine folds.

gcc 2.7.2's cse fold_rtx handles plus/minus chains. What about a multiplication: `s0 = (s0 + 0x1000) * 1;`? folds.

What about a *division*: `s0 = s0 / 1;`? folds. `s0 = s0 * 0x10000 >> 16`? The shift of 0... folds.

What about a bitfield read? `struct {s32 a:1;} ...`? Hmm, reading a bitfield from a local struct: `s0 = bf.a;` where bf.a = 0 set earlier — gcc may fold or use memory.

What about using a pointer cast of the address of a stack array that's zero? Not initialized.

Honestly, maybe the intended crack is something else entirely: perhaps the target's sll is achievable by removing the *pre-loop assignment* and instead making the loop-bottom assignment produce both via rotation. Wait — what if we write:

```
s0 = 0;
a0 = s0 << 10;
```
→
```
s0 = 0;
a0 = (s0 << 10);
```
same.

Hold on. Let me reconsider the diff. Mine without launder:
1f64: move a0,zero
1f68: sw ra
1f6c: sll v0,s0,0x1

Target:
1f64: sw ra
1f68: sll a0,s0,0xa
1f6c: sll v0,s0,0x1

So target has the sll right where mine has sw ra. What if the sll in target is actually the loop-bottom sll of the *previous* iteration... no, there's no previous.

Alternatively — what if the target's pre-loop sll is not from source `a0 = s0 << 10` but the *initial* a0 computed inside the loop and then the loop was rotated so the shift appears before the loop? gcc doesn't rotate loops here.

Hmm, what if the source is:
```
s0 = 0;
a0 = 0;  // constant 0
```
then gcc emits move a0,zero. Target emits sll. So target's source definitely had a real shift with a non-constant operand (the asm).

OK so the task is exactly "defeat cse fold_rtx's const-prop of s0". Let me look for what plain C defeats fold_rtx. fold_rtx uses reg_known_value[reg]. reg_known_value is set in cse_main for insns `(set (reg) (const))`? Let me check gcc-2.7.2/cse.c for reg_known_value.

Let me grep.

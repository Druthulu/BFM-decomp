---
ts: 2026-10-22T00:15:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_FFx1QcpHqahbfxnAxsJ8
---
func_80181E64: score 3! The diff:
mine[15] = `andi s8,v0,0xfff` vs target[15:17] = `andi v0,v0,0xfff; move s8,v0`.

So the target has the opaque copy `move s8,v0` (the `t = v + zr` copy)! And mine folds it (t = v directly, t in s8).

So the ONLY difference is the opaque copy. Score 3 = the missing copy + the j offset.

So: I need `t = v + <opaque zero>`.

Hmm! So the whole item hinges on the opaque copy. Hmm.

Hmm, so close. Let me think REALLY hard about how to make gcc keep that copy.

The target: `andi v0,v0,0xfff` (v = the masked value) then `move s8,v0` (t = v, an opaque copy).

The source: `v = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF; t = v + zr;`

Without zr: `t = v;` → gcc propagates v into t (cse) → t is the same pseudo as v → `andi s8,v0,0xfff` (the mask computed directly into t's register).

To keep the copy, we need t ≠ v as pseudos.

**IDEA**: What if `t` is used BEFORE the copy? no.

**IDEA**: What if `v` is MODIFIED after the copy? Then cse can't propagate v into t! Look at the source: v is not used after. But what if the source were:
```c
v = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF;
t = v;
v = something;   /* ✗ changes semantics */
```
✗.

**IDEA**: What if the copy is `t = v` where v is a **parameter or a value with a hard-reg preference**? no.

**IDEA**: what if `v` is declared as `volatile`? ✗ barrier.

**IDEA**: What if we compute the value twice?
```c
v = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF;
t = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF;
```
→ CSE merges them → 1 pseudo ✗.

**IDEA**: what if `t` is assigned BEFORE `v` is modified... no.

**IDEA**: **What if the copy is made opaque by the ORDER: `t` is assigned first from a DIFFERENT expression that is later recognized as equal?** Hmm.

**IDEA**: What if we use a `+` with a zero-valued expression that gcc keeps in a register? We're back to that.

Hmm, hold on!!! What about `t = v + 0` where the `0` is... hmm.

WAIT A MOMENT. What about the **`(u16)` cast**?!

```c
v = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF;
t = (u16)v + zr;
```
Hmm no.

Hmm, what about the moves.md trick: "s16 flag2/3/4 copies (HImode copy escapes cse, combine nonzero_bits -> move)". An HImode copy escapes cse!

In our case: `t = v` where the copy is in SI mode → cse propagates. But if the copy were in a different mode... e.g. if `t` were `u16` and `v` were `u16`:
```c
u16 v;
u16 t;
v = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF;
t = v;
```
Then the copy is `(set (reg:HI) (reg:HI v))` — an HImode copy! Does cse propagate HImode copies? The moves.md says the HImode copy ESCAPES cse. Hmm! But then the generated code would be a 16-bit copy: `move` doesn't exist for 16-bit; gcc would do `sll tmp,v,16; sra tmp,tmp,16` (2 insns) ✗ or `andi` (1 insn: `andi s8,v0,0xffff`)? Hmm, the target's copy is `move s8,v0` (a 32-bit move).

Hmm, but wait: if `t` is u16 but the copy is done as a 32-bit move (because the mode conversion is a no-op)... hmm, gcc 2.7 would insert the conversion.

Hmm, hmm. Let me look at the moves.md example again: "pin | func_8017E1D4 | MATCH — $0 zr pin: s16 flag2/3/4 copies (HImode copy a0 = u keeps the move); $18 w pin: ot = inner call split from the return (ot +2 refs > w in greg) (G02)".

"s16 flag2/3/4 copies (HImode copy a0 = u keeps the move)" — so there, the copy `a0 = u` where u is s16 and a0 is s16: the HImode copy escapes cse and generates a MOVE (32-bit!). Hmm, interesting: an HImode copy between two HImode pseudos generates a 32-bit move? In gcc 2.7, a copy between two HImode regs would be `move`?? Hmm, MIPS has no 16-bit move, so gcc 2.7's move_insn pattern is for SI mode only. For HImode copies, gcc would do the shift pair OR (since both are 16-bit values in 32-bit regs, a plain move suffices — gcc 2.7 might use `move` since the upper bits are undefined for HImode... yes! In gcc 2.7, HImode values live in 32-bit regs with garbage in the upper bits, so a plain move suffices ✓).

So an HImode copy generates `move rd,rs` ✓ — exactly the target's `move s8,v0`!

So the lever: make the copy `t = v` an HImode copy! I.e., declare both `v` and `t` as `s16`/`u16`.

But careful: the target's masked value `andi v0,v0,0xfff` is a 32-bit AND (0xfff fits in 16 bits, but the target uses `andi v0,v0,0xfff` — a 32-bit andi with the mask 0xfff). If v were u16, the mask would be `andi v0,v0,0xffff` (HImode and with 0xfff → gcc would use `andi 0xfff` on a 16-bit value → the upper bits are garbage → the andi would be `andi v0,v0,0xfff`? For an HImode AND with 0x0fff, gcc 2.7 would emit `andi v0,v0,0xfff` (since the value is 16-bit in a 32-bit reg, and the andi clears the upper bits... hmm, actually for HImode, gcc would need to zero the upper 16 bits: `sll v0,v0,16; sra v0,v0,16`? no, that's for sign. For an unsigned 16-bit AND with 0x0fff, the result fits in 12 bits, so gcc could emit `andi v0,v0,0xfff` and the upper bits are zeroed by the andi ✓ (the andi clears bits 12-31 too).

Hmm, but the target's value: `v = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF` — the source computes it as a 32-bit expression. If v were u16, the expression `(*(u16*)... + 0x100) & 0xFFF` in u16 arithmetic: the addition `+ 0x100` in HImode → the result wraps at 16 bits. Hmm, the semantics differ (the original is 32-bit arithmetic). Since the u16 load is 0..65535 and +0x100 could overflow 16 bits... e.g. 0xFF00 + 0x100 = 0x10000 → in 32-bit: 0x10000 & 0xFFF = 0; in 16-bit: 0 ✓ same after the mask. Hmm, actually since the result is masked with 0xFFF, the difference in the upper bits doesn't matter! The value's low 12 bits are the same in both.

Hmm, but gcc's code generation might differ (e.g. the add in HImode might need extra masking).

Hmm, and `t` is used later: `*(s16 *)(arg1 + 0x100) = t;` (a 16-bit store) and `k = func_8004787C(t)` (a 32-bit arg!) and `t += 0x600`.

If t were u16, `t += 0x600` would wrap in 16 bits ✗ (semantics differ: t is used as a 32-bit arg).

Hmm! So t must be 32-bit.

Hmm, but the COPY could be HImode if the SOURCE (v) is 16-bit and the copy is done in HImode then widened. E.g.:
```c
u16 v;
s32 t;
v = (*(u16 *)(arg1 + 0x100) + 0x100) & 0xFFF;
t = v;
```
Here `t = v` is a HImode→SIMode conversion = a zero-extension of the 16-bit value → gcc 2.7 would emit `sll tmp,v,16; sra tmp,tmp,16` (or `move` + `andi`?). Hmm, for an unsigned 16→32 conversion, gcc 2.7 emits `sll tmp,v,16; srl tmp,tmp,16` (2 insns) ✗.

Hmm, unless the value's low 12 bits are all that matter... but the code must match exactly.

Hmm. What if BOTH v and t are `s16`? Then:
- `v = (...) & 0xFFF` in HImode → gcc 2.7: the and with 0xFFF on an HImode value → `andi v0,v0,0xfff` ✓ (the target's instruction!).
- `t = v` → an HImode copy → `move s8,v0` ✓ (the target's instruction!).
- `*(s16 *)(arg1 + 0x100) = t;` → a 16-bit store ✓.
- `k = func_8004787C(t);` → the arg needs the 16-bit value sign-extended to 32 bits → `sll/sra` ✗ (the target has `move a0,s8`? let me check the target).

Hmm! The target: let me look at the target's disassembly for func_80181E64 to see how t is used.

Let me dump it.

Also `t += 0x600` in HImode would wrap ✗.

Hmm, so t must be 32-bit for `t += 0x600` and the call arg.

Hmm. Unless `t` is 32-bit but the COPY is done through a 16-bit temp:
```c
u16 v;
s32 t;
{
    u16 w = v;      /* HImode copy → move */
    t = w;          /* 16→32 zero/sign extension → 2 insns ✗ */
}
```
✗.

Hmm.

Let me look at the target's disassembly to see exactly what's needed.

Let me dump the target for func_80181E64.

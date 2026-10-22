---
ts: 2026-10-22T08:18:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_CQySHlrQpGe22sXgHdhH
---
In x1 (my current structure), gcc put the LOAD in v1 and the copy in a1! And the compare reads v1 (the load) ✓ — interesting! So in the isolated case, the compare DOES read the original.

Hmm, but in the real function the compare read the copy. The difference: in the real function the compare is `v >= 0x801` where v is... hmm, same.

Wait, in x1: `lh v1,0(a0)` (the load in v1), `slti v0,v1,2049` (compare reads v1 = the original ✓), `move a1,v1` (the copy in a1), `addiu v1,a1,-512` (the result in v1 = the original's reg ✓).

That's EXACTLY the target's shape (modulo reg numbers: the target uses v0/v1, x1 uses v1/a1). Hmm, the target: `lh v0,24(a0)`, `move v1,v0`, `slti v0,v0,2049`, `addiu v0,v1,-512`. So the target's load is in v0 and the copy in v1; x1's load is in v1 and the copy in a1.

The register choice differs (v1/a1 vs v0/v1) — probably because in x1 there's no other register pressure... hmm, actually in the real function the diff showed mine had `move v1,v0` and `slti v0,v1,2049` — so mine's load was in v0 and the copy in v1, but the compare read v1.

Hmm, so in the real function, the compare reads the COPY, but in x1 it reads the original. Difference?

In the real function, the second arm repeats the pattern, and there are more variables (dp, p, frame_pad). Hmm.

Hmm, wait. Let me re-read the real diff:
```
replace mine[5:6] target[5:6]
     5  slti v0,v1,2049 | slti v0,v0,2049
```
mine[5] = `slti v0,v1,2049`. And mine[4] = `move v1,v0` (matched the target's `move v1,v0`).

Hmm, so mine: index 3 = `lh v0,24(a0)`, 4 = `move v1,v0`, 5 = `slti v0,v1,2049`.

So in mine, the load is in v0 and the copy in v1, and the compare reads v1 (the copy) — the copy's value.

In x1, the load is in v1 and the copy in a1, and the compare reads v1 (the load).

So in the real function gcc assigned the copy to v1 and then the compare read v1 → i.e. gcc used the COPY's reg for the compare, meaning it substituted the value.

Hmm, so in the real function the substitution happened; in x1 it didn't. What differs?

The real function's v is used AFTER: `v = c - 0x200; *(s16 *)(p + 0xC) = v;` — same as x1.

Hmm! The real function has TWO copies (two arms) and the same variables reused. Also `frame_pad`, `dp`, `p`.

Hmm, let me test the real structure more faithfully in the harness — with the two arms and the second load.

Actually, let me instead try variants directly on the real function (dt.sh takes ~30s each, acceptable).

Variant ideas for 8018302C:
(a) Use separate temps for the two arms (tmp1, tmp2) and separate c vars (c1, c2) — matching the target? The target uses v1 for both copies (the same reg, reused). Hmm, with c1/c2 the second copy would overwrite... hmm.

(b) Make the compare read the original by using a different variable for the copy's source: e.g.
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) { v = c - 0x200; *(s16 *)(p + 0xC) = v; }
```
(current, gives the substitution)

(c) Try declaring v as s16 (like x3 — but x3 gave sll/sra ✗).

(d) Try the compare as `if (v > 0x800)`.

(e) Try making the copy's temp a `u16` and the source... ✗ (andi)

(f) Try putting the copy in a separate block via a goto:
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) { v = c - 0x200; *(s16*)(p+0xC) = v; }
```

Hmm.

Let me think about WHY the real function substitutes. Maybe because of the SECOND arm: the second `v = *(s16 *)(p + 0xD); tmp = (s16)v; c = tmp;` — the second copy is from the same `tmp` and `c` variables. cse might merge the two copies' equivalence classes: `c` is redefined with tmp's value... and the first compare might then read the second c? Hmm, but the diff shows BOTH slti lines differ the same way.

Let me test the real function with SEPARATE variables per arm (tmp1/c1, tmp2/c2) — the "split reused vars" trick that worked for 8017E6EC. But the target reuses v1 for both copies... with c1 and c2 the second copy would go to a different reg? Hmm, in the target, the second `move v1,v0` reuses v1 (the first copy is dead by then). With c1/c2, gcc would allocate c1 → v1 and c2 → v1 (since c1 dies) — same ✓.

Let me try that. Also try: keep `c` shared but `tmp` split.

Let me run a batch of 3-4 real-function variants.

Variant A: tmp1/tmp2 + c1/c2.
Variant B: tmp shared, c1/c2.
Variant C: v1/v2 separate for the loads? Hmm, the target uses v0 for both loads (reused).

Let me try A and B.

Actually, wait. Let me think about the substitution differently: maybe gcc substituted because in the real function, the compare's operand `v` is DEAD after the compare on the fall-through path, and the copy `c` is live → gcc's "prefer the live value" logic (in local-alloc/combine) replaced the compare's operand with c.

In x1, the same structure held but the compare read the original. Hmm, but in x1 the load was in v1 and the copy in a1 — so the compare read the load's reg (v1) and the copy went to a1. Hmm, so in x1 there was NO substitution.

The difference between x1 and the real function... hmm! In the real function, `c` is declared BEFORE `v`? Let me check my c1.c: `s32 v; s32 c; s16 tmp;` — v first. In x1: `int v; int c; short tmp;` — same order.

Hmm, the real difference: the real function's copy is `c = tmp` where tmp = (s16)v, and v = *(s16*)(p+0xC) — the load is of an s16 → v's value is sign-extended. Same as x1.

Hmm, what else? The real function has `frame_pad[3]` and `(void)&frame_pad;` — the frame! The target has `addiu sp,sp,-16` (a 16-byte frame). The frame_pad array is there to force the frame size. Hmm, could the frame affect the register allocation? Possibly (the frame changes the local-alloc ordering).

Hmm! And in the real function the delay slot of the bnez is `addiu sp,sp,-16`.

Hmm, let me test the real function with variants and observe. Let me be systematic but quick: run 4 variants in one sc.sh call.

A: tmp1/c1, tmp2/c2.
B: tmp1/c2 shared.
C: the current one but with the compare `if (v > 0x800)`.
D: current but with v declared `s32` and the copy `c = tmp` where tmp is declared `s16` — same as current.

Hmm, let me think about D differently: what if the compare reads `c` and the subtraction reads `v`? i.e. swap which one the compare uses... no, we showed that doesn't match.

Hmm, what about making the compare use a variable that holds the value but is not c: e.g.

```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) { ... }
```
The problem: gcc knows v == c.

What if we add a "no-op" that makes gcc NOT know v == c? E.g. compare `v` where v is re-read... ✗

Hmm, what if the compare's operand is `v` but `v` is declared as `unsigned`? Then `v >= 0x801` is an unsigned comparison → `sltiu` ✗ (the target uses slti).

Hmm, what if `v` is s32 but the comparison is done as `if (v >= 0x801)` where the copy `c` is s16?! Then c = tmp (s16→s16, same mode) → hmm, a same-mode copy → cse propagates ✗.

Hmm.

What if the copy's dest `c` is `s16` and the subtraction `v = c - 0x200` → c promoted (sign-extended) → the sign extension might be free if c's value is known... and then `c` is s16 → the equality c == v? gcc knows c = (s16)v and v is sign-extended-16 → so c == v numerically. But gcc's internal representation: c is QImode, v is SImode. The compare `v >= 0x801` uses v (SImode) → the compare's operand is v ✓ (no substitution, since c is a different mode!).

And the subtraction `v = c - 0x200` → c is promoted to SImode via sign_extend:SI(c) → if gcc knows c's value is the sign-extended low 16 bits of v, and v is sign-extended-16, then sign_extend(c) == v → gcc folds → `addiu v0,v1,-512` ✓ (the promotion is free!).

So making `c` an s16 might:
- prevent the compare substitution (different modes),
- keep the copy (the copy `c = tmp` is a same-mode HImode copy → escapes cse per the G06 note "the HImode copy escapes cse's equivalence class"!),
- and the promotion folds.

Hmm! But careful: c is s16 → `c = tmp` (both s16) is a plain HImode copy → per the G06 note, HImode copies escape cse's equivalence class ✓.

But then how does the copy survive cse AND the compare not be substituted? The compare reads v (SImode) and c is QImode → different pseudo → no substitution ✓.

Hmm, but does the "promotion" of c to s32 in `v = c - 0x200` fold? gcc must know sign_extend(c) == v. It knows c == tmp == (s16)v → and v's value is sign-extended-16 → so sign_extend(c) == v ✓ IF gcc can prove that. Hmm, gcc's combine would need: sign_extend:SI(c) where c = (s16)v → combine's rule: `(sign_extend:SI (sign_extend:HI v))` → simplify to `(sign_extend:HI v)` → and if v is known to be sign-extended-16 (from the lh load), then it's v itself. Hmm, does gcc know v is sign-extended-16? The load `lh` → gcc's RTL for `lh`: in gcc 2.7's mips.md, "lh" is:
```
(define_insn "lh"
  [(set (match_operand 0 "register_operand" "=r,m")
	(match_operand 1 "mem_operand" "m"))
   (use_clobber (match_operand 3 "register_operand" "=r"))
   (set_attr_attr "move" "type,load_use,clobbered")]
```
The output operand 0 is SImode and the memory is QImode → the RTL is `(set (reg:SImode) (mem:QI))` — gcc's expand would insert the sign extension. Actually for `lh`, gcc emits the insn with the QImode mem and the SImode reg — the sign extension is implicit in the instruction. So gcc's RTL doesn't have an explicit sign_extend → gcc doesn't "know" the value is sign-extended-16.

Hmm. But empirically in 80182ED4 the round trip through the s16 temp produced NO sign extension insns, which means gcc DID fold the sign extension. Why? Because... hmm.

In 80182ED4: `t = unk84` (s16 field → s32 t) → `lh`. `tmp = (s16)t` → the RTL: convert t (SImode) to QImode → `(set (reg tmp:QI) (truncate:HI (reg t)))`? or sign_extend:HI. Then `u = tmp` (QI → SI) → `(set (reg u:SI) (sign_extend:SI (reg tmp:QI)))`.

For the result to be `or v1,v0` (no sll/sra), gcc must have determined that sign_extend(truncate(t)) == t. That requires knowing t's value fits in s16 → t is the sign-extension of a 16-bit value → hmm.

Hmm, but wait: in the 80182ED4 case, the `tmp = (s16)t` — maybe gcc implemented the truncation as `(sign_extend:HI (reg t))` (gcc's convert_to_mode for a signed narrow destination keeps the value sign-extended), so tmp's reg holds the sign-extended 16-bit value = t (since t's low 16 bits sign-extended = t only if t fits). Hmm, then `u = tmp` → `(sign_extend:SI (reg tmp:QI))` → combine: sign_extend of a QI reg → gcc's combine has a rule: "if the operand is a sign-extended narrow value, the extension is a no-op"?

Hmm, whatever. Empirically it worked. gcc's combine rule (gcc 2.7 combine.c, `simplify_expr`):
```c
    case SIGN_EXTEND:
      ...
      /* If we are extending a value that is known to be sign extended
	 (e.g. the result of a sign extending load), we can skip it. */
```
and there's this in gcc 2.7's combine.c:
```c
	  /* Handle the case of (sign_extend:SI (reg:QI)) where the reg
	     was set by a sign extending operation. */
```

Hmm, actually here's a much more likely mechanism: gcc's `convert_to_mode(SImode, x)` where x is a QI-mode register → gcc's convert.c:
```c
    case SImode:
      ...
      if (GET_MODE (x) == QImode)
	{
	  /* Sign extension of a QImode register: the value in the register
	     is already sign extended if it came from a sign extending
	     operation.  */
	  ...
	}
```
Hmm, gcc's convert.c has:
```c
/* Return an rtx for the conversion of X to mode MODE... */
rtx
convert_to_mode (machine_mode mode, rtx x)
{
  ...
    case SImode:
    case DImode:
      ...
      if (GET_MODE (x) == QImode || GET_MODE (x) == HImode)
	{
	  rtx extended;
	  ...
	  extended = extend_mode (mode, x, GET_MODE (x), 0, 1);
	  ...
	}
```
and `extend_mode` → `sign_extend` → the RTL `(sign_extend:SI (reg tmp:QI))`.

Then combine: combine's rule for SIGN_EXTEND (gcc 2.7 combine.c, in `simplify_expr`):
```c
    case SIGN_EXTEND:
      if (GET_MODE (x) == mode) return x;
      ...
      /* If we know that the value is already sign extended... */
```
Hmm.

There's also this gcc rule in `expand_expr`/`extend_mode`: when the source is a pseudo of a narrow mode, gcc uses `sign_extend` and then combine's `known_zero`...

OK. Let me just TEST: make `c` an s16 in the real function and see. Let me also test the "tmp is s16, c is s16" variant.

Let me run a batch of real-function variants:
A: c1/c2 split with tmp s16.
B: c as s16 (shared).
C: c1/c2 with c as s16.
D: separate tmp1/tmp2 and c1/c2, all s32 (the split-reuse trick).

Let me write and score them with sc.sh.

Note: sc.sh prints one line per candidate. Let me do it.

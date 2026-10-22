---
ts: 2026-10-22T08:00:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_cLLeBfM5c5ogGkPgTaKE
---
Excellent! This is exactly the family of func_801880E0. The move that cracked 8017E978:
1. `flag2/flag3/flag4` declared `s16` (not s32).
2. `ot = func_800D27DC(flag4 != 0, ot, w->f4, w->fC, 0);` split out before the return, so `ot` gets +2 refs → allocated first → s1.

Apply to 801880E0:
- flag2, flag3, flag4 → s16
- `ot = func_800D27DC(flag4 != 0, ot, w->f4, w->fC, 0); return func_800D29F8(flag4, ot, w->f8, w->fE, 0);`
- Also `w` local (no pin), `w = w0;` at top.

Note in 801880E0 the `w` pin is on a LOCAL fed from the parameter. In 8017E978, `w` is `Panel_8017E978 *w;` local, `w = w0;`. So for 801880E0: `Panel_8017E978_801880E0 *w; ... w = w0;` and use w-> everywhere.

Note the current win.c for 801880E0 uses w0-> directly (dropping the local). The G02 exemplar keeps `w = w0` local. Let me use that.

But careful: the src comment says "The pin lands on a LOCAL fed from the parameter, never on the parameter itself (S3)." So we need `w` as a local.

Also there's a subtlety: in 801880E0, `flag = -(D_8011511A != idx) & 0xFF;` — flag is s32 in target. In 8017E978 same. Keep flag as s32.

Let's write the candidate. Also need `sp18`/`sp60` etc.

Let me first check that the delever_search tool compares against build/ — the target. Let me try running dt.sh on current win.c to see score.

Actually let's be efficient. Let me create the candidate for 801880E0 first.

Also for the other items:

**80182ED4** (pins $2 t, $3 u, $0 zr): The note says the issue is `u = t + zr` — the $0 addend keeps the copy alive. Lever-free alternatives: any C-level zero folds. Options:
- Use `s16` types so the copy becomes a sign-extend that escapes cse? Hmm.
- Actually: `u = t;` gets cse-propagated. What about making `u` a different type e.g. `u16 u`? Then `u = t` truncates → combine nonzero_bits → move? Similar to the s16 trick in the family.

Actually, target: `t` in $2/v0, `u` in $3/v1. `u = t + zr` → `move v1,v0` in delay slot of branch. else arm: `addiu v0,v1,-1`.

Lever-free: we need a copy of t that survives. The s16 trick: declare `u` as `s16` — then `u = t` is a truncation (t is s32) which produces a sign-extension. Combine's nonzero_bits turns `u = t` into a move with sign extension. Hmm but that would change semantics: `u = t + zr` where t is s32, then `t = u - 1`. If u is s16 and t's value > 32767, truncation changes. But in this function t = unk84 which is bounded? Semantically it might not matter for score but it's a semantic change. Hmm. The task says "real C moves only" — the win must match the target asm. Semantics change is risky but the family moves (s16) did exactly that in G02.

Hmm, but actually wait: `u = t` where both s32 → cse propagates. What about `u = t` where u is `u16`? Then u = (u16)t, and `t = u - 1` → t = (u16)t - 1. That differs if t is large.

Let me think about what the target asm is exactly. Let me get the actual target asm. Let me check what delever_search does and where the target asm lives.

Let me look at tools/delever_search.py --help and the build/ dir.

Actually, let me think about the "s16" trick more carefully for 80182ED4.

In G02: flag2 = flag where flag is s32 (`-(D_8011511A != idx) & 0xFF`, so 0 or -1... wait `& 0xFF` gives 0xFF or 0). flag is s32 with value 0 or 255. flag2 = flag (s16). Then `flag2 != 0` test. With s16, the copy `flag2 = flag` becomes `move v,s0` with sign-extend semantics... In MIPS, `addu` doesn't sign extend. The s16 copy materializes as `move` + maybe sign extend. combine's nonzero_bits: for `flag2 = flag` where flag2 is s16 (QImode) and flag is s32, the assignment is a truncation, so RTL is `(set (reg flag2) (sign_extend (reg flag)))` → that's not a reg-reg copy so cse can't propagate it. Then combine's nonzero_bits turns sign_extend of a 32-bit reg into a move (since sign_extend of a value whose bits are known nonzero... hmm).

OK. So for 80182ED4: `u = t` where t is s32 → `move v1,v0` and cse propagates equality removing the copy. We want the copy to survive.

Alternative: make `u` an s16 (QImode) and `t` an s32: `u = t` → truncation to 16 bits. Then `t = u - 1` → u promoted back to s32. Semantically: `t = (s16)t - 1`. Original: `t = t - 1`. If t's value fits in s16 range, identical. t = unk84, probably small. But is it "real C"? It's a semantic change. Risky but the family did the same for flag (0/255 fits).

Hmm, but here the target is `move v1,v0` — a plain move, not a sign-extending move. With s16 u = t, gcc 2.7 might produce `move v1,v0` then `sll v1,16; sra v1,16`? That'd be extra instructions. The G02 note says "copies become sign-extend that combine (nonzero_bits) turns back into moves after cse -> 24". So combine turns it back into a move. Good, same should apply.

Let me think about the other items.

**8018302C** (pin $0 on z): `c = v + z` where z is pinned $0. The note says any C-level zero folds. But the s16 trick: `c` is s32; `v` is s32 = load of s16. Hmm.

What if z is declared s16 and `c = v + z`? Then z is sign-extended... The RTL would be `(plus v (sign_extend z))`. z = 0 constant? No, z is unassigned local → undefined value, but gcc treats it as whatever. Hmm, in the lever-free variant, `s32 z;` unassigned: `c = v + z` gave score 2 with addend in $5/a1 instead of $0.

The target wants `move v1,v0` (copy of v into c) plus `addu v1,v0,zero`? Actually the target: `c = v + z` with z=$0 → `addu v1, v0, $0`. Hmm, wait — the note says "the subtraction uses the copy's register (addiu v0,v1,-512) while the compare uses the loaded value's register (slti v0,v0,2049)". So the target's `c` is in $3/v1 and `v` in $2/v0? And `addu v1,v0,$zero` = move.

Hmm, wait. Let's reconsider: with pin z=$0, `c = v + z` becomes `(set c (plus v (reg 0)))`. combine doesn't fold because reg 0 isn't a constant in combine's view... Actually combine does fold `plus x (reg 0)`? Apparently not for a hard reg.

So the copy that survives is `c = v` effectively but kept as a separate pseudo. Lever-free: `c = v` → cse propagates → gone. `c = v + 0` → tree folds.

What escapes? An expression that is a copy but not a plain assignment: e.g. `c = v & 0xFFFF` (truncation) — but the target is `addu` (32-bit), so `& 0xFFFF` would give a zero-extend, wrong.

What about `c = v | 0`? tree folds. `c = v * 1`? folds. `c = (s32)(u16)v`? gives different instruction.

Hmm. What if `z` is declared as a `s16` type but assigned 0? `c = v + z` where z is s16 = 0 → sign_extend(z) is not a constant to the tree level? The tree level (fold) might not fold sign_extend of a constant... Actually front-end constant folding would fold z=0 to constant 0. But if z is assigned 0 in a way that front-end doesn't see as constant... e.g. `z` is a volatile? no.

Alternative: make z a function parameter? No, signature change not allowed... Actually "no signature or decl change outside the body" — we can't change the signature but can we change the body? The brief says write a body of `func`. Signature stays.

Hmm, what about `z` being a global variable? `extern s32 z;` then `c = v + z` — the load of z is not folded, so `addu v1, v0, at` — no, that adds a load.

What about using an s16 local `z` that is assigned a value from a volatile read? no.

Alternative approach: make the copy survive by using a type with different width where the truncation is free. E.g. `c` is `s32` and `v` is `s16`? Currently `v = *(s16 *)(p+0xC);` so v is s32 holding sign-extended s16. If we declare `v` as `s16 v;` then `c = v + z` → c = v + (s32)z. Hmm then `if (v >= 0x801)` comparison with s16 v → v promoted to s32. And `v = c - 0x200` truncated back to s16. Semantically that's actually what the original code does? Original: `v` is s32 but holds sign-extended s16 value; `v = c - 0x200` then `*(s16*)(p+0xC) = v` truncates. So declaring v as s16 is semantically nearly identical.

But the point is the copy `c = v + z`. With z as s16 and v as s16: `c = v + z` → both promoted to s32, then the addend is a sign_extend of z → not a constant → `addu v1, v0, a1`-ish. Doesn't give $0.

Hmm. Let me reconsider. Maybe the trick for $0 is different: In the G02 family, "$0 zr pin: s16 flag2/3/4 copies (sign-extend escapes cse, combine nonzero_bits -> move)". So there the $0 addend was replaced by an s16 copy which survives cse and becomes a move. Same idea applies here! `c = v + z` where the goal is a *copy* `c = v` that survives as a separate register.

So: if we make `c` an s16 and `v` an s32, then `c = v + z`... no wait, we need the copy to be v→c with the sign-extend property. `c = v` where c is s16 and v is s32 → truncation → sign-extend → survives cse → combine → move.

But we need `c = v + z` semantics with z=0. If z is a lever-free zero... The issue: the target's `c` value = v. And then `v = c - 0x200`.

So: declare `s16 c;` and write `c = v;`? But `v` could be > 32767? v = *(s16*) → range [-32768, 32767]. So c = v as s16 is exact! And `v = c - 0x200` → c promoted to s32, minus 0x200 → correct.

But careful: `c = v` where v is s32 holding sign-extended s16, c is s16 → truncation to 16 bits then reinterpretation as s16 → equals v exactly since v fits in s16.

Then the RTL: `(set c (sign_extend (truncate v)))`? Actually GCC would emit `(set (reg c) (sign_extend:HI (reg v)))` — hmm, v is already sign-extended so gcc might optimize. combine's nonzero_bits should turn it into a plain move.

Then the target: `move v1,v0` where v0 = loaded v, v1 = c. Yes! And then `addiu v0, v1, -512`. And compare `slti v0,v0,2049` uses v's reg.

But wait — in the target, is c in $3/v1? The note says "the subtraction uses the copy's register (addiu v0,v1,-512)". Yes.

But also the target has `c = v + z` where z is $0 → `addu v1, v0, $zero` — which is byte-identical to `move v1,v0`? MIPS `addu $3,$2,$0` vs `move $3,$2` (which is `or $3,$2,$0`) — different bytes! Hmm. But the target might be `move` (or). The note for 801880E0 said "assembles to the byte-identical `addu $s4, $s0, $zero`". So the target byte is `addu` with $zero.

Hmm so for 8018302C the target instruction is `addu v1,v0,$zero`? Or `move`? Let me check: does the target for 801880E0 use addu with zero? Yes per the comment. For 8018302C, "c = v + z with z = $0 materialises as move v1,v0" — the note calls it a COPY that survives, written as "move". Hmm, gcc's `move` is `or rd,rs,$zero`. But `addu rd,rs,$zero` is also possible.

Since delever_search compares instruction streams, I need to know. Let me get the target asm.

Let me check the build dir / how delever_search works.

Also for 80182ED4: `u = t + zr` → `move v1,v0`? note says "the `u = t + zr` line materialises as `move v1,v0` in the delay slot". Hmm — with zr = $0 (a hard reg), combine would emit `addu v1,v0,$0`? But note says "move". So in this TU the target is `move`??

Hmm wait, `register u32 zr __asm__("$0")` — the RTL is `(plus t (reg 0))`. GCC's combine for `plus x (reg 0)`: I believe gcc does fold `plus` with reg 0 into a reg copy in some cases (there is a combine rule: "convert (plus (reg) (reg 0)) into a copy"? Actually there's `x + 0` folding via `x + 0` handled in fold). Hmm, but the notes say the copy survives.

The difference between 80182ED4 (u32 zr) and 801880E0 (s32 zr) might matter for the instruction: with u32, `u = t + zr` where zr is u32 → result type u32. Hmm.

I need the actual target asm. Let me find it. The build/ dir has the compiled object. Let me look at delever_search.py to understand.

Let me check.

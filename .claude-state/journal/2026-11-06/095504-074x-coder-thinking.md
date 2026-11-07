---
ts: 2026-11-06T16:55:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zPMKuswiEfXde1WCgmOT
---
Both have the t+h4 sum first (v0) then +s2 (v0). The target wants h4+s2 (v1) then +t (v0).

So mine computes (t + h4) first. The target computes (h4 + s2) first.

The target's tree order is `t + ((h << 4) + s2)`. In w8_f I wrote `q = t + (h<<4); r = q + s2;` — that's the (t+h4)+s2 order. Let me instead write the temps in the target order:
```
q = (h << 4) + (s32)s2;
r = t + q;
```
That's w8_e → score 6 (REG-caller). Hmm.

So the target order comes with the wrong registers, and the right registers come with the wrong order. 

Hmm, let me think about the tie structure ONE more time with the target order:
`q = (h<<4) + s2; r = t + q;`
RTL: sll h4(81), addu q=81+75 (82, ties 81), addu r=t+82 (83, ties t).
Groups: h {76,81,82}, t {77,83}. h pri 4.5 > t 3 → h gets $2. Wrong.

For t to get $2, the t group must be bigger. In r1 (t+h4 first), the t group is {77,83,84} → wins.

So the target's allocation suggests the t group is {77,83,84}?? But then the instruction `addu v1,v1,s2` would be 82 in v1 and the final `addu v0,v0,v1` would be 84 (=83+75)... 

Hold on! Let me re-map the target:
```
2740: sll v1,v1,0x4     81 = 76<<4      -> v1
2744: addu v1,v1,s2     82 = 81 + 75    -> v1
2748: addu v0,v0,v1     83 = 77 + 82    -> v0
```
If the tie structure were r1's (t group = {77,83,84}), the target would have `addu v0,v0,v1` (83 = t + 82) with 83 in v0 and 82 in v1. That's what we see! And the group {77,83} or {77,83,...}.

Hmm, in the target, 82 is in v1 and 83 in v0 — different regs. So 83 is NOT tied to 82. And 83 is tied to 77 (both v0). So the t group is {77,83}. Confirmed.

OK so the target: t group {77,83} pri 3, h group {76,81,82} pri 4.5. h should win. But it doesn't. So my priority model must be wrong. Maybe the qty_n_refs for the h group isn't 12.

Wait — maybe the ties happen differently. At insn 35 `81 = 76 << 4`: the tie loop requires `insn_operand_constraint[code][0][0] == '='` etc. ashlsi3's operand 0 constraint? Let me check. If ashlsi3's operand 0 is "=d" fine. But maybe ashlsi3's operand 1 (the shift amount) has a special constraint.

Hmm, but the target's 76,81,82 all in $3 could also be WITHOUT ties (as I computed, without ties 76 gets $2 though).

Let me just empirically explore the r1 direction: r1 gives the right registers and the wrong order. What if I can get the order right by making the t+h4 sum's *result* be the inner... 

New idea: swap the roles! What if I make the h<<4 + s2 computation appear BEFORE t in the source? E.g., compute the inner sum in a temp before t:
```c
h = *(s16*)(...);
s0 = s0 + 1;
idx = (h << 4) + (s32)s2;   // before t?
t = s0 << 1;  // hmm, t = (old s0)<<1; s0 was incremented
```
Careful: t = s0 << 1 uses the OLD s0. So t must be computed before s0++.

What if:
```c
a = s0 << 9;
t = s0 << 1;
h = *(s16 *)((u8 *)s1 + 0x70);
s0 = s0 + 1;
q = (h << 4) + (s32)s2;
func(..., *(u16 *)(t + q), ...);
```
This is w8_e (score 6, wrong regs).

Hmm.

OK, time to consider the wall. I've spent ~35 min on item 3 and 25 tries. The rule: a WALL needs ≥20 min and ≥30 scored tries. I'm at 25 tries, 35 min. Let me do 6 more quick tries to reach 31, then wall with best 2.

Actually, the best is 2 — quite close. But a WALL is acceptable. Let me think once more if there's an obvious move...

The difference between r1 (right regs) and the target (right order): r1's t group has 3 regs. The target's t group has 2. But r1's allocation gives t=$2 and h=$3 — same as target. The ORDER is the only difference.

What if I keep r1's reassociation but force the *instruction order* via statement order? The RTL order for `(t + (h << 4)) + s2` is determined by the tree: the operands are evaluated... gcc expands `t + (h << 4)` first, then adds s2. To get the target order, the inner sum must be h4+s2.

What if I write:
```c
s32 q;
q = (h << 4) + (s32)s2;   // inner sum: h4+s2  (target order)
q = t + q;                // then +t
```
= w8_e → the ties: the inner q ties to 81 (h), the outer ties to t → target structure → h wins. Score 6.

What if I write:
```c
q = (h << 4) + (s32)s2;
q = q + t;    // outer plus (q, t): operand 1 = t (dies) → tie to t!
```
The RTL for `q + t` is (plus q t). The tie loop at i=1: r1 = q (dies) → tie to q (h group). Hmm, i=1 is the first input operand = q. So it ties to q. Unless gcc canonicalizes `q + t` to `t + q`? 

Hmm, in w8_a (`((h<<4)+s2)+t`) the tie went to the inner (h group) → score 4. So operand order matters as written.

So `q + t` would tie to q. Wrong.

What if the outer is `t + q` (ties to t, target structure) but the inner sum q is computed with the target order? That's w8_e. Score 6.

I keep concluding the target structure gives the wrong allocation. So the target's original C must differ elsewhere (e.g., different variable structure that changes nrefs/lives).

Let me try one more idea: change `s2` from a void* to an s32 or make it a local copy, affecting the inner addu. Or change the *cast* `(s32)s2`.

Alternatively: change `t` from `s32` to `u32`? Or make `t` used twice (e.g., also in the address via a different expression)?

Hmm, what if the original C had `t` declared as the *loop counter* alias? 

Let me try a few:
1. `t` as u32.
2. `a` as u32.
3. s2 as `s32 s2` (with a cast).
4. Original expression but with the h load written as `*(u16*)` + cast to s16: `h = (s16)*(u16 *)(...)` — that's lhu + sll/sra (extra insns).
5. Original expression with `h` declared first in the decl list.
6. Original expression with `s0` as u32.

Let me run 6 more to reach 31 tries, then wall.

Actually wait. Let me reconsider one thing: the target's `lh v1,112(s1)` is at 2738, and the lreg order in MY build is a(23), h(30), t(25). What if in the original, the sched1 order was h, a, t or a, t, h? The final .s order is the same in mine and target (a, t, h), so the *final* order doesn't tell us the lreg order. But the register allocation depends on the lreg order.

If the lreg order were a, t, h (t born before h), then:
- t group {77,83}: birth = t's birth, death = 83's death.
- h group {76,81,82}: birth = h's birth (later), death = 82's death.
The h group's life would be shorter (later birth) → HIGHER pri. Still h.

If the lreg order were h, a, t:
- h group birth earliest → longer life → lower pri. Let me compute: h birth 4, death 14 → life 10, nrefs 12 → pri 3.6.
- t group birth 6, death 16 → life 10, nrefs 8 → pri 2.4.
Still h.

What if the order is t, h, a? h birth 6, t birth 4:
- t group: birth 4, death 16 → life 12, nrefs 8 → pri 2.
- h group: birth 6, death 14 → life 8, nrefs 12 → pri 4.5.
h.

Hmm. The only way t wins with 2 regs is if the h group has fewer nrefs. 

Wait, maybe the h group's nrefs is not the sum but the first reg's? I read the code: `qty_n_refs[sqty] += reg_n_refs[sreg]`. Sum. Hmm.

But note: reg_n_refs values might not all be 4. The dump says "Register 76 used 4 times across 3 insns" etc. But maybe those counts are after something. Anyway.

OK, let me consider that the item is a wall with best 2. Actually, let me try the one thing that might flip: make the h group have only 2 tied regs by preventing the 76→81 tie. If h is used twice (e.g., `h << 4` and `h >> 16`), 76 doesn't die at the sll → no tie. Then:
- 76 alone: birth 6, death 10 (at the sll use), nrefs 4 → pri 2.
- 81 {h<<4}: birth 10, death 12, nrefs 4 → pri 4.
- 82 {+s2}: ties 81 → group {81,82}: nrefs 8, birth 10, death 14 → life 4 → pri 3*8/4 = 6!
- t group {77,83}: pri 3.
Then the {81,82} group pri 6 wins → $2. Wrong (h in $2).

Hmm.

What if the h<<4 output does NOT tie to anything: `82 = 81 + s2` ties 82 to 81 if 81 dies. To break that, 81 must be used later. If h<<4's result were used twice... no.

OK, I'll wall item 3 with best 2. But let me first run 6 more quick tries to meet the ≥30 rule.

Actually, the rule says "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item". I have 25 tries (win0, w6×7, w7×5, w8×6 = 19? Let me count: win0=1, w6 base,htop,ttop,s16,u16,tlast,a_after_t = 7 (total 8), w7 r1,r2,idx1,idx2,inline,swapdecl = 6 (total 14), w8 a,b,c,d,e,f = 6 (total 20). Hmm, 20 tries. Plus the diff runs don't count.

I need 30 scored tries. Let me run 10 more variants (cheap) to reach 30, exploring remaining spellings. Let me generate 10.

Variants:
1. `t` u32.
2. `a` u32.
3. `s2` as s32 (change decl `s32 s2` and cast `(s32)s2`).
4. h declared before t/a.
5. s0 as u32.
6. Original expression with `t` computed as `s0 * 2`.
7. Original expression with `h << 4` written `h * 16`.
8. r1 with temps: `q = t + (h<<4); q = q + s2;`
9. Original expression with `(s16)(... + a)` moved: cast `a` to s16 earlier.
10. Original with the `(u16*)` load split into a pointer temp: `p = (u8*)s1 + 0x70; h = *(s16*)p;`

Let me run them.

---
ts: 2026-10-22T00:08:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ZIxrYDZLLMLvhgQDcSf5
---
Not a CLI. But `md.insns_from_object` (tools/masked_diff) is a module. I can use python -c? "Never inline python -c" per house rules (§2: "Scripts, not inline python -c or one-liner chains"). And my own scripts are denied by the sandbox.

Hmm, but the denial was for `/usr/bin/python3 .run/.../script.py`. Maybe the denial is about writing files from the script? Let me test: run a script that only reads and prints (no writes). If allowed, then the denial was triggered by the write... Actually score.py writes nothing but reads and runs subprocess; strip.py writes. Both were denied. So arbitrary script execution is denied.

Alternative: is there a tool to dump an object's instructions? `tools/asm-differ`? Let me check what it is. Or `tools/objdiff_report.py`. Or `tools/residual_class.py`.

Actually — do I really need the target listing? The diff output gives me the target's relevant instructions in the differing region, which is what matters. For item 1, the diff region 194-221 shows both. That's enough to reason.

Target tail (from the diff):
```
194: sra a2,v0,0x10
195: bgez a2,7440
196: move a1,a2
197: negu a1,a2
198: lui a0,0x6666
199: ori a0,a0,0x6667
200: addiu v0,a2,160
201: nop
202: mult v0,a0
203: mfhi t1
204: addiu v0,a2,160
205: nop
206: mult v0,a0
207: sra a0,t1,0x6
208: subu a1,a0,v1
209: sra v0,v0,0x1f
210: mfhi a2
211: sra v1,a2,0x3
212: subu a2,v1,v0
213: bne a2,v0
...
217: sll a2,a2,0x8
218: li a2,15
```
Hmm wait, the diff listing at "replace mine[194:202] target[194:200]" printed 8 lines for mine and 6 for target, and then "replace mine[204:205] target[202:202]" etc. The printed pairs are index-aligned: mine[k] vs target[j]. Let me re-read:

```
  replace mine[194:202] target[194:200]
     194  sra	a3,v0,0x10                     | sra	a2,v0,0x10
     195  bgez	a3,7440 <...>                 | bgez	a2,7440 <...>
     196  move	a1,a3                         | move	a1,a2
     197  negu	a1,a3                         | negu	a1,a2
     198  lui	a2,0x6666                      | lui	a0,0x6666
     199  ori	a2,a2,0x6667                   | ori	a0,a0,0x6667
     200  addiu	a0,a3,160                    | --
     201  mult	a0,a2                         | --
  delete  mine[204:205] target[202:202]
     204  mfhi	a3                            | --
  replace mine[207:211] target[204:209]
     207  mult	v1,a2                         | mult	v1,a0
     208  sra	a0,a0,0x1f                     | mfhi	t1
     209  sra	v0,a3,0x3                      | addiu	v0,a2,160
     210  subu	a3,v0,a0                      | nop
     211  --                                 | mult	v0,a0
  replace mine[212:215] target[210:216]
     212  mfhi	t1                            | sra	a0,t1,0x6
     213  sra	v0,t1,0x6                      | subu	a1,a0,v1
     214  subu	a1,v0,v1                      | sra	v0,v0,0x1f
     215  --                                 | mfhi	a2
     216  --                                 | sra	v1,a2,0x3
     217  --                                 | subu	a2,v1,v0
  replace mine[216:220] target[217:221]
     216  bne	a3,v0,7498 <...>               | bne	a2,v0,749c <...>
     217  sll	a3,a3,0x8                      | sll	a2,a2,0x8
     218  li	a3,15                          | li	a2,15
```

So the TARGET (right column) sequence from 194:
```
sra a2,v0,0x10
bgez a2
move a1,a2
negu a1,a2
lui a0,0x6666
ori a0,a0,0x6667
(nop? no: target[199] ori, then target[200] is... the delete row says target[202:202] deleted, so target[200] and target[201] exist)
```
Hmm the alignment: "replace mine[194:202] target[194:200]" means mine indices 194..201 replaced target 194..199. So target[194]=sra a2, 195=bgez a2, 196=move a1,a2, 197=negu a1,a2, 198=lui a0, 199=ori a0. Then "delete mine[204:205] target[202:202]" means target[202] doesn't exist (mine[204] deleted) — so target[200], target[201] are equal to mine[202], mine[203]? But the diff opcodes say "delete" for mine[204:205] vs target[202:202] — that's a "delete" opcode meaning mine has extra. Hmm, in difflib "delete" means mine[204:205] deleted to match target (no target counterpart). But then target[200:202] equals mine[202:204] (equal opcode).

So target[200], target[201] = mine[202], mine[203] = "mfhi a3"? no wait mine[202] and mine[203] weren't shown (they were in an "equal" region). Let me reconstruct: mine[200]=addiu a0,a3,160, mine[201]=mult a0,a2, mine[202]=?, mine[203]=?, mine[204]=mfhi a3 (deleted).

And "replace mine[207:211] target[204:209]": target[204]=mult v1,a0, 205=mfhi t1, 206=addiu v0,a2,160, 207=nop, 208=mult v0,a0. And mine[207]=mult v1,a2 etc.

So target[200..203] = equal to mine[202..205]? but mine[204] is "mfhi a3" (deleted). Hmm, the delete opcode covers mine[204:205] with target[202:202] — that means target has nothing there. Confusing. Let me just reconstruct from the second/third replacement: target[204]=mult v1,a0; so target[203] is the instruction before = "addiu v0,a2,160"? no, target[206]=addiu v0,a2,160.

OK let me carefully reconstruct the target from 194 to 221 using the right column:
- 194 sra a2,v0,0x10
- 195 bgez a2,7440
- 196 move a1,a2
- 197 negu a1,a2
- 198 lui a0,0x6666
- 199 ori a0,a0,0x6667
- 200 ? (equal to mine[202])
- 201 ? (equal to mine[203])
- 202 (nothing; mine[204] deleted)
- 203 ? — hmm, the "replace mine[207:211] target[204:209]" implies target[203] = equal to mine[206].
- 204 mult v1,a0
- 205 mfhi t1
- 206 addiu v0,a2,160
- 207 nop
- 208 mult v0,a0
- 209 (equal to mine[211]?) hmm "replace mine[212:215] target[210:216]" → target[209] equal to mine[211].
- 210 sra a0,t1,0x6
- 211 subu a1,a0,v1
- 212 sra v0,v0,0x1f
- 213 mfhi a2
- 214 sra v1,a2,0x3
- 215 subu a2,v1,v0
- 216 (equal to mine[215]? no) ...

I'm making a mess. The key: mine has 236 ins, target 237. The target sequence (from the visible right column) is:

```
sra a2,v0,0x10
bgez a2
move a1,a2
negu a1,a2
lui a0,0x6666
ori a0,a0,0x6667
<...>
mult v1,a0        (v1 = sx? times magic)
mfhi t1
addiu v0,a2,160
nop
mult v0,a0
sra a0,t1,0x6
subu a1,a0,v1
sra v0,v0,0x1f
mfhi a2
sra v1,a2,0x3
subu a2,v1,v0
bne a2,v0
sll a2,a2,0x8
li a2,15
```

Interpretation: a2 = sx (sign-extended u16), a1 = |sx| (av), v1 = ? (maybe 0x7F? or sx-related). Chain 1 (VOL): v0 = a2+160?? hmm, "addiu v0,a2,160" — but vol = (0xA0-av)*0x7F/0xA0. Hmm, a2 = sx though. Unless... wait, the target's a2 might be 0xA0-av, not sx! Let's redo: "sra a2,v0,0x10" gives a2 = sign-extended high?? sra v0,0x10 = v0>>16 = the high half. Hmm! sra v0,0x10 gives the HIGH 16 bits of v0 (v0 holds the 32-bit sxy: low = sx, high = ?). Wait `(s16)*(u16*)&sxy` = low 16 bits → that would be `srl`/`andi` not `sra 0x10`.

Hmm, in the source: `sx = (s16)*(u16 *)&sxy;` and `*(u16*)&sxy` is the low half of sxy. So sx = sxy & 0xFFFF sign-extended. That would be `andi`/`srl`+`sra`. But the target shows `sra a2,v0,0x10`?? That extracts the HIGH half. Hmm, unless the compiler knows the value differently.

Hold on: maybe the source in the banked body isn't what the target was compiled from. The target is the original game code; the banked body reproduces it. So `sra a2,v0,0x10` = high half of the 32-bit sxy. And the source's `*(u16*)&sxy` would be the low half... So maybe v0 doesn't hold sxy but something else, and the banked body's `sx = (s16)*(u16*)&sxy` compiles to `sra v0,0x10`?? That would be the case if the compiler loaded a 16-bit value at &sxy+2? No...

Wait: `*(u16 *)&sxy` reads the low 16 bits of sxy (little-endian). To sign-extend: `sll v0,v0,16; sra v0,v0,16`. The target shows `sra a2,v0,0x10` only — hmm, that's a single instruction: a2 = v0 >> 16 (arithmetic). That equals the high half.

Unless v0 at that point holds a value where the compiler chose to compute the high half: e.g. `sx = (s16)*(u16*)&sxy` where the compiler... no.

Hmm, maybe the target function is not this exact source. But the banked body scores 0 (byte-identical), so the compiled code of the banked body IS the target. So `sx = (s16)*(u16*)&sxy` must compile to `sra a2,v0,0x10`?? Only if sxy's high half is what's read...

Oh wait! Maybe the read is `*(u16 *)&sxy` where &sxy is at sp+0x48, and the 32-bit load v0 = *(s32*)&sxy loads both halves; then `(u16*)&sxy` = low half → sll/sra 16. But the target has sra 0x10 only. So maybe the compiler recognized that only the high half is used?? Not possible for a u16 read.

Hmm, unless: `*(u16 *)&sxy` where the struct is {u16 x; u16 y} and sxy is the 32-bit block: x at offset 0, y at offset 2. `(u16*)&sxy` = x (low). The target's `sra a2,v0,0x10` = high = y.

But look at the source: the check uses `(*(u16 *)&sxy + 0x9F) & 0xFFFF` (x) and `*((u16*)&sxy + 1)` (y). And `sx = (s16)*(u16 *)&sxy;` = x.

So the target's sx = high half? That contradicts. Unless v0 doesn't hold sxy but holds something else, e.g. the compiler kept the loaded 32-bit value in v0 where the low half is x and high is y, and `(s16)*(u16*)&sxy` → hmm.

You know what? My interpretation of the instruction stream might be off because `sra a2,v0,0x10` might be `sra` of a value that was loaded differently. Let me stop the archaeology and instead focus on the *difference*, which is clear:

MINE (launder removed): the PAN chain first, PAN's magic in a2, PAN's result in a3, and one instruction fewer (236 vs 237: the target has 2× "addiu v0,a2,160 + nop + mult v0,a0" — one with the magic in a0 (0x66666667) and one with mult v1,a0).

TARGET: magic 0x66666667 in a0 used for BOTH chains: `mult v1,a0` (chain with dividend v1) and `mult v0,a0` (dividend v0 = a2+160). Both use the same magic constant a0! So the target reuses ONE magic constant for both divisions (VOL: /160 with shift 6, PAN: /20 with shift 3).

In MINE: the PAN chain (magic in a2) comes first, and the VOL chain uses... mine has `mult v1,a2` at 207 (so VOL's dividend v1 times magic a2) and `mult a0,a2` at 201 (PAN: a0 = a3+160 times a2). So in mine, both chains use magic a2 (shared), but the ORDER is PAN first, VOL second; and the register for the PAN chain's dividend is a0 vs target's v0, and the final result register is a3 vs a2.

So the difference is: (1) the order of the two multiply chains (target: chain with dividend v1 first, then chain with dividend (a2+160)); (2) the register assignment of the second chain's result (a2 vs a3).

Actually more precisely, in the target, the FIRST chain is `mult v1,a0` (v1 = the VOL dividend? or PAN?) and the second is `mult v0,a0` where v0 = a2+160 (i.e. sx+160 → PAN's dividend!). And the shift-6 result (t1) is used for `subu a1,a0,v1` (VOL result into a1 = av? no, a1 was av).

Hmm, whatever. The point: the target computes chain1 = mult v1 (result used with shift 6 → /160 → VOL), then chain2 = mult (a2+160) with shift 3 → /20 → PAN.

In mine, the order is reversed: chain PAN first (mult a0,a2 where a0=a3+160, shift 6?? mine[207]=mult v1,a2 then mine[208] sra a0,a0,0x1f ... mine[212] mfhi t1, 213 sra v0,t1,0x6 → the shift-6 chain ends later) and then the shift-3 chain.

So mine = PAN chain first, VOL chain second; target = VOL first, PAN second. And in the target the PAN chain's *dividend* is in v0 and result in a2; in mine PAN dividend is in a0 and result in a3.

So the launder's effect: it prevents sched1 from hoisting the PAN chain above the VOL chain.

How to achieve order VOL-then-PAN in plain C? Source order: vol is computed first (line: vol = ((0xA0-av)*0x7F)/0xA0;), then sx = (sx+0xA0)/0x14. So the source order IS vol first. But sched1 hoisted the PAN chain first anyway. Why? Because sched1 is a "PRE-reload" pass that hoists the load/mult? The launder asm creates a scheduling barrier for the value? Actually the launder is on vol, and it's *after* vol's computation. Hmm, how does that keep PAN after VOL?

The launder `"=r"(vol) : "0"(vol)` forces vol to be in a register (it's an opaque value). Possibly gcc's sched1 treats the asm as a barrier-ish node that prevents the PAN chain (which follows) from being hoisted above... no, the PAN chain is after the asm anyway.

Alternatively: the launder makes vol's *definition* not hoistable? Hmm, vol's chain is before the asm.

Wait — maybe the effect is the opposite: the launder prevents the VOL chain from being hoisted *down*? No, hoisting down isn't a thing.

Actually gcc's sched1 (reorder) can move the *later* chain earlier if independent. PAN chain is independent of VOL chain (both read a2/sx, av). So sched1 can hoist PAN's mult above VOL's mult. The launder asm (which reads vol) is placed after VOL's chain, so hoisting PAN above VOL would move PAN above the asm as well — but that's fine semantically since the asm only constrains vol.

Unless the asm is treated as a barrier for scheduling: gcc's asm insns with outputs are often given scheduling barriers (they're volatile? no, `__asm__` without volatile is still a barrier for CSE but for scheduling, non-volatile asm can be moved... in gcc 2.7, an asm statement is a scheduling barrier unless it's marked... hmm, actually gcc 2.7 treats asm as having no scheduling constraints but as a barrier for reordering? In gcc's `final.c`, an ASM insn is a barrier for the reordering passes (it can't be moved across). So the asm acts as a barrier: the PAN chain after the asm cannot be moved before the asm, and since the asm comes after the VOL chain, the PAN chain stays after the VOL chain. That's the mechanism: the asm is a *scheduling barrier*, i.e. a barrier lever, not a launder!

Interesting: the brief says kind = launder for this item. The lever census classified it as launder. But mechanically it's a barrier. Whatever — the kind is what matters for the "kinds gone" criterion: the row kind is launder, so I need to remove the `__asm__("" : "=r"(vol) : "0"(vol))` and keep the code matching.

How to keep the VOL chain first without the asm barrier? Options:
1. Create a data dependency between the PAN chain and the VOL chain so sched1 can't hoist PAN above. E.g. make the PAN dividend depend on vol: but the source semantics must stay: sx = (sx + 0xA0)/0x14 — sx doesn't depend on vol. We could write it in a way that creates a false dependency? e.g. `sx = (sx + 0xA0) / 0x14;` → what if we write `sx = ((sx + 0xA0) / 0x14) ...`? no.

2. Use a real second set of vol so that cse can't merge (the "real 2nd set" trick) — but that's about CSE, not scheduling.

3. Force the order via statement order? The lever comment says 9 spellings swept, all identical — source order doesn't help.

Hmm, what if the PAN chain is made to depend on vol through an operation that the compiler can't fold? E.g. compute vol into a variable, and then compute pan from a variable that was assigned from vol's *representation* in a way that keeps the arithmetic identical? That changes semantics? No — we need identical semantics AND identical generated code. The generated code for PAN is: dividend = sx+160 (addiu), mult by magic, mfhi, sra 3, etc. If we make the dividend = sx+160 but written as e.g. `sx = sx + 0xA0` first, then `sx = sx / 0x14` — the division's dividend is the same. A dependency on vol would require the compiler to fold it away, which it can't if it's a "real" computation.

Hmm: what if the PAN dividend is computed as `sx + 0xA0` where sx came from a computation involving vol? Not semantically equal.

4. Use `volatile`? That's a lever of another kind (not allowed to add new levers of any kind).

Hmm. Alternatively, maybe we can make the VOL chain itself *not* hoistable and instead hoist the PAN? No, we want VOL first, which is the source order. The problem is sched1 hoists PAN up.

5. What if the PAN division is written so that its dividend is computed AFTER vol in a way that creates a real dependency: e.g. `sx = (sx + 0xA0) / 0x14;` where the compiler emits "addiu v0,a2,160; mult v0,a0". If instead we wrote the pan as `sx = (sx + 0xA0) / 0x14` but with sx being a *u16/s16* variable, the compiler might generate different code (sign extension) — changing codegen.

6. What about giving vol a *second* real set so that the value flows differently, and the compiler's scheduling changes? E.g. split vol's computation: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` → what if we write `vol = ((0xA0 - av) * 0x7F) / 0xA0;` and then later `vol` is used. The "real 2nd set" trick in other items was: `pv = *p; pv &= 0xFF000000;` — an extra real assignment. Here an extra assignment would add instructions (no good) unless the second set replaces an existing one.

Hmm. What existing set can absorb vol? The final use: `func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);`. The target code for the OR is: `or` of vol with (0x3000|sx).

Idea: make the *call argument* the second set of a variable: e.g.
```
sx = sx << 8;
func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);
```
Suppose we restructure so that vol's value is combined with sx first and then something else. E.g.
```
s32 w;
...
w = vol | (0x3000 | sx);
func_8002D4C8(0xA9B, w & 0xFFFF);
```
That's just a temp; doesn't change sets count for vol.

Alternative approach: use the *pin* on av ($5) which is already there, and change the PAN to be computed in a way that depends on av! Look: PAN = (sx + 0xA0)/0x14 where sx = (s16)(u16)&sxy, and av = |sx|. VOL uses av. Hmm, PAN uses sx.

But note: in the target, after `bgez a2` (the sx<0 test), the code uses a2 (=sx) for "addiu v0,a2,160" (PAN dividend = sx+160) and a1 (=av) for "subu a1,a0,v1" (VOL result = into a1?? weird but ok).

What if we write PAN as `(sx + 0xA0) / 0x14` where sx is derived from av (i.e., |sx|)? Not semantically identical (sign).

Hmm, but hold on: the branch `bgez a2` — in the target, if sx<0 it branches away (to 7440) and presumably the negative path computes av=-sx and continues. So in the fall-through path, sx >= 0, meaning sx == av! So the source could be written as: `if (sx < 0) { av = -sx; ... }` — the fall-through has sx==av.

In the banked source:
```
sx = (s16)*(u16 *)&sxy;
av = sx;
if (sx < 0) { av = -sx; }
vol = ((0xA0 - av) * 0x7F) / 0xA0;
sx = (sx + 0xA0) / 0x14;
```
The target's flow: bgez a2 → fall-through uses a2 (sx) for PAN and a1 (av) for VOL. Since av == sx in the fall-through, the compiler could have used a1 for PAN. It didn't (it used a2) — because in the branch-taken path, av = -sx ≠ sx.

What if we restructure the source so that in the fall-through the PAN dividend comes from a variable that is *also* used by VOL? Like:

```
sx = (s16)*(u16 *)&sxy;
if (sx < 0) { sx = -sx; }   /* hmm changes semantics for the pan? */
```
No: pan uses sx+0xA0 where sx could be negative in the original? In the original, if sx<0, the branch at bgez is taken (to 7440) — the negative case jumps elsewhere (probably the `av = -sx` block). So the negative case never computes pan! So we could rewrite as:

```
sx = (s16)*(u16 *)&sxy;
if (sx < 0) {
    sx = -sx;   /* then both vol and pan use |sx|? */
}
```
But then pan = (|sx| + 0xA0)/0x14 differs from (sx+0xA0)/0x14 when sx<0 — but in the original the sx<0 path branches to 7440 and doesn't compute pan at all. Hmm, but what IS at 7440? It's the block that handles the negative case: `av = -sx; vol = ...` and then also pan? If the target computes pan in the negative path too (using the negative sx), then we can't change it.

Looking at the target flow: `sra a2,v0,0x10; bgez a2,7440; move a1,a2; negu a1,a2; ...` — the branch target 7440 is a *forward* branch (0x7440 > current?). The branch is `bgez a2,7440` and mine[195] is also `bgez a3,7440`, so both go to the same place. Since bgez skips the negu (i.e. if sx>=0, skip the negation), the fall-through (sx<0) computes av = -sx. Then the fall-through continues to the two mult chains. So the chain computation happens in the sx<0 case?? and the sx>=0 case branches to 7440.

Wait: `bgez a2,7440` — if a2 >= 0 → jump to 7440 (skipping the negu). So the code at 7440 is the sx>=0 path, and the fall-through is the sx<0 path (av = -sx). Then the fall-through continues to the multiply chains. Hmm, but then where's the sx>=0 path's chain computation? At 7440. And the diff shows that after the chains, the code at ~7498/749c (bne a2,v0) is the join.

So the structure is: if (sx<0) { av=-sx; } else { goto 7440 (av = sx, i.e. av = sx) } — i.e. the source's `av = sx; if (sx<0) av = -sx;` compiles as a branch around the negation: fall-through (sx<0) does negu, and the branch (sx>=0) jumps to 7440 where... hmm, at 7440 the code must be "av = sx" equivalent — but the fall-through at 196 does "move a1,a2" (av = sx) and 197 "negu a1,a2" (av = -sx) in the <0 case, and 7440 must contain just the "move a1,a2" (av = sx) for the >=0 case. Then both paths join.

So 7440 is a small block: `move a1,a2` then jump to the join. And the diff's first 5 mismatches (137,143,178,185,192) are branch targets changing by 4 bytes (74ac vs 74b0) because my code has 1 fewer instruction (236 vs 237) → addresses shift. That's just address noise from the missing instruction.

Now the chains: both chains are in the fall-through path (sx<0). Wait, but then in the sx>=0 path (7440) are the chains also computed? The join at 749c/7498 is after the chains, and 7440 < 749c, so the 7440 block would have to include the chains too, or jump back... Hmm, 7440 is before the chains at ~7480. If the >=0 path jumps to 7440 and then falls into the chains, then both paths execute the chains. But then what's the difference? av = sx vs av = -sx. So the chains are shared. Good: 7440: `move a1,a2` (av=sx) then fall into the chains.

So the target: chains executed once after the join, computing VOL (using av in a1) and PAN (using sx in a2).

Now, in the target, the order is: chain1 = `mult v1,a0` (v1 = ? maybe 0x7F? no, v1 is used as `subu a1,a0,v1` → the VOL result = (mfhi>>6) - v1? hmm: subu a1,a0,v1 where a0 = t1>>6 → VOL = a0 - v1?? That looks like the signed division correction: for signed division gcc computes hi = (x*M)>>32, then result = hi>>s - (x<0 ? 1 : 0) → `sra v0,v0,0x1f` gives the sign, and `subu a1,a0,v1`? Hmm.

Let's decode the target chain:
```
mult v1,a0      ; v1 * M  (M=0x66666667)
mfhi t1
addiu v0,a2,160 ; v0 = sx + 160
nop
mult v0,a0      ; (sx+160) * M
sra a0,t1,0x6   ; t1>>6
subu a1,a0,v1   ; a1 = (t1>>6) - v1
sra v0,v0,0x1f  ; sign of (sx+160)
mfhi a2         ; high of 2nd mult
sra v1,a2,0x3   ; >>3
subu a2,v1,v0   ; a2 = (hi>>3) - sign
bne a2,v0,...
```
So: chain1: v1 * M, hi → t1, >>6 → the /160 quotient of (v1 * something)? and v1 is subtracted. Hmm, "subu a1,a0,v1" where v1 is the *dividend* of chain1: a1 = (v1*M >> 6) - v1?? That's the standard gcc-2.7 signed division sequence! For signed division by a constant, gcc 2.7 emits:

```
mult $dividend, $magic
mfhi $t
sra  $t, $t, $shift
subu $quotient, $dividend, $t     <- correction for negative dividend
```
Hmm: actually the classic gcc-2.7 signed div by constant:
```
mult
mfhi t1
sra t1,t1,s
subu a0,a0,t1   (?)
```
Let me recall the standard "divide by constant" for gcc 2.7 signed:
```
   mult   $4,$5
   mfhi   $6
   sra    $6,$6,3
   subu   $2,$4,$6
```
Hmm: the well-known sequence for signed division by 20 (M=0x66666667, s=6? no) — the known gcc-2.7 pattern:

```
mult $a0, $m
mfhi $t1
sra  $t1, $t1, $s
subu $result, $a0, $t1   # correction
```
Hmm no. The actual gcc 2.x sequence for signed division by a constant d (magic M, shift s):
```
   mult    dividend, M
   mfhi    tmp
   sra     tmp, tmp, s
   subu    quotient, dividend, tmp
```
That's for the case where M is chosen so that the correction is `dividend - tmp`? Hmm, that's the "round toward zero" correction: for negative dividends, hi>>s is off by one, so subtract (dividend<0).

But the target shows `subu a1,a0,v1` = a0 - v1 where a0 = t1>>6 and v1 = the dividend. So quotient = (hi>>6) - dividend?? That seems inverted. Unless the dividend is negative and the correction adds. Whatever, it's the same in both mine and target (mine: `subu a1,v0,v1` with v0 = a3>>3, a3 = hi of chain2). The order of the two chains is what differs.

Anyway: the two chains: chain A divides by 160 (shift 6) and chain B divides by 20 (shift 3). Chain A's dividend is v1 (a variable), chain B's dividend is (sx+160) → v0.

Which is which? VOL = ((0xA0-av)*0x7F)/0xA0: the *160 division with dividend (0xA0-av)*0x7F. PAN = (sx+0xA0)/0x14: /20 with dividend sx+160.

In the target: chain with shift 6 (/160) has dividend v1, and chain with shift 3 (/20) has dividend (a2+160). So v1 = (0xA0-av)*0x7F — computed earlier (v1 = 0x7F*(0xA0-av)). And the shift-3 chain gives PAN in a2, then sll a2,2,0x8 (sx<<8) and li a2,15.

In mine: the /20 chain comes first (mult a0,a2 with a0 = a3+160, result a3 → then sra v0,a3,0x3 → subu a3,v0,a0 → a3 = PAN), then the /160 chain (mult v1,a2 → mfhi t1 → sra v0,t1,0x6 → subu a1,v0,v1 → a1 = VOL).

So the register differences: in target, PAN result in a2 (then sll a2), VOL result in a1. In mine, PAN result in a3 (sll a3), VOL result in a1 (same).

So the difference boils down to: chain ORDER (VOL first vs PAN first) and consequently the register assignment (a2 vs a3 for PAN result).

To get VOL first in plain C, we need to prevent sched1 from hoisting the PAN chain above the VOL chain. The PAN chain is independent of the VOL chain in the current spelling, so sched1 hoists it.

Idea: give the PAN dividend a dependency on the VOL computation. But the PAN dividend is sx+160 while VOL is based on av. Hmm, but what if we restructure to compute the PAN dividend from a value that is *also* the VOL's? Like the classic trick: since in the fall-through av==|sx| and in the 7440 path av==sx...

Alternative idea: make the VOL chain's *result* feed the PAN chain — impossible semantically.

Alternative: use C-level ordering that the scheduler respects: gcc's sched1 (the "pre-reload" reorder pass) hoists instructions whose operands are ready. The PAN chain's dividend is (a2+160) = sx+160, and sx is defined long before. So it's ready early. The VOL chain's dividend v1 = 0x7F*(0xA0-av) is also ready early. Both chains are ready; sched1 picks order by some priority (the "birth" of the multiply?).

In the target the order is VOL chain first. What determines it? The magic constant a0 is shared: the target has ONE magic constant (a0) used by both chains: `lui a0,0x6666; ori a0,a0,0x6667` appears ONCE (at 198-199) before both mults. In mine, the magic is in a2 (from lui a2/ori a2 at 198-199) and both mults use a2: `mult a0,a2` (PAN) and `mult v1,a2` (VOL). Also shared! So both share the constant.

So both mine and target share the magic constant; only the order of the two mults and the dest regs differ.

So the question: what makes gcc order the chains VOL-then-PAN? In the target, the first chain is `mult v1,a0` — the dividend is v1 (the VOL product 0x7F*(0xA0-av)) and the second is `mult v0,a0` with v0 = a2+160 (PAN dividend). In mine the first is `mult a0,a2` (PAN dividend a0=a3+160) and the second `mult v1,a2` (VOL).

Hmm, in mine, the PAN dividend addiu is `addiu a0,a3,160` and the PAN mult `mult a0,a2`. So in mine the PAN chain is fully formed first.

Scheduling priority: gcc's sched1 gives higher priority to instructions with more refs (REG_N_REFS) or to the "birth" of a register. The chains share the same magic constant a0/a2.

Why would the target schedule VOL first? Because the vol chain's *result* is needed earlier? VOL is used in the final call arg along with sx: `(vol | (0x3000|sx)) & 0xFFFF`. The OR uses both. Hmm, the `or` needs sx (PAN result) and vol.

Hmm — wait. Maybe the ordering in the target isn't from sched1 at all but because in the target's source, the PAN division is *later* and the compiler's basic-block ordering put the chains in source order, whereas in mine, sched1 hoisted.

The lever comment says: "§21 ZERO-BYTE RE-TIE on vol. Both magic-multiplies write the same match_scratch, so sched1 (the PRE-reload pass) is free to swap them and always hoisted the PAN multiply first, inverting the whole tail schedule and losing the mfhi→mult hazard nop. Source statement order does NOT move it (9 spellings swept, all identical); only the re-tie does."

"Both magic-multiplies write the same match_scratch" — In gcc 2.7, a division by constant uses the "match_scratch" (a dedicated register, e.g. $at or a pseudo) to hold the magic constant. So both divisions' magic constants are materialized in the SAME scratch register (match_scratch) → the two chains both write to match_scratch → they must be ordered?! Actually if both use the same pseudo (match_scratch), then the two `lui/ori` are the same pseudo → they appear once, and the two mults read it. The re-tie (zero-byte re-tie on vol) means the two chains are "tied" to the same scratch, and a "re-tie" is a scheduling constraint.

"ZERO-BYTE RE-TIE" — in gcc's sched, "re-tie" refers to a scheduling constraint that ties the ordering of two insns that use the same pseudo (to avoid a hazard). §21 might be about "match_scratch" ties.

The launder `__asm__("" : "=r"(vol) : "0"(vol))` creates a copy of vol into a register (a "re-tie" in the sense of the REG tie between vol and the asm's output?). Per §153, a launder defeats cse for the value.

Hmm, honestly, the mechanism: the launder's "=r"(vol) output creates a NEW pseudo (the asm's output) tied to vol, which then... The output asm pseudo is a copy of vol, and vol's use in the OR reads the copy. This makes the VOL chain's result have 2 sets (vol and the asm pseudo) and the asm's output pseudo becomes the one used in the OR. This changes the ref counts and hence the scheduling priority of the chain.

So per the "real 2nd set" recipe from moves.md: give vol a real second set so that the compiler sees 2 sets. In our case: what if we write:

```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
...
func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);
```
Two sets: definition and the OR use — that's already 2 sets? No: "sets" = definitions. vol has 1 definition.

The "real 2nd set" from other items: `pv = *p; pv &= 0xFF000000; *p = pv | ...` — pv has 2 definitions. The launder `__asm__("" : "=r"(pv) : "0"(pv))` in the original created 2 sets (the original + the asm output) which cse couldn't merge.

For vol: can we create a genuine second definition without changing the generated instructions? E.g.:

```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
vol = vol & 0xFFFF;   /* extra insn - no */
```

Hmm. What about making the OR's operand a separate variable:
```
s32 w;
w = vol | (0x3000 | sx);
func_8002D4C8(0xA9B, w & 0xFFFF);
```
w has 1 set, vol 1 set. Doesn't create vol's 2nd set.

What about: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` then later `sx = (sx + 0xA0)/0x14;` and then use `vol` — the same.

Alternatively, make the *av* variable have two sets such that the VOL chain is tied differently. E.g. the source currently has `av = sx; if (sx<0) av = -sx;` (2 sets of av: sx and -sx). The target's structure (branch around negu) matches.

Hmm. What if we swap: compute `av` differently so that av's 2 sets change the ref counts, shifting the priority of the VOL chain? But the divergence is in the *order* of the two chains which is a sched1 priority issue.

Alternative pragmatic approach: try things! I have a fast score loop. Let me try a set of variants:

V1: launder removed (done): score 30.
V2: launder removed + PAN written as `sx = (sx + 0xA0) / 0x14;` moved BEFORE vol (statement order swap).
V3: launder removed + vol written as `vol = (0xA0 - av) * 0x7F / 0xA0;` (different spelling) — the multiply order.
V4: use a "real 2nd set" for vol: e.g. compute `vol` then `vol = vol` — not allowed (identity launder).

Hmm wait. Actually — maybe a much simpler idea: keep the launder's *effect* by using a C-level "second set" of the PAN variable instead. I.e. instead of laundering vol, we could give sx a second set so that the PAN chain is not hoistable. For example:

```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) { sx = 0xF; }
```
sx already has 2 sets here (the /0x14 and the 0xF). Hmm, the sx==0x10 comparison and the assignment. In the target: `bne a2,v0` then `sll a2,a2,0x8` and `li a2,15` — so the "if (sx==0x10) sx=0xF" is compiled as a compare+branch, and the sll is in the branch delay slot.

Hmm OK. Let me think about what makes the VOL chain's mult come first in the target. In the target both chains are after the "negu" (fall-through). The target's first chain: `mult v1,a0` — dividend v1 = the VOL numerator (0x7F*(0xA0-av)); the second: `mult v0,a0` — dividend v0 = sx+160 (PAN).

In mine: first `mult a0,a2` (PAN dividend a0 = sx+160), second `mult v1,a2` (VOL).

The register difference: the target's PAN chain uses v0 (temporaries) and lands in a2; mine's PAN chain uses a0/a3. So in the target, the PAN chain is a *late* chain (v0 = temp), while in mine the PAN chain is early (a0 = arg register).

Interesting: in the target, the VOL chain's dividend v1 is a temp; in mine, the VOL chain's dividend is also v1 but the PAN chain is a0/a3.

What if the difference comes from the *order of the two chain computations in the source* interacting with local-alloc's qty priority? The lever comment says the launder is "lever 3: sched1 otherwise hoists the PAN multiply ahead of this one", and "Both magic-multiplies write the same match_scratch, so sched1 is free to swap them".

Ahh, here's a thought: if both multiplies write the same match_scratch (the pseudo holding the magic constant), the compiler must order them?? No, they only READ match_scratch.

Hmm, "Both magic-multiplies write the same match_scratch" — in gcc 2.7, `expand_mult` for a division by constant generates a `mult` whose scratch is match_scratch for the *high part*: the sequence is:
```
mult dividend, magic
mfhi match_scratch
```
YES! The mfhi writes match_scratch. So both division chains write match_scratch (via mfhi), creating a WAW dependency between them — the scheduler must order them, and the order is by priority. And with the launder, the priority flips.

So the ORDER of the two mfhi's is decided by sched1's priority (REG_N_REFS, birth, etc.). The launder changes ref counts: the launder's output pseudo is a copy of vol, and the OR reads the copy...

Hmm, how does the launder affect the ORDER of the two chains? The chains' dividends: vol's chain dividend is v1 = 0x7F*(0xA0-av); pan's dividend is (sx+160).

OK you know what, enough theory. Practical: I have a fast experiment loop. Let me try a bunch of C-level variants quickly. Each variant = one sed -i on cand.c + one score command. The score output can be long (diff). Let me make the score command print only the first line: use `| head -1`. Earlier I used `head -40`; the diff is long. Let me use `2>&1 | head -1` for quick checks, and full output when needed.

Wait, but is `| head -1` allowed? Pipes were fine earlier (grep -c | ...). Yes.

Let me set up: cand.c = copy of orig.c (via the sed r-trick from d1.c). Then variants via sed -i.

Variant ideas for item 1 (all with the launder removed):
(a) swap statement order: put the sx = (sx+0xA0)/0x14 block BEFORE vol.
(b) write vol with explicit parens: vol = (0xA0 - av) * 0x7F / 0xA0;
(c) make the pan dividend a separate variable: s32 pd = sx + 0xA0; sx = pd / 0x14;
(d) make vol's numerator a separate variable: s32 vn = 0x7F * (0xA0 - av); vol = vn / 0xA0;
(e) combine: both.

Note (d): "vol = (0x7F * (0xA0 - av)) / 0xA0" vs "vol = ((0xA0 - av) * 0x7F) / 0xA0" — the multiply operand order changes which register.

Let me try these. Each score run takes some seconds (compile). Fine.

Let me first make cand.c.

Also note: my sed edits are on cand.c; the sed 'r' trick requires the source file to exist.

Steps for item 1:
1. sed -i '1r orig.c' d1.c? No: d1.c already = orig content. Let me create cand.c = d1.c content: use `sed -i '1r d1.c' cand.c` after creating cand.c with Write ("x\n"). But Write costs tokens only for small content. Good: Write cand.c with "x\n" then sed r-trick.

Actually simpler: keep using d1.c as the working file (rename semantics don't matter) — but the name should be meaningful. I'll create cand.c via the trick and keep d1.c as scratch.

Let me do: Write cand.c with "x\n"; sed -i '1r .../orig.c' cand.c; sed -i '1d' cand.c. Then cand.c == orig.c.

Then variant edits.

Let me proceed. Note the launder line in orig.c is:
`            __asm__("" : "=r"(vol) : "0"(vol));  // !FAKE: launder`
Delete it: sed -i '/"=r"(vol)/d' cand.c.

Let me combine: after creating cand.c from orig.c, delete the launder line. Then score. Then try variants.

Also cleanup: remove d1.c, strip.py, score.py at the end (scratch cleanup). And I should delete score.py/strip.py since they can't be run anyway.

Let me go.

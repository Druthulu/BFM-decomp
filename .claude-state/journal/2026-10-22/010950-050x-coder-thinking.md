---
ts: 2026-10-22T07:09:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_uMI9PqwVH28wozrkVjAS
---
The target's sequence:
- c58: lui a0,0x6666 / ori a0,0x6667 → the magic constant 0x66666667 for /160.
- c60: li v0,160 ; c64: subu v0,v0,a1 → v0 = 160 - av
- c68: sll v1,v0,0x7 ; c6c: subu v1,v1,v0 → v1 = v0*127
- c70: mult v1,a0 ; mfhi t1 ; sra v1,v1,0x1f ; sra a0,t1,0x6 ; subu a1,a0,v1 → a1 = the quotient (vol)
- Then the pan: c78: addiu v0,a2,160 ; c80: mult v0,a0 ; c90: sra v0,v0,0x1f ; mfhi a2 ; sra v1,a2,0x3 ; subu a2,v1,v0 → a2 = (sx+160)/20

So the two divisions by 160 and 20 use the same magic constant a0 = 0x66666667.

Interesting: the vol division is `((0xA0 - av) * 0x7F) / 0xA0` = ((160-av)*127)/160. The magic for /160 is 0x66666667 with a shift of 6 (sra a0,t1,0x6) and the sign correction (sra v1,v1,0x1f; subu a1,a0,v1).

And the pan division is (sx+160)/20 → magic 0x66666667? Hmm, /20's magic is 0xCCCCCCCD with a shift of 3. But the target uses `mult v0,a0` with a0 = 0x66666667 and sra v1,a2,0x3 → hmm, that's the /20 division using the same 0x66666667 constant? For /20: magic = 0xCCCCCCCD, shift 3. But the target shows `mult v0,a0` where a0 = 0x66666667 and then `mfhi a2; sra v1,a2,0x3`. Hmm, 0x66666667 * n >> 32 >> 3 = n * 0x66666667 / 2^35 ≈ n/20.4. For n = sx+160 where sx ∈ [-160, ...]. Yes, gcc uses the "add" magic form sometimes. Anyway.

So both divisions share the constant 0x66666667 in a0 (cse merged them!). And the ORDER matters: the vol division's `mult v1,a0` (c70) comes BEFORE the pan's `mult v0,a0` (c80). The launder on vol kills the boost so that the vol multiply is scheduled before the pan multiply.

Hmm, interesting: the launder is on `vol` (a pseudo). The comment says "sched1 otherwise hoists the PAN multiply ahead of this one".

So: vol needs a 2nd SET. The G11 recipe: a compound assign.

Here, `vol = ((0xA0 - av) * 0x7F) / 0xA0;` → what if we write it as:
```
vol = (0xA0 - av) * 0x7F;
vol /= 0xA0;
```
Then vol's pseudo has 2 sets: the multiply and the division (the division is an RMW on vol). And the value is the same.

But will the generated code be identical? The target's division: `mult v1,a0; mfhi t1; sra v1,v1,0x1f; sra a0,t1,0x6; subu a1,a0,v1`. The dividend is v1 = (160-av)*127. With the compound form, the dividend would be vol's pseudo (which holds (160-av)*127) → the same insns but vol's pseudo would be the dividend and the quotient.

Hmm, but in the compound form, gcc must first put (160-av)*127 into vol (a copy or the multiply result), then divide in place. The target has: subu v0 (160-av), sll/subu v1 (×127), then mult v1,a0 — so the dividend is in v1 and the quotient lands in a1. In the compound form: vol = (160-av)*127 → the multiply result in vol (v1?), then vol /= 160 → the magic multiply on vol's pseudo → the result in vol → then `vol` is used in the call arg.

The number of instructions might differ by a copy. But it's worth trying!

Also alternative: `vol = (0xA0 - av) * 0x7F / 0xA0;` is the current form.

Other ways to give vol a 2nd set:
- `vol = ...; vol = vol;` folded.
- Use `vol` in a compound: `vol |= 0;` folded.

Hmm, another approach: the launder's purpose is to kill the birth boost of vol's pseudo. What if we instead give vol a 2nd set by writing the division as a compound? That's the plan.

Also possible: since the same magic constant is used by both divisions, maybe the order can be fixed differently.

Let me first check what the score of the plain removal is (cand01) — that gives the baseline diff.

Let me set up the item dir and run cand01 (remove the launder asm).

Note: this function's body is big (94 lines) but the diff tool compares the whole function.

Let me create cand01 = orig with the launder line removed.

Note: the launder line is:
```
            __asm__("" : "=r"(vol) : "0"(vol));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t8_tus2)
```

Let me write a script for this item too. Actually let me just create the candidates with a python script.

Candidates:
cand01: remove the launder.
cand02: `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` (compound divide) — replaces the two lines:
```
            vol = ((0xA0 - av) * 0x7F) / 0xA0;
            /* sched1 otherwise hoists the PAN multiply ahead of this one */
            __asm__(...);
```
→
```
            vol = (0xA0 - av) * 0x7F;
            vol /= 0xA0;
```
cand03: `vol = (0xA0 - av) * 0x7F; vol = vol / 0xA0;` (plain assign, 2 sets but a new temp? no — vol = vol/0xA0 is an RMW too).
cand04: `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` with the multiply written as `(0xA0 - av) * 0x7F` vs `0x7F * (0xA0 - av)`.

Let me start with cand01 and cand02.

Also I need to double check the "no signature or decl change outside the body" — I'm only changing the body ✓.

Let me write the generator script.

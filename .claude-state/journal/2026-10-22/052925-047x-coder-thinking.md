---
ts: 2026-10-22T11:29:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_1W9nOipmDcHNCqf3iLFt
---
Now I see the residual clearly:

Target:
```
198: lui a0,0x6666
199: ori a0,a0,0x6667      <- the magic constant materialised at the TOP (in a0)
...
201: subu v1,v1,v0
203: mult v1,a0
206: addiu v0,a2,160
208: mult v0,a0
209: sra v1,v1,0x1f
210: subu a1,a0,v1
211: sra v0,v0,0x1f
214: sra v1,a2,0x3
215: subu a2,v1,v0
```

Candidate (mine):
```
201: subu a1,v1,v0
202: lui v0,0x6666
203: ori v0,v0,0x6667
204: mult a1,v0
206: addiu v1,a2,160
208: mult v1,v0
209: (nothing)
210: sra v0,a1,0x1f
211: subu a1,a0,v0
212: sra v1,v1,0x1f
214: sra v0,a2,0x3
215: subu a2,v0,v1
```

So: in the TARGET, the magic constant 0x66666667 is materialised ONCE at the top (in a0) and used by BOTH multiplies (the /0xA0 division and the /0x14 division — both use the same magic? interesting: 0x66666667 is the magic for /10 and the code does `vol = (0xA0-av)*0x7F/0xA0` and `sx = (sx+0xA0)/0x14`... hmm, but both use 0x66666667? Let me look at the target more.

Wait: `sra v1,v1,0x1f` then `subu a1,a0,v1` — that's the signed division by 10 pattern: mult by 0x66666667, take the high 32 bits (mflo/mult?), shift right 31, subtract. Actually MIPS `mult` gives the 64-bit product in hi/lo; the code uses `mult v1,a0` then presumably `mflo`.

Anyway, the key difference: the target materialises the constant 0x66666667 ONCE at the top of the tail and uses it twice; the candidate materialises it in the middle (right before the first mult).

Hmm, but wait — the count is the same (237) in both, and the candidate has `lui v0,0x6666; ori v0,v0,0x6667` while the target has `lui a0,0x6666; ori a0,a0,0x6667` — same number of instructions, just at a different position and different register.

So the fix: get the constant materialised at the TOP of the tail (before the first chain), in a register that stays a0.

The launder `__asm__("" : "=r"(vol) : "0"(vol));` was what did that (it's a barrier between the chains, so sched1 couldn't hoist the PAN chain above the VOL chain, and the constant was born at the top).

Hmm, and also: the target uses a0 for the constant while the candidate uses v0.

What is the "tail"? The block containing the `if (sx == 0x10) ... func_8002D4C8(...)`. Let's see the target around index 190-220 to understand.

Let me get the target disassembly for func_801832A8 around there.

Let me find the object.

Actually, let me think about what's needed:
1. The constant 0x66666667 must be born at the top of the tail (before both chains).
2. The register allocation must give a0 to the constant.

The candidate (w4) has the VOL chain first (good) but the constant is born just before the first mult.

Hmm, why? Because the constant is used by the VOL chain's mult, and GCC materializes it right before use. To have it at the TOP, the constant must be "hoisted" — its birth must be earlier.

Hmm, "birth boost": from the cookbook, a constant that's used by 2 places gets hoisted. In the target it's used by both multiplies → hoisted to the top. In the candidate... it should also be used twice.

Hmm, in the candidate, is the constant used twice? Candidate:
```
202: lui v0,0x6666
203: ori v0,v0,0x6667
204: mult a1,v0
...
208: mult v1,v0
```
Yes, used twice, but born at 202 (just before the first mult at 204), not at the top.

The target:
```
198: lui a0,0x6666
199: ori a0,a0,0x6667
...
203: mult v1,a0
...
208: mult v0,a0
```
Born at 198.

So the difference is WHERE the constant is born — the target's is born earlier (higher up in the block).

So what makes GCC birth the constant earlier? If the constant is used by an insn that comes earlier in the schedule.

Hmm. Since both chains use it, the constant's position is determined by the scheduler.

Hmm, the candidate has the VOL chain first (per the notes: the compound assignment puts VOL first, matching the target). And the target has VOL first too? Let's check: target 201: `subu v1,v1,v0` — this is `(0xA0 - av)`: subu v1,v1,v0 where v1=0xA0? and v0=av. Then 203: mult v1,a0 (the *0x7F multiply). Then 206: addiu v0,a2,160 (the sx+0xA0). So the target's VOL chain is first too. ✓

So both have VOL first; the difference is the constant's birth and the register (a0 vs v0).

Now: in the target, the constant is born at index 198, before the VOL chain's subu at 201. So there are 2-3 instructions between 199 and 201.

What if the "tail" block starts with something? Let me get the target disassembly to see indices 190-220.

Let me look at the target.

Hmm, I realize the diff shows the target at 198-199 has the lui/ori in a0. What's at 200? Let me look at the full target listing.

Let me disassemble.

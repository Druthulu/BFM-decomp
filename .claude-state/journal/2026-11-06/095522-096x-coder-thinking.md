---
ts: 2026-11-06T16:55:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hQ3uOCq4ogrAq4iTbV8L
---
Very interesting. The target uses s0 as a persistent scratch across the whole function (it's a callee-saved register saved in the prologue). Look at the first computation (8dec-8e04):
```
bgez v0,8df8
move s0,v0        ; delay slot: n = q
addiu s0,v0,4095  ; if q<0: n = q+4095
sra s0,s0,0xc
sll s0,s0,0xc
jal rand          ; second rand for radius
subu s0,v0,s0     ; q2 - n
```
So s0 is used across the `jal rand` call! n's live range spans the call. In the source:
```
func_8012B0B4(&sp10, rand() % 0x1000, rand() % (...));
```
Hmm wait, this is the FIRST part: `rand() % 0x1000`. The code:
```
jal rand
bgez v0 ...
move s0,v0
...
sra s0,s0,0xc
sll s0,s0,0xc
jal rand          <- the third argument's rand()
subu s0,v0,s0     <- q - n
```
So `n` here is the temp for `rand() % 0x1000`! The source `rand() % 0x1000` compiles to: q=rand(); n = q; if (q<0) n=q+4095; n >>= 12; n <<= 12; q - n. That's the `%` expansion for a power of 2? Wait, 0x1000 = 4096, and the code uses sra 0xc/sll 0xc. Yes! `rand() % 0x1000` with signed int.

But our source writes `rand() % 0x1000` directly in the call argument, not as the n computation. So the compiler expands it. And n (our variable) is used in the OTHER computations (`q = rand(); n = q; ...`).

Hmm, but the target's s0 is used for BOTH: the first modulo and the two later ones. Since all these are the same variable n? No — the first is compiler-generated for `% 0x1000`.

Look at the target: s0 is set at 8df0 (delay slot of bgez) — that's the compiler's `%` expansion for `rand() % 0x1000`. Then reused at 8e94, 8ecc, 8ed0. So the compiler used the SAME register s0 for the `%` expansion temps and our variable n. The pin on n forced $16, and local-alloc also used $16 for the modulo temps? Hmm, but our variable n is a separate variable.

Wait, actually maybe our variable n IS the `%` expansion variable for the source's explicit `n = q; if (q<0) n=q+3; n = n>>2; n = n<<2; m = (q-n)<<16;` — and the target's s0 in the first part comes from `rand() % 0x1000` expanded by the compiler, which is a different temp that local-alloc gave s0 because... the pin on n reserved $16 for n, and local-alloc reused it for the modulo temps since n wasn't live yet? Hmm, that's the "global-hardreg-reserve" wall: the pin's hard-reg pseudo reserves a reg for the whole fn.

Actually, the target is the *baseline with the pin* and scores 0. We need to remove the pin and get the same allocation. The pin forces n to $16, and that has side effects: $16 (s0) is reserved and used as a scratch for the modulo expansions.

Without the pin, n goes to v1, and the modulo expansion temps use v1/v0.

We need real C that puts n in s0. Since n's live range in the source (the explicit computations) does NOT cross a call, the allocator gives it a caller-saved scratch (v1). The target has s0 because the pin forced it AND because the modulo temps were assigned to s0.

What real C would make the compiler allocate s0? A variable live across a call gets a callee-saved register. Our n could be made live across a call if the source used it in a way that spans a call.

Hmm, but the target's usage of s0 for the *first* modulo (rand()%0x1000) spans the rand() call for the third argument. That's compiler-generated: the first argument `rand() % 0x1000`'s temp is live across the second argument's `rand()` call. So the compiler needs a callee-saved reg for that temp — that's why s0 exists! The first modulo temp is live across the second rand() call (argument evaluation order). So the compiler picks s0 for it.

Then, in the target, our variable n (from the later computations) reuses s0 because... the pin forced n to $16, so it's the same register. Without the pin, the first modulo temp still needs a callee-saved reg (it's live across the call) — let's see what mine does.

Mine (no pin) diff showed v1->s0 x14, v0->s0 x4. So mine uses v1 for n and v0 for q, and s0 somewhere. Let me disassemble mine to see the first part.

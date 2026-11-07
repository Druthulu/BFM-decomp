---
ts: 2026-11-06T16:58:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8fEJ4passJbKqv5b8EBY
---
Worse (123). The if/else duplication made cse place the expression in both arms.

Let me step back and think about the target's RTL. Maybe there's a simpler real-C formulation of `rand() % 4` that produces the same code but with n's live range crossing the call naturally. The target's code for `rand() % 4`:
```
jal rand
bgez v0, L
move s0,v0
addiu s0,v0,3
L: sra s0,s0,2
   sll s0,s0,2
   subu s0,v0,s0
jal rand (sign)
sll s0,s0,0x10
```
Hmm, this is `q % 4` computed with s0. The source `rand() % 4` — the compiler's expansion of `%` for a non-power-of-2 constant uses div; for 4 it uses the sign-fix + sra/sll sequence. The temp for `% 4` is a compiler temp (not a source variable). local-alloc assigns it. If the source were `m = (rand() % 4) << 16;`, the temp would be block-local and get v1 (lowest free). But the target has s0.

Unless... the original source's expression made the temp cross the call. E.g.:
`m = (rand() % 4) << 16;` — the temp dies before the next call.

Hmm, so why s0? Because the target's pin? NO — the target is the ground truth from the original game, not from our pinned source! Wait, is it? The target.s is the disassembly of the original game's function. The pinned source scores 0 against it, meaning our decompiler source + pin reproduces the original's code exactly. The original code has s0 for the `%4` temp.

So the original compiler (same gcc 2.7.2) chose s0 for the `%4` temp. Why? Maybe the original source had the temp live across the call because of a different expression structure, e.g.:

`m = ((rand() % 4) << 16);` with the sign applied later:
```
if (rand() & 1) m = -m;
```
Still no.

OR maybe the original source computed the *sign first*:
```
m = (rand() & 1) ? -(rand() % 4) << 16 : (rand() % 4) << 16;
```
No.

Hmm, what if the original is:
```
m = ((rand() % 4) * (rand() & 1 ? -1 : 1)) << 16;
```
Unlikely.

Let's look at the target's first modulo again: `rand() % 0x1000` uses s0 across the `jal rand` of the third argument. So s0 is already "the modulo temp register" in this function. Then the `%4` temps reuse s0 because... local-alloc assigns per-block; s0 was allocated to the first modulo temp (crossing a call). The later `%4` temp could be v1.

Unless the `%4` temp ALSO crosses a call! Look at the target's second computation: `sra s0,s0,2; sll s0,s0,2; subu s0,v0,s0; jal rand; sll s0,s0,0x10` — the `%4` temp dies at the subu, before the jal. But the *result* m lives in s0 across the jal. So s0's value crosses the call (m), but the `%4` temp doesn't.

Hmm, so local-alloc assigned s0 to the `%4` temp AND the allocator ties m to s0 because m is born right after the temp dies. In local-alloc, when a qty dies and another is born, the new qty gets a "copy suggestion" or reuses the register via find_free_reg (lowest free). If s0 is free at m's birth... but v1 is lower. Unless v1 is occupied by q? q is v0. Hmm.

Wait, actually m is live across calls (it's used after the jal), so local-alloc must give m a callee-saved reg → s0 (lowest s-reg). So m = s0 naturally. And the `%4` temp (n) dies just before m's birth; local-alloc gives it v1 (lowest free, no calls crossed).

The target gives n = s0 because the *pin* forced n to $16. So the target's n = s0 is a consequence of the pin, not of natural allocation! 

Hmm, but the target is the original game's code... and the pinned source reproduces it. So the original's n was in s0. Why would the original's compiler put a short-lived temp in s0?

Maybe because in the original source, the `%4` temp WAS live across a call. Consider:
```
m = (rand() % 4) << 16;
if (rand() & 1) ...
```
no.

OR the original source was:
```
m = (rand() % 4) << 16;
```
where the `%4` temp's value is used in the `sll` after the sign call? No, the sll is after the call only due to scheduling.

Hmm, let me look at the target's RTL possibilities: `subu s0,v0,s0` then `jal rand` then `sll s0,s0,0x10`. In the RTL, `m = (q-n) << 16` is likely one insn sequence: sub, sll. Sched1 moved the sll into the delay slot. So n dies at the sub, before the call.

For local-alloc to pick s0 for n, n must cross a call OR s0 must be suggested. Copy suggestions! local-alloc has `qty_phys_copy_sugg`: if n's value is copied to/from another qty already in s0... 

Hmm, here's a thought: the first modulo temp is in s0 and is live across a call. Our n is a DIFFERENT pseudo. But if the compiler *reused the same pseudo* for both (e.g. the source used one variable for both modulos!), then n would be one pseudo live from the first modulo (across the call) to the last use → s0!

Look at the source: the first modulo `rand() % 0x1000` is a compiler temp. Our n is a source variable. What if the original source had `n` used for the first modulo too? E.g.:

```
n = rand() % 0x1000;
func_8012B0B4(&sp10, n, rand() % (...));
```
Then n's value crosses the rand() call for the third argument! And n would get s0. Then the later computations reuse the same variable n → same pseudo → s0. That would explain the target!

But wait, the target's first modulo code is exactly the `%` expansion with s0: `move s0,v0; ... sra/sll; subu s0,v0,s0` — that's `q % 0x1000`, i.e. the compiler's expansion of `rand() % 0x1000`. If the source wrote `func_8012B0B4(&sp10, rand() % 0x1000, ...)`, the temp is compiler-generated. If the source wrote `n = rand() % 0x1000; func(..., n, ...)`, the temp is n, live across the next rand call.

But the target's first modulo's value is in s0 and used at `move a1,s0` (8e50) — the second argument. So if n were the first modulo's result, n = s0 and crosses the call → natural s0! And then the later `n = q; ...` reuses the same variable, and local-alloc... the pseudo n is set multiple times; the first range crosses a call → n_calls_crossed > 0 → local-alloc gives n s0 for ALL its ranges (local-alloc doesn't split).

That fits perfectly! The original source likely had:
```
n = rand() % 0x1000;
func_8012B0B4(&sp10, n, rand() % (...));
```
Hmm, but the target's arg setup: `move a1,s0` (the second arg = n) and `mfhi a2` (the third arg = rand() % ...). Yes.

But our source passes `rand() % 0x1000` directly as the second argument. The expansion temp is compiler-generated and local-alloc gives it s0 (crosses the call) — that's the same s0. So the first modulo matches either way.

The difference: if the source names it `n`, then n is the SAME variable used later → one pseudo with calls_crossed > 0 → s0 for all ranges. That's the crack!

Let me restructure:
```
n = rand() % 0x1000;
func_8012B0B4(&sp10, n, rand() % ((*(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) * 3) >> 9));
```
But careful: the target's first modulo sequence is `bgez v0, ...; move s0,v0; addiu s0,v0,4095; sra s0,s0,0xc; sll s0,s0,0xc; jal rand; subu s0,v0,s0`. This is `% 0x1000` with the subu AFTER the jal (because the second rand is evaluated before the subtraction? no—). Actually the `%` expansion: q=rand(); n=q; if(q<0) n=q+4095; n>>=12; n<<=12; q-n. The compiler schedules the final subu after the other rand call (sched1 moved it). So the value n (the rounded-down q) is live across the jal → s0. Fine.

If we name it `n`, the pseudo n is set to q then modified; its live range ends at the subu (after the call). So n crosses the call → s0.

Then the later computations assign n again — the same pseudo. local-alloc: n_calls_crossed > 0 → only callee-saved regs → s0 (lowest). 

Let me try:
```
n = rand() % 0x1000;
func_8012B0B4(&sp10, n, rand() % ((*(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) * 3) >> 9));
```
But wait: the argument order. `func_8012B0B4(&sp10, arg2, arg3)`. The source has `rand() % 0x1000` as arg2. Replacing with n requires n computed before the call.

However, `n` is declared s32; `rand() % 0x1000` is int. Fine.

But there's a subtlety: the target's code evaluates rand() for arg2, then rand() for arg3, then calls. With `n = rand() % 0x1000;` before the call, the order is the same.

Also the target's `move a1,s0` at 8e50 — a1 = n = s0. Good.

Let me try this variant.

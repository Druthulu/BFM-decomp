---
ts: 2026-11-06T17:00:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RmRX1vcwMnholVRg2puG
---
In the pinned version, register n = $16 (16) should be listed... The list shows pseudo registers (>= 72). Let me grep for register 16 or the hard reg. The lreg dump lists pseudos; hard reg 16 wouldn't be listed. Hmm.

The pin makes n a hard register $16, so it's not in the lreg list.

OK, different approach. The `%4` temp in the target is in s0. Since the pin forces n=$16 and the source assigns n = q; ... the `%4` expansion's temp IS n (the source's n). In the unpinned version, the same expansion uses a pseudo n; local-alloc gives it v1.

So the target's s0 for the `%4` temp is purely the pin's doing. To reproduce with real C, we need a different mechanism.

Let me think about what the ORIGINAL source was (before the decompiler introduced n). Maybe:
```
m = (rand() % 4) << 16;
if (rand() & 1) ...
```
In that case, the `%4` temp is a compiler temp. Would local-alloc give it s0? Only if it crosses a call. Hmm.

Let me look at the target's `%4` expansion: `bgez v0, L; move s0,v0; addiu s0,v0,3; L: sra s0,s0,2; sll s0,s0,2; subu s0,v0,s0`. In this code, the temp s0 is set in the bgez delay slot and used in the subu. The `jal rand` (sign) is AFTER the subu. So the temp doesn't cross the sign call. But wait — maybe the RTL order has the subu after the jal (sched1 hoisted it before). In the target's .s the subu is before the jal. If the RTL had it after, sched1 moved it before — plausible since it's pure.

If the RTL had the subu after the sign call, the temp would cross the call → s0. And that would happen naturally if the source is:
```
m = (rand() % 4) << 16;
```
Hmm no, the rand() call is evaluated first (it's the operand), then the % expansion, then <<16, all before the next rand.

UNLESS the compiler's argument/expression evaluation order interleaves: `m = (rand() % 4) << 16;` — the rand call completes, then the % expansion. No crossing.

Hmm, what if the source is `(rand() % 4) << 16` used directly in a call argument that also has another rand? No.

Wait, maybe the sign is applied to the *%4 temp* before the shift:
```
m = (rand() & 1) ? ... 
```
no.

Let me reconsider: maybe the original source is:
```
m = ((rand() % 4) << 16) * (rand() & 1 ? -1 : 1);
```
Unlikely.

Alternatively, maybe the original code used a *helper function*? No, the code is inline.

Hmm, let me look at the target's sign call: `jal rand` at 8ea8. Before it: `subu s0,v0,s0` at 8ea4. After: `sll s0,s0,0x10` in the delay slot. So sched1 moved the sll into the delay slot. The sub is before. So in the RTL, the `%4` temp dies before the call, unless the RTL order was: sub after jal and sched1 moved it before (but then the sll would also move... sched1 moved only the sll into the slot, meaning the sll was the last insn before the call in RTL order? If the RTL had [jal, sub, sll], sched1 couldn't move the sub before the jal (it's after and depends on jal's result v0? no, sub depends on v0 = q and s0). Hmm.

Actually, if the RTL were [jal rand; subu; sll], sched1 could hoist both sub and sll before the jal if it's safe (it is: v0 holds q, but jal clobbers v0!). The jal rand clobbers v0, so the sub (using v0=q) MUST be before the call. So the RTL must have the sub before the jal. Therefore the `%4` temp dies before the call in the target's RTL.

So the target's temp is s0 for a different reason: the pin. The original source must have had something else that made the temp s0.

Hmm, wait. What if the original source used the SAME variable for q and the temp, e.g.:
```
q = rand();
q = q % 4;      /* or n = q; ... */
m = q << 16;
```
Then the temp (q) is live... still no call crossing.

What if the original's `%4` temp was shared with the FIRST modulo temp? The first modulo temp crosses a call and gets s0. If the compiler reused the same pseudo for both (e.g., both are the result of `rand() % K` assigned to the same variable), then the second `%4` temp would be the same pseudo → s0.

For that, the source would be like:
```
n = rand() % 0x1000;
func(&sp10, n, rand() % X);
...
n = rand() % 4;
m = n << 16;
```
i.e., use ONE variable n for both the first modulo and the %4! Then n is one pseudo; its first live range crosses a call → n_calls_crossed > 0 → local-alloc gives n s0 in all ranges.

That's promising! And it also explains why the target's first modulo is in s0 (it's n) and the later %4 in s0 (same n).

But wait, the target's first modulo: `move s0,v0; addiu s0,v0,4095; sra s0,s0,0xc; sll s0,s0,0xc; subu s0,v0,s0`. If n = rand() % 0x1000, the final subu result is n. The intermediates are the same pseudo n? The `%` expansion uses temps; the assignment to n happens at the subu. Hmm, but with `n = rand() % 0x1000`, gcc might expand the modulo into temps and then set n. The intermediates would be temps, not n.

In the target, the intermediate q copy is s0 — the same register. That suggests the temp and n are the same register (local-alloc can reuse).

OK, let me just try the "one variable n for both" structure:
```
n = rand() % 0x1000;
func_8012B0B4(&sp10, n, rand() % (...));
...
q = rand();
n = q;
if (q < 0) n = q + 3;
n = n >> 2;
n = n << 2;
m = (q - n) << 16;
...
```
That's z3 + keeping the later n computations (z3 already does that!). z3 scored 13 with 118 ins. The first modulo differed (v1 intermediates) and the later n still used v0/v1.

Hmm, z3's later n: `subu v0,v0,s0` — so the later n was in s0? Let me disassemble z3 fully to see.

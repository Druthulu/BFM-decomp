---
ts: 2026-11-06T16:59:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SLDY92YSZ5VzZ0AJKbvt
---
Interesting! z3 is close (score 13, 118 vs 117). The first modulo now uses v1 for the intermediate (q) and s0 for the rounded value:
```
move v1,v0      (n = q, in v1)
bgez v1, ...
addiu v0,v1,4095
sra s0,v0,0xc
sll v0,s0,0xc
subu s0,v1,v0
```
Target:
```
bgez v0, ...
move s0,v0
addiu s0,v0,4095
sra s0,s0,0xc
sll s0,s0,0xc
subu s0,v0,s0
```
So the named variable n got split into multiple pseudos by gcc's `%` expansion? Actually the `%` expansion uses temps; naming n = rand()%0x1000 creates a pseudo n whose value is the final result (subu). The expansion temps are separate.

In mine, n's pseudo is s0 (the subu result at 33 `subu s0,v1,v0`), and the intermediate is v1. Target has everything in s0.

Also the later computations: mine[73] `subu v0,v0,s0` vs target `subu s0,v0,s0` — the later n is still v0/v1, not s0.

Hmm, z3 got the first modulo's n into s0 (crossing the call), but the later n computations use v0/v1 because... n is redefined; local-alloc gives each live range a register based on n_calls_crossed for the whole pseudo. If n crosses a call in its first range, all ranges should be s0-only. But mine shows the later ones in v0/v1 — maybe the later uses are a different pseudo (the compiler may create a new pseudo per assignment? No, same variable).

Wait, mine[73:74] `subu v0,v0,s0` — this is `q - n` where n = s0 (from `sll v0,s0,0xc`? hmm). Let me disassemble z3 to see.

Actually the score is 13 with 118 ins (one more than target). Close but not matching. The first modulo's expansion differs (v1 intermediates). Maybe because n is now a named variable, the expansion of `%` produces a different temp sequence.

Hmm. What if we name n for the first modulo AND ensure the `%` expansion temp is n itself? The target's expansion uses s0 for the intermediate q copy (`move s0,v0`). In mine, the expansion uses v1 for the intermediate and s0 for the result.

The `%` expansion: gcc computes `q - (q/4096)*4096` using a temp. With n = rand() % 0x1000, the assignment to n means the final subu's destination is n's pseudo (s0). The intermediate temp (q copy) is separate (v1).

Target: the intermediate is also s0 (the same register). That suggests the target's `%` temp and the result are the same pseudo — i.e., the compiler's expansion reuses the same pseudo, and local-alloc gave it s0.

Hmm, in the target the sequence `move s0,v0; addiu s0,v0,4095; sra s0,s0,12; sll s0,s0,12; subu s0,v0,s0` — this is one pseudo s0 that is copied from q, adjusted, shifted, then subtracted. That's exactly the `%` expansion where the temp is a single pseudo. And it's s0 because it crosses the call (the subu is after the jal due to scheduling — but the RTL order might have the subu before the jal and sched1 moved it).

Hmm, wait: if the subu is before the jal in the RTL, the temp doesn't cross the call, so local-alloc would use v1. But the target uses s0. So in the target's RTL the temp DOES cross a call — meaning the source had the temp live across the call.

In our original (unnamed) source, `rand() % 0x1000` as an argument: the temp is used in the arg setup after the second rand's evaluation? Argument evaluation order: gcc evaluates args left to right? For `f(a, rand()%0x1000, rand()%X)`, it may evaluate arg1 then arg2 then arg3. The temp for arg2 must survive the arg3 rand → crosses a call → s0! Yes! That's why mine (original) had s0 for the first modulo — it matched.

OK so the first modulo is fine in the original. The problem is only the later n computations.

So naming n for the first modulo (z3) changes the first modulo's expansion (bad) and doesn't fix the later ones.

Let me revert to the original structure and think about the later n.

Target later n: s0. Why would the original's compiler put the `%4` temp in s0? The `%4` temp in the target is used in `subu s0,v0,s0` and the result m = s0. If the `%4` temp crossed a call, it'd be s0.

Look at the target's vel X computation RTL possibilities: maybe the source is `m = (rand() % 4) << 16;` and the `%4` temp's value is used in the `subu` which is scheduled after the jal. In RTL, is the subu before or after the jal? sched1 moved it. The RTL order determines liveness: if the RTL has the subu before the jal, the temp dies before the call. If after, it crosses.

The target's *final* code has the subu before the jal (8ea4 before 8ea8). So the RTL could be either (sched1 moved it). We can't tell from the .s alone; need the dumps.

Let me dump the orig (pinned) RTL and look at the `%4` temp's liveness. That will tell us whether the pin made the temp live across the call or whether the pin itself is what put it in s0.

Actually, the pin is a hard-reg pseudo n = $16. In the pinned RTL, the `%4` expansion assigns to n directly (since the source assigns to n). So n is a hard reg — always $16. The `%4` temp IS n. So the target's s0 is trivially from the pin.

So the question is: what real C makes the `%4` temp be allocated s0? We need the temp to cross a call.

Idea: the `%4` temp could cross the *sign* call if the source order puts the subtraction after the sign call. But the target's RTL might have it before.

Alternatively, the `%4` temp could cross the *next* rand call (for the second vel) if n is reused. But n is reassigned.

Hmm, what about this: if the two `%4` computations share the same variable n, and n's live range from comp1's def to comp2's use is continuous (no kill), then it crosses the calls. For that, n's value after comp1 must still be live when comp2 starts — but comp2 redefines it. The liveness of the pseudo: n is set at comp1, used at comp1's subu, dead; set at comp2. Unless the compiler considers the variable live throughout (no kill because it's used in both and not obviously dead?). Liveness analysis is precise: dead after the last use.

Hmm, unless n is used *after* comp2 in some way.

OK, let me look at the actual RTL of the pinned version to understand the `%4` structure. Dump orig.

---
ts: 2026-11-06T16:30:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mO242GZjIrZrDOUAEvpO
---
Canonical prefers fixed hard registers. arg0 is a hard reg (a0), so it stays canonical → uses become a0. In target, self was arithmetic so not equivalent.

So I need self to not be equivalent to arg0. Options in real C: a copy that cse can't prove equal. What about `self = arg0 ^ 0;`? combine/cse folds XOR with 0 into a copy at RTL combine, and cse at -O2: expand generates xor, then... cse1 sees `xor self,arg0,0`? Actually gcc's expand for `arg0 ^ 0` would emit `xor` with const 0; combine pass runs after cse1... cse1 would not equate xor with arg0. Then combine would fold it to a copy and cse2 would equate it! There are two cse passes (cse1, cse2). So folds get caught in cse2.

What survives both cse passes and combine? A memory round-trip? `self = *(s32 *)&arg0;` — taking address of param forces it to stack; bad.

An asm-free trick: use a volatile? `volatile s32 self = arg0;` — volatile local prevents optimization but loads/stores from stack → extra insns.

What about making arg0 itself not a hard-reg param? Can't.

What about `self` being a value derived from arg0 via a sign-extension that combine knows is redundant? E.g. arg0 declared `s32`, self declared `s32`; `self = (s16)arg0` gives sll/sra — extra instructions.

Hmm, but maybe there's another approach entirely: avoid the else-arm a0 issue by making the else arm clobber a0 first! In target else arm: `lw v0,32(a1)` — if instead the C in the else arm starts by assigning something to a0 (like mask), then the self use would go to a1. But the target's else arm doesn't have any a0 use. However, we can compute `mask = ~0x80;` before the if (unconditionally), so a0 holds mask throughout, and self's uses go to a1 in both arms. But then `li a0,-129` appears before the branch in the code — the target has it after bnez (in the then block). Would sched1 move it? sched1 could sink it? It's a set of a constant; sched1 typically hoists, not sinks. Hmm.

Alternatively, declare mask at top and assign in then arm, but also reference mask in else arm in a dead-but-real way? e.g. `mask = ~0x80; ... else { g = self->unkDC; ... }` — no.

Wait. Actually reconsider: what does target's `move a1,a0` come from? With zr pin: `self = arg0 + zr` → `addu self,arg0,zr` which combine folds to move. So self is a pseudo assigned to a1 (because a0 was... hmm actually why a1 not a0? Because arg0 is a0 and the copy needs a different register; local-alloc picks a1).

If we instead keep self as a *pointer* variable... let me just test a batch of candidates. Empirical is faster than theory.

Candidate ideas:
A. pointer self: `Unkstruct_8017EAD8_2 *self = (Unkstruct_8017EAD8_2 *)arg0;` and uses self->...
B. declare f before p (order swap) to fix v0/v1.
C. else: declare g before q (order swap) to fix v0/v1? Wait target else q=v0,g=v1; mine q=v1,g=v0. Swap declaration order: declare g before q → g gets lower regno → but target has g in v1 (higher). Hmm mine already has g in v0 despite g declared second. So local-alloc priority isn't regno order... Let me look at qty_compare_1.

Actually, priority = floor_log2(n_refs)*n_refs*size, ties broken by... let me read lines 1570-1630.

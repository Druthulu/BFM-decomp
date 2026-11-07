---
ts: 2026-11-06T16:45:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KgCDUafGdOEkh6OmYyMS
---
Score 2. The plain body has `move a0,zero` (const-folded a0=0) at insn 8, and lacks `sll a0,s0,0xa`. Everything else matches. So I need to prevent the constant folding of `a0 = s0 << 10` when s0=0, while producing `sll a0,s0,0xa`.

Real C options:
- Make s0's initial value opaque. E.g., `s0 = 0;` then something that makes gcc forget s0 is 0 without emitting an insn.

Hmm. What if `s0` is assigned from another variable that gcc knows is 0 but doesn't propagate across? gcc's copy propagation would.

What if `a0 = s0 << 10` uses a *different* variable that aliases? 

Wait — the launder forces s0 to be in a register AND makes it opaque. The effect on the target: `sll a0,s0,0xa` before the loop and after the call.

What if we restructure the loop so the `a0 = s0 << 10` is inside the loop at the top? Let me look at the C:

```c
s0 = 0;
a0 = s0 << 10;
do {
    ...
    a0 = 0x199;
    func_8012C658(a0, a1 >> 16, a2);
    a0 = s0 << 10;
} while (s0 < 4);
```

The target has the first `sll a0,s0,0xa` before the loop (at 1a50) and the last one in the loop's branch delay slot (1a90). So both computations are from the register s0.

Without the launder, the pre-loop one folds to `move a0,zero`.

How to make s0 opaque? Options in real C:
- `s0 = 0;` where s0 is `volatile`? A volatile local s0 would be loaded/stored to the stack each use — no.
- Use a pointer/alias: `s32 *p = &s0; *p = 0;` — gcc may still know.
- Initialize s0 from a global that's 0 at runtime but unknown: e.g., `s0 = D_something;` — but the target has `move s0,zero`, so the initial value must be the constant 0.
- Use `s0 = 0; s2 = ...;` and put the `a0 = s0 << 10` BEFORE `s0 = 0`? No, a0 must be 0.

Hmm, what if `s0` is assigned 0 and then the code uses `s0` in a way that gcc can't track — e.g., taking its address? `&s0` passed to something? That would spill.

Wait, maybe the mechanism isn't opacity. Let me look at the target again:

```
1a3c: move s0,zero
1a40: sw s2,24(sp)
1a44: lui s2, D_8018476C
1a48: addiu s2,s2,...
1a4c: sw ra,28(sp)
1a50: sll a0,s0,0xa
1a54: sll v0,s0,0x1
```

The `sll a0,s0,0xa` at 1a50. In the plain body, `move a0,zero` at insn 8. So yes, gcc const-folded.

What if `s0` is declared as a different type, e.g., `u32 s0`? `s0 = 0; a0 = s0 << 10;` still folds.

What if the shift is written as `a0 = s0 * 0x400;`? Folds too.

What if `a0` is assigned from `s0` via a *pointer* to the loop struct? no.

What if we swap the statements: `s2 = D; a0 = s0 << 10;` — still folds.

Hmm. What if `s0 = 0` is not the initializer but comes from a loop induction: e.g., use a `for (s0 = 0; s0 < 4; s0++)` loop? The target's loop is a do-while with the counter increment in the middle and the bound check at the end. A for loop might compile similarly, and the initial `a0 = s0 << 10` before the loop would still be folded (s0=0).

Unless the loop is structured so `a0 = s0 << 10` is only inside the loop and the pre-loop value is computed... The target has it before the loop because the first iteration needs it. If the C used a `while` loop with the computation at the top, gcc might still unroll the first check... Hmm, actually the target's structure is a do-while (check at the end). The `sll a0,s0,0xa` before the loop is the *loop body's first statement* duplicated? No wait:

Target:
```
1a50: sll a0,s0,0xa     <- before loop
1a54: sll v0,s0,0x1     <- loop body start
...
1a88: slti v0,s0,4
1a8c: bnez v0,1a54
1a90: sll a0,s0,0xa     <- delay slot (a0 = s0 << 10)
```
So the body starts at 1a54; the `sll a0,s0,0xa` at 1a50 is a *pre-loop* computation (the initial a0 for the first iteration). The one at 1a90 is the loop's last statement, executed in the delay slot.

So the C is: `a0 = s0 << 10;` before the loop (first iteration's value), then inside the loop at the end `a0 = s0 << 10;` for the next iteration.

Without the launder, gcc folds the first one because s0 is known 0.

How can real C prevent gcc from knowing s0==0 at that point? The launder forces the register. Real-C options:
1. Initialize s0 from a *volatile* read — extra insn.
2. Use a function call returning 0? extra insn.
3. Make s0 an alias of something opaque.

Hmm, what about the *declaration*: if s0 is declared `register`? Not allowed (no register vars). And it wouldn't make it opaque.

What if s0 is initialized via a *comma expression* or a cast that gcc doesn't fold? e.g., `s0 = (s32)(0 ^ some_global)`. No.

What if the initial `a0 = s0 << 10` is moved to AFTER the loop's first iteration? That would change the code.

Wait — maybe the launder's real effect is different: it makes s0 live in a register at that point, preventing the *scheduler* or *cse* from... Actually, the launder is an asm with "=r"(s0) input "0"(s0), which forces s0 into a register and creates a new value. It also acts as a barrier for cse/const-prop (asm volatile).

Real C: use a **volatile-free opacity**: e.g., `s0 = s0 + 0;`? folded.

Hmm, what about using the *global* `D_8018476C`: `s2 = (s32)D_8018476C;` is before. What if `s0` is computed from a global that is 0? e.g., `s0 = D_zero;` where D_zero is a global initialized to 0. Then the code would have a load, not `move s0,zero`. Not target.

What if `s0` is set to 0 and then `a0 = s0 << 10` is written in a way that gcc's const-prop misses, e.g., through a `union` or a `struct` member? Let me think: `struct { s32 n; } x; x.n = 0; a0 = x.n << 10;` — gcc folds struct member access.

What about a **bitfield**: `struct { s32 n:32; }`? Still folds.

What if the shift amount is a variable? `a0 = s0 << 10` — the 10 is constant; folding happens because s0 is constant, not the shift.

Hmm, what if `s0 = 0;` is inside a `do { } while(0)` and `a0 = s0 << 10;` outside? The do-while splits the EBB; gcc's const-prop across the EBB boundary... C0535 says do-while(0) splits cse1 EBB. Maybe it also stops const propagation! Let me try:

```c
do {
    s0 = 0;
} while (0);  // !FAKE: do-while
a0 = s0 << 10;
```
Hmm, would gcc still fold? The do-while(0) creates a NOTE_INSN_LOOP_BEG/END, which splits basic blocks. Constant propagation (cse1's cprop) might not cross the loop note boundary. Worth trying!

Also: `s2 = (s32)D_8018476C;` is between s0=0 and a0=s0<<10 in the source. So the EBB split might already... no.

Let me try several:
1. do-while(0) around `s0 = 0;`
2. do-while(0) around the whole prelude `s1=a0p; s0=0; s2=...;`
3. Assign `s0` from `a0p - a0p`? folds.
4. `s0 = a0p & 0;`? folds (a0p & 0 = 0).
5. `s0 = 0; s0 = s0;`? folded.
6. Make s0 a `u32` and `s0 = 0;` then `a0 = s0 << 10;`.
7. Use a `switch (s0) { default: ... }`? no.

Actually, another real-C trick: **make the initial a0 computation use a different expression that gcc can't fold**: e.g., `a0 = (s0 << 10) + (s1 - s1);`? folds.

Hmm, what about declaring `s0` as `s32` but assigning it inside a loop that gcc can't unroll? No.

Wait, maybe the simplest: use a **volatile read of s0**? Not allowed? `volatile` isn't a lever (no asm). But it would emit a load.

Hmm, let me think about what "real C" the original game code used. The original had no asm launder. So the original C produced `sll a0,s0,0xa` naturally. That means in the original, gcc did NOT know s0==0 at that point. How? Maybe the original source was:

```c
s0 = 0;
do {
    a0 = s0 << 10;
    v0 = s0 << 1;
    ...
} while (s0 < 4);
```
Wait! If `a0 = s0 << 10` is the FIRST statement of the loop body, then the loop is a do-while whose body starts with it. The target's layout:
```
1a50: sll a0,s0,0xa
1a54: sll v0,s0,0x1     <- loop head
...
1a8c: bnez v0,1a54
1a90: sll a0,s0,0xa     <- delay slot
```
Hmm, if the body starts at 1a50 with `a0 = s0 << 10`, then the loop back-edge would jump to 1a50, and the delay slot would contain the `sll a0,s0,0xa`... but the back-edge is `bnez v0,1a54` — jumping to 1a54, not 1a50. And the delay slot at 1a90 is `sll a0,s0,0xa`. So the `a0 = s0 << 10` is NOT at the loop head; it's the loop's last statement (in the delay slot) plus a pre-loop one.

Wait, that's the same as the C: `a0 = s0 << 10;` before the loop, and `a0 = s0 << 10;` at the end of the body. The delay slot fills with the loop's last statement.

So why did the original compiler not fold the pre-loop one? Because... hmm, unless the original C had the `a0 = s0 << 10` only ONCE, at the end of the body, and the pre-loop one is the same statement hoisted/duplicated? No.

Actually, let me reconsider: maybe the pre-loop `sll a0,s0,0xa` at 1a50 is the loop body's first statement, and the back-edge at 1a8c jumps to 1a54 (the second statement) because the first statement was moved before the loop by loop-invariant code motion? No, a0 is recomputed each iteration.

Hmm, let me reconsider: the C has `a0 = s0 << 10;` before the loop and `a0 = s0 << 10;` at the end. The target's delay slot at 1a90 is the end-of-body one. The pre-loop one at 1a50. Consistent.

So the original source likely had a launder-like construct too, OR the original had a different variable structure. Maybe the original had:

```c
s0 = 0;
a0 = s0 << 10;
do {
   ...
} while (s0 < 4);
```
and gcc 2.7.2 did NOT constant-fold the shift because... hmm, but our build DOES fold it. Unless the original's s0 was initialized differently, e.g., `s0 = 0;` where 0 is a *variable* or the initialization order differs.

Wait, maybe the original used a `for` loop:
```c
for (s0 = 0; s0 < 4; s0++) { ... }
```
with `a0 = s0 << 10` before the loop? The before-loop a0 would be folded (s0=0 known).

Hmm, maybe the original code was:
```c
s0 = 0;
a0 = s0 * 0x400;  // ...
```
folds.

Let me look at the actual decomp's history: the launder was added by the decomp team because without it the code differs by 2. So the original might have had something we can find. Let me check if there's a sibling function with the same pattern in the repo (the "twin" idea). This function is `ov_SC03_108_jr_8017BEBC` — there may be twins in other overlays with the same code (jr functions are copies). Let me search for `func_8012C658(a0, a1 >> 16, a2)` in src.

Let me grep for "a1 >> 16" and "unk70" patterns.

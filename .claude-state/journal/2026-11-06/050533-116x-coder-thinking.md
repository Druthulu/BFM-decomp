---
ts: 2026-11-06T12:05:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6zM6aaJeSxYav99iFy28
---
w1's diff: register allocation differences (s2/s3/s4) and extra `lui` instructions for `*(u16*)(base-0x34)`.

In the target, `lhu a3,-52(s2)` — base in s2, offset -52. In mine, `lui a3; lhu a3,-52(a3)` — rematerialized each time (2 insns).

So without the launder, the compiler rematerializes the base address (`lui a3,0x0; lhu a3,-52(a3)`) instead of keeping base in a register. That's the opposite of what the launder's comment says... wait, the launder comment says "address-rematerialisation launder"? No, that was item 3. Here the comment is just "L1".

Hmm, in the target, base is in s2 and used with offsets. In mine (w1), the compiler rematerializes `lui` each time (+3 insns).

So the launder (a re-set of base to the same value) makes the compiler keep base in a register? Interesting.

Real C to make base live in a register: use it more, or make the address non-constant-foldable.

Hmm. What about `base = (u8 *)&D_8011F7F0;` → `base = &D_8011F7F0;` (without the cast)? Same.

What about making base's value come from a computation the compiler can't fold: `base = (u8*)((u32)&D_8011F7F0 + 0);` folds.

Hmm. In the target, base = s2 = &D_8011F7F0 (lui+addiu). Then `arr = base - 0x48`. And `*(u16*)(base-0x34)` → `lhu a3,-52(s2)`.

In w1 (no launder), the compiler rematerializes the symbol address at each use (lui + lhu) instead of using s2. Why? Because cse knows base == &D_8011F7F0 (a constant address) and can rematerialize it. The launder breaks that.

Real C: make base an opaque value. Hmm, e.g., compute base from a runtime value: `base = (u8*)((s32)&D_8011F7F0 | 0);`? folds.

What about taking the address through a pointer variable? Same.

Hmm, what if `base` is assigned from `arr + 0x48`? i.e., compute arr first:
```
arr = (u8 *)&D_8011F7F0 - 0x48;
base = arr + 0x48;
```
Then base = arr+0x48 — cse might still fold to the constant.

What about declaring base as `volatile u8 *base`? That's a lever-ish qualifier (changes loads through base — but the loads are `*(u16*)(base-0x34)`, volatile would make them volatile loads — same code, but cse can't fold the address? Actually volatile affects the load, not the address computation). And it'd be a new lever (the volatile already exists at L2, but adding to base is new). Risky.

Hmm.

Let me look at the target more: `lhu a3,-52(s2)` appears at 4150 (in the 0x76/0x65 call) and later. And in the target there's no `lui` for D_8011F7F0 except the initial one.

So the target keeps base in s2. w1 rematerializes.

Real C idea: use `base` in a way that forces a register: e.g., `arr = base - 0x48;` then `*(u16*)(base - 0x34)`. Since base is a known constant, the compiler rematerializes. To prevent, the value must not be provably constant... 

What if base is computed as `(u8 *)((s32)&D_8011F7F0 + (param_1 & 0))`? Folds? `param_1 & 0` = 0, folds.

What if `base = (u8 *)((s32)&D_8011F7F0 + k * 0)` where k is a variable? folds (multiply by 0).

What if base = arr + 0x48 where arr is computed from a variable? arr = param_1*4 + ... hmm, arr = base - 0x48 then slot = param_1*4 + arr.

What if we write `slot = (u32 *)(param_1 * 4 + (s32)base - 0x48);` and keep base? Then base is used in a non-constant context? The compiler would fold base to the constant.

Hmm. The fundamental issue: `&D_8011F7F0` is a compile-time constant, so gcc rematerializes it. The launder makes the value opaque.

Real C that makes an address opaque without asm... a function call returning it? `base = (u8*)func_returning_addr();` — adds a call.

Hmm. What about the *volatile* pointer: `volatile u8 *base = (u8*)&D_8011F7F0;` — no.

Hmm, what about using `base` in a comparison? no.

OK, item 4 might be a WALL too. But wait — let me reconsider: w2 (barrier removed, launder kept) = 8. And w1 (launder → assignment, barrier kept) = 30. Both are load-bearing.

Let me think about the launder differently: maybe a C0414-style dead reset can replace it. The launder is a *re-set* of base (same value). What if I write:
```
base = (u8 *)&D_8011F7F0;
arr = base - 0x48;
base = (u8 *)&D_8011F7F0;   /* re-set (cse: same class) */
```
cse would fold. Hmm.

What about `base = arr + 0x48;`? That's a different expression that cse might not fold to the constant... Actually cse would know arr = base-0x48 → base = arr+0x48 = base. Folds.

Hmm, what about a dead store: `base = 0;` then `base = (u8*)&D_8011F7F0;`? The first is dead.

What about computing base via a union/char arithmetic: `base = (u8 *)((u32)&D_8011F7F0);` — folds.

Honestly, the launder here makes the address non-constant so it lives in a register. Real C cannot make a constant address opaque.

Hmm, unless: the value could be loaded from a global variable! E.g., `base = *(u8**)&D_8011F7F0;`? No, that changes semantics.

OK. So item 4: both levers load-bearing → WALL. Best lever-free: w3 = 38 (both gone) — or maybe a better variant.

Let me spend a bit more: try the C0414 dead reset for the launder and a few barrier ideas, then wall it.

Barrier idea: make the load depend on the store by using the stored value:
```
D_8011F83A = idx;
((void (*)(s32, u8 *))func_80024054)(((s32 *)D_8018DB2C)[D_8011F83A & 0x7F], local);
```
Here the index expression reads D_8011F83A (a load after the store). cse might forward the store (it knows D_8011F83A = idx) → the load becomes idx, no dependency. Let me test — maybe cse doesn't forward because the store is to a global and the load is the same global (it should forward).

Another idea: make the *store* to D_8011F83A volatile? It's already a plain store. If I write `*(volatile u8*)&D_8011F83A = idx;`, the store becomes volatile and the subsequent load (of the array) — sched's memory dependence would still... hmm, volatile stores are barriers for sched? In gcc 2.7.2, volatile memory references are not reordered across each other? Let me check sched.c: `sched_analyze_2` handles volatile MEM by... there's a `pending_lists`/`sched_before_next_call` thing.

Actually, in sched.c, volatile insns: `if (GET_CODE (insn) == INSN && GET_CODE (PATTERN (insn)) == ASM_OPERANDS)` → volatile asm is a barrier. For volatile MEM, sched_analyze_2 sets `true_dependence`. Hmm.

Let me just try a few variants:
- y1: index expression uses D_8011F83A: `((s32 *)D_8018DB2C)[D_8011F83A]`.
- y2: store via volatile: `*(volatile u8*)&D_8011F83A = idx;`
- y3: declare `idx` volatile? no.

Let me test y1, y2, and the dead-reset launder variants:
- y4: `base = (u8*)&D_8011F7F0; ... base = 0;` (dead reset) — but base is used later.

Hmm, for the launder let me try: replace `base` in the later expressions with a fresh expression each time? That's what the compiler does (rematerialize). 

Let me just try y1/y2/y3 quickly.

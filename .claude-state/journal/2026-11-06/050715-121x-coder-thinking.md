---
ts: 2026-11-06T12:07:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OAKilCiiSjVJ9KoyvV9C
---
All 30 (same as w1). The launder is hard to replace.

Let me check the time: 05:06. Item 4 started 05:02 — only 4 min?! The clock is definitely not tracking my real elapsed time (I've made ~15 tool calls with compiles). Maybe the sandbox clock is coarse or the VM clock is slow. Whatever.

Let me think about the launder mechanism more concretely. Without the launder:
- The compiler rematerializes `lui a3,0x0; lhu a3,-52(a3)` at each use of base.
- With the launder: base is in s2 and uses `lhu a3,-52(s2)`.

Wait, that's odd: the launder makes the value opaque → the compiler keeps it in a register. So the launder's role is to prevent rematerialization.

Real C: make base opaque. Options:
- `base = (u8 *)((u32)&D_8011F7F0 + (param_1 - param_1));` → folds to +0? `param_1 - param_1` = 0, folds.
- Use a volatile read: `base = *(u8 *volatile *)&some_global;` changes semantics.

Hmm, what about computing base from `slot` or `arr` in a way that's not foldable:
```
arr = (u8 *)&D_8011F7F0 - 0x48;
slot = (u32 *)(param_1 * 4 + (s32)arr);
base = (u8 *)((s32)slot - param_1 * 4 + 0x48);
```
This is real C where base is derived from slot (which depends on param_1) — cse might still fold. Hmm, but it's a longer chain.

Let me try that. Actually, the compiler's cse would compute `(s32)slot - param_1*4 + 0x48` = arr+0x48 = base. Folds.

What if base is only used via arr? Then no base variable — the compiler would rematerialize arr+offsets... same.

Hmm. What if I make base live across a call? E.g., compute base before a function call and use it after. It's already live across calls (func_80176D94 etc.) — and the compiler still rematerializes.

Actually, wait: in w1, the compiler rematerializes at the *later* uses (after the calls). Global alloc decided not to keep base in a register (it's cheaper to rematerialize a constant). With the launder, the value is opaque so it must be kept.

Real C can't make a constant opaque without asm or volatile.

Hmm, unless... we make base a *parameter*! Like `void f(s16 param_1, u8 *base)` — no, that changes the signature (prohibited).

What about deriving base from a memory load that the compiler can't constant-fold, e.g., `base = *(u8**)&D_8018DB2C[0];`? That changes the value.

OK. Item 4 looks like a WALL for the launder, and the barrier also resists (8 or 5 with +1 insn).

Actually, wait. Let me reconsider: maybe I can accept the +1 insn for the barrier if the rest matches, and combine with... no, score must be 0.

Let me try one more barrier idea: a *volatile* pointer store where the address is a symbol → maybe `*(volatile u8 *)&D_8011F83A = idx;` gave +1 (v0 materialization). What about storing through `D_8011F83A` declared volatile in the extern? Can't (decl change).

What if I use `*(u8 *)((u32)&D_8011F83A | 0)` — folds.

Hmm, what about making the *array load* depend on the store by using the same base register? 

Let me look at the sched1 mechanism: why does sched1 hoist the address computation? Because there's no memory dependency. If the load were correctly ordered after the store, sched1 would keep it (it doesn't reorder memory ops with dependencies).

The alias question: store to `(mem:QI (symbol_ref D_8011F83A))`, load from `(mem:SI (plus (symbol_ref D_8018DB2C) (reg)))`. In gcc 2.7.2 sched.c, `sched_analyze_2` for a MEM:
```
      /* Reading memory.  */
      ...
      for (u = pending_writes; u; u = XEXP (u, 1)) ...
```
It uses `true_dependence` from... let me check sched.c's includes. In 2.7.2, dependence is computed in sched.c itself via `add_dependence` and `sched_analyze_2`.

Given the compiler decided they don't alias, maybe because the store is to a SYMBOL_REF and the load is to a different SYMBOL_REF + register. gcc 2.7.2's `true_dependence` (in alias.c? not present in the reference set) — the reference set has no alias.c, so it's probably in sched.c or rtlanal.

Hmm.

Let me try one more idea: make the store address non-symbol: `*(u8 *)((s32)&D_8011F83A) = idx;` — same.

Or make the *load* use a pointer that could alias: the array D_8018DB2C is `u8 *D_8018DB2C[]` — an array of pointers. `((s32*)D_8018DB2C)[idx]` loads a pointer from the array. The store is to a u8 global. 

What if I read the array element through a `u32 *` variable that was derived earlier... no.

OK, let me wrap up item 4 as a WALL. Best lever-free: let me check a few more lever-free variants to get the best score. Currently w3 = 38.

Actually, let me try combining the volatile store (y2, barrier+1 insn but ordered right) with the launder's best (30) → both → maybe better than 38.

And also try the volatile load (y5) with the base assignment.

Let me generate 4 combos and score:
- c1: y2 (volatile store) + base assignment (launder gone).
- c2: y5 (volatile load) + base assignment.
- c3: w3 + reordered.
- c4: y1 + base assignment.

Let me do it.

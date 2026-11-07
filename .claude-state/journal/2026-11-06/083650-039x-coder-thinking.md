---
ts: 2026-11-06T15:36:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6lW1y2RQnZ3azN7BMRIW
---
Still 6. So the dead reset doesn't break it here because the expression is a symbolic constant.

Let me think differently. What actually makes gcc emit `addiu a0,s0,24` twice? In the target, the base s0 is a register holding &D_800AF630. The two adds are separate because... the launder made mb unknown.

Is there a plain-C way to make mb unknown? Yes: make mb's value depend on a call result or on a memory load that gcc can't fold, but arrange it to be the same address.

Wait — what about the function's existing variables? The function loads `D_800A651C`, `D_800B9A02`, etc. Hmm.

Actually! Maybe use the `dead` array or another local: The address of a local is (plus sp K), a runtime value. If we set mb = (u8*)((char*)&some_local + delta)? That's a different address.

No.

Hmm, is the launder here perhaps replaceable by an equivalent *real C* that changes the value between the calls? Let me look at the exact original intent: the two calls are func_8004914C(mb+0x18) and func_800491AC(mb+0x18) where mb = &D_800AF630. The target materializes base once and adds 24 twice. 

What if the C uses a different base variable per call, and the first one is also used later? For example:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
func_800491AC(mb + 0x18);
```
cse merges the two `(plus sym 24)` and keeps s0=sum.

What if the *second* call's argument is `mb + 0x18` where mb is re-derived from a *different symbol expression that aliases*: e.g. declare `extern u8 D_800AF630_alias[] __asm__("D_800AF630");` and use the alias for the second call. Then cse sees two different symbol_refs? No — same SYMBOL_REF after asm label? The asm-label alias produces the same symbol; cse's expression is the same symbol ref. Hmm, but the declaration might be a different decl → different rtx? SYMBOL_REF is shared by name. So same.

What if we use the address via `(u8 *)&D_800AF630` for the first and `(u8 *)(D_800AF630)` for the second — tested (h) no.

Let me reconsider whether we even need the base in s0. What if we get the target shape by having the *sum* not be a constant because it's computed with a runtime value that's provably the base: 

Actually, hold on. Let me look at the whole target function around those calls more carefully. Maybe the base s0 comes from something earlier (like the gte/vertex loops use s0 for another purpose?). The disassembly showed `lui s0; addiu s0` right before jal. So s0 = &D_800AF630.

Since the launder is a "minimum lever" (P36 S105 f11), maybe the intended crack is different: maybe restructure so the base is a real variable whose value is set from a *non-constant* expression. For instance, use `mb` as a pointer derived from `param_1`? No.

Alternatively, the base could come from an earlier existing pointer variable in the function! Look: `src = &D_801C8374[...]`, `param_1`... no relation to D_800AF630.

Hmm. What about using the `mb` variable across the three sites, i.e., set mb once at the top to &D_800AF630, and the three sites use it? Then cse still folds.

Let me look at what cse does with the constant: in cse1, `(symbol_ref D_800AF630)` + const 24. cse has "constant" handling where it can put a constant into a register equivalence. Then it shares.

Is there a way to make the base live as a register but the sum computed? Yes: if the base register is *used elsewhere* such that the base itself is in a register, then `mb+24` must be computed per use. In target, s0 holds the base and both adds are per call. Why would gcc keep the base rather than the sum? Because with the launder, mb is unknown after the asm; gcc keeps the *unknown register* (which physically holds the base) and adds 24 each time. The base is in s0.

So: if in plain C we can make mb a non-constant runtime value, we win. Plain C ways to get &D_800AF630 into a non-constant runtime value:
1. `mb = (u8 *)&D_800AF630;` — constant.
2. Load from a global pointer — extra load (wrong).
3. Pass through a function call — extra call (wrong).
4. Cast through a variable that cse can't fold.

Wait — maybe use `volatile` on a *copy*: `u8 * volatile m = (u8*)&D_800AF630;`? A volatile object's value is unknown to cse? Actually cse does not track volatile loads/stores but a local volatile assignment: `m = ...` then reading m requires a load from the stack, and cse won't fold it. But the read is a memory load — that adds a load instruction (lw from stack), and target doesn't have it. Unless gcc keeps m in a register anyway (volatile local is not kept in a register). So no.

Hmm, what about making the addition non-constant-foldable by using the *other* symbol D_800AF648? No, that changes the address.

Let me reconsider the problem. Maybe the target's `addiu a0,s0,24` is not from `mb+0x18` at all! Maybe the source should use a *struct pointer*: `func_8004914C((void*)((s32*)mb + ...))`. No.

Wait, maybe the right C is to have two separate variables that both hold the base and pass each to a call, with the addition done in the call argument. Hmm, tested.

Let me look at other functions in this file that call func_8004914C/AC with a similar pattern — maybe the intended idiom exists elsewhere without a launder. Search the src file for func_8004914C.

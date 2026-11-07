---
ts: 2026-11-06T15:38:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BcAeeDwey9OCC0iALPQQ
---
No prior attempts. Let me think about the actual original source. Maybe the original used a global *struct* variable and a pointer arithmetic with a *variable* offset. Let's look at the data at D_800AF630. Maybe it's a matrix buffer and the code is `func_8004914C((u8*)&D_800AF630 + 0x18)`.

What if the original code was:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
func_800491AC(mb + 0x18);
```
but `mb` was declared `register`? No — `register` is disallowed for me and would be a pin-ish lever (actually register keyword is a hint; not a lever kind, but the constraints say no `register` vars).

Hmm what if the variable is `volatile`? Would produce a load.

Let me reconsider: maybe there's a plain-C way to make cse treat the address as non-constant: use a cast from an integer type that's not a constant? E.g. `mb = (u8 *)((u32)&D_800AF630);` — the tree is a constant.

What about `mb = (u8 *)((u32)&D_800AF630 + (u32)param_4 * 0);`? Identity launder, disallowed.

What about using `param_4`'s low bits in a way that's provably 0 but real? Not allowed as identity.

Hmm, wait. Is there a legitimate C restructuring: the function already has `src` = &D_801C8374[(param_2 & 1) * 3]. What if we use a similar derived pointer for the matrix base? E.g.:

```
u8 *mb = (u8 *)&D_800AF630;
```
No.

Alternatively — maybe the target's addiu comes from a different source construct: `func_8004914C(&D_800AF630[0x18])` where D_800AF630 is declared `u8 D_800AF630[]`? Same.

Let me try a few more exotic spellings quickly (each cheap):
1. `func_8004914C((void *)((u8 *)&D_800AF630 + 0x18));` (cast to void* in arg)
2. `func_8004914C((void *)(&D_800AF630[0x18]));`
3. declare mb as `void *mb; mb = &D_800AF630; func_8004914C((u8*)mb + 0x18);`
4. `func_8004914C(&D_800AF630[0x18]);` where D_800AF630 is u8[] → same.
5. Use `(u8 *)D_800AF630 + 0x18` (no &) tested h.
6. Make mb a `s32` and cast at call: `s32 mb = (s32)&D_800AF630; func_8004914C((u8*)mb + 0x18);` — cse folds.
7. Use two different struct types: `((S18*)&D_800AF630)->x` etc.

None likely.

What about making the offset come from a *u16 variable* that's constant-propagated? E.g. `u16 off = 0x18; mb+off` — cse folds constant propagation? GCC 2.7.2's cse doesn't do constant propagation of variables; `off` would be a variable in a register (or constant?). If `off` is a local initialized to 0x18 and never modified, gcc's combine/cse may fold. Let's test:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + off);   /* off = 0x18 local */
func_800491AC(mb + off);
```
If off is a variable, `mb + off` is (plus (symbol) (reg off))? Actually mb's value is the constant symbol, off is a constant 0x18; combine might fold. But the tree has two variables; cse's fold_rtx could fold both. Hmm. But if off is stored to memory (address taken?), it'd be a load.

What if `off` is declared `const`? Folded.

Try it — cheap.

Also try `mb + (s32)0x18` no.

Another idea: use a pointer to a *union/array* indexed by a variable that's 0 at runtime — identity, disallowed.

Hmm, but wait: what about splitting the addition into the call argument using a *function pointer cast with a struct*: no.

Let me test the `off` variable idea and a couple of struct-field ideas.

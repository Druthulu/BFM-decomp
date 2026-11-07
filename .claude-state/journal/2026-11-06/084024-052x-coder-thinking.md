---
ts: 2026-11-06T15:40:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oroj7H3l9rk1cbSG6Re7
---
Twin has the same launder. So this is a known hard lever.

Given cse's CONSTANT_ADDRESS_P early return and reg_equiv_constant substitution, plain C likely cannot keep a constant symbol address in a register while adding per use. This is the cse-const-addr wall. But let me check the walls.txt definition and whether the shard's wall list includes an appropriate tag. cse-const-addr is defined at line 2.

Before declaring a wall I must have ≥20 min and ≥30 scored tries on this item. Started item 2 at roughly... let me check date. I started around 08:28; item 1 took some minutes. Let me record times. I need at least 30 tries. So far: c1 (1), va-vf (6), vg-vj (4), vk-vl-vm (3), vn-vo-vp-vq (4), vr-vs (2) = 20 scored candidates, plus orig baseline. Let me do ~10 more tries with other spellings, then decide.

More ideas:
- t: struct pointer with field: declare `struct M18 { u8 pad[0x18]; u8 x; };` and use `&((struct M18*)&D_800AF630)->x`. Probably 6.
- u: use `(u8 *)((u32)&D_800AF630 + 24)`.
- v: two different variable names with one set each, used at different sites.
- w: use `mb` set once and a second variable `mb2` set from `mb` (copy) — cse merges.
- x: use `mb` as a `void *` and `(u8 *)mb + 0x18`.
- y: make mb `u8 *` and use `mb + sizeof(struct {char c[0x18];})`? folds.
- z: place the add in a separate statement: `mb2 = mb + 0x18; func(...mb2);` no.
- aa: use a compound literal? C89 no.

Alternative idea: make the two call arguments go through *different* typed pointers so cse's expression differs? fold same.

What about making the address non-constant by using the `param_4` value in a legitimate way? E.g. the address is `&D_800AF630 + 0x18` and param_4 is unused? Let me check: param_4 is used at line 6065 `*(B4_8018AD9C *)&pkt[8] = *(B4_8018AD9C *)&param_4;`. So param_4 is used. No spare.

What about making the base pointer a *parameter-derived* pointer: e.g., `mb = (u8 *)&D_800AF630` — no.

Hmm, here's a thought: use a *pointer to pointer* initialized from the symbol via a cast of a *local array*? no.

Another: the CSE fold to constant requires mb to be in reg_equiv_constant. If mb is assigned inside a *conditional* (if) then cse treats it as non-constant? E.g.:
```
if (param_1) { mb = (u8*)&D_800AF630; } else { mb = (u8*)&D_800AF630; }
```
Both arms same → jump1 may merge and cse may still see constant. Extra branch = wrong.

What if mb is set from an expression like `(u8 *)&D_800AF630` where the symbol is accessed through a *volatile* pointer cast? `*(volatile u8 **)&...` adds a load.

I think it's a wall. But let me try a few more legitimate moves to be thorough, including the "named derived pointer" idea from C0505: a named derived pointer `q = p - k` that cse keeps as a REGISTER address. The mechanism: `q = p - k` where p is a *register* (e.g. param), cse keeps q as register address. Our base p would be constant, so q = constant - k = constant. Not applicable.

What if we build the base from a *non-constant* pointer that happens to equal &D_800AF630? E.g. `mb = (u8 *)&D_800AF630;` no.

OK here's one more real idea: the function has `param_1`, and `((s32*)param_1)[8]` points to some structure. The matrix at D_800AF630 is a *global* fixed matrix. But what if the original code used a *different* global pointer variable that holds &D_800AF630, like `D_800AF630` being an array and `mb` loaded from a pointer table? The target has no load, so no.

Let me also consider: maybe the target's `lui s0,%hi(D_800AF630); addiu s0,%lo(D_800AF630)` is from a *relocation* of the base, and the two `addiu a0,s0,24` are because the source passed `mb + 0x18` where mb is a *function parameter*? Not in this signature.

I'll do 10 more variants and then wall it.

Actually, wait. One more important idea: the launder makes mb "unknown" — what if instead we make the *base* pointer be loaded from an existing global that contains the address... no.

Hmm, what about making mb an `s32` and using `(u8 *)mb` at the calls where mb was set from `(s32)&D_800AF630` — cse folds.

Let me try a `union` variant: 
```
union { u8 *p; u32 i; } u;
u.i = (u32)&D_800AF630;
func_8004914C(u.p + 0x18);
```
GCC may put union in memory (load) → extra insns.

Let me test a batch of ~10: struct field, void*, u32 cast, two-var, conditional-free alternatives, and a "pointer to array" spelling.

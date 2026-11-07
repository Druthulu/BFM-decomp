---
ts: 2026-11-06T05:23:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_W9hL98pzEO68vPCFkKCE
---
Found it! Line 1726:

```c
if (GET_CODE (r) == MEM && last_mem_set && ! MEM_VOLATILE_P (r)
    && rtx_equal_p (r, last_mem_set))
  return 1;
```

`last_mem_set` is the last memory set in the *reverse* scan (i.e., the next store in program order). If the current store's destination is `rtx_equal_p` to the next store's destination, it's dead → deleted by flow.

`rtx_equal_p` compares the MEM expression. Note: it does NOT check MEM_IN_STRUCT_P? `rtx_equal_p` for MEMs compares the address and the mode, not the flags. Hmm, maybe it does compare MEM_IN_STRUCT_P? In gcc 2.7.2's rtx_equal_p:

```
case MEM:
  if (MEM_VOLATILE_P (x) != MEM_VOLATILE_P (y)) return 0;
  break;
```
Only VOLATILE! So MEM_IN_STRUCT_P doesn't matter. That's why z3/z4 failed.

So the dead store is deleted by flow.c's `last_mem_set` logic: a store to the same MEM expression as the next store is dead.

To prevent it: make the two store destinations NOT rtx_equal. Options:
- Different MEM expressions that are not rtx_equal but resolve to the same address. E.g., `(plus (reg sp) (const 24))` vs `(plus (reg sp) (const_int 24))` — same.
- Use a different addressing expression that the compiler doesn't fold to the same rtx: e.g., one store via `b[0]` (sp+24) and the other via `*(s16 *)((u8 *)b + 0)` — folds.
- Make the address expression differ structurally but compute the same: e.g., `b[0]` vs `*(s16 *)((char *)b + 0)` — folds to the same.
- Use a *pointer variable* for one store: `s16 *p = b; p[0] = t;` — the MEM is `(mem:HI (reg p))` vs `(mem:HI (plus (reg sp) 24))`. NOT rtx_equal! So flow keeps both stores. And after register allocation, p might be folded... but the MEM expressions differ at flow time.

But would the generated code still be `sh v1,24(sp)`? If p is a pseudo that gets allocated to a register, the store would be `sh v1,0(p)` — different from the target unless p is assigned to sp+24... Actually gcc's `memory_address`/reload might fold `p = b` into `sp+24` and emit `sh v1,24(sp)`. Since b is a local array at a fixed frame offset, gcc could rematerialize the address.

Hmm, but at the flow pass, `p` is a pseudo register. The store is `(mem:HI (reg p))`. The next store `b[0] = u88` is `(mem:HI (plus (reg 30) (const 24)))`. Not equal → both kept. Later, global-alloc/reload may or may not fold p to sp+24.

The target's stores are all `sh X,24(sp)`. If p becomes sp+24 via reload, we'd get the same instruction. Let's test.

Also, `last_mem_set`: it's set when a store is seen in the reverse scan. For the *second* store (b[0]=u88, the next in program order), the first store (b[0]=t) is compared. If they differ in form, both kept.

So the trick: make consecutive stores to the same location use *different address expressions* that both fold to the same final instruction.

How to make different address expressions without casts? 
- `b[0]` vs `*(b + 0)` — same after folding.
- `b[0]` vs `*p` where p is a pointer variable — different at flow.
- `b[0]` vs `*(s16 *)((u8 *)b)` — cast, but folds to the same address expression → rtx_equal → deleted.

So a pointer variable is the way. Let me test:

```
s16 *p = b;      // or p = b + 0
...
b[0] = t;        // store 1
...
p[0] = t;        // store 2 (different MEM: (reg p))
b[0] = u88;      // store 3
...
b[2] = t2;
p[2] = t2;
b[2] = u8C;
```

Hmm, but will `p[0]` generate `sh X,24(sp)` or `sh X,0(p)`? If p is allocated to a register, the latter (an extra register). The target has no extra register. But maybe gcc's `cse`/`reload` folds it.

Let me test with p as a pointer and see the score.

Alternatively, use `b[i]` with a variable i that's constant-propagated to 0? Then the address is `(plus (reg) (reg i))` → after propagation, the same.

Let me try the pointer variable.

Also, an alternative: use `*(s16 *)((u8 *)b + 0)` vs `b[0]` — folds.

Let me test a few:
v1: p pointer for the second b[0] and second b[2] stores.
v2: p pointer for ALL b stores.
v3: p pointer for the first stores.

Let me write them.

Wait — careful: `last_mem_set` is the *next* store in the reverse scan. The sequence is:
store1 (b[0]=t), store2 (b[0]=t), store3 (b[0]=u88), store4 (b[2]=t2), store5 (b[2]=t2), store6 (b[2]=u8C).
Reverse scan: store6 sets last_mem_set. store5: MEM equal to store6? Both b[2] → yes → store5 deleted. Then store4: compared to last_mem_set (still store6? or store5?) — after deleting store5, last_mem_set remains store6's MEM; store4's MEM is the same → deleted. Then store3: same as store6? b[0] vs b[2] → different → kept, last_mem_set = store3. store2: same as store3 → deleted. store1: same → deleted.

So the deleted ones are store5, store4, store2, store1 (4 stores), keeping store3 and store6 (2 stores). That matches mine (2 stores).

To keep them, each consecutive pair in the reverse scan must have different MEM expressions. So alternate the address expression for each store: store1: A, store2: B, store3: A, store4: B, store5: A, store6: B. Where A and B are non-equal but produce the same instruction.

If A = `b[k]` and B = `*p` (p = b), then:
reverse: store6 (B) sets last=B; store5 (A) ≠ B → kept, last=A; store4 (B) ≠ A → kept, last=B; store3 (A) ≠ B → kept, last=A; store2 (B) ≠ A → kept, last=B; store1 (A) ≠ B → kept. 

All 6 kept! And the instructions: store A = `sh X,24(sp)`, store B = `sh X,0(p)` — unless p folds to sp+24.

Hmm, p is a pseudo holding b's address. At flow time it's a register. Later, local/global alloc assigns p to... a register, not sp+24. The target uses sp+24 directly. So B stores would be `sh X,0(p)` with p in some register → extra insns (lui/addiu) and a different shape.

Unless gcc's `cse` replaces p with the address expression (b is a local array; `p = b` makes p equivalent to `&b[0]`, and cse might substitute `(reg p)` with the address). cse's equivalence propagation could turn `(mem (reg p))` into `(mem (plus (sp) 24))` — then rtx_equal would apply at the *next* pass (flow runs before cse? pass order: flow is run several times).

Hmm, the pass order in 2.7.2: `rest_of_compilation`: ... `flow_analysis` (before loop), `cse`, `flow_analysis` again, `combine`, `sched`, `local_alloc`, `global_alloc`, ... The dead-store deletion in flow happens in `life_analysis`? The function containing `insn_dead_p` with `last_mem_set` is `propagate_block`/`mark_used_regs` — run during `flow_analysis` (life_analysis). Multiple times.

If cse substitutes p's value, later flow passes would delete the stores. Let me just test empirically.

Let me also consider: maybe use `b[0]` and `*(b + 0)` — the front-end folds both to the same tree. `*(s16 *)((char *)b + 0)` also folds.

What about `*(s16 *)((char *)b + (0))`? folds.

What about using a *different type* with the same width: `*(u16 *)b = t;` vs `b[0] = t;` — the front-end creates the same MEM. No.

What about `b[0]` vs `((s16 *)b)[0]`? folds.

So the pointer variable is the only structural difference.

Let me test it.

---
ts: 2026-11-06T11:48:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wZWJHCfgKNQcKVRLly0K
---
The spelling: `struct S9 { u16 v; };` declared at BLOCK scope, then `struct S9 *sq = (struct S9 *)&D_800B9A02;` and `sq->v`. So a NAMED local struct type, not anonymous in a cast. And they cast a global address.

In my case, I used an anonymous struct in a cast: `((struct { u8 p[0xD0]; s16 v; } *)a1)->v`. Maybe gcc 2.7.2 doesn't set MEM_IN_STRUCT_P for anonymous struct casts, or the anonymous type isn't handled. Let me try a named local struct:
```
struct S9D0 { u8 p[0xD0]; s16 v; };
...
struct S9D0 *sq;
sq = (struct S9D0 *)a1;
d0 = sq->v;
```
Let me test this spelling.

But wait — the reload issue is a load-load (no store between). The struct trick in func_80175820 works because a store (ptr[2]) is between and the in_struct load is invalidated. In my case, there's no store between the top load and d0 reload. So even with in_struct hashing, the top load is scalar (not in_struct) and the reload is in_struct → different hash → NOT equated → reload survives! That's the theory. The hash difference alone should suffice, even without a store.

But my anonymous-struct test didn't work. Let me try the named-struct spelling.

Let me create v_named_sr:
- add at top of function body: `struct S9D0 { u8 p[0xD0]; s16 v; };` (declaration)
- `struct S9D0 *sq;`
- after a1 = a0v: `sq = (struct S9D0 *)a1;`
- `d0 = sq->v;`

Hmm, but adding `sq` might change register allocation (sq = a1 copy). Let me instead cast inline: `d0 = ((struct S9D0 *)a1)->v;` with the named type declared.

Let me test both.

Actually, in gcc 2.7.2, a local struct declaration `struct S9D0 { ... };` at block scope — is that allowed? C89 allows struct declarations at block scope (they declare a type). func_80175820's win does it, so yes.

Let me test v_named_sr and v_named_sr2 (with sq var).

Also, maybe the issue is that the top load is ALSO in_struct because a1 is cast to a struct pointer somewhere? No, the top is scalar.

Let me generate and score.

Let me also try declaring the struct at file scope? Can't (body only). Block scope is fine.

Let me write gen5.py.

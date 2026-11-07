---
ts: 2026-11-06T05:14:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NBqcr9aWKqjFwW3aRIYC
---
Line 21 is very relevant: "barrier | func_8017E180 | MATCH — arr reads as member arr[k].v[0] (de-cast): cse re-loads arr[0] after param_1 store (W03)".

So a prior MATCH used a *de-cast* (changing a cast to a member access) to make cse reload after a store. That's exactly our situation, and it was accepted! The move was to change `((S *)p)->arr[k]` to `arr[k].v[0]` (a real struct member access) so that cse re-loads.

And line 33: "vo stores via plain casts (no /s, load can't pass)" — a MATCH with plain casts.

So casts ARE an accepted real-C move in this project when they change the memory access semantics/type. The prohibition is specifically about *identity* statements (`w = (w>>16<<16)|x`) and "identity address spellings".

Hmm, but is `*(s16 *)&D_80078EA6` an identity address spelling? The line-21 precedent used a real member access (`arr[k].v[0]`) — a *de-cast*, i.e., a more natural spelling.

Our cast is a type-pun on a global. I'd argue it's a "width/sign" change of the load: the object is declared u16, we read it as s16. That's a legitimate C type change (the comparison is signed anyway).

Hmm. Let me look at whether there's a *more natural* spelling that achieves the same: e.g., declare a local `s16` alias? The header declares `extern u16 D_80078EA6;`. What if I add inside the function a declaration like `extern s16 D_80078EA6;`? That conflicts with the existing u16 declaration → error.

What about accessing it via the base pointer? No.

Hmm, what about `(s16)D_80078EA6` vs `*(s16 *)&D_80078EA6`: the latter is a load of type s16. A "natural" way to express that would be to declare the global as s16 — but we can't change the declaration (outside the body).

Actually, wait: the header's declaration `extern u16 D_80078EA6;` is *outside* the function body, in the same header. The brief says "no signature or decl change outside the body (callers stay as they are)". So I can't change the extern declaration.

Hmm.

OK, let me consider: is there any other way? Let me think about the *store* alias: per §425, `sb` aliases scalar globals. What if the store to EA4 were an `sb`? The target's store is `sw`. No.

What if the LOAD were an `lbu`/`lh`? The target is `lh`. Hmm.

What about making the *first* load use a different alias class so cse doesn't record it, then the second load is a fresh one? The first load must also be `lh`. If the first load is `*(s16 *)&D_80078EA6` (cast) and the second is `(s16)D_80078EA6` (direct), the alias sets differ → no reuse. That's the same trick, just on the first load. Is that less of an "identity spelling"? No.

I think the cast is the intended kind of move here (precedent line 21/33), and the "identity address spellings" prohibition targets things like `&x` vs `(char*)&x + 0` used *without* any type change.

Hmm, but our cast IS `&x` with a type change. Ugh.

Let me take a different approach to resolve this: can I make the reload happen with a *real struct* access, like the line-21 precedent? For example, treat D_80078EA6 as a member of a struct at that address:

```
struct { u16 pad; u16 v; } *s = (void *)&D_80078EA4;   // s->v is at EA4+2 = EA6
if (s->v >= 0x81)
```
But the reloc would be D_80078EA4+2, not D_80078EA6. Mismatch.

What if the struct is based at EA6 itself: `((struct S *)&D_80078EA6)->v` — reloc D_80078EA6, and the access is MEM_IN_STRUCT_P → per §425.2, "whole-struct copy into a 2-byte register local". Hmm, that's a different expansion.

The generated code must be `lui v0; lh v0,0(v0)` with reloc D_80078EA6. A struct-member access might produce the same.

Let me test: replace the inner load with `((struct { u16 v; } *)&D_80078EA6)->v`. If it scores 0 (or close), that's a more "real" spelling (struct member access, as in the W03 precedent). Actually the line-21 precedent says a member access made cse re-load. Let me test it.

Also test a union.

Let me run these.

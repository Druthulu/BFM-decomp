---
ts: 2026-11-06T17:01:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tohiWVtLmKzM5ZlRUh1g
---
y01 has `addiu a1,sp,32` (delay slot) and `addiu a0,sp,32` — the target! No s1 cache.

So in y01 (hand-expanded copy + s-launder + q dead-reset), cse doesn't cache &m. In z01 (struct assignment), it does.

The difference must be the s-launder (asm) or the hand-expanded copy. Let me test: z01's struct assignment but with a dead-reset for the copy's destination... 

Actually, let me test the reverse: keep the hand-expanded copy, remove the s-launder, add a real-C equivalent. The s-launder keeps `s` in a register. Without it, the loads remat D_800AE620 (x1 = 19). 

What if the hand-expanded copy uses a *local array copy* differently... Hmm.

Let me test: struct assignment + the s-launder-style real-C? No.

What about: hand-expanded copy where `s` is used to read the struct but we force the base into a register by using `s` in a way cse can't remat: e.g., `s = (Blk20 *)&D_800AE620;` and then `t0 = s->w[0]` — cse remats.

What if `s` is a `u32 *` and we do `t0 = s[0]; t1 = s[1]; ...`? Same remat.

What if the base is loaded from a global variable: `Blk20 *s = *(Blk20 **)&D_800AE620_ptr;`? That adds a load.

Hmm.

OK, alternative: accept the struct assignment but prevent the &m cache. The cache is a cse decision across the RotMatrixY call. What if we make the func_800484EC call's &m expression NOT identical to the RotMatrixY arg by using a pointer variable assigned from &m AFTER the call:
```
RotMatrixY(ang & 0xFFF, &m);
q = &m;
func_800484EC((s32)q, ...);
q = 0;
```
cse would equate q with &m; but the RotMatrixY arg is a different expression? Both are &m. Hmm.

What if the RotMatrixY arg is a *variable* q1 = &m (dead-reset after the call), and the func_800484EC arg is &m directly? The cse equivalence between q1 and &m is killed by the reset. Then the &m at the call is rematerialized. That's exactly y01's structure. Let me try it on z01 explicitly with the reset right after RotMatrixY:
```
q = &m;
RotMatrixY(ang & 0xFFF, q);
q = 0;
...
func_800484EC((s32)&m, ...);
```
That IS z01 (the q block). And it gives 3. So in z01, cse still caches &m from... the struct copy? 

Wait, maybe the cse equivalence is established by the *struct copy*: the copy's destination address is sp+32, and cse records that the value sp+32 is... no, cse records registers, not raw addresses.

Hmm, but the struct copy is `m = D_800AE620;` — the destination `m` is an aggregate; expand emits the stores with sp-relative addresses. cse's table might record `(plus sp 32)` as an address expression with a known value.

Then `q = &m` → cse computes `(plus sp 32)` and finds it in the table? It might reuse a register holding it. Then q=0 kills q. Then func_800484EC(&m) → cse recomputes.

But mine's asm has the addiu at e74 (before RotMatrixY), meaning cse materialized &m once and kept it. 

Let me try: in z01, make the q block's reset *before* the RotMatrixY call... no.

Let me try a totally different tack: put the struct copy AFTER the RotMatrixY? No, RotMatrixY needs m.

What if the struct copy is done via `memcpy`? changes bytes.

Let me try: struct assignment + a dead-reset of a pointer to m BEFORE the RotMatrixY call (to invalidate the cse entry):
```
q = &m;
q = 0;
m = D_800AE620;   // no...
```

Hmm, what about declaring `m` as `volatile`? No.

Let me look at the actual cse behavior: maybe the &m cache is due to the *vec* array: `vec[0]=0x4000; vec[2]=0; vec[1]=0;` and `func_800484EC(&m, vec, vec)`. The target has `addiu a1,sp,16; move a2,a1` — vec in a1/a2. Mine same.

I'm at ~10:05. Item 4 started ~09:56. That's only 9 minutes. I need 20 for a WALL (until 10:16). But maybe I can crack it.

Let me try the "hand-expanded copy without the s-launder but with a struct read through a pointer assigned from a non-constant". Actually — here's an idea: use the *struct assignment* but to a pointer variable that we dead-reset, AND make the RotMatrixY/func_800484EC use a *different* pointer variable each, dead-reset:
```
Blk20 *q = &m;
*q = D_800AE620;    // struct copy via pointer
q = 0;
```
ab01 did this → 3.

Hmm, what if the dead-reset of q happens *between* the copy and RotMatrixY, and the RotMatrixY uses &m directly (not q)? Then cse's &m entry from the copy is killed by q=0? Let me test:
```
Blk20 *q = &m;
*q = D_800AE620;
q = 0;
RotMatrixY(ang & 0xFFF, &m);
func_800484EC((s32)&m, ...);
```
ab01 has `*mp = ...; mp = 0;` then the q block. Let me try without the q block (direct &m) and with the reset after the copy.

Actually ab01 = struct copy via mp + mp=0 + q block. Let me try: struct copy via mp + mp=0 + direct &m for RotMatrixY + direct &m for func_800484EC. That's a new variant.

Let me also try: dead-reset of q AFTER the RotMatrixY call but where q was used for the copy:
```
Blk20 *q = &m;
*q = D_800AE620;
RotMatrixY(ang & 0xFFF, q);
q = 0;
func_800484EC((s32)&m, ...);
```
This is like y01 but with a struct copy through q. Let me test.

Time is limited. Let me run a batch of these.

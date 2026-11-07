---
ts: 2026-11-06T16:57:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jBHE1jvunowaG94sIwOF
---
z01 is close: the only residual is the `addiu s1,sp,32` (cse keeping &m in a register) — wait, but y01 (with the q dead-reset) scored 0. z01 also has the q dead-reset (derived from y01). Hmm, but z01 removed the s-launder block and replaced it with `m = D_800AE620;`. That changed the code around &m: now cse keeps &m in s1.

In y01, the s-launder kept the base in a register for the copy block, and the q dead-reset killed the remat for &m. Now with the struct assignment, &m is materialized... hmm, the `addiu s1,sp,32` is &m cached in s1, and `move a1,s1; move a0,s1` instead of `addiu a1,sp,32; addiu a0,sp,32`.

The q dead-reset should kill the cse equivalence for q... but maybe with the struct assignment, the &m equivalence comes from elsewhere.

The target:
```
e78 addiu a1,sp,32     (delay slot of RotMatrixY)
e7c addiu a0,sp,32
e80 addiu a1,sp,16
e84 move a2,a1
```
Mine (z01):
```
48 addiu s1,sp,32
50 move a1,s1
51 move a0,s1
```
So mine keeps &m in s1 and copies; the target rematerializes `addiu a0/a1,sp,32`.

Why? Because in z01, the `q` dead-reset is there... Let me check: the q block is:
```
    {
        void *q = &m;
        RotMatrixY(ang & 0xFFF, q);
        q = 0;
    }
```
Hmm, and `func_800484EC((s32)&m, (s32)vec, (s32)vec);` — the &m at the func_800484EC call. The target materializes it fresh (`addiu a0,sp,32`), mine reuses s1.

Wait, but in y01 (score 0) the same q dead-reset gave the target behavior. The difference is that y01 still had the s-launder and the hand-expanded copy, which made `s` a register and kept the D_800AE620 base in a2. Maybe the presence of the `s` variable changed cse's behavior for `&m`.

Hmm, the `addiu s1,sp,32` is about `&m`. In y01 it didn't appear; in z01 it does. The difference: the struct assignment `m = D_800AE620;` uses &m as a store base (the compiler may take its address once and keep it in s1). In y01, the hand-expanded copy stores to `m.w[i]` — same &m base, but maybe the launder's presence affected it.

Actually, in y01 the s-launder ties `s` to itself, which might make cse treat the block differently (cse's equivalence tables).

Let me try: keep the struct assignment but add the q dead-reset in a different place, or add a dead-reset for the m address. C0414: `q = &m; f(...,q); q = 0;`. The remat issue is at the second use (`func_800484EC(&m,...)`). If we name the &m pointer for that call too and dead-reset it, maybe.

Actually, the simplest: `q = &m; RotMatrixY(..., q); q = 0;` then later `func_800484EC((s32)&m, ...)`. The &m in the func_800484EC call is a separate expression; cse may CSE it with the earlier &m. The q=0 reset kills the *q* equivalence, but the &m equivalence at the call site may be tracked separately.

Hmm, in y01 the reset worked. In z01, the struct assignment `m = D_800AE620;` introduces a *use of &m* before the q block (as the store destination). That use creates the &m equivalence that survives to func_800484EC.

So: add a dead-reset of the &m equivalence after the struct assignment? e.g., `q = &m; m = D_800AE620;`? Hmm.

Alternative: name the &m pointer for the func_800484EC call too:
```
q = &m;
RotMatrixY(ang & 0xFFF, q);
q = 0;
...
q = &m;
func_800484EC((s32)q, (s32)vec, (s32)vec);
q = 0;
```
But the target has `addiu a0,sp,32` (remat), so passing &m via q would emit `addiu a0,sp,32` too (same). The point is to avoid the s1 cache. Let me try adding a dead-reset after the struct assignment:
```
m = D_800AE620;
q = &m; q = 0;   // hmm, flow deletes both
```
No.

Let me think: the `addiu s1,sp,32` in z01 is the compiler caching &m in s1 across the RotMatrixY call. The q dead-reset was supposed to prevent that. In y01 it did. Why not in z01? Because the struct assignment makes &m "used" as a store destination earlier, and cse's equivalence for the *expression* `sp+32` is established at the struct copy.

Actually, maybe the issue is the *order*: in z01 the `m = D_800AE620;` statement is before the q block. cse sees &m at the copy (as a store base) and at RotMatrixY (via q). The q=0 reset kills the q pseudo's equivalence, but the address expression `&m` may be re-CSEd at the func_800484EC call.

In y01, the hand-expanded copy also uses &m (as m.w[i] store bases). So the same situation... yet y01 scores 0. Hmm.

Wait, in y01 the s-launder is present, which is an asm with `"=r"(s) : "0"(s)`. That asm is BEFORE the copy block. Maybe it changes cse's block structure/equivalence.

Let me try adding the s-launder back to z01 (with the struct assignment) — but then the s-launder (a launder kind) remains, which fails the MATCH. Unless... the row kinds are keepalive,launder; the s-launder is a launder, so it must go.

OK, alternative: keep the hand-expanded copy but replace the s-launder with real C. The s-launder's role: keep the base in a register. What if we use a `Blk20 *s = &D_800AE620;` and then the loads... that's already there.

Hmm, what if the base is kept in a register by making `s` volatile? no.

What if we use an array of u32 and index it: `u32 *s = (u32*)&D_800AE620; t0 = s[0]; ...`? cse may still remat.

What if the base comes from a *function call* result? no.

Let me try a few:
- z02: hand-expanded copy kept, s-launder replaced by `s = &D_800AE620;` and a dead-reset at the end of the block: `s = 0;` — but the remat happens at each load, before the reset.
- z03: use `Blk20 *s = &D_800AE620;` with `volatile` reads? no.
- z04: struct assignment + add a dead-reset after it: `q = &m; q = 0;` no.

Actually, let me look at what the target's copy block uses: `lui a2, D_800AE620; addiu a2; lw v1,0(a2)...`. The base is in a2. The struct assignment `m = D_800AE620;` should produce exactly that (move_by_pieces uses a2 as the source base). Let me check z01's asm copy block — maybe it's correct and only the &m part is wrong.

z01 diff only shows the addiu s1,sp,32 and moves. So the copy block matches! Great.

So the only issue is the &m caching at the RotMatrixY/func_800484EC calls. The q dead-reset isn't enough because the struct assignment established the &m equivalence.

Idea: move the q block BEFORE the struct assignment? No, RotMatrixY needs m filled.

Idea: add a dead-reset right after the struct assignment:
```
m = D_800AE620;
q = &m;
q = 0;          // kills the &m equivalence before RotMatrixY
```
Then the q block: `q = &m; RotMatrixY(...,q); q = 0;` — hmm, that's two resets. cse processes forward: `q = &m` sets the equivalence; `q = 0` kills it; then `q = &m` again. The address expression `&m` itself might still be in the table. The reset kills the *register* equivalence, not the address expression. Hmm.

Actually, what exactly does the target do? `addiu a0,sp,32` and `addiu a1,sp,32` — remat twice. Mine caches in s1 once and moves. So cse replaced one `addiu` with a register copy.

C0414's mechanism: "cse's forward scan invalidates the equivalence at the second set". The second set is `q = 0` after the call. That kills the equivalence of `q`, so at the func_800484EC call, cse doesn't use q but recomputes &m. In y01 it worked.

In z01, maybe cse sees `&m` at the struct assignment as a store address and keeps it in s1 (not via q). The q=0 reset doesn't kill the *address* equivalence.

Hmm, but why didn't the same happen in y01? In y01 the copy stores to `m.w[i]` — each store address is `sp+32+i*4`, a different expression. In z01, `m = D_800AE620` is a single 32-byte store; its base `&m` = sp+32 is a single address expression that cse records. That's the difference!

So the struct assignment introduces the &m equivalence. To kill it, I could add a dead-reset of the address... e.g., after the struct assignment, reference &m via a pointer and reset:
```
m = D_800AE620;
q = &m;
q = 0;
```
This sets q then kills it. The address expression &m is computed once and stored in q; when q is killed, the address expression's equivalence might persist in the cse table (keyed by the expression). Hmm.

Alternatively, use a different form of the struct copy that doesn't create the &m equivalence as a single expression: keep the hand-expanded copy but remove the s-launder. Then the residual is the remat of D_800AE620 (6 ins). That's x1 = 19.

Hmm. Let me try: struct assignment + the q dead-reset + a dummy use to break the address equivalence. For example, use `q` for the func_800484EC call as well:
```
q = &m;
RotMatrixY(ang & 0xFFF, q);
q = 0;
...
q = &m;
func_800484EC((s32)q, (s32)vec, (s32)vec);
q = 0;
```
If q is dead-reset before, cse won't cache it. But the target wants remat at both calls (addiu a0,sp,32), which passing q would produce (`addiu a0,sp,32`). Let me try.

Actually the target:
```
e78 addiu a1,sp,32   (RotMatrixY's a1, delay slot)
e7c addiu a0,sp,32   (RotMatrixY's a0)
e80 addiu a1,sp,16
e84 move a2,a1
...
e94 jal func_800484EC
```
Wait, RotMatrixY's args: `move a0,sp+32` at e7c and `addiu a1,sp,32` at e78? RotMatrixY(ang, q) → a0=ang (e70 andi a0,v0,0xfff), a1=q=&m. So e78 addiu a1,sp,32 is q. e7c addiu a0,sp,32 is... the func_800484EC first arg &m, materialized BEFORE the RotMatrixY call! Interesting: the target computes a0=sp+32 for the later call early (sched).

So the target rematerializes &m for the func_800484EC call (addiu a0,sp,32) rather than keeping it. Mine caches in s1.

The q dead-reset in y01 prevented the cache. In z01 the struct assignment's &m use creates a longer-lived equivalence.

Let me try adding a dead-reset of q right after the struct assignment AND before RotMatrixY:
```
m = D_800AE620;
q = &m;
q = 0;
{ q = &m; RotMatrixY(ang&0xFFF, q); q = 0; }
```
Hmm, q is declared inside the block. Let me restructure: declare q at function scope, then:
```
m = D_800AE620;
q = &m;
q = 0;                  // kill the address equivalence from the struct copy
q = &m;
RotMatrixY(ang & 0xFFF, q);
q = 0;
```
But the second `q = &m` re-establishes the equivalence... and then q=0 kills it again. The func_800484EC call uses &m directly.

Let me just try it.

Alternatively, move the q block to cover the struct assignment: `q = &m; m = D_800AE620; q = 0;`? cse would use q as the store base? no.

Let me test a batch:
- aa01: struct assignment + `q = &m; q = 0;` after it + the existing q block (q declared at function scope).
- aa02: struct assignment + pass q to func_800484EC with a reset.
- aa03: struct assignment + q block, but q reset *before* the call as well.

Let me write these.

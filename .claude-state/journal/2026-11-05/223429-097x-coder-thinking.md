---
ts: 2026-11-06T05:34:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ShLAwERw6I5V4YpEoyB6
---
Interesting: with cmp_u16, mine has `lhu a0,18(sp)` / `lhu v1,26(sp)` (unsigned loads) and `sltu`. The target has `lh`/`slt`. So the comparison mode must be signed. And mine still forwards the `sh a0,122(s0)`.

The key remaining: the target reloads `lhu v0,18(sp)` in the then-arm and `lhu v0,26(sp)` in the else-arm.

Let me think about how to force those reloads in pure C. The reloads are `lhu` (unsigned) while the comparison loads are `lh` (signed). cse's memory table: after the comparison loads `lh v0,18(sp)`, the cse table has entries for the mem refs. When the arm stores `*(s16*)(e+0x7a) = *(u16*)(a+2)`, cse looks up the load of a+2: the mem ref `(mem:HI (plus (reg a) 2))`. The earlier `lh` load is `(sign_extend:SI (mem:HI ...))`. cse's table is keyed by the full expression (sign_extend...) so the `lhu` (zero_extend) is a different expression. But the *memory* is the same; cse also records the mem ref separately? In GCC's cse, when it sees `(sign_extend:SI (mem:HI X))`, it records the SET as the sign_extend expression. A later `(zero_extend:SI (mem:HI X))` won't match that expression. But the `sh` store only needs HImode; combine/cse may convert `(mem:HI X)` store value: the value is `(subreg:HI (zero_extend:SI (mem:HI X)))` which simplifies to `(mem:HI X)`. Then cse might look up `(mem:HI X)` — is there an entry? The earlier load recorded `(sign_extend:SI (mem:HI X))`, not `(mem:HI X)`. Hmm, but cse's `cse_insn` for a load also records the *memory* address in a separate "memory table" (`reg_eqv`?). In GCC 2.7.2 cse, there's no separate memory table; it uses the expression table with `hash_arg_in_memory`.

Hmm, but empirically the value IS forwarded (mine uses a0/v1 in the store). So somewhere the load is reused.

Wait — maybe it's not cse but the register allocator/scheduler: the comparison loads `lh a0,18(sp)` produce a0; the store `sh a0,122(s0)` uses a0 directly because the *same pseudo* holds the loaded value! The source `*(u16*)(a+2)` in the store is a *different expression* but the compiler's cse equated them, so the store uses the same pseudo as the comparison load.

In the target, the store reloads. To make the store use a *fresh* load, we need cse to not equate. Since cse equates mem refs by address (plus the mode), and both are HImode mem at the same address, they equate regardless of sign/zero extension (the extension is applied after).

Hmm, is there a way to make the two addresses *look* different? E.g., the comparison reads `*(s16*)(a+2)` and the store reads `*(u16*)((u8*)e ...)` no.

What if the comparison reads from `b` and the store from `a`? No, the values differ.

What if the comparison value is stored in a local *array* element that's then reloaded... no, cse would equate the array element.

What if the store's value expression involves a *different variable* that the compiler can't equate, e.g., `a[2]` vs `*(s16*)((u8*)a + 2)`? Same address.

What if we introduce a pointer `u8 *ap = a;` and read `*(u16*)(ap+2)`? Same address after folding.

Hmm. What about reading the store value through `out`? no.

OK, what if the comparison is computed as `*(s16*)(a+2) - *(s16*)(b+2) < 0`? Then the load is used in a subu; the store reload would still be equated.

I think cse-store-forward is unavoidable in pure C for this shape. But note the wall tag `cse-store-forward` describes "cse forwards the sh value into the reload after `*p -= 16` in one ebb; only a barrier/volatile stops it". Similar.

Let me try a few more exotic but legitimate moves:
1. Make the arms' stores use `a[0]`/`a[2]`/`a[4]` via a **u16 local array copy**: `u16 tmp[3]; tmp[0]=...` — no.
2. **Reorder** the comparison to *after* the first store: e.g., store a[0], then compare, then a[2]/a[4]? That changes semantics (the branch must come first). No.
3. Split the `if` into two nested ifs: `if ((r5|r6)!=0) { if (a2<b2) {...} else {...} }` — same.
4. Use `?:` to select: `s16 *src = (a2 < b2) ? a : b; ...` — that changes codegen a lot (pointer select), might produce different code. Semantically same. Let me try.
5. Make `a` and `b` `s16[4]` arrays instead of `u8[8]`: `s16 a[4]; ... a[0]=...; a[1]=...` — different addressing but maybe.
6. Use `*(s16*)(((s32)e)+0x7a) = *(s16*)(a+2)` (signed store value) — same bits.
7. Add a `s32` temp holding a[2] before the branch and store it — cse forwards.

Let me also reconsider the frame: vars 40 vs 24. The 16-byte extra is a reload spill slot. If I reduce register pressure (e.g., remove `r5`/`r6` live ranges), maybe the spill disappears. The spill likely holds a value across the calls (r5 is live across the second call; a, b, out addresses are live). With 2 callee-saved regs (s0=e, s1=r6?), the rest spill.

In the target (with clobber), the clobber forces memory reloads which changes liveness. Hard to replicate.

Let me try the `?:` pointer-select and s16 arrays. Also try removing `out` (can't, used in memcpy).

Actually — a thought: the target's *frame* is smaller because the arrays a/b are at sp+16..31 and out at 32..39 (24 bytes vars). The nobar has 40 bytes vars, meaning the arrays are at 16..39 and something at 40..55. What if the nobar allocates `out` at 32..39 and the spill at 40..55? Yes.

The spill is a reload artifact: a pseudo with 16 bytes (BLKmode from the memcpy?). Hmm, `__builtin_memcpy` of 8 bytes might create a BLKmode pseudo of size 8, not 16. Two 8-byte slots = 16. The memcpy temps.

Let me test: replace `__builtin_memcpy` with explicit 8-byte copies (two u32 stores) and see the frame/score. That's a real-C move (statement form). The target uses lwl/lwr/swl/swr (memcpy expansion), so explicit u32 stores would differ (two lw/sw instead of lwl/swl). Hmm, but maybe with `*(u32*)` it still uses lwl/lwr? No.

Let me check: the target's memcpy is expanded to lwl/lwr (unaligned copy) because the destination `e+0x80` may be unaligned. If I write two u32 stores, GCC would use lw/sw (aligned) — different code.

OK. Let me try a batch of ~10 more variants and then decide.

Actually, let me reconsider the whole item. The barrier is `__asm__ __volatile__("" ::: "memory")` INSIDE each arm, right after the `if`. Its effect: (1) prevents cse from forwarding the comparison load into the arm stores (forcing reloads), and (2) changes the frame from 40 to 24 vars.

Both effects are barrier artifacts. Pure C cannot insert a scheduling/cse barrier. The moves.md entry `cse-store-forward` (G18x) says exactly: "cse forwards the sh value into the reload ... only a barrier/volatile stops it". So this is a known wall.

Given the budget, item 1 is a WALL with tag `cse-store-forward`. But I need ≥30 tries. I have 25 (24 scored + 1 compile error). Let me add ~10 more.

Let me write wave 2 for item 1 with: ?: pointer select, s16 arrays, u16 arrays, explicit copy, reordered arms, r5/r6 as u32, e as s32 param cast, etc.

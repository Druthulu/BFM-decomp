---
ts: 2026-11-06T09:33:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9WEdj7rD1IoJOgQImQjQ
---
The diff: mine has `move a0,s0` at 37 then uses a0 for the store and the `lw v0,68(a0)`; target stores `sh zero,392(s0)` at 37 *before* `move a0,s0` at 38, and uses a0 for `lw v0,68(a0)`.

So in the target, the store `*(u16*)(s0+0x18A) = 0` uses s0, and only after it is s0 copied to a0 (for the func_801553C0 call arg). In mine, s0 is copied to a0 earlier (at 37) and the store uses a0.

Why? Source:
```
*(u16 *)(s0 + 0x18A) = 0;          // sh zero,392(s0)
...
__asm__("" : : "r"(s0));           // keepalive
*(u32 *)(s0 + 0x44) = *(u32 *)(s0 + 0x44) & 0xFFFFFFFB;   // lw v0,68(a0); and; sw v0,68(a0)
func_801553C0(s0);                 // move a0,s0; jal
```
Target: sh zero,392(s0) [37]; move a0,s0 [38]; lw v0,68(a0) [39]; li v1,-5 [40]; and [41]; jal func_801553C0 [42]; sw v0,68(a0) [43].

So s0 is copied to a0 at 38 (before the call), and the `& 0xFFFFFFFB` store uses a0. The store `sh zero,392(s0)` uses s0 directly (before the copy).

Without the keepalive, mine: move a0,s0 at 37 (hoisted earlier, before the store), sh zero,392(a0) at 40, lw v0,68(a0)...

So the keepalive forces s0 to be live at the point *after* the store, preventing the copy from being hoisted above the store? Actually the copy `move a0,s0` is for the call arg (a0 = s0). GCC's sched1 moved the copy up (birth of the copy) without the keepalive; with the keepalive, the copy stays after the store because s0 is used by the asm.

Hmm, more precisely: with the keepalive, the store must use s0 (s0 is live and is the natural base). Without, the compiler coalesced s0 and a0? No — the store uses a0 in mine, and the copy move a0,s0 is at 37 before it. So the compiler decided to copy s0 to a0 early and use a0 for the rest (because s0 dies? s0 is used later at the call and `lw v0,68(a0)`).

Actually `lw v0,68(a0)` in both: the load/store of +0x44 uses a0 (the copy). And the call arg is a0. So a0 = s0 copy for the tail. The store at +0x18A: target uses s0 (before the copy), mine uses a0 (after the copy).

So the question is the *order*: target does store-then-copy; mine does copy-then-store. That's sched1 order (or the copy's placement). The keepalive (a use of s0 after the store) keeps s0 live past the store, so sched1 doesn't move the copy above the store (the copy would then have to wait). Without it, sched1 hoists the copy to 37.

Real C: we need a genuine use of s0 after the `sh zero,392(s0)` store, before the copy. Is there one? The source:
```
*(u16 *)(s0 + 0x18A) = 0;
[keepalive]
*(u32 *)(s0 + 0x44) = *(u32 *)(s0 + 0x44) & 0xFFFFFFFB;
func_801553C0(s0);
```
The next real use of s0 is the `& 0xFFFFFFFB` read/write, which the target does via a0 (the copy). Hmm, but that use is after the keepalive.

So a real use of s0 after the store: the `*(u32*)(s0+0x44) & ...` — if the compiler keeps that in s0 instead of copying to a0, the store order would be right. The copy exists because the call arg needs a0 and the compiler copies s0 to a0 to free s0? s0 is callee-saved, so the call doesn't clobber it. Hmm, why copy at all? Because `func_801553C0(s0)` passes s0 in a0 — a copy is needed (a0 = s0). The compiler then uses a0 for the preceding load/store to shorten s0's live range (s0 dies after the copy). So s0's last use is the copy.

Target: s0's last use is the copy too, but the store at 37 happens before the copy.

So the difference is just scheduling/ordering: the copy's position relative to the store. With the keepalive, s0 is used after the store → the copy can't move above the store (it could, actually, since a0 is a separate reg... but sched1 keeps program order dependencies: the copy depends on s0; the store also uses s0; no dependency between them. sched1 could still hoist the copy above the store. But with the keepalive, the copy is *after* the keepalive in source order, and sched1 didn't hoist it).

Hmm, so with the keepalive, the source order is: store, asm(s0), load/store +0x44, call. The copy is before the load (source order: the +0x44 statement uses s0 directly; the copy appears at the call). Wait, the source `*(u32*)(s0+0x44) = ...` uses s0; the compiler generated `move a0,s0; lw v0,68(a0); ...; sw v0,68(a0)` — it substituted a0 for s0 in the +0x44 statement (reusing the call's copy). That's the "copy" optimization: the arg copy a0=s0 is made early and all later uses of s0 are rewritten to a0.

Without the keepalive: the +0x44 statement's uses are rewritten to a0, and the copy is hoisted above the +0x18A store too (because the +0x18A store also got rewritten? no, the store used a0 too). Hmm, in mine the +0x18A store uses a0 as well — so *all* s0 uses after the branch join got rewritten to a0, including the store, and the copy moved above it.

With the keepalive, the asm use of s0 sits between the +0x18A store and the +0x44 statement, so the +0x18A store stays on s0 (before the asm), and the +0x44 uses are rewritten to a0.

Real C: put a genuine use of s0 between the store and the +0x44 statement. Is there one? The keepalive is exactly there. Hmm.

What if we reorder: the +0x44 statement could be written *before* the +0x18A store? Target order: sh zero,392(s0) at 37, then lw/sw +0x44 at 39-43. So no.

What if the store's base is spelled differently, e.g. `*(u16 *)(a0 + 0x18A) = 0` with a0 = s0? There's no a0 variable in the source.

Alternative real C: make the +0x18A store use a *different* pointer variable that aliases s0, e.g.:
```
u8 *p = (u8 *)s0;  // or s32 *q = s0;
*(u16 *)(p + 0x18A) = 0;
```
Then p is a separate variable = s0 (copy). The copy would be `move a0,s0`? Hmm, p would be a pseudo; the compiler might use s0 directly (copy propagation). Not obviously different.

Better idea: swap the order of statements? The +0x18A store and the +0x44 RMW are independent; the target has store first. Source has store first. Without the keepalive, the compiler reordered (sched1) — the store moved after the copy.

What real C would keep the store on s0? If s0 were used *between* them, as noted. Or if the store's value/address computation made it depend on something.

Hmm, what about the store being `*(u16 *)(s0 + 0x18A) = 0;` — could we write it as `s0->field` style? The source uses casts. Maybe the real C had a struct pointer, e.g. `p->unk18A = 0;` where p is a local pointer = s0. Hmm.

Actually, wait: maybe the real C's store used a *different* variable: `*(u16 *)(iVar + 0x18A) = 0` where iVar is a copy of s0 made at the top. But target uses s0 for it.

Let me look at the whole function's source and target again:

```
void func_8016432C(s32 a0) {
    s32 s1 = a0;
    s32 s0 = *(s32 *)(s1 + 0x4C);
    func_80164418();
    if (func_80146E98(s1) != 0) {
        u32 v44;
        *(u16 *)(s0 + 0x18A) = 0;
        if (*(s32 *)(s0 + 0x184) != 0 && ((v44 = *(u32*)(s0+0x44)) & 0x400) == 0 && (*(u32*)(s0+0x1F8) & 0x80FFFFFF) == 0) {
            *(u32*)(s0+0x44) = v44 | 0x10;
            if (*(s16*)(s0+0x188) < 0x80) { *(u32*)(s0+0x184) |= 0x80000000; }
        } else {
            *(s32*)(s0+0x184) = 0;
        }
        *(u16*)(s0+0x188) = 0;
        [keepalive]
        *(u32*)(s0+0x44) = *(u32*)(s0+0x44) & 0xFFFFFFFB;
        func_801553C0(s0);
        ...
    }
}
```

Target insns: 36 `sw zero,388(s0)` (the else branch `*(s32*)(s0+0x184)=0`? 388 = 0x184; yes). 37 `sh zero,392(s0)` (0x188 = 392! wait 0x188 = 392 decimal. And 0x18A = 394). Let me recompute: 0x184 = 388, 0x188 = 392, 0x18A = 394. 

Target: insn 15 `sh zero,394(s0)` = *(u16*)(s0+0x18A) = 0 (the first store!). Then insn 37 `sh zero,392(s0)` = *(u16*)(s0+0x188) = 0 (the later store). Ah, I misattributed. So the store at 37 is `*(u16 *)(s0 + 0x188) = 0;` — the one right before the keepalive. And mine has `sh zero,392(a0)` at 40 after the copy.

OK so the keepalive is right after the 0x188 store, and it keeps s0 live so that store uses s0 (not the copy a0).

Real C use of s0 between the 0x188 store and the +0x44 statement: none. Same liveness issue.

BUT: maybe there's a real-C move: the +0x44 RMW statement. If we write it so it uses s0 in a way that the copy isn't made early... The compiler copies s0→a0 for the call arg and rewrites the RMW to a0. If instead the RMW were written *before* the call in a separate statement that doesn't get rewritten... it already is.

What if we introduce a genuine use of s0 in the RMW that prevents the rewrite? E.g., `*(u32*)(s0+0x44) &= ~4;` — same.

Hmm, what if we *change the call argument* to avoid the copy: `func_801553C0(s0)` — the call needs a0=s0. The copy is inherent.

What if the function's call were written with a cast: `((void (*)(s32))func_801553C0)(s0);` — same.

What if the call takes s0 as a *different* type? Same.

Alternatively, make the 0x188 store depend on a value that's computed later? E.g., `*(u16 *)(s0 + 0x188) = 0;` — constant 0.

Hmm, what if we combine the two stores: `*(u16 *)(s0+0x18A) = 0; ... *(u16 *)(s0+0x188) = 0;` — they're in different branches? The 0x18A store is at the top of the if-body; the 0x188 store after the inner if/else. Both before the keepalive.

Real C idea: move the +0x44 RMW *before* the 0x188 store? Target order: 0x188 store (37), then RMW (39-43). No.

What about making the RMW use a variable that is *also* used after (so it's not rewritten)? The RMW is `*(u32*)(s0+0x44) = *(u32*)(s0+0x44) & 0xFFFFFFFB;` Target: `lw v0,68(a0); li v1,-5; and v0,v0,v1; sw v0,68(a0)`. The base is a0 (the copy). If the source wrote this RMW via a pointer variable `p44 = (u32*)(s0+0x44); *p44 &= ~4;` — the compiler would use a0 or s0? Hmm.

What if the source used s0 *after* the call? No.

Let me try the simplest real-C moves:
1. `*(u16 *)(s0 + 0x188) = 0;` moved *after* the RMW? Target order says before.
2. Use a local pointer `u8 *p = (u8 *)s0;` at the top and use p for the 0x18A/0x188 stores? Then p is a copy of s0; the target's sh uses s0 though. If p is coalesced to s0, fine.
3. Make the 0x188 store use a value: `*(u16 *)(s0+0x188) = 0x0000;` same.
4. Reorder: move the RMW before the 0x188 store but keep insn order? no.
5. Declare `s32 s0` as `u8 *s0`? no.

Actually — wait. What if the real C had the 0x188 store *inside* the if/else, i.e. duplicated? Target has one sh at 37 after the join. No.

Hmm, what about the copy being avoided if the call is the last use and s0 is passed directly: GCC's "argument copy" optimization. Target: `move a0,s0` at 38 (after the store). Mine: at 37 (before). This is sched1 birth order (like the wall tag `sched1-birth-order`). The keepalive prevented it.

Real C lever: make the store's s0 use *ordered* after something... Or make the copy's birth later in source: the copy comes from the call arg, which is after the RMW in source. sched1 hoisted it above the store because nothing depends on it. With the keepalive, the copy stayed put.

Could we make the store depend on the copy? No.

Could we make s0 live across the store via a genuine use? What if the RMW statement is *split*: `u32 v = *(u32*)(s0+0x44); *(u32*)(s0+0x44) = v & ~4;` — then s0 is used twice after the store. The compiler would still use a0.

What if we add a genuine use of s0 in the branch condition? No.

Hmm, let me look at it from the other side: in mine, why does the *store* use a0 at all? Because the compiler replaced s0 with a0 in the store (copy propagation after the copy was hoisted). If we could prevent the replacement... e.g., if the store were before the copy in source and the compiler kept source order — the copy is generated at the call (source-later). The hoisting is sched1.

What if we make the store and the RMW *ordered* by aliasing? E.g., write the RMW through a pointer that the compiler can't prove doesn't alias... they're the same base s0.

What if the store is `*(u16 *)(s0 + 0x188) = (u16)v44;` where v44 is the RMW value? That would create a dependency but wrong semantics.

OK, what about a *different* real-C spelling of the RMW: `s0->unk44 &= ~4`? Same.

Maybe the real C wrote the +0x44 RMW as `*(u32 *)(s0 + 0x44) &= 0xFFFFFFFB;` — compound assignment. Currently it's `*(u32 *)(s0 + 0x44) = *(u32 *)(s0 + 0x44) & 0xFFFFFFFB;`. Compound assignment might produce a different RTL (no cse? still lw/and/sw). Let me try.

Also try: `v44` reuse: `v44 = *(u32*)(s0+0x44) & 0xFFFFFFFB; *(u32*)(s0+0x44) = v44;` — a temp. The v44 variable exists already in the inner if. Hmm.

Let me try a batch:
t1: RMW as compound `&= 0xFFFFFFFB`.
t2: RMW with temp: `u32 t = *(u32*)(s0+0x44); *(u32*)(s0+0x44) = t & 0xFFFFFFFB;`
t3: store 0x188 as `*(u16*)(s0 + 0x188) = 0;` moved after the RMW (order change) — try to see.
t4: pointer variable p = (u8*)s0 used for both stores.
t5: `s32 s0 = ...; s32 s0b = s0;`? 
t6: call arg `func_801553C0((s32)s0)` — cast.
t7: call arg `func_801553C0(s0 + 0)` — the copy might be forced differently (add 0 → maybe no copy).
t8: RMW using the pointer variable: `u32 *p44 = (u32 *)(s0 + 0x44); *p44 &= 0xFFFFFFFB;`
t9: `*(u16 *)(s0 + 0x188) = 0;` written via `((u16 *)s0)[0xC4] = 0;` (index spelling).
t10: use s0 in the call twice? no.

Let me score these.

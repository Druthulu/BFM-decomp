---
ts: 2026-11-06T21:07:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UyiIrU4WE96XD9Jj81Kz
---
Interesting! This is a DIFFERENT function with the same name but a different body (switch-based, different semantics: returns D_80184F58[...](tmp) with an argument). It's an overlay-local duplicate name (reach-1). Not the same as our item's body. Note the difference: this one passes `tmp` to the call, which keeps tmp live → different allocation. Not directly reusable.

But it shows `s32 tmp = ...; s32 ang = tmp;` — a lever-free body with a copy, and it's MATCH (68 ins). In that body, `tmp` is used later (`tmp = ratan2(...)`) so it has a second use → combine keeps the copy! That's the key: tmp is reassigned and used later, so `ang = tmp` isn't a single-use copy.

In our item's target, `a` is not used later. Hmm.

Wait, maybe our item's C could be structured so `a` is used later harmlessly? In the target, `a` (a0) is dead after the move. But what if the C uses `a` later in a way that's optimized to the same code? E.g., `res = (ang + ...)` uses ang. If instead we used `a` in the final expression... but a is clobbered by the ratan2 call at 3550. Unless the compiler re-copies.

Hmm.

Let me reconsider the whole thing. Perhaps the intended crack is different: maybe drop the pin and keepalive, and find that the target's `move s0,a0` can be produced by a *different* real-C structure that doesn't need the pin at all.

Let me look at the target's andi a0: why would plain C put the andi result in a0? If the andi result is used as... hmm, $4 is the first argument register. In plain C, a value would go to a0 if it's passed as an argument or if local-alloc prefers it. 

Actually, consider: maybe the original C used `a` as a function argument in the `case 0x41` path! Look at the SC03_099 sibling: `return D_80184F58[D_80126C02 >> 12](tmp);` — it passes `tmp` as an argument! And the target for OUR item at 34e0-3508: 
```
lui v0, D_80126C02
lhu v0,0(v0)
srl v0,v0,0xc
sll v0,v0,0x2
lui at, D_80188654
addu at,at,v0
lw v0,0(at)
nop
jalr v0
nop
sll v0,v0,0x10
j 3560
sra v0,v0,0x10
```
The jalr has no argument setup (a0 not set). But wait — a0 at that point already holds `a` from the andi (34ac move s0,a0 doesn't clobber a0; a0 still = a at 34e0). So the table function is called with a0 = a implicitly! The target's `jalr v0` uses whatever a0 is — which is `a`. So the C likely passes `a` (or `ang`?) as the argument, but the argument copy is free because a0 already holds it!

That's it! If the C is `return (s16)((s16(*)(s32))(D_80188654[D_80126C02>>0xc]))(a);` — passing `a` as the argument. Then `a` has a second real use (as a call argument), so combine keeps the copy. And the argument setup is free because a0 = $4 already holds a. 

But wait: in our item's orig.c, the call is `((s16 (*)())(D_80188654[D_80126C02 >> 0xc]))()` with no args. Yet the target's a0 is `a`. The original matched with the pin+asm. But the real C could pass `a`.

Let's check: target at 34e0: `lui v0, D_80126C02` etc. — no `move a0, s0`. So if C passes `a`, gcc emits the arg copy as a0 = a; since a is already in a0, it's a no-op (deleted). 

But careful: after `move s0,a0` (ang=a), a0 still = a. The branches don't clobber a0. The `call` path jumps to 34e0 with a0 = a. So passing `a` is free.

And the target's `jalr v0` with delay `nop` — then `sll v0,v0,0x10` / `j 3560` / `sra v0,v0,0x10`. The call returns s16, sign-extended.

So the C should be:
```
call:
    return (s32)(s16)((s16 (*)(s32))(D_80188654[D_80126C02 >> 0xc]))(a);
```
Wait, but the function type: `s16 (*)(s32)` — passing a. Actually the target doesn't set up any argument, meaning the argument is already in a0. Let me check the shared header `func_80148D44.h`? No, item1 is TU-specific. But the sibling in SC03_099 uses `s16 (*)(s32)` and passes tmp. Different function though.

Hmm, but our target's table is D_80188654 and the signature comment at the TU end: "derived from asm: lui/addu/lw %lo(D_80188694) indexed by (u16>>12)*4, then jalr with no args; the result is sign-extended from 16 bits => the table's functions return s16." That comment is about D_80188694 (a later function). For our function, the table is D_80188654.

Let me check if there's a comment about D_80188654. Also, passing `a` as an arg — the arg type: if the function takes s32, then `(s16(*)(s32))` and pass `a`. The result cast to s16.

But hold on: if we pass `a` to the call, then in the C the call is only on the `d==0x41` path. `a` is live there (from the andi). So `a` has 2 uses: ang=a and the call arg. Combine won't fold! And the pin forces $4. 

Let me also check the target: is there any `move a0,s0` before jalr? No. Because a0 already = a. If C passes `a` and a is in $4, no move. If C passed `ang` (s0), there'd be `move a0,s0` — which the target lacks. So it must pass `a`.

But wait, the andi result `a` is in a0 only if the pin/alloc puts it there. With the call arg use, a is live until the call (across the branches), so it can't be in a0 (call-clobbered)? It's used AT the call as the argument, so a0 is exactly right. But between the andi and the call, there's no other call on that path (the branches: d==0x41 → call). On the path to the call, no calls intervene. But a is live across the branch structure; if a is in $4 and any other path calls... the `final` path calls ratan2 at 3550, but a is dead there (ang used). Hmm, a is live on the call path only. Dataflow: a is live from andi to the call arg (on the 0x41 path) and to the ang copy (all paths). So a is live across the whole branch region → conflicts with $4 across the ratan2 call in final? But a is dead in final (after the copy). The copy is at 34ac, before the branches. So a dies at 34ac for the final path, but lives to 34e0 for the call path. So a's live range crosses the branches but not the ratan2 call in final (since on that path a is dead after 34ac). Actually a's live range is the union; if a is live on the 0x41 path up to 34e0, and the final path's ratan2 call at 3550 is a different path — in a single live-range analysis, a's live range includes the region from andi to the last use (34e0) along that path; the ratan2 call at 3550 is not in a's live range if no use after. So a can be $4 (a0) if local-alloc sees no conflict. But $4 is call-clobbered; the jalr at 3504 is on the same path as the a0 use (34e0→3504). a is used at 34e0 (as arg, in a0) — the call at 3504 clobbers a0 but a is dead after the arg setup. So fine.

But wait: the target's 34ac `move s0,a0` is the ang copy; a is still in a0 after. Then branches; on the 0x41 path, a0 still holds a → jalr uses it. On other paths, a0 dead. Good.

So passing `a` to the call should work and give combine a second use. Let me test!

Actually, careful: the call in orig.c is `((s16 (*)())(D_80188654[D_80126C02 >> 0xc]))()`. We need to add `(a)` argument with a cast to a function type taking an arg. The return type s16. Let me write:

```
call:
    return (s32)(s16)((s16 (*)(s32))(D_80188654[D_80126C02 >> 0xc]))(a);
```

But `a` is `register s32 a __asm__("$4")`. Passing a register-asm variable as an argument — GCC may complain or handle. Should be fine.

Hmm, but if we pass `a`, the compiler must ensure a0 = a at the call. Since a is pinned to $4, it's already there. 

Let me test w3: orig minus keepalive, plus `(a)` argument.

Also, maybe we can then also drop the pin? If a is passed as an argument, plain C would put the arg in a0 naturally, and the andi's destination could be a0 because it's the arg. But then ang=a copy: the andi writes a0, ang copy to s0. Might work without the pin! Let's test both.

Let me write w3 (with pin) and w4 (without pin).

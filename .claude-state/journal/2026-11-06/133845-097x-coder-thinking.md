---
ts: 2026-11-06T20:38:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jAx58D3dN4ssSoTWch5C
---
Item 4: kinds = pin. The def has:
- `register s32 zr __asm__("$0");` — pin $0 (the zero register!). This is the row lever.
- Also a `do { ... } while (0);` with `// !FAKE: do-while` — that's allowed (not a row kind; it's a real-C split, and the brief allows do-while with the comment).

So remove the `zr` pin: `register s32 zr __asm__("$0");` and `s32 ent = (s32)a0 + zr;` → `s32 ent = (s32)a0;` (or just use a0 directly).

The pin $0 forces `ent = a0 + $0`? $0 is zero, so `ent = a0`. Why would a pin on $0 matter? Because `s32 ent = (s32)a0 + zr;` with zr=$0 forces the compiler to materialize `add ent,a0,zero` (a move) — actually `a0 + 0` would be folded away normally. The pin makes the addition real (the compiler can't fold $0? It knows $0 is zero... hmm, gcc's fixed_regs[$0] is zero_reg, and the value is known 0. Maybe not folded because it's a register variable read).

Let me first remove the pin and score.

The target uses a0 directly as the base (`lw v1,196(a0)`, `sh v0,10(a0)` etc.) — no separate `ent` register. In the target, a0 = s0? Look: `move s0,a0` at the top, then later `move a0,s0` (ed4c) and the stores use a0 as base. So the target's `ent` is a0 (a copy of s0). Interesting: `ed4c move a0,s0` then `lw v1,196(a0)`, `sh v0,10(a0)`... So the target has a0 = s0 (a copy) at ed4c, used as the base for the stores.

In the C, `ent = (s32)a0 + zr` — with zr = $0, this is a move of a0 into ent (a new pseudo). The target's `move a0,s0` at ed4c is that move! So the pin forces the `ent` pseudo to be materialized as a real copy (move a0,s0), and the pseudo is allocated to a0.

So removing the pin: `ent = (s32)a0;` would be copy-propagated (ent = a0), and the stores would use s0 directly instead of a0 → different code (the move a0,s0 at ed4c would disappear).

So we need a real-C way to force a real copy of a0 into a new variable that the compiler keeps and allocates to a0.

Hmm, but wait: why does the target use a0 as the base rather than s0? Because the source's `ent` is a separate variable that got a0. The `move a0,s0` at ed4c is the copy.

Real C ways to create a copy that isn't propagated: 
- `s32 ent = (s32)a0;` — copy-prop removes it.
- Use the copy in a way that... hmm.

The `do{}while(0)` already splits the block. The copy `ent = a0` is created inside the block before the do-while.

Wait, actually the do-while is placed around the first two stores (`*(s16*)(ent+0xA) = v[1]; t1 = *(u32*)(ent+0xC4);`). The `ent` copy is before it.

Hmm, but why is `ent` needed at all? The code uses `ent` for all the stores. If we just used `a0` (the parameter) directly, the compiler would use s0 (the callee-saved copy of a0) as the base — that's what the lever-free version would do. The target uses a0 because the source introduced `ent`.

Wait, but the target's `move a0,s0` at ed4c — a0 = s0. Then all the stores use a0. And a0 is a call-clobbered register; the call func_80188650 at the end uses a0 = ent anyway. So a0 holds ent throughout.

Why would the compiler keep a separate copy in a0 rather than using s0? Because `ent` is a distinct pseudo (from the addition with zr). Without the pin, `ent = a0` is a copy → coalesced/propagated to a0 (the parameter's pseudo), which is s0. Then the stores use s0, and the final call would `move a0,s0` — the target's move a0,s0 at ed4c would be gone (it would appear at the call instead, in the delay slot).

So the pin forces the copy at ed4c.

Real-C alternatives to force a copy at that point:
1. Make `ent` a `volatile`? no.
2. `s32 ent = (s32)(a0);` copy-prop.
3. Make ent's value slightly different but equivalent: `ent = (s32)a0 + 0;` folded.
4. Use a cast through another type: `ent = (s32)(u32)a0;` — copy.
5. Use a pointer type: `u8 *ent = (u8 *)a0;` — copy-prop.

Hmm. The pin on $0 is a way to force an addition with a register whose value is known 0 but which the compiler treats as an opaque register read. Since $0 is a fixed register, `zr` reads $0 — gcc might treat a read of a fixed register as a value (not fold it).

Real-C equivalent without a register variable: an opaque zero. E.g., a global variable that's zero? That would add a load. 

What about `s32 ent = (s32)a0 + (s32)(a0 - a0);`? The compiler folds `a0 - a0` to 0? cse might not fold it initially; it could emit `subu` + `addu`. Hmm, that adds insns.

What about `ent = (s32)a0;` followed by `ent += 0;`? folded.

Hmm. But maybe we don't need a copy: maybe there's another way to make the compiler use a0 for the base. The parameter a0 is copied to s0 at the entry (because a0 is call-clobbered and the function calls things). The source uses `a0` in many places; gcc keeps it in s0.

The target's shape: after RotTransSV, `move a0,s0` and then a0 is used as the base for the stores and the final call. Why a0? Because `ent` (a separate variable) was allocated to a0, and the copy from s0 to a0 was emitted at its definition.

So we need a separate variable that isn't coalesced with a0's original pseudo. The pin on $0 prevented the coalescing because `ent = a0 + $0` is a real addition.

Real-C: `s32 ent = (s32)a0; ...` — the copy may be coalesced. But wait, the do-while split might prevent copy propagation? The `ent` variable is defined before the do-while and used inside/after. Copy propagation (cse1) could still replace ent with a0.

Hmm, but note: `ent` is used as an s32 and cast to pointers for stores. If we declare `ent` as a pointer (`u8 *ent = (u8 *)a0;`), copy-prop still applies.

Let me just test the straightforward lever-free body: remove the `register ... zr` line and change `s32 ent = (s32)a0 + zr;` → `s32 ent = (s32)a0;`. Score it.

Then try variants:
- `ent = (s32)a0;` 
- `u8 *ent = (u8 *)a0;`
- `s32 ent = (s32)(a0);` 
- Move the `ent` definition to where it's used.
- Use `a0` directly everywhere (no ent).

Let me first score the baseline.

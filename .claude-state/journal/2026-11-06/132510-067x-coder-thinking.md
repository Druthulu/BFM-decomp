---
ts: 2026-11-06T20:25:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_l27utzCxB36633C4Txr4
---
In orig, the asm is `__asm__ __volatile__("" : "=r"(r) : "0"(r))` — a volatile asm → "must be considered to use and clobber all hard registers, all pseudo-registers and all of memory" → sched2 treats it as a full barrier! That's why the const stays before it and the li stays after.

So the launder is a scheduling barrier in sched2 (volatile asm). Its real effect: pin the constant before the store.

Real-C equivalent: a scheduling barrier. There isn't one in plain C... unless a real dependency chain does it.

Alternative: reorder so that the store comes before the const in source and the const has a dependency on the store? No.

Hmm, what about making the constant *not* rematerializable/hoistable by sched2: sched2 moves the const down to the delay slot because it's low priority and has no deps. If the const were used earlier (a second use), it couldn't sink. Could we use r twice with the same final code? The callee gets r once. 

What if we write `r` into a memory location that already gets written? no.

OK, different approach: maybe we can achieve the target's final order by making the *store* last, i.e., the store is what reorg picks for the delay slot. In nolau, the order before the call is li, sh, const. If the const were before the li, the order would be const, li, sh → reorg picks sh. The const sank below because sched2 moved it down.

Why did sched2 move the const below the li/sh? Because the const has no dependency and the li/sh chain is higher priority? sched2's `schedule_block` builds the ready list and picks by priority. The const (a1) probably has low priority (used by the call, far).

In target (orig), the volatile asm blocked it.

Real-C: give the const a dependency that forces it before the li. E.g., make the const depend on `q` (a0=s0): `r = 0xFFF80000` can't depend on q without changing the value... unless we use a bitwise op with a value we know: no.

Hmm, what about declaring `r` as a *volatile* variable? `volatile s32 r = 0xFFF80000;` — then r is memory (stack slot), and the call arg would load from the stack: `lw a1, off(sp)` — different code.

What about `s32 r; ... r = 0xFFF80000;` with a barrier... no.

Alternative: use a union to make the constant opaque? e.g.
```
union { s32 i; u32 u; } c;
c.u = 0xFFF80000u;
r = c.i;
```
That's a stack store/load → different code.

What about making the constant 0xFFF80000 come from a computation that sched2 can't sink because it has a dependency on the store? E.g., `r = 0xFFF80000;` where the value is derived from `v`... 

Wait, actually, let me reconsider: maybe we can restructure the arm so the *store* comes before the const and the const's position doesn't matter because reorg picks the store. In nolau, the RTL before the call is li, sh, const; reorg picked the const (last insn) for the delay slot. If the const were before the li, reorg would pick the sh.

So we need sched2 to keep the const before the li. sched2's order is driven by priorities. What if we make the const's definition *later* in a dependency sense: e.g., make r depend on the value stored? no.

What if we increase the const's priority by making it feed something? The call arg use gives it priority 1 (or 2).

Hmm. Let me look at the sched2 dump for both to see the ready lists and why the const moves.

Actually, maybe a much simpler idea: make the store's value depend on r! E.g., `((Unk*)s0)->unk2 = 7;` and `r = 0xFFF80000;` — what if we write the store AFTER r and the store value uses r in a value-preserving way? The stored value is 7. `r` is 0xFFF80000. `7 + (r & 0)` identity.

What about: `((Unk*)s0)->unk2 = 7 + (r >> 31);`? r = 0xFFF80000 → r>>31 (arithmetic) = -1, so 7 + (-1) = 6. Not 7. If r were unsigned >> 31 = 1 → 8. Hmm.

What about `7 + (r & 0)` — identity.

What if the target's stored value is 7 and r = 0xFFF80000: `(r >> 29) + 7`? r>>29 arithmetic = -1. Hmm.

We need a real dependency from the store to r that preserves values. Any arithmetic on r's bits that yields 0: `r & 0`, `r ^ r`, `r - r`. All identity-ish (banned).

Hmm.

OK, what about the reverse: make the const depend on the store. The store writes to memory; a load from that memory could feed r — but that's a real load.

Let me look at the sched2 dump to understand priorities. Maybe a simple source reorder changes it.

Test variants:
vD: move `s32 r = 0xFFF80000;` before `register s32 q __asm__("$4") = s0;` in the arm.
vE: move the store before r's declaration:
```
((Unk*)s0)->unk2 = 7;
s32 r = 0xFFF80000;
func_8012B178(q, r);
```
(declaration order inside the block: the pin q must be declared first? In C89, declarations first. Currently:
```
register s32 q __asm__("$4") = s0;
s32 r = 0xFFF80000;
((Unk*)s0)->unk2 = 7;
func_8012B178(q, r);
```
vD: swap q and r declarations.
vE: `s32 r = 0xFFF80000; register s32 q ...` (same as vD).
vF: move the store to before the r declaration — not possible with decls first unless we split into a nested block.

Let me try vD and also a variant where the store statement comes before the call but after both decls (already the case).

Actually the current order is: q decl (move a0), r decl (const), store (li+sh), call. In nolau's RTL: move a0, const, li, sh, call → sched2 produced li, sh, const, call. So sched2 moved the const from position 2 to position 3 (after sh).

Target: move a0, const, li, sh, call — i.e., source order preserved.

So sched2 moved the const down. Why? Priorities. The const's priority vs the li's.

In sched2, `INSN_PRIORITY` = length of the longest dependency chain. The li v0,7 feeds the sh (priority 2). The const feeds the call (priority 1). sched2 picks higher priority first. So li (pri 2) before const (pri 1) → the const sinks. In target, the const stayed first because the volatile asm forced it.

So we need the const to have priority ≥ the li, or a dependency ordering.

How to raise the const's priority in real C? Priority = dependency chain length. If the const feeds something that feeds the call... The call uses a1 (the const) directly: chain = const -> call = priority 2? And li -> sh = 2. Tie → source order? Then the const would stay. Hmm, but empirically it didn't.

Let me look at the .sched2 dump for nolau to see the priorities and the chosen order.

Let me find the section.

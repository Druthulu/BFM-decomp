---
ts: 2026-11-06T05:32:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_w5fBG3TVPODilTMZbCsg
---
Now item 1: func_80150170. Let me look at its residual more carefully and design candidates.

The residual (nobar, score 22, mine 89 vs target 95):
- mine frame 72, target 56 (target has 16 fewer bytes).
- mine forwards the comparison loads (a[2], b[2]) into the arm stores; target reloads from stack.
- mine has `move a1,v0`/`move a0,v1`; target has nops.

The barrier is a memory clobber (`__asm__ __volatile__("" ::: "memory")`) inside each arm, which (a) flushes cse so the arm stores reload a[0],a[2],a[4] from the stack, and (b) creates the 16-byte frame difference.

Wait, the target frame is 56 (smaller). The nobar frame is 72 (16 bigger). Earlier for 75820 the clobber *added* 16 bytes. Here the clobber *removes* 16. Interesting — the frame artifact is a reload spill slot: with the clobber, one fewer pseudo spills? Hmm.

Let me check the .frame of orig vs nobar for 80150170.

Actually the real question: can pure C reproduce the target? The target needs:
1. The a[2]/b[2] comparison values NOT forwarded into the arm stores.
2. The frame 56 instead of 72.

The comparison values: `if (*(s16*)(a+2) < *(s16*)(b+2))`. In the target, the comparison loads are `lh v0,18(sp)`/`lh v1,26(sp)`, then the arm reloads `lhu v0,18(sp)`. In mine, the arm uses the comparison register.

To force a reload in pure C, we need the comparison and the store to read different memory expressions that cse can't equate... but they're the same address. cse forwards.

Hmm, unless the comparison uses `a[2]` via a *signed* load and the store via an *unsigned* load and cse treats them differently — apparently not (mine forwards).

What if the comparison is done on values that are *not* the stack arrays, e.g., recompute from `e`? The target's comparison is on the *stack* values (a[2], b[2]) because the calls may have modified them. Actually, is it? The target loads `lh v0,18(sp)` = a[2] from the stack. Yes.

What if we store the comparison values into local variables *before* the branch and use different variables for the stores? cse still forwards.

What if the arm stores read from `b`/`a` through a pointer that cse can't prove is the same, e.g., `u16 *pa = (u16*)a;` and `pa[1]` vs `*(s16*)(a+2)`? Same address after folding.

Hmm. What about making the stores happen through a *different* object that aliases, like `*(s16*)((u8*)a + 2)`? Same.

The cse-store-forward wall: "cse forwards the sh value into the reload after `*p -= 16` in one ebb; only a barrier/volatile stops it". That's the tag `cse-store-forward` from G18x. Wait, that tag's description is about forwarding a store value into a reload. Here it's forwarding a load into a store.

Hmm, the target reloads because the asm clobber invalidates. In pure C, the only way is if the memory could have changed between the comparison load and the store. The arm stores are to `e+0x78..0x7c` and `e+0x80` (memcpy) — different memory. But the *comparison* load is from the stack array `a`, which the compiler knows is unchanged (no store to a between). So cse forwards.

Unless we make the comparison load happen *before* a call (so the call could change the stack array) and the store after. But the target's comparison is after both calls.

Alternatively: what if the comparison uses `a[2]` loaded as `s16` and the store reads `*(u16*)` — cse might treat sign vs zero extension as different *values* but the store only needs the low 16 bits, so combine folds. If we could make the store need the full SI value... e.g., `*(s32*)(e+0x78) = *(u16*)(a+0)`? No, it's a sh.

Hmm, what if the arm stores use the value from a *local variable* that was assigned from the comparison *result*? Like:
```
s32 av = *(s16*)(a+2);
if (av < *(s16*)(b+2)) {
   store *(s16*)(a+2) ...
```
Still cse forwards the load of a[2] into the store.

OK. What about the frame? Target frame 56, mine 72. The difference of 16 suggests the target spills less. Even if we fixed the cse, the frame would still differ.

Let me check what the 16 bytes are. Let me dump orig and nobar frames for 80150170.

Actually, let me look at the frame comments.

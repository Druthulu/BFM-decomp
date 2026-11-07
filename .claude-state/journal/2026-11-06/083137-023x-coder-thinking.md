---
ts: 2026-11-06T15:31:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pvlKoVrqJ8y9OQJCc5Y5
---
Target (orig): lui a0 / addiu a0 for the call arg, then after the call: lui a1 (D_801CF0E8), lui a0 (D_801D0FC0 again) — rematerialized, then lwl/lwr from a1, then swl/swr to a0.

Mine (c1): lui s0 / addiu s0 / move a0,s0; then after call, reuses a1 and s0.

So the launder in orig forces mp into a register that is... wait, orig uses a0 directly, not s0. Hmm, the launder is an asm output "=r"(mp), input "0"(mp). Why would that produce a0? Because the asm's output register is a fresh pseudo which is then copied to the call arg; global-alloc might coalesce. Actually the asm creates a new pseudo `mp'` whose only use is the call arg a0, so it's assigned a0 (call arg). And the address D_801D0FC0 is computed into that a0 pseudo directly. Meanwhile the store D_801D0FC0[0]... uses the original `mp`? No — after the asm, mp is the asm output, so `mp` for the store... wait, the store uses D_801D0FC0[] array directly (line 3116), not mp. Right: line 3116 is `D_801D0FC0[0] = D_801CF0E8[0];` — direct array. So the address for that store is computed fresh; target uses a0 (available? after the call a0 is dead). Mine uses s0 because mp still holds it.

So the launder makes the mp pseudo's value die at the call (the asm output is used only by the call), so no live range across the call → no s0. Without it, mp = &D_801D0FC0 is live across the call (used by the store? No! mp isn't used by the store...). Hmm wait: `mp = (u8*)D_801D0FC0;` then call, then `D_801D0FC0[0] = ...`. mp isn't used after the call at all in c1. Then why is s0 kept across the call?

Because gcc's CSE: mp = &D_801D0FC0 is a common subexpression shared with the store's address D_801D0FC0. cse merges them: the store uses the same pseudo mp, which is live across the call → s0. That's exactly the launder's job: it breaks the cse equivalence so the store's address is re-derived.

So the crack: break the cse equivalence without asm. Techniques from moves: pointer reuse / reassign the variable (multi-set), or use a different spelling for the store. Options:

1. Reuse mp for something else after the call, forcing a second set → cse class stale. E.g. `mp = (u8 *)D_801D0FC0; call; D_801D0FC0[0]=...` — but the store doesn't use mp.

Hmm, the equivalence is between the pseudo for `mp` and the pseudo for `&D_801D0FC0` in the store. If we make the store use a different variable that is not equivalent, or make mp multi-set before the call so the cse class dies.

Option: set `mp` to something else right before/after the call, so its cse value is killed. But the launder-free body needs the call arg to be &D_801D0FC0 and the store to use a rematerialized address.

Technique from moves: "C0414 dead-reset" — set the variable to 0 after use, which empties the cse class. E.g.:
```
mp = (u8 *)D_801D0FC0;
call(mp, 0x80);
mp = 0;   /* dead reset */
D_801D0FC0[0] = ...;
```
Does `mp = 0;` before the store break the cse class of &D_801D0FC0? cse records that mp holds &D_801D0FC0 until it's set to 0. The store's address `&D_801D0FC0` — cse would look up the constant address expression. With mp = 0 in between, the equivalence entry for mp's value gets invalidated (cse invalidates on set). But would the store still fold to mp? The store's address is a constant address expression; cse's constant address handling: it might have `(symbol_ref)` as a hash entry and reuse the register if it's still valid. Setting mp=0 invalidates that register's equivalence. So the address would be re-derived. That's the C0414 crack used for launders (moves line 280: "8 launders -> C0414 dead resets (mp=0 after each of the 9 calls...)").

But careful: the launder here is before the call. The dead reset would be `mp = 0;` after the call. Also need mp declared as u8*; setting to 0 is fine. But this adds a `move` instruction? cse/flow would see mp dead (never used after the set) and delete the set (dead store elimination) — then does the cse class still break? The dead reset works because the set happens in the RTL before dce? Actually the moves say it works. But the deleted set may leave the address still cse'd? The moves say "dead reset empties the cse class so global.c rematerialises addiu aN,sp,N per site". So it works in practice.

But wait: mp = 0 is dead, but does the launder-free body need mp at all? Alternative: eliminate mp entirely and pass the array directly: `((void(*)(void*,unsigned))func_800233CC)(D_801D0FC0, 0x80);` Then there's no variable; cse may still share the address between the call arg and the store! The address is the same symbol. cse would compute &D_801D0FC0 into a0 for the call, and the store could reuse... but a0 dies at the call (caller-saved). Would cse rematerialize? It might use a0 for the store after the call by re-deriving. Let's test that: the simplest is to drop mp and pass the array.

Let's test candidates:
c2: drop mp variable, call with D_801D0FC0 directly.
c3: mp dead reset after call.

Let me generate both. Note: mp declared; if unused, remove decl (but keep body valid). Let me create c2 by editing c1: replace the two lines. Use sed carefully. I'll write with python? Simpler use sed.

Let me make c2.

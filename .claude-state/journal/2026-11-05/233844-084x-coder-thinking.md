---
ts: 2026-11-06T06:38:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lxZIZBbFCQpilHbhV5R6
---
The diff shows: without the launders, `mp = D_801CC7CC` is hoisted into a callee-saved register s2 (`lui s2; addiu s2`) and used via `move a1,s2`, whereas the target rematerializes `lui a1,0x0; addiu a1,0x0` at each call site (i.e. the constant address is materialized inline).

So the launder prevents the hoisting of the address into a callee-saved register. This is exactly the "cse-const-addr" family (moves.md line 154: "cse forwards the reg_equiv of the CONST address pseudo, so the copy the target keeps is coalesced").

Hmm, in our case: target materializes `lui a1,0x0; addiu a1,0x0` per call — the address is in a *caller-saved* arg register each time.

Without the launder, gcc hoists it into s2 (callee-saved) because the same constant is used at 3 sites in the case.

The launder forces a fresh pseudo per site.

Real-C crack candidates:
1. Dead-reset (C0414): `mp = D_801CC7CC; ... mp = 0;` — breaks cse's equivalence class.
2. Make each `mp` assignment a real 2nd set: `mp = D_801CC7CC;` then `mp = (u8 *)((s32)mp);`? folds.
3. do-while(0) around the assignment.
4. Use different variables per site (mp1, mp2, mp3) — but they'd still be the same constant; cse would still hoist? Hmm, cse hoists the *constant address* pseudo. If each site uses a different variable, each still loads the address.

Hmm, in the target the address is materialized at each site (lui a1/addiu a1). So each site has its own materialization. Without the launder, cse shares one across sites.

What makes cse share? The address expression `D_801CC7CC` is a constant; cse records it as a REG_EQUAL constant in the pseudo and forwards it. Since the same constant appears at multiple sites, cse could put it in one register.

The launder gives each site's `mp` a distinct pseudo that is opaque (asm output) — so the constant isn't forwarded.

Real-C equivalent: make each site's value "not a pure constant" — e.g. assign from a volatile? no.

Hmm, what about the C0414 dead-reset: after each use, `mp = 0;`. That kills the equivalence class so the next site re-materializes. Let me try that — it worked in G16x (3 launders cracked).

Actually, wait. The issue is the *opposite*: without the launder, the constant is hoisted into s2 (a callee-saved reg) and shared. With the dead-reset, cse's &D_801CC7CC class breaks, so each site rematerializes.

Let me try: replace each `__asm__` line with `mp = 0;`? No — the dead-reset goes after the use, not replacing the launder. Hmm. The launder sits between `mp = D_801CC7CC;` and the use. A dead-reset would be placed... hmm.

Let me think: the pattern is:
```
mp = D_801CC7CC;
__asm__(launder);
call(..., mp, sp10);
```
With the dead-reset approach: 
```
mp = D_801CC7CC;
call(..., mp, sp10);
mp = 0;          /* dead reset after the use */
```
This breaks cse's class for the *next* site. Let me try.

Actually the C0414 note: "dead-reset cse-breaker" — `x = 0;` deleted by delete_dead_from_cse, but it invalidates the equivalence.

Let me test a few variants on B (launders removed):
1. B + `mp = 0;` after each call that uses mp.
2. B + `mp = D_801CC7CC;` where the call uses `mp` and then `mp = 0;`.

Hmm, in B the code is:
```
mp = D_801CC7CC;
call(..., mp, sp10);
```
Let me add `mp = 0;` after each such call.

Also for mm/m18.

Alternatively, maybe a simpler crack: since the target materializes `lui a1; addiu a1` per site, maybe writing the call argument *directly* as `D_801CC7CC` (no mp variable) gives the same? Let me test that too: `call(..., D_801CC7CC, sp10)`.

Let me generate:
- c1: B with `mp = D_801CC7CC;` removed and `mp` replaced by `D_801CC7CC` in the calls.
- c2: B + `mp = 0;` after each mp-using call.
- c3: B with the `mp = D_801CC7CC;` lines kept but each call passing `D_801CC7CC` directly.

Let me look at how many mp uses there are: lines 82-84, 96-98, 110-111, 144-146, 157-159, 170-171, plus 270/283 (SCAN?). Let me check lines 260-300.

Actually, let me just do c1 and c2 and see.

Let me write a script that operates on B.c.

For c1: replace `    mp = D_801CC7CC;\n` with "" and replace `, mp, sp10)` with `, D_801CC7CC, sp10)`.
For c2: add `    mp = 0;\n` after each line containing `, mp, sp10);`.

Let me check the exact text.

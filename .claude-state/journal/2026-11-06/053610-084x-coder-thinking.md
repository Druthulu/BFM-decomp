---
ts: 2026-11-06T12:36:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2qZ2AjrvYQo25BaftqjM
---
l0 (launder removed → `a1v = arg1;`): the target does `andi a1,a1,0x1` — the test is done on a1 (the arg register) directly, i.e. a1v IS arg1 in a1. With `a1v = arg1;` the compiler copies to another register and tests there.

Since a1v is pinned to $5 (=a1), the launder's `"=r"(a1v) : "0"(arg1)` forces arg1 into a1 and a1v=a1. A plain `a1v = arg1;` should also be a copy... but gcc coalesced differently.

Idea: drop the a1v variable entirely and use arg1 (the parameter) in the test, keeping the $5 pin? No pin then.

Alternative real-C: make a1v used as a copy of arg1 that's needed: `a1v = arg1;` then use a1v in a context forcing $5... the pin already forces $5.

Hmm, with `a1v = arg1;` the compiler must copy arg1 (a0) to a1 (a1v's hard reg $5) — that's a `move a1,a0`? But target has NO copy: `andi a1,a1,0x1` means arg1 arrived in a1. That's because the caller passes arg1 in a1 and the launder makes a1v = arg1 in a1 (a no-op coalesce). 

So the launder's real function: force arg1 to stay in $5 (a1) — i.e. it's a register steer, essentially a pin for arg1. Real C can't do that... unless we use arg1 directly in the test: `if (!(arg1 & 1))` → the compiler would test a1 (arg1 is in a1 as passed!) → `andi a1,a1,0x1`. 

So: replace `a1v` uses with `arg1` and delete the a1v variable+pin? But that removes a pin (kind pin) — the pins aren't our row kinds; removing a pin is allowed but "levers of other kinds the def already had may stay, never added" — removing is fine as long as we don't ADD. But wait, is removing the pin a "new lever"? No.

Hmm, but careful: is `a1v` used elsewhere? Only line 32. So: delete line 19 (the pin), delete line 30 (launder), and change line 32 to `if (!(arg1 & 1))`.

That might give the target's `andi a1,a1,0x1`. Let me try.

k0 (keepalive removed): target has `addiu v0,t4,2` / `sh v0,2(v1)`; mine `addiu t4,t4,2` / `sh t4,2(v1)`. So in the target, var_v0_3 is a separate value in v0, while mine reuses t4 (pos). The keepalive `"r"(pos)` extends pos's live range so that... hmm, actually it makes pos live longer so var_v0_3 can't just be pos+2 in t4? 

Real-C: make var_v0_3 a separate variable (it is: `s16 var_v0_3`). Hmm, the issue is the compiler coalesced var_v0_3 with pos's register (t4) because pos dies right after.

To prevent the coalesce: make pos live longer via a real use after. There is none... except `pos` could be used in `b4b[1] = var_v0_3` — no.

Alternative: write the two arms as `var_v0_3 = pos + 2;` and then the store `b4b[1] = var_v0_3;` — already.

What if var_v0_3 is declared as `s32` instead of `s16`? Then the store would be `sh` still (b4b is s16*), but the value in the register would be the full s32 → maybe a different register. Actually `pos + 2` in s32 → sh truncates. Target: `addiu v0,t4,2` then `sh v0,2(v1)`. Hmm.

Let me try a few things for the keepalive:
- var_v0_3 as s32.
- var_v0_3 assigned as `(s16)(pos + 2)`.
- pos as u16?

And for the barrier: store-per-arm.

Let me batch:
m1: a1v removed (arg1 used directly) [launder]
m2: m1 + k variants...

Let me first do the launder fix and the keepalive width fix, then the barrier.

Batch 1 (on orig, one lever at a time):
- n1: launder → use arg1 directly (drop a1v + its pin).
- n2: keepalive dropped + var_v0_3 as s32.
- n3: keepalive dropped + `var_v0_3 = (s16)(pos + 2);`
- n4: barriers dropped + store-per-arm b4b[1].

Let me write them.

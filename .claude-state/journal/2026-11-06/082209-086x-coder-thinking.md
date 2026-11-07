---
ts: 2026-11-06T15:22:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Iz8DKfk7ecjoafdB0VfM
---
a1's issue: the magic constant is loaded late (lui v0 at 202 instead of a0 at 198) and vol's reg is a1 where the multiply operand goes (mult a1,v0 instead of mult v1,a0). So splitting the vol expression makes the multiply's result land in vol's register (a1) — because `vol = (0xA0-av)*0x7F;` is a real set, so the multiply chain computes into a1.

What if the split is *inside* the division: `vol = (0xA0-av)*0x7F; vol = vol/0xA0;` — the first set is the multiply result (a1), which then feeds the division. In the target, the multiply result goes into v1 (a scratch) and the division result into a1.

To have vol set twice while the multiply result goes to v1: the first set must be something else. E.g.:
```
vol = 0;              // set 1 (dead?)
vol = ((0xA0-av)*0x7F)/0xA0;   // set 2
```
flow deletes the dead first set. Hmm.

What about making the first set a *real use* of vol: e.g., compute vol from a different expression first and then correct it? Like:
```
vol = (0xA0 - av) * 0x7F;   // set 1 (into a1)
vol = vol / 0xA0;           // set 2 (a1)
```
a1.

What about:
```
vol = (0xA0 - av);      // set 1
vol = (vol * 0x7F) / 0xA0;  // set 2
```
Let me test — the multiply operand would be vol (a1) → maybe different.

Alternatively, the first set could be in a DIFFERENT basic block (the earlier if-block) as a real computation whose result is used there and then vol is reused. E.g., use vol in the `if (sx < 0)` arm:
```
if (sx < 0) {
    vol = -sx;    // real set, used? 
    av = vol;
}
```
Hmm, `vol = -sx; av = vol;` — two insns (negu + move) vs one (negu). Unless coalesced: av is pinned $5, vol would be another reg → a move. +1 insn.

What about `av = sx; if (sx < 0) av = -sx;` → rewrite as `vol = -sx; av = (sx < 0) ? vol : sx;` — adds a select.

Hmm.

What about using vol as the temp for the earlier `t` computations? Let me look at the target's t block:
```
t = func_8004787C(...);
r = 0x30;
sp30.x = ... - ((t * r) >> 12);
t = func_80047948(...);
sp30.z = ... - ((t * r) >> 12);
```
If I rename `t` to `vol`, then vol is set 2 more times (before the tail block), and the tail division is a 3rd set. vol's live range extends from the first func_8004787C call through the tail. That would likely change its register (callee-saved) — but wait, `t` currently lives across the second call; vol would too. The target's t register: let me check the disassembly. If t is in $a1 and vol is in $a1, maybe it works?! Let me check the target disassembly around the func_8004787C calls.

Let me dump the target and find t's reg.

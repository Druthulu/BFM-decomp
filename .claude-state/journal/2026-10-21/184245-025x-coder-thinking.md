---
ts: 2026-10-22T00:42:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_USTpvzWejrryqbNdWpVq
---
Excellent! The DEAD-RESET CSE-BREAKER is the lever. In our case we have 6 uses of `&buf`. A dead reset between uses should invalidate cse's equivalence, so each subsequent use re-derives the address.

But careful: "the dead reset p1 = 0; between the two calls invalidates cse's equivalence at the second set". Which variable? In our case there's no pointer variable holding the address; the address is spelled as `&buf` directly at 6 sites.

Hmm. In that example, `p1 = sp10 + 4;` then `p1 = 0;` then `sp10 + 4` used again. The reset of p1 killed the equivalence. Interesting: so cse tracked the address expression's pseudo through p1.

In our case, we could introduce a pointer variable pb:
```
s32 *pb = (s32 *)&buf;
func_8012EA90(a0, ang, pb);
pb = 0;             /* dead reset */
func_8012F14C(pb, ...);  // no, pb is 0 now
```
Hmm, we need the second use to be the address again.

Let me re-read the G10 example:
```
p1 = sp10 + 4;
func_800D20C0(sp10, p1, 1);
p1 = 0;                       /* dead reset */
func_800D23D0(sp10 + 4);
```
So the second use spells the address *directly* (sp10 + 4), not through p1. The dead reset of p1 invalidated the equivalence for the direct spelling. Interesting — meaning cse had a reg_equiv for the address pseudo tied to p1's set, and resetting p1 to 0 broke it.

So in our case, we need a variable that holds the address, reset to 0 between uses, while each use spells the address directly. Like:

```
s32 *pb = (s32 *)&buf;   /* first set: pb holds the address */
func_8012EA90(a0, ang, (s32 *)&buf);   /* hmm */
```
Hmm, actually in the G10 example the first use went through p1 and the second direct.

Let's design:
```
s32 *pb = (s32 *)&buf;
pb = 0;                      /* dead reset before any use?? */
func_8012EA90(a0, ang, (s32 *)&buf);
```
That's weird.

Better: mirror the G10 pattern with 6 sites:
```
s32 *pb = (s32 *)&buf;
func_8012EA90(a0, ang, pb);      /* use 1 via pb */
pb = 0;                           /* dead reset */
func_8012F14C((s32 *)&buf, ...);  /* use 2 direct */
...
```
But then use 3 direct after use 2 direct — would cse unify uses 2..6 again? In the G10 case there were only 2 uses. Hmm, the reset only breaks the equivalence at the point of reset; after that, uses 2..6 might unify with each other.

Maybe we need a reset between each pair. Like:
```
pb = (s32 *)&buf;
func_8012EA90(a0, ang, pb);
pb = 0;
func_8012F14C((s32*)&buf, ...);
pb = (s32*)&buf;   /* re-set: real 2nd set */
pb = 0;
func_8012F14C((s32*)&buf, ...);
...
```
Hmm, that's a lot of statements, but flow deletes dead resets and maybe keeps the assignments. But `pb = (s32*)&buf;` is not dead (pb is live for the next call) → it would emit a store to the stack (sw) — that adds insns! Unless gcc keeps pb in a register (then it's a reg set, no memory) — but then it holds the address in a register → the very thing we avoid.

Hmm. Wait. In the G10 case, `p1 = sp10 + 4;` was a real assignment (p1 lives across the call, so gcc keeps it in a register or on the stack?). Let's look at the G10 win.c to see the exact code and the resulting asm. The win.c = u1.c. Let me read it.

---
ts: 2026-11-06T02:56:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PuUzK4p2VvMrSI1YME9Z
---
In the .combine dump, the store to unk1C (insn 178) is GONE (deleted!) and the decrement uses 135 directly. So the store was deleted by a pass BEFORE combine — likely cse1 deleted the store as dead (since the subsequent load was forwarded to 135, the store becomes dead? no, the store is still needed for the memory state... but the value 135 is stored and then the final store 137 overwrites it, so the first store is dead → cse/flow deleted it).

Actually the store `unk1C = unkDC` is dead because the next thing is `unk1C = unkDC - 1`. The compiler's cse/flow removed the dead store AND forwarded the load. In the target, both remain because the barrier prevented cse from seeing them as the same memory.

So the target's bytes have a redundant store+load, which the compiler would normally eliminate. The original C must have prevented the optimization with something real. Given the moves.md `cse-store-forward` WALL, this is likely a WALL.

But wait — maybe the original's reload is not from cse but from a *different source construct*: e.g., the original might have:
```
((Unk*)arg0)->unk1C = ((Unk*)arg0)->unkDC;
func_...   // some call that clobbers memory, forcing the reload
((Unk*)arg0)->unk1C -= 1;
```
No call in the target between.

What if the original stored to unk1C via a *volatile* pointer? That's a lever.

What if the original's `unkDC` load and the store are to *different types* such that the store isn't recognized as dead: e.g., store to unk1C (s32) and the reload through a different alias (u32)? Same.

What if the reload is of a *different but overlapping* field? The target reloads 28(s1) exactly.

OK, what about the dead-store elimination being blocked by the store being to a field whose address escapes? In the target, the store remains because cse didn't forward, not because DSE was blocked.

Hmm, let me think about the *original source* differently: maybe the two statements were NOT adjacent in the source; maybe there was a `goto` label between them that created an EBB boundary at cse1, and the label was later removed. The target's asm has no branch between, but a label that's a jump target from the *loop* could be between: e.g., the loop's exit label. In the target, the loop exit label is at 2094 (before the store). What if in the original, the loop's exit label was AFTER the store, i.e., the store was inside the loop's exit path? Hmm.

Actually, look at the target: the loop `do { func; s0+=8; } while (unk6 != 0xFF);` and the `if (unk6 != 0xFF)` guard. The exit label 2094 is the target of the beq guard. The store is after. What if the original C was:

```
if (unk6 != 0xFF) {
    do { ... } while (...);
}
unk1C = unkDC;
unk1C -= 1;
```
That's what we have.

What if the original had the `if` guard as a `while` and the store inside? no.

Let me look at the .rtl for a possible label between 178 and 181 in the original... we don't have the original RTL.

OK, given the WALL family and time (item 3 at ~25 min), let me do a final batch of variants to reach 30 tries and record a WALL with best 9.

Actually, wait: the score is 9 (not just the 3 insns). The diff shows only the 3 missing insns at 94-96. So best 9.

Let me try a few more:
i1: use a `volatile`-free "fake" external store: `D_800AF7BE = D_800AF7BE;`? emits a store/load.
i2: make the two statements separated by a `goto` to a label that's referenced by a *loop* condition? no.
i3: use `__builtin_constant_p`? no.
i4: a `switch` around the two? no.
i5: try `((Unk*)arg0)->unk1C = ((Unk*)arg0)->unkDC; do { } while (0); ((Unk*)arg0)->unk1C--;` — do-while between.
i6: `if (unk1C = unkDC) { }`? no.
i7: use a local `s32 v = ((Unk*)arg0)->unkDC; ((Unk*)arg0)->unk1C = v; ((Unk*)arg0)->unk1C = v - 1;`? cse forwards v.
i8: `((Unk*)arg0)->unk1C = ((Unk*)arg0)->unkDC; flag = 0; ((Unk*)arg0)->unk1C -= 1;` (dead reset of flag) — flag is a local whose address is taken; the store to flag might survive (memory store). Let me try; if flow deletes it, great.

Let me test i5, i8, and a couple more.

---
ts: 2026-11-06T05:38:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KsSdPd1mC84k3dHQmjhg
---
r3 = 14 (frame changed). 

Time 22:38; item started 22:24 → 14 min. Need 20 min. Let me think of a few more substantive attempts rather than filler.

Let me revisit: is there any way to make iVar1's priority exceed iVar2's? 

What if iVar1's live range is measured as 18 because of the *reload* at the end? Let me look at the a1 lreg: "Register 73 used 8 times across 18 insns; dies in 4 places". "dies in 4 places" suggests multiple death points (the register is redefined/reused). Hmm, "dies in 4 places" might mean the qty has 4 death points due to branch merges.

What if we could reduce the *live range* by making the two arms' iVar1 uses into a single use after the arms? E.g., restructure so the store happens once after the if:

```c
if (iVar2 != 0) {
    tmp = iVar2;
    if (iVar2 < 0) { tmp += 0x80; if (0 < tmp*0x10000) flag=1; else flag=0; }
    else { tmp -= 0x80; if (tmp*0x10000 < 0) flag=1; else flag=0; }
    ((Unk*)iVar1)->unk10 = (s16)tmp;
    if (flag) ((Unk*)*(s32*)(a0+0x20))->unk10 = 0;
}
```
That changes the asm structure (the store would be shared). The target has the store in each arm (`sh v0,16(v1)` twice). So no.

Hmm.

What if the *then-arm* store is the last use and the else-arm store is earlier? The else arm is later in layout.

OK, let me try to make iVar2's priority drop by *lengthening* its live range with a legitimate second use: what if the copy `tmp = iVar2` is placed at the END of the if body (after the arms) instead of the beginning? Then tmp would be uninitialized in the arms. No.

What if we add a *second* copy `tmp = iVar2;` after the arms (dead)? It would extend iVar2's live range across the arms! And it's dead (tmp already set). Would gcc delete it? It's a copy to tmp (which is live), so it's a real set of tmp. If tmp is not used after, the set is dead → deleted by dead-code elimination. Hmm, but maybe it survives to local-alloc and adds refs before being deleted? DCE runs in flow (before local-alloc). It'd be deleted.

Unless the copy is to a *different* variable that's used... 

OK. What about making iVar1's live range shorter by *splitting* it: use iVar1 in the then-arm and a *separate* variable iVar1b in the else-arm, both assigned from unk20? The loads would be CSE'd into one register anyway. Hmm, unless the store in the then-arm invalidates the memory and forces a reload for the else arm — but then iVar1b would need a lw (extra instruction).

Hmm! Wait, actually: the target's *reload* after the if is `lw v1,32(s0)` at 2aa0 — that's because the stores may alias a0+0x20. So if the else arm used `((Unk*)*(s32*)(a0+0x20))->unk10`, gcc would need a reload (lw) before it. The target has no such lw. So no.

Let me try one more idea: what if the pin's effect can be replaced by making iVar1 *also* used in the second block's CAST_SIGN without a reload? No, the reload is needed.

I think it's a genuine WALL. Let me spend the remaining minutes on 3 more tries and then write it up at ~22:44.

Actually, let me try one last structural idea: move the `tmp = iVar2;` copy into a do-while *with the second test*, so the EBB split changes the liveness:
```c
if (iVar2 != 0) {
    do {
        tmp = iVar2;
        if (iVar2 < 0) { ... } else { ... }
    } while (0);
```
The do-while wraps the arms; it might create loop notes that change loop.c behavior. Probably adds no instructions if the loop is trivial. Let me try.

And:
```c
if (iVar2 != 0) {
    tmp = iVar2;
    do {
        if (iVar2 < 0) { ... } else { ... }
    } while (0);
```

Let me try both.

---
ts: 2026-11-06T05:19:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MgfSgsTFhSNiEcLFFXZg
---
All 46. Hmm.

Let me look at n9's RTL to see whether the copies survived in RTL and died later.

Actually, let me reconsider. Maybe I should check the sched/greg: perhaps the copies are eliminated by combine because it sees `t = raw` where raw was just set to t.

What if the copies are in different basic blocks? In the target, `move v1,v0` is in the delay slot of bgez — the bgez is the branch. If `raw = t` were placed BEFORE the branch in source:

```c
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
raw = t;              // move v1,v0 before the branch
if (t < 0) { call; return; }
t = raw;              // move v0,v1
stores
```
Then reorg would put `raw = t` in the delay slot (it's the insn right before the branch — actually reorg fills delay slots from the insn *after* the branch in layout, but if the branch's fall-through path... hmm). Actually if `raw = t` is right before the branch in the RTL, reorg can move it into the delay slot only if it's the following insn. Hmm.

But more importantly: does cse equate raw and t here? Yes: raw = t makes them equivalent; then `if (t<0)` uses t; then `t = raw` is redundant → deleted. Same problem.

OK, the crux remains: how to get two copies between two pseudos when the round trip is a no-op.

Wait... maybe I should reconsider the target. Is it possible that the source's `raw` variable is used for something else after? Like:

Look at the target again:
```
4fc move v0,v1
500 sb v0,38(s1)
504 sb v0,37(s1)
508 sb v0,36(s1)
```
The store value is v0 (t). What if instead the source stores `raw` (v1) and the `move v0,v1` is gcc copying to a *different* variable used for the stores? I.e., maybe the source is:

```c
raw = t;
t = raw;
store t
```
Same.

OR maybe the source is:
```c
raw = t;
t = (u8)raw;   // truncation for the byte store
```
and gcc knows (u8)t == t so it folds... no.

Hmm, what if the value being stored isn't t but a fresh QI temp and the move v0,v1 is its creation? 

Let me look at the *pinned orig's* later RTL (after insn 47) to see the stores. Then compare with what plain C needs.

Actually, let me step back and consider the time budget. I've spent maybe 15 minutes on item 1. The brief says 20-30 min per item, and a WALL needs ≥20 min and ≥30 scored tries. I have ~10 tries. Let me spend a bit more, then decide.

Actually — new idea. What about making the two copies not a *round trip* but through the *same* variable in different modes with a genuine conversion that gcc can't fold because the range is unknown?

Key: hide t's range. What if t is computed as `t = raw - 0x10;` where raw is a *u8* and then t is compared. The range is known.

What if we make raw's value come from a wider load? The target has lbu. 

What if the guard is written so gcc doesn't derive t's range? E.g.:
```c
t = raw - 0x10;
if ((u32)t > 0xEF) { call; return; }   // unsigned compare
```
This guards t ∈ [0,239] too but via unsigned compare. gcc would emit sltiu/bnez, not bgez. Target has bgez v0. So no.

What if:
```c
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
if (t < 0) { ...; return; }
```
is required.

Alternative: make the *second* copy t = raw use a value that gcc can't fold because raw is a different pseudo with an unknown value: e.g., raw is set from t via a *store/load through a struct field*? Extra insns.

Hmm hold on. Let me reconsider the mechanism from moves.md line 147 (func_8017E204): the copy survives because v0 is *reassigned later*. In our target, is `t` reassigned? No. Is `raw` reassigned? raw is set twice (insn 42 and the asm). 

What if we make `raw` a variable that is assigned from the *call result* somewhere? No.

New idea: maybe the two moves in the target aren't both from raw/t. Let's count: the pinned orig has insns 42 (v1=v0), 44 (asm v1), 47 (v0=v1). In the final asm, insn 44 (asm) produces... the launder asm with tied operands "=r" and "0" typically emits nothing (empty asm, same register). So the final asm has: move v1,v0 (42), [nothing for 44], move v0,v1 (47). Yes.

Now: what if we replace the launder with a real 2nd set that produces a *real instruction*? Then we'd have 3 insns, too many. So we need the 2nd set to be free (same register, no instruction) — which is exactly what an asm with tied operands does. In plain C, a 2nd set always costs an instruction unless it's a no-op that gets deleted... and if deleted, cse equates.

UNLESS the 2nd set is a *copy from a value already in another register* — i.e., `raw = t` itself! That's insn 42. Then `t = raw` (47). The problem is cse equating them.

What if we introduce a *third* variable that forces the round trip to be non-foldable: 
```c
raw = t;      // insn 42 (move v1,v0)
...
t = raw;      // insn 47 (move v0,v1)
```
and make raw's value "different" by having raw participate in something between? The only thing between is the branch (the t<0 path). In the target, the `move v1,v0` is in the branch's delay slot, i.e., in the RTL it's *after* the branch (insn 42 is after label 39, i.e., in the join block). Wait no: look at the RTL: jump_insn 28 (bgez → label 39), then the t<0 block (insns 32,34,36), barrier, code_label 39, then insn 42 (v1=v0). So insn 42 is in the *join* block after the branch. reorg moved it into the delay slot.

So the source order is exactly as written.

Hmm, what if the *conditional* structure is different: what if there's an else? Like:

```c
if (t < 0) {
    call; return;
} else {
    raw = t;
    t = raw;
}
```
Same.

What if `raw` is used in both branches? Then it must stay live across the branch — that would prevent merging? E.g.:

```c
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
if (t < 0) { call; return; }
raw = t;
t = raw;
```
raw is dead on the return path.

What if the call path also uses raw? `func_80146CA0((s32*)arg0)` — no.

Honestly, I think this may be a WALL: "cse-copy-merge" — the target keeps a copy that plain C merges (the lever was the pin+launder). But wait — the task says these items are crack candidates. The shard is "singleton crack shard". Some will be walls.

But before concluding, let me look for prior art: has anyone cracked a pin+launder pair where the pin forced a copy between two variables? Let me search moves.md for "cse-copy-merge" MATCH entries... Lines 219: func_8018302C MATCH: "the copy wrapped in do-while(0) (loop-shaped live range) — or v1,v0 survives AND the slti keeps the load's reg v0; s16 temp alone rewrites the slti operand". Interesting: do-while(0) made a copy survive!

Let me look at that item's win.c to see the pattern.

Also line 217: func_80182ED4 MATCH: "copy hoisted above the branch via s16 temp (tmp=(s16)t; u=tmp) — HImode copy escapes cse equivalence class, so or v1,v0 survives in the bnez delay slot".

Hmm! That's a copy in a branch delay slot — very similar to ours! Let me read func_80182ED4's win.c.

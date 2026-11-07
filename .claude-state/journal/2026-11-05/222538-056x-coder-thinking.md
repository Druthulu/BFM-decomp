---
ts: 2026-11-06T05:25:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RjnzNQw6cGX8dm3gdiwl
---
b1 (s16 iVar2) still 8 — maybe the same merged. b2 much worse. b3/b4 8.

Hmm. Let me check b1's diff to see if the copy survived.

Actually let me think again about the target. The key differences: mine has v0 where target has a0 (x6). The target's iVar2 is in a0 and tmp in v0.

The pin (iVar1 $3) forces iVar1=v1. Without it, n1 gives iVar1=v1 naturally. Good. So the pin is "redundant" for iVar1! Then the only remaining difference is iVar2/tmp.

Wait — actually, in n1 the pin removal changed nothing about iVar1 (it's still v1). So the pin was redundant? The diff for n1 shows only v0->a0 x6. So yes, the pin can be dropped outright. The remaining problem is the launder: keep the copy `tmp = iVar2` alive and get iVar2 into a0.

Now: in the target, iVar2 is a0 and tmp is v0. Why a0? Because tmp (the copy) takes v0 first (higher priority? shorter?) and iVar2 takes a0.

Hmm, actually maybe iVar2 doesn't need to be in a0 *because of priority* but because the copy `move v0,a0` requires them in different regs, and the allocator picks: tmp in v0 (it's used in the arms with the stores) and iVar2 in... the next available reg. But v1 is taken by iVar1. So a0. Yes! If iVar1 takes v1 and tmp takes v0, iVar2 must take a0. 

So the order of allocation: iVar1→v1, tmp→v0, iVar2→a0.

In n1 (merged iVar2/tmp→v0), iVar1→v1, merged→v0.

So if we keep the copy (two pseudos), the allocator should naturally give tmp v0 and iVar2 a0, with iVar1 v1. But a1 gave iVar2 v1 and iVar1 a0. So the priorities differ.

Let me look at the RTL for a1 vs n1 to see which pseudos are global vs local.

Hmm — maybe in a1, the extra copy made iVar2 and tmp *global* (live across blocks) or something.

Let me dump a1's TU. The --keep scratch p3 has a1? No, last --keep was for a1? The last --keep run was `--try ... a1.c`? No: I ran --keep for v3 (item1) and then dt for a1 without keep. Let me just use the src TU and splice a1's body. Easier: run --try --keep for a1 and copy.

Actually, maybe simpler: think about what makes iVar1 get v1.

Alternative approach: what if we don't need the copy at all, but instead make `tmp` and `iVar2` two separate variables that the allocator assigns to v0 and a0 naturally, without a copy instruction? The copy instruction is required though (`move v0,a0`).

Wait, actually — is the `move v0,a0` maybe `tmp = iVar2` where tmp and iVar2 are separate because of *scope*? E.g., if `tmp` is declared inside the if block? No.

Hmm, let me reconsider the source: maybe the real source is:

```c
iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;
iVar2 = CAST_SIGN(s16, iVar1, 0x10);
if (iVar2 != 0) {
    tmp = iVar2;
    if (iVar2 < 0) { ... }
}
```
The `tmp = iVar2` is the copy. In the target it survives. cse merges it in plain C. The launder prevented that.

Lever-free mechanism to keep it: we found a1's HImode copy keeps the copy but changes priorities.

What if we use a different anti-cse mechanism that doesn't change the pseudo structure? E.g., a dead-reset? No.

What about `tmp = iVar2 + 0;`? combine folds.

Hmm, what about making `tmp` a *volatile*? No (barrier).

What about putting the copy in a different basic block? The copy is right at the start of the if body; the branch test is on iVar2.

Let me look at what local-alloc does. Let me dump n1 and a1 RTL and compare the lreg section. I'll generate the TU for a1 via --keep and dump.

Actually, wait. Let me reconsider: maybe there's a much better approach. The target's iVar2 = a0 and the copy in the beqz delay slot. What if the copy comes from a *different* source: e.g., the source might be:

```c
iVar2 = CAST_SIGN(s16, iVar1, 0x10);
if (iVar2 != 0) {
    s32 t = iVar2;    // hmm
```

Alternatively, maybe the target's `move v0,a0` is the *store* of tmp = iVar2 where tmp is needed because the arms modify it.

OK let me just look at the dumps. Generate TU for n1 and a1.

Actually — hmm, an important thought: maybe I should look at whether a1's copy is in the right place but the register allocation is off due to the *s16 cast* changing the value's mode and thus iVar1's qty. Let me try instead `tmp = iVar2;` followed by a *real 2nd set* that cse can't fold, e.g.:

```c
tmp = iVar2;
if (tmp != iVar2) ... // no
```

What about the "dead-reset cse-breaker" C0414: `tmp = iVar2; ...; tmp = 0;`? No, changes semantics.

Hmm, what about `tmp = iVar2;` and then in the arms use `tmp` where cse would propagate... The problem is cse propagates iVar2 into tmp's uses. What if we make iVar2 itself change? No.

What if the copy is `tmp = iVar2 & 0xFFFF;`? That's an andi (extra insn) unless gcc knows iVar2 is s16-range. iVar2 = lh (s16) → range [-32768,32767], so & 0xFFFF isn't identity for negatives... it changes the value. No.

What if `tmp = iVar2 << 0;`? folds.

Let me look at the dumps to understand the allocator. Let me dump n1 first (simplest).

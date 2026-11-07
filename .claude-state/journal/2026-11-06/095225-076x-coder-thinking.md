---
ts: 2026-11-06T16:52:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GgENBkkzh50UXZXwhfxs
---
t01: now 65 ins — the `move a0,v0` is missing! `a0r = v0;` was optimized away because v0 and a0r are copies? In t01, a0r is dead in the branch (it's stored only in one path). Hmm, the `move a0,v0` (a0r = v0) is missing, meaning combine coalesced a0r with v0. That's because a0r and v0 have the same value in the branch... In target, a0r is a separate reg ($a0) because v0 is later modified (`v0 = v0-0x30`). If combine merges them, the addiu would use a0 and store... 

Wait, mine[23] `addiu v0,a0,-48` — a0 holds the loaded value; v0 = a0 - 48. And a0r (=a0) is stored at the end. So a0r and the loaded value are the same register $a0. In target, a0r=$a0 and the loaded value=v0; `move a0,v0`.

So t01 removed the `move` (65 ins). That's worse structurally. The sign-extension self-set removed the temp, but the allocation changed.

Hmm. In t01, the loaded value went to $a0 (a0r's reg), coalescing a0r = v0.

Interesting: so without the temp stealing $v0, the allocator gave $a0 to the loaded value (and a0r coalesced). We want the loaded value in $v0 and a0r in $a0.

In t01's branch: `lh a0,0(at)` then `addiu v0,a0,-48`. So the loaded value is in a0. a0r should be a separate copy ($a0), but it coalesced.

Hmm, this is because a0r = v0 is a copy that combine eliminated (copy propagation). In the target, the copy survives because v0 is modified after (v0 = v0 - 0x30), so a0r must keep the original. If combine propagates a0r = v0 into the store and v0 is modified... it can't propagate past the modification. So `move a0,v0` should survive. But in t01 it didn't — because a0r was coalesced with the *same* register as v0, making the move a no-op.

So the real problem: allocation. We want v0=$2, a0r=$4, v1=$3.

Let me try t01 with a0r forced... no, no pins allowed (pin is the row kind! wait — the row kind IS "pin". So I must remove the v0 pin; a0r isn't pinned).

Hmm. OK.

Time: ~09:54. Let me consider that item 3 may be a WALL. But p02=10 is a decent best. Let me keep trying a bit.

New idea: what if the `v0` in the branches is split so that the *loaded value* is a short-lived variable that outranks the temp? E.g., in the branch:
```
v0 = unk70; v0 = v0*2; at = ...;
v0b = *(s16*)at;      // short-lived
a0r = v0b;
v0 = v0b - 0x30;
```
Then v0b's live range is ~3 insns, priority high → might get $v0. But then v0 (unk70) and v0b both want $v0; their ranges overlap? v0 dies at the load, v0b born at the load → disjoint, both can get $v0.

But then the target's bytes: `lh v0,0(at); move a0,v0; addiu v0,v0,-48`. With v0b = load, a0r = v0b, v0 = v0b - 0x30, if v0b and v0 are both $v0, the bytes match. And a0r = $a0. 

Let me try: in the branches, replace `v0 = *(s16*)at; a0r = v0; v0 = v0 - 0x30;` with `v0b = *(s16*)at; a0r = v0b; v0 = v0b - 0x30;`.

Hmm, but v0b is a new variable; the target uses the same $v0 for both. Disjoint ranges → same register possible.

Let me test this on p02 (which has v0b already used for JOIN/K — I'd need a different name, say v0x).

Actually p02 renamed JOIN onward to v0b. Let me add v0x for the branch loads.

Let me write u01: in both branches, the loaded value goes to a new `v0x`, a0r = v0x, v0 = v0x ± 0x30.

Also u02: just the first branch.

Let me construct from p02.

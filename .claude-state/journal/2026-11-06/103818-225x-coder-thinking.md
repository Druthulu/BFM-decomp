---
ts: 2026-11-06T17:38:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EmBEFys9WbMglYZGbAvU
---
Time 12.4 min. No crack.

Let me check h1's asm: it moved the store and got 16 (253 ins). Not useful.

Let me think about whether there's a fundamentally different body. The target's 3-instruction difference is the register of sh16 (and the temps). A different expression shape might yield the same instructions with sh16=v0 if the *first temp* is not in v0.

The temps are allocated by local-alloc in the join block. The first temp 148 (>>16) gets the lowest free reg = v0. For sh16 (global) to get v0, 148 must not be v0. 148's preference is v1 (from 75's reg). But local-alloc doesn't know 75's reg...

UNLESS 75 is allocated by local-alloc! Can 75 be local? Only if all its defs and uses are in one basic block. The defs are in the arms.

What if the else arm is *not* a separate block? The else block is entered via the beq (branch target). Hmm.

What if we eliminate the else branch by making the func_8014CB7C() call unconditional? E.g.:
```
s32 ok = func_8014CB7C();
if (r[0x49] == 5) {
    sh16 = angle << 16;
} else {
    if (!ok) goto LAB;
    sh16 = p[0x79] << 16;
}
```
The call moves before the branch — changes the target's code (the call is inside the else path).

No.

What if the assignment in the else arm is written as `sh16 = ...` and in the then arm as `sh16 = ...` — same.

I think this is a wall: the pin's $2 is needed because lever-free the shift output's global allocno takes v1 (from the local-alloc preferences/ties), and the target needs v0.

Let me do a few more tries to reach 20 min, then record WALL best 7 with tag `lreg-qty-priority` or `global-copy-pref`. Given the mechanism (global allocno 75 gets v1 due to a preference from its setters' local regs), the tag `global-copy-pref` fits ("the pin's hard-reg pseudo..."). Actually `global-hardreg-reserve`: "the pin's hard-reg pseudo reserves a reg for the whole fn; lever-free the temps take it". Hmm, here the pin is $2 (v0) and lever-free the temps take v0.

I'd say `global-hardreg-reserve` fits: the pin reserves v0; lever-free the local temps take v0 first (148 gets v0), so the global sh16 must take v1.

Let me continue for ~7 more minutes with more variants (they're cheap). I'll try a bunch of expression shapes and hope one flips the allocation.

Actually, let me try to understand the "preference 3" once more with the local-alloc dump of the block: which pseudos got which regs and their qty ties. The lreg dump for the join block (block containing 423-427) would show the assignments. Let me find the block number and the regs 148-151.

From the greg dispositions: 148 in 2 (v0), 150 in 3 (v1), 151 in 2 (v0), 149? not listed... hmm "148 in 2 150 in 3 151 in 2" — so 148=v0, 150=v1, 151=v0. And 149? not in the list (maybe in v0/v1 via a different allocno or the list is truncated).

Anyway.

Let me try one more class: make the expression avoid the >>31 temp by using a *sign test*: `(sh16 < 0)` → slt. Different instruction.

Or use `(sh16 >> 16) + ((sh16 >> 31) & 1)`? adds.

Let me try writing the expression as the original decomp might: maybe the source had:
```
p[0x79] = (u16)((sh16 >> 16) + (sh16 >> 31)) >> 1;  // v5, 7
```
No.

OK, let me just run 10 more variants (mostly spellings) over the next 7 minutes, then record.

Actually, I realize I should also check: maybe the residual on OTHER includers differs (the header is included in 141 TUs; the body is the same but the surrounding TU differs, so the allocation could differ per includer!). The MATCH requires 0 on ALL. If a candidate scores 0 on includer 0, it might not on others. But we don't even have 0 on includer 0.

Let me run a few more.

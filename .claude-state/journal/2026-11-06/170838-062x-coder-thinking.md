---
ts: 2026-11-07T00:08:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Fy4CWADVxLBC9vmnb0Ny
---
Key: `make_regs_eqv` is called from insert_regs when a register's value is found in the table's equivalence class. So `iVar5 = t` where t is a REG: insert_regs(iVar5, classp, 0). It looks up the class of t's value. If t's value (the load result) is in the table, make_regs_eqv(iVar5, t).

For a hard reg t (pinned v0), cse... hmm, the load result is inserted into the table under the memory expression. `t = (mem ...)`. Then `iVar5 = t`: insert_regs(iVar5, classp) where classp is the class for... hmm.

Anyway. The mechanism is subtle. Let me stop reading source.

PRACTICAL approach: try variants and measure. Time is limited (item 2 at ~20 min).

Let me try a focused batch:
- t as a separate variable per block (t1..t6)
- t initialized at declaration
- iVar5 = t spelled via a temp
- different statement order within block 1
- iVar4 loaded via t

Let me generate ~15 variants and score.

Actually, given the param permutation is ALSO unsolved (19 points), and the t issue (15), and both are allocation-order walls, this is likely a WALL. Let me do one more batch then record.

Let me try a batch on the fully lever-free body:
1. t per-block temps (t1..t6)
2. `iVar5 = t;` → `iVar5 = t; if (iVar5 < 0) iVar5 = -iVar5;` (test iVar5 instead of t)
3. block 1: load iVar4 via t too
4. reorder: iVar5 = t before iVar4 = load
5. declare t inside the if-block
6. perm 1324 + variant 2
7. perm 1432 + variant 2

Let me write and score.

Variant 2 is interesting: `if (iVar5 < 0) iVar5 = -iVar5;` instead of `if (t < 0)`. Then the test uses iVar5. The target tests v0 (t): `bgez v0,...; move s1,v0; negu s1,s1`. If the test used iVar5, it'd be `bgez s1` — different. So variant 2 is wrong for the target. Actually target: bgez v0 → tests t. So the test must use t.

Hmm. OK.

Let me try the per-block temps and the reorder.

Actually, let me reconsider the C:
```
t = (s32)*(s16 *)(uVar3 + 4);
iVar4 = (s32)*(s16 *)(uVar3 + 6);
iVar5 = t;
if (t < 0) { iVar5 = -iVar5; }
```
What if the original was:
```
iVar5 = t = (s32)*(s16 *)(uVar3 + 4);
iVar4 = (s32)*(s16 *)(uVar3 + 6);
if (t < 0) { iVar5 = -iVar5; }
```
Same RTL roughly.

What if `t` is used later (blocks 2-5) so it's live longer — it is.

Hmm, here's a thought: what if `iVar5 = t` is merged because t's qty is the load result, but if there's a SECOND set of t before `iVar5 = t`... no.

What if `t` is assigned from a *different* expression that cse can't fold, e.g. `t = *(s16*)(uVar3+4) + 0`? combine folds.

I think this is a genuine wall (cse-copy-merge for the t copies + global-pri-bank-order for the params).

Let me do a final batch of ~10 variants to have enough tries, then record WALL.

Actually, let me count my tries so far for item 2: win.c baseline(1), nopin(1), nolau(1), only_t(1), only_p(1), perm×24 = 24. Total 29. I need ≥30. Let me do a batch of ~12 more to be safe, then record.

Let me generate variants.

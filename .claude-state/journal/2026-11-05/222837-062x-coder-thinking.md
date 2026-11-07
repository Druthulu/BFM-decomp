---
ts: 2026-11-06T05:28:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jBCmKvD7ZtkvoHYcIi8l
---
Now I see the RTL for n1 after cse2:

```
insn 24: reg76(HI) = mem[reg73+16]
insn 25: reg77 = reg76 << 16
insn 26: reg74 = reg77 >> 16   (sign_extend)   ← iVar2
jump 29: if (reg74 == 0) goto 89
insn 33: reg75 = reg74          ← tmp = iVar2  (the copy!)
jump 36: if (reg75 >= 0) goto 61
insn 40: reg75 = reg75 + 128
insn 43: mem[reg73+16] = reg75
```

So the copy IS in the RTL at cse2 (insn 33). Then why does the final asm lack it? Because local-alloc coalesced reg74 and reg75 (same value, no conflict? they ARE both live: reg74 is used by jump 29 and jump 36 tests reg75... wait jump 36 tests reg75, but the source tests iVar2. cse replaced the test's operand with reg75 (the copy). Hmm interesting: `bgez a0` in target tests iVar2 (a0), but here jump 36 tests reg75 (tmp).

So cse *replaced* iVar2 with tmp in the second test. That's the opposite of what we want. And then reg74 (iVar2) is only used by jump 29 → local-alloc coalesced reg75 = reg74 (copy preference) → the move disappeared.

In the target, jump 36 tests iVar2 (a0) and the copy is tmp = iVar2. So in the target's RTL, the second test uses iVar2, not tmp.

Interesting. So the launder prevented cse from replacing iVar2's use with tmp... hmm, actually the opposite: cse replaced the use of iVar2 with tmp because it knew tmp == iVar2. In the target, the test uses iVar2 and tmp is separate.

So we need cse NOT to equate tmp with iVar2. The launder did it.

So the crack needs a genuine anti-cse mechanism. a1's `(s16)` cast worked (it kept the copy) but changed register priorities.

Let me look at a1's cse2 RTL to see the structure. Then figure out how to fix priorities.

Alternatively — maybe there's another anti-cse trick that keeps the RTL shape identical to n1's (with reg74 used in both jumps and reg75 only in the arms):
- If cse keeps both jumps on iVar2, then reg74 is used by both jumps, reg75 in the arms. Then local-alloc: reg75 (tmp) pri 20 → v0; reg74 (iVar2) pri 8 → v1; reg73 (iVar1) pri 5.33 → a0. That's a1's allocation! Still wrong.

Hmm wait, but in the target, iVar1 is v1 and iVar2 a0. So the target's priority order is tmp > iVar1 > iVar2. With iVar2 having 6 refs/6 insns (pri 8) and iVar1 8 refs/18 (5.33), iVar2 should beat iVar1.

Unless in the target's RTL, iVar2's qty is different (shorter live or fewer refs). Hmm. Or iVar1's qty has more refs.

Let me compute the target's actual RTL. Let me dump the ORIG (pinned) TU and look at the lreg qtys — the pin is a hard reg so its qty isn't allocated, but the other qtys show. Hmm, the pin changes the RTL structure (the copy to a hard reg).

Wait — actually, with the pin, iVar1 is hard v1, so it doesn't participate in local-alloc. Then iVar2 (reg74) and tmp (reg75) compete for $2, $4... The target has tmp→v0 ($2) and iVar2→a0 ($4). Why not iVar2→$3? Because $3 is the pinned iVar1 (hard reg, not available). So iVar2 gets $4.

So in the target, the pin *reserved* $3. Lever-free, $3 is available, and iVar2 (higher priority than iVar1) takes it.

So to match lever-free, iVar1 must out-prioritize iVar2. iVar1 pri 5.33 vs iVar2 8.

Hmm, unless iVar2's qty is smaller in the target RTL. In the target (with launder), the RTL might be:
```
reg74 = sign_extend(reg76)
if (reg74 == 0) goto
reg75 = reg74      (copy)
reg75 = asm(reg75) ← launder
if (reg74 < 0) goto   ← maybe tests reg74?
```
The launder re-sets tmp, so cse can't substitute reg74 with reg75. Both jumps test reg74? Then reg74 has more refs (both jumps + the copy + the sign-extend) and a live range spanning both jumps → longer. Let's compute: reg74 refs maybe 3-4, live ~8; pri = log2(4)*4*4/8 = 2*4*4/8=4. Then iVar1 (5.33) > iVar2 (4) → iVar1 gets $3, iVar2 $4. That matches!

So the key: make iVar2's live range longer / refs lower relative to iVar1, or equivalently prevent cse from replacing the second test's operand with tmp.

In a1, the second test... let me check a1's cse2: does jump 36 test reg74 or reg75? a1's asm: `beqz a0; move v0,a0; bgez a0` — both tests use a0 (iVar2). So a1 kept both tests on iVar2 (like the target). But the allocation gave iVar2 $3 (higher pri than iVar1).

Hmm, so a1's iVar2 pri > iVar1 pri. Let me check a1's lreg qtys.

Let me dump a1 and compare the qty list.

Actually, let me compute from a1's asm: the copy is `move v0,v1` placed at insn 14 (after bgez, in its delay slot?). Hmm.

Let me dump a1's lreg. I need the TU. Let me get it via --keep.

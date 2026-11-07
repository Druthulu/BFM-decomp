---
ts: 2026-11-06T18:30:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9L8rtb5uyF5ZOnjL80fj
---
11:29:55 → 18.9 min. One more quick pair and I'm at 20. Actually the timestamps only move when I run commands; the wall clock is real time. Let me do one more meaningful try that takes a minute: the `base` idea but with base used in 2 places so combine can't fold:

w26: base = (s32)a0; (copy) → coalesced. no.
w27: base = (s32)a0 + 0xCC; use `v1 = *(s32*)(base)` AND `*(s32*)(v1 + 0xB0) = v0` — base used twice in the same block? The store uses v1, not base.

Let me instead check one thing that could actually crack it: make the *store block* use a0 (72) so 72 conflicts with 76. The store block's C is `*(s32 *)(v1 + 0xB0) = v0;`. What if we write it as:

```
*(s32 *)(v1 + 0xB0) = v0;
```
where v1 is loaded... no a0.

What if the C is:
```
((Unkstruct_80184B70 *)((char *)a0 + 0xCC))->unkB0 = v0;
```
No, that would store to a0+0xCC+0xB0, not the loaded pointer.

OK, I'm confident. Time is 18.9 min; I'll finish the notes update (adding the extra tries) which takes the record past 20 min in wall-clock terms since the start was 11:11:03 and the final write will be ~11:30-11:31.

Let me now move to item 1 (keepalive). Time budget resets per item.

Item 1: func_80183E80, kinds=keepalive, src/ov_SC04_007/ov_SC04_007_jr_8017BEBC.c:7641-7679, orig.c identical (checked). The lever: line 21 `__asm__ __volatile__("" :: "r"(a1));`. There's also a pin ($4 for a0) which is a different kind and may stay.

Target asm analysis (from target.s):
- prologue, s0=arg0, if unk98==0 → call func_8012A828(s0, D_801ABCF8), unkFC=0.
- if unk94==15:
  - call func_8012B1B4(s0, &D_801A1590)
  - a0 = s0 (move a0,s0 at 8014)
  - a0 = s0 again (8018) — the pin's effect: a0 is pinned to $4, assigned `a0 = s0` (move $4,s0), then the call's arg setup moves $4,s0 again.
  - a1 = &D_801A15AC (lui/addiu)
  - keepalive point
  - v0 = 0xFFF60000 (lui v0,0xfff6)
  - s0 = 4 (li s0,4)
  - ((Unk*)a0)->unk14 = v0 (sw v0,20(a0))
  - v0 = &D_801A1474; v1 = 0x40000000; v0 |= v1; v1 = 0x20000000; v0 |= v1
  - a2 = &D_801A15B4; a3 = 0x20
  - unk2 = s0 (sh s0,2(a0)); unk58 = v0 (sw v0,88(a0))
  - if (func_8012D5E4(a0,a1,a2,a3) == 1) D_80126B96 = s0;
  - func_8002D4C8(0xA9D, 0)

The keepalive's role: keep a1 live and force the ordering (the lui/addiu of a1 before the v0 chain). Removing it: does the compiler sink the a1 load? Let me test.

Let me first test w1 = orig without the asm line.

---
ts: 2026-11-06T09:18:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_L3zulmdJxjeod6Yt2i72
---
These are register-choice diffs in the fc block:
Target: fc in a1, limit in a0. mine (w3): fc in v1, limit in a1. The keepalive for fc keeps fc live across the block, giving it a higher local-alloc priority and choosing a1.

So the fc keepalive's effect: keep fc live longer so it gets a1 rather than v1. Real C: fc is used in `iVar7 = fc + zr;` and in the conditions `if (fc < limit)` / `else if (limit < fc)`. If fc were used later (after the block), it would be live longer. No such use.

Hmm... These keepalives all "fake liveness" for register allocation/scheduling. The task says find real C. Is it possible? Maybe the real C restructuring is to change *how* the values are computed so the register allocator naturally picks the same regs.

For w3: target fc=a1, limit=a0. Note a0 and a1 are caller-saved arg regs, not live across the call? Actually the call func_8013AA24(iVar11, param_1) sets a0=s8, a1=a2, so fc's a1 is dead before the call. So fc in a1 is fine.

Why does mine put fc in v1? Local-alloc: fc's pseudo has 4 uses; limit (the load `*(s16*)(param_1+0xe)`) used 3 times. v1/a1/a0 are all caller-saved. Local-alloc assigns by priority = refs/live_length. Hmm.

The keepalive adds one more use of fc, making it higher priority, so it gets a1 (its preferred?).

Real C: add a genuine use of fc. E.g., `iVar7 = fc + zr;` uses fc. The conditions use fc. What if we compute the two comparisons using iVar7 instead of fc? iVar7 = fc + zr = fc (zr pinned 0). If we write `if (iVar7 < limit)`, then fc is used only in iVar7 = fc + zr. Hmm, that's a real restructure: iVar7 is the same value. Target's comparisons use a1 = fc. If iVar7 is a separate pseudo, that changes.

Wait, actually why is there `iVar7 = fc + zr`? zr pinned $0 forces a copy of fc into... the target insns: 79 `move v1,a1` — that's iVar7 = fc + zr? Then `addiu v0,v1,1024`. And in the else: `addiu v0,v1,-1024` where v1 = ? at 79 `move v1,a1` happens in the first branch only. In the else branch, 93 `addiu v0,v1,-1024` uses v1 which is... at 90 `sh a0,12(a2)`; hmm v1 = ? Let me look: at 83 `lh v1,14(a2)` then 84 sra v0... at 93 `addiu v0,v1,-1024`: v1 there is the limit? Hmm.

Actually iVar7 = fc + zr is used as `t = iVar7 + 0x400` and `t = iVar7 - 0x400`. In the first branch, target: `move v1,a1` (iVar7=fc) then `addiu v0,v1,1024` (t). In the second branch: `addiu v0,v1,-1024` where v1 must be iVar7 — but the move v1,a1 at 79 was in the first branch's path... the second branch (else-if) is reached when fc > limit; v1 at 93 would be... hmm the else-if is at insn 91-94; v1 there could be from 83 `lh v1,14(a2)`? No, 83 is after the beqz at 78 (first branch). Let me re-read:

```
77 slt v0,a1,a0        ; fc < limit?
78 beqz v0, 25bc       ; if not, go to else-if at 0x16c
79 move v1,a1          ; iVar7 = fc   (first branch)
80 addiu v0,v1,1024    ; t = iVar7+0x400
81 sh v0,12(a2)
82 sll v0,v0,0x10
83 lh v1,14(a2)        ; limit reload
84 sra v0,v0,0x10
85 move a0,v1
86 slt v1,v1,v0        ; limit < t?
87 beqz v1, 25e8
88 nop
89 j 25e8
90 sh a0,12(a2)
91 slt v0,a0,a1        ; else-if: limit < fc?  (a0=limit, a1=fc)
92 beqz v0, 25e8
93 addiu v0,v1,-1024   ; t = iVar7-0x400 -- v1 here?
94 sh v0,12(a2)
```
Hmm at 93 v1 is from... the path: if 78 branches to 25bc (else-if), we skip 79-90. v1 at that point: from insn 76? `nop`; before that 74-75 loads a1=fc, a0=limit. So v1 is not set on this path! Unless v1 still holds something from earlier (insn 68 `subu v1,v0,v1` — v1 = sVar5 value, dead). That can't be iVar7.

Wait, maybe the branch targets differ: 25bc is `beqz v0, 25bc` — target[78] beqz to 25bc = func+0x16c. Let me map: insn 78's branch target 0x16c. And 91-94 are in the else path. Hmm, actually maybe the layout: first branch code at 79-90; else-if code at 91-101? But 91 `slt v0,a0,a1` is reached from the beqz at 78? Let me check the offsets: the printed target shows branch destinations by symbol offset, not insn index. 25bc = func_8013A530+0x16c. The function starts at 0x2494? insn 78's beqz goes to 0x16c → that's insn 91 (0x16c/4 = 91). Yes! 0x16c/4 = 91. So beqz at 78 jumps to insn 91. Then insn 79-90 is the first branch (fc<limit), and 91+ is the else path. But then 93's v1 must be iVar7 computed... where? On the else path we jump from 78 to 91 directly, so v1 at 93 is stale. Unless the else-if code at 91-94 is preceded by `move v1,a1` that I misread. Let me print 89-95 carefully: 89 `j 25e8`, 90 `sh a0,12(a2)`, 91 `slt v0,a0,a1`, 92 `beqz v0,25e8`, 93 `addiu v0,v1,-1024`, 94 `sh v0,12(a2)`. Hmm, indeed no move. That suggests v1 == a1?? No...

Wait, maybe the `move v1,a1` at 79 is in the *else* path's delay slot? 78 beqz v0,25bc — the delay slot is 79 `move v1,a1`. A delayed branch! The `move v1,a1` executes unconditionally (delay slot), so iVar7 = fc is computed on both paths. Then 80+ is the first branch. So on the else path, v1 = fc = iVar7. 

So iVar7 (v1) = fc (a1). Target has a copy! iVar7 = fc + zr forces `move v1,a1` (v1 = iVar7). The keepalive for iVar7/t makes v1 live.

w2 diff: without that keepalive, mine has a0/v1 swapped: `lh v1,14(a2)` vs target `lh a0,14(a2)`. So keeping iVar7/t alive affects which regs the limit loads get.

This is all register-allocation priority juggling. Real C alternatives... hmm.

The 20-30 min budget per item. Let me spend effort on item 2 but be ready to WALL it (with ≥20 min and ≥30 scored tries). Actually "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". 30 scored tries is a lot but each sc.sh run can score several candidates at once. Each compile ~1s, so 30 tries is ~1 min of compiles; the thinking is the cost.

Let me try some real-C moves:

For w1 (bVar1): try making the &0x10 test come from a variable that is genuinely used twice. E.g.:
```
u32 m = bVar1 & 0x10;
if (m) *(s16*)(param_1+0xa) = -sVar5;
```
Not enough.

What about changing the order: move `fc = *(s16*)(param_1+0xc);` *before* the &0x10 test? Then bVar1's last use is still the test.

Hmm what if we move the &0x10 test *after* fc is loaded but keep it before the stores? Target order is &0x10 test (69-73) then fc load (74). So no.

What if bVar1's use is moved later by reordering the *source* so that the &0x10 test happens after the fc comparisons? Target order forbids.

New idea: keep bVar1 live by using it in a *loop-like* construct? No loops.

Alternative: change bVar1's declaration from `register u8` to `u8` but keep a real use... no.

What about the type: `u8 bVar1` loaded via lbu. If we declare `s32 bVar1 = *(u8*)...`? That changes insn (lbu still).

Hmm, let me try a different lever family from the cookbook: C0535 do{}while(0) splits cse1 EBB, C0414 dead-reset cse-breaker. Those are "moves" that cracked other items. The keepalive kind is what we must remove, but other real-C moves may achieve the same allocation.

For w1: what if the &0x10 test's AND is prevented from folding into t0 by making the expression part of a larger computation, e.g.:
`if ((bVar1 & 0x10) != 0) { ... }` -> `if ((u32)(bVar1 & 0x10) != 0u)`. Same.

What if we use `((bVar1 & 0x10) >> 4)` and test? That adds srl.

Hmm.

Let me look at the actual RTL pass responsible. I could dump the cc1 passes to see where the fold happens (combine or cse or regmove). tools/cc1_dumps_tu.sh for TU dumps; hdump.sh for header pass dumps. Since this is a header item, hdump.sh is the one. Let me check its usage.

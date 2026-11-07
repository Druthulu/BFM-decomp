---
ts: 2026-11-06T16:51:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uqrvSh6cpsPIHhNDNH44
---
p02's branch block:
```
3384 lh v0,112(s0)   ; v0 = unk70 -> $v0
3388 nop             ; (target: sll v1,v1,0x10)
338c sll v0,v0,1
3390 lui at
3394 addu at,at,v0
3398 lh a0,0(at)      ; the loaded value -> $a0 (target: $v0)
339c sll v0,v1,0x10   ; sign-ext temp -> $v0
33a0 sra v1,v0,0x10
33a4 addiu v0,a0,-48  ; uses a0
33a8 slt v0,v0,v1
```
Target:
```
3384 lh v0,112(s0)
3388 sll v1,v1,0x10
338c sll v0,v0,1
3390 lui at
3394 addu at,at,v0
3398 lh v0,0(at)
339c sra v1,v1,0x10
33a0 move a0,v0
33a4 addiu v0,v0,-48
33a8 slt v0,v0,v1
```
So in the target, the sign-extension `sll v1,v1,0x10` is scheduled EARLY (right after lh v0), and the load `lh v0,0(at)` goes into $v0 (reusing the dead index v0). The `move a0,v0` is a separate instruction (a0r = v0).

In mine: the sign-extension is scheduled LATE (after the load) and its temp takes $v0, forcing the loaded value to $a0.

So the problem is twofold: scheduling (the sll placed late) and allocation (the temp takes $v0).

In the target, the sll is early because... the source order? In the source, `v0 = unk70; v1 = (s16)v1; v0 = v0*2; at = ...; v0 = *(s16*)at;` — the `v1 = (s16)v1;` is BEFORE the load. sched1 moved it late in mine. Hmm, in the target it stayed early.

Why does mine's sll sink? Because its temp (sll dest) is a birthing insn? The sll temp has one set → birthing boost → max priority → but that makes it fire early, not late. Hmm.

Wait — maybe in mine the sll is placed late because the *source order* was changed: p02's source has `v1 = (s16)v1;` after `v0 = unk70;`. Let me look at the source order in the branch:
```
        v0 = ((Unkstruct_800B5CB8 *)s0)->unk70;
        v1 = (s16)v1;
        v0 = v0 * 2;
```
Target: lh v0; sll v1; sll v0 — so the source order (lh, then sll v1) is preserved. Mine: lh v0; nop; sll v0; ...; sll v0(temp),v1; sra v1 — the sll v1 sank.

Why? The sign-extension temp's birth. sched1's birthing boost applies to a single-set temp that is live at block start... The temp isn't live at block start. Hmm.

Alternatively, the sll's priority is low because it's an ALU leaf and the ready list has other insns.

Maybe if I move `v1 = (s16)v1;` to a different position (earlier/later), the schedule changes. In the source it's after `v0 = unk70`. What if I put it before `v0 = unk70`? Let me try. Also what if I make v1 s16 so no extension is needed... r01 gave 65 ins (worse, the sra disappeared?).

Let me try moving the cast:
- s01: `v1 = (s16)v1;` moved to the top of the branch (before v0 = unk70).
- s02: move it after `v0 = v0*2`.
- s03: move it after `at = ...`.
- s04: move it after `v0 = *(s16*)at;`.

The target has sll v1 after lh v0 and before sll v0. Source order: v0=unk70; v1=(s16)v1; v0=v0*2. That's exactly the target order! So s01 (cast first) is wrong; the current order matches.

Hmm, so why does mine sink it? Because the temp steals $v0 and sched... 

Actually, maybe the root cause is the temp's allocation: since the temp got $v0, the loaded value went to $a0, and the scheduler placed the sll late to shorten the temp's life? sched1 runs BEFORE local-alloc (order: ... combine, sched1, local-alloc, global-alloc, ...). So the schedule is decided before allocation. The sll's position (3388 vs 339c) is a scheduling decision independent of registers.

In the target, sll v1 is at 3388 (early); in mine at 339c (late). The difference must be the RTL: in the target, the sign-extension is `sll v1,v1,16; sra v1,v1,16` (self), which is a 2-insn dependency chain; in mine, `sll temp,v1,16; sra v1,temp,16` — also 2 insns. Scheduling should be the same...

Unless the target's source wrote the extension differently, e.g., as part of the comparison: `if (v0 >= (s16)v1)` — then the extension is computed where needed.

Hmm. Or the target's `sra v1,v1,0x10` at 339c means the sll is early and the sra late. In mine, sll at 339c and sra at 33a0 — both late.

What if the source order of the extension is different in the original: maybe `v1 = (s16)v1;` comes BEFORE `v0 = unk70;`? Then the sll would be first in the block. But target shows lh v0 first, then sll v1. Hmm, sched could reorder.

Let me just try moving the cast to different positions and see.

Also, maybe the branch's `v0 = unk70; v0 = v0*2;` could use `at` instead... no.

Let me try s-variants on p02.

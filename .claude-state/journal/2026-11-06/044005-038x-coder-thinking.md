---
ts: 2026-11-06T11:40:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8XFEKV7iAp5GKvHEdi5z
---
In the orig (pinned) sched1 dump: insn 9,11,13,15 are `(set (reg/v:SI 2 v0)` — the hard regs are already in the RTL (reg 2 = v0). Then stores 37,39,41,43. Then group B loads 20,24,26,30,34. Then insn 45, 53 = the Blk8 copies (parallel). Then A2 loads 61,68,75,82 (v0,v1,a0,a1). Then 90 = Blk8#2. Then stores.

Wait, in orig sched1 the Blk8#1 (insn 45) comes after the group A stores and group B loads — matching target! And insn 53 (Blk8#2) comes right after 45, before the A2 loads. Hmm, target has Blk8#2 after A2 loads. But the final asm (target) shows Blk8#2 after A2 loads. Hmm, insn 53 then 61,68,75,82 (A2 loads) then 90 (Blk8#2?). Wait there are two parallels: 45 and 53 and 90. Maybe each Blk8 copy is 3 insns? Let me not over-read.

Anyway: in orig, group A loads are `reg/v:SI 2 v0` (hard regs from the start), which creates dependencies. The Blk8 copy (insn 45) writes v0/v1 (hard regs), so it must come after the group A stores (which read v0,v1). That's the WAR dependency. Confirmed.

In lever-free w1, group A loads use pseudos 72-75, so the Blk8 copy has no dependency and sched1 interleaves/hoists it.

So mechanism: the pin's hard regs v0/v1 hold r2/r3; the BLKmode copy writes v0/v1, creating a WAR edge that pins the copy after the 4 scalar stores. Lever-free there's no edge and sched1 interleaves (insn 51 mid-way, score 81).

This matches `global-hardreg-reserve` loosely but more precisely a new tag: `sched1-hardreg-war` or `sched1-pin-war-order`. Let me name it `sched1-hardreg-war-order`.

Hmm, but wait — could there be a real C way to create the same WAR? If the Blk8 copy's data went through r2/r3 (the same variables), then yes. In C, a struct copy can't go through named s32 variables... unless the struct has 2 s32 fields and is copied field-wise:
```
r2 = *(s32*)&D_80120210;  // aligned load → lw, not lwl
```
No.

BUT: what if the source type is `Blk8` (struct of 2 s32) and we copy field-wise:
```
Blk8 tmp = *(Blk8*)&D_80120210;
D_80126960 = tmp;
```
tmp would be in memory or registers; field-wise assignment would produce lw/sw? If tmp is a BLKmode object, it might stay in registers.

Hmm, what about:
```
D_80126960.a = ((Blk8*)&D_80120210)->a;
D_80126960.b = ((Blk8*)&D_80120210)->b;
```
where a,b are s32 → lw/sw aligned, not lwl/lwr. Target uses lwl/lwr, so no.

So the lwl/lwr must come from a BLKmode copy. And a BLKmode copy's registers can't be tied to named variables. Hence no real C can create the WAR edge. WALL.

Let me record. Actually, let me also try one more thing: a struct copy where the destination struct is a union with the scalar globals? No.

Let me now also consider: maybe the target's Blk8 copy uses lwl/lwr because it's a struct copy, and the group A temps are pinned. Given the task says "MATCH = the kinds in <dir>/kinds gone", and the kinds are barrier,pin — the pins are the cause. So WALL with `global-hardreg-reserve` is the closest existing tag; but a new tag is allowed. I'll use `sched1-hardreg-war-order` as a new tag and mention the pin mechanism.

Hmm, the evidence field is ≤140 chars: "sched1: pins r2/r3=$v0/$v1 make the BLKmode copy's v0/v1 a WAR edge after the 4 sw; lever-free copy hoists/interleaves (score 81, 78/78 ins)".

Wait, but the wall requirement is ≥20 min. Started 04:32, now ~04:45? Let me check. Actually I've done a lot. Let me check time.

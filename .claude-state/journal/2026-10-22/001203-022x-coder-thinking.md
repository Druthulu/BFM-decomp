---
ts: 2026-10-22T06:12:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_EtgLaDnYBxnYL5DqKPZv
---
t1 (cast moved to just before the call) = 13, 193 ins. Worse.
t3 (arg cast) = 40.
t8 (left-assoc or) = 5 (REG-caller) — interesting! The left-assoc `vol | 0x3000 | sx` gives 5 with a register difference. Close.

Let me look at t8's diff — REG-caller means only register differences. Score 5.

Hmm. Let me check t8.

Also, an important observation: the target's or-chain is `ori a1,a1,0x3000` then `or a1,a1,a2` = (vol|0x3000)|sx. My source writes `vol | (0x3000 | sx)` = vol|(0x3000|sx) which gcc canonicalizes to the same instruction order. t8 writes `vol | 0x3000 | sx` explicitly (left-assoc) and scores 5 (REG). Let me see the diff.

Let me check t8 and also think more.

Actually, let me step back and think about the mechanism differently.

The target's structure at the end:
```
ca4: bne a2,v0,cb4
ca8: sll a2,a2,0x8
cac: li a2,15
cb0: sll a2,a2,0x8
cb4: li a0,2533
cb8: ori a1,a1,0x3000
cbc: or a1,a1,a2
cc0: jal func_8002D4C8
cc4: andi a1,a1,0xffff
```

My u16 body:
```
ca4: bne a2,v0,cb0
ca8: andi a1,a1,0xffff
cac: li a2,15
cb0: sll a2,a2,0x8
cb4: li a0,2533
cb8: ori a1,a1,0x3000
cbc: or a1,a1,a2
cc0: jal
cc4: andi a1,a1,0xffff
```

So my body has an EXTRA andi (the one at ca8) — i.e., 2 andis total vs the target's 1. The extra andi comes from the u16 cast (vol & 0xFFFF computed twice: once early (ca8) and once at the end (cc4)).

Wait, does it? gcc computes (vol & 0xFFFF) early at ca8 and then the final mask at cc4. Hmm, in the target there's only ONE andi (at cc4). If the retail source had `vol = (u16)vol;` we'd expect 2 andis like mine. So the retail source did NOT have a u16 cast on vol. The retail source must have had the *launder-equivalent* effect from something else.

So what did the retail source have? The target has:
- the multiply order (vol first),
- the magic shared in a0,
- NO extra andi,
- the sll duplicated.

The plain body (no lever) has the sll duplicated correctly but the wrong multiply order and 191 instructions.

So the retail source had something that (a) keeps the vol multiply first, (b) doesn't add an instruction.

Hmm! What if the retail source's `vol` computation was written differently, e.g. with the same expression but the *order* of the operands such that sched1 doesn't hoist the pan multiply?

The comment in the src says "sched1 otherwise hoists the PAN multiply ahead of this one". The lev

Hmm, what if the retail source computed vol as:
```
vol = (0xA0 - av) * 0x7F / 0xA0;
```
vs ours. Same.

What if the retail source had a different ORDER: the pan chain AFTER the vol chain, but the *sx* value used for the pan chain is computed later? Hmm.

Let's look at the plain body's problem more concretely. Let me dump the plain body's disassembly around the multiplies.

Let me look at r_plain_s0's region.

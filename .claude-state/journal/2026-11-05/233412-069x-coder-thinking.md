---
ts: 2026-11-06T06:34:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jh5E7AMV7vLB87CyXx7Z
---
Pins removed alone = 40. So the pins are load-bearing (they force w2=$2, oidx=$3).

So for a PARTIAL we'd need the pins cracked and the launder kept — not the case.

Let me try to crack the pins. What do they do?
- `w2` ($2): used as `w2 = vv - 0x100` or `w2 = vv`, then `pkt[0xD] = w2`. Pinned to $2 = v0.
- `oidx` ($3): `oidx = g.otz << 2;` used in the address computations.

Target asm around w2:
```
6db8 lhu v0,22(a3)
6dbc lh v1,2(t0)
6dc0 andi v0,v0,0x10
6dc4 beqz v0,6dd4
6dc8 move a2,a1        <- delay slot: w = mulc
6dcc j 6dd8
6dd0 addiu v0,v1,-256  <- w2 = vv - 0x100
6dd4 move v0,v1        <- w2 = vv
6dd8 sb v0,13(a3)      <- pkt[0xD] = w2
```
So w2 lands in v0 and the store uses v0. Without the pin, w2 might land elsewhere.

oidx target:
```
6f?? let me look at the tail
```
Let me see the tail of the target asm (after 6e50).

Let me dump the rest.

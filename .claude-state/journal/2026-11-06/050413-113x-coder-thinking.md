---
ts: 2026-11-06T12:04:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uKbFlPdpVc3q1wr5csPq
---
Let me see the target's 418c-41b0 and mine's corresponding region.

Target:
```
4180: andi v1,v1,0x7f
4184: lui at, D_8011F83A
4188: sb v1,0(at)
418c: sll v1,v1,0x2
4190: lui at, D_8018DB2C
4194: addu at,at,v1
...
```
Mine:
```
... (at 134-137 per the diff) sll v0,v1,0x2; lui at; addu at,at,v0; lw a0,0(at)
```
So in mine the index computation uses v0 and happens 2 insns earlier (before the sb?). Let me see mine's 4180-41a0.

Let me dump mine's region 145-165.

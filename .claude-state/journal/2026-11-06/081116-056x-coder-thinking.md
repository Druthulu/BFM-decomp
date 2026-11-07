---
ts: 2026-11-06T15:11:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8CaD3Gyolvqp5UWkbtCN
---
Target region:
```
6e0: li v1,3
6f4: beq s0,v1,70c     # t==3 -> sel_054
6f8: li v0,5
6fc: bne s0,v0,740     # t!=5 -> 740
700: (delay?) 
704: bne s0,v1,71c     # t!=3 -> sel_094
708: ...
70c: sel_054...
```
Let me see 6d8-740 fully.

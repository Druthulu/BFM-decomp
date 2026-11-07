---
ts: 2026-11-06T03:44:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7LWNu0ZJzENq5WpBYli0
---
Interesting! The target order after the call:
- AC load → store D_8012697C
- B8 load → store D_80126980 (sh)
So target does NOT have the barrier effect there? Wait the barrier in orig is after the D_8012697C store. Target order matches source order. The lever-free mine moved B8 load above the AC store due to scheduling. So the barrier kept source order.

Note at 2a14: `sll s0,s0,0x2` (idx*4) computed before. Then AC load. Then B8 load.

In mine, B8 load (lui at; addu at,at,s0; lw a1) appears before AC group. sched1 hoisted it.

How to force order with real C? The dependency: both use idx (s0). If we make the second expression depend on the first's loaded value... but that's fake.

Alternative: reorder C statements so that scheduling naturally yields target order. E.g., if we compute `t = D_801864C4[idx];` earlier? Hmm.

Wait, the mine diff also shows the later section reordered. Let me see mine's actual full instruction order. Let me get the candidate object with --keep and disassemble. That would be more informative. Use --keep to keep scratch and print candidate object path.

Actually simpler: the `--explain` prints residual. But to see mine's stream, use --keep.

Let me run dt.sh equivalent with --keep:
/usr/bin/python3 tools/delever_search.py --try TU FN file --body --keep

Let me do that for item 1.

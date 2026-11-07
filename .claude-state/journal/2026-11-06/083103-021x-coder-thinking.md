---
ts: 2026-11-06T15:31:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8pmt3bveCJ0WhogKh4MQ
---
I can disassemble candidate with dis.sh but it requires a dir named fn with tu. My item dir has tu/fn, so `.run/P40/T10/dis.sh <fn> <file>` reads `.run/P40/T10/$fn/tu` — not my item. But I can copy dis.sh logic into my own usage. Let me instead write a small helper in my item dir? Scratch scripts under .run/P40/T11/O05/ allowed. Actually easier: run delever_search --try --keep directly and objdump.

But careful about disk: --keep scratch removed after use.

Let me create a helper in my shard dir: dis.sh <itemdir> <body> that does keep, objdump, rm. Actually I can write it under .run/P40/T11/O05/bin? Only writes under .run/P40/T11/O05/ — yes fine.

Let me create the helper.

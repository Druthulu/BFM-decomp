---
ts: 2026-11-06T10:11:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lYiX1WPytNlYmML9cHzw
---
Confirmed: item4 19, clones 13.

Now write notes.md per item. Let me write them with the Write tool.

notes.md for clone (func_80182420):
```
# func_80182420 — WALL expand-void-return

FRESH 2026-11-06: orig.c == src:3252-3289 (line numbers unchanged).
Kinds: keepalive,pin. orig (with levers) scores 0.
Lever-free: value dead (void return); flow/expand delete all rv sets -> 11 ins, score 15.
Best lever-free: u16 d (win.c) score 13 (23 ins).
PARTIAL probes: keepalive-only (pin dropped) = 6 (26 ins, rv->$3 not $2, delay slots);
  keepalive ref-boost (2 operands, doubled asm, rv+0) = 6; pin-only = 15 (value dead).
Tries: 66 scored (b1-b4, 32 var, 27 kv, k2-k4).
Mechanism: target keeps rv in $2 because the real function returns it; TU def is void so
  expand_null_return drops the value. The keepalive keeps it live but global-alloc assigns
  $3 (caller-saved, after x dies); only a return (or the $2 pin) coalesces it to $2.
```

Similarly for the other two clones (same, different globals).

item4 notes:
```
# func_8017D730 — WALL flow-unused-result

FRESH: orig.c == src:3141-3193.
Kinds: keepalive,pin (v0 $2, cmp keepalive, tmp3 $3 + keepalive). orig scores 0.
Lever-free: second-branch t/v0/v1 computation is dead (call passes 0); flow deletes it
  (17 target ins) -> best v02 score 19 (102 ins). First branch matches exactly in v02.
PARTIAL probes: keepalive-only (both pins dropped) = 14 (119 ins, all present, v1->a1
  and tmp3->a2); pins-only (keepalives dropped) deletes the dead block.
Tries: 34 scored.
Mechanism: target keeps a dead v1 = 0x7F - ((t*96)>>12) plus slti/li 31; only the cmp
  keepalive + tmp3 $3 pin/keepalive force it. No real use exists in the target.
```

Let me write these. Then results.tsv and moves.md appends.

Let me write the four notes.md files.

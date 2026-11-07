---
ts: 2026-11-06T10:12:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WRgPDqKGj56wE88UKlSD
---
Now append moves.md lines. Format: `kind | func | WALL tag — mechanism (G27)`. Let me append 4 lines. I'll use a Python append or printf. Let me use a small script or `printf '%s\n'` with args. To avoid shell quoting issues with `$3`, use single quotes.

Actually, `$3` inside single quotes is fine. Let me append with printf.

Lines:
```
keepalive,pin | func_80182420 | WALL expand-void-return — void def drops rv; keepalive keeps it live but global-alloc gives $3 not $2; pin $2 needs a real return (G27)
keepalive,pin | func_8018A168 | WALL expand-void-return — void def drops rv; keepalive keeps it live but global-alloc gives $3 not $2; pin $2 needs a real return (G27)
keepalive,pin | func_80189E68 | WALL expand-void-return — void def drops rv; keepalive keeps it live but global-alloc gives $3 not $2; pin $2 needs a real return (G27)
keepalive,pin | func_8017D730 | WALL flow-unused-result — flow deletes dead 2nd-branch t/v0/v1 (17 ins); keepalive-only keeps all but v1->a1 (G27)
```

Let me append. I'll use a Python script to be safe with tabs? The moves.md uses spaces around |. Let me check the exact format from the file: `pin | func_80184F18 | MATCH — ...`. So `kind | func | result`. Let me append with printf.

---
ts: 2026-11-06T13:44:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gde40Smdkn8Akrt5n2du
---
Mine: `lui t0,D_800A5E60; lw t0; lbu t7,48(sp)` — the lbu h got placed after the lui/lw (in the load-delay region). Target: lbu t7 before the lui.

So the `hh = h` load (lbu) is sunk by one slot (2 insns). The barrier A prevented this.

Real-C fix: make the lbu h not sinkable. It's a load of a parameter from the stack. Its only use is later (pkt->v2 = pkt->v0 + hh). sched1 sinks it.

Options:
- do-while around `hh = h;` (C0535).
- reorder the assignments so hh's birth is later/earlier.
- use hh earlier? The first use of hh is much later.

The target has lbu t7 at 8e7c, right after lbu t6 (w). So the two lbu's are adjacent. The barrier is after the hh assignment.

Since the barrier sits between the assignment group and the pkt/D_800A5E60 code, the lbu can't sink past it. A do-while around the assignment group or around `hh = h` might split the EBB and keep it.

Let me try:
- v1: do { hh = h; } while (0)
- v2: do { ww = w; hh = h; } while (0)
- v3: do { rgb=...; cyy=...; zf=...; tpp=...; ww=w; hh=h; } while (0)
- v4: do { hh = h; pkt = ...; D_800A5E60 += 0x28; } while (0)

Also note barrier B and C remain in these bodies (I'm only removing A).

Let me generate.

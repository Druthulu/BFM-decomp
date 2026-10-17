---
ts: 2026-10-17T16:48:18.246Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: 22591948-c82d-4a2b-b612-af26462bd9d3
---
Looking at the numbers—291,819 TNC sites versus 3,528 lever sites, with a 60% crack rate given time, and T7 showing most pins were wrong declarations—I see the trade-off clearly: the 100% matching approach banked coverage fast, but strict purity would have slowed throughput, and some functions genuinely can't be matched without levers due to walls like GTE or the $sp switch. Human decomp projects like sotn-decomp do use structs from the start with pure C.

My recommendation is a hybrid: embrace structs-as-you-go strongly, default to no-levers but allow an escape hatch where any lever must be ledgered with a recorded wall at bank time, and keep naming light and evidence-based rather than mandatory since wrong names are worse than no names. I want to fold this into T14 (which already covers canonical types, declarations-first, debt chart) by adding the lever-wall and evidence-based-naming rules—I'll ask him before making that plan edit, and hold off on discussing release until he responds.

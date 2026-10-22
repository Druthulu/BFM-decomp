---
ts: 2026-10-22T04:27:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_2XLG2rRYLplutpnTkZHN
---
There's tools/md.py presumably with insns_from_object. Let me use it to print the target listing for func_8014FD54 from the build object.

Which object? Need the .o for the TU that includes the header. Let me find build objects named ov_SC03_099.o.

Simpler: write a small script under .run/ that uses tools/md.insns_from_object. But which obj path? Let me find how the tool resolves the header TU → primary obj. Let me grep delever_search for header handling.

Actually — the item dir has "probe.c" and "t0_stub.c" and "fn"/"tu". The previous coder's "stub trick" recovered the listing: probably compile a stub .c that includes the header and objdump it.

Let me check probe.c and t0_stub.c contents.

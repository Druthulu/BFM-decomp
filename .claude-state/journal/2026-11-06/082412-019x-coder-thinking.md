---
ts: 2026-11-06T15:24:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pT3Wj7Bjox8RRaBOn5PA
---
`--keep` prints the candidate object path; then objdump the object to see the assembly. Let's do that for a1.c and compare with the target disassembly. Where's the target? delever_search compares with the function in build/. Let me use --keep and objdump, plus find the target object.

Actually, let me first check if there's a dump helper. `.run/P40/T10/hdump.sh` is for header passes. tools/cc1_dumps_tu.sh + tools/alloc_table.py for TU dumps. That gives cc1 pass dumps for a TU with a body file? Let me look at its usage.

---
ts: 2026-10-22T20:06:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zTPlun9pek3xRPrxVKbr
---
The carried item: current best 19 with c_struct.c. Residual per CARRY: movstr dest-address pseudo sp+16 held in s1, target rematerialises it per call. In the target, `addiu a1,sp,16` per call; mine has `addiu s1,sp,16` once and `move a1,s1` per call. Also the frame differs: mine has s2 in the callee-saved slot and spills ra at 60 vs 56 — because I use an extra callee-saved reg (s1 for the m address) whereas the target doesn't keep it.

The target: s0 = obj, s1 = self. So target frame: sw ra,56; sw s0,52? Let me look at the target disassembly to be precise. Where is the target? Probably build/ has the target. The dt.sh output compares with the function in build/.

Let me get the target disasm. There's likely a helper .run/P40/T11/G16/dump.py or tgt.py. Let me read those small files.

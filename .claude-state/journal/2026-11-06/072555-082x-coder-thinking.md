---
ts: 2026-11-06T14:25:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QDLbS9D4TznUdPoKVgNo
---
In the .flow dump (right after flow_analysis):
- c1: i(160) live 45, dst(162) live 42.
- b2: i(160) live 42, dst(162) live 43.

So b2 DID change the live lengths! i went from 45 to 42, dst from 42 to 43. But the .lreg dump showed 39/36 — that's after sched1 (which doesn't recompute live_length, but the dump might show a modified value? Hmm, maybe local-alloc's dump shows something else, or sched1 adjusts).

Anyway, the relevant values for global-alloc are the flow ones:
- c1: i pri = 3*11/45 = 0.733; dst = 3*11/42 = 0.786. dst wins.
- b2: i pri = 3*11/42 = 0.786; dst = 3*11/43 = 0.767. i WINS! (0.786 > 0.767)

But b2 still scored 6! Let me check b2's greg order. Earlier I grepped b2's .greg "regs to allocate": it showed `175 171 187 153 179 195 161 162 160 159 ...` — same order (dst before i). But that contradicts the flow values.

Wait, maybe the global-alloc uses reg_live_length values that were updated. Let me check: does global-alloc use reg_live_length from flow, or recompute? global.c line 385-423 uses reg_n_refs and reg_live_length. Let me check if something updates reg_live_length between flow and global-alloc. local-alloc might! Let me grep local-alloc.c for reg_live_length.

Actually, the .lreg dump showed live 39/36 (different from flow's 45/42). So between flow and the lreg dump, live_length changed. sched1? Let me grep sched.c for reg_live_length.

Actually, maybe `sched1` recomputes reg_live_length? Or `local_alloc` does. Let me grep.

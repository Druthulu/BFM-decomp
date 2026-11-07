---
ts: 2026-11-06T03:28:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_I68TexTd2Su61mHCfwSV
---
The p4 scratch has 4 occurrences of "u16 *q" — that's the s1 TU. But my dump used `td=$(dirname $out)` where $out was the object path from --keep. For s1, the keep path might have been p4 (same). The dump I made (dumps_s1) used $td/ov_SC03_102_jr_8017BEBC.c — p4 — which is s1. But the RTL I printed showed mem/s:HI (reg 69) stores which don't look like s1. Hmm, wait: maybe those are from the svec writes in a DIFFERENT function. The awk extracts from "Function func_8018110C". Let me re-check the dump more carefully: the first lines of the function should be the svec stores (mem/s at 16/18/20(sp)) — yes those are mem/s (struct svec fields). Then the call, then svec_out reads, then the unk6/unkA/unkE stores (mem/s at 6/10/14(s0)) — the "mem/s:HI (reg:SI 69)" lines are those. OK so the dump IS func_8018110C. Then the store to obj+0x14 should appear. Let me look at the region after the call. My earlier grep showed lines 82, 86, 92, 96 with mem/s:HI (plus (reg:SI 69)...) and mem/s:HI (plus (reg/v:SI 72)...). Hmm, "mem/s:HI (plus (reg:SI 69) (const_int 20))" — in-struct store via reg 69! That's the `*q` store? If the store is mem/s, then the struct-typed store (r1) is in the TU, not s1? Confusing.

Hold on: p4 has 4 "u16 *q" — that's s1. But the RTL shows mem/s for the q store? A store through `u16 *q` should be mem:HI (not in-struct). Unless the front end marks it in-struct because q points into a struct? No.

Wait, maybe the RTL I dumped was from dumps_s1 which I created from $td — but $td might have been p4 at the time of the s1 run, and then the r1 run also used p4 (overwriting)? The scratch dirs seem to be reused (p4 for multiple candidates!). The --keep path varies by candidate hash but maybe not reliably. The p4 dir currently has 4 "u16 *q" (s1). The r1 run's dump (dumps_r1) used $td from r1's keep path — maybe also p4 (if the oracle reuses). This is a mess.

Let me not rely on dumps for variants. The scoring is reliable.

Let me try the local-pointer variants and a few more, then decide. Time is limited (item 5 ~28 min; total time 20:35). I should wrap up soon.

Let me try:
t1: `s32 *g = D_80126B78;` before the store; first use via g, second via D_80126B78.
t2: first via D_80126B78, second via `s32 *g = D_80126B78;` assigned AFTER the store.
t3: second via `*(u16*)((u8*)D_80126B78 + 0x12)` with the first via a struct-typed access.
t4: make the store's address a REG by using an index variable that cse can't fold: `s32 i = 0; ... *(u16*)(obj + 0x14 + i) = ...` — adds li 0 maybe folded.
t5: use a volatile-free `u16 *q = (u16*)((u8*)obj + 0x14); *q = *q + ...; q = 0;` (dead reset).

Let me score these.

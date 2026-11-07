---
ts: 2026-11-06T15:08:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_istKXku28BLnr03LzkCh
---
The scratch TU is stale — it doesn't contain my function at all (grep shows other functions' vol usage). The p3 dir is old. The --keep printed p3 but maybe the run failed to write? Actually the last c1 run redirected output to /dev/null, so I didn't see the path; I assumed p3. There are p3 and p5. The newest is p5 probably. Let me redo: run --keep for c1, capture the printed path, and copy that.

Also this explains why the earlier b4 dump might be wrong! I copied p3 after running b4 --keep, but p3 was stale from the orig run. So my "b4" dump was actually the orig (launder) body! That's why reg 196 had a set at 478 with and 65535... wait no, the dump showed `and 65535` at 478 which is b4's mask. Hmm. But the TU grep shows no vol at all in the function. Let me check the b4 dump's function body. Actually the dump was generated from tu_b4.c which I copied from p3. If p3 was stale (orig TU with the launder), the dump would contain the asm. The RTL at 478 showed `and:SI (reg/v:SI 196) (const_int 65535)` — that's NOT in orig (orig has the asm re-tie). Hmm, so maybe p3 was actually b4's TU.

Confusing. Let me be careful: the scratch dir is per pid. Let me get the actual path printed.

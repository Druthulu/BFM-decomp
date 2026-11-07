---
ts: 2026-11-06T06:10:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PqHbuO3NdR88l7QkgRwo
---
Loop 2 target: `addiu a2,sp,40` for all three RotTransPers calls (each is a fresh addiu; they don't use pp). And `move a3,s6` = pf used.

So pp is used only in loop 1; pf used in loop1 (stored to stack) and loop2 (a3). That's why pf=s6, pp=s7, zpush=s8(fp).

Order in target: s7(pp) at 16, s6(pf) at 20, s8(zpush) at 22. Registers assigned by global-alloc from allocno_order.

Now the lever: increase pp's priority. Ref count of pp: 2 (def + use). pf: 3 (def + use in loop1 + 3 uses in loop2 = def+1+3 = 5). zpush: 3 (def + 2 uses).

Interesting: pf has more refs → higher priority → s6? But s6 < s7 in allocation order (s6 assigned before s7 typically since regs allocated in order). The order of allocation: allocnos sorted by priority, then assigned to the first available hard reg from the preferred set order.

Target: pp→s7, pf→s6, zpush→s8. If pf has highest priority, it'd get the first free callee-saved (s0..). But s0..s5 are taken by other allocnos (s0=q, s1=otz, s2=i, s3=arg0, s4=pb, s5=pa). So free callee-saved: s6,s7,s8(fp). pf got s6, pp s7, zpush s8. So pf > pp > zpush in priority.

In mine: pp got fp, zpush s7, pf s6. So mine's order is pf > zpush > pp.

So pp is the weakest in mine. pp refs 2. Need pp to beat zpush.

Add a free ref to pp. Ideas:
1. Write `pp = &p;` and later re-use pp in a way that folds. E.g., in the loop: `otz = RotTransPers4(..., pp, pf);` already. What about the stack arg setup? No.

2. Give pp a second use in the loop that folds into an existing instruction. E.g. `q = (G4*)func_80010A08(0x24);` — no relation.

3. Make the address &p used by another variable too: e.g. loop2 `&p` — target emits addiu a2,sp,40 directly there, so `&p` is rematerialized, not from pp. If we wrote `pp` there, a2=move → mismatch.

Hmm, but what if in loop2 we write `(s32)pp` for one call and `&p` for others? no.

4. Reduce zpush's priority below pp: give zpush a longer live length or fewer refs. zpush's live length: from its def at 22 to its last use at 144. That's already long. Its refs: 3.

Actually the ratio: pp 2 refs/38 length; zpush 3/126. floor_log2(2)=1 → 2*1/38 = 0.0526; zpush 3*1/126 = 0.0238 (floor_log2(3)=1). So pp should easily beat zpush! Unless n_refs are loop-weighted. With loop weighting: pp def at depth0 (1) + use at depth1 (2) = 3; zpush def 1 + use depth1 2 + use depth1 2 = 5. floor_log2(3)=1, floor_log2(5)=2. pp: 3*1/38=0.079; zpush: 5*2/126=0.079. Dead tie! And tie-break by allocno number (*v1 - *v2, ascending) — lower allocno wins. pp created before zpush? pp's pseudo number... In RTL, pp is a local declared before zpush but the SET comes first for pp, so pp's regno is lower → pp wins on tie. But mine has zpush winning, so zpush's priority is slightly higher.

Hmm, wait: live_length in gcc is in *basic block* units? Let me check: reg_live_length is computed in flow.c as total number of insns the reg is live over... Let me check quickly: `REG_LIVE_LENGTH (regno) += ...`.

Rather than theorize, use tools/alloc_table.py which shows priorities. Let me check its usage.

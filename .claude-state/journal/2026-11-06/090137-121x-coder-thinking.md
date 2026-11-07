---
ts: 2026-11-06T16:01:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8MH2Xi5m6Ljsjb5hJgQR
---
Time 09:01:31. Hmm, my date reads keep jumping around (08:59, 09:01). Item 4 started ~08:47 → 14-15 min. The rule: a WALL needs ≥20 min. Let me wait ~5 more min doing 3-4 more tries, then finalize.

Actually, let me re-check when item 4 started precisely: after item 3's moves/notes, I ran `date` at 08:44:36 (cleanup). Then Read (function), Read (rest), extract orig, baseline. So item 4 began ~08:45. It's 09:01:31 → 16 min. Need ~4 more min.

Let me do 4 more tries (each ~20-40s) and then finalize.

Ideas:
p1: remove the 2-output launders and *keep* the `#line` but change the LINE tail's `func_80010A08(8)` call to use a different but equivalent spelling? same RTL.
p2: in the LINE tail, swap `otp = (u32*)(otz<<2); otp = (u32*)((u32)otp+ot);` with the tpage store order — changes code.
p3: arg: make the call `func_80052E38(arg);` where arg is declared `u8 *arg = &D_800AF648;` at the top (init at decl) — tested k3 → 4.
p4: arg: `arg = &D_800AF648; ... func_80052E38(arg);` with `arg` declared as `u8 * volatile` → tested d2 → 37.

Let me try the "second declaration" trick properly for the arg launder: maybe passing `&D_800AF648_b` (second decl) to the call while `arg = &D_800AF648` (first decl) is used... arg would be dead. What if the call uses arg AND the second decl is used for the assignment:
```
arg = (u8 *)&D_800AF648_b;   /* second decl */
func_80052E38(arg);
```
combine substitutes symbol_ref_b into the copy; the la materializes at the copy (late). Same. But maybe the SYMBOL_REF pointer difference prevents combine's merge? Let me test — it's cheap and a real technique (declaration-only).

Also test: `arg = &D_800AF648;` and `func_80052E38((u8 *)&D_800AF648_b);` — arg dead.

Let me test the second-decl assignment.

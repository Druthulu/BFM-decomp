---
ts: 2026-11-06T06:13:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9OkOEMnyUeTYylSCD2QC
---
r72: 70 uses, 219 insns, crosses 24 calls → param a0.
r73: 9 uses, 35 insns, crosses 5 calls, pointer → loop pointer s2.
r76: 3 uses, 66 insns, crosses 5 calls, pointer → s5 (end ptr) maybe.
r74: 3 uses, 31 insns, crosses 5 calls.
r80: 3 uses, 12 insns, crosses 1 call, pointer → ent.
r75: 3 uses, 35 insns.

Target allocation (with pin): a0 $16, ent $17, loop ptr $18(pinned), then s3 $19, s4 $20, s5 $21 presumably. Wait from the original's dispositions in the target: let's dump the target's greg? We can't (build/ is compiled). But from the diff: target a0=s0, ent=s1, loopptr=s2, and others s3,s4,s5.

Hmm wait, but that's the pinned version. In the pinned version the pin put the loop ptr at $18, and global-alloc assigned the others around it. a0 took $16 (next free after excluding 18? no, it takes the lowest free = $16). ent took $17. Others $19,$20,$21.

Lever-free: we need the order a0, ent, then loopptr.

Priority numbers from alloc_table (cand):
r72 (a0): pri 19178
r73 (loopptr): pri 7714
r80 (ent): pri ? 
r74: ?
r76: ?
r75: ?

Let me see the full table rows for these. The table earlier showed r72 19178 and r73 7714. Let me get rows for 74,75,76,80.

From the lreg data: r74 3 uses/31 insns → pri = floor_log2(3)=1 *3/31*1e4 = 967. r76 3/66 → 454. r75 3/35 → 857. r80 3/12 → 2500.

So priority order: r72 (19178) > r73 (7714) > r80 (2500) > r74 (967) > r75 (857) > r76 (454).

Allocation order from .greg: 78 77 134 140 72 167 73 80 74 75 76. Indeed after the caller-saved ones: 72, then 73, 80, 74, 75, 76. So order matches priority.

So the first callee-saved to be allocated is r72 (a0) — it should get $16! But it got $17 because it conflicts with hard reg 16.

Therefore: the conflict with $16 is the blocker, not the priority. Interesting! So where does $16 come from?

Hmm... could it be that the *spliced TU* still has a hard-reg variable used in the function from the *original file's other code*? No.

Let me look at the .greg dump text for the function and grep the pre-allocation conflict lines. Actually, better: grep the .lreg RTL for "reg/v:SI 16" — I did for `s0` and found 0 in the section 2316-3600. But the function section extends further (2316 to ~?). The .lreg file has 46112 lines and the section might be longer than 1284 lines. The next ";; Function" was not found in 2300-4000. So the function section is long. My grep for s0 in 2316-3600 may have missed the part where $16 appears. Let me grep the whole section (2316 to the next ";; Function" line).

Let me find the next ";; Function" after 2316.

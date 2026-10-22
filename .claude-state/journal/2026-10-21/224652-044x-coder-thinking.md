---
ts: 2026-10-22T04:46:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_PVQ7rTRD551Vo3pYuMP2
---
Now it's crystal clear.

Lever-free (nopin) RTL:
- insn 63: the call, output = hard reg v0 (reg:SI 2 v0).
- insn 65: `(set (reg/v:SI 73) (reg:SI 2 v0))` — the copy of the call result into pseudo r73! (r73 = the local `ret`.)
- insn 68: the test `eq (reg 73) 0` → beqz on r73.
- insn 72: `(set (reg/v:SI 74) (const_int 0))` — r74 = the local `result` = 0.
- insn 74: `(set (reg:SI 80) (and (reg 73) 32768))` — r80 = the AND result (a temp! not the local ret).
- insn 76: the branch on r80.
- insn 81: r82 = the byte load; insn 83: r84 = the xor; insn 85: r74 = (r84 < 1) → the boolean into r74 (the local result).
- insn 97: r74 = 0 (the else path).
- insn 102: `(set (reg/i:SI 2 v0) (reg/v:SI 74))` — the copy to the return reg.

So the pseudos:
- r73 = the call result copy (the local `ret`) — refs 3 (the copy def, the test use, the and use) live 4 → pri = 1*3*10000/4 = 7500 ✓ (matches "r73 used 3 times across 4 insns").
- r74 = the local `result` — refs 4, live 7 → pri 11428 ✓.
- r80 = the AND temp, r82 = the byte load, r84 = the xor temp.

So in the lever-free version, the copy `move v1,v0` (insn 65) IS present in the RTL! It's `(set r73 v0)`. But in the final code it VANISHED because r73 was allocated v0 → the copy was coalesced/removed.

In the TARGET (pinned), r73 (the call result copy) got v1 → the copy `move v1,v0` remained ✓.

So the question: why did r73 get v0 in the lever-free version? Because r73 is a LOCAL allocno? Let's see: r73's live range = [insn 65..74] → blocks 1 and 2. Its hard reg is v0 because the copy from the hard reg v0 was coalesced (gcc's local allocation assigns r73 the hard reg v0 because the copy prefers it).

In the pinned version, r73 could not get v0 because the pinned pseudo (hard reg v0) reserved it → r73 got v1.

So: to make r73 get v1 lever-free, v0 must be unavailable to it. v0 is unavailable if another pseudo takes it in local allocation with higher priority, OR if the hard reg v0 is reserved by a hard-reg pseudo.

Local allocation: the local allocnos (r72, r73, r75, r76, r80, r82, r84) are allocated to hard regs by priority. r73's pri = 7500. Others: r72 (s0, crosses a call), r75/r76 (pri 5000, HI constants), r80 (pri 10000, refs 2 live 2), r82/r84 (pri 10000).

Hmm interesting: r80 (the AND temp) has pri 10000 and r73 has 7500. If r73's pri were > 10000, would r73 take v0 before r80? They'd conflict anyway (both live at overlapping times? r73 is live [65..74], r80 [74..76] → they overlap at 74 → conflict).

The key: which pseudo could take v0 away from r73? The hard regs available: v0, v1, a0-a3, t0-t7, s0-s7.

In the target, r73 got v1 and the value pseudo (r74, the local result) got v0. So in the target, r74 (a GLOBAL allocno, pri 11428) got v0!

Wait — in the target, is r74 global? The pinned dump's order line was "73" (only r73 global). Hmm, in the pinned version, r74 (the local result) doesn't appear in the lreg table at all — because in the pinned version, the local `result` is the HARD-REG pseudo (pinned to $2) → it's not a pseudo → no r74. Instead, the RESULT_DECL is r73? Hmm, in the pinned dump r73 = pri 7500 refs 3 live 4, conflicts v0, prefers v1 → that's the same numbers as the lever-free r73 (the call-result copy)! Hmm, but in the pinned dump r73 is the only global allocno.

Confusing: in the pinned version, the local `result` is a hard-reg pseudo (reg 2) — so the RTL would be `(set (reg:SI 2 v0) (const_int 0))` etc. And the RESULT_DECL would be a pseudo. Hmm, in the pinned dump the lreg table has r72, r73, r75, r76, r77, r80, r83, r85 (8 pseudos) vs lever-free 9 (r72, r73, r74, r75, r76, r77, r80, r82, r84). The difference: lever-free has r74 and r82/r84; pinned has r83/r85 (the temps renumbered).

So in the pinned version: r73 = the RESULT_DECL (pri 7500, refs 3, live 4, conflicts v0, prefers v1) — and the call-result copy pseudo would be r80 (in v1!) per the table ("r80 hard v1, pri 10000, refs 2, live 2, block 1").

Hmm, r80 in the pinned dump has pri 10000 refs 2 live 2 in block 1, while in the lever-free dump r80 = the AND temp (pri 10000, refs 2, live 2, block 1)? Coincidence of numbering.

OK whatever. The important structural insight:

LEVER-FREE RTL:
```
(insn 65) (set (reg/v:SI 73) (reg:SI 2 v0))    <- the copy of the call result into the local `ret`
```
This copy EXISTS in the RTL. It's removed later because r73 gets v0.

For the target, r73 must get v1 (or any reg ≠ v0), so the copy stays.

In local allocation, r73 competes for hard regs. Its preference: it was copied FROM v0 → gcc's local allocation has a "copy preference" (r73 prefers v0). The preference is honored if no conflict.

So to make r73 NOT get v0: another pseudo must take v0 with a higher priority. Candidates in the lever-free RTL:
- r80 (the AND temp, pri 10000 > r73's 7500) — but r80's live range [74..76] overlaps r73's [65..74] at insn 74 → they conflict → r80 gets another reg anyway. Hmm, but which one gets v0? In the lever-free result, r73 got v0 (the AND temp r80 got v1 presumably: mine[25] `andi v0,v0,0x8000` — the andi is IN v0! so r80 = v0 and r73 = v0 too?!

Look at the lever-free mine listing:
```
24 beqz v0      <- the test on r73 → r73 is in v0
25 andi v0,v0,0x8000   <- r80 in v0
26 beqz v0      <- the test on r80 → v0
```
So BOTH r73 and r80 are in v0 (their live ranges don't truly overlap: r73 dies at insn 74 (the andi kills it: REG_DEAD r73 at insn 74) — so r73 is live [65..74) and r80 [74..76) → NO overlap ✓ (they're sequential, not overlapping). Right, the `and` uses r73 and kills it.

OK so both can be in v0.

To force r73 into v1, we need v0 occupied during [65..74] by something else. In the pinned version, the hard-reg pseudo `result` (v0) occupies v0 during... hmm, in the pinned version, the local `result` is a hard reg v0 pseudo whose live range is [insn 72..97] (the defs) — that's AFTER insn 74 → no overlap with r73's [65..74]!

Yet r73 got v1 in the pinned version. So the hard reg v0 was reserved GLOBALLY for the pinned pseudo (not just in its live range) → r73 couldn't use v0 at all.

This is the key mechanism: a hard-reg pseudo (register var with __asm__) reserves its register for the WHOLE function (gcc's local allocation assigns hard regs to hard-reg pseudos first, and other pseudos can only use them outside the hard pseudo's live range... hmm, but here there's no overlap).

Hmm, in gcc's local allocation (`local_alloc`), the hard regs are allocated: first the "fixed" pseudos (hard-reg pseudos) get their regs; then the remaining pseudos are assigned the remaining hard regs — a hard reg assigned to a fixed pseudo is NOT available to others at all (in gcc 2.x, `local_alloc` iterates over the hard regs; for each hard reg, it finds the pseudo that has it as its fixed reg (if any) and assigns it; that hard reg is then not available for other pseudos). YES — in gcc 2.x's local allocation, each hard register is given to at most ONE pseudo (the one with a fixed preference or the highest priority among those that fit), and other pseudos that could use it get "conflict" marks.

Hmm, but then in the lever-free version, r73 (the call-result copy) and r80 (the AND temp) can't BOTH be in v0 if only one pseudo per hard reg... but we saw both in v0 (sequentially). That's the RELOAD phase (reload/reg move elimination) — the "global register allocation" phase handles the pseudos that need specific hard regs (like the AND temp's preferred v0 for the andi instruction). The reload phase can insert moves to satisfy hard-reg preferences after local allocation.

Right! The reload phase (reload.c) inserts register moves to satisfy hard-reg preferences (e.g. the `andi` needs v0 because the mips andi pattern requires specific regs? no...). Hmm, actually the andi was in v0 because r80's preference was v0 (the "copy preference" from the andi pattern?).

OK. Given the complexity, let me consider the practical question: is there ANY lever-free spelling where the call-result pseudo (r73) doesn't get v0?

In the pinned version it didn't because v0 was reserved.

Lever-free alternatives that reserve v0:
1. A pseudo that is live across the whole function and has v0 as a hard preference... e.g. the RESULT_DECL prefers v0 (but it's live only [97..epilogue]).
2. Hmm! What about the reload phase's behavior: if a pseudo has a hard-reg preference for v0 and a copy preference chain...

Hmm, what about this: the AND temp r80 (pri 10000) has a hard preference for v0? If the AND temp is live at the same time as r73 (overlapping), then one of them must be in another reg. Currently they're sequential (r73 dies at the andi).

Can we make the AND temp live OVERLAP the call-result copy? E.g. if the mask test's result is needed while the call result is still live. In the ROM, the andi is in the delay slot of the first branch — so the AND result is computed while the call result is still live? No: the andi kills the call result (REG_DEAD r73 at insn 74) — the andi OVERWRITES r73's register (that's why `andi v0,v0,0x8000` is in-place). In the target, the andi is on v1 (the copy) and the call result's copy is in v1 too — the copy r73→v1 then andi v1,v1.

So in the target: r73 (the call result copy) is in v1 and the AND result is ALSO in v1 (in-place) → so the AND temp r80 is coalesced with r73 (the andi reuses r73's register). In the lever-free: r73 in v0, the andi in v0 → also in-place ✓ (same shape, different reg).

So the ONLY difference is which reg r73 lands in.

So: how to make r73 land in v1 instead of v0? Options:
(a) Make the AND temp (r80) live at the same time as r73 so they conflict, and give the AND temp v0 (higher pri 10000 > 7500) → then r73 gets v1 ✓!

How to make them overlap? The AND result is used by the branch; the call result is used by the AND. They're inherently sequential... UNLESS the AND's value is needed later (e.g. if the mask test result is used again after the boolean is computed)!

E.g. if the source were:
```
if (ret != 0) {
    result = 0;
    if ((ret & 0x8000) != 0) {
        result = (*(u8*)((char*)buf2 + 6) == 0x15);
    }
}
```
The AND result is used only by the branch. But if the source used the mask value again, e.g.:

```
mask = ret & 0x8000;
if (mask != 0) { ... }
```
then the mask's live range extends → but that changes the code (an extra store/load? no, a local var → an extra move).

Hmm, what if the mask test is written as `(ret & 0x8000) != 0` but the value is ALSO used in the boolean? e.g. `result = ((ret & 0x8000) != 0) & (...)`? That changes the code.

(b) Make r73's priority LOWER so it loses v0 to another pseudo. r73's pri = refs*2^floor(log2 refs)*10000/live. Currently refs 3, live 4 → 7500. If r73 had refs 2 (live 3) → 1*2*10000/3 = 6666; or refs 3 live 5 → 6000. Meanwhile another pseudo (r80, pri 10000) would take v0 — but r80 doesn't conflict with r73 (sequential) → hmm, in local allocation, can two pseudos share a hard reg if their live ranges don't overlap? YES (that's normal: local allocation assigns each hard reg to one pseudo, but the reload phase can move things around; actually gcc's local allocation DOES allow multiple pseudos in the same hard reg if they don't conflict — the conflict graph).

Hmm, in gcc 2.x's local allocation, each hard reg is assigned to exactly one pseudo, and other pseudos that need it get a conflict (they're forced to other regs) — no wait, that's not right either, because the reload phase can move pseudos in and out of hard regs.

Honestly, empirically: the AND temp got v0 and the call-result copy also got v0 — they were in different hard regs at different times and gcc handled it via the reload phase (moving r73 into v0 for the test, and r80 into v0 for the andi).

Hmm, in the lever-free code, the sequence is: `beqz v0` (r73 in v0), `andi v0,v0,0x8000` (r80 in v0 — r73 was copied? no! the andi is in-place on r73's reg because r73 dies there).

So r73 = v0 and r80 = v0 as well (they share the reg since r73 dies at the andi). In the target, r73 = v1 and r80 = v1.

So really the question is: why v0 vs v1 for the pair?

In local allocation, r73 (the call result copy) has a copy preference: it was copied FROM v0 → prefers v0. r80 (the AND temp) also prefers v0 (the andi pattern? no—the reload phase assigns it).

Since both prefer v0 and are sequential, gcc can give them v0 ✓ (the lever-free case).

In the pinned case, v0 was reserved → they got v1.

So the lever-free way to deny v0 to r73: make r73 NOT prefer v0 and have something else take v0. r73's preference for v0 comes from the copy `(set r73 v0)` — gcc's copy propagation in the reload phase: the "reload" phase removes the copy if r73 is allocated v0.

What if r73's copy source were not the hard reg v0 but another pseudo? Then r73 wouldn't prefer v0. E.g. if the call's output were a pseudo instead of the hard reg v0! When does gcc 2.7.2 use a pseudo for the call's output? If the call's return value is used in a context... Hmm, in the RTL above: `(call_insn 63 ... (set (reg:SI 2 v0) (call ...)))` — the output is the hard reg v0. Then `(set r73 v0)` copies it.

In the TARGET, the same RTL would have `(set r73 v0)` and r73 allocated v1 → the copy remains ✓.

So we need r73 to not get v0. r73 is a LOCAL allocno? It's in the lreg table; in the lever-free dump, the .greg order line was "74 73" → BOTH r73 and r74 are global! So r73 (the call result copy) is a GLOBAL allocno in the lever-free version, and in the pinned version r73 is also global ("73").

Hmm, in the pinned dump, the order line was "73" and r73 had pri 7500, refs 3, live 4, "conflicts v0,sp, prefers v1" → that's the same numbers as the lever-free r73 (the call-result copy)! So in the pinned version, r73 = the call-result copy (global, conflicts v0 → because v0 is the pinned pseudo's reg → so r73 can't be v0 → it prefers v1 → gets v1 ✓✓✓).

So in the pinned version, r73 is global because it conflicts with the hard-reg pseudo (v0). In the lever-free version, r73 is ALSO global ("74 73" order) but "conflicts sp, prefers v0" — it prefers v0 and there's no hard-reg conflict → it gets v0.

So: r73 is global in both. In global allocation, the hard reg preferences are honored: r73 prefers v0 → gets v0 (lever-free). In the pinned version, r73 conflicts v0 (the pinned pseudo holds v0) → gets v1 ✓.

KEY: to make r73 get v1 lever-free, we need r73 to CONFLICT with v0 — i.e. some OTHER pseudo must hold v0 during r73's live range [65..74]. Which pseudo could hold v0 there? The RESULT_DECL (r74 in the lever-free dump, pri 11428, conflicts v0,sp → it got v1). Hmm, in the lever-free dump r74 (the local result) conflicts v0 → so r74 is the one conflicting, and it got v1.

So: if the local `result` (r74) could take v0 instead, r73 would be forced to v1. But r74 conflicts with v0 BECAUSE r73 has v0. Circular: the allocation is simultaneous; the conflict graph is symmetric. r73 and r74 conflict (their live ranges overlap? r73 [65..74], r74 [72..97] → overlap at 72-73 ✓) → so they can't share v0. r73 prefers v0 (copy preference), r74 has no preference (or prefers v0 too? "conflicts v0,sp" and no "prefers" → r74 has no preference).

In global allocation, when two pseudos conflict and one prefers v0: the preferring one gets v0 (r73), the other gets something else (r74 → v1) ✓ consistent with the lever-free result.

In the pinned version, r73 conflicts with the hard reg v0 (the pinned pseudo) → it can't have v0 → it prefers v1 → gets v1 (if free) ✓, and r74 (the local result — in the pinned version it's the hard-reg pseudo v0, not a pseudo) hmm.

OK!! So now the question is crisp: **can we make the local `result` (r74) prefer v0 strongly enough to take it from r73?**

r74's preferences: in the lever-free dump, r74 has no "prefers" note → no hard-reg preference. r73 "prefers v0" (the copy preference from the call's v0).

To give r74 a preference for v0: hmm. Copy preferences come from copies: if the local `result` were copied FROM v0... no.

Hmm, what about the RESULT_DECL? In the lever-free dump, r73 = the call-result copy (prefers v0) and r74 = the local result (conflicts v0). And the RESULT_DECL? The final copy `(set v0 r74)` — the destination is the HARD reg v0 (the return). So there's no RESULT_DECL pseudo! Interesting: the RTL's final insn is `(set (reg/i:SI 2 v0) (reg/v:SI 74))` — a direct copy to the hard reg v0. So the RESULT_DECL was optimized away.

So the pseudos are: r73 (call result copy), r74 (the local result), r80/r82/r84 (temps), r72 (param_1), r75/r76 (HI consts).

Now: in the TARGET, the value is computed into v0 (lbu v0, xori v0, sltiu v0) and the final copy to v0 is absent → so r74 (the local result) was allocated v0 and the final copy `(set v0 r74)` was coalesced away ✓. And r73 (the call result copy) got v1 → the copy `(set r73 v0)` remained as `move v1,v0` ✓.

So in the TARGET: r74 = v0, r73 = v1.
In the lever-free: r74 = v1, r73 = v0.

The difference: in the target, v0 was unavailable to r73 (reserved by the pinned pseudo) → r74 (no preference) took v0.

Hmm, so how does the allocation decide between r73 and r74 for v0 in the lever-free case? r73 prefers v0 (a copy preference) → r73 wins; r74 gets v1.

To flip lever-free: r74 must have a HIGHER priority than r73 in the global allocation, or r73 must lose its v0 preference.

r73's pri = 7500 (refs 3, live 4). r74's pri = 11428 (refs 4, live 7) — r74 has a HIGHER priority but no preference for v0, and r73 has a preference for v0. In gcc's global allocation, the preference (copy preference) acts as a tiebreak/bonus.

Hmm! So if r74 had a preference for v0 too, or if r73 lost its preference...

How can r74 get a preference for v0? A copy preference arises when a pseudo is the source of a copy to/from a hard reg. r74 is the source of the final copy `(set v0 r74)` → that gives r74 a preference for... hmm, the copy's src prefers the dst's reg? In gcc's copy preference computation, a copy `(set a b)` creates preferences: a prefers b's reg and b prefers a's reg (mutual copy preferences). So r74 (src of the copy to v0) should PREFER v0!

Hmm, but the dump shows r74 with no "prefers" note... maybe the dump's "prefers" only lists certain things.

OK, empirically: r73 (pri 7500, prefers v0) vs r74 (pri 11428, prefers v0 via the final copy): in the lever-free result r73 got v0. Hmm, so maybe the preference isn't decisive and the priority is: r74 (11428) should have won v0! But it didn't...

Unless r74's live range makes it ineligible for v0: r74 is live [72..97] and r73 [65..74] → they overlap only at [72..74]. In global allocation, a pseudo's hard-reg assignment must avoid conflicts with the hard regs' live ranges. r73's live range [65..74] includes the hard reg v0 (the call's output at insn 63) — so during [63..74], v0 is occupied by the call's hard-reg output → r74 (live [72..97]) CONFLICTS with v0's occupied range [63..74] → r74 can't be v0! ✓ That's why r74 "conflicts v0"!

And r73 (live [65..74]) — it's live during [63..74] where v0 is occupied by the call's output... hmm, but r73 IS the copy FROM v0, so it takes over v0 at insn 65.

So in the lever-free case, v0 is taken by the call's output → the copy r73 inherits it → r73 = v0.

For r74 (the local result, live [72..97]) to take v0, the call's hard-reg output v0 must not be live at [72..74]... The call's output v0 is live from insn 63 (the call) until its last use. Its last use is the copy to r73 at insn 65 — but the copy is coalesced: in the RTL, v0 is live [63..65] only. Hmm, but the andi at insn 74 uses r73 (not v0).

Hmm, so why does r74 conflict with v0? Because r74 is live at insn 72-74 and v0 (the call's output reg) is live until insn 74? In the RTL, the copy `(set r73 v0)` at insn 65 kills v0 (REG_DEAD v0) → v0 is live [63..65].

Hmm, so r74 shouldn't conflict with v0 from that. Unless the "conflict" in the .greg dump is computed on the ALLOCATED hard regs (after local allocation): r73 got v0 → and r74 conflicts with r73's v0.

OK, I need to stop analyzing and start experimenting. The decisive question: can we get r74 (the local result) into v0?

Experiment idea: make the local `result`'s live range start LATER so it doesn't overlap r73's [65..74]. In the ROM, the value's first def is at insn 72 in the RTL? Let's see: the RTL for nopin:
- insn 72: `(set r74 0)` — the then-branch's `result = 0` — so r74 is live from insn 72 (which is after insn 74's `and`? no: insn 72 < insn 74!). The RTL insn numbers: 65 (copy r73←v0), 68 (branch on r73), 72 (set r74=0), 74 (set r80 = r73 & 32768), 76 (branch on r80), 81 (r82 = load), 83 (r84 = xor), 85 (set r74 = (r84<1)), 91 (jump), 97 (set r74 = 0), 102 (set v0 = r74).

So r74's live range = [72..97] (def at 72, last use at 102 → hmm, live 7).

r73's live range = [65..74].

They overlap at [72..74] ✓ → they conflict.

To avoid the overlap: make the local result's first def LATER than insn 74. In the ROM's target, the value's first def (the `move v0,zero` at ins 28 = the mask-fail path) comes after the andi (ins 26/27). In the nopin RTL, the def at insn 72 is the then-branch's `result = 0` — which the scheduler placed BEFORE the andi (insn 74). In the target, the `move v0,zero` is in the delay slot of the branch at ins 27 — i.e. AFTER the andi (ins 26) ✓.

So in the target, the local result's first def is after the AND. In our lever-free code, the scheduler placed the `result = 0` before the andi (in the delay slot of the first branch, ins 25 in the machine code = the andi's position). Hmm, in the nopin machine listing:
```
24 beqz v0       <- branch on r73 (RTL 68)
25 andi v0,v0,0x8000   <- RTL 74 (the AND, in the delay slot)
26 beqz v0       <- branch on r80 (RTL 76)
27 move v1,zero   <- RTL 72 (set r74 = 0) in the delay slot
```
So the machine order differs from the RTL order (the scheduler moved the AND before the `set r74=0`).

In the target:
```
24 move v1,v0
25 beqz v1
26 andi v1,v1,0x8000
27 beqz v1
28 move v0,zero    <- the set r74=0 in the delay slot
```
Same structure ✓ (the AND before the `set r74=0`).

So both have the local result's first def AFTER the AND at the machine level. But the RTL order (which determines the live ranges) has the `set r74=0` (RTL 72) BEFORE the AND (RTL 74) → r74 is live from 72 → overlapping r73 (live [65..74]) → conflict.

If the RTL had the AND before the `set r74=0`, then r74 would be live [74..97] → no overlap with r73 [65..74] → no conflict → r74 could take v0!

How to change the RTL order? The RTL order follows the source order: `result = 0;` comes BEFORE the `if ((ret & 0x8000) != 0)` test in the source. To make the AND come first in the RTL, the source should have the mask test BEFORE the `result = 0` assignment:

```
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
    } else {
        result = 0;
    }
} else {
    result = 0;
}
```
Here the `result = 0` (in the else of the inner if) comes after the AND in the RTL ✓. But then the machine code might differ (the delay slot contents).

Hmm, but the target's structure has the "mask==0 → result=0" path in the delay slot of the second branch. Let's just try it!

Also: with `result` defined only in the two branches, the "live at start" changes.

Let me also try:
```
if (ret != 0) {
    if ((ret & 0x8000) == 0) {
        result = 0;
    } else {
        result = X;
    }
} else {
    result = 0;
}
```

And a version where the value is assigned only in the inner branch and the outer else returns 0 directly:
```
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        result = X;
    } else {
        result = 0;
    }
} else {
    result = 0;
}
```

Let me generate several such variants and score them. This is the most promising lever yet (statement order).

Let me write:
y1: as above (inner else assigns 0).
y2: same but the inner test written as `(ret & 0x8000) == 0` with the branches swapped.
y3: the value assigned via a temp then to result.
y4: like y1 but with the outer else first.
y5: like y1 with `unsigned char` result.
y6: y1 with the result declared at the top vs after.

Let me write them quickly.

Time: 23:15. I'm over budget for this item but this is the decisive idea. Let me spend 10 more minutes, then move on.

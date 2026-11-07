---
ts: 2026-11-06T07:47:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4EgG7HFyy3N14Fy3uurw
---
In v5: r79 in 4 (a0) — the loaded value; r80 in 3 (v1) — the pointer. So r80 (w3d) got v1. Why not a0? Because at r80's birth, a0 (r79) is still live? r79 dies at `L.w3C = w3c` (insn 59). r80 is born at `w3d = (u32)L.o1` (line 452, before the stores). Actually source order: `L.w3C = w3c; w3d = (u32)L.o1; L.v58[2] = 0;` then the GTE block. So r80 is born at ~line 452 (insn ~59). If r79 dies at the store at insn 60, and r80 is born at insn 59, they overlap → r80 can't use a0 → v1.

In the target, the addiu for the pointer is at insn 60 (after the store at 59), so r80 is born after r79 dies → reuses a0. So I need the pointer's birth to be AFTER the store. In source, `w3c = (u32)L.o1;` comes right after `L.w3C = w3c;` — but sched1 may move the addiu. The target's addiu is at 60, after the store at 59. In v5 mine, addiu at 59, store at 60 — reversed!

Why? Because the store `L.w3C = w3c` (sw a0,60(sp)) and the addiu `w3d = L.o1` are independent; sched1 ordered addiu first. In the target, store first. This is a sched1 order issue. Hmm.

But note: in the single-variable base (w1), the same two statements are `L.w3C = w3c; w3c = (u32)L.o1;` — and the diff showed mine: `sw s5,60(sp); addiu s5,sp,16` — store then addiu, same register! So with the single variable, the order is correct (store then addiu). The single-variable version's only problem is the register (s5 vs a0). The split version fixes the register but breaks the order/register of the pointer.

So: keep the single variable, and make it conflict with s5 (extend twicep). OR find a spelling where the single variable gets a0.

What if we keep the single variable w3c but ALSO declare it in a way that makes its range shorter? No, the variable is reused.

Let me think again about the conflict. Maybe the natural C's r79 (w3c) conflicts with s5 because of a DIFFERENT reason: the load `w3c = *(u32*)twicep` uses twicep at insn 40, and w3c is born at insn 40. If the load's REG_DEAD for twicep is placed AFTER the def, they'd conflict. In w1, no conflict. Could a real-C change move twicep's death one insn later? For example, if the load is `w3c = *(u32*)twicep;` and the next statement also uses twicep... 

Wait — what if the original source reads twicep THREE times but two of them are CSE'd into one? E.g.:
```
L.w38 = *(u32 *)twicep;
w3c = *(u32 *)twicep;
...
L.w3C = *(u32 *)twicep;   // third
```
cse might CSE the 2nd and 3rd if no aliasing store. There are stores to L (stack) between; if cse decides they don't alias twicep, it CSEs. Then the third read is free (reuses w3c's value), but twicep's live range extends to the third read? No — cse replaces the load with the register holding the value; twicep's use disappears. So twicep's liveness wouldn't extend.

Hmm.

What if the original passed twicep to the final `func_800174DC()`? Target's final jal has no arg setup (delay slot is `sh v0,48(sp)`), so no.

Let me reconsider the target's s5: it's saved at entry and restored at exit. If twicep were dead at insn 40, the allocator could have put it in a caller-saved reg for the pre-call part? It crosses 4 calls, so it must be callee-saved (s5). Fine.

Is there any chance the target's r79 is NOT w3c but the loaded value is a different pseudo? In the target, `lw a0,0(s5)` then `sw a0,60(sp)` — the value flows through a0. If the source had `L.w3C = *(u32*)twicep;` the compiler would emit `lw v0,0(s5); sw v0,60(sp)` immediately (or scheduled). But the target has the load at 40 and the store at 59 with a0 held. So the value is a variable.

Let me look at the target's instructions between 40 and 59 to see if a0 is used for anything else. From the dump: after `lw a0,0(s5)` at 40, the next insns are the v48/v50/v58 stores (lhu/sh), and a0 is not touched until `sw a0,60(sp)`. So a0 is dedicated to w3c.

Now, could the natural C declare w3c as `register`? No (forbidden and it's a lever).

Let me try: make w3c's live range start EARLIER so it conflicts with s5. If w3c is defined before twicep's last use, e.g. swap the order so the w3c load is BEFORE the L.w38 load:
```
w3c = *(u32*)twicep;   // at 37
L.w38 = *(u32*)twicep; // at 40
```
v1_swapreads scored 18 (bad). Hmm.

What if w3c is used in the L.w38 computation? No.

Let me look at the .greg for v5 vs base to see r79's conflicts and preferences. In v5, r79 in 4 with no preferences line. In w1, r79 preferences 21. 

The "preferences 21" in w1 comes from the copy `lw s5,0(s5)`? Actually local-alloc's combine_regs can suggest the hard reg s5 for the loaded value because the load's source and dest are the same pseudo? No. The preference for 21 (s5) is a copy preference from `lw s5,0(s5)`: the destination pseudo (w3c) is suggested s5 because the load's address base is s5? combine_regs ties a pseudo to a hard reg when there's a copy; the load `lw s5,0(s5)` is a load into s5 from (s5), where the base s5 dies. Hmm, maybe the preference is because twicep (s5) dies at that insn and the load's dest can reuse it.

In v5, splitting means the load is `lw a0,0(s5)` (no s5 preference for w3c? or the preference exists but conflicts differ).

OK, new approach: maybe the natural C uses a local pointer variable for the loaded value, e.g.:
```
u32 *wp;
...
L.w38 = *(u32 *)twicep;
wp = (u32 *)twicep;
w3c = *wp;
...
L.w3C = w3c;
w3c = (u32)L.o1;
```
No.

Let me look at the score-1 candidate from the engine more concretely. The moves: "R7 block @441" then "R12 width tmp0 u32->u16 @413". Let me use --explain with --path to reproduce and see the diff (score 1) and maybe it prints the NEEDED sites/text. Let me try:

/usr/bin/python3 tools/delever_search.py --explain src/md_MAIN_026/md_MAIN_026.c func_800CB900 --path "R7 block @441|R12 width tmp0 u32->u16 @413"

The move names must match exactly. Let me run it and see. It may also print the final text? Let me check the explain function further (lines 680-740).

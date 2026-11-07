---
ts: 2026-11-06T12:55:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gAWs5JyzoNvCVsHYCJCd
---
Key: `adjust_priority(prev)` is called when a predecessor becomes ready, and adjust_priority boosts birthing insns to max_priority. Also ready[] is a sorted array (queue_insn inserts sorted by priority).

The birthing check: `bb_live_regs[offset] & bit` — pseudo not live at block entry → returns 0. Hmm, so no boost. Unless... after reload? No, sched1 is before reload.

Hmm wait, actually — which insn is the "birth"? Let me reconsider: maybe it's not the lui. Let me reconsider what makes sched put the lui/ori before the sh.

All priorities 1. The ready list is sorted by priority only; equal priorities keep insertion order: `ready[new_ready++] = prev;` appends at the end. And the pick is ready[0] (with schedule_select possibly reordering by hazard).

Initial ready list: `make_ready_list` walks backward from the block end, adding insns with no successors. Hmm, actually let me check: does it add in reverse order (last first)?

If the initial ready list contains (in order): [last insn, ..., sh, ...]. The pick takes ready[0] = the last insn of the block. As insns are scheduled, predecessors are appended at the end.

So the order in which insns get scheduled is: initial ready in reverse-source order, then newly-ready appended.

For the join block, the source order is: sh(Y), C400, C78, C64, CE, vsum-loads, S8, S10, S12, the RMW, out+=5...

The last insns (no successors) are stores and the final ones. Reverse order → the ready list starts with the LAST insn in the block.

The lui/ori become ready when their successor (the sw C64) is scheduled. The sw C64 is scheduled when... it's ready from the start (a store). Its position in the initial ready list = reverse source position.

So: initial ready list order (reverse source): ..., S12, S10, S8, vsum-store, ..., CE, C64(sw), C78, C400, sh(Y), ...

Hmm, the ready list is sorted by priority (all 1) then hazard. With equal priorities, `schedule_select` may pick by hazard; otherwise ready[0].

Wait, but `queue_insn` inserts in sorted order; and the initial list from make_ready_list — let me check it adds in which order.

This is getting deep. The empirical result: in mine, the order of final insns is lui, ori, sh. In target: sh, lui, ori.

Since backward scheduling places scheduled insns at the end (last = latest position), the insn scheduled FIRST goes latest. Mine: sh scheduled first (placed at 143, latest of the three), then ori, then lui. Target: ori first (placed last at 143), then lui, then sh (placed at 141).

So in the target, the sh was scheduled AFTER the lui/ori. In mine, BEFORE.

Now: after the sw C64 is scheduled, the ori becomes ready and is appended to the ready list. The sh was already in the ready list from the start. If the ready list is FIFO among equal priorities, the sh (older) is picked first → mine. For the target, the ori must have been picked first — meaning either the ori had higher priority, or the ready list reordering put it first (schedule_select's hazard selection picks the insn with the largest potential hazard, not necessarily ready[0]!).

`schedule_select`: among the equal-priority group, it picks the one with the largest potential_hazard. So the *function unit hazard* decides ties! The potential_hazard of a lui/ori vs a sh. Hmm, that's machine-dependent and hard to influence from C... but it depends on the unit of the insn.

Hmm, but both target and mine use the same machine; the difference must come from the ready list contents at that moment.

OK. Time to stop on item 2 — I have 32 tries and ~35 minutes. Record WALL.

Wall tag: `sched1-birth-order` — "sched1 orders two independent insn births opposite to source; reorder moves the other". Hmm, our case is a constant build hoisted above an independent store. Maybe a new tag `<pass>-<what>`: `sched1-const-hoist` — "sched1 hoists the 0x64808080 lui/ori pair above the preceding s16 store; only the memory barrier separates them". That's a legitimate new tag per the brief ("or a new `<pass>-<what>`").

Hmm, but walls.txt already has `sched1-birth-boost` = "sched1 vs local-alloc birthing-insn priority boost against a local-alloc constant". Not quite.

I'll use a new tag: `sched1-const-pair-hoist` — defined in the results evidence.

Wait, but PARTIAL is also possible: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". Since the only kind is barrier, a PARTIAL would mean keeping the barrier → but then it scores 0 with the barrier = that's just orig, not a crack. Hmm: PARTIAL lists kinds still kept; if I keep the barrier, PARTIAL:barrier — but then it's the orig body, which is not a lever-free body at all. The brief says PARTIAL = win.c scores 0 keeping only those levers. A win.c that keeps all row kinds is a WALL, whatever it scores. Since the only kind is barrier and any scoring-0 body must keep it, this is a WALL.

So: WALL, best = 2 (lowest score of a lever-free body).

Now let me move to item 3. But first, let me record notes and results for items 1 and 2 as I go (the brief says append rows per item; and don't stop between items).

Let me write the results rows now (one command per action — the brief says "One action per command: a results.tsv fix is its own step"). I'll append the row for item 1 and item 2 in separate commands? The rule is about fixing errors. Appending two rows in one command is fine but let me be safe and do them as separate appends... Actually "Per item append exactly one row" — I'll append one row per command.

Row format: `dir file func kinds result best tries wall evidence` (tabs).

Item 1: dir func_80186CE0__ov_SC02_027_jr_8017D898, file src/ov_SC02_027/ov_SC02_027_jr_8017D898.c, func func_80186CE0, kinds barrier, result MATCH, best 0, tries 5, wall -, evidence "do{}while(0) around the fifth-word store keeps the u16 adds out of the t load-delay slot (target nop); pins $7/$3 unchanged, barrier gone".

Item 2: dir func_8018BCD4__ov_SC03_001_jr_8018B8DC, file src/ov_SC03_001/..., func func_8018BCD4, kinds barrier, result WALL, best 2, tries 32, wall sched1-const-pair-hoist, evidence "sched1 hoists the 0x64808080 lui/ori pair above the preceding sh y store in the join block; 203 ins, only the barrier separates them".

Let me first write win.c for item 1 (copy w3.c → win.c) — required: "each MATCH/PARTIAL has its win.c scoring 0".

Then append rows.

Then moves.md appends after each item.

Let me do item 1's win.c + notes + moves line, then item 2's.

Actually, let me batch efficiently but respect "one action per command" for results.tsv fixes only. I'll do:
1. cp w3.c win.c (item1)
2. append results row 1
3. append moves line 1
4. write notes (item1)
... same for item2.

That's a lot of commands; let me combine non-results actions reasonably.

Actually the instruction "One action per command: a results.tsv fix is its own step, never folded into a check command" refers to *fixing* results.tsv. Appending rows is the normal action. I'll do one row per command to be safe.

Let me proceed.

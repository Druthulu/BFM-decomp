---
ts: 2026-10-22T01:12:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Ekfheqs03AcO1OvI7t1Z
---
The project's practice is to write the coder log in phase-ends/current/logs/T11.cG14.md. So I'll write it (consistent with the brief's LOG field and the project practice).

Let me look at an existing shard log (e.g. T11.cG08.md) to match the format. Let me peek at a short one.

Hmm, "Never read phase-ends/*/logs/" — my system prompt says: "Never read `phase-ends/*/logs/`". Hmm! But those are the *current* phase's logs... The rule says never read them (the context-management rule). Hmm, but I need the format. Let me just write a reasonable log following the brief's spec: "timeline per item, moves that cracked, walls with evidence" and "LOG EXTRA: per item, in the log timeline, record start/end time (date), minutes, and tries".

Let me not read the other logs (per the rule) and write my own in the brief's terms.

Now let me finish:
1. Write notes.md for the 5 WALL items.
2. Rewrite results.tsv with all 11 rows.
3. Append the moves.md lines for the 5 WALL items (and fix the earlier WALL line for func_8018656C — it's append-only, so I'll add a MATCH line noting it supersedes).
4. Write the log file.
5. Clean up: remove the dump dirs? I didn't create cc1 dumps. Remove the scratch? The brief says the shard dir stays < 200 MB and "--keep scratch is removed after use". My item dirs have many variant .c files (small). The .run/P36/engine/score scratch — that's the tool's own scratch (not mine).

Let me check the shard dir size at the end.

Let me first write the notes for the 5 WALL items. Let me be efficient and write them in one batch (5 Write calls).

Wall items and their mechanisms:
1. func_80183098 (best 10): cse-const-addr — cse's find_best_addr rematerialises the +4 address for cam->y (lui+addiu) instead of keeping the base in the reg; only an opaque (asm) base keeps `lh v1,4(s1)`. A plain-C base is always a known constant, so cse may rematerialise it.
2. func_8018C730 (best 6): flow-unused-result — the asm materialises a dead constant (the address of func_80172710 / 0) into v0 at the return; a void function's return value is dead, so plain C drops it (18 vs 23 ins). The lever is only removable by a signature change (not allowed).
3. func_8017D96C (best 2) and func_8017EA24 (best 2): the two levers are on v1 (the mode) and e (a pointer). The v1 lever -> `v1 = (s16)v1;` (value-preserving), the e lever -> an empty do-while(0). That gets to 2: one instruction (the `li a0,409` vs `lw v1,32(s0)` order in the case0 block) is scheduled the other way. A cast on e (which would reach 1) truncates the pointer → not faithful.
   Tag: `sched-order-swap`? Hmm, let me name it: `sched1-order-li-load`.
4. func_80191020 (best 2): the lever on vol blocks sched1 from hoisting the PAN multiply ahead of the vol multiply. `vol = (u16)vol;` (value-preserving) restores that, but one instruction is scheduled differently: the reorg puts the `andi a1,a1,0xffff` in the bne's delay slot where the target speculates the `sll a2,a2,0x8`. Tag: `sched1-reorg-delay-slot`.

Hmm, for the walls.txt tags: the wall tag must be "a tag from .run/P40/T11/walls.txt or a new `<pass>-<what>`". So new tags are fine (defined in the coder's results evidence).

Let me now write everything. First the notes files (5 Write calls, can be done in parallel? The Write tool calls are independent → I can issue several in one message).

Let me write them.

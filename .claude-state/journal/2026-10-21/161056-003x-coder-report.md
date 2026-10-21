---
agent: ext-T11.cG08
label: T11.cG08
status: done
commit: 
---
done

Two items finished, both WALL (no lever-free body reached score 0); the remaining 7 were triaged only.

- func_80145C54__func_80145C54: WALL, best 6 of 38 insns, 746 tries, wall `cse-copy-merge`. Target holds `a1` in $5 and `v1` in $3 with a live `move a1,v1`; without the pin cse's `make_regs_eqv` folds the `a1 = v1` copy into one pseudo. `s16 a1` keeps the copy but both still land in $3. win.c kept (score 6).
- func_801468C8__func_801468C8: WALL, best 2 of 23 insns, 599 tries, wall `sched1-order`. Without the $3 pin, sched1 emits the two loop `addiu`s in birth order, and the source order that reproduces the target's increment order flips the regalloc to $3/$6 — the two residuals are mutually exclusive. win.c kept (score 2).

Recorded: `.run/P40/T11/G08/results.tsv` (2 rows), two lines appended to `.run/P40/T11/moves.md`, log at `phase-ends/current/logs/T11.cG08.md`. Scratch object dir `.run/P40/T11/G08/scr` removed; no compiler dumps were produced. Shard is 800 KB.

Not reached (developer restart, no rows written): func_8014C308 (17), func_8014FD54 (9), func_801536DC (11), func_801580B4 (8), func_801581AC (8), func_8017849C (two pins on one line — needs the declaration rewritten, not deleted), func_8018655C (58); those scores are pin-line removal only.

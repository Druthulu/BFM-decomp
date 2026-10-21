---
agent: ext-T11.cG10
label: T11.cG10
status: done
commit: 
---
done

Item 1 of 7 finished (developer pause-for-restart); items 2-7 left unfinished with no results.tsv rows.

- func_801627E8__ov_SC01_077_jr_8015C32C — MATCH, best 0, wall `-`. The launder+pin pair is replaced by a call-site cast `((void (*)(u8 *))D_801896C0[idx])(p)`: the call argument is what materializes `&D_8011F750` into `$a0` (lui/addiu/lbu 0(a0)), so the re-tie asm and the `register __asm__("$4")` pin are both gone. win.c scores 0 (19 ins, byte-identical), no pin/launder/asm/volatile, no declaration outside the body changed.
- Evidence: "launder+pin both gone: call-site cast ((void (*)(u8 *))D_801896C0[idx])(p) makes the arg materialize &D_8011F750 into $a0 (MAIN_012 twin shape), same lui/addiu/lbu 0(a0)".
- Deliverables: `G10/results.tsv` (1 row), `G10/func_801627E8__.../win.c` + `notes.md` + `orig.c`, one `moves.md` line, log `phase-ends/current/logs/T11.cG10.md`.
- No src/, config/, tools/, build/ or other-shard file touched; no make, no git, no commit. Shard dir 440 KB; no cc1 dump dirs were created (the sweeps compile objects only, which the scorer deletes), so there was nothing to `rm -rf`. The background sweep for items 2-7 ended on its own.
- Items 2-7 (func_80180D54, func_801815D4, func_8018483C, func_8017DA30, func_80184828, func_8017D81C) are untouched: no results rows, `orig.c` + first candidates + target disassembly (`G10/tgt.txt`) are on disk, and the log records the per-item target-asm observations for the next coder.

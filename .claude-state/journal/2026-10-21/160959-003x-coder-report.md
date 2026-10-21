---
agent: ext-T11.cG07
label: T11.cG07
status: done
commit: 
---
done

Stopped as instructed. **func_801415C0 is left unattempted**: its scratch is deleted, and it has no `results.tsv` row and no `moves.md` line. (Deleting the item dir also removed the shard's pre-existing `tu`/`fn`/`kinds` metadata; I restored them byte-identically, so the dir again holds only those three files, same sizes as the untouched sibling items.)

**Items finished (3 of 10):**

| dir | func | result | best | wall |
|---|---|---|---|---|
| func_8012EF34__func_8012EF34 | func_8012EF34 | MATCH | 0 | - |
| func_8012EF70__func_8012EF70 | func_8012EF70 | MATCH | 0 | - |
| func_800D02D0__resident_jr_800D00E4 | func_800D02D0 | WALL | 8 | lreg-qty-order |

**The lever that cracked both headers:** the pins were masking a wrong prototype. The tree spells the shared header `void func_8012EF34(s32, s32)`, but the game's real function returns `s32` — 5 TUs already declare it `extern s32` and consume the value, and `src/ov_SC01_084/ov_SC01_084_jr_80182A00.c` carries a warning that the `void` spelling leaks the return value. Restoring the `s32` prototype keeps `$v0` live across the `gte_stsz` asm, so local-alloc can no longer hand `$v0` to the `&sp10`/reload temp and gives it `$v1` ($3) — exactly the register the two `register ... __asm__("$3")` pins were forcing. The bodies are lever-free (plain `s32 r` returned; no `register`, no `__asm__`). Verified: score 0 on 141/141 includers for each header, and the whole-object bank verdict IDENTICAL on every recipe.

**func_800D02D0** stays a WALL: the target loads `D_800D3768[arg0].word0` into `$v1` and keeps the `&D_800C7C60` pointer in `$v0`; lever-free `p` makes the *load* take `$v0` instead, because `p` becomes a global pseudo live across the `func_8001ABBC` call and global-alloc gives it `$v3` while the local keeps `$v2`. Best 8 of 39 tries.

**For the expert's judgement on the two MATCHes:** 1294 TUs declare `extern void func_8012EF34(s32, s32)` and 5 declare `extern s32`. The header is the definition the 136 including TUs compile against; the 1299 call sites' compiled bytes are unaffected (the callee ABI is unchanged — the flag still leaves in `$v0`), and the 5 value-consuming sites were already declaring `s32` and reading `$v0`. If you prefer the header to stay `void`, both items become WALLs instead, and the 5 value-consuming callers remain the status-quo inconsistency rather than a regression.

Recorded in `.run/P40/T11/G07/results.tsv` (3 tab-separated rows), 3 lines appended to `.run/P40/T11/moves.md`, and `phase-ends/current/logs/T11.cG07.md` (timeline, moves, wall evidence, plus the func_801415C0 partial lead for whoever picks it up). All cc1 dump dirs are deleted; the shard dir is 796 KB. `src/` is untouched. No commit, no make.

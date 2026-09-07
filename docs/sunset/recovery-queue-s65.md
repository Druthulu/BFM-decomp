# Recovery queue — the step-2 lane, QUEUED for the next session (built S65, 2026-08-29)

`wave-harvest-is-a-pipeline-step` step 2 (RECOVER the failure set) was SKIPPED for every wave
this session and for the earlier t5b–t5r waves. This file is that backlog, classified. Drew's
instruction (S65): build it, do NOT run it — run it next session.

**Population: 69 unbanked wave targets** — 47 with a draft on disk, 22 errored/no-draft.

## Lane A — GATE-DROPS (14): `match_one` says MATCH, the whole-binary gate refused
These are NOT codegen problems. The body is byte-correct in isolation; the refusal is
declaration/TU plumbing or the §8e JTBL_PADS rodata class. Probe first — it is $0:

```
tools/recover_integration.py --draft-dir <dir> --binary <bin> --no-propagate --probe-only
# then, for a named+transformable blocker, drop --probe-only and add --commit
```
| binary | function | ins | wave | draft |
|---|---|---|---|---|
| ov_SC01_001 | func_8017F830 | 18 | t5c | `.run/t5c/sonnet/func_8017F830.c` |
| ov_SC01_001 | func_8017F830 | 18 | t5e | `.run/t5e/opus/func_8017F830.c` |
| ov_SC04_011 | func_8018FE20 | 213 | t5i | `.run/t5i/opus/func_8018FE20.c` |
| ov_SC07_010 | func_80180E68 | 164 | t5l | `.run/t5l/opus/func_80180E68.c` |
| ov_SC06_032 | func_801866B0 | 97 | t5o | `.run/t5o/opus/func_801866B0.c` |
| md_MAIN_044 | func_800CCDB0 | 46 | t5o | `.run/t5o/sonnet/func_800CCDB0.c` |
| ov_SC07_010 | func_80181304 | 36 | t5p | `.run/t5p/sonnet/func_80181304.c` |
| ov_SC04_010 | func_8017D6CC | 53 | t5q | `.run/t5q/sonnet/func_8017D6CC.c` |
| ov_MAIN_012 | func_80144B9C | 770 | t5r | `.run/t5r/opus/func_80144B9C.c` |
| ov_SC01_004 | func_8017EB30 | 279 | t5s | `.run/t5s/opus/func_8017EB30.c` |
| ov_SC06_008 | func_8017E37C | 80 | t5s | `.run/t5s/sonnet/func_8017E37C.c` |
| md_MAIN_031 | func_800CB1CC | 47 | t5u | `.run/t5u/sonnet/func_800CB1CC.c` |
| ov_SC03_111 | func_80180A10 | 92 | t5u | `.run/t5u/sonnet/func_80180A10.c` |
| ov_SC07_000 | func_8017F098 | 14 | t8b | `.run/t8b/sonnet/func_8017F098.c` |

**`ov_MAIN_012:func_80144B9C` is 770 instructions** — the single largest recoverable item in the queue.

## Lane B — NEAR-MISSES (33): drafted, never reached MATCH
Fresh-eyes redraft with the residual class NAMED in the card (the S65 pack builder now embeds
the measured residual automatically — `claude_wave_packs.py`), permuter for the REGALLOC-PERM/
DELAY-SLOT ones. Closest first; the top of this list is nearly free:

| closeness | binary | function | ins | wave |
|---|---|---|---|---|
| 1 | ov_SC03_112 | func_80181D08 | 96 | t5r |
| 2 | ov_SC02_027 | func_8017F498 | 99 | t5i |
| 2 | ov_SC06_032 | func_8017D4A0 | 81 | t5m |
| 2 | ov_SC06_032 | func_8017D4A0 | 81 | t5r |
| 2 | ov_SC03_012 | func_8017DCB4 | 89 | t5r |
| 2 | ov_SC04_005 | func_801809B8 | 109 | t5r |
| 3 | ov_SC03_013 | func_8017E6F4 | 182 | t6a |
| 4 | ov_SC05_018 | func_80181294 | 26 | t5m |
| 4 | ov_SC05_000 | func_8017DB10 | 99 | t5r |
| 5 | ov_SC06_032 | func_80185F4C | 60 | t5m |
| 5 | ov_SC06_032 | func_80185F4C | 60 | t5r |
| 6 | ov_SC06_018 | func_8017DB20 | 78 | t5r |
| 7 | ov_SC03_028 | func_80185344 | 101 | t5h |
| 7 | ov_SC03_099 | func_8017D2AC | 46 | t5x |
| 10 | ov_SC02_031 | func_801831B4 | 71 | t5t |
| 12 | ov_SC03_094 | func_8017E254 | 87 | t5x |
| 16 | ov_SC05_018 | func_80181294 | 26 | t5k |
| 16 | ov_SC06_024 | func_8018A3CC | 91 | t5r |
| 18 | ov_SC03_028 | func_80185344 | 101 | t5c |
| 19 | ov_SC04_002 | func_80183790 | 36 | t5r |
| 23 | ov_SC04_012 | func_8017D4CC | 115 | t5s |
| 24 | ov_SC05_008 | func_80182334 | 33 | t5s |
| 24 | ov_SC05_001 | func_8017FE0C | 123 | t6b |
| 26 | ov_SC03_124 | func_80180D48 | 62 | t5r |
| 32 | ov_SC06_029 | func_80185214 | 52 | t5m |
| 32 | ov_SC06_029 | func_80185214 | 52 | t5r |
| 37 | ov_SC01_080 | func_80180728 | 100 | t5b |
| 37 | ov_SC01_080 | func_80180728 | 100 | t5h |
| 37 | ov_SC05_008 | func_80182794 | 83 | t5r |
| 41 | ov_SC06_032 | func_801866B0 | 97 | t5m |
| 52 | ov_SC02_027 | func_8017F498 | 99 | t5h |
| 89 | ov_SC02_021 | func_8017DC10 | 512 | t5r |
| 190 | ov_SC06_025 | func_8017EF94 | 292 | t5b |

## Lane C — ERRORED / NO DRAFT (22): straight re-draft
Agents killed by rate limits etc. — no draft was ever written, so these are NOT failures.

| binary | function | ins | wave |
|---|---|---|---|
| ov_SC01_080 | func_80180728 | 100 | t5e |
| ov_SC03_028 | func_80185344 | 101 | t5e |
| ov_SC02_027 | func_8017F498 | 99 | t5f |
| ov_SC06_029 | func_80185214 | 52 | t5o |
| ov_SC06_032 | func_8017D4A0 | 81 | t5o |
| ov_SC06_032 | func_80185F4C | 60 | t5o |
| ov_SC03_012 | func_8017DCB4 | 89 | t5o |
| ov_SC03_124 | func_80180D48 | 62 | t5o |
| ov_SC04_005 | func_801809B8 | 109 | t5o |
| ov_SC05_008 | func_80182794 | 83 | t5o |
| ov_SC06_018 | func_8017DB20 | 78 | t5o |
| ov_SC06_024 | func_8018A3CC | 91 | t5o |
| ov_SC02_021 | func_8017DC10 | 512 | t5o |
| ov_SC04_002 | func_80183790 | 36 | t5p |
| ov_SC03_112 | func_80181D08 | 96 | t5p |
| ov_SC04_012 | func_8017D4CC | 115 | t5q |
| ov_SC05_000 | func_8017DB10 | 99 | t5q |
| ov_SC05_001 | func_801809B8 | 59 | t5q |
| ov_MAIN_012 | func_80144B9C | 770 | t5q |
| ov_SC01_004 | func_8017EB30 | 279 | t5q |
| ov_SC04_012 | func_8017D4CC | 115 | t5r |
| ov_SC01_004 | func_8017EB30 | 279 | t5r |

*(Live JSON while `.run` survives: `.run/recovery_classified.json`, `.run/recovery_set.json`.)*

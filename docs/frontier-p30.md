# The P30 frontier report (T0(f) — report point #1)

> **Generated 2026-07-30 at HEAD `commit:1218`**, after the T0 instrument repairs (a–e), from
> same-tree regenerations only: `progress.fleet.md` · `family-hseq.md` (+`.run/family_hseq.json`) ·
> `worklist.md` · `.run/fuel_manifest.json` · `.run/autopsy/residuals.jsonl` · `docs/autopsy.md`.
> Every number below is re-derivable from those artifacts at this HEAD (R33/R35). This file is a
> point-in-time report — it is NOT re-baselined; consume via a fresh regen.

## Standing

**87.5% instr** (11,493,049/13,141,652) · **78.0% distinct** (4,396,900/5,634,875) · **92.00%
fn-count** (325,417/353,720) · **140/140 byte-identical** (R22 re-proven this session after the
21-file include fix) · dedup 1886/0 · 0 NON_MATCHING.

**Open:** overlays 27,248 instances / 17,629 distinct / 1,587,311 ins · main 1,034 stubs (0.7%
game-code) · resident 14.

## The pinned populations (what T0 was for)

| population | pinned value | consequence |
|---|---|---|
| **Stranded byte-correct drafts** (T1 fuel) | **108 match_one-MATCH** + 1,178 near + 63 nobuild (autopsy, 1,349 rows, 0 classifier errors, second-oracle agree) | T1's recovery sweep has 3× the population the S16 sample suggested (36 → 108 fresh MATCHes) |
| **The `-O0` cluster** (T2) | **18 families / 2,192 open members** (2,131 on o0b-bearing overlays / 61 SC07); 15/18 exemplar-matched. **⚠ CORRECTED by the T2 ×1 probe (R14):** o0b-*bearing* ≠ o0b-*adjacent* — T85's `0x801457A4` banked by APPEND only because its address abuts the o0b object's END; the remaining families (`0x8013Bxxx–0x8013Cxxx`, below the whale) mis-place on append (probe: 1/1 gate-reject) and the alternative per-fn isolation IS the re-carve that trips Arm-A | **T2's real substance is the Arm-A `+0x20` defect itself** (first hypothesis: the re-carve lets splat re-GUESS a data-symbol boundary → pin the shifting symbol in the config and re-probe). The generalized driver (`rollout_o0.py`) stands as the sweep harness once placement works, and for any future adjacent case |
| **Zero-crack roster** (Lane A) | **114 families / 3,166 open members / ~204k weighted ins** (28 substantial). The head of the roster IS the `-O0` route set — T2 and Lane A open together | Propagation-only fuel behind already-matched exemplars; the non-o0 tail is ~100 small families for `family_sweep`/`dedup_extend` as classed |
| **Concentration** | **top-20 = 24.0% · top-100 = 44.8%** of open family weight (1,587,311 ins) | Lane B works the head down; flatter than SESSION-13's 53% (the campaign consumed the head — expected) |
| **Core queue** (fresh worklist) | **101 live stubs / 261,789 gain-ins**; GIANTs (`func_801412A8` close=110, `func_80178004` close=91) = 19.1% of it | The stale 160/583k rows are gone; queue is oracle-derived |
| **Instrument repairs shipped** | gate_stage **stage-0** + journal undo (§122) · rtu_match error surfacing · digests scope+HEAD-stamped · backlog scanner deleted (R33; 0 divergence vs corpus across 131 binaries) · 21-file include fix (R22 140/140) · autopsy refreshed | Every number above was produced AFTER the repairs (R35 sequencing) |

## The opening play this frontier implies

1. **T0.5 prefetch batch** (background): tail + main Ghidra-C — fuel for Lanes B/C and P31.
2. **T1 recovery sweep [Ultracode]** over the 108 stranded MATCHes (+ the 10 named S16 drafts) —
   cheapest distinct wins, now through the stage-0-safe ladder.
3. **T2 the generalized o0b driver [Max]**: ~9 non-jr route-ready `-O0` families first (~950
   members), then the jr+o0 composites (probe ×1 before ×136), then the 3 exemplar cracks; the 61
   SC07 members and any re-carve-needed residue go to the wall ledger with evidence.
4. **T3 lanes** as planned — Lane A's non-o0 tail, Lane B down the concentration head, Lane C on
   prefetched seeds, Lane D (PINS 19 / W4 / permuter backlog).

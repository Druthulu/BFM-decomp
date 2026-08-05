# Fable 5 — frontier attack analysis (P30 SESSION-38, 2026-08-04)

> **Provenance:** produced by a read-only Fable-5 agent commissioned during S38 with the explicit
> brief *"this project has repeatedly declared 'no more families' and been wrong — treat my
> conclusion as a hypothesis to attack."* The agent's harness blocked it from writing to disk, so
> this file is its **verbatim returned report**, transcribed by the orchestrator so it survives the
> session. Its computed scratch data — the h_exact / h_norm pools — **is** on disk at
> `.run/fable_frontier/pool_ovres.json` (136 KB) and is the reusable artifact.
>
> **Status of its claims:** the two headline refutations were independently re-verified against the
> repo before this was acted on (23,211 `.run/hseq_failed.*.classified.txt` files exist; the
> `0x801833f0` family went 0/6 → 6/6 after the type lift, R22 140/140). The pool numbers in §"Top 3
> findings" item 3 are the agent's own computation and are **not** independently re-verified —
> verify before scaling a wave onto them (R14).

---

## Top 3 findings

**1. Both session-38 zeros were PLUMBING, and their diagnoses were already on disk, written by the sweep itself at probe time — unread.**
- `0x801833f0` (0/6) → `.run/hseq_failed.ov_SC03_097.0.classified.txt`: `func_801813B4 PLUMBING: src/ov_SC03_097/ov_SC03_097_jr_8017D898.c:4162: parse error before 'vtx'`. All 11 instances of this family (5 matched + 6 open) have **identical h_norm** — the code is byte-proven identical modulo relocation; 0/6 was a compile-error certainty. Cause: the staged draft (`.run/sweep/ov_SC03_097/func_801813B4.c`) references the exemplar's TU-local types `Ft4_801833F0`/`Drm_801833F0`/`PTag_801833F0` whose **typedefs were never gathered** into the member TU (gcc-2.7.2 parses the unknown-type declarator as an expression → decl-after-statement error at `vtx`). `gather_externs` copies extern lines, not local typedef/macro definitions.
- `0x80128c98` (0/138) → `.run/hseq_failed.ov_SC03_097.52.classified.txt`: `PLUMBING: conflicting types for 'cdFileLocTable'` — the §103/§20 extern-conflict class. Neither probe ever reached codegen. The S38 claim "family_sweep reports banked/failed without the per-member build error" is itself false — the `.classified.txt` payloads exist per member, per run.

**2. "The ×138 era is over / 4 families collide by chance" is another false wall — the map's own classifier refutes it.** `classify_member` (family_remap.py:213) is a per-word diff with reloc tracking; PURE means every differing word sits at a reloc position — the opposite of chance collision. All four "chance" families classify PURE or IMM ×138 (`0x80128c98` PURE×138, `0x80146ab4` PURE×138, `0x80161418` PURE×138 with **552 already-matched siblings** — this family has swept successfully before — `0x80146c3c` IMM×138). The two "ledgered not-templatable" families are also contradicted: `0x80175820` is IMM×137 (the T2a immediate engine's exact domain, 7,535 ins), `0x80132018` is PURE×132 (6,072 ins). Zero STRUCT members in any of them. Only the 2 GIANT walls survive scrutiny — and those are *exemplar* walls (close=91/110 regalloc) whose 138 members each classify PURE: 50,094 ins ride on 2 cracks. Historical blocker mix across ALL sweep runs' classified files: **~24k PLUMBING vs 4,917 DIFF (5:1)** — sweep failure has always been mostly plumbing.

**3. Half the open overlay code sits in h_norm-identical structure nobody is targeting.** Computed fresh from sig+corpus (overlays+resident, 12,094 open fns / 702,647 ins):
- **h_exact pool**: 250 open fns / 12,981 ins are byte-identical (including reloc payloads) to an already-matched function — including **the whale `0x80144b9c` (770 ins), matched in 134/138 overlays, open only in SC07_006/007/010/011** — 3,080 ins of literally identical bytes blocked solely by the SC07 carve defect.
- **h_norm pool**: 860 fns / 35,438 ins normalization-identical to matched code (859 of them inside the 148 matched-exemplar families — half the "free sweep lane" is h_norm-proven, not h_seq-inferred).
- **Open-only h_norm clusters** (≥2, no matched sibling): **1,689 clusters / 5,956 fns / 326,261 ins = 46% of all open overlay instructions**. Exemplar ins 88,649, propagated ins 237,612 — a free 2.7× multiplier on every crack aimed here. Includes an unflagged alive ×138 h_norm-identical cluster (`0x80162ccc`, 3,174 ins) and 947-ins functions with identical siblings (`0x8017c6f4` ×3, `0x8017d538` ×2).
- **Main is structurally barren** (zero h_exact overlap with anything, 5k ins of internal h_seq dups in 49,673 open ins) — genuine agent tail, different compiler era; its Ghidra sig is 7 weeks stale and missing 757 of 2,002 stubs. **Resident**: 2 of its 14 stubs (`func_800CFE60`, `func_800D0214`) already have match_one-MATCH drafts recorded in backlog.jsonl as "gate rejected (declaration/TU plumbing)" — same defect class.

## Ranked attack plan (tokens/instruction; baseline wave = 490)

| # | Strategy | Reachable ins | tok/ins | Pre-work | Validate/kill experiment |
|---|---|---|---|---|---|
| S1 | **Fix 2 plumbing classes (typedef/macro gather + extern-conflict reconcile), re-sweep the 148 matched-exemplar families** (1,585 members / 75,383 ins gross, 71,178 PURE+IMM) | 35–60k | **~10–25** (tool work ~0.5–1M, ~0 agent) | edit family_remap gather + wire reconcile into --hseq | `family_sweep.py --hseq --only 0x801833f0` after the typedef fix — 6 h_norm-identical members; less than ~6/6 means the fix is wrong, not the family. Then `--only 0x80128c98` after the extern fix |
| S2 | jr matched-exemplar fams via `jtbl_family_bank` (§53's own lesson): 11 fams / 52 members | 10–18k | ~0 | none | ×1 member of the largest jr family |
| S3 | SC07 carve/pin fix (T2 Arm-A +0x20): whale ×4 (3,080 h_exact-identical ins) + 61 SC07 o0 members | 5–15k | ~0 | already scoped in CURRENT_PHASE T2 | ov_SC07_007 symbol-inventory diff → pin → re-extract |
| S4 | Draft-recovery on 39 draft-exemplar fams (382 members / 77,380 ins incl. walls) + the 2 resident TU-plumbing MATCHes | 10–25k | ~10–50 | T1a driver exists | `w6_diag.py`-shape run on one stored draft per family, read the error |
| S5 | **Re-aim waves at open-only h_norm cluster exemplars, sweep after every bank**: 1,689 clusters / 326k ins | up to 326k | **~130–150 blended** (2.7× multiplier) | S1 must land first or propagation never realizes; regen map per crack | one 8-target wave from the ×16/×7/×6 clusters; measure realized propagation |
| S6 | The two GIANT exemplar walls (50,094 ins / 2 cracks) | 50k | ~50–200, high variance | §17 pins, §52; prior close=91/110 | time-boxed siege, hard budget stop |
| S7 | Singleton tail (232k) + main (~50k; regenerate sig + DefineFunctions first, then a 5-fn PsyQ-4.0 calibration probe to price it) | remainder | ~490+ | main sig regen | 5-fn main probe wave |

S1–S4 ≈ **80–115k instructions moved from the 490-t/ins column to ~0** (11–15% of everything left), and S1 restores the propagation multiplier that makes every later wave ~3× cheaper.

## Verification of the S38 numbers
Distribution survives (I measure 5,793 fams / 709,920 ins at HEAD vs claimed 5,792/701,508 — snapshot drift; the 100+ band is 74,741 ins exactly). The 147-family pool is real (148 / 1,585 / 75,383 at HEAD). Fleet 96.29/94.2/88.9 confirmed. What does NOT survive: "chance collision" (all four refuted), "ledgered not-templatable" (both contradicted), "free-sweep 0/0 undiagnosed" (both diagnosed, on disk, PLUMBING), and "the ×138 era is over."

## False-wall watch list
1. CURRENT_PHASE.md:228's ×138-era paragraph (S38) — rests entirely on the two undiagnosed zeros; should be rewritten against the classified files. *(DONE — struck in commit `commit:1413`.)*
2. The `0x80175820`/`0x80132018` "not-templatable" ledger entries — provenance predates or ignores the current classifier.
3. Any post-S1 sweep still returning 0% on an h_norm-identical family is a NEW undiagnosed zero — the one-line h_norm check against the sig files should become a standard pre-probe step (it would have predicted both of today's zeros as compile-error certainties before spending the probe).

Key files: `.run/hseq_failed.ov_SC03_097.0.classified.txt` and `.52.classified.txt` (the smoking guns), `.run/sweep/ov_SC03_097/func_801813B4.c` (the typedef-less draft), `tools/family_remap.py:213` (classify_member), `tools/sig_image.py:134` (norm_stream's conservative-miss guarantee), `.run/fable_frontier/pool_ovres.json` (computed h_exact/h_norm pools).

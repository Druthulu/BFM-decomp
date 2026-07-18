# Phase-29 Task-3 preserved drafts — 12 giants/cores, each with its exact bank blocker

**Provenance:** two ultracode `worker_wave` runs (2026-07-16/17), ~2.6M agent tokens total. Every draft here
is either a **match_one MATCH** (relocation-masked byte-correct, standalone) or a characterized near-miss.
The 5 that banked cleanly are already in `src/` (commits `commit:0668`, `commit:0669`) and are NOT duplicated here.

**Why preserved (R20):** reproducing these costs ~2.6M tokens. Each is blocked on *integration plumbing*,
not codegen — a fresh session can bank several cheaply with the named fix.

**The universal caveat (§55b, learned the hard way this task):** `match_one` MATCH ≠ bank. It compiles the
draft STANDALONE, so it is blind to the member TU's conflicting decls. The whole-binary byte-gate
(`harvest_verify`) is the sole arbiter (G3/P9). Trust the SOURCE (`grep INCLUDE_ASM`), never a gate report
(`gate_stage`'s default `.run/harvest_verified.txt` accumulates → phantom banks).

---

## A. The 4 jr cores — ALL match_one MATCH, ALL gate-rejected on integration (Task-3 target list)

| draft | nins | src home | status | BLOCKER → the fix to try |
|---|---|---|---|---|
| `p29t3_func_8013F350.c` | **490** | `ov_SC01_077.c` | MATCH 490/490 | **def-side sig**: draft is `s32 func_8013F350(void)`, `engine_core.h` canon is `void(void)`. The fn really returns `$v0` and callers already cast ⇒ the CANON is wrong, not the draft. Fix = **§30#2 def-side return-type macro-widen** (widen the caller macro's extern `void`→`s32`; byte-neutral iff callers discard the return). NOT `--fix-def-sig` (that rewrites the DRAFT to the canon — wrong direction here; a `void` return would DCE the live `$v0` set). |
| `p29t3_func_80131340.c` | **424** | `_jr_8012ACE0.c` | MATCH 424/424, verified **twice** (standalone + in-TU, cc1 rc=0, zero conflicting types) | Agent already moved the file-scope `extern int func_80131CF4(int,int)` to **block scope** (it hard-conflicts with the stale 1-arg canonical in `DEFINE_func_80131AC8()` @TU L1964, cc1 rc=33), mirroring matched `func_801312D0` @L1619. It still gate-rejected ⇒ **re-diagnose against the real gate**; the in-TU proof says the body is right. Closest to banking. |
| `p29t3_func_80159C84.c` | **337** | `_jr_8015444C.c` | MATCH 337/337 | Not yet characterized — gate-rejected. Re-run the gate and read the cc1 error (do NOT infer from match_one). |
| `p29t3_func_8013C414.c` | **329** | **`_o0.c` (-O0!)** | MATCH 329/329 **at -O0** | **§8a rodata island**: needs `jtbl_801D836C` (27 entries @ `0x801D836C`, still nonmatching in `asm/ov_SC01_077/data/tail3.data.s`) carved into a `.rodata` subseg co-located with its code object + `ld_interleave --section`. A matched jr-fn's C emits its jtbl into `.rodata` (section_order floats it FRONT) while the raw copy stays in the data tail ⇒ duplicate + wrong address. See `config/splat.ov_SC01_077.yaml` lines 78-86 (the `func_8012ACE0` / `jtbl_801D8078` PoC). |

**-O0 note:** `func_8013C414` only matched because `worker_wave` now passes `--o0` to `match_one` (committed
`commit:0670`). Against an `-O2` self-check it can never match — the wrong-build-step trap (§53/§54, Task-1).

## B. Wave-1 leftovers — byte-correct or near, not banked

| draft | nins | status | BLOCKER / residual |
|---|---|---|---|
| `p29t3_func_8013FAF8.c` | **312** | **MATCH 312/312** | **plumbing only**: def-sig `s16/s16` vs fleet-canonical `s32/s32` externs (callers already pass `(s16)`-cast args) + `D_80187AC0` declared `s32[]` vs canonical `u8`. Prime `--fix-def-sig` / macro-widen candidate. |
| `p29t3_func_8014F4C0.c` | 141 | **MATCH**, byte-verified **in-TU** (full cpp+cc1+maspsx+as, 0 mismatched) | one byte-neutral decl: `ov_SC01_077_after.c:1898 extern s32 func_8014F4C0(void);` (exists only for the inline-asm caller `func_8014F468`, whose `jal` is inside `__asm__`) conflicts with the def's `s32` param. `fix_arity_callers --apply --funcs func_8014F4C0 --binary ov_SC01_077` did NOT clear it — needs a hand look. |
| `p29t3_func_80177940.c` | 101 | near, **close=5** | sched1 swaps the `$s1(c)`/`$s2(a)` param copies (equal-priority birthing insns tie-broken by INSN_LUID — swept all 6 assign orders/pin combos) + idx 51 `andi $a2,$v0,0xf` vs target `addu`. **Permuter fuel.** Carries NEW byte-proven levers → distilled to §55a. |
| `p29t3_func_801670E4.c` | 279 | near, **close=16** | 3 runs, ONE class: post-reload list scheduler emits `la $s2`/`addu $s4,$zero,$zero` BEFORE the callee-arg setup; target emits AFTER. Inert to ~40 stmt-order permutations + all pin/barrier combos (`rank_for_schedule` ranks priority first, never reaches the LUID tie-break). ⚠️ **Draft carries `register __asm__("$2")` pins + an `asm volatile("")` fence ⇒ pycparser/permuter CANNOT ingest it as-is**; stripping them re-enters the grinder at ~57, not 16. Needs a human call. |
| `p29t3_func_8014D820.c` | 304 | near, **close=33** | entry-block regalloc: target keeps `$a0` live so `addu $s4,$a0,$zero` fills the load-delay slot; my `$a3` pin gets copy-propagated so the pin move sinks into that slot → prologue save-order cascade. Body/frame/calls/consts/tail all byte-correct. |
| `p29t3_func_80140958.c` | 260 | near, close=116 | LICM hoists inner-loop consts `8`/`0xFFFFFF` to the OUTER preheader (`combine_movables` merges the 8 with the outer `func_80140D68` arg), stealing the two callee regs the target gives const-3 (`$fp`) and `&D_801879BE` (`$s6`). Ins count 260/260, frame 0x50 + all prologue offsets EXACT. Pin/mask/index/store-order variants all worse (118-228) → **permuter**. |
| `p29t3_func_80176734.c` | **371** | near, close=76 | ins 0..263 byte-exact; `D_80126CE0` needs BOTH `lh` (test) + `lhu` (value), but every C form forcing the 2nd load relieves pressure → frame 0x40→0x38 → save-offset cascade (76→84..95). §27 frame-pressure lock → **permuter-only**. |
| `p29t3_func_80176218.c` | **327** | near, close=271 | 281/327 aligned-equal (325 vs 327 ins); frame 0x58 + `$s0-$s5` EXACT; residual = ne-boolean coalescing copy + blk-1 delay-slot steal + blk-2 cross-jumped into the adjust tail. Hardest of the set. |

---

## STATUS after Phase-29 T4 session (2026-07-17) — the giants split into TWO classes

**✅ DONE (both NON-jtbl giants, fully banked + propagated fleet-wide):**
- **`func_8013FAF8` (312)** — banked x1 (cookbook §56 multi-symbol reconciliation) + **propagated x137**
  via `family_sweep --hseq` (h_seq family; §56b — align the exemplar's callee externs to fleet-canonical
  first or it banks 0/137). Commits `commit:0673`, `commit:0675`. ~+42.7k ins.
- **`func_8014F4C0` (141)** — banked x1 (clean; earlier reject was §55b propagate-damage) + **propagated
  x134** via `dedup_propagate --recover` (h_exact). Commit `commit:0674`. ~+19k ins.

**⏸ DEFERRED — the 4 jtbl giants are BLOCKED on ONE tooling gap (the teed-up next-session task):**
`func_80131340` (424), `func_80159C84` (337, +a trivial D_801891B8 (u8*/void*) plumbing fix),
`func_8013C414` (329, -O0), `func_8013F350` (490, +§30#2 macro-widen void→s32).
Each needs a per-overlay jtbl carve (`jtbl_carve` / `jtbl_family_bank`) x~137, and the carve currently
OVERSHOOTS: **byte-proven on func_80131340 —** its `jtbl_801D8144` is a non-first, 4-aligned jtbl in a
shared code object; the carved `.rodata` run comes out **+4 bytes** (an 8-align pad at rodata offset 0xCC
after the 51-entry jtbl_801D8078), shifting the whole data island → all downstream `%lo` relocs break
image-wide (+5B, 3077 diffs from a CLEAN build).
**ROOT CAUSE HALF-PINNED (do NOT re-derive):** it is NOT gcc — **cc1 AND maspsx both emit the jtbl
`.align 2` (4-byte, correct)** (probe: `.run/probe_jtbl_cc1.s` / `probe_jtbl_maspsx.s`). The 8-byte pad
is a downstream build-infra artifact (GNU `as` `.rodata` section-align defaulting to `2**3`, or the
`ld_interleave` placement). **NEXT-SESSION TASK:** pin whether it's `as` section-align vs interleave →
fix `jtbl_carve`/`ld_interleave` to pack the non-first jtbl 4-aligned (or isolate) → prove x137 propagation
on func_80131340 end-to-end BEFORE scaling to all 4. Ceiling ≈ +1 to +1.5pp instr (the biggest lever left).

**Permuter fuel (separate track):** `func_80177940` (5), `func_801670E4` (16 — strip pins first),
`func_8014D820` (33), `func_80140958` (116).

**Gate law (§55b):** `--no-propagate` per group → **commit the banks** → THEN one targeted
`dedup_propagate --addr <banked>` (~233s/core on a healthy tree; only `--auto-from` is fleet-slow).
**h_seq giants use `family_sweep --hseq` (per-overlay symbol remap), NOT dedup_propagate (reach<2);
pre-align the exemplar's callee externs to the fleet-canonical (§56b).**

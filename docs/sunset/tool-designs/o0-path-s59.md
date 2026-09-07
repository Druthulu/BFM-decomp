# The -O0 path — per-population bankability, the byte-proven crack, and the ranked plan (P31 S59, 2026-08-24)

**Provenance:** S59 subagent task over the S59 census (167 prologue-carrying functions; 51 covered /
116 stranded / 14,148 stranded ins). Everything below is anchored to a file read or a command run
this session; the one build allowance was spent on the gate that BANKED `func_80184058` (§3).

**Headline results:**
1. `func_80184058` (131 ins, `ov_SC03_014_o0c`) went **first-compile MATCH → whole-binary
   BYTE-IDENTICAL → committed** (`a1e8b9a5f`). The -O0 idiom set exists, transfers from banked
   siblings, and one-shots without iteration. Q3 is answered YES with bytes.
2. **md_MAIN_011 needs NO carve at all.** Its entire code subseg (0x7C..0x4400 = 17,284 B =
   4,321 ins) is exactly the 21 stranded -O0 functions, and `src/md_MAIN_011/md_MAIN_011.c` is
   INCLUDE_ASM-only. One boot-style Makefile line unlocks 31% of the stranded mass. The ox study's
   "requires a ≥3-object re-carve" claim is wrong for this module.
3. **47.6% of the stranded mass (6,730 ins / 58 fns) needs zero drafting** — the bodies already
   exist (ov_SC01_077 cluster exemplars 16/16 matched; the whale shared header; the T85
   `func_801457A4` exemplar). Those need only carve+remap mechanics.
4. The §18-P29 wall is **sequencing-avoidable**: `match_one` iterates stranded functions against
   their existing `.s` TODAY (proven in §3 — no carve needed to reach MATCH), so every carve can
   land **populated** (no INCLUDE_ASM in the new -O0 object) — the exact shape the P30 ×137 `_o0c`
   rollout used to beat the wall, vs the 1/4 record of the stub-carrying P29 carve.

---

## 1. The census, function-level (verify: `.run/s59_o0/census.py`)

Denominators: 14,400 `.s` under `asm/`; 166 carry the -O0 prologue at `glabel`+8, +1 (`boot/start.s`,
-O0 by subseg, no ordinary prologue) = 167. Covered = subseg is an -O0 object (`boot`, `*_o0*`):
50 fns / 2,299 ins (+start). Stranded = 116 fns (my ins counter says 14,130 vs the census's 14,148 —
a <0.2% counting-convention delta on the same file set; immaterial).

Both md runs close arithmetically gap-free (every function's end == the next's start), so **neither
contains a matched -O2 island**:

* md_MAIN_011: one contiguous run 0x800CEE74..0x800D31F8 — and it is the WHOLE code subseg.
* md_MAIN_003: one contiguous run 0x800D0100..0x800D1E18 (0x1308..0x3020 in-file), with genuine
  -O2 stubs before (0xD8..0x1308, incl. the matched `func_800CEED0` dispatch) and after
  (0x3020..0x477C). 29 stubs total in the TU, 16 of them -O0.
* SC03_118/119's run 0x80183178..0x801838A4 is 10 contiguous fns inside `_jr_8017FB84`
  (0x57A2C..0x5E274). **All 58 open stubs of that subseg are raw-word IDENTICAL between 118 and
  119** (relocation immediates included) — a byte-twin pair: draft once, bank twice, same symbols.

## 2. Per-sub-population: why unbankable, and the minimum unlock (Q1)

| population | fns / ins | why it cannot bank | minimum unlock | wall exposure |
|---|---|---|---|---|
| **md_MAIN_011** | 21 / 4,321 | object compiled -O2; no Makefile glob matches `src/md_*/` | **one Makefile line** (boot-style whole-object override — §6 shape, no splat change, no carve; byte-neutral on a stub-only object, gate it anyway) + the oracle-coupling fixes in §7.3 | **NONE** — nothing is re-disassembled |
| **md_MAIN_003** | 16 / 1,862 | same, but the module mixes -O2 stubs + 1 matched fn around the run | `o0_subsplit md_MAIN_003 --lo 0x800D0100 --hi 0x800D1E18` (pre/-O0/post; K=0 islands inside) + an md Makefile glob + byte-neutral gate. **Sequence: draft all 16 to MATCH first** (works today), then carve POPULATED | dice-roll if carved with stubs (precedents §8); ~zero if populated |
| **`*_jr_801380E0` ×3** (SC02_037, MAIN_012, SC03_107) | 48 / 3,867 | the 16-fn cluster (0x8013B568..0x8013C98C) never got the P30 `_o0c` carve in these 3 — it sits whole inside their `jr_801380E0` subseg (0xFF88..0x171F8) | o0_subsplit at [0x13410,0x14834) per overlay + **populate all 16 from the ov077 exemplars in the same commit** (`ov_SC01_077_o0.c` has 16/16 matched; per-overlay data addrs via the existing remap machinery; C0F8/C414 need the §132 `tables=+0x0,+0x70` spec like the 137) | avoided by populate-at-carve (the ×137 precedent) |
| **`*_jr_8013F350` ×3** (same three) | 6 / 2,547 | the whale (770) + `func_801457A4` (79) sit inside `jr_8013F350`; these 3 never got `_o0b` | carve [0x1CA44,0x1D64C) as a **whale-shape** file (`#include "../shared/func_80144B9C.h"`, zero stubs) + append the T85 `func_801457A4` remap + stub-drop | **NONE** — the whale shape never hits it (§18-P29's own finding) |
| **`*_jr_8017FB84` ×2** (SC03_118/119) | 20 / 918 | fresh -O0 region, no carve, no exemplars | draft the 10 distinct fns to MATCH (today, vs the stranded `.s`), then carve [0x5B020,0x5B74C) populated, both twins | ~zero once populated; twins share bytes so one carve spec serves both |
| **`*_jr_801457A4` ×4** (SC07_006/007/010/011) | 4 / 316 | NOT a carve problem: each already has a whale-ending -O0 object at 0x1D64C (`_o0d` in 006/007/011, `_o0c` in 010) — `rollout_o0.py` just hardcodes the `_o0b` NAME and lists SC07 out-of-scope | **~15-line rollout_o0.py fix**: resolve the whale file by content (the shared-header include), drop `SC07_NO_O0B`; then the proven append+stub-drop (no splat change at all) | **NONE** |
| **`main`/`800`** | 1 / 299 | `func_8002C410` is a lone -O0 island inside the EXE's `800` object (0x800123F0..0x8003A444) | draft to MATCH now (oracle works); banking needs a 3-way 800 carve (§18 mid-blob law; the EXE already tolerates subseg splits — `800b`..`800b_6` are precedent) + a rule for the new object | carve-with-0-stubs-in-the-o0-object if drafted first; still the crown-jewel binary — do it LAST, manually |

Key asymmetry the table encodes: **the `md_*` rows are Makefile/carve problems; the `ov_*` rows are
almost entirely REMAP problems** (bodies exist), except 118/119 which is a small drafting problem.

## 3. Can we write -O0-matching C? YES — byte-proven this session (Q3)

Target: `func_80184058` (131 ins, open in both `ov_SC03_014_o0c` and `ov_SC03_015_o0c`). Method:
read the banked siblings in the same TU first (§127a), lift their proven spellings, draft, iterate
with the fixed oracle. Result — **zero iterations needed**:

```
$ .venv/bin/python tools/match_one.py func_80184058 --c .run/s59_o0/func_80184058.c \
      --asm-subdir asm/ov_SC03_014/nonmatchings/ov_SC03_014_o0c
match_one: compiling at -O0 (frame-pointer prologue in the target; pass --no-auto-o0 to override)
MATCH (131 ins)  func_80184058
```

then spliced into the TU and gated under the binary's lock:

```
[ OK ] build/ov_SC03_014/ov_SC03_014
       sha1 d84b01a2bd4c712e1127707f5cd2007d79f4afb0 == config/check.ov_SC03_014.sha  (BYTE-IDENTICAL)
```

Committed as `a1e8b9a5f` (R42). The identical stub remains in `ov_SC03_015_o0c.c` — the same body
banks it (byte-twin), one gate away; left for the campaign since the task's one-build allowance was
spent.

The C that matched (also at `.run/s59_o0/func_80184058.c`):

```c
typedef struct {            /* 32-bit view: unkE0 is a 16.16 accumulator whose HIGH half */
    s16 unk00, unk02;       /* is the s16 unkE2 the rest of the function reads */
    u8  pad04[0xD8];
    s16 unkDC, unkDE;
    s32 unkE0;
} Ent58_fx;
typedef struct {
    s16 unk00, unk02;
    u8  pad04[0xD8];
    s16 unkDC, unkDE, unkE0, unkE2, unkE4, unkE6, unkE8, unkEA;
} Ent_80184058;

void func_80184058(Ent_80184058 *p) {
    func_8017DF84(&D_801EAFD0, D_8018F858[p->unkE4], p->unkDC, p->unkE2);
    func_80184354();
    if (p->unkEA == 0) {
        ((Ent58_fx *)p)->unkE0 += 0x5CCCC;
    } else {
        if (--p->unkEA == 0) func_8002D4C8(0x81E, 0);
    }
    if (--p->unkE8 == 0) {
        func_8013C9C4(&D_8018BCC8);
        p->unkE8 = (D_800B99DC & 7) + 3;
    }
    if (p->unkE2 >= 0x259) {
        p->unkE2 = 0;
        D_801270C8 = 2;
        p->unkE4 = 0;
        func_8013373C(1);
        func_8002D4C8(4, 0x81E);
        ++p->unk02;
    }
    p->unkDC += 8;
}
```

**What made it one-shot — the -O0 frame-reload grammar** (read straight off the target and confirmed
by the sibling's banked bytes; promoted to cookbook §261a):

* `p->f += k` (value unused) → **2** frame reloads of `p` (store-base first, read-base second), no
  register copy.
* `--p->f` / `++p->f` → **3** reloads (the first one DEAD), an `addu rd,rs,$zero` copy after the
  add, and — only if the value is used — `sll 16; sra 16` sign-extension of the STORED register (no
  re-load). So `if (--p->f == 0)` is distinguishable from `p->f -= 1; if (p->f == 0)` (the latter
  re-loads) and from `p->f -= 1;` (2 reloads, no copy) **by reload count alone**.
* s16 fields load `lh` at plain reads but `lhu` inside read-modify-write.
* An overlapping s32/s16 view (16.16 fixed point) is spelled with a second struct view and a free
  pointer cast — no union needed, no extra code at -O0.
* The verdict §127 predicted holds: plain C maps 1:1; no pins, no scheduling barriers, no permuter.
  **-O0 is strictly easier than -O2 per instruction** — the entire difficulty is (a) knowing the
  reload grammar and (b) being compiled at the right level, which is what the S59 oracle fix bought.

Caveat quoted with its denominator: this is **n=1** at 131 ins with a same-TU sibling to crib from.
The §127 P30 wave (15 targets, n=15) found agents independently re-deriving the idioms and still
converging. The population's big tail (7 fns ≥ ~400 -O0-ins in md_MAIN_011/003) is untested — but
-O0 ins are ~2× inflated, so 575 -O0-ins ≈ a ~280-ins -O2 function without the regalloc/schedule
search space that makes 200+ collapse in §262's table.

## 4. Are the 51 covered functions reachable? (Q2)

The 51 = 48 boot fns (2,037 ins, incl. `main` at 509) + `func_80184058` ×2 (now ×1 — 014 banked
today) + `start` (crt0, hand-asm, realistically permanent INCLUDE_ASM — honest denominator is **50
draftable**).

* **`rollout_o0.py` is NOT the vehicle** for these — it is a remap tool. Its full `--all-o0` dry run
  today: **46 attempts, 0 reachable** — `{'no-o0b': 42}` (the ×3 group: no -O0 object exists yet =
  needs the U3 carve) + `{'out-of-scope-sc07': 4}` (the U2 name-resolution fix). Both blockers are
  exactly two items of the plan below; after U2+U3 it banks 46 members mechanically.
* **The vehicle for the 50 is ordinary drafting with the fixed oracle.** Nothing draws them today
  because the atlas excludes the `o0` LEVER from drafting lanes (`build_wave_atlas.py:38`) — a rule
  from the era when the oracle compiled everything -O2. The new `_o0_unbankable` filter already
  separates stranded from covered, so re-admitting the lever exposes only bankable targets.
* **Boot's 48 are main-binary work**: draw with `--only-bins main` (a supported flow per the atlas's
  own help text) and gate through `gate_main.py`. This week: one mini-wave (48 drafts vs the boot
  stubs, sizes 8..509) + gate_main per bank; plus the one-gate 015 twin bank.

## 5. Serial vs wave (Q4)

**Recommendation: a 3-5 function serial warm-up, then wave the rest — but the real answer is that
most of the mass should never see a drafting agent at all.**

* 58 fns / 6,730 ins (47.6% of stranded) are remap-only → **tooling lane, zero drafts** (U2+U3).
* 48 distinct fns / 6,941 distinct ins need drafts (md_011 21, md_003 16, 118-twins 10, main 1;
  banked value 7,418 ins with the 119 twin).
* Evidence for wave-readiness: my n=1 first-compile at 131 ins; §127a's sibling-transfer;
  the grammar now being IN the cookbook (§261a) rather than re-derived per agent (§127's measured
  failure mode: 12 of 15 agents paid to rediscover a source-comment lever).
* Evidence for serial-first: the §127 wave predates §261a and the oracle fix, so no honest wave
  yield number exists for the current toolchain; and md_MAIN_011's 7 fat functions (397-575
  -O0-ins) are exactly the band where a wrong idiom costs the most iterations.
* Cost shape (units are drafts and gates, not dollars — no calibrated $/draft for -O0 exists yet):
  serial warm-up = 3-5 drafts (pick md_MAIN_011's 8-35-ins tail: `func_800D0430` 8,
  `func_800D04C4` 12, `func_800D0828` 12, `func_800D03F8` 14, `func_800CEE74` 35) against
  `match_one` only — **no build, no gate, no carve needed to learn the answer**. If ≥4/5 MATCH
  within a few iterations each (my prior after today: likely), wave the remaining ~43 with the
  subagent ladder on EFFECTIVE size (-O0 ins ÷ 2): Haiku ≲100 -O0-ins, Sonnet 100-240, Opus above.
  If the warm-up stalls instead, the grammar has a hole — feed it to §261a and re-probe before
  waving (the flywheel, not a bigger wave).

## 6. Is it worth it at all? (Q5)

**Yes — with U1-U3 unconditionally; U4-U5 as ordinary drafting work; U7 optional.** The numbers:

* Total addressable: 14,148 stranded + 2,339 covered = **16,487 ins ≈ 3.3% of the ~499k-ins
  frontier** — 2.5× the ox study's estimate (its census undercounted, 6,564).
* Of that, **11,051 ins (67%) require zero or one-line infrastructure and zero drafting**
  (md_MAIN_011's 4,321 behind one Makefile line + 6,730 remap-only) — the cheapest
  instruction-per-effort mass currently identified anywhere on the frontier.
* The wall's actual record, quoted with denominators: carve-with-stubs = 1/4 clean (P29
  `rollout_o0_cluster`, SC07) but 2/2 clean (P30 `o0_subsplit`, SC03_014/015); carve-populated =
  **137/137 clean** (the P30 fleet `_o0c` rollout — 136/137 twice only for the §132a jtbl
  role-name bug, since fixed). Draft-first sequencing converts every remaining carve into the
  137/137 shape. The "documented image-corruption wall" is real but it is a *shape* to avoid, not
  a barrier — and the failure mode is a refused gate + a yaml revert, never a corrupted commit.
* Opportunity cost: the campaign's default lane banks ~44.6% of drafts at full band (§262). The -O0
  drafting pool at 48 distinct fns is one wave's worth of cards; the remap pool competes with
  nothing (different lane). This does not displace jtbl-lane-scale work; it retires a whole CLASS
  (every future -O0 mis-draw, every "o0-in-an-O2-object" skip) plus two of the fleet's last
  never-touched binaries.

**Not worth doing:** re-opening the deferred ~1,233-member legacy harvest framing (it conflated this
population with per-overlay re-derivation the remap machinery now does), and any md-module carve
BEFORE its bodies are matched.

## 7. The ranked plan, with wall risks named

Order is by instructions-per-unit-risk; each step is independently gate-protected and revertible.

1. **U1 — md_MAIN_011 Makefile rule** (unlocks 21 fns / 4,321 ins for drafting; zero risk).
   Proposed diff (after the `O0_CLUSTER_OBJS` block, Makefile ~:726):
   ```make
   # S59: md_MAIN_011's entire code subseg is the 21-fn -O0 run 0x800CEE74..0x800D31F8 (census
   # .run/s59_o0/): whole-object override, the boot precedent. Byte-neutral while stub-only (§6).
   build/src/md_MAIN_011/md_MAIN_011.o: CC1FLAGS := -quiet -O0 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker
   ```
   Gate `md_MAIN_011` once to prove byte-neutrality (§6's verified precedent, but prove it).
   `corpus.o0_sources()` parses explicit rules and picks this up automatically.
2. **U2 — rollout_o0.py SC07 fix** (4 fns / 316 ins, zero drafting, zero splat change). Replace the
   `o0b = .../<ov>_o0b.c` path + `SC07_NO_O0B` skip with content resolution:
   ```python
   def whale_file_of(ov):
       """The overlay's -O0 object ending at 0x801457A4 = the file whose tail includes the
       whale's shared header (letter drifts: _o0b fleet, _o0c SC07_010, _o0d SC07_006/007/011)."""
       for p in sorted(glob.glob(os.path.join(REPO, f"src/{ov}/{ov}_o0*.c"))):
           if 'shared/func_80144B9C.h' in open(p).read():
               return p
       return None
   ```
   and in `attempt()`: `o0b = whale_file_of(ov)` (delete the SC07 branch). The append+stub-drop
   mechanics are unchanged (T85, 130/130).
3. **U3 — the ×3 group carve+remap** (54 fns / 6,414 ins, zero drafting). Per overlay ×3:
   `o0_subsplit <ov> --lo 0x8013B568 --hi 0x8013C98C` **plus, in the same commit, populate all 16
   bodies** by remapping the ov077 exemplars (the machinery `rollout_o0`/`family_remap` already
   keys these families — the dry run's 42 `no-o0b` rows ARE this list) with the §132
   `tables=+0x0,+0x70` spec on the new `_o0X` rodata carve; then the whale: carve
   [0x80144B9C,0x801457A4) whale-shape + U2's append for `func_801457A4`. Gate per overlay.
   Risk: populate-at-carve = the 137/137 shape; pre/post jr stubs remain, ×137-precedented. If a
   gate still refuses, revert the yaml (cheap), pin the drifted `D_*` in
   `config/symbols.<ov>.txt`, retry — the never-yet-tried surgical counter to §18-P29.
4. **U4 — the 50 covered** (2,037+131 ins): re-admit the `o0` lever for covered targets in wave
   draws; one `--only-bins main` mini-wave for boot's 48 through `gate_main`; one gate banks the
   `ov_SC03_015` twin with today's body.
5. **U5 — SC03_118/119** (20 fns / 918 ins): serial-or-wave draft the 10 distinct fns to MATCH
   against the stranded `.s` (works today), then `o0_subsplit` both twins at
   [0x80183178,0x801838A4) populated. One carve spec serves both (byte-twins).
6. **U6 — md_MAIN_003** (16 fns / 1,862 ins): draft all 16 to MATCH first, then
   `o0_subsplit md_MAIN_003 --lo 0x800D0100 --hi 0x800D1E18` populated + extend the md Makefile
   coverage:
   ```make
   MD_O0_OBJS := $(patsubst src/%.c,build/src/%.o,$(wildcard src/md_*/md_*_o0*.c))
   $(MD_O0_OBJS): CC1FLAGS := -quiet -O0 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker
   ```
   Pre-flight: verify `jr_isolate_all.plan()` on a jr-less md module (expected fine — it reads the
   yaml generically — but assert before trusting; R43).
7. **U7 — main/800 `func_8002C410`** (1 fn / 299 ins): draft to MATCH now and stage the body; carve
   the `800` subseg 3-way only in a dedicated main-surgery window (the `800b_N` splits are
   precedent, §18's mid-blob law was learned on this very object). Smallest payoff, biggest
   binary — last, manual, or accept matched-unbanked indefinitely.

**Oracle-coupling fixes to land WITH U1** (else the 21 stay invisible): three helpers key -O0-ness
on the subseg NAME (`'_o0' in seg or seg == 'boot'`) — `match_one`'s subseg oracle,
`build_wave_atlas._o0_unbankable`, `test_o0_detect.sub_is_o0`. U1's object keeps its plain name, so
they must derive from `corpus.o0_sources()` (the Makefile ground truth) instead of the name. Until
then the prologue oracle still auto-selects -O0 for all 21 (every one carries the tell), but the
atlas would keep refusing to draw them and `match_one` would mis-warn "cannot bank".

## 8. Appendix — the §18-P29 wall, restated precisely

Mechanism (decision-log 2026-07-16, Arm A): 3-way splitting a code subseg and re-running `make
extract` makes spimdisasm re-infer data auto-symbols inside the SPLIT subsegs; when INCLUDE_ASM
stubs remain **in the new -O0 object**, some `%lo` refs re-bind to a different auto-symbol (+0x20),
and the reassembled stubs shift 34% of the image. The discriminating variable across all recorded
attempts is stubs-in-the-new-object:

| attempt | shape | record |
|---|---|---|
| P29 `rollout_o0_cluster` SC07 ×4 | stubs left in `_o0` | 1/4 clean (010 only) |
| P30 `o0_subsplit` SC03_014/015 `_o0c` | stubs left in `_o0c` | 2/2 clean (dice-roll won) |
| P30 fleet `_o0c` rollout ×137 | **populated at carve** | 137/137 byte-neutral |
| whale `_o0b` ×134 | populated (shared header) | never hit the wall |

So: populate-at-carve when bodies exist (U3), draft-first to make bodies exist (U5/U6), and the
untried surgical fallback (pin the drifted symbol in `config/symbols.<bin>.txt`) if a roll is ever
lost anyway. The wall gates nothing in this plan; it only orders it.

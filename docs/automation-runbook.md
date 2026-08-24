# Automation runbook — the autonomous campaign, as it actually runs

**Rewritten 2026-08-24 (P31 S59).** The previous version described the June reach-1 grinder pivot and
was two months stale: it named no lane that exists today. If this file and the lane scripts ever
disagree again, **the scripts are the truth** — `tools/lanes/*.sh` are the tracked copies of what runs.

Companions: `docs/SETUP.md` (per-tool reference table, versions, install), `docs/accelerators.md`
(ops traps that cost real time), `docs/matching-cookbook.md` (the matching knowledge the drafters grep).

---

## 1. What runs right now

Six detached lanes, each `setsid`-launched from `.run/<name>.sh` (a copy of `tools/lanes/<name>.sh`):

| lane | script | what it does | safe to restart? |
|---|---|---|---|
| **drafter** | `.run/drafter.sh` | draw → shard → draft → queue a ready marker, forever | **Never stop it to ship a change.** Doing that cost 139 of 162 idle minutes on 2026-08-23. Restart only at a wave boundary (see §3) |
| **gater** | `.run/gater.sh` | reloc pre-filter → gate → commit → harvest → ledger | yes, freely — nothing is lost but the pause |
| **maintenance** | `.run/maintenance.sh` | free zero-token work when the gater is idle: the A-prop sibling sweep **and** `recover_rejects.py` (rebase pre-gate rejects whose body already matches and only the symbols are wrong — §171; 45% of drafts never reach the gate and 13% of those are recoverable) | yes |
| **stallguard** | `.run/stallguard.sh` | 60 s: revive a dead lane shell, kill agents silent >20 min, kill a gate >90 min, bounce an idle drafter | yes |
| **distill** | `.run/distill.sh` | watch harvested candidates, raise a READY marker when a batch is worth review | yes |
| **main** | `.run/main.sh` | the EXE's own draft→gate→commit cadence (§5) | yes — `gate_main` reverts its own aborts |

```bash
# is everything alive?
for l in drafter gater maintenance stallguard distill main; do
  printf "%-12s %s\n" "$l" "$(pgrep -f "bash .run/$l.sh" >/dev/null && echo alive || echo DEAD)"; done
pgrep -cf '^\.venv/bin/python -u tools/api_agent'      # drafting agents right now

touch .run/ox_campaign.stop        # THE KILL SWITCH — every lane exits at its next loop top
rm .run/ox_campaign.stop           # then relaunch the lanes you want
```

---

## 2. The drafting toolchain (OpenRouter)

`tools/ox_campaign.py --drafter` draws a wave, shards it, and spawns one `tools/api_agent.py` per
card. **Shard count tracks CARDS, not the `--workers` cap**: a 71-card wave runs 71 agents however
many workers are configured. Card supply, not throughput, is the binding constraint.

* **Models.** `--models 'stealth/ox-alpha:2000'` — ox is free for this window. The paid deepseek lane
  was dropped 2026-08-24 at $2.22 remaining (§7). Restoring it is two edits, named in the drafter
  script's header.
* **The card is the fuel.** `tools/build_wave_atlas.py` writes `.run/wave_<tag>_cards.json`:
  `fn · binary · nins · lever · model · tu · seed_ref · tu_ref · decl_prior`. `api_agent._fuel`
  renders it, and `LEVER_CRIB` explains what each lever MEANS plus the cookbook § to grep — a bare
  lever label is a dead end (108 transcripts grepped `extend-tell` against a cookbook containing
  that string zero times).
* **Budgets are per lane** (`ox_campaign.LANE_BUDGET`): tells gets 40 turns / $0.40, everything else
  24 / $0.15. One global cap starved the large cards — 98 of 270 tells attempts ended AT the cap.
* **Model routing inside a wave** is by function size (cookbook §157): Haiku ≤30 ins → Sonnet 50-120
  → Opus ≥120. **Fable is for new wall classes only — never for idiom distillation or review.**
* **Output budget and socket timeout are ONE setting** (P31 S59, probed directly against ox-alpha):

  | knob | value | why |
  |---|---|---|
  | `--maxtok` | **16000** | the model's thinking is IN the content stream (`reasoning_tokens=0`), so the output cap WAS the reasoning cap. At 8k, 240 of 244 turn-finishes in wave `bk` were `no tool call (finish=length) — NUDGE n/6`: the turn did no work at all. An uncapped hard prompt wanted **8,067** tokens — finishing exactly where the old cap cut it |
  | `HTTP_TIMEOUT` | **700** | ox generates at **~30 tok/s**, so a full 16k generation needs ~530 s. At the old 420 s the socket would kill the very turns the bigger budget exists to allow — and a timeout wastes the whole turn where truncation leaves a partial |
  | model ceiling | 1M context / **131,072** max completion | so 16k is OUR choice, not a limit. The binding constraint is the timeout, not the model |

  **The ordering that must hold:** generation < `HTTP_TIMEOUT` (700) < stallguard's wedged-agent kill
  (1200 s). 420 was itself deliberate — 1800 once parked a hung agent for thirty minutes.
  A **reasoning cap** (`REASON_CAP` → `reasoning:{max_tokens}`) does work on ox, but it shortens the
  ANSWER too (618-672 tokens against 8,067 uncapped): a quality dial, not a truncation fix.
* **Turn caps are NOT binding on the default lane.** Across 1,166 completions, non-MATCH runs used a
  median of 4 oracle calls and a p90 of 12 against 24 available; exactly 1 of 194 reached 20. Agents
  give up early after truncated turns — which is why the fix above is the budget, not the cap.
  (The tells lane WAS cap-bound, 98 of 270, hence its 40.)

### What the draw admits, and what it refuses (all counted in the skip census)

| filter | why |
|---|---|
| `o0-in-an-O2-object` | an -O0 function in an -O2 object cannot bank however good the draft (§261). 11 such were drawn **79 times across 19 waves** before this existed |
| `tells-oversize-serial-lane` | tell-lever members > `--tells-max-ins` (80). Bank rate 27-40% at 5-80, 10% at 81-120, 1% at 121-200, 0% above. Those 383 members are `idiom_serial`'s work |
| `jtbl-*` (`main-manual`, `island-blocked`, `island-pads`) | the gate's carve cannot reach that table yet (`jtbl_carve.island_probe`) |
| `jtbl-one-per-binary` | §61c: one table-bearing draft per gate invocation |
| `already-waved` / `already-banked` / `out-of-band` | ordinary pool bookkeeping |

**One lane, one band** (P31 S59): every wave is a full-range default draw. The tells slot became redundant when the quota landed, and the dedicated 120-2000 slot was the worst wave we ran — bank rate 3% at 120-200 and 6% above, against 57% under 50 ins. Large functions still appear: the full band contains them and the draw takes mass-first inside each gate group.

**Quotas** reserve cards that the gate-group ranking would otherwise never pick, because they are
spread thin across binaries: `--tells-quota 60`, `--jtbl-quota 6`. **A quota is a floor AND a
ceiling** — tells enter through the quota or not at all (left free, they took 41% of a test wave).

---

## 3. Changing something while it runs (read this before editing a lane)

bash parses a `while … done` body **in full** before executing it, so the loop's command line is
fixed for the life of that shell (`docs/accelerators.md` #5):

| change | how it takes effect |
|---|---|
| lane **code** (`tools/*.py`) | next python start — bounce the python, args are unchanged |
| lane **args** (the `.sh` invocation) | needs a fresh **shell** — `tools/lanes/relaunch_drafter_shell.sh` waits for a wave to queue first, so no drafts are lost |
| wave-draw **defaults** (`build_wave_atlas.py`) | next draw — it is a fresh subprocess per wave, no restart at all |
| the **gater's** args | `tools/lanes/restart_gater_when_idle.sh` — restarts once no sweep is in flight |
| the **main lane's** args | `tools/lanes/restart_main_lane_when_idle.sh` — restarts in the gap between its gate and its next draw |

Verify from the PROCESS, never the file: `tr '\0' ' ' < /proc/<pid>/cmdline`, or the startup banner.

---

## 4. The banking toolchain, by binary class

**A bank is byte-identical instructions AND a green whole-binary SHA1. Nothing else counts (G3/P9).**

| class | path | notes |
|---|---|---|
| overlays / md | `sweep_parallel` → `gate_stage` → `harvest_verify` | per-binary flock `.run/auto/gate.<bin>.lock`; distinct binaries gate concurrently |
| **main** | `gate_main.py` ONLY | incremental builds give a FALSE diff (main's extract rewrites the linker script). `sweep_parallel` REFUSES main (R43) after wave `ab` banked 0 of 105 |
| jtbl functions | the carve happens **at the gate** (`harvest_verify._jtbl_prep_one`), never pre-draw | §61b's proven order; `jtbl_lane.py` is the serial route |
| -O0 functions | ordinary gates, but only from an **-O0 object** | the Makefile decides per object; `corpus.o0_subseg()` is the oracle, not the subseg name |

Standing verification: **R22 = a CLEAN rebuild** (`make clean && make extract-all && make check-all`,
~1 min parallel). Do not run it while gates are building; scope it to the binary you touched with
`rm -rf build/<bin> build/src/<bin> && make extract BINARY=<bin> && make check BINARY=<bin>`.

**R42 — never revert a dirty `src/` or `config/`.** Other lanes bank real, byte-proven functions with
`commit=False`, and no tool can tell them from residue; a blind `git checkout` destroyed 61 banked
functions once. Commit named paths, or leave the tree alone.

---

## 5. The main lane (P31 S59)

main is excluded from every overlay wave draw (`--exclude-bins main`) because its gate is a clean
whole-EXE rebuild that bisects — three measured stalls put it off the critical path. It now has its
own lane instead of no cadence at all:

```
.run/main_queue/*.json  (parked drafts, free)      ─┐
build_wave_atlas --only-bins main                  ─┴→ draft → reloc filter → gate_main --apply
                                                        → verify main byte-identical → commit (R42)
```

* Batches of 40: **one clean rebuild verifies the whole slate** (~15 s measured), which is what makes
  main affordable. The reloc pre-filter keeps the batch from bisecting.
* On a `COMPILE conflict` the lane **halves the slate and retries** — `gate_main` deliberately
  refuses to bisect a decl clash (right for a human, wrong for an unattended lane: 40 innocent drafts
  died with one conflicting symbol that was in the TU and in no draft).
* Failed drafts are parked with a try count (`.run/main_queue_failed.json`), capped at 2.
* **Credit requires two oracles**: the `INCLUDE_ASM` line gone from the tree AND main re-checked
  byte-identical. The first version asked `corpus.stubs('main')` — which returns `{addr: Stub}`, keyed
  by INT — so a name-vs-int comparison reported "12 banked of 12" from a gate that banked nothing.

---

## 6. The distill lane and the flywheel

The gater harvests every wave before the next draw (`idiom_harvest.py`) into
`.run/idiom_candidates.<tag>.md`. That is EXTRACTION. **Distillation into the cookbook is what
changes the next wave**, because that is what the agents grep.

* `.run/distill.sh` raises `.run/distill_ready/<batch>.json` at ≥30 novel candidates or ≥2 waves.
* State is `{tag: novel-count-when-mined}` — never a done-list, because a re-gated wave rewrites its
  candidate file under the same tag.
* **The reviewer is an Opus or Sonnet subagent, never Fable** (Drew, 2026-08-24).
* Measured yield, twice: **~82-88% of candidates are already covered**, ~1 new law + ~10 addenda per
  80 candidates, and **one in three credited levers is byte-inert** (§266 — strip it and recompile
  before writing the law).
* Wave N's ore is distilled while wave N+1 drafts, so **wave N+2 is the first that can grep it**.
  That one-wave lag is the price of never pausing the fleet.

---

## 7. Rate limits, credits, and the measured ceiling

| fact | number |
|---|---|
| lifetime requests / 429s | 121,166 / 7,667 = **6.3%** |
| 429 attribution | 100% provider shared capacity (`openrouter_shared_capacity`, `upstream_provider_shared_pool`) — **zero platform refusals, ever** |
| steady state | 50-95 req/min → **0-3.5%** 429s |
| the knee | 195-227 req/min → **6.6-12.7%** 429s |
| one-minute peak observed | 2,755 requests |
| per-agent request rate | 0.31-0.78 req/min (mean ~0.6) — so ~350-380 agents sits at the knee |
| retry policy | `MAX_429=10` with 20 s backoff (default 6). A 429 costs a retry; an idle agent costs a card |

Telemetry: every request appends to `.run/api_rate.jsonl`; read it with `tools/api_rate.py`.
**Bucket 429s over time before calling anything a ceiling** — launch bursts fake one.

**Credits.** `credits_left()` reads the OpenRouter balance. `--credit-floor` does **not** pause the
paid lane, it breaks the whole drafting loop — and the shell then restarts a python that breaks
again. With a free model the balance is not a proxy for "can we draft", so the floor is 0.25.

---

## 8. Recovery

1. `git status --porcelain -- src/ config/` — if dirty, **COMMIT it, never revert** (R42). The one
   safe revert is `src/800.c`/`src/800c.c` alone when a `gate_main` was interrupted mid-substitution.
2. Salvage drafts: `find .run/wave_* -name '*.c' | wc -l` — drafts survive crashes and are worth
   re-gating via `ox_campaign.py --gate-only <tag>` before drafting anything new.
3. Relaunch lanes: `setsid nohup .run/<lane>.sh >> .run/<lane>.log 2>&1 </dev/null &`, and verify
   from the STARTUP BANNER, not the file.
4. Drafting is the clock-limited resource (the free-model window) — start it FIRST, do bookkeeping
   while it runs.

**Never `pkill -f` a lane by a bare name**: it matches the harness's own `bash -c "… eval '…'"`
wrapper and kills the command issuing it (three times, twice fatally). Anchor the pattern
(`'^bash \.run/drafter\.sh'`) or collect PIDs first and `kill` them in a separate call.

# Crack-wave performance metrics

> **Evolvable reference (docs/ layer).** Started 2026-08-04 (Phase 30, sessions S33–S37).
> **Append one row per wave.** The point of this file is that the wave harness has knobs — the
> prompt, the concurrency shape, the model tier — and their effects are only visible if the numbers
> are recorded in one place. Two of them were already measured to matter a lot (§ below).
>
> Sources, all derivable — do not hand-transcribe (R33):
> - counts/tokens/duration: the Workflow completion notification (`agent_count`, `subagent_tokens`, `duration_ms`)
> - per-agent wall-clock + parallelism: `min/max(timestamp)` per `agent-*.jsonl` under
>   `~/.claude/projects/.../subagents/workflows/<runId>/`
> - banked: the whole-binary gate log (`.run/s*_gate.log`) — **the gate is the arbiter, never the
>   agents' claim** (G3/P9)

## The table

| wave | script | targets | templ ins | agents | tokens | wall | parallelism | median / slowest agent | claimed | **banked** | +members |
|---|---|---|---|---|---|---|---|---|---|---|---|
| 1 (S33) | `s33w.js` | 17 | 26,227 | 25 | 6.87M | 169 min | 4.8× | 33 / 63 min | 15/17 | **15** (13+2 rec) | 65 |
| 2 (S34) | `s34w.js` | 13 | 37,943 | 19 | 4.51M | 208 min | 2.7× | 20 / 79 min | 11/13 | **10** (9+1 rec) | 18 |
| 3 (S35) | `s35w.js` | 13 | 17,644 | 14 | 2.73M | 140 min | 2.1× | 9 / 51 min | 13/13 | **13** (12+1 rec) | 21 |
| 4 (S36) | `s36w.js` | 14 | 16,844 | 17 | 2.99M | 136 min | 2.5× | 14 / 48 min | 14/14 | **14** (13+1 rec) | 26 |
| 5 (S37) | `s37w.js` | 16 | 16,884 | 19 | 2.71M | **82 min** | **3.8×** | 9 / 50 min | 16/16 | **16** (16+0 rec) | 26 |

All waves: Sonnet drafters with an Opus escalation rung (§136i), whole-binary byte-gate as the sole
arbiter, R22 clean-fleet 140/140 after every banked batch.

## Finding 1 — the PROMPT is the lever, and the agents write it

Bank rate **76% → 77% → 100% → 100% → 100%**, with the models and the gate held constant. The only
variable was the prompt's `extra` block.

The jump came from **STEP 0: `grep -rn "<MAGIC>" src/`** using a distinctive literal from the target
`.s`, placed *ahead* of `engine_core.h` in §136c's search order — because §136c's first two steps are
same-TU/shared-header scoped and structurally cannot reach a banked twin in a *different overlay's*
TU, which is where the big template classes live.

**That step came from a wave-2 agent's `index_gap` report.** The wave schema asks every agent for
`index_hit` / `index_gap`; harvesting those into the next wave's prompt is what compounds. By wave 4
most agents cited step 0 by name and reported `index_gap: none`.

*Honesty caveat:* wave 3–5 targets also trended easier (smaller families, more banked twins
available), so the prompt is not solely responsible for 100%. The claim that holds without
qualification is the direction and the mechanism, not the exact percentage.

## Finding 2 — `pipeline()` vs batched `parallel()`: 40% faster on 14% more targets

Waves 1–4 split each wave into two `parallel()` batches, which is a **hard barrier** — batch 2 cannot
start until batch 1's slowest agent finishes. Visible directly in the launch timestamps as 37–50
minute dead gaps at each boundary.

| | wave 4 `parallel()` | wave 5 `pipeline()` |
|---|---|---|
| targets | 14 | **16** |
| wall-clock | 136 min | **82 min** |
| parallelism | 2.5× | **3.8×** |
| median agent | 14 min | 9 min |

The batching existed to dodge S10's 30-wide server throttle, but the harness already caps workflow
agents at `min(16, cores-2)` and these waves are 13–16 targets — so it bought nothing and cost a
barrier. **Use `.run/s37w.js`'s execution block for every future wave.**

**The remaining floor is real:** the slowest single agent is still ~50 min at 200–300 turns. That is
genuine `match_one` iteration (one agent tested 470+ statement orderings on a 793-instruction
function). Wall-clock cannot go below the slowest chain, so the lever there is target *selection*,
not concurrency.

## Finding 4 — a perfect gate is a signal that the prompt rules landed

Wave 5 is the first **16/16 banked with ZERO reconcile**. Waves 1–4 each needed 1–2 declaration
reconciles after the gate; wave 5 needed none. The difference is that by then the prompt carried
both §138 rules (the *(macro-shape, TU-shape)* pair, and the reconcile-direction line-number check)
plus the wave-4 lesson that two targets sharing a TU can create each other's conflicts. **The
reconcile lane is the fallback, not the plan — when it goes quiet, the prompt is doing its job.**
Lifetime reconcile record across the session: **21/22**.

## Finding 3 — economics

Roughly 170k–300k tokens per banked head across waves 3–5 (the stable regime). But a head is not the
unit of value: **the unit is the head plus its propagated members**, and the sweep rate is a property
of the FAMILY, not the wave — wave 3 swept 21/21 while wave 2 swept 18/165, because wave 2's big
families are per-location variants that do not template (settled by probe: remapped member is BUILD
OK **and** byte-different ⇒ genuine per-member codegen). **Rank targets by open templatable
instructions derived from `corpus.stubs`, and expect the sweep yield to be bimodal, not average.**

## How to add a row

After a wave's gate + sweep land, before the commit:

```
# tokens / agents / duration: from the Workflow completion notification
# parallelism + per-agent spread:
python3 - <<'PY'
import json, glob, datetime
d = "<runId dir under ~/.claude/projects/.../subagents/workflows/>"
T = lambda s: datetime.datetime.fromisoformat(s.replace("Z","+00:00"))
ag=[]
for f in glob.glob(f"{d}/agent-*.jsonl"):
    ts=[T(r["timestamp"]) for r in map(json.loads, open(f)) if r.get("timestamp")]
    if ts: ag.append(((max(ts)-min(ts)).total_seconds()/60, min(ts), max(ts)))
wall=(max(a[2] for a in ag)-min(a[1] for a in ag)).total_seconds()/60
tot=sum(a[0] for a in ag); ag.sort()
print(f"{len(ag)} agents · wall {wall:.0f}m · agent-time {tot:.0f}m · {tot/wall:.1f}x · "
      f"median {ag[len(ag)//2][0]:.0f}m · slowest {ag[-1][0]:.0f}m")
PY
```

Related: cookbook **§138** (the reconcile/search rules these waves produced), memory
`wave-prompt-seed-step0-and-gaps` (what to seed the next prompt with), `docs/effort-map.md`
(Ultracode/breadth policy), `docs/calibration.md` (templatability measurements).

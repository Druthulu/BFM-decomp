### `tools/gap_triage.py` — harvest pre-filter (added P31 S55)

Scores a wave's `index_gap` reports against every cookbook section by IDF-weighted distinctive-term
overlap (`file.c:line` cites, `§` refs, register names, MIPS mnemonics, pass names) and names the
sections a reader should open first.

```
.venv/bin/python tools/gap_triage.py .run/wave_<N>_gaps.json [--min-score 0.15] [--top 3]
```

**Why it exists:** the majority verdict of every harvest so far is "already covered" — 61/71 (T),
44/64 (U), 76/67 (V), 41/68 (W), 56/63 (X) — and reaching that verdict is a text search, which does
not need a model. It runs as **step 0 of the harvest reader prompt**.

**What it is not:** an oracle. It is deliberately dumb term overlap, no embeddings; a candidate is a
starting point and an empty list is not evidence of novelty (it misses paraphrase entirely). The
0.15 default was set by measurement, not taste — on wave Y's 67 gaps the top-candidate scores ran
min 0.009 / p50 0.08 / p90 0.26 / max 0.53, and hand-checking below the threshold found generic
co-occurrence ("delay slot" matching every section that says "delay slot"). Emitting those is worse
than emitting nothing: an empty list costs a reader nothing, a plausible-but-wrong section costs a
read. At 0.15 it reports 14 confident candidates out of 67 rather than 51 mostly-noise ones.


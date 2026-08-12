# tools/wave — the crack-wave harness (P30 S48)

`crack_wave.js` is the CURRENT wave script, kept in the repo because it encodes contracts that were
paid for in real failures. Invoke with `Workflow({scriptPath: "tools/wave/crack_wave.js", args:[…]})`
where each arg is `{name, binary, sub, nins, reach, jr, model, prior}`.

**Contracts it encodes — do not drop these when editing:**
* **Per-agent output dir** `.run/waveN/<fn>/`, and "never delete or modify anything outside your own
  directory, do not clean up". Wave 2 shared one directory and later agents deleted earlier agents'
  drafts: 21 adversarially-VERIFIED cracks vanished. (They were all recovered from the run
  transcripts by `tools/recover_drafts.py` — but only because the transcript is the backup.)
* **The verifier re-runs `sha1sum` LAST**, after the gate, and reports it separately, so a draft that
  vanishes mid-run is DETECTED rather than trusted.
* **Prior-notes seeding.** A target that previously failed is re-run WITH ITS PREDECESSOR'S MEASURED
  RESIDUAL (`.run/jr48/prior_notes.json`). Measured 7/9 (wave 3) and 10/12 (wave 4). NEAR is a cheap
  RESUMABLE state, not a write-off.
* **The cookbook citation list must name every banked block** (§160-§164 today). Idioms are harvested
  after every wave precisely so the NEXT wave's agents start with them; a stale citation list silently
  wastes that.
* **Size-routing** haiku ≤30 ins / sonnet ≤120 / opus above. Wave 2 (20 of 28 Sonnet) beat the
  all-Opus wave 1 on bank rate.

**Bank rate to date:** 67% → 79% → 69% → 68% of cracks survive the whole-binary gate.

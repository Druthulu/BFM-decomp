## §8 Model strategy per phase

Principle: the oracles (SHA1 check, asm-differ, RAM-dump byte-compares) make *correctness* model-independent — a weaker model can't fake a match. Model tier therefore buys **fewer dead ends in ambiguous work**, not safer results. Spend the strongest available model where ambiguity is highest; let the oracle-protected grind run on cheaper tiers. (Precedent: psxrecomp's post-mortem — model capability was load-bearing exactly once, on the most ambiguous subsystem.)

| Phase | Reasoning demand | Recommended tier |
|---|---|---|
| 1 — Installs, EXE import | Mechanical | Standard (Opus-class) |
| 2 — Extraction pipeline | Well-specified coding vs byte-exact oracle | Standard |
| **3 — File-loader & overlay-map RE** | **Highest in project** — raw MIPS reading, US address derivation, RAM-dump experiment design | **Strongest available** |
| 4 — WSL setup | Mechanical; **order-flexible** (nothing in 1–3 depends on it — schedule it when the strong-model window is closed or limits are exhausted) | Any |
| 5 — splat config + build skeleton | Iterative debugging, loud error signals | Standard; strongest if available |
| **6 — Compiler fingerprint + first matches** | **Second highest** — ASPSX 2.56-vs-2.67 idiom discrimination is subtle. The fingerprint *analysis* is pure RE and can be front-run before Phase 4/5 exist if a strong-model window is closing | **Strongest available** |
| 7 — Matching at scale | Pattern grind against hard oracle | Standard; smaller tiers acceptable for bulk iteration (cost = wasted iterations, never wrong matches) |

Budget notes (Max 20x plan): long autonomous RE sessions are token-hungry; prefer single-agent flow with oracle checks for in-phase grind, reserving multi-agent fan-outs for verification moments. *Window note (2026-06-10): Fable 5 access expires ~2026-06-22 — priority order for that window: Phases 1→2 fast, then maximum depth on Phase 3, then Phase 6 fingerprint analysis if time remains; defer Phase 4 past the window.*

---


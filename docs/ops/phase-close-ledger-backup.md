# Phase-close ledger backup (P3.40 T15)
When: every phase close, before the PhaseEnd archive (the ledgers live in gitignored `.run/` and go with it).
Command: `/usr/bin/python3 tools/ledger_backup.py` (phase from the `# Phase X.YY` header of `phase-ends/current/PHASE_PLAN.md`; `--phase` overrides); `--scan` first when a ledger gained fields.
Inputs: `.run/P37/restruct/ledger.jsonl` (restruct-ledger), `.run/P36/delever/ledger.jsonl` (delever-ledger); streamed, never modified.
Outputs:
- full: `../BFM-decomp-archive/ledgers/P<phase>/<name>.jsonl.gz`, every line unchanged; the tool commits it in that clone (`ledgers: P<phase> snapshot`). Local only: the developer pushes. Older `ledgers/P*/` dirs are kept. Clone made with `gh repo clone Druthulu/BFM-decomp-archive ../BFM-decomp-archive -- --depth 1` when absent.
- public: `docs/ledgers/<name>-P<phase>.jsonl.gz`, committed here (`git add -f` if ignored); `audit_public.py` cannot look inside a gz, so the tool self-verifies: every line parses, record count == source, disassembly-predicate hits 0, size < 50 MB (rc 1 otherwise).
Dropped from the public copy (disassembly or ROM-derived operands): restruct `residual.pairs` (objdump word+mnemonic pairs), `hint`; delever `sites[].detail` (register/mnemonic operand), `sites[].why`, plus `before_text`, `after_text`, `source`, `record.direct[].delta` (the 3.40 `--scan` found `$reg` tokens in them: C register-pin annotations; the full archive copy keeps them). The full list and the predicate are in `--help`.
Restore: `zcat docs/ledgers/<name>-P<phase>.jsonl.gz | ...` (one JSON record per line); the full lines: `zcat ../BFM-decomp-archive/ledgers/P<phase>/<name>.jsonl.gz > .run/<...>/ledger.jsonl`.

<!-- decomp-architect: appended VERBATIM to the project's CLAUDE.md at Step 8, as a marked section (ProjectArchitect's own
     precedent for merged content). Nothing above it in CLAUDE.md is edited. -->

## Decomp fail-safes (decomp-architect, Phase 0.5 — installed {{INSTALL_DATE}})

*Duplicated here so they survive even if the Session Start Protocol is skipped; the full rules are the registry's G-group.*

- **Never commit game-derived bytes.** The dump, extracted payloads, generated disassembly, assets, build output, memory
  images, the reverse-engineering database, the vendor SDK, transcripts that quote disassembly, and any text file that
  pastes the target's instructions stay out of git — from the first commit, private or not. `config/firewall.txt` and
  `tools/audit_public.py` enforce it; review `git status` before every commit.
- **A match is byte-for-byte AND the whole-binary hash stays green.** Never report a functionally-equivalent function, a
  passing-looking build or any unverified outcome as done; verified from a clean rebuild, never incremental
  (`{{FLEET_CHECK_CMD}}`); a build is verified by its exit code.
- **Never `git clean -x` / `git clean -fdx` in this tree.** The game-derived data is ignored-but-present; a `-x` clean deletes
  the reverse-engineering database. `make clean` is the only clean.
- **The byte gate is the only claim.** "Banked" is written only from a tool's printed success line; names and types are
  evidence-based, never guessed; outward text to third parties is written by a person.

## Session-start extras (decomp-architect)

- **The digest replaces the full PhaseEnd read once it exists.** When `phase-ends/DIGEST.md` exists, step 3 of the Session
  Start Protocol reads the digest (every phase's synopsis) and the **three most recent** PhaseEnds in full, instead of every
  PhaseEnd — the protocol's cost stays bounded as phases accumulate. Every PhaseEnd appends its synopsis to the digest.
- **Replay the checkpoint verbatim.** The `## 🛑 SESSION CHECKPOINT` block at the end of `phase-ends/CURRENT_PHASE.md` is
  reproduced in full in the session-start message, never summarised; it is the only in-phase context the session inherits.
- **The oracle ping only when the next task is reverse-engineering.** Verify the disassembler server with one cheap call
  before any RE task — not merely because the phase contains RE tasks somewhere. After a server restart or a program switch,
  pause and ask the developer to reconnect the client; the agent cannot.
- **The flywheel.** Before recurring matching work, consult `docs/{{COOKBOOK_NAME}}` by symptom (grep the index; never read a
  large cookbook whole) and the pinned triple; after a hard-won match, feed the generalisable lesson back into both the
  cookbook and the tooling.
- **Effort.** Max for the compiler pin, an address derivation, the segmentation decision, any wall verdict, the phase plan and
  the PhaseEnd; breadth (isolated agents) for fleet-wide audits and bulk drafting; every transition prompted and waited for.

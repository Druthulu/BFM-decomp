# PLACEHOLDERS.md — every `{{…}}` the decomp kit uses, and when each is filled

> **The contract.** The set of placeholders that appear anywhere under `decomp-architect/` (this file included) must equal
> the set listed here — `tools/kit_lint.py` computes both with one regex over the package and diffs them; a placeholder
> used in a template but not listed, or listed but unused, fails the lint. Adding a placeholder means editing this file
> in the same change. After the kit's install, the leftover-placeholder audit (ProjectArchitect's F9 rule, run again at
> the kit's Step 10) must find none of these anywhere in the project outside the kit's own package folder and the
> reference copy of the methodology.
>
> **Two classes**, following ProjectArchitect: **copy-time** placeholders are filled while the templates are copied in
> (the kit's SETUP Steps 2–5, from the game interview and from values ProjectArchitect already stamped); **generation-time**
> placeholders are filled when the overlays are generated (Steps 7–9), and some legitimately stay a `TODO` until the phase
> that produces their value — those say so.

## Shared with ProjectArchitect (read back from the files it already stamped; never re-asked)

| Placeholder | Filled from | Used in |
|---|---|---|
| `{{PROJECT_NAME}}` | the installed `CLAUDE.md` title | the README and CONTRIBUTING skeletons, the docs and scratch READMEs |
| `{{INSTALL_DATE}}` | today, in the same format ProjectArchitect used | every overlay's "installed" line |
| `{{COOKBOOK_NAME}}` | the cookbook file ProjectArchitect created under `docs/` | the CLAUDE overlay's flywheel line, the cookbook overlay |
| `{{DOMAIN_FAILSAFES}}` | **referenced only, never filled by the kit** — ProjectArchitect's own CLAUDE.md placeholder, which its generation step fills from the intake's Part D | `intake.decomp.md` Part D names it so the generation step knows which four fail-safes to write |

## Copy-time (the game interview — SETUP Step 2)

| Placeholder | What it is | Used in |
|---|---|---|
| `{{GAME_TITLE}}` | the game's title | the intake, the README skeleton, the ops-setup overlay |
| `{{GAME_SERIAL}}` | region and serial (the identifier printed on the medium) | the intake, the README and NOTICE skeletons, the ops-setup overlay |
| `{{PLATFORM}}` | the console or platform | the intake, the README and NOTICE skeletons, the ops-setup overlay, `TODO(platform)` resolution |
| `{{TARGET_BINARY}}` | the main executable's file name on the medium | the ops-setup overlay, the firewall config's first purge path |
| `{{DUMP_PATH}}` | the absolute path of the developer's own dump — machine-local, never committed | the intake; the machine-local line of the ops-setup overlay only |
| `{{CONTAINER_LAYOUT}}` | one line: how code is packaged on the medium (archives, overlays, compression) | the intake, the docs README, the ops-setup overlay |
| `{{SDK_EVIDENCE}}` | the SDK/compiler-era evidence found (library version stamps, strings, a loader's detection) | the intake, the ops-setup overlay, the cookbook overlay's pinned context |
| `{{COMPILER_FAMILY}}` | the compiler family the evidence suggests — a candidate set, not the pin | the intake, the ops-setup version-pins row (`TODO` until Phase 4 replaces it with `{{TOOLCHAIN_TRIPLE}}`) |
| `{{COMMUNITY_WORK}}` | prior public work found, or "none found on <date>" | the intake, the README skeleton's acknowledgements |
| `{{PROJECT_GOALS}}` | the developer's stated goals, one paragraph | the intake, the README skeleton |
| `{{LICENSE_CHOICE}}` | the license for tools and documents, and the statement made over the decompiled source | LICENSE, `src/NOTICE.md`, the README skeleton |
| `{{AI_DISCLOSURE}}` | the project-level sentence disclosing how AI is used | the README skeleton, CONTRIBUTING |
| `{{PUBLIC_OR_PRIVATE}}` | the day-one visibility decision (the firewall applies either way) | the README skeleton, the ops-setup git posture |

## Generation-time (the overlays — SETUP Steps 7–9)

| Placeholder | What it is | Filled when | Used in |
|---|---|---|---|
| `{{TOOLCHAIN_TRIPLE}}` | the pinned compiler → assembler shim → binutils triple with flags | **Phase 4** — installed as a literal `TODO(phase-4)` line that the pin task replaces | the ops-setup version pins, the cookbook overlay's pinned context |
| `{{EXTRACT_CMD}}` | the one command that extracts the medium and verifies the manifest | Step 9 (as `TODO(phase-1)` until the extractor exists) | the ops-setup build/run/test block |
| `{{FLEET_CHECK_CMD}}` | the clean fleet verification (`clean → extract → build` over every binary, exit code read) | Step 9 (`TODO(phase-3)` until the baseline exists) | the ops-setup gate line, the CLAUDE overlay's fail-safe wording |
| `{{DISASSEMBLER_MCP}}` | the disassembler server's endpoint and the command that starts it | Step 9 (`TODO(phase-2)`) | the ops-setup MCP/hooks row |
| `{{EMULATOR_BRIDGE}}` | the runtime oracle's scripting interface or bridge endpoint | Step 9 (`TODO(phase-2)`) | the ops-setup MCP/hooks row |

## Not placeholders (by design)

- `TODO(platform)`, `TODO(phase-N)` markers are for the developer, in prose or config; they are not filled by the
  installer and are not in the placeholder set. The kit's lint counts them separately so the README can say how many
  remain.
- The registry seed's G-numbers are literal (G1–G65 by construction, see `registry-E.decomp.md`'s header); there is no numbering placeholder.
- The firewall config's hash sources are literal paths tagged `required:` or `pending:`, not placeholders; a `pending:`
  source becomes `required:` at the phase that creates it (the audit fails on a missing required source and warns loudly
  on a missing pending one).

## The check (what `kit_lint.py` does with this file — task 11 of the kit's own build)

```
used   = sorted(set(re.findall(r'\{\{[A-Z_0-9]+\}\}', <every file under decomp-architect/>)))
listed = sorted(set(re.findall(r'`\{\{[A-Z_0-9]+\}\}`', PLACEHOLDERS.md)))
assert used == listed, (set(used) ^ set(listed))
```

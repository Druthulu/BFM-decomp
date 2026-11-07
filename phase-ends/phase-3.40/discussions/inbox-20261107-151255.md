# INBOX

<!-- The developer writes here whenever they want; nobody asks them to. Freeform bullets.
     The router consumes it at the top of every loop (`tools/status.py inbox-consume`),
     which prints the contents, archives them to discussions/inbox-<ts>.md and empties
     this file. Items that change the plan become plan_edit.py edits with a Changes line;
     items that change a standing fact go to HOW_WE_WORK.md.
     Routing: each bullet becomes an I<n> row in discussions/INDEX.md, deferred:<P> or now.
     First match wins: `-> 3.12` / `-> Gen 4`; `Gen N` beyond this generation; a later
     plan phase id (`3.11 ...`); the word `later` (next open phase); else now. The current
     or an earlier phase, or an id not in GENERATION_PLAN.md, routes now. -->

- <note, correction, priority change, or question>
- -> 3.45 License: developer wants no commercial reuse (free community mods OK, selling not). Recommended CC BY-NC-SA 4.0 for src/ + docs/ (src/ has no license today); tools/ stays AGPL unless decided; tools/brave-CUE GPL untouched; check sole-contributor before relicensing; update README license section + headers; audit_public.py. Prompted by Blizz127 MIT PC port (2026-10-14).

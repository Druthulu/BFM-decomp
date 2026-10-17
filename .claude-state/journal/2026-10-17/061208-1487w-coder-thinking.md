---
ts: 2026-10-17T12:12:08.789Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a56c959d43d67f5c6
model: claude-opus-5-5[1m]
effort: medium
turnId: 0c52f25b-3226-4f4e-bcd1-94c2abf6159e
---
I'm checking that copy at 5deb6e94a9dc with its 5 instances, but noticing each duplicate uses a different function name across its own translation unit, so the signature change needs to track each copy's local naming rather than a shared header.

For each crack/copy pair, I'm planning to pull the exemplar's head body and sibling body, remap them, and write the file before applying it. The tricky part is that prototypes and definitions must change together — editing the prototype alone while the definition still uses the old type would cause a conflicting-types compile error, so both edits need to land atomically before I run apply-body and verify the byte comparison.

I also need to double check callers in other TUs within the same overlay that reference this function with the old prototype, since their return value isn't used the signature change shouldn't affect their bytes, but I should confirm that with a full check-all rather than assume. Next I want to look at the exemplar's definition, the relevant win.c files, and compile a table of all known copies.

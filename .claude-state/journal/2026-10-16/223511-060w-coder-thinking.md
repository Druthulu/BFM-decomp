---
ts: 2026-10-17T04:35:11.550Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5605ba96cc5ff027
model: claude-opus-5-5[1m]
effort: medium
turnId: 0c792287-f11f-4848-8566-c39a9bb058a0
---
I'm noting that the ov_SC07_000-type files have K&R-style function declarations proven byte-exact via rung D, where calls pass either 0 or 1 arguments — meaning conversion to ANSI style would require updating those short calls. The shared header files are included by SC03_126 and SC04, which matters for scoping the fix.

The scope question is tricky since there are 188 affected files across many overlays, but the stated constraints only cover the ov_SC07_* path. My plan is to handle the four extend translation units' declarations and calls plus the shared body extension and the exception row removal, tackle the K&R sites within ov_SC07_* that are byte-confirmed, and flag the remaining out-of-scope sites in other overlays and shared headers as findings for further review, since changing those headers would ripple into non-SC07 binaries that aren't covered by the constraint list.

I'm breaking the work into phases: first convert the four extend TUs' function declarations to proper prototypes with explicit parameter types and update their short calls accordingly, verifying each with a build check; then convert the remaining K&R sites in the other ov_SC07 files one at a time, checking output and reverting any that cause binary differences.

Planning a Python script to handle the edits across many files rather than sed, since the patterns vary slightly between prototype declarations and K&R forward declarations with mismatched argument comments, plus the short call sites that need the correct first parameter cast depending on each file's variant.

I'll write a script to fix each short call so it passes the enclosing function's first parameter (cast to `s32` if it's a pointer) across the 4 extend TUs and the ov_SC07 files, then run `make check` on every touched binary.

---
ts: 2026-10-17T17:45:52.457Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af8c379eaae6cf6ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 4f5d1d7b-243b-4976-9079-51d9b9c05b4b
---
I'm trying to work out what counts as a MATCH here — whether dropping the singleton rows for a given file/func pair is enough, or whether I need to verify that unused pins like the one in func_80185944 are actually accounted for in win.c before treating it as resolved.

For PARTIAL cases, I'm checking whether a "kept" kind actually matches one of the row kinds — if it doesn't (like the pin case for func_80185944), it gets ignored and the original row, like the missing-parameter pin, stays untouched rather than being dropped alongside the launder rows.

For MATCH, I'll simplify by dropping rows where the cause starts with "singleton(" for that file/func pair, then let the strict check handle whatever else needs arbitration — I'll just write this logic and verify its output against the TSV data. I also need to confirm WALL causes pull their best/tries values from the results, and that shared header files under src/shared/ov are keyed properly in the TSV since they're included by many translation units. LoaderInitFileTable being WALL in G01 means it only needs a TSV rewrite, no swap required.

Now checking func_80157BC8's MATCH status and header, then comparing win.c against orig.c to see if win.c captures the entire function definition including leading comments — I should look at a sample WH1 win.c to confirm.

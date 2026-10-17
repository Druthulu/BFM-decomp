---
ts: 2026-10-17T16:42:35.739Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6aaa11811b8be773
model: claude-opus-5-5[1m]
effort: medium
turnId: c3153718-defe-4620-a7c2-e0184cae88c0
---
I'll start with the smallest items to maximize matches, beginning with func_8017DF44 which is only 13 lines. My plan is to extract each function's current definition, identify the compiler levers, try removing or restructuring the C code, and score the result with dt.sh, working smallest to largest.

I'll process each item by copying its current definition to orig.c, stripping listed lever kinds, and scoring lever-free variants with dt.sh using only genuine C moves (temps, declaration order, widths, statement order, folds), starting with the smallest items first. I'll log every result in results.tsv as MATCH, PARTIAL, or WALL with gcc pass and mechanism evidence, keeping all writes confined to W07.

---
ts: 2026-10-17T15:48:53.276Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abc9700d4a3ffcffd
model: claude-haiku-5-5[1m]
effort: medium
turnId: 7ef976bd-e783-42c8-aead-e51ace4d47d5
---
I've used enough calls now, so it's time to write the report file to the pending research folder, naming it with the agent and a descriptive slug like "retriever-phase340-t7-t10-lever-residue.md".

Before writing, I'm keeping track of the row counts across tasks to flag discrepancies—T7's missing-parameter survivors drop from 546 to 384, with total data rows going from 2430 to 2269, and T8 continues the trend down to 2042. I need to note that the T9/T10 residue figures don't line up cleanly with the TSV line counts, so I'll flag that uncertainty in the report while keeping the whole thing compact and under the line cap.

Noting that the pass names appear only in the logs, not the TSV instrument column — important for reconciling T9. For T10, residue counts don't match (2342→2309 vs 1457), which I'm flagging as a discrepancy, and I'm now cataloging the 8 surviving non-cracked samples by their specific compiler-pass causes: scheduling hoists, CSE merges and substitutions, and stack-switch cases with no C equivalent.

I'm checking whether there's a standard "wall:" tag convention in the repo, but find none — the T10 wall text is just free prose, not a structured label. Now I'm sorting through which categories haven't been re-judged yet, like the head-class groupings and missing-parameter refusals, trying to track which rows T7, T8, and T9 actually touched versus left alone.

For the lying declarations question, I'm tracing through T8's cracks: func_80026514 and func_800268D0 got their extern decls changed from void to u8* while keeping the K&R-empty parameter list, and func_800CBA44 similarly moved from extern void to extern s32. Since all three keep the empty-parens style, type_census still flags all three as lying — I'm also noting the CAST_NONSTRUCT unbacked count discrepancy between T7's measurement of 5 and T10's claim of 1 pre-existing, with no clear log pinning down the origin.

The fix options are either to add these three to lying_exceptions.tsv (which T6 emptied to header-only) or convert the declarations to full prototypes, since the plan explicitly allows K&R-empty to be load-bearing in some cases. I'm also checking for any "wall" vocabulary convention in the TSV cause/instrument columns but haven't found one yet.

Now I'm sorting through the T10 numbers: 430 remaining functions, 572 rows, projected ~258 cracks against ~172 survivors, with cost and timing estimates (~17M crack tokens, ~2M banking, ~14h wall), recommending option (a) with an amended milestone. I also want to flag the parked items (unresolved instruction rows, the func_80188C04 family, the func_80177940 signature issue) and note the ambiguity between the 2342 residue count and 1457 TSV rows before writing everything up.

I'm ready to write the digest file now at the specified path, keeping it near the 40-line cap, with the standard header fields (task, agent, tags, sources) followed by the findings sections, then send the handback report pointing to that pending file.

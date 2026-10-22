---
ts: 2026-10-22T00:35:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_UXxd0bxdrqbC5LzhLkoq
---
c3 = 54, worse.

So item 3's best is c1 (score 2). WALL.

Time check: it's about 20:20 now. I've done 3 items in ~2 hours. 8 items left. At this rate that's 5+ hours. I need to speed up considerably. Let me prioritize:
- For each remaining item, do a quick pass: read the function, write a lever-free candidate (removing the lever), score it, and look at the residual. If the residual is small, try 2-3 targeted fixes. If not, record a WALL.
- Budget ~8-10 min per item.

Let me record item 2 and 3 results now, then continue.

Item 2: WALL cse-const-addr, best 10, tries 3.
Item 3: WALL, best 2, tries 3. Tag: the mechanism is that the asm makes n opaque so the per-loop `if (n != 0)` tests survive; plain C folds them since n ∈ {16,20}. Tag: `fold-range-nonzero`? Hmm, maybe better: `cse-redundant-test`? The pass that removes them: it's the RTL "jump threading"/cse that removes a conditional jump whose condition is known. I'd name it `cse-known-nonzero`. Let me use `cse-known-nonzero`.

Hmm, "cse" isn't exactly the pass. GCC's flow analysis (flow.c) computes the known nonzero bits, and then the branch is removed in flow/rtl-expand. Let me name the tag `flow-known-nonzero`.

Let me now write the rows and moves lines for items 2 and 3, plus win.c and notes.md for each (win.c = the best lever-free body).

For item 2: win.c = c1 (the simple lever-free version, score 10).
For item 3: win.c = c1 (score 2).

Let me batch: copy c1 → win.c for both items (cp via run.sh), write notes.md, append results rows and moves lines.

Actually, the results.tsv rows: let me use printf with tabs. In printf, "\t" works.

Let me do it in one run.sh command for both items (appends to results.tsv and moves.md), plus cp for win.c.

Note: I must be careful with quoting in the nested bash -c. Let me use single quotes around the bash -c script and double quotes inside for the strings, escaping the tabs as \t (printf interprets them).

Let me write the evidence strings (≤140 chars):
Item 2: "cse: find_best_addr rematerialises D_80126B5E+4 (lui+addiu) for the y loads; the base reg must be opaque (asm) to keep lh 4(s1)"
Item 3: "flow: n is provably 16/20 so the 2nd/3rd 'if (n != 0)' tests fold away; the asm keeps n opaque, 3 tests stay (177 ins)"

Moves lines:
"launder | func_80183098 | WALL cse-const-addr — cse: find_best_addr rematerialises the +4 address for cam->y (lui+addiu) instead of the base reg; only the opaque (asm) base keeps lh 4(s1) (G14)"
"launder | func_80183098 ..." — wait, the func for item 2 is func_80183098 and for item 3 is func_8017D73C.

Let me write these.

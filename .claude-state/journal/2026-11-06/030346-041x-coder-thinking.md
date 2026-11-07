---
ts: 2026-11-06T10:03:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4ZEBhKSuXXdfTMriYoPd
---
Wait, v12's do-while has a goto out of a do-while to a label inside? I wrote `goto done` inside the do-while and `done:` inside the loop body. That's legal (goto to a label within the same function; jumping within the loop). But the `done:` label is inside the do-while body, and `goto done` from inside is fine. However, after `done: ;` the loop condition `while (0)` runs. That changes control flow. And `return rv;` is outside the loop. Hmm, the label is inside the loop so `return rv` after the loop won't execute after goto done (it continues to the while condition then exits loop then return rv). OK.

But this is getting complicated and the variants won't matter. Let me simplify: skip v12/v25 (do-while) to avoid compile issues; or keep and see. The generator will tell.

Actually, I realize the generator has a bug: v11 uses a weird expression. Let me simplify v11. It's `mk([...], <body>)` with a conditional expression `V['v01'].split(...)[1] if False else """..."""` → the else branch is the body. Fine, it works (the `if False` means always the triple-quoted string). OK.

Let me run the generator for func_80182420 and score all 32. Note: sc.sh takes item dir and files. Let me run.

But first, the generated files are in outdir; let me put them in the item dir under a subfolder `var/`. That's fine (< 200MB).

Let me generate and score. sc.sh prints one line per candidate. 32 lines — under 40. OK. But the scorer output per file is long; sc.sh greps one line. Good.

Let me run.

---
ts: 2026-10-22T20:46:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6rchjTJdfD2f9mvhPkbn
---
p2/p4 (base live via `it = base`) still fold. So cse folds regardless of liveness for this constant. Then why doesn't the if branch fold? Because in the if branch, `base` is used in the *loop* (a different BB, in a loop) — cse1 is per-BB: the constant table doesn't cross BBs. In the if branch, the add `p = base + K` is in the same BB as `base = symbol` — so it should fold too... but it doesn't!

Hmm, the if branch: `s32 base = (s32)D_80120194; p = base + 0x6480; if (p != base) { do {...} }`. The add is in the same BB as the assignment. The target keeps `addiu a1,v1,0x6480`. So no fold there even though it's the same BB. So the fold is NOT prevented by liveness.

Then what's different in the else? Maybe nothing about liveness — maybe the fold in mine happens at *expand* (the initial RTL) rather than cse. Let me check: in gen_base's RTL dump, is the else branch already folded at expand? For the if branch, `p = base + 0x6480` where base is a variable → expand emits (plus reg const). For the else, same.

Hmm, but the if branch does NOT fold in mine? Let me check gen_base's actual diff: the diff showed only the else branch (insn 21-24) differing. The if branch matched the target (addiu a1,v1,0x6480). So in mine, the if branch keeps base in v1 and does addiu; the else branch folds.

Difference: in the if branch, `base` is used later (in the loop) so the *register* v1 must hold it; cse can still fold `p = base + K` into a symbol+const address (that's independent). But it didn't. In the else branch it did.

So liveness DOES matter for the fold. In p2/p4, `it = base` after the add makes base live... but cse might delete `it = base` before/within cse? In p4 (`p = base + K; it = base;`), base is used by the copy. Hmm.

Wait, maybe the fold in the else branch isn't a cse fold but a *local-alloc/reload* thing: `p` and `it`... no, the code shape `lui a1,symbol+K` is a folded address.

Let me look at the RTL for the else branch in gen_base to see where the fold happens (expand or cse1). That will tell me which pass to target. Let me dump gen_base and inspect the .rtl and .cse sections around the else branch.

I'll reuse dump1.sh (it's for this item's TU? It uses -Isrc/ov_MAIN_012 which is the includer for func_8012B4B8; for func_8012C750 the includer might be different). Let me check which includer recipe is used: the --try uses recs[0] — for this header, likely also ov_MAIN_012. The score line said `src/shared/ov/func_8012C750.h:func_8012C750` without the recipe name. dump1.sh cpps src/ov_MAIN_012/ov_MAIN_012.c which includes many headers; if func_8012C750.h is included there, fine. It's probably included in the same TU.

Let me run --keep on gen_base and dump with dump1.sh (which hardcodes -Isrc/ov_MAIN_012; if the scratch dir is for a different includer, the cpp might still work since the .c is the scratch copy of the recipe src). Actually dump1.sh takes the scratch dir and uses $S/ov_MAIN_012.c — the scratch .c name depends on the recipe. Let me generalize: use $S/*.c. I'll just pass the file. Quick edit of dump1.sh to glob.

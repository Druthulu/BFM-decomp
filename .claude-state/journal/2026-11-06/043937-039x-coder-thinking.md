---
ts: 2026-11-06T11:39:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MRvEhhmV8w6osM4641Ho
---
So sched1 runs after combine, jump opts have removed constant branches, and basic blocks are recomputed by `schedule_insns`? schedule_insns calls `find_basic_blocks` again? Let me check.

Actually schedule_insns starts with `find_basic_blocks (insns, max_reg_num (), 0)` maybe. If do-while(0) is gone by then, blocks merge.

Hmm, but C0535's effect was attributed to cse1's EBB splitting (cse1 runs before jump opt, so the block boundary existed there and affected cse's copy merging), and then sched1's birth order (LUID) differed because cse didn't merge copies. So the do-while is a *cse* lever, not a sched1 block-splitter.

In our case, the do-while changed LUID order? v1's diff shows massive regalloc change. Not obviously the right tool.

Let me step back and consider the actual residual in v0: 30. Maybe there are other real-C moves that produce the target order.

Idea: what if the stores in the first group are written to `p` as an array of bytes via a loop? No.

Idea: make the adds depend on something in the store group so their priority drops? Priority can't drop below 1.

Hmm, alternatively: make the loads (w_, h_) have priority such that... The issue is the adds get priority 2 and thus schedule before the stores. To stop that, we can make the adds depend on a *store* (anti-dependence cost 0 via ADJUST_COST: anti/output dependence cost = 0 → priority = priority(store)+0-1... wait for anti-dep link, insn_cost returns 0? ADJUST_COST sets COST=0 for anti/output. Then prev_priority = priority(x) + 0 - 1 = 0, which is < max 1. So the add's priority stays 1! 

So if the add has an anti-dependence on a store (i.e., the store writes a register/value that the add reads... anti-dependence means the add writes a register the store reads, forcing order), priority stays 1.

Hmm, but the priority calculation only looks at LOG_LINKS (backward deps) of the insn: dependencies *from* other insns *to* this one. An anti-dependence link in LOG_LINKS means "this insn's output is used by that earlier insn"? Let me think: LOG_LINKS(insn) lists deps where insn depends on earlier insn x. REG_NOTE_KIND nonzero = anti/output dep. So for addu, if it has an anti-dep on a prior store... that would mean the prior store reads a register the addu writes (e.g., the store uses s1 before addu overwrites it). Yes! `sh s1,8(v0)` (store vx from s1... wait vx is a copy a0; but in mine the first store used s1 directly) then `addu s1,s1,t1` writes s1 → anti-dependence between the store (reads s1) and the add (writes s1). That's an anti-dep with cost 0.

But this is after register allocation (sched2)? No — sched1 runs before register allocation, on pseudos. The anti-deps are between pseudos.

Hmm OK. But sched1's ordering in mine had the add before the store, so the anti-dep doesn't force order; it's a scheduling constraint but the scheduler can reorder since the add is a *successor*.

Let me just look at the actual sched1 dump to see priorities and what happened. That requires the .sched dump from cc1 on the TU. Heavy but doable. However, we need a spliced TU. I can get one: run --keep (candidate object) — no, need the .c. Alternatively, use tools/rtu_match.py? The brief says .run/P40/T10/tryinc.py for header items only.

Simplest: construct a scratch TU = src/800.c with the body spliced. I could write a script that does the splice the same way delever_search does (body_span + line_starts), then run cc1_dumps_tu.sh on it with DUMP_ROOT under my item dir. Let me check if a helper exists: tools/cc1_dumps_tu.sh takes a .c file directly. I need the spliced file. Let me write .run/P40/T11/G30/splice.py using the same body_span logic (import from tools.delever_search? It imports lots). Simpler: replicate: find "void func_80015B6C(" line and match braces to the end.

Actually, `delever_search.py --try ... --keep` leaves the scratch source? It prints only candidate object path; the scratch dir contains scratch_src = the TU copy! `scratch_src.write_text(text)` where text = raw[:start] + body + raw[end:]. And the scratch dir is `.run/P36/engine/score/main__func_80015B6C/p3/` — but score_file's finally block removes dirs unless --keep. With --keep it keeps. And the source is 800.c basename in that dir. So I can feed that file to cc1_dumps_tu.sh! But wait, the dir is under .run/P36 (not my shard) — that's the tool's own scratch, fine (I shouldn't write there myself, but the tool does). The brief says cc1 dumps go under my item dir; I'll pass DUMP_ROOT.

But hold on: is the scratch TU complete? It's `raw[:ls[line-1]] + text + raw[ls[end]:]` — yes, the whole TU.

Let me do that: get the dump of v0's TU (--keep), run cc1_dumps_tu.sh with DUMP_ROOT=.../dumps. Read .sched (sched1 dump). Then I can see priorities and blocks.

Disk: 800.c is 18k lines; dumps maybe several MB. Acceptable if deleted after.

Actually wait — is this worth it? Budget 20-30 min per item. We're maybe 10 min in. The function is 120 insns with lots of matching; the residual is only 30 (COUNT). Understanding the sched1 dump may crack it.

Alternatively, empirically try the "dead-reset cse-breaker" C0414 move: a dead store that splits cse. Hmm.

Let me first try a couple of cheap variants:
v2: v0 with a `do{}while(0)` only around the middle group (tag2..pmask store) — see score.
v3: v0 with do-while only around the last two statements.

Also v4: v0 with the first group wrapped in do-while (and the rest plain).

Actually v1 had all three blocks; maybe just the middle matters. But the regalloc damage in v1 came from wrapping the FIRST block (the loop includes p+=8 etc. and the c params get loop refs). Let me try v2 = v0 + do-while around middle group only; v3 = v0 + do-while around last group only.

Let me create them quickly with sed? No — write files. Two Write calls, then two dt.sh calls. Each dt.sh ~few sec.

Actually, I can be smarter: write a variant generator? Keep it simple: Write v2 and v3.

Actually, wait. Before that, let me reconsider the "which real C move" catalog C0505: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse. A `&&`/`||` fold creates branches. Hmm.

What about making the second group conditional on something always true, e.g. `if (p != 0)`? That's fake-ish (p just returned from malloc, could be 0). Hmm, but `if (otp) ...`? The target has no branch.

Let me try the do-while variants first.

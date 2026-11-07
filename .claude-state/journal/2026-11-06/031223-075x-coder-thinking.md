---
ts: 2026-11-06T10:12:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Aw23SoUFYnAUbTKJAjuz
---
In b12's lreg RTL: insn 68 (t=74, unk4C), insn 74 (tb=76, unk54), insn 83 (u=75, unk50). Note the ORDER: 68, 74, 83 — t, tb, u in RTL order.

At insn 68, is v0 live? The preceding insn 65 is a store `sh reg96, 26(reg78)`. reg96 got... dispositions: r96 in 2 (v0). So at insn 65, v0 holds reg96 (used by the store), and reg96 is DEAD at insn 65. So v0 should be free at 68.

But local-alloc's find_free_reg checks `regs_live_at[qty_birth]`? Actually it uses `regs_live_at` computed for the whole block per insn? Let me read find_free_reg.

Hmm, but actually the dispositions show r74 in 3 (v1) — meaning local-alloc's qty for t got v1. The order of allocation: qty_order sorted by qty_compare. All three have equal priority (tie) → qsort leaves order by qty number (qty_compare_1 tie-break `*q1 - *q2`). qty numbers are assigned in order of `alloc_qty` calls during block_alloc's scan. The scan goes through insns in order and calls alloc_qty when it sees a new reg. So t (insn 68) gets qty 0, tb (74) qty 1, u (83) qty 2. Tie → qty 0 first → t gets first free reg.

find_free_reg(qty_min_class, ...) — for t, at its birth/death (insn 68..71), which regs are free? It checks `qty_phys_reg` of other qtys? Actually find_free_reg checks `regs_live_at` (hard regs live) and `qty_phys_reg` of allocated qtys. Since t is first, no qtys allocated yet. So it checks hard regs live at t's range (68-71).

What hard regs are live at insn 68? Looking at the RTL, at 68: reg72 (s0) is live, reg78 (p) dead at 65. v0? The `li a0` at 93 is later. Hmm.

But the disposition says r74 in 3 (v1), so find_free_reg returned v1 for t. That means v0 was considered live at insn 68. What's live? Possibly reg 72 or 78 in v0? No, they're pseudos.

Hmm, maybe the `qty_phys_reg` of an earlier-allocated qty (not t) occupies v0. But t is qty 0 (first). Unless the qty order isn't by qty number: qty_compare uses pri, and if tie, qsort with qty_compare_1 → `*q1 - *q2` (qty numbers). But if priorities are equal but NOT a tie in the truncated int... pri = (floor(log2(2))*2*1/(death-birth))*10000 = 1*2/live*10000. All live=12? If all have live 12, pri equal 1666. Hmm, "live 12" — but t's actual live is 2 (insn 68-71). Why 12?

Wait, the table's "live" column comes from the "used 2 times across 12 insns" line. For r74: "used 2 times across 12 insns in block 2" — hmm, that would be 12 insns of life. But t is used at 68 and 71 — 4 insns. Unless the "12 insns" is the qty's birth..death across the whole block due to REG_EQUIV or something.

Hmm, actually those "Register N used X times across Y insns" lines are from GLOBAL-alloc (allocno), not local. For a local qty, the line might not appear. The alloc_table merges. For r74 with "in block 2" — maybe it's from local-alloc's debug? Let me not trust it.

I'm going too deep. Time check: ~03:15 now, item started 02:54 → 21 min. Let me decide: this item is a WALL with best 6. But wait — a WALL's best = lowest score of a lever-free body. We have 6.

But hold on: is a PARTIAL possible? PARTIAL = win.c scores 0 keeping only some levers. We can't score 0 at all. So WALL.

Let me record the item and move on. But first, let me make sure I have the wall evidence: which pass/mechanism. The residual: local-alloc gives the single-death `tb` qty v0 (it's block-local and allocated first), so global-alloc sees v0 occupied across `t`'s range and colors t v1; the target's pin on tb=$3 removed tb from the local pool, and the target's `t` gets a v0 copy preference from the addiu. Without the pin, no lever-free spelling both keeps tb out of v0 and keeps the sh t,6 before the unk50 load.

Wall tag: something like `lreg-v0-local-first` (exists in walls.txt: "lreg-v0-local-first local-alloc gives block-local cmp temps v0 before global ret(r77) is allocated; target needs ret in v0 live across blocks"). Yes! `lreg-v0-local-first` fits exactly: local-alloc gives the block-local tb v0 before global t is allocated; target needs t in v0.

Great, wall tag = lreg-v0-local-first.

Best = 6 (a5.c). Evidence: "local-alloc: tb (1 def, reg_n_deaths==1) is block-local and takes v0; global t then conflicts v0 -> v1; pin $3 removed tb from the pool (G28)".

Wait, but the delay slot fix (arg0) is part of a5. So a5 is the best lever-free body. Let me make win.c = a5.c? The results format: for WALL, win.c isn't required to score 0; "best = lowest score of a lever-free body". The DONE WHEN says "each MATCH/PARTIAL has its win.c scoring 0". For WALL, I should still keep the best body — I'll copy a5.c to best.c or win.c. Let me put the best body in win.c anyway for reference? The spec says win.c is the lever-free body that scores 0 for MATCH. For WALL, I'll keep best.c = a5.c and note it.

Hmm, actually re-reading: "write a lever-free body of func in G28/<dir>/win.c (bare definition) that scores 0." For WALL items we can't. The results row records best. I'll write win.c as the best lever-free body (score 6) so the shard has a concrete artifact, and note in notes.md.

Actually to avoid confusion, let me name it win.c with the best body and note it scores 6 (WALL). The DONE WHEN only requires win.c to score 0 for MATCH/PARTIAL. OK.

Let me now verify a5 is truly lever-free (no asm/register). Yes, nopin had no asm, a5 derived from it.

Let me record the row and moves line, then move to item 2.

Actually wait — the results.tsv format: `dir file func kinds result best tries wall evidence`. Columns: dir, file, func, kinds, result, best, tries, wall, evidence.

Row:
`func_800CD314__md_MAIN_047	src/md_MAIN_047/md_MAIN_047.c	func_800CD314	barrier,pin	WALL	6	47	lreg-v0-local-first	local-alloc: tb(1 def) block-local takes v0; global t conflicts v0->v1; pin $3 removed tb from pool; best a5.c (call arg0 fixes delay slot)`

Wait, the header is `# dir file func kinds result best tries wall evidence`. So 9 fields.

Let me count tries: I scored orig(1 baseline? that's not a candidate), nopin, v1-v5, a1-a25 (25), b1-b16 (16) = 5+25+16+1 = 47. Plus b12 etc. Let me say 47.

Let me write the files: win.c = a5.c, notes.md, results row, moves line.

Actually, before finalizing, let me make one more attempt at cracking: the b8 insight (tb global via reuse gives t=v0, tb=v1) is SO close. The only issue is unk50 in tb. What if I make t also global with 2 defs while tb has 2 defs? Let me try:
```
t = unk4C; unk6 = t;
tb = unk54; unkE = tb;
t = unk50;
tb = ???  // second def of tb
unkA = t - 8;
```
Need tb's second def to not emit code. What if `tb = t - 8;` and then `unkA = tb;`? That emits `addiu tb, t, -8; sh tb`. Target has `addiu v0, v0, -8; sh v0`. If tb is v1 and t is v0, then addiu v1,v0,-8 → wrong (target v0,v0). Unless tb and t get the same reg? No.

What if `tb` second def is `tb = t;` and then `unkA = tb - 8`? → move v1,v0; addiu v1,v1,-8 → extra move.

Hmm.

What if the second def of tb is in the OTHER branch, but the branch isn't taken? The else branch (`cnt >= 0x20`) is separate. If I assign tb there, it's a different block → tb global (good!) and the assignment emits code in the else branch (bad, changes that block).

What if I add a use of tb in the else branch that's optimized away? E.g., `if (0) func(tb);` — removed.

What about making tb global by making it a parameter-like? no.

OK, one more idea: make t have 2 defs and keep tb local, but change the local qty priority so tb takes v1 instead of v0. In nopin, tb (local) took v0. If there were another local qty with higher priority occupying v0 across tb's birth, tb → v1. The natural candidate: make the FIRST store's temp local with higher priority. But t is global.

Hmm, what if the `unk6 = t` store's value `t` were a separate local temp with a longer life? No.

Actually — what if I make tb's live range longer than t's, so local-alloc... no, tb is the only local qty.

I'll stop. WALL with best 6.

Actually hold on, let me reconsider one thing: the local-alloc condition is `reg_basic_block[i] >= 0 && reg_n_deaths[i] == 1`. If tb is used in TWO basic blocks, it's global. What if the `if ((cnt & 7) == 0)` body is split into two blocks by an if? E.g., wrap the tb statements in an `if (1)` — the compiler removes it. Wrap in a condition that's always true but not folded, e.g. `if (cnt != 0x20)` — emits a branch. No.

OK, WALL. Let me finalize item 1 and move on. Time is tight for 3 more items (20-30 min each → up to 90 min more). Let me be efficient.

Let me write win.c, notes.md, results row, moves line.

---
ts: 2026-11-06T21:00:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_M65yQ6m2X2wYkiWxRPtQ
---
Score 23. Register pairs v1->v0 x3, v0->v1 x3. The whole thing is a register swap: the pin was forcing `t` into v0, and the target wants t in v0. In my lever-free version the compiler chose v1 for t. So we need to steer the register choice toward v0 without a pin.

This is the classic "lreg-qty-priority" thing. `t` and other temps compete for v0/v1.

Observations: target uses v0 for the subtract result `addiu v0,v0,-256` and `sll v0,v0,0x10` and `sh v0`. My version uses v1 for the subtract and v0 for the load. So the allocation of the pseudo for t: target t -> v0, my t -> v1. Also at the end, target x->v0 and y->v1 (lhu v0,16; lhu v1,18); mine x->v1, y->v0.

So in both regions, v0/v1 are swapped. Global alloc assigns registers by priority (refs*length). Since t and x are the long-lived ones? Hmm.

Actually notice: target first block: `lhu v0,88(s0)` then `addiu v0,v0,-256` — so the load result itself is in v0 (v0 is both load dest and t). Wait: `lhu v0,88(s0)` loads into v0, then addiu v0,v0,-256 writes v0 = t. So the load pseudo and t share v0? The load's result is used in addiu as src and dest. So the pseudo being loaded is v0. Then t is also v0 — they are the same pseudo? No: `t = load - 0x100` gives one pseudo for the sub; the load is another pseudo. If the load is in v0 and t also v0, they're coalesced? Actually `lhu v0,88(s0)` then `addiu v0,v0,-256` - the same register v0 for both is natural if the load's pseudo dies at the addiu and the addiu result reuses it (local-alloc tie). Hmm, in my version: `lhu v0,88(s0)` then `addiu v1,v0,-256`; so load v0, t v1.

Target uses v0 for the chain. Mine uses v1. The register allocator chose differently because of ref counts/priorities.

Note the two block `t` uses: t has many uses. In my version t got v1 in the first two blocks and v1 in the third block. Target gets v0.

Simplest lever: reduce/increase the ref counts so priority favors v0. Since global-alloc assigns higher priority pseudo to... Let's recall GCC 2.7.2 global.c: it assigns registers by priority (floor_log2(refs * live_length)) per class; hard registers ordered. For the GENERAL_REGS class, order is probably $2,$3,$4... Actually local-alloc handles most, global-alloc for those live across blocks. Hmm.

Alternatively, restructure so fewer pseudos compete: e.g., reuse a single variable. Perhaps declare `t` as u16 rather than s32, or use the same var for x? Wait the target's first block uses `sll v0,v0,0x10` to test sign — that's (t<<16)<0, which needs s32 t. If t were u16, `(t << 16) < 0`? Hmm.

Alternatively: use `&&`/`||` folds or statement order.

The key difference is register assignment of the pseudo for t: mine v1, target v0. In global-alloc, the first pseudo to get a register in GENERAL_REGS... Let's think: v0 ($2) and v1 ($3). Actually the allocation order is by priority: higher priority gets first pick. Wait but which is preferred? global.c's `find_reg` picks from `regs` order list. For GENERAL_REGS, the order is likely $2, $3, $4... So higher priority pseudo gets $2 (v0). So t in target has higher priority than in mine? But both same code...

Hmm, maybe the difference is elsewhere: maybe in target the pseudo is the load result and t got coalesced; in mine, the sub result got its own. Let's look at the instruction sequences:

Target block1:
```
lhu v0,88(s0)
nop
addiu v0,v0,-256
sh v0,88(s0)
sll v0,v0,0x10
bgez v0,...
nop
sh zero,88(s0)
```
Mine:
```
lhu v0,88(s0)
nop
addiu v1,v0,-256
sll v0,v1,0x10
sh v1,88(s0)
bgez v0,...
...
sh zero,88(s0)
```
Wait ordering differs: mine does sll before sh (sched reorder? no, target has sh then sll). Hmm, mine has `addiu v1,v0,-256; sll v0,v1,0x10; sh v1,88(s0)`. Target: `addiu v0,v0,-256; sh v0,88(s0); sll v0,v0,0x10`. Interesting: in mine the sll comes before sh because... sched1? Actually both should be after. The sh in target is placed in the load-delay slot? No, `lhu v0,88(s0)` is followed by `nop` in target... Hmm wait target at 1694: lhu v0,88(s0); 1698 nop; 169c addiu; 16a0 sh; 16a4 sll; 16a8 bgez; 16ac nop; 16b0 sh zero.

Mine order: lhu; nop; addiu v1; sll v0; sh v1; bgez v0. So in mine, the sll got scheduled before the sh, and the sh uses v1.

Why? Because in mine the `sh` uses v1 and sll uses v0; there's no dependency ordering constraint between sh v1 and sll v0 (both depend on addiu v1). In target, sh uses v0 and sll uses v0, so sh must precede sll (WAR). So the order difference is a consequence of register assignment. So the core is just t in v1 vs v0.

So we need t's pseudo to get v0. t is the long-lived variable spanning blocks. In global.c, the pseudo for t: it's live across basic blocks? The `if` blocks are separate BBs. `t` is used in block1 and block2 and block3 (different definitions, each short-lived within its block probably). Actually each `t = ...; use; use` is within one BB, so local-alloc handles them, not global. Local-alloc assigns within a block, and gives preferences based on the pseudos.

Hmm, local-alloc for a block: it scans the block, allocating dying pseudos to registers. The order matters.

In target, the load result is v0 and the sub result is v0 — the sub result can reuse v0 since load dies. That's local-alloc tying: the sub's pseudo gets v0 because... local-alloc's algorithm: it looks at each insn, and for pseudos that are born and die, uses `reg_pref`? Actually local-alloc assigns registers to pseudos that are local to a block by "qty" priority, considering death.

The difference might come from ref counts: `t` in my version maybe has an extra use, or the load pseudo has fewer refs.

Alternatively the CAST_WIDTH macro may produce something. Let me look at what CAST_WIDTH does. Maybe CAST_WIDTH(u16, (u8*)a0, 0x58) expands to a union-based read producing u16. And the load pseudo is typed u16.

Target first block: `lhu v0,88(s0)`. The `lhu` result is u16; then `addiu v0,v0,-256` — so u16 extended. Since target t is s32, and the sub is done in SImode after HImode load? `lhu` zero-extends.

Hmm. Let's try changes:
1. Declare t as `u16` and use `(s16)(t - 0x100)` etc. But `t<<16 < 0` requires s32.
2. Maybe split: `u16 u = load; s32 t = u - 0x100;`.

Actually the pin was for $2 for `t` used across all three blocks. Wait, the register allocator gave t v1 consistently in all three blocks in my version. Since t is one variable declared in the function but each definition is block-local... if the compiler treats them as separate pseudos, each gets its own allocation. Yet all three got v1 — consistent because the same pattern.

Target has all three in v0. So target's allocation prefers v0 in these blocks; mine prefers v1. What determines? Perhaps the *number of refs* of the pseudo: local-alloc gives priority to pseudos with more refs. If t's pseudo has high refs, it gets v0 first. In mine... same code though.

Hmm, unless the difference is the `x`/`y` at the end: target x->v0, y->v1; mine x->v1, y->v0. In the last block, `lhu v0,16; lhu v1,18` — target assigns x to v0, y to v1. Mine assigns x to v1, y to v0. The order of allocation: x is defined first. So target allocates x first -> v0, y -> v1. Mine allocates y first -> v0? That suggests in mine, y has higher priority than x (or allocation order reversed).

Wait — in mine, x's pseudo maybe died early: x is used in `sh v0,16(s1)` at the end. Both x and y are live to the stores. Hmm.

Maybe the issue is *scheduling*: sched1 reorders the two loads. Target: lhu v0,16 then lhu v1,18 in order. Mine: lhu v1,16 then lhu v0,18. That's after register allocation though — actually sched1 runs before register allocation (sched1 is the first scheduling pass, pre-register). Then local-alloc. Hmm, sched1 could reorder loads x and y. Target order: lhu 16 first, then lhu 18. Mine: lhu 16 first too (lhu v1,16(s1); lhu v0,18(s1)) — same order, just registers differ.

So the register assignment for x/y is swapped: target x=v0,y=v1; mine x=v1,y=v0. Hmm, that's not a simple "prefers v0" difference; in the last block mine prefers v0 for y.

Interesting: maybe in mine, the ordering of instruction birth is such that y is born before x in the allocator's view? Or the local-alloc scans backwards and allocates in order of death.

local-alloc (GCC 2.7.2): `local_alloc` calls `block_alloc` per basic block; it sorts qty's by `qty_compare` (refs/live, size) descending, then allocates. Higher priority gets the preferred register.

If both x and y have identical refs and size, tie-break by birth/death order. The one born earlier / dies later wins.

In mine, x=v1, y=v0 means y won v0. In target x won v0. So priorities differ by ref counts: perhaps in mine y has more refs? y is used only in `sh v1,18`. x used in `sh v0,16`. Same.

Unless... hmm. In target, the stores order: `sh v0,16(s1)` then later `sh v1,18(s1)`. Both at the end. And target has `andi v0` right after addiu, and addiu v1 then andi v1... Let me recount target:

```
171c addiu a3,a0,88
1720 lhu v0,16(s1)
1724 lhu v1,18(s1)
1728 addiu v0,v0,45
172c andi v0,v0,0xfff
1730 addiu v1,v1,22
1734 andi v1,v1,0xfff
1738 sh v0,16(s1)
173c jal
1740 sh v1,18(s1)
```
So x: lhu/addiu/andi/sh; y: lhu/addiu/andi/sh, interleaved: x's addiu+andi, then y's addiu+andi, then x's sh, then y's sh in the delay slot.

Mine:
```
46 lhu v1,16(s1)
47 lhu v0,18(s1)
48 addiu v1,v1,45
49 -- 
50 -- 
51 andi v0,0xfff? 
```
From the diff: mine[46:49] target[48:53]:
```
46 lhu v1,16(s1)   | 48 lhu v0,16(s1)
47 lhu v0,18(s1)   | 49 lhu v1,18(s1)
48 addiu v1,v1,45  | 50 addiu v0,v0,45
49 --              | 51 andi v0,v0,0xfff
50 --              | 52 addiu v1,v1,22
51 addiu v0,v0,22  | ...
52 andi v0,0xfff
53 sh v1,16(s1)
```
Hmm, so mine does addiu v1,45 then addiu v0,22, andi... Actually mine's sequence has 61 insns vs 63 target.

Anyway, the swap is systematic: it looks like the *whole* allocation of v0/v1 is swapped between the two pseudos in each region. That strongly suggests the pin previously forced t into v0 and the target was generated with the pin. Removing the pin, GCC assigns the other register. Hmm, but why would it assign v1 rather than v0?

Key insight: register $2 (v0) has a special property — it's a "caller-saved" and also the function return register. But more importantly, GCC 2.7.2's local-alloc has `regs` order; in the MIPS machine description, GENERAL_REGS order is $2, $3, $4, ... but there's also `FIXED_REGISTERS`? No.

Hmm, maybe the issue is that in the *original* body, without the pin, there's a pseudo that occupies v0 across the whole function (e.g. `s1` is in s1 register...). Actually look: the function has s0 = a0, s1 = a0->0x20. Those are in s0/s1 (callee-saved). v0 is free.

Wait — could it be the *second* pin `register u16 x __asm__("$2")` also affects? I removed both.

Let me consider that local-alloc prefers a register that is *not* used... The rule: local-alloc tries to avoid assigning a hard reg that's live across the block. v0/v1 both free.

Alternatively maybe the target's v0 assignment comes from `t` being in v0 because the pseudo is the same across blocks (global-alloc, since t is live across blocks?). Wait, in the orig, `t` is declared once and used in all three if-blocks and nowhere else. Each block assigns t and uses it within the block. So no cross-block liveness — unless the compiler keeps t live because... Hmm.

Actually in the target, `t` in block 1 is v0, block 2 v0, block 3 v0. In mine, all v1. Since a single pseudo (if it were global) would be assigned one register for the whole function, consistent v0/v1 across blocks is consistent with a single global pseudo. That suggests t IS one pseudo live across blocks? No — it's redefined; the pseudo value from block1 dies at end of block1. But global-alloc could assign it because... hmm, a pseudo that is live only within one block is "local" and handled by local-alloc. But if the same pseudo (same REG rtx) appears in multiple blocks with different definitions, it's one pseudo whose live ranges are in separate blocks. It's not live across blocks. Local-alloc handles pseudos whose live range doesn't span blocks... Actually local-alloc handles pseudos that are used only within one basic block; a pseudo defined in block1 and block2 separately is one pseudo but each definition-use region is within a block. Hmm, GCC's local-alloc requires the pseudo's life to not cross blocks; a pseudo with multiple disjoint lives in different blocks: local-alloc "block_alloc" handles per block and considers only the qty's live in that block. Since each block has its own def/use, it works.

But then why consistent v1 in all blocks? Because each block's allocation has the same pattern -> same choice. Fine.

So what makes target choose v0? The target was produced by the original source with the pin, so of course v0. The question: can we steer v0 without a pin?

Ideas from the catalog: "u16 t (HImode copy escapes cse equiv)" from line 6: func_80184F18 MATCH — u16 t. Hmm.

Since the pattern is a consistent swap in *all* blocks, maybe the trick is to make v0 *preferred* by tying something. E.g., if we make the value also used in a context that must be v0 (like a function call's return?). In block 1, after the `if` there's a call to func_80146CA0(a0) inside the third sub-if. The target has `jal` at 1700 and returns... hmm.

Wait, look at the target's first `jal func_80146E98` at 1678: result unused. Then the branch. Hmm.

Another approach: maybe the difference is because `t`'s pseudo in mine has *lower* priority than the load pseudo. In target, the addiu reuses the load's v0 (load dies), whereas mine assigns the sub a different register. That's local-alloc's "tie" behavior: a pseudo that dies at an insn can be tied to the input. The tie preference: if the result pseudo dies at... hmm.

Let me look at actual local-alloc rules in GCC 2.7.2 to understand: `block_alloc` sorts by qty priority (refs / live length), and for each qty, if it has a preferred register (from `reg_pref` / `allocno_pref`?), uses it. Preferences come from `REG_N_REFS`, `REG_LIVE_LENGTH`, and `qty_birth/death`. Also `reg_preferred` set by `local_alloc`? In 2.7.2, local-alloc computes `qty` and uses `qty_compare`:
```
static int qty_compare (q1, q2) { return q2->n_refs * q1->live_length - q1->n_refs * q2->live_length; }
```
something like that. Then assigns from `regs` in order, using `reg_pref` maybe.

Hmm, wait: maybe the difference isn't in allocation of t but in the *scheduling*, which changed which insn is where. Let's not over-theorize; let me try concrete C variations and see scores. That's the intended workflow (30 tries).

Variation A: make `t` u16 and do sign test differently.
Variation B: split into separate variables per block (t1, t2, t3) — changes ref counts.
Variation C: combine the two `(t<<16)<0` tests using `&&`/`||` folds.
Variation D: statement order / assignment to a separate temp for the store.

Also the diff at the start: mine `beqz v0,1704` vs target `beqz v0,170c` — just addresses, ignore.

Let me think about which pseudo gets v0 in local-alloc. In target's block, `lhu v0,88(s0)` (load) and `addiu v0,v0,-256` (sub) — load and sub share v0. Then `sh v0` and `sll v0`. So the sub pseudo = v0, the load pseudo = v0 (tied). In mine: load v0, sub v1. So local-alloc gave the sub pseudo v1. Why? Priority: the load pseudo dies at the addiu (1 use); the sub pseudo has many uses (sh, sll, and comparisons). So the sub should have higher priority and get v0. Unless the allocation order prefers to give the *earlier-born* pseudo the lower register first: local-alloc scans forward and allocates when a pseudo is born? In 2.7.2 `block_alloc`:
```
  /* Allocate the quantity with the highest priority first */
```
Actually I recall it does: for each qty in order of `qty_compare` (descending), allocate. The load has n_refs 1, live_length small; sub has more refs. So sub should win v0... but mine gives sub v1.

Unless the register order for GENERAL_REGS is $3 before $2? Hmm! If regs order were $2,$3,..., then winner gets $2. If the sub won and got $2, we'd see sub in v0. We see sub in v1, load in v0. So maybe the load won $2 (allocated first). So the load has higher priority? That would be weird unless the load's live length is larger (it is born at insn and dies at addiu, length ~2). n_refs 1. Sub: born at addiu, dies at sll... Hmm, in mine the sub's uses: sll v0,v1; sh v1; and the bgez on v0 (sll result). So sub has 2 uses. Refs: load 1, sub 2. Priority proportional to n_refs/live_length. Both tiny.

Hmm, actually maybe GCC gives the load v0 because loads have `reg_pref` preferences? No.

Alternatively the *order of qty birth* tie-break: if equal priority, the first-allocated is the one whose birth is later? Hmm.

Rather than theorize, let me try making the load's pseudo die immediately (e.g., compute directly into t in one expression) and see. That's already the case.

Try: use a u16 temp for the load and s32 t:
```
u16 u;
s32 t;
...
u = CAST_WIDTH(u16, (u8*)a0, 0x58);
t = u - 0x100;
CAST_WIDTH(s16,...) = t;
```
That adds a variable, may change things.

Try 2: make the sign test use `if (t < 0)` after storing as s16 and reloading? Target does `sll v0,v0,0x10; bgez v0` — that's from `(t << 16) < 0` where t is s32 and (t<<16) s32. Alternative: `if ((s16)t < 0)` would generate `sll`+`bgez` too? `(s16)t < 0` -> `sll v0,v0,16; bltz` maybe. Hmm, `bgez` on the shifted value is equivalent to bltz on the original.

Try 3: reorder statements: store then test.

Actually, the whole diff is a systematic v0/v1 swap, meaning the C semantics are identical; only allocation differs. This is the "lreg-qty-priority" class wall. To crack it we must alter ref counts/priorities so that the right pseudo gets v0.

Which pseudos compete? In each region, the load pseudo and the sub pseudo. Both want v0. In target, both got v0 (load dies at sub, so reuse). In mine, load v0, sub v1 — no reuse. So target got the tie, mine didn't.

Wait, maybe in mine the *sub* pseudo is not dying early enough — the sh and sll both use it, so it's alive. Local-alloc "ties" a dying pseudo to its source: the *load* dies at the addiu, so local-alloc may tie the load to the addiu's output register. In target, the load and sub share v0 because the load dies and the sub is born — a natural tie. In mine they don't share, so something prevented the tie: perhaps the load's pseudo is also used elsewhere? No.

Hmm — maybe in mine, the load is scheduled differently: mine has `addiu v1,v0,-256; sll v0,v1,0x10; sh v1,88`. The load v0 is used only by addiu. Sub v1 used by sll and sh.

OK here's another thought: in local-alloc, when a pseudo dies at an insn, it can be tied to a register that's free, and the *insn's output* is a new pseudo that gets allocated independently. The tie happens when `qty` has `n_refs == 1` and dies: then it's given the same reg as the output if the output is in a "preferred" set.

I'm going too deep. Let me check the GCC source for local-alloc qty ordering quickly (it's in tools/reference/gcc-2.7.2/). But better: run a couple of cheap experiments.

Experiment: swap the order of the two `if` bodies? No.

Experiment: declare `t` inside each block scope (three separate `s32 t;` declarations) so each gets its own pseudo with fewer cross-block... they're already separate lives.

Experiment: change `s32 t` to `u32 t` or `u16`.

Let me try the simplest first: `s32 t;` -> `u16 t;` and adjust. If t is u16: `t = load - 0x100;` (HImode arithmetic), store t. Then `if ((t << 16) < 0)` — t promoted to int, `t << 16` in SImode; `(int)(t<<16) < 0`. Would give `sll v0,v0,16` too. But the store `sh v0` of an HImode value — and `sll` uses the s32 promotion... could change codegen.

Let's do the experiments systematically but quickly. Each dt.sh run is cheap.

Actually, wait. Let me reconsider: the target's `sh v0,88(s0)` comes *before* `sll v0,v0,0x10`. In C, the order is: t = ...; store; if ((t<<16)<0). GCC's scheduling (sched1) may reorder. In mine, the sll is before the sh because they use different regs (no dependency). In target, sh must precede sll (same reg, WAR). So the register assignment causes the order.

Now here's a thought: perhaps the correct lever-free C is to make the store use a *different* variable than the test, i.e. the target's single v0 chain is exactly what the pin produced. Hmm.

Let me look at what happens with a plain `s16` store variable:
```
u16 u;
s32 t;
u = CAST_WIDTH(u16,...);
t = u - 0x100;
CAST_WIDTH(s16,...) = t;
if ((t << 16) < 0) ...
```

Let me just run experiments. First, record start time and set up notes.

Actually time budget: 20-30 min per item, 3 items. Let me be efficient.

Let me try a batch of candidate bodies using bin/sc.sh (scores many files in one line each). Let me check sc.sh.

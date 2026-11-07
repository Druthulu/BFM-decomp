---
ts: 2026-11-06T09:59:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_H0Yy6TNXoJ3yUCXFdD16
---
cc1_dumps_tu.sh takes a TU file. I can create a spliced TU: copy the src TU with the function body replaced. That's a lot of work (174KB file). But maybe there's a helper in the item dir? The item dirs have only fn/kinds/tu. Hmm.

Alternative: use the retriever to answer "what does local-alloc do..." Not needed.

Let me step back and prioritize. The brief says 4 items, 20-30 min each. The clones are likely walls (expand-void-return). But before declaring, I should do ≥30 scored tries per item. That's expensive. But maybe a real-C move can crack them.

Let me think about the clones differently. What if we *keep* the keepalive and change the body so that rv is allocated v0? The keepalive `__asm__("" :: "r"(rv))` is a kind we may keep for PARTIAL. To get rv into v0, we need the allocation to prefer v0. 

In b3, why v1? Because rv's live range overlaps v0's uses. Let's look: In the block with `rv = -1; goto done`, rv's live range starts at the `li`. The `slt v0,...` for that branch's condition precedes. But local-alloc's block-level conflict: within the same basic block, if v0 is used anywhere in the block while rv is live... The block containing `rv=-1` is just `li v1,-1` + `j`. But rv is live from there to the function end (across blocks). local-alloc does global allocation per pseudo using live ranges across blocks (it uses the CFG). rv is live across many blocks where v0 is used (e.g., the d<16 block uses slti v0). Hence conflict → v1.

But the target has rv=v0 AND v0 used as scratch in the d<16 block! How? Because in the target, rv is the return value — hard reg $2 — and the compiler allows hard reg $2 to be used as scratch too (v0 is a normal allocatable reg; the return value in v0 is defined at the end, and the scratch uses of v0 happen before the definition). Live range analysis: rv is *not* live at the scratch uses in the target, because on the path through the d<16 block, rv is defined at the end (li v0,31 or sll v0). Wait, rv=-1 is defined in a different path. The pseudo rv (one pseudo, multiple definitions) — in SSA-less gcc, one pseudo can have multiple defs, and its live range is computed as the union? For local-alloc, a pseudo's live range is computed by flow; with multiple defs, the live range is from the first def that reaches... Actually if a pseudo has defs in several blocks and is used only at the end (the keepalive), its live range includes all paths from each def to the use. In the d<16 path, the def is `rv=d*2` then goto done; the value reaches the keepalive. So rv is live from that def. v0 is used for the slti AFTER the def? No: `d=x-a0; if (d<16) { rv=d*2; goto done; }` — the slti v0,a0,16 happens BEFORE rv=d*2. So v0's use is before rv's def. In the final block, `rv=31` then keepalive — no v0 use. So rv's live range shouldn't conflict with v0. Hmm, but flow may compute a single live range for the pseudo from its first def to its last use, spanning blocks where v0 is live. That's the issue: gcc's register allocation is not SSA; a pseudo with multiple defs gets one live range from the earliest def to the last use. Since rv is defined early (in the `a0>=x` block) and used at the end, its live range spans the whole middle, conflicting with v0.

The target's rv is $2 (hard reg), so it can be assigned regardless of conflicts (hard regs are fixed; conflicts with other pseudos mean those others get other regs). But in the target, the middle scratch uses ARE v0. That contradicts: if rv=$2 is live across the middle, the scratch pseudos can't use $2... unless rv's live range in the target is NOT spanning the middle because the compiler knew rv is dead on those paths. Hmm, but the same source structure.

Oh! In the target, the function RETURNS rv. The return is at the end. But the middle blocks don't define rv, so rv isn't live there in a dataflow sense — flow computes live ranges as: a pseudo is live at a point if some def reaches it and it's used later. With multiple defs, at a point between defs, rv is live if a def reaches and there's a use. In the middle blocks (d<16), the path from the `rv=-1` def doesn't reach (the def block jumps to done, not into the middle). So at the middle, rv is not live unless a def reaches from a predecessor. The middle block's predecessor is the earlier code; rv hasn't been defined on that path yet. So rv is NOT live in the middle. Good — so local-alloc should also see no conflict, and give v0.

But b3 got v1. Why? Maybe because v1 was already chosen due to a different reason: the keepalive is at the very end after the label; rv's uses/defs. Hmm, maybe v0 is not allocatable for rv because v0 is the return-value register and gcc reserves it? In gcc 2.7.2 MIPS, $2 is a general reg used for return values; for non-returning functions, local-alloc can allocate it. In b3, the comparison results use v0, so maybe rv was allocated v1 because v0 was preferred by the comparison pseudos (they have higher priority?).

Let me get the actual full asm of b3. I can do this by making a spliced TU copy under my shard and running cc1_dumps_tu.sh. But splicing a 174KB TU: I can do it with a Python script (allowed, under .run). The TU text with the function definition replaced by b3. Then cc1_dumps_tu.sh on that file (it accepts a .c file). But it writes dumps to ${DUMP_ROOT:-.run/P32/t4e}/dumps_<tag> — I can set DUMP_ROOT to my shard dir. Good.

Actually, the score tool already compiles the spliced TU. The dump would show the .lreg/.greg. This is useful.

But wait — is this worth it? Let me reconsider the whole task. There are 4 items, all void-returning with pins/keepalives. The prior shards found WALL expand-void-return for many. The likely outcome: all 4 WALL. But the brief wants real effort. Let me try the most promising: item 4 (func_8017D730) is not a value-return; its v0 is scratch. Let me test lever-free there. That one might crack.

Let me first quickly test item 4 lever-free and item clones' variants. Time management: 20-30 min per item.

Item 4: remove `register s32 v0 __asm__("$2")` → `s32 v0;`; remove the keepalive asm on cmp and the tmp3 pin/keepalive. But the second branch's cmp/tmp3 were dead levers; remove them. Let me write lever-free body and score.

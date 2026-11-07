---
ts: 2026-11-06T14:09:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZoMXEF4sp3rmSyuqZQji
---
So local-alloc priority uses `floor_log2(n_refs)*n_refs*size`, and shorter-lived quantities get higher priority (qty_compare_1). Since both i and dst have similar lives, n_refs matters.

Now, the final difference is exactly a swap of i and dst between t2 and t3. Higher priority -> allocated first -> gets... which register? The allocation order: qsort puts highest priority first, and then allocates. The first allocated gets the lowest available register among the preferred set. For caller-saved temps, the preferred order is $2,$3,...? Actually for a pseudo with no preference, `find_free_reg` scans from the beginning of the allocatable set. In the MIPS machine description, `ALL_REGS`/`GENERAL_REGS` order. Typically $2 (v0), $3 (v1), $4..$7 (a0-a3), $8-$15 (t0-t7)... But $2,$3 are used for other things.

Anyway: I need i to have higher priority than dst so i gets the lower-numbered free reg ($10/t2) and dst gets $11/t3.

Wait, but mine currently gives i t3 and dst t2. So dst has higher priority than i in my version. Target: i gets t2 (higher priority). The keepalive on i added refs to i, raising i's priority above dst. That's the "$t2 race" — the race between i and dst for $t2/$t3.

So: I need to add real references to i, or reduce references to dst, to flip the priority order.

Current refs: 
- i: initialized `i = 0`, used in `i++`, `i < n`. That's 3 refs.
- dst: `dst = src + n`, `*dst = out`, `dst++`. That's 3 refs.

Hmm both 3 refs. The priority formula also includes size (both SImode) and lifetime. Shorter-lived gets priority. i's life: from `i=0` before the if to `slt` at loop end. dst's life: from `dst = src+n` to `dst++` at loop end. Roughly similar.

Wait — the asm added +3 refs to i (comment says "+3 refs on i (depth-3)"). With refs 3+3=6 for i vs 3 for dst, floor_log2(6)*6 = 2*6=12 vs floor_log2(3)*3=1*3=3. So i wins clearly. But the comment says "+3 refs" - the asm at loop depth 2? reg_n_refs += loop_depth, and loop_depth inside the do-while is 2? Then one asm ref adds loop_depth=2? Hmm. Actually the comment "+3 refs (depth-3)" might mean it's inside depth 3? There's the outer `if (arg0 != 0)` no loop, `while` depth1, `do` depth2. Hmm.

Actually, wait. Let me reconsider: maybe the `__asm__` reference contributes REG_N_REFS by `loop_depth` at the point. The src asm is outside the do-while (depth 1 in the while loop) so +2? Hmm "depth-2". And i asm is inside do-while (depth 2) so +3? That doesn't map cleanly.

Doesn't matter. The practical goal: make i's local-alloc priority exceed dst's using real C.

Options to raise i's refs:
1. Use i in more real expressions. E.g., compute `src + i`? No, changes codegen.
2. Use `i` as the loop condition differently.
3. Reorder: make i's def earlier / lifetime different.

Alternatively lower dst's priority: reduce dst refs from 3 to 2 by folding `dst++` into `*dst++ = out`? That's still 2 refs to dst (one in *dst++? Actually `*dst++ = out` is: dst is read and written = 1 ref? In RTL, `*dst++ = out` becomes `sh out,0(dst); dst=dst+2`? It'd be one pseudo use plus one def... Let me think: `dst++` as an expression is a read+write; `*dst++` uses dst once and sets it once.

Hmm, ref counts in gcc: each pseudo appearance in RTL. `dst = src + n` is 1 use + 1 def? REG_N_REFS counts... Let me check flow.c: `REG_N_REFS (regno) += loop_depth;` for each reg occurrence in each insn. A set counts as 1? Let's look.

Actually the simplest empirical approach: try a bunch of real-C restructurings and score them.

Idea A: Make i a loop condition variable used differently: `while (i < n)` at top instead of do-while. But loop shape matters for the target.

Idea B: Use `i` in the `dst` computation: `dst = src + n;` could be `dst = src + n;`... no.

Idea C: Change the loop to count down: `for (...)`.

Hmm. Let me think about what real C naturally adds a ref to i without changing generated code. The code for `i++` then `slt` — if instead we write `i += 1` same. If we write the condition as `i != n`? changes slt to bne.

What about `dst = src + n;` -> we could instead index: `dst[i] = out; i++;`? That would use i in the store addressing: `sh out, 0(dst+i*2)`, changing codegen.

Alternative: reduce dst refs. Currently `dst = src + n; ... *dst = out; dst++;` = refs: def at assignment, use at store, use+def at increment. If we write `*dst++ = out;` combined, the increment and store merge? In RTL, `*dst++ = out` = `(set (mem (dst)) out)` + `(set dst (plus dst 2))`. Still 2 refs (one use in mem, one use+def in plus). Hmm.

What about writing `dst = dst + 1;`? same.

What about moving the store to use src? No.

Let me look at the actual reg_n_refs in the dump. The .lreg or .greg dump might show REG_N_REFS. Let me check .lreg for the pseudos. Let me look at local-alloc dump (.lreg = -dl). Let me find the loop portion.

Actually maybe easier: look at .sched dump priorities? sched1 uses its own priority (INSN_PRIORITY). But the issue here is local-alloc (which reg). Hmm, but actually maybe it IS sched1: the register swap could come from sched1 reordering? No — the instructions are the same, just registers differ. That's regalloc.

Wait, score says "REG-caller" category — register allocation of caller-saved regs. Yes local-alloc.

Let me look at the local-alloc dump to see the quantity ordering and n_refs for i and dst.

Let me grep the .lreg dump for the region. Find func_8013D53C in .lreg.

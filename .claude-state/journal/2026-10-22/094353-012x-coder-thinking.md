---
ts: 2026-10-22T15:43:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OEbNfWNKGzYiboetHb0W
---
There's `--explain TU FN` which reads one body's residual. That's the full residual — useful. Let me use --explain on the current src (which scores 0? then no residual). Hmm, --explain reads "one body's residual (no writes)". Maybe it reads the current body from the TU.

More useful: get the target disassembly. The build has the target object. Let me find it: `find build -name '*8012B4B8*'`. But the instruction says never ls/find outside project — build is inside project. Fine.

Let me find the target object and disassemble with mips-linux-gnu-objdump? The tools path is reachable through bin/sc.sh... but I can use tools/cc1_dumps_tu.sh for dumps. Hmm.

Actually the diff output gives me target instruction lines as they align; the tail cut at 120 lines. Let me just request tail 400 and head more. But diff output may be long. Better: use `--explain` maybe prints full residual including counts.

Alternatively, the simplest: my goal is score 0. I have a strong idea (struct copy). Let me test it right away — cheap (one dt.sh call).

Candidate: replace the 8 load/store lines with:
```
        *(Mat32 *)m = D_800AE620;
```
But `m` is `int m[8]`, Mat32 presumably 32 bytes. Let me check Mat32 definition. grep in include/.

Let me write candidate and score. Also try variants: `*(Mat32 *)&m[0] = D_800AE620;`, `m[0] = ...` with a pointer copy loop? Let's first test the struct copy.

Note: does the pin on src matter? I can drop the src pin if unused (removing a pin is fine; pins are a lever but removing is not adding). Actually if `src` is unused, declaring `register int *src __asm__("$5")` still reserves $5 maybe. Better to drop the src declaration entirely for the struct copy. But careful: the constraint says "levers of other kinds the def already had may stay, never added". Dropping is fine and may be necessary.

But wait: the pin $5 might be what makes the target use a1? No — with the pin, the compiler used $5 (a0) maybe. Target uses a1. Let me check what the with-launder version generates: it scores 0, so it's identical to target — meaning with the launder the base is in a1? Hmm, the pin says $5. But target's base is a1. Wait the diff for w1 (no launder) shows mine using v0/v1/a0 (no register), target a1. With the launder + pin $5, score 0 means mine uses... $5 is a1! In MIPS o32 ABI, $4=a0, $5=a1. Yes! $5 = a1. Right.

So the launder + pin $5 gives the target exactly. Without the launder, cse folds the constant into each load.

So the crack: get a real C construct that makes the compiler keep &D_800AE620 in a1 (or any reg) with 8 offset loads. Note the target uses a1, which is the arg register freed after `self = param_1`. Without the pin, the allocator could pick a1 naturally? Maybe. If we force the address into a register by making it multi-use and non-foldable, cse still folds constant addresses (find_best_addr). The classic cse-const-addr wall.

But a struct copy is a block move, not 8 independent lvalue loads; expand_block_move uses `gen_rtx_MEM` with offsets from one base register — cse doesn't rematerialize inside block moves. So very likely crack.

Let me check Mat32 and try.

Actually the group sizes: target lw v0,0; lw v1,4; lw a0,8; then (store) lw v0,12; lw v1,16; lw a0,20; then lw v0,24; lw v1,28. Hmm 3+3+2 pattern with stores interleaved. That's typical of expand_block_move with MOVE_RATIO or the scheduler. Actually expand_block_move for 32 bytes on MIPS would emit lw/sw pairs: lw v0,0(a1); sw v0,0(sp); lw v0,4(a1); sw v0,4(sp)... But the scheduler could reorder loads ahead. The observed pattern of 3 loads then stores looks like scheduler reordering of lw/sw pairs. So a struct copy is plausible.

Let me test.

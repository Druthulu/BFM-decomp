---
ts: 2026-10-22T15:42:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HnFmVbwBTxSmdaqYNwga
---
Interesting. The `gen_x1_copy2.c` etc. still have `src = (int *)&D_800AE620;` with `src` pinned to $5. Wait — the pin is a lever of kind `pin`, not the row kind (launder). But the constraint says "no new lever of any kind" and "levers of other kinds the def already had (pins under other causes) may stay, never added". The pin $5 exists in the def. So keeping it is allowed. And with the pin, src = &D_800AE620 gets $5 → the address held in $5. Score 20 though! Wait, gen_x1_copy2 keeps the pin $5 and src = (int*)&D_800AE620, yet scores 20. Hmm, but the target uses a1... with the launder, `src` is a hard-reg $5 pseudo whose assignment `src = &D_800AE620` is laundered so the compiler can't fold it. Without the launder, cse folds `src`'s value into the uses — the pin doesn't help because the pseudo is replaced by the constant.

So score 20: 90 ins, extra 6 lui/lw pairs? Let's count: 8 loads → target uses 1 lui+addiu then 8 lw; mine uses 8 lui+8 lw = 16 ins vs 9 → 7 extra... but 6 extra total (90-84). Anyway.

Target address is `a1` (arg reg), which is dead after param_1 copied to self. So the target uses a1 as a scratch base register. Mine (with launder) presumably used $5.

The wall tag `cse-const-addr` matches exactly.

Now, the crack strategy: make `src` a value that is NOT a pure constant so cse can't rematerialize, but that still lets the compiler compute the address once into a register. The known MATCH moves: "p = *abase; p += 0x2D (self-reassign stales cse (plus p K) equiv, bump chain stays addiu)" — that's for a different shape. Also "pointer reuse: a1 = (u8 *)link; ... keeps the store base in the link reg".

Here we want: one register holds &D_800AE620, then 8 `lw` with offsets 0..28. The target: lui a1,0; addiu a1,a1,0; lw v0,0(a1)... 

Options in real C:
1. Use a struct copy: `Mat32 tmp = D_800AE620; m = tmp;`? Mat32 is likely 8 ints (32 bytes). `*(Mat32 *)m = D_800AE620;` — that would be a struct assignment from a global. That might generate exactly lui/addiu then 8 lw/st? But we need t0..t2 temps to be loaded in groups and stored into m — target sequence: lw v0,0(a1); lw v1,4(a1); lw a0,8(a1); then presumably sw to m... Actually the target's first 8 instructions after the base: lw v0,0(a1); lw v1,4(a1); lw a0,8(a1); then likely sw v0, sp..; sw v1..; sw a0..; then lw v0,12(a1)... So it's a copy of 32 bytes from D_800AE620 to stack m, done in groups of 3,2,3 (register pressure). A struct assignment `*(Mat32*)m = D_800AE620;` might do exactly this! Or `m` is int[8], so `*(Mat32 *)m = D_800AE620;` requires Mat32 type. orig.c already uses `*(Mat32 *)(obj + 0x34) = *(Mat32 *)m;` so Mat32 is known.

Let me try: replace the 8 load/store lines with `*(Mat32 *)m = D_800AE620;`. That's a struct copy from a global — the compiler must load all 8 words and store them. Address likely kept in a register (a1) because it's a block copy. That's a real C move (struct copy) and very promising. But does it change instruction scheduling? Let's test.

But careful: does the target really copy through a register in groups? The diff shows target: lui a1; addiu a1; lw v0,0(a1); lw v1,4(a1); lw a0,8(a1); then (probably sw to m) and lw v0,12(a1)... Actually if the target were a struct copy, GCC's expand_block_move would emit lw/sw pairs with offsets from a1, likely exactly. But the observed target has lw 0/4/8 into v0,v1,a0 — 3 loads before stores, which is not a simple pairwise block move; that's the scheduler interleaving? Hmm, the target shows lw v0,0(a1); lw v1,4(a1); lw a0,8(a1); then next lines probably sw... Let me look at the full target disassembly. Where's the target file? delever_search compares with build/. Let me find the target disasm. Maybe in .run/P40/T11/G16/dumps or the item dir `target.txt` (only item 4 has target.txt).

Let me check what's in the item's tu: src/shared/ov/func_8012B4B8.h — the TU is the header itself? That's odd. delever_search --try takes a TU path and function name. The TU here is the header path. It probably finds includers. Hmm, the score line says "src/shared/ov/func_8012B4B8.h:func_8012B4B8: score 0". And the includer recipe print. So delever_search knows how to build a TU from the header's includers.

Let me look at tools/delever_search.py briefly to understand --try and whether there's a way to get target disasm. Also check bin/dump.py in shard dir (probably prior coder's helper).

Actually dt.sh gives a diff. I can get the full target listing by looking at the diff with a big tail; the diff prints mine and target instructions. Let me get the whole diff for w1 (tail 200).

Let me also think about item counts. Four items, each a header with N includers (31/19/42/91 presumably = number of includers). For a MATCH I must check every includer. sweep.sh does that. 91 includers × ~1.5s = 2-3 min per candidate. That's costly but only for final verification (and if a candidate scores 0 on the first TU, maybe it's generally good).

Wait, actually the target function is a single body shared across all includers (one source instantiated at each site). The target code is the same for all? Presumably each member's address differs but the body shape is identical... Actually the header defines the function and each includer instantiates it at its own site; the "target" for each includer is the same function from the ROM? Hmm, the shared-body dedup: same bytes at multiple overlay addresses. The body compiled in each includer's TU might differ slightly due to context. The score-0 requirement on every includer is a robustness check.

Let me first understand the scale: for item 1, how many includers? sweep.sh defaults kmax=141. The list.tsv 4th column "31" may be lines. Let me count lines of the header: 35 lines. Hmm 31? Let me check wc -l for each header.

Let me do a batch of inspection.

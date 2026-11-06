---
ts: 2026-10-22T15:41:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FFAtdWMc2Vi1PDJKyT1V
---
I see: the prior coder (or prep) has done a lot. But wait — `variants.py` contains code referencing D_80120194, 0x658C which is a different function (8012C2D0 maybe). It's a generic script but written for a specific item? Actually it's in the G16 root, likely written for item 2. Hmm.

Actually, wait. The instruction says these dirs were pre-populated? The gen_* files for item 1 are all from 07:04 today; the shard dir was created 07:04. So an earlier coder run (maybe the same task, earlier attempt that was killed) generated them. My task starts 09:38. There's no results.tsv row. I should use their work as a starting point but verify.

Important: the brief says "Budget 20-30 min wall per item" and "a WALL needs ≥ 20 min and ≥ 30 scored tries". The prior work already counts as tries? Not mine. But it's evidence. I should be efficient: reuse the existing candidates, and try to crack with new ideas.

Key observation for item 1: base (no launder) score 20, 90 ins vs 84. The diff shows the target uses a single `a1` base register: `lui a1,0x0; addiu a1,a1,0; lw v0,0(a1); lw v1,4(a1); lw a0,8(a1); ...` while mine reloads the symbol address into v0/v1/a0 each time (8 `lui` + 8 `lw`). The launder forces `src` into $5 which... hmm, but even with the launder, how did it get 84 ins? With the launder the compiler used $5 as the base: lui $5,0; addiu $5,$5,0; then lw with offsets. So the target's code is exactly "keep the address in a register". Without the launder, GCC rematerializes the address per load (cse decides the constant address is cheap to rematerialize). Classic `cse-const-addr` wall from walls.txt: "cse folds or substitutes a constant/absolute address the target keeps base-relative".

So the wall tag likely `cse-const-addr`. The moves.md shows several `launder | func_... | WALL cse-const-addr` entries. Let me grep moves for cse-const-addr and for successful launder cracks to see if any launder got cracked lever-free.

Let me grep the moves.md for "MATCH" lines with launder, and "cse-const-addr".

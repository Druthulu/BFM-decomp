---
ts: 2026-10-21T23:40:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Q4ir9MNNsxRsTx1f6dP5
---
The baseline is the ORIGINAL GAME's bytes (the ROM snapshot), not the tree's build. So the target is the real ROM code.

So the score compares candidate body vs the ROM's function bytes. The pinned body scores 0 → the pinned body matches ROM exactly. Our job: find a lever-free body that also matches ROM.

Now, the ROM function bytes are identical across includers (it's the same ROM function). The baseline object is per-includer but contains the same ROM bytes for this function. So scoring at rec[0] is sufficient in principle — as long as the *candidate* compiles the same at every includer. Since the candidate is spliced into the header, which is included in 136 TUs, the compiled function could theoretically differ if macro context differs, but for these shared headers it's uniform.

To be rigorous but cheap: I can verify by compiling the candidate at a different includer... which I can't rotate. Hmm.

Wait — maybe I can: recs_for uses `inc.get(tu, [])` where inc = dl.includers(). If I give --try a TU path of an *includer .c file* and pass a full-TU candidate file (not --body), then recs_for(tu) → by_src.get(tu) → that TU's own recipe, and text = my full candidate TU. But then the candidate TU must contain the whole includer file with the function body substituted. That's doable! I can copy the includer .c file, replace the #include of the header with the function body text? Hmm, the header contains the def; the includer does `#include "../shared/ov/func_8014C308.h"`. I could produce a modified copy of the includer where the header include is replaced by the candidate def (as a full TU candidate, no --body). Then --try with TU=src/ov_SC03_099/ov_SC03_099_after.c and the candidate file → compiles that TU (with my body) and compares the function's insns against that includer's baseline.

That gives me per-includer verification. Cost: writing such files (one per includer) — but I can create them with Write for a couple of includers. Actually simpler: I can create ONE modified copy for a second includer and check it; if the score is 0 there too, that's evidence for all.

Hmm, but there's a subtlety: does the includer .c compile standalone with the header replaced? The header has other content? For these ov headers, the header seems to contain just the comment + externs + the def. The includer includes it. Replacing the include with the def text (externs + def) should work if the externs are only used by this function. But other decls in the header might be needed... Let me check the header content of item 3: comment + def only (the externs? no externs in item 3's header). OK.

But wait: does the includer reference symbols declared in the header? For item 3, the header has no externs. Fine.

Plan for verification (cheap): for each item, after finding a candidate that scores 0 at rec[0], verify at one more includer by this TU-substitution trick.

Let me first focus on finding lever-free bodies; verification at the end.

Now back to item 3's crack.

Target (ROM) 39 ins. Mine (nopin) 41 ins. Differences:
- register mapping: mine's const-chain temp in $2, "1" in $3; target: const-chain in $3, "1" in $2.
- Mine has extra `move v0,zero` + `j` + `li v0,1` (3 extra ins vs 39/41).

Let me get the full target listing. Let me view the whole diff output (not just tail) for nopin.c. Let me re-run with more lines shown (tail -60).

Actually the earlier output was tail -30 and showed the whole diff (score line + pairs + opcodes). It showed mine[20:30] vs target[20:30], delete mine[31:33], replace mine[36:37] vs target[34:35]. It didn't show insns 0..19 (equal). So:

common 0..19, then:
mine[20] bnez v0,6ac4 | target[20] bnez v0,6ab8   (branch target differs → different block layout; the last insns' targets)
mine[21] move v0,zero | target[21] li v1,9
mine[22] li v0,9 | target[22] beq a2,v1,6abc
mine[23] beq a2,v0,6aa4 | target[23] li v0,1
mine[24] li v0,17 | target[24] li v1,17
mine[25] beq a2,v0,6aa4 | target[25] beq a2,v1,6abc
mine[26] li v0,41 | target[26] li v1,41
mine[27] beq a2,v0,6aa4 | target[27] beq a2,v1,6abc
mine[28] li v0,10 | target[28] li v1,10
mine[29] bne a2,v0,6aac | target[29] beq a2,v1,6abc
mine[30] (equal to target[30]?) — mine[30] not shown; the opcode range mine[20:30] target[20:30] replaced 10 lines each, so mine[30] == target[30]? Actually "replace mine[20:30] target[20:30]" means mine[20..29] vs target[20..29].
mine[31] j 6ac4 | target[31] --
mine[32] li v0,1 | target[31] --
mine[33] ? | target[32] ?
mine[34],[35] equal to target[33],[34]?
mine[36] j 6ac4 | target[34] j 6abc
```

Interesting. So the target's structure (last part):
```
20  bnez v0, <else>      ; test something
21  li v1,9
22  beq a2,v1, <ret1>    ; arg2 == 9 -> return 1
23  li v0,1              ; v0 = 1 (assigned AFTER the first compare!)
24  li v1,17
25  beq a2,v1, <ret1>
26  li v1,41
27  beq a2,v1, <ret1>
28  li v1,10
29  beq a2,v1, <ret1>
30  ...
31  ...
32  ...
33  ...
34  j <ret1>
```
Hmm, that means in the ROM, `li v0,1` occurs once, after the first comparison. And each "beq" branches to a common return block (6abc) that presumably does `jr $ra; move v0,$2`? Hmm, and the last `j 6abc`.

Wait: the branch target 6abc is the "return v0" block. And at 20 `bnez v0,6ab8` — jumps to 6ab8 (another block).

Hmm, so where does v0=1 come from in the ROM? `li v0,1` at 23 only. And the "return 1" happens at the branch target 6abc: presumably `move v0,v1`? no...

Let me think about the original ROM code semantics: the function returns 1 in those cases. The ROM likely:
```
if (arg2 == 9) return 1;   -> but only one li v0,1?
```
Hmm, the ROM has one `li v0,1` shared by 5 returns. That's what the current C source expresses (v0=1 once, 5 `return v0`).

And the ROM's `li v0,1` at position 23 (after the first beq) suggests gcc scheduled the assignment late.

My nopin compiled: `move v0,zero` at 21?! Where does a "move v0,zero" come from in mine? That's `return 0` — the `return 0` at the end of the function (the fall-through case returns 0). But in the ROM, the "return 0" path is elsewhere.

Hmm wait, in mine, $2 = v0 is the const-chain temp AND the return register. `move v0,zero` = setting the return value 0 → but that's in a different block.

OK let me stop reverse-engineering from the diff and get the full ROM asm. I'll objdump the baseline object.

Where's the baseline? BASELINE in tools/delever_oracle.py. Let me find BASELINE dir and the object for one includer, then objdump the function.

Let me grep BASELINE definition.

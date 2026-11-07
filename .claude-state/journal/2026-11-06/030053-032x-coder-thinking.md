---
ts: 2026-11-06T10:00:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mSNiG55w4VqVmGGveimf
---
So the scorer writes a scratch dir under .run/P36/engine/score/<alias>__<fn>/p<pid>/ and removes it. It adds -I<src_dir>. If I want dumps, I can replicate the compile myself: build a spliced TU under my shard, then preprocess with the right includes. But the include `../shared/engine_prelude.h` relative to the TU's own directory requires the file to sit in a directory whose parent has shared/. My shard dir .run/P40/T11/G27/<item>/ has no ../shared. But I can pass -I with a path such that "../shared/engine_prelude.h" resolves: the preprocessor resolves quoted includes relative to the including file's directory first, then -I dirs. `-Isrc/ov_SC03_124` would make "../shared/engine_prelude.h" → src/ov_SC03_124/../shared = src/shared ✓. So `-Isrc/ov_SC03_124` works. And "common.h" via -Iinclude. Good.

So I can make a dump manually:
1. Write spliced TU to my shard.
2. Run mipsel-linux-gnu-cpp with -Iinclude -I<tu dir> -Isrc/shared -Isrc -Isrc/ov_SC03_124 ... then cc1 with dumps.

But the tools/bin/cc1 path is used by cc1_dumps_tu.sh. I could just invoke cc1_dumps_tu.sh on my spliced file with DUMP_ROOT set; but its cpp line lacks -Isrc/ov_SC03_124. However it does -I"$(dirname $tc)" which for my spliced file is my item dir — wrong. Hmm.

Simplest: write my own dump script under .run/P40/T11/G27/ that mirrors cc1_dumps_tu.sh but with the right -I. That's allowed (scratch). But "the toolchain is reached through bin/sc.sh, bin/dt.sh, tools/cc1_dumps_tu.sh" — using the same binaries directly might be considered fine (the brief lists these as the routes; a custom script using mipsel-linux-gnu-cpp/cc1 is essentially cc1_dumps_tu.sh with an extra -I). I'd rather avoid friction.

Alternative: put the spliced TU in a temp dir one level under src? Not allowed (write only under shard).

Hmm, wait: cc1_dumps_tu.sh accepts a .c FILE. If I give it the ORIGINAL TU path with the body modified in place — no, can't modify src.

Let me reconsider: maybe I don't need dumps. The diff output is enough to iterate. For the clones, the question is allocation. Let me just try many real-C variants and score them in batch. That's the practical path and matches "≥30 scored tries".

Let me think about what real-C moves might get rv→v0 with keepalive kept:
- Declare rv at a different scope/position (decl order affects pseudo numbers and allocation order).
- Add/remove other locals.
- Use `s32 rv = -1;` initialization at decl? The structure rv is set in branches.
- Restructure the gotos into if/else chains (statement order).
- Change `d` to u16/s16.
- Compute d inline.
- Use `&&`/`||` folds.

But the fundamental: rv is a normal pseudo; local-alloc picks v1 because of the keepalive's register pressure? Let's understand: at the end, rv is live and the keepalive forces it to a register. The allocator gives it v1 because v0 is used by the comparison pseudos which have higher "priority" (more refs). In the target, rv is the return value so it's forced to v0 regardless.

Could we give rv more refs so it wins v0? The keepalive adds 1 ref. More refs to rv would change allocation priority. E.g., `rv = rv;`? That's an identity launder (not allowed) and might be deleted. Or use rv multiple times: `if (rv & 0x10000000) {}` adds instructions.

Hmm, local-alloc in gcc 2.7.2 uses `reg_qty`/`qty_phys_reg` with priorities based on `REG_N_REFS * loop_depth` and live length (`floor_log2(n_insns) - floor_log2(live_length)`). Actually local-alloc assigns per basic block: for each pseudo, it tries to find a free hard reg; the order of allocation among pseudos is by qty (refs/live). rv's live range spans multiple blocks, so local-alloc handles it... Actually local-alloc allocates only pseudos live within a single block; pseudos live across blocks are handled by global-alloc. rv is live across blocks → global-alloc. Global-alloc assigns based on priority (refs/live, loop depth). The target's return value is a hard reg ($2), so global-alloc doesn't move it.

For the keepalive-only variant, rv is a cross-block pseudo; global-alloc gives it a callee-saved or caller-saved reg based on priority. It got v1 (caller-saved). To get v0, rv must have the highest priority for v0... but global-alloc's v0 is just a caller-saved reg; the order of allocation matters. Hmm.

This is getting deep. Given time, the realistic outcome for the 3 clones: WALL expand-void-return (with PARTIAL:keepalive maybe not reachable). But the brief says WALL needs ≥30 tries. Let me do a batch of ~30 real-C variants per clone and see if any hits 0. I can generate them programmatically.

Actually, wait. Let me reconsider whether the clones might be crackable via a completely different route: what if the function body ends with a call that leaves v0 set? The target's last insn is `jr ra` with v0=rv. If the source's last statement were a call returning rv... no.

What if we use the "return value via an inline function" no.

Hmm, let me look at the prior wall for func_80183E68 (G26): "keepalive,pin | WALL lreg-copy-pref-dying-base — local-alloc ties `rv=(s32)a0` to the dying a0... void def makes the value dead; lever-free 42/43, 30 tries". So a similar void rv case was walled after 30 tries. Good — precedent.

And func_800CD5CC, func_801F0C4C: expand-void-return walls. So the clones are almost certainly walls.

But wait — maybe PARTIAL is possible for the clones: keep only the keepalive and score 0? b3 scored 6. If no real-C move gets 0, then WALL.

Hmm, but hold on: maybe keep only the PIN and drop the keepalive but replace the keepalive with a real use that keeps the value live at zero instruction cost? The pin makes rv=$2; then any use of rv would be in $2. But we need a use that costs nothing. E.g., at `done:`, `return rv;` — in a void function, dropped. What if `done: if (rv) {}`? Adds `beqz`. What about `done: ;`? No use.

Wait — actually, if rv is pinned to $2 and the function is void, the stores to rv ($2) might survive if gcc treats hard-reg vars as volatile? b2 (pin only) scored 15 (11 ins), so no, deleted.

Hmm, what about pinning rv and then the last statement being `func_8002D4C8(rv, 0)`? no.

OK. Let me also consider: maybe the whole premise is that these 4 items are walls, and the shard G27 is a "crack shard" where the expected outcome is mostly walls. The brief's RETURN asks per item result best wall. So walls are expected.

But I must give each item a fair 20-30 min and ≥30 tries for WALL. Let me be efficient: write a generator that produces many real-C variants and batch-score them. But first, let me handle each item's FRESH check and notes.

Actually, let me reconsider item 4 more. Its lever-free b1 has score 22. Maybe some real-C moves reduce it, but the 12 missing dead-computation instructions are the wall. Could a real use of v1 be added that costs 0? The call is `func_8002D4C8(0x407, 0)`. What if the real source is `func_8002D4C8(0x407, v1 & 0)`? gcc 2.7.2 folds `x & 0` → 0 and drops v1. Tested? Not yet. Let me test some variants for the second branch:
- `func_8002D4C8(0x407, (v1 & 0));`
- `if (v1 < 0x1F) v1 = 0x1F; func_8002D4C8(0x407, v1 & 0);`
- `func_8002D4C8(0x407, (u8)v1 & 0);`
- `func_8002D4C8(0x407, v1 - v1);` → folds to 0 but may keep v1? `v1 - v1` folds to 0.
- `func_8002D4C8(0x407, v1 * 0);` folds.

But these are "identity-statement launders" — explicitly do NOT count as a crack. So even if score 0, it wouldn't be accepted as MATCH (a lever of kind launder remains). So no.

What about a real use that isn't a launder: e.g., the second branch computes v1 and uses it for something with a real effect that the target also has? The target has no such effect. So no.

Thus item 4 = WALL flow-unused-result (dead v1 computation) plus maybe expand-void-return? The wall is flow deleting the dead computation. Tag `flow-unused-result` fits: "flow deletes results the target computes but never uses". Evidence: gcc pass flow/combine.

But before WALL, I need ≥30 tries. Let me generate variants of item 4's body (real-C moves) and score them. The best lever-free is what goes in win.c. Let me do that.

Actually, the requirement: "wall (WALL/PARTIAL) = a tag ... evidence = gcc pass + mechanism ≤ 140 chars". For WALL, best = lowest score of a lever-free body. So I need to find the lowest score among lever-free variants, with ≥30 scored tries. Fine.

Plan per item:
1. FRESH: diff orig.c vs current src (done at extraction; but src may move between items — re-extract at each item start).
2. Generate ~30 lever-free variants via a script (systematic real-C moves).
3. Score all in batch (sc.sh).
4. Pick best; if 0 → MATCH; else WALL with tag.
5. Append results row, moves line, notes.

Time: 4 items. Let me be efficient with batch generation.

But wait — for the clones, there might be a subtle possibility: the target's `rv` in v0. Let me look at whether the clones' orig actually needs both pin and keepalive, or just one. b3 (keepalive only) = 6. b2 (pin only) = 15. So the keepalive is the essential keeper; the pin fixes the register. A PARTIAL:keepalive would need rv→v0. Since global-alloc chose v1, maybe adding a *real* local/ref could shift it. Let me try a few real-C moves on b3:
- move `d` declaration/scope
- change d to u16
- compute rv via if/else instead of goto
- add `s32 e` unused? (dead locals don't affect)
- change `x`/`y` types
- reorder statements

Let me first check b3's full asm to see the register map and whether v0 is free. I'll get the diff more fully. Actually the diff showed mine uses a1 for rv in some places? No, that was item 4. For b3: mine v1→v0 x1, and delay slots. So rv=v1, x=v1? Let me see the whole mine asm. I need a dump.

Let me just create the spliced TU and run cpp+cc1 manually with a small script under my shard. I'll mirror cc1_dumps_tu.sh. This is scratch; acceptable. Let me check the cc1 binary path and flags from the script: /home/musashi/bfm-decomp/tools/bin/gcc-2.7.2-psx/cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -dr -ds ...

And cpp: mipsel-linux-gnu-cpp -lang-c -Iinclude -I"$(dirname $tc)" -Isrc/shared -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C -Isrc '-DINCLUDE_ASM(a,b)='

I'll add -Isrc/ov_SC03_124. Let me write a script.

Actually, maybe simpler: use tools/cc1_dumps_tu.sh with the spliced file but place the spliced file's directory such that includes resolve. I can't write under src. But I could symlink? No.

Hmm, the cpp line's -I"$(dirname $tc)" — if my spliced file is at .run/P40/T11/G27/<item>/tu_b3.c, then -I that dir. The include "../shared/engine_prelude.h" → .run/P40/T11/G27/<item>/../shared = .run/P40/T11/G27/shared — I could create that dir with the header? No, header content needed.

I'll write my own dump script. Let me do it for one item to understand allocation, then decide.

Actually, let me reconsider priorities. The 3 clones are likely walls; dumps won't change that (void return). The only path to MATCH would be changing the return type (forbidden). So a dump is not decisive; the wall is structural. Let me instead spend tries on real-C moves that might shift allocation for PARTIAL:keepalive.

Let me generate variants of the clone body (keepalive kept, pin dropped) with real-C moves:
1. if/else instead of goto
2. rv declared s32 (done)
3. d as u16
4. x,y as u16
5. compute d twice inline
6. reorder the two checks
7. `rv = d << 1` instead of `d * 2`
8. combine `d = x - a0; if (d < 16)` → `if (x - a0 < 16)`
9. `s32 rv = 31;` init and early returns via if/else
10. use a do/while(0) — needs // !FAKE: do-while
...

But these change the target structure; only variants that keep 26 ins with rv→v0 could score 0.

Hmm, actually, let me reconsider the allocation. In b3, rv got v1. The target rv=v0. What if we *remove* the `d` variable and compute inline? Then fewer pseudos; v0 might go to rv. Let me test a handful quickly. I'll create a generator script to produce variants from a template.

Let me write a Python generator for the clone body that emits named variants. I'll use the func_80182420 clone (same for all three, different globals).

Let me define the base and variations as strings in a script. Then sc.sh batch.

Time check: I've spent a while. Let me be decisive.

Approach for clones:
- Generate ~35 variants across real-C move families, all lever-free EXCEPT keep the keepalive asm (to target PARTIAL:keepalive) — wait, no: lever-free means kinds gone. For WALL, the best score is "lowest score of a lever-free body". PARTIAL means win.c keeps only some levers. So I should test BOTH:
  (a) fully lever-free variants → best score → WALL best.
  (b) variants keeping the keepalive (kind kept) → if any scores 0 → PARTIAL:keepalive.
  (c) variants keeping the pin → if 0 → PARTIAL:pin.

For (a) fully lever-free, rv dead → flow deletes everything → score 15 (11 ins). Real-C moves can't keep a dead value. So best fully-lever-free is likely ~15. Actually could some real-C move keep it? No real use exists. So WALL best = 15 (or lower if a variant leaves the value in v0 via the void return... no).

Wait, but maybe a real use that the target ALSO has: does the target use rv anywhere else? No. So no.

Hmm, so (a) is hopeless; the "best lever-free" is just the minimal deletion. Let me compute it.

For (b)/(c), the levers remain → PARTIAL possible if 0. Let me try hard on (b): keepalive kept, rv→v0.

Let me get the actual b3 asm. I'll write the dump script. It's worth it.

Let me write .run/P40/T11/G27/dump.sh:
```bash
#!/bin/bash
# dump.sh <spliced_tu.c> <srcdir> <tag> <outdir>
tc=$1; inc=$2; tag=$3; d=$4
rm -rf "$d"; mkdir -p "$d"
mipsel-linux-gnu-cpp -lang-c -Iinclude -I"$inc" -Isrc/shared -Isrc -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C '-DINCLUDE_ASM(a,b)=' "$tc" > "$d/$tag.i" 2>"$d/cpp.err"
(cd "$d" && /home/musashi/bfm-decomp/tools/bin/gcc-2.7.2-psx/cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker -dl -dg -dc -dr -ds "$tag.i" -o "$tag.s" 2>"$tag.err")
```
And a splice script to produce the TU with the body replaced. The body_span logic: find the function definition. I can use the same body_span? Simpler: I know the line ranges (e.g., 3252-3289 for func_80182420). Replace those lines with the candidate body text.

Let me write a Python splice script that takes src, start, end, body file, out.

But FRESH: line ranges may shift. I just extracted, so current.

Let me write these two scripts and dump b3.

Actually — the cc1 -dl dump shows local-alloc, -dg global-alloc, -dc combine, -dr RTL. I want the .lreg (register allocation) and maybe .greg.

Let me do it.

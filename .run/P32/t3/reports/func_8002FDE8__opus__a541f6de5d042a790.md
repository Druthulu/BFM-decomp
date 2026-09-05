# main:func_8002FDE8 — arm opus — model claude-opus-5
agent a541f6de5d042a790 · start 2026-09-05T06:55:12.154Z · end 2026-09-05T07:16:19.278Z · transcript /home/musashi/.claude/projects/-home-musashi-bfm-decomp/c6a5fb71-f2ae-4846-a4a9-a43a4c1c3496/subagents/agent-a541f6de5d042a790.jsonl

## Task prompt (first 600 chars)

Byte-match ONE function for the Brave Fencer Musashi matching decomp. Repo: /home/musashi/bfm-decomp (run every command from there). Target: func_8002FDE8 in binary main (73 instructions, class F-FAR, best closeness 35 at exact length, OPCODE-MIXED only — gcc caches &D_800A46D2 in a callee-saved register across the func_800419B0 call where the target rematerialises lui/lo at both sites; un-chaining, volatile and a ref-boost asm were falsified). Arm: opus. READ FIRST, in order: .run/P32/t3/BRIEF.md, .run/P32/t3/SYS.md, .run/P32/t3/packs/func_8002FDE8.md. Target asm (read IN FULL): asm/nonmatchi

## Final report (verbatim)

**MATCH** — 73/73 instructions, byte-identical in the leaf check *and* in the real TU (`rtu_match`). Draft at `/home/musashi/bfm-decomp/.run/P32/t3/opus/func_8002FDE8.c`. `src/` and `config/` untouched.

## What closed it (four independent levers, in order)

**1. The wall the last four attempts hit was already solved twice in this very TU.** The residual everyone called "an unresolved regalloc-priority wall" (gcc caching `&D_800A46D2` in a callee-saved reg) is documented at `src/800_b_2.c:2866` (`func_8002FF0C`) and `:3000` (`func_800301C8`): declare it **`extern s16 D_800A46D2;` (scalar) at block scope**, not the TU's file-scope `extern s16 D_800A46D2[]`. The array spelling makes cse materialise the address; the scalar spelling emits two independent `%hi/%lo` accesses. 35 → 3 mismatched instantly. Attempts 1–4 all carried the array spelling from the pack's prior body and never read the neighbours the pack pointed at.

**2. Tail spelling.** The third `return 1` must live *inside* the `== -1` arm; writing it as a trailing fallthrough inverts the final `beq` into `bne` and swaps the two tail blocks.

**3. The §47 live-length slider, computed not guessed.** `-dl -dg` gave the real numbers: `data` = 2 refs/15 insns → pri **1333**; the `1` constant = 4 refs/58 insns → pri **1379**. A 3% gap, so the constant allocated first and stole `$s1`. One zero-byte `__asm__ __volatile__("")` placed where the constant is live and `data` is dead flipped `allocno_order` from `…84 73` to `…73 84` — `data`→`$s1`, `1`→`$s2`, as the target.

**4. Two new shape facts (cookbook candidates).** The final 4-instruction swap was *not* reachable by any fence position — 118 enumerated variants plateaued at 4:
- **The `1` constant needs its own C statement** (`one = 1;`) so a fence can sit *between* the `li` and the `sb`: the `li` must head the block while the `sb` sinks below the index computation. The literal-at-every-site spelling costs 10 mismatched.
- **`i4 = idx * 4;` as a separate statement.** The `sb D_800A46B0` and the `lw D_800652F0` carry a memory dependence, so sched1 orders them by LUID; splitting the index out gives the `sll` a lower LUID than the `sb`, reproducing `sll / addu $a0 / sb / lw`.

Generalisable lesson for the harvest: **a "regalloc-priority wall" verdict is worth re-testing whenever the pack names a same-TU neighbour** — and §47's slider is a *computation*, not a search: read `n_refs`/`live_length` out of `.lreg`, evaluate `floor_log2(n)·n/L`, and you know exactly how many static insns you need and where. Falsified here and not worth re-trying: fences alone (any of 4 positions × 6 statement orders), `u8` vs `s32` for the constant, and a named temp for the loaded value.

{"fn": "func_8002FDE8", "binary": "main", "arm": "opus", "status": "MATCH", "closeness": 0, "compiles": true, "draft_path": ".run/P32/t3/opus/func_8002FDE8.c", "note": "Closed by 4 levers: (1) the 35-plateau residual was the ARRAY spelling of D_800A46D2 - the same-TU neighbours func_8002FF0C (src/800_b_2.c:2866) and func_800301C8 (:3000) both document the fix, a block-scope scalar `extern s16 D_800A46D2;`, which emits two independent %hi/%lo instead of a cse'd callee-saved address; (2) the third `return 1` inside the `== -1` arm (trailing-fallthrough spelling inverts the final beq and swaps the tail blocks); (3) SS47 live-length slider computed from -dl/-dg: data = 2 refs/15 ins pri 1333 vs the `1` constant 4 refs/58 ins pri 1379, so one zero-byte fence where the constant is live and data is dead flips allocno_order and hands $s1 to data, $s2 to the constant; (4) two new shape facts - the `1` constant needs its own statement (`one = 1;`) so a fence can split the `li` from the `sb`, and `i4 = idx * 4;` must be a separate statement because the sb/lw memory dependence makes sched1 order them by LUID. Measured INERT: all fence positions alone (118 variants enumerated, plateau 4 mismatched), u8-vs-s32 for the constant, a named temp for the loaded value."}

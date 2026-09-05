# main:func_80023BF0 — arm opus — model claude-opus-5
agent a98e2f3aedcf71003 · start 2026-09-05T06:54:23.504Z · end 2026-09-05T07:05:35.147Z · transcript /home/musashi/.claude/projects/-home-musashi-bfm-decomp/c6a5fb71-f2ae-4846-a4a9-a43a4c1c3496/subagents/agent-a98e2f3aedcf71003.jsonl

## Task prompt (first 600 chars)

Byte-match ONE function for the Brave Fencer Musashi matching decomp. Repo: /home/musashi/bfm-decomp (run every command from there). Target: func_80023BF0 in binary main (281 instructions, class D-NEAR, best closeness 11 — two seeds exist: the S80 permuter waypoint .run/S79w/permuter/func_80023BF0.c (11, but its ADDRESSING change moved a lui/ori constant across a sll/bne — VERIFY that seed's semantics against the target before trusting it) and the S79 Opus draft .run/S79w/opus/func_80023BF0.c (18, every lever explained in its header via gdb-on-cc1 allocno arithmetic). The pack carries the jour

## Final report (verbatim)

**MATCH — closeness 0, both leaf and real-TU.** No permuter cycles used; no `src/` or `config/` edits.

**What closed it:** the OT link is a libgpu `P_TAG` 24-bit bitfield store, not a hand-written mask/OR. Cookbook **§364** (the `-O2` half) plus the `func_8017FD64` addendum at cookbook L30700 describe this residual exactly — and this is a third witness for it.

The plateau at 11–18 had two halves that are *mutually exclusive* from a hand-written `(A & 0xFF000000) | (B & 0xFFFFFF)`:
- both loop preheaders (and the epilogue) emit the two mask constants **before** the `sll/addu` forming `&otab[idx]`; the target emits them after;
- the paired `lui/ori` mask register and the OT-slot pointer are two-cycle swapped (`$t3`↔`$t4`).

Swapping the `|` operands buys the target's hoist order but inverts the body's two loads and the `ior` roles (measured 35). `expand_assignment` → `store_field` → `store_fixed_bit_field` expands the RHS **bitfield extract first**, then the destination read — which simultaneously gives loop.c the movable order `[&otab[idx] ; 0xFFFFFF ; 0xFF000000]`, gives `expand_binop(ior_optab, temp, value)` the target's `or $v1,$v1,$v0` operand roles, and emits the store-side `and $v1,$t1,$t3` ahead of the slot reload. §364's `-O2` veto (`MEM_IN_STRUCT_P` letting the alias oracle CSE a global load across the tag store) does not bite here: the only nearby global read is `D_800B9A02`, loaded once in the prologue.

**Kept from the S79w 90→18 chain** (each re-measured against the new body): the §194-A fence in *both* arms (removing it → `WIDTH/lhu!=lbu`); `code` split from its 0x74/0x76 base with compound accumulation; `register u32 base __asm__("$3")` (still required — unpinning re-colours the file from insn 9); and the 13 zero-byte fences after `pkt = D_800A5E60;` (re-measured plateau on this body: 0→15, 8→13, 10/11/12→7, 13→MATCH).

**Dropped as no longer needed** (each verified still MATCH): the `m24 __asm__("$11")` 0xFFFFFF pin — the bitfield hoists it into `$t3` by itself — and the `e1 __asm__("$4")` pin for `0xE1000015`.

**Notes for the coordinator:** the S80 permuter waypoint (closeness 11) was semantically **unsound** — it had sunk `m24 = 0xFFFFFF` into the `c == 0x3870` arm of the sprite loop, leaving the mask register undefined on any first iteration taking the other arm; it was not used. Also re-confirmed inert/worse here: an explicit `u32 *ot = &otab[idx]` in any scope buys a 4th callee-saved register and costs +3 instructions (284). Typedefs follow the TU's own convention (`PTag_80023BF0`, `SVEC_80023BF0`); `src/800.c` already uses this bitfield idiom in `func_8001D3FC`, `func_80021284`, `func_80023570`. Symbols audited against the target's own relocation lines: `D_800AF630`, `D_800A6610`, `D_800B9A02`, `D_800A5E60`, no `jal`.

{"fn": "func_80023BF0", "binary": "main", "arm": "opus", "status": "MATCH", "closeness": 0, "compiles": true, "draft_path": ".run/P32/t3/opus/func_80023BF0.c", "note": "Closed by the libgpu P_TAG 24-bit bitfield OT link (cookbook §364 -O2 half + the func_8017FD64 addendum at L30700), replacing the hand-written (A&0xFF000000)|(B&0xFFFFFF): store_fixed_bit_field expands the RHS bitfield extract before the dest read, which fixes loop.c's preheader hoist order [&otab[idx]; 0xFFFFFF; 0xFF000000] AND the ior operand roles/$t3-$t4 pairing at once — the two halves the mask/or form can never satisfy together (operand swap alone = 35). Kept: §194-A fence in both arms, base split + register base __asm__(\"$3\"), 13 fences after pkt=D_800A5E60 (13 is the minimum: 0->15, 8->13, 10/11/12->7). Dropped as now inert: the m24 $11 and e1 $4 pins. Re-measured worse: explicit u32 *ot (+3 ins, 4th callee-saved). The S80 permuter seed at 11 was semantically unsound (m24 sunk into the 0x3870 arm) and was not used."}

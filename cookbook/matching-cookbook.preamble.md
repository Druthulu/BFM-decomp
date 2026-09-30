# Matching Cookbook — reusable compiler idioms & C-writing techniques

> **⚠️ SOURCE-CITATION PROVENANCE (swept 2026-07-28, `tools/sweep_citations.py`).** This file's ~57
> gcc-source citations are **MIXED provenance** — some are exact for our gcc 2.7.2
> (`tools/reference/gcc-2.7.2/`), others came from `gcc-papermario`, which is gcc **2.8.1**. Spot-
> verified exact: `loop.c:5556` (`emit_iv_add_mult`), `local-alloc.c:1765/1795/1825` (`combine_regs`),
> `global.c:906/917/924/1000` (`find_reg`), `local-alloc.c:1021/1064` (`update_equiv_regs`).
> **Known miss — NOW FIXED (2026-07-28):** `expr.c:5535` was `MIN_EXPR`/`MAX_EXPR` optab code. The
> two sites that idiom actually means are **4577** (INDIRECT_REF, guarded 4570-4576) and **4888**
> (COMPONENT_REF, unconditional). Both corrected in place below, re-derived twice independently.
> (`4904` is the `OFFSET_REF` grant — a third site, not the one that idiom is about.)
> **Why this is lower-stakes here than in `docs/gcc-2.7.2-map/*`:** those files are source-derived
> *reasoning*, so a bad read means bad advice. This file's idioms are **byte-proven**, with citations
> attached as *explanation* — a drifted cite corrupts the why, not the lever. Re-derive a citation
> (`grep -n '^sym (' tools/reference/gcc-2.7.2/*.c`) before building new reasoning on it.

> **Evolvable reference (docs/ layer). Created Phase 6, 2026-06-14.** Append an entry every
> time a reusable nuance is found — these recur across nearly every function, so capturing
> them once accelerates all future matching. Companion to `SETUP.md` §5 (the pinned triple)
> and §6.6 (the matching loop). **Consult this at session start before matching.**

**Pinned toolchain (the context all entries assume):** `tools/bin/gcc-2.7.2-psx/cc1`
`-O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker` → `maspsx --aspsx-version=2.56
--expand-div` → `mipsel-as -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0`. (See SETUP.md
§5.4. psx≈cdk and 2.56≈2.67 produce identical bytes on functions without the discriminating
idioms — they only diverge on `sltu`+`$at` / div-expansion specifics.)

---


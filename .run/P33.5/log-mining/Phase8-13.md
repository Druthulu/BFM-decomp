# Log mining — Phase8-13
Files/ranges: `phase-ends/logs/Phase8.md`:1-53 · `Phase9.md`:1-55 · `Phase10.md`:1-102 · `Phase11.md`:1-96 · `Phase12.md`:1-65 · `Phase13.md`:1-29  ·  Lines read: 400 of 400
Candidates considered: 38 · NEW: 4 · ALREADY-BANKED: 34

> Grep corpus used for every "already banked?" test (`$C`), verbatim:
> `docs/matching-cookbook.md docs/cookbook-index.md docs/decision-log.md docs/accelerators.md docs/retrospective.md docs/wave-playbook.md docs/how-to-ai-decomp/{00..12}-*.md decomp-architect/corpus/decomp-kernels.md decomp-architect/templates/registry-E.decomp.md phase-ends/DIGEST.md`
>
> **Headline:** Phases 8-13 are the most thoroughly distilled span I could have drawn — cookbook §9.x/§9.7/§11/§12/§13
> were written *from* these logs, so ~90% of every candidate is already banked, often verbatim. The residue is four
> items, and one of them (C1) is not merely unbanked: **the distilled record still asserts the claim these logs refuted.**

## NEW

### C1 — A toolchain/SDK-version detector's verdict is a HYPOTHESIS until a placement COUNT backs it; when a version stamp and a byte-probe disagree, the probe wins — and the refuted stamp must be un-banked everywhere it was written
- **Evidence:** `phase-ends/logs/Phase10.md:44-54` —
  > "DetectPsyQ on the imported resident program reports **PsyQ Version = 470** (the EXE is 4.0.0) … the one PsyQ-signature hit in-range is `DsMix`"
  > "**Implication:** the resident's PsyQ library linking (Phase 11/12) uses **4.7**, not the EXE's 4.0 — so the 4.7 `.LIB`s are a needed asset"

  and the refutation, `phase-ends/logs/Phase12.md:41-46` —
  > "**Result: NIL library footprint.** … 4.7 libsnd **1/226** (a 4-ins coincidence `ut_rev_2.o`), libspu **0/134**, libgte **0/509**"
  > "R24's 'resident is 4.7 → link its 4.7 libs' is **moot** — the DetectPsyQ 4.7 signal was one coincidental DsMix-region pattern, not a linked footprint."
  > "the resident uses the Makefile's default pinned triple (no override) … **Two byte-exact matches** confirm it"
- **What happened / what it cost:** A signature scanner reported a second SDK version for the second binary on the strength of
  **one** in-range hit. That single number was promoted to a project rule (R24), carried forward in the PhaseEnd's "Notes for
  Future Phases" (`Phase10.md:52-54`), acted on by sourcing/converting/checksumming a whole second SDK
  (`Phase11.md:10` — "PsyQ 4.7 = sha-record only … `tools/psyq/conv47/` + `psyq-4.7-converted.zip`"), and used to shape an
  entire Block A of the Phase-12 plan around linking those libs. Phase 12's T1 then measured the footprint with a
  denominator — 1/226, 0/134, 0/509, 0/61 — and T2's two byte-exact matches proved the binary's triple was **identical to
  the one already in use**. Every 4.7 task was removed mid-phase (`Phase12.md:19,59`).
- **Not banked — greps:**
  `grep -n -i -E 'DetectPsyQ' $C` → **0**;
  `grep -n -i -E 'nil footprint|NIL library' $C` → **0**;
  `grep -n -i -E 'signature hit|single hit|version detect|footprint survey' $C` → **0**;
  `grep -n -i -E 'resident is 4\.7|resident.*PsyQ 4\.7|refuted|moot' $C` → 12 hits, **all about other refutations** (the
  producer-census, the pin-crash wall, the §42e wall) — none about the SDK version;
  `grep -n -i 'dsmix' $C` → 1 hit (`docs/decision-log.md:2260`, an unrelated phantom-function bug).
  The failure museum's 37 exhibits (`docs/how-to-ai-decomp/12-failure-museum.md:9-45` — one row per exhibit) and the retrospective's belief
  table (`docs/retrospective.md:20-36`) both cover Phase 12 — but only for the script-VM belief (exhibit #3), never this one.
- **⚠ LIVE STALE ASSERTION (worth more than the lesson):** `docs/matching-cookbook.md:978-981`, the §11 heading
  **"Per-binary toolchain provenance (R24)"**, still reads *"the EXE is PsyQ 4.0, the **resident is 4.7**
  (`tools/psyq/conv47/`…). Never assume one binary's SDK applies to another — the 4.0 libs won't byte-match the
  resident's 4.7 objects."* Every clause after the first is false on the bytes: the resident links **no** stock objects of
  **either** version, and its compiler triple is the EXE's. `phase-ends/DIGEST.md:76` repeats it ("it detects PsyQ 4.7").
  A future project inheriting the cookbook inherits the error. (I am read-only; flagging, not editing.)
- **Proposed home:** DK (a kernel, paired with DK-8's "second oracle on anything that steers strategy") **+** a failure-museum
  exhibit **+** a correction to cookbook §11 / DIGEST R24. The kernel's prescription: *a version/SDK stamp is a lead, not a
  finding — before it steers a plan, run the placement survey and quote its denominator, and run the detector against a
  binary whose version you already know (Phase 12 did exactly this: "4.0 libsnd vs the EXE snd region = **35/163** placed —
  the tool works + is version-sensitive", `Phase12.md:42`).* It also **sharpens the banked bootstrap order**
  (`docs/how-to-ai-decomp/03-bootstrap-order.md:22-25`, "Library version stamps, **then** idiom-revealing probe
  functions"): the two steps can disagree, and the ranking is not stated there — the probe function's bytes win.
- **Portable because:** every console decomp starts by fingerprinting an SDK from signatures, on every binary it finds; a
  one-hit positive with no denominator is the default output of every signature matcher ever written.

### C2 — Histogram a secondary binary's `jal` targets BY ADDRESS RANGE before assuming it carries its own copy of anything
- **Evidence:** `phase-ends/logs/Phase12.md:45` —
  > "Call-target scan: **61 distinct EXE-range `jal` vs 37 internal** — the resident calls the EXE's SDK/engine.
  > **Resident = game code, no linkable library. Verified by both oracles.**"

  corroborated at `Phase12.md:43`: "the PsyQ SDK lives in the **EXE** (959 LINKED); the **resident is entirely custom engine
  code** that calls the EXE's resident SDK + engine fns via fixed addresses (no RAM-wasting SDK duplication in an
  always-loaded blob)."
- **What happened / what it cost:** The whole 4.7 detour (C1) is answered in one cheap scan that needs no SDK, no signature
  database and no decompiler: bucket every `jal` target by which binary's address range it lands in. A blob whose calls
  leave its own range is *linked against* the primary image, so it cannot contain the library code you are about to go
  source. On a memory-constrained console this is the expected architecture, not the exception — an always-resident blob
  that duplicated the SDK would waste the RAM the design exists to save.
- **Not banked — greps:**
  `grep -n -i -E 'call-target|call target' $C` → 3 hits, **all** about a *wrong call target being invisible to a
  relocation-masked diff* (`docs/matching-cookbook.md:5120`, `docs/decision-log.md:1988`) or a DESTPTR cross-check
  (`:36769`) — a different subject;
  `grep -n -i -E 'jal.*range|cross-range|calls into the (EXE|main)' $C` → 1 hit
  (`docs/matching-cookbook.md:11125`, a liveness-across-`jal` question — unrelated);
  `grep -n -i -E 'no.*duplicat.*SDK|SDK duplication|shares the (EXE|main)\x27s' $C` → **0**.
  Cookbook §11 records the *consequence* ("overlays *call*, don't embed, the resident", `:968`) but never the
  **instrument** that measures it, and never as a step to run on a newly-discovered binary.
- **Proposed home:** accelerator + a line in the bootstrap-order chapter's Phase-1 census (alongside "duplication,
  families, reach × size, the unique tail"): *for every non-primary binary, the call-target range histogram, before any
  library survey.*
- **Portable because:** any multi-binary game (overlays, DLLs, a kernel + modules, a resident + transients) answers
  "does this binary contain library code or borrow it?" from its own call targets, with a disassembler and a histogram.

### C3 — A raw blob's load address is a hypothesis; the free confirmation is arithmetic against the NEXT known segment's base
- **Evidence:** `phase-ends/logs/Phase10.md:13` —
  > "Load **vram 0x800CEDF8** (Phase-3 T6b proven); `VRAM_BASE`=0x800CEDF8 (fileoff 0→vram). Computed **end vram
  > 0x80128154** (4 B under overlay slot 0x80128158 — boundary corroboration)."
- **What happened / what it cost:** Before carving a single subsegment of a headerless 365,404-byte blob, the phase
  checked `base + size` against the *already-known* base of the segment that loads next. It landed 4 bytes under it. That
  is an independent confirmation of the load address — obtained from arithmetic, at zero cost, ahead of the byte-match
  iteration that would otherwise have been the first thing to discover a wrong base (and would have presented as a
  mystery diff, not as "your base is wrong"). The blob had **no header segment** (`Phase10.md:14`), so nothing in the file
  itself carried the address.
- **Not banked — greps:**
  `grep -n -i -E '(verify|confirm|corroborat|prove).{0,40}(load address|vram base|base address)' $C` → **0**;
  `grep -n -i -E '(load address|vram base|base address).{0,40}(corroborat|cross-check|neighbou?r)' $C` → **0**;
  `grep -n -i -E 'corroborat' $C` → 78 hits, **all** cookbook card cross-references ("corroborated by wave dl…") — a
  different sense of the word;
  `grep -n -i -E 'end vram|code end|end address' $C` → 3, all about function epilogues / loop back-edges.
  The flat-blob recipe is banked (`docs/matching-cookbook.md:1091-1096`, SETUP §6.7) but it starts *from* a known base.
- **Proposed home:** accelerator, or a bullet in the flat-blob recipe (cookbook §11 "notes for reuse").
- **Portable because:** every console has a documented memory map with adjacent, known segment bases, and every
  headerless payload's load address starts as an inference from a loader trace.

### C4 — ⚠ LOW VALUE, recommend dropping: during a parameterization refactor whose oracle is a byte-locked binary, generalize only what a second target actually needs
- **Evidence:** `phase-ends/logs/Phase9.md:26` —
  > "**Refinement vs plan:** SDK-region vars (LIB*_ELF…) left un-namespaced — they're already main-only by the ifeq gate;
  > namespacing deferred to when a 2nd binary needs SDK regions (avoids speculative churn, consistent with de-risked scope)."
- **What happened / what it cost:** The Phase-9 plan called for namespacing every Makefile variable; the executor
  namespaced only what the second binary would actually resolve, on the grounds that each unnecessary edit is diff
  surface against a byte-locked oracle carrying no proof with it. It held — Phase 10's resident and Phase 13's four
  overlays never needed those vars.
- **Not banked — greps:**
  `grep -n -i -E 'speculative' $C` → **0**;
  `grep -n -i -E 'second instance|rule of three|generali[sz]e (only )?(at|on) the second' $C` → 9 hits, all cookbook cards
  citing "a second instance of §187/§343" (evidence corroboration, not scope discipline);
  `grep -n -i -E 'de-risked scope|speculative churn' $C` → **0**.
- **Proposed home:** none — **recommend NOT banking.** It is generic YAGNI wearing a decomp costume; its one
  decomp-specific edge (an edit with no negative control attached is risk without proof) is already covered by the banked
  negative-control law at `docs/matching-cookbook.md:842-845`. Listed only so the parent can see it was considered and
  judged, rather than missed. It also sits in tension with DK-5 (`decomp-architect/corpus/decomp-kernels.md:68`, "Build
  propagation the moment a second binary exists") and would need that boundary drawn before it could be stated safely.
- **Portable because:** (weakly) any refactor under a byte-locked oracle; not decomp-specific.

## ALREADY-BANKED (one line each)
- An object's `.text` size is the PADDED/aligned size, not its instruction count — a boundary set from the nominal size shifts every byte after it (libc2 SETJMP.o: 30 ins = 0x78, `.text` = 0x80, +8 global shift) — lives at `docs/matching-cookbook.md:796`
- Two libraries whose objects interleave must be linked as ONE combined region; disambiguate an aliased address by byte-matching the *linked* `.text` — `docs/matching-cookbook.md:801-805`
- An object whose `.bss` commons the original linker scattered can't be reproduced by one NOLOAD base → exclude it BY ADDRESS and bank the other 60 (the GS_001 class) — `docs/matching-cookbook.md:806-811`
- Never byte-check an incremental build — `psyq_integrate` rewrites the `.ld` in place and a rebuild can transiently mis-resolve a sibling library (a harvest falsely diffed in libmcrd) — `docs/matching-cookbook.md:812-815`; R22; `docs/how-to-ai-decomp/12-failure-museum.md:18` (exhibit 10)
- Byte-correct-but-not-hand-written code needs its own progress category (LINKED), never counted as a stub — the metric jumped 20.31% → 50.24% with no bytes changed — `docs/matching-cookbook.md:816-818`
- Derive the progress metric from the build's own single source of truth (the Makefile's `psyq_integrate` calls), and land the parser change in the SAME commit as the call-site change — `docs/matching-cookbook.md:816-817`, `:846-852`
- Transitional-default technique: give each tool a param DEFAULTING to the kept global, update callers one green commit at a time, then a final commit removes the globals → required params; refactor LEAF-FIRST so a missed call site fails loud — `docs/matching-cookbook.md:834-841`
- A pure no-op refactor proves nothing (the param may be accepted-but-ignored) — ALSO pass a deliberately WRONG value and require the build to DIVERGE — `docs/matching-cookbook.md:842-845`
- Required params with no defaults, so a second binary can never silently inherit the first's values — `docs/matching-cookbook.md:826-833`
- The dual gate: byte-identical WITH the vendor objects AND WITHOUT them (the fresh-clone stub fallback), or the public tree rots — `docs/matching-cookbook.md:727-729` (§9.3); `docs/how-to-ai-decomp/11-publishing.md:69-70`; the cost of only ever checking it by hand is at `docs/decision-log.md:3090-3095`
- A resegment/trim must preserve the existing matched C and `#ifdef NON_MATCHING` blocks — splat will NOT overwrite an existing `.c`, so a stale one mis-places everything — `docs/matching-cookbook.md:704-710`
- A flat blob's leading data word before code fights `section_order` → emit it as a no-dot `rodata` subseg; `build_path` must match the Makefile's object rules — `docs/matching-cookbook.md:1091-1096`, `:36731`
- Ghidra's raw-binary auto-analysis finds only the `jal`-reachable subset — seed it with splat's validated boundaries (`DefineFunctions.java`) — `docs/matching-cookbook.md:1113-1116`
- Call-graph BFS FAILS on overlays that dispatch through function-pointer tables; use a linear partition bounded by a validity-based `detect_code_end` — `docs/matching-cookbook.md:970-976`
- Function-boundary rule for a linear sweep: the first `jr $ra`(+delay) at/after all forward branch targets; non-contiguous bodies are the inherent residual — `docs/matching-cookbook.md:970-972`, `:975-976`
- Game-code dedup is SOURCE-LEVEL, not an object swap — the linker cannot excise bytes interior to an object, so author the body once as a macro and instantiate it per site — `docs/matching-cookbook.md:945-950`; `docs/how-to-ai-decomp/10-integration-and-propagation.md:38-39`
- Dedup value lives among peers that share a LOAD ADDRESS (134 overlays at one vram), not across binaries with different roles; schedule highest reach × size first — `docs/matching-cookbook.md:929-931`, `:968`; `docs/how-to-ai-decomp/03-bootstrap-order.md:94`
- `h_norm` should be self-consistent, NOT a byte-exact replica of another tool's normalization — the byte gate is the acceptance, so chasing the third-party tool's own inconsistencies is low-value — `docs/matching-cookbook.md:965-968`
- Collapsing duplicates whose members are already individually matched has no recovery value — leave the dedup backlog alone; propagate deliberately — `docs/how-to-ai-decomp/10-integration-and-propagation.md:64`
- Never `git add -A` in a tree with a live reverse-engineering database (or a dirty gate) — commit the named files; DB rename churn is noise — `phase-ends/DIGEST.md:193` (R23); `docs/matching-cookbook.md:6827`
- A draft's inlined scalar `typedef` is a C89 REDEFINITION error — a compile fail, not a byte miss; strip them and keep the types in `common.h` — `docs/matching-cookbook.md:1042`, `:1344`, `:2759-2760`
- A standalone match is not a bank: the single-TU build rejects bodies on conflicting shared-symbol extern types; recover by unifying widths/signatures, don't redraft — `docs/matching-cookbook.md:1660`, `:2496`; `docs/wave-playbook.md:356-395`
- Parallel-draft + an incorruptible deterministic byte-gate scales blind drafting safely (resident 1.4% → 71.7% in one session); agent over-claims cost nothing — `docs/matching-cookbook.md:983-1010` (§12)
- The non-4-aligned-overlay gotcha (`bin` subseg carve + `.incbin` asset rule + `objcopy --set-section-alignment`), ≈75% of the fleet — `docs/matching-cookbook.md:1098-1106`
- Two binaries with the SAME sha1 are one target: `src/ov_B/ov_B.c` can `#include "../ov_A/ov_A.c"` and inherit every match from one source — `docs/matching-cookbook.md:1134-1136`
- Detect `-O0` by the frame-pointer prologue signature `21F0A003` (`addu $fp,$sp,$zero`); opt level is a property of the FILE — `docs/matching-cookbook.md:274-276`, `:1521`; `docs/cookbook-index.md:24`
- Pin the compiler/assembler/flags by evidence from the binary; never inherit a sibling's triple; expect per-module variation — `docs/how-to-ai-decomp/03-bootstrap-order.md:22-25` *(C1 above sharpens the ordering of its two clauses)*
- "The engine holds a bytecode script VM" was false — it is compiled-MIPS dispatch; a written determination replaced a phase of work — `docs/retrospective.md:22`; `docs/how-to-ai-decomp/12-failure-museum.md:11` (exhibit 3)
- A tool that writes a placeholder and exits 0 on missing input is the R43 failure class — *(origin visible in this slice: `Phase10.md:81-82` installs exactly that behaviour deliberately, for the not-yet-existing second-binary sig file)* — `docs/how-to-ai-decomp/12-failure-museum.md:16` (exhibit 8); `docs/decision-log.md:769`
- A report tool silently crediting binary A's linked libraries to binary B (`progress.py` before `linked_subsegs()` was scoped) is the assert-the-denominator class — `phase-ends/DIGEST.md:224` (R41); `docs/how-to-ai-decomp/12-failure-museum.md:33` (exhibit 25)
- Census the corpus shape with instruments verified against a disagreeing oracle, with a known-true case checked first, before choosing a strategy — `decomp-architect/corpus/decomp-kernels.md:108-118` (DK-8); `docs/how-to-ai-decomp/03-bootstrap-order.md:27-40`
- A deferral/exclude list records what the TOOLING could not do on the day it was written, not a property of the functions — *(this slice labels its deferrals "low-value" at `Phase8.md:28,44`, which is precisely the property-claim G38 forbids)* — `decomp-architect/templates/registry-E.decomp.md:243-247` (G38); `docs/how-to-ai-decomp/12-failure-museum.md:28` (exhibit 20)
- Renaming is byte-neutral — a type or symbol name emits no code — so naming/RE work never risks the byte gate — `docs/matching-cookbook.md:2568`, `:5012`, `:29834`
- A verdict is the table with every row accounted for ("zero UNEXPLAINED"), not a headline percentage — `docs/accelerators.md:805`; `docs/retrospective.md:55`

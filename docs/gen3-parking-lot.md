# Gen3 Parking Lot — asset export / native rebuild (speculative; NOT in scope)

> The evolvable docs/-layer home for Gen3 ideas (`PROJECT_CONTEXT.md` is static/permanent — P1 — so
> its "Gen3" + "Parking Lot" sections can't be appended to; this file is where Gen3 speculation and
> its supporting findings accumulate). **Gen3 is PARKED** per the roadmap: do not start until Gen2 is
> substantially matched. Recorded 2026-07-01 at Drew's request, after a "could we export the town mesh
> / Musashi model and rebuild it in Unity?" discussion + a read-only survey of the current state.

## The idea
Export BFM's 3D assets — location/town **meshes + textures**, and **character models** (Musashi et al.) —
and rebuild / inspect them in **Unity** (or any modern engine). This is *enabled by* the code decomp but
is a **separate axis** from it (the decomp byte-matches CODE; this interprets DATA). None of the
asset-export tooling exists yet.

## Current state — what we ALREADY have (VERIFIED 2026-07-01, read-only survey)

**Rendering = stock PsyQ libgpu (understood).** The game builds primitives with `SetPolyF3/F4/FT3/FT4/
G3/G4/GT3/GT4`, manages ordering tables (`AddPrim`/`CatPrim`/`NextPrim`/`TermPrim`/`DrawOTag`/`DrawSync`),
all byte-matched/linked (Phase 7/8). So on-screen geometry is standard PS1 polys (flat/gouraud,
textured/untextured tris & quads) with vertices/colors/UVs/tpage/clut.

**Model data = the libgs TMD path IS used (the key positive finding).** Verified by real `jal` call
sites in the disassembly — not grep-count speculation (R14):
- `jal GsMapModelingData` (maps/relocates a **TMD** in RAM) in the EXE model subsystem —
  `func_8001C214 / C320 / C4A4 / C5B8 / C810 / C924 / C97C` clustered at ~`0x8001C2xx–0x8001C9xx` —
  **and in ≥1 overlay** (`ov_SC02_005/func_801871E4`).
- `jal GsLinkObject5` (link a TMD → a texture-mapped GsDOBJ) in `func_8001C320 / C5B8`.
- ⇒ BFM's model data is **TMD (or GsMapModelingData-compatible)** — a **documented Sony format**. This
  makes static geometry substantially more exportable than a fully custom format would.

**Animation / scene mgmt likely CUSTOM.** No call sites found for `GsSortObject*`, `GsInitCoordinate2`,
or `GsGetLws` (the libgs LWS/TOD animation + auto-sort path). Read: the game uses libgs for **model data**
but a **custom sort/draw loop and custom animation** on top. ⇒ static town geometry (TMD) is the easy
case; **animated characters (Musashi) are harder** (bespoke skeleton + animation format to RE).

**Textures — the tractable half.** The upload/handling path is named (`LoadTPage`/`LoadClut`/`GetTPage`/
`GetClut`/`SetDrawTPage`/`DumpTPage`/`DumpClut`). PS1 textures live in **VRAM** (1024×512 16-bit; texture
pages + CLUTs), so a **VRAM dump → texpage/CLUT decode → PNG** rip needs no full format RE, and PCSX-Redux
is already wired (Phase 3). The **type-0 PAC entries** (301 extracted `.0` "graphics" blobs, each with a
`+0x08` dimension/format param — see `formats.md`) are the prime TIM-candidate source.

**Data is all extracted; WHERE a town's geometry lives is TBD.** Every raw byte is on disk
(`extracted/retail/SCxx.CD.dir/...`). Candidate geometry/texture blobs: **type-0** (301, "graphics"),
**type-7** (139, uninterpreted `.7`), and possibly the **type-4 overlay data tails**. Which blob holds a
given town's TMDs is unknown — trace it from a `GsMapModelingData` caller's source pointer.

**Tooling: NONE.** No TIM/TMD/mesh decoder or exporter in `tools/`; `formats.md` has zero geometry
coverage (only disc-sector "geometry"). This is greenfield.

## Difficulty read
| Target | Difficulty | Why |
|---|---|---|
| **Town textures** | **Low** | VRAM rip (no format RE); type-0 "graphics" blobs; harness exists |
| **Town static mesh** | **Medium** | TMD is documented; locate the blob + confirm stock-TMD vs a Square tweak, then decode |
| **Musashi character model** | **High** | Skinned + **custom** animation (no libgs LWS) — bespoke skeleton/anim format on top of the mesh |
| **Unity rebuild (static)** | **Low–Med** | Import glTF/OBJ + PNG; handle fixed-point→float, handedness, unlit/vertex-color + affine→perspective |
| **Unity rebuild (animated)** | **High** | Needs the recovered rig + anim export |

## Decisive next probes (in order, WHEN we pick this up)
1. **VRAM texture rip first** (quick, high-reward): PCSX-Redux VRAM dump at a town → decode texpages/CLUTs → PNG.
2. **Trace a `GsMapModelingData` caller** (Ghidra) → find which loaded blob/offset the TMD is read from → **locate town geometry on disc** (map the type-0/7/overlay-tail question).
3. **Confirm stock-TMD vs Square variant**: parse a candidate blob as TMD (header id `0x41`, flags, primitive list); a stock TMD decodes with existing PS1 tooling.
4. **Write a `TMD→glTF/OBJ` exporter + `TIM→PNG` converter** (`tools/` — leverage existing PS1 TMD/TIM knowledge).
5. **Unity import** + the PS1-ism handling above.
6. **Animated (Musashi)**: RE the custom skeleton + animation format (separate, harder sub-project).

## Related Gen3 / parking-lot items (from PROJECT_CONTEXT.md, kept here for continuity)
- Shiftable build; **asset repack** (LZSS recompression becomes real here — a standing Gen3 problem).
- **Native recomp / PC port** (the original psxrecomp ambition, properly sequenced).
- Randomizer-grade tooling; JP/proto as extra splat versions; text/translation tooling; decomp.me preset;
  frogress/decomp.dev dashboards; the public flip (Phase 14, deferred to Gen3+).

## Honest caveat
This is speculation + a survey, not committed RE. The load-bearing new fact — **BFM uses libgs TMD model
data** — is byte-verified (real `jal` sites). Everything downstream (which blob, stock-vs-variant, the
exporter, Musashi's anim) is **unstarted** and belongs to a future Gen3 effort. The decomp is the enabler:
the matched renderer + the located call sites are the format spec.

---

# Native PC port — the recomp architecture (PsyQ→Vulkan HLE boundary)

> Spitball with Drew, 2026-07-08 (during a T5b wait). The fleshed-out "native recomp / PC port" parking-lot
> item. **PARKED — Gen3.** Not committed; captured while fresh (R30). The key architectural insight is the
> **PsyQ-SDK HLE boundary**, which is what makes a PS1 port tractable rather than "write another emulator."

## The idea
A **native PC build** of BFM via a **static-recomp front-end** for the game's MIPS code + a **PsyQ-SDK
HLE layer** on modern backends (**Vulkan** for the GPU, an audio lib for the SPU, native FS for the CD).
Distinct from the asset-export axis above (that interprets DATA; this makes the CODE run natively).

## The key insight — HLE the SDK API, not the hardware
A naïve PS1 recomp is hard because you end up re-emulating the GPU at the command/register level (the
emulator problem). **But BFM never touches GPU registers — it goes through the PsyQ SDK** (libgpu
`GsSortObject`/`DrawOTag`, libgte `RotTransPers`, libspu, libcd). The SDK is a **finite, documented API**,
and **we've already isolated it byte-exact** (Phase 7/8 linked libgpu/libgte/libspu/libcd from the real
PsyQ 4.0 objects; we know precisely which addresses are SDK vs game code). So reimplement the **API**, not
the **hardware** — Wine/Proton-shaped, not emulator-shaped.

**Our decomp already draws the exact boundary:** every function is partitioned "game code (matched C)" vs
"PsyQ library (linked object)." That split **IS** the "translate vs HLE" partition — Phase 7/8 hands the
port its function partition for free. So: **game code → static-recomp** (or use our decomp'd C where it
exists); **PsyQ SDK → replace with the Vulkan/audio/FS HLE layer** (don't translate it).

## Three architectures (and the winning hybrid)
- **A — full static recomp** (N64Recomp-style): translate ALL MIPS + emulate the GPU at command level. Hard;
  re-does emulator work.
- **B — PsyQ-HLE port (this idea):** game code recomp'd/decomp'd, boundary cut at the SDK, HLE'd on Vulkan.
  The sweet spot.
- **C — decomp port:** compile our matched C native + a PsyQ shim — converges with B (both need a PsyQ
  reimplementation).
- **Hybrid (the winning move):** a recomp front-end boots a native build **far sooner than a 100% decomp**,
  then the **decomp incrementally replaces** recomp'd functions with readable C (recomp-now, decomp-forever).
  This is the N64 world's proven pattern.

## Hard parts (honest)
- **Overlays — the #1 PS1 gotcha, and BFM is overlay-heavy** (134 overlays streamed to `0x80128158`). Static
  recomp hates "same address = different code over time." N64Recomp handles it by recompiling each overlay
  separately + dispatching on which is loaded — and **we've already mapped every overlay boundary + the
  loader state machine** (Phase 3), so this is derisked *for us specifically*. This is the biggest reason our
  recomp is more feasible than a cold one.
- **GPU HLE (biggest single chunk):** walk the OT in `DrawOTag`, translate each primitive (`POLY_FT4`, …) to
  Vulkan. Choose fidelity — replicate PS1 quirks (affine warp, OT painter's-algo, 15-bit dither) *or* "fix"
  them (perspective-correct, hi-res). DuckStation's hardware renderer = a *reference* for the mapping.
- **GTE:** mostly free via libgte HLE, **except** BFM uses inline GTE macros (`gte_rtps` → raw cop2; why our
  import auto-detects GTEMAC + `gte_macros.inc`) — those cop2 ops land in recomp'd game code → still need a
  small **software GTE** (fully documented, a few hundred lines).
- **SPU + CD:** HLE libspu (SEQ/VAB) + libcd → read our extracted assets. The CD loader is **already RE'd**
  (Phase 3), so the streaming state machine maps to a file/event model.

## The gap + the reusability sleeper
- **No mature PS1→PC static recompiler exists** the way N64Recomp does (the PS1 world went the emulator +
  per-game-decomp routes). Drew's own **psxrecomp** (rocky v1–v3 post-mortem) is the closest prior art.
  ⚠️ **Verify via web before committing** (X2/R17) — check for recent experimental MIPS-R3000/PS1 static-BT
  efforts or anyone extending N64Recomp's `RabbitizerLib`/`N64ModernRuntime` toward R3000.
- **Reusability:** because ~every PS1 game used PsyQ, a **PsyQ-HLE + MIPS-R3000-recomp toolkit generalizes to
  the whole PsyQ library** — "N64Recomp for PS1," a genuinely new community tool + a Gen2-public-flip hook.

## Sequencing
Gen3, parked — do NOT fork Gen2 focus. This capture **is** the architecture decision to revisit at Gen3:
*port architecture = PsyQ-SDK HLE boundary on Vulkan; recomp front-end for early boot, decomp replaces
incrementally; overlays per-N64Recomp; reuses the Phase-7/8 SDK partition + the Phase-3 overlay/loader map.*

## Also worth noting — C++ vs C# (from the same discussion)
- **C++** = natural port target: closest to the decomp's C (structs/unions/pointer-math/manual-memory carry
  over ~mechanically), best perf, direct graphics/audio interop. Port native first, modernize incrementally.
- **C#** = a *reimplementation* character (pointer arithmetic/unions fight the managed model) using the decomp
  as an executable spec/oracle — the Unity-remake route. Valid, more freedom, much more work.
- The decomp enables both; C++ is pragmatic, C# is the "remake."

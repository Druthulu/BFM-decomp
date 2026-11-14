# PS1 decomp struct counts and dedup practice (SOTN, FF7, Silent Hill, others)

task: Brave Fencer Musashi struct-count question: typical struct counts in mature PS1 decomps and how fragments get merged into real types
agent: retriever-web
tags: struct, dedup, sotn, ps1, decomp-practice, web

## Answer
No public PS1 decomp I could check documents a struct-count target, and none states "about 200 structs" for a comparable Square title. The best-documented example (Castlevania SOTN) has roughly 70 `typedef struct` in `include/game.h` alone, plus a large per-entity family in `include/entity.h`. Its dedup method is not "merge fragments into one big struct"; it is per-entity-type `ET_*` layouts hung off a shared `Entity.ext` slot, reuse of one layout by aliasing, and address-named placeholder types for unidentified code. I found no project that documents typing the base pointer as the main dedup mechanism, though the OoT tutorial (old mirror) describes the same idea informally.

## Findings
- SOTN (Xeeynamo/sotn-decomp, README fetched 2026-11-13): matching decomp of PS1/PSP/Saturn versions. Has docs/ with NAMING.md and STYLE.md, plus CONTRIBUTING.md and a wiki decompilation guide.
- SOTN include/game.h (raw file fetched 2026-11-13, summary by small model, approximate): about 70 typedef structs (64 anonymous, 6 tagged). Main ones: Entity (0xBC, `Ext ext` at 0x7C), PlayerState (0x3D0), PlayerStatus (0x334), SaveData (0x11CC), GameApi (0x140), GpuBuffer. Variant handling elsewhere: shared fields reused with comments ("used as an Entity for maria").
- SOTN include/entity.h (fetched 2026-11-13; read was truncated at 100k of 128k chars): `ET_<Kind>` typedefs overlay the ext area from 0x7C, e.g. ET_Bat, ET_Ghost, ET_Demon. Estimated 200 to 250 typedefs in the read portion (unverified).
  - Shared layout by alias: ET_Galamoth "shares its layout with ET_GurkhaHammer".
  - Unidentified: address-named types (ET_801D0B40, ET_8016D9C4) and numbered ones (ET_WeaponUnk006).
  - Unions only for compromises: ET_FireDemon union, commented "This union is a compromise."
  - Placeholder: ET_Placeholder union of 0x3C arrays, "No code should be merged which uses them."
  - Padding to full size with `s32 : 32` or `pad[...]`; `#ifdef PLATFORM_64BIT` `_align_*` pads to keep 32-bit offsets.
- SOTN docs/STYLE.md (fetched 2026-11-13): use types.h; typedef all structs; struct types PascalCase, members camelCase; pointer goes on type (`s32* var;`); offset comments.
- SOTN docs/NAMING.md (fetched 2026-11-13): placeholders use prefixes `func_`, `D_`, `Unk`; "the initial priority in decompiling is functionality (rather than readability)"; "If you are not sure what something does, it is better to leave it unnamed than name it wrongly" (STYLE). NAMING.md itself covers only player/entity/state names, not struct merging.
- Zelda OoT tutorial (old commit mirror, git.new.deadbsd.org, not current upstream; fetched via search 2026-11-13): unknown fields get char-array padding that is gradually replaced with real fields; changing the Init prototype's first arg to the actor pointer type lets the compiler use real fields. This is the base-pointer typing method, stated for N64.
- Final Fantasy VII (Xeeynamo/ff7-decomp README, fetched 2026-11-13): no struct count or typing guidance; links to CONTRIBUTING.md; bans LLM-generated decomp code.
- Silent Hill (Vatuu/silent-hill-decomp README, fetched 2026-11-13): 43/43 game map overlays matched; one line: raw data "needs to be parsed into proper C structs." No count.
- MGS (d3nwah/mgs_reversing README, fetched 2026-11-13): no struct guidance, Discord #metal_gear_dev. No count.
- Legend of Mana (celophi/lom-decomp): reported 100% matched NA and JP (search snippet, not fetched). Wiki exists at github.com/celophi/lom-decomp/wiki; not read, so no struct data.
- Not found: public decomp repos for Legend of Legaia, Parasite Eve, Vagrant Story (rood-reverse named in a PC port README, repo not located), Tomba (TombaRecomp is static recompilation, not decomp). Spyro: ThirstyWraith/spyro-1 and OpenPETE, no struct docs read.

## Dead ends
- Generic decomp CONTRIBUTING searches returned N64/GC projects (MM, ISLE, Prime), not PS1.
- sotn-decomp `include/` directory listing: no struct docs there.
- Legaia and Parasite Eve searches returned nothing relevant.

## Method caveats
- Struct counts come from a small model summarizing fetched pages, not from grep. Reproduce with: `grep -c "typedef struct" include/*.h` on a clone of sotn-decomp.
- The 200-to-250 figure for entity.h is from a truncated read.

sources:
- https://github.com/Xeeynamo/sotn-decomp (fetched 2026-11-13)
- https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/master/include/game.h (fetched 2026-11-13)
- https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/master/include/entity.h (fetched 2026-11-13)
- https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/master/docs/STYLE.md (fetched 2026-11-13)
- https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/master/docs/NAMING.md (fetched 2026-11-13)
- https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/master/CONTRIBUTING.md (fetched 2026-11-13)
- https://git.new.deadbsd.org/falso/mm/raw/branch/main/docs/tutorial/beginning_decomp.md (search snippet, fetched 2026-11-13)
- https://raw.githubusercontent.com/Xeeynamo/ff7-decomp/main/README.md (fetched 2026-11-13)
- https://github.com/Vatuu/silent-hill-decomp (fetched 2026-11-13)
- https://github.com/d3nwah/mgs_reversing (fetched 2026-11-13)
- https://github.com/celophi/lom-decomp/wiki (search result, 2026-11-13)

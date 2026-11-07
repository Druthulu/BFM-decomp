---
ts: 2026-11-06T12:01:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cNsbgx9ogtJ4taCUZ4r8
---
Target: at 3618 `addiu s5,sp,292` and 361c `addiu s6,sp,296`. Mine: s6,292 then s5,296. So the target's &m2 (sp+292) → s5, &m3 (sp+296) → s6. Mine: &m2 → s6, &m3 → s5.

Hmm wait, that's the *preheader* address setup. Hmm, these are the &m2/&m3 addresses (from the launders/dead resets). In the target they're rematerialized at each use site, so why are they in s5/s6 in the preheader? Maybe these are different: sp+292 and sp+296.

Anyway. This is global-alloc ordering.

Given the complexity, and that this is a global-alloc priority tie (documented as needing zero-byte sliders), item 3 is likely a WALL too. But let me try a couple of the structural real-C ideas:

1. The "my set before the if" restructure.
2. Swapping the y0/y1 loads.

Let me look at the target's FT3 arm y-handling to see the exact structure. Let me find the region with the y compare (after the x compare). Search for `lh` with offsets 2,6 in the FT3 arm. Let me grep the disassembly for "lh" lines.

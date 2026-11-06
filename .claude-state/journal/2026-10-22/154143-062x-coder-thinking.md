---
ts: 2026-10-22T21:41:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WZwlO2wYyKPmKIyUtWzQ
---
The difference: `li v0,-64` comes before `sw ra` in mine; target has `sw ra` first, then `li v0,-64`.

So it's an ordering between the `li` (from the loc.a.raw[2] = -0x40 store) and `sw ra`. sched2 moved the li up past sw ra.

Ideas:
- init at decl: `S16_SC02_005_8017F7CC loc = { ... }`? The struct has a union/raw. Hmm.
- Move the `loc.a.raw[2] = -0x40;` statement after the `loc.b` copy? That changes order.
- Make the value -0x40 come from a variable (born later).
- Reorder the stores: currently raw[0]=0, raw[2]=-0x40, b=D_801E2DD8. Target order in asm: sh zero,16; sh v0,18; then the lwl/lwr copy.

In mine: li v0,-64; sw ra; sh zero,16; sh v0,18. So the li got hoisted above sw ra and the zero store.

Try:
c1: swap the two raw stores: raw[2] first then raw[0].
c2: `s16 m = -0x40;` then raw[2] = m.
c3: init at decl: `S16_SC02_005_8017F7CC loc = {0};` then set fields? changes.
c4: write both raw stores as a single s32 store? changes asm.
c5: move the `loc.b` copy first? changes asm.

Since item 2 was cracked by init-at-decl, let me try the analogous: `S16_SC02_005_8017F7CC loc = { 0 };`? Hmm, need to know the struct. Let me look at S16_SC02_005_8017F7CC.

Actually simpler first: try c1 and c2 and a couple more, cheap.

The key mechanism: the `li` is hoisted above `sw ra` — sched2 chose the li over sw ra. To keep sw ra early, it needs to be "ready" earlier or the li later. In item 2, moving the stores earlier (init at decl) fixed it because the stores were then before the load.

Here, the `li v0,-64` is already the first ALU insn. Hmm, in the target the sw ra comes BEFORE the li. So in the target, sw ra was scheduled first. Why? Because of the barrier: the barrier is a memory clobber at the top, so sw ra (a MEM) has a memory dependence chain and sched2's potential_hazard picks it first.

Plain C: make a memory op come first? The stores `sh zero,16(sp)` etc. are memory ops but come after.

What if I make the `loc` initialization happen via a struct initializer at declaration, so the stores are at the decl point (which is before the barrier position — i.e., the top of the block)? In item 2 that worked.

Here `loc` is uninitialized at decl; the stores come after. If I write `S16_SC02_005_8017F7CC loc = {{0}, ...}` hmm — need the struct layout. Let me check the type.

Let me look at S16_SC02_005_8017F7CC in include/struct_types.h.

---
ts: 2026-10-22T21:47:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_n2NBgNRzmfzQhWmc6Isb
---
g1 = 14. So the tail size matters (12 bytes vs 8). With `s32 tail[2]` (8 bytes) the frame/layout matches the target; with 12 bytes it doesn't.

Interesting: with tail[2] (8 bytes at sp+20..27), the frame is 16 bytes for locals (sp+16..31) — the b write at sp+24..31 stays within the frame (ra is at sp+36, s0 at 32). So the write at sp+24..31 is within the 16-byte local area but beyond `tail` — it spills into the top 4 bytes of the local area which is otherwise the struct's b member in the original.

Hmm, so with tail[2] at sp+20..27, writing 8 bytes at sp+24..31 writes 4 bytes past tail. It works because the frame has room (the original struct was 16 bytes).

I could declare `s32 tail[2]; s32 tail2[1];`? That's 12 bytes → same as g1 (14).

OK, e1 it is. It's a scratch artifact; the notes will explain.

Hmm, but wait: is e1 acceptable as a "real C move"? It's a local declaration layout change (decl order/scope, widths) — within the catalog. The out-of-bounds store is ugly. Let me reconsider a cleaner formulation: what if the b-copy target is a *separate* 16-byte local at the same offset?

Actually: what if I keep `S16_SC02_005_8017F7CC loc;` (16 bytes, at sp+16..31) and just initialize the two s16s via a separate initialized local? No — the stores must be at sp+16/18.

Alternative: declare `loc` with a partial initializer using a *nested* designator on the u8 array? Not possible for s16 stores.

I'll take e1. It scores 0 and is lever-free.

Actually, hold on. Let me reconsider the semantics: writing 8 bytes at sp+24 when the local area is sp+16..31 — the write covers sp+24..31, which is within the frame's local area. Fine at runtime. In C terms it's OOB of `tail`, but this is a decomp artifact and the notes will say so.

Hmm, I could make it in-bounds by declaring `s32 tail[2];` and writing at `(u8 *)tail + 4` = sp+24..31 — tail is sp+20..27, so +4..+11 still exceeds by 4. Same.

What if the order were `s32 head; s16 loc16[2];`? Different offsets.

OK, accept e1. Actually wait — one more: what about `u8 tail[8]` and writing at +8 where tail is placed at sp+16 and loc16 after? No.

Let me finalize with e1. Set win.c = e1, clean up, write notes + results + moves line.

Time: 16:04. Item 3 took 23 min, 35 tries. Good.

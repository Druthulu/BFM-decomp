---
ts: 2026-11-06T09:36:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uh5PMRlYalE6lPq36Pvz
---
Oops, B4 is wrong: `sp10[0] = p[0] + ...` assigns a word (s32) at sp10[0], which spans bytes 0-3, whereas the original stores a halfword at offset 2. That changes semantics (offsets 0-1 would be clobbered). Not acceptable as a real-C move. Let me replace B4 with a pointer-based variant: use a `s16 *sp = (s16*)sp10;` and `sp[1] = ...`, `sp[3] = ...`, `sp[5] = ...`. That preserves offsets (s16 index 1 = byte 2, 3 = byte 6, 5 = byte 10). And the call still uses (s32)sp10.

Let me rewrite B4.

Also B3 == B0 currently (identical). Let me make B3 a width variant: `s32 t` instead of s16 t. But the DECL strings have `s16 t;`. I'd need a replacement. Let me handle B3 by post-replacing "s16 t;" with "s32 t;" in the generated text. Hmm, but `t` is used in `*(s16*)... = t` and `unk100 = t`; making it s32 changes codegen slightly (probably not). It's a legitimate real-C variant.

Let me restructure: BODY has B0,B1,B2,B4(pointer) and a flag for width. 6 decl × 5 = 30.

Let me rewrite the file.

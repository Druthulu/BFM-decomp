---
ts: 2026-10-22T07:36:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_NfKWqPLmdbzEwc6FQQ4D
---
SCAN is the only macro-ish item, and no shard has scored it yet.

Let me try scoring it directly: delever_search --try <tu> SCAN <file> --body. It will probably fail (no function named SCAN). Let me test with the macro text as the body.

Actually — maybe the right approach: the "body" for a macro item is the macro definition, and the scorer splices it into the TU (replacing the macro definition text). delever_search's body_span looks for the function named SCAN in the TU — for a macro, `func_8018D98C` is the containing function. Hmm.

Let me just try it and see what happens.

First, create the candidate: the SCAN macro definition with the "launder" removed. But what IS the launder in SCAN?

Let me re-read the SCAN macro:
```
#define SCAN()                                                                \
    e = D_801202A0;                                                           \
    i = 0;                                                                    \
    do {                                                                      \
        if (*(u16 *)e == 0x318 && e != (u8 *)a0 &&                            \
            (*(s16 *)(e + 0x70) == 0 || *(s16 *)(e + 0x70) == 6) &&           \
            *(u16 *)(e + 0x34) == 6 && *(s32 *)(e + 0x1C) < 0x11) {           \
            *(s32 *)(e + 0x1C) = *(s32 *)(e + 0x1C) + 0x10;                   \
        }                                                                     \
        e += 0x10C;                                                           \
        i++;                                                                  \
    } while (i < 0x60);
```
No asm here. Hmm.

Hmm, so the census's "launder" for SCAN might be about the `e = D_801202A0;` — an address assignment that the census classifies as a launder? Hmm, the census classifies lever kinds from the source text (e.g. `__asm__` = launder/pin, `volatile` = barrier, macros = keepalive...). "launder" sites in the census might include address assignments?

Hmm, but the census would need an explicit lever marker. Hmm.

Given the ambiguity, maybe the practical approach: the SCAN macro's launder is the ZERO-EMISSION LAUNDER mentioned in the comment (the D_801C8344 one) — but that's in CHAIN/LAST, not SCAN.

Hmm, hold on. Let me look at the NOTES.md in the src tree (the comment says "see NOTES.md"). Maybe there's a NOTES.md next to the TU explaining the levers, including for SCAN.

Let me look for src/ov_SC06_033/NOTES.md or similar.

Actually, since the tree's TU is what matters, let me look at the census classification: maybe I can find the census entry for (tu, SCAN). The census cache dir may have per-TU JSON. Let me search the census cache for "8018D98C".

Let me dothat.

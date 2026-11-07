---
ts: 2026-11-06T09:36:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4hlcqDAPdDdEkqFHUqnw
---
Item 4: 30 tries, best 8 → WALL.

Now item 5: 30 variants. Let me write the generator.

Body forms:
L0: original
L1: t declared before p/q, if/else swapped
L2: sp10 offsets via char* arithmetic `*(s16*)((u8*)sp10 + 0x2)` (same)
L3: rv = sp20; *a0 = rv; rv = (s32)a0; (original) vs rv declared first
L4: p = (u16*)(q - 3) vs p = (u16*)&D_80126CBA - 3

Let me do decl orders (6) × body forms (5).

Body forms (all lever-free, no asm):
B0: original body (q/p/t/sp10, rv=sp20, *a0=rv, rv=(s32)a0)
B1: same but rv=(s32)a0 written as `rv = (s32)(void*)a0;`
B2: if/else inverted: if (*q != 0) {...} else {...}
B3: t declared s32? (t is s16, used in sh) — width variant `s32 t`? t = p[1] + ... then sh — s32 t would store a word? `*(s16*)((s32)sp10+0x6) = t` still truncates. Real width move.
B4: sp10 declared s16 sp10[8]? Then `(s32)sp10` address same; offsets same. Might change codegen slightly. Hmm, `s32 sp10[4]` = 16 bytes; `s16 sp10[8]` = 16 bytes. The casts `*(s16*)((s32)sp10 + 0x2)` still work.

Let me write it.

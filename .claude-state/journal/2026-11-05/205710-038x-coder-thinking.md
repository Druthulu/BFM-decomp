---
ts: 2026-11-06T03:57:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GQtGqbJ1lXVTpD3bMupL
---
unk2E is u16 (unsigned), target uses `lh` (signed load), so the current source uses `*(s16*)` for sign. If I use `((Unkstruct_800B5CB8*)s0)->unk2E`, it'd be `lhu`, not `lh`. So not directly.

But I could define a local struct type with s16 at 0x2E? Can't add types? I can define a local struct in the body? That's a decl change outside the body? The brief says "no signature or decl change outside the body". Inside the body we can add local types? Probably allowed but unusual.

Alternatively cast to a different struct type that has s16 at 0x2E. E.g., there may be `Unkstruct_80126948` etc. But easiest: define a one-off struct in the body:
```
struct S2E { u8 pad[0x2E]; s16 v; };
```
and access `((struct S2E*)s0)->v`. That yields MEM_IN_STRUCT_P=1 for one and 0 for the other. Would cse distinguish? Let me verify GCC 2.7.2 cse's MEM equality: check cse.c rtx_equal_p / hash.

Actually, does the MEM_IN_STRUCT_P flag even exist in 2.7.2? Yes, MEM_IN_STRUCT_P was a macro bit. Let me grep cse.c.

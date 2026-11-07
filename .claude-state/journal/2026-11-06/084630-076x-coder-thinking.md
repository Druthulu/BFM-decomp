---
ts: 2026-11-06T15:46:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Vng2WA276grGY67aAX70
---
Now build c3 from c2: replace the two 6-space post-switch _m launder patterns with dead reset, and remove the m/_v launders with dead resets.

Post-switch pattern:
```
      __asm__ __volatile__("" : "=r"(_m) : "0"(_m));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t8_mac1)
      ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)((s0) + 0x20) + 0x34, _m, (s32)(v10)); }
```
→
```
      ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)((s0) + 0x20) + 0x34, _m, (s32)(v10)); _m = 0; }
```

m/_v block: remove both asm lines and add dead resets after RotTransSV:
```
        { void *m = &D_801C836C;
          s32 _v;
          _v = (s32)v18;
          RotTransSV(m, (void *)_v, &flag); m = 0; _v = 0; }
```
Hmm, but `m = 0` for a void* is fine; `_v = 0` s32.

Let me generate c3 and score.

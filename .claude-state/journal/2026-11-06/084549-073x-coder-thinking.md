---
ts: 2026-11-06T15:45:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_L3PwVIEL4wNZ7X8z88XW
---
Removing all 7 launders gives 176 (711 ins vs 710). That's a big diff — but note the diff is only in the case-7 tail region (insn 627+), where two launders (m and _v) were in the RotTransSV block at 3154-3159, plus the post-switch launders. Wait, the diff shows differences from 627 to 705 — a big chunk. But the score is 176 which counts many mismatches.

Interesting: the non-launder sites (3101, 3128, 3270) already have no launder and presumably match. The launders at 3036, 3051 (case 6) — the diff starts at 627 which is late, so maybe case 6 still matches? Hmm, but those launders are before. Let me check which insns correspond.

Actually the diff at 627+ shows s1/s2/s0 register swaps. This looks like the *post-switch* block or the case-7 tail where the RotTransSV launders were. The register allocation shifted.

Strategy: remove launders one at a time (or in groups) and find which are load-bearing, then crack each with a C0414-style dead reset.

The launder pattern `_m = (s32)&D_801C8344; asm; call(...,_m,...)` — the existing site at 3101 uses `_m = 0;` after the call. So for the launders, adding `_m = 0;` after the call might work (dead reset). Let me test that first: replace each launder asm with nothing, and add `_m = 0;` after the corresponding call.

Sites:
1. 3035-3037: `_m = &D_801C8344; asm; call(...,_m,...)` — add `_m = 0;` after call.
2. 3050-3052: same.
3. 3115-3117: same.
4. 3154-3159: m and _v launders:
```
{ void *m = &D_801C836C;
  s32 _v;
  asm(m);
  _v = (s32)v18;
  asm(_v);
  RotTransSV(m, (void *)_v, &flag); }
```
Here after RotTransSV, dead-reset both: `m = 0; _v = 0;`? Or restructure. Let me first handle the _m launders, and for the m/_v pair, use dead resets after the call.
5. 3243-3245: `_m` launder — add `_m = 0;`.
6. 3257-3259: `_m` launder — add `_m = 0;`.

Wait, the post-switch sites 3270 (no launder) already has no dead reset but matches. Hmm.

Let me build candidate c2: remove all launder lines and add `_m = 0;` after each call that had a launder. For the m/_v pair, add `m = 0; _v = 0;` after the RotTransSV call.

Careful: for site 1, the structure is:
```
        { s32 _m = (s32)&D_801C8344;
          asm...
          ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)((s0) + 0x20) + 0x34, _m, (s32)(v10)); }
```
Add `_m = 0;` before the closing brace: `...)); _m = 0; }`.

Let me write a python script to do these transformations based on the orig text. Since the launder lines are identical for _m, I can replace the two-line pattern:
```
          __asm__ __volatile__("" : "=r"(_m) : "0"(_m));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t8_mac1)
          ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)((s0) + 0x20) + 0x34, _m, (s32)(v10)); }
```
with:
```
          ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)((s0) + 0x20) + 0x34, _m, (s32)(v10)); _m = 0; }
```

And the m/_v block:
```
        { void *m = &D_801C836C;
          s32 _v;
          __asm__ __volatile__("" : "=r"(m) : "0"(m));  // !FAKE: launder ...
          _v = (s32)v18;
          __asm__ __volatile__("" : "=r"(_v) : "0"(_v));  // !FAKE: launder ...
          RotTransSV(m, (void *)_v, &flag); }
```
→
```
        { void *m = &D_801C836C;
          s32 _v;
          _v = (s32)v18;
          RotTransSV(m, (void *)_v, &flag); m = 0; _v = 0; }
```
Hmm, but the dead reset must be immediately after the use. `RotTransSV(...); m = 0; _v = 0; }`.

But wait: m = &D_801C836C is a constant symbol address; the issue here is different — the target wants m opaque? Let me see what the diff says at that region later.

Let me first apply the _m dead resets only (keep m/_v launders), and score. That isolates.

Let me write gen script for this item.

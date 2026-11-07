---
ts: 2026-11-06T11:57:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6XJiHBeKww0Zfh1q0Ugy
---
Big residual (75, 110 vs 94 insns). The lever-free body diverges a lot: the `&blk` direct usage vs the `q` temp changed codegen substantially (16 extra insns).

The source uses `void *q = &blk; RotMatrixZ(ang, q);` — passing q. Using `&blk` directly should be the same, but the register allocation of the blk address differs.

Let me instead keep the q temp (a real C variable) but remove only the asm:
```
{ void *q = &blk; RotMatrixZ(ang, q); }
```
That's still a block with q. That's what the original did minus the launder. Let me redo v0 with q temps kept.

Let me rewrite v0 preserving the structure exactly and only deleting asm statements:

```
    obj = ...;
    ent = ...;
    { register Blk20 *s __asm__("$5") = &D_800AE620; s32 t0, t1, t2;  // pin
      t0 = ...
      ... }
    ang = ...;
    { void *q = &blk; RotMatrixZ(ang, q); }
    vec[0] = ...
    { void *q = &blk; ApplyMatrixSV(q, vec, vec); }
    ...
    { void *q; q = &blk;
      RotMatrixZ(ang2, q); }
```
And remove the standalone barrier lines.

That is v0'. Let me write it.

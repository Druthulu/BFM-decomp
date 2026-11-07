---
ts: 2026-11-06T05:40:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_B3R0PLMp8beVFDsmVebR
---
The win.c is a bare function definition (no file-scope externs; those come from the TU context). For a header item, the externs in the header are at file scope *inside* the header. Hmm, but this example is a TU-level function, not a header.

For my header item, the header content is:
```
extern s32 func_801502EC(s32 e, void *a1, void *a2);
extern s32 func_80150460(s32 e, s32 a1);
extern u8 D_801152A8[];
s32 func_80150170(void *e) {...}
```
The "bare definition" for the win.c would be just the function. But the function uses func_801502EC, func_80150460, D_801152A8 — these are declared in the header (file scope) or already in the TU. If the win.c is spliced in place of the header include, the externs would be lost unless the TU declares them. Does the TU (includer) declare them? They're referenced by the function, so they must be declared somewhere. In the header they're at file scope; removing them might cause implicit declaration warnings/errors.

Since the "bare definition" convention means the function body that will replace the def in the src header, and the src header keeps its externs... Actually for the final fix, the expert will apply win.c to src. The header will keep its externs; only the function body changes. So win.c should be just the function definition.

But my --body test file had the externs and scored 0. If I strip the externs from win.c, would it still score 0 when spliced? The TU context might already have the externs (from other headers). Let me test: strip the 3 extern lines from v_fix2.c and score on all 141 includers. If it works, win.c is truly bare.

Let me create win.c as the bare function and test it.

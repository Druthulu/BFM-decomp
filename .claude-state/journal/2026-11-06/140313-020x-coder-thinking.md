---
ts: 2026-11-06T21:03:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WpnUkNonRdhz7IhsK1Ws
---
I can create a minimal TU:
```
#include "struct_types.h"  // but that's include/struct_types.h
typedef int s32; ... 
```
Actually the project uses common typedefs. Let me check what a minimal standalone TU looks like. cc1_dumps_tu.sh uses -Iinclude -Isrc/shared. So I can write:

```
#include <...>?
typedef signed int s32; ...
```
Better to reuse the existing types. There's likely a types header. Let me see what src/ov_SC01_077/ov_SC01_077_after.c includes at top. But the file is huge; read the first ~40 lines.

Actually the delever engine already compiles the body against the real TU. For pass inspection, I could also use the `--keep` scratch object and objdump it — but that gives final asm, not pass dumps. The diff already shows final asm.

Let me think more cleverly rather than dumping. The question: which pass merges `$4 = andi` + `ang = $4` into `ang = andi`? Let me test with the -dr (rtl) dumps using a minimal TU. Let me construct one.

Minimal TU: I need Unkstruct_80126948 with fields unk44, unk50, unk48, unk3C at correct offsets. include/struct_types.h has it. The TU likely includes it. Let me write:

```
#include "struct_types.h"
extern s32 ratan2(s32,s32);
extern s32 D_801151D4;
extern u8 D_80126C01;
extern u16 D_80126C02;
extern u16 D_80126C06;
extern s32 D_80188654[];
<body>
```
But struct_types.h may need typedefs (s32 etc.) defined first. Let me check its top.

Actually, simpler: use the actual TU header. The file src/ov_SC01_077/ov_SC01_077_after.c begins with includes. Let me read lines 1-40.

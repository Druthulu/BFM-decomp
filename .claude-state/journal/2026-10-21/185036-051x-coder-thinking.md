---
ts: 2026-10-22T00:50:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_qwVm30egzCUHmnuXCZqR
---
The pipeline uses `tools/bin/gcc-2.7.2-psx/cc1` (cc1 directly) with -S-like output (gas syntax) piped through maspsx.py. I can run cc1 myself on a small file and read the assembly output! E.g.:

```
mipsel-linux-gnu-cpp -lang-c -Iinclude -undef ... myfile.c | tools/bin/gcc-2.7.2-psx/cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker
```
This prints assembly to stdout. That's a super-fast iteration loop for designing bodies (no need to score each time; only score the promising ones).

But: is running `tools/bin/gcc-2.7.2-psx/cc1` allowed by the permission classifier? Probably (it's a tool). Pipelines with `|` are allowed (worked earlier).

Note the function body needs the surrounding declarations (D_8011DB28 etc.) — for a standalone test I can write a small file with just the function and dummy externs.

This gives me the assembly listing of my candidate → I can iterate quickly toward the target listing. Excellent.

Let me set this up for item 1. I need the exact target listing (have it) and then craft C.

Let me write a test file: /home/musashi/bfm-decomp/.run/P40/T11/G08b/func_8014C308__func_8014C308/asmtest.c with the function body + needed externs (D_8011DB28 is not used here; this function uses only args).

The function:
```
s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
```
No externs needed. But the .h is included in a TU with other stuff; the function's own code is what matters.

Let me create the test file and compile.

Command:
```
mipsel-linux-gnu-cpp -lang-c -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C .run/P40/T11/G08b/func_8014C308__func_8014C308/asmtest.c | tools/bin/gcc-2.7.2-psx/cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker
```

Let me try it.

---
ts: 2026-11-06T16:31:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2tN3vCr12u3aQcXjbTYO
---
The scratch .c is placed under .run/P36/... so relative includes fail. Copy the TU to my item dir with a directory structure that resolves? Better: copy the scratch TU to a dir one level under src? We can't write to src. But the script accepts a .c file and passes -I"$(dirname)" and -Isrc/shared. The include is `"ov_SC01_084_shared.h"` which is in src/ov_SC01_084/. We could copy the TU to my item dir and add -I via... the script doesn't allow extra includes. But it does `-Isrc`, so include "ov_SC01_084/ov_SC01_084_shared.h"? The TU says `#include "ov_SC01_084_shared.h"` — searched relative to the TU dir and -I paths (include, src/shared, src, dirname). If I copy the TU into a directory and also copy the shared header there, it resolves. Let me do that: put t.c and copies of the includes into $D/dumptu/. Copy the shared header and check what it includes.

Actually simpler: `-I` includes `src` so `#include "ov_SC01_084_shared.h"` won't find it. But I can place the TU under .run/P40/T11/W48/.../dumptu/ and copy ov_SC01_084_shared.h there. Let me check the shared header's own includes.

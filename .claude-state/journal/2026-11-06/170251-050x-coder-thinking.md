---
ts: 2026-11-07T00:02:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RLijnHnREsQpV7SVUwWk
---
So for a header TU, recs are the recipes of the includers. The includer's TU is src/ov_MAIN_012/ov_MAIN_012.c (a real TU). To dump, I can copy that TU and replace the include with my body.

Let me create a spliced TU: read src/ov_MAIN_012/ov_MAIN_012.c, replace the line `#include "../shared/ov/func_8012DBD0.h"` with the contents of win.c. Write to my item dir. Then run cc1_dumps_tu.sh.

But careful: the header is included at line 1274 in the includer. Let me do it.

Also note the TU may include the header multiple times? Only once per the grep.

Let me write a splice script for headers.

Actually, wait: ov_MAIN_012.c may be large. Let me check size and whether cc1 dumps of the whole TU are heavy. It's fine.

Let me do it.

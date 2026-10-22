---
ts: 2026-10-22T12:54:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_XlZeHFwGqPDBDOmK4jyW
---
hdump.sh: `<includer TU> <header basename> <body.c> <outdir> <tag>`. The outdir must be absolute under my shard dir. This dumps the passes including .cse2, .jump2, .dbr etc.

This is a good tool for understanding. But it takes time and disk. Let me use it for item 2 to understand the fold — it will inform items 1, 3, 4 as well.

Let me run hdump for the no-launder candidate (w1.c) and for the orig, and compare the .cse / .reload dumps. Actually the key question: at which pass does the base get folded into the address?

Let me do it: outdir = /home/musashi/bfm-decomp/.run/P40/T11/G16/dumps (absolute).

Includer: src/ov_MAIN_012/ov_MAIN_012.c, header basename func_8012C2D0.h, body w1.c.

Hmm, wait: the header basename is "func_8012C2D0.h" and the include line in the includer is `#include "../shared/ov/func_8012C2D0.h"`. The script replaces that include with the body text. So the body must be the FULL header content minus the include? No — it replaces the include with the body file's content. The body file should be the header's text (the whole header: the externs + the function). Hmm, my w1.c is just the function definition. The include replacement would remove the extern declarations → compile errors.

So the body file should be the whole header text (with the launder removed). Let me create that: take src/shared/ov/func_8012C2D0.h and remove the launder lines → that's the "candidate header".

Let me do that and run hdump for both the original header and the no-launder header, then compare the .cse dumps.

Actually, is this worth the time? The decision I need: is there a plain-C spelling? Understanding the fold tells me exactly what to defeat. I think it's worth ~5 minutes.

Let me do it.

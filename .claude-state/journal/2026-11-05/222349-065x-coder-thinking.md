---
ts: 2026-11-06T05:23:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lEBSMFJGSnk3trCN0v0y
---
Frame 0 in the standalone probe with the exact body! So the 16-byte frame in the real TU is caused by the *context* (the includer TU / the specific instantiation), not the body alone.

Hmm! That changes things. The hdump .s for the real includer had frame 16 with the asm and 0 without. But standalone has 0. So the asm interacts with something in the TU.

Wait, maybe the .frame I read (line 4106) was for a *different* function instance? The header is included at multiple sites? Let me check: hdump replaces the include in ONE TU. But the TU may include the header via another header too, or the same body appears at several member sites (dedup). The `func_80175820:` label appears once (line 4105). Hmm.

Let me re-check: in the real includer, does the nobar .s really have frame 0 at the same function? Yes, I checked line 4106 of dumps_nb/nb.s: frame 0.

So with the exact body standalone: frame 0 (with asm). In the real TU: frame 16 (with asm). The difference must be in the TU context — maybe the include's *surrounding declarations* or the fact that the function is defined inside a block? Or the header is included inside `#include` at a site where the body is preceded by `INCLUDE_ASM`?

Hmm, actually! Maybe the .s I looked at (line 4105) corresponds to the header's instantiation, but the body is included MULTIPLE times in the TU (dedup: one source instantiated at each member's site). The label `func_80175820:` — if instantiated at multiple sites, the function would be defined multiple times (error). So once.

Let me look at the .frame more carefully: maybe the 16 bytes come from a *different* mechanism: the asm is `__asm__("" ::: "memory")` and in the real TU it's inside a function that... hmm.

Wait, maybe the difference is the *source line number* of the asm! In the real body, the asm line is line 18 of the header. In my probe, it's a different line. Line numbers shouldn't matter... unless `-g` debug? No.

Let me look again at the real orig.s around the function to see if the frame is really from this function. Line 4105-4130:
```
4105 func_80175820:
4106 .frame $sp,16,$31 # vars= 16
...
4130 subu $sp,$sp,16
```
Yes.

But my standalone probe with the same body gives frame 0. So something in the includer TU differs. Perhaps the includer TU has `-G0` or different options? Both use the same cc1 flags.

OR: the hdump splice replaced `#include "../shared/ov/func_80175820.h"` with the body, but the includer TU might have *other* code around it that affects the function (e.g., the function is inside a `#pragma` or the TU uses `INCLUDE_ASM`). 

Hmm, let me check: maybe the difference is the *struct definitions in the real TU* are different! The includer might have a different `S_AE7BC_80175820_80175820` typedef with a bigger struct. I grepped engine_types.h and found `typedef struct { u32 *f0; s32 pad[4]; } S_AE7BC;`. But maybe the includer TU defines a *local* struct with a different size? Let me grep the includer TU for S_AE7BC.

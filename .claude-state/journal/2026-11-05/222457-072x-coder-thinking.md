---
ts: 2026-11-06T05:24:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hwblxKh4JtedfpSTgpdS
---
The t4.c is fine. But the .s shows the body deleted! Why? Because... `func_80175820` is declared `s32` and returns 0; the stores to globals should stay. Unless the compiler considers the stores to *undefined* externs as ... no.

OH WAIT. The `__asm__("" ::: "memory")` — the function is the first in the file. Hmm, the .s output for t4 shows the function body as just `#APP #NO_APP` then `j $31; move $2,$0`. So all the memory operations were eliminated. This looks like the compiler treated the function as *unused and static*? It's global, not static.

Hmm, unless the cc1 invocation failed and the .s is from a previous run? No.

Actually — maybe `-fgnu-linker` + `-O2` and the `extern` declarations inside the function... Let me check: is `E0` defined? The pad functions write to undefined externs and they were emitted (`sw $0,E0`). So stores to externs are kept.

So why did func_80175820's body vanish? Let me look at the .err file.

---
ts: 2026-11-06T05:24:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BjsoOoHNduAGSqPXFrab
---
The probe t4 generated NO code for func_80175820 — just `j $31; move $2,$0`. The compiler optimized the whole body away! Because D_800B9A02 etc. are declared extern *inside* the function and... wait, why would it remove the stores? The globals are extern, so stores to `ptr[2]` and `D_800AF634[*q].g0` must be kept... unless the compiler thinks the function is unused/static? No, it's global.

Hmm, `j $31; move $2,$0` — the body vanished. Why? Because the probe's D_800AE7BC etc. are undefined externs... no, that doesn't allow removal.

OH! The probe t4 has the struct types `S_AE7BC` but the body uses `D_800AE7BC` — I declared `extern S_AE7BC D_800AE7BC[];` inside. Hmm.

Wait, maybe the whole function got removed because... it's the *first* function and the `__asm__` with memory clobber... no.

Actually, look: the standalone probe's function emitted only the asm and return. That means the compiler deleted the stores as dead. Why? `ptr[2] = ...` — ptr comes from D_800AE7BC[*q].f0, a global load. Stores through a pointer can't be deleted. Unless... the compiler treats the function as `noreturn`? No.

Hmm, is it because the externs are declared *inside* the function and the file-scope symbols don't exist? Undefined symbols are still external. The stores should remain.

Wait — maybe the probe's function body got mangled by my gen script (a Python string issue). Let me look at the generated t4.c.

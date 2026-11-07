---
ts: 2026-11-06T10:35:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8FHtkGh8GXsk4ZghSti5
---
These two are nearly identical. Kinds: barrier,pin. We need to remove:
- `register void *s0 __asm__("$16")` pin
- `register s32 t __asm__("$2")` pin
- `__asm__("" ::: "memory")` barrier

Let's create a lever-free version. Start with nopin.c = orig with the register asm removed (plain vars) but barrier kept, and a lever-free win.c with all removed. Let's first measure the residual after removing pins only, and after removing barrier only, to know what each lever does.

Let me create variants:
- nopin.c: `void *s0;` and `s32 t;` plain, barrier kept.
- nobar.c: pins kept, barrier removed.
- win0.c: both removed.

Let me write a quick sed script? Better to write the files with Write tool. For func_8018966C: orig is small.

Let me create win candidate for 8018966C.

Actually first do the diagnostic: remove pins only.

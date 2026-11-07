---
ts: 2026-11-06T06:06:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Stk0sJ7B7qkKP7AILcJh
---
Item 1: func_801804A0, 158 lines, kinds launder,pin. The launder is the asm at 3114, pin is s2 at 3011.

Wait, this is a large function. First, understand the setup: copy the current def to orig.c, then create a lever-free version win.c.

The pin is `register u16 *s2 __asm__("$18");` — a register-asm pin. Removing that declaration means s2 is just `u16 *s2;`. That is lever-free (no pin).

The launder: `__asm__("" : "=r"(p) : "0"(&D_801C00D0));` then `func_8012A828(a0, p);`. Lever-free means plain C: `func_8012A828(a0, &D_801C00D0);`.

But wait — the note says "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". Hmm — but here the task is to remove launder levers and use real C. The launder in case 2 site: after the asm, p == &D_801C00D0. So plain C is direct call.

But also case 0 and case 1 already call `func_8012A828(a0, &D_801C00D0);` directly. So the difference in case 2 is that the launder causes a copy. Lever-free body should call directly.

Let me first check the delever_search tool help and how a "body" file is supplied: `--body` means the file contains just the function definition body? Let's look at an example worked dir .run/P40/T10/func_80181F4C/ (notes.md, win.c).

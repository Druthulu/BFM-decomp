---
ts: 2026-11-06T07:34:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jEeZUer3udV6OOfyixwS
---
Interesting! The sed `s/extern void func_800CAF84(void);/extern void func_800CAF84();/` produced `extern void func_800CAF84(arg0);` — because sed's `\1`? No... Oh! `&` in the replacement? No. Wait, the replacement was `extern void func_800CAF84();` — sed interprets `\1`? No. The output shows `func_800CAF84(arg0)`. That's bizarre. Unless the file base.c already had something? Let me re-check: my sed command was:

`sed 's/extern void func_800CAF84(void);/extern void func_800CAF84();/; s/func_800CAF84();/func_800CAF84(arg0);/'`

The FIRST substitution replaces `func_800CAF84(void);` with `func_800CAF84();`. Then the SECOND substitution `s/func_800CAF84();/func_800CAF84(arg0);/` — applies to the line ALREADY modified by the first (sed applies both to the same line in order!). So `extern void func_800CAF84();` became `extern void func_800CAF84(arg0);` — declaring a function with a parameter named arg0 (type int). That's a valid prototype taking one int arg. But the error said "too many arguments" at line 266? With `extern void func_800CAF84(arg0);` the prototype takes 1 arg, so calling with 1 arg is fine. Hmm, but "too many arguments" implies 0 params.

Wait, actually in the scratch TU, line 253 would be `extern void func_800CAF84(arg0);` which in old-style C means one int parameter. The call has 1 arg. Fine.

Unless the first sed's second substitution also changed the declaration line into `extern void func_800CAF84(arg0);` and GCC 2.7 parsed `arg0` as... hmm.

The error at line 266: let me look at the actual scratch. The scratch gets restored after the run, but --keep leaves it? --keep keeps the candidate object, not the TU. The scratch TU is written to the real src path then restored. Hmm.

Let me avoid sed double-substitution confusion: write the variant explicitly. Let me write v33.c with Write: base but with the local extern replaced by nothing (remove the line) and call `func_800CAF84(arg0)`. Earlier v30 (sed removing the line then substituting call) gave "too many arguments" too. With no local decl, the visible decl is the K&R definition at line 88. GCC 2.7 says too many args → so the K&R definition gives 0-arg? That can't be, since func_800CB158 calls with arg0 and compiles (it has `extern void func_800CAF84();` at file scope line 134 though).

Hmm wait: is line 134's `extern void func_800CAF84();` a declaration that takes unspecified args? Yes. So at line 159, calling with an arg is allowed. For our function, if we remove the local decl, the visible is line 88's definition (and line 134's). Should be fine. But it errored "too many arguments". Unless the local decl in orig wasn't removed in v30? Let me check v30 content.

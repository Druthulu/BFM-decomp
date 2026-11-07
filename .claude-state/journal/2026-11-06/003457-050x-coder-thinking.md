---
ts: 2026-11-06T07:34:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_79cJchQaeWmIPWJU1MZO
---
v30 has no local decl, calls with arg0 → "too many arguments". That means the K&R definition at line 88 does NOT give a prototype accepting args? Weird. But wait — maybe the compile uses `-fno-builtin`? No.

Actually! Maybe the issue is the local extern at line 134 `extern void func_800CAF84();` — in GCC 2.7, an empty parameter list in a *declaration* might mean `(void)` in this dialect? No, in C it means unspecified.

Hmm, but the error is "too many arguments to function `func_800CAF84'". That error occurs when a prototype with fewer params is in scope. The only `(void)` prototype was the local one in orig, which I removed in v30. Unless... the body replacement: `--try --body` replaces the definition but maybe it does NOT remove the old body? It replaces the function's text in the TU. Let me verify by checking what line 253 is in the scratch. Let me run v30 with --keep and immediately look at the scratch TU before restore? The scratch is the real src path during compile, restored after. Can't easily.

Alternative: maybe the local extern in the *src* file at line 253 is being merged because the tool extracts the function by name and the "body" file replaces only the inner text? No, --body means FILE holds the function's definition only, replacing the whole definition.

Let me test the hypothesis differently: change the extern to `extern void func_800CAF84(void *);` and call `func_800CAF84((void *)arg0)` — v31 gave "conflicting types" with line 88. So line 88's type conflicts with `(void*)`. That means line 88's definition type is `void ()` — unprototyped! An unprototyped decl conflicts with a prototyped one in GCC 2.7? Apparently yes ("conflicting types for func_800CAF84"). So to call with an arg, use an unprototyped decl `extern void func_800CAF84();`.

v32 produced `extern void func_800CAF84(arg0);` (due to double sed) which is a prototype with one *int* parameter, and calling `func_800CAF84(arg0)` with an s32 arg should be fine... but error "too many arguments" at line 266. Wait, maybe line 266 is NOT the call in v32; maybe it's the line in the scratch where the `extern void func_800CAF84(void);` from the ORIGINAL body still exists? Hmm.

Hold on: v32's line 2 is `extern void func_800CAF84(arg0);`. But the tool might prepend/keep the original local extern? No.

Let me carefully construct v33: replace the local extern line with `extern void func_800CAF84();` and the call with `func_800CAF84(arg0);` — done via two separate sed expressions that don't interfere. Use a different pattern for the call, e.g. `s/func_800CAF84();$/func_800CAF84(arg0);/`. But the extern line also ends with `();` — it would match the call substitution. So do the call substitution FIRST, then the extern? Order matters. Better: use python.

Let me write v33 via a small python edit: replace exactly the two lines.

Actually simplest: take orig.c and do python replacements:
- `extern void func_800CAF84(void);` → `extern void func_800CAF84();`
- `func_800CAF84();` → `func_800CAF84(arg0);`
These are exact-line replacements; python str.replace applies both (the second would also hit the extern line if applied after the first? The extern line after first becomes `extern void func_800CAF84();` which contains `func_800CAF84();` → would become `extern void func_800CAF84(arg0);`). So replace the call FIRST, then the extern (the call line becomes `func_800CAF84(arg0);`, no longer matching `(void)`). 

Let me do that with a python script.

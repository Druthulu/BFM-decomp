---
ts: 2026-11-06T18:47:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hXXTs3nAAAnYwFihxCap
---
The scratch header has no `register` — so my w1 body is there. But the RTL dump showed `(reg/v:SI 7 a3)`. That means the variable a7 got hard reg $7 in the RTL?! That can't be from a plain variable... unless the dump is from an *earlier* scratch (the p3 dir from my earlier item-3 runs? No, this is ov_MAIN_012).

Hmm wait — the RTL `(reg/v:SI 7 a3)` with regno 7. In GCC's RTL dump, a pseudo register with regno >= 16 prints as `(reg/v:SI 76)`. A regno of 7 prints as `a3`. So the RTL genuinely has hard reg 7 for that variable — meaning the *pinned* version was compiled.

Unless the cc1 dump I made used a stale copy: the DUMP_ROOT dump was created from the .c file in p3. But maybe the .c includes `../shared/ov/func_80146750.h` and the cpp -I flags resolved to a DIFFERENT shared dir (the real src/shared/ov/func_80146750.h with the pin)! The cc1_dumps_tu.sh script adds `-Isrc/shared` — so the include `../shared/ov/func_80146750.h` from the scratch .c (which lives in the p3 dir) resolves to the scratch's shared/ov/... or to src/shared? The .c is at p3/ov_MAIN_012_jr_801458E0.c; its include is probably `#include "../shared/ov/func_80146750.h"` → p3/../shared/ov/... = .run/P36/engine/score/ov_MAIN_012__func_80146750/shared/ov/... Hmm, the scratch's shared dir is at p3/shared/ov/. So `../shared/ov` from p3/ = ov_MAIN_012__func_80146750/shared/ov — which may not exist; then the -Isrc/shared path would be searched... The cpp command in cc1_dumps_tu.sh: `-I"$(dirname $tc)" -Isrc/shared -Isrc`. dirname = p3. So `"../shared/ov/func_80146750.h"` relative to the .c file's directory? CPP resolves relative includes relative to the including file's directory: p3/../shared/ov = ov_MAIN_012__func_80146750/shared/ov — doesn't exist. Then it searches -I paths: p3/, src/shared, src. With -Isrc/shared, `../shared/ov/func_80146750.h` → src/shared/../shared/ov = src/shared/ov/func_80146750.h — THE REAL SRC (with the pin)!

So my dump compiled the REAL header (pinned), not the candidate. That's why the RTL has a3. Damn — that's a stale-input trap (the notes warn about this: G08c). The cc1_dumps_tu.sh comment says "-Isrc/shared on the cpp line: a TU's #include "../shared/..." resolves from any directory one level under src/, and a copied TU's own directory is not one". So the dump tool is not faithful for the scratch TU unless the include resolves to the scratch.

I need to dump the *scratch header* directly. Option: create a TU file in my shard dir that includes the scratch header by absolute path? Or run cpp manually with the scratch dir first. Actually, simpler: cc1_dumps_tu.sh accepts a .c FILE; I can create a wrapper .c in my item dir that does `#include "<scratch header>"`? The header is a bare function body with extern declarations — it can be compiled standalone? The header has `extern unsigned short D_8011FD10;` etc. and the function definition. It might need the struct/typedefs? It uses plain types. So I can compile the header alone as a TU!

Let me test: cc1_dumps_tu.sh on the scratch header file directly? It does cpp -Iinclude -I$(dirname tc) -Isrc/shared ... — for a header .h file, cpp would treat it as C. Should work.

But wait — for the *scores*, delever_search handles the header item correctly (it knows the includers and compiles each). The score 3 result is from the real comparison. Only my dump was wrong.

Let me redo the dump with the scratch header as the TU (it has the same body). Actually, the function's codegen doesn't depend on the includer (unless the includer defines something). The header item's score is computed on the includer TUs. For the dump, compiling the header alone should give the same function code (the header has all its externs).

Let me try: DUMP_ROOT=... cc1_dumps_tu.sh <scratch header path> t2b.

Hmm, but the header file's name is .h; the script checks `[ -f "$wd" ]` → yes, treats it as the TU. cpp with -x? It runs `mipsel-linux-gnu-cpp -lang-c ... "$tc"` → -lang-c forces C. OK.

Let me do that.

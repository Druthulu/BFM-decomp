---
ts: 2026-11-06T16:32:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zhuZC4wYwlty33ankF2N
---
When ureg is hard reg (a0) and sreg is pseudo self, it adds a *suggestion* (qty_phys_copy_sugg) to self's qty, not a hard tie. Then find_free_reg prefers suggestions. Since self is a global? Actually self lives in one block? Hmm, self is used in both then and else blocks; local-alloc only handles block-local pseudos. self's uses in each block... The pseudo self spans two blocks, so reg_qty[self] may be -1 (not local) and local-alloc skips it; then global-alloc handles it. But the observed code has a1 for the then and a0 for else — so uses were replaced by the copy source.

Actually maybe it's *flow*'s copy propagation (regmove?) Hmm.

Let me stop theorizing and get the RTL dumps. That's the reliable path. Plan: create a .i from the real TU with cpp, splice candidate body into the .i, run cc1 with dumps, inspect the .lreg (local alloc) and .greg dumps to see where self→a0 happens.

But wait: the body in the .i is macro-expanded (CAST_SIGN etc. appear? The src body uses plain C with struct types; macros like CAST_SIGN appear in other functions). The function body text in the .i should be recognizable. To splice, I can locate `void func_8017EAD8(arg0)` in the .i and the matching closing brace.

Alternative approach that avoids .i: use tools/cc1_dumps_tu.sh with a *copy of the TU* placed in a temp dir inside src/? Not allowed to write src/.

Hmm, but there's another way: cc1_dumps_tu.sh takes a .c file; cpp includes are resolved relative to the .c file's directory. The TU's includes are `#include "../shared/..."`. If I copy the TU to `.run/P40/T11/O05x/<item>/t.c`, then "../shared/..." resolves to `.run/P40/T11/O05x/shared/...` — fails. But cpp also gets -Isrc/shared and -Isrc... the include string is "../shared/ov/..." which is not found via -Isrc/shared. Could I pre-create a symlink? Can't write src. Hmm, I could copy the TU to a subdir of .run and create `.run/P40/T11/O05x/<item>/../shared` -> no.

Simplest: use cpp on the real TU to produce the .i, then splice. cpp with the same flags. Let me write a script dump.sh in the item dir:
1. mipsel-linux-gnu-cpp -lang-c -Iinclude -Isrc/shared ... src/ov_SC05_007/ov_SC05_007_jr_8017BEBC.c > t.i
2. splice body: python script replaces the function definition region in t.i with candidate body.
3. cc1 dumps on t.i.

Let me check the .i: does the function body appear intact? Let me try cpp and grep.

Actually simpler for splicing: instead of splicing into the .i, I can cpp the *whole TU* but with the function replaced by a unique marker via `-D`? no.

Let's do: generate t.i from the real TU, find the function text in t.i (the body is likely identical except whitespace and macro expansions — this function uses no macros), replace between `void func_8017EAD8(arg0)` and the matching closing brace, then cc1.

Let me try.

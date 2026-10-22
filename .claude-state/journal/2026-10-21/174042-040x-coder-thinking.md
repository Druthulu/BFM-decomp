---
ts: 2026-10-21T23:40:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_JZ1lOOnSzR8Z8UVn2yFl
---
The source is right. But the compile produced constants 0. So gcc 2.7's `cse2`/`jump` propagated constants into the function because the function is NOT static and gcc 2.7 has a bug/feature: it "assumes" something?

AH — I know! gcc 2.7's CSE has a feature: "cse.c: find_duplicate_insn" — for a call to an unknown function, gcc assumes the callee may modify globals but NOT... hmm.

Actually the real explanation: **gcc 2.7's CSE assumes that a function whose address is not taken and which has no address-taken... no.**

Hmm, "move $4,$0" means a0=0 at the call. So d was folded to 0, c folded to 0, e folded to 0.

This is CSE propagating the constant 0 into the parameters. Why would d be 0?

OH!!! I think I've got it: the `pad_fn_i` static functions are UNUSED → gcc removed them. But `func_801415C0` is non-static and unused → gcc keeps it. Still no constant folding.

Unless... **the header's `func_800291B4` etc. are actually DEFINED somewhere with constant args**? No, they're extern.

Hmm, hold on: what if gcc 2.7's cse treats the *arguments* of an extern function as constant because of `-fno-builtin`? No.

Let me test: compile the unpadded tu_c1.c directly with the same cc1 and see.

Actually — simpler hypothesis: **gcc 2.7's `jump`/`cse2` "PRE" performed dead-code elimination because the function's result is unused and it's a void function**... but the calls have side effects.

Hmm, but actually: `func_800291A0(d, ...)` — d = 0 because d = b + 0x2F and b = (s16)param_1 and param_1 = 0. So param_1 was constant 0.

Where would param_1 = 0 come from? **Because the function was cloned/specialized by the "constant propagation" of a call site** — but there is no call site.

UNLESS: the .i file has a *declaration* or the function is also defined elsewhere in the TU... no.

OK here's another thought: maybe gcc 2.7 `-quiet` with `-dR` etc. printed the RTL of the function AFTER `expand` had replaced the parameters with... no, expand doesn't do that.

Hmm, but wait: what if the dump/asm corresponds to a *different* function that happens to be named func_801415C0 — i.e., the assembler output's `func_801415C0:` label. And the RTL dump section named func_801415C0.

Let me test with the actual pipeline used by delever_search (which produces a correct compile — the candidate scored 40 with real register allocations). The pipeline is `rec["pipeline"]`. Let me look at what the pipeline is and use it. The difference: maybe my cc1 invocation lacks something like `-fno-...` or the real pipeline uses `-D` flags that matter. Actually! The real pipeline might include `-fkeep-inline-functions` or... hmm.

AH WAIT. I've got it! The real pipeline probably compiles with `-fno-inline` etc. But the key: the real pipeline might NOT use `cpp`+`cc1` on a standalone file — it compiles the whole includer.

Hmm, but constant propagation...

OHHH!!! I think I finally get it: gcc 2.7's **CSE** performs "find_duplicate_insn" on the *call insn* — no.

Let me look at it from a different angle: `move $4,$0` = `movsi_internal2` of const 0 → the arg is 0. So the *pseudo* for param_1 was replaced by 0. In gcc, a function's incoming parameters are `reg:SI 4` (a0) and `reg:SI 5` (a1) at function entry. In the dump, the function's first insn is insn 13 setting a0=0. So a0 (which held param_1) was overwritten with 0 — meaning param_1 was DEAD (unused) at that point! Because b = (s16)param_1 was optimized away... no, b is used.

Unless the flow analysis determined the whole function is dead: the calls to func_800291B4 etc. are to extern functions — gcc assumes they have side effects, so it can't remove them. But it CAN remove the computation of the args if it knows... no, args must be computed.

Unless gcc knows the extern functions never read their args? No.

Hmm, `move $4,$0` — actually maybe the args ARE computed but the compiler proved d==0? d = b+0x2F, b = (s16)param_1. For d to be 0, param_1 = -25.

WAIT!!! What if the params got swapped/aliased weirdly... 

Hold on, let me reconsider: what if this dump/asm is of a DIFFERENT function whose label is func_801415C0 but which is a *static* copy... 

Let me just do a sanity test: compile tu_c1.c (unpadded) with cc1 and look at the asm. If it also gives constants, then something about my TU. If the padding is the problem (e.g., `pad.inc` defines `s32` type? No, s32 comes from include/...).

OH!!! THAT'S IT! `s32` is a type from the project's include headers. My scratch TU doesn't include the prelude that defines `s32`! But cpp succeeded (no error) — because `-Iinclude` and... hmm, if `s32` were undefined, cpp would leave it as an identifier and cc1 would error. But the .i shows `void func_801415C0(s32 param_1, s32 param_2)` — s32 unresolved! So `s32` is an implicit int in K&R C style (gcc 2.7 with -lang-c allows implicit int). So param_1 and param_2 are `int` — fine.

But that's not the issue either.

Hmm, so why constants?!

Let me look at the c1.err file for warnings.

Actually, let me look at the .rtl or .cse dump for the function to see when the constants appear. Let me check .cse2.

Actually — hold on. Let me reconsider the possibility that this gcc-2.7.2-psx build does "function specialization" via the `jump` pass's "cross-jump" and `cse2`'s PRE... no.

Simplest: let me test the unpadded version and also check c1.err.

Actually, actually, actually. WAIT. I bet the padding functions are the culprit in a different way: they're `static` and unused. gcc 2.7 might warn. But more importantly — maybe cc1 processed the file in a weird order.

Let me just test: compile tu_c1.c (unpadded) directly.

Hmm, but cc1_dumps_tu.sh refuses short .i. I can call cc1 myself:
mipsel-linux-gnu-cpp ... then cc1.

Let me instead take a completely different approach to get the allocation table: use the REAL pipeline. The delever_search tool compiles via `rec["pipeline"]` which is the fleet's build command. Let me find the pipeline for this TU and reproduce it with the dump flags.

Let me look at the recipes to get the pipeline. I'll add a mode to my sweep.py to print rec["pipeline"].

Actually, let me first check c1.err.

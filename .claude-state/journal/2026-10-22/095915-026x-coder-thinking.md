---
ts: 2026-10-22T15:59:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_u6hGCYcSK6nkoF3NxvKB
---
The .i at line 43586 has `extern Mat32 D_800AE620;` and line 43601 `src = (int *)&D_800AE620;` — so the .i contains the ORIGINAL launder body, not my c_struct body. So p6's shared header was NOT my body at dump time? But we grepped it and found `*(Mat32 *)m = D_800AE620;` at line 17. Hmm, but maybe the file has *both*: the original body plus my inserted one? Line 17 is the struct copy. Let me print the whole scratch header.

Oh wait — I bet the scratch dir p6 is shared and another process (a concurrent coder or a leftover) rewrote it between my grep and the dump. Or `--keep` p6 is not the dir used; maybe the `--keep` object is p6/cand.o but the TU it compiled was p7? Let me re-grep now and print the file.

Actually more likely: the p6 dir is the *shared* scratch and delever_search uses per-call dirs; my --keep printed p6/cand.o but the compile used a different path... Let me not go down this hole. 

The important question is whether the dump corresponds to my candidate. It doesn't. Let me regenerate a dump properly: create my own TU copy under my item dir with the candidate body, then dump that. I control the paths. Build a TU = a copy of the real includer .c with the header path rewritten to my local copy? The header include is `../shared/ov/func_8012B4B8.h`; if I put my TU at $d/tu_dump/t.c and my header at $d/tu_dump/../shared/ov/... that's awkward. Simpler: copy the scratch p6 tree to my item dir (it's small) and overwrite the header with my body, then dump. But the p6 scratch dir will be removed by --keep? "--keep scratch is removed after use" — it says the scratch is kept (--keep). Whatever.

Let me instead build a minimal TU myself: the scratch TU is 2000+ lines including the whole overlay. But I only need the function. Actually cc1 compiles the whole TU; the dumps will contain all functions, but I can grep by the ";; Function func_8012B4B8" marker.

Plan: copy $s/ov_MAIN_012.c to $d/tu_dump/ov.c, and copy p6/shared/ov/func_8012B4B8.h (with my body) to $d/tu_dump/../shared... hmm, the include is `../shared/ov/func_8012B4B8.h` relative to the TU file's dir. If TU is at $d/tu_dump/ov.c, then `../shared/ov/` = $d/shared/ov/. I can put my header there. But that pollutes my item dir with a `shared` dir — allowed (under shard dir). Or simply edit the TU's include line to point to an absolute/local path: `#include "cand_body.h"` where cand_body.h is the full header. That's easiest: replace the include line 911 with `#include "cand.h"`, write cand.h = the header with my body.

But wait, the header also needs the extern decls; my body file from dt.sh is just the function (no externs). The TU already has externs? The header has `extern Mat32 D_800AE620; extern void RotMatrixX(...)`. I'll make cand.h = full header text with my body.

Also the TU includes the header at line 911 with a guard? Fine.

Let me do that. Then dump and grep.

Actually, hold on. Is this RTL dive worth it? The residual is clear: &m gets a register. Let me think of the C construct that avoids it.

Observation from the dump (of the launder version): in the launder version, the loads from a1 are 0,4,8 then stores to fp+16,20,24 — wait, that's the same as my struct copy! But the launder version's source code is `t0 = src[0]; t1 = src[1]; t2 = src[2]; m[0]=t0; ...` and the dump shows loads into v78,v79,v80 then stores to fp+16,20,24. So the RTL is the same shape as a block move (the scheduler reorders). And the stores use `(reg:SI 30 $fp)` — note: $fp (s8) not sp! Because this function needs a frame pointer? Hmm, in the target the stores are `16(sp)`. Interesting: the dump uses $fp. But the final .s for the target/candidate... the diff showed target instructions with sp offsets.

Wait, `reg:SI 30 $fp` — in this dump, the function uses a frame pointer? That would be odd. Hmm, maybe this dump is from a *different* function's body? No, "Function func_8012B4B8".

Hmm, actually GCC 2.7.2 MIPS uses $fp as a general callee-saved reg (s8) when not a frame pointer; but here it's the frame base. In the final .s, it'd be `sw v0,16(sp)` if sp is the frame base. If $fp is the frame base, the prologue sets $fp=sp and stores at 16(fp). The diff showed sp. So the dump may not match the final .s.

OK, the dump is stale/mismatched. Let me do the clean local dump. But first, let me reconsider the empirical route with more ideas; RTL may take several calls.

Ideas to kill &m reg:
(A) Make the calls use `(void *)(m + k)` where the addresses differ from the copy dest: e.g. the copy dest is `m` (sp+16) and calls pass `m` — same. But what if I *offset* the array: declare `int m[9]` and use `m+1` as the matrix everywhere? Then all uses still share sp+20. Same.

(B) Do the copy into `m` *before* the `if` (outside)? No — target has it inside. Actually would the code be identical? The copy outside would execute unconditionally; the target's is inside the if. Different.

(C) Split the copy into 8 element assignments but from a *pointer variable* that is initialized with `&D_800AE620` and marked `volatile`? volatile would reload.

(D) Use `__builtin_memcpy`? libcall.

(E) Use a struct copy where the destination is a *temporary pointer* that is dead: `{ Mat32 *d = (Mat32 *)m; *d = D_800AE620; }` — tried (d2), same.

(F) Do the copy with `*(Mat32 *)&m[0] = D_800AE620;` — same.

(G) Make the copy's destination `m` and then pass `m` to the calls through a *different* object of the same address, e.g. a union with two arrays and pass one while copying into the other — tried (d5), same. Because cse sees the same RTL address.

So all spellings give the same RTL address sp+16. The question is why cse keeps it. Perhaps it's *not* cse but local-alloc: the address pseudo `(plus sp 16)` appears in MEMs; cse might turn it into a reg only if... hmm.

Wait, maybe I misread the diff: `addiu s1,sp,16` at mine[9] — maybe that's not &m but the *stack pointer adjustment*? No, the prologue already did addiu sp,sp,-64. And target[8] is nop. Hmm, target has a nop at 8 (delay slot). So mine has `addiu s1,sp,16` where target has `nop` (the branch delay slot of beqz s0). So mine's branch delay slot is filled with addiu s1,sp,16! That's reorg filling the delay slot. So the instruction existed before reorg and got scheduled into the delay slot.

In target, the delay slot is a nop. So target has no such instruction.

Which pass creates a reg for sp+16? Let me look at the .lreg/.greg dumps properly. But the dump is stale.

Let me build the clean dump. Steps:
1. Copy the scratch TU to $d/tu_dump/ov.c (from p6; but p6's TU is the real includer for ov_MAIN_012).
2. Write $d/tu_dump/cand.h = header text with my c_struct body.
3. Replace line 911 include with #include "cand.h".
4. DUMP_ROOT=$d/dumps bash tools/cc1_dumps_tu.sh $d/tu_dump/ov.c cst2.
5. grep the function region in .cse2/.lreg/.greg.

But there's a catch: the TU may include func_8012B4B8.h elsewhere or the same function may be defined by another header? Only line 911.

Actually simpler: keep the include line but create $d/shared/ov/func_8012B4B8.h with my body and put the TU at $d/tu_dump/ov.c → `../shared/ov/...` resolves to $d/shared/ov/. Good, no TU edit needed. But then $d/shared would contain only that header; other includes fall back to -Isrc/shared. 

Wait: $d is .run/P40/T11/G16/func_8012B4B8__func_8012B4B8. If TU is $d/tu_dump/ov.c, `../shared/ov/` = $d/shared/ov/. Good.

Let me do that.

Also note: the cpp include path `-I$(dirname $tc)` = $d/tu_dump. Fine.

Let me set it up.

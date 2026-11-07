---
ts: 2026-11-06T16:32:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_w0GrMvW5XxqSxN3ZIKai
---
The TU includes "../shared/engine_prelude.h". If I copy the TU to .run/P40/T11/W47x/dumpdir/md_MAIN_041.c, then "../shared" → .run/P40/T11/W47x/shared — I could create a symlink .run/P40/T11/W47x/shared → ../../../src/shared. But writing symlinks under the shard dir is allowed. Hmm, but "shared helpers" constraint says write only under .run/P40/T11/W47x/ — a symlink inside is fine.

Alternatively: copy to a directory whose parent has `shared`: e.g., .run/P40/T11/W47x/dumpsrc/src/md_MAIN_041/... no, "../shared" from src/md_MAIN_041 → src/shared. So mimic: .run/P40/T11/W47x/dumpsrc/md_MAIN_041/ and .run/P40/T11/W47x/dumpsrc/shared → symlink to src/shared. Wait "../shared" from dumpsrc/md_MAIN_041/x.c → dumpsrc/shared. Yes! And "common.h" resolves via -Iinclude (script passes -Iinclude). And -Isrc/shared too.

So: mkdir .run/P40/T11/W47x/dumpsrc/{md_MAIN_041,shared}, symlink shared → ../../../../src/shared. Hmm, symlinks may be blocked by the sandbox? Let's try. Actually simpler: copy src/shared/engine_prelude.h? It may include other things. Symlink is cleaner.

But do I really need dumps? The empirical search may be enough. Yet understanding the mechanism would help. Let me first do a few more empirical variants, then dump if needed.

Actually, let me reconsider the HImode result: w1_r16 gives everything right except the zero-test extension. What if ret is `u16` but the test is on a *different* expression that gcc knows is SImode? E.g.:

```c
s32 t;
u16 ret, m;
t = func(...);
ret = (u16)t;
if (t == 0) ...   // test on t (v0)? but target tests v1
```
No.

What if the test is `if (ret == 0)` but ret's upper bits are known zero because of how it's produced? If ret is produced by a zero-extending operation, gcc knows. E.g. `ret = t & 0xFFFF` (SImode andi) — but then ret is SImode and the andi is extra.

Hmm what about: ret u16 assigned from a `u16` load? Not our case.

Wait — maybe the extension `andi v0,v1,0xffff` can be avoided if the comparison is with `!= 0` in a context where... Actually gcc generates `andi 0xffff` because HImode in a register may have garbage upper bits. But what if we compare `(u32)ret < 1U`? Still needs extension.

Alternatively: what if the test is on `m` and m is computed... no.

New idea: what if `ret` is `s32` but assigned from a HImode *volatile*? no.

Let me reconsider. The target's `beqz v1` on an SImode ret is natural. And the andi v0,v1 means m is SImode too (andi is SImode-ish). So ret is SImode and the copy v1←v0 is SImode. For an SImode copy to survive local-alloc, the source must be live or... hmm.

Wait, is it possible that the move v1,v0 comes from a different source: a *store* or a *function argument*? Like the call `func_801638A0((u8 *) a0, (s32) sp20)` — no.

What if the C is:
```c
s32 ret;
s32 *p = &ret;
...
```
no.

Hmm, what about this: maybe the copy is from the call result to a variable that is live in the *else* arm, so it's live across the branch. E.g.:

```c
ret = func(...);
if (ret == 0) {
} else if ((m = ret & 0x8000) != 0) {
    ...
} else {
    ... ret used here? ...
}
```
If ret were used in the else arm, ret's live range extends into the else block (a different basic block). Then local-alloc in the first block: ret is live at the block end (it crosses into another block) — but that doesn't prevent tying: tying with the call result would still be possible since the call result dies at the move. Actually tying gives ret the same reg as v0 and deletes the move — ret then holds the call result, live into the else block. That's fine semantically. So still tied.

Unless v0 is not allocatable across blocks? v0 is call-clobbered; global-alloc would handle.

Hmm, let me look at the actual pinned dump to see the insn sequence and maybe the source shape hint (the pins were added by the decompiler, maybe from a different original). 

Actually, let me reconsider the possibility that the ORIGINAL source had `ret` as a `register` or that the move is an artifact the decomp team never cracked. These W47x shards exist precisely because some pins may be uncrackable (walls). The budget is 20-30 min/item and walls are acceptable.

But let me spend a bit more on ideas:

Idea: `s32 ret; s32 m;` and write the call as `ret = (s32)(func_801638A0(...) + 0);`? The `+0` would be folded.

Idea: use a ternary: `ret = func(...) ? : 0`? Not C89.

Idea: use the result in an `if` that creates a temp: `if ((ret = func(...)) == 0)` — same.

Idea: assign the call result to `m` and derive ret from m via a HImode copy while keeping the SImode test... 

Hmm, what about: ret SImode, m SImode, and:
```c
t = func(...);       // t v0
ret = t;             // copy
if (ret == 0) ...
```
with t used in the andi? andi reads t (v0). Not target.

What if `m = ret & 0x8000` where ret is the copy, and t is used *later* in the tail (after the if)? Then t stays live across the copy → the copy survives → ret=v1, t=v0. But then the andi reads ret (v1) → andi v0,v1,0x8000. Target! And t must be used later. Where? Maybe in the tail: the target's tail has func_80163408(a0, 0x2C, 0x80, 0x200) etc. If t were used there, we'd see an extra instruction. Unless t's later use is dead and flow deletes it — but if flow deletes it, t is dead at the copy, so local-alloc/global might still have the copy... flow runs before local-alloc? Order: flow, combine, sched1, local-alloc, global-alloc. So if flow deletes the later use, t dies at the copy → tie. So no.

What if t's later use is a *set* that's dead? e.g. `t = 0;` later — flow might delete a dead store.

Hmm.

Idea: the `move v1,v0` could be a copy that exists because the call result is used as an argument to another call... no.

Let me look at the exact RTL dump. I'll set up the dump dir. Actually — maybe easier: use `--keep` on a --try to get the scratch TU path, then run cc1_dumps_tu.sh on that .c with DUMP_ROOT pointing under my item dir. The scratch TU path is under .run/score/... and the dump script copies nothing; it runs cpp on that file with -Iinclude and -I<its dir> and -Isrc/shared. Its `#include "../shared/..."` would fail (since .run/score/../shared doesn't exist). But the delever pipeline already compiled it successfully... how? Because delever adds `-I{src_dir}` where src_dir = dirname(rec["src"]) = src/md_MAIN_041. But that doesn't fix `#include "../shared"` either... unless cpp resolves quoted includes relative to the *including file* first, then -I dirs. `#include "../shared/engine_prelude.h"` from .run/score/x/md_MAIN_041.c → tries .run/score/shared/engine_prelude.h (fail), then -Iinclude/../shared? -Iinclude gives include/../shared = shared/ (repo root shared?) Hmm, -Isrc/shared is also passed by cc1_dumps_tu but delever's pipeline maybe has -Isrc. Let me check: `-Iinclude -Isrc/shared`? The recipe pipeline. If -Isrc/shared is there, then "../shared/engine_prelude.h" from any -I dir: for -Iinclude → include/../shared/engine_prelude.h = shared/engine_prelude.h (repo root shared — exists?). For -Isrc/shared → src/shared/../shared/engine_prelude.h = src/shared/engine_prelude.h. Yes! So quoted includes search each -I directory. So -Isrc/shared makes it resolve. 

So cc1_dumps_tu.sh on the scratch TU should work if -Isrc/shared is passed (it is). Great.

Let me do --keep on w1_base to get a TU, then dump. Actually the scratch dir name uses pid; --keep prints the object path; the source is beside it.

Let me run: /usr/bin/python3 tools/delever_search.py --try <tu> <fn> <file> --body --keep.

But careful: the scratch dir persists; I must clean it later (it's under .run/score, not my shard — the constraint says write only under my shard; but --keep scratch is a tool behavior. The brief says "`--keep` scratch is removed after use". OK.)

Let me do it.

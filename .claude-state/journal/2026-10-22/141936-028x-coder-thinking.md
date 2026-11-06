---
ts: 2026-10-22T20:19:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uBXra3zZnGnmF25mr2tu
---
141 includers! For a header MATCH I must score 0 on every includer (tryinc.py k=0..n-1). That's expensive but the prior coder's approach... The task says header item: MATCH only if score 0 on every includer. But scores across includers should be the same body compiled in different TUs — usually identical since it's the same body text and same gcc. The prior results row for func_8012C2D0 was WALL. For this item, I need to check every includer at the end. Ugh, 141 × ~2s = ~5 min. Acceptable.

Wait, but this is a header item and prior worked examples (func_80181F4C in T10) presumably also header. The check is part of the job.

OK. Let me get back to cracking. Time budget: 20-30 min per item, ~28 min/40 tries already spent on this item. So I have maybe a few minutes more? "count its earlier ~28 min/40 tries toward its budget" — budget 20-30 min per item. So this item is nearly out of budget. Past 30 min, stop and record a wall; a WALL needs ≥20 min and ≥30 scored tries. It has 40 tries/28 min already, so a WALL is justified if I can't crack it soon. But let me give it a few more focused tries since I have a concrete hypothesis.

Time check: started at 14:05. Now maybe 14:20. The prior run's 28 min counts toward the budget, so the item is effectively at ~30+ min. I should make a handful of tries and then wall it.

Let me do a focused batch of ~8 candidates quickly.

Batch:
1. mp assigned after copy (int *mp).
2. void *mp assigned after copy.
3. copy via d ptr, calls via mp assigned after.
4. `Mat32 m;` + `m = D_800AE620;` + mp.
5. scalar copy from a struct pointer variable but with the source read via a struct copy? 

Hmm, also worth trying: keep scalar m[i] stores but get the source base via a *second* statement that cse can't fold: e.g.
```
t0 = D_800AE620.w0; ... 
```
direct global member reads (cse creates a base reg for symbol addresses used ≥2 times — this is the classic behavior). Actually n1's folding produced lui per load because src was a pseudo with a constant value and cse substituted the constant into the address expression, then the address `(plus (symbol_ref) (const))`... cse normally creates a base register for a symbol used many times! Hmm, but it didn't. Because each load's address is `symbol+0`, `symbol+4`, ... different constants; cse folds each into the load separately. In the target, one lui + offsets — that's reload's doing: the symbol address is a `(high)` pair; reload... hmm, actually gcc usually emits lui+addiu per symbol use unless cse merges. The target merged.

So the movstr/block-move route is what merged the source. Fine.

Direct global member reads: `m[0] = D_800AE620.w0; m[1] = D_800AE620.w4; ...` — this is a struct copy expressed as member copies. cse would fold each address to symbol+offset → lui per load probably. Unless it merges. Worth one try? Maybe.

Let me just run the batch. Write candidates with the Write tool? They're small; use a heredoc via bash? Rules: write scratch scripts with Write; files under .run. I'll use Write for each candidate (a bit verbose). Better: write a generator script under the item dir that emits the candidates, then sc.sh them. That's one Write + one run.

Let me write gen.py under the item dir that writes c2_*.c from a template. Template base = c_struct.c with placeholders for the copy and call args.

Simpler: write a bash script that sed-generates variants. But C text with quotes... Python is cleaner.

Let me define the base body and variants as full text in a Python script.

Base (c_struct):
```
s32 func_8012B4B8(int param_1)
{
    int self;
    register int obj  __asm__("$16");  // !FAKE: pin $16 ...
    int m[8];
    short sVar1;
    int o2, t0, t1, t2;
    self = param_1;
    obj = *(int *)(self + 0x20);
    if (obj != 0) {
        <COPY>
        RotMatrixX((int)*(short *)(obj + 0x10), <A1>);
        RotMatrixZ((int)*(short *)(obj + 0x14), <A2>);
        RotMatrixY((int)*(short *)(obj + 0x12), <A3>);
        *(Mat32 *)(obj + 0x34) = *(Mat32 *)m;
        ...
    }
}
```
Variants:
v1: COPY=`*(Mat32 *)m = D_800AE620;` A=`(void *)m` (baseline 19)
v2: COPY + `mp = m;` with `int *mp;` decl; A=`(void *)mp`
v3: same with `void *mp;`
v4: `Mat32 *d = (Mat32 *)m; *d = D_800AE620;` + `mp = m;` A mp
v5: COPY; then `mp = m + 0;`? identity.
v6: `*(Mat32 *)m = D_800AE620;` then `m[0] = m[0];`? no (self-assign removed).

Alternative idea: what if the calls pass `m` but the copy uses `m` only via a *different type* that creates a separate base: e.g. copy as `*(Mat32 *)(void *)m = D_800AE620;`.

Honestly, the cleanest hypothesis: the call-arg pseudo is merged with the movstr dest pseudo. To keep them separate, make the movstr dest a pointer variable that is *reassigned* to the array before the calls... cse equates same values.

What if the calls use `m` and the copy uses a struct member of a union/struct where m is the second member? e.g. `struct { int pad; int m[8]; } s;` copy to s.m, calls to s.m — same address expr.

What if the copy destination is `m + 0` via a variable `int *dst = m + 0;` — identity.

Hmm. Different approach: make the *copy* happen through the source pointer with the destination as the call-arg address — i.e., order: compute `mp = m;` FIRST, then copy `*(Mat32 *)mp = D_800AE620;`, then calls `mp`. Then there's ONE pseudo used for dest and calls (4 refs) — same as c_struct.

What if the copy is done with an explicit element loop with a *variable* index? That would use a base register for m (good for the calls) and the loop's stores use the base... but the loop would add overhead.

What if the copy is expressed as two block moves of 16 bytes each into m and m+4? The dest address pseudos differ; each dies at its move. The calls' pseudo is separate (3 refs) → may remat. But the source: two symbol addresses → two lui? The target has ONE lui a1 for the source and one for... no, just one lui. Two block moves would produce two lui/addiu (one per move) unless cse merges. Risky.

Let me test v2/v3/v4 plus a couple more and see the score.

Actually — wait. Let me reconsider the difference between the score-0 body and c_struct at the *RTL* level properly by dumping both correctly. This could save many blind tries. Let me build the dump command:

```
mipsel-linux-gnu-cpp -lang-c -Iinclude -I$S/inc -Isrc/ov_MAIN_012 -Isrc/shared -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C -Isrc '-DINCLUDE_ASM(a,b)=' $S/ov_MAIN_012.c > t.i
```
Then cc1 with the dump flags on t.i.

But careful: the header include from the .c is `"../shared/ov/func_80128158.h"`. With -I$S/inc, the resolution of `../shared/ov/func_80128158.h` = $S/inc/../shared/ov/... = $S/shared/ov/... which only has func_8012B4B8.h. For func_80128158.h it doesn't exist there, so it falls to the next -I dir: -Isrc/ov_MAIN_012 → src/shared/ov/func_80128158.h. Good.

Let me write a small dump script under the item dir that takes the scratch dir and tag. Actually, I can just do it in one Bash call with the cpp and cc1 commands, writing into the item dir. But cc1 must run with cwd = the dump dir? The script does `(cd $d && cc1 ...)`. I can run `cd` in a subshell — allowed? The rule says never prefix with `cd <dir> &&`. Hmm. But cc1 needs to write .s in the cwd. I can pass -o with a full path. Let me just do:

```
/usr/bin/python3 - <<'EOF' ... 
```
No inline python -c; scripts only.

Let me write .run/P40/T11/G16/func_.../dump.sh (scratch script under my item dir) that does the cpp+cc1 for a given scratch dir and tag, DUMP_ROOT under item dir.

Given time pressure (item near budget), is this worth it? The alloc tables pre-reload were identical for the wrong body, so I don't know. The difference between score-0 and c_struct in the final code is the address pseudo allocation; the RTL at lreg/greg would show the ref counts. I think it's worth ~3 minutes: it tells me the exact threshold to beat.

Actually, simpler decisive experiment: score-0 body with the launder removed = 20 (cse folds source). What if I keep the launder's *effect* with real C: the source address held in a variable that cse can't fold because it's set from a *parameter-like* opaque source... The only real-C way to stop cse from folding a constant address is to make the value come from a non-constant (e.g., a function call or memory load). No.

Hmm, but hold on: the target's source base is a1, loaded via lui/addiu. That IS the symbol address computed once. cse folding it into 8 loads (each with its own lui) is what happens with `src[i]`. Why does the target not do that? Because the target's copy is a *struct copy* (block move), where the source is a single `mem:BLK` address used once by the movstr insn → the address is a pseudo, and the loads generated from it use offsets. So yes, the target C is `*(Mat32 *)m = D_800AE620;` or equivalent.

So c_struct is essentially the right C; the difference is a *scheduling/allocation* artifact of the call-arg address. The target's address pseudo is rematerialized; mine gets s1. That's a global-alloc/reload difference driven by pseudo refs.

In c_struct's alloc table (cs), which allocno is the address? The .greg order was 78 79 80 72. Hmm, these are global allocnos (the ones needing callee-saved). r78/r79/r80: 6 refs, live 11, pri 10909, conflict a1,s0,sp, "dies in 3 places". r72: 9 refs live 48 pri 5625 crosses 3 calls. 

Hmm, r72 crosses 3 calls = self. r78/79/80 die in 3 places each, 6 refs, live 11 — these look like the three `RotMatrixX/Y/Z` arg setups? No...

Wait, maybe r78/r79/r80 are the `obj+0x10` short loads? No, they'd be local.

Let me look at the actual .greg dump section for the function to see the allocation order and regs. It says order 78 79 80 72. If r72 (self) is allocated LAST, it gets... global-alloc assigns the first allocno the first available hard reg? The order line is the sorted order (highest priority first?). Then s0/s1/s2 go to 78,79,80 and self (72) gets spilled?! But self is in s2 in the output. Hmm, the order may be reversed.

This is a rabbit hole. Since the item is at budget, let me do one quick decisive thing: compare the .greg dump of the *correct* bodies (need the shadow fix). Let me just do the dump properly — 5 minutes max.

Let me write the dump script.

---
ts: 2026-11-06T10:37:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xzf3owretVw6hA7irCbF
---
Hmm so where does the second pseudo come from? Note `v0` is also a local variable (s32 v0) holding the call result. In orig, the function has `s32 v0;` local plus `v0 = func_8012C1B8()`. Wait — in orig, `v0` is a plain C local named v0 (not pinned). The call result assignment `v0 = ...`. So v0 is a pseudo, allocated to $2 presumably by preference.

The two pointer pseudos... Maybe because in the orig, `s0` pinned to $16 — and gcc has to copy the incoming a0 into $16. That's one move. Now without the pin, the local `s0` is a pseudo, and the copy `s0 = a0` becomes... coalescing. But gcc 2.7.2's global-alloc might not coalesce a param copy if the pseudo is live across calls. It creates the local in s1 and then... hmm, where does the second come from?

Wait, look again at mine insns:
```
0 addiu sp,-32
1 sw s1,20(sp)
2 move s1,a0
3 sw ra,24(sp)
(4?)
5 sw s0,16(sp)
6 move s0,s1
```
Maybe instruction 4 is something and 6 `move s0,s1` is the copy for the *parameter* pseudo of the call `func_8012CAE4(s0)`? No, that uses s1 at index 10.

Hmm, maybe I should look at the raw full listing. Let me get the candidate object with --keep and objdump it. Actually easier: use dt.sh with orig (0) and then with nopin, and print full 70 lines — we already have the full diff which is all differences; equal parts aren't shown. Let me get the full mine listing via --keep.

Alternatively use tools/cc1_dumps_tu.sh? That dumps the TU. Let me check what's available: .run/P40/T10/hdump.sh (header pass dumps), tools/cc1_dumps_tu.sh.

Simplest: `delever_search.py --try TU fn file --body --keep` prints the candidate object path; then objdump -d. But objdump output >40 lines → run via run.sh. Fine.

Actually, wait. Maybe the extra copy is caused by the *barrier* interacting: in nopin, the barrier is still present. The barrier `__asm__("" ::: "memory")` might force the address of `s0` to be spilled/reloaded... no.

Hmm, but nobar (pins kept) had 63 ins and no prologue diff. win0 (both removed) had 66. nopin (pins removed, barrier kept) had 66 too. So the extra copy is purely from removing the s0 pin.

Let me think about what a `register ... __asm__` variable does in gcc 2.7.2: it's a hard register *local to the function*; references to it are hard reg $16. Crucially, in the C code, `s0` is used as the pointer everywhere. Without the pin, the local is a pseudo.

The second pseudo might come from the address expression `(s32)s0 + 0x20` and casts? No.

Let me test: variant A1: declare `void *s0 = a0;` (init at decl). Variant A2: eliminate the local: use a new parameter name? Can't change signature. Variant A3: use `void *s0; s0 = a0;` but mark s0 as `volatile`? no.

Alternatively maybe the extra copy is because gcc treats `s0 = a0` where a0 is a parameter and s0 is used in the `if (v0==0)` branch — the value must survive; it's one pseudo. There should be no second.

Unless... the second pseudo is for `v0`!? Look: `move s0,s1` — no.

Hmm, hold on: maybe mine index 5 `sw s0,16(sp)` and 6 `move s0,s1` — could it be that s0 here is being used as a *scratch* register by the register allocator, and `move s0,s1` is actually the copy from the parameter pseudo (a0, which global-alloc put in s1) into the local pseudo (s0)? I.e., the local s0 is a *global* allocno (live across calls) and the parameter a0 pseudo also got a callee-saved reg s1 because it's live from entry to the copy point... but a move from a0 to a local at the top should coalesce.

Actually gcc 2.7.2 global-alloc does NOT do coalescing like modern GCC; it does "copy propagation" during allocation: if the source dies at the copy, it can assign the same hard reg (tie). Here a0 dies at the copy, so it could tie. But maybe a0 is used later? Is a0 used after `s0 = a0`? In the C: `func_8012CAE4(s0)` uses s0, not a0. So a0 dies.

Hmm, but wait: parameter a0 in gcc is also the *incoming argument* pseudo which has a "preference" for $4. The copy to s0: if a0 dies, global-alloc can coalesce... but gcc 2.7.2's global.c doesn't coalesce; local-alloc handles copies within a block (it tries to tie). The copy is in the entry block, so local-alloc might tie it. Hmm.

I'm spending too long theorizing. Let me experiment. Variants to try:
1. `void *s0 = a0;`
2. Direct parameter use in all expressions but save a0 to a local only where needed... 
3. Two-level: maybe declare `void *s0; s0 = a0;` but move the assignment after the call? No, the pointer must survive the call — that's why it's saved.

Actually! Maybe the issue is that the assignment `s0 = a0` occurs BEFORE the call func_8012C1B8, and gcc must keep s0 live across that call, so it's allocated to a callee-saved reg. But the *incoming* a0 (REG 4) is the parameter; global-alloc sees a0's live range from entry to the copy. It assigns a0 to... the copy at the top means a0's live range is tiny. Global alloc assigns it $4 probably. Then the copy `move s1,a0` where s1 = local. That's the ONE move. The second `move s0,s1` remains unexplained.

Let me just dump the candidate object and look at the actual full listing to understand. Use --keep.

Let me run: `/usr/bin/python3 tools/delever_search.py --try src/ov_SC03_028/ov_SC03_028_jr_801887A8.c func_8018966C .run/.../nopin.c --body --keep` and then objdump. Output should be short-ish (diff only). --keep prints the object path.

Then `objdump -d <obj> --start-address...`? We can use tools/objdump? Just objdump -dr and grep the function.

Hmm, but simpler: maybe I can use `tools/cc1_dumps_tu.sh` to see the rtl? Let me check what it does.

Actually, let's not over-engineer. Let me try candidate variants and score them with sc.sh — cheap.

Variant ideas for the s0 copy:
- v_init: `void *s0 = a0;`
- v_param: don't use a local at all; instead save a0 into a `s32` local? same thing.
- v_two: declare `void *s0;` and assign `s0 = a0;` after the call? Not possible (a0 clobbered).
- v_reuse: use the `v0` local for both? no.

Another idea: the target's shape is exactly what a *parameter* used directly would produce if it weren't clobbered: the compiler would save a0 to s0 in the prologue. Since a0 is used after the call, gcc's expand must copy it to a pseudo anyway (can't keep a0 live across a call). The pseudo would be allocated to s0 (first callee-saved). The current code does exactly that via `s0 = a0`, giving two pseudos? Hmm, unless the assignment in the entry block plus uses in later blocks means the pseudo is a "global" allocno, and the incoming a0 pseudo is also global (live from entry). global-alloc assigns a0 → s1 and local → s0, then local-alloc inserts the copy... but wait, the copy `s0 = s1` in the prologue is the *only* copy then, and `move s1,a0`? That's two copies: a0→s1 then s1→s0. Weird.

Unless the first move `move s1,a0` is not a copy but the assignment of the *parameter save*: gcc saves the incoming argument register to its stack slot? No, it's a move to s1.

Hmm, let me actually look at the full mine listing. I'll dump.

Actually — maybe there are THREE pseudos: a0 (in $4), local s0 (P), and v0's... The `sw s0,16(sp)` and `move s0,s1` order: gcc saves the old s0 (callee-saved) then copies. The copy `move s0,s1` is P2←P1.

What if P1 is the local `s0` (assigned a0), and P2 is... the value used as base in the address computations `(s32)s0 + 0x20`? When you cast a pointer to s32 and add, gcc's expand creates a copy? No.

OK, dump time. Let me use --keep and objdump -dr. I'll run through tools/run.sh? The output could be long. I'll grep the function.

Actually maybe easier: use `tools/cc1_dumps_tu.sh` — let me read its help quickly.

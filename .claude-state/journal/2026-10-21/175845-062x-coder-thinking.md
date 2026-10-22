---
ts: 2026-10-21T23:58:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_8ZwGpoB3oCuQId8HBroN
---
M4's structure (39 ins):
```
24 beqz v0        ; ret == 0 (ret in $2)
25 move v1,zero   ; result = 0  (result in $3)
26 andi v0,v0,0x8000
27 beqz v0
28 move v0,v1     ; return result (copy $3 → $2)
...
32 sltiu v1,v0,1  ; result = (byte != 0x15)
33 move v0,v1
```
Target:
```
24 move v1,v0   ; ret copy
25 beqz v1
26 andi v1,v1,0x8000
27 beqz v1
28 move v0,zero ; result = 0
29 lbu v0,30(sp)
30 nop
31 xori v0,v0,0x15
32 j +0x8c
33 sltiu v0,v0,1
34 move v0,zero
```
So the target: the ret value is copied to $3 and the result is computed in $2 (the return reg) directly (no final copy).

So I need: (1) ret copied to $3, (2) result computed in $2.

In M4, result is in $3 and ret in $2 — the opposite.

The allocator gives $2 to `ret` (the call result, born first) and $3 to `result`. Why doesn't `result` get $2 (the copy preference for the return value)? Because in gcc 2.7, the "preference" is honored by global-alloc; for locals, local-alloc's order decides.

Hmm! Important: in the target (pinned), `result` is a hard reg $2 → obviously $2. And `ret` is a local pseudo → $3 with a copy from the call's $2 ✓.

For the lever-free version, I need `result` to be allocated $2 and `ret` $3.

Local-alloc's rule (gcc 2.7 final.c local_alloc): it processes the block's pseudos ordered by... I recall `local_alloc` uses a "qty"-based sort: `qsort (pseudos, n_pseudos, sizeof (pseudo_reg), pseudo_reg_qty_cmp)` where the comparison is by "qty" (number of refs) — but there's also `pseudo_reg_forced_p`.

In our case: `ret` has 1 set + 2 uses = 3 refs; `result` has 2 sets + 2 uses = 4 refs (in M4: 1 set + 1 use + return = 3). Hmm.

In nopin (the original structure): result has 3 sets (2 zeros + 1 comparison) + 1 use (return) = 4 refs; ret has 3 refs. So result has MORE refs, yet got $3 ✗ (contradicts the qty hypothesis).

Hmm. So it's not qty.

What if it's "birth order" (the pseudo number)? `ret` is born at the call (earlier in the block) → $2. `result` is born later → $3.

To flip: make `result` born BEFORE `ret` — but not live across the call (that spilled it to $s1 in M5/M6).

Hmm, M5/M6 spilled because result=0 before the call made it live across the call. What if `result` is born before the call but the assignment is dead there? E.g.:

```c
    int result = 0;   /* init at decl */
    ...
    ret = func_80133784(...);
```
→ `result` is live across the call ✗ (same problem).

What if the function's `result` variable is declared before `ret` and assigned only after the call, but the pseudo's NUMBER (birth) is determined by the first RTL set, not the declaration. Hmm, pseudo numbers are allocated at the declaration/creation time (in the front end, each local var gets a pseudo number at declaration). So declaring `result` before `ret` gives result a lower pseudo number → local-alloc might prefer the lower pseudo number for $2.

I tested M2 (decl swap: result before ret) → score 9 (same as nopin). So no.

Hmm. Let me think about local-alloc's actual algorithm in gcc 2.7 (final.c):

```c
static void
local_alloc (insn, block, reg, regset, i, pseudos, n_pseudos, live, n_live, need, n_need)
{
  ...
  /* Find the pseudo-regs that are live in this block, and count the number of references */
  ...
  qsort (pseudos, n_pseudos, sizeof (pseudo_reg), pseudo_reg_qty_cmp);
```
Hmm, I recall `pseudo_reg_qty_cmp` compares `REG_N_REFS`. And the sort is ascending? Then the LAST pseudo (highest qty) gets the first hard reg? Hmm.

Also there's `local_var`... and importantly, in local_alloc there's a step where a pseudo that is "the return value" gets preference? Hmm.

Let me look at what gcc 2.7 does with the return value: in `expand_end_function` / the "return" handling, the return value is copied to the return register at the end. There's a step in final.c: "if (DECL_REGISTER_P (retval)) ..." — the return value pseudo is treated specially: `cse->x`... In gcc, `DECL_RTL (DECL_RESULT (current_function_decl))` is the return pseudo, and there's code in final.c's `reload`/`local_alloc` that gives the return pseudo preference for the return register (RETURN_INSN_REGNUM). Hmm! In gcc 2.7's final.c, function `assign_regs`/`allocate_regs` — there's `choose_regs` and a specific handling: "if (pseudo_uid == DECL_UID (DECL_RESULT (current_function_decl))) prefer the return reg".

I believe there IS such a preference for the function's RESULT_DECL. But our `result` variable is not the RESULT_DECL — the function returns `result` (a copy). gcc creates the RESULT_DECL pseudo and copies our variable into it at the return. So the preference goes to the RESULT_DECL pseudo, not to `result` ✗.

=> If the source returned the value DIRECTLY (no local variable), the RESULT_DECL pseudo would be the value → and the preference would give it $2!

So: what if the source is written so that the returned expression IS the result? E.g.:

```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        if ((ret & 0x8000) != 0) {
            return *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
        return 0;
    }
    return 0;
```
Hmm, but then the return value is set in 3 places (3 sets of $2): the ROM has 2 `move v0,zero` + 1 `sltiu` ✓ = 3 sets! ✓✓

Let's check the ROM's structure with this source:
```
ret = call;             ; $2 = call result
if (ret != 0) {         ; beqz → return 0 path
    if ((ret & 0x8000) != 0) {
        return (byte == 0x15);   ; lbu, xori, sltiu
    }
    return 0;           ; the "move v0,zero" at ins 28
}
return 0;               ; the "move v0,zero" at ins 34
```
The ROM:
```
24 move v1,v0    ; ret copy (still needed! because ret is a local pseudo and $2 is the RESULT_DECL's reg)
25 beqz v1
26 andi v1,v1,0x8000
27 beqz v1
28 move v0,zero   ; return 0 (mask path)
29 lbu v0,30(sp)
31 xori v0,v0,0x15
32 j +0x8c
33 sltiu v0,v0,1
34 move v0,zero  ; return 0 (ret==0 path)
```
Hmm, in this source the `return 0` for the mask path (ins 28) is the fallthrough of the beqz at 27 ✓ and the "return 0" for ret==0 is at ins 34 ✓. But the ORDER: the ROM has ins 28 (mask-path return 0) BEFORE the byte check (29-33) — i.e. the "return 0" for the mask path is at ins 28 and the byte check follows it (the byte check is the fallthrough of ins 27 → wait, ins 27 `beqz v1,+0x8c` jumps to +0x8c = ins 34 (the ret==0 path) when the mask is 0. So the fallthrough of ins 27 is the mask-set path → ins 28 `move v0,zero` → hmm, but then ins 29-33 (the byte check) follow, and the `move v0,zero` at ins 28 would be overwritten by the byte check ✗.

So ins 28 `move v0,zero` is NOT the mask-path return; it's the "result = 0" assignment (from the source's `result = 0;` in the then-branch) which is then overwritten by the byte check ✓ (the source: result = 0; if (mask) result = (byte == 0x15);).

OK so the ROM's structure matches the ORIGINAL source structure (with `result` as a variable): ins 28 = result = 0 (in the then-path), then the byte check may overwrite it.

Hmm OK. So the source structure is right; the issue is purely the allocation.

Let me think about the "copy preference" mechanism more concretely. In gcc 2.7, final.c's local_alloc has this (I recall the code):

```c
      /* If this pseudo is the return value, and the return register is available, use it. */
```
Hmm, I'm not sure. But there's a known gcc feature: "the return value's pseudo gets the return register" — implemented via `prefer` in global-alloc for the RESULT_DECL. For locals, `local_alloc` doesn't consider preferences.

So the local `result` won't get $2 unless it's born first.

Hmm, what if we make `result` the RESULT_DECL by using the "return" statement directly... but the source's structure needs the variable (result=0 then conditionally overwritten).

Hmm, alternatively: what if the value returned is computed as an expression that gcc puts in the RESULT_DECL pseudo, and the local `result` is eliminated? E.g.:

```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        if ((ret & 0x8000) != 0) {
            return *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
        return 0;
    }
    return 0;
```
This has 3 returns → the RESULT_DECL pseudo gets 3 sets ✓ (the ROM: ins 28 `move v0,zero` = the "return 0" in the mask path; ins 33 sltiu = the byte check; ins 34 `move v0,zero` = the "return 0" in the ret==0 path) — 3 sets ✓✓.

But the ORDER in the ROM: ins 28 `move v0,zero` comes BEFORE the byte check (ins 29-33). In my proposed source, the mask-path "return 0" is the block after the byte check (the byte check's block ends with `j` to the epilogue). Hmm: the ROM's ins 28 `move v0,zero` then ins 29 `lbu v0,30(sp)` — the `move v0,zero` is dead (overwritten by lbu) — that's the source's `result = 0;` before the byte check ✓ (a dead store that the compiler kept because it's a separate statement? gcc would fold it away! Since result is overwritten unconditionally in that path... hmm, but the ROM keeps it → in the ROM's compilation (with the pin), the `move v0,zero` is a real insn to $2 and the byte check overwrites it → dead code that gcc 2.7 didn't remove (it's a hard-reg set, so gcc doesn't know it's dead? It does know... but hard-reg sets aren't DCE'd as easily).

Interesting! So the ROM's ins 28 `move v0,zero` is a dead store — evidence that the source has `result = 0;` before the byte check ✓ (as the current src does).

Without the pin, gcc would eliminate that dead store (the local variable's set is dead) → 39 ins (like M4).

Hmm! So the ROM's structure with the dead store requires... hmm, M4 (39 ins) lacks the else-branch `move v0,zero`? Let me compare M4 vs nopin ins counts: nopin = 40 ins (same as target) ✓ but score 9; M4 = 39.

nopin has 40 ins: the structure matches the count but the registers differ.

OK so for item 4, the crux: get `result` into $2 while `ret` is copied to $3.

Since `ret` is born at the call and `result` after, and local-alloc gives $2 to the first-born...

Hmm, what if `ret` is NOT a variable but the call result is used directly? Then the call result stays in $2 (no copy) ✗ (the target copies it).

What if the source forces the copy by assigning the call result to a variable of a different type? e.g. `short ret;`? Then the call result → HImode copy: `move v1,v0` + maybe truncation. The ROM's ins 24 is exactly `move v1,v0` ✓ and then `andi v1,v1,0x8000` — for a u16 ret, `ret & 0x8000` → the zero-extended value → `andi v1,v1,0x8000` ✓ (if the HImode value was copied without truncation... gcc would need `andi v1,v1,0xffff` to truncate ✗).

Hmm, unless the copy is `move v1,v0` and gcc knows the value fits in 16 bits? No.

What about `ret` being `unsigned int` and the source doing `(ret & 0x8000)` — same as now.

Hmm, what if the source assigns the call result to a variable AND uses it in a comparison with a signed/unsigned mix that forces a copy? Meh.

NEW IDEA: what if the `result` variable is born before the call but does NOT stay live across the call — i.e. it's assigned before the call and re-assigned after? Like:

```c
    result = 0;               /* born before the call */
    ret = func_80133784(...);
    if (ret != 0) {
        result = 0;
        ...
```
M6 did that → 41 ins (spilled to $s1) ✗ — because `result` was live across the call (its value must be preserved). Hmm, but the first `result = 0` is dead (overwritten in all paths) → gcc should eliminate it... but it didn't (it kept the value across the call → spill). Hmm, because the "else" branch also assigns result=0 → so the value from before the call is dead in all paths → gcc should DCE it. But M6 showed a spill to $s1 → gcc didn't DCE it (gcc 2.7's DCE is weak).

Hmm, so if I could make gcc eliminate the pre-call set, the spill would vanish and `result` would be born... hmm, but the pseudo would still be "born" before the call in the numbering.

Let me try M6 variant where the pre-call assignment is clearly dead and the else branch is removed:
M7:
```c
    result = 0;
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        if ((ret & 0x8000) != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    }
    return result;
```
= M5 (41 ins, spill) ✗.

Hmm, M5 spilled. So a pre-call set of `result` → live across the call → spill ✗.

What if the pre-call value is a DIFFERENT variable that dies? no.

OK, let me think about the "birth order" hypothesis differently: maybe local-alloc gives $2 to the pseudo that is live at the block's start... or the one with the longest live range.

Alternatively, maybe I should attack from the other side: make `ret` NOT be in $2 by making the call's result NOT land in $2 — e.g. by using the call's result in a context that forces a copy right away. What if the source is:

```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    } else {
        result = 0;
    }
    return result;
```
and we add a "use" that forces ret out of $2: e.g.
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) { ... }
```
Hmm.

What if the source reads `ret` twice in DIFFERENT blocks, e.g.:
```c
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
```
Both uses are in the same "if" block chain but different sub-blocks (the `ret != 0` test is in the block after the call; the `ret & 0x8000` test is in the then-block) → so `ret` IS live across a block boundary → it's a GLOBAL pseudo → global-alloc allocates it (callee-saved preferred!) → hmm, but it got $2 in my compile.

Hmm, in gcc, a pseudo live across blocks but not across a call is still local-ish ("local pseudo" = used in one block; otherwise global). `ret` is used in 2 blocks → global → global-alloc would give it a callee-saved reg ($s0-$s7) — but my compile put it in $2! Hmm, because global-alloc prefers... hmm, in gcc the "local" pseudo definition is about the pseudo's *home* — pseudos that don't cross a call can be allocated caller-saved regs by global-alloc ✓ (that's the "call-clobbered" analysis).

So `ret` is a global pseudo allocated by global-alloc, and `result` is a local pseudo (used in one block? no — result is set in 2 blocks and used in 1) → also global-ish.

Global-alloc's priority: floor(log2(refs)) * refs / live * 1e4.
- ret: refs = 3 (1 set + 2 uses), live = ~10 insns → floor(log2(3)) = 1 → 1*3/10 = 0.3 → 3000.
- result: refs = 4 (3 sets + 1 use), live = ~8 → floor(log2(4)) = 2 → 2*4/8 = 1 → 10000 → result should win $2!? But mine gave $2 to ret ✗.

Hmm, unless `result` is local (allocated by local-alloc) while `ret` is global.

In the pinned version, `result` is a hard reg → not a pseudo at all.

So: to flip, `result` must be a global pseudo with a higher priority than `ret`, or `ret` must be local.

Hmm, how about making `ret` local (used in one block only)? E.g. restructure so the call result is used in a single block:
```c
    if ((ret = func_80133784(1, buf1, (int)buf2)) != 0) {
        if ((ret & 0x8000) != 0) {
```
Still 2 blocks.

What if we compute the mask test in the same block:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0 && (ret & 0x8000) != 0) {   /* && fold */
        result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
    } else {
        result = 0;
    }
```
Hmm! The `&&` fold is in the C0505 catalog ✓. But this changes the structure: the ROM has 2 `move v0,zero` (ins 28 and 34) → the && version has 1 set of result=0 (in the else) + the comparison ✗ (the ROM's ins 28 is a dead store in the then-path).

Hmm, but the ROM's ins 28 `move v0,zero` (dead) — in the && version, the else-path's `move v0,zero` would be at... the ROM's ins 28 is in the then-path (before the byte check) and ins 34 in the ret==0 path. So the ROM has 2 sets: one dead (ins 28) and one live (ins 34).

So the source has 2 assignments: `result = 0;` in the then-path (dead, overwritten by the byte check) and `result = 0;` in the else path ✓ = the current source's structure exactly.

OK so the source structure is right. The problem is purely: which register.

Hmm, let me reconsider: maybe the trick is that `result` must be a pseudo that is LIVE ACROSS THE CALL? No — that spilled.

What if `result` is live across a branch but not across the call (like now)?

Let me approach empirically: try variants that change the qty of `result` or `ret`:
- V1: make `result`'s refs higher: e.g. `result = 0;` in the then-path, and the else-path `result = 0;` — plus an extra use: `if (result) ...`? changes semantics.

Hmm.

- V2: make `ret`'s refs lower: the source uses ret twice. What if the source computes the mask into a variable?
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
```
Hmm.

- V3: What if `ret` is declared as `unsigned int ret;`? The test `ret != 0` and `ret & 0x8000` — with unsigned, the `!= 0` test becomes `beqz`? and `& 0x8000` → andi ✓. The signedness might change the priority/reg class? Probably not.

- V4: what if `result` is `unsigned int result;`? Hmm.

- V5: What if the function returns `int` but the variable is `long`? no.

Hmm, let me think about the "copy preference" once more. In gcc 2.7's global-alloc, the copy preferences come from "hard reg copy" (copying a pseudo to a hard reg). Here the copy is `set $2, result` at the return → a hard-reg copy → global-alloc records a preference for `result` → $2 (the "copy preferences" mechanism). This applies to GLOBAL pseudos. `result` — is it global? It's set in 2 blocks and used in 1 → it's live across blocks → global ✓. So global-alloc should give it a preference for $2.

But global-alloc allocates callee-saved regs first for globals, and the caller-saved regs are allocated last (in "allocate_regs", the caller-saved regs go to the pseudos with the LOWEST priority). Hmm! In gcc, global-alloc: first allocates the callee-saved registers (to the globals with the highest priority), then the caller-saved ones (to the remaining globals with the lowest priority).

Hmm, so both `ret` and `result` would be globals competing for $2 (a caller-saved reg). The one with the HIGHER priority gets $2. Per the priority formula: result (refs 4, live ~8) → 2*4/8 = 1.0 → 10000; ret (refs 3, live ~10) → 1*3/10 = 0.3 → 3000. So result should get $2 ✗ (contradiction with observation).

Unless the live ranges differ from my estimate. `ret`'s live range: from the call (ins 22) to its last use (ins 26) → ~5 insns → priority = 1*3/5 = 0.6 → 6000. `result`: sets at ins 28 and 34, use at the return (ins 39) → live from 28 to 39 = 11 → 2*4/11 = 0.73 → 7272. So result (7272) > ret (6000) → result should get $2. But observed: ret got $2!?

Hmm, my estimates are rough. Also the "floor(log2(refs))" for refs=3 → 1; for refs=4 → 2.

Hmm, the observation says otherwise. Maybe `result` is a LOCAL pseudo (not global): if its sets and uses are all within one block... The then-path's `result = 0` (ins 28) and the else-path's `result = 0` (ins 34) are in different blocks → global.

Hmm, unless gcc's "local pseudo" definition is about the pseudo being live in only ONE block at a time...

I could stop theorizing and get the alloc table. But that requires the cc1 dumps (expensive).

Let me try a few more cheap variants and then decide. Cheap ideas:
(a) `result` as `unsigned int` (the ROM's `sltiu v0,v0,1` suggests unsigned comparison! `sltiu v0,zero,v0` — hmm, `sltiu v0,zero,v0` = (0 <u v0) = (v0 != 0) ✓ unsigned comparison!). The source has `result = *(unsigned char *)((char *)buf2 + 6) == 0x15;` → the comparison of two u8 values → gcc computes `xori v0,v0,0x15; sltiu v0,zero,v0` ✓ (unsigned). OK, no change.

(b) What if `result` is declared `int` but assigned `0` via an expression that makes it a different pseudo? meh.

(c) What about the ORDER of the two tests: `if ((ret & 0x8000) != 0)` — the ROM does `andi v1,v1,0x8000` then `beqz`. ✓ mine does the same on $2.

(d) What if we swap which variable holds the call result vs the result: e.g. rename so that the "result" variable is the one holding the call result? I.e. swap the roles of `ret` and `result` in the source:
```c
    result = func_80133784(1, buf1, (int)buf2);   /* the call result */
    if (result != 0) {
        ret = 0;
        if ((result & 0x8000) != 0) {
            ret = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    } else {
        ret = 0;
    }
    return ret;
```
Now the variable that gets returned is named `ret` but declared AFTER `result`... The allocation is by pseudo, not name. The returned variable is the second one; the call result is the first. Same structure → same allocation ✗.

Hmm, unless the DECL ORDER matters (the returned variable declared first?). Let me try:
(e) swap the declaration order so the RETURNED variable is declared FIRST:
```c
    int result;   /* the returned one */
    int ret;      /* the call result */
```
= M2 → 9 (same).

Hmm, M2 didn't change anything, so decl order doesn't matter here.

(f) What if `result` is assigned in a way that makes it a *copy* of something in $2?

Hmm, let me try yet another approach: what if we can get the ROM's structure by making the RETURN happen in the same block as the computation? E.g. the ROM's ins 28 `move v0,zero` (dead) suggests the pin version.

Honestly, maybe the answer for item 4: the `ret` value must be copied to $3 — this happens because $2 is occupied by `result`. Since the returned value in the ROM is in $2 and computed in place (ins 29-33: lbu/xori/sltiu all in $2), the `result` pseudo must be $2.

What if the source returns the value DIRECTLY (no variable) in the byte-check path and 0 in the others? I showed that gives 3 return sites — but the ROM's structure has the dead `move v0,zero` at ins 28, which a direct-return source wouldn't have ✗ (the direct-return version would have: the byte check → sltiu; the mask path → move v0,zero; the ret==0 path → move v0,zero = 3 sets, but no DEAD store).

Hmm, wait: is ins 28's `move v0,zero` really dead? The path: ins 27 `beqz v1,+0x8c` (mask == 0 → jump to ins 34/35?) Hmm, +0x8c = ins 35? Let me recompute the addresses: ins n at +0x4n → ins 34 at +0x88, ins 35 at +0x8c. The label "+0x8c" = ins 35 = `lw ra,36(sp)` (the epilogue) and "+0x88" = ins 34 = `move v0,zero` ✓.

So: ins 25 `beqz v1,a4fc` = +0x88 → ins 34 (`move v0,zero`) → the ret==0 path returns 0 ✓.
ins 27 `beqz v1,a500` = +0x8c → ins 35 (the epilogue) → the mask==0 path returns v0 as-is = the value set at ins 28 (`move v0,zero`) ✓✓ — so ins 28's `move v0,zero` is NOT dead: it's the return value for the mask==0 path!

I misread earlier: ins 28 `move v0,zero` is in the "mask set" path, and the byte check (ins 29-33) is the "mask set AND byte check" path. So the source's `result = 0;` (in the then-branch) is live for the mask==0 sub-path ✓ and overwritten by the byte check ✓.

So the structure:
```
if (ret != 0) {
    result = 0;                       // ins 28
    if ((ret & 0x8000) != 0) {        // ins 26-27
        result = (byte == 0x15);      // ins 29-33
    }
} else {
    result = 0;                       // ins 34
}
return result;
```
✓ exactly the current source. And the sets: 3 (`move v0,zero` at 28, `sltiu` at 33, `move v0,zero` at 34) ✓.

So the direct-return variant would also have 3 sets but the ORDER differs (the "return 0" in the mask path would be after the byte check block).

OK. Let me try the direct-return variant anyway (cheap):
P1:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        if ((ret & 0x8000) != 0) {
            return *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
        return 0;
    }
    return 0;
```
Hmm, in this version the "return 0" (mask path) is the block AFTER the byte-check block → the ROM has it BEFORE (ins 28, then the byte check). Block order in the ROM: ins 28 (move v0,zero) then ins 29-33 (byte check) → so the "mask path" block comes first, then the byte check block. In P1's source, the byte-check block comes first (it's the then-branch of the inner if) and the "return 0" is the else/fallthrough → the compiler might lay them out either way.

Let me test P1.

Also P2: the same but with the inner if inverted:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        if ((ret & 0x8000) == 0) {
            return 0;
        }
        return *(unsigned char *)((char *)buf2 + 6) == 0x15;
    }
    return 0;
```

Let me test both.

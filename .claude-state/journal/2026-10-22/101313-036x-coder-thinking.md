---
ts: 2026-10-22T16:13:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YkXx4hTQfwonnxQAINeL
---
The base candidate's .s:
```
la $4, D_80120194+25996    ; a0 = &D_80120194 + 0x658C  (p)
j $L472
$L473:
  j $L479
  move $2,$3               ; return it (v0 = v1)
$L472:
  la $3, D_801202A0        ; it = v1 = &D_801202A0
  beq $4,$3,$L480          ; if (p == it) goto zero
  move $2,$0
...
```
So GCC used `la` (load address pseudo) and assigned p to a0, it to v1. The target:
```
lui v1,%hi(D_80120194)
addiu v1,v1,%lo(D_80120194)   ; it = &D_80120194 in v1
lw? ...
addiu a0,v1,25996             ; p = it + 0x658C in a0
```
Wait target[0..1] lui v1; addiu v1; target[2] (same as mine[2] which is `j $L472`); target[3] addiu a0,v1,25996. Hmm, in mine: [0] lui a0 (part of la), [1] addiu a0, [2] j, [3] nop (delay slot). In target: [0] lui v1, [1] addiu v1, [2] j, [3] addiu a0,v1,25996 — so the target fills the branch delay slot with `p = it + 0x658C`, i.e. it computes p *after* the branch instruction using v1 (it). Mine computes p as a constant `la` before the branch and leaves the delay slot nop.

So the target does: it = &D_80120194 (v1); p = it + 0x658C (a0); then goto test. Mine: p = &D_80120194 + 0x658C (a0) [constant folded]; then... wait, where does mine load `it = &D_80120194`? The .s shows only `la $4,D_80120194+25996` — no separate it load! Because cse folded `it = &D_80120194` into `p = it + 0x658C` (constant) and then `it` is dead until reassigned at test. So the first `it` value is never materialized — correct, because it's unused before being reassigned (copy: return it — but copy is reached only after test's assignment; hmm, the `copy` label returns `it`, and it's set at test. So the first `it` is indeed dead).

So the target keeps `it = &D_80120194` in v1 even though it's dead! Why? Because the target's C had the launder (asm) making it live. Lever-free, the first assignment is dead and gets folded into p as a constant. The target has `lui v1; addiu v1` (it) then `addiu a0,v1,25996` (p) — a register-held it. That's the launder's effect: the asm makes `it` opaque/live so p is computed from it.

Lever-free, can we make the compiler keep `it = &D_80120194` and compute p from it? Options:
1. Make the first `it` *live*: use it somewhere before the reassignment. The only path that uses the first it is `p = it + 0x658C` (which gets folded) — so if p is computed via a form that doesn't fold: e.g. `p = (s32)(D_80120194 + 0x658C)` is the same fold.
2. Use a pointer type: `u8 *p = D_80120194 + 0x658C;` → `la a0, D_80120194+25996` (same fold).
3. Make `it` a pointer: `u8 *it = D_80120194; u8 *p = it + 0x658C;` → cse folds the address arithmetic into `la a0, D_80120194+25996`? Probably yes (find_best_addr / plus folding). Actually with pointer arithmetic, GCC's RTL is the same.
4. Introduce a *second use* of `it` that cse can't fold: e.g. `p = it + 0x658C; ... use it`. The target's code uses `it` later (after test's reassignment) but that's a different value.

Hmm. So the target's `it` first value is dead in the C semantics, yet the target computes it. That means the target's C made it live: the launder asm `"=r"(it)` is an output — the asm *sets* it, so it's live after the asm. But cse can't fold through the asm. Then `p = it + 0x658C` uses the asm output. And the asm output is dead after p... but the asm remains because it's volatile.

Lever-free: we need `it` to be a real value used by `p = it + 0x658C` such that the compiler doesn't fold the constant. Since `it = (s32)D_80120194` is a constant address, folding is inevitable unless the value is "opaque".

BUT: maybe there's a real-C way to make the address non-constant-foldable: use a *volatile* read of a pointer? Or make `it` come from a *global pointer variable*? Is there a global holding &D_80120194? Hmm.

Wait — what if we write `it = (s32)D_80120194;` and then use `it` in a way that forces it to a register before p: e.g. `if (it == 0) return 0;`? That adds a branch (extra insns). No.

What about computing p first from D_80120194 and then assigning it = p - 0x658C? That's the same constant fold in reverse: `p = (s32)D_80120194 + 0x658C; it = p - 0x658C;` → it = D_80120194 constant → la v1. Hmm! That might generate `la v1, D_80120194` (it) and `la a0, D_80120194+25996` (p) — two la's, not `addiu a0,v1,25996`. The target has p = it + 0x658C computed from the register. So no.

What if p is computed as `it + 0x658C` where `it` is a *pointer variable of a different type* that prevents folding? E.g. `it = (s32)(u8 *)D_80120194;` same.

Hmm, what about declaring `it` as `volatile s32`? Then `it = (s32)D_80120194` stores to the stack (extra insns). No.

What about making the first assignment and p computation *inside a different basic block* so the fold is blocked? The target computes it and p in the entry block before the j. If we reorder: 
```
it = (s32)D_80120194;
p = it + 0x658C;
```
that's the current order.

Alternatively, make `it`'s first value live across the branch by using it in the `copy:` block? The copy block returns `it` — but that's the test-assigned it. If we changed the flow so `copy` can be reached with the first it... The control flow: body → if (*(u16*)it==0) goto copy. At that point it is the test value. So no.

Hmm. What if we reverse the roles: compute p from the *first* it and keep it live by making the test comparison use it? No, the target's code uses `it` = D_801202A0 at test.

So lever-free, the first `it` is dead and GCC folds. The target keeps it because of the launder. This looks like the `flow-unused-result`-ish wall? No, more like "cse-const-addr" — cse folds the constant address that the target keeps in a register. Actually the target keeps `it` in a register and derives p from it. The wall tag cse-const-addr fits: "cse folds or substitutes a constant/absolute address the target keeps base-relative".

Hmm, but maybe there's another angle: make the address computation not a plain constant by using a *pointer arithmetic* through a variable that is genuinely non-constant. For instance, we could define the address via a global array whose base is a *pointer variable*? Not available.

Wait — what about `it = (s32)D_80120194; p = it + 0x658C;` and then `it` is reassigned at test. What if the reassignment happens via a different variable and we *swap* which variable holds what? The target's test loads D_801202A0 into it (v1) and compares with p (a0). Mine does the same but with a0=it? Let me check: mine's .s: `la $4, D_80120194+25996` (p in a0); `la $3, D_801202A0` (it in v1); `beq $4,$3` (p==it). Target: `lui v1; addiu v1` (it = &D_80120194); `addiu a0,v1,25996` (p); `la a0? no` — at test, target does `la ?` Let me see the full target. The diff says target[3] addiu a0,v1,25996 and mine[8] beq a0,v1 vs target[8] beq v1,a0. So at test, target's it (D_801202A0) is in v1? But v1 held &D_80120194 earlier. Reused. And a0 = p. So target: beq v1,a0 → compares it(v1) with p(a0). Mine: beq a0,v1 → compares a0 with v1 where a0=p, v1=it. Same operands, just swapped in the encoding. The diff counts them as different because operand order differs (beq a0,v1 vs beq v1,a0) — a real byte difference.

So the target's register assignment: it = v1, p = a0. Mine: it = v1 too (at test), p = a0 too! Wait: mine's `la $3, D_801202A0` = v1, and `beq $4,$3` = beq a0,v1. Target's `beq v1,a0` — if target's it is in v1 and p in a0, the encoding is beq v1,a0. Mine has beq a0,v1. The *operand order* in the branch differs because the C comparison order differs: mine compares `it == p` → beq a0,v1? Hmm, GCC emits `beq $4,$3` for `if (it == p)` where $4=p? Confusing.

Anyway, the target's sequence:
```
lui v1,%hi(D_80120194)
addiu v1,v1,%lo(D_80120194)   # it = &D_80120194
j test
addiu a0,v1,25996             # p = it + 0x658C  (delay slot)
test:
la v1, D_801202A0             # it = &D_801202A0
beq v1,a0,zero
move v0,zero
body:
...
```
Mine:
```
la a0, D_80120194+25996       # p = &D_80120194+0x658C
j test
nop
test:
la v1, D_801202A0             # it
beq a0,v1,zero
move v0,zero
```
So the only differences: (1) target materializes it=&D_80120194 in v1 and computes p from it in the delay slot; mine folds p and nops the delay slot. (2) branch operand order.

So we need `it = &D_80120194` to be a live register value, and p computed from it, and the p computation scheduled into the delay slot.

Idea: make `it`'s first value live by using it *later* — but semantically it's overwritten. Unless we restructure so the first it is used in the test comparison? No.

Idea: use `p = it + 0x658C` where `it` is a *pointer to a struct* and the addition is done via a pointer that cse can't fold because... hmm, cse folds `(plus (symbol_ref) const)`.

Idea: Make `it` an `int` derived from a *cast through a function-like* opaque? No asm allowed.

Idea: `it = (s32)D_80120194;` then `p = it + 0x658C;` but with `it` declared as a pointer and `p` as s32, e.g.:
```
u8 *it; s32 p;
it = D_80120194;
p = (s32)(it + 0x658C);
```
The RTL: it = symbol_ref; p = plus(it, 0x658C). cse folds symbol_ref into the plus → constant. Same.

Unless the pointer arithmetic is done in a *wider type* or with a cast that produces a different RTL shape, e.g. `p = (s32)(u8 *)((u32)it + 0x658C);` same.

Hmm. What about making the *second* assignment's value come from the first? No.

OK, what about the `flow` angle: make the first `it` "used" in a way that costs no instructions in the target? The target has no extra instruction for it besides the lui/addiu that mine folds into the la. So if we make `it` live but the use is dead-code-eliminated... impossible (if live, it's used).

Wait — actually, is the first `it` really dead in the target's semantics? The target materializes it (lui/addiu) and uses it for p. If we make it live via a *use that the target also has*, e.g., the `p` computation itself is the use. So we need p's computation to not fold. 

Hmm, what if we write `p = it + 0x658C` where `it` is a `s32` and then use `p` in a *comparison against a constant* that makes GCC compute p from it? No.

Let me think about cse's folding rules: `it = symbol_ref` gets REG_EQUAL symbol_ref. `p = it + 0x658C` → fold_rtx substitutes it → plus(symbol_ref, 0x658C) → constant expression → emitted as `la`. To prevent, `it` must not have a REG_EQUAL or must be in a register (hard). cse creates a REG_EQUAL for a SET of a constant. 

What if `it` is set from a *memory load*? Not available.

What if `it` is set by a *conditional* that cse can't fold: e.g.
```
it = (s32)D_80120194;
if (it == 0) it = (s32)D_80120194;   // identity-ish, adds branch
```
No.

Hmm, what about `it = (s32)(D_80120194 + 0);` — same.

What about using the *address of the global's element*: `it = (s32)&D_80120194[0];` same symbol.

I think this is a genuine cse-const-addr wall (the target's register-held constant address is only kept by the launder). BUT the moves list has MATCHes for launder with similar "constant address" shapes? Let me look at the moves lines 154-160 etc. E.g. func_8018483C WALL cse-const-addr-copy; func_80183098 WALL cse-const-addr. Those are walls.

However, this item's residual is only score 4, and maybe a small C change flips it. Let me look at what the prior coder tried: gen_addr_*, gen_bound_*, gen_decl_*, gen_loop_*, gen_order_*, gen_use2_*. All score 4. Plus b1-b5, n2, n3. They tried ~40 variants. So the prior coder spent a lot here. The remaining idea space: make the first `it` live.

Idea: restructure the goto soup into a plain C form that produces the same CFG but with `it` live. E.g.:
```
s32 func_8012C2D0(void) {
    s32 p, it;
    it = (s32)D_80120194;
    p = it + 0x658C;
    it = (s32)D_801202A0;
    if (it == p) return 0;
    do {
        if (*(u16 *)it == 0) return it;
        it += 0x10C;
    } while (it != p);
    return 0;
}
```
Would that produce the same CFG? The original has `copy: return it;` reached from body when *(u16*)it==0. A do-while with return it inside. The prior coder's gen_loop_dowhile got 12 (16 ins) — different.

The target CFG:
- entry: it = A; p = it + K; goto test
- copy: return it
- test: it = B; if (it == p) goto zero; 
- body: if (*(u16*)it == 0) goto copy; it += 0x10C; if (it != p) goto body
- zero: return 0

Note the `copy: return it` block is a separate label; it's the target of `beq $2,$0,$L473` then `j $L479; move $2,$3`. So copy just returns it (v1).

The lever-free base already reproduces the CFG exactly (19 ins, same count) — only the it/p register story differs. So the CFG is fine.

Now, can we make `it` live at entry without adding insns? If `it`'s first value is live at the `copy` block... The copy block is reached only from body, where it is the test value. Unless we make the CFG such that the copy block can also be reached from entry — no.

Hmm! What if we compute `p` from `it` *and* also use `it` in the test comparison? The test sets it = B before comparing. No.

What if we swap: `p = it + 0x658C;` then `it = (s32)D_801202A0;` — the target order is it=A, p=it+K, goto, test: it=B. Fine.

Idea: make `p` a pointer variable of a type that forces the addition to be in a register: e.g. `u8 *p = &it[0x658C]`? Same.

Idea: use `it` as `s32` but write `p = (it + 0x658C) | 0;` — cse folds constants too.

Idea: make the constant 0x658C come from a variable `s32 off = 0x658C;` then `p = it + off;` — the prior coder tried gen_bound_var (score 4). The RTL: off is a constant pseudo; cse folds it too.

Hmm, what if `off` is a *volatile*? That adds a load.

What if `p` is computed as `it + 0x658C` where `it` is obtained from a *parameter*? No params.

OK. What about the *second* launder? The test's `it = (s32)D_801202A0` — in the lever-free base, does cse fold that? Mine's .s has `la $3, D_801202A0` (a register), so no folding there because `it` is used multiple times (lhu, +=, compare). Good — only the first launder matters.

So the wall is: the first `it` value is dead except for p, and cse folds it into p's constant. The target keeps it in a register.

Can we make the first `it` value live across the branch in a way that costs nothing? The target's code: it=A is in v1, used for p; then at test, v1 is overwritten with B. So it=A is live only up to the delay slot. That's exactly what a non-folded `p = it + K` gives.

So we need to defeat the fold of `it + K` where it = &A. 

What if `it` is assigned via a *union or struct field* whose address... no.

What if `it` is a *global* variable? `it` is a local; if we made it a global, the code would use memory. No.

What about making the assignment `it = (s32)D_80120194;` and then `p = it + 0x658C;` where `it` is declared `volatile`? Volatile local forces a stack store/load (extra insns).

What about `it` declared as `register`? No `register` vars allowed (constraint: "no `register` vars").

What about making `it` a `s64`? Then the address arithmetic is in DImode — different insns.

What about `p` declared `long long`? no.

Hmm, what about making the *first* assignment's value non-constant by using a cast that GCC's fold can't see through, like `it = (s32)(u8 *)D_80120194;` — same.

`it = (s32)(void *)D_80120194;` same.

`it = (s32)&D_80120194[0];` same.

`it = (s32)D_80120194 + 0;` same.

So it's a wall: cse-const-addr. Best score 4.

Hold on. Let me reconsider: what does the score "4 (MIXED)" count? Register pairs a0->v1 x4, v1->a0 x1, plus 2 replaced insns. That's the diff cost. Could a different register assignment make it 0 without fixing the fold? If mine's it=A were kept in v1 (not folded), we'd match. If we could get the compiler to put p in a0 and it=A in v1 but still fold p... no, folding removes it=A entirely.

What if we reorder the C so that `it` is assigned *after* p is computed from a *constant*, e.g.:
```
p = (s32)D_80120194 + 0x658C;   // la a0
it = (s32)D_80120194;           // la v1  (dead? no — it's live until test reassigns? it's dead)
```
GCC would delete the dead `it = ...`. Unless we use it: no.

OK so the fold is the wall.

BUT WAIT. Maybe there's a subtlety: the target's `it = &D_80120194` is in v1, and `p = it + 0x658C` is in a0. What if we write the C so that `it` is *live* because the `copy` block returns it and the compiler can't prove copy is unreachable from entry with it=A? The copy block returns `it`; if the compiler's dataflow thinks the path entry→copy exists... The CFG: entry jumps to test; copy is reached only via body. But GCC's flow analysis: `it` at copy has the test-assigned value. So it=A is dead. Unless we restructure the CFG so the copy block is reachable from entry (e.g., fallthrough). E.g., write:
```
it = A;
p = it + K;
if (something) goto copy;   // extra branch — no
```

Hmm.

What about making `it` = A used in the `test` comparison by comparing *it* to p *before* reassigning? The target does `test: it = B; if (it == p)`. If we instead write the comparison as `if (p == it)`? That changes the branch operand order (mine beq a0,v1 vs target beq v1,a0). Interesting! The diff shows mine[8] `beq a0,v1` vs target[8] `beq v1,a0`. That's because the C is `if (it == p)` in mine; if the target's C were `if (p == it)`, GCC would emit beq a0,v1? Hmm, GCC canonicalizes comparisons: for `if (a == b) goto`, it emits `beq a,b` in the order given (a first). Mine: `if (it == p) goto zero` → it is v1, p is a0 → beq v1,a0 expected, but mine emitted beq a0,v1. Hmm, so GCC swapped: it emits beq with the first operand being the one in $4? No, mine's beq is `$4,$3` = a0,v1. it is v1, p is a0. So GCC emitted beq p,it for `if (it == p)`. It canonicalizes so the first operand is... the register with the lower number? a0=$4 < v1=$3? No, $4 > $3. Hmm.

Whatever — if I flip the C to `if (p == it)`, maybe the encoding flips to beq v1,a0 matching the target. But that's only one of the 4 differences; the fold remains. Actually the "register pairs a0->v1 x4" are the it=A register differences. Let me not chase the branch order alone.

Let me reconsider whether the first `it` could be made live by a *real* C construct that adds no instructions: 

What if we compute p *before* it? `p = (s32)D_80120194 + 0x658C; it = (s32)D_80120194;` — it is dead, deleted.

What if `it` is used as the base for p via a *cast to a pointer and a dereference* that doesn't happen? no.

What if the copy block returns a *different* expression that keeps it live? `copy: return it;` — if we write `copy: return it + 0;` same.

Hmm, what if we restructure to:
```
it = (s32)D_80120194;
p = it + 0x658C;
goto test;
copy:
    return it;
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
body:
    ...
```
That's the base. The only use of the first it is p.

I'm fairly convinced it's a wall. But before declaring, let me check: is there maybe a *different* target interpretation? Let me dump the target fully to see if maybe the target's `it = A` is used in the branch delay slot and the `p` is a0 — yes, confirmed by the diff.

Alternative real-C idea: make `it` a *pointer* and p a pointer, then the comparison `if (it == p)` etc. The insn count is the same. The fold of `it + 0x658C` → still a constant.

Alternative: make the addition non-foldable by making the addend a *value loaded from memory* that equals 0x658C? E.g. is there a global with 0x658C? No, and it'd add a load.

OK: WALL cse-const-addr, best 4. But the task requires ≥20 min and ≥30 scored tries for a WALL. The prior coder's tries (gen_*, b*, n*, w*) — do they count as "scored tries on that item" in this session? They were scored by sc.sh presumably (the files exist). I have run sc.sh on ~40 of them (that's 40 scored tries by me, though reused candidates). The rule likely means genuine attempts. Let me add a batch of new attempts targeting the fold, then wall.

Let me generate a focused batch (10-15 variants) around:
- `it`/`p` types and expressions
- flip comparison order
- alternate CFG spellings (goto/if)
- use of the address in a second statement
- `p` computed via pointer arithmetic
- splitting the declaration/initialization
- s16/u32 widths for p (p is an address, must be 32-bit)

Let me check the prior gen_* contents to avoid duplicates. Let me list their key lines.

Actually, the prior coder's variants.py generated these; I saw the script. gen_addr_* (5), gen_bound_* (7), gen_use2_* (6), gen_decl_* (4), gen_loop_* (2), gen_order_* (2) = 26, plus b1-b5, n2, n3, x1, w1-w3. So ~36 already.

New ideas not covered:
1. Flip comparison operand order: `if (p == it) goto zero;` and `if (p != it) goto body;`
2. Rewrite the CFG with if/else instead of gotos (gen_loop tried do-while/for).
3. Make `it` live via a *dead* second use that cse can't delete: e.g. `if (0) ...` — folded away. `p = it + 0x658C; it = it;` — dead.
4. Compute p as `it + (0x658C)` where 0x658C comes from a `static const`? fold.
5. Use `s32 *` casts.
6. Assign `it` from `D_80120194` as `(s32)(D_80120194 + 0)` — same.
7. Use `u32 it;` — gen_decl_u32 tried.
8. Use `p = (s32)&D_80120194[0x658C];` — constant fold → la a0.
9. Make `it` a `char *` and `p = it + 0x658C` — same fold.
10. Swap the order: `p = it + 0x658C;` after `goto test`? The goto splits blocks; the p computation is before the goto in the target's delay slot (after the j). In C, `p = it + 0x658C; goto test;` — GCC may move p after the j (delay slot) if the fold is a register computation. In the target, the addiu is in the delay slot. Mine's `la` is before the j (because it's a constant la, and the delay slot is nop). So if we could get the register-based computation, the delay-slot placement follows.

11. Use a *volatile* read? no.

12. Key new idea: make `it`'s value live by using it in the `test` block *before* reassignment, e.g.:
```
test:
    if (it == p) ...   // uses the first it? No, must be B.
```
Not semantically equivalent.

13. What if we swap the assignment order in the source: `p = (s32)D_80120194 + 0x658C;` and drop the `it = A` assignment entirely, then `it` is uninitialized before test — the target still materializes it=A. No.

14. What if we make the `copy` block's return value come from a variable that is live from entry? E.g.:
```
it = A;
p = it + K;
goto test;
copy:
    return it;
```
If the compiler believed `copy` is reachable from entry... no.

15. Use `switch`/computed goto? no.

16. Make the first `it` assignment's value *not* a symbol_ref by loading it from a *local array* initialized with the address? Adds stores.

Hmm. Given the wall tag library, cse-const-addr is the right tag. The prior coder's 36 tries + my ~5. I need ≥30 scored tries; I've scored 40 files. I'll do one focused batch of ~12 genuinely new spellings, then record WALL with best 4.

Actually wait — there's one more promising idea: the target's `it` is in v1 and `p` in a0. What if the C's `it` is a *u32* and p computed with an *unsigned* addition? Same fold.

Another: make `it` an `s32` but assign `it = (s32)D_80120194;` where the cast is to a *pointer-sized type through a struct member*: e.g. `((s32 *)D_80120194)[-1]`? no.

Another thought: what if the fold happens because `it` is dead; if we make `it` *live* by using it in the `copy` block's return via a *different variable* that is NOT overwritten? For example:
```
s32 it, q;
it = A;
p = it + K;
q = it;        // q live? q is never used -> dead
goto test;
copy:
    return q;   // q live! copy returns q = A
```
But that changes semantics: the copy block must return the *test* value of it (the target's copy returns the current it, which is B). Actually wait — is that true? Let me re-read the target: `copy: return it;` and `it` at that point is the test-assigned value (B + increments). So returning q=A would be wrong.

Unless... hmm, what if the original C's copy block returned a variable that is the *first* it? The decompiled C says `return it` and it is reassigned at test. So no.

OK. But here's a thought: make the first it live by using it in an expression whose result is dead but that cse can't remove — e.g. a store to a local that is later... no, dead stores are removed.

17. What if `p` is computed *in the copy block*? no.

I'll accept the wall. But let me first check the `--explain` or the moves for this function's "class" — maybe a previous shard cracked a twin (func_8012C2D0 is an h_exact shared body). The moves grep for 8012C2D0 found nothing. There might be twin functions with the same body shape (e.g. other launder items in moves). Let me grep moves for "0x658C" or "D_80120194" or "25996". Also check the research index? The brief only says read moves.md. Let me grep moves for 'D_8012' / '0x658C'.

Let me do a quick grep and then the batch.

Also, I must be time-aware: the developer wants me to finish only this item. I've spent ~30 min on item 1 and ~10 min here. Let me be efficient: do the batch, then decide, write rows/log, done.

One more important check: the MATCH requirement for headers is score 0 on *every* includer. w2/w3 score 0 on includer 0 but keep the launder. If I find a lever-free 0, I must run sweep.sh (141 includers) — that's ~141 × ~1.5s ≈ 3.5 min. Doable in the background if needed.

Let me generate the batch now. I'll write a Python script (under .run, per rules) to create variants, then sc.sh them.

Batch ideas (new, not in prior files):
1. cmp_flip: `if (p == it) goto zero;`
2. cmp_flip2: also `if (p != it) goto body;`
3. ptr_types: `u8 *it; u8 *p;` with `it = D_80120194; p = it + 0x658C;` and `it = D_801202A0;` comparisons; `it += 0x10C;` — note the `copy: return it;` must return s32 → cast. Careful with return type: `return (s32)it;`.
4. ptr_it_only: `s32 it; u8 *p;` `p = (u8 *)it + 0x658C;`
5. addr_elem: `it = (s32)&D_80120194[0];`
6. decl_init: `s32 it = (s32)D_80120194;` (init at decl) — prior gen? Not seen; gen files were addr/bound/decl/use2/loop/order. Init-at-decl not tried.
7. p_init: `s32 p = (s32)D_80120194 + 0x658C;` then `it = (s32)D_80120194;`? no, it dead.
8. two_stmt_p: `p = it; p += 0x658C;` — this makes p's value a two-step: p = it (register copy!) then p += K. cse may fold p = it (copy propagation) → p = symbol; then += K → constant. Hmm, but a real second set might prevent folding of `it`. Worth trying.
9. p_plus_var: `s32 k = 0x658C; p = it + k;` — tried (gen_bound_var).
10. goto_order: move `p = it + 0x658C;` after `goto test;`? Can't (unreachable).
11. body_while: `while (*(u16*)it != 0) { it += 0x10C; if (it == p) break; } return it;` — different CFG, probably differs.
12. it_dead_store: `p = it + 0x658C; *(volatile s32 *)0 = 0;` no.
13. return it in copy via pointer cast.

Honestly, the fold is structural. But let me run a batch of ~12.

Actually, here's a genuinely promising idea I haven't considered: **make `it` live by using it in the `body`/`copy` path via a value that GCC's flow can't prove dead — e.g., make the `goto test` conditional on something opaque but with the same target**. No.

Another: **the target's `it = A` is live because the launder asm's output is used by `p`, and the asm also has a *use* of it.** The asm is `"=r"(it) : "0"(it)` — output tied to input. In RTL, the asm sets a new pseudo from the input; the input (symbol) is in a register. Lever-free, we need a real operation that reads `it` and writes `it` — i.e., a real second set! "launder->real 2nd set pv &= mask" is a known MATCH move. Here, a real second set of `it` that preserves the value: is there one? E.g. `it = it + 0;` → folded (identity). `it |= 0;` → folded. `it &= -1;` → folded. GCC folds all identities.

What about a non-identity that happens to preserve the value because of the value's properties? E.g. `it = it & 0xFFFFFFFC;` — D_80120194 is 4-byte aligned (0x...194 is 4-aligned: 0x194 = 404, /4 = 101, yes aligned). So `it &= ~3` preserves the value! Is that an identity launder? It's a real operation (andi) but would emit an `andi` instruction — extra insn, not matching the target (which has no andi). So no.

`it = it >> 2 << 2;` — two insns, and the moves say such identity launders don't count.

So no.

Therefore: WALL cse-const-addr, best 4.

Hmm, wait. But the target's code has `it` materialized and `p = it + K`. What if we make the *p computation* the thing that keeps it: `p = it + 0x658C` where the compiler *can't* fold because `it` is assigned from a *conditional move* or a *function call*... no.

Let me look at this from the score's perspective: maybe a small change to the *branch operand order* alone plus keeping the fold could get score 2 or so, but not 0.

OK let me run the batch, then write the WALL row.

Actually, hold on. Let me reconsider the CFG: the target has `it = A; p = it + K; goto test;` and mine (lever-free) has `p = &A + K` with the delay slot nop. What if we *reverse* the two statements:
```
p = (s32)D_80120194 + 0x658C;
it = (s32)D_80120194;
goto test;
```
`it` is dead → deleted. Score similar.

What if we write `it = (s32)D_80120194;` and `p = (s32)((u8 *)it + 0x658C);`? Same.

Let me also consider: maybe the target's `it` register is NOT the address of D_80120194 but something else. The diff target[0..1]: lui v1,0x0; addiu v1,v1,0 — the immediates are 0 in the object (relocations). Hmm, both immediates are 0! In mine: lui a0,0x0; addiu a0,a0,25996 — the addend 25996 = 0x658C. So target's it = a symbol with addend 0, mine's p = symbol+0x658C. Consistent with my analysis.

Wait, but target[3] addiu a0,v1,25996 = p = it + 0x658C. Yes.

OK, batch then wall. Let me also double check that a lever-free body with the launder *replaced by nothing* is really the best (score 4) and that no other candidate gets below 4. The prior gen_use2_cmp_other got 7; gen_loop_for 10. So 4 is best.

Let me run the batch.

Actually — one more idea, and I think it's the real one: **the target's `it` value is live because the C assigns `it` twice and the *first* assignment is not dead if `p` is computed from `it` via a `goto`-split block that the compiler's cse can't see through**. cse runs per function, so no.

And another: **make `it` a global-scope temporary?** no.

Let me just do the batch. I'll write variants via a script under the item dir.

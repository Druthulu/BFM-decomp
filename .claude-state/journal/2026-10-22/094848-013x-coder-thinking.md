---
ts: 2026-10-22T15:48:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NhGzqzXS6xqxEHCFwJXP
---
Excellent! Huge progress: score 19, 86 ins vs 84. The copy itself is now correct (no diff in the copy region!). The remaining differences:

1. Register allocation: mine uses s2 for self, target s1. That's because `obj` pin $16 = s0? Actually $16 = s0. Target: s1 = self, s0 = obj. Mine: s2 = self. Why? The frame: mine saves ra at 60, s2 at 56; target saves ra at 56 and s1 at 52? Target: move s1,a0; sw ra,56(sp). Mine: sw s2,56(sp); move s2,a0; sw ra,60(sp). So mine has one extra saved reg (s2 and s0?), i.e. mine uses s2 for self while target uses s1 (so target only saves s0,s1; mine saves s0,s2 = still 2). Hmm, the stack size differs by 4? mine: sw s2,56, sw ra,60. target: sw ra,56. Target probably sw s0,52? not shown in diff (aligned).

2. `addiu s1,sp,16` in mine vs target `nop`?? Wait, "replace mine[9:10] target[8:9]: addiu s1,sp,16 | nop". That means mine computes the address of m into s1 early, target doesn't (target uses addiu a1,sp,16 at each call: "move a1,s1 | addiu a1,sp,16"). So in target, `&m` is re-derived at each of the 3 calls instead of kept in s1; mine keeps it in s1.

So now the struct copy introduced a local-alloc difference: `m`'s address is held in a register (s1) in mine, and self got s2 instead of s1. Target re-derives addiu a1,sp,16 at each call and doesn't hold &m.

This is a register-pressure/priority issue. Since mine keeps &m in s1, self needs s2 → extra saved reg? Actually both save 2 callee regs (s0 for obj pin, plus s1 or s2). Frame sizes: mine 64, target 56? The diff shows ra at 60 vs 56, so mine frame is 64, target 56? Hmm target: sw ra,56; maybe sw s1,52, sw s0,48. mine: sw s2,56, sw ra,60, sw s0? So mine frame 64 vs target 56: 8 bytes bigger. That's a real difference (score 19 counts everything).

The copy region matched exactly (great!). Now to fix: make &m not live in a register; and self in s1.

The target: `addiu a1,sp,16` at each call → the address of m is rematerialized. Why would mine hoist it? Because &m is a constant address (sp+16) used 3 times; cse replaces it with a register if cheap? Actually cse may create a reg for the stack address when it has multiple uses. Hmm.

Wait — maybe the struct copy's base (a1 = &D_800AE620) is what differs? No, copy region matched.

Let's get the full picture: what does the target look like exactly? Let me dump both full instruction lists. I can use --explain? Or use `--try ... --keep` to keep the candidate object and objdump it, and compare to target. The build target object path: let me find.

Better: write a small script to get the residual with all instructions. Actually the diff already shows all differences; the remaining diff is: s2/s1 swap (8 register pairs), the &m hoist, and stack offsets.

Root cause: `m`'s address held in s1 in mine. If I can make the compiler not hold &m, then self can take s1 (the target's choice). Since &m is used as `(void *)m` 3 times and `*(Mat32 *)m` twice, all uses. In target all 5 uses are addiu a1,sp,16 (rematerialized) — including `*(Mat32*)(obj+0x34) = *(Mat32*)m` (lw from sp). Hmm.

Why does mine keep it? Possibly because the struct copy `*(Mat32 *)m = D_800AE620` created a base pointer... no, the copy region matched.

Maybe the difference is that in mine, `m` was used as a value in the copy expression `*(Mat32*)m`, generating an address pseudo with a longer live range, and cse decided to keep it. Whereas the original had `m[0]=t0` etc. Hmm, but the original with launder scored 0 and had `src[0]`... and m stores as direct sp offsets.

Alternative: use the struct copy differently to avoid making &m an address pseudo that gets a register. E.g. `*(Mat32 *)(m + 0) = D_800AE620;`? Same.

Or do the copy with an explicit pointer that is not `m`? Like `int *d = m; *(Mat32 *)d = D_800AE620;` — that would make d a pseudo and might be worse.

Hmm, wait. Let me reconsider: maybe mine's `addiu s1,sp,16` comes from local-alloc assigning the stack address to s1 because it's used 5 times; the target's compiler decided to rematerialize. The difference could be the *priority* of the pseudo (birth insn). If the copy's first use of &m is the block-move base (an address used in 8 loads/stores), cse might create an equivalence... 

Actually, is the struct copy region really identical? The diff shows no differences in the copy region, meaning mine's copy is lw 0(a1)... with a1 = &D_800AE620. Yes.

So the only issue now is stack address &m and self's register. Let's look at target more fully to understand which regs it uses. Let me get the target disassembly. The diff alignment shows target[2:4] move s1,a0; sw ra,56(sp). So target prologue: move s1,a0; sw ra,56(sp); sw s1,52(sp)?; sw s0,48(sp)?; addiu sp,sp,-56.

Mine: addiu sp,sp,-64; sw s2,56; move s2,a0; sw ra,60; ... so mine uses s2 for self and s0 for obj, saves s2,s0,ra at 56,60,+? frame 64. Target uses s1 for self, s0 for obj, saves ra,s1,s0 in frame 56.

If I eliminate the &m pseudo in s1, then s1 frees and self takes s1 (local-alloc prefers lower regs? Actually allocno order). Let's try.

How to prevent hoisting &m? Ideas:
- Use `(void *)m` — already.
- Make the calls take `m` via different spellings: `(void *)(m + 0)`, `(void *)&m[0]`, `(void *)m` — all same.
- Insert a fake re-set: `t0 = 0;`? no.
- Use `m` as `int m[8]` and do the struct copy via a local pointer that dies: `{ int *q = m; *(Mat32 *)q = D_800AE620; }` — the address of m still used later.
- Maybe the hoist is caused by the copy expression itself: in mine the base of the copy is `m`, and its address pseudo (sp+16) is used by the block move AND the 3 calls; cse merges them into one reg. In the original (score 0 with launder), the stores `m[0] = t0` use sp+16 directly (no address pseudo? Actually `m[i]` is a memory ref with constant offset, cse may not create a reg for it) and the calls use `(void *)m` (addiu a1,sp,16 each). So cse didn't create a reg.

Hmm, but with the struct copy, cse might create the address reg because the block move takes a pointer. Yet the target also had a struct copy? Wait, no: the target is a specific ROM body; the compiler that produced it is the same. The target's copy is from `D_800AE620` — but in the target, the *source* of the copy is a global; maybe the original C was `m[0]=D_800AE620.w0; ...` etc. Hmm, but the target's copy pattern matched mine exactly, which is a strong sign the target also came from a struct copy... or from 8 separate loads (the scheduler grouped them 3+3+2). Both produce the same insns if the base is a register.

OK, let me try to kill the &m register. Options:

(a) Move the struct copy to use `m` indirectly: `*(Mat32 *)(m + 0) = D_800AE620;` probably identical.
(b) Use two separate half copies: `*(Mat32 *)m = D_800AE620;` is one. Could split into `*(Mat32 *)m = ...; ...` no.
(c) Make the three call args use `m` via a volatile? no.
(d) Reorder: put the copy *after* the first call? Not correct semantics but m is uninitialized then... Actually the target's copy happens before RotMatrixX.
(e) Declare `m` as a struct variable: `Mat32 m;` then `m = D_800AE620;` and `RotMatrixX(..., &m)` — then &m is still an address. Hmm.
(f) Increase register pressure so the allocator prefers rematerialization? Unlikely.
(g) Make the address of m *not* a single pseudo: use `(void *)((u8 *)m)` etc. CSE canonicalizes.

Hmm, maybe the &m pseudo is not from cse but from the struct copy: the block move base `m` is an address; after the copy, `m`'s address is used in calls; cse records it. If I make the copy's base differ syntactically but same address, cse still merges.

Alternative: split the copy so no single instruction references `m` as an address — i.e., go back to individual element loads but keep the *source* base in a register. That's the original idea: the problem was only the source address being folded. So use a struct copy *from* a pointer to a local? Hmm: 
```
int *p = (int *)&D_800AE620;   // still constant
m[0] = p[0]; ...
```
cse folds.

What about copying the global into a local struct variable first?
```
Mat32 tmp = D_800AE620;   // block move global -> stack tmp
*(Mat32 *)m = tmp;        // block move stack tmp -> m
```
That adds a copy (too many insns).

Alternative: make the source pointer's value non-constant-foldable via a *real* second set that the target's code tolerates? No, must match exactly.

Hmm, what about using the global directly as a struct: `m` copy is fine; the issue is &m. Let me test whether dropping the src pin and using a struct copy but with the *call args* taking `(void *)&m[0]` changes anything. Probably not.

Wait — maybe the &m reg is because `m`'s address is taken and used as `void *`; local-alloc gives the address pseudo a register if its live range is long. In target it's rematerialized. The difference might be *register pressure*: target has one fewer pseudo live (self in s1, obj s0, &m none). Mine has self in s2 because s1 is taken by &m — circular.

The allocator's decision may hinge on the *number of uses* of the address: 5 in mine. Target rematerializes at 5 uses. Why? Maybe because in target the address pseudo was never created — because the C didn't have a struct copy. So target's C probably had `m[i] = t` stores (direct sp offsets, no address pseudo) plus calls with `(void *)m` (address used, but cse may rematerialize since it's a "cheap" address). Hmm, but the calls in mine are `addiu a1,sp,16` vs target `addiu a1,sp,16` — identical in target. In mine they're `move a1,s1` (because s1 holds it).

So the struct copy *created* the address pseudo (block move base is a pointer operand, and it's the first use, giving the pseudo a birth priority), making cse/local-alloc keep it.

Solution: keep the source base in a register (needed) without making &m an address pseudo that gets allocated. What if the copy destination is spelled as `m[0]` etc. but the source as a pointer register with an offset? We need 8 loads from one base. E.g.:

```
int *s = (int *)&D_800AE620;   // folded by cse -> per-load lui
```
What if we use a `Mat32 *` and copy elements: `m[0] = D_800AE620.w0;` — no, each field access is a constant address again.

Key insight from moves: "pv &= 0xFF000000 (compound assign) = a REAL 2nd SET of the pinned pv, kills the sched1 birth boost" and "p = *abase; p += 0x2D (self-reassign stales cse (plus p K) equiv)". These are about killing cse's equivalence. Here cse's equivalence is the constant address. In func_80183098: "only an opaque (asm) base keeps lh 4(s1)" → wall.

But here, maybe there's a real C trick: make the base address depend on a value cse can't fold, e.g. compute it from a variable that happens to be the constant:
```
int base = (int)&D_800AE620;  // cse folds
```
Hmm.

What about using the global via a pointer obtained from a function? No.

Alternative: use `D_800AE620` as a struct copy *into a register-held pointer* then load? No.

Let's reconsider: the copy from global to m in target keeps the source in a1. Why a1? Because a1 is free (param_1 copied to self). The target's base = a1. If the target C had `*(Mat32*)m = D_800AE620;`, the block move base is &D_800AE620 (a constant address) and expand_block_move would use a1 as the base register — exactly. And the destination &m... in expand_block_move the destination is a stack address; it would use `addiu a1,sp,16`? No, it would use a separate reg or offsets from sp. Actually expand_block_move for a 32-byte move with a memory destination at sp+16: it emits loads from src base (a1) and stores to sp+16+off directly. So no destination address register is created! Then the 3 calls each do `addiu a1,sp,16`. And self gets s1. That's exactly the target.

So in target's C, the struct copy base a1 = &D_800AE620 and the destination is a memory ref sp+16. In mine, same? The diff showed the copy region identical. But mine created `addiu s1,sp,16` early — that's the destination address of the copy being materialized. Why? Possibly because in mine, `m` is used as `(Mat32 *)m` — a pointer-typed cast — and cse created the equivalence from the copy's dest? Hmm, but the copy dest in RTL is `(mem (plus sp 16))` not a pointer.

Wait, mine[9] is `addiu s1,sp,16` at instruction 9, right after the prologue. Target[8] is nop. The copy is at ~mine[9..]. So the `addiu s1,sp,16` is the base for the copy's *stores* (dest), then stores use `sw v0,0(s1)`. Meanwhile target uses `sw v0,16(sp)` etc. So the difference is the destination base of the block move: mine materializes it into s1, target uses sp offsets.

Why would GCC materialize the dest base? Because of MIPS's `move_by_pieces`/expand_block_move using `copy_addr_to_reg`? The destination address is `m` = sp+16 which is not a valid offset-only base? Actually sp+16 is fine.

Hmm — maybe because the source base (a1) and dest base both... no.

Maybe the difference is `*(Mat32 *)m = D_800AE620;` vs the target's actual C. If the target C were `*(Mat32 *)(obj + 0x34) = ...` no.

Could the target's copy be from a *struct assignment* `m_struct = D_800AE620;` where m_struct is a Mat32 local? Then dest is a struct variable at sp+16. Same thing.

Alternatively the target's C might be `*(Mat32 *)m = D_800AE620;` but with `m` declared as `Mat32 m;` (not int[8]) — then `m` as a value expression yields the address directly. Hmm.

Let's think about why GCC materialized dest base in mine. The MIPS block move code: if the destination is a MEM with a PLUS (sp, 16), it uses it directly. Unless... the copy is emitted by `expand_assignment` with a `(mem (plus))`, fine.

Wait, maybe mine's `addiu s1,sp,16` is not the dest base but something else: at mine[9] right after prologue, before the copy. Then `sw v0,0(s1)`? The diff didn't show the stores as differing, meaning mine and target stores aligned — so mine's stores must be `sw v0,16(sp)` too, not `sw v0,0(s1)`. Hmm, if the diff showed no difference in the copy region, then the copy instructions are identical (same registers/offsets). So s1 isn't used in the copy. Then what is `addiu s1,sp,16`? It's the address of m computed early and held for the 3 calls (target re-derives addiu a1,sp,16 at each call). So mine keeps &m in s1.

But why does mine keep it? The calls use `(void *)m`; cse sees the same address 3 times and may create a reg. Target doesn't. In the original with launder (score 0), the calls also used `(void *)m` and were `addiu a1,sp,16` each. So the struct copy made the address pseudo live longer: the copy's dest `m` is a use at the top, so cse created a reg covering from the copy to the calls (5 uses, live across 3 calls). In target, the copy's dest is sp-relative and doesn't create a pointer pseudo.

So: avoid the struct copy's destination being `m` as a pointer. Use `memcpy`? `memcpy(m, &D_800AE620, 32)` — a libcall, not good.

Use explicit element stores but with a source base register. How to get a source base register without the launder? The known wall is cse-const-addr: cse rematerializes the constant. But maybe a struct copy from the global *into a local struct* is fine, and then element stores from that? Too many insns.

Alternative: copy from the global into m using a *pointer variable* that is set to &D_800AE620 and also used... cse folds.

Hmm, what about doing the copy in the *other direction* in terms of addressing: `m[0] = D_800AE620.w0; ...` all 8 — the compiler would do 8 lui+addiu+lw (like the failing w1, score 20), then 8 sw to sp offsets. Not good.

What if the source base is a *struct pointer parameter*? No.

What about using `Mat32 *s = &D_800AE620;` and then a *loop* copying 8 elements? A loop would use a register base and an induction variable, but the target has no loop (unrolled 3+3+2).

Hmm. But wait: is the residual's remaining difference really only register naming? Let me look: score 19 counts each differing instruction. The diff shows 8 register-pair differences (s2->s1), the prologue differences (3 delete + 2 insert), addiu s1 vs nop, 3 move vs addiu, several lhu/lw base reg differences, and epilogue. That's consistent with "self in s2 vs s1" + "&m in s1 vs none". If I fix the &m hoist, self goes to s1 and everything aligns.

So the whole item reduces to: prevent cse/local-alloc from keeping &m in a register, while keeping the source base in a register.

Idea: make the copy's destination not `m` but a *separate* stack object that aliases m? Not possible in C without union.

Idea: use a union:
```
union { int m[8]; Mat32 mm; } u;
...
u.mm = D_800AE620;
RotMatrixX(..., u.m);
```
Then the copy dest is u.mm (sp+16) and the calls use u.m. Same address. cse may still create a pseudo from the union member address.

Idea: `*(Mat32 *)m = D_800AE620;` but make the calls not use `m` directly: `RotMatrixX(..., (void *)(m + 0));` etc. cse canonicalizes.

Hmm. What if the destination of the block move is a *local pointer variable* that is dead after? e.g.
```
{ Mat32 *d = (Mat32 *)m; *d = D_800AE620; }
```
The address pseudo d is set and used once → cse folds it into the move (dest mem sp+16), and the later `(void*)m` uses are separate address pseudos with 3 uses → maybe cse keeps one reg? In target, they're rematerialized.

Actually why does cse create a register for an address used 3 times? Normally cse replaces *loads* of the same address, and for address expressions it creates a reg when the address is "expensive" or used multiple times. `sp+16` is cheap (a PLUS of sp and const) — cse's `find_best_addr` may rematerialize it. In the target it did. So why not in mine? Because of the block move? The block move dest is `(mem (plus sp 16))`, which cse may have registered as a known address... hmm.

Let me test variants quickly:
1. `*(Mat32 *)(m + 0) = D_800AE620;`
2. `{ Mat32 *d = (Mat32 *)m; *d = D_800AE620; }`
3. `Mat32 *d = (Mat32 *)m; *d = D_800AE620;` (d lives)
4. struct-typed local: declare `Mat32 mm;` use `mm = D_800AE620;` and pass `&mm` / `(void*)&mm`.
5. Use a union.

Also: maybe declare m as `Mat32 m;` and use `m.w0` etc. for the calls? Calls take void*.

Let me test candidate 2 and 4 and the union. Each dt.sh run ~2s. Good.

Also consider that the `int m[8]` array vs `Mat32` struct matters for the copy: with `Mat32 m;`, `m = D_800AE620;` is a struct assignment; passing `(void *)&m`.

Let me write these variants.

Another thought: the target's copy source base a1 and the *three calls* use a1 too. In mine the copy source base is a1 as well (matched). Good.

Let me generate variants in one script and score them all with sc.sh. But sc.sh uses one line per candidate — good.

Note: sc.sh scores only the first TU (includer 0). Fine for iteration; final check with sweep.sh.

Let me create the variants.

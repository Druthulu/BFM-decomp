---
ts: 2026-10-22T00:34:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_WX866LaBZV7ACPCpwYdz
---
The sibling uses fixed trip counts (20) — no lever there (it's a different TU with a different target asm).

So for our item, the count is 20 or 16 based on unk70.

Now, how to make the count opaque in plain C? Options:

(a) Make the count come from a *field* directly in the loop test — but the `if (n != 0)` test must remain a separate branch in the target. Hmm, wait: maybe I can restructure so the *test* is on something GCC can't fold, but the *loop bound* is the known count. E.g.:

```
if (n != 0) { do {...} while (i < n); }
```
The test `n != 0` is what GCC folds (since n ∈ {20,16}).

What if the test is on a *different* variable that is opaque? E.g. `if (n != 0)` → `if (cnt != 0)` where cnt is loaded from memory? no.

(b) What if the *count* variable is assigned from a *function call*? e.g. `n = func_8012BD14(a0) & 0x1F;`? Changes semantics.

(c) What if the count is *recomputed* in a way that's opaque: e.g. `n = 0x14 - (((Unkstruct_800B5CB8 *)a0)->unk70 >= 2) * 4);` — same value, known.

(d) What if we use a *pointer* to compute the count: e.g. the count = the number of elements between two pointers? constant.

Hmm, (e): What if the *loop* is restructured so that the test `n != 0` is *not* redundant by construction: e.g. the loops use a *different* variable that GCC can't relate to n. Since the values are the same, cse would relate them. Unless the second count is computed from a *different field* that has the same value at runtime but GCC can't prove: e.g. `unk70 >= 2` for loop 1 and `unk70 >= 2` for loop 2 — the same.

Hmm, what if the count for loop 2 is derived from a *different but equal* expression, e.g. `n2 = (unk70 - 2 >= 0) ? 0x10 : 0x14`? Same value; CSE would unify (both are the same computation on the same field → the values are equivalent but the *pseudos* are distinct unless CSE proves them equal — cse's make_regs_eqv WOULD make them equal since they're the same expression). Hmm, but would it? CSE works on the RTL: two computations of the same expression on the same reg → equivalent → yes, unified.

But hold on: would the *tests* then be merged? The tests are `if (n2 != 0)`. Even if n2 is a different pseudo with the same value, GCC's *flow* analysis (the "known nonzero" fact) would still eliminate the test if it can prove n2 != 0. It can prove it if it knows the value range.

Hmm, so the question is: what makes GCC unable to prove "n != 0"?

In the target (with the lever), n is opaque → unknown.

So I need an opaque count. The count comes from `unk70 >= 2` — a *field* read. GCC knows the field's value is unknown! So `n = (unk70 >= 2) ? 0x10 : 0x14` → GCC knows n ∈ {16, 20} → nonzero.

What if the count were computed from the field in a way that could be zero? E.g. `n = unk70 >= 2 ? 0x10 : 0x14` — nonzero. What if `n = (unk70 >= 2) ? 0x10 : 0x14` but written as `n = 0x14 - 4 * (unk70 >= 2)`? Still nonzero.

Hmm, the *runtime* value must be 20 or 16 (matching the target), but GCC must not know it.

The lever achieves opacity. In plain C, opacity comes from a *load* or a *call*.

What if the count is read from a *global* that holds it? In the original game, the count was probably a global (e.g. the number of entities). Hmm! But the decompiler derived the count from the field unk70. Hmm, but the *original* code must have had an opaque count — maybe the original read the count from a global (like D_801xxxx) and the decompiler replaced it with the field-based computation? No — the decompiler's job is to match the asm; the asm has the count in s4 computed from... let me look at the target's asm: 1500: `lh v0,112(s3)` (unk70), 1508: `slti v0,v0,2`, 150c: `bnez v0,1518` with delay `li s4,20`; 1514: `li s4,16`. So the target computes s4 = 20 or 16 from the field — exactly the C. And the asm (the lever) then makes s4 opaque for the later tests.

So the original game asm has the same structure: s4 computed from the field, then the three tests on s4. The original game's compiler (a different one, or the same?) — well, the original game asm was hand-written/optimized by MIPS-GCC 2.x too, probably with the same behavior... interesting: the original asm has the three tests because the original *source* had an opaque count (e.g. read from memory).

Hmm! So the original source likely had something like:
```
n = *(u16 *)something;   /* or a global count */
```
Hmm, but the target's asm computes s4 from the field... so the count IS field-derived. And yet the original compiler kept the three tests. That suggests the original compiler couldn't fold the test either — maybe because the count was in memory (a global) and the *field* comparison was different.

Hmm, whatever. Our job: make GCC 2.7.2 (this build) keep the three tests without the lever.

The lever makes n opaque. Plain C alternative: make the count's value unknown to GCC but still correct at runtime. Options:
- `n = *(volatile s32 *)&someGlobal`? barrier lever, forbidden.
- Make the count depend on a *value GCC can't range* — e.g. `n = 0x14 - 4 * (unk70 >= 2)` — known.

Hmm, what if the count is computed as `n = 0x14; if (unk70 >= 2) n = 0x10;` and then for the later loops, the count is *re-read from the stack*? no.

What if the count is *stored* to a local and reloaded? GCC would forward it.

Hmm. What if the count for loops 2/3 is computed from a *different field* that GCC can't relate, e.g. `unk6C`? That changes semantics (the runtime value might differ).

What if the count is computed as the *difference* of two pointer values? e.g.
```
n = (u32)((u8 *)&D_8018934C[20] - (u8 *)&D_8018934C[0]) >> 1;  /* 20 */
```
constant.

Hmm, so how about this: the *trip count* could be expressed via the *table* itself in a way that GCC can't fold: e.g. the loop could iterate over a *pointer* rather than an index:
```
for (p = D_8018934C; p < D_8018934C + n; p += 4)
```
Hmm, that changes the loop shape (the target uses an index in s0 and a separate pointer s1).

Wait, actually, let me look at the target's loop structure more carefully:
```
1528: lui s5,0x0        ; s5 = &D_80189324
152c: addiu s5,s5,0
1530: addiu s2,s5,6     ; s2 = s5+6  (pointer to D_80189324[3])
1534: move s1,s5        ; s1 = s5
1538: sll v1,s0,0x1     ; i*2
153c: lhu v0,0(s1)      ; D_80189324[i]  (s1 = base + i*2, incremented by 8 each iteration)
...
1588: addiu s2,s2,8
158c: addiu s0,s0,4
1590: slt v0,s0,s4      ; i < n
1594: bnez v0,1538
1598: addiu s1,s1,8
```
So the loop uses both an index (s0) and a pointer (s1).

The lever's role: the *test* `if (n != 0)` before each loop. In the target, `beqz s4,159c` — the test is a real branch on s4.

So I need n to be opaque at each test.

IDEA: What if n is *not* a variable but the count is read from a *global* that the game uses for this? Hmm, we don't know it.

IDEA: What if we make the *first* loop's `if (n != 0)` test the only one, and the *other* loops' tests are on a *recomputed* count that GCC can't fold because it comes from a *call*? no.

IDEA (promising!): make n's value *depend on the loop's own side effects* so that GCC can't prove it's still nonzero. E.g., if the loop body modified n... but the loop body doesn't.

Hmm, what if the count is recomputed from the field *after* the loop, where the field might have been changed by the called function? GCC doesn't know that func_8012DEB8 doesn't modify the field (it's an external function) → but the *value* of the field is re-read → GCC knows unk70's value is unknown at that point! Wait: unk70 is read via a pointer (`((Unkstruct_800B5CB8 *)a0)->unk70`) — a0 is a parameter, and the called function could modify it → so after the call, unk70's value is UNKNOWN to GCC!

So if the count is *recomputed* after the first loop from unk70, GCC would know:
- n = 0x14 if unk70 < 2 else 0x10 → still nonzero! Because the *expression* is known to be nonzero regardless of unk70's value.

Hmm, right, GCC would still know n != 0.

Unless the count expression is such that it *could* be zero, e.g. `n = unk70 >= 2 ? 0x10 : 0x14` — always nonzero. What if the count were `n = unk70 * 4`? Hmm, that changes the runtime value.

OK, so the *only* way is opacity, which in plain C means a load/call.

WAIT. What about this: the count could be *read from the parameter's field* in a way that produces the right runtime value but where GCC can't prove nonzero. E.g. what if the count is `n = 0x14; if (unk70 >= 2) n = 0x10;` for loop 1, and for loops 2/3 the count is computed as `n = 0x14 - ((unk70 >= 2) ? 4 : 0)` — same.

Hmm, what if for loops 2/3 we use `n = 0x10 + ((unk70 < 2) ? 4 : 0)`? Same value.

What if we use the *sum* of two things: `n = 0x10 + 4 * (unk70 < 2)`: GCC knows ∈ {16,20} → nonzero.

What if the count were `n = (0x10 + 4 * (unk70 < 2)) & 0x1F`? Still nonzero.

What if `n = (0x10 + 4 * (unk70 < 2)) * (unk70 != 0xFFFF)`? Hmm! That's a real runtime value: if unk70 == 0xFFFF, the count becomes 0 (wrong semantics, and the runtime value differs from the target's). But GCC can't prove it's nonzero! Hmm, but it changes the semantics (if unk70 == 0xFFFF the loops would be skipped, whereas the target would run them). Since unk70 >= 2 is the condition, unk70 == 0xFFFF satisfies it → the target runs 16 iterations; my version would run 0. That's a semantic change. Not acceptable for a decomp (the C must be faithful).

Hmm, unless the multiplier is something that can't be 0 given the constraints: e.g. `n = (unk70 >= 2) ? 0x10 : 0x14` — always nonzero.

Hmm, so any *faithful* expression of the count is provably nonzero → GCC folds the test.

Therefore the only lever-free route is opacity → needs a load/call → changes the code.

CONCLUSION: item 3 is also a WALL?! Hmm, but the score was 2 (very close). The residual is only the two branch targets. Hmm!

Wait, hold on. Let me reconsider: maybe I can keep the tests by making the *loops* use *different* count variables that GCC can't relate — because the *loop bound* comparison `i < n` needs the count in a register, and the *test* `n != 0`... GCC's folding of "if (n != 0)" requires knowing n != 0. If n is a *different* variable with the same value-range knowledge, GCC still folds it.

BUT: what if the count variable for loops 2/3 is *not* provably nonzero because it's computed by an expression that GCC can't range-analyze, e.g. via a *pointer difference* or a *shift*? E.g.:

`n = 0x14 - 4 * (unk70 >= 2)` — GCC's value range: {16, 20}.

What about `n = (0x14 - 4 * (unk70 >= 2)) & 0xFFFF`? Same.

What if the count is *loaded from the stack* (a local array) — e.g. the count is stored into a local `s32 cnts[3]` and read back? GCC forwards it.

What if the count is stored in a *global*? Then it's opaque but the code changes (a store + load).

Hmm, what if the count is read from a global that ALREADY holds the right value at runtime? We'd need to know the game's memory layout. The count 20/16 is derived from unk70 — no global holds it.

OK, so item 3 = WALL, tag? The mechanism: "the empty asm makes n opaque, so the per-loop `if (n != 0)` tests survive; plain C folds them (n is provably 16/20)".

Tag: `fold-nonzero-test`? The pass: cse/flow (value range) → "flow" is in walls.txt: "flow-unused-result: flow deletes results the target computes but never uses". Hmm, this is more like "cse/range folds the redundant test". I'd name it `fold-range-nonzero` — hmm, the tag format is `<pass>-<what>`. Pass = "fold" (tree folding) or "cse". Let me use `fold-range-nonzero`.

Hmm, hold on. Wait. Before I settle: maybe there IS a plain-C way! What if the *count* is recomputed *inside* the loop-2 test from the field, and the field is read through a pointer that the *called function* could modify → GCC knows unk70 is unknown after the call → but the expression still yields {16,20}.

What if the count is `n = 0x14; if (unk70 >= 2) n = 0x10;` but the *first* loop's `if (n != 0)` is what GCC keeps, and for loops 2/3 the count is recomputed... GCC would still fold.

Hmm, what if the count for loops 2/3 is recomputed from a *different* source that's opaque but faithful: e.g. the count could be stored in the *sp arrays*? no.

What about the *param_1* field unk70 being read through a *pointer that is opaque*? The *value* of unk70 is what matters, and it's the same.

OK: WALL.

Hmm, wait. Actually, hold on! What about making the count depend on a value that GCC cannot range but is *faithful*: the count is 20 or 16 — what if we express it as `n = 0x14; if (unk70 >= 2) { n = 0x10; }` and then, for the later loops, we *reuse* the same variable but *recompute* it in a way that includes the *previous* value: e.g.
```
n = n - (n - 0x14) + ... 
```
no.

What about: the count is *recomputed* by calling a *pure* function? e.g. `n = table[(unk70 >= 2)];` where table is a local array {0x14, 0x10}? GCC folds the array read (it's a local constant array) → known.

What if the table is a *global* (static const in the TU)? A global read is opaque! But it adds a load (the target has no such load) → the code changes → mismatch.

OK. WALL for item 3. Best score 2 (c1). tries 1.

Hmm, this is depressing: 3 items, 3 walls. Let me reconsider the whole approach...

WAIT. Maybe I should reconsider what "score 0" requires. The score 2 for item 3 is due to *branch target addresses* differing. Hmm! Those are just label differences — the diff tool compares the *text* of the instructions including the target addresses. If the code layout differs slightly, the addresses differ.

Hmm, but a score of 2 with "mine 177 ins, target 177" means the instruction *count* is the same and only 2 branch targets differ. If I could make the layout match... the layout difference comes from the missing/extra branches.

Hmm! Actually, hold on. What if the *number* of branches is the same but the *targets* differ? Let me look: the target has `beqz s4,159c` at 1520 (jump to the 2nd loop's test) and `beqz s4,1618` at 159c (jump to the 3rd loop's test). Mine has `beqz s4,1694` at 30 and `beqz s4,1694` at 61 — both jumping to the same place (1694) = the end (skipping everything).

So mine has 2 tests: the first loop's test jumps to the end (1694) — wait, that skips loops 2 and 3 entirely?! That would be wrong semantically... unless mine's first `beqz` is the *first* loop's test and it jumps to... hmm, if n == 0, all loops are skipped → jumping to the end is correct! And then the second `beqz` at 61 is the *third* loop's test? Hmm, if the first test jumps to the end when n == 0, then the second/third tests are only reached when n != 0 → they're redundant → GCC removed one.

So mine has: test1 (n==0 → end), and one more test later (at 61) — for one of the loops.

The target has 3 tests chained.

So the difference is the *number* of tests: 2 vs 3. The residual is 2 because the diff aligns them.

OK so my analysis holds.

Hmm, hmm. But wait: what if I could make the *loop count variable* differ between the loops in a way that's faithful? E.g. what if the trip count for loops 2 and 3 is *derived from the table pointer*: e.g.

```
n = 0x14;
if (unk70 >= 2) n = 0x10;
```
What if instead we compute the count as the number of *elements* in the table: `n = 20` for table 1 and the same for tables 2/3 — the same.

OK. Let me think about the *other* possibility: maybe the lever's effect isn't opacity of n but something else entirely, and there's a plain-C way. Let me look at the target's asm again around the 2nd/3rd loops to see if s4 is *reloaded* or if there's something else.

From the target listing:
```
1520: beqz s4,159c     ; test 1
...
159c: beqz s4,1618     ; test 2
```
and presumably 1618: beqz s4,16xx (test 3).

So s4 (n) is tested 3 times, unchanged.

Without the lever, GCC knows n != 0 → the 2nd and 3rd tests vanish.

Plain C: to keep the tests, n must be unknown.

=> WALL. Tag: `fold-range-nonzero`? Hmm, but let me reconsider: maybe the tag should reflect the pass: the *test elimination* is done by cse/flow ("jump threading" removes the redundant branch). I'd call it `cse-redundant-test` or `flow-nonzero-fold`.

Hmm, hold on. Actually, WAIT. What if the count variable is *reassigned* in the source (a real 2nd set) between the loops, e.g.:

```
n = 0x14;
if (unk70 >= 2) n = 0x10;
...loop1...
n = 0x14;                    /* real 2nd set */
if (unk70 >= 2) n = 0x10;
...loop2...
n = 0x14;
if (unk70 >= 2) n = 0x10;
...loop3...
```
Even with a real 2nd set, GCC's value range for n is still {16,20} → nonzero → the tests are folded. Hmm, BUT: maybe not! After a *call* inside the loop (func_8012DEB8), GCC knows the field unk70 might have changed... but the *recomputation* reads it again → the value is still {16,20}.

Hmm, BUT: what if the recomputation is done via a *pointer that the callee could have modified*? E.g. `a0` is a pointer; the callee could modify `a0`'s target. So after the call, unk70's value is unknown. But the *expression* still yields 16 or 20. So n != 0 is still provable.

Unless the count is expressed as a *field value* directly: e.g. `n = unk70 >= 2 ? 0x10 : 0x14` — provably nonzero.

So the ONLY faithful way to have an unknown count is a memory read of the count itself. The count is not in memory.

CONCLUSION: item 3 = WALL. Best 2, tries 1-2.

Hmm, hmm. But hold on, hold on. Let me reconsider: is the target really "the built object with the lever"? YES. And the built object has 3 tests. And a plain-C version has 2. So the lever IS needed to match the built object.

BUT — the decompiler's *intent* is to match the ORIGINAL game asm. The original game asm (in asm/ov_SC06_008/nonmatchings/ov_SC06_008_jr_8017C294/func_8017D73C.s) exists! The comment at line 2937 mentions it. So the original asm has 3 tests too (that's why the decompiler needed the lever).

So this is a genuine lever. The question remains: can plain C reproduce it?

AH WAIT. Maybe YES — with a *different trip count expression*! What if the count were read from a *field* that holds the count in the original game? Hmm, the target asm computes s4 = 20/16 from unk70 — so no.

Hmm, so the original source must have had something like:
```
if (n) { do {...} while (i < n); }
```
where n was an opaque variable. The original game code probably read the count from a global/field. But our reconstruction reads unk70 → provably nonzero.

Wait... unless the original count was `n = unk70 >= 2 ? 16 : 20` where unk70 is a *u8* field... same.

Hmm, what if the original code was:
```
count = table_count;   /* from memory */
```
and the decompiler replaced it with the field-based computation because the asm showed the comparison `slti v0,v0,2` + `li s4,20/16`. So the original asm ALSO computed it from a field. And the original asm kept 3 tests because the original compiler (or the same compiler with a different source shape) couldn't fold.

Hmm! Maybe the original source was:
```
n = 0x14;
if (unk70 >= 2) { n = 0x10; }
if (n != 0) { loop1 }
if (n != 0) { loop2 }
if (n != 0) { loop3 }
```
and the original compiler didn't fold the redundant tests because... hmm, the same compiler should fold them.

UNLESS the original compiler saw n as *modified* by the callee! I.e., if the count variable `n` were a *global* (or a memory location), the call to func_8012DEB8 could modify it → the test couldn't be folded!

Hmm! But the target's asm keeps n in s4 (a register) across the call... so n is a local. But the *compiler* can't fold the test if the *value* could have changed — for a local in a register, the compiler knows the callee can't change it (it's a callee-saved reg, but the callee can't change a local's value).

So the original compiler must have had n in *memory*? No, the target has it in s4.

Hmm, so how did the original compiler keep 3 tests with n in a register? Because the original compiler didn't do the "n != 0 → redundant" folding? It's the same compiler (MIPS GCC 2.x)...

Wait, maybe the original source had the tests in a form that isn't redundant: e.g. the original might have been:
```
if (n != 0) { ... }   /* with n being a *pointer* count or something */
```

OR the original source might have had the count *recomputed* from a field that the callee could modify! E.g.:
```
for (i = 0; i < (unk70 >= 2 ? 16 : 20); i += 4) ...
```
Hmm, that's a constant expression per iteration.

Hmm, what if the count was *re-read from the field* each time and the field's value could be anything? Like:
```
n = *(s16 *)(a0 + 0x70);  /* the count itself, not the comparison */
if (n >= 2) n = 16; else n = 20;
```
Hmm, that's still {16,20}.

What if the original was:
```
count = unk70 >= 2 ? 16 : 20;
if (count) { loop1 }
if (count) { loop2 }
```
and the *compiler* that produced the original asm (a different MIPS GCC version, maybe 2.7.2 too) kept the tests because it didn't do that folding? Our compiler (the project's gcc 2.7.2 build) folds them. But the *target* is the project's build with the lever, so we need the lever's effect.

OK so: WALL for item 3, unless a plain-C trick exists.

Hmm, one more idea: what if the *test* is on a value that GCC can't fold because it's a *pointer comparison*? E.g. `if (cam_ptr != 0)`. no.

What if the count is a *u16* loaded from a *volatile*... no.

OK, let me try ONE candidate for item 3: use *three separate count variables*, each computed from the field separately:
```
n1 = 0x14; if (unk70 >= 2) n1 = 0x10;
n2 = 0x14; if (unk70 >= 2) n2 = 0x10;
n3 = 0x14; if (unk70 >= 2) n3 = 0x10;
```
Would GCC fold the tests? Each n is {16,20} → nonzero → folded. But maybe GCC's *jump threading* wouldn't merge the branches... Let me test it — cheap.

Also candidate: recompute n before loops 2 and 3 (a real 2nd set).

Let me test both (c2: three vars; c3: recompute).

Actually, the "recompute" version might be interesting: after loop 1, `n = 0x14; if (unk70 >= 2) n = 0x10;` — this is a REAL second set (the field is re-read after the call, so its value is unknown → but the range is still {16,20}).

Let me test c2 and c3 quickly.

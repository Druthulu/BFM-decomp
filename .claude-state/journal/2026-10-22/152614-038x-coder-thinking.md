---
ts: 2026-10-22T21:26:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_i81L4yUzmuuh6DjvN3Y5
---
Key: "What does NOT work: plain, cast, array-decay, volatile, struct-typed, unprototyped, cast-through-fn-ptr, asm between the blocks — all hoist. This class is not reachable by respelling."

But there's §195-I: "ANY second SET of a pseudo in the address's equivalence chain (in-place `p += K`, §145(b)'s `p = r;` copy, or an asm re-tie) kills the fold; the pass is cse and the gate is `invalidate`'s reg_tick++". That's a different symptom (pointer bump addiu saved by cse).

Also cookbook C0264 "SPELL THE CSE BARRIER AS A REASSIGNED POINTER". Let me read C0264 quickly.

And C0505 the move catalog.

But also: the C0164 case is about a *symbol* address (la). Here it's a *stack* address (addiu sp,32) — the target rematerialises it. The mechanism: the address used twice in one block → one pseudo with 2 refs → no remat → callee-saved reg. To crack: make the address have a *single use* per pseudo. That's exactly what the launder does. Plain C cannot split it (per C0164's 14 probes).

BUT: §195-I says any second SET of a pseudo in the address's equivalence chain kills the fold. If I can add a second set to the *address's* pseudo chain, cse's fold is killed. E.g., if the address value is computed as a variable:
```
s32 *m1 = mid;    // pseudo A = &mid
...
m2 = m1;          // copy
```
Hmm, "p = r" copy: `m1 = mid;` gives m1 = &mid. If then `m2 = m1;` — cse's reg_eqv would merge m2 with m1... but the §195-I claim is that a second SET kills the fold (reg_tick++ invalidates).

Alternatively, in-place bump: make m2 = m1 where m1 is bumped by 0? Not allowed identity.

Let me think about the actual desired output again: call1 a2 = addiu a2,sp,32; call2 a0 = addiu a0,sp,32. So the address is computed twice from sp. 

What if the source declares TWO separate arrays for the two purposes, and gcc's stack layout gives both the same slot? Impossible.

What if the source uses the address of a *parameter-derived* pointer? no.

Hmm, what about the possibility that the value doesn't need to be live across the call if call2's arg is computed from a *value that is only available after the call*? E.g. if the second call's pointer is derived from `out`'s address: `(s32*)((char*)&out + 8)` — expand folds to sp+32. But if the fold doesn't happen at expand time (because out's address is taken as a char* plus 8 with a cast), gcc may emit `addiu a0,sp,24; addiu a0,a0,8`? The target has a single addiu from sp. gcc folds constant offsets into the frame base at expand. Let's test it — cheap.

But is that an "identity address spelling"? `&out + 8` is not an identity; it's a different object + offset. Yet semantically it points to mid. Hmm, this is exactly the kind of thing the rules might call a launder. The rule: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". `(s32 *)((char *)&out + 8)` is an address spelling of the same address → identity address spelling. Not allowed.

Let me look at the third item (func_801495C4) and fourth (func_80177F84) — maybe they're easier and give insight, then come back. Actually no, focus.

Alternative idea: maybe the crack is to *avoid* the second use of mid entirely by restructuring: e.g. the second call could take `mid` but we can make the first call's arg be a *different object* that gcc gives a different slot... no, semantics.

Wait wait. Let me reconsider the target: does the target really have both calls sharing the same buffer? Target: call1 a2 = sp+32, call2 a0 = sp+32. Yes, same address.

Hmm, so how was this function originally written (before levers)? The header comment says "NEEDED DIFFERS (P36 rung B headers1)" — meaning the launder is currently needed. The task is to find a lever-free body that matches. Maybe the answer is that this one is a WALL (launder crack impossible per C0164's 14 probes: "This class is not reachable by respelling").

Indeed! C0164 says exactly this class is not reachable by respelling. That's a documented wall: cse merges the two address uses in one block → callee-saved reg; only an asm launder fixes it. Tag: something like `cse-addr-hoist` (exists? walls.txt has `cse-const-addr` = "cse folds or substitutes a constant/absolute address the target keeps base-relative" — not quite; here it's a stack address hoisted into a callee-saved reg). A new tag: `cse-stack-addr-merge` or use `global-copy-pref`? Let me define `<pass>-<what>`: `cse-stack-addr-hoist`.

But before declaring a wall I must spend ≥20 min and ≥30 scored tries on the item. Item 2 started ~15:20; now 15:28. I need ~30 tries. Let me do a systematic sweep of real-C variants (each ~1.2s). That's fine.

Let me generate many variants programmatically:
1. mid passed directly both calls (a2) - 22
2. m1/m2 both temps (nopin) - 22
3. m1 reassigned (c1) - 7
4. mid via &mid[0] vs mid
5. m1 = &mid[0]; m2 = mid;
6. temps declared with different order/scope (block-local for call1)
7. mtx without launder but with a temp/2nd set
8. statement order permutations
9. do-while(0) wrappers
10. init at decl
11. s32 mid[2] → separate mid0/mid1 scalars? no, must be an array.
12. use a union
13. pointer reuse: `pin` reused?

Let me also try: block scope for the first call's temp:
```
    {
        s32 *m1 = mid;
        call1(mtx + 0x34, pin, m1);
    }
    call2(mid, &out);
```
The block scope may make m1 block-local → local-alloc remat (reg_basic_block >= 0 and n_refs==2?). Actually local-alloc's remat path requires reg_n_refs == 2 && reg_basic_block < 0 — hmm, that says reg_basic_block < 0 (i.e. NOT block-local) allows remat. Whatever, test.

Also: what if call2 gets `&mid[0]` while call1 gets `mid`? cse equates.

What about making the second use an lvalue that requires the address: `func_8012EFB8(mid, &out)` — the address is an argument.

Another idea: pass `mid` to call2 but declare mid AFTER out... offsets change (bad).

Another idea: the target's second addiu a0,sp,32 comes *after* the first call. What if the second call's arg is a value that's *live* but from a different chain: e.g. `m2 = mid;` where mid was written through between? cse kills MEM equivalences but not addresses.

Hmm, what about `register`? Not allowed.

OK, let me also consider: maybe the pseudo doesn't get s1 if the function's register pressure is higher... but we need exact match.

Actually, hold on. Let me reconsider the mechanism in *this* function. In nopin (22): s1 held the address, `move a0,s1`, and a2 = addiu sp,32 at the call. So a2 was rematerialized at the call (good) but the copy for call2 came from s1. Interesting: so gcc chose to compute a2 fresh at call1 and keep s1 for... the second use. Since P has 2 refs (call1 arg + call2 arg), and local-alloc's remat requires n_refs==2 && reg_basic_block < 0 → P is function-scope, 2 refs → remat should fire! But it didn't; it got s1.

Hmm, maybe because the two "uses" are 3 refs (the address pseudo also used in a copy). Whatever.

Let me try to think about what would make the *second* use rematerialize too. If P has 2 refs and remat fires for one of them... 

Different idea: make the address used exactly once per pseudo by giving the second call a *copy through memory*. For example:

```
s32 *pm;
pm = mid;            // pm in a register, live across call
```
no.

Or use the fact that the buffer is written by call1: after call1, `mid`'s contents changed, but the address doesn't.

Honest assessment: C0164 documents this exact class as unreachable by respelling (14 probes). Our case is the stack-address variant of the same class. So a WALL is plausible, but the rules require ≥20 min and ≥30 scored tries. Let me spend the tries productively with a generator, and also test the "dead-reset" idea (§373) — `pb = 0;` after each use, which empties the equivalence class! From moves line 198: "DEAD-RESET CSE-BREAKER (§373): pb=&buf; call(pb); pb=0; before every site; cse's &buf address class breaks, so all 6 sites rematerialise addiu aN,sp,56".

THAT is the answer! moves.md line 198 (G15 func_8018A180, MATCH): "pb=&buf; call(pb); pb=0; before every site". So:

```
m1 = mid;
call1(mtx + 0x34, pin, m1);
m1 = 0;              // dead reset — empties cse's equivalence class for &mid
m2 = mid;
call2(m2, &out);
```
Wait, but is `m1 = 0` a "dead store" (no asm)? It's plain C: assigning 0 to a pointer that is never read after → dead, no code emitted. And it breaks the cse equivalence class. This is a documented, accepted MATCH move (G15). 

Let me test that immediately.

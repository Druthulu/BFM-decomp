---
ts: 2026-11-06T16:54:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_C3MuJMSIIgYvkVwBcsMm
---
Same 8 (sched1 reordered it back). 

Let me think about cnt vs ot allocation more concretely with a dump. Dump no_ot and look at the block-local assignments and priorities. Maybe I can see which reg t0 goes to and why.

Time check: ~10:08, 24 min in. I need to decide soon. Let me do a couple more targeted tries and then record a WALL with best 52 (or PARTIAL if something scores 0).

Actually, for a PARTIAL, keeping fp pinned is allowed only if the remaining kinds are declared. Our item kinds = "pin"; PARTIAL:<kinds still kept> means win.c scores 0 keeping only those levers. So PARTIAL:$16 would be valid if win.c (with only the fp pin) scores 0.

For no_t0c (score 5): the only issue is the missing copy pair. Let me try harder on that one since it's close.

no_t0c diff:
```
122 addiu s3,s4,12    | addiu v0,s4,12
123 --                | move s3,v0
```
Target: `addiu v0,s4,12; move s3,v0`. Mine: `addiu s3,s4,12`.

The source: `t0c = (s32)((u8 *)buf + 0xC); prim = (u8 *)t0c;` with t0c unpinned.

Target semantics: t0c in v0, prim in s3, with a move. To force this lever-free, make t0c a value that must be materialized in a register other than prim's. If t0c is used *later* (after prim is set), the compiler must keep it, but that would add a use and change instructions unless the use is free.

Where could a free use be? `primPtrs[0] = (s32)prim;` — if the source used `primPtrs[0] = t0c;` then the store would use t0c's register (v0) not s3. Target stores s3 (prim). So no.

Hmm, unless the store is `primPtrs[0] = (s32)prim;` and t0c dies at prim = t0c, so combine folds. The target's move means the original source had something else: maybe `prim = (u8 *)((s32)buf + 0xC);` where the value was computed into a temp for a different reason — e.g., the original used a *function-like* expression or the temp was `s32` in a struct.

What if the original had `prim = (u8 *)buf; prim += 0xC;`? Then: prim = buf (move s3,s4); prim += 0xC (addiu s3,s3,12). Not target.

What if `primPtrs[0] = (s32)((u8 *)buf + 0xC); prim = (u8 *)buf + 0xC;` — the store and prim use the same expression; cse would compute once in v0 then move to s3? Hmm: primPtrs[0] is stored at line 3883 (after [1],[2]). If the expression is computed once and used twice (store + prim), the value would live in v0 and then... Actually the target stores s3, and prim=s3.

Hmm, what if the original source computed `prim` later, e.g.:
```
primPtrs[0] = (s32)((u8 *)buf + 0xC);
primPtrs[1] = ...
prim = (u8 *)buf + 0xC;  // cse reuses
```
No.

Let me look at the pinned target's exact sequence again:
```
addiu v0,s4,12
move s3,v0
lui s5,0
addiu s5,s5,0     ; table
addiu s0,s4,46    ; fp
```
With the pin, t0c=$2 (v0). `t0c = buf+0xC` → addiu v0,s4,12. `prim = (u8*)t0c` → move s3,v0.

Without the pin, gcc folds t0c into prim → addiu s3,s4,12.

To keep the copy, we could make prim a *different mode* than t0c: prim is `u8 *` (Pmode), t0c is s32. Copy between SImode and Pmode — same. What if t0c is declared `s8 *`? Then `prim = (u8*)t0c` is a pointer copy (same mode). Folds.

What if t0c is `u16` or `s16`? Then `t0c = (s16)((u8*)buf + 0xC)` would truncate (andi) — extra instruction.

Hmm, what about using a union or a cast through a different type that forces a register copy? 

What about the dead-reset (C0414): 
```
t0c = (s32)((u8 *)buf + 0xC);
prim = (u8 *)t0c;
t0c = 0;
```
The dead-reset set t0c=0 after the copy: cse's forward scan sees t0c's set to 0, invalidating the equivalence... but the fold happens at combine (before? combine is after cse1, before local_alloc). The dead set t0c=0 would be deleted by flow before combine? Pass order: cse1 → jump_opt → flow_analysis → combine → sched1. The dead set is deleted in `delete_dead_from_cse` right after cse1? That function deletes dead sets from cse's tables. Hmm.

Actually the copy `prim = t0c` may be eliminated by cse1 (copy propagation) *if* prim is a copy and t0c is canonical. cse would rewrite prim's later uses to t0c? No, prim is used later and t0c dies — cse doesn't do that (it would need to know prim's value).

The fold `addiu s3` instead of `addiu v0; move s3` likely happens in combine: the insn `(set prim (reg t0c))` after `(set t0c (plus buf 12))` gets combined into `(set prim (plus buf 12))`.

A dead-reset on t0c after the copy doesn't stop combine (combine looks at the copy's source).

What if we make t0c a *volatile*? Extra loads/stores.

What if prim is declared `s32` and cast at use sites? `s32 prim; prim = t0c;` then `AddPrim(otAddr, (void*)prim)` and `prim += 0x24;` — prim as s32; the copy from t0c (s32) is a plain copy → folds.

Hmm.

What if t0c is used in the `primPtrs[0] = (s32)prim;` line as `primPtrs[0] = t0c;`? Then t0c's second use forces it live to that store. The store would use v0 (t0c) rather than s3. Target uses s3. So no.

Unless we then also set prim = t0c... no.

OK, what if the original code was:
```
prim = (u8 *)func_80010A08(...)?? 
```
No.

Let me look at the target's move differently: `addiu v0,s4,12; move s3,v0`. Note s4 = buf. Why would gcc compute into v0 then move to s3? Because t0c is a variable pinned to v0 in our src. The REAL original code produced this too (since the target is the original ROM). So the original source had a genuine two-step. Possibly:
```
prim = (u8 *)((s32)buf + 0xC);
```
where `(s32)buf` forces an intermediate? Or the original had `u8 *prim; s32 primAddr; primAddr = buf + 0xC; prim = primAddr;`.

The move suggests the original computed an address into a temp (v0) and then copied it to the pointer variable. This is what our t0c does — with the pin. Lever-free, combine folds it.

Is there a C form where combine can't fold? If the intermediate is used with a *different mode*: e.g., t0c as `s32`, prim as `u8*` — same mode. If t0c were `u16`/`s16`, the conversion would add instructions.

What if the intermediate is a *pointer to a different type*, e.g., `s32 *t0c; t0c = (s32*)((u8*)buf + 0xC); prim = (u8*)t0c;` — still same mode.

What about a cast through a union member? no.

What about an intermediate that is a *float*? no.

Hmm — what about making the copy happen through a function argument or a struct member? E.g., `struct { u8 *p; } s; s.p = (u8*)buf + 0xC; prim = s.p;` — the struct is a local; expand might store/load → extra instructions. Unless the struct is a single field in a register? GCC would scalarize.

Let me try a few and score. Time is short (10:10). Let me generate ~10 t0c variants quickly and score them in one sc.sh call.

Variants (with fp/ot pinned):
1. `s32 t0c; t0c = (s32)buf; t0c = t0c + 0xC; prim = (u8*)t0c;`
2. `u8 *t0c; t0c = (u8*)buf + 0xC; prim = t0c;`
3. `s32 t0c; t0c = (s32)((u8*)buf + 0xC); prim = (u8*)t0c; t0c = 0;` (dead-reset)
4. `s32 t0c; t0c = (s32)((u8*)buf + 0xC); prim = (u8*)t0c; t0c = t0c;`
5. `s32 t0c; t0c = (s32)((u8*)buf + 0xC); prim = (u8*)t0c; if (t0c == 0) return;` (adds branch - bad)
6. `u8 *prim = (u8*)buf + 0xC; primPtrs[0] = (s32)prim;` (no t0c at all) — probably score 5-like without the move.
7. t0c as `s32` initialized at declaration: `s32 t0c = (s32)((u8*)buf + 0xC); prim = (u8*)t0c;`

Let me test 1,2,3,7 and a do-while variant:
8. `s32 t0c; do { t0c = (s32)((u8*)buf + 0xC); } while (0); prim = (u8*)t0c;`
9. `s32 t0c; t0c = (s32)((u8*)buf + 0xC); do { prim = (u8*)t0c; } while (0);`

Let me generate from no_t0c.c by replacing the block:
```
    {
        s32 t0c;
        t0c = (s32)((u8 *)buf + 0xC);
        prim = (u8 *)t0c;
    }
```
Check the exact text in no_t0c.c.

---
ts: 2026-10-22T20:13:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xVV9YKm5ixDZjER3r5PV
---
Scratch is .run/P36/engine/score/... Not my shard. To keep dumps under my item dir, I'll splice the TU myself.

How does the TU look? src/shared/ov/func_8012B4B8.h is a header with includes? It's a header instantiated by includers. The recipe's src for a header is an includer .c. For dumps I need the includer TU with the header content. tryinc.py does header item scoring with k-th includer. Hmm, this is a header item, but only 1 includer? incl.py would tell. Let me check.

Actually the score output said `src/shared/ov/func_8012B4B8.h:func_8012B4B8`. For dumps, cc1_dumps_tu.sh takes a .c file. The header is included by a .c TU; dumps of the includer TU include all functions, but alloc_table.py takes fn.

Wait — simpler approach to get the dump: use delever_search --try --keep, then find the scratch dir and its .c file, and dump that with cc1_dumps_tu.sh, with DUMP_ROOT under my item dir. The scratch dir is deleted unless --keep, and --keep prints the object path. The scratch_src is in the same dir. That gives me the exact spliced TU. Good.

But the scratch dir is under .run/P36/engine/score — writes outside my shard. That's the tool's own behavior (allowed route). I should clean it after. --keep leaves it; I'll rm it.

Let me do that for c_struct.c and for orig.c, dump both, and compare the alloc tables. Actually first, maybe a quicker thought:

The address pseudo in c_struct has 4+ refs (dest of movstr + 3 calls). In the score-0 body the movstr dest pseudo is separate and only the 3-call pseudo exists. global-alloc's priority formula: floor(log2 refs)*refs/live*1e4. For 3 refs vs 4 refs. Live length also. If the call-arg pseudo in score-0 has priority lower than self/obj, it gets spilled → reload rematerializes the address (addiu per use). In c_struct the merged pseudo has higher priority → wins s1.

So I need the movstr dest pseudo to be a *different* pseudo from the call-arg address, i.e., prevent cse from merging. How? cse merges when both are (address of m). If the movstr dest is expressed as something cse can't equate with &m, e.g., a pointer variable that's been through a "real second set". Ideas:

- Copy via a pointer p that is assigned the address *inside a different basic block*? cse is per-block (cse1 is per basic block extended). The if-block is one basic block probably. Hmm.

- Use `(char *)m` cast for the copy destination: `*(Mat32 *)(char *)m` — identity cast, cse probably still merges.

- Use an array index: `*(Mat32 *)&m[0]` — same.

Alternative: make the call argument not &m but a value cse treats differently, e.g., `m + 0` where m is `int*`? m is an array; `m + 0` → pointer arithmetic with constant 0 → folds to &m.

What if m is a pointer to a heap? No, must be stack.

What about doing the copy into m via a *different* object that aliases the stack slot? Not possible in C.

Different approach: keep the scalar-copy form (which produces the right address behavior) but avoid the launder by making the source pointer's value opaque without asm. Options:
- Make the source address a function parameter? No.
- Use a volatile pointer? `volatile int *src = (int*)&D_800AE620;` — volatile load would prevent cse folding, but changes the loads to volatile (maybe same code? volatile loads can't be reordered/merged; the target's loads are grouped by sched, volatile might block). Also volatile is a "launder"-ish? kinds = launder only; volatile is a different mechanism, but the constraint says "no new lever of any kind" — a volatile pointer to block cse is a launder-like lever. Not allowed.
- Make the copy from D_800AE620 via a struct copy (block move) — that's the c_struct route, legit.

Hmm, but what about the *source* address being kept in a register: in c_struct, a1 holds &D_800AE620 and the loads use it — that's exactly the target. Good.

So the dest-address issue: what if the calls don't take `m` but take a pointer variable that is set *after* the copy with a real assignment, e.g.:

```
int *mp;
...
*(Mat32 *)m = D_800AE620;
mp = m;              // real 2nd set? 
RotMatrixX(x, mp); ...
```
cse will equate mp with &m (both constant address) — cse's make_regs_eqv substitutes constants too (it folds `&m` into mp and then into the call). Hmm, but the target's address is a frame-address constant, which is in cse's table as a constant; cse does substitute constants into insns if cheaper. That's why without the launder, `src` got folded.

But wait: in the score-0 body, the call arg is `(void *)m` and cse did NOT fold/merge it with the movstr dest pseudo... The movstr dest pseudo isn't a cse equivalence; movstr is expanded after cse maybe. Order: cse runs, then expand? No—expand happens before cse. movstr (block move) is expanded at expand time into load/store RTL with the address pseudo. Then cse sees the address pseudo and &m... 

OK, empirical route is faster: try a batch of candidate spellings and score them. The key: separate the call-arg address pseudo from the copy dest pseudo, and lower the call-arg pseudo's priority so it gets spilled (rematerialized).

Batch ideas:
a) m as `int m[8]`, copy with `*(Mat32 *)m = D_800AE620;`, calls with `(void *)&m[0]`? identity.
b) Copy with dest `(int *)m`? 
c) Copy the other direction with a loop: `for (i=0;i<8;i++) m[i] = ((int*)&D_800AE620)[i];` — loop may unroll into block move; cse folds source address into each load (lui each) → bad.
d) Copy via `Mat32 tmp = D_800AE620; *(Mat32*)m = tmp;` — extra copy.
e) Calls with `(void *)(m + 0)` where m is int*: same.
f) Give the call argument a local `void *mp = m;` declared at top and assigned after the copy... cse merges anyway, but the merged pseudo's birth is after the copy — the movstr dest pseudo dies at the last store, then mp is set. Two different pseudos with non-overlapping lives; cse might merge them (making one pseudo live from copy to call) or not. Worth testing: `mp = m;` right before calls.
g) Declare m as a `Mat32` struct, copy `m = D_800AE620;`, and call with `(void *)&m`. c_d4 = 19.
h) Put the copy inside a separate scope/block: `{ Mat32 *d = (Mat32 *)m; *d = D_800AE620; }` c_d2 = 19.
i) Change the order: calls take a pointer computed from a variable that's not the array, e.g. `int *p = m; p[0] = ...` no.

Another idea: make the address pseudo *not* rematerializable-cheap but force the allocator's hand by making the call-arg expression different, e.g., pass `(void *)(m + 0)` — no.

Actually, maybe reverse: force the address into a callee-saved reg *deliberately* but make self/obj use fewer regs? No, target uses s1 for self.

Wait. Look again at target: s1=self, s0=obj, and the address pseudo spilled/remat. In mine: s2=self, s0=obj, s1=addr. So the allocator chose addr over self. That's suspicious: self has many refs. Unless... self's pseudo and addr's priority: self is set once (move s,a0) and used ~10 times, live the whole function. Priority = log2(refs)*refs/live. For self: refs ~12, live ~80 → 3*12/80*1e4 = 4500. For addr: refs 4, live ~20 → 2*4/20*1e4=4000. Close. So the addr could beat self. In target's version, addr has refs 3, live ~20 → 1*3/20*1e4=1500, loses.

So yes: reduce the call-arg address pseudo's ref count/live length. The merged pseudo in c_struct has 4 refs (3 calls + 1 copy). In score-0 it has 3 refs and loses. So if I can get the copy dest pseudo separate, it'll be 3 refs and lose → remat. 

How to prevent cse merging? cse equivalence for address constants: cse inserts a REG_EQUAL note maybe, and `cse_insn` handles (symbol_ref) and address constants. Merging happens if the same value expression appears. Both are (plus (reg fp) (const 16))? or (addressof)? In gcc 2.7, address of local is (plus (reg fp) (const N)) — after reload. Before reload it's a pseudo assigned from `virtual_stack_vars_rtx + offset` maybe via (addressof). cse can equate them.

But hold on: in c_struct, does the movstr dest address pseudo actually merge with the call-arg? The evidence `addiu s1,sp,16` before the copy, in the beqz delay slot, suggests a single pseudo born early. If it were only the call-arg pseudo (3 refs) created after the copy, it'd be born after the copy... In score-0, `addiu a1,sp,16` appears in each call delay slot, i.e., born at each use (remat).

Alternatively, maybe the difference is that in c_struct the *source* a1 is not available? No.

Empirics. Let me write a batch of ~10 candidates and score them. Candidates are cheap (~2s each?). sc.sh runs sequentially. Let me create them.

Candidate list (all from c_struct base):
1. mp variable assigned after copy:
```
        *(Mat32 *)m = D_800AE620;
        mp = m;
        RotMatrixX(..., (void *)mp);
```
with `int *mp;` declared.
2. Same but `mp = &m[0];`
3. `mp = (void *)m;` void*.
4. Copy with `d` pointer then calls with `(void *)m` (c_d3 = 19, already).
5. Copy via `*(Mat32 *)m = *(Mat32 *)&D_800AE620;`
6. m declared as int[8]; copy with `memcpy`-like? no.
7. Put the copy after computing a pointer used for calls: `mp = m; *(Mat32 *)m = D_800AE620;` then calls mp → the pseudo born before copy; cse may merge; likely same as c_struct.
8. Use `Mat32 m;` + `m = D_800AE620;` + calls `(void *)(int *)&m` (c_d4 19).
9. Split copy into two halves: `*(Mat32 *)m = D_800AE620;` is 32 bytes; Mat32 is 32 bytes (4*4 + 2*2 + pad + 3*4 = 16+4+12=32). Could copy as two 16-byte structs? e.g. define a 16-byte type and copy twice: `*(Blk16*)m = *(Blk16*)&D_800AE620; *(Blk16*)(m+4) = *(Blk16*)((int*)&D_800AE620+4);` Hmm, that changes the load grouping (4 lw then 4 sw vs 3+3+2). Target is 3,3,2 → block move of 32 bytes with max 3 regs? The movstr expansion uses up to 3 registers per iteration? Interesting: 8 words with 3 loads at a time. That's gcc's block move with MIPS movstr pattern: it moves in chunks of 4? 3,3,2 = 8. Yes, the standard block-move for 32 bytes uses 3 regs then 3 then 2 (or 4+4). So one block move of 32 bytes.

Let me just run the batch. Also try:
10. `m` as int[8] and copy via `*(Mat32 *)m = D_800AE620;` then calls via `(void *)((char *)m)` — identity cast, cse may still merge.

And a different angle: make the call-arg address pseudo die between calls by giving each call a different expression that cse can't merge: e.g., three different pointer variables each assigned before its call:
```
p1 = m; RotMatrixX(..., p1);
p2 = m; RotMatrixZ(..., p2);
p3 = m; RotMatrixY(..., p3);
```
cse would merge p1,p2,p3 into one (same constant). Unless each p is assigned in a separate statement and cse equates them... it will.

Hmm. But wait — maybe the target's source passes the address via a *different base*: e.g., the calls use `m` where m is declared as `Mat32 m;` and the movstr dest is... same.

Let me look at this from the "what does the allocator need" angle: the call-arg pseudo needs priority below self's ~? Let me get the actual alloc table for c_struct and see priorities. That'll tell me the threshold. Let's dump.

Plan: run --try --keep on c_struct, capture the scratch dir, dump with cc1_dumps_tu.sh using DUMP_ROOT under item dir, run alloc_table.py, read the addr pseudo's row.

The scratch .c is in .run/P36/engine/score/<alias>__<fn>/p<pid>/. --keep prints object path. Let me do it.

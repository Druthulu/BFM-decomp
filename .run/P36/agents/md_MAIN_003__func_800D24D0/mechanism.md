# func_800D24D0 — score 0, ZERO levers (P36 S104 e38)

(a) Residual (start 4, COUNT): the target loads `D_800EC9B8` TWICE from one shared base (`lw s0,0(v1); lw v0,0(v1); … sltiu v0,v0,1;
    sw v0,0(v1)`); the lever-free body's second load was forwarded from `s0` by cse (`sltiu v0,s0,1`), one instruction short. The tree
    kept a `"memory"` barrier between `s0 = *pb;` and `*pb = (*pb == 0);` to stop the forward.

(b) Pass + decision: cse, `cse.c` lookup of the second `(mem D_800EC9B8)` hits the `(set s0 (mem))` entry and substitutes `s0`
    (`cse_insn`, the `src_eqv`/`lookup` path). What blocks it in the original: an intervening STORE whose alias status cse cannot
    prove — the 8-byte struct copy `sp10[0] = *(D24D0_Rect *)&D_800EC9D0` (expanded as lwl/lwr/swl/swr to the frame) — cse's
    `invalidate` on a MEM store drops every in-memory hash entry it cannot prove disjoint (`cse.c` `invalidate`/`refers_to_mem_p`, the
    frame-based `(plus sp 16)` store vs the `symbol_ref` load), so the second read survives. sched then hoists the copy above the load
    pair (`lw s0`/`lw v0` land right after `swr`) — the target's order.

(c) Moves that closed it (all inside the existing `{ s32 *pb = &D_800EC9B8; … }` block, the pointer keeps the ONE `lui/addiu` base):
    1. `s0 = *pb;` moved ABOVE the struct copy; `*pb = (*pb == 0);` stays below it — the copy's stores sit between the two reads.
    2. (readability, byte-neutral) the `goto join` chain rewritten as `if (D_800EC9F0 != 0 && (r = … % …) != 0) { … } else { px block }`.
    Proven on bytes: score 0 for both the goto text and the structured text.

(d) GENERATOR PROPOSAL: when the residual is `insert lw rX,0(base)` + `replace sltiu/… rX,sK → rX,rX` (a second read of the same global
    forwarded from the first read's register), and the body has an aggregate/struct copy (or any store cse cannot disambiguate: a
    frame/stack destination, an unknown pointer store) nearby, move the first read ABOVE that store and leave the second below it
    ("split a load pair around an opaque store"). Byte-neutral test: the store must not alias the global.

(e) Did NOT work: dropping the `pb` pointer (plain `s0 = D_800EC9B8; copy; D_800EC9B8 = (D_800EC9B8 == 0);`) — score 29: each access
    rematerialises its own `lui`, the target shares one `addiu v1` base for all three (the pointer is what keeps the address in a reg
    and is in body_free already); dropping the `px` block at the same time also changed the cross-jump shape of the `else` tail.

(f) Method: the residual's "insert lw" read as a cse forward at once (METHOD step 2/3: the S102 "count first" note). One try on the
    obvious reorder, then one more to keep the base pointer. Nothing fell short.

(g) STRUCTS: `D_800EC9A4..D_800EC9F0` is plainly one struct (a CD-stream state: `D_800EC9B8` buffer parity, `D_800EC9D0..D6` a RECT, `D_800EC9CC`
    index, `D_800EC9F0` flag). Giving it a struct type would not change THIS pass decision: the forward is blocked by the frame store, not
    by the global's access form. It would, however, remove the two `pb`/`px` pointer blocks (the shared-base `lui/addiu` would come from
    the struct base instead) — worth testing in the structs phase, byte-neutral in principle.

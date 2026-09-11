# func_800348A8 (src/800_b_2.c) — S104 agent e2 — CLOSED at 0, ZERO levers

## (a) The residual
Score 9, REG-caller, 29 vs 29 instructions: the loop counter `i` and the second walked pointer `q` (= p + 6 bytes) swap
`$a1`/`$v1` (target: i = `$v1`, q = `$a1`; mine: i = `$a1`, q = `$v1`). Every other register, the instruction count and the
order were already identical.

## (b) The pass and the decision
global.c allocation order. `allocno_compare` (global.c:587-603) ranks by `floor_log2(refs)*refs/live`:
lever-free: q (loop.c's giv r87) 9 refs / 13 live = 20769; i 9 refs / 18 live = 15000; p 8/18 = 13333. q goes first and
takes `$v1` (the first call-clobbered reg not conflicting — `$v0` is the loop temps', `$a0` is excluded in pass 0 because
`hi` prefers it, `regs_someone_prefers`, global.c:953); i then takes `$a1`. The target needs i ahead of q.
Refs are counted by flow BEFORE combine, weighted by loop depth (flow.c:2067 `reg_n_refs[regno] += loop_depth`).

## (c) The moves that closed it (proven on bytes, alloc table re-read after)
1. `return i + 1;` -> `return ++i;` — the RTL becomes `i = i + 1; $v0 = i;` (2 more uses + 1 more set of i inside the
   loop, each worth 2 at loop depth 2 => refs 9 -> 13); combine then folds the pair back into `addiu v0,v1,1` (i is dead
   after), so zero bytes change. Priority 21666.7 > q's 20769.2 > p's 13333.3 => i = `$v1`, q = `$a1`, p = `$a2`. PROVEN
   (`tools/alloc_table.py a9`: r74 refs 13 live 18 pri 21666.7, first in the `.greg` order line).
2. (readability, byte-neutral) the tree's explicit second pointer `q = p + 3` deleted: loop.c creates exactly that giv
   itself (`record_giv` loop.c:4341, the `p+4` address combined into it as `-2(q)` by `combine_givs` loop.c:5494). The
   `five`/`lo`/`hi` locals deleted too: loop-invariant motion hoists `5`, `arg0 & 0xFFFF`, `arg0 >> 16` to the loop head in
   source order, which is the target's order. The loop is a plain `for`.

Final text (body.c):
```c
p = D_800A46E8;
for (i = 0; i < 8; i++, p += 0x2A) {
    if (p[0] == 5 && p[2] == (arg0 & 0xFFFF) && ((arg0 >> 16) == 0 || p[3] == (arg0 >> 16))) {
        return ++i;
    }
}
return 0;
```

## (d) GENERATOR PROPOSAL
When a register residual is a swap between a loop counter and another loop-carried pseudo and the counter's only extra
use is `return i + K;` / `x = i + 1` on an exit path, rewrite it as `return ++i;` (or `i += K; return i;`): refs rise by
3 x loop depth with zero bytes (combine folds the increment into the result copy); check `floor_log2(refs)*refs/live`
against the rival in `alloc_table.py` first.

## (e) What did not work (bytes)
- 156 enumerated spellings (loop form do/for/while x condition nesting/flat/continue x increment order x u16*/u8* x
  invariants inline / as locals / hi-first) all 9 or worse: none changes refs/live of i or q.
- Two `return i + 1;` sites: 18 — loop.c turns `i + 1` into its own giv (extra `li a1,1`, extra increment).
- Indexing `D_800A46E8[i * 0x2A + k]` instead of walking p: 31 — three separate givs (D+0, D+4, D+6), not combined.
- An unused second parameter (to make `$a1` ever-live; regs_used_so_far, global.c:332-360): 9 — flow deletes the dead
  parameter copy; also every call-clobbered reg is "used so far" anyway (global.c:353-355), so this channel is inert.
- lo/hi as locals declared hi-first: 16 (order change).

## (f) Where the method fell short
Nothing blocked; the allocation table settled it in one line once the refs formula was applied. The history.txt search
never proposes changing an expression's side effects (`i + 1` -> `++i`), which is the move; that belongs in a generator.

## (g) Structs
A `Slot54` struct type for `D_800A46E8` (fields u16 type @0, u16 @4, u16 @6, size 0x54) would only re-spell `p[0]`,
`p[2]`, `p[3]` as fields; the addresses are the same `(mem (plus p K))` and the decision here is a refs count in global.c,
not an aggregate/scalar alias question — structs would not have changed it (not needed; tested u8*-cast spelling: same 9).

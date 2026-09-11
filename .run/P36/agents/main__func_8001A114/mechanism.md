# func_8001A114 (main, src/800.c) — T7 agent e20 (S104)

**Result: score 0, lever-free** (no pin, no asm, no volatile, no do-while added). Levers 2 -> 0 (the two NEEDED
`"=r"(c) : "0"(c)` launders on the state-0 CdControl's constant arguments). Signature unchanged. Whole-object check on
the `--try --keep` object: `.text` (101,572 bytes), `.data`, `.rodata` byte-equal to
`.run/P36/delever/baseline/src/800.o` (`scratch/cmpobj.sh`).

The move: the pointer `p`, which the tree assigned in BOTH state 0 (`&cdReq_cdResult`) and state 2 (`&D_800AE740`),
becomes two variables, one per case (`result`, `mode`); the `c0`/`c1` launder temps are gone (literals passed).
```c
    case 0:
        func_800434BC();
        result = &cdReq_cdResult;
        func_80043830(1, 0, result);
        if ((*result & 0x10) != 0) {
            break;
        }
        ...
    case 2:
        mode = &D_800AE740;
        *mode = 0x80;
        if (func_80043830(0xE, mode, mode - 8) == 0) {
```

## (a) Residual
ORDER 4, 137 = 137: in state 0 the `la $s0,cdReq_cdResult` was scheduled BEFORE `li a0,1; move a1,zero`; the target
issues the two constant arguments first, then the address (whose copy to `$a2` fills the `jal` delay slot).

## (b) Pass and decision (PROVEN on the spliced-TU dumps `scratch/dumps_free/`, `scratch/dumps_v7/` + bytes)
sched1's birth boost. The RTL order is identical in both bodies (address set, a0, a1, a2 = address, call —
`scratch/free.combine.txt` / `v7.combine.txt`). In the scheduler (`scratch/*.sched.txt`, block 3) the address set is
boosted to max priority `7f000001` only when its destination is set ONCE in the function: `birthing_insn_p`
(`sched.c:2469-2490`, `reg_n_sets[i] == 1`) via `adjust_priority` (`sched.c:2507-2543`). Reverse list scheduling then
picks it first at T-7 (`ready list at T-7: 24 (1) 22 (1) 20 (7f000001), now 20 24 22`), i.e. it lands AFTER the two
argument constants in the final order — the target. With the shared `p` (`reg/v:SI 73`, set in state 0 AND state 2,
`reg_n_sets == 2`) there is no boost, all four insns tie at priority 1 and the original insn order wins
(`now 26 17` last -> address first). The tree's launders made `c0`/`c1` asm outputs to fake the order.

## (c) Move
One pointer variable per case (`result` for state 0, `mode` for state 2) instead of one `p` assigned in both. Three
spellings all score 0: a case-0-only variable (`scratch/e/w1.c`), a block-local `u8 *res` in case 0 (`w2.c`), a new
variable for case 2 (`w3.c`); also passing `&cdReq_cdResult` directly and assigning `p` after the call (`v7.c`: the
argument's temp is set once and `p` is cse'd into it). `body.c` is w1/w3 with names.

## (d) Generator proposal
When an ORDER residual has a pointer/constant set that the target schedules LATER (next to its use) than yours, and the
destination variable is assigned in another switch case / statement group too, split that variable into one per
assignment (R23-style, but across switch cases) — a set-once destination gets sched1's birth boost
(`sched.c:2469-2490`, `:2539`), which puts the set last among tied insns.

## (e) What did not work
`func_80043830(1, 0, p = &cdReq_cdResult)` (v1, v8), literals with the shared `p` (v3, v4), `c0/c1` kept with the
assignment in the argument (v5), a comma expression (v6): all 4 — `p` still has two sets. `&cdReq_cdResult` passed and
`cdReq_cdResult` read directly without a pointer (v2) = 6: cse rematerialises the address for the read (`lui v0; lbu`),
so the callee-saved base disappears. The sweep's 178 compiles (swap, block, do-while, const-holder, widths on c0/c1):
all 4 — none splits `p` across cases.

## (f) Where the method fell short
The tree's own header (§ADD-8) had the right pass ("sched1 ranks the address load first") but the wrong decision (it
blamed the dependence chain, not the birth boost). Step 16's "a variable set in two switch cases -> one variable per
case" (d22) is exactly this crack; worth adding the ORDER signature to it: "a set scheduled too EARLY among
priority-1 ties = its destination has more than one set; split it".

## (g) Structs
No. The decision is `reg_n_sets` of the pointer's pseudo (sched1's birth boost); nothing is an aggregate-vs-scalar
memory dependence. `cdReq_cdResult` and `D_800AE740` are fields of one CD-request block (`D_800AE740 - 8 ==
cdReq_cdResult`, the body's `mode - 8`), so a `CdReq` struct would read better (`req->result`, `req->mode`) — but a
struct pointer set in both cases would again have two sets and lose the boost; the one-variable-per-case rule still
applies.

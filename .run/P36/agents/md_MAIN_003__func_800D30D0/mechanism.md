# func_800D30D0 (aF800D30D0) — score 0, ZERO levers, but needs a DECLARATION change outside the body (PARKED-class, one line)

(a) Residual (start 14, COUNT, 8-instruction tail): the target sets the return value FIRST (`move v0,zero` right after
    `sw zero,0(v0)`), then the dummy volatile read and the `0x60000000` store run in `v1`/`a0`; the lever-free body emits the
    tail in `v0`/`v1` and `move v0,zero` LAST. The tree kept a `"=r"(ret) : "0"(0)` launder asm to pin the constant early.

(b) Pass + decision — sched1 (pre-allocation), `birthing_insn_p` `sched.c:2477-2490` and `adjust_priority` `sched.c:2538-2545`:
    cse forwards `ret = 0` into the return copy (COST(const_int 0) = 0 < a pseudo's 1, `cse.c:6899`), so the RTL is
    `(set (reg/i v0) 0)` at the END; sched1 (reverse list scheduling, `sched.c:44-56`) then asks whether that insn BIRTHS a
    register that is set exactly once — `reg_n_sets[v0] == 1` — and if so gives it `max_priority`, i.e. keeps it as late as
    possible, next to its `use`; the chain's pseudos are then free to take `v0` and sched2 keeps the move last. In the
    original, `v0` is set FOUR times: the three `func_8005C604` calls are `printf` and return `int`, so each call insn is
    `(set (reg v0) (call …))` (flow counts hard-reg sets, `flow.c:2035-2047`) — `reg_n_sets[v0] == 4`, no birth, the
    `(set v0 0)` keeps its natural priority (lowest in the block), is placed right after the last insn it depends on (the
    anti-dependence on `sw zero,0(v0)`), the chain's pseudos conflict with the live `v0` and get `v1`/`a0`, and sched2 leaves it.
    In this TU the callee is declared `extern void func_8005C604();` (twice, lines 749 and 864) — a `void` callee is
    `(call …)` with no set, which is the whole defect.
    PROVED on bytes: (1) a throw-away probe adding a second `return` (`scratch/x1.c`, 2 sets of v0) reproduced the target's
    tail exactly (only the added branch differed); (2) the real fix below scores 0 and the whole object's disassembly+relocs
    are identical to the baseline.

(c) Moves:
    1. `extern void func_8005C604();` → `extern s32 func_8005C604();` at src/md_MAIN_003/md_MAIN_003_jr_800D1E18.c:749 and :864
       (it IS printf — `"%s timeout:\n"`, `"\t DMA=(%d,%d), ADDR=(0x%08x->0x%08x)\n"`). Zero bytes change anywhere else in the
       object (func_800D2D68's `default:` call scores 0, whole-object diff empty).
    2. In the body: the launder goes; `ret` deleted; `return 0;`. `body.c` keeps the TU's existing `aF800D30D0` asm-label alias
       header (line 902 is outside the body); `body_realname.c` is the same body as `s32 func_800D30D0(char *arg0)` — also 0
       and whole-object identical when the two caller externs at :826/:843 become `extern s32 func_800D30D0(char *a0);` and the
       :902 alias line is dropped (`scratch/tu_sig3.c`). Both are declaration edits outside the body: parked-class, but the
       cheapest kind (a callee's true return type).
    Levers: 1 (launder) → 0. The three `(volatile T *)` casts were already in body_free.c and stay.

(d) GENERATOR PROPOSAL: when the residual is a function's final `move v0,K`/`li v0,K` sitting LAST in mine and EARLY in the
    target with the surrounding temporaries permuted off `v0`, count the TU's declared return types of every callee the body
    calls: any callee declared `void` whose real return type is non-void (printf/sprintf/strlen-class helpers, `Cd*`/`Gs*`
    SDK calls, any function whose other TUs declare a value) is a `(set v0 (call))` the original had — declare it `s32` (in
    the TU or a header) and re-try; the birthing test `reg_n_sets[v0] == 1` flips at the second set. A whole-TU `--try`
    scores the callee's other callers in the same compile.

(e) Did NOT work (all byte-tested, 14 unless noted): `ret = 0` at the top / before the last call / `return 0` (cse forwards
    regardless); `*p = ret = 0`, `ret = *volatile = 0` (u1: score 2 — gcc 2.7.2 RE-READS a volatile lvalue as the assignment's
    value, so `ret = (*aD800DB650 = 0)` emits `lw v0,0(v0)`), returning the volatile read (t5, 4), a `do{}while(0)` around the
    chain (t4: the loop-note barrier is below the forwarded copy), `ret` set twice by two constants (w1/w2: the dead first set
    is deleted before flow counts). None touched `reg_n_sets[v0]`.

(f) Method: cost me the longest of the four; the residual reads as a scheduling/allocation residual and every register-side
    theory was wrong until the `.sched` trace showed `125 (7f000001)` — the `adjust_priority` max-priority marker on the
    return-value set. Suggest adding to METHOD: "a return-value `move v0,K` that is LAST in mine and EARLY in the target =
    `birthing_insn_p`: count the sets of `v0` — every value-returning callee declared `void` is a missing set".

(g) STRUCTS: no struct is involved — `D_800DB6xx` are global POINTER variables to the MDEC/DMA registers (`lw` of the pointer,
    then the access); the decision is the callee's return type, not any access shape. Giving the MDEC/DMA registers a struct
    would not move this pass.

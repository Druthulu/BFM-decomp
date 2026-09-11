# func_80035210 (src/800_b_2.c) — S104 agent e2 — CLOSED at 0 with ZERO levers, but it is a SIGNATURE change (parked)

## (a) The residual
Score 4, REG-caller, 24 vs 24: the post-`SpuWrite` read-modify-write of `D_80076218` (`lw; addu ..,s1; sw`) lives in `$v0`
in mine and in `$v1` in the target. Nothing else differs.

## (b) The pass and the decision
local-alloc. The load and the sum are one quantity (tied by `combine_regs`), born after the `SpuWrite` call inside block 0.
`find_free_reg` (local-alloc.c:2073, the scan at :2158-2175) takes the first hard reg not live over the quantity's
life: `$v0` in the lever-free body. In the target `$v0` is LIVE across that stretch — it holds `SpuWrite`'s return value
until the function returns it — so the scan's first free register is `$v1`. The tree's `register … __asm__("$3")` pin was
faking exactly that.

PROVEN on the dumps (`scratch/dumps_b3/b3.i.lreg`): the SpuWrite `call_insn` is `(set (reg:SI 2 v0) (call …))`, `$v0` is
copied to the return register and stays live (REG_DEAD v0 only at the final `use`), and `;; Register 76 in 3.` /
`;; Register 77 in 3.` put the load and the sum in `$v1`.

## (c) The move that closed it
The function RETURNS `SpuWrite`'s result (PsyQ's `SpuWrite` returns `unsigned long`, the size written; `func_8003C498`
is used as `SpuSetTransferStartAddr`-shaped too, and the TU's own `func_8002FC64` already calls `func_8003C498` through a
value-returning cast):

body.c (compiles in the tree as it stands, `--try … --body` = 0):
```c
s32 func_80035210(s32 a0, s32 a1)
{
    s32 ret;

    func_8003C498(D_80076218);
    ret = ((s32 (*)(s32, s32))SpuWrite)(a0, a1);
    D_80076218 += a1;
    return ret;
}
```
The CLEAN spelling (needs the TU's two file-scope `extern void SpuWrite(s32, s32);` at src/800_b_2.c:2737 and :7513
changed to `extern u32 SpuWrite(s32, s32);`, the real PsyQ return type) is `scratch/b3.c`; tested as a whole TU
(`scratch/b3tu.c`): func_80035210 = 0 AND the other SpuWrite caller func_8002FC64 = 0:
```c
u32 func_80035210(s32 a0, s32 a1)
{
    u32 ret;

    func_8003C498(D_80076218);
    ret = SpuWrite(a0, a1);
    D_80076218 += a1;
    return ret;
}
```
SIGNATURE CHANGE: the return type goes `void` -> `s32`/`u32`. No `extern` prototype of func_80035210 exists in `src/` and
nothing in `src/`/`asm/` references it by name (it is reached through a table or not at all), so no caller text changes.
Per Drew S104 (d) this is reported, not expected to bank now. The minimum-lever body WITHOUT the signature change is the
tree's own (1 pin, `register s32 v1 __asm__("$3")`): lever count 1 -> 1; with the signature change 1 -> 0.

## (d) GENERATOR PROPOSAL
When a `void` function's LAST call is to a value-returning library/callee (declared `void` in the TU) and the residual is a
`$v0`->`$v1` (or `$v0`->next free) rename of every late local after that call, try `T ret = call(...); …; return ret;`
with the function's return type changed (d29's family: a live `$v0` keepalive = a returned value).

## (e) What did not work (bytes)
- `D_80076218 += a1;` with the load inlined into the call argument (scratch/b1.c): 4 — same `$v0`.
- The history's R6/R7/R10 moves (inline, block, param-copy): all 4 — none makes `$v0` live.
- There is no plain-C, same-signature way to make `$v0` live after the last call: nothing else in the body produces a value
  there, and a keepalive of it is exactly the lever this replaces.

## (f) Where the method fell short
The `d29` note in METHOD step 15 predicted it; the only work was recognising that `$v0` must be live and asking what
could hold it after a call.

## (g) Structs
Not a struct question: the decision is `$v0` liveness in local-alloc, fixed by the callee's and the function's return
types (a prototype matter, which the structs/types phase owns). A struct type for `D_80076218` would change nothing.

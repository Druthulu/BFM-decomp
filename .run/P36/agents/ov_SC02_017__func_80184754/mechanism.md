# func_80184754 — e4 (P36 T7 S104) — score 22 (sweep best 8) -> 0, ZERO levers

(a) Residual: COUNT 72 vs 73 + a t0/t1 permutation. The target copies the incoming `$a0` into `t0` once
(`move t0,a0` in the prologue) and uses `t0` for the object and `t1` for `s1` everywhere. The lever-free text keeps
the object in `$a0` in the first block and copies it to `t1` in the `beq` delay slot for the else arm (two pseudos:
the parameter and the local `s0`). The tree's `launder` asm (`"=r"(s0) : "0"(s0)`) faked the target by making `s0`
a fresh value cse cannot identify with the parameter.

(b) Pass/decision (dump-verified, `PACK/scratch/dumps_b1`, `dumps_v1`, `dumps_v2`):
  1. The local copy `s32 s0 = (s32)a0;` makes two pseudos, r72 (param) and r73 (s0). cse1 applies the
     `(set REG0 REG1)` swap (cse.c:7440-7474) and the second cse pass swaps it back (`.cse2`: the first-block uses
     and the call argument read r72, the else arm reads r73) — the canonical-register choice is `make_regs_eqv`
     (cse.c:826-862, "if NEW will live longer … make it the new canonical"). r72 has only a `$a0` copy preference
     and no conflict with `$a0` (it dies at the branch), so global gives it `$a0`; r73 lives through the else arm's
     block moves (lwl/lwr through `$a0/$a1` … `$a3`, `.greg` "73 conflicts: … 4 5 6 7") and gets `t1`.
  2. With ONE pseudo for the object (no local copy), it inherits the else-arm conflicts with `$a0-$a3`, so the
     copy preference cannot be honoured and it lands in a temporary -> the target's `move t0,a0`. Which of
     `t0/t1` it gets is `allocno_compare` (global.c:594-610), priority = floor_log2(refs)·refs/live:
     param-only body: r72 10 refs / live 24 = 12500 < s1 (r73) 10/23 = 13043.5 -> s1 takes t0 (score 19, pure
     permutation). Passing the object to `func_8012C218` (its real arity: `extern void func_8012C218(void *a0)`
     at TU:7066; every lever-free sibling passes it, e.g. func_80180590 TU:4132) adds one ref:
     11 refs / live 25 = 13200 > 13043.5 -> the object is allocated first and takes t0. The arg copy costs 0
     bytes (the value is still in `$a0` on that path — `jal func_8012C218; nop` in both).

(c) Moves (joint — each alone scores worse than 0: param-only 19, arity-only 22):
  - delete `s32 s0 = (s32)a0;` and use the parameter directly (`(s32)a0 + K`, the house spelling);
  - `((void (*)(void))func_8012C218)();` -> `func_8012C218(a0);` (the declared prototype, real arity).

(d) GENERATOR PROPOSAL: when the tree carries a `launder` on a local that is a plain copy of a parameter
(`T x = (T)argN; asm("" : "=r"(x) : "0"(x));`), delete the local and substitute the parameter for every use
(R-new "inline param copy"), and combine it with R19 (pass every held argument to calls whose cast/decl drops it).

(e) Did not work: the sweep's R7 do-while/block and R8 temp moves (best 8); passing `a0` or `(void *)s0` to the
call with the local copy kept (22, two pseudos survive cse2).

(f) Method: METHOD bullets "(d24) `T x = argN;` at the top -> delete, use argN" and "(c35) a call through a CAST that
asserts fewer arguments … pass the argument" together are the whole close; the allocation table (tools/alloc_table.py)
confirmed the priority arithmetic in one run. The sweep cannot find it because neither move alone improves on 8.

(g) Structs: no. The decision is pseudo identity (cse's canonical register) + global priority; a struct type for
`a0`/`s1` (fields +0x04/+0x08/+0x0C/+0x20/+0x36/+0x64/+0xFC) would change the spelling, not the refs/live counts
or the copy. (The SV4x block copies already use a struct type.)

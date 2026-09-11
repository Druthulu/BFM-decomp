# func_801A1E94 (md_SC07_004) — P36 S104 agent e1 — score 14 (lever-free) -> 0 with ZERO levers via a SIGNATURE change

(a) Residual: body_free.c is 41 ins vs 42 — the target's `move s0,a0` in the prologue is missing and `$s0/$s1` are swapped.
The function reads the caller's `$a0` (the object pointer) but the TU declares and defines it `void func_801A1E94(void)`;
the tree's `register s32 param_1 __asm__("$4")` pin was faking a PARAMETER. Lever-free, `param_1` is an uninitialised local:
nothing copies `$a0`, so one instruction is missing and the allocation of the remaining pseudos reshuffles.

(b) Pass/decision: no optimisation pass — the incoming argument register is only named through a PARM_DECL
(`function.c:3157` `assign_parms`, which emits the `move s0,a0` parameter copy). A `(void)` function cannot read `$a0` in C:
proven on bytes both ways — a prototype definition `void func_801A1E94(s32 p)` against the TU's `extern ... (void)` is
"conflicting types" (line 10 / 4471), and a K&R definition `void func_801A1E94(p) s32 p;` is "number of arguments doesn't
match prototype". Every caller already has the object in `$a0` at the call: `func_801A0230` calls it through a cast
`((void (*)(s32))func_801A1E94)(a0)` and `func_801A6A18(void) { func_801A1E94(); }` is a pass-through wrapper.

(c) The close (proven, score 0; all callers byte-identical; WHOLE OBJECT .text/.data/.rodata/.sdata/.bss sha1-identical to the
baseline and .text relocations identical, with all three of this agent's bodies spliced — `scratch/tu_all3.c`):
1. `void func_801A1E94(s32 a0)` — the parameter replaces the pin + `p = param_1` copy + the dead `s0` local.
2. Both `extern void func_801A1E94(void);` (lines 10, 4471) -> `(s32 a0)`.
3. `func_801A0230`: `((void (*)(s32))func_801A1E94)(a0);` -> `func_801A1E94(a0);` (0 bytes).
4. `func_801A6A18(void) { func_801A1E94(); }` -> `func_801A6A18(s32 a0) { func_801A1E94(a0); }` (0 bytes; no other
   declaration of func_801A6A18 in src/).
The whole-TU patch (with func_801A5C44's identical fix) is `signature.diff`; `scratch/mktu.py` regenerates it.
body.c is the new definition; it does NOT compile under `--try --body` alone (the TU's `(void)` externs conflict) — it
needs signature.diff. PARKED for the structs phase per Drew S104 (d).
Fallback if the signature change is refused: `body_minlever.c` — ONE marked pin (`register s32 arg __asm__("$4"); s32 a0 =
arg;`), score 0 under `--try --body`. Lever count 1 -> 1 (the tree's pin, now honestly marked as a signature lever); the pinned
variable must be COPIED into an ordinary local (using the pinned var directly scored 18: it stays in `$a0`).

(d) GENERATOR PROPOSAL: when a `(void)` function's first statement pins `$4`–`$7` and reads it before any write, rewrite it
as a parameter of that type, update every `extern` of it in the TU and route each caller's value in that register as the
argument (a cast call `((void (*)(T))f)(x)` -> `f(x)`; a `(void)` pass-through wrapper gains the parameter too), then score
the callee AND every caller. A regex census finds 158 such `(void)`+early-`$4..$7`-pin functions in src/ (unverified
denominator: the regex does not check read-before-write; ~110 are copies of `func_80157D20`); a third in this TU is
`func_801A4258`.

(e) Did NOT work / not needed: the free sweep's R12 width moves (`p`/`param_1` s32->u16/u8, score 1) and every R4–R18 move at
1 were operating on an UNINITIALISED variable — no spelling can create the missing parameter copy. Lower-level alternative
spelling of the final body: dropping the `sp = &D_801BF01C` local (using the global directly) scored 13 — the target keeps
the address in `$s1` (`lui/addiu s1` once, `lw a2,0(s1)`); the local, as sibling `func_801A66DC` spells it, is the shape.

(f) Method gap: the residual reads as a register permutation + one missing copy; the real defect is the SIGNATURE, visible
only in body_tree.c (a pin as the first statement, read before written) and in the TU's callers. A pre-check for "a pinned
argument register read before any write in a (void) function" would have skipped the 312+246 sweep compiles.

(g) Structs: NO for the lever — a struct type changes nothing about how `$a0` enters the function; only the parameter does.
Once it is a parameter, typing it as the object struct (fields 0x0A/0x0E s16, 0x1C s32, 0x20 s32 handle, 0xD4 s32, 0x84/0x100
s16) is a readability gain only; there is no scalar-vs-aggregate ordering question left in this body (no stores are
reordered in the residual). Not tested on bytes (nothing to close).

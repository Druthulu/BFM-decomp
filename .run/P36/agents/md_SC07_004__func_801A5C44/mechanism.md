# func_801A5C44 (md_SC07_004) — P36 S104 agent e1 — score 15 (lever-free) -> 0 with ZERO levers via a SIGNATURE change

(a) Residual: body_free.c is 40 ins vs 41 — the target's `sw s0,16(sp); move s0,a0` parameter copy is missing and the
three callee-saved holders rotate (`s2->s0, s0->s1, s1->s2`). Same defect as func_801A1E94 in this TU: the function reads the
caller's `$a0` but is declared and defined `void func_801A5C44(void)`; the tree's `register s32 a0 __asm__("$4")` pin was
faking a parameter, and lever-free `a0` is an uninitialised local.

(b) Pass/decision: none — the incoming `$a0` is only named by a PARM_DECL (`function.c:3157` `assign_parms`, which emits the
`move s0,a0`). Proven for this TU on func_801A1E94: both a prototype definition against the `(void)` externs ("conflicting
types") and a K&R definition ("number of arguments doesn't match prototype") are compile errors. All three callers hold the
object in `$a0` at the call (`func_801A6560`: first statement; `func_801A6FD4`: after a load into `s1`; `func_801A7184`:
already a cast call `((void (*)(void *))func_801A5C44)(arg0)`).

(c) The close (proven, score 0; every caller byte-identical; whole object sha1-identical per section with all three of this
agent's bodies spliced — see func_801A1E94's pack `scratch/tu_all3.c`):
1. `void func_801A5C44(s32 a0)`, and the body tidied: `s2`/`s1` initialised at declaration, the `temp` local and the
   `s32 s0 = a0` copy deleted, each `func_8004787C(...) >> 4` written inline in its sum (score 0; the tree-shaped text with
   just the parameter also scores 0 — `scratch/b2_1.c`).
2. The three `extern void func_801A5C44(void);` (lines 4265, 4753, 4811) -> `(s32 a0)`.
3. Callers: `func_801A5C44();` -> `func_801A5C44(arg0);` in `func_801A6560`, `func_801A5C44((s32)arg0);` in `func_801A6FD4`,
   and `((void (*)(void *))func_801A5C44)(arg0);` -> `func_801A5C44((s32)arg0);` in `func_801A7184` (all 0 bytes).
The whole-TU patch (both functions) is `signature.diff` (same file as in func_801A1E94's pack). body.c needs it: alone under
`--try --body` it is a "conflicting types" error. PARKED for the structs phase per Drew S104 (d).
Fallback if the signature change is refused: `body_minlever.c` — ONE marked pin (`register s32 arg __asm__("$4"); s32 a0 =
arg;`), score 0 under `--try --body`. Lever count 1 -> 1.

(d) GENERATOR PROPOSAL: a `(void)` function whose first statement pins `$4`–`$7` and reads it before writing -> make it a
parameter, update every TU `extern`, pass the caller's value at each call site (cast calls collapse), score callee + callers
(158 regex hits across src/, unverified; third in this TU: `func_801A4258`).

(e) Did NOT work / not needed: the sweep's best 1 (R12 `s0` s32->u16, R5/R6/R7/R8/R9/R18) all act on an uninitialised
variable; none can create the parameter copy.

(f) Method gap: same as func_801A1E94 — a register-rotation + one-missing-copy residual whose cause is the signature; detect
"pinned arg register read before write in a (void) function" before sweeping.

(g) Structs: NO for the lever (only a parameter brings `$a0` in). With the parameter, a struct for the object (0x70 s16 index,
0x100 s16 angle, 0xCC s32 sprite ptr, 0xD4 s32 table ptr of {u16, u16} pairs) is readability only; no ordering decision
remains. Not tested on bytes.

# `func_8017D2DC` @ `ov_SC01_001` — behemoth #7, 1,586 ins — **match_one MATCH**

**Result: `MATCH (1586 ins)`** on the candidate gate, pin-free, in one session / four gate runs.

```
.venv/bin/python tools/match_one.py func_8017D2DC \
    --c .run/giants/s21_func_8017D2DC_b1.c \
    --asm-subdir asm/ov_SC01_001/nonmatchings/ov_SC01_001_jr_8017BEBC
=> MATCH (1586 ins)
```

**NOT BANKED.** `match_one` masks `jal`/HI16/LO16 and never links. This is a `jr` function
(1 `jr $v0`, `jtbl_801EC46C`) ⇒ **§81 carve chain is mandatory** before the whole-binary gate can
agree. The carve picture is unusually favourable — see §5 below.

---

## 1. What it is

The `ov_SC01_001` **scene-script driver**: a 125-case jump-table state machine over the scene state
`D_801F313C` (`sltiu 0x7D`, `jtbl_801EC46C`, 125 entries). Each case pokes a few overlay globals and
calls the scene primitives (`func_8017F1C8` = play/queue a script blob, `func_8017EBA4` = show a text
blob, `func_8017EC28` = fire an event id, `func_8017EC18` = "is the current thing finished?"). Two
timer globals (`D_801ED9E4` countdown, `D_801ED9F4` up-counter) and a sub-phase (`D_801F3034`) drive
the per-case logic. Four cases carry a nested 3/4-way `switch` compiled as a comparison tree
(cases 46, 48, 66, 67 on `D_801F3034`; case 106 on `D_801ED9E4`).

Structurally shallow: no loops, no stack locals, frame `0x18` (`0x10` arg-save + `$s0` + `$ra`).

---

## 2. The relative — §71 fired, but NOT via the callee set

**The callee-set fingerprint was near-useless here and I want that recorded.** The target has 32
distinct `jal` callees but only **6 are shared** (`< 0x80128158`):
`{800149E0, 80016450, 8001AAA0, 8002D4C8, 800D0C48, 800D1724}` — and the other 26 are
overlay-local, so they cannot match anything outside `ov_SC01_001`. A full scan of **21,815 matched
functions** (`.run/giants/s21_fp.py`) returned a best Jaccard of **0.286 / containment 0.333**, and
every top hit was an 11-line stub sharing only the two ubiquitous helpers
`{func_8002D4C8, func_800D0C48}`. That is noise, not a relative.

**Two false leads, both worth recording:**

| lead | why it looked good | verdict |
|---|---|---|
| `src/ov_SC07_011/ov_SC07_011_jr_8017BEBC.c` **defines `func_8017D2DC`** and has no `nonmatchings/*.s` for it | same address, same jr-carve file name, MATCHED — looks like a free twin | **NOT a twin.** Overlays share load addresses, not code. `ov_SC07_011`'s `func_8017D2DC` is a 4-line handler-table dispatcher. A census across all 48 `*_jr_8017BEBC` overlays: 1 UNMATCHED (ours), 1 MATCHED (that one), 46 ABSENT. |
| `D_801F313C` cross-overlay | the state variable might be a shared engine global | Only **3** references tree-wide, all inside `ov_SC01_001`. It is per-overlay. |

**What actually worked: fingerprint by SHAPE inside the same overlay.**
`grep -c 'case '` over `src/**` ⇒
**`src/ov_SC01_001/ov_SC01_001_jr_80178D40.c :: func_80178D40` — 890 ins, 94-case `jr` switch,
MATCHED, in the same overlay, carrying a 13-point recipe comment.** That comment handed over the
whole house style for this function shape and is why the first compile was already 96%:

* **#1 NO status variable** — every case stores `D_801ED9F4 = 0; D_801F313C++;` *directly*;
  `.L8017EB5C/.L8017EB64/.L8017EB70` are a jump2 **cross-jump merge** of those stores living at the
  tail of case 123.
* **#2** the after-switch code is the fall-out of the out-of-range default — **no `default:` label**.
* **#7** per-case temporaries are **block-local**.
* **#8** locals in stack-slot order.

> **Generalisation for the next behemoth: when the callee set is dominated by overlay-local symbols,
> §71 is structurally blind (this is §79's blind spot in a second guise). Fall back to a SHAPE
> fingerprint — for a jump-table function, `grep -c 'case '` across matched `src/`, then prefer a hit
> in the SAME overlay.** It cost one grep and replaced the entire mapping phase.

---

## 3. The residual and what closed it

| round | edit | result |
|---|---|---|
| b1.0 | full longhand decode from the asm + the `func_80178D40` house style | **1586/1586 exact length**, **64 mismatched** (8 sites × 8 insns — one repeated idiom, nothing else) |
| b1.1 | **L1** — the 8 `D_801ED9F4 > K` timeouts compare against a **block-local variable** holding `K` | **8 mismatched** (case 95 only) |
| b1.2 | **L2** — case 95's `lim` moved into an **inner block after the call-bearing `if`** | **MATCH (1586 ins)** |
| b1.3 | §17a-1 pair for `func_8017EBA4` (bank plumbing, see §4) | **MATCH (1586 ins)** — byte-neutral |

### L1 — §78's literal-position law, applied to a COMPARISON (new, and it is the whole crack)

Target:
```
lw    $v1, D_801ED9F4
addiu $v0, $zero, 0x8A      <- the LIMIT materialised into a register
addiu $v1, $v1, 1
slt   $v0, $v0, $v1         <- constant on the LEFT of slt
sw    $v1, D_801ED9F4
beqz  $v0, <break>
```
Every *literal* spelling collapses to the other form. Measured on a dedicated probe
(`.run/giants/s21_probe.c`, all eight compiled with the pinned triple):

| source | emitted |
|---|---|
| `x++; if (x > 0x8A)` | `slt $2,$2,139` + `bne` |
| `x++; if (x >= 0x8B)` | `slt $2,$2,139` + `bne` |
| `x++; if (0x8A < x)` | `slt $2,$2,139` + `bne` |
| `x++; if (0x8B <= x)` | `slt $2,$2,139` + `bne` |
| `x++; if (!(x <= 0x8A))` | `slt $2,$2,139` + `bne` |
| `if (++x > 0x8A)` | `slt $2,$2,139` + `bne` |
| `x++; if (x <= 0x8A) return; ...` | `slt $2,$2,139` + `bne` |
| **`s32 k = 0x8A; x++; if (k < x)`** | **`slt $2,$2,$3` + `beq`** ✅ |

**Mechanism.** MIPS `slti` computes `rs < imm`, so a constant can only ever sit on the RIGHT. gcc's
`mips.c:gen_conditional_branch` therefore rewrites `LE`/`GT` against a `CONST_INT` into
`LT (x, K+1)` and emits `slti`. When the limit is a **pseudo** at expand time, that rewrite is
unavailable: gcc emits `slt (k, x)` and takes the `invert = 1` path, giving `beq` on the branch.
`cse` cannot undo it — the `slt reg,reg` insn is already chosen; only the `li` survives constant
propagation.

> **RULE (§78 extension, byte-proven ×8 here):** in a `slt`, the operand that had to be *materialised
> into a register* was **not a literal in the source**. If the target shows `li K; slt K, x` the
> source compared against a VARIABLE; if it shows `slti x, K+1` the source compared against a
> literal. This is decidable from the bytes alone and there is no source spelling that crosses over.

### L2 — §76, and why the same edit is wrong in one of the eight cases

Case 95 is the only timeout site preceded by a call-bearing `if`. With `s32 lim = 0x3C;` at the top
of the case block, `lim`'s live range spans `func_8013C9C4`/`func_8002D4C8`/`func_80182EB0` ⇒ it must
be callee-saved ⇒ `$s0`, and the `li` hoists above the calls (`li s0,60` where the target has `nop`).
Moving the declaration into an inner block *after* that `if` shortens the range to one basic block
⇒ `REG_N_DEATHS == 1` ⇒ local-alloc ⇒ `$v0`, in the right place. **8 → 0.**

---

## 4. Do-not-re-buy table — `(edit, base) → result` (§80: all measured on the b1 base)

| edit | base | result |
|---|---|---|
| `if (D_801ED9F4 > K)` literal at one site (case 68) | b1 (MATCH) | **8 mismatched** — L1 is required per-site |
| `s32 lim` at the TOP of case 95's block | b1 (MATCH) | **8 mismatched** — L2 is required |
| drop `pv`, use `*(s32 *)&D_80126948[8] = 0x100` inline | b1 (MATCH) | **1587 ins, 1204 mismatched** (LENGTH-DRIFT) — `pv` is a real function-scope pointer |
| drop `case 124:` (empty body) | b1 (MATCH) | **1 mismatched** (IMM-OFFSET) — the `sltiu` bound falls 0x7D→0x7C |
| head as nested `if`s instead of `&&` | b1 (MATCH) | **MATCH** — equivalent, *not* a lever, don't spend on it |
| §17a-1 cast at all 41 `func_8017EBA4` call sites | b1 (MATCH) | **MATCH** — byte-neutral, keep it |
| `>= K+1` / `K < x` / `!(x <= K)` / `++x > K` / early-return, all with a literal | probe | all identical to `> K` — **the whole family is spent**, only a variable works |

### Refuted diagnoses
* *"`ov_SC07_011` has this function matched, mechanically remap it."* — same address ≠ same code
  across overlays. Cost: one `sed -n`. Check the body, not the address.
* *"§71 callee-set fingerprinting will work, it has 32 callees."* — **it will not** when 26/32 are
  overlay-local. Containment 0.333 against 21,815 functions. The brief's expectation was wrong and
  the shape fingerprint replaced it.
* *"the 34 identical `func_8017EC18` blocks are a cross-jump problem I will have to fight."* — no,
  see §6; they stay separate for free.

---

## 5. Banking (§81) — the carve picture, which is unusually clean

```
grep -cE 'jr\s+\$(v0|v1|a0|t[0-9])' <the .s>   => 1        (jtbl_801EC46C)
```

* **`func_8017D2DC` is the ONLY remaining `jr` function in the `ov_SC01_001_jr_8017BEBC` code
  subseg** (checked over all 100+ `.s` in that directory). ⇒ **step 1 (`jr_isolate_all --only`)
  looks unnecessary** — the code subseg it needs already exists.
* `config/splat.ov_SC01_001.yaml` has
  `- [0xc42f4, .rodata, ov_SC01_001_jr_8017BEBC]` immediately followed by
  `- [0xc4314, data, tail21]`, and **`tail21` STARTS with `jtbl_801EC46C`**
  (`asm/ov_SC01_001/data/tail21.data.s`, first label, 125 words = `0xc4314 .. 0xc4508`, and
  `D_801EC660` @ `0xc4508` is the next symbol).
  ⇒ the carve is a **contiguous extension** of the existing `.rodata` subseg to `0xc4508` with
  `tail21` moved to `0xc4508`. **§81's step-2 "non-contiguous `.rodata`" refusal cannot fire.**

Suggested chain:
```
tools/jtbl_carve.py ov_SC01_001 --func func_8017D2DC
make extract BINARY=ov_SC01_001 && make build BINARY=ov_SC01_001   # must be BYTE-IDENTICAL
tools/harvest_verify.py --binary ov_SC01_001 --drafts <dir> --chunk 1
# then a full R22 (config changed => T2)
```

### Decl plumbing — audited against the real TU, 3 findings

`src/ov_SC01_001/ov_SC01_001_jr_8017BEBC.c` already declares or defines 13 of the draft's symbols.
Twelve agree with the draft verbatim (`D_80126948` `u8[]`, `D_801EDA20` `s32`, `func_8002D4C8`,
`func_800D0C48`, `func_800D1724`, `func_8013C9C4`, `func_80174E9C`, `func_8017EC18` `s32(void)`,
`func_80181834`, `func_80181A28`, …). **Three need care:**

1. **`func_8017EBA4` — already handled in the draft.** The TU **DEFINES** it at line 3274 as
   `void func_8017EBA4(void) { D_801EDA20 = (void *)((s32 (*)(void))func_8013767C)(); }` — a
   *pass-through* whose body never names its argument, so `$a0` flows straight into `func_8013767C`.
   Our 41 call sites pass a pointer ⇒ a `void *` prototype is a hard conflict (§75a class B).
   The draft ships the **full §17a-1 pair**: `extern void func_8017EBA4();` (K&R, compatible with
   the later `(void)` definition in either order) **plus a cast at every call**. Re-gated: **MATCH**,
   byte-neutral.
2. **`func_8001AAA0`** — TU says `extern int func_8001AAA0(void);` (fleet: 489 `(void)` vs 138
   `(int)`, a genuine class-B split). Draft keeps the TU spelling and casts at the one call site.
3. **`func_8013D13C`** — fleet canon `extern s32 func_8013D13C(void);` ×420, but this function calls
   it with an argument (twice). Draft keeps the canon decl and casts at both call sites.

`func_800149E0` and `func_80016450` have **no decl anywhere in the tree** — the draft's spellings
(`s32 func_800149E0(s32)`, `void func_80016450(s32,s32)`) are free choices and establish the canon.

### §87 / §84 blind-spot checks, run
* All **107** `D_`/`func_` data symbols the draft names resolve: 105 are `dlabel`/`glabel` in
  `asm/ov_SC01_001/**`, and the 2 that are not (`D_800B99D8`, `D_80126948`) are **resident-shared**
  (`< 0x80128158`, 688 and 3,142 fleet uses). No unresolvable symbol hiding behind the MATCH.
* **No derived offsets (§84).** The only non-zero offset into a symbol is `pv[2]` (= `D_80126948 + 8`),
  a field offset into a *shared* symbol, not a hand-computed distance between two per-overlay symbols.

---

## 6. NEW cookbook candidate — §88: **cross_jump will not merge a common suffix that contains a CALL**

This function is a natural experiment with a huge sample, and the result is unambiguous:

| shape | count | merged? |
|---|---|---|
| `jal func_8017EC18; beqz $v0,.L8017EB5C; j .L8017EB78` — **byte-identical 6-insn blocks** | **~34** (cases 5,14,16,20,22,24,26,28,30,32,34,36,38,40,52,54,58,60,62,74,76,80,82,86,88,90,102,104,110,112,116,118,120,122) | **NO** |
| case 66 sub-0 vs sub-2 — **byte-identical 12-insn blocks**, both containing a `jal` | 2 | **NO** |
| `D_801ED9F4 = 0; D_801F313C++` (call-free) → `.L8017EB5C/EB64/EB70` | ~60 cases | **YES** |
| `D_801ED9F4 = 0; D_801F313C++` with the state in `$v1` → `.L8017E9A0/E9AC/E9B4` | 6 cases | **YES** |
| `D_801F3034 = v+1` → `.L8017E06C`; `D_801ED9E4 = K; D_801F3034++` → `.L8017DAF0`; `D_801ED9E8 = 0x10; D_801ED9E4++` → `.L8017E804` | 3 groups | **YES** |

Every merged suffix is call-free; every unmerged one contains a `CALL_INSN`. **Practical
consequence: on a big dispatcher, write the repeated call-shaped cases out longhand — they will not
collapse — while the call-free tails will merge themselves, so do NOT hand-factor them into a helper
or a status variable** (that is `func_80178D40`'s lever #1, and this function is a second
byte-proof of it).

Corollary observed here, worth banking with it: cases whose *entire* body is a mergeable tail
(19,21,27,31,51,53,57,59,87,89) get reduced to a bare `j .L8017EB5C`, and `jump.c`'s ADDR_VEC
`follow_jumps` pass then retargets their **jump-table entries** straight at `.L8017EB5C`. So a table
entry pointing at a *shared tail* is a real case with a tail-only body — **not** a `default`. Only an
entry pointing at the after-switch label is default-or-empty. (Here `case 124:` had to exist with an
empty body: it is what sets the `sltiu 0x7D` bound — dropping it costs exactly 1 instruction.)

---

## 7. Remaining residual classes

**None on the candidate gate.** The open work is entirely §81 banking plumbing, which is the
parent's. The single highest-value next move is
`tools/jtbl_carve.py ov_SC01_001 --func func_8017D2DC` followed by a byte-identical
`make extract/build BINARY=ov_SC01_001`, then splice + `harvest_verify`.

## 8. Artifacts

| file | what |
|---|---|
| `.run/giants/s21_func_8017D2DC_b1.c` | the draft — MATCH (1586 ins), pin-free, bank-ready decls |
| `.run/giants/s21_8017D2DC_report.md` | this report |
| `.run/giants/s21_compact.txt` | the target disassembly, one line per insn, with `<<< case N >>>` tags resolved from `jtbl_801EC46C` — the decode surface |
| `.run/giants/s21_fp.py` | §71 callee-set fingerprint over all matched `src/` functions (reusable; takes the target `.s` as argv[1]) |
| `.run/giants/s21_probe.c` | the 8-variant comparison-form probe that produced the L1 table |
| `.run/giants/s21_abl_{pv,c124,head,lit68}.c` | the four drop-one ablations |

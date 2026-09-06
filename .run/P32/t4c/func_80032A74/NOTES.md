# func_80032A74 (main / 800_b_2, 422 ins) — T4b HAND PASS, S84 (2026-09-06), Fable 5.1 at Max

## Verdict: PROVED at closeness 1 — the pass is named, every producer of the residual is enumerated and refuted on the bytes.

**State (re-verified this session, real TU, `rtu_match … --tu src/800_b_2.c --asm-subdir asm/nonmatchings/800_b_2`):**
* `.run/P32/t4/drafts/func_80032A74_tuclean.c` (`s16 u18`): **DIFF 1** — idx 244 `lh v0,0x18(s1)` vs target `lhu`; frame exact (0x78).
* `.run/P32/t4c/func_80032A74/lhu_tuclean.c` (the same draft with `u16 u18`, TU-clean): **DIFF 22** = all 22 frame rows
  (`addiu sp,-0x70` vs `-0x78`, the 10 saved-register offsets ×2); **422/422 instructions otherwise identical.**
So the residual is EXACTLY one never-referenced stack slot at sp+0x48 (bytes: sp10 local 0x10–0x2F, the a0/a1/a2 reload
spills at 0x30/0x38/0x40 — 5/2/4 refs — nothing at 0x48, saved regs 0x50–0x74). vars 56 → 64: any slot of 1..8 bytes
allocated AFTER pseudo 74's slot lands there and rounds (`MIPS_STACK_ALIGN`) to the same frame; an expand-time slot cannot
(it precedes the reload slots and would push `sw $a0,0x30($sp)` to 0x38).

## The producer census (from tools/reference/gcc-2.7.2 — every stack-slot allocation site that runs after the parameters' slots)
| producer | source | requirement | refuted on THIS function by |
|---|---|---|---|
| 1. ghost pseudo: `alter_reg(i,-1)` in the initial loop | reload1.c:658 (8-byte slot, regno order → right after 72/73/74) | a pseudo with `reg_n_refs>0`, `reg_renumber<0`, no REG_EQUIV, i.e. minted with NO occurrences BEFORE regclass (class `ST_REGS or none` → unallocatable) | only combine mints those (below): path (a) forces `lh`/`lb`; path (b) needs a 3-insn chain whose 2-insn merge fails outright and whose fold is one insn — every reachable fold of a memory head is a narrow load (`lh`/`lb`/a duplicate `lhu`), the target has one load at the site, no `lb`, no double load, all nine `lh` single-use |
| 2. caller-save area: `setup_save_areas` | caller-save.c:249 (4-byte slot per call-used hard reg holding ANY pseudo with `reg_n_calls_crossed>0`, once `caller_save_needed` is set by the profitability path global.c:1085 / local-alloc.c:2209) | a call-used-reg pseudo with a STALE positive count and no real crossing (else `save_call_clobbered_regs` emits `sw/lw` around the call — the target has none) | the only staleness route is sched.c:4962 (a multi-block pseudo keeps flow's count when sched's is 0) after sched1 moved a register-only def/use across a call INSIDE the call's block; the seven call blocks contain only arg setups (fenced by the call's USEs), loads/stores (fenced by `flush_pending_lists`) and call-result copies — nothing can move. combine never crosses a call except with a constant source (combine.c:924). `update_equiv_regs` moves nothing (it deletes 2-ref multi-block inits and doubles `reg_live_length`) |
| 3. invalid-equivalent-address slot | reload1.c:879 (`reg_equiv_memory_loc` whose address eliminates to a spilled pseudo → new slot) | an UNALLOCATED pseudo with a REG_EQUIV MEM through `arg0`/`arg2` (both spilled) | such pseudos are single-block (`update_equiv_regs` requires `reg_basic_block>=0`) and local-alloc/global allocate them unless every GR conflicts — impossible over a 2-insn life |
| 4. `spill_stack_slot` | reload1.c:3499 (`spill_hard_reg` → `alter_reg(i, regno)`; no retry for local-alloc'd pseudos, `retry_global_alloc` for allocnos) | a pseudo evicted from `$t0` or `LO` that gets no new home | `$t0` holds no pseudo (else `order_regs_for_reload` makes `$t1` the spill register — every param reload is `lw $t0`); LO-pref mult results are global allocnos with alternate class `GR_REGS` (`pref LO_REG, else GR_REGS`) and retry into a free GR — the draft's 273→`$t1`, 316→`$v1` |

## The NEW ghost producer found and measured (cookbook §501-M) — and why it cannot slot
`local-alloc.c optimize_reg_copy_2`: `tmp = x; <use tmp>; tmp = tmp op c; <use tmp>; x = tmp;` in ONE block (x dead at
the head copy and live after the copy-back; the head copy survives combine when tmp's first use is not its last and no
3-insn chain passes through it (combine.c:904 guard); the copy-back survives when tmp has an intervening use) rewrites
every `tmp` into `x`, leaves the two copies as no-op self-moves (deleted by jump.c), and decrements `reg_n_refs[tmp]` once
per insn while flow counted the in-place insn TWICE → `tmp` = a ghost with stale refs (P13: refs 5; P14: refs 1, "dies in 0
places"). **But it is minted AFTER regclass**, so it keeps `GR_REGS` and has no conflicts → global allocates it → **vars=0**
(P14). Only combine-minted ghosts (pre-regclass → `ST_REGS or none`) take a slot.

## Probes (all isolated reproducers, `.run/P32/t4c/dump.sh <p>.c <tag>`; oracle = `vars=` + `tools/ghost_census.py`)
| tag | shape | vars | ghost? | what it showed |
|---|---|---|---|---|
| p1–p4 | `m = vol; m = (m<<7)-(m<<4) / m *= 0x70 / m += 3; m >>= 7; vol = m` | 0 | no | combine absorbs the head copy through the 3-insn chain (sll,subu,copy) and the copy-back into the srl |
| p5 | `a = m<<3; b = m<<4; m = a-b` (independent uses) | 0 | no | head copy SURVIVES (`move`) — combine.c:904 guard; copy-back merged |
| p6/p7 | `m = m * K` / `m = m * m` | 0 | no | as p2 |
| p8 | intervening `J = m & 0x7F` before the copy-back | 0 | no | copy-back survives (`move`), head copy absorbed |
| p9 | a call between | 0 | no | the scan breaks at a CALL unless src crosses calls elsewhere |
| p10 | store-protected both copies | 0 | no | both `move`s survive but sched sinks the store below the copy-back → death note moves → optimize_reg_copy_2 sees no `REG_DEAD` |
| p11 | as p10 without a later mention of m | 0 | no | cse canonicalizes m→vol (`make_regs_eqv`: the longer-lived reg wins) → head copy dead |
| p12 | `k = m & 0x7F` after the srl, stored after the copy-back | 0 | no | still a `move` |
| **p13** | `k = m & 3; m >>= 7; Q = k + m; vol = m` + later real uses of m | 0 | **YES (refs 5)** | `.lreg`: `(set 72 72)` ×2, every m rewritten to vol — optimize_reg_copy_2 FIRED; m allocated ($2) because it still had real uses |
| **p14** | p13 with a dead trailing `m = 0` (keeps m canonical for cse; flow deletes it) | 0 | **YES (refs 1, GR_REGS)** | the pure ghost — allocated by global, no slot: the post-regclass rule |
| p15 | p14 without the trailing mention | 0 | no | cse canonicalizes m away |
| p16–p18 | register-only 3-chains with a live head (`(n<<24)>>24`, sign chain, `+4,*3,-12`) | 0 | no | fold at cse/tree level or the middle temp is reused by `find_split_point` — combine path (b) never runs |
| lhu_tuclean | the draft with `u16 u18` in the real TU | 56 | — | DIFF 22 (frame only), 422/422 code |

## What the S83 briefs got right and wrong
* S83 hand pass (HYPOTHESIS.md): "caller-save area, transient at iteration 1" — WRONG in its `$t0` form (Fable F1: a
  pseudo in `$t0` displaces the spill register) and wrong in general (no staleness route in this function; see producer 2).
* T4b Fable (402k tokens): "ghost pseudo of the SIGN_EXTEND split" — RIGHT about the species; its "next lever" (a ghost
  from a non-memory 3-chain) is combine path (b) and is refuted here (p16–p18 + the target's chains are already folded).

## Files
`.run/P32/t4c/func_80032A74/{lhu_tuclean.c,p1..p18.c,NOTES.md}` · `.run/P32/t4c/dump.sh` (private dump + census) ·
`tools/ghost_census.py` (promoted) · `tools/cc1_dumps.sh` (repaired: frame line + census instead of the `(use)` grep) ·
dumps under `.run/P32/t4c/dumps_*/` (regenerable, ignored).

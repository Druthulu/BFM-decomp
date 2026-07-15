# func_8016CBC0 (209 ins, ov_SC01_077_after) — PIN-FREE near-miss 153/209, NEEDS FABLE5

**Result:** `match_one` **DIFF, masked-match 153/209** (56 mismatched), PIN-FREE. Draft:
`.run/giants/func_8016CBC0.opus.c` (= variant m7). Gate command (task spec):
```
.venv/bin/python tools/match_one.py func_8016CBC0 --c .run/giants/func_8016CBC0.opus.c \
  --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077_after --work .run/match_fw_8016CBC0
```
The prior dB seed was pinned (6 `register __asm__("$N")` pins → ×1-only) at masked-155. **This
draft ties it (153) while being PIN-FREE** and fixes the counter-forms + uv-split the pins broke.
It is NOT a byte match — escalating honestly per the "do not ship a pinned ×1 / new class" rule.

**Pin-free: YES.** No `register __asm__("$N")`, no hard-reg asm. Only 4 empty-string opaque fences
`__asm__("" : "=r"(t) : "0"(t))` (generic constraint, NO opcode) — pure barriers, ×134-safe (the
§42e SIGABRTs are from fixed-reg pins). Block-scoped decls, no file-scope footprint, no //@EDIT.

## Flagship levers that LANDED (measured on match_one masked)

1. **Lever B / opaque-copy fence (§36) → the 3 counter chains.** The target renders `cnt` (initial
   + loopback), `uv`, and `i` as **compute-in-caller-temp-then-copy** (`addiu vN,sN,-1;
   addu sN,vN,zero`) — the K8 global.c no-coalesce signature of a call-crossing global allocno.
   The dB **pins FORCED in-place** (`addiu sN,sN,-1`): a `register __asm__("$18")` var is a hard
   reg, so there is no coalescing decision. Pin-free alone still coalesced (cse/copy-prop fold
   `t=x-1; x=t` back to in-place — confirmed, the flagship's "pure-C dissolves" warning). Fix:
   `t = x-1; __asm__("":"=r"(t):"0"(t)); x = t; test t` — the fence makes `t` opaque so the copy
   `x=t` survives to global-alloc → K8 keeps it. (mine=204→208 ins, counters now correct.)
2. **uv-split cured (free rider of #1).** Pin-free baseline scattered `uv` to reload pseudo 201;
   the fence lands it on a clean early pseudo → $s1 (disposition `73 in 17`).
3. **SINGLE reused inner-scope `pv` pointer — fixed the first-block spine (§44-3 inverted).** Naive
   block-LOCAL scoping of the vertex temps did NOTHING (m2≡seed). The win was the OPPOSITE: one
   `u8 *pv;` at inner-loop scope, reused in both vertex blocks, so it's a **GLOBAL** allocno that
   global-alloc assigns a1 AFTER the block-local w3 grabs a0. This flipped **(short)uv→v1, po→v0,
   pv-base→a1** to exactly the target (was v0/a0/a0). This is the flagship's local-vs-global
   first-fit insight, applied by making the pointer *more* global, not less.

## Residual — ONE interlinked RC-6 qty-birth / allocno-priority lock (§31/§27), the wall

| # | issue | mine | target | class |
|---|-------|------|--------|-------|
| 1 | w0 LOAD reg | `lhu a0,0(a1)` | `lhu v1,0(a1)` | local-alloc qty first-fit at identical reg-state |
| 2 | w3 reg | a2/a3 | a0 (3rd merges to pv a1) | local-alloc qty-birth order |
| 3 | mat/i $s | mat=$s5,i=$s4 | mat=$s4,i=$s5 | global.c:594 allocno_compare priority |
| 4 | beqz delay | `li v0,-1` | `addiu v0,s5,1` (i+1) | dbr, downstream of -1 materialise point |
| 5 | length | 208 | 209 | one load-delay nop mine's schedule fills |

- **#1/#2 (the bulk, ~24 ins over both unrolled blocks):** at the *identical* register state
  (v0=po dead, v1=(short)uv dead, a1=pv live) gcc first-fits the w0 load to a0 (mine) vs v1
  (target). Target keeps the whole `w0→(short)w0→sum→av` chain in v1 (workhorse) + w3 in a0.
  Merging w0/av (Lever A var-reuse) DOES pull w0→v1 but **regresses av→a0 in the 3rd unrolled
  vertex** under the uvm/c8c pressure (net −13, m8=144). Not C-separable.
- **#3:** both mat & i are call-crossing globals with **4 refs each**; `allocno_compare`
  (`floor_log2(n_refs)*freq/live_length`) ranks i strictly above mat → i takes $s4 first.
  Declaration order (col,uv,cnt,vb,mat,i,ret → pseudos 72..78) would give the target by the
  `v1-v2` tie-break IF priorities tied — they don't. Insensitive to i-fence (m6), while-vs-break
  outer loop (m10), pointer split (m5). Can't add a mat ref cheaply (the block-copy is
  sp-relative; a mat-relative copy mismatches the target's `sw $v0,0x80($sp)`).

## Levers tried (match_one masked-match / 209)

| variant | what | matched |
|---------|------|---------|
| dB seed | pinned (×1) | 155 |
| m1 | pin-free structural | 140 |
| m2 | pinned + block-scoped vertex temps | 155 (≡seed, no effect) |
| m3 | explicit-temp counters (no fence) | ~136 (cse folds) |
| m4 | + opaque counter fences | 140 |
| **m7** | **+ single global pv (THIS)** | **153** |
| m8 | + w0/av merge | 144 (av regresses) |
| m7a | m7 − uvm fence | 146 |
| m10 | m7 clean while-outer | 153 |

Siblings func_80166994 / func_8016CF04 are switch-shaped — no transferable vertex-loop idiom.

## Fable5 handoff (gdb-on-cc1 oracle, §34 — the two roots)

The residual is two compiler-internal quantities; use the flagship's oracle to confirm each, then
hunt the pin-free C form (dumps reproducible via `.run/giants/opus_8016CBC0/dump.sh <c> <tag>`,
which adds `-dr -dj -dc -dl -dg -dS -dJ`; alignment differ `adiff.py` + `mcount.py` next to it):

1. **w0-load / w3 qty-birth (roots #1/#2).** Trace `find_free_reg` (ffr2.gdb, pointer note in the
   flagship .md: `qty_first_reg` at `0x82c5404`) at the first inner-loop vertex load. Patch the
   qty pick to force the w0 load into v1 and confirm the whole `{w0,w3,av}` block snaps to
   v1/a0 — that licenses the C search (candidate: a load-side in-out asm à la the flagship's
   `lh %0,off(%2):"0"(h),"r"(p)` to set the load's qty-birth, since var-merge regresses av).
2. **mat/i priority (root #3).** Break at global.c `allocno_compare`; dump `n_refs`, `freq`,
   `live_length` for the mat and i allocnos (pseudos 76, 77 in the greg conflict table). Confirm
   whether it's freq (inner-loop weight of mat's 2 call-arg refs) or live_length; then find the
   C form that makes mat.pri ≥ i.pri (e.g. shortening mat's live range, or a byte-neutral extra
   inner ref). If unreachable pin-free, this is the honest ceiling — the pins existed for exactly
   this $s4/$s5 swap.

Confirms the prior agent's Fable5 verdict, now from a **pin-free** base with counters + spine
already cracked (so Fable5 starts at 153 pin-free, not 155 pinned).

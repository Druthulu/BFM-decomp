#!/usr/bin/env python3
"""Phase-26 §8 ×134: bank a matched jr-function exemplar across its h_seq family siblings.

Per sibling (idempotent, revert-on-fail — the whole-binary byte-gate G3/P9 is the sole arbiter):
  1. jtbl_carve  — carve the sibling's jtbl into a dotted .rodata subseg + set <ov>_JTBL_INTERLEAVE
  2. make extract — regenerate asm + run ld_interleave (the data->rodata->data sandwich)
  3. remap_hseq + canon_sig_reconcile — template the exemplar body onto the sibling's TU
  4. make build  — whole-binary gate; keep iff byte-identical, else revert (config + src)

Usage:  jtbl_family_bank.py <func> <from_ov> <from_addr_hex> <members.json> [--raw crack.c]
        members.json = [[to_ov, to_addr_hex], ...]

--raw <crack.c>: template from the RAW crack body via remap_hseq_body instead of the exemplar's
banked source unit. REQUIRED when the exemplar banked at the `reconciled` stage: a reconciled body
is ov077-TU-SPECIFIC (§41c — uniquified type names, TU-targeted casts), so extract_unit hands the
sweep a polluted template and every sibling gate-fails. The raw crack + the per-sibling stage
ladder (raw → scoped → recovered → reconciled) is the correct composition — the same law behind
family_sweep's --reconcile-raw. (func_8015AE2C banked raw, so its unit WAS the raw crack and the
sweep worked; func_80178D40 banked reconciled and its sweep failed 0/4 until this mode.)
"""
import glob
import json
import shutil
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__))))
REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
from family_remap import remap_hseq, remap_hseq_body   # noqa: E402
from canon_sig_reconcile import reconcile     # noqa: E402
from scope_data_externs import fix as scope_data_fix   # noqa: E402


def sh(cmd):
    return subprocess.run(cmd, shell=True, capture_output=True, text=True)


def stub_file(ov, func):
    """The ONE .c holding this func's INCLUDE_ASM stub. Fail-loud on duplicates (Phase-29 §8e):
    the first-sorted-glob behavior once returned a STALE duplicate stub in a different TU
    (func_80131340 spliced into ov_SC01_077_a.c instead of ..._jr_8012ACE0.c), producing a
    misattributed `conflicting types` cascade — a wrong-TU splice, not a draft defect."""
    hits = [cf for cf in sorted(glob.glob(f"src/{ov}/{ov}*.c"))
            if re.search(rf'INCLUDE_ASM\("[^"]*",\s*{func}\);', open(cf).read())]
    if len(hits) > 1:
        sys.exit(f"jtbl_family_bank: {func} has {len(hits)} INCLUDE_ASM stubs in {ov}: {hits} — "
                 f"duplicate/stale stub; fix the source before banking (a first-match splice "
                 f"would hit the wrong TU's decl environment)")
    return hits[0] if hits else None


def region_files(ov):
    """The §8b isolation region files currently on disk for this overlay."""
    return set(glob.glob(f"src/{ov}/{ov}_jr_*.c"))


def revert(ov, cf=None, keep_regions=None, extract=True):
    """Restore the overlay to its committed state. `keep_regions` = the region files that existed
    BEFORE this bank attempt (a previously-banked core's, possibly still uncommitted) — only the
    files THIS attempt created are removed.

    `extract` (default True) RE-EXTRACTS afterwards. This is not optional for correctness: restoring
    config/ from git does NOT rewind asm/, so a reverted overlay is left GIT-CLEAN BUT UNBUILDABLE —
    and `git status` is structurally blind to it (the R22 corollary, here inside a tool's own undo).
    Byte-witnessed 2026-07-22 on the 0x8013C414 probe: after 3 gate-fails `git status` was EMPTY and
    ov_SC01_004 failed to link (`undefined reference to jtbl_8018DAC8`). Within a sweep each sibling
    is a DIFFERENT overlay, so the next sibling's own extract never repairs the previous one — the
    damage persists to whatever runs next. Pass extract=False only where the caller extracts
    immediately afterwards anyway (the clean-slate call at the top of bank_one)."""
    if cf:
        # Only `git checkout` a TRACKED path: an isolation creates region .c files that were never
        # added, and checkout on those emits `error: pathspec ... did not match any file(s) known to
        # git` while doing nothing. Those are removed by the keep_regions cleanup below instead.
        if subprocess.run(f"git ls-files --error-unmatch {cf}", shell=True,
                          capture_output=True).returncode == 0:
            subprocess.run(f"git checkout -- {cf}", shell=True)
    sh(f"python3 tools/jtbl_carve.py {ov} --revert")
    # The splat config too: a lazy isolation rewrites the CODE-subseg lines, which jtbl_carve
    # --revert does NOT touch — without this, a failed attempt leaves the isolation's config in
    # place, and the NEXT isolation walks an obj list containing the object twice (duplicate/
    # reversed subseg lines → splat "segments out of order"; byte-proven: the committed
    # ov_SC01_000 duplicate that broke the func_80178D40 sweep).
    subprocess.run(f"git checkout -- config/splat.{ov}.yaml 2>/dev/null", shell=True)
    subprocess.run(f"git checkout -- src/{ov}/ 2>/dev/null", shell=True)
    if keep_regions is not None:
        for f in region_files(ov) - keep_regions:
            os.remove(f)
    if extract:
        sh(f"make --no-print-directory -j16 extract BINARY={ov}")


def recover(body, to_ov, cf, func):
    """The §20/§24 recovery pass, run against THIS sibling's TU: `cast_call_sites` (rewrite a callee decl
    that conflicts with its real engine_core.h definition to the canonical type, and cast at the call
    site — codegen-neutral) then `reconcile_tu` (the DATA-symbol analog).

    Phase 26-A: `reconcile_decls` -> `reconcile_tu` here TOO, and this is the path that mattered most.
    This is the ×134 family sweep — the project's economic engine — and it was running every sibling
    through the FLEET-MAJORITY oracle, which is measurably wrong for the TU **16% of the time**
    (across ov_SC01_077's 12 TUs: 2,883 answers agree, **548 CONFLICT** — cc1 rejects the result —
    and 357 are absent). A poisoned declaration means that sibling silently does not bank, and the
    loss is invisible: the sweep just reports a smaller number. The irony is exact — the docstring
    below already knew the symbols are PER-OVERLAY, which is precisely why a FLEET-wide oracle could
    never have been right.

    It must be redone PER SIBLING: the conflicting symbols are largely PER-OVERLAY (`D_801812A4` in
    ov_SC01_000 vs `D_800D4F8C` in ov_SC01_077), so the exemplar's recovered decls do not transfer —
    the remapped body reintroduces the same conflict class against a different symbol set. Returns None
    if the tools produce nothing (caller falls back to the raw body)."""
    d_in, d_mid, d_out = (f".run/_fb_{k}_{to_ov}" for k in ("in", "mid", "out"))
    for d in (d_in, d_mid, d_out):
        shutil.rmtree(os.path.join(REPO, d), ignore_errors=True)
        os.makedirs(os.path.join(REPO, d), exist_ok=True)
    open(os.path.join(REPO, d_in, f"{func}.c"), "w").write(body)
    sh(f"python3 tools/cast_call_sites.py --overlay {to_ov} --src-file {cf} --in {d_in} --out {d_mid}")
    stage2 = d_mid if os.path.exists(os.path.join(REPO, d_mid, f"{func}.c")) else d_in
    sh(f"python3 tools/reconcile_tu.py --overlay {to_ov} --src-file {cf} --in {stage2} --out {d_out}")
    for d in (d_out, d_mid):
        p = os.path.join(REPO, d, f"{func}.c")
        if os.path.exists(p):
            return open(p).read()
    return None


def isolate(ov, func):
    """§8b LAZY isolation: give `func` its own code subseg so its jtbl carves without a same-subseg
    collision. Only invoked when jtbl_carve reports a NON-CONTIGUOUS collision — i.e. `func` shares a
    code object with an already-banked jr whose jtbl is not adjacent to it. Isolating every jr in all
    134 overlays upfront is byte-proven (R22 136/136) but would add ~7,200 region files, so we pay
    only for the cores we actually bank."""
    return sh(f"python3 tools/jr_isolate_all.py {ov} --only {func}")


RAW_BODY = None      # set by main() from --raw; templates via remap_hseq_body instead of extract_unit


def bank(func, from_ov, from_addr, to_ov, to_addr):
    # CROSS-ADDRESS families: the sibling hosts the same function at a DIFFERENT vram, so its symbol
    # is func_<to_addr>, not the exemplar's name. Everything on the sibling side (carve, isolation,
    # stub lookup, reconcile) must use the sibling's name; `remap_hseq` already self-renames the body
    # (T2b). The first two banked jr families were same-address, so this never surfaced until
    # func_80182268 (ov_SC01_077 @0x80182268 -> ov_SC02_000/003 @0x8017FCB0).
    to_func = "func_%08X" % to_addr
    # clean slate (idempotent): restore this overlay's config AND src to the committed state
    keep = region_files(to_ov)
    revert(to_ov, extract=False)      # the explicit extract below covers it (no double-extract)
    subprocess.run(f"git checkout -- src/{to_ov}/ 2>/dev/null", shell=True)
    # Extract FIRST so the on-disk asm matches the reverted committed config (the carve reads the
    # new fn's raw jtbl from asm/<ov>/data — a stale/absent asm from a prior config would miss it).
    if sh(f"make --no-print-directory -j16 extract BINARY={to_ov}").returncode:
        revert(to_ov, keep_regions=keep); return "extract0-fail", ""
    r = sh(f"python3 tools/jtbl_carve.py {to_ov} --func {to_func} --like {from_ov}")
    _carve_out = r.stdout + r.stderr
    # Auto-isolate on EITHER §8b same-subseg wall: the NON-CONTIGUOUS collision, OR the span-fit wall
    # ("do not fit the span" — the --like structure transfer's merged span doesn't match this sibling's
    # actual jtbl layout because another matched fn's tables share the subseg). Phase-29 finding: jr_isolate
    # unblocks the span-fit case too (byte-proven on func_8017AE2C's exemplar), same as non-contiguous —
    # splitting the fn into its own subseg shrinks the carve span to just its tables, which then fit.
    # NOTE: the DISTINCT "more rodata .align than pad specs" table-count-drift error is NOT isolate-fixable
    # and is deliberately excluded here (it falls through to carve-fail).
    if r.returncode and ("NON-CONTIGUOUS" in _carve_out or "do not fit the span" in _carve_out):
        if isolate(to_ov, to_func).returncode:
            revert(to_ov, keep_regions=keep); return "isolate-fail", ""
        if sh(f"make --no-print-directory -j16 extract BINARY={to_ov}").returncode:
            revert(to_ov, keep_regions=keep); return "extract-iso-fail", ""
        r = sh(f"python3 tools/jtbl_carve.py {to_ov} --func {to_func} --like {from_ov}")
    if r.returncode:
        revert(to_ov, keep_regions=keep)
        return "carve-fail", ((r.stdout + r.stderr).strip().splitlines()[-1:] or [""])
    if sh(f"make --no-print-directory -j16 extract BINARY={to_ov}").returncode:
        revert(to_ov, keep_regions=keep); return "extract-fail", ""
    if RAW_BODY is not None:
        body, info = remap_hseq_body(from_addr, from_ov, to_ov, to_addr, RAW_BODY)
    else:
        body, info = remap_hseq(from_addr, from_ov, to_ov, to_addr)
    if body is None:
        revert(to_ov, keep_regions=keep); return "remap-refuse", info
    cf = stub_file(to_ov, to_func)
    if not cf:
        revert(to_ov, keep_regions=keep); return "no-stub", ""

    # TWO-STAGE GATE — the recovery pass is a FALLBACK, never unconditional (the §19 lesson, now
    # byte-proven for canon_sig_reconcile too): reconcile rewrites the def to the canonical sig, and
    # its `void`->`s32` return promotion is NOT byte-neutral for a void body with no `return` — it
    # costs one instruction (proven on func_80182268: raw = MATCH 31 ins, reconciled = 32 ins, and the
    # extra word shifted the whole image +4). So gate the RAW remapped body first and only reconcile
    # if it fails (which is what the §41 def-side wall actually needs).
    orig = open(cf).read()
    m = re.search(rf'INCLUDE_ASM\("[^"]*",\s*{to_func}\);', orig)
    if not m:
        revert(to_ov, keep_regions=keep); return "no-stub", ""
    # SCOPED — the §8d fix (tools/scope_data_externs.py). `gather_externs` prepends the exemplar's data
    # decls at FILE scope; for a per-location symbol the sibling declares only at BLOCK scope inside its
    # OWN later functions (loosely typed), that carried decl establishes a global the TU never had, and
    # every later block-scope `extern` of it must now agree — they don't, so gcc rejects the TU
    # (`conflicting types for D_801812A4`). Demoting those decls into the function body declares no
    # global, preserves the TU's decl environment exactly, and is byte-neutral (an extern emits no code).
    # Strictly never worse than raw, so it also becomes the base the later recovery stages build on.
    scoped, moved = scope_data_fix(body, orig, m.start(), to_func)
    base = scoped if moved else body
    stages = [("raw", lambda: body)]
    if moved:
        stages.append(("scoped", lambda: scoped))
    stages += [("recovered", lambda: recover(base, to_ov, cf, to_func) or base),
               ("reconciled", lambda: reconcile(to_func, base, tu_path=cf))]
    last_err = ""
    for name, make in stages:
        try:
            cand = make()
        except Exception as e:
            # A stage that cannot even PRODUCE a candidate is not a failure of the sibling — skip to the
            # next one. (canon_sig_reconcile raises on a K&R definition: it expects an ANSI signature.
            # A K&R def is mandatory whenever a zero-arg engine_core.h thunk calls the function, so this
            # must not abort the bank.)
            last_err = f"{name}: {repr(e)[:90]}"
            continue
        open(cf, "w").write(orig[:m.start()] + cand + orig[m.end():])
        b = sh(f"make --no-print-directory -j16 build BINARY={to_ov}")
        if b.returncode == 0 and "[ OK ]" in b.stdout:
            return "BANKED", f"{cf} [{name}]"
        open(cf, "w").write(orig)          # restore the stub before the next stage
    revert(to_ov, cf, keep_regions=keep)
    return "gate-fail", last_err


def main():
    global RAW_BODY
    args = sys.argv[1:]
    if "--raw" in args:
        i = args.index("--raw")
        RAW_BODY = open(args[i + 1]).read()
        del args[i:i + 2]
    func, from_ov, from_addr_hex, members_path = args[:4]
    from_addr = int(from_addr_hex, 16)
    members = json.load(open(members_path))
    # The per-sibling revert restores config/ and src/ from HEAD, so an UNCOMMITTED prior family
    # bank would be silently reverted mid-sweep. Stop loudly instead (P9).
    dirty = subprocess.run("git status --porcelain -- config/ src/", shell=True,
                           capture_output=True, text=True).stdout.strip()
    if dirty:
        sys.exit("jtbl_family_bank: config/ or src/ has uncommitted changes — the per-sibling revert "
                 "restores from HEAD, so a prior uncommitted bank would be lost.\nCommit (or stash) "
                 "the previous family before sweeping the next.\n" + dirty[:400])
    tally = {}
    banked = []
    for i, (to_ov, to_addr_hex) in enumerate(members, 1):
        status, detail = bank(func, from_ov, from_addr, to_ov, int(to_addr_hex, 16))
        tally[status] = tally.get(status, 0) + 1
        if status == "BANKED":
            banked.append(to_ov)
        print(f"[{i:3}/{len(members)}] {to_ov:16} {status}"
              + (f"  {detail}" if status not in ("BANKED",) else ""), flush=True)
    print(f"\n=== {func}: {tally} ===")
    print(f"banked {len(banked)} siblings")
    json.dump(banked, open(f".run/banked_{func}.json", "w"))


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""Phase-25 T7 — the MECHANICAL family sweep (the endgame's economic engine).

For each MATCHED ov_SC01_077 function that has unmatched SAME-ADDRESS h_norm-siblings (a byte-variant of
the same engine function in other overlays), remap its matched C to each sibling with `tools/family_remap`
and byte-gate it into that overlay. Banks per-overlay matches MECHANICALLY — ~0 agent tokens per member —
turning the 11.1 MB of h_norm structural families from "draft every copy" into "crack one, remap the rest".

The whole-binary byte-gate (`harvest_verify`) is the SOLE arbiter (G3/P9): a wrong remap is rejected.
Two-phase for efficiency: stage ALL remapped drafts grouped by (overlay, split-file), then gate each group
ONCE (chunk+bisect) — ~a few hundred gate cycles, not 156x134 individual builds. Remapped drafts are already
correct + self-contained, so they gate via PLAIN harvest_verify (NOT gate_stage's transforms, which perturb
a correct draft — T3 finding). Type-using families (custom struct types / conflicting shared decls) fail the
compile and are logged for the decl-reconcile pass; they are NOT remap failures.

  tools/family_sweep.py [--source ov_SC01_077] [--limit N] [--min-sibs 1] [--chunk 8] [--commit]
                        [--only 0xADDR,0xADDR]   # sweep just these exemplar addrs (validation)
"""
import json, glob, re, subprocess, os, sys, shutil, collections, argparse
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import family_remap as FR
import family_hseq                     # §53 interlock — the ONE has_mid_jr oracle (R33, shared with dedup_extend)
import canon_sig_reconcile as CSR      # v3.2 (Phase-25 T7-M2 per-sibling re-reconcile, Q5-proven)
from scope_data_externs import fix as scope_data_fix   # §8d (Phase-26 session 8)
import normalize_self_decls as NSD     # the same-function decl-normalize (Phase-29, §17a-1 3rd direction)

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, 'tools'))
import corpus   # the derived corpus oracle (Phase 26-A)
PY = ".venv/bin/python"
SWEEP = ".run/sweep"


def sh(cmd, timeout=None):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, timeout=timeout)


def load_sigs():
    """{overlay: {addr: (nins, h_exact, h_norm)}}."""
    sig = {}
    for p in sorted(glob.glob(os.path.join(REPO, ".run/sig.ov_*.jsonl"))):
        ov = os.path.basename(p).split("sig.")[1][:-6]
        d = {}
        for line in open(p):
            r = json.loads(line)
            d[int(r["addr"], 16)] = (r["nins"], r["h_exact"], r["h_norm"])
        sig[ov] = d
    return sig


_HDR_SIG_CACHE = None
def header_sig_map():
    """{func_name: 'ret func(params)'} from the `extern <ret> func_X(<params>);` decls a DEFINE_func
    macro emits in src/shared/engine_core.h (a shared engine fn that CALLS the member forward-declares
    it). When family_remap copies the EXEMPLAR's def signature onto a member, and that member is
    forward-declared in engine_core.h with a DIFFERENT signature (e.g. `s32 *a0` vs the exemplar's
    `void *a0`), the member TU gets `conflicting types for func_X` and never compiles — the dominant
    tiny-IMM mega-pool gate-block (Phase-29 T6, byte-proven). This maps each such fn to its CANONICAL
    signature so `reconcile_def_sig` can rewrite the draft def to match (byte-neutral for pointer-type
    param diffs; the whole-binary gate arbitrates anything else, G3/P9)."""
    global _HDR_SIG_CACHE
    if _HDR_SIG_CACHE is not None:
        return _HDR_SIG_CACHE
    smap = {}
    for hdr in ("src/shared/engine_core.h", "src/shared/engine_types.h"):
        path = os.path.join(REPO, hdr)
        if not os.path.exists(path):
            continue
        for m in re.finditer(r'extern\s+([A-Za-z_][\w ]*?\**)\s*(func_[0-9A-Fa-f]+)\s*\(([^)]*)\)\s*;',
                             open(path).read()):
            ret, fn, params = m.group(1).strip(), m.group(2), " ".join(m.group(3).split())
            smap.setdefault(fn, f"{ret} {fn}({params})")   # first (engine_core precedence) wins
    _HDR_SIG_CACHE = smap
    return smap


def reconcile_def_sig(draft, to_func, smap):
    """If `to_func` is forward-declared in a shared header, rewrite the draft's DEFINITION signature
    (return type + param list) to that canonical decl, so the member TU stops seeing conflicting types.
    Body param names come from the header decl (auto-generated a0/a1/... on both sides, so they align in
    the common case; a rare name mismatch makes the body reference an undeclared name → the gate rejects
    it, never a false bank). Returns the draft unchanged if the fn isn't in a header or no def is found."""
    canon = smap.get(to_func)
    if not canon:
        return draft
    # match the def line: `<ret...> to_func(<params>) {`  (allow ptr stars + multiword return type)
    pat = re.compile(rf'(^|\n)[A-Za-z_][\w ]*?\**\s*{to_func}\s*\([^;{{]*\)\s*\{{')
    m = pat.search(draft)
    if not m:
        return draft
    return draft[:m.start()] + m.group(1) + canon + " {" + draft[m.end():]


def draft_def_ref(draft, to_func):
    """The reference decl string (`extern <ret> to_func(<params>);`) for the DEFINITION this draft
    will splice into the sibling TU — the ground truth `normalize_self_decls` conforms the TU's other
    decls of to_func to. Derived from the draft's own def line (so it is right whether or not
    --fix-def-sig canonicalized it), falling back to the engine_core.h canonical if the def is unreadable."""
    m = re.search(rf'(^|\n)([A-Za-z_][\w \t\*]*?)\b{to_func}\s*\(([^;{{]*)\)\s*\{{', draft)
    if m:
        ret, params = m.group(2).strip(), " ".join(m.group(3).split())
        return f"extern {ret} {to_func}({params});"
    return None


def stub_map(ov):
    """{addr: (src_rel, asm_subdir)} for every INCLUDE_ASM stub in this overlay's src (all split files).

    DERIVED from tools/corpus.py (Phase 26-A audit). The regex here was `func_[0-9A-Fa-f]+` only, so a
    stub carrying a CURATED symbol name was invisible — and an address absent from stub_map reads as
    "already matched". That manufactured PHANTOM matched-exemplars: family_hseq nominated them, the
    sweep re-nominated them every run, extract_unit returned None, and each run booked a silent skip.
    (The one live instance — `listCdBuffer` at 0x80180000, a stub in 100 overlays and a REAL function
    in 3 of them — is gone as of A4, but the SHAPE stays armed: curated naming is something this
    project does more of as RE quality improves, so a func_-only oracle rots by design.)

    corpus.stubs() resolves ANY C identifier through the binary's splat symbol stack and fails LOUD on
    one it cannot resolve — it can no longer mistake a named stub for a match."""
    return {s.addr: (s.path, s.asm_dir) for s in corpus.stubs(ov).values()}


def reconcile_remap(addr, source, ov, src_rel, rawdir):
    """The Q5-proven M2 member draft: symbol-remap the RAW exemplar draft (source->ov), then
    RE-RECONCILE against THIS sibling's TU (canon_sig_reconcile v3.2 — the block-scope-vs-ambient
    decisions depend on the sibling's own decompile state, so a single ov077-reconciled body can't
    just be remapped). Returns text or None."""
    fn = f"func_{addr:08X}"
    raw = os.path.join(REPO, rawdir, fn + ".c")
    if not os.path.exists(raw):
        return None
    m, err = FR.symbol_map(addr, source, ov)
    if err:
        return None
    text = open(raw).read()
    for s, d in m.items():
        text = re.sub(rf"\b{s}\b", d, text)
    CSR._AMBIENT_CACHE.pop(src_rel, None)               # sibling TU is static during phase-1 staging,
    for k in [k for k in CSR._VISIBLE_CACHE if k[0] == src_rel]:  # but each fn needs its own visibility
        CSR._VISIBLE_CACHE.pop(k, None)
    try:
        return CSR.reconcile(fn, text, None, src_rel)
    except Exception:
        return None


def reconcile_remap_hseq(from_addr, from_ov, to_ov, to_addr, to_src_rel, rawdir):
    """Phase-26 §41c: the h_seq per-sibling reconcile — the M2 path over remap_hseq. A cracked exemplar's
    RAW draft (isolation-MATCH body with its own types/sigs) can't template plainly: the reconcile is
    TU-specific. So per sibling: h_seq-remap the RAW draft (symbol + immediate + cross-address self-rename)
    then canon_sig_reconcile against THAT sibling's TU. Returns the reconciled sibling body or None."""
    raw = os.path.join(REPO, rawdir, f"func_{from_addr:08X}.c")
    if not os.path.exists(raw):
        return None
    remapped, info = FR.remap_hseq_body(from_addr, from_ov, to_ov, to_addr, open(raw).read())
    if remapped is None:
        return None
    fn_to = f"func_{to_addr:08X}"
    CSR._AMBIENT_CACHE.pop(to_src_rel, None)
    for k in [k for k in CSR._VISIBLE_CACHE if k[0] == to_src_rel]:
        CSR._VISIBLE_CACHE.pop(k, None)
    try:
        return CSR.reconcile(fn_to, remapped, None, to_src_rel)
    except Exception:
        return None


def edit_remap_sweep(a, sig, src_sig, stubs):
    """§42e --edit-remap: recover byte-drift families whose crack carries OUT-OF-BODY edits (a file-scope
    //@EDIT the remapped body doesn't contain, and/or a once-global engine_core.h flip). Per family in the
    JSON manifest: apply ec_edits ONCE to engine_core.h (byte-neutral); then per same-address h_norm sibling,
    symbol-remap the split //@EDIT directives (family_remap.symbol_map) + apply to the sibling split, stage
    the family_remap body, and gate each (overlay,split) group via plain harvest_verify (the sole arbiter —
    a body that byte-drifts or cc1-crashes fails+reverts; its already-applied edit is byte-neutral, R22-checked)."""
    manifest = json.load(open(os.path.join(REPO, a.edit_remap)))
    src = a.source

    # 1. once-global engine_core.h edits (byte-neutral; e.g. the func_80156044 return-type flip)
    ecp = os.path.join(REPO, "src/shared/engine_core.h")
    ec = open(ecp).read()
    nec = 0
    for fam in manifest["families"]:
        for e in fam.get("ec_edits", []):
            if e["old"] in ec:
                ec = ec.replace(e["old"], e["new"]); nec += 1
    if nec:
        open(ecp, "w").write(ec)
        print(f"[edit-remap] applied {nec} engine_core.h global edit(s)")

    # 2. stage per (overlay,split): symbol-remapped split-edits + the remapped body
    shutil.rmtree(os.path.join(REPO, SWEEP), ignore_errors=True)
    splits = {}                                          # src_rel -> mutated split text (accumulates edits)
    groups = collections.defaultdict(list)               # (ov, src_rel, subdir) -> [fn]
    skipped = collections.Counter()
    for fam in manifest["families"]:
        addr = int(fam["addr"], 16)
        hn = src_sig[addr][2]
        sibs = [ov for ov in sig if ov != src and addr in sig[ov]
                and sig[ov][addr][2] == hn and addr in stubs[ov]]
        for ov in sibs:
            src_rel, subdir = stubs[ov][addr]
            m, err = FR.symbol_map(addr, src, ov)
            if err:
                skipped["symmap"] += 1; continue
            body, berr = FR.remap(addr, src, ov)
            if body is None:
                skipped["remap"] += 1; continue
            txt = splits.get(src_rel)
            if txt is None:
                txt = open(os.path.join(REPO, src_rel)).read()
            for e in fam.get("edits", []):
                old, new = e["old"], e["new"]
                for k, v in m.items():                   # exemplar symbol names -> this sibling's
                    old = old.replace(k, v); new = new.replace(k, v)
                if old in txt:
                    txt = txt.replace(old, new)          # apply. Absence is FINE (already-applied, or the
                else:                                    # edit is exemplar-specific, e.g. a canon-sig-layer
                    skipped["edit-absent"] += 1          # decl a sibling lacks) — NEVER skip the sibling;
                                                         # the whole-binary byte-gate is the sole arbiter (G3/P9).
            splits[src_rel] = txt
            d = os.path.join(REPO, SWEEP, ov)
            os.makedirs(d, exist_ok=True)
            open(os.path.join(d, f"func_{addr:08X}.c"), "w").write(body + "\n")
            groups[(ov, src_rel, subdir)].append(f"func_{addr:08X}")
    for src_rel, txt in splits.items():                  # persist the edited splits for the build
        open(os.path.join(REPO, src_rel), "w").write(txt)
    print(f"[edit-remap] staged {sum(len(v) for v in groups.values())} member drafts across {len(groups)} "
          f"(overlay,split) groups; skipped {dict(skipped)}")

    # 3. gate each group via plain harvest_verify (bodies; the edits are already in the split)
    banked = collections.Counter()
    failed = collections.Counter()
    for (ov, src_rel, subdir), fns in sorted(groups.items()):
        good_sha = open(os.path.join(REPO, f"config/check.{ov}.sha")).read().split()[0]
        sh([PY, "tools/harvest_verify.py", "--binary", ov, "--src", src_rel, "--asm-subdir", subdir,
            "--out", f"build/{ov}/{ov}", "--good-sha", good_sha,
            "--drafts", os.path.join(SWEEP, ov), "--chunk", str(a.chunk),
            "--verified-out", f".run/sweep_verified.{ov}.txt",
            "--failed-out", f".run/sweep_failed.{ov}.txt"], timeout=3600)
        vpath = os.path.join(REPO, f".run/sweep_verified.{ov}.txt")
        nver = len([x for x in open(vpath).read().split() if x]) if os.path.exists(vpath) else 0
        banked[ov] += nver
        failed[ov] += len(fns) - nver
        print(f"  {ov} [{os.path.basename(src_rel)}]: {nver}/{len(fns)} banked")

    nb, nf = sum(banked.values()), sum(failed.values())
    print(f"\n[edit-remap] BANKED {nb} member-matches / {nf} failed across {len(banked)} overlays")
    if a.commit and nb:
        sh(["git", "add", "-A", "src"])
        sh(["git", "commit", "-q", "-m",
            f"feat(phase-25): T7 --edit-remap sweep — {nb} member-matches (out-of-body //@EDIT families)"])
        print("[edit-remap] committed.")
    print(json.dumps({"banked": nb, "failed": nf, "skipped": dict(skipped)}))


def hseq_sweep(a):
    """Phase-26 T3 --hseq: template h_seq FAMILIES (looser than h_norm — members may sit at DIFFERENT
    addresses per overlay and differ in a few immediates). Per family in `.run/family_hseq.json` with a
    MATCHED exemplar (its C exists), template each still-stubbed member via `family_remap.remap_hseq`
    (reloc symbol remap §40b + immediate substitution T2a + cross-address self-rename T2b), stage grouped
    by (overlay, split), and gate each group ONCE via plain harvest_verify (the sole arbiter, G3/P9).
    remap_hseq REFUSES register-drift (STRUCT) and unresolved-immediate members — that IS the member
    pre-filter, so a chunk never bisects on a hopeless draft. Pin-free templates only (§42e): a matched
    exemplar carrying hard-reg pins would cc1-crash a sibling TU → that group fails+reverts at the gate."""
    manifest = json.load(open(os.path.join(REPO, a.hseq)))
    stubs = {ov: stub_map(ov) for ov in
             [os.path.basename(p).split("sig.")[1][:-6] for p in
              sorted(glob.glob(os.path.join(REPO, ".run/sig.ov_*.jsonl")))]}
    only = set(int(x, 16) for x in a.only.split(",")) if a.only else None
    bands = None if a.band == "all" else set(a.band.split(","))

    # --source override (Phase-29 fix): the --hseq path otherwise templates from the manifest exemplar
    # (pick_exemplar hard-prefers ov_SC01_077), silently ignoring --source. When --source names a DIFFERENT
    # overlay AND that overlay carries a MATCHED member of the family, template from IT instead — the
    # wave-2 finding (ov077's spelling can carry heavy local structs remap_hseq drops; a sibling's minimal
    # spelling banks clean). Self-correcting: only a matched (non-stub) source member is used, so remap_hseq
    # always has real C to template; the whole-binary gate stays the sole arbiter (G3/P9).
    if a.source and a.source != family_hseq.EX_OV:
        n_over = 0
        for f in manifest["families"]:
            for m in f.get("members", []):
                if m[0] == a.source and int(m[1], 16) not in stubs.get(a.source, {}):
                    f["exemplar"] = dict(f["exemplar"], ov=m[0], addr=m[1], kind="matched")
                    n_over += 1
                    break
        print(f"[hseq] --source {a.source}: overrode {n_over} family exemplar(s) to a matched {a.source} member.")

    kinds = (("matched", "matched-ov077", "draft-ov077") if a.reconcile_raw
             else ("matched", "matched-ov077"))            # reconcile-raw templates from the RAW seed, so an
    fams = [f for f in manifest["families"] if f["exemplar"]["kind"] in kinds]  # unbanked ov077 crack qualifies
    if bands:
        fams = [f for f in fams if f["band"] in bands]
    if only is not None:
        fams = [f for f in fams if int(f["exemplar"]["addr"], 16) in only]
    if a.reconcile_raw:                                        # only families with a raw crack to reconcile
        fams = [f for f in fams if os.path.exists(
            os.path.join(REPO, a.reconcile_raw, f"func_{int(f['exemplar']['addr'], 16):08X}.c"))]
    if a.min_members > 1:
        fams = [f for f in fams if f["n_members"] >= a.min_members]

    # ---- §53 INTERLOCK: a has_mid_jr family CANNOT bank through this carve-less path.
    # Its exemplar's own bank required a jump-table carve (jtbl_family_bank / the §8 rodata workflow);
    # sweeping it here just burns gate cycles and returns 0% — and a 0% from the WRONG tool is the exact
    # artifact that manufactured the Phase-26 "structural families ≈0% / don't template" doctrine and
    # steered two phases of strategy (§53, Phase-28 T1). So SKIP them LOUDLY and name the right tool,
    # rather than let the omission read as a wall. `has_mid_jr` comes from the manifest (family_hseq
    # already derived it off the exemplar's words — R33: one oracle, don't re-derive).
    # --allow-jr is the escape hatch (the whole-binary byte-gate remains the sole arbiter, G3/P9).
    jr_fams = [f for f in fams if f.get("has_mid_jr")]
    if jr_fams and not getattr(a, "allow_jr", False):
        fams = [f for f in fams if not f.get("has_mid_jr")]
        skipped_members = sum(f["n_members"] for f in jr_fams)
        print(f"[hseq] §53 INTERLOCK: skipping {len(jr_fams)} has_mid_jr family(ies) "
              f"({skipped_members} member-slots) — they need the jtbl carve, NOT this sweep.\n"
              f"        route: tools/jtbl_family_bank.py <func> <from_ov> <from_addr> <members.json>\n"
              f"        (a 0% from this path would be a TOOL artifact, not a wall — §53. "
              f"Override with --allow-jr if you mean it.)")
        for f in jr_fams[:8]:
            print(f"          jr-family exemplar {f['exemplar']['addr']} band={f['band']} n={f['n_members']}")

    fams.sort(key=lambda f: -f["byte_weight_templatable"])
    if a.limit:
        fams = fams[:a.limit]
    print(f"[hseq] {len(fams)} matched-exemplar families (band={a.band}); "
          f"{sum(f['n_members'] for f in fams)} candidate members")

    # ---- phase 1: template every (exemplar -> still-stubbed member), stage by (overlay, split, subdir)
    shutil.rmtree(os.path.join(REPO, SWEEP), ignore_errors=True)
    groups = collections.defaultdict(list)                     # (ov, src_rel, subdir) -> [fn]
    skip = collections.Counter()
    hdrmap = header_sig_map() if getattr(a, "fix_def_sig", False) else {}
    nsd_snapshots = {}                                          # src_rel -> pre-edit text (§17a-1 backstop)
    for f in fams:
        exov, exaddr = f["exemplar"]["ov"], int(f["exemplar"]["addr"], 16)
        for ov, addr_s in f["members"]:
            to_addr = int(addr_s, 16)
            if (ov, to_addr) == (exov, exaddr):
                continue
            if to_addr not in stubs.get(ov, {}):               # already matched / not a stub now
                skip["not-stub"] += 1; continue
            src_rel, subdir = stubs[ov][to_addr]
            if a.reconcile_raw:                                 # §41c per-sibling reconcile from the raw crack
                draft = reconcile_remap_hseq(exaddr, exov, ov, to_addr, src_rel, a.reconcile_raw)
                if draft is None:
                    skip["reconcile-fail"] += 1; continue
            else:
                draft, info = FR.remap_hseq(exaddr, exov, ov, to_addr)
                if draft is None:
                    r = info.split(":")[0] if isinstance(info, str) else "skip"
                    skip[r[:24]] += 1; continue
            _code = re.sub(r'//[^\n]*', '', re.sub(r'/\*.*?\*/', '', draft, flags=re.S))
            if not getattr(a, "allow_pins", False) and re.search(r'__asm__\s*\(\s*"\$', _code):   # hard-reg pin (§42e): ×1-only, cc1-crashes
                skip["pinned-exemplar"] += 1; continue          # sibling TUs → skip. Strip comments first: a body
                                                                # that DOCUMENTS a removed pin ("__asm__(\"$16\") REMOVED")
                                                                # is pin-free code and must not be false-skipped.
            # §8d — place the carried DATA externs at a scope this sibling's TU can accept.
            # `remap_hseq` (via gather_externs) prepends them at FILE scope; for a per-location symbol the
            # sibling declares only at BLOCK scope inside its own later functions, that ESTABLISHES A GLOBAL
            # THE TU NEVER HAD and every later block-scope extern must now agree with it — loose typing ⇒ they
            # don't ⇒ `conflicting types for D_80115128`. Byte-proven to be the dominant gate-rejection class
            # here (as it was for the jr sweeps). Demoting is byte-neutral and never worse than raw, and the
            # whole-binary gate remains the sole arbiter (G3/P9).
            to_func = f"func_{to_addr:08X}"
            if hdrmap:                                          # T6: reconcile the def sig to the shared-header
                draft = reconcile_def_sig(draft, to_func, hdrmap)   # decl (else `conflicting types` in the TU)
            tu_path = os.path.join(REPO, src_rel)
            if getattr(a, "normalize_self_decls", False):
                # Phase-29: this sibling's OWN callers of to_func may carry a divergent block-scope decl
                # of it that collides with the def we are about to splice (`conflicting types`, per-sibling,
                # invisible in the exemplar whose caller used a fn-ptr cast). Drop each divergent decl +
                # cast its in-scope calls (byte-neutral §17a-1). This edits the TU FILE (harvest_verify's
                # baseline); snapshot it so the phase-2 MISMATCH backstop can revert a non-neutral edit.
                if src_rel not in nsd_snapshots:
                    nsd_snapshots[src_rel] = open(tu_path).read()
                new_tu, nfix, _notes = NSD.fix(open(tu_path).read(), to_func, draft_def_ref(draft, to_func))
                if nfix:
                    open(tu_path, "w").write(new_tu)
            tu = open(tu_path).read()
            mstub = re.search(rf'INCLUDE_ASM\("[^"]*",\s*{to_func}\);', tu)
            if mstub:
                draft, _moved = scope_data_fix(draft, tu, mstub.start(), to_func)
            d = os.path.join(REPO, SWEEP, ov)
            os.makedirs(d, exist_ok=True)
            open(os.path.join(d, f"func_{to_addr:08X}.c"), "w").write(draft + "\n")
            groups[(ov, src_rel, subdir)].append(f"func_{to_addr:08X}")
    print(f"[hseq] staged {sum(len(v) for v in groups.values())} member drafts across {len(groups)} "
          f"(overlay,split) groups; skipped {dict(skip)}")
    if a.stage_only:
        print(json.dumps({"families": len(fams), "staged": sum(len(v) for v in groups.values()),
                          "groups": len(groups), "skipped": dict(skip)}))
        return
    if not groups:
        print(json.dumps({"families": len(fams), "banked": 0, "failed": 0, "skipped": dict(skip)}))
        return

    # ---- phase 2: gate each group ONCE (unique verified-out per group so multi-split overlays sum right)
    banked = collections.Counter()
    failed = collections.Counter()
    for gi, ((ov, src_rel, subdir), fns) in enumerate(sorted(groups.items())):
        good_sha = open(os.path.join(REPO, f"config/check.{ov}.sha")).read().split()[0]
        vout = f".run/hseq_verified.{ov}.{gi}.txt"
        r = sh([PY, "tools/harvest_verify.py", "--binary", ov, "--src", src_rel, "--asm-subdir", subdir,
                "--out", f"build/{ov}/{ov}", "--good-sha", good_sha,
                "--drafts", os.path.join(SWEEP, ov), "--chunk", str(a.chunk),
                "--verified-out", vout, "--failed-out", f".run/hseq_failed.{ov}.{gi}.txt"], timeout=3600)
        # --normalize-self-decls backstop: a final MISMATCH means a self-decl TU edit was NOT byte-neutral
        # (a transform bug — harvest_verify always reverts a wrong DRAFT, so a wrong draft leaves the binary
        # byte-identical, just unbanked). Restore this group's edited TU from the phase-1 snapshot + rebuild
        # so byte-identity is recovered; count the members failed. The whole-binary gate stays the arbiter.
        if "MISMATCH" in (r.stdout or "") and src_rel in nsd_snapshots:
            open(os.path.join(REPO, src_rel), "w").write(nsd_snapshots[src_rel])
            sh(["make", "build", f"BINARY={ov}"], timeout=1200)
            print(f"  {ov} [{os.path.basename(src_rel)}]: ⚠ self-decl edit NON-NEUTRAL — reverted TU, 0/{len(fns)} banked")
            failed[ov] += len(fns)
            continue
        vpath = os.path.join(REPO, vout)
        nver = len([x for x in open(vpath).read().split() if x]) if os.path.exists(vpath) else 0
        banked[ov] += nver
        failed[ov] += len(fns) - nver
        print(f"  {ov} [{os.path.basename(src_rel)}]: {nver}/{len(fns)} banked")

    nb, nf = sum(banked.values()), sum(failed.values())
    print(f"\n[hseq] BANKED {nb} member-matches / {nf} failed across {len(banked)} overlays; "
          f"skipped {dict(skip)}")
    if a.commit and nb:
        sh(["git", "add", "-A", "src"])
        sh(["git", "commit", "-q", "-m",
            f"feat(phase-26): h_seq family sweep — {nb} member-matches banked via remap_hseq"])
        print("[hseq] committed.")
    print(json.dumps({"families": len(fams), "banked": nb, "failed": nf, "skipped": dict(skip)}))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--source", default="ov_SC01_077")
    ap.add_argument("--limit", type=int, default=0, help="cap #exemplars (0 = all)")
    ap.add_argument("--min-sibs", type=int, default=1)
    ap.add_argument("--chunk", type=int, default=8)
    ap.add_argument("--commit", action="store_true")
    ap.add_argument("--only", default=None, help="comma-separated exemplar addrs to sweep (validation)")
    ap.add_argument("--allow-pins", action="store_true",
                    help="bypass the §42e pinned-exemplar skip: template WITH the register pins and let the "
                         "whole-binary byte-gate arbitrate (some pinned families bank ×134 per-sibling, e.g. func_8017A4AC).")
    ap.add_argument("--allow-jr", action="store_true",
                    help="§53 escape hatch: sweep has_mid_jr families through this carve-less path anyway "
                         "(they normally need tools/jtbl_family_bank.py). The whole-binary byte-gate stays "
                         "the sole arbiter, but expect ~0% — and do NOT read that 0% as a wall.")
    ap.add_argument("--fix-def-sig", action="store_true",
                    help="T6: rewrite each member draft's DEF signature to the shared-header (engine_core.h) "
                         "canonical decl, so a member forward-declared there with a different sig (e.g. s32* vs "
                         "void*) stops throwing `conflicting types` and compiles. Byte-neutral; gate arbitrates.")
    ap.add_argument("--reconcile", default=None, metavar="RAWDIR",
                    help="M2 def-side-wall path: per (exemplar,sibling), symbol-remap the RAW draft in RAWDIR "
                         "then canon_sig_reconcile against the sibling TU (Q5-proven). Implies --no-preclassify.")
    ap.add_argument("--edit-remap", default=None, metavar="MANIFEST",
                    help="§42e out-of-body-edit path: JSON manifest of families with `edits` (split-scope "
                         "//@EDIT old||new in EXEMPLAR symbols, symbol-remapped per sibling) + optional "
                         "`ec_edits` (once-global engine_core.h, byte-neutral). Per sibling: apply the remapped "
                         "edits to the split + stage the family_remap body, gate via harvest_verify (the sole "
                         "arbiter, G3/P9 — pin-heavy families that cc1-crash fail+revert).")
    ap.add_argument("--no-preclassify", action="store_true",
                    help="skip the match_one isolation pre-classify (it can't see src/shared/engine_types.h, "
                         "so it false-negatives type-lifted families); route every remappable exemplar straight "
                         "to the harvest_verify byte-gate (the real TU sees the shared types). Use after a "
                         "build_engine_types type-lift for the decl-reconcile pass.")
    ap.add_argument("--hseq", nargs="?", const=".run/family_hseq.json", default=None, metavar="MANIFEST",
                    help="Phase-26 T3: template h_seq FAMILIES from the family_hseq manifest (cross-address + "
                         "immediate-substituting via remap_hseq), instead of the same-address h_norm path.")
    ap.add_argument("--band", default="substantial",
                    help="--hseq: family size band(s) to sweep — substantial|mid|tiny|all or a comma list")
    ap.add_argument("--min-members", type=int, default=1, help="--hseq: skip families with fewer members")
    ap.add_argument("--stage-only", action="store_true",
                    help="--hseq: stage the templated drafts to .run/sweep/ and stop before the byte-gate "
                         "(dry-run for inspection; no builds)")
    ap.add_argument("--reconcile-raw", default=None, metavar="RAWDIR",
                    help="--hseq §41c: template reconcile-class cracks — per sibling, h_seq-remap the RAW "
                         "crack draft in RAWDIR (func_<EXEMPLAR>.c) then canon_sig_reconcile against the "
                         "sibling TU. For type-heavy exemplars whose reconciled body is TU-specific.")
    ap.add_argument("--normalize-self-decls", action="store_true",
                    help="--hseq (Phase-29, §17a-1 3rd direction): before gating, drop each divergent "
                         "block/file-scope decl of the templated member IN ITS OWN SIBLING TU (left by that "
                         "overlay's caller, in a different C form than the exemplar's) and cast its in-scope "
                         "calls to the dropped sig — byte-neutral. Fixes the `conflicting types for func_X` "
                         "that blocked 133/137 of func_801670E4. Snapshotted + reverted on a gate MISMATCH.")
    a = ap.parse_args()
    os.chdir(REPO)

    if a.hseq:
        return hseq_sweep(a)

    sig = load_sigs()
    src_sig = sig[a.source]
    src_stubs = stub_map(a.source)
    stubs = {ov: stub_map(ov) for ov in sig}

    if a.edit_remap:
        return edit_remap_sweep(a, sig, src_sig, stubs)

    # exemplars: MATCHED source fns (not a stub) with >=1 unmatched same-address h_norm-sibling
    only = set(int(x, 16) for x in a.only.split(",")) if a.only else None
    exemplars = []
    for addr, (nins, hx, hn) in src_sig.items():
        if addr in src_stubs:                                   # must be matched in the source
            continue
        if only is not None and addr not in only:
            continue
        sibs = [ov for ov in sig if ov != a.source and addr in sig[ov]
                and sig[ov][addr][2] == hn and addr in stubs[ov]]
        if len(sibs) >= a.min_sibs:
            exemplars.append((addr, nins, sibs))
    exemplars.sort(key=lambda e: -e[1] * len(e[2]))             # byte-weight order
    if a.limit:
        exemplars = exemplars[:a.limit]
    print(f"[sweep] {len(exemplars)} matched exemplars w/ h_norm-siblings; "
          f"{sum(len(s) for _, _, s in exemplars)} member-remaps")

    # ---- pre-classify: only sweep exemplars whose remap match_ones (isolation). TYPE-USING families
    # (custom struct types like MatEntry) CC1-FAIL in isolation AND need decl-reconcile in the TU; a
    # compile-failing draft makes harvest_verify bisect a whole chunk (1 build -> ~8), so deferring them
    # keeps the sweep gating only clean drafts. Deferred -> .run/sweep_deferred.txt (decl-reconcile pass).
    simple, deferred = [], []
    for addr, nins, sibs in exemplars:
        if a.reconcile:                                         # M2: gate is the sole arbiter, no pre-classify
            simple.append((addr, nins, sibs)); continue
        draft, _ = FR.remap(addr, a.source, sibs[0])
        if draft is None:
            deferred.append((addr, "remap-fail")); continue
        if a.no_preclassify:                                    # trust the real-TU byte-gate (type-lift pass)
            simple.append((addr, nins, sibs)); continue
        open(os.path.join(REPO, ".run/_clsfy.c"), "w").write(draft + "\n")
        r = sh([PY, "tools/match_one.py", f"func_{addr:08X}", "--c", ".run/_clsfy.c",
                "--asm-subdir", stubs[sibs[0]][addr][1]], timeout=180)
        first = (r.stdout.strip().splitlines() or ["?"])[0]
        (simple if first.startswith("MATCH") else deferred).append(
            (addr, nins, sibs) if first.startswith("MATCH") else (addr, "type/decl" if "FAIL" in first else "diff"))
    open(os.path.join(REPO, ".run/sweep_deferred.txt"), "w").write(
        "\n".join(f"0x{a:08x} {r}" for a, r in deferred) + "\n")
    print(f"[sweep] pre-classify: {len(simple)} simple (sweep now) / {len(deferred)} deferred "
          f"(decl-reconcile/investigate -> .run/sweep_deferred.txt)")
    exemplars = simple

    # ---- phase 1: remap every (exemplar -> sibling), stage grouped by (overlay, split src, asm subdir)
    shutil.rmtree(os.path.join(REPO, SWEEP), ignore_errors=True)
    groups = collections.defaultdict(list)                     # (ov, src_rel, subdir) -> [fn]
    remap_fail = 0
    for addr, nins, sibs in exemplars:
        for ov in sibs:
            src_rel, subdir = stubs[ov][addr]
            if a.reconcile:
                draft = reconcile_remap(addr, a.source, ov, src_rel, a.reconcile)
            else:
                draft, _ = FR.remap(addr, a.source, ov)
            if draft is None:
                remap_fail += 1
                continue
            d = os.path.join(REPO, SWEEP, ov)
            os.makedirs(d, exist_ok=True)
            open(os.path.join(d, f"func_{addr:08X}.c"), "w").write(draft + "\n")
            groups[(ov, src_rel, subdir)].append(f"func_{addr:08X}")
    print(f"[sweep] staged {sum(len(v) for v in groups.values())} drafts across {len(groups)} (overlay,split) "
          f"groups; {remap_fail} remap-fail")

    # ---- phase 2: gate each group ONCE (plain harvest_verify; remapped drafts need no transforms)
    banked = collections.Counter()
    failed = collections.Counter()
    for (ov, src_rel, subdir), fns in sorted(groups.items()):
        good_sha = open(os.path.join(REPO, f"config/check.{ov}.sha")).read().split()[0]
        r = sh([PY, "tools/harvest_verify.py", "--binary", ov, "--src", src_rel, "--asm-subdir", subdir,
                "--out", f"build/{ov}/{ov}", "--good-sha", good_sha,
                "--drafts", os.path.join(SWEEP, ov), "--chunk", str(a.chunk),
                "--verified-out", f".run/sweep_verified.{ov}.txt",
                "--failed-out", f".run/sweep_failed.{ov}.txt"], timeout=3600)
        vpath = os.path.join(REPO, f".run/sweep_verified.{ov}.txt")
        nver = len([x for x in open(vpath).read().split() if x]) if os.path.exists(vpath) else 0
        banked[ov] += nver
        failed[ov] += len(fns) - nver
        print(f"  {ov} [{os.path.basename(src_rel)}]: {nver}/{len(fns)} banked")

    nb, nf = sum(banked.values()), sum(failed.values())
    print(f"\n[sweep] BANKED {nb} member-matches / {nf} failed (decl-reconcile/byte) across {len(banked)} overlays")
    if a.commit and nb:
        sh(["git", "add", "-A", "src"])
        sh(["git", "commit", "-q", "-m",
            f"feat(phase-25): T7 mechanical family sweep — {nb} member-matches banked via family_remap"])
        print("[sweep] committed.")
    print(json.dumps({"exemplars": len(exemplars), "banked": nb, "failed": nf}))


if __name__ == "__main__":
    main()

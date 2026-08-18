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
import concurrent.futures as _cf
import threading as _th
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import family_remap as FR
import family_hseq                     # §53 interlock — the ONE has_mid_jr oracle (R33, shared with dedup_extend)
import canon_sig_reconcile as CSR      # v3.2 (Phase-25 T7-M2 per-sibling re-reconcile, Q5-proven)
from scope_data_externs import fix as scope_data_fix   # §8d (Phase-26 session 8)
import scope_data_externs as SDE       # §37 auto-alias + its decl regexes (P30 S47-F2/F2b)
import normalize_self_decls as NSD     # the same-function decl-normalize (Phase-29, §17a-1 3rd direction)
import scope_tu_externs as STU         # §103 — the TU-side decl-scope lever (Phase-29 T51/T56)
import cast_call_sites as CCS          # §17a-1/§20 — the CALLEE-conflict lever (Phase-29 T77)

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, 'tools'))
import corpus   # the derived corpus oracle (Phase 26-A)
import cdecl    # the coverage-asserting C-declaration parser (Phase 26-A) — used by _merge_sig
PY = ".venv/bin/python"
_OV_LOCKS = __import__("collections").defaultdict(_th.Lock)   # two splits of ONE overlay build the same binary
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
_MACRO_DEF_SIG_CACHE = None


def macro_def_sig_map():
    """{func_name: 'ret func(params)'} from the DEFINE_func_X() macros in engine_core.h that DEFINE
    the function (`void func_80142C84(s32 a0) { ... }`), as opposed to `header_sig_map()` which reads
    the `extern` decls a macro emits for its callees.

    §121 (Phase-29 T95): a draft that references such a function has nothing to harvest — `gather_externs`
    copies file-scope `extern` lines out of the exemplar TU, and a macro-DEFINED shared function has no
    extern anywhere. The member TU instantiates the macro too, but often BELOW the splice point, so the
    symbol is `undeclared (first use)` when our body uses it as a value (a cast call site). Guessing the
    type is worse than useless — a no-prototype `extern s32 f();` then collides with the macro's real
    `void f(s32)`. Byte-verified on func_80142B2C: undeclared -> (wrong guess) conflicting types ->
    MATCH (34 ins) once the extern is synthesised from the macro's OWN definition head."""
    global _MACRO_DEF_SIG_CACHE
    if _MACRO_DEF_SIG_CACHE is not None:
        return _MACRO_DEF_SIG_CACHE
    smap = {}
    path = os.path.join(REPO, "src/shared/engine_core.h")
    if os.path.exists(path):
        txt = open(path).read()
        for m in re.finditer(r'#define\s+DEFINE_(func_[0-9A-Fa-f]+)\(\)\s*\\\n((?:.*\\\n)*?.*?)\{',
                             txt):
            fn, body = m.group(1), m.group(2)
            d = re.search(rf'([A-Za-z_][\w \*]*?)\s*\b{fn}\s*\(([^)]*)\)\s*$',
                          body.replace("\\\n", "\n").strip().split("\n")[-1])
            if d and d.group(1).strip():
                smap[fn] = f"{d.group(1).strip()} {fn}({d.group(2).strip()})"
    _MACRO_DEF_SIG_CACHE = smap
    return smap


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
    to the canonical TYPES while KEEPING THE BODY'S PARAMETER NAMES, so the member TU stops seeing
    conflicting types without the body losing the identifiers it references.

    THE NAME BUG THIS FIXES (Phase 29 T59/T60). The first cut substituted the canonical decl string
    WHOLESALE — types AND names. Its docstring called a name mismatch "rare", and said the gate would
    reject it. Both were wrong in the way that matters: an exemplar drafted with the `param_N`
    convention hits it EVERY time, and the result is not a rejected match but a whole family booking
    as a compile failure — indistinguishable from a compiler wall:

        canonical : void func_8014D610(s32 a0, void *a1, void *a2)
        draft body: ... param_1 ...            ->  `param_1' undeclared (first use this function)

    Three families / 411 members sat at 0/N on exactly this. The types are what cc1 compares; the
    names are the body's own business, and both are in hand right here.

    Parsed with `cdecl`, not a regex (R33): `base` is the return type, `params` the types, `pnames`
    the names. Falls back to the wholesale canonical string when a canonical param type is one this
    cannot safely re-render (a function-pointer or array parameter) — honest, and no worse than before.
    Returns the draft unchanged if the fn isn't in a header or no def is found."""
    canon = smap.get(to_func)
    if not canon:
        return draft
    # match the def line: `<ret...> to_func(<params>) {`  (allow ptr stars + multiword return type)
    pat = re.compile(rf'(^|\n)[A-Za-z_][\w ]*?\**\s*{to_func}\s*\([^;{{]*\)\s*\{{')
    m = pat.search(draft)
    if not m:
        return draft
    sig = _merge_sig(m.group(0), canon, to_func, body=draft[m.end():])
    if sig is None:                       # a precondition failed — leave the draft's own signature alone
        return draft
    return draft[:m.start()] + m.group(1) + sig + " {" + draft[m.end():]


_RET_WARNED = set()


def _return_axis_safe(to_func, draft_ret, canon_ret, body=""):
    """§85, applied to the DEFINITION side. Changing a function's return type is byte-neutral only if
    NO caller consumes the return — a consumed return changes the CALLER's codegen. `conform_decls`
    already enforces this for declaration rewrites and REFUSES when it fails; the same rule binds
    here, and nothing was checking it (Phase 29 T60).

    When it fails, the header is the artifact that disagrees with the byte truth, not the draft:
    `engine_core.h` declares `func_8014D610` returning `void` while its callers use the value, so
    conforming the definition to `void` emitted `void value not ignored as it ought to be` — an
    uncompilable draft, booked family-wide as a compile failure. Refusing here keeps the draft
    honest and names the real fix (correct the header, which is fleet-shared blast radius §61/§63).

    Reuses conform_decls.consumers (R33 — one implementation of the precondition, not two)."""
    if draft_ret == canon_ret:
        return True
    # DEMOTING TO `void` ALSO CHANGES THE CALLEE'S OWN CODEGEN, and the caller-side test above is
    # blind to it: if the body says `return <expr>;`, making the function `void` lets gcc delete the
    # whole computation feeding it as dead. Byte-measured (Phase 29 T62): func_8016163C demoted
    # s32 -> void compiled to 58 instructions against a 78-instruction target — a SIZE-MISMATCH the
    # classifier routes to `redraft`, i.e. the tool manufactured a "different function" and then the
    # verdict blamed the draft. The §85 note records the same hazard in the other direction (a
    # void->s32 promotion costs one instruction on a body with no return).
    if canon_ret.strip() == 'void' and re.search(r'\breturn\s+[^;\s]', body):
        if to_func not in _RET_WARNED:
            _RET_WARNED.add(to_func)
            print(f"  [fix-def-sig] {to_func}: REFUSED the return-axis change "
                  f"{draft_ret!r} -> 'void' — the BODY returns a value, so demoting deletes the "
                  f"computation feeding it. The shared header disagrees with the byte truth.",
                  flush=True)
        return False
    import conform_decls
    cs = conform_decls.consumers(to_func)
    if not cs:
        return True
    if to_func not in _RET_WARNED:        # once per function, not once per member (x137)
        _RET_WARNED.add(to_func)
        print(f"  [fix-def-sig] {to_func}: REFUSED the return-axis change "
              f"{draft_ret!r} -> {canon_ret!r} — {len(cs)} caller(s) CONSUME the return (§85). "
              f"The shared header disagrees with the byte truth; correcting it is the real fix.",
              flush=True)
    return False


def _render_param(ctype, name):
    """`void*` + `a1` -> `void *a1`;  `s32` + `a0` -> `s32 a0`. cdecl renders a param type with its
    stars glued on, which is not how a declarator is written."""
    stars = len(ctype) - len(ctype.rstrip('*'))
    return f"{ctype.rstrip('*')} {'*' * stars}{name}" if name else ctype


_USE_WARNED = set()


def _param_use_safe(to_func, dnames, dtypes, ctypes, body):
    """Retyping a parameter is only safe if the BODY does not depend on its type.

    Conforming the TYPES has the same failure mode the name bug had, one level down: the canonical
    decl is what cc1 compares, but the body was written against the DRAFT's types. `func_8014D610`'s
    header says `void *a2` where the byte-true definition takes `u16 *param_3`, and the body does
    `param_3[0]` — retyped to `void *` that is `void value not ignored as it ought to be`, i.e. an
    uncompilable draft booked family-wide as a compile failure (Phase 29 T61).

    The test is not "are the types compatible" (the tool's whole PURPOSE is pointer-type param
    diffs, per header_sig_map's docstring — those are usually byte-neutral) but **"does the body USE
    this parameter in a way its type governs"**: an index, a dereference, or a `->`. A parameter
    merely passed through or cast at use is retype-safe; one that is indexed is not."""
    for i, ct in enumerate(ctypes):
        if i >= len(dtypes) or ct == dtypes[i]:
            continue
        nm = dnames[i] if i < len(dnames) and dnames[i] else None
        if not nm:
            continue
        if re.search(rf'\b{re.escape(nm)}\s*\[', body) or \
           re.search(rf'\*\s*{re.escape(nm)}\b', body) or \
           re.search(rf'\b{re.escape(nm)}\s*->', body):
            if to_func not in _USE_WARNED:
                _USE_WARNED.add(to_func)
                print(f"  [fix-def-sig] {to_func}: REFUSED the param-type change "
                      f"{dtypes[i]!r} -> {ct!r} for {nm!r} — the body indexes/dereferences it, so "
                      f"retyping breaks it. The shared header disagrees with the byte truth; "
                      f"correcting the header is the real fix.", flush=True)
            return False
    return True


def _merge_sig(def_line, canon, to_func, body=""):
    """Canonical TYPES + the definition's own parameter NAMES -> a signature string (no trailing brace).

    Positional: name[i] comes from the draft where it has one, else from the canonical decl. An arity
    mismatch is not smoothed over — the canonical arity governs the declaration (it is what callers
    see), and if the draft had MORE parameters its extra names simply are not declared, so the body
    references an undeclared identifier and the byte-gate rejects it. That is the correct outcome for
    a genuinely disagreeing signature; it must not be papered into a false bank (G3/P9)."""
    try:
        cd = cdecl.parse(canon.rstrip('; ') + ';')[0]
        dd = cdecl.parse(def_line.strip().lstrip('\n').rstrip('{ \t\n') + ';')[0]
    except Exception:
        return canon
    if not _return_axis_safe(to_func, dd.base, cd.base, body):
        return None                       # refuse: the caller leaves the draft's own signature alone
    ctypes = cd.params or []
    if any(('(' in t or '[' in t) for t in ctypes):     # fn-ptr / array param: cannot re-render safely
        return canon
    if not ctypes:
        # `(void)` and `()` both parse to params==[] and are NOT the same declaration (§99: `()` is
        # the no-prototype form). Distinguish them on the raw text:
        #   `()`     -> a NO-PROTOTYPE decl constrains nothing. Conforming to it would DELETE the
        #              definition's parameters and leave the body referencing undeclared names
        #              (`param_1' undeclared, 137 members — Phase 29 T74, caused by this tool
        #              meeting the §99 header fix). Refuse: there is nothing to conform to.
        #   `(void)` -> a real zero-parameter prototype; hand back the canonical verbatim.
        if re.search(r'\(\s*\)\s*$', canon.strip()):
            return None
        return canon
    dnames = list(dd.pnames or [])
    cnames = list(cd.pnames or [])
    if not _param_use_safe(to_func, dnames, dd.params or [], ctypes, body):
        return None
    out = []
    for i, t in enumerate(ctypes):
        nm = (dnames[i] if i < len(dnames) and dnames[i] else
              (cnames[i] if i < len(cnames) and cnames[i] else f"a{i}"))
        out.append(_render_param(t, nm))
    return f"{cd.base} {to_func}({', '.join(out)})"


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


_TU_DATA_TYPES = {}


def _tu_data_types(tu_path):
    """{D_sym -> declared type text} AS CC1 SEES IT (`cdecl.tu_scope`, i.e. cpp), cached per TU.

    The text scanners cannot see a MACRO-INJECTED declaration, and that is where these conflicts
    live: `extern Vec8 D_80114F24;` sits inside a DEFINE_func_* macro body in engine_core.h while
    the overlay .c contains only `DEFINE_func_XXXX()`. tu_scope is the repo's stated oracle for
    "what does this TU declare", and its own docstring warns that the `above` form answers
    visibility, NOT conflict — C requires compatibility regardless of order, so the FULL scope is
    the right question here."""
    if tu_path not in _TU_DATA_TYPES:
        try:
            sc = cdecl.tu_scope(tu_path)
            _TU_DATA_TYPES[tu_path] = {n: SDE._decl_type_text(d.text or '', n)
                                       for n, d in sc.items()
                                       if n.startswith('D_') and d.text and
                                       SDE._decl_type_text(d.text or '', n)}
        except Exception as e:                    # never block a sweep on the oracle (R32: loud)
            print(f"  [tu-types] {tu_path}: {repr(e)[:80]}", flush=True)
            _TU_DATA_TYPES[tu_path] = {}
    return _TU_DATA_TYPES[tu_path]


def _alias_group_data_conflicts(groups):
    """§37-alias any DATA symbol that the drafts staged into ONE TU declare with DIFFERENT types.

    THE COLLISION `scope_data_fix` CANNOT SEE (P30 S47-F2b, byte-witnessed). That function is handed
    one draft plus the PRE-SPLICE TU, so it detects draft-vs-TU disagreements only. But this sweep
    stages EVERY member of an (overlay, split) group into the same TU before gating, and two
    templated bodies routinely carry different views of one address — `D_80114F24` is `s32` in one
    body and `Vec8` in another, `D_80078EB4` is `s16` at 2,409 fleet sites and `u16` at 1,341.
    Measured: ov_MAIN_012 failed `conflicting types for D_80114F24` at the SPLICE POINT while the TU
    itself declares that symbol nowhere — the two drafts were conflicting with each other.

    Canonicalising is not available: for data the declared type drives the load (`lh` vs `lhu`), so
    one type would silently change the codegen of every view that is not it. Each body keeps its own
    type and gets a PER-DRAFT private name bound by an asm label, which is what the fleet already
    hand-writes for `D_800AE620` (9 sites). The alias is suffixed with the function so that two
    conflicting drafts cannot collide on the alias itself — the bug this fix would otherwise create.
    Codegen is unchanged: the label fixes the emitted symbol, so the same load reaches the address."""
    n = 0
    for (ov, _src_rel, _subdir), fns in groups.items():
        paths = {fn: os.path.join(REPO, SWEEP, ov, fn + ".c") for fn in fns}
        texts = {fn: open(p).read() for fn, p in paths.items() if os.path.exists(p)}
        views = collections.defaultdict(lambda: collections.defaultdict(list))
        for fn, txt in texts.items():
            for ln in txt.split("\n"):
                if not SDE.ANY_EXTERN_RE.match(ln) or SDE.is_asm_alias(ln):
                    continue
                d = SDE.DATA_SYM_RE.search(ln)
                ty = SDE._decl_type_text(ln, d.group(0)) if d else None
                if ty:
                    views[d.group(0)][SDE._norm_ws(ty)].append(fn)
        for sym, byty in views.items():
            if len(byty) < 2:
                continue                                  # one view across the group ⇒ no conflict
            for fns_with in byty.values():
                for fn in fns_with:
                    alias = f"aD{sym[2:]}_{fn[5:]}"
                    t = re.sub(rf'\b{re.escape(sym)}\b', alias, texts[fn])
                    t = t.replace(f'__asm__("{alias}")', f'__asm__("{sym}")')
                    t = re.sub(rf'^(\s*extern\s[^;\n]*\b{re.escape(alias)}\b[^;\n]*?)\s*;',
                               rf'\1 __asm__("{sym}");', t, count=1, flags=re.M)
                    texts[fn] = t
                    n += 1
        for fn, txt in texts.items():
            open(paths[fn], "w").write(txt)
    return n


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
    # Binary set DERIVED from src/ dirs (ov_* + md_* + resident), mirroring family_hseq (P30 S45):
    # the old `.run/sig.ov_*.jsonl` glob had no md_ entries, so every module member fell into
    # `stubs.get(ov, {})` = {} -> counted "not-stub" -> silently skipped (the R32 class again).
    _bins = [os.path.basename(d) for d in
             sorted(glob.glob(os.path.join(REPO, "src/ov_*"))) +
             sorted(glob.glob(os.path.join(REPO, "src/md_*")))]
    if os.path.isdir(os.path.join(REPO, "src/resident")):
        _bins.append("resident")
    stubs = {ov: stub_map(ov) for ov in _bins}
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
            # A freshly-banked <source> member sits in matched_members (family_hseq moves matched
            # members out of `members` after a sig-regen), so search BOTH lists (Phase-29 crack-wave
            # fix: the fresh-exemplar sweep is the whole point of --source, and the member is matched).
            for m in list(f.get("members", [])) + list(f.get("matched_members", [])):
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
        # ---- R32/R33 (P31 S56): --only IS KEYED ON THE FAMILY'S EXEMPLAR ADDRESS, and the caller
        # almost never has those. The natural thing to pass after a crack wave is the addresses you
        # just BANKED -- which are family MEMBERS. Keyed strictly, that silently selects almost
        # nothing: wave Z passed 15 banked addrs, matched 2 families, swept 4 candidates and banked
        # 3, reporting success. Re-derived through member lookup it was 21 families / 196 open
        # members / 50 banked. A 17x difference, invisible, because the tool answered exactly what
        # was asked. So: resolve member addrs to their family too, and ALWAYS report the coverage.
        by_ex = {int(f["exemplar"]["addr"], 16): f for f in fams}
        member_of = {}
        for f in fams:
            for m in list(f.get("members", [])) + list(f.get("matched_members", [])):
                member_of.setdefault(int(m[1], 16), f)
        picked, via_member, unresolved = {}, 0, []
        for addr in only:
            f = by_ex.get(addr)
            if f is None:
                f = member_of.get(addr)
                if f is not None:
                    via_member += 1
            if f is None:
                unresolved.append(addr)
            else:
                picked[id(f)] = f
        print(f"[hseq] --only: {len(only)} addr(s) -> {len(picked)} family(ies) "
              f"({len(only) - via_member - len(unresolved)} matched an exemplar directly, "
              f"{via_member} resolved via family MEMBERSHIP, {len(unresolved)} unresolved)")
        if unresolved:
            print("[hseq] UNRESOLVED (not an exemplar and not a member of any sweepable family): "
                  + ", ".join(f"0x{x:08x}" for x in sorted(unresolved)[:12]))
        if not picked:
            sys.exit("[hseq] REFUSING: --only resolved to ZERO families. Passing addresses that are "
                     "not exemplars and not members yields a silent no-op that reads as a clean 0. "
                     "Check the addrs against .run/family_hseq.json, or drop --only.")
        fams = list(picked.values())
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
    tu_snapshots = {}          # src_rel -> pre-edit TEXT. Shared backstop for BOTH staging-time TU
                               # edits: --normalize-self-decls (§17a-1) and tu-scope (§103). Reverted
                               # on MISMATCH (non-neutral) or on a zero-bank group (§61 undo law).
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
            # PINS ARE SWEPT BY DEFAULT (Phase 29 SESSION-22). This guard skipped any exemplar
            # carrying a `register __asm__("$N")` pin because templating it cc1-CRASHED the sibling
            # TUs (§42e). **Phase 27 byte-proved that SIGABRT was `extract_unit` dropping the body's
            # file-scope macros — OUR bug — and fixed it (`_carry_macros`);** its own roadmap delta
            # then put the PINS class "back on the mechanical-harvest table". The cause was removed
            # and the default never changed, so the guard kept skipping real work: measured on ONE
            # family this session, `func_80175AB8` reported `skipped {'pinned-exemplar': 137}` and
            # then banked **133/137** the moment it was bypassed. A protection whose cause is gone is
            # not free — it is a silent skip (R32) wearing a safety label. The whole-binary byte-gate
            # was always the real arbiter here; `--no-pins` restores the old behaviour.
            if getattr(a, "no_pins", False) and re.search(r'__asm__\s*\(\s*"\$', _code):
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
                # SNAPSHOT ONLY WHEN WE ACTUALLY EDIT (Phase-30 S6e). The snapshot used to be taken
                # unconditionally, one line before the `if nfix:` that decides whether to edit at all —
                # so a TU that NSD merely INSPECTED still landed in `tu_snapshots`, and the phase-2
                # MISMATCH backstop then attributed ANY group failure to a "self-decl edit" that was
                # never made: it reverted the TU and reported `0/N banked`. MEASURED: **909 of 909
                # groups** took that branch in one run, while NSD actually fired on ~25% of members
                # (3 of 12 probed) — so the flag could not bank anything, and its 0/1,622 was a TOOL
                # artifact, not a verdict on the lever. The §103 tu-scope path below has always
                # snapshotted inside its own `if _rep["moved"]:`; this now matches it.
                _cur = open(tu_path).read()
                new_tu, nfix, _notes = NSD.fix(_cur, to_func, draft_def_ref(draft, to_func))
                if nfix:
                    if src_rel not in tu_snapshots:
                        tu_snapshots[src_rel] = _cur
                    open(tu_path, "w").write(new_tu)
            tu = open(tu_path).read()
            mstub = re.search(rf'INCLUDE_ASM\("[^"]*",\s*{to_func}\);', tu)
            if mstub and not getattr(a, "no_tu_scope", False):
                # TU-SCOPED (§103, Phase-29 T56) — must run BEFORE scope_data_fix, because it is what
                # makes scope_data_fix's give-up branch unnecessary. §8d DROPS the draft's own decl of a
                # symbol the TU already declares at FILE scope, letting the TU's type govern the body:
                # right when they agree, fatal when the byte-true draft needs a different one (a
                # file-scope extern constrains every LATER function in the TU). That is not a codegen
                # wall even though it gate-fails like one — it cost func_80135260 133 of 137 siblings
                # until the TU's decl was moved, and it is what blocked func_80144090 at 0/136 (T55:
                # `conflicting types for D_800A651C`). Moving the TU's decl into its consumers is
                # declaration-only, so it does NOT violate this sweep's plain-harvest_verify rule —
                # that rule is about not perturbing a correct DRAFT, and this never touches the draft.
                # Byte-neutral by construction, and the two backstops below undo it if it was not
                # neutral or bought nothing.
                try:
                    _syms = STU.contested(draft, tu, mstub.start())
                    if _syms:
                        _new_tu, _rep = STU.scope(tu, _syms, mstub.start())
                        if _rep["moved"]:
                            if src_rel not in tu_snapshots:
                                tu_snapshots[src_rel] = tu
                            open(tu_path, "w").write(_new_tu)
                            tu = _new_tu
                            mstub = re.search(rf'INCLUDE_ASM\("[^"]*",\s*{to_func}\);', tu)
                except STU.ScopeRefused as e:
                    print(f"  [tu-scope] {ov} {to_func}: {e}", flush=True)   # loud, never fatal (R32)
            if mstub:
                draft, _moved = scope_data_fix(draft, tu, mstub.start(), to_func,
                                               _tu_data_types(tu_path))
            # CALLEE-CONFLICT (§17a-1/§20, Phase-29 T77) — the THIRD decl axis, and the one nothing in
            # this pipeline reconciled. scope_data_fix handles DATA externs; reconcile_def_sig handles
            # the draft's OWN signature; neither touches a CALLEE the draft declares differently from
            # the target TU. That is what blocked every byte-identical family measured in T76:
            #   func_80173A60 -> `conflicting types for func_80173B4C`   (a callee)
            #   func_8012F40C -> `conflicting types for RotTransPers`    (a PsyQ library symbol)
            #   0x80143d28    -> `conflicting types for ApplyMatrixSV`
            # cast_call_sites already solves exactly this (rewrite the decl to the TU's canonical,
            # cast each call site back to the draft's intended sig — gcc folds the cast of a known
            # symbol to a direct jal, so it is codegen-neutral). It lived only in gate_stage, which
            # this sweep deliberately does not use — the same "lever unreachable from this path" shape
            # as T56. The canonical map is derived from the TU by cpp (cdecl.tu_scope), so it sees
            # macro-injected declarations, and it is read AFTER the tu-scope edit is on disk.
            if mstub and not getattr(a, "no_cast_callees", False):
                try:
                    _canon, _ = CCS.canonical_map(ov, src_file=tu_path)
                    draft, _ncast = CCS.transform(draft, to_func, _canon)
                except Exception as e:
                    print(f"  [cast-callees] {ov} {to_func}: {repr(e)[:90]}", flush=True)
            # TYPE-NAME COLLISION (§120, Phase-29 T93) — a draft may define a local struct/typedef
            # whose auto-generated name (`S_AF634`) ALSO names a type at file scope in this sibling's
            # TU, so cc1 dies with `conflicting types` before codegen. Renaming a DRAFT-defined type
            # is byte-neutral (C type names never reach codegen), and
            # canon_sig_reconcile._uniquify_draft_types is exactly this lever — it lived only on the
            # --reconcile-raw path (the 5th "lever unreachable from THIS path" this phase).
            # Byte-verified on func_801759D8: rtu_match CC1 FAIL -> MATCH (56 ins) with this alone.
            try:
                draft = CSR._uniquify_draft_types(
                    draft, CSR.tu_ambient(tu_path).get("typedefs", {}), to_func)
            except Exception as e:
                print(f"  [uniquify-types] {ov} {to_func}: {repr(e)[:90]}", flush=True)
            # §121 — declare macro-DEFINED callees the draft references but nothing declares
            # ABOVE it (the member TU instantiates DEFINE_func_X() below our splice point).
            try:
                _mds = macro_def_sig_map()
                _need = []
                for _fn in sorted(set(re.findall(r'\bfunc_[0-9A-Fa-f]{8}\b', draft))):
                    if _fn == to_func or _fn not in _mds:
                        continue
                    if re.search(rf'\b(?:extern|void|s32|u32|int|char|short|float)\b[^;\n]*\b{_fn}\s*\(', draft):
                        continue                       # already declared/defined in the draft
                    _need.append(f"extern {_mds[_fn]};")
                if _need:
                    draft = "\n".join(_need) + "\n" + draft
            except Exception as e:
                print(f"  [macro-extern] {ov} {to_func}: {repr(e)[:90]}", flush=True)
            d = os.path.join(REPO, SWEEP, ov)
            os.makedirs(d, exist_ok=True)
            open(os.path.join(d, f"func_{to_addr:08X}.c"), "w").write(draft + "\n")
            groups[(ov, src_rel, subdir)].append(f"func_{to_addr:08X}")
    _nal = _alias_group_data_conflicts(groups)
    print(f"[hseq] staged {sum(len(v) for v in groups.values())} member drafts across {len(groups)} "
          f"(overlay,split) groups; skipped {dict(skip)}"
          + (f"; aliased {_nal} draft-vs-draft data conflict(s)" if _nal else ""))
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
    _items = sorted(groups.items())

    # PHASE 2a — run the gates in PARALLEL ACROSS DISTINCT BINARIES, then phase 2b consumes the
    # results in the ORIGINAL serial order. Only the subprocess call moves; every line of the
    # post-processing below (the MISMATCH backstop, the zero-bank restore, the counters, the prints)
    # runs exactly as before, in order, so output stays deterministic.
    #
    # WHY: SESSION-20 measured serial gating as "roughly an 8-16x throughput loss on a 32-thread box"
    # and built `tools/sweep_parallel.py` for it — but only reachable via a manual `--stage-only`
    # two-step, so THIS path stayed serial and three sweeps in SESSION-22 (543 members) ran serially
    # for no reason (§101, the stale-default class).
    #
    # SAFE, and not a new claim: the Makefile already builds binaries concurrently (`check-all`/
    # `extract-all` run `xargs -P$(JOBS)`, JOBS=16) and bulk_harvest's farm does the same with a
    # per-binary lock. The hazard §28 records is two makes racing on the SAME artifacts — prevented
    # here by the per-overlay lock, since two splits of one overlay build the same binary.
    def _gate(gi, key):
        ov, src_rel, subdir = key
        good_sha = open(os.path.join(REPO, f"config/check.{ov}.sha")).read().split()[0]
        with _OV_LOCKS[ov]:
            return sh([PY, "tools/harvest_verify.py", "--binary", ov, "--src", src_rel,
                       "--asm-subdir", subdir, "--out", f"build/{ov}/{ov}", "--good-sha", good_sha,
                       "--drafts", os.path.join(SWEEP, ov), "--chunk", str(a.chunk),
                       "--verified-out", f".run/hseq_verified.{ov}.{gi}.txt",
                       "--failed-out", f".run/hseq_failed.{ov}.{gi}.txt"], timeout=3600)

    _res = {}
    if a.jobs > 1 and len(_items) > 1:
        print(f"[hseq] gating {len(_items)} group(s) across distinct binaries, -j{a.jobs}")
        with _cf.ThreadPoolExecutor(max_workers=a.jobs) as _ex:
            _f = {_ex.submit(_gate, gi, key): gi for gi, (key, _fns) in enumerate(_items)}
            for _fu in _cf.as_completed(_f):
                _res[_f[_fu]] = _fu.result()
    else:
        for gi, (key, _fns) in enumerate(_items):
            _res[gi] = _gate(gi, key)

    # ---- phase 2b: consume the results in the original order (unchanged from the serial version)
    for gi, ((ov, src_rel, subdir), fns) in enumerate(_items):
        vout = f".run/hseq_verified.{ov}.{gi}.txt"
        r = _res[gi]
        # --normalize-self-decls backstop: a final MISMATCH means a self-decl TU edit was NOT byte-neutral
        # (a transform bug — harvest_verify always reverts a wrong DRAFT, so a wrong draft leaves the binary
        # byte-identical, just unbanked). Restore this group's edited TU from the phase-1 snapshot + rebuild
        # so byte-identity is recovered; count the members failed. The whole-binary gate stays the arbiter.
        if "MISMATCH" in (r.stdout or "") and src_rel in tu_snapshots:
            open(os.path.join(REPO, src_rel), "w").write(tu_snapshots[src_rel])
            sh(["make", "build", f"BINARY={ov}"], timeout=1200)
            print(f"  {ov} [{os.path.basename(src_rel)}]: ⚠ self-decl edit NON-NEUTRAL — reverted TU, 0/{len(fns)} banked")
            failed[ov] += len(fns)
            continue
        vpath = os.path.join(REPO, vout)
        nver = len([x for x in open(vpath).read().split() if x]) if os.path.exists(vpath) else 0
        # ZERO-BANK HYGIENE (Phase 29 SESSION-21): if the group banked NOTHING, restore the
        # self-decl TU edit even though it was byte-NEUTRAL. The MISMATCH backstop above only fires
        # on a non-neutral edit, so a 0-bank run left every edit in the tree: SESSION-20's
        # `--normalize-self-decls 0/123` run left 123 files / 246 insertions / 246 deletions of dead
        # diff that a `git add -A` would have committed as noise. Byte-safe is not the test —
        # §61's undo law says an edit that bought nothing gets undone. Nothing banked here, so
        # there is no splice to preserve and the restore cannot cost a match. No rebuild is needed:
        # the edit was byte-neutral by construction (had it not been, the branch above already ran).
        if nver == 0 and src_rel in tu_snapshots:
            open(os.path.join(REPO, src_rel), "w").write(tu_snapshots[src_rel])
            print(f"  {ov} [{os.path.basename(src_rel)}]: 0 banked — reverted the byte-neutral "
                  f"self-decl edit (no dead diff left behind)")
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
    ap.add_argument("-j", "--jobs", type=int, default=12,
                    help="gate groups across DISTINCT binaries in parallel (1 = serial). "
                         "The per-overlay lock keeps two splits of one overlay serialised.")
    ap.add_argument("--commit", action="store_true")
    ap.add_argument("--only", default=None, help="comma-separated exemplar addrs to sweep (validation)")
    ap.add_argument("--allow-pins", action="store_true",
                    help="DEPRECATED / no-op — pinned exemplars are swept BY DEFAULT since SESSION-22 "
                         "(the §42e cc1 crash was our own extract_unit macro-drop, fixed in Phase 27). "
                         "Accepted so existing recipes and docs keep working.")
    ap.add_argument("--no-pins", action="store_true",
                    help="restore the old §42e behaviour: SKIP any exemplar carrying a register pin. "
                         "Measured cost of that skip on one family: 137 skipped, 133 of which bank.")
    ap.add_argument("--allow-jr", action="store_true",
                    help="§53 escape hatch: sweep has_mid_jr families through this carve-less path anyway "
                         "(they normally need tools/jtbl_family_bank.py). The whole-binary byte-gate stays "
                         "the sole arbiter, but expect ~0%% — and do NOT read that 0%% as a wall.")
    ap.add_argument("--fix-def-sig", action="store_true",
                    help="A REPAIR, NOT A DEFAULT (§119, T84 — do not pass it routinely). Rewrites each member "
                         "draft's DEF signature to the shared-header (engine_core.h) canonical decl, so a member "
                         "forward-declared there with a DIFFERENT sig (e.g. s32* vs void*) stops throwing "
                         "`conflicting types`. It is a repair for drafts whose def contradicts a CORRECT header, "
                         "and a BREAKER for drafts whose def is right and the header is wrong: on 0x80161c98 it "
                         "imposed a signedness-wrong `s32 a1` over the true `u32`, turning a byte-correct draft "
                         "into a 1-instruction DIFF (slti vs sltiu) and holding 137 members at 0 until the flag "
                         "was DROPPED. Use only after a member fails on a def-vs-header conflict you have read.")
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
    ap.add_argument("--no-cast-callees", action="store_true",
                    help="--hseq: DISABLE the §17a-1 callee-conflict cast (Phase-29 T77). ON by "
                         "default: it only fires when a callee's canonical TU signature conflicts "
                         "with the draft's, it is codegen-neutral (gcc folds the cast of a known "
                         "symbol to a direct jal), and the whole-binary gate arbitrates. Use this "
                         "flag to A/B it.")
    ap.add_argument("--no-tu-scope", action="store_true",
                    help="--hseq: DISABLE the §103 tu-scope pre-pass (Phase-29 T56). It is ON by "
                         "default because it is byte-neutral by construction (a declaration move), "
                         "a no-op when nothing collides, and auto-reverted by the same two backstops "
                         "as --normalize-self-decls if it is not neutral or the group banks nothing. "
                         "It moves the SIBLING TU's own file-scope decl of a contested D_ symbol into "
                         "its consumers, so scope_data_fix stops dropping the draft's byte-true decl "
                         "and letting the TU's type govern the body. Use this flag to A/B it.")
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

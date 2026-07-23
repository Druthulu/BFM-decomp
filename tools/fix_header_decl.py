#!/usr/bin/env python3
"""fix_header_decl.py — reconcile shared-header forward-decls to a fn's BYTE-TRUE signature.

THE FRESH-138 DEF-SIDE BLOCKER (Phase-29 SESSION-13, cookbook §63). A shared caller macro in
`src/shared/engine_core.h` forward-declares an engine fn with a SIMPLIFIED, caller-derived signature
(`extern void func_X(s32 a0, void *a1, void *a2);`) that conflicts with the fn's BYTE-TRUE definition
(`int func_X(s32, u16*, u16*)`). When a wave drafts that fn, splicing its true def into an overlay TU
that `#include`s the header throws `conflicting types for func_X` (cc1 exit 33) — so the fn can NEVER
bank, even with a byte-perfect body. `gate_stage`'s arity pre-pass is param-COUNT-only (misses return
type + pointer element type); §54 `reconcile_def_sig` fixes the DRAFT to the header (wrong direction —
the header is the simplified one). This tool fixes the HEADER to the byte-true def.

PROVEN (func_8014CD80, SESSION-13): one byte-neutral header edit -> harvest_verify banks x1
BYTE-IDENTICAL -> `dedup_propagate --addr` fills 138/138 overlays byte-identical -> R22 140/140.

BYTE-NEUTRALITY (why rewriting the decl cannot change any shipped byte):
  - return void <-> intN: the true fn always sets $v0; a caller that declared it `void` simply never
    read $v0 (unchanged), and no current caller USES the return (it was declared void). Widening the
    decl to the true return is a pure type-check change.
  - pointer element type void* <-> T*: pointers are register-passed regardless of element type.
  REFUSED (would change the ABI, left to a human / permuter): a param-COUNT change, or a param that
  flips pointer<->scalar, or a scalar-CLASS change (int<->float — different register file).
The whole-binary byte-gate (harvest_verify / dedup_propagate / R22) is the FINAL arbiter regardless;
this tool only rewrites the decl, and never trusts its own byte-neutrality judgement.

FLEET-SHARED SAFETY (§61): editing engine_core.h touches all 138 overlays. --apply snapshots every
touched file first and prints the exact `git checkout` restore; the undo is ALWAYS a restore, never an
inverse transform, and correctness is validated FLEET-WIDE by R22, never by the per-binary gate that
authorised the bank (the SESSION-12 incident).

USAGE
  # dry-run: show the rewrite the tool would make
  fix_header_decl.py --fn func_8014CD80 --draft .run/drafts-X/func_8014CD80.c --check
  # apply the header rewrite (snapshots first), then bank+propagate yourself:
  fix_header_decl.py --fn func_8014D12C --draft .run/drafts-X/func_8014D12C.c --apply
  #   -> python tools/harvest_verify.py --binary <ov> --drafts <draftdir>
  #   -> python tools/dedup_propagate.py --addr 0x<addr> --recover
  #   -> make clean && make extract-all && make check-all   (R22, MANDATORY — fleet-shared edit)
"""
import argparse, os, re, sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HEADERS = ["src/shared/engine_core.h", "src/shared/engine_types.h"]

# canonical project spellings (byte-identical typedefs; used for the rewritten decl's style)
CANON = {
    "int": "s32", "unsigned int": "u32", "unsigned": "u32",
    "short": "s16", "unsigned short": "u16",
    "char": "s8", "unsigned char": "u8", "signed char": "s8",
    "long": "s32", "unsigned long": "u32",
}
INT_CLASS = {"s8", "u8", "s16", "u16", "s32", "u32", "int", "unsigned", "short", "long", "char",
             "unsigned int", "unsigned short", "unsigned char", "signed char", "unsigned long"}


def canon_base(base):
    base = " ".join(base.split())
    return CANON.get(base, base)


def parse_param(p):
    """'unsigned short *param_2' -> (base='unsigned short', is_ptr=True, name='param_2')."""
    p = " ".join(p.replace("*", " * ").split())
    if p in ("", "void"):
        return None
    is_ptr = "*" in p
    toks = [t for t in p.split() if t != "*"]
    TYPEWORDS = {"unsigned", "signed", "short", "long", "int", "char", "void", "float", "double",
                 "u8", "u16", "u32", "s8", "s16", "s32", "f32", "const", "struct", "void"}
    name = ""
    if toks and toks[-1] not in TYPEWORDS:
        name = toks[-1]
        toks = toks[:-1]
    return " ".join(toks), is_ptr, name


def parse_sig(sig_body):
    """sig_body = the text between ( and ). Returns list of (base, is_ptr, name)."""
    sig_body = sig_body.strip()
    if sig_body in ("", "void"):
        return []
    return [parse_param(p) for p in sig_body.split(",")]


def byte_true_sig(draft_path, fn):
    """Parse the fn's DEFINITION (has a { body) from the draft. Returns (ret, [params])."""
    text = open(draft_path).read()
    m = re.search(rf"(?:^|\n)[ \t]*([A-Za-z_][\w \t\*]*?)\b{re.escape(fn)}[ \t]*\(([^;{{]*?)\)[ \t\n]*\{{",
                  text)
    if not m:
        return None
    return m.group(1).strip(), parse_sig(m.group(2))


DECL_RE_T = r"(extern\s+)([A-Za-z_][\w \t\*]*?)\b{fn}[ \t]*\(([^;]*?)\)([ \t]*;)"


def find_decls(fn):
    """Return [(hdr_path, lineno, full_line, ret, [params])] for every forward-decl of fn."""
    out = []
    rx = re.compile(DECL_RE_T.format(fn=re.escape(fn)))
    for h in HEADERS:
        path = os.path.join(REPO, h)
        if not os.path.exists(path):
            continue
        for i, line in enumerate(open(path), 1):
            m = rx.search(line)
            if m:
                out.append((h, i, line, m.group(2).strip(), parse_sig(m.group(3)), m))
    return out


def compatible(true_ret, true_params, decl_ret, decl_params):
    """Byte-neutral iff same param count, ptr-ness matches per param, and scalar params stay in the
    integer class (no int<->float flip). Return (ok, reason)."""
    if len(true_params) != len(decl_params):
        return False, f"param COUNT differs (true {len(true_params)} vs decl {len(decl_params)}) — ABI change, REFUSED"
    for i, (tp, dp) in enumerate(zip(true_params, decl_params)):
        if tp is None or dp is None:
            return False, f"param {i} unpar4seable"
        tb, tptr, _ = tp
        db, dptr, _ = dp
        if tptr != dptr:
            return False, f"param {i} flips pointer<->scalar ({db}{'*' if dptr else ''} -> {tb}{'*' if tptr else ''}) — ABI change, REFUSED"
        if not tptr:  # scalar: both must be integer-class
            if canon_base(tb) not in INT_CLASS or canon_base(db) not in INT_CLASS:
                if canon_base(tb) != canon_base(db):
                    return False, f"param {i} scalar class change ({db} -> {tb}) — REFUSED"
    return True, "ok"


def canon_param_str(p):
    if p is None:
        return "void"
    base, is_ptr, _ = p
    return canon_base(base) + ("*" if is_ptr else "")


def canon_sig(ret, params):
    """Typedef-normalized (ret, param-string) — the C-type identity, so int==s32, unsigned short*==u16*.
    Two decls with the same canon_sig do NOT `conflicting types`; different ones DO."""
    r = "void" if ret.strip() == "void" else canon_base(ret)
    ps = ",".join(canon_param_str(p) for p in params) if params else "void"
    return r, ps


def build_decl(m, true_ret, true_params):
    """Return just the rewritten `extern <ret> func_X(...);` span (the caller splices it back into the
    line, preserving leading whitespace + any trailing macro `\\` continuation)."""
    extern = m.group(1)
    decl_params = parse_sig(m.group(3))
    ret = canon_base(true_ret) if true_ret.strip() != "void" else "void"
    parts = []
    for i, tp in enumerate(true_params):
        tb, tptr, _ = tp
        name = decl_params[i][2] if i < len(decl_params) and decl_params[i] and decl_params[i][2] else ""
        base = canon_base(tb) if tb else "void"
        parts.append((f"{base} *{name}" if tptr else f"{base} {name}").rstrip())
    inner = ", ".join(parts) if parts else "void"
    return f"{extern}{ret} func_{FN_ADDR}({inner});"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--fn", required=True, help="func_XXXXXXXX")
    ap.add_argument("--draft", required=True, help="draft .c holding the byte-true DEFINITION")
    ap.add_argument("--check", action="store_true", help="dry-run: show the rewrite, touch nothing")
    ap.add_argument("--apply", action="store_true", help="snapshot + rewrite the header decls")
    args = ap.parse_args()
    global FN_ADDR
    FN_ADDR = args.fn.replace("func_", "")

    os.chdir(REPO)
    true = byte_true_sig(args.draft, args.fn)
    if not true:
        print(f"[fix_header_decl] FATAL: no byte-true DEFINITION of {args.fn} in {args.draft}", file=sys.stderr)
        return 2
    true_ret, true_params = true
    pstr = ", ".join(f"{b}{'*' if p else ''}" for (b, p, _) in true_params) or "void"
    print(f"byte-true def: {true_ret} {args.fn}({pstr})")

    decls = find_decls(args.fn)
    if not decls:
        print(f"[fix_header_decl] no shared-header forward-decl of {args.fn} — nothing to reconcile "
              f"(the blocker is elsewhere: callee/data/struct/DIFF).")
        return 1
    changes = []
    for h, ln, line, dret, dparams, m in decls:
        already = (canon_sig(true_ret, true_params) == canon_sig(dret, dparams))
        ok, why = compatible(true_ret, true_params, dret, dparams)
        # splice the rewritten decl span back into the line, preserving leading ws + trailing `\`
        new_line = line[:m.start()] + build_decl(m, true_ret, true_params) + line[m.end():]
        status = "ALREADY-OK" if already else ("SAFE" if ok else "REFUSE")
        print(f"  {h}:{ln}  [{status}]")
        print(f"    - {line.rstrip()}")
        if already:
            continue
        if not ok:
            print(f"    ! {why}")
            continue
        print(f"    + {new_line.rstrip()}")
        changes.append((h, line, new_line))

    if not changes:
        print("no change needed (decls already byte-true, or all REFUSED).")
        return 0
    if args.check:
        print(f"[--check] {len(changes)} decl(s) WOULD be rewritten. Re-run with --apply.")
        return 0
    if not args.apply:
        print("pass --apply to write (or --check to dry-run).", file=sys.stderr)
        return 3

    # §61: snapshot every touched header before writing; undo is a RESTORE (git checkout), never inverse.
    touched = sorted({h for h, _, _ in changes})
    for h in touched:
        path = os.path.join(REPO, h)
        text = open(path).read()
        for _, old, new in [c for c in changes if c[0] == h]:
            assert text.count(old) >= 1, f"decl line vanished in {h}"
            text = text.replace(old, new, 1)
        open(path, "w").write(text)
    print(f"[--apply] rewrote {len(changes)} decl(s) in {len(touched)} header(s).")
    print(f"  UNDO (if the bank fails / R22 is not 140/140): git checkout -- {' '.join(touched)}")
    print(f"  NEXT: harvest_verify --binary <ov> --drafts <dir> ; dedup_propagate --addr 0x{FN_ADDR.lower()} --recover ; R22 (make clean && extract-all && check-all)")
    return 0


if __name__ == "__main__":
    sys.exit(main())

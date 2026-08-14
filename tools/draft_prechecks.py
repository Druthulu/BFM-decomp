"""Static pre-checks that turn a BUILD-time draft failure into a GENERATION-time skip.

Every class here was measured as a real failure in the S50 autodraft runs, and every one is
decidable without compiling anything. That is the whole point: a build spent to learn something a
regex knows is a build wasted, and at ~1 min/group over ~100 groups the waste is the run.

  1. ARITY DISAGREEMENT — `too few arguments to function 'func_80146C3C'`.
     The destination TU already declares a callee with a different parameter count than the seed's
     body passes. Neither emitting the seed's decl (conflicting types) nor relying on the
     destination's (too few arguments) can work; the member needs a real edit.

  2. UNDEFINED DATA — `undefined reference to 'D_801E9C44'`.
     The draft references a symbol nothing in the DESTINATION binary defines. The seed's own data
     symbol survived into the draft because it sits at no relocation slot symbol_map covers.
"""
import glob
import os
import re


def _decl_arity(text, sym):
    """Parameter count of the first declaration/definition of `sym` in `text`, or None."""
    m = re.search(rf'^[ \t]*(?:extern\s+)?[A-Za-z_][\w \*]*\b{re.escape(sym)}\s*\(([^;{{)]*)\)',
                  text, re.M)
    if not m:
        return None
    args = m.group(1).strip()
    if args == '':
        return None      # C89: `f()` declares UNSPECIFIED parameters, not zero — never a conflict
    if args == 'void':
        return 0
    return len([a for a in args.split(',') if a.strip()])


def _call_arity(body, sym):
    """Argument count at the first CALL of `sym` in `body`, or None. Depth-aware so a nested call
    or a comma inside a cast does not miscount."""
    m = re.search(rf'\b{re.escape(sym)}\s*\(', body)
    if not m:
        return None
    depth, args, cur = 0, [], ''
    for ch in body[m.end() - 1:]:
        if ch == '(':
            depth += 1
            if depth == 1:
                continue
        elif ch == ')':
            depth -= 1
            if depth == 0:
                args.append(cur)
                break
        if depth == 1 and ch == ',':
            args.append(cur)
            cur = ''
            continue
        if depth >= 1:
            cur += ch
    return len([a for a in args if a.strip()])


def arity_conflicts(body, dest_text, syms, self_name=None):
    """Symbols the body CALLS with an argument count the destination's own declaration refuses."""
    bad = []
    for s in syms:
        if not s.startswith('func_') or (self_name and s.lower() == self_name.lower()):
            continue   # the member's own definition is not a call to itself
        d, c = _decl_arity(dest_text, s), _call_arity(body, s)
        # CONSERVATIVE by measurement: flag only when the destination declares NAMED parameters and
        # the body passes fewer. Every true positive had that shape (`dest decl 1 vs call 0`) and
        # every false positive the other one (`dest decl 0 vs call 1`) — where the `0` comes from a
        # `(void)` my parser reads out of a declaration it should not have matched. A pre-check that
        # throws away good drafts is worse than one that lets a few builds fail.
        if d is not None and c is not None and d > c:
            bad.append(f"{s}(dest decl {d} vs call {c})")
    return bad


_DEF_CACHE = {}


def defined_in_binary(binary, sym):
    """True if `sym` is defined anywhere in the destination binary — its asm (a dlabel/glabel, or
    a symbol file entry) or its C. Cached per binary: the asm scan is the expensive part."""
    key = binary
    if key not in _DEF_CACHE:
        defs = set()
        for p in glob.glob(f"asm/{binary}/**/*.s", recursive=True):
            for m in re.finditer(r'^(?:dlabel|glabel|jlabel)\s+([A-Za-z_]\w*)', open(p).read(), re.M):
                defs.add(m.group(1))
        for p in glob.glob(f"config/symbols.{binary}*.txt"):
            for m in re.finditer(r'^([A-Za-z_]\w*)\s*=', open(p).read(), re.M):
                defs.add(m.group(1))
        _DEF_CACHE[key] = defs
    return sym in _DEF_CACHE[key]


def undefined_data(binary, dest_text, syms, self_name=None, body=""):
    """Referenced symbols nothing in the destination binary defines, and the destination TU does
    not define locally either.

    A symbol the DRAFT ITSELF defines is not undefined — its own function name above all, which
    has no `glabel` left in asm precisely BECAUSE it is now C. Skipping that was 38 of 38 false
    positives in the negative control."""
    out = []
    for s in syms:
        if self_name and s.lower() == self_name.lower():
            continue
        if re.search(rf'^[^\n=;]*\b{re.escape(s)}\b[^\n;]*\)\s*\{{', body, re.M) or \
           re.search(rf'^[ \t]*(?:const\s+|static\s+)*[A-Za-z_][\w \*]*\b{re.escape(s)}\b'
                     rf'(?:\s*\[[^\]]*\])?\s*=', body, re.M):
            continue
        if defined_in_binary(binary, s):
            continue
        if re.search(rf'^[ \t]*(?:const\s+|static\s+)*[A-Za-z_][\w \*]*\b{re.escape(s)}\b[^\n;]*[=;]',
                     dest_text, re.M):
            continue
        out.append(s)
    return out

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


def is_verbatim_asm_draft(text, fn):
    """True if `text` is the target's own assembly, not a decompile of it (P31 S76).

    THE DEFECT THIS CATCHES, and why no byte gate can. `tools/asm_verbatim.py` emits a §265
    verbatim body -- the function's own .s pasted into a file-scope `__asm__` string. Those files
    sit in the same draft directories as real C drafts and are named `<fn>.c` like everything else.
    Score one with match_one and it prints MATCH, truthfully: a raw asm blob assembles to the bytes
    it was copied from. Substitute one and the whole-binary gate goes GREEN, also truthfully. The
    function is then reported BANKED while nothing whatsoever has been decompiled.

    S75 hit this once (an agent submitted the verbatim block as its own "decompile"; only an
    adversarial reader caught it) and recorded "No byte gate can" catch it. That is true of the
    BYTE check and false of a slate-load refusal, which is why this lives here: the verbatim form
    is trivially decidable from the text (R43 -- refuse the input, never mishandle it).

    S76 hit it again, from the other direction and at scale: nine functions were converted from
    verbatim bodies to stubs precisely so they could be decompiled, then "banked" from stored
    drafts that were the same verbatim blocks -- a round trip through the gate that moved
    progress.py by exactly zero and read as 9 of 9 MATCH. The instrument was right and the claim
    was wrong.

    A draft is verbatim iff a file-scope `__asm__` names this function as a .ent/.globl/label AND
    no C definition of it exists. Both halves matter: a real draft may legitimately carry a small
    inline `__asm__`, and a verbatim body may omit .globl for a static."""
    if '__asm__' not in text:
        return False
    f = re.escape(fn)
    # The escaped forms are what the emitters write INTO a C string: `.ent\tfoo\n` is backslash-t,
    # not a tab. Match both the escaped and the literal spellings -- five S76 censuses of this
    # class disagreed with each other until both were handled.
    asm_names = re.search(rf'\.(?:ent|globl)(?:\\t|[ \t])+{f}\b', text) or \
        re.search(rf'"\s*{f}:\s*(?:\\n|$)', text)
    if not asm_names:
        return False
    c_def = re.search(rf'^[A-Za-z_][\w \*]*\b{f}\s*\([^;]*\)\s*(?:/\*.*?\*/\s*)?\{{', text, re.M | re.S)
    return not c_def


def is_epilogueless_fragment(asm_path=None, asm_text=None):
    """True if this function has NO `jr $ra` of its own — cookbook §179-C (P31 S76).

    THE CLASS. A §179-C function ends mid-basic-block, or every exit is a raw `j` into a SIBLING's
    label, and the shared `lw $ra / addiu $sp / jr $ra` tail lives in the next symbol. gcc-2.7.2 has
    no sibcall/cross-function tail-merge pass and `expand_function_end` appends an epilogue to every
    C function it compiles, so NO C spelling exists: every attempt comes out +2 instructions
    (a phantom `jr $ra` / `nop`). The only correct form is a file-scope `__asm__`.

    WHY IT IS A PRECHECK AND NOT A LESSON (S76). The manifest already marks these DECOMPILE-AS-PARENT
    ("this row is a FRAGMENT — decompile the unit_entry, NEVER the fragment") and the cookbook §179-C
    entry NAMES several of them. I converted six of them to INCLUDE_ASM stubs anyway, on a `rows == 1`
    filter that meant "the manifest listed one row", not "this is an independent function" — putting
    six unbankable targets into the drawable frontier. Three separate drafting agents then rediscovered
    §179-C from scratch, one of them citing the very cookbook line that names its target.

    The symptom is one grep over the target's own `.s`, so no one should ever pay an agent to find it
    again: a function with no `jr $ra` is not drawable and not convertible, whatever any disposition
    field says. Verified on the S76 set: 6 of 6 main `src/800c.c` conversions flagged, 5 of 5 overlay
    conversions cleared.

    READ THE RIGHT SOURCE. Pass `asm_text` when the function is still a VERBATIM body: splat stops
    emitting `<fn>.s` for a function that is not a stub, so a path-only check has nothing to read and
    returns False — inert for exactly the case it exists to prevent. Measured S76: the first version
    of this guard passed a §179-C fragment straight through for that reason, caught only by testing
    it on a case whose answer was already known. The verbatim block IS the assembly; use it."""
    if asm_text is None:
        try:
            with open(asm_path, errors='replace') as fh:
                asm_text = fh.read()
        except (OSError, TypeError):
            return False      # cannot read -> not our call to make; the caller's oracle decides
    return not any('jr' in ln and '$ra' in ln for ln in asm_text.splitlines())

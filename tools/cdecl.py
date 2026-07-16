#!/usr/bin/env python3
"""tools/cdecl.py — THE C-declaration oracle. One parser; fifteen deleted models.

WHY THIS EXISTS  (Phase 26-A tooling audit; R33 before R32)
===========================================================
Fifteen tools in this repo carry their own regex model of what a C declaration is. They disagree.
Two tools in ONE pipeline (reconcile_decls and canon_sig_reconcile) already disagree about whether
`extern s32 D_a, D_b;` is a declaration at all. The audit measured the cost of that:

    * 6,384 of the fleet's 39,440 data symbols get NO canonical decl, ever.
    * 3,717 symbols get an ACTIVELY WRONG one — a fleet plurality vote won by a minority spelling,
      because every correctly-shaped decl was invisible to the regex that counted the votes.
    * One unparsed `[4]` (engine_core.h:2114, `extern s32 D_80127530[4];`) has been single-handedly
      blocking func_801387B8 — still INCLUDE_ASM in 134 TUs.

THE ROOT CAUSE IS ONE CHARACTER CLASS, COPIED FIFTEEN TIMES:

    extern\\s+([A-Za-z_][\\w\\s\\*]*?\\bD_[0-9A-Fa-f]+\\s*(?:\\[\\s*\\])?)\\s*;
                          ^^^^^^^^^                            ^^^^^^^^
                          cannot hold '(' or ','               EMPTY brackets only

so three whole declarator shapes are invisible to every one of them:

    extern void (*D_8018E858[])(void);   <- a jump table.   the '(' is not in [\\w\\s\\*]
    extern s32  D_80127530[4];           <- a sized array.  the '4' is not in \\[\\s*\\]
    extern s32  D_a, D_b, D_c;           <- 3 symbols.      the ',' is not in [\\w\\s\\*]
                                            (the WHOLE line is dropped, not just declarator 2..N)

Patching fifteen regexes is fifteen chances to diverge again. C's declarator grammar, by contrast,
is small, closed, and TOTAL — it describes those three shapes and every other one without being
told about them. So this module parses the grammar, and the fifteen models get deleted.

    R33: the best outcome is a DELETED SCANNER, not a fixed regex.

WHAT IT DERIVES FROM, AND WHY THERE ARE TWO STATEMENT PATHS
===========================================================
1. A TU's file scope is decided by cpp, NOT by reading the .c.
   `src/shared/engine_core.h` is 23,546 backslash-continued lines inside 1,801 `#define
   DEFINE_func_*` macro bodies. A declaration in a macro BODY is not a declaration of anything —
   it becomes one only where the macro is INVOKED, above the invocation point (the §8c law that
   cost sessions 5 and 6). So a raw text scan of a TU is wrong in both directions: skip the
   `#define`s and you miss all 1,801; read them and you invent ambient decls the TU never had.
   `cpp` answers the question exactly, in 54 ms on the largest TU. That is why
   `canon_sig_reconcile._file_scope_statements` is the ONE scanner the audit measured CLEAN, and
   why `reconcile_tu._macro_externs()` — a hand-rolled model of macro expansion, `.rstrip('\\\\')`
   and all — is a defect waiting to be deleted.  ->  `tu_statements()`

2. A DRAFT is rewritten in place, so it needs SPANS, and it has no macro bodies.
   ->  `split_statements()`, span-preserving, comment/string-masked, brace-depth-aware.

Both feed ONE parser.

THE COVERAGE ASSERTION IS ITSELF DERIVED (R32, and R33 applied to R32)
=====================================================================
Every other tool here hand-maintains an over-approximating candidate regex to measure its own
coverage. It does not need one. **At file scope, C admits nothing but declarations** — there are no
executable statements at depth 0. So the candidate set is *every depth-0 statement*, taken from the
C grammar itself, and the assertion is the strongest one available:

    a depth-0 statement this parser cannot read is a DEFECT, not a shrug.

The only exclusions are NAMED and explicit (unexpanded macro invocations in raw draft text) — never
"whatever the regex happened not to match", which is the failure mode that wrote the fifteen bugs.

A SECOND ORACLE THAT CAN DISAGREE WITH ME (R34)
===============================================
A parser I merely believe is correct is worth exactly nothing — the audit exists because six people
believed their regexes were correct. So `--audit` hands every distinct declaration SHAPE in the
corpus to the real cross-gcc as

    <the original declaration>
    <this parser's reconstruction of it>

in one TU. If the parse got the type wrong in any way, gcc says `conflicting types` and names me.
That is not a self-check: it is the same C front end that arbitrates the build, and it cannot be
fooled by a plausible-looking regex.

Usage:
    from cdecl import parse, scope, tu_statements, split_statements
    tools/cdecl.py --audit [--gcc] [--limit N]     # coverage + gcc + differential oracles
    tools/cdecl.py --tu src/ov_SC01_077/ov_SC01_077.c [--above func_8012ACE0]
    tools/cdecl.py --parse 'extern void (*D_8018E858[])(void);'
"""
import argparse
import functools
import glob as _glob
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# The build's own preprocessor, with the build's own flags (docs/SETUP.md §5.4). Deriving the TU's
# file scope from anything else would be re-deriving what the build already guarantees.
CPP = ['mipsel-linux-gnu-cpp', '-lang-c', '-Iinclude', '-undef', '-Wall', '-fno-builtin',
       '-Dmips', '-D__GNUC__=2', '-D__OPTIMIZE__', '-Dpsx', '-D_PSYQ', '-D_MIPSEL', '-D_LANGUAGE_C']
CC = 'mipsel-linux-gnu-gcc'

STORAGE = {'extern', 'static', 'register', 'auto', 'typedef', 'inline'}
QUALS = {'const', 'volatile'}
TYPEKW = {'void', 'char', 'short', 'int', 'long', 'float', 'double', 'signed', 'unsigned', '_Bool'}
TAGKW = {'struct', 'union', 'enum'}
GNU = {'__asm__', 'asm', '__attribute__', '__extension__', '__inline__'}

# Macro invocations that are NOT declarations in RAW draft/source text (they become declarations
# only after cpp). An EXPLICIT, NAMED exclusion list — the audit's rule: never let the exclusion set
# be "whatever the parser happened to choke on".
MACRO_STMT = re.compile(r'^\s*(INCLUDE_ASM|DEFINE_func_[0-9A-Fa-f]+|SETTER|RETCONST|CLEAR_TBL40)\b')


class CDeclError(Exception):
    """A declaration this parser could not fully read. ALWAYS raised, never swallowed."""


# ---------------------------------------------------------------------------------------------
# lexing
# ---------------------------------------------------------------------------------------------
_TOKEN = re.compile(r"""
      (?P<ws>\s+)
    | (?P<id>[A-Za-z_]\w*)
    | (?P<num>\.?\d[\w.]*(?:[eEpP][+-]\w*)?)
    | (?P<str>"(?:\\.|[^"\\])*")
    | (?P<chr>'(?:\\.|[^'\\])*')
    | (?P<punct>\.\.\.|[-+*/%&|^!~<>=]=|<<=?|>>=?|&&|\|\||[][(){}.,;:*&+\-/%!~<>=?|^])
    | (?P<other>.)
""", re.X)


class Tok:
    __slots__ = ('kind', 'text', 'pos')

    def __init__(self, kind, text, pos):
        self.kind, self.text, self.pos = kind, text, pos

    def __repr__(self):
        return f'{self.kind}:{self.text!r}'


def tokenize(text):
    """-> [Tok] with source offsets. Comments are assumed already masked (see _mask).

    The `other` catch-all means the lexer can NEVER die on an unexpected character (a `#directive`
    inside a function body, say — bodies are consumed verbatim and never parsed). A surprising
    character therefore becomes a token the PARSER rejects in context, naming the statement, rather
    than a lexer crash naming a byte offset."""
    out, i, n = [], 0, len(text)
    while i < n:
        m = _TOKEN.match(text, i)
        i = m.end()
        if m.lastgroup == 'ws':
            continue
        out.append(Tok(m.lastgroup, m.group(), m.start()))
    return out


def _mask(text):
    """Length-preserving blank-out of comments and string/char literals, so brace/paren counting
    and token scans cannot be fooled by a '}' in a comment or a '"' in a string. Offsets into the
    mask are valid offsets into the original — that is what makes span-preserving rewrites safe."""
    def blank(m):
        return re.sub(r'[^\n]', ' ', m.group(0))
    text = re.sub(r'/\*.*?\*/', blank, text, flags=re.S)
    text = re.sub(r'//[^\n]*', blank, text)
    text = re.sub(r'"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', blank, text)
    return text


# ---------------------------------------------------------------------------------------------
# statements — two paths, because the two inputs are semantically different
# ---------------------------------------------------------------------------------------------
class Stmt:
    """A depth-0 statement. `start`/`end` index the ORIGINAL text (spans survive masking)."""
    __slots__ = ('text', 'start', 'end')

    def __init__(self, text, start, end):
        self.text, self.start, self.end = text, start, end

    def __repr__(self):
        return f'Stmt({self.text[:60]!r} @{self.start}:{self.end})'


def _depth0_spans(text):
    """Spans of every brace-depth-0 statement. A function DEFINITION flushes at its closing '}'
    (the '{' followed a ')' — ANSI — or a ';' — a K&R declaration-list); everything else flushes at
    its ';'. Preprocessor lines are skipped.

    A col-0 LINE test is not a file-scope test, and this is why: m2c emits goto labels
    (`done:`, `block_13:`) at column 0 INSIDE function bodies. Every tool that equates "starts at
    column 0" with "is at file scope" is relying on a heuristic the corpus violates.
    """
    m = _mask(text)
    spans, depth, start, last = [], 0, None, ''
    i, n = 0, len(m)
    while i < n:
        ch = m[i]
        if ch == '#' and (i == 0 or m.rfind('\n', 0, i) == i - 1 - (len(m[:i]) - len(m[:i].rstrip(' \t')))):
            pass  # fall through; handled by the line skip below
        if depth == 0 and start is None and not ch.isspace():
            # skip a whole preprocessor line
            line_start = m.rfind('\n', 0, i) + 1
            if m[line_start:i].strip() == '' and ch == '#':
                i = m.find('\n', i)
                if i < 0:
                    break
                continue
            start = i
        if ch == '{':
            if depth == 0:
                # What precedes this brace decides what it is. Scan back over ALL preceding text,
                # not just the current statement — because a K&R definition
                #     s32 f(arg0) s32 arg0; { ... }
                # already flushed at the declaration-list's ';', leaving the body orphaned. (That
                # is the same K&R shape that made progress.py read 670 banked definitions as
                # forward declarations and count them as nothing.)
                back = next((c for c in reversed(m[:i]) if not c.isspace()), '')
                kr_body = start == i and spans and back == ';'   # (start was set to i just above)
                in_body = kr_body or (start != i and back in (')', ';'))
                if not in_body:
                    depth += 1                     # a struct body or an initializer: keep reading
                    i += 1
                    continue
                d, i = 1, i + 1                    # consume the body to its matching close
                while i < n and d:
                    if m[i] == '{':
                        d += 1
                    elif m[i] == '}':
                        d -= 1
                    i += 1
                if kr_body:
                    # A K&R declaration-list is a SEQUENCE of ';'-terminated declarations, so the
                    # prologue may have flushed as SEVERAL spans:
                    #     void f(a0, arr)  s32 a0;   |   s32 *arr;   |   { body }
                    # Merge backwards until the merged text parses to a FUNCTION declarator — the
                    # grammar's own answer to "where does this definition begin". Getting this
                    # wrong does not just misplace the body: it leaks the K&R parameter names
                    # (a0, arr) into the file-scope namespace as if they were globals.
                    j = len(spans) - 1
                    while j >= 0 and len(spans) - j <= 12:
                        try:
                            ds = parse(m[spans[j][0]:spans[-1][1]])
                            if ds and ds[0].kind == 'func':
                                break
                        except CDeclError:
                            pass
                        j -= 1
                    j = max(j, 0)
                    spans[j:] = [(spans[j][0], i)]
                else:
                    spans.append((start, i))
                start = None
                continue
            depth += 1
        elif ch == '}':
            depth -= 1
            if depth < 0:
                depth = 0
        elif ch == ';' and depth == 0:
            spans.append((start, i + 1))
            start = None
        i += 1
    if start is not None and m[start:].strip():
        spans.append((start, n))
    return spans


def split_statements(text):
    """RAW, span-preserving depth-0 split. For DRAFTS (which get rewritten, so spans are mandatory,
    and which contain no #define macro bodies)."""
    return [Stmt(text[a:b], a, b) for a, b in _depth0_spans(text)]


_TU_CACHE = {}


def tu_statements(tu_path, above=None):
    """The file-scope statements the COMPILER sees in `tu_path` — cpp-derived (the §8c law).

    `above`: a function name; truncate the TU at that function's INCLUDE_ASM stub, so the result is
    exactly what is in scope at the splice point (declarations BELOW it are not visible to a body
    spliced in above them).

    This is the derived oracle that replaces reconcile_tu._macro_externs()+tu_visible() (a
    hand-rolled model of what cpp does) and canon_sig_reconcile._file_scope_statements (correct, but
    a second copy).
    """
    key = (os.path.abspath(tu_path), above)
    if key in _TU_CACHE:
        return _TU_CACHE[key]

    src = tu_path
    tmp = None
    if above:
        text = open(tu_path).read()
        m = re.search(r'^INCLUDE_ASM\("[^"]*",\s*' + re.escape(above) + r'\);\s*$', text, re.M)
        if m:
            # The temp MUST live beside the TU: cpp resolves #include "..." relative to the
            # including file's own directory. Dot-prefixed so no src glob can ever see it.
            tmp = os.path.join(os.path.dirname(tu_path), f'.cdecl_{above}.c')
            open(tmp, 'w').write(text[:m.start()])
            src = tmp
    try:
        p = subprocess.run(CPP + [src], capture_output=True, text=True, cwd=REPO)
        if p.returncode:
            raise CDeclError(f'cpp failed on {tu_path}: {p.stderr[-300:]}')
        out = [s.text for s in split_statements(
            '\n'.join(l for l in p.stdout.split('\n') if not l.startswith('#')))]
    finally:
        if tmp and os.path.exists(tmp):
            os.remove(tmp)
    _TU_CACHE[key] = out
    return out


# ---------------------------------------------------------------------------------------------
# the parser — C's declarator grammar, which is total over the shapes fifteen regexes enumerate
# ---------------------------------------------------------------------------------------------
PTR, ARR, FUN = 'PTR', 'ARR', 'FUN'


class Declarator:
    """One declared name, with its type read the way C reads it: OUTWARD from the name.

    `chain` is the derivation list, name-first — exactly the C rule that regexes cannot express:
        void (*D_x[])(void)   ->  chain [ARR, PTR, FUN]   "D_x is an ARRAY of POINTERs to
                                                            FUNCTIONs returning void"
        s32 D_x[4]            ->  chain [ARR(4)]
        void func_X(s32)      ->  chain [FUN]
        u8 *D_x               ->  chain [PTR]
    """
    __slots__ = ('name', 'chain', 'base', 'storage', 'quals', 'params', 'pnames', 'is_proto',
                 'is_definition', 'text', 'span', '_fun')

    def __init__(self, name, chain, base, storage, quals):
        self.name, self.chain, self.base = name, chain, base
        self.storage, self.quals = storage, quals
        self.params, self.pnames, self.is_proto, self.is_definition = None, None, None, False
        self.text, self.span, self._fun = None, None, None
        for op in chain:
            if op[0] == FUN:
                self._fun = op
                self.params, self.pnames = op[1], op[2]
                self.is_proto = not op[4]          # provisional; parse() resolves the K&R ambiguity
                break

    # -- the four questions every consumer in this repo actually asks -------------------------
    @property
    def kind(self):
        """'func' | 'fnptr' | 'fnptr_array' | 'array' | 'ptr' | 'scalar'. Derived from the chain,
        so a fn-ptr can never be mistaken for a scalar — the mistake that elected 3,717 wrong
        canonical decls."""
        ops = [o[0] for o in self.chain]
        if not ops:
            return 'scalar'
        if ops[0] == FUN:
            return 'func'
        if FUN in ops and PTR in ops:
            return 'fnptr_array' if ops[0] == ARR else 'fnptr'
        if ops[0] == ARR:
            return 'array'
        if ops[0] == PTR:
            return 'ptr'
        return 'scalar'

    @property
    def is_array(self):
        return self.chain and self.chain[0][0] == ARR

    @property
    def type(self):
        """The abstract type: the declaration with the name removed. 'void (*[])(void)', 's32 [4]',
        'u8 *'. This is what gcc compares, so this is what a canonical decl must preserve."""
        return _render(self.base, self.chain, '')

    def declaration(self, name=None, storage=None):
        """Reconstruct a valid C declaration. The gcc oracle (--audit --gcc) checks that this is
        the SAME declaration as the source it was parsed from."""
        st = self.storage if storage is None else storage
        core = _render(self.base, self.chain, self.name if name is None else name)
        return f'{st + " " if st else ""}{" ".join(self.quals) + " " if self.quals else ""}{core};'

    def __repr__(self):
        return f'Declarator({self.name}: {self.kind} = {self.type})'


def _ws(s):
    """Canonical spacing, so two declarations that MEAN the same thing RENDER the same. Consumers
    compare types by string, so the renderer must be deterministic — always parse both sides and
    compare renderings; never compare a rendering against raw source spacing."""
    s = re.sub(r'\s+', ' ', s).strip()
    return re.sub(r'(\w)\s*\(\s*\*', r'\1 (*', s)          # `void(*)(void)` -> `void (*)(void)`


def _render(base, chain, name):
    """Rebuild declarator text from the chain, applying C's inside-out rule: a suffix ([] or ())
    binds tighter than a prefix '*', so a '*' must be parenthesised whenever a suffix follows it."""
    s = name
    for i, op in enumerate(chain):
        nxt = chain[i + 1][0] if i + 1 < len(chain) else None
        if op[0] == PTR:
            s = '*' + s
            if nxt in (ARR, FUN):          # *x[] means "array of ptr"; (*x)[] means "ptr to array"
                s = '(' + s + ')'
        elif op[0] == ARR:
            s = f'{s}[{op[1] or ""}]'
        elif op[0] == FUN:
            params = ', '.join(op[1]) if op[1] else ('' if op[4] else 'void')
            s = f'{s}({params})'
    return _ws(f'{base} {s}'.strip() if s else base)


class _P:
    """Recursive-descent over the declarator grammar. Every failure raises."""

    def __init__(self, toks, src):
        self.t, self.i, self.src = toks, 0, src

    def peek(self, k=0):
        return self.t[self.i + k] if self.i + k < len(self.t) else Tok('eof', '', -1)

    def take(self):
        t = self.peek()
        if t.kind == 'eof':
            raise CDeclError(f'unexpected end of declaration: {self.src[:90]!r}')
        self.i += 1
        return t

    def expect(self, s):
        t = self.take()
        if t.text != s:
            raise CDeclError(f'expected {s!r}, got {t.text!r} in {self.src[:90]!r}')
        return t

    def skip_balanced(self, open_t='(', close_t=')'):
        self.expect(open_t)
        d, out = 1, []
        while d:
            t = self.take()
            if t.text == open_t:
                d += 1
            elif t.text == close_t:
                d -= 1
                if not d:
                    break
            out.append(t.text)
        return ' '.join(out)

    def skip_gnu(self):
        """__attribute__((...)) / __asm__("...") — GNU suffixes that decorate a declarator but
        declare nothing. 1,109 and 27,334 occurrences respectively; a parser that dies on them is
        useless here."""
        while self.peek().text in GNU:
            self.take()
            if self.peek().text == '(':
                self.skip_balanced()

    # -- decl-specifiers ---------------------------------------------------------------------
    def specifiers(self):
        storage, quals, base, have_type = None, [], [], False
        while True:
            t = self.peek()
            if t.text in STORAGE:
                storage = self.take().text
                continue
            if t.text in QUALS:
                quals.append(self.take().text)
                continue
            if t.text in TYPEKW:
                base.append(self.take().text)
                have_type = True
                continue
            if t.text in TAGKW:
                base.append(self.take().text)
                if self.peek().kind == 'id':
                    base.append(self.take().text)
                if self.peek().text == '{':
                    base.append('{' + self.skip_balanced('{', '}') + '}')
                have_type = True
                continue
            if t.text in GNU:
                self.skip_gnu()
                continue
            if t.kind == 'id' and not have_type:
                # A typedef-name, or the declared name of an implicit-int declaration?
                # Without a symbol table C itself cannot tell — so use the only local evidence:
                #   `M2C_UNK func_X(...)`   next is an ID       -> this ID is the TYPE
                #   `Ent *D_x`              next is '*'         -> this ID is the TYPE
                #   `s32 (*D_801274D0)(s32)` next is '(' + '*'  -> a GROUPED declarator follows,
                #                                                  so this ID is the TYPE
                #   `func_X(s32)`           next is '(' + type  -> a param list: implicit int,
                #                                                  so this ID is the NAME
                nxt, nxt2 = self.peek(1), self.peek(2)
                if nxt.kind == 'id' or nxt.text == '*' or \
                        (nxt.text == '(' and nxt2.text in ('*', '(')):
                    base.append(self.take().text)
                    have_type = True
                    continue
            break
        return storage, quals, ' '.join(base)

    # -- declarators -------------------------------------------------------------------------
    def suffixes(self):
        out = []
        while True:
            t = self.peek()
            if t.text == '[':
                self.take()
                dim = []
                d = 1
                while True:
                    t = self.take()
                    if t.text == '[':
                        d += 1
                    elif t.text == ']':
                        d -= 1
                        if not d:
                            break
                    dim.append(t.text)
                out.append((ARR, ' '.join(dim) or None))
                continue
            if t.text == '(':
                types, names, all_bare, empty = self.params()
                out.append((FUN, types, names, all_bare, empty))
                continue
            break
        return out

    def params(self):
        """-> (types, names, all_bare, empty).

        `empty` (`f()`) is the NO-PROTOTYPE form — gcc-2.7.2's K&R declaration, which accepts any
        argument list — as distinct from `f(void)`, a prototype taking nothing. That distinction is
        the entire subject matter of fix_arity_callers.py, which spends three regexes expressing
        what the grammar states in one production.

        `all_bare` (`f(a0, a1)` — every parameter a lone identifier) is AMBIGUOUS in C and cannot be
        resolved here: it is a K&R identifier-list in a DEFINITION, but a prototype with typedef'd
        parameter types in a DECLARATION (`M2C_UNK f(s32, s32);` — `s32` is a typedef, not a
        keyword, so it is lexically identical to a K&R parameter name). The caller resolves it with
        the one piece of evidence that settles it: whether a body follows.
        """
        self.expect('(')
        if self.peek().text == ')':
            self.take()
            return [], [], False, True                        # f()  — no prototype
        if self.peek().text == 'void' and self.peek(1).text == ')':
            self.take(), self.take()
            return [], [], False, False                       # f(void) — a prototype, no params
        parts, cur, d = [], [], 0
        while True:
            t = self.take()
            if t.text in '([':
                d += 1
            elif t.text in ')]':
                if t.text == ')' and d == 0:
                    break
                d -= 1
            if t.text == ',' and d == 0:
                parts.append(cur)
                cur = []
                continue
            cur.append(t)
        parts.append(cur)
        types, names, all_bare = [], [], True
        for p in parts:
            if not (len(p) == 1 and p[0].kind == 'id' and p[0].text not in TYPEKW):
                all_bare = False
            types.append(_param_type(p, _spaced(p)))
            names.append(_param_name(p))
        return types, names, all_bare, False


def _spaced(toks):
    out = ''
    for t in toks:
        if out and (t.kind in ('id', 'num') and out[-1] not in '*([ ,'):
            out += ' '
        out += t.text
    return out


def _param_name(toks):
    """The parameter's NAME, if it has one. canon_sig_reconcile keeps the DRAFT's parameter names
    while adopting the TU's canonical parameter TYPES — so both halves must be recoverable."""
    if len(toks) >= 2 and toks[-1].kind == 'id' and toks[-1].text not in TYPEKW \
            and toks[-2].text not in ('struct', 'union', 'enum'):
        return toks[-1].text
    m = re.match(r'^.*\(\s*\*\s*([A-Za-z_]\w*)\s*\).*$', _spaced(toks), re.S)   # `void (*a0)(void)`
    return m.group(1) if m else None


def _param_type(toks, txt):
    """A parameter's TYPE (the name, if any, removed): `s32 a0` -> `s32`, `void (*a0)(void)` ->
    `void (*)(void)`, `s32 *a1` -> `s32 *`."""
    if len(toks) >= 2 and toks[-1].kind == 'id' and toks[-2].text not in ('struct', 'union', 'enum'):
        if toks[-1].text not in TYPEKW and toks[-2].kind != ',':
            return _ws(_spaced(toks[:-1]))
    m = re.match(r'^(.*\(\s*\*\s*)[A-Za-z_]\w*(\s*\).*)$', txt, re.S)   # fn-ptr param with a name
    if m:
        return _ws(m.group(1) + m.group(2))
    return _ws(txt)


def parse(stmt, span=None):
    """Parse ONE declaration -> [Declarator]. Raises CDeclError on anything it cannot fully read.

    A statement that declares no object (`struct S { ... };`, a bare `;`) returns []."""
    text = _mask(stmt)
    p = _P(tokenize(text), stmt)
    storage, quals, base = p.specifiers()
    out = []
    if p.peek().text in (';', ''):
        return out                                              # a tag definition; declares no name
    while True:
        stars = 0
        while p.peek().text == '*':
            p.take()
            stars += 1
            while p.peek().text in QUALS:
                p.take()
        name, chain = _direct(p)
        chain = chain + [(PTR,)] * stars
        p.skip_gnu()
        if name is None:
            raise CDeclError(f'declaration with no declared name: {stmt[:90]!r}')
        d = Declarator(name, chain, base, storage, quals)
        d.span = span
        d.text = stmt.strip()
        out.append(d)
        t = p.peek()
        if t.text == '=':                                       # initializer — skip, balanced
            p.take()
            d_ = 0
            while p.peek().kind != 'eof':
                tt = p.peek().text
                if tt in '([{':
                    d_ += 1
                elif tt in ')]}':
                    d_ -= 1
                elif (tt == ',' or tt == ';') and d_ <= 0:
                    break
                p.take()
            t = p.peek()
        if t.text == ',':
            p.take()
            continue                                            # `extern s32 D_a, D_b, D_c;`
        if t.text == '{' or (t.kind == 'id' or t.text in ('*',)):
            # a body, or a K&R declaration-list and then a body: this is a DEFINITION.
            for dd in out:
                dd.is_definition = True
            return _resolve_kr(out)
        if t.text == ';' or t.kind == 'eof':
            return _resolve_kr(out)
        raise CDeclError(f'unexpected {t.text!r} after declarator in {stmt[:90]!r}')


def _resolve_kr(decls):
    """Settle the one ambiguity C cannot settle locally: `f(a0, a1)` is a K&R identifier-list in a
    DEFINITION, but a prototype with typedef'd parameter types in a DECLARATION. Now that we know
    whether a body followed, decide — and for a K&R list, drop the "types" (they are parameter
    NAMES; handing them to a consumer as types would be a lie)."""
    for d in decls:
        op = d._fun
        if op is None:
            continue
        types, names, all_bare, empty = op[1], op[2], op[3], op[4]
        if empty:
            d.is_proto = False                                  # `f()` — no prototype
        elif all_bare and d.is_definition:
            d.is_proto = False                                  # K&R identifier-list
            d.pnames, d.params = list(types), []                # those "types" are the names
        else:
            d.is_proto = True
    return decls


def _direct(p):
    """direct-declarator := ID suffixes | '(' declarator ')' suffixes"""
    t = p.peek()
    if t.text == '(' and p.peek(1).text in ('*', '('):
        # a GROUPED declarator — `(*D_x[])(void)`. (A '(' that is NOT followed by '*' or '(' is a
        # parameter list on an abstract declarator, which `suffixes()` handles.)
        p.take()
        stars = 0
        while p.peek().text == '*':
            p.take()
            stars += 1
            while p.peek().text in QUALS:
                p.take()
        name, inner = _direct(p)
        p.expect(')')
        inner = inner + [(PTR,)] * stars
        return name, inner + p.suffixes()          # the group's suffixes apply OUTSIDE it
    if t.kind == 'id':
        p.take()
        return t.text, p.suffixes()
    return None, p.suffixes()                      # abstract declarator (a parameter)


# ---------------------------------------------------------------------------------------------
# what consumers actually want
# ---------------------------------------------------------------------------------------------
def declarations(statements, path=''):
    """Parse a statement list -> [Declarator]. COVERAGE-ASSERTING (R32): at file scope C admits
    nothing but declarations, so every statement MUST parse. A silent skip is a defect."""
    out, bad = [], []
    for st in statements:
        text = st.text if isinstance(st, Stmt) else st
        span = (st.start, st.end) if isinstance(st, Stmt) else None
        if not text.strip().strip(';'):
            continue
        if MACRO_STMT.match(text):                 # NAMED, explicit exclusion — never a shrug
            continue
        try:
            out.extend(parse(text, span))
        except CDeclError as e:
            bad.append((text[:100], str(e)))
    if bad:
        raise CDeclError(f'{path}: {len(bad)} file-scope statement(s) did not parse — a depth-0 '
                         f'statement C accepts and this parser cannot read is a DEFECT:\n' +
                         '\n'.join(f'    {t!r}\n      -> {e}' for t, e in bad[:5]))
    return out


def scope(statements, path=''):
    """{name: Declarator} — the TU's file-scope namespace. FIRST declaration of a name wins (they
    must already be mutually compatible: the TU compiles today)."""
    ns = {}
    for d in declarations(statements, path):
        ns.setdefault(d.name, d)
    return ns


def tu_scope(tu_path, above=None):
    """{name: Declarator} the compiler sees in `tu_path` (optionally above a stub). THE oracle that
    every 'what does this TU declare' question in this repo should be asking.

    ⚠️ `above` answers *"can I USE this symbol without declaring it"* — the visibility question, which
    drives the block-scope-demotion branch. It is the WRONG question for *"will my declaration
    CONFLICT"*: C requires every declaration of a name in a TU to be compatible **regardless of
    order**, so a declaration BELOW the splice point conflicts just as hard as one above. Use the
    full scope (`above=None`) for conflict detection. (`canon_sig_reconcile` drives both decisions
    off one `visible` set — which is why `func_801387B8` hits `conflicting types` against a decl
    1,000 lines below its stub and the recovery pass reports nothing to fix.)"""
    return scope(tu_statements(tu_path, above), tu_path)


# ---------------------------------------------------------------------------------------------
# DRAFT TYPEDEF STRIP — one primitive, six copied regexes (Phase-27 T4)
# ---------------------------------------------------------------------------------------------
# A drafted matching-C body is written "self-contained": it carries its own `typedef unsigned char
# u8;` … so it compiles standalone. Spliced into a TU that already provides those names (via
# common.h / engine_types.h), C89/gcc-2.7.2 REJECTS the redefinition — a plumbing error, not a byte
# mismatch. Six tools each carried a scalar-name regex to strip the dups; they had COMPLEMENTARY
# holes (harvest_verify._TD lacked M2C_UNK; masked_diff.SCALAR_TYPEDEF_RE's `[^;]*` body could not
# cross a `;`, so a multi-typedef LINE stripped none; none handled a struct typedef the target
# provides), and each silently recorded the resulting compile failure as "not a match". These two
# functions replace all of it with the parser that already knows what a typedef is.

_TYPEDEF_HEAD = re.compile(r'\s*typedef\b')


@functools.lru_cache(maxsize=None)
def typedef_names(tu_path, above=None):
    """The set of names the TU declares as typedefs (what a self-contained draft must NOT redefine).

    Built on tu_statements (cpp-derived, NOT coverage-asserting) rather than tu_scope on purpose:
    this feeds the byte-gate, and a cdecl coverage gap on some unrelated file-scope statement must
    not be able to crash a matching run — only typedef statements are parsed, everything else is
    ignored. PER-TU by design: engine_types.h reaches ~1470 of 1683 TUs, so a global header parse
    would strip a `Blk16` the 213 non-including TUs still need. Cached via tu_statements' own cache."""
    names = set()
    for st in tu_statements(tu_path, above):
        if not _TYPEDEF_HEAD.match(st):
            continue
        try:
            for d in parse(st):
                if d.storage == 'typedef':
                    names.add(d.name)
        except CDeclError:
            pass                      # a typedef this parser can't read -> don't strip on a guess
    return names


def strip_provided_typedefs(draft_text, provided):
    """Remove from a DRAFT every depth-0 typedef statement whose declared name(s) are ALL in
    `provided` (the target scope already supplies them). Splits multi-typedef lines correctly
    (`split_statements` is depth-aware: `typedef ...;typedef ...;` -> two, `typedef struct{int
    a;}F;` -> one), and covers scalar AND struct typedefs uniformly. KEEPS a draft-local typedef
    whose name `provided` lacks, and KEEPS a mixed statement (some names provided, some not) so a
    needed local type is never dropped — the byte-gate then arbitrates. `provided` empty -> no-op."""
    if not provided:
        return draft_text
    drop = []
    for st in split_statements(draft_text):
        if not _TYPEDEF_HEAD.match(st.text):
            continue
        try:
            ds = parse(st.text)
        except CDeclError:
            continue
        if ds and all(d.storage == 'typedef' and d.name in provided for d in ds):
            drop.append((st.start, st.end))
    if not drop:
        return draft_text
    out, last = [], 0
    for s, e in sorted(drop):
        out.append(draft_text[last:s])
        last = e
    out.append(draft_text[last:])
    return ''.join(out)


# ---------------------------------------------------------------------------------------------
# C TYPE COMPATIBILITY — the predicate four tools each half-implement, and get wrong
# ---------------------------------------------------------------------------------------------
# The question every recovery pass actually asks is "will gcc accept the draft's declaration
# alongside the TU's?" — and that is C's *compatible type* relation, which is NOT string equality:
#
#   * `extern s32 D_x[];`  IS compatible with  `extern s32 D_x[4];`   (incomplete vs complete array)
#   * `extern s32 D_x;`    is NOT compatible with  `extern u32 D_x;`   (signedness — gcc REJECTS it)
#
# Both existing implementations get this exactly backwards. `reconcile_decls._norm_type` collapses
# `s32|u32|int|unsigned|long` to ONE token, so it declares a signedness change "already compatible"
# and refuses to repair it — the compile then fails anyway, on a decl the tool looked at and
# approved. It is right about CODEGEN (same width, same load) and wrong about the C FRONT END, which
# rejects the redeclaration before codegen is ever reached.
#
# Validated against the real cross-gcc over every (TU, draft) declaration pair in the corpus:
# `tools/cdecl.py --audit --compat`.

_PRIM = {'char': 'char', 'short': 'short', 'int': 'int', 'long': 'long', 'float': 'float',
         'double': 'double', 'void': 'void', 'signed': 'int', 'unsigned': 'unsigned int'}


@functools.lru_cache(1)
def _aliases():
    """typedef name -> underlying primitive, resolved transitively from the project's own prelude.
    Derived by parsing common.h + engine_types.h with THIS parser — never a hand-kept table."""
    al = {}
    for h in ('include/common.h', 'src/shared/engine_types.h'):
        p = os.path.join(REPO, h)
        if not os.path.exists(p):
            continue
        for st in split_statements(open(p).read()):
            try:
                for d in parse(st.text):
                    if d.storage == 'typedef' and not d.chain:
                        al[d.name] = d.base
            except CDeclError:
                pass
    for _ in range(4):                                   # resolve chains (u32 -> unsigned int -> …)
        al = {k: al.get(v, v) for k, v in al.items()}
    return al


def _prim(base):
    """Resolve a base type to its underlying spelling, canonically ordered."""
    al = _aliases()
    words = [al.get(w, w) for w in (base or '').split()]
    words = ' '.join(words).split()
    if any(w in TAGKW for w in words):
        return ' '.join(words)                           # struct/union/enum: identity by tag
    order = {'unsigned': 0, 'signed': 0, 'long': 1, 'short': 1, 'char': 2, 'int': 3, 'float': 2}
    core = sorted((w for w in words if w not in QUALS), key=lambda w: order.get(w, 4))
    s = ' '.join(core)
    return {'int unsigned': 'unsigned int', 'unsigned': 'unsigned int', 'signed': 'int',
            'signed int': 'int', 'long int': 'long', 'unsigned long int': 'unsigned long'}.get(s, s)


def compatible(a, b):
    """CAN THESE TWO DECLARATIONS OF ONE NAME COEXIST IN ONE TU? — i.e. **will cc1 accept them.**

    Not "are these the same type", and NOT what the C standard says. This models **gcc-2.7.2's
    actual behaviour**, because gcc-2.7.2 is what compiles this project, and it is measurably laxer
    than both the standard and modern gcc. Every rule below was either confirmed or REFUTED by
    running the real `cc1` over the live corpus (`tools/cdecl.py --compat`, 1,485 real pairs):

      * A TYPEDEF may not be redeclared at all — not even identically (`redefinition of 'X'`). Two
        typedef declarations of one name can NEVER coexist, however equal their types. (Modern gcc
        ALLOWS this — C11 relaxed it — which is exactly why the adjudicator must be cc1. This is
        also why `_uniquify_draft_types` must strip-or-rename rather than compare.)
      * QUALIFIERS DO NOT CONFLICT: cc1 accepts `extern u16 X;` beside `extern volatile u16 X;`
        (modern gcc rejects it). REFUTED by the oracle; the rule was removed.
      * THE NO-PROTOTYPE RULE IS **ORDER-DEPENDENT**, and that is the headline. Measured on cc1:
              void X(s16);  then  void X();      ->  ACCEPTS
              void X();     then  void X(s16);   ->  REJECTS  (`conflicting types`)
              void X();     then  void X(s32)/X(void*)  ->  ACCEPTS   (no default promotion)
        i.e. a later PROTOTYPE must be compatible with the composite type the earlier `()` already
        fixed (whose args are default-promoted) — but an earlier prototype simply wins.
        ⚠️ **This is the wall Phase 15 wrote up as "the `()` no-prototype escape can never work"** —
        the basis of the "159 arity/narrow-param conflicts — no clean deterministic fix" dead-end.
        It is only true in ONE DIRECTION. Put the narrow-param prototype FIRST and cc1 accepts it.
        Whether the resulting CODEGEN matches is a separate question the byte-gate answers — but the
        wall's stated cause does not hold. **Re-test target for A10.**

    So `compatible(first, second)` takes them IN TU ORDER. Callers get the order from
    `tu_scope(above=fn)`: a TU declaration above the splice point precedes the draft's; one below
    follows it.

    Being permissive is also the SAFE direction: a decl cc1 accepts needs no rewrite, so the draft
    keeps the types it intended (its `volatile`, its narrow params — all load-bearing for codegen),
    and the whole-binary byte-gate remains the sole arbiter of the bytes (G3/P9). Every needless
    rewrite is a perturbation that can only lose a match.
    """
    if a is None or b is None:
        return True                                      # nothing to conflict with
    if a.storage == 'typedef' or b.storage == 'typedef':
        return False                                     # C89/2.7.2 forbids redeclaring a typedef
    ca, cb = [o[0] for o in a.chain], [o[0] for o in b.chain]
    if ca != cb:
        return False                                     # array vs ptr vs fn: different types
    if _prim(a.base) != _prim(b.base):
        return False                                     # includes the signedness case cc1 rejects
    for x, y in zip(a.chain, b.chain):
        if x[0] == ARR and x[1] and y[1] and x[1] != y[1]:
            return False                                 # T[4] vs T[8]; T[] vs T[4] IS compatible
        if x[0] == FUN:
            xt, yt, xe, ye = x[1], y[1], x[4], y[4]      # `empty` == a no-prototype declaration
            if xe and not ye:
                # `()` FIRST, prototype SECOND: the prototype must be compatible with the composite
                # type the `()` already fixed — so no parameter may be altered by default promotion.
                return not any(_prim(p.rstrip('* ')) in _PROMOTES and '*' not in p for p in yt)
            if ye:
                continue                                 # prototype first, `()` second: cc1 accepts
            if len(xt) != len(yt):
                return False                             # arity
            if any(_prim(p.rstrip('* ')) != _prim(q.rstrip('* ')) or ('*' in p) != ('*' in q)
                   for p, q in zip(xt, yt)):
                return False
    return True


# The types C's default argument promotions alter. A later prototype naming one of these is
# incompatible with an earlier `()` — the one direction in which the "no-prototype escape" really
# does fail (measured on cc1, not assumed from the standard).
_PROMOTES = {'char', 'short', 'unsigned char', 'unsigned short', 'signed char', 'float'}


# ---------------------------------------------------------------------------------------------
# THE THREE ORACLES.  The deliverable of this module is a MEASUREMENT, not a belief.
# ---------------------------------------------------------------------------------------------
def _tus():
    return (sorted(_glob.glob(os.path.join(REPO, 'src/ov_*/*.c'))) +
            sorted(_glob.glob(os.path.join(REPO, 'src/*.c'))) +
            sorted(_glob.glob(os.path.join(REPO, 'src/resident/*.c'))))


def _drafts():
    return sorted(_glob.glob(os.path.join(REPO, '.run/drafts*/*.c')))


def audit_coverage(limit=None, verbose=False):
    """ORACLE 1 (R32) — COVERAGE, with a candidate set taken from the C grammar rather than from a
    hand-maintained regex: at file scope C admits NOTHING BUT DECLARATIONS, so every depth-0
    statement is a candidate and any one this parser cannot read is a DEFECT."""
    tus, drafts = _tus(), _drafts()
    if limit:
        tus, drafts = tus[:limit], drafts[:limit * 10]
    stmts = decls = 0
    bad = []

    for p in tus:                                   # TUs: cpp-derived (the §8c law)
        try:
            sts = tu_statements(p)
        except CDeclError as e:
            bad.append((p, str(e)))
            continue
        stmts += len(sts)
        for st in sts:
            if not st.strip().strip(';') or MACRO_STMT.match(st):
                continue
            try:
                decls += len(parse(st))
            except CDeclError as e:
                bad.append((p, f'{st[:90]!r} -> {e}'))

    for p in drafts:                                # drafts: raw, span-preserving
        try:
            sts = split_statements(open(p, errors='replace').read())
        except Exception as e:
            bad.append((p, str(e)))
            continue
        stmts += len(sts)
        for st in sts:
            if not st.text.strip().strip(';') or MACRO_STMT.match(st.text):
                continue
            try:
                decls += len(parse(st.text))
            except CDeclError as e:
                bad.append((p, f'{st.text[:90]!r} -> {e}'))

    # ADJUDICATE MY OWN GAP WITH GCC, rather than deciding for myself which failures "don't count".
    # A statement gcc ALSO rejects is not C, so rejecting it is correct and the INPUT is corrupt; a
    # statement gcc ACCEPTS and this parser does not is MY defect. That verdict belongs to the C
    # front end, not to me — the whole audit exists because six people graded their own homework.
    defects, notc = [], []
    for p, e in bad:
        stmt = e.split(' -> ')[0].strip("'\"")
        try:
            src = os.path.join(REPO, '.run/audit/cdecl/adj.c')
            open(src, 'w').write(_PROBE_HDR + stmt.encode().decode('unicode_escape') + '\n')
            r = subprocess.run([CC, '-fsyntax-only', '-w', '-I' + os.path.join(REPO, 'include'),
                                '-I' + os.path.join(REPO, 'src'), src],
                               capture_output=True, text=True, cwd=REPO)
            (notc if r.returncode else defects).append((p, e))
        except Exception:
            defects.append((p, e))

    print(f'[coverage] {len(tus)} TUs (cpp-derived) + {len(drafts)} drafts (raw)')
    print(f'[coverage] depth-0 statements: {stmts}   declarators parsed: {decls}')
    print(f'[coverage] unparsed: {len(bad)}  ->  PARSER DEFECTS (gcc accepts, cdecl does not): '
          f'{len(defects)}   NOT-C (gcc rejects it too — corrupt input): {len(notc)}')
    for p, e in defects[:20 if verbose else 8]:
        print(f'    DEFECT {os.path.relpath(p, REPO)}: {e}')
    if notc:
        dirs = sorted({os.path.dirname(os.path.relpath(p, REPO)) for p, _ in notc})
        print(f'    NOT-C in {len(dirs)} dir(s) (all scratch, none in src/): {dirs[:6]}')
        print(f'      e.g. {notc[0][1][:100]}')
    return not defects


_PROBE_HDR = '#include "common.h"\n#include "shared/engine_types.h"\n'


@functools.lru_cache(1)
def _known_types():
    """Every type name common.h + engine_types.h already define — parsed with THIS parser (the
    probe environment must not redefine them)."""
    names = set(TYPEKW) | set(QUALS) | set(TAGKW)
    for h in ('include/common.h', 'src/shared/engine_types.h'):
        p = os.path.join(REPO, h)
        if not os.path.exists(p):
            continue
        for st in split_statements(open(p).read()):
            try:
                for d in parse(st.text):
                    if d.storage == 'typedef':
                        names.add(d.name)
            except CDeclError:
                pass
    return names


def _synth(decls):
    """Synthesize a typedef for every TU-LOCAL type a statement names (Vec3s, CdlFILE, E_3B7AC…),
    so gcc can adjudicate a declaration lifted out of its own TU. Safe: BOTH the original and the
    reconstruction see the same synthetic type, so a mangled type still shows up as a mismatch —
    what this cannot do is hide a defect."""
    known, out = _known_types(), set()
    for d in decls:
        for tok in re.findall(r'[A-Za-z_]\w*', (d.base or '') + ' ' + ' '.join(d.params or [])):
            if tok not in known and not re.match(r'^(void|struct|union|enum)$', tok):
                out.add(tok)
    return ''.join(f'typedef int {t};\n' for t in sorted(out))


def _gcc_probe(items, tag, with_recon):
    """Compile the originals (and optionally this parser's reconstructions) -> gcc's stderr."""
    d = os.path.join(REPO, '.run/audit/cdecl')
    os.makedirs(d, exist_ok=True)
    src = os.path.join(d, f'probe_{tag}.c')
    with open(src, 'w') as f:
        f.write(_PROBE_HDR)
        f.write(''.join(sorted({s for _, _, syn in items for s in syn.splitlines(True)})))
        for i, (orig, recons, _syn) in enumerate(items):
            f.write(f'/* {i} */ {orig}\n')
            if with_recon:
                for r in recons:
                    f.write(f'{r}\n')
    p = subprocess.run([CC, '-fsyntax-only', '-w', '-I' + os.path.join(REPO, 'include'),
                        '-I' + os.path.join(REPO, 'src'), src],
                       capture_output=True, text=True, cwd=REPO)
    return p.stderr


def _sift(items, with_recon, tag):
    """-> (accepted, rejected). Batch, and bisect only on failure."""
    ok, bad, B = [], [], 200
    for b in range(0, len(items), B):
        chunk = items[b:b + B]
        if not _gcc_probe(chunk, tag, with_recon):
            ok.extend(chunk)
            continue
        for one in chunk:
            e = _gcc_probe([one], tag + '1', with_recon)
            (bad.append((one, e.strip().split('\n')[0])) if e else ok.append(one))
    return ok, bad


def audit_gcc(limit=None):
    """ORACLE 2 (R34) — THE C FRONT END, WHICH CAN DISAGREE WITH ME.

    For every distinct declaration in the corpus, hand gcc the ORIGINAL and this parser's
    RECONSTRUCTION of it, declaring the same name in one TU. If the parse got the type wrong in any
    way, gcc answers `conflicting types` and names the line. This is not a self-check — it is the
    same front end that arbitrates the build, and it cannot be fooled by a plausible regex.

    (Definitions are excluded: their bodies cannot compile out of context. Declarations are what the
    fifteen scanners operate on.)"""
    seen, pairs = set(), []
    for p in _tus()[:limit] if limit else _tus():
        for st in tu_statements(p):
            if not st.strip().strip(';') or MACRO_STMT.match(st) or st in seen:
                continue
            seen.add(st)
            try:
                ds = parse(st)
            except CDeclError:
                continue                            # oracle 1 owns unparsed statements
            if not ds or any(d.is_definition for d in ds) or any(d.storage == 'typedef' for d in ds):
                continue
            i = len(pairs)
            orig, recons = st, []
            for d in ds:                            # rename so 200 can share one probe TU
                new = f'{d.name}_p{i}'
                orig = re.sub(r'\b' + re.escape(d.name) + r'\b', new, orig)
                recons.append(d.declaration(name=new))
            pairs.append((orig, recons, _synth(ds)))

    print(f'[gcc] {len(pairs)} distinct declarations -> the real cross-compiler')

    # A: can gcc compile the ORIGINAL at all? If not, the probe environment lacks that TU's local
    # types and CANNOT adjudicate — an honest, COUNTED skip, never a silent one.
    judged, env = _sift(pairs, False, 'a')
    # B: now add MY reconstruction. A declaration that compiled alone and does NOT compile beside
    # my reconstruction of it means the two are DIFFERENT TYPES — i.e. I parsed it wrong.
    good, bad = _sift(judged, True, 'b')

    print(f'[gcc] adjudicated: {len(judged)}   env-skipped (gcc cannot compile the original out of '
          f'its TU): {len(env)}')
    print(f'[gcc] accepted: {len(good)}   REJECTED (my reconstruction is a DIFFERENT TYPE): {len(bad)}')
    for (orig, recons, _s), e in bad[:10]:
        print(f'    DISAGREES  orig: {orig.strip()[:88]}')
        print(f'               mine: {recons}')
        print(f'               gcc : {e}')
    return not bad


CC1 = os.path.join(REPO, 'tools/bin/gcc-2.7.2-psx/cc1')
CC1FLAGS = ['-quiet', '-O2', '-G0', '-mips1', '-mcpu=3000', '-mgas', '-msoft-float', '-fgnu-linker']
_ERR = re.compile(r'error|redefinition|conflicting|incompatible|redeclar|parse error', re.I)


def _cc1_accepts(body):
    """Does THE REAL BUILD FRONT END (gcc-2.7.2 `cc1`) accept this? — not modern gcc.

    They DISAGREE, and it matters: C11 permits redefining a typedef to the same type, C89/2.7.2 does
    NOT (`redefinition of 'X'`). Validating a compatibility rule against a compiler that is not the
    one compiling the code is *exactly* the failure this module exists to prevent — a recovery pass
    that "approves" a declaration the real front end then refuses."""
    d = os.path.join(REPO, '.run/audit/cdecl')
    os.makedirs(d, exist_ok=True)
    c, i = os.path.join(d, 'cc1probe.c'), os.path.join(d, 'cc1probe.i')
    open(c, 'w').write(body)
    p = subprocess.run(CPP + ['-Isrc', c], capture_output=True, text=True, cwd=REPO)
    if p.returncode:
        return None                                      # cannot adjudicate
    open(i, 'w').write(p.stdout)
    r = subprocess.run([CC1] + CC1FLAGS + [i, '-o', '/dev/null'],
                       capture_output=True, text=True, cwd=REPO)
    return not (r.returncode or _ERR.search(r.stderr or ''))


def _synth_distinct(decls):
    """Synthesize each unknown type as a DISTINCT struct. Emitting `typedef int Vec8;` would collapse
    `extern Vec8 X;` and `extern int X;` into the same type and the probe would call them compatible
    — the oracle destroying the very distinction it is meant to test."""
    known, out = _known_types(), set()
    for d in decls:
        for tok in re.findall(r'[A-Za-z_]\w*', (d.base or '') + ' ' + ' '.join(d.params or [])):
            if tok not in known and tok not in ('void', 'struct', 'union', 'enum'):
                out.add(tok)
    return ''.join(f'typedef struct {{ int _{t}; }} {t};\n' for t in sorted(out))


def audit_compat(limit=2500):
    """ORACLE 4 — `compatible()` vs the REAL cc1, on every (TU-decl, draft-decl) pair the corpus
    actually contains. My predicate says accept/reject; gcc-2.7.2 says accept/reject. Any
    disagreement is MY bug, and it is the kind that silently caps the whole recovery pipeline."""
    tus = sorted(_glob.glob(os.path.join(REPO, 'src/ov_SC01_077/*.c')))
    scopes = {t: tu_scope(t) for t in tus}
    pairs = {}
    import random
    for p in random.Random(11).sample(_drafts(), min(limit, len(_drafts()))):
        try:
            txt = open(p, errors='replace').read()
        except Exception:
            continue
        for st in split_statements(txt):
            try:
                ds = parse(st.text)
            except CDeclError:
                continue
            for d in ds:
                if d.is_definition:
                    continue
                for ns in scopes.values():
                    tu = ns.get(d.name)
                    if tu is None:
                        continue
                    key = (tu.declaration(name='X'), d.declaration(name='X'))
                    pairs.setdefault(key, (compatible(tu, d), (tu, d)))

    print(f'[compat] {len(pairs)} distinct (TU-decl, draft-decl) pairs from the real corpus')
    print(f'[compat] adjudicator: gcc-2.7.2 cc1 (THE BUILD FRONT END), not modern gcc')
    bad, skip = [], 0
    for (tu_d, dr_d), (mine, (tu, d)) in pairs.items():
        body = _PROBE_HDR + _synth_distinct([tu, d]) + tu_d + '\n' + dr_d + '\n'
        got = _cc1_accepts(body)
        if got is None:
            skip += 1
        elif got != mine:
            bad.append(((tu_d, dr_d), mine, got))
    print(f'[compat] agree: {len(pairs) - len(bad) - skip}   DISAGREE: {len(bad)}   unadjudicable: {skip}')
    for (k, mine, got) in bad[:10]:
        print(f'    TU   : {k[0]}\n    draft: {k[1]}')
        print(f'    cdecl says {"compatible" if mine else "CONFLICT"}, cc1 says '
              f'{"compatible" if got else "CONFLICT"}\n')
    # An UNADJUDICABLE pair is a silent skip, and a gate that skips its whole corpus and prints GREEN
    # is the exact bug this module was written to hunt. (It did that here, once: a missing `-Isrc`
    # made cpp fail on all 1,485 probes, `bad` stayed empty, and the audit reported success. R32 is
    # not "fail loud" — it is COUNT WHAT YOU SKIPPED.)
    if skip:
        print(f'    !! {skip} pair(s) could not be adjudicated — a skipped check is NOT a passed one')
    return not bad and not skip


def audit_differential():
    """ORACLE 3 — vs THE FIFTEEN INCUMBENTS. This parser must find a strict SUPERSET of every
    scanner it replaces: any symbol an incumbent sees and this one does not is a defect in THIS
    tool. The reverse (symbols only this one sees) is the measured size of the hole."""
    sys.path.insert(0, os.path.join(REPO, 'tools'))
    import gen_harvest_targets as ght
    import reconcile_decls as rd
    import sig_unify as su

    ec = os.path.join(REPO, 'src/shared/engine_core.h')
    text = open(ec).read()

    # The incumbents scan engine_core.h's RAW TEXT — i.e. the bodies of 1,801 #define macros. A
    # declaration in a macro body declares nothing until the macro is INVOKED (the §8c law), so the
    # honest like-for-like comparison is against what cpp produces when every macro IS invoked.
    # That synthetic TU is exactly "everything engine_core.h is capable of declaring".
    d = os.path.join(REPO, 'src/shared')
    tmp = os.path.join(d, '.cdecl_allmacros.c')
    macros = re.findall(r'^#define\s+(DEFINE_func_[0-9A-Fa-f]+)\(\)', text, re.M)
    with open(tmp, 'w') as f:
        f.write('#include "../../include/common.h"\n#include "engine_types.h"\n'
                '#include "engine_core.h"\n')
        for mac in macros:
            f.write(f'{mac}()\n')
    try:
        stmts = tu_statements(tmp)
        mine = scope(stmts, tmp)
        expanded = '\n'.join(stmts)
    finally:
        os.path.exists(tmp) and os.remove(tmp)
    print(f'[differential] expanded {len(macros)} DEFINE_ macros through cpp -> {len(mine)} names')

    mine_d = {n for n in mine if n.startswith('D_')}
    rows = []
    for name, rx in (('gen_harvest_targets.DATA_DECL_RE', ght.DATA_DECL_RE),
                     ('reconcile_decls.DATA_DECL_LINE_RE', rd.DATA_DECL_LINE_RE),
                     ('sig_unify.DATA_DECL_RE', su.DATA_DECL_RE)):
        theirs = set()
        for m in rx.finditer(text):
            theirs |= set(re.findall(r'\bD_[0-9A-Fa-f]+\b', m.group(0)))
        # A symbol I do not report is only MY defect if it is genuinely at FILE scope. A
        # block-scope `extern` is private to its function and is NOT part of the TU's namespace —
        # reporting it as an authoritative canonical is what produced the §8d
        # `conflicting types for D_801812A4` wall. So separate the two, and never let a real defect
        # hide behind the excuse.
        lost = theirs - mine_d
        block = {s for s in lost if re.search(r'\bextern\b[^;]*\b' + s + r'\b', expanded)}
        defect = lost - block
        rows.append((name, len(theirs), len(mine_d), len(mine_d - theirs), sorted(defect),
                     sorted(block)))

    print('[differential] engine_core.h — D_ symbols (raw-text scan vs cpp-expanded file scope)')
    print(f'    {"incumbent":<36} {"theirs":>7} {"cdecl":>7} {"cdecl-only":>11} {"MY DEFECT":>10} '
          f'{"their block-scope error":>24}')
    ok = True
    for name, t, m, g, defect, block in rows:
        print(f'    {name:<36} {t:>7} {m:>7} {g:>11} {len(defect):>10} {len(block):>24}')
        if defect:
            print(f'        DEFECT (file-scope, invisible to cdecl): {defect[:8]}')
        if block:
            print(f'        they count BLOCK-scope externs as file-scope canonicals: {block[:4]}')
        ok &= not defect

    named = {'D_80127530': 'array', 'D_80127088': 'fnptr', 'D_8011DB28': 'fnptr',
             'D_801274D0': 'fnptr', 'D_8018E858': 'fnptr_array'}
    print('    the audit\'s named blind symbols (engine_core.h), now resolved WITH THEIR KIND:')
    for n, want in named.items():
        d = mine.get(n)
        got = d.kind if d else 'MISSING'
        flag = 'ok' if got == want else 'WRONG'
        ok &= (got == want)
        print(f'      {n:<14} kind={got:<12} (expected {want})  [{flag}]'
              + (f'  {d.type}' if d else ''))
    return ok


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--audit', action='store_true', help='oracle 1 (coverage) + oracle 3 (differential)')
    ap.add_argument('--gcc', action='store_true', help='oracle 2: the C front end (slow, decisive)')
    ap.add_argument('--compat', action='store_true',
                    help='oracle 4: compatible() vs the REAL gcc-2.7.2 cc1 on live corpus pairs')
    ap.add_argument('--limit', type=int, help='sample N TUs (a fast smoke run)')
    ap.add_argument('--tu', help='print the file-scope scope of a TU')
    ap.add_argument('--above', help='...truncated above this function\'s INCLUDE_ASM stub')
    ap.add_argument('--parse', help='parse one declaration and print it')
    ap.add_argument('-v', '--verbose', action='store_true')
    a = ap.parse_args()

    if a.parse:
        for d in parse(a.parse):
            print(f'{d.name}: kind={d.kind} type={d.type!r} proto={d.is_proto} '
                  f'def={d.is_definition} params={d.params} names={d.pnames}')
            print(f'  reconstruction: {d.declaration()}')
        return
    if a.tu:
        ns = tu_scope(a.tu, a.above)
        for n, d in sorted(ns.items()):
            print(f'  {n:<24} {d.kind:<12} {d.type}')
        print(f'{len(ns)} file-scope names visible' + (f' above {a.above}' if a.above else ''))
        return
    if a.audit or a.gcc or a.compat:
        ok = True
        if a.audit:
            ok &= audit_coverage(a.limit, a.verbose)
            print()
            ok &= audit_differential()
        if a.gcc:
            print()
            ok &= audit_gcc(a.limit)
        if a.compat:
            print()
            ok &= audit_compat()
        print('\n' + ('cdecl: ALL ORACLES GREEN' if ok else 'cdecl: DEFECTS FOUND (see above)'))
        sys.exit(0 if ok else 1)
    ap.print_help()


if __name__ == '__main__':
    main()

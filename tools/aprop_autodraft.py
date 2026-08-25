"""Mechanically draft A-prop members: seed body + symbol rebase + a MINIMAL self-contained preamble.

WHY THIS EXISTS (S50, cookbook §171a). A lane-A member shares its family's `h_seq` with a MATCHED
sibling, so its body IS the seed's body with the per-location symbols rebased. Two mechanisms had
each taken a run at that population and each left it on the table:

  - `family_sweep --hseq` remaps mechanically but CARRIES the seed's declaration layer, and its
    dominant failure is decl-agreement — 331 of the 458 verdicts in S49's post-repair ledger
    (conflicting-types 213 / arity 45 / undeclared 40 / undef-ref 23 / redef 13). The body was
    never the problem; the decls it dragged along were.
  - the A-prop agent wave re-derives the same body at ~80k tokens per banked function, and got the
    per-location symbol WRONG every time it mattered (§171).

This does neither: it takes the seed body, applies `family_remap.symbol_map` (positional reloc zip,
three-oracle target spelling — authoritative, and far better than any text diff), and SYNTHESIZES a
minimal preamble from scratch — one `extern` per referenced symbol, plus only those seed typedefs
the body actually names and the destination TU does not already define. Nothing else travels.

Byte-proven on the ×1 probe before this tool existed: `func_801E2858`@md_SC03_132 banked from a
hand-written 15-line draft of exactly this shape, in a family the mechanical sweep had refused.

Every draft is a CANDIDATE. The whole-binary byte-gate stays the sole arbiter (G3/P9) — run the
output slate through `tools/gate_lane.py`.

  tools/aprop_autodraft.py [--limit N] [--only <family-addr>] [--max-sites N]
"""
import argparse, collections, glob, json, os, re, subprocess, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import aprop_symfix as ASF
import corpus
import draft_prechecks as PRE
import family_cousins as FC
import family_remap as FR

CARDS = ".run/aprop_cards.json"


def seed_file_text(path):
    return open(path).read() if path and os.path.isfile(path) else ""


def macro_body(header_text, name):
    """A `DEFINE_<fn>()` engine_core macro, de-macroized back into a plain C block.

    The macro form already carries its own externs plus the definition — the very shape this tool
    synthesizes for inline seeds, pre-assembled. Macro-bodied seeds are the single largest slice of
    the A-prop pool (567 of 1,196 members), so skipping them skips half the lane."""
    m = re.search(rf'^[ \t]*#define\s+DEFINE_{re.escape(name)}\s*\(\s*\)\s*(\\?)\s*$',
                  header_text, re.M | re.I)
    if not m or not m.group(1):
        return None
    # m.end() sits BEFORE the newline the trailing `\` continues over; splitting from there yields
    # an empty first element and ends the walk immediately with an empty body.
    out = []
    for ln in header_text[m.end():].lstrip('\n').split('\n'):
        cont = ln.rstrip().endswith('\\')
        out.append(ln.rstrip()[:-1].rstrip() if cont else ln.rstrip())
        if not cont:
            break
    body = '\n'.join(out)
    # R32: refuse a body whose braces do not balance rather than emit a truncated definition.
    return body if body.count('{') and body.count('{') == body.count('}') else None


def seed_body(sb, seed_name, header="src/shared/engine_core.h"):
    """-> (body_text, seed_text_for_decl_lookup, kind) for an inline OR macro seed."""
    if sb["kind"] == "macro":
        h = seed_file_text(sb["path"] or header)
        for nm in (sb.get("name"), seed_name):
            block = macro_body(h, nm) if nm else None
            if block:
                # The DEFINITION only — the macro's own extern block becomes the DECL SOURCE, not
                # part of the draft. Pasting it wholesale reintroduces the exact decl-agreement
                # failure the minimal-preamble design exists to avoid: measured, macro seeds banked
                # 77/276 (28%) that way against inline's 145/213 (68%), and the macro failures were
                # `parse error before '*'` / `too few arguments` — decl collisions, every one.
                return ASF.body_in_text(block, nm) or block, block, "macro"
        return None, "", "macro"
    for nm in (sb.get("name"), seed_name):
        b = ASF.body_text(sb["path"], nm) if nm else None
        if b:
            return b, seed_file_text(sb["path"]), sb["kind"]
    return None, "", sb["kind"]


def dlabel_bytes(asm_path, sym):
    """The bytes of `sym` when it is DEFINED INSIDE the member's own nonmatchings .s — data that
    vanishes the moment the INCLUDE_ASM stub is replaced. Such a symbol must be DEFINED in the
    draft (with the member's OWN bytes, which differ per location), never merely declared extern.
    Byte-proven on func_801EDC18 x4, whose four siblings each carry their own const."""
    if not asm_path or not os.path.exists(asm_path):
        return None
    m = re.search(rf'^dlabel {re.escape(sym)}\b(.*?)^enddlabel {re.escape(sym)}\b',
                  open(asm_path).read(), re.M | re.S)
    if not m:
        return None
    out = b''
    for w in re.findall(r'\.word\s+(0x[0-9A-Fa-f]+)', m.group(1)):
        out += int(w, 16).to_bytes(4, 'little')
    for b in re.findall(r'\.byte\s+([^\n]+)', m.group(1)):
        out += bytes(int(x, 0) for x in b.split(',') if x.strip())
    return out or None


def data_def_for(sym, new_sym, seed_text, data):
    """The seed's DEFINITION of `sym`, renamed and re-initialised with this member's bytes.

    Only the flat-byte-list shape is handled: the substitution must be provably byte-for-byte, and
    a partially-understood initializer silently mis-initialised is exactly the failure the gate
    would catch but nobody would explain."""
    m = re.search(rf'^[ \t]*((?:const\s+|static\s+|volatile\s+)*[A-Za-z_]\w*[\s\*]+)'
                  rf'{re.escape(sym)}\b(\s*\[[^\]]*\])?\s*=\s*([^;]+);', seed_text, re.M)
    if not m:
        return None
    lits = re.findall(r'0x[0-9A-Fa-f]{1,2}\b', m.group(3))
    if len(lits) != len(data):
        return None
    it = iter(data)
    init = re.sub(r'0x[0-9A-Fa-f]{1,2}\b', lambda _: f"0x{next(it):02X}", m.group(3))
    return f"{m.group(1).strip()} {new_sym}{m.group(2) or ''} = {init};".replace("static ", "")


def _paren_args(text, i):
    """arg count of the call whose '(' is at text[i]; None if unparsable. Empty list -> 0."""
    depth, args, empty = 0, 1, True
    for j in range(i, min(i + 2000, len(text))):
        c = text[j]
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                return 0 if empty else args
        elif depth == 1 and c == ",":
            args += 1
        elif not c.isspace():
            empty = False if depth >= 1 and (j > i) else empty
    return None


def _arity_breaks(decl, sym, body):
    """True iff adopting `decl` makes a CALL in `body` uncompilable — a prototyped decl with N
    params against a call passing M != N args (`too few/many arguments`). The seed's body carries
    the original code's K&R sloppiness (empty calls to functions that take args), and the seed's
    own TU spelled the callee to match; a stricter destination prototype rejects those calls, so
    the seed's spelling is the only one that compiles the body (S59: 15 fresh drafts died on
    `too few arguments to func_80146C3C` when the destination's 2-param prototype was adopted)."""
    if not body:
        return False
    pm = re.search(rf'\b{re.escape(sym)}\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)\s*;', decl)
    if not pm:
        return False
    params = pm.group(1).strip()
    if params == "":
        return False                                             # no-proto: any call is legal
    if "..." in params:
        return False
    nparams = 0 if params == "void" else params.count(",") + 1
    for cm in re.finditer(rf'\b{re.escape(sym)}\s*\(', body):
        n = _paren_args(body, cm.end() - 1)
        if n is not None and n != nparams:
            return True
    return False


def decl_for(sym, seed_text, dest_text="", body="", fleet_text="", target_sym=None):
    """A file-scope declaration for `sym`, preferring the DESTINATION TU's own spelling — where
    that spelling can still compile the body.

    WHY THE DESTINATION IS PREFERRED (P31 S59, measured). This used to read the SEED's TU only, and
    the seed's spelling of a shared callee is frequently not the destination's: 45 of 188 staged
    A-prop drafts (24%) declared an extern whose type conflicted with the destination TU's own —
    C rejects the spliced TU on the conflict, so the byte-correct body never reaches the gate.
    The destination's declaration is what the spliced TU must coexist with (wave law 2), so take it
    when it exists.

    TWO SCOPE CORRECTIONS (S59, measured on the first fixed batch — COMPILE-FAIL went 43->85):
      * dest_text must be the member's HOME TU only, never the whole binary concatenated. C scope
        is the TU: a decl in a SIBLING TU of the same overlay can neither conflict with nor rescue
        the splice, and the whole-binary scan adopted `extern void func_8012BD14(s32)` from eleven
        sibling files into a TU that never declares it.
      * the destination's spelling is only usable if the BODY still compiles against it: 42 fresh
        drafts adopted a void return for a callee whose value the seed body reads
        (`if (func_8012BD14(..) > 0x1000)`) — `void value not ignored`, standalone and spliced
        alike. When the spellings conflict AND the body reads the value, the seed's spelling is
        the only one that preserves the bytes (signedness drives slt vs sltu); TU agreement is then
        the gate ladder's job (reconcile_tu casts the use, §41).

    A definition (`const Blk8 D_801EF6C0 = {...}`) must become a DECLARATION in the member — the
    member's own TU already emits those bytes (as `INCLUDE_RODATA`, or inside the function's own
    `.s`). Emitting the definition instead would either duplicate the data or fight splat for the
    address."""
    # the destination HOME TU's own spelling first — unless the body cannot compile against it.
    # DEST/FLEET are searched for the TARGET name; the seed tiers below use the SEED name. The
    # first cut searched the destination for the SEED's spelling of a RENAMED symbol — which the
    # destination cannot contain — so every renamed data symbol silently fell through to the
    # seed's spelling and the destination preference never applied where it mattered (S59:
    # D_801B9DF8 adopted `short` from the seed against the TU's file-scope `s32`).
    tsym = target_sym or sym
    if dest_text:
        m = re.search(rf'^[ \t]*extern[^\n;]*\b{re.escape(tsym)}\b[^\n;]*;', dest_text, re.M)
        if m:
            d = m.group(0).strip().rstrip("\\").rstrip()          # macro-body decls end in ` \`
            void_ret = re.match(r'extern\s+void\s*[^\(\*]*\b' + re.escape(tsym), d) and '*' not in d.split(tsym)[0]
            value_used = body and re.search(
                rf'(=\s*[^=;]*\b{re.escape(tsym)}\s*\(|\breturn\s+[^;]*\b{re.escape(tsym)}\s*\(|'
                rf'[<>!=+\-*/&|^]\s*{re.escape(tsym)}\s*\(|\b{re.escape(tsym)}\s*\([^;]*\)\s*[<>!=+\-*/&|^)])', body)
            if not (void_ret and value_used) and not _arity_breaks(d, tsym, body):
                return d
    m = re.search(rf'^[ \t]*extern[^\n;]*\b{re.escape(sym)}\b[^\n;]*;', seed_text, re.M)
    if m:
        return m.group(0).strip()
    m = re.search(rf'^[ \t]*((?:const\s+|static\s+|volatile\s+)*[A-Za-z_]\w*[\s\*]+)'
                  rf'{re.escape(sym)}\b(\s*\[[^\]]*\])?\s*=', seed_text, re.M)
    if m:
        return f"extern {m.group(1).strip()} {sym}{m.group(2) or ''};".replace("static ", "")
    m = re.search(rf'^[ \t]*[A-Za-z_][\w \*]*\b{re.escape(sym)}\s*\([^;{{]*\)\s*;', seed_text, re.M)
    if m:
        return m.group(0).strip()
    # LAST RESORT — BORROW a sibling TU's spelling (S59). When both the seed's TU and the home TU
    # are silent, the old whole-binary scan happened to supply a spelling and the scope fix removed
    # it wholesale — but "which TU may CONFLICT" (home only) and "where may a GUESS come from"
    # (anywhere) are different questions. A borrowed extern is a guess with the same guards as an
    # adopted one, and the whole-binary byte-gate arbitrates; refusing outright left 125 members
    # undrafted. Refuse only when nobody in the fleet spells the symbol at all.
    if fleet_text:
        m = re.search(rf'^[ \t]*extern[^\n;]*\b{re.escape(tsym)}\b[^\n;]*;', fleet_text, re.M)
        if m:
            d = m.group(0).strip()
            void_ret = re.match(r'extern\s+void\s*[^\(\*]*\b' + re.escape(tsym), d) and '*' not in d.split(tsym)[0]
            value_used = body and re.search(
                rf'(=\s*[^=;]*\b{re.escape(tsym)}\s*\(|\breturn\s+[^;]*\b{re.escape(tsym)}\s*\(|'
                rf'[<>!=+\-*/&|^]\s*{re.escape(tsym)}\s*\(|\b{re.escape(tsym)}\s*\([^;]*\)\s*[<>!=+\-*/&|^)])', body)
            if not (void_ret and value_used) and not _arity_breaks(d, tsym, body):
                return d
    # SYNTHESIZED no-proto for a FUNCTION whose call value the body never reads (S59). A function
    # symbol used only as a call target or an address needs nothing but linkage: `extern void f();`
    # is always compilable, coexists with any promotion-safe definition, and an address-take or an
    # ignored-value call emits identical code whatever the return type. Never synthesized when the
    # body reads the value — the return type drives codegen there, and guessing it is how wrong
    # bytes are born (the gate would catch it, but a build is not free).
    if re.match(r'func_[0-9A-Fa-f]{8}$', tsym) and body:
        value_used = re.search(
            rf'(=\s*[^=;]*\b{re.escape(tsym)}\s*\(|\breturn\s+[^;]*\b{re.escape(tsym)}\s*\(|'
            rf'[<>!=+\-*/&|^]\s*{re.escape(tsym)}\s*\(|\b{re.escape(tsym)}\s*\([^;]*\)\s*[<>!=+\-*/&|^)])', body)
        if not value_used:
            return f"extern void {tsym}();"
    return None


_MACRO_BODIES = None
_DEST_CACHE = {}
_FLEET_CACHE = {}


def _all_macro_bodies(header="src/shared/engine_core.h"):
    """{name: de-macroized body} for every DEFINE_<name>() in engine_core.h, parsed in ONE pass
    (macro_body() re-scans the 57k-line header per name — fine for one seed, quadratic for all)."""
    global _MACRO_BODIES
    if _MACRO_BODIES is None:
        _MACRO_BODIES = {}
        h = seed_file_text(header)
        lines = h.split("\n")
        i = 0
        while i < len(lines):
            m = re.match(r'^[ \t]*#define\s+DEFINE_(\w+)\s*\(\s*\)\s*\\\s*$', lines[i])
            if m:
                out = []
                j = i + 1
                while j < len(lines):
                    ln = lines[j].rstrip()
                    cont = ln.endswith("\\")
                    out.append(ln[:-1].rstrip() if cont else ln)
                    j += 1
                    if not cont:
                        break
                _MACRO_BODIES[m.group(1)] = "\n".join(out)
                i = j
            else:
                i += 1
    return _MACRO_BODIES


def _file_scope_only(text):
    """text with every brace-enclosed region blanked (length-preserving) — so a decl search sees
    FILE-scope declarations only. WHY (S59, measured): the TUs are full of BLOCK-scope externs
    inside banked bodies (`void f(){ extern short D_x; … }` — the §63 per-fn override idiom), and
    a flat regex over the TU adopted one of those (`extern short D_801B9DF8;`) as "the destination
    spelling" while the TU's true file scope (a DEFINE_ macro body) says `extern s32 D_801B9DF8;`
    — the drafted file-scope `short` then conflicts and cc1 rejects the TU with the byte-correct
    body in it (func_8018067C@ov_SC04_018, one of 12 stranded on exactly this)."""
    out, depth = [], 0
    for c in text:
        if c == "{":
            depth += 1
            out.append(c)
        elif c == "}":
            depth = max(0, depth - 1)
            out.append(c)
        else:
            out.append(c if depth == 0 or c == "\n" else " ")
    return "".join(out)


def dest_scope(path):
    """The member's HOME TU text with its DEFINE_x() engine-core instantiations EXPANDED — what the
    TU's file scope actually contains at the splice point (S59).

    Two prior scopes were both wrong, measured on consecutive batches:
      * the WHOLE-BINARY concat adopted `extern void func_8012BD14(s32)` from eleven sibling TUs
        into a TU that never declares it (and C scope is the TU — a sibling's decl neither
        conflicts nor rescues), while its bulk also vetoed typedefs the home TU needs;
      * the RAW home-TU text missed every declaration living inside an instantiated DEFINE_ macro
        — which is where a dedup'd caller's `extern void f(void);` actually sits, i.e. the exact
        decl the draft must agree with (the func_80162CCC conflict was at engine_core.h:57282,
        inside a macro the TU instantiates)."""
    if path not in _DEST_CACHE:
        txt = open(path).read() if path and os.path.isfile(path) else ""
        mb = _all_macro_bodies()
        extra = [mb[n] for n in re.findall(r'^\s*DEFINE_(\w+)\s*\(\s*\)', txt, re.M) if n in mb]
        _DEST_CACHE[path] = _file_scope_only(txt + "\n" + "\n".join(extra))
    return _DEST_CACHE[path]


TYPES_H = "src/shared/engine_types.h"


def typedef_block(text, name):
    """The FULL (possibly multi-line) `typedef struct {...} NAME;` for NAME, brace-matched.

    The shared types (`MATRIX`, `SVECTOR`, …) live in engine_types.h, which the `md_*` TUs do not
    include — the `ov_*` ones reach them through engine_core.h. A draft using one in an md module
    dies as `parse error before 'm1'`, which is what 4 of the 9 func_8017D290 members did."""
    m = re.search(rf'^[ \t]*typedef\s+(?:struct|union|enum)\b[^\n]*?\{{', text, re.M)
    for m in re.finditer(r'^[ \t]*typedef\s+(?:struct|union|enum)\b[^;{]*\{', text, re.M):
        i = text.index('{', m.start())
        depth = 0
        for j in range(i, len(text)):
            if text[j] == '{':
                depth += 1
            elif text[j] == '}':
                depth -= 1
                if depth == 0:
                    end = text.find(';', j)
                    blk = text[m.start():end + 1]
                    if re.search(rf'\}}\s*{re.escape(name)}\s*;\s*$', blk):
                        return blk
                    break
    return None


def shared_types_for(body, dest_text):
    """Shared typedefs the body NAMES, the destination lacks, and engine_types.h defines."""
    if not os.path.exists(TYPES_H):
        return []
    types = open(TYPES_H).read()
    out = []
    for m in re.finditer(r'\}\s*([A-Za-z_]\w*)\s*;', types):
        n = m.group(1)
        if re.search(rf'\b{re.escape(n)}\b', body) and not re.search(rf'\b{re.escape(n)}\b', dest_text):
            blk = typedef_block(types, n)
            if blk and blk not in out:
                out.append(blk)
    return out


def typedefs_for(body, seed_text, dest_text):
    """Single-line seed typedefs the body NAMES and the destination TU does not already define.

    Re-emitting a typedef the destination already has is a hard error in C89, and that is one of
    the `redef` rows in the sweep's failure ledger — so the destination gets a veto."""
    out = []
    # Two forms, and the braced one must NOT stop at the `;` INSIDE its braces — the naive
    # `typedef[^;]*;` captures `typedef struct { u8 c[8];` and names the field, not the type.
    for pat in (r'^[ \t]*typedef\s+(?:struct|union|enum)\b[^\n]*?\}\s*([A-Za-z_]\w*)\s*;',
                r'^[ \t]*typedef\s+[^\n{};]*?\b([A-Za-z_]\w*)\s*;'):
        for m in re.finditer(pat, seed_text, re.M):
            name = m.group(1)
            if re.search(rf'\b{re.escape(name)}\b', body) and \
               not re.search(rf'\b{re.escape(name)}\s*;', dest_text) and \
               m.group(0).strip() not in out:
                out.append(m.group(0).strip())
    return out


_NARROW = re.compile(r'\b(char|short|signed\s+char|unsigned\s+char|unsigned\s+short|s8|u8|s16|u16|float|f32)\b')


def kr_definition(body, name):
    """Convert the member's ANSI definition to the K&R form when every param is promotion-safe.

    WHY (P31 S59, byte-proven func_80162CCC@ov_MAIN_012 via rtu_match then the whole-binary gate).
    16 of the 117 staged drafts of the 21:04 pass carried a byte-correct body (match_one MATCH) and
    still failed the gate. The chain, measured on the real TU: the destination TU and 42 DEFINE_
    macros in engine_core.h declare the member `extern void f(void);` — the original code calls it
    K&R-style with no args. gate_stage's arity pre-pass relaxes those DECLS to no-proto, but the
    draft's ANSI definition `void f(u8 *a0)` then establishes a prototype, and the TU's own empty
    call sites `f()` die as `too few arguments` — cc1 rejects the TU and the gate can never see the
    bytes. A K&R definition establishes NO prototype, so the empty calls stay legal (§99: the
    zero-blast-radius def-side fix).

    Codegen-neutral ONLY for promotion-safe params (pointers, int-width scalars): a K&R narrow
    param (u8/s16 by value) is promoted and compiles DIFFERENTLY from its ANSI form (§43/§102), and
    the seed banked in the ANSI form — so narrow-param definitions are left as the seed wrote them
    and take their chances with the gate exactly as before. Any parse doubt (fn-ptr param, array)
    also bails to the untouched body: this transform must only ever widen compatibility."""
    m = re.search(rf'^([^\n=;]*?\b{re.escape(name)}\s*)\(([^;{{)]*)\)(\s*\{{)', body, re.M)
    if not m:
        return body
    params = m.group(2).strip()
    if params in ("", "void"):
        return body[:m.start()] + m.group(1) + "()" + m.group(3) + body[m.end():]
    names, decls = [], []
    for p in (x.strip() for x in params.split(",")):
        pm = re.match(r'^((?:const\s+|volatile\s+|unsigned\s+|signed\s+|struct\s+[A-Za-z_]\w*\s+'
                      r'|[A-Za-z_]\w*\s+)+[\s\*]*)([A-Za-z_]\w*)$', p)
        if not pm:
            return body                                   # unparsed shape: keep ANSI
        if "*" not in pm.group(1) and _NARROW.search(pm.group(1)):
            return body                                   # narrow by-value: K&R would change codegen
        names.append(pm.group(2))
        decls.append(p + ";")
    kr = "%s(%s)\n%s\n%s" % (m.group(1), ", ".join(names), "\n".join(decls), m.group(3).strip())
    return body[:m.start()] + kr + body[m.end():]


def build_draft(body, seed_name, member_name, renames, seed_text, dest_text,
                already_self_contained=False, member_asm=None, fleet_text=""):
    """-> (draft_text, skipped_reason). Renames are applied SIMULTANEOUSLY (one pass), so a chain
    like D_A->D_B, D_B->D_C can never cascade."""
    keys = sorted((k for k in renames if k != seed_name), key=len, reverse=True)
    pat = re.compile(r'\b(' + '|'.join(re.escape(k) for k in keys) + r')\b') if keys else None
    new_body = pat.sub(lambda m: renames[m.group(1)], body) if pat else body
    new_body = re.sub(rf'\b{re.escape(seed_name)}\b', member_name, new_body, flags=re.I)
    # R32: assert the DEFINITION, not merely the name. The seed name used to be recovered by
    # scanning the body for the first `func_XXXXXXXX(` token — which in a de-macroized body is the
    # first EXTERN DECLARATION, not the definition. That renamed a callee to the member's name and
    # left the definition under the seed's, and the draft linked with `undefined reference to
    # <member>`: a full binary build spent to learn what one regex knows.
    if not re.search(rf'^[^\n=;]*\b{re.escape(member_name)}\s*\([^;]*\)\s*\{{', new_body, re.M):
        return None, "no definition of the member after rename (seed-name misidentified?)"

    # NO VERBATIM-ASM BODIES (Drew, P31 S59). A seed whose body is a raw `__asm__(".set noreorder"…)`
    # block (§265) transcribes instructions rather than decompiling them. Remapping one produces a
    # draft that trivially "MATCHes" the local oracle — it IS the target's bytes — and, if it banks,
    # counts as a matched function in every progress number we quote while nothing was decompiled.
    # 26 of 188 staged drafts (14%) were this shape. §265 is a deliberate escape hatch for
    # hand-written asm, used by a human who knows what it costs; it must not be a thing an
    # unattended lane propagates across a family.
    if re.search(r'__asm__\s*(__volatile__\s*)?\(', new_body) and '.set' in new_body:
        return None, "seed body is a verbatim __asm__ block (§265) — not decompiled C, refusing to propagate"

    # K&R the definition (promotion-safe params only; see kr_definition's docstring for the
    # byte-proof). Done AFTER the definition-assert so the regex there sees the ANSI form.
    new_body = kr_definition(new_body, member_name)

    # BLOCK-SCOPE externs the seed body carries can CONFLICT with the destination's file scope
    # (`extern short D_801B9DF8;` in the body vs the TU macro's file-scope `extern s32 …` —
    # cc1 rejects a block decl that diverges from a visible file-scope one, measured S59 on
    # func_8018067C@ov_SC04_018). When every use of the symbol is ADDRESS-ONLY (`&sym`), the type
    # is codegen-irrelevant, so adopt the destination's spelling in place; a valued use keeps the
    # seed's spelling (its type drives the emitted opcode) and takes its chances at the gate.
    for bm in list(re.finditer(r'^([ \t]+)(extern\s+[A-Za-z_][^\n;{}]*?\b([A-Za-z_]\w*)\s*;)[ \t]*$',
                               new_body, re.M)):
        s2 = bm.group(3)
        dm = re.search(rf'^[ \t]*extern[^\n;]*\b{re.escape(s2)}\b[^\n;]*;', dest_text, re.M)
        if not dm:
            continue
        dd = dm.group(0).strip().rstrip("\\").strip()
        if dd.split() == bm.group(2).strip().split():
            continue                                             # same spelling already
        addr_only = True
        for u in re.finditer(rf'\b{re.escape(s2)}\b', new_body):
            before = new_body[:u.start()].rstrip()
            line_start = new_body.rfind("\n", 0, u.start()) + 1
            if "extern" in new_body[line_start:u.start()]:
                continue                                         # the decl itself
            if not before.endswith("&"):
                addr_only = False
                break
        if addr_only:
            new_body = new_body.replace(bm.group(0), bm.group(1) + dd, 1)

    if already_self_contained:
        # A de-macroized body already carries its own externs; synthesizing a second set would
        # re-declare every one of them.
        return new_body + "\n", None

    decls, missing = [], []
    for s in sorted(ASF.syms_in_text(new_body)):
        if s == member_name:
            continue
        old = next((k for k, v in renames.items() if v == s), s)
        data = dlabel_bytes(member_asm, s)
        if data is not None:
            d = data_def_for(old, s, seed_text, data)
            if d is None:
                return None, f"data lives in the member's own .s and its initializer is not a flat byte list: {s}"
            decls.append(d)
            continue
        d = decl_for(old, seed_text, dest_text, body=new_body, fleet_text=fleet_text, target_sym=s)
        if d is None:
            # No decl in the seed — but if the DESTINATION already declares it, none is needed.
            # Refusing here cost 55 macro-seeded members whose definition references a symbol the
            # destination TU knows perfectly well (R32 should refuse the UNKNOWN, not the
            # already-satisfied). The match must be a REAL declaration or definition: the old
            # optional-keyword form ('(extern|const|static)?[^;]*sym[^;]*;') also matched the
            # TU's own `INCLUDE_ASM("...", sym);` stub line and bare CALL statements — so a draft
            # taking sym's ADDRESS shipped with no extern at all and died in the real TU as
            # `sym undeclared (first use)` (S59, func_80180F1C@ov_SC03_002 using func_8018118C
            # as a function-pointer value while the TU merely stubs it).
            if re.search(rf'^[ \t]*extern[^\n;]*\b{re.escape(s)}\b[^\n;]*;', dest_text, re.M) or \
               re.search(rf'^[ \t]*(?:const\s+|static\s+|volatile\s+)*[A-Za-z_]\w+[\s\*]+'
                         rf'{re.escape(s)}\s*[\[=;(]', dest_text, re.M):
                continue
            missing.append(s)
            continue
        decls.append(re.sub(rf'\b{re.escape(old)}\b', s, d))
    if missing:
        # R32: a draft missing a declaration is a KNOWN-BAD draft. Don't spend a build on it.
        return None, "no seed decl for " + ",".join(missing[:3])

    pre = (shared_types_for(new_body, dest_text)
           + typedefs_for(new_body, seed_text, dest_text) + sorted(set(decls)))
    return "\n".join(pre) + "\n\n" + new_body + "\n", None


def _local_verdict(fn, text, sub, o0):
    """('match'|'near'|None, closeness) from match_one on a draft variant — the LOCAL adjudicator
    for ordinal-ambiguous IMM pairings (S59). Advisory only: the whole-binary gate stays the sole
    arbiter (G3/P9); this merely picks WHICH candidate to spend the build on."""
    d = os.path.join(".run", "aprop_mo")
    os.makedirs(d, exist_ok=True)
    p = os.path.join(d, fn + ".c")
    open(p, "w").write(text)
    cmd = [".venv/bin/python", "tools/match_one.py", fn, "--c", p, "--asm-subdir", sub, "--json"]
    if o0:
        cmd += ["--o0"]
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, timeout=180)
        j = json.loads([l for l in r.stdout.strip().splitlines() if l.strip()][-1])
        return j.get("status"), j.get("closeness")
    except Exception:
        return None, None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--cards", default=CARDS)
    ap.add_argument("--outdir", default=".run/aprop_autodraft")
    ap.add_argument("--slate", default=".run/aprop_autodraft_slate.json")
    ap.add_argument("--only", help="restrict to these family exemplar addrs (comma-separated)")
    ap.add_argument("--limit", type=int, default=0, help="cap the number of drafts emitted")
    ap.add_argument("--max-sites", type=int, default=0, help="skip members with more diff sites")
    ap.add_argument("--allow-impure", action="store_true",
                    help="also draft IMM/STRUCT members (a rename cannot fix either — measured 0/5)")
    a = ap.parse_args()

    cards = json.load(open(a.cards))
    want = set(x.lower() for x in a.only.split(",")) if a.only else None
    skip = collections.Counter()
    slate = []
    for c in cards:
        if want and c["family"].lower() not in want:
            continue
        seed = c["seed"]
        sb = FC.seed_body_ref(seed["binary"], int(seed["addr"], 16))
        body, seed_text, kind = seed_body(sb, seed["name"])
        if not body:
            skip[f"seed body not extractable ({kind})"] += len(c["members"])
            continue
        seed_words = FR.stream_words(seed["binary"], int(seed["addr"], 16), c["nins"])
        for m in c["members"]:
            if a.limit and len(slate) >= a.limit:
                break
            if a.max_sites and m["n_sites"] > a.max_sites:
                skip["over --max-sites"] += 1
                continue
            stubs = corpus.stubs(m["binary"])
            home = next((s for s in stubs.values() if s.symbol.lower() == m["name"].lower()), None)
            if home is None:
                skip["already banked"] += 1
                continue
            # THE SELECTOR (S50, measured): a symbol rebase can only ever fix a RELOC diff. An IMM
            # (per-location literal) or a STRUCT (register/opcode drift) site needs a real edit, and
            # drafting one spends a full binary build to learn what classify_member already knows —
            # the first 5 such members gated 0/5, every one IMM or STRUCT.
            sib_words = FR.stream_words(m["binary"], int(m["addr"], 16), c["nins"])
            cls, _pos = FR.classify_member(seed_words, sib_words)
            if cls == "STRUCT" and not a.allow_impure:
                skip["not templatable (STRUCT: register/opcode drift needs a real edit)"] += 1
                continue
            member_body, imm_map, alt_bodies = body, {}, []
            if cls == "IMM":
                # T2a's immediate engine resolves a per-location LITERAL the same way symbol_map
                # resolves a per-location symbol. Measured: 131 of 275 IMM members resolve with no
                # unresolved sites — the rest genuinely need an edit.
                imm_map, unresolved, member_body, alt_bodies = FR.imm_map_tier1(
                    body, seed_words, sib_words, want_alts=True)
                if unresolved and not a.allow_impure:
                    skip[f"IMM unresolved ({unresolved[0][1]})"] += 1
                    continue
                if not imm_map and member_body == body and not alt_bodies:
                    skip["IMM with no resolvable literal edit"] += 1
                    continue
            ren, err = FR.symbol_map(int(seed["addr"], 16), seed["binary"],
                                     m["binary"], int(m["addr"], 16))
            if err:
                skip["symbol_map: " + err.split("(")[0].strip()] += 1
                continue
            # THE HOME TU ONLY, macro-expanded (S59). C scope is the TU: a decl in a sibling TU of
            # the same overlay can neither conflict with nor rescue the splice, and the whole-binary
            # concat both adopted spellings the home TU never declares AND vetoed typedefs the home
            # TU needs. dest_scope() expands the TU's DEFINE_x() instantiations so the decls INSIDE
            # engine-core macros (where the dedup'd callers' externs actually live) are visible.
            dest = dest_scope(home.path)
            # sibling-TU spellings, as a LAST-RESORT decl source only (see decl_for's borrow tier)
            if m["binary"] not in _FLEET_CACHE:
                _FLEET_CACHE[m["binary"]] = "".join(
                    open(p).read() for p in sorted(glob.glob(f"src/{m['binary']}/*.c")))
            fleet = _FLEET_CACHE[m["binary"]]
            if imm_map:
                member_body = FR.apply_remap(member_body, imm_map)
            draft, why = build_draft(member_body, sb.get("name") or seed["name"],
                                     m["name"], ren, seed_text, dest,
                                     already_self_contained=False,
                                     member_asm=corpus.asm_path(m["binary"], m["name"]),
                                     fleet_text=fleet)
            if draft is None:
                skip[why.split(" for ")[0]] += 1
                continue
            # ORDINAL-AMBIGUOUS IMM: adjudicate the candidate pairings with the LOCAL compile
            # oracle before spending a whole-binary build (S59). No static pairing is right for
            # every shape (`*(p + OFF) = VAL` names OFF first, gcc emits VAL first — 35 of the
            # 21:04 pass's 117 staged drafts shipped with the two swapped, closeness-2 forever).
            # match_one is seconds; the gate is minutes; the gate remains the sole arbiter.
            if alt_bodies:
                variants = [draft]
                for ab in alt_bodies:
                    ab2 = FR.apply_remap(ab, imm_map) if imm_map else ab
                    dtext, _w = build_draft(ab2, sb.get("name") or seed["name"],
                                            m["name"], ren, seed_text, dest,
                                            already_self_contained=False,
                                            member_asm=corpus.asm_path(m["binary"], m["name"]),
                                            fleet_text=fleet)
                    if dtext:
                        variants.append(dtext)
                if len(variants) > 1:
                    o0 = corpus.is_o0(home.path)
                    best, bestcl = None, None
                    for vt in variants:
                        st_, cl_ = _local_verdict(m["name"], vt, m["sub"], o0)
                        if st_ == "match":
                            best = vt
                            break
                        if st_ == "near" and cl_ is not None and (bestcl is None or cl_ < bestcl):
                            best, bestcl = vt, cl_
                    if best is not None:
                        draft = best
            # STATIC PRE-CHECKS (S50): both classes below were measured as real build failures and
            # both are decidable without compiling. Negative-controlled against all 205 banked
            # drafts of run 1: zero false positives; catches 39 of 67 known failures.
            syms = ASF.syms_in_text(draft)
            bad = (PRE.arity_conflicts(draft, dest, syms, self_name=m["name"])
                   + PRE.undefined_data(m["binary"], dest, syms, self_name=m["name"], body=draft))
            if bad and not a.allow_impure:
                skip["pre-check: " + bad[0].split("(")[0]] += 1
                continue
            d = os.path.join(a.outdir, m["binary"])
            os.makedirs(d, exist_ok=True)
            p = os.path.join(d, m["name"] + ".c")
            open(p, "w").write(draft)
            slate.append(dict(fn=m["name"], binary=m["binary"], sub=m["sub"], draft=p,
                              family=c["family"], n_sites=m["n_sites"], seed_kind=kind))

    json.dump(slate, open(a.slate, "w"), indent=1)
    total = sum(len(c["members"]) for c in cards if not want or c["family"].lower() in want)
    print(f"drafted {len(slate)} of {total} members -> {a.outdir}")
    for k, v in skip.most_common():                        # R32: name every skip, never drop silently
        print(f"  skipped {v:5}  {k}")
    print(f"slate: {a.slate}")


if __name__ == "__main__":
    main()

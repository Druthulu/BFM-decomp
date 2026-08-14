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
import argparse, collections, glob, json, os, re, sys

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


def decl_for(sym, seed_text):
    """A file-scope declaration for `sym` taken from the SEED's own TU, normalised to an `extern`.

    A definition (`const Blk8 D_801EF6C0 = {...}`) must become a DECLARATION in the member — the
    member's own TU already emits those bytes (as `INCLUDE_RODATA`, or inside the function's own
    `.s`). Emitting the definition instead would either duplicate the data or fight splat for the
    address."""
    m = re.search(rf'^[ \t]*extern[^\n;]*\b{re.escape(sym)}\b[^\n;]*;', seed_text, re.M)
    if m:
        return m.group(0).strip()
    m = re.search(rf'^[ \t]*((?:const\s+|static\s+|volatile\s+)*[A-Za-z_]\w*[\s\*]+)'
                  rf'{re.escape(sym)}\b(\s*\[[^\]]*\])?\s*=', seed_text, re.M)
    if m:
        return f"extern {m.group(1).strip()} {sym}{m.group(2) or ''};".replace("static ", "")
    m = re.search(rf'^[ \t]*[A-Za-z_][\w \*]*\b{re.escape(sym)}\s*\([^;{{]*\)\s*;', seed_text, re.M)
    return m.group(0).strip() if m else None


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


def build_draft(body, seed_name, member_name, renames, seed_text, dest_text,
                already_self_contained=False, member_asm=None):
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
        d = decl_for(old, seed_text)
        if d is None:
            # No decl in the seed — but if the DESTINATION already declares it, none is needed.
            # Refusing here cost 55 macro-seeded members whose definition references a symbol the
            # destination TU knows perfectly well (R32 should refuse the UNKNOWN, not the
            # already-satisfied).
            if re.search(rf'^[ \t]*(extern|const|static)?[^\n;]*\b{re.escape(s)}\b[^\n;]*;',
                         dest_text, re.M):
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
            if not any(s.symbol.lower() == m["name"].lower() for s in stubs.values()):
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
            member_body, imm_map = body, {}
            if cls == "IMM":
                # T2a's immediate engine resolves a per-location LITERAL the same way symbol_map
                # resolves a per-location symbol. Measured: 131 of 275 IMM members resolve with no
                # unresolved sites — the rest genuinely need an edit.
                imm_map, unresolved, member_body = FR.imm_map_tier1(body, seed_words, sib_words)
                if unresolved and not a.allow_impure:
                    skip[f"IMM unresolved ({unresolved[0][1]})"] += 1
                    continue
                if not imm_map and member_body == body:
                    skip["IMM with no resolvable literal edit"] += 1
                    continue
            ren, err = FR.symbol_map(int(seed["addr"], 16), seed["binary"],
                                     m["binary"], int(m["addr"], 16))
            if err:
                skip["symbol_map: " + err.split("(")[0].strip()] += 1
                continue
            dest = "".join(open(p).read() for p in sorted(glob.glob(f"src/{m['binary']}/*.c")))
            if imm_map:
                member_body = FR.apply_remap(member_body, imm_map)
            draft, why = build_draft(member_body, sb.get("name") or seed["name"],
                                     m["name"], ren, seed_text, dest,
                                     already_self_contained=False,
                                     member_asm=corpus.asm_path(m["binary"], m["name"]))
            if draft is None:
                skip[why.split(" for ")[0]] += 1
                continue
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

#!/usr/bin/env python3
"""Split a Sony PSYLINK library archive (LIB\\x01) into its member LNK objects.

Format (derived from PsyQ 4.0 LIBCD.LIB, Phase 7):
    "LIB\\x01"
    per member:
        name[8]        space-padded object name (e.g. "CDROM   ")
        date[4]        little-endian timestamp
        obj_off[4]     little-endian: bytes from THIS member header to its LNK object
        <symbol dictionary>   (obj_off - 16 bytes: the symbols this object exports)
        <LNK object>          starts with "LNK\\x02", runs to the next member header

We don't parse the LNK record stream to find each object's end; instead each member
header is located by the invariant  u32@(header+12) == (LNK_offset - header)  — i.e.
obj_off points exactly at that member's "LNK\\x02". An object therefore spans from its
"LNK\\x02" to the NEXT member header (or EOF for the last). psyq-obj-parser validates
the result downstream (a wrong boundary fails to parse), and the ultimate check is the
byte-match of the linked function against the target EXE.

Usage:  psyq_lib_split.py <archive.LIB> <out_dir>   ->  writes <out_dir>/<NAME>.obj
"""
import struct, sys, os

LNK_MAGIC = b"LNK\x02"

def split(lib_path, out_dir):
    d = open(lib_path, "rb").read()
    if d[:4] != b"LIB\x01":
        sys.exit(f"{lib_path}: not a LIB\\x01 archive (magic {d[:4]!r})")
    # 1) all LNK object starts
    lnk = []
    i = d.find(LNK_MAGIC, 4)
    while i != -1:
        lnk.append(i)
        i = d.find(LNK_MAGIC, i + 4)
    if not lnk:
        sys.exit(f"{lib_path}: no LNK objects found")
    # 2) each LNK's member header: scan back for P with u32@P+12 == lnk-P
    headers = []
    for L in lnk:
        P = None
        for cand in range(L - 16, max(L - 0x8000, 0) - 1, -1):
            if struct.unpack_from("<I", d, cand + 12)[0] == L - cand:
                # sanity: name bytes printable-ish
                nm = d[cand:cand + 8]
                if all(32 <= c < 127 for c in nm.rstrip(b" \x00") or b" "):
                    P = cand; break
        if P is None:
            sys.exit(f"{lib_path}: could not locate member header for LNK@0x{L:x}")
        headers.append(P)
    # 3) extract: object k = [lnk[k] : headers[k+1]]  (EOF for last)
    os.makedirs(out_dir, exist_ok=True)
    members = []
    for k, L in enumerate(lnk):
        end = headers[k + 1] if k + 1 < len(headers) else len(d)
        name = d[headers[k]:headers[k] + 8].rstrip(b" \x00").decode("ascii", "replace")
        # uniquify (PSYLIB names are unique, but be safe)
        obj = d[L:end]
        out = os.path.join(out_dir, f"{name}.obj")
        n = 1
        while os.path.exists(out):
            out = os.path.join(out_dir, f"{name}_{n}.obj"); n += 1
        open(out, "wb").write(obj)
        members.append((name, len(obj)))
    return members

if __name__ == "__main__":
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    ms = split(sys.argv[1], sys.argv[2])
    print(f"{os.path.basename(sys.argv[1])}: {len(ms)} objects -> {sys.argv[2]}")
    for nm, sz in ms[:8]:
        print(f"  {nm}.obj  ({sz} B)")
    if len(ms) > 8:
        print(f"  … +{len(ms)-8} more")

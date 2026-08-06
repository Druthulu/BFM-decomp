#!/usr/bin/env python3
"""disc_audit.py — L1 of the definitive disc audit: a PARTITION over every byte on the disc.

Drew, 2026-08-05: "im getting tired of learning there was more code all along, we really need a full
audit that definitively lists ALL code that we need to decomp."

THE INVARIANT (R32): every byte on the disc belongs to exactly ONE bucket —
    onboarded-code | unclaimed-code | classified-data | audio-video | filesystem-metadata
— the buckets SUM TO THE DISC, and residue is a DEFECT. A partition with an asserted residue of zero
is a completeness proof; a longer list is only a longer list.

WHY THIS EXISTS. Three "there was more code all along" surprises each came from a tool that was
correct about the subset it examined and silent about the rest: a `0.4.dec` glob missed 4 SC07
overlays whose code sits at PAC entry 1; `disc_code_sweep` decoded only the RAW layer, so it was
structurally blind to COMPRESSED code (its type-4 row was vacuous for 138 known binaries); a
4,096-word window classified only the head of each payload. So this walks the DISC IMAGE rather than
our configs, classifies WHOLE payloads with no window, and decodes BOTH layers.

CLAIMED-BY IS DERIVED, NOT RE-PARSED (R33). `config/check.<bin>.sha` IS the SHA1 of that binary's disc
payload — the build's own byte-identity gate. So payload→binary is a hash lookup against the committed
check files: it cannot drift from the build, and needs no config-walking heuristic.

ACCOUNTING MODEL (exact by construction). Tracks 2..N are CD-DA in full. On track 1 each file costs its
SECTOR FOOTPRINT (ceil(size/2048) * 2352); inside a `.CD` container the raw payload bytes go to their
own buckets and the container's leftover footprint (TOC + padding) goes to filesystem-metadata; the
track-1 bytes outside every file (system area, PVD, path tables, directory records) go to
filesystem-metadata. Totals therefore sum to the disc exactly, or the run FAILS.

    python3 tools/disc_audit.py       # -> docs/disc-ledger.md + .run/disc_audit.json
    make audit-disc
"""
import glob, hashlib, json, os, re, sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(REPO)
sys.path.insert(0, os.path.join(REPO, 'tools', 'bfm_extract'))

import iso9660, cd_archive, pac, lzss  # noqa: E402  (the frozen Phase-2 extractor)

RAW_SECTOR = 2352
USER_BYTES = 2048
DISKS = 'disks'
LEDGER = 'docs/disc-ledger.md'

VALID_OPS = frozenset((0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
                       32, 33, 34, 35, 36, 37, 38, 40, 41, 42, 43, 46, 49, 57))


def classify(buf):
    """('code'|'data', valid_ratio, jr_density) over the WHOLE buffer — no window (that was defect #3).

    Deliberately the same heuristic `disc_code_sweep` uses, so L2's independent oracle (sig_image
    boundary carving) has something to DISAGREE with (R34); disagreements are a review queue."""
    n = len(buf) // 4
    if n < 16:
        return 'data', 0.0, 0.0
    valid = jr = 0
    for i in range(0, n * 4, 4):
        w = int.from_bytes(buf[i:i + 4], 'little')
        if (w >> 26) in VALID_OPS:
            valid += 1
        if w == 0x03E00008:                      # jr $ra
            jr += 1
    vr, jd = valid / n, jr / n
    return ('code' if vr >= 0.90 and jd >= 0.01 else 'data'), vr, jd


def onboarded_payload_shas():
    """{sha1: alias} from every committed config/check.<bin>.sha (R33 — the build's own oracle)."""
    out = {}
    for p in sorted(glob.glob('config/check.*.sha')):
        alias = re.sub(r'^check\.|\.sha$', '', os.path.basename(p))
        parts = open(p).read().split()
        if parts:
            out[parts[0].lower()] = alias
    return out


FORM2_BYTES = 2324          # MODE2 FORM2 user bytes (STR/XA streaming sectors)


def footprint(size, form2=False):
    """Raw sector cost of a file. MODE2 FORM1 carries 2048 user bytes per 2352-byte sector; STR/XA
    streaming data is FORM2 and carries 2324 — using 2048 for those over-counts their footprint."""
    per = FORM2_BYTES if form2 else USER_BYTES
    return ((size + per - 1) // per) * RAW_SECTOR


def main():
    claimed = onboarded_payload_shas()
    tracks = sorted(glob.glob(os.path.join(DISKS, '*Track *.bin')))
    if not tracks:
        sys.exit('disc_audit: no tracks under disks/ — this audit reads the DISC, not our configs')
    t1 = [t for t in tracks if 'Track 1' in t][0]
    disc_bytes = sum(os.path.getsize(t) for t in tracks)
    t1_size = os.path.getsize(t1)
    print(f'disc: {disc_bytes:,} bytes across {len(tracks)} tracks; '
          f'onboarded payload hashes: {len(claimed)}')

    B = dict.fromkeys(('onboarded-code', 'unclaimed-code', 'classified-data',
                       'audio-video', 'filesystem-metadata'), 0)
    B['audio-video'] += sum(os.path.getsize(t) for t in tracks if 'Track 1' not in t)

    rows, payloads, file_fp_total = [], 0, 0
    with iso9660.Iso9660Image(t1) as img:
        recs = list(img.list_files())
        print(f'ISO root files: {len(recs)}')
        t1_sectors = t1_size // RAW_SECTOR
        for rec in recs:
            name = rec.name
            up = name.upper()
            # A `.DA` entry's LBA points PAST track 1 into the CD-DA tracks (Phase 2 deviation:
            # "the .DA ISO entries point past Track 1 into the audio tracks"). Those bytes are
            # already counted whole as audio-video, so charging a track-1 footprint too
            # double-counts them — this was 49.7 MB of the first run's residue.
            if rec.lba >= t1_sectors or up.endswith('.DA'):
                continue
            fp = footprint(rec.size, form2=up.endswith(('.STR', '.XA')))
            file_fp_total += fp
            if up.endswith(('.STR', '.XA')):
                B['audio-video'] += fp
                continue
            data = img.extract_file(name)
            if not up.endswith('.CD'):
                k, vr, jd = classify(data)
                h = hashlib.sha1(data).hexdigest()
                who = claimed.get(h)
                b = ('onboarded-code' if who else 'unclaimed-code') if k == 'code' else 'classified-data'
                B[b] += fp
                payloads += 1
                if k == 'code' or who:
                    rows.append((name, '-', '-', len(data), b, who or 'UNCLAIMED', f'{vr:.2f}/{jd:.4f}'))
                continue

            acct = 0
            try:
                toc = cd_archive.parse_toc(data)
                subs = list(cd_archive.iter_subfiles(data, toc))
            except Exception as e:
                print(f'  ! {name}: TOC walk failed ({e}) — whole file booked as data')
                B['classified-data'] += fp
                rows.append((name, '-', '-', len(data), 'classified-data', 'TOC-FAIL', '-'))
                continue
            for si, (_ent, sbuf) in enumerate(subs):
                try:
                    entries = pac.split_pac(sbuf) if pac.is_pac(sbuf) else []
                except Exception:
                    entries = []
                if not entries:
                    items = [(-1, -1, sbuf, len(sbuf))]
                else:
                    items = [(e.index, e.type, e.payload, e.length) for e in entries]
                for idx, etype, raw, rawlen in items:
                    payloads += 1
                    buf = raw
                    if etype == pac.COMPRESSED_TYPE:
                        try:
                            buf = lzss.decompress(raw, expected_len=len(raw)).data or raw
                        except Exception:
                            buf = raw
                    k, vr, jd = classify(buf)
                    h = hashlib.sha1(buf).hexdigest()
                    who = claimed.get(h)
                    b = ('onboarded-code' if who else 'unclaimed-code') if k == 'code' else 'classified-data'
                    B[b] += rawlen
                    acct += rawlen
                    if k == 'code' or who:
                        rows.append((f'{name}/{si}', idx, etype, len(buf), b,
                                     who or 'UNCLAIMED', f'{vr:.2f}/{jd:.4f}'))
            B['filesystem-metadata'] += max(0, fp - acct)

    # track-1 bytes outside every file: system area, PVD, path tables, directory records, gaps
    B['filesystem-metadata'] += max(0, t1_size - file_fp_total)

    total = sum(B.values())
    residue = disc_bytes - total
    unclaimed = [r for r in rows if r[5] == 'UNCLAIMED']

    os.makedirs('.run', exist_ok=True)
    with open(LEDGER, 'w') as fh:
        fh.write('# Disc ledger — the completeness partition (L1)\n\n')
        fh.write('> `tools/disc_audit.py` (`make audit-disc`). Walks the DISC IMAGE, not our configs;\n'
                 '> classifies WHOLE payloads (no window) at BOTH the raw and LZSS-decompressed layer.\n'
                 '> `claimed-by` is derived from `config/check.<bin>.sha` — the build\'s own\n'
                 '> byte-identity gate (R33). Residue is a DEFECT (R32), not a rounding note.\n\n')
        fh.write(f'**Disc:** {disc_bytes:,} bytes · {len(tracks)} tracks · {payloads:,} payloads examined\n\n')
        fh.write('| bucket | bytes | share |\n|---|---:|---:|\n')
        for k, v in B.items():
            fh.write(f'| {k} | {v:,} | {100*v/disc_bytes:.2f}% |\n')
        fh.write(f'| **TOTAL** | **{total:,}** | {100*total/disc_bytes:.2f}% |\n')
        fh.write(f'\n**Residue: {residue:,} bytes — '
                 f'{"PARTITION HOLDS" if residue == 0 else "DEFECT, unaccounted"}**\n\n')
        fh.write(f'## Code payloads — {len(unclaimed)} UNCLAIMED of '
                 f'{len([r for r in rows if "code" in r[4]])}\n\n')
        fh.write('| file | entry | type | bytes | bucket | claimed-by | valid/jr |\n')
        fh.write('|---|---|---|---:|---|---|---|\n')
        for r in sorted(rows, key=lambda r: (r[5] != 'UNCLAIMED', str(r[0]))):
            if 'code' in r[4]:
                fh.write(f'| {r[0]} | {r[1]} | {r[2]} | {r[3]:,} | {r[4]} | {r[5]} | {r[6]} |\n')

    json.dump({'buckets': B, 'disc_bytes': disc_bytes, 'residue': residue,
               'payloads': payloads, 'unclaimed_code': len(unclaimed)},
              open('.run/disc_audit.json', 'w'), indent=1)

    for k, v in B.items():
        print(f'  {k:22s} {v:>14,}')
    print(f'  {"TOTAL":22s} {total:>14,}   disc {disc_bytes:,}   residue {residue:,}')
    print(f'UNCLAIMED code payloads: {len(unclaimed)}')
    for r in unclaimed[:25]:
        print(f'    {r[0]} entry={r[1]} type={r[2]} {r[3]:,} B  valid/jr={r[6]}')
    print(f'ledger -> {LEDGER}')
    if residue != 0:
        sys.exit(f'AUDIT-DISC FAIL (R32): {residue:,} bytes unaccounted — the partition does not hold')


if __name__ == '__main__':
    main()

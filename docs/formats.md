# On-Disc File Formats — Brave Fencer Musashi (SLUS-00726 USA)

> **Evolvable reference layer.** This file may be updated freely as RE progresses; note each
> change in the active phase log (`CURRENT_PHASE.md`). It is the canonical specification of
> the disc image layout and the game's container/compression formats (.CD, PAC, LZSS, SQV).
> Every entry is tagged with its provenance; anything not byte-verified against the local
> US dump is explicitly marked **UNVERIFIED** or **TBD**. RAM addresses are owned by
> `docs/memory-map.md` (authoritative); they are cross-referenced here, never redefined.

**Primary sources reconciled in this file:**

| Source | What it provides | Trust level |
|---|---|---|
| Local dump `Brave Fencer Musashi (USA)\` (4×.bin + .cue) | All `verified-local` facts (re-parsed 2026-06-10) | Ground truth |
| `tools/brave-CUE/brave.c` + `brave.txt` (CUE, 2012-2013, GPLv3) | Reference extractor: .CD TOC, PAC header, LZSS decoder | Authoritative for tool semantics; **diverges from game semantics on LZSS termination (§4.4)** |
| AiroRom wiki MIPS listing (pleonex) | Game-side LZSS decompressor, byte-verified vs local US EXE | Verified (see memory-map §2.1) |
| jywjyw/bravefencer-hack (Java repacker, 2018) + `doc/note.md` | LIST.CD structure, PAC details, working recompressor, overlay map | **JP (SLPS-01490)** unless noted — re-verify for US |
| romhacking.net thread 15730 (Vehek, Dark Fulgore, Auryn, 2013-2014) | LZSS termination/bias discoveries, US datapoints | Reported, partially re-verified |

---

## 1. Disc layout

### 1.1 BIN/CUE — 4 tracks

From the local `.cue` and track binaries (verified-local):

| Track | Mode | File size (bytes) | Sectors (2352 B raw) | Content |
|---|---|---|---|---|
| 01 | MODE2/2352 | 364,846,944 | 155,122 | Data (ISO9660 volume `MUSASHI`) |
| 02 | AUDIO (CD-DA) | 10,678,080 | 4,540 | `ST01_13A.DA` (see §1.4); INDEX 00 at 00:00:00, INDEX 01 at 00:02:00 |
| 03 | AUDIO (CD-DA) | 7,328,832 | 3,116 | `ST01_13B.DA`; same index layout |
| 04 | AUDIO (CD-DA) | 33,167,904 | 14,102 | `DUMMY_DA.DA`; same index layout |

Volume space size in the PVD = 176,880 sectors = 155,122 + 4,540 + 3,116 + 14,102 exactly
(the ISO volume spans all four tracks) (verified-local).

### 1.2 Track 1 sector geometry

- Raw sectors are 2352 bytes (MODE2). **User data (2048 bytes) begins at raw-sector offset
  +24** (12-byte sync + 4-byte header + 8-byte Mode 2 Form 1 subheader).
- Byte offset of LBA *n*'s user data within `(Track 1).bin` = `n * 2352 + 24`.
- PVD at LBA 16; root directory record at LBA 22 (2048 bytes) (verified-local).

### 1.3 ISO root inventory — 27 files, no directories

Re-parsed from the raw image 2026-06-10 (verified-local). All names carry the `;1` version
suffix on disc; LBA = 2048-byte-sector index from track start; sizes are exact byte lengths
from the directory records.

| File | LBA | Size (bytes) | Notes |
|---|---|---|---|
| SYSTEM.CNF | 23 | 68 | Boot config (§1.5) |
| SLUS_007.26 | 24 | 413,696 | PS-X EXE (§1.6) |
| MUSA.ID | 226 | 9 | Disc-ID check file; contents `MUSASHI\r\n` |
| LIST.CD | 227 | 4,096 | Concatenated .CD TOCs (§2.3) |
| MAIN.CD | 229 | 5,988,352 | Resident/global archive, 49 sub-files (§2.2) |
| LOGOA.STR | 3,153 | 3,080,192 | FMV (out of scope, §7) |
| LOGOB.STR | 4,657 | 3,080,192 | FMV |
| SC01.CD | 6,161 | 20,078,592 | Chapter 1 scenario archive |
| ST01.STR | 15,965 | 12,795,904 | FMV |
| OPEN.STR | 22,213 | 22,724,608 | FMV |
| SC02.CD | 33,309 | 22,126,592 | Chapter 2 scenario archive |
| ST02.STR | 44,113 | 21,430,272 | FMV |
| SC03.CD | 54,577 | 64,569,344 | Chapter 3 scenario archive (largest) |
| ST03.STR | 86,105 | 8,028,160 | FMV |
| SHOPS01.STR | 90,025 | 7,536,640 | FMV |
| OUT.STR | 93,705 | 1,867,776 | FMV |
| SC04.CD | 94,617 | 19,425,280 | Chapter 4 scenario archive |
| ST04.STR | 104,102 | 17,825,792 | FMV |
| SC05.CD | 112,806 | 16,498,688 | Chapter 5 scenario archive |
| ST05.STR | 120,862 | 9,240,576 | FMV |
| SC06.CD | 125,374 | 23,928,832 | Chapter 6 scenario archive |
| ST06.STR | 137,058 | 18,612,224 | FMV |
| SC07.CD | 146,146 | 12,734,464 | Chapter 7 scenario archive |
| END.STR | 152,364 | 5,341,184 | FMV |
| ST01_13A.DA | 155,272 | 8,990,720 | CD-DA pointer → track 2 (§1.4) |
| ST01_13B.DA | 159,812 | 6,074,368 | CD-DA pointer → track 3 |
| DUMMY_DA.DA | 162,928 | 28,573,696 | CD-DA pointer → track 4 (padding audio) |

Observations (verified-local):
- **12 STR files** (not 13 as one earlier planning summary said — that was a miscount;
  this table is the corrected, re-verified inventory). Tally: 12 STR + 3 `.DA` + 12 others
  (SYSTEM.CNF, SLUS_007.26, MUSA.ID, LIST.CD, MAIN.CD, SC01–SC07.CD) = 27.
- STR movies are interleaved between the chapter archives in ascending LBA order
  (seek-distance optimization).
- All `.CD` sizes are exact multiples of 2048.
- Layout is contiguous: e.g. SLUS_007.26 occupies LBA 24–225 (202 sectors), MUSA.ID
  follows at 226; MAIN.CD ends exactly where LOGOA.STR begins.

### 1.4 `.DA` files = directory entries pointing into the CD-DA tracks

Verified by arithmetic in-session (2026-06-10): each `.DA` extent LBA equals the first
INDEX 01 sector of an audio track, and each size equals `(track sectors − 150 pregap) × 2048`
(the directory records use 2048 B/sector accounting even though the underlying sectors are
2352-byte audio):

| File | Extent LBA | Track start (cumulative) | + 150 pregap | Size check |
|---|---|---|---|---|
| ST01_13A.DA | 155,272 | track 2 @ 155,122 | = 155,272 ✓ | (4,540−150)×2048 = 8,990,720 ✓ |
| ST01_13B.DA | 159,812 | track 3 @ 159,662 | = 159,812 ✓ | (3,116−150)×2048 = 6,074,368 ✓ |
| DUMMY_DA.DA | 162,928 | track 4 @ 162,778 | = 162,928 ✓ | (14,102−150)×2048 = 28,573,696 ✓ |

So the `.DA` files contain no data inside track 1; they are the ISO-level handles the game
uses to seek CD-DA audio. They are **out of scope** for the extraction pipeline (§7).

### 1.5 SYSTEM.CNF (68 bytes, verified-local)

```
BOOT = cdrom:\SLUS_007.26;1
TCB = 4
EVENT = 16
STACK = 801ffff0
```

### 1.6 SLUS_007.26 — PS-X EXE header (verified-local)

| Field | Value | Notes |
|---|---|---|
| magic | `PS-X EXE` | |
| `pc0` | 0x80010000 | Entry point |
| `gp0` | 0x00000000 | No $gp in header ⇒ likely −G0; confirm in Phase 6 |
| `t_addr` | 0x80010000 | Image spans 0x80010000–0x80074800 |
| `t_size` | 0x64800 | File = 0x800 header + 0x64800 text = 0x65000 = 413,696 bytes ✓ |
| `sp` | 0x801FFFF0 | Matches SYSTEM.CNF STACK |

The EXE is tiny (~400 KB) relative to a ~340 MB game: the bulk of code/script lives inside
the `.CD` archives as LZSS-compressed PAC type-4 overlays (§3, §4; memory-map §4).

### 1.7 The `\DEBUG.BIN;1` ghost reference

The EXE's CD-path string table (`CdPathTable`, base **0x80062C24**, 23 entries, 0x30-byte
stride — see memory-map §2.2) contains the string **`\DEBUG.BIN;1` at 0x80063044**
(verified-local), adjacent to `\MUSA.ID;1` at 0x80063014. **DEBUG.BIN does not exist on the
retail ISO** (see §1.3). A surviving code path therefore references a debug loader file that
was stripped from the disc — a prime RE anchor (xref the string to find the debug loader;
relates to the TCRF L3 debug menu, memory-map §5).

Also note: the table covers LIST.CD, MAIN.CD, SC01–SC07.CD and ten of the STR movies, but
`LOGOA.STR`/`LOGOB.STR` and the three `.DA` files are absent from it — referenced elsewhere
(**TBD**, memory-map open question #14).

---

## 2. .CD container format

### 2.1 TOC structure (verified-local for MAIN.CD; brave.c is the reference parser)

A `.CD` file begins with a table of contents at offset 0:

| Offset | Type | Meaning |
|---|---|---|
| +0x00 | u32 LE | `count` — number of sub-files (MAIN.CD: 0x31 = 49) |
| +0x04 | u32 LE | zero |
| +0x08 + 8*i | u32 LE | sub-file *i* start, **in 2048-byte sectors relative to the start of the .CD file** |
| +0x0C + 8*i | u32 LE | sub-file *i* length in bytes (unpadded) |

- **The first field of each entry is NOT a disc LBA.** `brave.txt` calls it "LBA", but the
  code in `brave.c::Extract()` proves it is file-relative (`buffer + entry_sector * 0x800`).
  Do not add the `.CD` file's own disc LBA when splitting.
- The TOC and every sub-file are sector-aligned (0x800), zero-padded, and contiguous; the
  first sub-file starts at sector 1 (offset 0x800).
- MAIN.CD and SC01–SC07.CD use this identical format — one code path in every known tool,
  no per-file special-casing (brave.c; confirmed by jywjyw's `Conf.java` rebuilding all 8
  with the same `CdRebuilder`).

### 2.2 Roles of each .CD file

| File | Role | Sub-file count | Provenance |
|---|---|---|---|
| LIST.CD | Concatenated TOCs of the other 8 `.CD`s (§2.3) — **not itself a normal container** | n/a | jywjyw (JP) + partial local check |
| MAIN.CD | Global/resident archive: loader-resident script blob (`FILE_010` PAC entry index 1, type 1), fonts, shared assets | **49** (0x31, verified-local US; same count in JP) | local + jywjyw |
| SC01.CD | Chapter 1 scenario archive (per-location PAC chains: scripts/overlays, graphics, VAB audio, SQV music) | **86** (0x56, **verified-local US 2026-06-13**; == JP) | local + jywjyw |
| SC02.CD | Chapter 2 scenario archive | **43** (**verified-local US 2026-06-13** — corrects the "45" Auryn hearsay) | local |
| SC03.CD | Chapter 3 scenario archive | **140** (verified-local US 2026-06-13) | local |
| SC04.CD | Chapter 4 scenario archive | **31** (verified-local US 2026-06-13) | local |
| SC05.CD | Chapter 5 scenario archive | **30** (verified-local US 2026-06-13) | local |
| SC06.CD | Chapter 6 scenario archive | **39** (verified-local US 2026-06-13) | local |
| SC07.CD | Chapter 7 scenario archive | **29** (verified-local US 2026-06-13) | local |

Sub-files inside a `.CD` are either PAC chains (§3) — identified by the `PAC\0` magic — or
non-PAC files, which per `brave.txt` are SQV (MIDI) archives (§5). Anything without either
signature is unknown (**TBD**).

JP reference sizes (jywjyw `Conf.CD_JAPAN_SIZE`, for cross-version diffing only — the US
sizes are in §1.3): MAIN 6,205,440; SC01 20,615,168; SC02 6,580,224; SC03 78,168,064;
SC04 20,764,672; SC05 16,502,784; SC06 23,908,352; SC07 12,730,368.

### 2.3 LIST.CD (4,096 bytes = 0x1000)

Per `brave.txt`: "contiene las cabeceras de todos los archivos CD" (contains the headers of
all the CD archives). The exact structure, per jywjyw's `ListCdWriter.java` +
`CdHeader.trimBuild()` (JP repacker source):

- LIST.CD = the 8 TOCs of MAIN.CD, SC01.CD … SC07.CD **in that order**, each **trimmed** to
  exactly `8 + 8*N` bytes (u32 count + u32 zero + N entries — i.e. the TOC without its
  sector padding), **concatenated back-to-back with no alignment between tables**, written
  into a fixed 0x1000-byte (2-sector) buffer.
- Purpose (jywjyw `note.md`): loaded into RAM at game start so the engine can locate any
  sub-file in any `.CD` without re-reading each archive's header sector. US RAM cache
  location **TBD** (memory-map §3.2 `listCd_ramCache`, open question #3).

**Verification status:** locally confirmed only that LIST.CD *begins with* an exact copy of
MAIN.CD's TOC (first bytes identical to MAIN.CD sector 0). The full
trimmed-concatenation layout (SC01–SC07 portions, their order, the no-alignment packing) is
from the JP repacker and is **UNVERIFIED against the US disc** — verify by recomputing the
8 trimmed TOCs from the US `.CD` files and diffing against LIST.CD (cheap Phase-2 check).

⚠️ CUE's BRAVE tool does **not** special-case LIST.CD. Because LIST.CD *starts* with a valid
TOC, running BRAVE on it parses MAIN.CD's table and then reads garbage sector offsets inside
a 4 KB file. Never feed LIST.CD to the extractor; treat it as derived data (regenerable from
the other 8 TOCs).

---

## 3. PAC archive format

A `.CD` sub-file whose first u32 is `0x00434150` (`"PAC\0"` LE) is a **PAC chain**: a
sequence of entries, each with its own 0x800-byte header block immediately followed by its
payload, repeated until an entry's last-flag is set.

### 3.1 Entry header (0x800-byte block; fields per brave.c/brave.txt + jywjyw PacHeader.java)

| Offset | Type | Meaning | Status |
|---|---|---|---|
| +0x00 | u32 LE | Magic `0x00434150` = `"PAC\0"` | verified (tool + local) |
| +0x04 | u8 | **Type** (0–8), selects payload interpretation (§3.2) | verified |
| +0x05 | u8 | **Last-entry flag**: 1 = last entry in chain, 0 = more follow | verified |
| +0x06 | u16 | Zero | verified |
| +0x08 | u32 LE | **Unknown** — partly characterized (Phase 2, 2026-06-13). Across all 1189 US PAC entries it is **non-zero only for type 0 (301/301 graphics) and type 6 (29/29)**; it is **0 for every type-4 entry**, so it is **NOT a decompressed-size hint** (the original F2 guess is refuted). Likely a type-specific parameter (type-0 graphics dimensions/format; type-6 unknown). jywjyw preserves it verbatim. Decode meaning via the loader (memory-map #7) | type-0/6 param (F2) |
| +0x0C | u32 LE | **Length including this 0x800 header** — payload = `len − 0x800`, payload starts at entry+0x800 | verified |
| +0x10 … +0x7FF | — | Not interpreted by any known tool. jywjyw preserves the *entire* 0x800 header verbatim, implying it may contain meaningful non-zero bytes | **UNVERIFIED** |

### 3.2 Type table

Sources: `brave.txt` (CUE) + jywjyw `note.md`.

| Type | Payload | Notes |
|---|---|---|
| 0 | Graphics | Mostly 32×32 image blocks (8bpp = 64×32, 4bpp = 128×32 per jywjyw) |
| 1 | Graphics / **uncompressed script** | The memory-resident MAIN.CD `FILE_010` entry "1.1" and the shop-dialog "2.1" scripts are type 1 |
| 2 | VAB header (`.VH`) | PsyQ sound bank header |
| 3 | VAB body (`.VB`) | PsyQ sound bank sample data |
| 4 | **LZSS-compressed data** (§4) | Location scripts **containing embedded MIPS code** = the game's overlays. The only compressed type |
| 5 | — | Unused per CUE ("---") |
| 6 | Unknown | **TBD**. jywjyw notes all of a type-6 entry's data fits within its first 0x800 bytes |
| 7 | Unknown | **TBD** |
| 8 | Graphics | |

Only type 4 is compressed; everything else is stored raw. ("All .CD files are
LZSS-compressed" — an early planning claim — is **wrong**; compression is a per-PAC-entry
type flag, with no magic and no size heuristic.)

**Observed US type distribution (Phase 2, all 1189 PAC entries, 2026-06-13):**
type 0 = 301, type 1 = 166, type 2 = 201, type 3 = 201, type 4 = 138, type 6 = 29,
type 7 = **139**, type 8 = 14; **type 5 = 0 (absent, consistent with "unused")**. Note types
2 and 3 are equal counts (201 each) — VAB header/body pairs. **Type 7 is common (139
entries), not rare**, and type 6 (29) — both remain uninterpreted (F1), extracted raw.

### 3.3 Chaining (brave.c::UnPAC, verbatim semantics)

```
pos = 0
do:
    type = buf[pos+0x04]; last = buf[pos+0x05]
    len  = u32le(buf + pos + 0x0C)              # includes the 0x800 header
    payload = buf[pos+0x800 : pos+len]          # len − 0x800 bytes
    pos += (len + 0x7FF) & ~0x7FF               # next entry at sector alignment
while not last
```

Entries are sector-aligned, zero-padded between payload end and the next 0x800 boundary.

---

## 4. LZSS variant (PAC type-4 payloads) — CRITICAL SECTION

Two authoritative implementations exist and they **disagree on termination** (§4.4):
the game's own MIPS decompressor (US EXE **0x80018730**, byte-verified against the AiroRom
listing — memory-map §2.1) and CUE's `brave.c::Decode()` (tool reference). Everything below
is reconciled from both plus Vehek's findings in romhacking thread 15730.

### 4.1 Parameters

| Parameter | Value | Notes |
|---|---|---|
| `POS_BITS` | 10 | Position field width |
| `N` (ring size) | 1024 bytes (`1 << 10`) | Game keeps the ring in **scratchpad 0x1F800000** (memory-map §3.1) |
| `THRESHOLD` | 1 (CUE's naming) | jywjyw's encoder calls it 2 — naming difference only; both agree real match length = 6-bit field + 2 |
| Max match `F` | 65 bytes (`(1 << 6) + 1` + the loop's `<=`) | Copy lengths range **2..65** |
| Ring initial state | Zero-filled, write index `r = 0` | Encoder-side origin is index **1** (§4.3, §4.6) |
| Decompressed size | **No size field anywhere** | CUE grows the output buffer dynamically (start 128 KB, +64 KB steps); the game decodes until the terminator |

### 4.2 Flag engine (LSB-first with 0xFF00 sentinel)

From `brave.c`, verbatim:

```c
if (!((flags >>= 1) & 0xFF00)) flags = 0xFF00 | encoded[enc_size++];
if (flags & 1) { /* literal */ } else { /* match */ }
```

- A flag byte is loaded into the low 8 bits with sentinel `0xFF00` ORed above it; each step
  right-shifts once and tests bit 0. After 8 shifts the sentinel is exhausted
  (`& 0xFF00 == 0`) and the next flag byte is fetched. Net effect: **flag bits are consumed
  LSB-first**, one flag byte governs the next 8 tokens.
- The game's MIPS routine implements the same order with a mask walking 0x01→0x80 against a
  held token byte (AiroRom listing) — equivalent semantics, verified.
- Flag bit **1 = literal**, **0 = match reference**.

### 4.3 Literal and match paths

**Literal (flag bit = 1):** read 1 input byte → append to output **and** write to
`ring[r]`; `r = (r + 1) & 0x3FF`.

**Match (flag bit = 0):** read u16 **little-endian** `code`, then:

```
pos = code & 0x3FF              // low 10 bits — ABSOLUTE ring index (NOT a relative offset!)
len = (code >> 10) + 1          // THRESHOLD = 1
for i in 0 ..= len:             // len+1 iterations  =>  2..65 output bytes
    b = ring[(pos - 1 + i) & 0x3FF]   // note the −1 bias
    output(b); ring[r] = b; r = (r + 1) & 0x3FF
```

- **Absolute index, not distance:** the 10-bit `pos` addresses the ring directly. Generic
  LZSS tools (relative-distance decoders) will NOT work on this format.
- **The −1 bias:** stored positions are ring-index+1, because the game's *encoder* starts
  writing at ring index 1 (Vehek: "the starting position in the buffer appears to be 1").
  An off-by-one here corrupts every decompressed overlay. Validate any new implementation
  by diffing a decompressed type-4 blob against a live emulator RAM dump at the overlay
  load address (memory-map §4, open question #1).
- The ring write pointer `r` advances on **every** output byte (literals and match bytes
  alike) and is independent of `pos`.

### 4.4 Termination — GAME vs TOOL discrepancy (load-bearing)

| Implementation | Stop condition | Consequence |
|---|---|---|
| **Game** (MIPS @ 0x80018730, US-verified; Vehek Aug 2014) | A match code whose **low 10 bits == 0** (`pos == 0`) terminates the stream. Streams typically end with bytes `00 00`. The PAC header length field has **no effect** on the game's decompressed size (Vehek-tested) | `pos == 0` is reserved ⇒ legal references are `pos` 1..1023, i.e. biased start indices 0..1022 |
| **CUE's brave.c** | No terminator check; stops when the input length (`PAC len − 0x800`) is consumed | Trusts the header length; never sees `pos == 0` specially |

**Project rule:** our extractor must implement **game semantics — stop on `pos == 0`** —
with a **length sanity cross-check**: after hitting the terminator, verify input consumption
is consistent with the PAC length field (`len − 0x800`, allowing trailing padding), and warn
on any stream that exhausts its input without a terminator or overruns it.

**Verified Phase 2 (2026-06-13, F6 RESOLVED):** all **138** US type-4 streams decode cleanly
under game semantics — every one hits a `pos == 0` terminator with the length cross-check
satisfied (zero warnings across the whole disc). Cross-checked byte-for-byte against
`brave.c`: our output is a **strict prefix** of brave's for all 138, and brave appends
**exactly 2 bytes** to each — it decodes the terminating `00 00` as a match (code 0 ⇒
pos 0, len 1 ⇒ emits `ring[1023], ring[0]` = `00 00`) instead of stopping. So game and tool
semantics **coincide on the real payload**; the only divergence is brave's 2-byte over-decode
of the terminator/padding. Our game-semantics output is the correct one. No retail stream was
found where the two diverge *within* the payload.

Additional tool caveat: `brave.c`'s `ring[]` is a global that is never re-zeroed between
files (only `r` resets), so CUE's tool is not a strict oracle for streams that reference
ring positions not yet written; the game expects a zero-filled ring at stream start.

### 4.5 Game-side streaming state machine (resumable, sector-fed)

The game's decompressor consumes input in **0x800-byte CD-sector chunks** and is a
**resumable 5-state machine** so decompression can suspend mid-token at a sector boundary.
All addresses US-verified; full ledger in memory-map §2.1/§3.1:

| Item | Address (US) |
|---|---|
| Decoder entry | 0x80018730 (`LzssDecodeSector`); returns at 0x80018910 |
| State jump table | 0x80072A30 (`00000000 FFFFFFFF` then 5 state pointers) |
| State variable | 0x800C7D24 (runtime BSS) |
| Persistent state block | 0x800747A0 mask, 0x800747A4 token byte, 0x800747AC output ptr, 0x800747B0 ring index, 0x800747B4 partial 16-bit match code |
| Ring buffer | 0x1F800000 (scratchpad, 1024 B) |
| Sector staging buffer | JP 0x80078BD0–0x800793D0 — **JP-only, US equivalent TBD** (memory-map §3.2) |

States: 0 finish, 1 init token ring, 2 check token bit, 3 process match, 4 next token bit.
The partial-code slot exists precisely because a 16-bit match code can straddle a sector
boundary.

### 4.6 Recompression — NOT byte-stable (encoder constraints)

- LZSS parsing is ambiguous (literal-vs-match and match-length choices); jywjyw's working
  binary-search-tree encoder explicitly notes "recompressed 0.4 script not equals original".
  **No recompressor is expected to reproduce Square's original bitstream.**
- ⇒ **Compressed type-4 payloads are opaque binary for build verification.** Only the
  *decompressed* overlays can be matched; the matching build treats compressed blobs as
  binary data. Repacking/injection is a **Gen3 parking-lot concern**.
- Any future encoder MUST: (a) **never emit a `pos == 0` reference mid-stream** — stock
  Okumura-style LZSS output does, and the game treats it as end-of-stream (Vehek's failed
  2013 attempt); (b) terminate the stream with a `pos == 0` pair; (c) start its ring origin
  at index 1 (jywjyw's `Compresser.java` does exactly this — it also documents the encoded
  byte order: byte0 = `pos & 0xFF`, byte1 = `(len-2) << 2 | pos >> 8`).

---

## 5. SQV format (sequenced music archives)

`.CD` sub-files that are not PAC chains; signature `".sqv"`. Source: `brave.txt` (CUE) —
**not yet locally re-verified against extracted US files (UNVERIFIED)**.

| Item | Spec |
|---|---|
| Magic | 4 bytes `".sqv"` at +0x00 |
| Header u32s | Up to **3** u32 offsets to `MThd` (Standard MIDI File) sub-files. Each value is an offset **to which 4 must be added** (+4 bias); a value of **0 means the archive holds a single MThd** (no further offsets) |
| Header alignment | 16 bytes, zero-padded |
| Member alignment | 4 bytes, zero-padded |
| VAB | A VAB file at **fixed offset 0x7000**, after the MThd data |

Pairs with PAC types 2/3 (VAB header/body) for the game's sound banks. **Driver — semi-custom
(Phase 12, partial):** the resident engine holds a **thin Square-custom sound layer over PsyQ
libsnd**. `DsMix` (0x800D1BD8) is a custom 2-line wrapper (`{ FUN_800d1bf8(); return 1; }` — ignores
its arg; NOT the stock libsnd `DsMix` — ghidra_psx_ldr's PsyQ-4.7 signature hit there was coincidental,
Phase-12 T1). The resident's sound cluster wraps/calls the (EXE-resident) PsyQ libsnd SEQ/VAB
primitives; the SQV→libsnd bridge is the custom glue (its **bytes** were matched in the Phase-12 harvest,
but the deep MThd→SEQ + VAB-load *playback semantics* are not exhaustively traced — deferred to Gen3 repack
work, and not needed for the byte-match). Verdict: **semi-custom** = Square wrappers/glue over stock PsyQ
libsnd sequencing.

## 6. Save / memory-card format (Q#5 — Phase 12, partial)

`SaveLoadRoutine` @ `0x8002B154` (EXE) is a multi-entry save/load handler blob driving the **linked
PsyQ libmcrd** primitives (`0x8005Fxxx`–`0x80061xxx`, e.g. `0x800603BC` heavily, `0x8006023C`,
`0x80060AE0`, `0x80061114`). Its config/dispatch data is `saveHeaderTemplate` @ `0x80072DF0`:

| Off | Bytes | Meaning |
|---|---|---|
| +0x00 | `82 67 82 85 82 92 82 8F` + pad | 4-char SJIS label (`Ｈｅｒｏ`?) |
| +0x0C | `"BASLUS-00726MUSASHI"` | **memcard filename** (PS1 `BA` + region-product + name) |
| +0x20 | SJIS `ＢＲＡＶＥ ＦＥＮＣＥＲ ＭＵＳＡＳＨＩ` | **save title** (BIOS memcard-manager display) |
| +0x44 | `2A 00 00 00` | count/flag (0x2A = 42) |
| +0x54 | `0x8002B154, 0x8002B1AC, 0x8002BEA4, …` (a run of `0x8002Bxxx` pointers) | **handler dispatch table** — addresses INTERIOR to the SaveLoadRoutine blob; the save/load/validate sub-operations |

So the Gen1 "multi-entry blob" note **is** this dispatch table: the header holds a vector of sub-handler
addresses (the 3 known entries + more), each performing one memcard step via libmcrd.

**VERIFIED (static, Phase 12):** the header layout above; SaveLoadRoutine calls the linked libmcrd objects.
**TBD (needs Ghidra-on-EXE + a Drew-operated PCSX-Redux save trace + PsyQ-memcard research, R17):** the
**save-DATA block** serialization — almost certainly the Phase-3 player/progress state (`0x80078Exx`:
gold/HP/BP/day/hour/flags) + a **checksum**; capture the live memcard buffer from a real save to pin the
field order + the checksum algorithm — and matching the tractable handler entries. `dumps/ram_savescreen.bin`
(save screen, overlay flushed) holds the live `saveHeaderTemplate` for cross-check.

**Runtime-confirmed (Phase 12 trace — live save to card slot 1):** the memcard path is
`bu00:BASLUS-00726MUSASHI` (PsyQ device path `bu00:` = card unit 0 / slot 1, via libmcrd); the
title-frame + a directory list of 32-byte records stage in low RAM (~`0x80004E00`). The
**save-DATA serialization** (which game-state region is written + the checksum) was NOT isolated
from a live before/after RAM diff — the running game churns the diff (491 changed runs; the one
big region @`0x8007CD28` is an unrelated UI list of `"XXX,"`-tagged records, not save data), and
BFM appears to serialize from the live game-state rather than a findable staging copy. The clean
route to the byte-exact block is the **`.mcd` memcard file** (or a paused-state capture).
**Deferred** as Gen3-repack territory — **not needed for the `SaveLoadRoutine` byte-match** (that
is code-level: matched from the disassembly like any other function, when attempted; the 1139-ins
multi-entry blob remains the documented hard-defer per the Gen1 precedent, P9).

---

## 6. Extractor implementation notes (Phase 2 pipeline)

1. **Naming collision in CUE's tool — do not copy.** `brave.c` saves sub-files as
   `<file>.dir/FILE_%03d` (fine) but names PAC chain entries `%03d` **by type byte**
   (`sprintf(name, "%s.dir/%03d", filename, num)` where `num` = type). Two same-type entries
   in one chain **silently overwrite each other** on extraction. **Our extractor uses
   `{index}.{type}` naming** (jywjyw's `CdSplitter` convention: `0.4`, `1.1`, `2.1` …) so
   every entry survives and the type remains visible.
2. **Decode rule:** decompress **only** type-4 entries, using game termination semantics
   with the length cross-check (§4.4). Save all other types raw. Save non-PAC sub-files
   as-is (SQV etc.).
3. **Never run the pipeline on LIST.CD** (§2.3); instead verify LIST.CD by *regenerating*
   the trimmed-TOC concatenation from the 8 archives and diffing.
4. **Round-trip / repack reference (Gen3):** `github.com/jywjyw/bravefencer-hack`
   (Java/Maven, 2018) — `CdHeader.java` (TOC rebuild: count, entries from sector 1,
   `addr += paddedLen/0x800`), `PacHeader.java` (full 0x800 header incl. unknown bytes),
   `hack/Compresser.java` (game-compatible LZSS encoder; LGPL 2.1 header, adapted from
   JSword), `hack/CdRebuilder.java` (rebuilds all 8 .CDs, preserves original PAC headers via
   `headers.bin`, recomputes length fields, pads to 0x800, warns if a rebuilt .CD outgrows
   the original), `hack/ListCdWriter.java` (LIST.CD regeneration), `dump/Uncompresser.java`
   + `dump/CdSplitter.java` (decoder/splitter with the `{index}.{type}` naming). Its
   `doc/note.md` is the best third-party memory/format document (JP-based).
5. **Cross-validation — DONE (Phase 2, `tools/bfm_extract/crosscheck.py`).** brave is built
   from source on WSL via `tools/brave-CUE/posix_shim.h` (the GPL upstream `brave.c`/
   `common.inc` stay byte-for-byte unmodified; `brave.exe` is a Windows PE, unused on Linux).
   The harness maps brave's type-only names back to our `{index}.{type}` by re-walking each
   chain (skipping "shadowed" same-type entries brave overwrites), then byte-compares.
   Result on `--sample all`: **1484 raw payloads identical, 138/138 type-4** byte-identical up
   to our `pos==0` terminator (brave's 2-byte over-decode logged as the expected F6
   divergence; see §4.4).
6. **Licensing:** `brave.c` is GPLv3 (study/port is fine; note license if vendoring);
   `Compresser.java` carries LGPL 2.1.

## 7. Out of scope (for now)

| Format | Status |
|---|---|
| `.STR` (12 files) | Standard PS1 STR movie streams (Mode 2 Form 2 interleaved video/XA). No game-specific container suspected (**UNVERIFIED** — assumed standard). Not part of the extraction/matching pipeline |
| `.DA` (3 files) | CD-DA track handles (§1.4). **Phase 2 (user scope change 2026-06-13):** now extracted as raw 2352-byte/sector audio from tracks 2-4 — ST01_13A.DA=Track 2 (10,325,280 B), ST01_13B.DA=Track 3 (6,976,032 B), DUMMY_DA.DA=Track 4 (32,815,104 B). Their 2048-based ISO sizes differ from the raw audio by design. Out of scope for *matching* (audio), but extracted for completeness |

## 8. Open questions specific to formats

| # | Question | Attack |
|---|---|---|
| F1 | PAC types 6/7 semantics (CUE "???", jywjyw "??") | **Phase 2:** both present in US (type 6 = 29, type 7 = **139** entries), extracted raw; semantics still TBD → Ghidra PAC-header parser in the loader |
| F2 | PAC header +0x08 u32 meaning | **Phase 2: size-hint hypothesis REFUTED** — +0x08 == 0 for all 138 type-4; non-zero only for type 0 (301/301) and type 6 (29/29). Remaining: decode the type-0/6 meaning via the loader |
| F3 | PAC header bytes +0x10..+0x7FF — meaningful content? | Hex-survey across all extracted headers (jywjyw preserves them) — **not yet done** |
| F4 | LIST.CD full layout on the US disc (only the MAIN.CD-TOC prefix is locally verified) | **Deferred** — extractor excludes LIST.CD (§2.3); regenerating the 8 trimmed TOCs and diffing is a cheap follow-up |
| F5 | ~~US sub-file counts for SC01–SC07~~ — **RESOLVED (Phase 2)** | MAIN=49, SC01=86, **SC02=43** (not the hearsay 45), SC03=140, SC04=31, SC05=30, SC06=39, SC07=29 — read from each US TOC (§2.2) |
| F6 | ~~Do any retail type-4 streams violate the length/terminator cross-check?~~ — **RESOLVED (Phase 2): NO** | All 138 decode clean (0 warnings) and are byte-identical to brave up to our `pos==0` terminator (§4.4) |
| F7 | Are `.sqv` details (3-offset cap, +4 bias, VAB at 0x7000) correct for US files? | **Phase 2:** 98 SQV sub-files detected by `.sqv` magic and extracted raw; header details still UNVERIFIED (Gen3 parse) |
| F8 | Where are LOGOA/LOGOB.STR and the .DA files referenced, if not in `CdPathTable`? | memory-map open question #14 |

> **Phase 2 extraction summary (2026-06-13).** One command (`tools/bfm_extract/extract.py`)
> extracts the full disc: 24 Track-1 files verbatim + 3 `.DA` files as raw CD-DA audio from
> tracks 2-4 (each `(Track N).bin` = 150-sector INDEX 00→01 pregap + audio). The 8 `.CD`
> archives split into **447 sub-files → 1189 PAC entries** (`{index}.{type}` naming, no
> collisions) → **138 type-4 LZSS payloads** decoded under game semantics. A deterministic
> JSON-Lines manifest (`manifest.jsonl` + `manifest.sha1`, 1801 artifacts) is the
> reproducibility contract; `--verify` re-checks it. Cross-validated byte-for-byte against
> CUE's `brave` (built from source via `tools/brave-CUE/posix_shim.h`): **1484 raw payloads
> identical, 138/138 type-4 F6-equivalent** (ours = the game-correct prefix). EXE round-trips
> to SHA1 `143dbb89…`.

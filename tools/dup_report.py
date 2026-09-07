#!/usr/bin/env python3
"""Duplicate-function report (G7 "duplicates first") — intra-binary repurpose of
match_protos.py. Finds functions that are byte-identical (h_exact) or structurally
identical (h_norm) to each other, so one match can be shared to the rest
(match-once-share-many). Ghidra-free; consumes .run/sig.<bin>.jsonl (regenerate with
`make sig-refresh` when the Ghidra DB changes; overlay images via tools/sig_image.py).

Two modes:
  * per-binary (default): one binary's self-duplicates -> docs/duplicates[.<bin>].md
  * --cross (Phase 11): bucket EVERY binary's functions together, split into
    cross-binary (members span >1 binary -> the Phase-12/13 work queue) vs intra-binary
    groups, ranked by collapsible bytes -> docs/duplicates.cross.md

Usage: tools/dup_report.py [MIN_INS] [--binary <alias>]   (per-binary; MIN_INS default 8)
       tools/dup_report.py [MIN_INS] --cross                (cross-binary; scans all BINARIES)
"""
import json, sys, hashlib, pathlib
from collections import defaultdict

ROOT = pathlib.Path(__file__).resolve().parent.parent

# Per-binary config (Phase 9). main = the retail EXE (current paths = no-op default);
# a second binary (Phase 10) adds its sig/md entry. Phase 11's --cross scans EVERY entry
# here, so a new overlay binary (Phase 13) joins the cross report automatically. The dict
# insertion order is the report's deterministic source order (committable digests).
BINARIES = {
    "main": dict(sig=".run/sig.main.jsonl", md="docs/duplicates.md"),   # P33 A2: build-derived (make sig-main), was the Ghidra sig
    "resident": dict(sig=".run/sig.resident.jsonl", md="docs/duplicates.resident.md"),
    "ov_SC01_077": dict(sig=".run/sig.ov_SC01_077.jsonl", md="docs/duplicates.ov_SC01_077.md"),
    "ov_SC01_005": dict(sig=".run/sig.ov_SC01_005.jsonl", md="docs/duplicates.ov_SC01_005.md"),
    "ov_SC01_006": dict(sig=".run/sig.ov_SC01_006.jsonl", md="docs/duplicates.ov_SC01_006.md"),
    "ov_SC03_001": dict(sig=".run/sig.ov_SC03_001.jsonl", md="docs/duplicates.ov_SC03_001.md"),
    "ov_SC01_000": dict(sig=".run/sig.ov_SC01_000.jsonl", md="docs/duplicates.ov_SC01_000.md"),
    "ov_SC01_001": dict(sig=".run/sig.ov_SC01_001.jsonl", md="docs/duplicates.ov_SC01_001.md"),
    "ov_SC02_000": dict(sig=".run/sig.ov_SC02_000.jsonl", md="docs/duplicates.ov_SC02_000.md"),
    "ov_SC02_003": dict(sig=".run/sig.ov_SC02_003.jsonl", md="docs/duplicates.ov_SC02_003.md"),
    "ov_SC03_002": dict(sig=".run/sig.ov_SC03_002.jsonl", md="docs/duplicates.ov_SC03_002.md"),
    "ov_SC03_006": dict(sig=".run/sig.ov_SC03_006.jsonl", md="docs/duplicates.ov_SC03_006.md"),
    "ov_SC04_000": dict(sig=".run/sig.ov_SC04_000.jsonl", md="docs/duplicates.ov_SC04_000.md"),
    "ov_SC04_018": dict(sig=".run/sig.ov_SC04_018.jsonl", md="docs/duplicates.ov_SC04_018.md"),
    "ov_SC04_019": dict(sig=".run/sig.ov_SC04_019.jsonl", md="docs/duplicates.ov_SC04_019.md"),
    "ov_SC05_000": dict(sig=".run/sig.ov_SC05_000.jsonl", md="docs/duplicates.ov_SC05_000.md"),
    "ov_SC06_000": dict(sig=".run/sig.ov_SC06_000.jsonl", md="docs/duplicates.ov_SC06_000.md"),
    "ov_SC07_000": dict(sig=".run/sig.ov_SC07_000.jsonl", md="docs/duplicates.ov_SC07_000.md"),
    "ov_SC01_004": dict(sig=".run/sig.ov_SC01_004.jsonl", md="docs/duplicates.ov_SC01_004.md"),
    "ov_SC01_008": dict(sig=".run/sig.ov_SC01_008.jsonl", md="docs/duplicates.ov_SC01_008.md"),
    "ov_SC01_009": dict(sig=".run/sig.ov_SC01_009.jsonl", md="docs/duplicates.ov_SC01_009.md"),
    "ov_SC01_074": dict(sig=".run/sig.ov_SC01_074.jsonl", md="docs/duplicates.ov_SC01_074.md"),
    "ov_SC01_080": dict(sig=".run/sig.ov_SC01_080.jsonl", md="docs/duplicates.ov_SC01_080.md"),
    "ov_SC01_084": dict(sig=".run/sig.ov_SC01_084.jsonl", md="docs/duplicates.ov_SC01_084.md"),
    "ov_SC02_004": dict(sig=".run/sig.ov_SC02_004.jsonl", md="docs/duplicates.ov_SC02_004.md"),
    "ov_SC02_005": dict(sig=".run/sig.ov_SC02_005.jsonl", md="docs/duplicates.ov_SC02_005.md"),
    "ov_SC02_011": dict(sig=".run/sig.ov_SC02_011.jsonl", md="docs/duplicates.ov_SC02_011.md"),
    "ov_SC02_015": dict(sig=".run/sig.ov_SC02_015.jsonl", md="docs/duplicates.ov_SC02_015.md"),
    "ov_SC02_016": dict(sig=".run/sig.ov_SC02_016.jsonl", md="docs/duplicates.ov_SC02_016.md"),
    "ov_SC02_017": dict(sig=".run/sig.ov_SC02_017.jsonl", md="docs/duplicates.ov_SC02_017.md"),
    "ov_SC02_021": dict(sig=".run/sig.ov_SC02_021.jsonl", md="docs/duplicates.ov_SC02_021.md"),
    "ov_SC02_026": dict(sig=".run/sig.ov_SC02_026.jsonl", md="docs/duplicates.ov_SC02_026.md"),
    "ov_SC02_027": dict(sig=".run/sig.ov_SC02_027.jsonl", md="docs/duplicates.ov_SC02_027.md"),
    "ov_SC02_028": dict(sig=".run/sig.ov_SC02_028.jsonl", md="docs/duplicates.ov_SC02_028.md"),
    "ov_SC02_031": dict(sig=".run/sig.ov_SC02_031.jsonl", md="docs/duplicates.ov_SC02_031.md"),
    "ov_SC02_035": dict(sig=".run/sig.ov_SC02_035.jsonl", md="docs/duplicates.ov_SC02_035.md"),
    "ov_SC02_039": dict(sig=".run/sig.ov_SC02_039.jsonl", md="docs/duplicates.ov_SC02_039.md"),
    "ov_SC02_041": dict(sig=".run/sig.ov_SC02_041.jsonl", md="docs/duplicates.ov_SC02_041.md"),
    "ov_SC03_003": dict(sig=".run/sig.ov_SC03_003.jsonl", md="docs/duplicates.ov_SC03_003.md"),
    "ov_SC03_007": dict(sig=".run/sig.ov_SC03_007.jsonl", md="docs/duplicates.ov_SC03_007.md"),
    "ov_SC03_010": dict(sig=".run/sig.ov_SC03_010.jsonl", md="docs/duplicates.ov_SC03_010.md"),
    "ov_SC03_011": dict(sig=".run/sig.ov_SC03_011.jsonl", md="docs/duplicates.ov_SC03_011.md"),
    "ov_SC03_012": dict(sig=".run/sig.ov_SC03_012.jsonl", md="docs/duplicates.ov_SC03_012.md"),
    "ov_SC03_013": dict(sig=".run/sig.ov_SC03_013.jsonl", md="docs/duplicates.ov_SC03_013.md"),
    "ov_SC03_014": dict(sig=".run/sig.ov_SC03_014.jsonl", md="docs/duplicates.ov_SC03_014.md"),
    "ov_SC03_015": dict(sig=".run/sig.ov_SC03_015.jsonl", md="docs/duplicates.ov_SC03_015.md"),
    "ov_SC03_023": dict(sig=".run/sig.ov_SC03_023.jsonl", md="docs/duplicates.ov_SC03_023.md"),
    "ov_SC03_024": dict(sig=".run/sig.ov_SC03_024.jsonl", md="docs/duplicates.ov_SC03_024.md"),
    "ov_SC03_028": dict(sig=".run/sig.ov_SC03_028.jsonl", md="docs/duplicates.ov_SC03_028.md"),
    "ov_SC03_029": dict(sig=".run/sig.ov_SC03_029.jsonl", md="docs/duplicates.ov_SC03_029.md"),
    "ov_SC03_030": dict(sig=".run/sig.ov_SC03_030.jsonl", md="docs/duplicates.ov_SC03_030.md"),
    "ov_SC03_031": dict(sig=".run/sig.ov_SC03_031.jsonl", md="docs/duplicates.ov_SC03_031.md"),
    "ov_SC03_089": dict(sig=".run/sig.ov_SC03_089.jsonl", md="docs/duplicates.ov_SC03_089.md"),
    "ov_SC03_090": dict(sig=".run/sig.ov_SC03_090.jsonl", md="docs/duplicates.ov_SC03_090.md"),
    "ov_SC03_091": dict(sig=".run/sig.ov_SC03_091.jsonl", md="docs/duplicates.ov_SC03_091.md"),
    "ov_SC03_092": dict(sig=".run/sig.ov_SC03_092.jsonl", md="docs/duplicates.ov_SC03_092.md"),
    "ov_SC03_093": dict(sig=".run/sig.ov_SC03_093.jsonl", md="docs/duplicates.ov_SC03_093.md"),
    "ov_SC03_094": dict(sig=".run/sig.ov_SC03_094.jsonl", md="docs/duplicates.ov_SC03_094.md"),
    "ov_SC03_095": dict(sig=".run/sig.ov_SC03_095.jsonl", md="docs/duplicates.ov_SC03_095.md"),
    "ov_SC03_096": dict(sig=".run/sig.ov_SC03_096.jsonl", md="docs/duplicates.ov_SC03_096.md"),
    "ov_SC03_097": dict(sig=".run/sig.ov_SC03_097.jsonl", md="docs/duplicates.ov_SC03_097.md"),
    "ov_SC03_098": dict(sig=".run/sig.ov_SC03_098.jsonl", md="docs/duplicates.ov_SC03_098.md"),
    "ov_SC03_099": dict(sig=".run/sig.ov_SC03_099.jsonl", md="docs/duplicates.ov_SC03_099.md"),
    "ov_SC03_100": dict(sig=".run/sig.ov_SC03_100.jsonl", md="docs/duplicates.ov_SC03_100.md"),
    "ov_SC03_101": dict(sig=".run/sig.ov_SC03_101.jsonl", md="docs/duplicates.ov_SC03_101.md"),
    "ov_SC03_102": dict(sig=".run/sig.ov_SC03_102.jsonl", md="docs/duplicates.ov_SC03_102.md"),
    "ov_SC03_103": dict(sig=".run/sig.ov_SC03_103.jsonl", md="docs/duplicates.ov_SC03_103.md"),
    "ov_SC03_104": dict(sig=".run/sig.ov_SC03_104.jsonl", md="docs/duplicates.ov_SC03_104.md"),
    "ov_SC03_105": dict(sig=".run/sig.ov_SC03_105.jsonl", md="docs/duplicates.ov_SC03_105.md"),
    "ov_SC03_108": dict(sig=".run/sig.ov_SC03_108.jsonl", md="docs/duplicates.ov_SC03_108.md"),
    "ov_SC03_109": dict(sig=".run/sig.ov_SC03_109.jsonl", md="docs/duplicates.ov_SC03_109.md"),
    "ov_SC03_110": dict(sig=".run/sig.ov_SC03_110.jsonl", md="docs/duplicates.ov_SC03_110.md"),
    "ov_SC03_111": dict(sig=".run/sig.ov_SC03_111.jsonl", md="docs/duplicates.ov_SC03_111.md"),
    "ov_SC03_112": dict(sig=".run/sig.ov_SC03_112.jsonl", md="docs/duplicates.ov_SC03_112.md"),
    "ov_SC03_113": dict(sig=".run/sig.ov_SC03_113.jsonl", md="docs/duplicates.ov_SC03_113.md"),
    "ov_SC03_114": dict(sig=".run/sig.ov_SC03_114.jsonl", md="docs/duplicates.ov_SC03_114.md"),
    "ov_SC03_115": dict(sig=".run/sig.ov_SC03_115.jsonl", md="docs/duplicates.ov_SC03_115.md"),
    "ov_SC03_116": dict(sig=".run/sig.ov_SC03_116.jsonl", md="docs/duplicates.ov_SC03_116.md"),
    "ov_SC03_117": dict(sig=".run/sig.ov_SC03_117.jsonl", md="docs/duplicates.ov_SC03_117.md"),
    "ov_SC03_118": dict(sig=".run/sig.ov_SC03_118.jsonl", md="docs/duplicates.ov_SC03_118.md"),
    "ov_SC03_119": dict(sig=".run/sig.ov_SC03_119.jsonl", md="docs/duplicates.ov_SC03_119.md"),
    "ov_SC03_121": dict(sig=".run/sig.ov_SC03_121.jsonl", md="docs/duplicates.ov_SC03_121.md"),
    "ov_SC03_124": dict(sig=".run/sig.ov_SC03_124.jsonl", md="docs/duplicates.ov_SC03_124.md"),
    "ov_SC03_125": dict(sig=".run/sig.ov_SC03_125.jsonl", md="docs/duplicates.ov_SC03_125.md"),
    "ov_SC03_126": dict(sig=".run/sig.ov_SC03_126.jsonl", md="docs/duplicates.ov_SC03_126.md"),
    "ov_SC04_002": dict(sig=".run/sig.ov_SC04_002.jsonl", md="docs/duplicates.ov_SC04_002.md"),
    "ov_SC04_003": dict(sig=".run/sig.ov_SC04_003.jsonl", md="docs/duplicates.ov_SC04_003.md"),
    "ov_SC04_004": dict(sig=".run/sig.ov_SC04_004.jsonl", md="docs/duplicates.ov_SC04_004.md"),
    "ov_SC04_005": dict(sig=".run/sig.ov_SC04_005.jsonl", md="docs/duplicates.ov_SC04_005.md"),
    "ov_SC04_006": dict(sig=".run/sig.ov_SC04_006.jsonl", md="docs/duplicates.ov_SC04_006.md"),
    "ov_SC04_007": dict(sig=".run/sig.ov_SC04_007.jsonl", md="docs/duplicates.ov_SC04_007.md"),
    "ov_SC04_008": dict(sig=".run/sig.ov_SC04_008.jsonl", md="docs/duplicates.ov_SC04_008.md"),
    "ov_SC04_009": dict(sig=".run/sig.ov_SC04_009.jsonl", md="docs/duplicates.ov_SC04_009.md"),
    "ov_SC04_010": dict(sig=".run/sig.ov_SC04_010.jsonl", md="docs/duplicates.ov_SC04_010.md"),
    "ov_SC04_011": dict(sig=".run/sig.ov_SC04_011.jsonl", md="docs/duplicates.ov_SC04_011.md"),
    "ov_SC04_012": dict(sig=".run/sig.ov_SC04_012.jsonl", md="docs/duplicates.ov_SC04_012.md"),
    "ov_SC04_015": dict(sig=".run/sig.ov_SC04_015.jsonl", md="docs/duplicates.ov_SC04_015.md"),
    "ov_SC04_016": dict(sig=".run/sig.ov_SC04_016.jsonl", md="docs/duplicates.ov_SC04_016.md"),
    "ov_SC04_020": dict(sig=".run/sig.ov_SC04_020.jsonl", md="docs/duplicates.ov_SC04_020.md"),
    "ov_SC04_021": dict(sig=".run/sig.ov_SC04_021.jsonl", md="docs/duplicates.ov_SC04_021.md"),
    "ov_SC05_001": dict(sig=".run/sig.ov_SC05_001.jsonl", md="docs/duplicates.ov_SC05_001.md"),
    "ov_SC05_002": dict(sig=".run/sig.ov_SC05_002.jsonl", md="docs/duplicates.ov_SC05_002.md"),
    "ov_SC05_003": dict(sig=".run/sig.ov_SC05_003.jsonl", md="docs/duplicates.ov_SC05_003.md"),
    "ov_SC05_004": dict(sig=".run/sig.ov_SC05_004.jsonl", md="docs/duplicates.ov_SC05_004.md"),
    "ov_SC05_005": dict(sig=".run/sig.ov_SC05_005.jsonl", md="docs/duplicates.ov_SC05_005.md"),
    "ov_SC05_006": dict(sig=".run/sig.ov_SC05_006.jsonl", md="docs/duplicates.ov_SC05_006.md"),
    "ov_SC05_007": dict(sig=".run/sig.ov_SC05_007.jsonl", md="docs/duplicates.ov_SC05_007.md"),
    "ov_SC05_008": dict(sig=".run/sig.ov_SC05_008.jsonl", md="docs/duplicates.ov_SC05_008.md"),
    "ov_SC05_009": dict(sig=".run/sig.ov_SC05_009.jsonl", md="docs/duplicates.ov_SC05_009.md"),
    "ov_SC05_010": dict(sig=".run/sig.ov_SC05_010.jsonl", md="docs/duplicates.ov_SC05_010.md"),
    "ov_SC05_011": dict(sig=".run/sig.ov_SC05_011.jsonl", md="docs/duplicates.ov_SC05_011.md"),
    "ov_SC05_017": dict(sig=".run/sig.ov_SC05_017.jsonl", md="docs/duplicates.ov_SC05_017.md"),
    "ov_SC05_018": dict(sig=".run/sig.ov_SC05_018.jsonl", md="docs/duplicates.ov_SC05_018.md"),
    "ov_SC05_019": dict(sig=".run/sig.ov_SC05_019.jsonl", md="docs/duplicates.ov_SC05_019.md"),
    "ov_SC06_006": dict(sig=".run/sig.ov_SC06_006.jsonl", md="docs/duplicates.ov_SC06_006.md"),
    "ov_SC06_008": dict(sig=".run/sig.ov_SC06_008.jsonl", md="docs/duplicates.ov_SC06_008.md"),
    "ov_SC06_010": dict(sig=".run/sig.ov_SC06_010.jsonl", md="docs/duplicates.ov_SC06_010.md"),
    "ov_SC06_011": dict(sig=".run/sig.ov_SC06_011.jsonl", md="docs/duplicates.ov_SC06_011.md"),
    "ov_SC06_013": dict(sig=".run/sig.ov_SC06_013.jsonl", md="docs/duplicates.ov_SC06_013.md"),
    "ov_SC06_014": dict(sig=".run/sig.ov_SC06_014.jsonl", md="docs/duplicates.ov_SC06_014.md"),
    "ov_SC06_015": dict(sig=".run/sig.ov_SC06_015.jsonl", md="docs/duplicates.ov_SC06_015.md"),
    "ov_SC06_016": dict(sig=".run/sig.ov_SC06_016.jsonl", md="docs/duplicates.ov_SC06_016.md"),
    "ov_SC06_018": dict(sig=".run/sig.ov_SC06_018.jsonl", md="docs/duplicates.ov_SC06_018.md"),
    "ov_SC06_020": dict(sig=".run/sig.ov_SC06_020.jsonl", md="docs/duplicates.ov_SC06_020.md"),
    "ov_SC06_022": dict(sig=".run/sig.ov_SC06_022.jsonl", md="docs/duplicates.ov_SC06_022.md"),
    "ov_SC06_024": dict(sig=".run/sig.ov_SC06_024.jsonl", md="docs/duplicates.ov_SC06_024.md"),
    "ov_SC06_025": dict(sig=".run/sig.ov_SC06_025.jsonl", md="docs/duplicates.ov_SC06_025.md"),
    "ov_SC06_027": dict(sig=".run/sig.ov_SC06_027.jsonl", md="docs/duplicates.ov_SC06_027.md"),
    "ov_SC06_029": dict(sig=".run/sig.ov_SC06_029.jsonl", md="docs/duplicates.ov_SC06_029.md"),
    "ov_SC06_030": dict(sig=".run/sig.ov_SC06_030.jsonl", md="docs/duplicates.ov_SC06_030.md"),
    "ov_SC06_032": dict(sig=".run/sig.ov_SC06_032.jsonl", md="docs/duplicates.ov_SC06_032.md"),
    "ov_SC06_033": dict(sig=".run/sig.ov_SC06_033.jsonl", md="docs/duplicates.ov_SC06_033.md"),
    "ov_SC07_001": dict(sig=".run/sig.ov_SC07_001.jsonl", md="docs/duplicates.ov_SC07_001.md"),
    "ov_SC07_002": dict(sig=".run/sig.ov_SC07_002.jsonl", md="docs/duplicates.ov_SC07_002.md"),
    "ov_SC07_008": dict(sig=".run/sig.ov_SC07_008.jsonl", md="docs/duplicates.ov_SC07_008.md"),
    "ov_SC07_009": dict(sig=".run/sig.ov_SC07_009.jsonl", md="docs/duplicates.ov_SC07_009.md"),
    "ov_SC07_006": dict(sig=".run/sig.ov_SC07_006.jsonl", md="docs/duplicates.ov_SC07_006.md"),
    "ov_SC07_007": dict(sig=".run/sig.ov_SC07_007.jsonl", md="docs/duplicates.ov_SC07_007.md"),
    "ov_SC07_010": dict(sig=".run/sig.ov_SC07_010.jsonl", md="docs/duplicates.ov_SC07_010.md"),
    "ov_SC07_011": dict(sig=".run/sig.ov_SC07_011.jsonl", md="docs/duplicates.ov_SC07_011.md"),
    "ov_MAIN_012": dict(sig=".run/sig.ov_MAIN_012.jsonl", md="docs/duplicates.ov_MAIN_012.md"),
    "ov_SC02_037": dict(sig=".run/sig.ov_SC02_037.jsonl", md="docs/duplicates.ov_SC02_037.md"),
    "ov_SC03_107": dict(sig=".run/sig.ov_SC03_107.jsonl", md="docs/duplicates.ov_SC03_107.md"),
    "md_MAIN_013": dict(sig=".run/sig.md_MAIN_013.jsonl", md="docs/duplicates.md_MAIN_013.md"),
    "md_MAIN_014": dict(sig=".run/sig.md_MAIN_014.jsonl", md="docs/duplicates.md_MAIN_014.md"),
    "md_MAIN_015": dict(sig=".run/sig.md_MAIN_015.jsonl", md="docs/duplicates.md_MAIN_015.md"),
    "md_MAIN_016": dict(sig=".run/sig.md_MAIN_016.jsonl", md="docs/duplicates.md_MAIN_016.md"),
    "md_MAIN_017": dict(sig=".run/sig.md_MAIN_017.jsonl", md="docs/duplicates.md_MAIN_017.md"),
    "md_MAIN_018": dict(sig=".run/sig.md_MAIN_018.jsonl", md="docs/duplicates.md_MAIN_018.md"),
    "md_MAIN_019": dict(sig=".run/sig.md_MAIN_019.jsonl", md="docs/duplicates.md_MAIN_019.md"),
    "md_MAIN_020": dict(sig=".run/sig.md_MAIN_020.jsonl", md="docs/duplicates.md_MAIN_020.md"),
    "md_MAIN_021": dict(sig=".run/sig.md_MAIN_021.jsonl", md="docs/duplicates.md_MAIN_021.md"),
    "md_MAIN_022": dict(sig=".run/sig.md_MAIN_022.jsonl", md="docs/duplicates.md_MAIN_022.md"),
    "md_MAIN_023": dict(sig=".run/sig.md_MAIN_023.jsonl", md="docs/duplicates.md_MAIN_023.md"),
    "md_MAIN_024": dict(sig=".run/sig.md_MAIN_024.jsonl", md="docs/duplicates.md_MAIN_024.md"),
    "md_MAIN_025": dict(sig=".run/sig.md_MAIN_025.jsonl", md="docs/duplicates.md_MAIN_025.md"),
    "md_MAIN_026": dict(sig=".run/sig.md_MAIN_026.jsonl", md="docs/duplicates.md_MAIN_026.md"),
    "md_MAIN_027": dict(sig=".run/sig.md_MAIN_027.jsonl", md="docs/duplicates.md_MAIN_027.md"),
    "md_MAIN_028": dict(sig=".run/sig.md_MAIN_028.jsonl", md="docs/duplicates.md_MAIN_028.md"),
    "md_MAIN_029": dict(sig=".run/sig.md_MAIN_029.jsonl", md="docs/duplicates.md_MAIN_029.md"),
    "md_MAIN_030": dict(sig=".run/sig.md_MAIN_030.jsonl", md="docs/duplicates.md_MAIN_030.md"),
    "md_MAIN_031": dict(sig=".run/sig.md_MAIN_031.jsonl", md="docs/duplicates.md_MAIN_031.md"),
    "md_MAIN_032": dict(sig=".run/sig.md_MAIN_032.jsonl", md="docs/duplicates.md_MAIN_032.md"),
    "md_MAIN_033": dict(sig=".run/sig.md_MAIN_033.jsonl", md="docs/duplicates.md_MAIN_033.md"),
    "md_MAIN_034": dict(sig=".run/sig.md_MAIN_034.jsonl", md="docs/duplicates.md_MAIN_034.md"),
    "md_MAIN_035": dict(sig=".run/sig.md_MAIN_035.jsonl", md="docs/duplicates.md_MAIN_035.md"),
    "md_MAIN_036": dict(sig=".run/sig.md_MAIN_036.jsonl", md="docs/duplicates.md_MAIN_036.md"),
    "md_MAIN_037": dict(sig=".run/sig.md_MAIN_037.jsonl", md="docs/duplicates.md_MAIN_037.md"),
    "md_MAIN_038": dict(sig=".run/sig.md_MAIN_038.jsonl", md="docs/duplicates.md_MAIN_038.md"),
    "md_MAIN_039": dict(sig=".run/sig.md_MAIN_039.jsonl", md="docs/duplicates.md_MAIN_039.md"),
    "md_MAIN_040": dict(sig=".run/sig.md_MAIN_040.jsonl", md="docs/duplicates.md_MAIN_040.md"),
    "md_MAIN_041": dict(sig=".run/sig.md_MAIN_041.jsonl", md="docs/duplicates.md_MAIN_041.md"),
    "md_MAIN_042": dict(sig=".run/sig.md_MAIN_042.jsonl", md="docs/duplicates.md_MAIN_042.md"),
    "md_MAIN_043": dict(sig=".run/sig.md_MAIN_043.jsonl", md="docs/duplicates.md_MAIN_043.md"),
    "md_MAIN_044": dict(sig=".run/sig.md_MAIN_044.jsonl", md="docs/duplicates.md_MAIN_044.md"),
    "md_MAIN_045": dict(sig=".run/sig.md_MAIN_045.jsonl", md="docs/duplicates.md_MAIN_045.md"),
    "md_MAIN_046": dict(sig=".run/sig.md_MAIN_046.jsonl", md="docs/duplicates.md_MAIN_046.md"),
    "md_MAIN_047": dict(sig=".run/sig.md_MAIN_047.jsonl", md="docs/duplicates.md_MAIN_047.md"),
    "md_MAIN_001": dict(sig=".run/sig.md_MAIN_001.jsonl", md="docs/duplicates.md_MAIN_001.md"),
    "md_MAIN_008": dict(sig=".run/sig.md_MAIN_008.jsonl", md="docs/duplicates.md_MAIN_008.md"),
    "md_MAIN_011": dict(sig=".run/sig.md_MAIN_011.jsonl", md="docs/duplicates.md_MAIN_011.md"),
    "md_SC07_003": dict(sig=".run/sig.md_SC07_003.jsonl", md="docs/duplicates.md_SC07_003.md"),
    "md_SC07_004": dict(sig=".run/sig.md_SC07_004.jsonl", md="docs/duplicates.md_SC07_004.md"),
    "md_MAIN_003": dict(sig=".run/sig.md_MAIN_003.jsonl", md="docs/duplicates.md_MAIN_003.md"),
    "md_SC03_073": dict(sig=".run/sig.md_SC03_073.jsonl", md="docs/duplicates.md_SC03_073.md"),
    "md_SC03_074": dict(sig=".run/sig.md_SC03_074.jsonl", md="docs/duplicates.md_SC03_074.md"),
    "md_SC03_075": dict(sig=".run/sig.md_SC03_075.jsonl", md="docs/duplicates.md_SC03_075.md"),
    "md_SC03_076": dict(sig=".run/sig.md_SC03_076.jsonl", md="docs/duplicates.md_SC03_076.md"),
    "md_SC03_077": dict(sig=".run/sig.md_SC03_077.jsonl", md="docs/duplicates.md_SC03_077.md"),
    "md_SC03_078": dict(sig=".run/sig.md_SC03_078.jsonl", md="docs/duplicates.md_SC03_078.md"),
    "md_SC03_079": dict(sig=".run/sig.md_SC03_079.jsonl", md="docs/duplicates.md_SC03_079.md"),
    "md_SC03_132": dict(sig=".run/sig.md_SC03_132.jsonl", md="docs/duplicates.md_SC03_132.md"),
    "md_SC03_133": dict(sig=".run/sig.md_SC03_133.jsonl", md="docs/duplicates.md_SC03_133.md"),
    "md_SC03_134": dict(sig=".run/sig.md_SC03_134.jsonl", md="docs/duplicates.md_SC03_134.md"),
    "md_SC03_135": dict(sig=".run/sig.md_SC03_135.jsonl", md="docs/duplicates.md_SC03_135.md"),
    "md_SC03_136": dict(sig=".run/sig.md_SC03_136.jsonl", md="docs/duplicates.md_SC03_136.md"),
    "md_SC03_137": dict(sig=".run/sig.md_SC03_137.jsonl", md="docs/duplicates.md_SC03_137.md"),
    "md_SC03_138": dict(sig=".run/sig.md_SC03_138.jsonl", md="docs/duplicates.md_SC03_138.md"),
    "md_SC04_024": dict(sig=".run/sig.md_SC04_024.jsonl", md="docs/duplicates.md_SC04_024.md"),
    "md_SC04_025": dict(sig=".run/sig.md_SC04_025.jsonl", md="docs/duplicates.md_SC04_025.md"),
    "md_SC04_026": dict(sig=".run/sig.md_SC04_026.jsonl", md="docs/duplicates.md_SC04_026.md"),
    "md_SC04_027": dict(sig=".run/sig.md_SC04_027.jsonl", md="docs/duplicates.md_SC04_027.md"),
    "md_SC04_028": dict(sig=".run/sig.md_SC04_028.jsonl", md="docs/duplicates.md_SC04_028.md"),
    "md_SC04_029": dict(sig=".run/sig.md_SC04_029.jsonl", md="docs/duplicates.md_SC04_029.md"),
    "md_SC04_030": dict(sig=".run/sig.md_SC04_030.jsonl", md="docs/duplicates.md_SC04_030.md"),
    "md_SC05_023": dict(sig=".run/sig.md_SC05_023.jsonl", md="docs/duplicates.md_SC05_023.md"),
    "md_SC05_024": dict(sig=".run/sig.md_SC05_024.jsonl", md="docs/duplicates.md_SC05_024.md"),
    "md_SC05_025": dict(sig=".run/sig.md_SC05_025.jsonl", md="docs/duplicates.md_SC05_025.md"),
    "md_SC05_026": dict(sig=".run/sig.md_SC05_026.jsonl", md="docs/duplicates.md_SC05_026.md"),
    "md_SC05_027": dict(sig=".run/sig.md_SC05_027.jsonl", md="docs/duplicates.md_SC05_027.md"),
    "md_SC05_028": dict(sig=".run/sig.md_SC05_028.jsonl", md="docs/duplicates.md_SC05_028.md"),
    "md_SC05_029": dict(sig=".run/sig.md_SC05_029.jsonl", md="docs/duplicates.md_SC05_029.md"),
    "md_SC02_009": dict(sig=".run/sig.md_SC02_009.jsonl", md="docs/duplicates.md_SC02_009.md"),
    "md_MAIN_007": dict(sig=".run/sig.md_MAIN_007.jsonl", md="docs/duplicates.md_MAIN_007.md"),
    "md_MAIN_009": dict(sig=".run/sig.md_MAIN_009.jsonl", md="docs/duplicates.md_MAIN_009.md"),
    "md_SC03_053": dict(sig=".run/sig.md_SC03_053.jsonl", md="docs/duplicates.md_SC03_053.md"),
    "md_SC03_054": dict(sig=".run/sig.md_SC03_054.jsonl", md="docs/duplicates.md_SC03_054.md"),
    "md_SC03_056": dict(sig=".run/sig.md_SC03_056.jsonl", md="docs/duplicates.md_SC03_056.md"),
    # <<< overlays: tools/new_overlay.sh inserts ov_* entries above this line (Phase 13) >>>
}
CROSS_MD = "docs/duplicates.cross.md"


def _load_sig(rel):
    """Read a .run/sig.<bin>.jsonl -> (rows, sha1) or (None, None) if absent."""
    p = ROOT / rel
    if not p.exists():
        return None, None
    raw = p.read_bytes()
    return [json.loads(l) for l in raw.decode().splitlines() if l.strip()], hashlib.sha1(raw).hexdigest()


OV_GLOB = ".run/sig.ov_*.jsonl"   # sig_image overlay outputs (convention: ov_<SCxx>_<nnn>)
CROSS_CAP = 200                    # max groups listed per subsection (ranked by collapsible bytes)
MEMBERS_SHOWN = 4                  # sample members per group row (large groups span dozens of overlays)


def cross_report(minins):
    """Phase 11: bucket EVERY binary's functions together; emit docs/duplicates.cross.md. Sources =
    the named BINARIES (main, resident) + every sig_image overlay sig (.run/sig.ov_*.jsonl). A group
    whose members span >1 binary is a cross-binary duplicate (the dedup target an engine/overlay match
    auto-credits — the Phase-12/13 work queue); same-binary groups are where the share machinery is
    first proven. Ranked by collapsible bytes = (count-1)*nins*4 (bytes SAVED — one member stays the
    source). h_exact = guaranteed byte-match; h_norm = candidate (byte-confirm via dedup_integrate)."""
    import glob
    sources, funcs = [], []
    # An onboarded overlay is BOTH a named BINARIES entry AND a .run/sig.ov_*.jsonl glob hit — ingest
    # each overlay ONCE (named ∪ glob, deduped by alias), else its functions count twice and the
    # collapsible-byte figure doubles once the whole fleet is onboarded (the Phase-15 honesty fix, R14).
    # main + resident are listed individually; overlays are summarized as one reproducible source line.
    ov_sigs = {a: cfg["sig"] for a, cfg in BINARIES.items() if a.startswith("ov_")}
    for p in sorted(glob.glob(str(ROOT / OV_GLOB))):
        a = pathlib.Path(p).name[len("sig."):-len(".jsonl")]
        ov_sigs.setdefault(a, str(pathlib.Path(p).relative_to(ROOT)))

    def _ingest(alias, rel):
        rows, sha = _load_sig(rel)
        if rows is None:
            return None
        for r in rows:
            if r['nins'] >= minins and r.get('src') != 'IMPORTED':
                r = dict(r); r['binary'] = alias
                funcs.append(r)
        return sha

    for alias, cfg in BINARIES.items():
        if alias.startswith("ov_"):
            continue   # overlays handled (deduped) below
        sha = _ingest(alias, cfg["sig"])
        sources.append(f"#   {alias:10} {cfg['sig']}  " + (f"sha1={sha}" if sha else "(ABSENT — run sig-refresh)"))
    ov_set = hashlib.sha1(); ov_n = 0
    for alias in sorted(ov_sigs):
        sha = _ingest(alias, ov_sigs[alias])
        if sha:
            ov_set.update(sha.encode()); ov_n += 1
    if ov_n:
        sources.append(f"#   overlays   {ov_n}x (named+sig_image, deduped, nins>={minins})  set-sha1={ov_set.hexdigest()}")

    out = ["# Cross-binary duplicate function groups  (generated by tools/dup_report.py --cross)",
           "# sources:", *sources,
           "# Collapsible bytes = (count-1)*nins*4 (bytes saved; one member stays the source).",
           "# A cross-binary group (binaries>1) is the Phase-12/13 work queue; lead with h_exact",
           "# (guaranteed byte-match), h_norm is candidate-only (byte-confirm via dedup_integrate).",
           f"# Overlay sigs are sig_image (Ghidra-free): h_exact is exact; h_norm is self-consistent.",
           f"# Each subsection lists the top {CROSS_CAP} groups by collapsible bytes; totals are stated.", ""]

    def emit(groups, tier_letter, cls_letter, title):
        total_bytes = sum((len(g) - 1) * g[0]['nins'] * 4 for g in groups)
        cap = f"  (top {CROSS_CAP} of {len(groups)} shown)" if len(groups) > CROSS_CAP else ""
        out.append(f"### {title} — {len(groups)} groups, {total_bytes} collapsible bytes{cap}")
        out.append("| gid | bytes | nins | count | #bin | sample members (binary:addr) |")
        out.append("|---|---|---|---|---|---|")
        for i, g in enumerate(groups[:CROSS_CAP]):
            g = sorted(g, key=lambda r: (r['binary'], r['addr']))
            rep = g[0]
            nbin = len({r['binary'] for r in g})
            shown = "; ".join(f"{r['binary']}:{r['addr']}" for r in g[:MEMBERS_SHOWN])
            if len(g) > MEMBERS_SHOWN:
                shown += f"; …+{len(g) - MEMBERS_SHOWN}"
            out.append(f"| {tier_letter}{cls_letter}{i} | {(len(g) - 1) * rep['nins'] * 4} | {rep['nins']} | "
                       f"{len(g)} | {nbin} | {shown} |")
        out.append("")

    for tier, label, tl in (('h_exact', 'byte-identical', 'e'), ('h_norm', 'structural', 'n')):
        idx = defaultdict(list)
        for r in funcs:
            idx[r[tier]].append(r)
        groups = [g for g in idx.values() if len(g) > 1]
        cross = [g for g in groups if len({r['binary'] for r in g}) > 1]
        intra = [g for g in groups if len({r['binary'] for r in g}) == 1]
        keyf = lambda g: (-(len(g) - 1) * g[0]['nins'] * 4, min((r['binary'], r['addr']) for r in g))
        cross.sort(key=keyf); intra.sort(key=keyf)
        out.append(f"## {tier} ({label})")
        out.append("")
        emit(cross, tl, "x", "cross-binary  (binaries > 1)")
        emit(intra, tl, "i", "intra-binary")

    (ROOT / CROSS_MD).write_text("\n".join(out) + "\n")
    for line in out:
        if line.startswith('#') or line.startswith('##'):
            print(line)


def main():
    import argparse
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("min_ins", nargs="?", type=int, default=8)
    ap.add_argument("--binary", default="main", choices=list(BINARIES))
    ap.add_argument("--cross", action="store_true",
                    help="cross-binary mode: scan all BINARIES -> docs/duplicates.cross.md (ignores --binary)")
    a = ap.parse_args()
    minins = a.min_ins
    if a.cross:
        cross_report(minins)
        return
    cfg = BINARIES[a.binary]
    SIG = ROOT / cfg["sig"]
    MD = ROOT / cfg["md"]
    if not SIG.exists():
        # The signature file is a Ghidra export (`make sig-refresh`), not present until the
        # binary's program has been analyzed + dumped. Degrade gracefully (don't crash the
        # whole `make report`) so a freshly-added binary reports before its Ghidra pass.
        MD.write_text(f"# Duplicate function groups ({a.binary})\n\n"
                      f"_No signature file yet ({cfg['sig']}). Run `make sig-refresh "
                      f"BINARY={a.binary}` after the binary's Ghidra program is analyzed._\n")
        print(f"dup_report: {cfg['sig']} absent — wrote placeholder {cfg['md']} (run sig-refresh first)")
        return
    raw = SIG.read_bytes()
    sig_sha = hashlib.sha1(raw).hexdigest()
    rows = [json.loads(l) for l in raw.decode().splitlines() if l.strip()]
    funcs = [r for r in rows if r['nins'] >= minins and r.get('src') != 'IMPORTED']

    out = ["# EXE-wide duplicate function groups  (generated by tools/dup_report.py)",
           f"# sig: {cfg['sig']}  sha1={sig_sha}  ({len(rows)} funcs, {len(funcs)} with nins>={minins})",
           "# Match the representative once -> share the body to the duplicates (h_exact = guaranteed",
           "# byte-match; h_norm = same source, re-point any single address constant).", ""]

    for tier, label in (('h_exact', 'byte-identical'), ('h_norm', 'structural')):
        idx = defaultdict(list)
        for r in funcs:
            idx[r[tier]].append(r)
        groups = [g for g in idx.values() if len(g) > 1]
        groups.sort(key=lambda g: (-len(g) * g[0]['nins'], g[0]['addr']))
        redundant = sum(len(g) - 1 for g in groups)
        out.append(f"## {tier} ({label}) — nins>={minins}: {len(groups)} groups, {redundant} redundant (collapsible)")
        out.append("| score | nins | count | representative | duplicates |")
        out.append("|---|---|---|---|---|")
        for g in groups:
            g.sort(key=lambda r: r['addr'])
            rep = g[0]
            dups = " ".join(r['addr'] for r in g[1:])
            out.append(f"| {len(g)*rep['nins']} | {rep['nins']} | {len(g)} | "
                       f"{rep['name']} ({rep['addr']}) | {dups} |")
        out.append("")

    MD.write_text("\n".join(out) + "\n")
    # console summary
    for line in out:
        if line.startswith('##') or line.startswith('#'):
            print(line)

if __name__ == "__main__":
    main()

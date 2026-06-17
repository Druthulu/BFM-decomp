#!/usr/bin/env python3
"""Difficulty-ranked inventory of UNMATCHED functions — the harvest queue for matching.

Ghidra-free: parses each unmatched stub's asm/nonmatchings/800/<name>.s for size, control
flow, jump-table presence, and call count, then ranks easiest-first. Jump-table functions
score high (they need the deferred rodata-island workflow, Task 2'). Writes the actionable
easy queue to docs/difficulty.md and the full CSV to .run/difficulty.csv.

Usage: tools/difficulty.py [TOP] [--binary <alias>]   (TOP default 120; binary default main)
"""
import re, sys, pathlib

ROOT = pathlib.Path(__file__).resolve().parent.parent

# Per-binary config (Phase 9). main = the retail EXE (current paths = no-op default).
# The overlay src/asm subtree LAYOUT is a Phase-10 decision (main = the originals).
BINARIES = {
    "main": dict(src="src", asm="asm/nonmatchings", md="docs/difficulty.md", csv=".run/difficulty.csv"),
    "resident": dict(src="src/resident", asm="asm/resident/nonmatchings",
                     md="docs/difficulty.resident.md", csv=".run/difficulty.resident.csv"),
    "ov_SC01_077": dict(src="src/ov_SC01_077", asm="asm/ov_SC01_077/nonmatchings",
                        md="docs/difficulty.ov_SC01_077.md", csv=".run/difficulty.ov_SC01_077.csv"),
    "ov_SC01_005": dict(src="src/ov_SC01_005", asm="asm/ov_SC01_005/nonmatchings",
                        md="docs/difficulty.ov_SC01_005.md", csv=".run/difficulty.ov_SC01_005.csv"),
    "ov_SC01_006": dict(src="src/ov_SC01_006", asm="asm/ov_SC01_006/nonmatchings",
                        md="docs/difficulty.ov_SC01_006.md", csv=".run/difficulty.ov_SC01_006.csv"),
    "ov_SC03_001": dict(src="src/ov_SC03_001", asm="asm/ov_SC03_001/nonmatchings",
                        md="docs/difficulty.ov_SC03_001.md", csv=".run/difficulty.ov_SC03_001.csv"),
    "ov_SC01_000": dict(src="src/ov_SC01_000", asm="asm/ov_SC01_000/nonmatchings",
                        md="docs/difficulty.ov_SC01_000.md", csv=".run/difficulty.ov_SC01_000.csv"),
    "ov_SC01_001": dict(src="src/ov_SC01_001", asm="asm/ov_SC01_001/nonmatchings",
                        md="docs/difficulty.ov_SC01_001.md", csv=".run/difficulty.ov_SC01_001.csv"),
    "ov_SC02_000": dict(src="src/ov_SC02_000", asm="asm/ov_SC02_000/nonmatchings",
                        md="docs/difficulty.ov_SC02_000.md", csv=".run/difficulty.ov_SC02_000.csv"),
    "ov_SC02_003": dict(src="src/ov_SC02_003", asm="asm/ov_SC02_003/nonmatchings",
                        md="docs/difficulty.ov_SC02_003.md", csv=".run/difficulty.ov_SC02_003.csv"),
    "ov_SC03_002": dict(src="src/ov_SC03_002", asm="asm/ov_SC03_002/nonmatchings",
                        md="docs/difficulty.ov_SC03_002.md", csv=".run/difficulty.ov_SC03_002.csv"),
    "ov_SC03_006": dict(src="src/ov_SC03_006", asm="asm/ov_SC03_006/nonmatchings",
                        md="docs/difficulty.ov_SC03_006.md", csv=".run/difficulty.ov_SC03_006.csv"),
    "ov_SC04_000": dict(src="src/ov_SC04_000", asm="asm/ov_SC04_000/nonmatchings",
                        md="docs/difficulty.ov_SC04_000.md", csv=".run/difficulty.ov_SC04_000.csv"),
    "ov_SC04_018": dict(src="src/ov_SC04_018", asm="asm/ov_SC04_018/nonmatchings",
                        md="docs/difficulty.ov_SC04_018.md", csv=".run/difficulty.ov_SC04_018.csv"),
    "ov_SC04_019": dict(src="src/ov_SC04_019", asm="asm/ov_SC04_019/nonmatchings",
                        md="docs/difficulty.ov_SC04_019.md", csv=".run/difficulty.ov_SC04_019.csv"),
    "ov_SC05_000": dict(src="src/ov_SC05_000", asm="asm/ov_SC05_000/nonmatchings",
                        md="docs/difficulty.ov_SC05_000.md", csv=".run/difficulty.ov_SC05_000.csv"),
    "ov_SC06_000": dict(src="src/ov_SC06_000", asm="asm/ov_SC06_000/nonmatchings",
                        md="docs/difficulty.ov_SC06_000.md", csv=".run/difficulty.ov_SC06_000.csv"),
    "ov_SC07_000": dict(src="src/ov_SC07_000", asm="asm/ov_SC07_000/nonmatchings",
                        md="docs/difficulty.ov_SC07_000.md", csv=".run/difficulty.ov_SC07_000.csv"),
    "ov_SC01_004": dict(src="src/ov_SC01_004", asm="asm/ov_SC01_004/nonmatchings",
                        md="docs/difficulty.ov_SC01_004.md", csv=".run/difficulty.ov_SC01_004.csv"),
    "ov_SC01_008": dict(src="src/ov_SC01_008", asm="asm/ov_SC01_008/nonmatchings",
                        md="docs/difficulty.ov_SC01_008.md", csv=".run/difficulty.ov_SC01_008.csv"),
    "ov_SC01_009": dict(src="src/ov_SC01_009", asm="asm/ov_SC01_009/nonmatchings",
                        md="docs/difficulty.ov_SC01_009.md", csv=".run/difficulty.ov_SC01_009.csv"),
    "ov_SC01_074": dict(src="src/ov_SC01_074", asm="asm/ov_SC01_074/nonmatchings",
                        md="docs/difficulty.ov_SC01_074.md", csv=".run/difficulty.ov_SC01_074.csv"),
    "ov_SC01_080": dict(src="src/ov_SC01_080", asm="asm/ov_SC01_080/nonmatchings",
                        md="docs/difficulty.ov_SC01_080.md", csv=".run/difficulty.ov_SC01_080.csv"),
    "ov_SC01_084": dict(src="src/ov_SC01_084", asm="asm/ov_SC01_084/nonmatchings",
                        md="docs/difficulty.ov_SC01_084.md", csv=".run/difficulty.ov_SC01_084.csv"),
    "ov_SC02_004": dict(src="src/ov_SC02_004", asm="asm/ov_SC02_004/nonmatchings",
                        md="docs/difficulty.ov_SC02_004.md", csv=".run/difficulty.ov_SC02_004.csv"),
    "ov_SC02_005": dict(src="src/ov_SC02_005", asm="asm/ov_SC02_005/nonmatchings",
                        md="docs/difficulty.ov_SC02_005.md", csv=".run/difficulty.ov_SC02_005.csv"),
    "ov_SC02_011": dict(src="src/ov_SC02_011", asm="asm/ov_SC02_011/nonmatchings",
                        md="docs/difficulty.ov_SC02_011.md", csv=".run/difficulty.ov_SC02_011.csv"),
    "ov_SC02_015": dict(src="src/ov_SC02_015", asm="asm/ov_SC02_015/nonmatchings",
                        md="docs/difficulty.ov_SC02_015.md", csv=".run/difficulty.ov_SC02_015.csv"),
    "ov_SC02_016": dict(src="src/ov_SC02_016", asm="asm/ov_SC02_016/nonmatchings",
                        md="docs/difficulty.ov_SC02_016.md", csv=".run/difficulty.ov_SC02_016.csv"),
    "ov_SC02_017": dict(src="src/ov_SC02_017", asm="asm/ov_SC02_017/nonmatchings",
                        md="docs/difficulty.ov_SC02_017.md", csv=".run/difficulty.ov_SC02_017.csv"),
    "ov_SC02_021": dict(src="src/ov_SC02_021", asm="asm/ov_SC02_021/nonmatchings",
                        md="docs/difficulty.ov_SC02_021.md", csv=".run/difficulty.ov_SC02_021.csv"),
    "ov_SC02_026": dict(src="src/ov_SC02_026", asm="asm/ov_SC02_026/nonmatchings",
                        md="docs/difficulty.ov_SC02_026.md", csv=".run/difficulty.ov_SC02_026.csv"),
    "ov_SC02_027": dict(src="src/ov_SC02_027", asm="asm/ov_SC02_027/nonmatchings",
                        md="docs/difficulty.ov_SC02_027.md", csv=".run/difficulty.ov_SC02_027.csv"),
    "ov_SC02_028": dict(src="src/ov_SC02_028", asm="asm/ov_SC02_028/nonmatchings",
                        md="docs/difficulty.ov_SC02_028.md", csv=".run/difficulty.ov_SC02_028.csv"),
    "ov_SC02_031": dict(src="src/ov_SC02_031", asm="asm/ov_SC02_031/nonmatchings",
                        md="docs/difficulty.ov_SC02_031.md", csv=".run/difficulty.ov_SC02_031.csv"),
    "ov_SC02_035": dict(src="src/ov_SC02_035", asm="asm/ov_SC02_035/nonmatchings",
                        md="docs/difficulty.ov_SC02_035.md", csv=".run/difficulty.ov_SC02_035.csv"),
    "ov_SC02_039": dict(src="src/ov_SC02_039", asm="asm/ov_SC02_039/nonmatchings",
                        md="docs/difficulty.ov_SC02_039.md", csv=".run/difficulty.ov_SC02_039.csv"),
    "ov_SC02_041": dict(src="src/ov_SC02_041", asm="asm/ov_SC02_041/nonmatchings",
                        md="docs/difficulty.ov_SC02_041.md", csv=".run/difficulty.ov_SC02_041.csv"),
    "ov_SC03_003": dict(src="src/ov_SC03_003", asm="asm/ov_SC03_003/nonmatchings",
                        md="docs/difficulty.ov_SC03_003.md", csv=".run/difficulty.ov_SC03_003.csv"),
    "ov_SC03_007": dict(src="src/ov_SC03_007", asm="asm/ov_SC03_007/nonmatchings",
                        md="docs/difficulty.ov_SC03_007.md", csv=".run/difficulty.ov_SC03_007.csv"),
    "ov_SC03_010": dict(src="src/ov_SC03_010", asm="asm/ov_SC03_010/nonmatchings",
                        md="docs/difficulty.ov_SC03_010.md", csv=".run/difficulty.ov_SC03_010.csv"),
    "ov_SC03_011": dict(src="src/ov_SC03_011", asm="asm/ov_SC03_011/nonmatchings",
                        md="docs/difficulty.ov_SC03_011.md", csv=".run/difficulty.ov_SC03_011.csv"),
    "ov_SC03_012": dict(src="src/ov_SC03_012", asm="asm/ov_SC03_012/nonmatchings",
                        md="docs/difficulty.ov_SC03_012.md", csv=".run/difficulty.ov_SC03_012.csv"),
    "ov_SC03_013": dict(src="src/ov_SC03_013", asm="asm/ov_SC03_013/nonmatchings",
                        md="docs/difficulty.ov_SC03_013.md", csv=".run/difficulty.ov_SC03_013.csv"),
    "ov_SC03_014": dict(src="src/ov_SC03_014", asm="asm/ov_SC03_014/nonmatchings",
                        md="docs/difficulty.ov_SC03_014.md", csv=".run/difficulty.ov_SC03_014.csv"),
    "ov_SC03_015": dict(src="src/ov_SC03_015", asm="asm/ov_SC03_015/nonmatchings",
                        md="docs/difficulty.ov_SC03_015.md", csv=".run/difficulty.ov_SC03_015.csv"),
    "ov_SC03_023": dict(src="src/ov_SC03_023", asm="asm/ov_SC03_023/nonmatchings",
                        md="docs/difficulty.ov_SC03_023.md", csv=".run/difficulty.ov_SC03_023.csv"),
    "ov_SC03_024": dict(src="src/ov_SC03_024", asm="asm/ov_SC03_024/nonmatchings",
                        md="docs/difficulty.ov_SC03_024.md", csv=".run/difficulty.ov_SC03_024.csv"),
    "ov_SC03_028": dict(src="src/ov_SC03_028", asm="asm/ov_SC03_028/nonmatchings",
                        md="docs/difficulty.ov_SC03_028.md", csv=".run/difficulty.ov_SC03_028.csv"),
    "ov_SC03_029": dict(src="src/ov_SC03_029", asm="asm/ov_SC03_029/nonmatchings",
                        md="docs/difficulty.ov_SC03_029.md", csv=".run/difficulty.ov_SC03_029.csv"),
    "ov_SC03_030": dict(src="src/ov_SC03_030", asm="asm/ov_SC03_030/nonmatchings",
                        md="docs/difficulty.ov_SC03_030.md", csv=".run/difficulty.ov_SC03_030.csv"),
    "ov_SC03_031": dict(src="src/ov_SC03_031", asm="asm/ov_SC03_031/nonmatchings",
                        md="docs/difficulty.ov_SC03_031.md", csv=".run/difficulty.ov_SC03_031.csv"),
    "ov_SC03_089": dict(src="src/ov_SC03_089", asm="asm/ov_SC03_089/nonmatchings",
                        md="docs/difficulty.ov_SC03_089.md", csv=".run/difficulty.ov_SC03_089.csv"),
    "ov_SC03_090": dict(src="src/ov_SC03_090", asm="asm/ov_SC03_090/nonmatchings",
                        md="docs/difficulty.ov_SC03_090.md", csv=".run/difficulty.ov_SC03_090.csv"),
    "ov_SC03_091": dict(src="src/ov_SC03_091", asm="asm/ov_SC03_091/nonmatchings",
                        md="docs/difficulty.ov_SC03_091.md", csv=".run/difficulty.ov_SC03_091.csv"),
    "ov_SC03_092": dict(src="src/ov_SC03_092", asm="asm/ov_SC03_092/nonmatchings",
                        md="docs/difficulty.ov_SC03_092.md", csv=".run/difficulty.ov_SC03_092.csv"),
    "ov_SC03_093": dict(src="src/ov_SC03_093", asm="asm/ov_SC03_093/nonmatchings",
                        md="docs/difficulty.ov_SC03_093.md", csv=".run/difficulty.ov_SC03_093.csv"),
    "ov_SC03_094": dict(src="src/ov_SC03_094", asm="asm/ov_SC03_094/nonmatchings",
                        md="docs/difficulty.ov_SC03_094.md", csv=".run/difficulty.ov_SC03_094.csv"),
    "ov_SC03_095": dict(src="src/ov_SC03_095", asm="asm/ov_SC03_095/nonmatchings",
                        md="docs/difficulty.ov_SC03_095.md", csv=".run/difficulty.ov_SC03_095.csv"),
    "ov_SC03_096": dict(src="src/ov_SC03_096", asm="asm/ov_SC03_096/nonmatchings",
                        md="docs/difficulty.ov_SC03_096.md", csv=".run/difficulty.ov_SC03_096.csv"),
    "ov_SC03_097": dict(src="src/ov_SC03_097", asm="asm/ov_SC03_097/nonmatchings",
                        md="docs/difficulty.ov_SC03_097.md", csv=".run/difficulty.ov_SC03_097.csv"),
    "ov_SC03_098": dict(src="src/ov_SC03_098", asm="asm/ov_SC03_098/nonmatchings",
                        md="docs/difficulty.ov_SC03_098.md", csv=".run/difficulty.ov_SC03_098.csv"),
    "ov_SC03_099": dict(src="src/ov_SC03_099", asm="asm/ov_SC03_099/nonmatchings",
                        md="docs/difficulty.ov_SC03_099.md", csv=".run/difficulty.ov_SC03_099.csv"),
    "ov_SC03_100": dict(src="src/ov_SC03_100", asm="asm/ov_SC03_100/nonmatchings",
                        md="docs/difficulty.ov_SC03_100.md", csv=".run/difficulty.ov_SC03_100.csv"),
    "ov_SC03_101": dict(src="src/ov_SC03_101", asm="asm/ov_SC03_101/nonmatchings",
                        md="docs/difficulty.ov_SC03_101.md", csv=".run/difficulty.ov_SC03_101.csv"),
    "ov_SC03_102": dict(src="src/ov_SC03_102", asm="asm/ov_SC03_102/nonmatchings",
                        md="docs/difficulty.ov_SC03_102.md", csv=".run/difficulty.ov_SC03_102.csv"),
    "ov_SC03_103": dict(src="src/ov_SC03_103", asm="asm/ov_SC03_103/nonmatchings",
                        md="docs/difficulty.ov_SC03_103.md", csv=".run/difficulty.ov_SC03_103.csv"),
    "ov_SC03_104": dict(src="src/ov_SC03_104", asm="asm/ov_SC03_104/nonmatchings",
                        md="docs/difficulty.ov_SC03_104.md", csv=".run/difficulty.ov_SC03_104.csv"),
    "ov_SC03_105": dict(src="src/ov_SC03_105", asm="asm/ov_SC03_105/nonmatchings",
                        md="docs/difficulty.ov_SC03_105.md", csv=".run/difficulty.ov_SC03_105.csv"),
    "ov_SC03_108": dict(src="src/ov_SC03_108", asm="asm/ov_SC03_108/nonmatchings",
                        md="docs/difficulty.ov_SC03_108.md", csv=".run/difficulty.ov_SC03_108.csv"),
    "ov_SC03_109": dict(src="src/ov_SC03_109", asm="asm/ov_SC03_109/nonmatchings",
                        md="docs/difficulty.ov_SC03_109.md", csv=".run/difficulty.ov_SC03_109.csv"),
    "ov_SC03_110": dict(src="src/ov_SC03_110", asm="asm/ov_SC03_110/nonmatchings",
                        md="docs/difficulty.ov_SC03_110.md", csv=".run/difficulty.ov_SC03_110.csv"),
    "ov_SC03_111": dict(src="src/ov_SC03_111", asm="asm/ov_SC03_111/nonmatchings",
                        md="docs/difficulty.ov_SC03_111.md", csv=".run/difficulty.ov_SC03_111.csv"),
    "ov_SC03_112": dict(src="src/ov_SC03_112", asm="asm/ov_SC03_112/nonmatchings",
                        md="docs/difficulty.ov_SC03_112.md", csv=".run/difficulty.ov_SC03_112.csv"),
    "ov_SC03_113": dict(src="src/ov_SC03_113", asm="asm/ov_SC03_113/nonmatchings",
                        md="docs/difficulty.ov_SC03_113.md", csv=".run/difficulty.ov_SC03_113.csv"),
    "ov_SC03_114": dict(src="src/ov_SC03_114", asm="asm/ov_SC03_114/nonmatchings",
                        md="docs/difficulty.ov_SC03_114.md", csv=".run/difficulty.ov_SC03_114.csv"),
    "ov_SC03_115": dict(src="src/ov_SC03_115", asm="asm/ov_SC03_115/nonmatchings",
                        md="docs/difficulty.ov_SC03_115.md", csv=".run/difficulty.ov_SC03_115.csv"),
    "ov_SC03_116": dict(src="src/ov_SC03_116", asm="asm/ov_SC03_116/nonmatchings",
                        md="docs/difficulty.ov_SC03_116.md", csv=".run/difficulty.ov_SC03_116.csv"),
    "ov_SC03_117": dict(src="src/ov_SC03_117", asm="asm/ov_SC03_117/nonmatchings",
                        md="docs/difficulty.ov_SC03_117.md", csv=".run/difficulty.ov_SC03_117.csv"),
    "ov_SC03_118": dict(src="src/ov_SC03_118", asm="asm/ov_SC03_118/nonmatchings",
                        md="docs/difficulty.ov_SC03_118.md", csv=".run/difficulty.ov_SC03_118.csv"),
    "ov_SC03_119": dict(src="src/ov_SC03_119", asm="asm/ov_SC03_119/nonmatchings",
                        md="docs/difficulty.ov_SC03_119.md", csv=".run/difficulty.ov_SC03_119.csv"),
    "ov_SC03_121": dict(src="src/ov_SC03_121", asm="asm/ov_SC03_121/nonmatchings",
                        md="docs/difficulty.ov_SC03_121.md", csv=".run/difficulty.ov_SC03_121.csv"),
    "ov_SC03_124": dict(src="src/ov_SC03_124", asm="asm/ov_SC03_124/nonmatchings",
                        md="docs/difficulty.ov_SC03_124.md", csv=".run/difficulty.ov_SC03_124.csv"),
    "ov_SC03_125": dict(src="src/ov_SC03_125", asm="asm/ov_SC03_125/nonmatchings",
                        md="docs/difficulty.ov_SC03_125.md", csv=".run/difficulty.ov_SC03_125.csv"),
    "ov_SC03_126": dict(src="src/ov_SC03_126", asm="asm/ov_SC03_126/nonmatchings",
                        md="docs/difficulty.ov_SC03_126.md", csv=".run/difficulty.ov_SC03_126.csv"),
    "ov_SC04_002": dict(src="src/ov_SC04_002", asm="asm/ov_SC04_002/nonmatchings",
                        md="docs/difficulty.ov_SC04_002.md", csv=".run/difficulty.ov_SC04_002.csv"),
    "ov_SC04_003": dict(src="src/ov_SC04_003", asm="asm/ov_SC04_003/nonmatchings",
                        md="docs/difficulty.ov_SC04_003.md", csv=".run/difficulty.ov_SC04_003.csv"),
    "ov_SC04_004": dict(src="src/ov_SC04_004", asm="asm/ov_SC04_004/nonmatchings",
                        md="docs/difficulty.ov_SC04_004.md", csv=".run/difficulty.ov_SC04_004.csv"),
    "ov_SC04_005": dict(src="src/ov_SC04_005", asm="asm/ov_SC04_005/nonmatchings",
                        md="docs/difficulty.ov_SC04_005.md", csv=".run/difficulty.ov_SC04_005.csv"),
    "ov_SC04_006": dict(src="src/ov_SC04_006", asm="asm/ov_SC04_006/nonmatchings",
                        md="docs/difficulty.ov_SC04_006.md", csv=".run/difficulty.ov_SC04_006.csv"),
    "ov_SC04_007": dict(src="src/ov_SC04_007", asm="asm/ov_SC04_007/nonmatchings",
                        md="docs/difficulty.ov_SC04_007.md", csv=".run/difficulty.ov_SC04_007.csv"),
    "ov_SC04_008": dict(src="src/ov_SC04_008", asm="asm/ov_SC04_008/nonmatchings",
                        md="docs/difficulty.ov_SC04_008.md", csv=".run/difficulty.ov_SC04_008.csv"),
    "ov_SC04_009": dict(src="src/ov_SC04_009", asm="asm/ov_SC04_009/nonmatchings",
                        md="docs/difficulty.ov_SC04_009.md", csv=".run/difficulty.ov_SC04_009.csv"),
    "ov_SC04_010": dict(src="src/ov_SC04_010", asm="asm/ov_SC04_010/nonmatchings",
                        md="docs/difficulty.ov_SC04_010.md", csv=".run/difficulty.ov_SC04_010.csv"),
    "ov_SC04_011": dict(src="src/ov_SC04_011", asm="asm/ov_SC04_011/nonmatchings",
                        md="docs/difficulty.ov_SC04_011.md", csv=".run/difficulty.ov_SC04_011.csv"),
    "ov_SC04_012": dict(src="src/ov_SC04_012", asm="asm/ov_SC04_012/nonmatchings",
                        md="docs/difficulty.ov_SC04_012.md", csv=".run/difficulty.ov_SC04_012.csv"),
    "ov_SC04_015": dict(src="src/ov_SC04_015", asm="asm/ov_SC04_015/nonmatchings",
                        md="docs/difficulty.ov_SC04_015.md", csv=".run/difficulty.ov_SC04_015.csv"),
    "ov_SC04_016": dict(src="src/ov_SC04_016", asm="asm/ov_SC04_016/nonmatchings",
                        md="docs/difficulty.ov_SC04_016.md", csv=".run/difficulty.ov_SC04_016.csv"),
    "ov_SC04_020": dict(src="src/ov_SC04_020", asm="asm/ov_SC04_020/nonmatchings",
                        md="docs/difficulty.ov_SC04_020.md", csv=".run/difficulty.ov_SC04_020.csv"),
    "ov_SC04_021": dict(src="src/ov_SC04_021", asm="asm/ov_SC04_021/nonmatchings",
                        md="docs/difficulty.ov_SC04_021.md", csv=".run/difficulty.ov_SC04_021.csv"),
    "ov_SC05_001": dict(src="src/ov_SC05_001", asm="asm/ov_SC05_001/nonmatchings",
                        md="docs/difficulty.ov_SC05_001.md", csv=".run/difficulty.ov_SC05_001.csv"),
    "ov_SC05_002": dict(src="src/ov_SC05_002", asm="asm/ov_SC05_002/nonmatchings",
                        md="docs/difficulty.ov_SC05_002.md", csv=".run/difficulty.ov_SC05_002.csv"),
    "ov_SC05_003": dict(src="src/ov_SC05_003", asm="asm/ov_SC05_003/nonmatchings",
                        md="docs/difficulty.ov_SC05_003.md", csv=".run/difficulty.ov_SC05_003.csv"),
    "ov_SC05_004": dict(src="src/ov_SC05_004", asm="asm/ov_SC05_004/nonmatchings",
                        md="docs/difficulty.ov_SC05_004.md", csv=".run/difficulty.ov_SC05_004.csv"),
    "ov_SC05_005": dict(src="src/ov_SC05_005", asm="asm/ov_SC05_005/nonmatchings",
                        md="docs/difficulty.ov_SC05_005.md", csv=".run/difficulty.ov_SC05_005.csv"),
    "ov_SC05_006": dict(src="src/ov_SC05_006", asm="asm/ov_SC05_006/nonmatchings",
                        md="docs/difficulty.ov_SC05_006.md", csv=".run/difficulty.ov_SC05_006.csv"),
    "ov_SC05_007": dict(src="src/ov_SC05_007", asm="asm/ov_SC05_007/nonmatchings",
                        md="docs/difficulty.ov_SC05_007.md", csv=".run/difficulty.ov_SC05_007.csv"),
    "ov_SC05_008": dict(src="src/ov_SC05_008", asm="asm/ov_SC05_008/nonmatchings",
                        md="docs/difficulty.ov_SC05_008.md", csv=".run/difficulty.ov_SC05_008.csv"),
    "ov_SC05_009": dict(src="src/ov_SC05_009", asm="asm/ov_SC05_009/nonmatchings",
                        md="docs/difficulty.ov_SC05_009.md", csv=".run/difficulty.ov_SC05_009.csv"),
    "ov_SC05_010": dict(src="src/ov_SC05_010", asm="asm/ov_SC05_010/nonmatchings",
                        md="docs/difficulty.ov_SC05_010.md", csv=".run/difficulty.ov_SC05_010.csv"),
    "ov_SC05_011": dict(src="src/ov_SC05_011", asm="asm/ov_SC05_011/nonmatchings",
                        md="docs/difficulty.ov_SC05_011.md", csv=".run/difficulty.ov_SC05_011.csv"),
    "ov_SC05_017": dict(src="src/ov_SC05_017", asm="asm/ov_SC05_017/nonmatchings",
                        md="docs/difficulty.ov_SC05_017.md", csv=".run/difficulty.ov_SC05_017.csv"),
    "ov_SC05_018": dict(src="src/ov_SC05_018", asm="asm/ov_SC05_018/nonmatchings",
                        md="docs/difficulty.ov_SC05_018.md", csv=".run/difficulty.ov_SC05_018.csv"),
    "ov_SC05_019": dict(src="src/ov_SC05_019", asm="asm/ov_SC05_019/nonmatchings",
                        md="docs/difficulty.ov_SC05_019.md", csv=".run/difficulty.ov_SC05_019.csv"),
    "ov_SC06_006": dict(src="src/ov_SC06_006", asm="asm/ov_SC06_006/nonmatchings",
                        md="docs/difficulty.ov_SC06_006.md", csv=".run/difficulty.ov_SC06_006.csv"),
    "ov_SC06_008": dict(src="src/ov_SC06_008", asm="asm/ov_SC06_008/nonmatchings",
                        md="docs/difficulty.ov_SC06_008.md", csv=".run/difficulty.ov_SC06_008.csv"),
    "ov_SC06_010": dict(src="src/ov_SC06_010", asm="asm/ov_SC06_010/nonmatchings",
                        md="docs/difficulty.ov_SC06_010.md", csv=".run/difficulty.ov_SC06_010.csv"),
    "ov_SC06_011": dict(src="src/ov_SC06_011", asm="asm/ov_SC06_011/nonmatchings",
                        md="docs/difficulty.ov_SC06_011.md", csv=".run/difficulty.ov_SC06_011.csv"),
    "ov_SC06_013": dict(src="src/ov_SC06_013", asm="asm/ov_SC06_013/nonmatchings",
                        md="docs/difficulty.ov_SC06_013.md", csv=".run/difficulty.ov_SC06_013.csv"),
    "ov_SC06_014": dict(src="src/ov_SC06_014", asm="asm/ov_SC06_014/nonmatchings",
                        md="docs/difficulty.ov_SC06_014.md", csv=".run/difficulty.ov_SC06_014.csv"),
    "ov_SC06_015": dict(src="src/ov_SC06_015", asm="asm/ov_SC06_015/nonmatchings",
                        md="docs/difficulty.ov_SC06_015.md", csv=".run/difficulty.ov_SC06_015.csv"),
    "ov_SC06_016": dict(src="src/ov_SC06_016", asm="asm/ov_SC06_016/nonmatchings",
                        md="docs/difficulty.ov_SC06_016.md", csv=".run/difficulty.ov_SC06_016.csv"),
    "ov_SC06_018": dict(src="src/ov_SC06_018", asm="asm/ov_SC06_018/nonmatchings",
                        md="docs/difficulty.ov_SC06_018.md", csv=".run/difficulty.ov_SC06_018.csv"),
    "ov_SC06_020": dict(src="src/ov_SC06_020", asm="asm/ov_SC06_020/nonmatchings",
                        md="docs/difficulty.ov_SC06_020.md", csv=".run/difficulty.ov_SC06_020.csv"),
    "ov_SC06_022": dict(src="src/ov_SC06_022", asm="asm/ov_SC06_022/nonmatchings",
                        md="docs/difficulty.ov_SC06_022.md", csv=".run/difficulty.ov_SC06_022.csv"),
    "ov_SC06_024": dict(src="src/ov_SC06_024", asm="asm/ov_SC06_024/nonmatchings",
                        md="docs/difficulty.ov_SC06_024.md", csv=".run/difficulty.ov_SC06_024.csv"),
    "ov_SC06_025": dict(src="src/ov_SC06_025", asm="asm/ov_SC06_025/nonmatchings",
                        md="docs/difficulty.ov_SC06_025.md", csv=".run/difficulty.ov_SC06_025.csv"),
    "ov_SC06_027": dict(src="src/ov_SC06_027", asm="asm/ov_SC06_027/nonmatchings",
                        md="docs/difficulty.ov_SC06_027.md", csv=".run/difficulty.ov_SC06_027.csv"),
    "ov_SC06_029": dict(src="src/ov_SC06_029", asm="asm/ov_SC06_029/nonmatchings",
                        md="docs/difficulty.ov_SC06_029.md", csv=".run/difficulty.ov_SC06_029.csv"),
    "ov_SC06_030": dict(src="src/ov_SC06_030", asm="asm/ov_SC06_030/nonmatchings",
                        md="docs/difficulty.ov_SC06_030.md", csv=".run/difficulty.ov_SC06_030.csv"),
    "ov_SC06_032": dict(src="src/ov_SC06_032", asm="asm/ov_SC06_032/nonmatchings",
                        md="docs/difficulty.ov_SC06_032.md", csv=".run/difficulty.ov_SC06_032.csv"),
    "ov_SC06_033": dict(src="src/ov_SC06_033", asm="asm/ov_SC06_033/nonmatchings",
                        md="docs/difficulty.ov_SC06_033.md", csv=".run/difficulty.ov_SC06_033.csv"),
    "ov_SC07_001": dict(src="src/ov_SC07_001", asm="asm/ov_SC07_001/nonmatchings",
                        md="docs/difficulty.ov_SC07_001.md", csv=".run/difficulty.ov_SC07_001.csv"),
    "ov_SC07_002": dict(src="src/ov_SC07_002", asm="asm/ov_SC07_002/nonmatchings",
                        md="docs/difficulty.ov_SC07_002.md", csv=".run/difficulty.ov_SC07_002.csv"),
    "ov_SC07_008": dict(src="src/ov_SC07_008", asm="asm/ov_SC07_008/nonmatchings",
                        md="docs/difficulty.ov_SC07_008.md", csv=".run/difficulty.ov_SC07_008.csv"),
    "ov_SC07_009": dict(src="src/ov_SC07_009", asm="asm/ov_SC07_009/nonmatchings",
                        md="docs/difficulty.ov_SC07_009.md", csv=".run/difficulty.ov_SC07_009.csv"),
    # <<< overlays: tools/new_overlay.sh inserts ov_* entries above this line (Phase 13) >>>
}
SRCS = ASM_ROOT = MD = CSV = None    # set by main() from --binary

def find_s(name):
    """Locate <name>.s in any asm/nonmatchings/<seg>/ subdir."""
    for p in sorted(ASM_ROOT.glob(f"*/{name}.s")):
        return p
    return None

INSTR = re.compile(r'^\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+[0-9A-Fa-f]+\s*\*/\s+([a-z][a-z0-9.]*)')
BRANCH = re.compile(r'^b(eq|ne|gez|gtz|lez|ltz|nez|eqz|c1t|c1f|gezal|ltzal)?z?$')

def is_data_blob(txt):
    return 'glabel' not in txt and 'jlabel' not in txt and 'dlabel' in txt

def unmatched_stubs():
    """INCLUDE_ASM names that are real functions (exclude data-blobs) and not inside NON_MATCHING."""
    out = []
    for src in SRCS:
        lines = src.read_text().split('\n'); n = len(lines); i = 0
        while i < n:
            s = lines[i].strip()
            if s.startswith('#ifdef NON_MATCHING'):
                while i < n and not lines[i].strip().startswith('#endif'):
                    i += 1
                i += 1; continue
            m = re.match(r'INCLUDE_ASM\("[^"]+",\s*(\w+)\)', s)
            if m:
                out.append(m.group(1))
            i += 1
    return out

def analyze(name):
    p = find_s(name)
    if p is None: return None
    txt = p.read_text()
    if is_data_blob(txt): return None                     # not a function
    nins = branches = ncalls = 0; last_vaddr = None; jtbl = False
    if 'jtbl_' in txt: jtbl = True
    for ln in txt.splitlines():
        m = INSTR.match(ln)
        if not m: continue
        nins += 1; last_vaddr = int(m.group(1), 16); mn = m.group(2)
        if mn == 'jal': ncalls += 1
        elif mn == 'j': branches += 1
        elif mn == 'jr' and '$ra' not in ln: jtbl = True   # indirect jump = switch/jumptable
        elif BRANCH.match(mn): branches += 1
    score = nins + 3*branches + 25*(1 if jtbl else 0) + 2*ncalls
    return dict(name=name, nins=nins, branches=branches, ncalls=ncalls,
                jtbl=jtbl, leaf=(ncalls == 0), score=score)

def main():
    import argparse
    global SRCS, ASM_ROOT, MD, CSV
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("top", nargs="?", type=int, default=120)
    ap.add_argument("--binary", default="main", choices=list(BINARIES))
    a = ap.parse_args()
    cfg = BINARIES[a.binary]
    SRCS = sorted((ROOT / cfg["src"]).glob("*.c"))
    ASM_ROOT = ROOT / cfg["asm"]
    MD = ROOT / cfg["md"]
    CSV = ROOT / cfg["csv"]
    top = a.top
    rows = [r for r in (analyze(n) for n in unmatched_stubs()) if r]
    rows.sort(key=lambda r: (r['score'], r['name']))

    CSV.parent.mkdir(exist_ok=True)
    CSV.write_text("name,score,nins,branches,ncalls,jtbl,leaf\n" +
                   "".join(f"{r['name']},{r['score']},{r['nins']},{r['branches']},"
                           f"{r['ncalls']},{int(r['jtbl'])},{int(r['leaf'])}\n" for r in rows))

    trivial = sum(1 for r in rows if r['nins'] <= 5)
    leaves  = sum(1 for r in rows if r['leaf'] and not r['jtbl'])
    jtbls   = sum(1 for r in rows if r['jtbl'])
    md = ["# Unmatched difficulty inventory  (generated by tools/difficulty.py — harvest queue)",
          "",
          f"unmatched functions : {len(rows)}",
          f"trivial (<=5 ins)   : {trivial}",
          f"non-jtbl leaves     : {leaves}    (best harvest targets)",
          f"jump-table funcs    : {jtbls}    (deferred — need the rodata-island workflow, Task 2')",
          "",
          f"## Easiest {min(top, len(rows))} unmatched (score asc) — the work queue",
          "| score | name | nins | br | calls | jtbl | leaf |",
          "|---|---|---|---|---|---|---|"]
    for r in rows[:top]:
        md.append(f"| {r['score']} | {r['name']} | {r['nins']} | {r['branches']} | "
                  f"{r['ncalls']} | {'Y' if r['jtbl'] else '-'} | {'Y' if r['leaf'] else '-'} |")
    MD.write_text("\n".join(md) + "\n")
    print("\n".join(md[:9]))
    print(f"... full table -> {MD.relative_to(ROOT)} (top {top}), CSV -> {CSV.relative_to(ROOT)}")

if __name__ == "__main__":
    main()

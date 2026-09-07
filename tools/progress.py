#!/usr/bin/env python3
"""BFM matching-progress report (authoritative; supersedes the Phase-6 PhaseEnd estimate).

Classifies every matchable function across all src/*.c and prints a deterministic summary
(also written to docs/progress.md). Ghidra-free. The REAL count is the number the
Gen1-exit "≥25 matched functions" bar counts (splat-auto empties do NOT count).

Usage:
  tools/progress.py            # print summary + write docs/progress.md
  tools/progress.py --audit    # also verify every empty no-op's asm is exactly {jr,nop}
  tools/progress.py --check     # also hash build/us/SLUS_007.26 vs config/check.us.sha
  tools/progress.py --binary <alias>   # report a non-default binary (default: main = the EXE)
"""
import os, re, sys, hashlib, pathlib
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cdecl                      # §134/R33: the ONE comment/string masking oracle

ROOT = pathlib.Path(__file__).resolve().parent.parent

# Per-binary report config (Phase 9). `main` = the retail EXE; its paths are the originals
# (no-op default). A second binary (Phase 10) adds an entry — its build/check + src/asm tree;
# the overlay src/asm subtree LAYOUT is a Phase-10 decision, not invented here.
BINARIES = {
    "main": dict(build="build/us/SLUS_007.26", check="config/check.us.sha",
                 src="src", asm="asm/nonmatchings", out="docs/progress.md"),
    "resident": dict(build="build/resident/resident", check="config/check.resident.sha",
                     src="src/resident", asm="asm/resident/nonmatchings", out="docs/progress.resident.md"),
    "ov_SC01_077": dict(build="build/ov_SC01_077/ov_SC01_077", check="config/check.ov_SC01_077.sha",
                        src="src/ov_SC01_077", asm="asm/ov_SC01_077/nonmatchings", out="docs/progress.ov_SC01_077.md"),
    "ov_SC01_005": dict(build="build/ov_SC01_005/ov_SC01_005", check="config/check.ov_SC01_005.sha",
                        src="src/ov_SC01_005", asm="asm/ov_SC01_005/nonmatchings", out="docs/progress.ov_SC01_005.md"),
    "ov_SC01_006": dict(build="build/ov_SC01_006/ov_SC01_006", check="config/check.ov_SC01_006.sha",
                        src="src/ov_SC01_006", asm="asm/ov_SC01_006/nonmatchings", out="docs/progress.ov_SC01_006.md"),
    "ov_SC03_001": dict(build="build/ov_SC03_001/ov_SC03_001", check="config/check.ov_SC03_001.sha",
                        src="src/ov_SC03_001", asm="asm/ov_SC03_001/nonmatchings", out="docs/progress.ov_SC03_001.md"),
    "ov_SC01_000": dict(build="build/ov_SC01_000/ov_SC01_000", check="config/check.ov_SC01_000.sha",
                        src="src/ov_SC01_000", asm="asm/ov_SC01_000/nonmatchings", out="docs/progress.ov_SC01_000.md"),
    "ov_SC01_001": dict(build="build/ov_SC01_001/ov_SC01_001", check="config/check.ov_SC01_001.sha",
                        src="src/ov_SC01_001", asm="asm/ov_SC01_001/nonmatchings", out="docs/progress.ov_SC01_001.md"),
    "ov_SC02_000": dict(build="build/ov_SC02_000/ov_SC02_000", check="config/check.ov_SC02_000.sha",
                        src="src/ov_SC02_000", asm="asm/ov_SC02_000/nonmatchings", out="docs/progress.ov_SC02_000.md"),
    "ov_SC02_003": dict(build="build/ov_SC02_003/ov_SC02_003", check="config/check.ov_SC02_003.sha",
                        src="src/ov_SC02_003", asm="asm/ov_SC02_003/nonmatchings", out="docs/progress.ov_SC02_003.md"),
    "ov_SC03_002": dict(build="build/ov_SC03_002/ov_SC03_002", check="config/check.ov_SC03_002.sha",
                        src="src/ov_SC03_002", asm="asm/ov_SC03_002/nonmatchings", out="docs/progress.ov_SC03_002.md"),
    "ov_SC03_006": dict(build="build/ov_SC03_006/ov_SC03_006", check="config/check.ov_SC03_006.sha",
                        src="src/ov_SC03_006", asm="asm/ov_SC03_006/nonmatchings", out="docs/progress.ov_SC03_006.md"),
    "ov_SC04_000": dict(build="build/ov_SC04_000/ov_SC04_000", check="config/check.ov_SC04_000.sha",
                        src="src/ov_SC04_000", asm="asm/ov_SC04_000/nonmatchings", out="docs/progress.ov_SC04_000.md"),
    "ov_SC04_018": dict(build="build/ov_SC04_018/ov_SC04_018", check="config/check.ov_SC04_018.sha",
                        src="src/ov_SC04_018", asm="asm/ov_SC04_018/nonmatchings", out="docs/progress.ov_SC04_018.md"),
    "ov_SC04_019": dict(build="build/ov_SC04_019/ov_SC04_019", check="config/check.ov_SC04_019.sha",
                        src="src/ov_SC04_019", asm="asm/ov_SC04_019/nonmatchings", out="docs/progress.ov_SC04_019.md"),
    "ov_SC05_000": dict(build="build/ov_SC05_000/ov_SC05_000", check="config/check.ov_SC05_000.sha",
                        src="src/ov_SC05_000", asm="asm/ov_SC05_000/nonmatchings", out="docs/progress.ov_SC05_000.md"),
    "ov_SC06_000": dict(build="build/ov_SC06_000/ov_SC06_000", check="config/check.ov_SC06_000.sha",
                        src="src/ov_SC06_000", asm="asm/ov_SC06_000/nonmatchings", out="docs/progress.ov_SC06_000.md"),
    "ov_SC07_000": dict(build="build/ov_SC07_000/ov_SC07_000", check="config/check.ov_SC07_000.sha",
                        src="src/ov_SC07_000", asm="asm/ov_SC07_000/nonmatchings", out="docs/progress.ov_SC07_000.md"),
    "ov_SC01_004": dict(build="build/ov_SC01_004/ov_SC01_004", check="config/check.ov_SC01_004.sha",
                        src="src/ov_SC01_004", asm="asm/ov_SC01_004/nonmatchings", out="docs/progress.ov_SC01_004.md"),
    "ov_SC01_008": dict(build="build/ov_SC01_008/ov_SC01_008", check="config/check.ov_SC01_008.sha",
                        src="src/ov_SC01_008", asm="asm/ov_SC01_008/nonmatchings", out="docs/progress.ov_SC01_008.md"),
    "ov_SC01_009": dict(build="build/ov_SC01_009/ov_SC01_009", check="config/check.ov_SC01_009.sha",
                        src="src/ov_SC01_009", asm="asm/ov_SC01_009/nonmatchings", out="docs/progress.ov_SC01_009.md"),
    "ov_SC01_074": dict(build="build/ov_SC01_074/ov_SC01_074", check="config/check.ov_SC01_074.sha",
                        src="src/ov_SC01_074", asm="asm/ov_SC01_074/nonmatchings", out="docs/progress.ov_SC01_074.md"),
    "ov_SC01_080": dict(build="build/ov_SC01_080/ov_SC01_080", check="config/check.ov_SC01_080.sha",
                        src="src/ov_SC01_080", asm="asm/ov_SC01_080/nonmatchings", out="docs/progress.ov_SC01_080.md"),
    "ov_SC01_084": dict(build="build/ov_SC01_084/ov_SC01_084", check="config/check.ov_SC01_084.sha",
                        src="src/ov_SC01_084", asm="asm/ov_SC01_084/nonmatchings", out="docs/progress.ov_SC01_084.md"),
    "ov_SC02_004": dict(build="build/ov_SC02_004/ov_SC02_004", check="config/check.ov_SC02_004.sha",
                        src="src/ov_SC02_004", asm="asm/ov_SC02_004/nonmatchings", out="docs/progress.ov_SC02_004.md"),
    "ov_SC02_005": dict(build="build/ov_SC02_005/ov_SC02_005", check="config/check.ov_SC02_005.sha",
                        src="src/ov_SC02_005", asm="asm/ov_SC02_005/nonmatchings", out="docs/progress.ov_SC02_005.md"),
    "ov_SC02_011": dict(build="build/ov_SC02_011/ov_SC02_011", check="config/check.ov_SC02_011.sha",
                        src="src/ov_SC02_011", asm="asm/ov_SC02_011/nonmatchings", out="docs/progress.ov_SC02_011.md"),
    "ov_SC02_015": dict(build="build/ov_SC02_015/ov_SC02_015", check="config/check.ov_SC02_015.sha",
                        src="src/ov_SC02_015", asm="asm/ov_SC02_015/nonmatchings", out="docs/progress.ov_SC02_015.md"),
    "ov_SC02_016": dict(build="build/ov_SC02_016/ov_SC02_016", check="config/check.ov_SC02_016.sha",
                        src="src/ov_SC02_016", asm="asm/ov_SC02_016/nonmatchings", out="docs/progress.ov_SC02_016.md"),
    "ov_SC02_017": dict(build="build/ov_SC02_017/ov_SC02_017", check="config/check.ov_SC02_017.sha",
                        src="src/ov_SC02_017", asm="asm/ov_SC02_017/nonmatchings", out="docs/progress.ov_SC02_017.md"),
    "ov_SC02_021": dict(build="build/ov_SC02_021/ov_SC02_021", check="config/check.ov_SC02_021.sha",
                        src="src/ov_SC02_021", asm="asm/ov_SC02_021/nonmatchings", out="docs/progress.ov_SC02_021.md"),
    "ov_SC02_026": dict(build="build/ov_SC02_026/ov_SC02_026", check="config/check.ov_SC02_026.sha",
                        src="src/ov_SC02_026", asm="asm/ov_SC02_026/nonmatchings", out="docs/progress.ov_SC02_026.md"),
    "ov_SC02_027": dict(build="build/ov_SC02_027/ov_SC02_027", check="config/check.ov_SC02_027.sha",
                        src="src/ov_SC02_027", asm="asm/ov_SC02_027/nonmatchings", out="docs/progress.ov_SC02_027.md"),
    "ov_SC02_028": dict(build="build/ov_SC02_028/ov_SC02_028", check="config/check.ov_SC02_028.sha",
                        src="src/ov_SC02_028", asm="asm/ov_SC02_028/nonmatchings", out="docs/progress.ov_SC02_028.md"),
    "ov_SC02_031": dict(build="build/ov_SC02_031/ov_SC02_031", check="config/check.ov_SC02_031.sha",
                        src="src/ov_SC02_031", asm="asm/ov_SC02_031/nonmatchings", out="docs/progress.ov_SC02_031.md"),
    "ov_SC02_035": dict(build="build/ov_SC02_035/ov_SC02_035", check="config/check.ov_SC02_035.sha",
                        src="src/ov_SC02_035", asm="asm/ov_SC02_035/nonmatchings", out="docs/progress.ov_SC02_035.md"),
    "ov_SC02_039": dict(build="build/ov_SC02_039/ov_SC02_039", check="config/check.ov_SC02_039.sha",
                        src="src/ov_SC02_039", asm="asm/ov_SC02_039/nonmatchings", out="docs/progress.ov_SC02_039.md"),
    "ov_SC02_041": dict(build="build/ov_SC02_041/ov_SC02_041", check="config/check.ov_SC02_041.sha",
                        src="src/ov_SC02_041", asm="asm/ov_SC02_041/nonmatchings", out="docs/progress.ov_SC02_041.md"),
    "ov_SC03_003": dict(build="build/ov_SC03_003/ov_SC03_003", check="config/check.ov_SC03_003.sha",
                        src="src/ov_SC03_003", asm="asm/ov_SC03_003/nonmatchings", out="docs/progress.ov_SC03_003.md"),
    "ov_SC03_007": dict(build="build/ov_SC03_007/ov_SC03_007", check="config/check.ov_SC03_007.sha",
                        src="src/ov_SC03_007", asm="asm/ov_SC03_007/nonmatchings", out="docs/progress.ov_SC03_007.md"),
    "ov_SC03_010": dict(build="build/ov_SC03_010/ov_SC03_010", check="config/check.ov_SC03_010.sha",
                        src="src/ov_SC03_010", asm="asm/ov_SC03_010/nonmatchings", out="docs/progress.ov_SC03_010.md"),
    "ov_SC03_011": dict(build="build/ov_SC03_011/ov_SC03_011", check="config/check.ov_SC03_011.sha",
                        src="src/ov_SC03_011", asm="asm/ov_SC03_011/nonmatchings", out="docs/progress.ov_SC03_011.md"),
    "ov_SC03_012": dict(build="build/ov_SC03_012/ov_SC03_012", check="config/check.ov_SC03_012.sha",
                        src="src/ov_SC03_012", asm="asm/ov_SC03_012/nonmatchings", out="docs/progress.ov_SC03_012.md"),
    "ov_SC03_013": dict(build="build/ov_SC03_013/ov_SC03_013", check="config/check.ov_SC03_013.sha",
                        src="src/ov_SC03_013", asm="asm/ov_SC03_013/nonmatchings", out="docs/progress.ov_SC03_013.md"),
    "ov_SC03_014": dict(build="build/ov_SC03_014/ov_SC03_014", check="config/check.ov_SC03_014.sha",
                        src="src/ov_SC03_014", asm="asm/ov_SC03_014/nonmatchings", out="docs/progress.ov_SC03_014.md"),
    "ov_SC03_015": dict(build="build/ov_SC03_015/ov_SC03_015", check="config/check.ov_SC03_015.sha",
                        src="src/ov_SC03_015", asm="asm/ov_SC03_015/nonmatchings", out="docs/progress.ov_SC03_015.md"),
    "ov_SC03_023": dict(build="build/ov_SC03_023/ov_SC03_023", check="config/check.ov_SC03_023.sha",
                        src="src/ov_SC03_023", asm="asm/ov_SC03_023/nonmatchings", out="docs/progress.ov_SC03_023.md"),
    "ov_SC03_024": dict(build="build/ov_SC03_024/ov_SC03_024", check="config/check.ov_SC03_024.sha",
                        src="src/ov_SC03_024", asm="asm/ov_SC03_024/nonmatchings", out="docs/progress.ov_SC03_024.md"),
    "ov_SC03_028": dict(build="build/ov_SC03_028/ov_SC03_028", check="config/check.ov_SC03_028.sha",
                        src="src/ov_SC03_028", asm="asm/ov_SC03_028/nonmatchings", out="docs/progress.ov_SC03_028.md"),
    "ov_SC03_029": dict(build="build/ov_SC03_029/ov_SC03_029", check="config/check.ov_SC03_029.sha",
                        src="src/ov_SC03_029", asm="asm/ov_SC03_029/nonmatchings", out="docs/progress.ov_SC03_029.md"),
    "ov_SC03_030": dict(build="build/ov_SC03_030/ov_SC03_030", check="config/check.ov_SC03_030.sha",
                        src="src/ov_SC03_030", asm="asm/ov_SC03_030/nonmatchings", out="docs/progress.ov_SC03_030.md"),
    "ov_SC03_031": dict(build="build/ov_SC03_031/ov_SC03_031", check="config/check.ov_SC03_031.sha",
                        src="src/ov_SC03_031", asm="asm/ov_SC03_031/nonmatchings", out="docs/progress.ov_SC03_031.md"),
    "ov_SC03_089": dict(build="build/ov_SC03_089/ov_SC03_089", check="config/check.ov_SC03_089.sha",
                        src="src/ov_SC03_089", asm="asm/ov_SC03_089/nonmatchings", out="docs/progress.ov_SC03_089.md"),
    "ov_SC03_090": dict(build="build/ov_SC03_090/ov_SC03_090", check="config/check.ov_SC03_090.sha",
                        src="src/ov_SC03_090", asm="asm/ov_SC03_090/nonmatchings", out="docs/progress.ov_SC03_090.md"),
    "ov_SC03_091": dict(build="build/ov_SC03_091/ov_SC03_091", check="config/check.ov_SC03_091.sha",
                        src="src/ov_SC03_091", asm="asm/ov_SC03_091/nonmatchings", out="docs/progress.ov_SC03_091.md"),
    "ov_SC03_092": dict(build="build/ov_SC03_092/ov_SC03_092", check="config/check.ov_SC03_092.sha",
                        src="src/ov_SC03_092", asm="asm/ov_SC03_092/nonmatchings", out="docs/progress.ov_SC03_092.md"),
    "ov_SC03_093": dict(build="build/ov_SC03_093/ov_SC03_093", check="config/check.ov_SC03_093.sha",
                        src="src/ov_SC03_093", asm="asm/ov_SC03_093/nonmatchings", out="docs/progress.ov_SC03_093.md"),
    "ov_SC03_094": dict(build="build/ov_SC03_094/ov_SC03_094", check="config/check.ov_SC03_094.sha",
                        src="src/ov_SC03_094", asm="asm/ov_SC03_094/nonmatchings", out="docs/progress.ov_SC03_094.md"),
    "ov_SC03_095": dict(build="build/ov_SC03_095/ov_SC03_095", check="config/check.ov_SC03_095.sha",
                        src="src/ov_SC03_095", asm="asm/ov_SC03_095/nonmatchings", out="docs/progress.ov_SC03_095.md"),
    "ov_SC03_096": dict(build="build/ov_SC03_096/ov_SC03_096", check="config/check.ov_SC03_096.sha",
                        src="src/ov_SC03_096", asm="asm/ov_SC03_096/nonmatchings", out="docs/progress.ov_SC03_096.md"),
    "ov_SC03_097": dict(build="build/ov_SC03_097/ov_SC03_097", check="config/check.ov_SC03_097.sha",
                        src="src/ov_SC03_097", asm="asm/ov_SC03_097/nonmatchings", out="docs/progress.ov_SC03_097.md"),
    "ov_SC03_098": dict(build="build/ov_SC03_098/ov_SC03_098", check="config/check.ov_SC03_098.sha",
                        src="src/ov_SC03_098", asm="asm/ov_SC03_098/nonmatchings", out="docs/progress.ov_SC03_098.md"),
    "ov_SC03_099": dict(build="build/ov_SC03_099/ov_SC03_099", check="config/check.ov_SC03_099.sha",
                        src="src/ov_SC03_099", asm="asm/ov_SC03_099/nonmatchings", out="docs/progress.ov_SC03_099.md"),
    "ov_SC03_100": dict(build="build/ov_SC03_100/ov_SC03_100", check="config/check.ov_SC03_100.sha",
                        src="src/ov_SC03_100", asm="asm/ov_SC03_100/nonmatchings", out="docs/progress.ov_SC03_100.md"),
    "ov_SC03_101": dict(build="build/ov_SC03_101/ov_SC03_101", check="config/check.ov_SC03_101.sha",
                        src="src/ov_SC03_101", asm="asm/ov_SC03_101/nonmatchings", out="docs/progress.ov_SC03_101.md"),
    "ov_SC03_102": dict(build="build/ov_SC03_102/ov_SC03_102", check="config/check.ov_SC03_102.sha",
                        src="src/ov_SC03_102", asm="asm/ov_SC03_102/nonmatchings", out="docs/progress.ov_SC03_102.md"),
    "ov_SC03_103": dict(build="build/ov_SC03_103/ov_SC03_103", check="config/check.ov_SC03_103.sha",
                        src="src/ov_SC03_103", asm="asm/ov_SC03_103/nonmatchings", out="docs/progress.ov_SC03_103.md"),
    "ov_SC03_104": dict(build="build/ov_SC03_104/ov_SC03_104", check="config/check.ov_SC03_104.sha",
                        src="src/ov_SC03_104", asm="asm/ov_SC03_104/nonmatchings", out="docs/progress.ov_SC03_104.md"),
    "ov_SC03_105": dict(build="build/ov_SC03_105/ov_SC03_105", check="config/check.ov_SC03_105.sha",
                        src="src/ov_SC03_105", asm="asm/ov_SC03_105/nonmatchings", out="docs/progress.ov_SC03_105.md"),
    "ov_SC03_108": dict(build="build/ov_SC03_108/ov_SC03_108", check="config/check.ov_SC03_108.sha",
                        src="src/ov_SC03_108", asm="asm/ov_SC03_108/nonmatchings", out="docs/progress.ov_SC03_108.md"),
    "ov_SC03_109": dict(build="build/ov_SC03_109/ov_SC03_109", check="config/check.ov_SC03_109.sha",
                        src="src/ov_SC03_109", asm="asm/ov_SC03_109/nonmatchings", out="docs/progress.ov_SC03_109.md"),
    "ov_SC03_110": dict(build="build/ov_SC03_110/ov_SC03_110", check="config/check.ov_SC03_110.sha",
                        src="src/ov_SC03_110", asm="asm/ov_SC03_110/nonmatchings", out="docs/progress.ov_SC03_110.md"),
    "ov_SC03_111": dict(build="build/ov_SC03_111/ov_SC03_111", check="config/check.ov_SC03_111.sha",
                        src="src/ov_SC03_111", asm="asm/ov_SC03_111/nonmatchings", out="docs/progress.ov_SC03_111.md"),
    "ov_SC03_112": dict(build="build/ov_SC03_112/ov_SC03_112", check="config/check.ov_SC03_112.sha",
                        src="src/ov_SC03_112", asm="asm/ov_SC03_112/nonmatchings", out="docs/progress.ov_SC03_112.md"),
    "ov_SC03_113": dict(build="build/ov_SC03_113/ov_SC03_113", check="config/check.ov_SC03_113.sha",
                        src="src/ov_SC03_113", asm="asm/ov_SC03_113/nonmatchings", out="docs/progress.ov_SC03_113.md"),
    "ov_SC03_114": dict(build="build/ov_SC03_114/ov_SC03_114", check="config/check.ov_SC03_114.sha",
                        src="src/ov_SC03_114", asm="asm/ov_SC03_114/nonmatchings", out="docs/progress.ov_SC03_114.md"),
    "ov_SC03_115": dict(build="build/ov_SC03_115/ov_SC03_115", check="config/check.ov_SC03_115.sha",
                        src="src/ov_SC03_115", asm="asm/ov_SC03_115/nonmatchings", out="docs/progress.ov_SC03_115.md"),
    "ov_SC03_116": dict(build="build/ov_SC03_116/ov_SC03_116", check="config/check.ov_SC03_116.sha",
                        src="src/ov_SC03_116", asm="asm/ov_SC03_116/nonmatchings", out="docs/progress.ov_SC03_116.md"),
    "ov_SC03_117": dict(build="build/ov_SC03_117/ov_SC03_117", check="config/check.ov_SC03_117.sha",
                        src="src/ov_SC03_117", asm="asm/ov_SC03_117/nonmatchings", out="docs/progress.ov_SC03_117.md"),
    "ov_SC03_118": dict(build="build/ov_SC03_118/ov_SC03_118", check="config/check.ov_SC03_118.sha",
                        src="src/ov_SC03_118", asm="asm/ov_SC03_118/nonmatchings", out="docs/progress.ov_SC03_118.md"),
    "ov_SC03_119": dict(build="build/ov_SC03_119/ov_SC03_119", check="config/check.ov_SC03_119.sha",
                        src="src/ov_SC03_119", asm="asm/ov_SC03_119/nonmatchings", out="docs/progress.ov_SC03_119.md"),
    "ov_SC03_121": dict(build="build/ov_SC03_121/ov_SC03_121", check="config/check.ov_SC03_121.sha",
                        src="src/ov_SC03_121", asm="asm/ov_SC03_121/nonmatchings", out="docs/progress.ov_SC03_121.md"),
    "ov_SC03_124": dict(build="build/ov_SC03_124/ov_SC03_124", check="config/check.ov_SC03_124.sha",
                        src="src/ov_SC03_124", asm="asm/ov_SC03_124/nonmatchings", out="docs/progress.ov_SC03_124.md"),
    "ov_SC03_125": dict(build="build/ov_SC03_125/ov_SC03_125", check="config/check.ov_SC03_125.sha",
                        src="src/ov_SC03_125", asm="asm/ov_SC03_125/nonmatchings", out="docs/progress.ov_SC03_125.md"),
    "ov_SC03_126": dict(build="build/ov_SC03_126/ov_SC03_126", check="config/check.ov_SC03_126.sha",
                        src="src/ov_SC03_126", asm="asm/ov_SC03_126/nonmatchings", out="docs/progress.ov_SC03_126.md"),
    "ov_SC04_002": dict(build="build/ov_SC04_002/ov_SC04_002", check="config/check.ov_SC04_002.sha",
                        src="src/ov_SC04_002", asm="asm/ov_SC04_002/nonmatchings", out="docs/progress.ov_SC04_002.md"),
    "ov_SC04_003": dict(build="build/ov_SC04_003/ov_SC04_003", check="config/check.ov_SC04_003.sha",
                        src="src/ov_SC04_003", asm="asm/ov_SC04_003/nonmatchings", out="docs/progress.ov_SC04_003.md"),
    "ov_SC04_004": dict(build="build/ov_SC04_004/ov_SC04_004", check="config/check.ov_SC04_004.sha",
                        src="src/ov_SC04_004", asm="asm/ov_SC04_004/nonmatchings", out="docs/progress.ov_SC04_004.md"),
    "ov_SC04_005": dict(build="build/ov_SC04_005/ov_SC04_005", check="config/check.ov_SC04_005.sha",
                        src="src/ov_SC04_005", asm="asm/ov_SC04_005/nonmatchings", out="docs/progress.ov_SC04_005.md"),
    "ov_SC04_006": dict(build="build/ov_SC04_006/ov_SC04_006", check="config/check.ov_SC04_006.sha",
                        src="src/ov_SC04_006", asm="asm/ov_SC04_006/nonmatchings", out="docs/progress.ov_SC04_006.md"),
    "ov_SC04_007": dict(build="build/ov_SC04_007/ov_SC04_007", check="config/check.ov_SC04_007.sha",
                        src="src/ov_SC04_007", asm="asm/ov_SC04_007/nonmatchings", out="docs/progress.ov_SC04_007.md"),
    "ov_SC04_008": dict(build="build/ov_SC04_008/ov_SC04_008", check="config/check.ov_SC04_008.sha",
                        src="src/ov_SC04_008", asm="asm/ov_SC04_008/nonmatchings", out="docs/progress.ov_SC04_008.md"),
    "ov_SC04_009": dict(build="build/ov_SC04_009/ov_SC04_009", check="config/check.ov_SC04_009.sha",
                        src="src/ov_SC04_009", asm="asm/ov_SC04_009/nonmatchings", out="docs/progress.ov_SC04_009.md"),
    "ov_SC04_010": dict(build="build/ov_SC04_010/ov_SC04_010", check="config/check.ov_SC04_010.sha",
                        src="src/ov_SC04_010", asm="asm/ov_SC04_010/nonmatchings", out="docs/progress.ov_SC04_010.md"),
    "ov_SC04_011": dict(build="build/ov_SC04_011/ov_SC04_011", check="config/check.ov_SC04_011.sha",
                        src="src/ov_SC04_011", asm="asm/ov_SC04_011/nonmatchings", out="docs/progress.ov_SC04_011.md"),
    "ov_SC04_012": dict(build="build/ov_SC04_012/ov_SC04_012", check="config/check.ov_SC04_012.sha",
                        src="src/ov_SC04_012", asm="asm/ov_SC04_012/nonmatchings", out="docs/progress.ov_SC04_012.md"),
    "ov_SC04_015": dict(build="build/ov_SC04_015/ov_SC04_015", check="config/check.ov_SC04_015.sha",
                        src="src/ov_SC04_015", asm="asm/ov_SC04_015/nonmatchings", out="docs/progress.ov_SC04_015.md"),
    "ov_SC04_016": dict(build="build/ov_SC04_016/ov_SC04_016", check="config/check.ov_SC04_016.sha",
                        src="src/ov_SC04_016", asm="asm/ov_SC04_016/nonmatchings", out="docs/progress.ov_SC04_016.md"),
    "ov_SC04_020": dict(build="build/ov_SC04_020/ov_SC04_020", check="config/check.ov_SC04_020.sha",
                        src="src/ov_SC04_020", asm="asm/ov_SC04_020/nonmatchings", out="docs/progress.ov_SC04_020.md"),
    "ov_SC04_021": dict(build="build/ov_SC04_021/ov_SC04_021", check="config/check.ov_SC04_021.sha",
                        src="src/ov_SC04_021", asm="asm/ov_SC04_021/nonmatchings", out="docs/progress.ov_SC04_021.md"),
    "ov_SC05_001": dict(build="build/ov_SC05_001/ov_SC05_001", check="config/check.ov_SC05_001.sha",
                        src="src/ov_SC05_001", asm="asm/ov_SC05_001/nonmatchings", out="docs/progress.ov_SC05_001.md"),
    "ov_SC05_002": dict(build="build/ov_SC05_002/ov_SC05_002", check="config/check.ov_SC05_002.sha",
                        src="src/ov_SC05_002", asm="asm/ov_SC05_002/nonmatchings", out="docs/progress.ov_SC05_002.md"),
    "ov_SC05_003": dict(build="build/ov_SC05_003/ov_SC05_003", check="config/check.ov_SC05_003.sha",
                        src="src/ov_SC05_003", asm="asm/ov_SC05_003/nonmatchings", out="docs/progress.ov_SC05_003.md"),
    "ov_SC05_004": dict(build="build/ov_SC05_004/ov_SC05_004", check="config/check.ov_SC05_004.sha",
                        src="src/ov_SC05_004", asm="asm/ov_SC05_004/nonmatchings", out="docs/progress.ov_SC05_004.md"),
    "ov_SC05_005": dict(build="build/ov_SC05_005/ov_SC05_005", check="config/check.ov_SC05_005.sha",
                        src="src/ov_SC05_005", asm="asm/ov_SC05_005/nonmatchings", out="docs/progress.ov_SC05_005.md"),
    "ov_SC05_006": dict(build="build/ov_SC05_006/ov_SC05_006", check="config/check.ov_SC05_006.sha",
                        src="src/ov_SC05_006", asm="asm/ov_SC05_006/nonmatchings", out="docs/progress.ov_SC05_006.md"),
    "ov_SC05_007": dict(build="build/ov_SC05_007/ov_SC05_007", check="config/check.ov_SC05_007.sha",
                        src="src/ov_SC05_007", asm="asm/ov_SC05_007/nonmatchings", out="docs/progress.ov_SC05_007.md"),
    "ov_SC05_008": dict(build="build/ov_SC05_008/ov_SC05_008", check="config/check.ov_SC05_008.sha",
                        src="src/ov_SC05_008", asm="asm/ov_SC05_008/nonmatchings", out="docs/progress.ov_SC05_008.md"),
    "ov_SC05_009": dict(build="build/ov_SC05_009/ov_SC05_009", check="config/check.ov_SC05_009.sha",
                        src="src/ov_SC05_009", asm="asm/ov_SC05_009/nonmatchings", out="docs/progress.ov_SC05_009.md"),
    "ov_SC05_010": dict(build="build/ov_SC05_010/ov_SC05_010", check="config/check.ov_SC05_010.sha",
                        src="src/ov_SC05_010", asm="asm/ov_SC05_010/nonmatchings", out="docs/progress.ov_SC05_010.md"),
    "ov_SC05_011": dict(build="build/ov_SC05_011/ov_SC05_011", check="config/check.ov_SC05_011.sha",
                        src="src/ov_SC05_011", asm="asm/ov_SC05_011/nonmatchings", out="docs/progress.ov_SC05_011.md"),
    "ov_SC05_017": dict(build="build/ov_SC05_017/ov_SC05_017", check="config/check.ov_SC05_017.sha",
                        src="src/ov_SC05_017", asm="asm/ov_SC05_017/nonmatchings", out="docs/progress.ov_SC05_017.md"),
    "ov_SC05_018": dict(build="build/ov_SC05_018/ov_SC05_018", check="config/check.ov_SC05_018.sha",
                        src="src/ov_SC05_018", asm="asm/ov_SC05_018/nonmatchings", out="docs/progress.ov_SC05_018.md"),
    "ov_SC05_019": dict(build="build/ov_SC05_019/ov_SC05_019", check="config/check.ov_SC05_019.sha",
                        src="src/ov_SC05_019", asm="asm/ov_SC05_019/nonmatchings", out="docs/progress.ov_SC05_019.md"),
    "ov_SC06_006": dict(build="build/ov_SC06_006/ov_SC06_006", check="config/check.ov_SC06_006.sha",
                        src="src/ov_SC06_006", asm="asm/ov_SC06_006/nonmatchings", out="docs/progress.ov_SC06_006.md"),
    "ov_SC06_008": dict(build="build/ov_SC06_008/ov_SC06_008", check="config/check.ov_SC06_008.sha",
                        src="src/ov_SC06_008", asm="asm/ov_SC06_008/nonmatchings", out="docs/progress.ov_SC06_008.md"),
    "ov_SC06_010": dict(build="build/ov_SC06_010/ov_SC06_010", check="config/check.ov_SC06_010.sha",
                        src="src/ov_SC06_010", asm="asm/ov_SC06_010/nonmatchings", out="docs/progress.ov_SC06_010.md"),
    "ov_SC06_011": dict(build="build/ov_SC06_011/ov_SC06_011", check="config/check.ov_SC06_011.sha",
                        src="src/ov_SC06_011", asm="asm/ov_SC06_011/nonmatchings", out="docs/progress.ov_SC06_011.md"),
    "ov_SC06_013": dict(build="build/ov_SC06_013/ov_SC06_013", check="config/check.ov_SC06_013.sha",
                        src="src/ov_SC06_013", asm="asm/ov_SC06_013/nonmatchings", out="docs/progress.ov_SC06_013.md"),
    "ov_SC06_014": dict(build="build/ov_SC06_014/ov_SC06_014", check="config/check.ov_SC06_014.sha",
                        src="src/ov_SC06_014", asm="asm/ov_SC06_014/nonmatchings", out="docs/progress.ov_SC06_014.md"),
    "ov_SC06_015": dict(build="build/ov_SC06_015/ov_SC06_015", check="config/check.ov_SC06_015.sha",
                        src="src/ov_SC06_015", asm="asm/ov_SC06_015/nonmatchings", out="docs/progress.ov_SC06_015.md"),
    "ov_SC06_016": dict(build="build/ov_SC06_016/ov_SC06_016", check="config/check.ov_SC06_016.sha",
                        src="src/ov_SC06_016", asm="asm/ov_SC06_016/nonmatchings", out="docs/progress.ov_SC06_016.md"),
    "ov_SC06_018": dict(build="build/ov_SC06_018/ov_SC06_018", check="config/check.ov_SC06_018.sha",
                        src="src/ov_SC06_018", asm="asm/ov_SC06_018/nonmatchings", out="docs/progress.ov_SC06_018.md"),
    "ov_SC06_020": dict(build="build/ov_SC06_020/ov_SC06_020", check="config/check.ov_SC06_020.sha",
                        src="src/ov_SC06_020", asm="asm/ov_SC06_020/nonmatchings", out="docs/progress.ov_SC06_020.md"),
    "ov_SC06_022": dict(build="build/ov_SC06_022/ov_SC06_022", check="config/check.ov_SC06_022.sha",
                        src="src/ov_SC06_022", asm="asm/ov_SC06_022/nonmatchings", out="docs/progress.ov_SC06_022.md"),
    "ov_SC06_024": dict(build="build/ov_SC06_024/ov_SC06_024", check="config/check.ov_SC06_024.sha",
                        src="src/ov_SC06_024", asm="asm/ov_SC06_024/nonmatchings", out="docs/progress.ov_SC06_024.md"),
    "ov_SC06_025": dict(build="build/ov_SC06_025/ov_SC06_025", check="config/check.ov_SC06_025.sha",
                        src="src/ov_SC06_025", asm="asm/ov_SC06_025/nonmatchings", out="docs/progress.ov_SC06_025.md"),
    "ov_SC06_027": dict(build="build/ov_SC06_027/ov_SC06_027", check="config/check.ov_SC06_027.sha",
                        src="src/ov_SC06_027", asm="asm/ov_SC06_027/nonmatchings", out="docs/progress.ov_SC06_027.md"),
    "ov_SC06_029": dict(build="build/ov_SC06_029/ov_SC06_029", check="config/check.ov_SC06_029.sha",
                        src="src/ov_SC06_029", asm="asm/ov_SC06_029/nonmatchings", out="docs/progress.ov_SC06_029.md"),
    "ov_SC06_030": dict(build="build/ov_SC06_030/ov_SC06_030", check="config/check.ov_SC06_030.sha",
                        src="src/ov_SC06_030", asm="asm/ov_SC06_030/nonmatchings", out="docs/progress.ov_SC06_030.md"),
    "ov_SC06_032": dict(build="build/ov_SC06_032/ov_SC06_032", check="config/check.ov_SC06_032.sha",
                        src="src/ov_SC06_032", asm="asm/ov_SC06_032/nonmatchings", out="docs/progress.ov_SC06_032.md"),
    "ov_SC06_033": dict(build="build/ov_SC06_033/ov_SC06_033", check="config/check.ov_SC06_033.sha",
                        src="src/ov_SC06_033", asm="asm/ov_SC06_033/nonmatchings", out="docs/progress.ov_SC06_033.md"),
    "ov_SC07_001": dict(build="build/ov_SC07_001/ov_SC07_001", check="config/check.ov_SC07_001.sha",
                        src="src/ov_SC07_001", asm="asm/ov_SC07_001/nonmatchings", out="docs/progress.ov_SC07_001.md"),
    "ov_SC07_002": dict(build="build/ov_SC07_002/ov_SC07_002", check="config/check.ov_SC07_002.sha",
                        src="src/ov_SC07_002", asm="asm/ov_SC07_002/nonmatchings", out="docs/progress.ov_SC07_002.md"),
    "ov_SC07_008": dict(build="build/ov_SC07_008/ov_SC07_008", check="config/check.ov_SC07_008.sha",
                        src="src/ov_SC07_008", asm="asm/ov_SC07_008/nonmatchings", out="docs/progress.ov_SC07_008.md"),
    "ov_SC07_009": dict(build="build/ov_SC07_009/ov_SC07_009", check="config/check.ov_SC07_009.sha",
                        src="src/ov_SC07_009", asm="asm/ov_SC07_009/nonmatchings", out="docs/progress.ov_SC07_009.md"),
    "ov_SC07_006": dict(build="build/ov_SC07_006/ov_SC07_006", check="config/check.ov_SC07_006.sha",
                        src="src/ov_SC07_006", asm="asm/ov_SC07_006/nonmatchings", out="docs/progress.ov_SC07_006.md"),
    "ov_SC07_007": dict(build="build/ov_SC07_007/ov_SC07_007", check="config/check.ov_SC07_007.sha",
                        src="src/ov_SC07_007", asm="asm/ov_SC07_007/nonmatchings", out="docs/progress.ov_SC07_007.md"),
    "ov_SC07_010": dict(build="build/ov_SC07_010/ov_SC07_010", check="config/check.ov_SC07_010.sha",
                        src="src/ov_SC07_010", asm="asm/ov_SC07_010/nonmatchings", out="docs/progress.ov_SC07_010.md"),
    "ov_SC07_011": dict(build="build/ov_SC07_011/ov_SC07_011", check="config/check.ov_SC07_011.sha",
                        src="src/ov_SC07_011", asm="asm/ov_SC07_011/nonmatchings", out="docs/progress.ov_SC07_011.md"),
    "ov_MAIN_012": dict(build="build/ov_MAIN_012/ov_MAIN_012", check="config/check.ov_MAIN_012.sha",
                        src="src/ov_MAIN_012", asm="asm/ov_MAIN_012/nonmatchings", out="docs/progress.ov_MAIN_012.md"),
    "ov_SC02_037": dict(build="build/ov_SC02_037/ov_SC02_037", check="config/check.ov_SC02_037.sha",
                        src="src/ov_SC02_037", asm="asm/ov_SC02_037/nonmatchings", out="docs/progress.ov_SC02_037.md"),
    "ov_SC03_107": dict(build="build/ov_SC03_107/ov_SC03_107", check="config/check.ov_SC03_107.sha",
                        src="src/ov_SC03_107", asm="asm/ov_SC03_107/nonmatchings", out="docs/progress.ov_SC03_107.md"),
    "md_MAIN_013": dict(build="build/md_MAIN_013/md_MAIN_013", check="config/check.md_MAIN_013.sha",
                        src="src/md_MAIN_013", asm="asm/md_MAIN_013/nonmatchings", out="docs/progress.md_MAIN_013.md"),
    "md_MAIN_014": dict(build="build/md_MAIN_014/md_MAIN_014", check="config/check.md_MAIN_014.sha",
                        src="src/md_MAIN_014", asm="asm/md_MAIN_014/nonmatchings", out="docs/progress.md_MAIN_014.md"),
    "md_MAIN_015": dict(build="build/md_MAIN_015/md_MAIN_015", check="config/check.md_MAIN_015.sha",
                        src="src/md_MAIN_015", asm="asm/md_MAIN_015/nonmatchings", out="docs/progress.md_MAIN_015.md"),
    "md_MAIN_016": dict(build="build/md_MAIN_016/md_MAIN_016", check="config/check.md_MAIN_016.sha",
                        src="src/md_MAIN_016", asm="asm/md_MAIN_016/nonmatchings", out="docs/progress.md_MAIN_016.md"),
    "md_MAIN_017": dict(build="build/md_MAIN_017/md_MAIN_017", check="config/check.md_MAIN_017.sha",
                        src="src/md_MAIN_017", asm="asm/md_MAIN_017/nonmatchings", out="docs/progress.md_MAIN_017.md"),
    "md_MAIN_018": dict(build="build/md_MAIN_018/md_MAIN_018", check="config/check.md_MAIN_018.sha",
                        src="src/md_MAIN_018", asm="asm/md_MAIN_018/nonmatchings", out="docs/progress.md_MAIN_018.md"),
    "md_MAIN_019": dict(build="build/md_MAIN_019/md_MAIN_019", check="config/check.md_MAIN_019.sha",
                        src="src/md_MAIN_019", asm="asm/md_MAIN_019/nonmatchings", out="docs/progress.md_MAIN_019.md"),
    "md_MAIN_020": dict(build="build/md_MAIN_020/md_MAIN_020", check="config/check.md_MAIN_020.sha",
                        src="src/md_MAIN_020", asm="asm/md_MAIN_020/nonmatchings", out="docs/progress.md_MAIN_020.md"),
    "md_MAIN_021": dict(build="build/md_MAIN_021/md_MAIN_021", check="config/check.md_MAIN_021.sha",
                        src="src/md_MAIN_021", asm="asm/md_MAIN_021/nonmatchings", out="docs/progress.md_MAIN_021.md"),
    "md_MAIN_022": dict(build="build/md_MAIN_022/md_MAIN_022", check="config/check.md_MAIN_022.sha",
                        src="src/md_MAIN_022", asm="asm/md_MAIN_022/nonmatchings", out="docs/progress.md_MAIN_022.md"),
    "md_MAIN_023": dict(build="build/md_MAIN_023/md_MAIN_023", check="config/check.md_MAIN_023.sha",
                        src="src/md_MAIN_023", asm="asm/md_MAIN_023/nonmatchings", out="docs/progress.md_MAIN_023.md"),
    "md_MAIN_024": dict(build="build/md_MAIN_024/md_MAIN_024", check="config/check.md_MAIN_024.sha",
                        src="src/md_MAIN_024", asm="asm/md_MAIN_024/nonmatchings", out="docs/progress.md_MAIN_024.md"),
    "md_MAIN_025": dict(build="build/md_MAIN_025/md_MAIN_025", check="config/check.md_MAIN_025.sha",
                        src="src/md_MAIN_025", asm="asm/md_MAIN_025/nonmatchings", out="docs/progress.md_MAIN_025.md"),
    "md_MAIN_026": dict(build="build/md_MAIN_026/md_MAIN_026", check="config/check.md_MAIN_026.sha",
                        src="src/md_MAIN_026", asm="asm/md_MAIN_026/nonmatchings", out="docs/progress.md_MAIN_026.md"),
    "md_MAIN_027": dict(build="build/md_MAIN_027/md_MAIN_027", check="config/check.md_MAIN_027.sha",
                        src="src/md_MAIN_027", asm="asm/md_MAIN_027/nonmatchings", out="docs/progress.md_MAIN_027.md"),
    "md_MAIN_028": dict(build="build/md_MAIN_028/md_MAIN_028", check="config/check.md_MAIN_028.sha",
                        src="src/md_MAIN_028", asm="asm/md_MAIN_028/nonmatchings", out="docs/progress.md_MAIN_028.md"),
    "md_MAIN_029": dict(build="build/md_MAIN_029/md_MAIN_029", check="config/check.md_MAIN_029.sha",
                        src="src/md_MAIN_029", asm="asm/md_MAIN_029/nonmatchings", out="docs/progress.md_MAIN_029.md"),
    "md_MAIN_030": dict(build="build/md_MAIN_030/md_MAIN_030", check="config/check.md_MAIN_030.sha",
                        src="src/md_MAIN_030", asm="asm/md_MAIN_030/nonmatchings", out="docs/progress.md_MAIN_030.md"),
    "md_MAIN_031": dict(build="build/md_MAIN_031/md_MAIN_031", check="config/check.md_MAIN_031.sha",
                        src="src/md_MAIN_031", asm="asm/md_MAIN_031/nonmatchings", out="docs/progress.md_MAIN_031.md"),
    "md_MAIN_032": dict(build="build/md_MAIN_032/md_MAIN_032", check="config/check.md_MAIN_032.sha",
                        src="src/md_MAIN_032", asm="asm/md_MAIN_032/nonmatchings", out="docs/progress.md_MAIN_032.md"),
    "md_MAIN_033": dict(build="build/md_MAIN_033/md_MAIN_033", check="config/check.md_MAIN_033.sha",
                        src="src/md_MAIN_033", asm="asm/md_MAIN_033/nonmatchings", out="docs/progress.md_MAIN_033.md"),
    "md_MAIN_034": dict(build="build/md_MAIN_034/md_MAIN_034", check="config/check.md_MAIN_034.sha",
                        src="src/md_MAIN_034", asm="asm/md_MAIN_034/nonmatchings", out="docs/progress.md_MAIN_034.md"),
    "md_MAIN_035": dict(build="build/md_MAIN_035/md_MAIN_035", check="config/check.md_MAIN_035.sha",
                        src="src/md_MAIN_035", asm="asm/md_MAIN_035/nonmatchings", out="docs/progress.md_MAIN_035.md"),
    "md_MAIN_036": dict(build="build/md_MAIN_036/md_MAIN_036", check="config/check.md_MAIN_036.sha",
                        src="src/md_MAIN_036", asm="asm/md_MAIN_036/nonmatchings", out="docs/progress.md_MAIN_036.md"),
    "md_MAIN_037": dict(build="build/md_MAIN_037/md_MAIN_037", check="config/check.md_MAIN_037.sha",
                        src="src/md_MAIN_037", asm="asm/md_MAIN_037/nonmatchings", out="docs/progress.md_MAIN_037.md"),
    "md_MAIN_038": dict(build="build/md_MAIN_038/md_MAIN_038", check="config/check.md_MAIN_038.sha",
                        src="src/md_MAIN_038", asm="asm/md_MAIN_038/nonmatchings", out="docs/progress.md_MAIN_038.md"),
    "md_MAIN_039": dict(build="build/md_MAIN_039/md_MAIN_039", check="config/check.md_MAIN_039.sha",
                        src="src/md_MAIN_039", asm="asm/md_MAIN_039/nonmatchings", out="docs/progress.md_MAIN_039.md"),
    "md_MAIN_040": dict(build="build/md_MAIN_040/md_MAIN_040", check="config/check.md_MAIN_040.sha",
                        src="src/md_MAIN_040", asm="asm/md_MAIN_040/nonmatchings", out="docs/progress.md_MAIN_040.md"),
    "md_MAIN_041": dict(build="build/md_MAIN_041/md_MAIN_041", check="config/check.md_MAIN_041.sha",
                        src="src/md_MAIN_041", asm="asm/md_MAIN_041/nonmatchings", out="docs/progress.md_MAIN_041.md"),
    "md_MAIN_042": dict(build="build/md_MAIN_042/md_MAIN_042", check="config/check.md_MAIN_042.sha",
                        src="src/md_MAIN_042", asm="asm/md_MAIN_042/nonmatchings", out="docs/progress.md_MAIN_042.md"),
    "md_MAIN_043": dict(build="build/md_MAIN_043/md_MAIN_043", check="config/check.md_MAIN_043.sha",
                        src="src/md_MAIN_043", asm="asm/md_MAIN_043/nonmatchings", out="docs/progress.md_MAIN_043.md"),
    "md_MAIN_044": dict(build="build/md_MAIN_044/md_MAIN_044", check="config/check.md_MAIN_044.sha",
                        src="src/md_MAIN_044", asm="asm/md_MAIN_044/nonmatchings", out="docs/progress.md_MAIN_044.md"),
    "md_MAIN_045": dict(build="build/md_MAIN_045/md_MAIN_045", check="config/check.md_MAIN_045.sha",
                        src="src/md_MAIN_045", asm="asm/md_MAIN_045/nonmatchings", out="docs/progress.md_MAIN_045.md"),
    "md_MAIN_046": dict(build="build/md_MAIN_046/md_MAIN_046", check="config/check.md_MAIN_046.sha",
                        src="src/md_MAIN_046", asm="asm/md_MAIN_046/nonmatchings", out="docs/progress.md_MAIN_046.md"),
    "md_MAIN_047": dict(build="build/md_MAIN_047/md_MAIN_047", check="config/check.md_MAIN_047.sha",
                        src="src/md_MAIN_047", asm="asm/md_MAIN_047/nonmatchings", out="docs/progress.md_MAIN_047.md"),
    "md_MAIN_001": dict(build="build/md_MAIN_001/md_MAIN_001", check="config/check.md_MAIN_001.sha",
                        src="src/md_MAIN_001", asm="asm/md_MAIN_001/nonmatchings", out="docs/progress.md_MAIN_001.md"),
    "md_MAIN_008": dict(build="build/md_MAIN_008/md_MAIN_008", check="config/check.md_MAIN_008.sha",
                        src="src/md_MAIN_008", asm="asm/md_MAIN_008/nonmatchings", out="docs/progress.md_MAIN_008.md"),
    "md_MAIN_011": dict(build="build/md_MAIN_011/md_MAIN_011", check="config/check.md_MAIN_011.sha",
                        src="src/md_MAIN_011", asm="asm/md_MAIN_011/nonmatchings", out="docs/progress.md_MAIN_011.md"),
    "md_SC07_003": dict(build="build/md_SC07_003/md_SC07_003", check="config/check.md_SC07_003.sha",
                        src="src/md_SC07_003", asm="asm/md_SC07_003/nonmatchings", out="docs/progress.md_SC07_003.md"),
    "md_SC07_004": dict(build="build/md_SC07_004/md_SC07_004", check="config/check.md_SC07_004.sha",
                        src="src/md_SC07_004", asm="asm/md_SC07_004/nonmatchings", out="docs/progress.md_SC07_004.md"),
    "md_MAIN_003": dict(build="build/md_MAIN_003/md_MAIN_003", check="config/check.md_MAIN_003.sha",
                        src="src/md_MAIN_003", asm="asm/md_MAIN_003/nonmatchings", out="docs/progress.md_MAIN_003.md"),
    "md_SC03_073": dict(build="build/md_SC03_073/md_SC03_073", check="config/check.md_SC03_073.sha",
                        src="src/md_SC03_073", asm="asm/md_SC03_073/nonmatchings", out="docs/progress.md_SC03_073.md"),
    "md_SC03_074": dict(build="build/md_SC03_074/md_SC03_074", check="config/check.md_SC03_074.sha",
                        src="src/md_SC03_074", asm="asm/md_SC03_074/nonmatchings", out="docs/progress.md_SC03_074.md"),
    "md_SC03_075": dict(build="build/md_SC03_075/md_SC03_075", check="config/check.md_SC03_075.sha",
                        src="src/md_SC03_075", asm="asm/md_SC03_075/nonmatchings", out="docs/progress.md_SC03_075.md"),
    "md_SC03_076": dict(build="build/md_SC03_076/md_SC03_076", check="config/check.md_SC03_076.sha",
                        src="src/md_SC03_076", asm="asm/md_SC03_076/nonmatchings", out="docs/progress.md_SC03_076.md"),
    "md_SC03_077": dict(build="build/md_SC03_077/md_SC03_077", check="config/check.md_SC03_077.sha",
                        src="src/md_SC03_077", asm="asm/md_SC03_077/nonmatchings", out="docs/progress.md_SC03_077.md"),
    "md_SC03_078": dict(build="build/md_SC03_078/md_SC03_078", check="config/check.md_SC03_078.sha",
                        src="src/md_SC03_078", asm="asm/md_SC03_078/nonmatchings", out="docs/progress.md_SC03_078.md"),
    "md_SC03_079": dict(build="build/md_SC03_079/md_SC03_079", check="config/check.md_SC03_079.sha",
                        src="src/md_SC03_079", asm="asm/md_SC03_079/nonmatchings", out="docs/progress.md_SC03_079.md"),
    "md_SC03_132": dict(build="build/md_SC03_132/md_SC03_132", check="config/check.md_SC03_132.sha",
                        src="src/md_SC03_132", asm="asm/md_SC03_132/nonmatchings", out="docs/progress.md_SC03_132.md"),
    "md_SC03_133": dict(build="build/md_SC03_133/md_SC03_133", check="config/check.md_SC03_133.sha",
                        src="src/md_SC03_133", asm="asm/md_SC03_133/nonmatchings", out="docs/progress.md_SC03_133.md"),
    "md_SC03_134": dict(build="build/md_SC03_134/md_SC03_134", check="config/check.md_SC03_134.sha",
                        src="src/md_SC03_134", asm="asm/md_SC03_134/nonmatchings", out="docs/progress.md_SC03_134.md"),
    "md_SC03_135": dict(build="build/md_SC03_135/md_SC03_135", check="config/check.md_SC03_135.sha",
                        src="src/md_SC03_135", asm="asm/md_SC03_135/nonmatchings", out="docs/progress.md_SC03_135.md"),
    "md_SC03_136": dict(build="build/md_SC03_136/md_SC03_136", check="config/check.md_SC03_136.sha",
                        src="src/md_SC03_136", asm="asm/md_SC03_136/nonmatchings", out="docs/progress.md_SC03_136.md"),
    "md_SC03_137": dict(build="build/md_SC03_137/md_SC03_137", check="config/check.md_SC03_137.sha",
                        src="src/md_SC03_137", asm="asm/md_SC03_137/nonmatchings", out="docs/progress.md_SC03_137.md"),
    "md_SC03_138": dict(build="build/md_SC03_138/md_SC03_138", check="config/check.md_SC03_138.sha",
                        src="src/md_SC03_138", asm="asm/md_SC03_138/nonmatchings", out="docs/progress.md_SC03_138.md"),
    "md_SC04_024": dict(build="build/md_SC04_024/md_SC04_024", check="config/check.md_SC04_024.sha",
                        src="src/md_SC04_024", asm="asm/md_SC04_024/nonmatchings", out="docs/progress.md_SC04_024.md"),
    "md_SC04_025": dict(build="build/md_SC04_025/md_SC04_025", check="config/check.md_SC04_025.sha",
                        src="src/md_SC04_025", asm="asm/md_SC04_025/nonmatchings", out="docs/progress.md_SC04_025.md"),
    "md_SC04_026": dict(build="build/md_SC04_026/md_SC04_026", check="config/check.md_SC04_026.sha",
                        src="src/md_SC04_026", asm="asm/md_SC04_026/nonmatchings", out="docs/progress.md_SC04_026.md"),
    "md_SC04_027": dict(build="build/md_SC04_027/md_SC04_027", check="config/check.md_SC04_027.sha",
                        src="src/md_SC04_027", asm="asm/md_SC04_027/nonmatchings", out="docs/progress.md_SC04_027.md"),
    "md_SC04_028": dict(build="build/md_SC04_028/md_SC04_028", check="config/check.md_SC04_028.sha",
                        src="src/md_SC04_028", asm="asm/md_SC04_028/nonmatchings", out="docs/progress.md_SC04_028.md"),
    "md_SC04_029": dict(build="build/md_SC04_029/md_SC04_029", check="config/check.md_SC04_029.sha",
                        src="src/md_SC04_029", asm="asm/md_SC04_029/nonmatchings", out="docs/progress.md_SC04_029.md"),
    "md_SC04_030": dict(build="build/md_SC04_030/md_SC04_030", check="config/check.md_SC04_030.sha",
                        src="src/md_SC04_030", asm="asm/md_SC04_030/nonmatchings", out="docs/progress.md_SC04_030.md"),
    "md_SC05_023": dict(build="build/md_SC05_023/md_SC05_023", check="config/check.md_SC05_023.sha",
                        src="src/md_SC05_023", asm="asm/md_SC05_023/nonmatchings", out="docs/progress.md_SC05_023.md"),
    "md_SC05_024": dict(build="build/md_SC05_024/md_SC05_024", check="config/check.md_SC05_024.sha",
                        src="src/md_SC05_024", asm="asm/md_SC05_024/nonmatchings", out="docs/progress.md_SC05_024.md"),
    "md_SC05_025": dict(build="build/md_SC05_025/md_SC05_025", check="config/check.md_SC05_025.sha",
                        src="src/md_SC05_025", asm="asm/md_SC05_025/nonmatchings", out="docs/progress.md_SC05_025.md"),
    "md_SC05_026": dict(build="build/md_SC05_026/md_SC05_026", check="config/check.md_SC05_026.sha",
                        src="src/md_SC05_026", asm="asm/md_SC05_026/nonmatchings", out="docs/progress.md_SC05_026.md"),
    "md_SC05_027": dict(build="build/md_SC05_027/md_SC05_027", check="config/check.md_SC05_027.sha",
                        src="src/md_SC05_027", asm="asm/md_SC05_027/nonmatchings", out="docs/progress.md_SC05_027.md"),
    "md_SC05_028": dict(build="build/md_SC05_028/md_SC05_028", check="config/check.md_SC05_028.sha",
                        src="src/md_SC05_028", asm="asm/md_SC05_028/nonmatchings", out="docs/progress.md_SC05_028.md"),
    "md_SC05_029": dict(build="build/md_SC05_029/md_SC05_029", check="config/check.md_SC05_029.sha",
                        src="src/md_SC05_029", asm="asm/md_SC05_029/nonmatchings", out="docs/progress.md_SC05_029.md"),
    "md_SC02_009": dict(build="build/md_SC02_009/md_SC02_009", check="config/check.md_SC02_009.sha",
                        src="src/md_SC02_009", asm="asm/md_SC02_009/nonmatchings", out="docs/progress.md_SC02_009.md"),
    "md_MAIN_007": dict(build="build/md_MAIN_007/md_MAIN_007", check="config/check.md_MAIN_007.sha",
                        src="src/md_MAIN_007", asm="asm/md_MAIN_007/nonmatchings", out="docs/progress.md_MAIN_007.md"),
    "md_MAIN_009": dict(build="build/md_MAIN_009/md_MAIN_009", check="config/check.md_MAIN_009.sha",
                        src="src/md_MAIN_009", asm="asm/md_MAIN_009/nonmatchings", out="docs/progress.md_MAIN_009.md"),
    "md_SC03_053": dict(build="build/md_SC03_053/md_SC03_053", check="config/check.md_SC03_053.sha",
                        src="src/md_SC03_053", asm="asm/md_SC03_053/nonmatchings", out="docs/progress.md_SC03_053.md"),
    "md_SC03_054": dict(build="build/md_SC03_054/md_SC03_054", check="config/check.md_SC03_054.sha",
                        src="src/md_SC03_054", asm="asm/md_SC03_054/nonmatchings", out="docs/progress.md_SC03_054.md"),
    "md_SC03_056": dict(build="build/md_SC03_056/md_SC03_056", check="config/check.md_SC03_056.sha",
                        src="src/md_SC03_056", asm="asm/md_SC03_056/nonmatchings", out="docs/progress.md_SC03_056.md"),
    # <<< overlays: tools/new_overlay.sh inserts ov_* entries above this line (Phase 13) >>>
}
MAKEFILE = ROOT / "Makefile"
# Per-binary state (BINARY/_cfg/SRCS/ASM_ROOT/OUT/BUILD/CHECK/LINKED_SEGS) is set by
# set_binary() so report() can run over MANY binaries in one process (--fleet, Phase 15).
BINARY = _cfg = SRCS = ASM_ROOT = OUT = BUILD = CHECK = LINKED_SEGS = None

def set_binary(binary):
    """Point the module globals at <binary>'s src/asm/build/check tree + recompute LINKED_SEGS."""
    global BINARY, _cfg, SRCS, ASM_ROOT, OUT, BUILD, CHECK, LINKED_SEGS
    if binary not in BINARIES:
        sys.exit(f"progress.py: unknown --binary '{binary}' (known: {', '.join(BINARIES)})")
    BINARY = binary
    _cfg = BINARIES[binary]
    SRCS = sorted((ROOT / _cfg["src"]).glob("*.c"))   # every c-segment (src/boot.c, src/800.c, ...)
    ASM_ROOT = ROOT / _cfg["asm"]                      # per-segment subdirs (boot/, 800/, ...)
    OUT, BUILD, CHECK = ROOT / _cfg["out"], ROOT / _cfg["build"], ROOT / _cfg["check"]
    LINKED_SEGS = linked_subsegs()
    global _S_INDEX  # one directory walk per binary (not a glob per function — 340k globs over the fleet)
    _S_INDEX = {p.stem: p for p in ASM_ROOT.glob("*/*.s")} if ASM_ROOT.exists() else {}

def linked_subsegs():
    """Library subsegments swapped to real PsyQ objects at build time = the 5th positional arg
    of each `psyq_integrate.py` call in the Makefile (e.g. `libcd1,libcd2`). Parsing the Makefile
    keeps it the SINGLE source of truth: a new library integration adds its psyq_integrate call and
    its stubs are auto-counted LINKED (no separate manifest to drift). Stubs in these subsegs build
    byte-identically from the real SDK objects when present, and from the committed asm fallback
    otherwise (fresh clone) — so they are LINKED regardless of local .run/obj40 state (a property of
    the project, not the machine).

    Scoped to the active binary: every psyq_integrate call lives inside the Makefile's
    `ifeq ($(BINARY),main)` block (PsyQ library linking is the EXE's layout — Phase 8), so only
    `main` has LINKED subsegs. A second binary (e.g. resident) has none. When a future binary gains
    its own gated integration, parse that gate here instead of the main-only shortcut."""
    # FAIL-CLOSED on an unconfigured module (R32). This function is gated on the module global
    # BINARY, which set_binary() assigns; imported as a LIBRARY without that call it used to
    # return an empty set — i.e. "this binary has no linked library subsegs", which for `main` is a
    # confidently WRONG answer (there are 49). An importer then classifies ~1,300 already-
    # byte-identical LINKED library stubs as outstanding game-code work. Silent, and exactly the
    # shape R32 exists for; caught 2026-07-27 by an importer (mine) that hit it.
    # set_binary() assigns BINARY before calling this, so the CLI path is unaffected.
    if BINARY is None:
        raise RuntimeError(
            "progress.linked_subsegs(): module not configured — call progress.set_binary(<binary>) "
            "first. Returning an empty set here would silently claim 'no linked subsegs'.")
    if BINARY != "main":
        return set()
    return _main_linked_segs_from_makefile()


def _main_linked_segs_from_makefile():
    """The EXE's LINKED subseg names, parsed from the Makefile's psyq_integrate calls — BINARY-independent
    (P31 S78: the fleet's weighted metric needs main's link state while iterating other binaries)."""
    if not MAKEFILE.exists():
        return set()
    txt = MAKEFILE.read_text()
    # stub lists may be passed inline (`libcd1,libcd2`) or via a make var (`$(LIBGTE_STUBS)` for the
    # long multi-block ones) — collect `NAME := <comma,list>` defs so either form resolves.
    mvars = dict(re.findall(r'^(\w+)\s*:=\s*([A-Za-z0-9_,]+)\s*$', txt, re.M))
    segs = set()
    # leading --flag value pairs (Phase 9: --vram-base/--exe/--symbols) precede the 4 positionals
    # (elf_dir ld_path objdir syms_ld); the 5th positional is the stub list captured below.
    for m in re.finditer(r'psyq_integrate\.py(?:\s+--\S+\s+\S+)*\s+\S+\s+\S+\s+\S+\s+\S+\s+(\S+)', txt):
        arg = m.group(1)
        vm = re.fullmatch(r'\$\((\w+)\)', arg)
        if vm:
            arg = mvars.get(vm.group(1), '')
        segs.update(s for s in arg.split(',') if re.fullmatch(r'[A-Za-z0-9_]+', s))
    return segs

_DEDUP_CACHE = None  # binary -> set(shared fn names); parsed once (the registry is large at fleet scale)

def dedup_members(binary):
    """Function names matched-once-and-shared via config/dedup.us.yaml for this binary. They are
    hand-matched byte-identical C, but instantiated from a shared body (a macro in src/shared/),
    so classify()'s function-definition scan does NOT recognize the macro form — count them REAL
    via the registry instead (the source of truth for code shares, Phase 11). Returns a set."""
    p = ROOT / "config/dedup.us.yaml"
    if not p.exists():
        return set()
    global _DEDUP_CACHE
    if _DEDUP_CACHE is None:                    # parse the registry ONCE, not per --fleet binary (136x)
        _DEDUP_CACHE = {}
        try:
            import yaml
            sys.path.insert(0, str(ROOT / "tools"))
            from dedup_integrate import group_members   # one parser for both verbose + shorthand forms
            data = yaml.safe_load(p.read_text()) or {}
            for g in (data.get("groups") or []):
                for (b, _v, name) in group_members(g):
                    _DEDUP_CACHE.setdefault(b, set()).add(name)
        except Exception:
            _DEDUP_CACHE = {}
    return _DEDUP_CACHE.get(binary, set())

_S_INDEX = {}  # name -> .s path, rebuilt per binary in set_binary() (avoids a glob per function)

def find_s(name):
    """Locate <name>.s in any asm/nonmatchings/<seg>/ subdir (segments: boot, 800, ...)."""
    return _S_INDEX.get(name)

INSTR = re.compile(r'^\s*/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s*\*/\s+[a-z]')

def strip_comments(s):
    """Blank comments AND string/char-literal contents, via the ONE masking oracle (`cdecl._mask`).

    §134 / R33 (P30 S39). This was a private two-line regex that removed `/*…*/` and `//…` and was
    NOT string-aware — so a brace or a semicolon inside a C string literal (`printf("}")`, a path
    like `"a;b"`) was seen as real syntax by the callers below, every one of which is a LINE-SHAPE
    decision on this function's output: the `{`-vs-`;` scan that separates a definition from a
    declaration, the `count('{') - count('}')` body-depth walk, and the empty-vs-real body test.
    A miscount there mis-buckets a function in the fn-count metric.

    That is the §134 class, which had by this point appeared in SIX tools; the fix is routing every
    line-shape decision through `cdecl._mask` rather than writing a seventh regex. `_mask` is
    length-preserving (it blanks rather than deletes), which is strictly better here: the callers
    compare offsets (`br < sm`) and count characters, and blanking keeps those offsets valid
    against the ORIGINAL line while removing the false tokens."""
    return cdecl._mask(s)

def is_data_blob(name):
    """A .s with a code label (glabel/jlabel) is a function; data-only (dlabel, no code) is a blob."""
    p = find_s(name)
    if p is None:
        return False
    txt = p.read_text()
    return ('glabel' not in txt and 'jlabel' not in txt and 'dlabel' in txt)

def asm_is_trivial(name):
    """True iff the function's asm is exactly {jr, nop} (the empty-no-op shape splat emits void{} for)."""
    p = find_s(name)
    if p is None:
        return None
    mnem = []
    for ln in p.read_text().splitlines():
        m = re.match(r'^\s*/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s*\*/\s+([a-z0-9.]+)', ln)
        if m:
            mnem.append(m.group(1))
    return set(mnem) <= {'jr', 'nop'} and len(mnem) <= 2

SIG = re.compile(r'^\s*[A-Za-z_][\w \t\*]*\b([A-Za-z_]\w*)\s*\(')
# A K&R parameter declaration sitting between the signature and the `{`: a bare `<type> <name>;`
# (optionally an array/pointer). It carries NO parens — that is what distinguishes it from the
# continuation line of a wrapped ANSI prototype, which always carries the closing `)`.
KR_PARAM = re.compile(r'^\s*[A-Za-z_][\w \t\*]*\s+\**\w+\s*(?:\[[^\]]*\])?\s*;\s*$')

def classify():
    real, empty, nonmatching, stubs, blobs, linked, verbatim = [], [], [], [], [], [], []
    for src in SRCS:
        lines = src.read_text().split('\n')
        n = len(lines); i = 0
        while i < n:
            s = lines[i].strip()
            if s.startswith('#ifdef NON_MATCHING'):
                # THE `#else` HALF IS LIVE CODE, AND SWALLOWING IT UNDERCOUNTS REAL (P31 S73).
                # The old form consumed from `#ifdef NON_MATCHING` all the way to `#endif`, so a
                # function BANKED into the `#else` branch landed in NO bucket at all — not real,
                # not a stub, invisible, exactly like the K&R and `#if 0` defects documented below
                # and above. Measured: CdReadStateMachine, CdReadSectorReadyCB and
                # StreamLoadStateMachine were all byte-identical in the shipped build and counted
                # as zero, because banking replaces the `#else` INCLUDE_ASM with the real body and
                # leaves the old attempt in the dead half.
                # So: consume only the DEAD half, then decide from the LIVE half. If it still holds
                # an INCLUDE_ASM the function is a NON_MATCHING stub (unchanged accounting); if it
                # holds anything else, rewind and let the normal scan classify it.
                dead = []
                while i < n and not lines[i].strip().startswith(('#else', '#endif')):
                    dead.append(lines[i]); i += 1
                had_else = i < n and lines[i].strip().startswith('#else')
                i += 1                                   # step over the `#else` / `#endif`
                live_start = i
                live = []
                if had_else:
                    while i < n and not lines[i].strip().startswith('#endif'):
                        live.append(lines[i]); i += 1
                    i += 1                               # step over the `#endif`
                m = re.search(r'INCLUDE_ASM\("[^"]+",\s*(\w+)\)', '\n'.join(dead + live))
                if m and (not had_else or re.search(r'INCLUDE_ASM\("[^"]+",\s*(\w+)\)',
                                                    '\n'.join(live))):
                    nonmatching.append(m.group(1))       # still a stub: accounting unchanged
                    continue
                if had_else and live:
                    i = live_start                       # a banked body: classify it normally
                continue
            # `#if 0` — DEAD CODE, not a match (Phase-28 T5). The scanner knew `#ifdef NON_MATCHING`
            # but not this, so a `#if 0`-preserved analysis body was read as a live definition AND its
            # real INCLUDE_ASM stub was counted separately => the SAME function landed in both `real`
            # and `stubs`. Live case: src/resident/resident.c:868-925 wraps a full
            # `void func_800D00E4(s32){...}` in `#if 0` (its jtbl dossier) and re-declares the stub at
            # :926 — inflating resident REAL by 1 and the denominator by 1 (reported 123/146 = 85.62%;
            # honest 122/145 = 85.5%). Skip the block entirely: dead code is neither matched nor stubbed.
            if re.match(r'#\s*if\s+0\b', s):
                depth = 1
                i += 1
                while i < n and depth:
                    t = lines[i].strip()
                    if re.match(r'#\s*if', t):
                        depth += 1
                    elif t.startswith('#endif'):
                        depth -= 1
                    i += 1
                continue
            m = re.match(r'INCLUDE_ASM\("([^"]+)",\s*(\w+)\)', s)
            if m:
                seg, fn = m.group(1).rstrip('/').rsplit('/', 1)[-1], m.group(2)
                if is_data_blob(fn):
                    blobs.append(fn)
                elif seg in LINKED_SEGS:     # subseg swapped to a real PsyQ object (byte-identical)
                    linked.append(fn)
                else:
                    stubs.append(fn)
                i += 1; continue
            if s.startswith('INCLUDE_RODATA'):
                # Bucket the symbol as a data BLOB rather than skipping it unbucketed: the module
                # class (S45) emits header rodata (the §154 id word, orphan jtbl carriers) as
                # per-symbol .s files in nonmatchings/, so they enter _S_INDEX and an unbucketed
                # skip reads as an R32 COVERAGE DEFECT. Rodata is data by construction.
                m = re.match(r'INCLUDE_RODATA\("[^"]+",\s*(\w+)\)', s)
                if m:
                    blobs.append(m.group(1))
                i += 1; continue
            # §265 VERBATIM-ASM BODY — bytes, NOT a decompile, and it needs its OWN bucket (P31 S75).
            #
            # A file-scope `__asm__("...")` block that DEFINES a function (`.ent NAME` / `.globl NAME`
            # + `NAME:`) matches none of the patterns above, so it landed in NO bucket and surfaced as
            # `UNPLACED (parse hole)` — which is R32 doing its job, but leaves the operator with an
            # error instead of a number. Counting it REAL would be worse: it is the assembly pasted
            # into a C string, byte-identical BY CONSTRUCTION and completely unexplained.
            #
            # Measured fleet-wide at introduction: 116 such bodies (114 main, 1 md_MAIN_003,
            # 1 ov_SC05_005), the largest being SaveLoadRoutine at 1,165 instructions. Several main
            # ones are PsyQ library routines where verbatim is defensible; the point of the bucket is
            # that the GAP between "byte-identical binary" and "decompiled source" is now visible in
            # the headline instead of hiding inside REAL or inside a parse hole.
            if s.startswith('__asm__') and '(' in s:
                blk, j, depth, opened = [], i, 0, False
                while j < n:
                    c = lines[j]
                    blk.append(c)
                    depth += c.count('(') - c.count(')')
                    if '(' in c: opened = True
                    j += 1
                    if opened and depth <= 0: break
                txt = '\n'.join(blk)
                # BOTH SPELLINGS, AND REQUIRE THE `\n` TERMINATOR (P31 S75, second cut).
                # The sources use `".ent\tNAME\n"` AND `".ent NAME\n"`, and a bare fragment
                # `".ent\t"` also occurs. A pattern with an OPTIONAL `\t` and no terminator matched
                # the fragment and captured the literal name `t`, while a pattern requiring `\t`
                # missed every space-spelled block: three of my own counts (116 / 112 / 108) were
                # all wrong before this was validated against one known-true case of EACH spelling
                # (SaveLoadRoutine = tab, func_80047D3C = space). True count: 178.
                names = set(re.findall(r'\.ent(?:\\t|\s)+(\w+)\\n', txt))
                if not names:
                    g = set(re.findall(r'\.globl(?:\\t|\s)+(\w+)\\n', txt))
                    names = g & set(re.findall(r'"(\w+):\\n"', txt))
                verbatim.extend(sorted(names))
                i = j; continue
            fm = SIG.match(lines[i])
            if fm and '(' in lines[i]:
                # Definition ({ ... }) vs forward declaration (ends ;)? Scan to the first { or ;.
                # extern/prototype lines (e.g. `extern s32 CdQueueBusy(void);`) are NOT functions.
                #
                # K&R DEFINITIONS (Phase 26 session 8 — this silently erased ~190k banked instructions):
                #     s32 func_8015AE2C(arg0)
                #     s32 arg0;              <- a `;` BEFORE the `{`
                #     { ... }
                # The old scan hit that `;` and classified the function as a forward declaration, so it
                # landed in NO bucket at all — not REAL, not a stub, invisible. And a K&R def is MANDATORY
                # whenever a zero-arg engine_core.h thunk calls the function (it must be unprototyped), so
                # the metric was blind to exactly the shape our own banking recipe requires: the heavy-jr
                # cores. func_8015AE2C (562x134), func_8015A3C8 (493x132), func_80166994 (369x134) were all
                # compiled, linked and BYTE-IDENTICAL in the shipped build while counting as zero.
                # A K&R parameter declaration is a bare `<type> <name>;` — no parens (a wrapped ANSI
                # prototype's continuation carries the `)`), so it is unambiguous to skip over.
                j = i; kind = None
                while j < n:
                    c = strip_comments(lines[j])
                    br = c.find('{'); sm = c.find(';')
                    if br != -1 and (sm == -1 or br < sm): kind = 'def'; break
                    if sm != -1:
                        if j > i and '(' not in c and ')' not in c and KR_PARAM.match(c):
                            j += 1; continue       # K&R parameter declaration -> keep scanning for the `{`
                        kind = 'decl'; break
                    j += 1
                if kind != 'def':
                    i = j + 1; continue            # skip the declaration
                start = i; depth = 0; opened = False
                while i < n:
                    c = strip_comments(lines[i]); depth += c.count('{') - c.count('}')
                    if '{' in c: opened = True
                    i += 1
                    if opened and depth <= 0: break
                body = '\n'.join(lines[start:i])
                a, b = body.index('{'), body.rindex('}')
                (real if strip_comments(body[a+1:b]).strip() else empty).append(fm.group(1))
                continue
            i += 1
    return real, empty, nonmatching, stubs, blobs, linked, verbatim

def report(binary, audit=False, write=True):
    """Classify one binary; write docs/progress.<binary>.md (if write) + print; return a stats dict
    (for --fleet aggregation). Single-binary output is byte-for-byte the legacy format."""
    set_binary(binary)
    real, empty, nonmatching, stubs, blobs, linked, verbatim = classify()
    # Code-shared functions (dedup.us.yaml) are REAL byte-identical matches whose macro-instantiated
    # form classify() doesn't parse — fold them in (dedup-safe) so the count stays honest (P9).
    #
    # ...but ONLY if they are actually instantiated. A member that is STILL an INCLUDE_ASM stub in this
    # binary is not banked, whatever the registry says — the registry can go stale (a group whose
    # DEFINE_ macro no longer exists in src/). Counting it REAL while it also sits in `stubs`
    # double-counts it into `matchable` AND inflates `byteident`. Measured: 532 phantom instances
    # (Phase 26 session 8 scanner audit). Subtracting `stubs` makes the registry advisory, and the
    # source tree authoritative — which is the right precedence (P9: only what is in the build counts).
    shared = sorted(dedup_members(BINARY) - set(real) - set(stubs))
    real = sorted(set(real) | set(shared))

    # ---- COVERAGE ASSERTION (the rule ratified 2026-07-14: a scanner over the corpus must assert its
    # own coverage; a silent skip is a DEFECT, not a no-op). Ground truth = every function splat emitted
    # a .s for. Anything classify() could not place in ANY bucket is a parsing hole, and it is exactly
    # how the K&R blindness above hid ~190k banked instructions for 26 phases while the byte-gate stayed
    # green (the gate compiles; this tool only reads text — they share no code, so the gate can never
    # catch a miscount). Report it LOUDLY rather than silently under-reporting progress.
    placed = (set(real) | set(empty) | set(nonmatching) | set(stubs) | set(blobs)
              | set(linked) | set(verbatim))
    unplaced = sorted(set(_S_INDEX) - placed)

    # OVER-coverage is the DUAL defect, and the assertion above is blind to it (Phase-28 T5). `placed`
    # is a set union, so it catches a function in NO bucket — but `matchable` below summed len()s, so a
    # function in TWO buckets was counted twice and nothing complained. Not hypothetical: the `#if 0`
    # hole (fixed above) put func_800D00E4 in BOTH `real` and `stubs`, reporting the resident as
    # 123/146 = 85.62% when the truth is 122/145 = 85.5% — and the flag-plant target is that very
    # denominator. R32 means assert coverage in BOTH directions: nothing missing, nothing counted twice.
    _buckets = {"real": real, "empty": empty, "nonmatching": nonmatching, "stubs": stubs,
                "linked": linked, "verbatim": verbatim}
    _seen = {}
    for _name, _b in _buckets.items():
        for _fn in _b:
            _seen.setdefault(_fn, []).append(_name)
    _multi = {f: bs for f, bs in _seen.items() if len(bs) > 1}
    assert not _multi, ("progress.py: %d function(s) landed in MULTIPLE buckets — a MISCOUNT, not a "
                        "no-op (R32): %s" % (len(_multi), dict(list(_multi.items())[:5])))

    matchable = len(set(real) | set(empty) | set(nonmatching) | set(stubs) | set(linked)
                    | set(verbatim))  # SET, not a len() sum
    # VERBATIM counts as byte-identical (it is, by construction) but NEVER as REAL.
    byteident = len(set(real) | set(linked) | set(empty) | set(verbatim))

    out = []
    out.append("# BFM matching progress  (generated by tools/progress.py — authoritative)")
    out.append("")
    out.append(f"REAL substantive matches : {len(real):5d}   <- the Gen1-exit >=25 bar counts THIS")
    if shared:
        out.append(f"  (of which dedup-shared : {len(shared):5d}   one body -> N sites, config/dedup.us.yaml)")
    out.append(f"LINKED real PsyQ objects : {len(linked):5d}   <- byte-identical via linked SDK objects")
    if verbatim:
        out.append(f"VERBATIM __asm__ bodies  : {len(verbatim):5d}   <- §265: BYTES, NOT A DECOMPILE "
                   f"(byte-identical by construction, unexplained; NOT counted in REAL)")
    out.append(f"NON_MATCHING (near-miss) : {len(nonmatching):5d}")
    out.append(f"splat-auto empty no-ops  : {len(empty):5d}")
    out.append(f"INCLUDE_ASM stubs        : {len(stubs):5d}")
    out.append(f"data blobs (excluded)    : {len(blobs):5d}")
    if unplaced:
        out.append(f"!! UNPLACED (parse hole) : {len(unplaced):5d}   <- classify() could not bucket these; "
                   f"a SILENT SKIP is a defect, not a no-op. e.g. {', '.join(unplaced[:4])}")
        print(f"[progress] COVERAGE DEFECT in {binary}: {len(unplaced)} function(s) splat emitted a .s for "
              f"are in NO bucket — the count is WRONG. e.g. {', '.join(unplaced[:6])}", file=sys.stderr)
    out.append("-" * 40)
    out.append(f"matchable functions      : {matchable:5d}")
    out.append(f"REAL / matchable         : {len(real)} / {matchable} = {100*len(real)/matchable:.2f}%")
    out.append(f"byte-identical/ matchable: {byteident} / {matchable} = {100*byteident/matchable:.2f}%   (REAL+LINKED+empties+VERBATIM)")
    out.append("")
    out.append("LINKED subsegs: " + " ".join(sorted(LINKED_SEGS)) + f"  ({len(linked)} fns)")
    out.append("REAL matches: " + " ".join(sorted(real)))
    out.append("NON_MATCHING: " + " ".join(sorted(nonmatching)))

    if BUILD.exists():
        h = hashlib.sha1(BUILD.read_bytes()).hexdigest()
        want = CHECK.read_text().split()[0] if CHECK.exists() else ""
        out.append("")
        out.append(f"build SHA1: {h}  ({'byte-identical' if h == want else 'MISMATCH'})")

    if audit:
        bad = [n for n in empty if asm_is_trivial(n) is False]
        out.append("")
        out.append(f"empties audit: {len(empty)-len(bad)}/{len(empty)} genuine jr;nop"
                   + (f"  !! SUSPICIOUS: {bad}" if bad else "  (all clean)"))

    if write:
        text = "\n".join(out) + "\n"
        print(text, end="")
        OUT.write_text(text)
    return dict(binary=binary, real=len(real), shared=len(shared), linked=len(linked),
                nonmatching=len(nonmatching), empty=len(empty), stubs=len(stubs), blobs=len(blobs),
                matchable=matchable, byteident=byteident)


def _sig_binary(sigpath):
    """Map a sig filename to its corpus/build binary name. main's sig is historically named after the
    EXE (sig.SLUS_007.26.jsonl); overlays/resident already match."""
    b = os.path.basename(sigpath).split("sig.")[1][:-6]
    return "main" if b == "SLUS_007.26" else b


def _main_linked_ranges():
    """[(vram_lo, vram_hi)] of main's LINKED subsegs, derived from the Makefile's psyq_integrate stub
    lists (LINKED_SEGS) and the splat yaml's subseg rows (vram = fileoff + (segment vram - segment start)).
    P31 S78 (R33): the game-code denominator must follow the LIVE link state, not a sig's snapshot."""
    import yaml as _yaml
    y = _yaml.safe_load(open(ROOT / "config/splat.us.exe.yaml"))
    out, rows, vb = [], [], None
    for seg in y["segments"]:
        if isinstance(seg, dict) and "subsegments" in seg:
            vb = int(seg["vram"]) - int(seg["start"])
            for r in seg["subsegments"]:
                if isinstance(r, list) and len(r) >= 3:
                    rows.append((int(r[0]), str(r[2])))
                elif isinstance(r, list) and len(r) == 1:
                    rows.append((int(r[0]), None))
    rows.sort()
    linked = _main_linked_segs_from_makefile()
    for i, (off, name) in enumerate(rows):
        if name in linked and i + 1 < len(rows):
            out.append((off + vb, rows[i + 1][0] + vb))
    return out


def weighted_metrics():
    """Instruction/byte-weighted matching % from the committed sigs (.run/sig.*.jsonl) + the DERIVED
    stub oracle (corpus.stubs, R33 — NOT a func_-only regex, which missed curated-named stubs and, for
    main, would have globbed the nonexistent src/SLUS_007.26/ and reported main 100% matched). Against
    EXECUTABLE CODE only; MIPS instrs are 4 bytes so instruction% == byte%:
      - fleet   : sum(matched nins) / sum(total nins) over resident + every overlay (shared engine
                  counted PER-OVERLAY) — the decomp.dev/frogress per-binary aggregate DISPLAY number.
      - dedup   : each distinct h_exact class ONCE, nins-weighted — the 'distinct RE' number.
      - main    : the main EXE's GAME-CODE weighted %, reported SEPARATELY (Phase-27 T10). main is not
                  folded into `fleet` because its only sig today is a Ghidra sig (different provenance
                  from the overlays' sig_image sigs) that EXCLUDES the LINKED PsyQ objects (Ghidra never
                  analysed them) — so it is a clean game-code-only number, but a stale one (see main_sig_date),
                  and folding a stale/incomplete value into the decomp.dev-comparable headline would
                  mislead. A fresh/complete main sig (sig-refresh, or the deferred sig_image-on-main
                  oracle — docs/second-oracle.md) makes it authoritative and foldable.
    Returns a dict, or None if no sigs."""
    import os, glob, json
    sys.path.insert(0, str(ROOT / "tools"))
    import corpus
    paths = sorted(glob.glob(str(ROOT / ".run/sig.ov_*.jsonl")))\
            + sorted(glob.glob(str(ROOT / ".run/sig.md_*.jsonl")))   # S44: module class
    rp = ROOT / ".run/sig.resident.jsonl"
    if rp.exists():
        paths.append(str(rp))
    if not paths:
        return None

    def stub_addrs(binary):
        # FAIL LOUD (R32/R35). This was `except Exception: return set()` — and an empty stub set does
        # not mean "no stubs", it means "the oracle could not answer": `matched = sig − stubs` then
        # credits EVERY function in that binary as banked. Byte-witnessed during P30 S1e: running
        # this metric in a tree with no `asm/` made corpus.stubs raise its (correct, coverage-asserted)
        # CorpusError for all 140 binaries, the swallow turned each into an empty set, and the tool
        # cheerfully reported **instr-weighted 100.00% / distinct-code 100.00%** — a 100%-complete
        # decomp, from a swallowed error. corpus.stubs is deliberately fail-closed ("it refuses to
        # answer rather than guess 'banked'"); wrapping it in a bare except reinstated exactly the
        # guess it refuses to make. A loud failure nobody counts is as invisible as a silent one
        # (R32) — so here it is neither swallowed nor merely logged: it aborts the metric.
        return set(corpus.stubs(binary))           # {addr:int -> Stub}; the derived INCLUDE_ASM set (R33)

    fm = ft = 0
    cls_nins, matched_cls = {}, set()
    for p in paths:
        st = stub_addrs(_sig_binary(p))
        for line in open(p):
            r = json.loads(line)
            a, n, hx = int(r["addr"], 16), r["nins"], r["h_exact"]
            ft += n
            cls_nins[hx] = n                       # h_exact-identical -> identical nins
            if a not in st:                        # non-stub == matched (fleet is byte-identical)
                fm += n
                matched_cls.add(hx)
    ut = sum(cls_nins.values())
    um = sum(n for hx, n in cls_nins.items() if hx in matched_cls)

    # main — game-code only. P33 A2: the sig is the BUILD-DERIVED one (`make sig-main` →
    # .run/sig.main.jsonl: every game-code object's functions at build-true lengths, from the link map
    # + the objects' own symbols; Ghidra-free, splat-free, regenerable on a public clone). The
    # 2026-08-05 Ghidra sig (.run/sig.SLUS_007.26.jsonl) is the legacy fallback. NO sig at all is an
    # ERROR (R32): this block used to set mt=0 and carry on, which made the digest read "217 binaries"
    # and MAIN 0/0 on any machine without the Ghidra file — a public clone would have published a
    # headline that quietly omitted the EXE.
    mm = mt = 0
    mp = ROOT / ".run/sig.main.jsonl"
    main_prov = "build-derived sig (make sig-main)"
    if not mp.exists():
        mp = ROOT / ".run/sig.SLUS_007.26.jsonl"
        main_prov = "LEGACY Ghidra sig"
    if not mp.exists():
        raise SystemExit("progress: no main sig — run `make check BINARY=main && make sig-main` "
                         "(.run/sig.main.jsonl); the fleet digest is not written without the EXE (R32)")
    import datetime
    main_date = datetime.date.fromtimestamp(mp.stat().st_mtime).isoformat()
    mst = stub_addrs("main")
    # P31 S78: exclude LINKED subsegs LIVE (R33 — derive from the Makefile stub lists + the yaml
    # ranges), not by trusting the sig's generation-time exclusion. When 13 "game code" subsegs
    # became libgte23..30/libgs7/snd10/snd11 the 2026-08-05 sig still carried their 2,907 ins,
    # which then read as unmatched game code (59.8% -> 56.1% with no game-code change).
    lr = _main_linked_ranges()
    for line in open(mp):
        r = json.loads(line)
        a, n = int(r["addr"], 16), r["nins"]
        if n == 0:
            continue                           # GTE thunks / no-body
        if any(lo <= a < hi for lo, hi in lr):
            continue                           # LINKED PsyQ object — not game code
        mt += n
        if a not in mst:
            mm += n

    # MAIN IS NOW IN THE WEIGHTED DENOMINATORS (roadmap §1 metrics contract, 2026-07-22).
    # The contract requires all three headline metrics to include the main EXE; it had been reported
    # as a separate provisional line since Phase-27 T10, which meant the headline silently measured
    # 139 of 140 binaries and flattered itself by omitting the least-decompiled one.
    #
    # What the caveat actually is (restated precisely, because "stale" was misleading): main's sig
    # comes from Ghidra (2026-06-14), and function BOUNDARIES derive from the original bytes, which
    # do not change — matched-vs-stub comes from the LIVE corpus.stubs. So the numbers do not drift.
    # The real limitation is R34: `sig_image` cannot independently validate a PS-X EXE's boundaries,
    # so main has no SECOND, DISAGREEING oracle for the PHANTOM/TRUNCATED class (closed P31 S77:
    # `make sig-main-oracle`).
    #
    # CORRECTION (P31 S78): this block used to claim "the sig also EXCLUDES the LINKED PsyQ objects".
    # It did not. The 2026-08-05 sig carried every Ghidra function including the ~31,000 ins of linked
    # SDK objects, whose INCLUDE_ASM stub records read as UNMATCHED game code — so main's game-code
    # weighted % was reported as 59.8% (47,521 / 79,510) when the game-code denominator is 48,537 ins
    # and the honest figure was 91.8%. The LINKED exclusion is now applied LIVE above
    # (_main_linked_ranges, R33/R35); the remainder 48,537 − 44,562 = 3,975 ins equals the sum of
    # main's open stubs in `frontier_classify` (a known-true-case check).
    fleet_m_all, fleet_t_all = fm + mm, ft + mt
    dedup_m_all, dedup_t_all = um + mm, ut + mt      # main's fns are unique — no h_exact sharing
    return dict(fleet_m=fleet_m_all, fleet_t=fleet_t_all,
                fleet_pct=(100 * fleet_m_all / fleet_t_all if fleet_t_all else 0.0),
                dedup_m=dedup_m_all, dedup_t=dedup_t_all,
                dedup_pct=(100 * dedup_m_all / dedup_t_all if dedup_t_all else 0.0),
                nbins=len(paths) + (1 if mt else 0),
                dedup_fns=len(matched_cls), dedup_total_fns=len(cls_nins),
                fleet_m_exmain=fm, fleet_t_exmain=ft,
                fleet_pct_exmain=(100 * fm / ft if ft else 0.0),
                main_m=mm, main_t=mt, main_pct=(100 * mm / mt if mt else 0.0), main_sig_date=main_date,
                main_sig_prov=main_prov)


def main_oracle_line():
    """main's independent-oracle verdict, DERIVED at render time (P33 A2). The fleet digest used to
    carry the literal "0 phantom, 0 truncated, 1 explained pad-tail", which went stale the moment the
    last pad-tail function was banked (S85) — a published number nobody was computing (R51)."""
    sys.path.insert(0, str(ROOT / "tools"))
    import corpus
    if not corpus.sig_is_independent("main"):
        return "oracle sig absent — run `make sig-main-oracle`"
    r = corpus.audit("main")
    return f"{len(r['phantom'])} phantom, {len(r['truncated'])} truncated, {len(r['pad_tail'])} pad-tail"


def fleet():
    """Aggregate every binary into docs/progress.fleet.md — DETERMINISTIC (source-derived from the
    committed src/*.c + config/dedup.us.yaml). The live byte-identity gate is `make check-all`;
    collapsible-byte leverage lives in docs/duplicates.cross.md. Rows: main, resident, overlays sorted."""
    order = [b for b in ("main", "resident") if b in BINARIES] + \
            sorted(b for b in BINARIES if b not in ("main", "resident"))
    rows = [report(b, write=False) for b in order]
    tot = lambda k: sum(r[k] for r in rows)
    REAL, SHARED, LINKED, EMPTY, NM, STUBS, MATCH, BYTE = (tot('real'), tot('shared'), tot('linked'),
        tot('empty'), tot('nonmatching'), tot('stubs'), tot('matchable'), tot('byteident'))
    # dedup registry totals (deterministic from the committed yaml)
    ngroups = nmembers = 0
    dp = ROOT / "config/dedup.us.yaml"
    if dp.exists():
        try:
            import yaml
            from dedup_integrate import group_members   # expands verbose + shorthand alike
            gs = (yaml.safe_load(dp.read_text()) or {}).get("groups") or []
            ngroups = len(gs); nmembers = sum(1 for g in gs for _ in group_members(g))
        except Exception:
            pass

    wm = weighted_metrics()
    head = ["# BFM FLEET matching progress  (generated by tools/progress.py --fleet — authoritative)",
            f"# {len(rows)} binaries: main + resident + {len(rows)-2} location overlays. DETERMINISTIC,",
            "# source-derived (committed src/*.c + config/dedup.us.yaml). Live byte gate: `make check-all`;",
            "# cross-binary collapsible-byte leverage: docs/duplicates.cross.md.", "",
            "# THREE progress metrics (all matter — see the labels):",
            f"FLEET fn-count byte-ident: {BYTE:6d} / {MATCH} = {100*BYTE/MATCH:.2f}%   (REAL+LINKED+empties; FUNCTION-count, ×134-inflated — one crack counts per overlay)"]
    if wm:
        head += [
            f"FLEET instr-weighted     : {wm['fleet_m']:7d} / {wm['fleet_t']} = {wm['fleet_pct']:.1f}%   (shipped .text across main + resident + {wm['nbins']-2} overlays; the decomp.dev-DISPLAY number)",
            f"FLEET distinct-code(uniq): {wm['dedup_m']:7d} / {wm['dedup_t']} = {wm['dedup_pct']:.1f}%   ({wm['dedup_fns']}/{wm['dedup_total_fns']} unique fns; the DISTINCT-RE number)"]
        if wm.get('main_t'):
            head += [
                f"MAIN game-code weighted  : {wm['main_m']:7d} / {wm['main_t']} = {wm['main_pct']:.1f}%   (INCLUDED in the fleet numbers above since 2026-07-22 — roadmap §1 metrics contract; {wm['main_sig_prov']} dated {wm['main_sig_date']}; boundaries INDEPENDENTLY VERIFIED since P31 S77 — `make sig-main-oracle` + `make audit-corpus`: {main_oracle_line()})",
                f"  (fleet EXCLUDING main, for continuity with pre-2026-07-22 readings: {wm['fleet_m_exmain']} / {wm['fleet_t_exmain']} = {wm['fleet_pct_exmain']:.1f}%)"]
    else:
        head += ["# (instr-weighted + distinct-code metrics need .run/sig.*.jsonl — run `make sig-overlays`)"]
    head += ["",
             f"FLEET REAL substantive   : {REAL:6d}   (of which dedup-shared {SHARED} via {ngroups} groups / {nmembers} instances)",
             f"FLEET LINKED PsyQ objs   : {LINKED:6d}",
             f"FLEET NON_MATCHING       : {NM:6d}   (0 in any default build — G4)",
             f"FLEET INCLUDE_ASM stubs  : {STUBS:6d}",
             f"FLEET matchable          : {MATCH:6d}", ""]
    table = ["| binary | REAL | shared | LINKED | byte-ident | matchable | byte-ident % |",
             "|---|---:|---:|---:|---:|---:|---:|"]
    for r in rows:
        pct = (100 * r['byteident'] / r['matchable']) if r['matchable'] else 0.0
        table.append(f"| {r['binary']} | {r['real']} | {r['shared']} | {r['linked']} | "
                     f"{r['byteident']} | {r['matchable']} | {pct:.1f}% |")
    text = "\n".join(head + table) + "\n"
    print("\n".join(head[:-1]))                    # the summary block (drop the trailing blank)
    (ROOT / "docs/progress.fleet.md").write_text(text)


def main():
    if '--fleet' in sys.argv:
        fleet(); return
    if '--weighted' in sys.argv:
        wm = weighted_metrics()
        if not wm:
            sys.exit("progress.py --weighted: no .run/sig.*.jsonl — run `make sig-overlays` first.")
        print("BFM byte-weighted matching progress (executable code only; resident + %d overlays; main EXE excluded):"
              % (wm['nbins'] - 1))
        print("  instr-weighted (fleet, decomp.dev-display): %7d / %d = %.1f%%"
              % (wm['fleet_m'], wm['fleet_t'], wm['fleet_pct']))
        print("  distinct-code  (dedup, distinct-RE)       : %7d / %d = %.1f%%  (%d/%d unique fns)"
              % (wm['dedup_m'], wm['dedup_t'], wm['dedup_pct'], wm['dedup_fns'], wm['dedup_total_fns']))
        return
    audit = '--audit' in sys.argv
    check = '--check' in sys.argv
    binary = next((sys.argv[i + 1] for i, x in enumerate(sys.argv)
                   if x == "--binary" and i + 1 < len(sys.argv)), "main")
    report(binary, audit=audit, write=True)
    if check:
        import subprocess
        sys.exit(subprocess.run(["make", "-C", str(ROOT), "check"]).returncode)

if __name__ == "__main__":
    main()

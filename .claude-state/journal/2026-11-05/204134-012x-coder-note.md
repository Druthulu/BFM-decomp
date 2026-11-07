---
agent: ext-T11.cG20
label: T11.cG20
---
These four are barrier-locked bodies: each is byte-exact only because an opaque `__asm__` fence stops sched1/reorg from moving one statement. My job is to replace each fence with a real C dependency — a second set, a temp, a width cast, or statement order — that reproduces the same placement, and prove score 0 with no barrier left. I'll extract each current def to `orig.c`, score a lever-free baseline (`nopin.c`), then iterate candidates with `dt.sh`; a match requires the listed `kinds` gone.

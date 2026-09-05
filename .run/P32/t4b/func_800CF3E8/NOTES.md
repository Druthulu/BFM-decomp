# func_800CF3E8 (md_MAIN_003, 469 ins) — S83 pointer (residual 27, one cause: cse.c find_best_addr swaps the pinned base's
offset-0 tag-load address for a pseudo; §500-H). The S83 Opus second look refuted the alias lever 5/5 and found the pinned-pointer
launder `__asm__("" : "=r"(p6) : "0"(p6))` frees the load (idx 0–377 & 385–399 exact) but lands it 4 slots late (79 @ 470).
Next: the freed load must land at slot 380 — give it a consumer/dependence that pins it there (a zero-byte asm USE of the
loaded tag right after the target's slot-380 position, or make the tag load feed the FIRST store of the block so sched1's
critical path puts it first). Report: .run/P32/t3/reports/func_800CF3E8__opus_s83.md.

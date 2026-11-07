---
agent: ext-T11.cG25x
label: T11.cG25x
---
Approach: these three are header bodies where a `__asm__` keepalive forces a register/value to stay live so a pinned hard reg is chosen or a value is not folded. Removing the keepalive must be replaced by a real C use that creates the same liveness or reference weight — for item 1, making `pm` (the `param_2 & 0xffff` mask result) genuinely live across the `div`/`dm` setup so the `$3` pin holds the `andi` result; for item 2, real uses of `bVar1`, `iVar7`/`t`, and `fc` in later code instead of empty asms; for item 3, a real use of `s0` after the `& 0xFFFFFFFB` store. I test each with `dt.sh` and verify all includers with `tryinc.py` at the end.

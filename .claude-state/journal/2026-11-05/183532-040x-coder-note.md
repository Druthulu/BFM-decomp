---
agent: ext-T11.cG18x
label: T11.cG18x
---
The barrier here guards a cross-jump between the last block's tail and the `dec:` block's tail. Reading gcc 2.7.2's `find_cross_jump` (tools/reference/gcc-2.7.2/jump.c:1978) shows the minimum-1 merge only happens when the target label's physical predecessor is the identical `sw`; if the last block also ends in an explicit jump, the jump_chain retry needs 2 matching insns and stops. So the lever-free move is likely a plain `return;` at the end of the last block (deleted as a jump-to-next later, so zero extra bytes).

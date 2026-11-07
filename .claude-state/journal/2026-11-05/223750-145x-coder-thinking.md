---
ts: 2026-11-06T05:37:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MwV1qH5CDk89BFsWZORD
---
Item 4: baseline 0; lever-free score 9, 176 vs 174 insns (2 extra). Differences:
1. mine[47] beqz s1 → target beqz s1 (address shift only).
2. mine[96:99] `beq v1,v0; nop; j` vs target[96:97] `bne v1,v0` — a branch inversion!
3. mine[103:105] `bnez v0; move v0,s1` vs target[101:102] `bnez v0` — mine has an extra `move v0,s1`.
4. mine[107] missing `ori s1,s1,0x4000` (moved to 123 in mine).
5. mine[122:124] `j; ori s1` vs target[120:122] `j; move v0,s1`.

So the barrier (memory clobber) affects the branch shape / code motion around the `if (ret == 0x2000) ... else if (ret == 0x4000) ...` and the `ret &= ~0x2000; ret |= 0x4000;` part.

Let me look at the source:
```
ret = func_80133784(0, &sp10, (s32)&sp18);
if (ret != 0) {
    ... stores ...
    if (ret == 0x2000) {
        __builtin_memcpy((void *)(arg0 + 0x120), (void *)D_801152A8, 8);
    } else if (ret == 0x4000) {
        __builtin_memcpy((void *)(arg0 + 0x120), (void *)&D_801152B0, 8);
    }
    if (*(u16 *)(arg0 + 0x16C) != 0x1D) {
        return ret;
    }
    if ((func_80029178(0x21) & 0xFF) == 0) {
        ret &= ~0x2000;
        ret |= 0x4000;
        __builtin_memcpy((void *)&D_801152B0, (void *)D_801152A8, 8);
        D_801152BC = 1;
    }
    __asm__ __volatile__("" ::: "memory");   <- the barrier at line 42
    return ret;
}
/* ret == 0 */
...
```

So the barrier is right before `return ret;` — it prevents... hmm, a memory clobber before the return. It affects the code motion of the `ret |= 0x4000` (ori s1,s1,0x4000) and the memcpy.

The diff shows:
- target: `bne v1,v0, a10c` (branch to the "else if ret == 0x4000" path) vs mine: `beq v1,v0, ...; nop; j ...`. So the branch structure differs (inverted).
- target has `ori s1,s1,0x4000` at position 104 (before a jump), mine at 123.

Hmm, this is a code-motion difference: the `ret |= 0x4000` is hoisted/moved.

Let me look at the target's disassembly around there to understand. Let me dump the target.

The barrier's effect here: it prevents the compiler from moving the `ori s1,s1,0x4000` (or the memcpy) across it.

Let me look at the full target listing around the relevant region.

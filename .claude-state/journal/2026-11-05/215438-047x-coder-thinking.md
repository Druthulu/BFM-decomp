---
ts: 2026-11-06T04:54:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7PXUP64OKmbvElUibzSx
---
The target has the duplicated code (each block duplicated), and without the barriers cse merges the identical blocks. So the barrier is a cse barrier. We need a real-C way to prevent cse from merging equivalent expressions.

Classic cse-breakers in real C:
- Different expression spellings that compute the same value but aren't recognized as equivalent (e.g., `x + y` vs `y + x`? cse canonicalizes commutative ops).
- Different temp variables with different life ranges (a store through a different pseudo).
- Dead-reset (C0414): `p = 0;` between blocks kills the equivalence.
- Making the second store use a different variable whose value cse can't prove equal.

Let me look at the actual source blocks:

```
if (a2 != 0) {
    D_80078EA4 += a1;
    BARRIER;
    if ((s16)D_80078EA6 >= 0xA1) {
        D_80078EA4 = 0xA00000;
    }
} else {
    if ((func_80029178(0x1B) & 0xFF) != 0) {
        D_80078EA4 += a1;
        BARRIER;
        if ((s16)D_80078EA6 >= 0xA1) {
            D_80078EA4 = 0xA00000;
        }
    } else {
        if ((s16)D_80078EA6 < 0x80) {
            D_80078EA4 += a1;
            BARRIER;
            if ((s16)D_80078EA6 >= 0x81) {
                D_80078EA4 = 0x800000;
            }
        }
    }
}
```

Wait, in the third block, `if (>= 0x81) D_80078EA4 = 0x800000;` — inside `if (< 0x80)`, so the inner condition is never true (0x80 is not < 0x80... hmm: if D_80078EA6 < 0x80 then D_80078EA6 >= 0x81 is false). So the store is dead? But the target has `slti v0,v1,129` at mine[51]/target[74]... Hmm.

Wait, target block 3: `lh v0; nop; slti v0,v0,128; beqz v0,join; nop; lui v0,0; lw v0,0(v0); nop; addu v0,v0,s1; lui at; sw; lui v0; lh v0; nop; slti v0,v0,129; ...` — so it loads D_80078EA6, checks < 0x80; then does the += and then checks >= 0x81 (slti 129 = <129, i.e. <=0x80; so if >= 0x81 store 0x800000).

Hmm, wait: `slti v0,v0,129` → v0 = (D_80078EA6 < 129); then presumably `bnez v0, skip` or `beqz`. In the target at 74-75: slti 129; then j at 74? The diff shows target[74:75] = slti and mine[67] = j. Confusing.

Anyway, the crux: cse merges the three copies of `D_80078EA4 += a1` + the check.

Real-C cse-breakers:
1. Give each arm a different temp for the loaded D_80078EA6, e.g. `s16 t = D_80078EA6;` in arm 1, `s16 u = D_80078EA6;` in arm 2, etc. cse might still see the load as equivalent and substitute. But if the temps are distinct pseudos and each has a store in between... Hmm.

2. The `+= a1` store: `D_80078EA4 += a1` in each arm. cse's equivalence for the *load* of D_80078EA4 and the *store*. The barrier prevents cse from forwarding the stored value across the barrier.

3. Dead-reset (C0414): insert `D_80078EA4 = 0;`? No, changes semantics.

Actually, C0414 is a "dead-reset cse-breaker": a dead store that kills the equivalence. E.g., `x = 0;` where x is dead — cse can't track the memory across an aliasing store... but a store to D_80078EA4 itself would break it.

Hmm, let me think about what exactly cse merges. Between the first block's store `sw v0, D_80078EA4` and the second block's identical code, cse sees: both load D_80078EA4, add s1, store. If the path between them doesn't store to D_80078EA4, cse can reuse the *value* from the first store... The barrier stops it.

Wait, but actually the structure is: the three blocks are on *different* paths (if/else-if/else), not sequential. cse's extended basic blocks span the join? Hmm, the paths are exclusive, so how can cse merge them? Because cse treats the CFG; the `else` arm's block is reachable only via the else branch. But cse can still replace a redundant computation if the same expression was computed on all paths to that point (cse does "available expressions" per EBB with jumps ending EBBs...). 

Hmm, the target's code has duplicated `lh v0, D_80078EA6` etc. in different arms. Without barriers, mine has fewer instructions — so gcc *did* merge (probably by cross-jumping? no, that's jump2). Or cse forwarded the D_80078EA4 value.

Look at mine[25:44] vs target[27:28]: mine has a 20-insn block where target has 1. So mine has MORE there? No: `replace mine[25:44] target[27:28]` means mine[25:44] (19 insns) replaced by target[27:28] (1 insn). Then `replace mine[51:52] target[35:59]` means mine[51:52] (1) replaced by target[35:59] (24). So mine has a big block at 25-44 where target has 1, and target has a big block at 35-59 where mine has 1. It's a reordering/merging difference.

This is complex. Let me look at the actual target and candidate disassembly side by side.

Let me find the object for item 2.

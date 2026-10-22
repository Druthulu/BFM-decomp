---
ts: 2026-10-22T00:16:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_KPPRgTABVsKo0Za07yMR
---
(V2's alloc table: r103 = the RESULT_DECL (pri 10000, refs 3, live 3, prefers v0) — now the LOWEST-numbered among the 10000-tie group? No: r102 (a temp, blk 3) is lower than r103 → r102 wins $2 ✗. And the temps r102/r106/r111/r117 (pri 10000) also compete.

So the RESULT_DECL (r103) ties with r102 (a temp in block 3) and loses (r102 < r103).

To win, the RESULT_DECL needs pri > 10000 → refs ≥ 4 with live 3 → 26667 ✓ (V2 has refs 3 — hmm, so the direct-return version didn't raise the refs).

Hmm, r103: refs 3, live 3 — same as before (r104 in the nopin version). So the RESULT_DECL's refs stayed 3.

Hmm, what makes the RESULT_DECL have 3 refs? In V2: `return X;` and `return 1;` → 2 sets + 2 uses = 4? But it shows 3. Hmm, maybe gcc merges the returns into one block (cross-jump) → 1 set + ... hmm.

Let me think about what the RESULT_DECL's refs mean: "Register 103 used 3 times across 3 insns". So 3 references over 3 instructions.

To get refs=4: the RESULT_DECL must be referenced 4 times. E.g. 2 sets + 2 uses.

Hmm, in V2 the two returns are in different blocks → 2 sets + 2 uses = 4 refs. But the table says 3 ✗ (maybe one return was merged or the copy was optimized).

OK, let me think about lever C instead: make the temps' live longer (3 instead of 2) → their pri drops to 6666 ✓ and the RESULT_DECL (10000) wins $2 ✓.

The temps are the load temps: `lh v0,6(s0); lh v1,160(s0); bne v0,v1` — the first temp's live = 2 insns (from its load to the bne = 2 insns? the load itself + the compare). Hmm, the table says the temps have live 2 (blocks 3,6,7,8,9).

To make a temp live 3 insns, the loaded value must be used 3 insns later. E.g. if the source loads into a variable and uses it a bit later:
```c
    v6 = *(s16 *)(s0 + 6);
    v7 = *(s16 *)(s0 + 0xA0);
    if (v6 == v7 && ...) {
```
V1 did that and gave the same score (11). Hmm, but maybe V1's temps still had live 2 (gcc folded them into the same pseudos).

Hmm. Let me dump V1's table? That's another dump cycle. Hmm.

Alternatively, think about the target's allocation: the target (pinned) has the temps in $3/$4 and r in $2. In the pinned version, `r` is a hard reg → no competition. So the ROM's allocation of the temps ($3, $4) is just "the next free regs after $2".

For the lever-free version to match, the RESULT_DECL must take $2 and the temps $3, $4 ✓.

Since the RESULT_DECL ties at 10000 with the temps and loses the tie-break by allocno (r102 < r103), the lever is: make the RESULT_DECL's allocno LOWER than the temps' allocnos. The temps' allocnos (r102, r106, r111...) are created during RTL expansion of the loads; the RESULT_DECL (r103) is created... hmm, r103 is created before r106 but after r102. The RESULT_DECL is created at the return statement (late in the source) — but its number r103 is low because pseudo numbers are allocated per-function in order of creation: the front end creates the user's variables first (r74, r75, r77 = the user's globals?), then the RESULT_DECL?, then the temps.

Hmm, r73 = s0 (the param), r74/r75 = other user variables (crossing calls), r77 = another user var (pri 7500, refs 3, live 4, conflicts a0,sp).

In V2 the user variables are: s0 (param), s1, s2, q (and t, chk in the inner block). So r74, r75, r77 = s1, s2, q or t/chk.

And r103 = the RESULT_DECL (created when the return statement is expanded — after the user's vars but before the temps? hmm, r102 = a temp in block 3 (created early in the RTL).

Hmm, r102 < r103: the temp in block 3 was created before the RESULT_DECL. Block 3 is early in the function (the `func_80012C6C` calls?). So the temps in the early blocks get lower numbers ✗.

The temps in block 9 (r124, r127) are HIGHER than r103 ✓ — so the RESULT_DECL (r103) beats those by allocno ✓. But r102 (block 3) beats it. Hmm, but wait: is r102 in the same BLOCK as the RESULT_DECL? The RESULT_DECL is in block 9 (the return). The local-alloc works per block: within block 9, the pseudos are r122 (pri 6666), r124 (10000), r127 (10000), r103 (10000) → the tie among r103, r124, r127 → the lower allocno (r103) wins ✓✓ → the RESULT_DECL should get the first reg in block 9!

But the observed code has the temps in $2/$3 in block 9 ✗. Hmm! Unless the block-9 allocation order differs (the local-alloc might assign by a different rule within a block, e.g. by the "reg" preference).

Hmm, but r102 (block 3) and r106 (block 6) etc. are in other blocks — each block's local-alloc is independent. So in block 9: r103 (10000), r124 (10000), r127 (10000), r122 (6666) → r103 has the lowest allocno → it should get $2 in block 9 ✓.

But the compiled code (V2) had `lh v1,6(s0); lh v0,160(s0)` → the temps in $3/$2 ✗ (the temp in $2). Hmm! So r124 (hard v1) and r127 (hard v0) — the table says r127's hard reg is v0 ✗ (so the temp got $2, not the RESULT_DECL).

Hmm, so within block 9, r127 (a temp) got v0 and r103 (the RESULT_DECL) got... nothing (it's a global "-" → allocated by global-alloc!). Hmm! r103 has hard "-" and is in the .greg order (73 103 77 74 75) → so r103 IS a global allocno → global-alloc allocates it (not local-alloc) → it gets a CALLEE-SAVED register (the globals get $16+ first) — hmm, but then the RESULT_DECL would be in $16-$19 ✗ (not $2).

Hmm, but the RESULT_DECL "prefers v0" — global-alloc honors the preference when allocating the caller-saved regs. The global order: 73 (s0), 103 (the result), 77, 74, 75. The globals get callee-saved regs first (s0 → $16, then the next global → $17, ...) — so r103 would get $17?! But the "prefers v0" preference would make global-alloc give it $2 (a caller-saved reg) instead ✓ — that's how the preference works: `allocno->reg` (the preferred hard reg) is honored when allocating.

So r103 (the RESULT_DECL) should get $2 (its preference) — but the observed code has a temp in $2 ✗ and the result in $4.

Hmm, why? Because the CALLER-SAVED regs are allocated to the globals in the .greg order, but only after the callee-saved ones... and the "prefers v0" only matters if v0 is still free at that point. The temps (local pseudos) are allocated by local-alloc AFTER global-alloc → so the global (the RESULT_DECL) should get $2 first ✓.

Unless the RESULT_DECL's allocno was refused the preferred reg due to a conflict: the note says "conflicts sp" only.

I'm clearly missing something about gcc 2.7's global-alloc. Let me look at the .greg dump for the preferences/order lines of this function — maybe the ";; N preferences:" lines show what r103 prefers and whether it got v0.

Let me grep the .greg dump for the function section and look at the order/preference lines. That's informative: the .greg dump carries "the INPUTS to global allocation — the order, each allocno's conflicts and its copy preferences".

Let medo that.

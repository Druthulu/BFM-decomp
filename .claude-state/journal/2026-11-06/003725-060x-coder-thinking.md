---
ts: 2026-11-06T07:37:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Y25sZE3rR9ku9sZ38PuT
---
Confirmed: a block-scope `(void)` declaration in an earlier function changes the global function type and persists, causing "too many arguments" later. This is a quirk of GCC 2.7.2 (and actually C standard says block-scope extern declarations have external linkage and the composite type rules; declaring `(void)` when a non-prototype definition exists... it should be a conflict, but GCC accepted it with a warning and changed the type).

So how do the target bytes call func_800CAF84 with an argument while func_800CB400's `(void)` decl precedes? In the ORIGINAL source, func_800CB400 has `extern void func_800CAF84(void);` and calls it with no args. If our function called it with arg0, it would fail to compile as shown. So the original source must have called `func_800CAF84()` with NO args! Then the target's jal has no arg setup — consistent with no args. But then what keeps a0 live across the copies?

Hmm wait, maybe func_800CB400's `(void)` decl is itself a lever artifact? Let's check its bytes vs target: it's in the tree and builds, so its `(void)` decl is part of the banked source. If it leaked the type, then ANY later call with args would fail. func_800CB158 (earlier) calls with arg0 fine. Functions after 238 that call with args: our function (line 269, no args). So the file is consistent.

Therefore our function's call is genuinely with no args in the original. So the a0 liveness must come from something else.

BUT: the block-scope `(void)` declaration in func_800CB400 is at line 238. What if the original our-function source had NO local extern decl at all (relying on the leaked `(void)` type) and called `func_800CAF84()`? That's plausible! Then the local extern `(void)` in our body might be a lever artifact or unnecessary. Removing it should not change codegen. Let me test removing the local extern but keeping the no-arg call. That was v30-ish? No, v30 changed the call to arg0. Let me test: base with local extern removed, call unchanged.

That won't change codegen (same call), so score stays 14. The a0 issue remains.

Hmm. So what natural C reserves a0?

Let me reconsider the leaked-type discovery: the `(void)` prototype is GLOBAL after line 238. Does that affect our function's call codegen? No.

Let me go back to finding the a0 reservation. Maybe the answer is that the original our-function source had its own local `extern void func_800CAF84(void);`? Not relevant.

Think about `s0`: In the target, `move s0,a0` at insn 2. The struct copies use a1-a3, meaning a0 live. What if the original source used `arg0` directly for the two struct copies (like the sibling func_800CB158 does), i.e.:
```
*(Struct16 *)(arg0 + 0x38) = *(Struct16 *)(v0 + 0x34);
```
and ALSO used arg0 in the if-block? Then arg0 is live from entry through the if-block, crossing the call → callee-saved → the compiler copies it to s0 at entry, and all uses become s0. Then a0 is dead after the move. Same.

Unless the compiler keeps arg0 in a0 for the FIRST block (before the call) and copies to s0 only before the call? GCC 2.7 global-alloc doesn't split live ranges, so no.

Hmm, wait: what if the call `func_800CAF84()` is at the END and there's a use of arg0 AFTER the call, but the compiler... no.

Let me look at the target again: is a0 really "live" in the first block, or could the a1-a3 allocation be due to a *suggestion* (copy_sugg) from something? The 4 loads each feed a store. `combine_regs` can tie a load's pseudo to the hard reg suggested by a copy. The store `sw v1,56(s0)` — the value in v1 was loaded from `52(v0)`. No hard reg suggestion.

But local-alloc's `qty_phys_copy_sugg` can suggest hard regs from `mov` instructions. Is there a move before? `move s0,a0` suggests a0 for s0's qty? That's the s0 qty (callee). Hmm.

Actually, here's another thought: `find_free_reg` excludes `regs_live_at[ins]` for the qty's live range. The copy temps' live ranges are within the block. If the *function's incoming arg0* is still considered live at those insns because the `move s0,a0` is a REG_DEAD note that flow didn't add? The K&R-style parameter... Actually, in target, `move s0,a0` at insn 2: if there's no REG_DEAD note on a0, local-alloc thinks a0 is live throughout the function! That would reserve a0 everywhere. But then `li a0,75` at 32 would conflict. Local-alloc is per-block; a0 live at insns 0..? The `li a0,75` is in the if-block (a different block), so no conflict within a block. And regs_live_at for the first block would include a0 (live from entry to... end of function if no REG_DEAD). That would reserve a0 in the first block! And in the if-block, a0 is defined (li) and used, so it's local there.

When does a move's source not get a REG_DEAD note? If the parameter is used later, no REG_DEAD. But then a0 would be live across the call (needs callee-saved). Unless the later use is only in the if-block where a0 is redefined by `li a0,75`... no, a0 is redefined, so the old value dies.

Hmm, but in target, maybe the parameter arg0 IS used later and the compiler allocated it to a0 (caller-saved) DESPITE crossing the call? That would be a compiler bug; not likely.

Let me look at the if-block in target: `li a0,75` — this redefines a0. So arg0's value in a0 is killed there. Between the move and the if-block, arg0 in a0 is live but unused. If the compiler's liveness says arg0 is live to the if-block (because the original used arg0 there, e.g. `((Unkstruct*)arg0)->unk1C`), then arg0 crosses the call → global-alloc gives it a callee-saved reg... but wait, if the if-block uses arg0, the compiler would replace those uses with s0 (the callee copy) — and then a0's live range ends at the move. Hmm.

UNLESS the if-block's use is a RE-DEFINITION, not a use: `id` is assigned in the if-block to a0. But that's a different pseudo.

Let me consider: maybe the original source is exactly like the sibling func_800CB158 but with the structure:
```
void func_800CB458(s32 arg0) {
    s32 s0 = arg0;
    ...
    func_800CAF84();
    if (...s0...) { ... }
}
```
and the a0 reservation comes from the `func_800CAF84` call being to a function whose prototype (leaked `(void)`) is fine.

I'm going in circles. Let me try to get the RTL dump to see which pseudo is in a0. tools/cc1_dumps_tu.sh + tools/alloc_table.py. Let me check the alloc_table tool: it shows the allocation table. The brief points to tools/alloc_table.py for TU dumps. Let me read its help.

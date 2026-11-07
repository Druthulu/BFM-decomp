---
ts: 2026-11-06T04:02:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Shv6o6aZMAVUP0MmWNJ7
---
c1 still has ONE lh (v1,46(s0)) — the do-while did NOT break the load forwarding here. Wait but ins count is 59 (target 59). Hmm, mine has 59 now because of the loop overhead (maybe an extra nop). And score 10.

The do-while changed scheduling: `lh v1,46` before `li a0,8` and the load feeding both `subu` and `sll v1,v1,6` — still forwarded (single load).

So do-while doesn't break cse load forwarding. Right: cse1's load forwarding within a block; a do-while(0) creates a loop but cse processes the whole loop and can still forward? Hmm.

So we need another route to prevent forwarding. Let me think again about the original source.

Maybe the original source's second load is NOT the same address expression. Let me look at the target's lhu v1,14(s0) — that's `*(u16*)(s0+0xE)`. And lh v0,46(s0) twice. What if the first lh is from `*(s16*)((s32)s0 + 0x2E)` and the second from `((s16*)s0)[23]`? Same.

Hmm, what if the second is through a `u16` then cast to s16? `(s16)*(u16*)(s0+0x2E)` → lhu, not lh. Target lh.

Wait, maybe the second lh is actually loaded from a *different* base: 46(s0) — the same. Yes.

Could the target's double load come from the *barrier* being present in the ROM build? The build/ target is the current tree's build. If the tree currently has the barrier, the build object = barrier version = matches ROM (score 0). So the ROM's original code has the double load. The ROM was compiled from Square's original C with the same compiler. So there IS a C formulation.

Let me think about what prevents cse in the original. Perhaps the original source used `s16` fields in a struct with the struct having a *different* type for the two accesses, and cse's `exp_equiv_p` compares... we saw it ignores in_struct. But wait — the hash function: `hash += (unsigned) MEM;` and for the address: `goto repeat`. The `hash_arg_in_struct` is set as a side effect and stored in the table entry, but the hash itself is the same. Table lookup uses `find_best_addr`? Actually the matching of a MEM to a table entry: in cse_insn, for a load, `lookup`? Let me read the section that records MEM loads (around line 6300-6500). But the key comparison is exp_equiv_p, which ignores in_struct.

Alternatively, the original might have had the load in different *basic blocks* with a store in between? No.

Wait, maybe the barrier in the source corresponds to something else entirely: perhaps the original C had the two blocks in a different order or the `t = diff << 9` uses a different variable. But the double load is the only diff.

Let me reconsider the diff more carefully. In target:
77c8: li a0,8
77cc: lh v0,46(s0)
77d0: lhu v1,14(s0)
77d4: subu a0,a0,v0
77d8: lh v0,46(s0)
77dc: sll a0,a0,0x9
77e0: sll v0,v0,0x6
77e4: addu v1,v1,v0
77e8: sh v1,14(s0)

Hmm! Notice: the second lh v0,46(s0) at 77d8 — could this be a RELOAD of a pseudo that was spilled? No, there's no spill (no stack use).

Could it be that the first lh's value is used by subu, and the second lh is a *separate CSE-insensitive* load because the first was in a different *equivalence class* due to being loaded with a different signedness... The mode is HImode for both.

What if the first is `*(s16*)` (QImode? no) and the second is a `u16` load that got sign-extended by explicit shifts? e.g. `(s32)(s16)(*(u16*)(s0+0x2E))` → lhu + sll/sra? Target has plain lh, so no.

What if the first access is a 32-bit load then truncated? Target lh.

OK, different approach: maybe make the first load's value *not available* at the second point by forcing a clobber of the pseudo — e.g., the first load's result is used in a context that ends its live range: assign `diff = 8 - x;` where x is a temp; then reuse the SAME temp variable for something else that gets overwritten before the second use. But cse would still substitute the load's pseudo into the second use (cse replaces the MEM with the pseudo regardless of C variable scoping). Unless the pseudo is dead... cse's `reg_in_table`/`reg_tick` validation: cse replaces a load with a register only if the register still holds the value (reg_tick == reg_in_table). If between the two uses the register is *clobbered* (e.g., assigned another value), cse can't forward. But the register holding the load's value is a pseudo; cse tracks pseudo assignments too: if the pseudo is reassigned between, the entry is invalidated.

So: reuse the temp variable! In the C, if the first load is assigned to a variable `x`, and then `x` is reassigned before the second access, cse's table entry for the load (which is tied to the register of the first load) would be invalidated when that register is reassigned. But careful: cse works on RTL; each C variable maps to a pseudo; if the same C variable is reassigned, that's the same pseudo being SET again → invalidates the load entry for that pseudo.

Current source:
```
s32 diff = 8;
diff -= *(s16*)((s32)s0 + 0x2E);   // load into pseudo (say r70), subu
t = diff << 9;
{
    s32 x2 = *(s16*)((s32)s0 + 0x2E);   // second load
    ...
}
```
The first load's result pseudo (r70) is used by subu; then not reused. cse's table has entry {MEM 0x2E(s0) → r70}. At the second load, it checks if r70 is still valid (reg_in_table == reg_tick). Since r70 wasn't reassigned, valid → forward.

To invalidate: reassign the pseudo that holds the load. In C, that means the compiler must reuse the same pseudo for a later assignment. E.g.:
```
s32 x = *(s16*)((s32)s0 + 0x2E);
s32 diff = 8 - x;
t = diff << 9;
x = 0;                    // reassign x -> invalidates the load entry for x's pseudo
{
    s32 x2 = *(s16*)((s32)s0 + 0x2E);
    ...
}
```
But `x = 0` is dead; GCC would delete a dead assignment? At -O2, dead stores to locals may be eliminated by... In 2.7.2, there's no DSE pass, but `combine`/`cse`/`flow` may remove dead code? A dead assignment to a local pseudo that is never used: `flow` (dead code elimination) removes insns whose result is dead! Yes, flow.c's `delete_dead_code`/life analysis removes dead sets. So x=0 would be removed. Unless the variable is used later.

What if the same variable is genuinely reused for the second load:
```
s32 x = *(s16*)((s32)s0 + 0x2E);
s32 diff = 8 - x;
t = diff << 9;
x = *(s16*)((s32)s0 + 0x2E);   // same variable reused
*(u16*)((s32)s0 + 0xE) += (x << 6);
```
Here `x` is one pseudo, assigned twice. First assignment's load result in x; second assignment sets x again. cse: the first load's table entry maps MEM→x. When the second load is processed, cse checks whether x is still valid; x was SET (by the second load) — but the check happens at the second load before its own set is processed? Order: cse processes the insn `set x = MEM`. It first checks the table for MEM equivalence: finds entry MEM→x, but validation `reg_in_table[REGNO(x)] == reg_tick[REGNO(x)]` — the tick for x may be bumped because x is being set by this insn? cse_insn increments reg_tick when it sees a SET of a register. Actually the insn is processed as a SET: cse_insn first canonicalizes the src (the MEM), looks it up, then records the dest. Hmm, the invalidate for the dest happens when processing the dest. Let me think: in cse_insn, for `set (reg x) (mem ...)`, the src (mem) is looked up first? Or the dest first?

In cse_insn, it computes `sets[i].src`, `src_elt`, then for each set: "If this is a store, invalidate memory"; then it records the destination and its value. The destination register x is recorded as having the value MEM. If x was already in the table with the same value... The order of operations matters.

Actually a simpler, well-known CSE-defeating idiom: reassigning the variable. Let me just test it.

Let me construct c4:
```
    {
        s32 x = *(s16 *)((s32)s0 + 0x2E);
        s32 diff = 8 - x;
        t = diff << 9;
        x = *(s16 *)((s32)s0 + 0x2E);
        *(u16 *)((s32)s0 + 0xE) += (x << 6);
    }
```
Wait, but the first block declares diff with init; the original had `s32 diff = 8; diff -= ...;`. Let me keep structure:
```
    {
        s32 x;
        s32 diff = 8;
        x = *(s16 *)((s32)s0 + 0x2E);
        diff -= x;
        t = diff << 9;
        x = *(s16 *)((s32)s0 + 0x2E);
        *(u16 *)((s32)s0 + 0xE) += (x << 6);
    }
```
Hmm, but reusing x for both loads changes liveness: the first x value dies at `diff -= x`, then x is redefined. cse might still forward the second load using the first's value if the register is the same and still valid... but the register was just redefined by the second load — the validation check is exactly what determines. Let's just test.

Actually there's a subtlety: the second load `x = MEM` — cse looks up MEM in the table, finds the first load's entry with value = x's pseudo (since the first load's dest was x). Since the entry's value register IS x and x is being set right now, validation `reg_in_table[x] == reg_tick[x]` — reg_tick[x] is incremented when cse sees the SET dest. But the lookup happens before recording the dest? Let me check cse_insn's order: I recall it processes src first, replacing it with equivalent, then handles the dest. If the src lookup sees the old entry valid, it would replace the load with x itself (self-assignment `x = x`) which is then deleted → single load. Hmm.

But maybe the entry is invalidated because x's tick was bumped when the insn was scanned in `cse_insn`? Let's look at cse_insn around where it handles the SET dest and src. Let me read the relevant part. Actually easier: just test empirically. Let me create c4.

Another idea: use two different variables but force the first to be redefined: `x = ...; diff = 8 - x; x = 0; ...` — dead store removed.

Let me test c4 (single var reused).

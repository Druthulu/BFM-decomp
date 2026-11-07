---
ts: 2026-11-06T15:39:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZI1ai198rLXw7HG6wu54
---
vn gives 403 ins (off variable caused extra). All same 6.

I think this is the cse-const-addr wall for a constant symbol address. But wait — the target keeps the base in a register. Is there any *real C* that yields a base register? The moves line 24: "greg-const-ptr-priority — e (const symbol ptr, 2 refs)..." suggests const symbol pointers do get registers sometimes.

Hmm, actually let's reconsider: maybe cse's early return for CONSTANT_ADDRESS_P happens only in find_best_addr (for memory addresses). Here the address is an argument to a call, not a memory operand. The folding of `mb+24` to the constant happens because mb's reg_equiv is the constant. cse replaces the reg with its equivalent constant (that's `fold_rtx` / `equiv_constant`). This is cse's constant substitution of a register whose only set is a constant. 

In cse, a register set to a constant gets a REG_EQUIV/reg_equiv_constant entry, and uses are replaced by the constant (if `cse_insn` decides). This happens for the *first* use too, so `mb + 24` becomes `(const sym+24)`. Then cse materializes it once.

To prevent mb from being treated as a constant, we need it to have more than one set, or be set from a non-constant. The "second set" move: "Set counts steer three passes: a second identical assignment demotes sched1's birthing boost, keeps a constant off REG_EQUIV's doubled live length". So a second identical assignment to mb would demote the constant equivalence? "keeps a constant off REG_EQUIV's doubled live length" — hmm, a second set means mb is not a constant-only pseudo, so cse can't substitute.

Let's test: assign mb = &D_800AF630 twice (same value) before the first call:
```
mb = (u8 *)&D_800AF630;
mb = (u8 *)&D_800AF630;    /* second set */
func_8004914C(mb + 0x18);
func_800491AC(mb + 0x18);
```
Now mb has 2 sets of the same constant. cse might still know the value is constant at each use... but the reg_equiv_constant is only set when there's a single set. With 2 sets, cse can't keep it as a constant across; at each use, mb's value is known from the most recent set? cse's local value tracking (reg_eqv) would still know mb == constant within the block after the set. Hmm, but `mb + 24` would be folded via fold_rtx using the "known value" table. Let me just test.

Variant r: double set before first call.
Variant s: second set between the calls (tested a → 6).
Variant t: set mb once, then a different variable mb2 = mb; calls use mb and mb2? cse still constant.

Test r. Also maybe a self-increment pattern: 
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb += 0x18;
func_800491AC(mb);
```
tested b → 6.

Hmm b scored 6; what was the diff? Maybe s0=base+24 still. Let me check dt for vb quickly. Actually sc only gives score. Let me check vb diff: could be different from 6 (maybe addiu per call?). Let me run dt on vb.

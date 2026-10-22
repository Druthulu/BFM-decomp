---
ts: 2026-10-22T12:56:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_toMZfbL1Hvhua9gLw7ol
---
This is a deep rabbit hole. Let me step back and take a completely different, PRACTICAL approach:

**Empirical search over spellings.** I'll write a generator that produces many variants and score them in a batch (1s each). If none works, record a WALL with the mechanism (cse substitutes the constant address into the plus; only an opaque base keeps the base reg — the tag would be "cse-const-addr", which already exists in walls.txt!).

Actually — walls.txt already has: `cse-const-addr  cse  cse folds or substitutes a constant/absolute address the target keeps base-relative (T10 S09, S11, S16)`.

That's EXACTLY our wall! So if I can't crack it, the result is WALL cse-const-addr.

Given the time (I'm ~40 min into item 2), let me do a focused batch of spelling attempts (maybe 15-20 variants), and if none works, record the WALL.

But wait — before giving up, let me reconsider the "the base is used twice" idea in a *layout-preserving* way for C750 (which has a runtime parameter a0!). In C750's ELSE branch, we could use `a0` — e.g. an expression that's value-preserving: `p = it + 0x658C` where the base is used in a compare with a0? That changes semantics ✗.

Hmm, hold on! For C750's ELSE branch, is the base used elsewhere? Hmm.

Hmm, what about this idea: **the base's value could be forced into a register by using it as the base of a MEM access that the compiler folds into the same address**? E.g. `*(u8 *)it` → a load ✗ (extra instruction).

Hmm, what about `&((u8 *)it)[0]`? That's the address itself — the front end would fold it to the constant.

What about taking the address of a LOCAL variable and adding the difference? no.

**IDEA: use the `sizeof` trick**: `p = it + 0x658C;` → what if we write `p = it + (s32)(sizeof(u8) * 0x658C);` → folded.

**IDEA: Use a conditional expression**: `p = it ? it + 0x658C : it + 0x658C;` → GCC folds.

**IDEA: Use a comma/sequence**: no effect.

**IDEA: Cast through a pointer-to-int of a different size**: `(s32)(long)it` → on a 32-bit target, long is 32 bits → no-op.

**IDEA: Cast through a function pointer type**: `it = (s32)(void (*)())D_80120194;` → the cast between a data pointer and a function pointer — GCC might not fold it? The value is the same. In RTL, the cast would be a no-op (both are 32-bit addresses) → folded. Hmm, but maybe the front end keeps it as a "conversion" → hmm.

**IDEA: `(s32)(volatile u8 *)D_80120194`** → the cast to a volatile-qualified pointer: the VALUE is the same; the qualification doesn't affect the address. GCC would fold it. Hmm, but maybe it prevents the "const" propagation? The address of a non-volatile object cast to a volatile pointer — the value is still a constant. ✗ probably.

Let me now think about what makes GCC keep a *constant* in a register: reload's rematerialization vs. the REG_EQUAL note. The REG_EQUAL note on insn 9 (73 = symbol_ref) is the mechanism. The note is added when the set's src is a constant and the dest is a reg and n_sets == 1 (for that dest in the block?).

In the n2 experiment, the note WAS added on insn 12 even with 2 sets of 73 in the block. Hmm, so n_sets != 1 didn't prevent it. Let me look at the exact code that adds the note (around line 6923) and what `n_sets` counts there.

From the earlier snippet:
```c
      /* If this is a single SET, we are setting a register, and we have
	 an equivalent constant, we want to add a REG_NOTE.   */
      if (n_sets == 1 && src_const && GET_CODE (dest) == REG
	  && GET_CODE (src_const) != REG)
```
This is inside a loop over `sets[i]` for the block. So n_sets = the number of sets in the BLOCK (not of that dest!). In n2, the block had 5 sets → n_sets = 5 → the note should NOT be added. But it WAS added!

Hmm, so the note came from elsewhere. Looking at the dump:
```
(insn 12 9 15 (set (reg/v:SI 73) (symbol_ref:SI ("D_80120194"))) 159 {movsi_internal2} (nil)
    (insn_list:REG_WAS_0 9 (expr_list:REG_EQUAL (symbol_ref:SI ("D_80120194")) (nil))))
```
This has a REG_WAS_0 note and a REG_EQUAL note. The REG_WAS_0 note is added when "the register previously held 0" — from the code I saw:

```c
	      /* If this is a single SET, ... and we have an equivalent constant ... */
	      if (n_sets == 1 && src_const && ...)
		{
		  tem = find_reg_note (insn, REG_EQUAL, NULL_RTX);
		  if (tem) XEXP (tem, 0) = src_const;
		  else REG_NOTES (insn) = gen_rtx (EXPR_LIST, REG_EQUAL, src_const, REG_NOTES (insn));
		  /* If storing a constant value in a register that previously held the constant value 0, record this fact with a REG_WAS_0 note */
```
Hmm, this block is guarded by "n_sets == 1" where n_sets is the count for this dest in the block? Let me look at the code just before line 6923 to see how n_sets is computed there.

Let me print lines 6860-6930.

Actually, from the n2 dump, the note WAS added with 5 sets in the block. So n_sets must be per-dest. Let me check: the code at 6102 `register int n_sets = 0;` then in the loop over sets: `if (GET_CODE (dest) == REG && REGNO(dest) < FIRST_PSEUDO_REGISTER) ...`. Hmm.

Let me look at the actual code at 6860-6930.

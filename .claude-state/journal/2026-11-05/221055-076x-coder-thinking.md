---
ts: 2026-11-06T05:10:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_G1xYNkjd1sTb8mFtPdn7
---
cse.c's `cse_end_of_basic_block` probably ends at CODE_LABEL or JUMP. Let me look for the function that determines the EBB end.

Actually, C0535's mechanism: "The block boundary splits cse1's extended basic block". Maybe the do-while generates a CODE_LABEL after all (from loop.c or the RTL expansion of do-while)? Hmm.

Let me check the u2 cse dump to see if the loop note is present. Let me run hdump on u2 and grep the .cse dump around the third block for the load.

Actually, let me instead try the dead-self-store idea and other variants quickly, and also test whether the cast is really needed by trying `D_80078EA6 = D_80078EA6;`.

Wait, actually — maybe a cleaner approach: what if I write the third block's inner condition using a **temp that is loaded via a pointer that the compiler already has**? Hmm.

Let me think about the alias-set mechanism. In gcc 2.7.2, `-fstrict-aliasing` doesn't exist (introduced in 3.0). But `alias_sets` exist in C++ and C (for type-based aliasing?). Let me check if the cast actually changed the alias set or something else. The cast `*(s16 *)&D_80078EA6` vs `(s16)D_80078EA6`: both produce a HImode MEM at the same symbol_ref. The RTL should be identical! Yet the output differs (114 vs 111 insns). So the difference must come earlier — at the tree/expand level, or the *type* of the expression affects `-fstrict-aliasing`... 

Hmm, actually maybe the difference is that `*(s16 *)&D_80078EA6` is a *different MEM alias set* recorded in the MEM's `alias_set` field at expand time. In 2.7.2, `get_alias_set` is called for MEMs when the type is a pointer dereference vs a variable reference. For a direct variable `D_80078EA6`, the alias set is from the variable's type (u16). For `*(s16*)&...`, the alias set is from s16. Different alias sets → cse's `exp_equiv_p` / `memrefs_conflict_p` treats them as potentially conflicting → no reuse.

So the cast changes the alias set. Is that an "identity address spelling"? It's the same address, but a different type/alias set. The rule's phrase "identity address spellings" suggests they consider this a launder.

Hmm, let me check the cookbook/moves for prior rulings on `*(T *)&x` as a cse-breaker. Let me grep moves.md and the cookbook for "alias" or "*(s16 *)".

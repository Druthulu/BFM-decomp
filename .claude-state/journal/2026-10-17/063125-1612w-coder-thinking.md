---
ts: 2026-10-17T12:31:25.701Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm wondering whether do-while(0) loop notes survive to the scheduler, since jump.c may delete loop notes for empty loops. Let me try an inline helper function that takes a pointer argument.

For this to work with gcc 2.7.2's deferred emission, the static inline helper must still exist in the file, which effectively adds another definition alongside the real function—so I need to check whether that counts as acceptable or still introduces an extra do-nothing symbol. Since the parameter is a const pointer, inlining would substitute the symbol reference directly everywhere it's used, meaning cse can see through it just like a constant propagation case, so the trick likely won't hide anything from cse after all.

I'm trying to think of what case genuinely blocks cse's ability to track the equivalence between a pseudo and its constant value—maybe something involving the address of a local static array, a struct field offset, or a differently-named symbol that's still effectively the same object, but none of these seem to actually evade cse's constant tracking either.

Right, expr.c's ARRAY_REF handling does fetch the constant element directly from a readonly array's initializer at expand time, but that would just collapse to the same symbol_ref as a plain reference—no extra base layer for cse to simplify. So that path doesn't explain it either, and function returns clearly can't produce a la. I need to pin down why cse itself would ever fold a plus of a register and constant back into a symbol in free.c's logic.

I'm digging into find_best_addr: when cse encounters a MEM address, it checks if it can replace with a cheaper equivalent from the hash table, comparing candidates like reg+k against const(sym+k) using ADDRESS_COST. Given MIPS costs favor reg+const_int as cheapest, that address shouldn't get folded back into the symbol form—so maybe the collapsing isn't happening in address selection but somewhere earlier, like cse1 substituting uses of the base register itself.

Checking address cost logic...

So symbol refs cost 2 while reg+small-constant costs 1, meaning the address-finding routine should prefer keeping reg+k rather than folding to a symbol. That contradicts what I'm seeing in the free dump, so I should stop theorizing and actually inspect the real CSE dump output to see what's happening.

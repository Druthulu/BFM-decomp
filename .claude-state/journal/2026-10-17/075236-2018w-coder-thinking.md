---
ts: 2026-10-17T13:52:36.679Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2ab9a444ea3aa2ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd53509-0294-4563-a878-c510da735377
---
Right, cse did replace the address, confirming my suspicion. Now I'm wondering when that pointer wouldn't be replaceable—maybe if pp is derived in a way cse can't recognize as equivalent, like coming from a different cast path to the same offset, or if the base object itself is a field loaded from another struct rather than the original pointer.

Another angle: cse's equivalences only persist within an extended basic block, so if pp is computed before a label or branch, the later block wouldn't know pp equals obj+20. I'm also considering whether find_best_addr only substitutes when the replacement is cheaper, which on MIPS depends on how ADDRESS_COST scores plain registers versus register-plus-constant addressing.

Maybe computing the pointer before the call would require a callee-saved register and an extra save, which seems like a bad fit. I'm also considering whether the invalidation happens because the address is held in a parameter register like a0, or whether the source actually reloads D_80126B78 some other way.

I'm checking whether the second read happens through a different declared type in this translation unit, like a struct pointer dereference versus a scalar load, but that would still trigger merging under CSE. Another possibility is an aliased extern symbol pointing to the same address, but that would require a linker script change I don't have access to.

So it seems the barrier is likely necessary, unless the two loads fall into different extended basic blocks, since CSE respects block boundaries at labels — and I'm now tracing whether the second load and store actually sit inside a branch delay slot after a conditional jump.

I'm considering whether the duplicate assignment appears in both branches of an if/else and gets merged through cross-jumping, which jump.c performs on identical tail code before a shared jump target rather than at block heads — so I need to check if CSE's follow-jumps behavior extends the block across the fallthrough path while the else branch starts fresh after a label, forcing a reload there.

Then I think about whether a `do {} while(0)` construct could split the block via its loop-start label, but since that label ends up unused when there's no actual looping, the jump pass deletes it before CSE runs, so it wouldn't create a new block boundary. I'm now weighing whether a `for(;;) { ...; break; }` loop would behave differently, since its start label might actually be referenced by a continue statement.

With -O2's cse-follow-jumps enabled, the fallthrough branch would reuse the cached value from before the jump, so no reload happens there — but that means the store could be hoisted into the branch's delay slot during instruction scheduling, which doesn't quite match the layout I'm seeing. Given limited time, I want to try typing the pointer as a u16 pointer and see if that changes the generated load/store pattern.

Still, that address computation involves a PLUS again, so it won't help. I'm wondering if I can make the store's address avoid being a PLUS expression by routing it through a load that invalidates the cse cache, or by checking whether the symbol address varies for cse's purposes — but that's a dead end since it's a plain symbol. The real question is whether there's a hard barrier preventing cse from merging these blocks, and I want to check the index for existing documentation on that barrier behavior.

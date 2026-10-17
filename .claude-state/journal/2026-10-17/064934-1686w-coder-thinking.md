---
ts: 2026-10-17T12:49:34.664Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm tracing why the compiler forces this constant memory address into a temporary register during expand, since GCC's MIPS legitimization logic pulls constant addresses into registers when CSE isn't expected to handle them later.

Then I follow how cse1 and cse2 rewrite that register into offset-based plus expressions, comparing this against the free/p0 case where the base is known and folds straight to a constant address.

Now I'm puzzled over why c0's second block keeps most stores absolute except the +4 one, since cse1's related-value logic should rebase registers sharing the same symbol — but in f2 the register being related isn't itself a known constant, which raises the question of how cse1 could still relate it to the symbol offset.

So I'm tracing whether cse2's REG_EQUAL notes in c0 are what later fold the rebased address back to an absolute one, unlike in f2 where that doesn't happen.

In f2's cse2, 76 ought to carry a constant-equivalent that makes (plus 76 16) fold to a direct constant address, but it apparently doesn't -- suggesting that quantity isn't tracked as constant at that point. I'm now wondering if that's because 75 has multiple sets, with a later `(set 75 75)` creating a gap where the constant knowledge gets lost before the use, possibly because cse2's extended basic block boundary starts somewhere that excludes that info.

The key difference seems to be in how cse1 initially expands the address: t1 directly produces (plus 75 k), which cse1 leaves alone and cse2 later folds; f2 instead goes through constants, so cse1 rebases it to (plus 76 k), and cse2 then rewrites it to (plus 75 k) by finding the cheapest equivalent address in that register class — reg+4 being cheaper than the constant form.

I'm not fully certain how the hash table ends up containing (plus 75 k) in the f2 case if it was just replaced, but the pattern points to the constant-spelled addresses combined with an anchor register holding the symbol value being the deciding factor, since case c0 had exactly that anchor present in both cse1 and cse2's knowledge yet still produced a different final result.

In c0, cse1 rebases constant addresses relative to the known anchor 76, and then cse2 folds those back because the quantity for 76 is itself a plain constant rather than a plus expression. In f2, the equivalent anchor 76 is defined as (plus 75 -12), so its quantity is const sym-12, and folding (plus 76 16) against that produces const sym+4 instead.

But the final result shows (plus 75 4), meaning there's a later cheapest-address-selection step swapping the constant for the plus-form because 75 belongs to the equivalence class for sym, and (plus 75 4) is cheaper. I'm reasoning that in c0 this substitution doesn't happen because 76 there was set from an actual constant, not a user variable like sym, so the equivalence class for sym+4 never includes (plus 76 16) -- whereas in f2, 75 holding sym directly puts it in that class, letting find_best_addr pick the plus form.

I want to test this with a hybrid case: take the c0 body with constant addresses and add a user variable base pointing to D_800A5E94 used once in a store, where both block 1's offset store and the call arguments stay as constants, to see if cse1 rebases the constant address onto that variable.

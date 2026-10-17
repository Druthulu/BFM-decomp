---
ts: 2026-10-17T13:53:36.465Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2ab9a444ea3aa2ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd53509-0294-4563-a878-c510da735377
---
The regex substitution attempt didn't trigger, consistent with C0473's observation that `sb` aliases scalar globals while struct stores via sh/sw don't. I'm wondering if I could avoid the CSE-folded address by routing the add through a type where the computed address isn't equivalent to a simpler PLUS expression, like obj+0x14 where obj itself derives from unk20.

I'm also considering whether `pp` staying live longer changes CSE's preference, or whether the store address could instead be a variable-offset PLUS that resists folding. None of these quite explain it -- invalidation logic around writes and clobbers looks unaffected, and there are no intervening calls, so I'm now questioning whether D_80126B78 is declared differently, like an array of pointers accessed via indexing rather than a direct symbol read.

The target has two separate lhu reads at offset 18 plus two lw reads of D, suggesting the source might split the subtraction and store into separate statements rather than reusing one cached read, which would explain why CSE doesn't merge them.

I keep hitting dead ends on the halfword-offset variants, so let me consider whether a small static inline accessor function could be the source of the barrier — inlining under -O2 in this compiler version only happens with the explicit `inline` keyword, so the question becomes whether that integration process itself introduces the gap I'm seeing.

I'm also toying with wrapping the second read inside a `do {} while(0)` block, or a `for(;;)` with a goto, to see if the loop-start label survives CSE even after the loop gets optimized away. I'll limit myself to trying just these two variants before moving on.

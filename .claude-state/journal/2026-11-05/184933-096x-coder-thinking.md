---
ts: 2026-11-06T01:49:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_I8RNFaBAcwzKCPMO0dkh
---
In the mini case, at .jump (first pass), the first return's jump (18) to label 29 survived, and the final return was elided. So the elision of the final return happened at expansion or the first pass. In .rtl? Let me check mini.c.rtl — I didn't dump it. Whatever.

Key: the last return is elided, others kept.

So to keep a jump at the end of zero's block until jump2, zero's block must NOT be the last statement/block of the function in source. But the target layout requires zero last...

Wait, maybe the layout does NOT follow source order! The block order in the RTL is the order of emission, which follows the statement order, BUT `goto` labels and if-else structures can produce different orders. In the target, zero is last because the source's `if (t == 0) {...}` block is... hmm, if the source is `if (t == 0) { zero } else { ... }`, the zero block would be emitted FIRST (right after the branch), not last.

The current reconstruction uses gotos precisely to force the layout: `goto zero` with the zero block written last.

So the original C must have had something that made the zero block last AND kept a jump. 

Hmm, what if the original had the zero block last and ended with `return;`, and the jump-to-next deletion did NOT fire because the return label is not the next insn: because the original function's return label is placed *before* the epilogue code, and there might be a `(use (reg 31))` or `(note)`... 

Wait, in the mini test the final return WAS elided, but let me check whether that was at expansion (no jump in .rtl) or at the first jump pass. If at expansion, then a return inside an if-block might survive! Let me test that.

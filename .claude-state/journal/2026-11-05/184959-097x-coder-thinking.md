---
ts: 2026-11-06T01:49:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sZyIx9HkNkFzUTUmxtnD
---
Same: the final return (in the else block) is elided. So the expander elides the last return regardless of nesting.

Hmm. So no C shape with the return as the final executed statement keeps a jump.

Therefore, the target's zero block must have had a jump at jump2 that was NOT a "return" — maybe an explicit `goto` to a label, where the label is not the function's end but something else. But the target has no jump in the final zero block.

OR the target's zero block at jump2 had a different last insn. Let me reconsider: maybe the original C's zero block's LAST statement was not the unk1C store but something whose insn is between the store and the label, and dbr_schedule/reorg moved it. E.g., a statement that emits an instruction which reorg moved elsewhere. What could be after the store in the zero block in source, emitting an insn, that ends up not being in the final bytes after the store? 

Looking at the target's zero block final: li; sh; sw. If the source had: ...; sh; sw; X where X emits an insn that got removed/moved. Reorg can move an insn into a delay slot of a *preceding* branch? The zero block is preceded by dec's `j 180c` — no. Hmm, reorg can also delete "dead" instructions.

What about a `(use ...)` insn from a variable? no.

Alternatively: maybe the zero block's store at jump2 was NOT the same instruction because the register allocation differed *at jump2* and then reload/sched2 changed it? No, jump2 is after reload.

Hmm, wait. Let me reconsider the possibility that the target was built with a *different* dec block: maybe dec's store at jump2 was `sw v1,28(s0)` or something, and sched2/reorg later... no, jump2 is after sched2, and the final bytes show v0.

Hold on — maybe the target's merge DID happen but the final bytes differ because the merged version is what we see in nopin and the TARGET actually has the unmerged version... which is what we see. Yes, target = unmerged.

Let me look at the problem from a different angle: use the barrier-free orig but with a small change to the DEC block, and see if the merge can be avoided while the final bytes stay. For instance, write dec as `((Unk*)a0)->unk1C -= 1;` (compound assignment) — the RTL might differ: the load and store with a REG_EQUIV note. Hmm, the store insn itself is the same (set mem (reg v0)). find_cross_jump compares PATTERN only (plus CALL usage). So same.

What about writing dec as `t = ((Unk*)a0)->unk1C; t--; ((Unk*)a0)->unk1C = t;`? Same insns.

What if dec's store is not `sw` but `sh`? Target is sw.

Hmm hmm.

New idea: what if the zero block's store isn't at the end because the zero block in the original was followed by another *unreachable* statement that the compiler kept as RTL but flow deleted? For example:
```
unk1C = 0x1D;
return;
... 
```
no.

What about the `zero:` block in the original being the last block but ending with a `break` out of a loop or switch? Hmm.

Let me look at the problem from the *structure* angle: in the target, the epilogue label 180c is targeted by many jumps. The zero block falls through. For the zero block to not cross-jump with dec, the jump2 pass must not see the store as the label's predecessor. What if there is a CODE_LABEL between the store and the epilogue label? find_cross_jump skips CODE_LABELs (while loop), so no.

What if there is a NOTE that is not skipped? Notes are always skipped.

What if there's a BARRIER between? Barrels come after jumps. A barrier would require a jump before it.

What if there's an INSN that emits nothing? That's exactly an asm_input. Any other zero-byte insn? A `(use ...)` insn emits nothing! USE insns are emitted by the compiler in specific cases: 
- expand_function_end emits `(use (reg))` for the return value register? Let me check.
- `emit_use` for... 

If we could get a USE insn after the store, the merge would be blocked (i1=store vs i2=USE → differ). And USE insns emit no code (and are deleted before final? They're in the insn stream, removed by final).

How to create a USE insn via C? Looking at expand_function_end in gcc 2.7.2: it emits `(use (reg ...))` for the return value if the function returns a value. Our function is void. Hmm.

Another way: `__builtin_...`? Not available.

Hmm, what about the `clobber` from a call? No.

Let me look at what USE insns exist in the orig function's RTL. grep the orig .jump2 for "(use".

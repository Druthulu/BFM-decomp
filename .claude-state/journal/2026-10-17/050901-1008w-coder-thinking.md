---
ts: 2026-10-17T11:09:01.424Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
I notice the field accesses use absolute addressing, and matching up offsets, pd[2] corresponds to D_80115120, which gets zeroed out in the else branch via that same absolute store pattern.

This suggests the original code may have accessed a struct through a pointer base for some fields while hitting others via the global directly, which could explain why gcc preserves a redundant base register. I'm also noticing the zero-extension via andi after lhu looks suspicious—normally that pattern gets folded away, so there must be something preventing that optimization here.

The deeper question is why cse keeps the pointer register live in the address computation at all when the symbol offset is constant and known. It seems like cse's fold_rtx behavior on bare register memory accesses differs from offset accesses, meaning the zero-offset case might not get replaced by the absolute symbol the same way the offset-4 case does.

I'm trying to reconstruct plausibly what the original C source looked like.

Alternatively, maybe the original used a static inline helper function that gcc 2.7.2 inlined with the global address as a constant parameter, which would explain why cse could still fold it into both offsets and the store — the inlined pseudo for the parameter would carry the constant propagation through just like a direct pointer cast would.

Actually, I'm second-guessing that theory—if the else arm were scanned once in its own block, cse would still likely fold the store since pd's value is still a known constant there, so that doesn't explain the discrepancy either. The real distinguishing factor must be that pd's value itself is unknowable to cse along one path, which would happen if pd were assigned conditionally, like pointing to different structs depending on a branch.

Another possibility is that pd is set right before a point where multiple control-flow paths merge, since cse normally loses its tracked constants at a label with multiple predecessors—but I don't see such a label appearing before the dereference in this target code. I'm now wondering if a loop construct is involved, since cse1 treats loop-end markers as boundaries for extended basic blocks, which could explain why the analysis differs between the two stores.

I recall `cse_around_loop` records equivalences from the loop end back to the start. So the question becomes whether a later reassignment of pd (e.g. reused for another purpose further down the function) breaks the constant-propagation assumption cse relies on, since that variant scored notably higher in testing.

But cse operates EBB-locally, so the loop head still sees pd as a known constant regardless of later reassignment. I'm now wondering if the fold is instead avoided through cost comparisons -- checking whether `find_best_addr` only substitutes the constant address when it's cheaper, which seems to hinge on how MIPS computes address costs for offset versus symbolic forms.

Looking at the actual output though, offset-0 got folded too (`lhu a0,0(a0)`), suggesting this isn't purely a cse/cost decision but something combine does afterward -- substituting pd's single-use definition into the load once cse has already eliminated its other uses.

So the real culprit is that cse folds the pd[2] read and write, leaving pd with just one remaining use, which lets combine substitute the symbol directly into the memory reference. I need to find a way to stop cse from folding `(plus pd 4)` into a constant address in the first place, since if that offset access survived, pd would still have three uses and combine couldn't simplify it away.

I'm trying variants: using an array symbol declaration instead of a plain pointer, computing the address via explicit byte-pointer arithmetic plus offset, considering volatile (ruled out), and considering a static local initializer (would just be a load, not what we want). None of these change how cse treats the symbolic constant equivalence — I need to figure out whether there's a way to make cse not record that pd equals the symbol address at all.

I need a label with multiple predecessors before the dereference for cse to skip the set, but there's no earlier branch, so maybe the function layout itself was rotated. I'm wondering what else could generate that lui/addiu base register pattern from an absolute address access—maybe it's not pointer-based code at all but something combine or another pass produced.

For MIPS absolute addresses, gcc 2.7.2 normally emits them directly as a load macro rather than creating a register with the symbol address, so the a1 pattern suggesting a separate `(set (reg) (symbol_ref))` insn feels unusual. I'm checking whether this could come from loop-invariant code motion pulling an address computation out of a loop, but with `!TARGET_ABICALLS` and `-G0`, symbol_ref addresses are typically legitimate on their own without needing a separate register.

Looking at another possibility: taking the address of a global struct field and storing it in a pointer variable could trigger `expand_expr` to materialize the symbol_ref into a register, which seems closer to what's happening with pd. I'm also considering whether a COMPONENT_REF offset on a global, or `-fforce-addr`, could be responsible, but neither seems to match without more evidence.

Thinking further about it: the key insight might be that the store in the taken block survives into cse2 because it's only scanned once, while the real issue is the read in BB1 being visited along two separate paths during cse2 — and critically, cse1 already associates the pointer arithmetic (folding `(plus pd K)` plus a constant into `(plus pd K+c)`) without immediately simplifying it, deferring that fold to a later pass.

Now I'm wondering whether restructuring the branch so the read of pd[2] lands inside a taken-branch target would force it to be scanned only once too — tracing through how the delay-slot filling reorganizes BB0's load-and-branch, BB1's read-and-branch, and BB2's decrement into that layout.

But if BB1's branch target weren't followable (say L_store had two predecessors or lacked a barrier), cse2 would instead walk paths [T] and [N], with [N] traversing BB0, BB1, BB2 in sequence — changing how many times BB1 itself gets scanned.

So if bne isn't followable, BB1 appears on only one path and gets scanned once in cse2, letting the base+offset association survive and keeping the read pointer-relative. But I still need cse1 to actually produce an associated (non-folded) form in the first place, using the derived-pointer trick — and since -fcse-follow-jumps affects both cse1 and cse2 equally, I need to check whether cse1's path-following behaves the same way here.

Looking at c28's trace, BB1 seems unassociated even in cse1, since .cse keeps both accesses as (plus (reg 74) 2), which makes sense since pe's constant isn't known yet at that pass. So the path processing redoes insns from insn 2 each time, and I need to trace what happens in that first scan.

Actually, propagate_change modifies insns in place, so even in cse1 with pe=(plus pd 2), reading pe[1] gives (plus pe 2): on path 1 this associates to (plus pd 4), and on path 2 pd's constant gets folded directly. So if BB1 only had one path, path 1's association alone would be enough — then in cse2, pd's set is still in BB0, and (plus pd 4) would fold the moment pd's class shows no PLUS, meaning a single scan suffices to fold it regardless of path structure.

So the store surviving cse2 depended on pe staying unresolved through cse1 (due to the do-while split) and then being scanned exactly once in cse2, which associates but doesn't yet fold. Survival requires the access to stay in derived-pointer form through cse1 and be touched only once afterward — meaning I need a boundary that stops cse1 processing (like a banned do-while(0) or loop-end note) combined with a single scan in cse2. I wonder if routing the address through a loop structure, since NOTE_INSN_LOOP_END marks the end of a cse1 extended basic block, could create exactly that kind of boundary.

Now I'm considering whether the loop over i, which comes right after the head, could be reordered or whether there's an earlier statement that forms a genuine loop before the head — but the target code starts directly with the head, so that seems unavailable. I'm also wondering if cse1 might treat pd as non-constant only after jump optimization or combine resolves it, perhaps through an address computed via some intermediate control flow, or through a type cast on the address arithmetic that changes how cse analyzes it.

Shifting to another possibility: maybe the original source accessed a single global struct via field references rather than separate symbols, and at -O2 with gcc 2.7.2 the BLKmode struct's address gets expanded as a symbol plus constant offset for each field, which would stay absolute throughout -- unless the field access goes through memory_address in a way that changes its behavior.

I'm now recalling that in explow.c, memory_address has a check: if cse_not_expected is true and the address is a constant, it forces the constant into a register via force_reg. That's the exact mechanism that would convert an absolute symbol address into a register-based address once the compiler decides cse_not_expected applies.

I'm trying to recall the exact MIPS address cost function from gcc 2.7.2's mips.c—specifically how it ranks SYMBOL_REF, CONST, LO_SUM, and LABEL_REF costs, since that determines whether cse folds the constant address back out of the register.

So absolute-address folding happens specifically through fold_rtx's constant-arg handling of PLUS into CONST, not through plain REG mem addresses, which cse always keeps base-relative. That means the pd[2] accesses are the only candidates for folding into absolute addresses, since offset-0 reads through pd stay register-relative—unless those accesses are instead written as offset-0 forms themselves.

I'm realizing a plain REG address stays untouched by fold_rtx, while a PLUS with a constant offset gets folded into a const. So maybe the offset-4 pointer should be defined with a negative-offset trick: let the pointer itself point at the higher address, and access the lower one via `pp[-2]`, so the base-case access becomes the bare REG (kept) while the other folds away.

But that still doesn't match the target's `lhu 4(a1)` form where a1 holds the base symbol — the escaping PLUS case doesn't line up. I need to dig into fold_rtx's PLUS handling: it checks equiv_constant on the REG operand before folding, and that lookup might be where I can prevent the (plus pd 4) from collapsing into a const.

I'm also considering whether pd could be set through a subreg, a libcall equivalence, or a variable offset, and whether incrementing pd afterward (pd++ or pd+=) breaks CSE's constant tracking in a way that produces the mismatched addressing pattern I'm after.

So the real question is whether cse's associative folding in fold_rtx would combine the plus-with-constant pointer arithmetic even when the base register isn't a known constant at that point — checking how GCC 2.7.2 handles that case in its source.

For the binary case, it tries simplify_binary_operation using whichever constant args are available, so association happens before constant folding gets applied. I'm reconsidering whether pd's equivalence class could carry a constant from a different mode or an indirect register, but cse should still resolve that within the EBB via qty_const lookup — so that's not the gap I'm looking for.

The real escape must be something cse genuinely can't evaluate: an asm, a memory load, a call return value, or an EBB boundary like a label or loop end that separates the set from the use. I'm checking whether there's a code label between BB0's start and BB1's read, since BB1 is just the fallthrough of the beqz — and cse's EBB traversal does continue across conditional branches into their fallthrough blocks, so that boundary shouldn't be the issue either.

I'm now considering that the label could exist at cse time but get removed later, once jump2 eliminates dead labels after cse2 runs — which would explain why pd[2] still appears to persist across what looks like a pure fallthrough in the final RTL.

I'm also second-guessing the whole loop/switch-based reconstruction and wondering if pd isn't a fixed global address at all, but actually a function parameter, which would change the entire shape of the source I'm trying to recover.

Then I pivot to thinking about inlining: maybe this was originally a small static function taking a pointer parameter, and gcc 2.7.2's inliner substituted a constant argument for it, which would explain why the compiled code computes the address directly rather than loading it through a register parameter. I'm recalling how integrate.c's expand_inline_function handles non-MEM locations when substituting constant parameters.

I'm tracing through copy_rtx_and_substitute: when a parameter's value is constant, uses get substituted directly, including inside memory addresses like a symbol_ref plus offset, where the result might not get re-simplified and could get cleaned up later by CSE.

Given how much effort prior attempts spent with low success, I'm weighing whether to try defining a static inline function or restructuring the loop differently, but I'm skeptical any of these quick experiments will actually dodge the constant propagation CSE performs.

Register pressure and reload tricks like absolute addressing also seem unlikely to help. I'm wondering if the original code instead computed the pointer from a switch or ternary expression that avoided this constant-folding issue entirely.

Then I try another angle: maybe pd is reassigned so that cse tracks it as sym+2 after an increment, letting subsequent offset additions fold into constants too — but that still doesn't explain the extra instruction. I also consider whether pd's equivalence class containing a PLUS expression triggers some associativity rewrite in cse that produces the pattern we're seeing.

I rule out EBB breaks from CALL instructions or NOTE_INSN_LOOP_END markers, since cse doesn't treat those as extended basic block boundaries, and pseudos aren't invalidated by call clobbers anyway.

Then I check whether the loop structure itself could interact with the head block — but the head precedes any back-branch, so they're unrelated. I consider that -fcse-skip-blocks and cse_follow_jumps are both likely enabled at -O2 in this GCC version, and that the pad write happening only in the then-branch doesn't matter since the pad read occurs earlier, before the conditional.

I also reconsider the declared type of D_8011511C — maybe it's an incomplete extern array rather than a scalar, which would mean array indexing expands as a BLKmode symbol with constant offset, forced into a register and then possibly folded back to an absolute address by CSE.

Rather than keep theorizing, I decide to actually check the real compiler dump output — using the dump tool on the base case to see what CSE produces for the head of the function. I want to run a quick experiment: treat D_8011511C as an array type and see what changes.

I also consider a struct-cast approach, pointing a PadRep pointer at the address and accessing its prev field, but scores across different test bodies are inconsistent and not clearly informative since "cur" varies. I decide the more productive path is to go straight to the GCC source for cse.c's find_best_addr function to understand the real address cost logic.

Prior agents found that cse knows pd equals a fixed address throughout the block, letting fold_rtx fold the offset into an absolute address and collapse into lui/lhu once pd has one use left. I'll verify this by checking find_best_addr myself before testing spellings.

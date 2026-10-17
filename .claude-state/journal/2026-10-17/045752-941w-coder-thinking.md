---
ts: 2026-10-17T10:57:52.919Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
I'm checking whether constant integer and symbol reference addresses could alias—since both are treated as distinct constants, the comparison finds no conflict, so this path is a dead end. I'm now considering whether canonicalizing a PLUS expression might reveal something different.

What if the base register is reassigned—reused for two different purposes, first pointing to one table then another? In that case the number of sets would be greater than one, making the scheduler treat it as opaque, but CSE might still fold each use within its own block since it tracks the known constant value locally.

But I keep running into the same circular problem: CSE folds pointer-plus-constant into a legitimate symbolic address on MIPS, since `sym+k` is valid there. Unless the fold fails for some structural reason—maybe if accesses go through a struct field rather than a raw pointer offset, something changes in how the address gets validated.

Maybe the real original source actually used loops with barrier instructions, and I need to reconsider where those barriers actually land relative to the schedule—a barrier insn is the first real instruction after loop notes, with dependencies cutting across it in both directions.

I'm considering whether the barrier actually attaches to the call insn itself, since CALL_INSN with loop notes gets handled specially in sched_analyze_insn. But if LOOP_END is emitted right before the call statement's argument setup rather than right at the call insn, that complicates where the barrier would actually land relative to a0/a1 being set.

Testing another scenario: if the call sits inside the loop body itself, the LOOP_CONT/LOOP_END notes would come after the call insn and attach to the next block's first insn instead — which doesn't match what's needed. I'm wondering if that first insn could be something inert, like a redundant self-set insn that produces no actual code, similar to what shows up in one of the failing cases.

I need something that survives flow and cse1 but produces no actual code and gets erased later — maybe a trivial self-assignment that jump1/flow would normally delete as a no-op move, but I need to check whether cse1 would also strip a (set 75 75) pattern before it reaches sched1.

I'm trying to trace why cse2 knows the base value at that re-set point when cse1 apparently didn't — maybe it's tied to how loop notes get split around LOOP_END versus LOOP_BEG, with the after_loop parameter affecting whether cse treats that boundary as a split point. The mechanics are murky, so I should just test this empirically rather than keep reasoning about it abstractly.

Tracing through further, I realize the barrier set itself becomes a real set in a new EBB since cse1 won't know base there, but then block 3 would see that set and fold anyway — so I need the barrier to be something that vanishes entirely, like a redundant self-move that gets deleted by the no-op move cleanup before cse runs.

So instead I'm considering a different setup: have an intermediate pointer variable assigned at the top that cse1 in the later block treats as an unknown constant, so base's value stays opaque and the pointer arithmetic can't be folded by cse1 while still allowing cse2 to recognize the redundancy.

But then I worry about how cse2 would actually rewrite that assignment — whether it collapses to a trivial self-copy or keeps it as a copy that creates extra register pressure from two live pseudos across a call, which could add an instruction rather than remove one. And since cse2 would know base equals that symbol, any later uses of base in the block would fold to constants too, unlike my earlier example where the addresses stayed as unresolved plus-expressions.

I'm not sure yet — I need to compare f2's cse vs cse2 dumps for insn 110 and check how block 3 addresses written as sym+k constants were handled in cse1.

No conflict shows up for CONST_INT vs SYMBOL_REF, so casting the address won't help. I'll now check how cse1 and cse2 handle f2's re-set and block 3 to see what each pass actually knows.

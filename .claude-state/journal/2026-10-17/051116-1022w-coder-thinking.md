---
ts: 2026-10-17T11:11:16.968Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
Working through the cost comparison, I'm finding that the constant costs 8 while the plus expression costs around 4, so for a set like rX = pd + 4, CSE would prefer keeping the plus form since it's cheaper than substituting the constant.

But then I realize there's a crucial exception: find_best_addr unconditionally folds non-register addresses via fold_rtx when the address appears inside a MEM, bypassing any cost check entirely — that's the real culprit. So the address needs to either be a bare REG, or a PLUS whose fold doesn't collapse to a constant, and for a REG address the decision comes down to comparing ADDRESS_COST and rtx_cost between the register and the equivalent plus expression in its class.

I'm now tracing whether cse actually inserts the constant form into the register's equivalence class alongside the plus expression — checking whether REG_EQUAL notes or src_const insertion would pull in the symbolic constant as a competing candidate.

Then I'm sketching out the pointer arithmetic scenario: a pseudo pointing to a global struct, a derived u16 pointer offset by 4, and how the memory reference through that offset pointer resolves to `(plus pd 4)` as the chosen address via the rtx_cost tie-break, then how a later cse pass would re-examine that memory access.

If the second pass hits the same issue, it depends on whether find_best_addr actually replaces the register address with the plus expression — that hinges on mips_address_cost comparing REG vs PLUS. If REG is cheaper, `*pe` stays as a plain register reference and never gets folded, meaning pe remains a separate register tied to pd+4 that combine likely won't substitute across multiple uses since it's set once but read and stored multiple times.

So the real question becomes whether the final pass's in-place replacement of the register with the plus expression survives without being re-folded on a subsequent scan — this depends on how cse2 processes successive paths and whether a later path reprocesses the same block and folds the expression back down.

So any plus-pd-K address gets folded on the second scan, meaning BB1's read must resolve to a form CSE won't rewrite — like a separate register holding sym+4, which costs an extra instruction, or offset-0 from the same base register distinctly from a1. That points toward a target like lhu v0,4(a1) where a1 still serves the offset-0 access too, which raises the question of how the original compiler actually generated that pattern.

I'm reconsidering the control flow: maybe BB1 only gets scanned once if its branch target is used elsewhere, making one path skip it entirely. If path [T] jumps straight to the else-branch and BB1 only appears in path [N], then in a single CSE scan, something like pe = pd + 2 followed by a dereference of pe would get rewritten as plus pd 4 rather than being folded against a second pass.

I'm trying to pin down exactly why the first CSE pass leaves the address as mem pe while the second pass folds it into a constant. The key must be that pe's defining set lies outside pd's known class in pass one — maybe separated by a LOOP_END-style boundary — so pass two is the first time pe and pd+4 are associated, and that single substitution happens only once before the def becomes dead and gets cleaned up afterward.

Actually, c28 already flagged do-while(0) splits as banned since even two of them still get folded by the optimizer — the BB1 read can't survive. There's no backward branch to 0 in the target, so a real loop around the head seems ruled out too. I'm now reconsidering whether cse2 even runs here, given -frerun-cse-after-loop is active at -O2.

So between cse1 and cse2, pd's const value should still be known from BB0 unless its defining insn got deleted or merged somehow — but there's no loop to cause that. Maybe pd isn't even a plain register in cse's view; perhaps the base register gets created later by reload, by the loop pass's strength reduction, by scheduling, or by combine building a plus-constant expression after the fact.

I'm also considering whether local-alloc's update_equiv_regs could give a pseudo a REG_EQUIV note holding (plus pd 4), and whether reload substituting that equivalence into an unallocated pseudo's uses could explain the pattern — though that mechanism seems more suited to producing a direct constant than an `4(a1)` address. The more likely culprit is combine itself, which can fold a separate plus-4 computation directly into a memory reference, turning a register holding an address offset into the `4(a1)` addressing form.

For the store side, I'd need a second pe-like register used only once, or combine won't fold since pe has multiple uses and doesn't die at the first one. This really hinges on how mips_address_cost rates (plus reg 4) versus a bare reg, so I should check mips.c for that cost function.

---
ts: 2026-11-06T10:11:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9kXmDVmAUnQVfa1PhWWC
---
Still 6. The allocation isn't shifted. So rv→$2 requires the pin/return. Let me try a different approach: make rv a *parameter copy* or use it as the last assignment to a0/a1? Hmm.

What if we make rv the value assigned to a variable that global-alloc prefers $2? The target's $2 is the return register; in a void function, global-alloc can use $2 but apparently prefers $3 for rv. 

Let me look at the .greg dump to understand the priority ordering. Actually, let me check what reg 78 (rv) got and why. In b3's lreg dump, reg 78 is "used 6 times across 9 insns; dies in 2 places". Let me look at the .greg dump for the register allocation order. GCC 2.7.2's -dg might not print allocations. Let me grep the .s for how global-alloc ordered... not available.

Alternative: maybe local-alloc's block-local pseudos (comparisons) grabbed $2 and global-alloc then avoided it for rv due to *conflicts with local-alloc'd regs in the same block*. In the `li $3,-1` block (L98), the comparison `slt $2,$4,$3` is in the *predecessor* block; hmm.

Let me try restructuring so that the comparisons in the block containing rv's def are absent. In the target, `li v0,-1` is in a block reached from `bnez v0,L95` — the block L98 (j L94; li v0,-1) has no comparison. In b3, `j $L94; li $3,-1` — same. So the block is clean. Why $3?

Maybe global-alloc assigns caller-saved regs in order $2,$3,... to pseudos by priority; rv might be lower priority than another global pseudo. In b3, which other global pseudos exist? reg 72 (a0 copy), 74, 75 (a1 copy), 77 (x), 78 (rv). x (reg 77) is live across blocks and has 7 refs. Maybe x got $3? In the .s, `lw $3,D_801E1BCC` → x=$3. And rv also $3 (after x dies). So x took $3, rv took... also $3 (reuse after x dies). $2 is used by the comparisons (local-alloc). Global-alloc couldn't give rv $2 because $2 was assigned to block-local pseudos that are live across... hmm, no.

Wait: global-alloc runs AFTER local-alloc. Local-alloc assigns regs to pseudos confined to one block. The comparison pseudos are block-local, so local-alloc gave them $2. Then global-alloc assigns cross-block pseudos (x, rv, a0, a1). It must avoid $2 if $2 is live across a block boundary at any point where the global is live. The comparison pseudo `slt $2,$5,$4` is live only within its block (dies at the beqz). But global-alloc's conflict graph is built from `regs_live_at` per block? It uses the live ranges; a block-local reg assigned by local-alloc is "used" in that block, and global-alloc considers it conflicting with globals live across that block. If rv is live across the block containing a comparison that uses $2, conflict. Is rv live across such a block? rv is live from `li $3,-1` (in block L98) to the end. The comparison blocks (L4: slti $2,$4,16) — is rv live there? rv is live at the *end* of the function (L94), and L4 flows to L94 after defining rv. At L4's start, rv is not yet defined (killed by the later def), so not live. Hmm, but global-alloc's live analysis for a multi-def pseudo: at L4's start, is rv live? From L4, the path goes slti, bnez -> either L94 (rv defined by sll before) or continue to subu... Eventually rv is defined before L94. So at L4's start, rv is not live (a def kills it on all paths before use). So no conflict with $2 in L4.

But maybe global-alloc is conservative: it computes live ranges from `reg_live_length` and `basic_block_live_at_start` including the pseudo as live across the whole range from its first def to its last use (a single interval). Since rv's defs are in multiple blocks, global-alloc may treat it as live from the earliest def to the end, spanning blocks with $2 comparisons → conflict → $3.

The target's rv is a return value coalesced to $2 (a hard reg), so no allocator choice. Confirmed: only a return can force it.

So PARTIAL:keepalive is impossible. WALL.

OK, I'm confident now. Let me finalize.

Actually, one more possibility for the clones: what if we make the function's *first* definition return type s32 but keep the callers happy by... no.

Let me also reconsider: the function `func_80182420` is defined `void` but the callers declare `extern void func_80182420(s32,s32)` and call via cast. If we change the definition to `s32`, the callers' `extern void` conflict → error. Confirmed.

Alright, walls for all 4.

Now let me write the artifacts.

Best lever-free:
- func_80182420: 13 (v05)
- func_8018A168: 13 (v05)
- func_80189E68: 13 (v05)
- func_8017D730: 19 (v02)

Wait, item4 v02 is "remove the second branch's t/v0/v1 computation". Let me double check v02 content: it has SEC_NOV1 which removes the computation but keeps the call. Good. Score 19.

Hmm, but v02's best 19 vs v01 22. The 19 is because the source omits the dead computation (so no extra RTL weirdness) and the first branch allocates correctly. Good.

Now, is there a lever-free variant with the second branch computation *included* but a lower score? v01=22. No.

Let me write win.c files.

Then notes.md per item with the variant summary and wall mechanism.

Then results.tsv rows. Format: `dir file func kinds result best tries wall evidence` (tabs). Header exists. dir = item dir name? Let me look at the header: `# dir	file	func	kinds	result	best	tries	wall	evidence`. The `dir` is the item directory name, `file` the TU, `func`, `kinds`, `result`, `best`, `tries`, `wall`, `evidence`.

For MATCH rows wall `-`. For WALL: wall = tag, evidence = gcc pass + mechanism ≤140 chars.

Rows:
```
func_80182420__ov_SC03_124_jr_80181B44	src/ov_SC03_124/ov_SC03_124_jr_80181B44.c	func_80182420	keepalive,pin	WALL	13	59	expand-void-return	expand/flow drop the void return value: keepalive keeps rv live but global-alloc gives it $3, target $2 (return reg); pin $2 needs the return. 32 lever-free + 27 keepalive-kept tries
```
Hmm, tries count: 32 lever-free + 27 keepalive-kept = 59. For the other clones, 32 lever-free only (I didn't run keepalive probes on them). But the keepalive probe on SC03 is representative. For each item, "tries" should be the number of scored tries on that item. SC04: 32. SC05: 32. SC06 item4: 32 + 4 (k1-k4) = 36. Let me record accurately:
- func_80182420: 32 (var) + 27 (kv) + 4 (k2,k3,k4 + k1? k1 was item4; for clone I did k2,k3,k4 = 3) + b1,b2,b3,b4 = 4 → 32+27+3+4 = 66. Hmm, let me count: b1, b2, b3, b4_s32 (4) + 32 var + 27 kv + k2,k3,k4 (3) = 66. That's a lot. Let me just say 66.
- func_8018A168: 32 var + b/orig? orig scored too. 32 lever-free. Let me say 32.
- func_80189E68: 32.
- func_8017D730: b1 + 32 var + k1 + k2,k3,k4? No, k2/k3/k4 were clones. For item4: b1 (1) + 32 var + k1 (1) = 34. Plus orig. Let me say 34.

Wait, k2/k3/k4 were for func_80182420 (clone), yes.

Let me be precise in the log, and in results just put the number of lever-free+partial tries.

Evidence strings ≤140 chars. Let me craft:
- clones: "flow/expand drop void return value; keepalive keeps rv live but global-alloc gives $3 not $2 (return reg); pin $2 requires a return (void)" — ~135 chars.
- item4: "flow deletes dead 2nd-branch t/v0/v1 (target keeps 17 ins); keepalive-only keeps them but v1->a1 ($3 target) without $2 pin" — ~125.

Wall tags:
- clones: expand-void-return (in walls.txt).
- item4: flow-unused-result (in walls.txt).

Now moves.md lines: `kind | func | MATCH: move / WALL tag — mechanism (G27)`. Format from the file: e.g., `keepalive,pin | func_800D2A24 | WALL expand-void-return — ... (W03)`. So:
`keepalive,pin | func_80182420 | WALL expand-void-return — rv kept by keepalive but $3 not $2; pin $2 needs return (G27)`
etc.

Let me now write the files. First copy win.c.

Let me do the copies.

---
ts: 2026-11-06T13:10:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hTLAwnQCpEv01OIPspjA
---
d_ has "line" and "end" (1-based line numbers). Let me write the extractor using share_census scan_text via delever_search import. Let me write script.

Actually, I could use `delever_search --explain`? No. Let's write extract.py under my shard.

Plan:
1. For each item, extract def -> orig.c.
2. Run dt.sh with orig.c to confirm score 0 (baseline sanity; the current tree def should score 0).
3. Then create win.c by removing barrier(s) and applying real-C moves to recover.

Note: the barrier removal may just score small (e.g., 7 ins drift). The task: find a real-C equivalent that restores 0. For item1 the barrier prevents cross-jump merging of case1 tail and case3 body. Real-C move: make the two tails not byte-identical in some legitimate way. Since they're duplicated code in source, any real difference in one copy (e.g., different temp widths/statement shape) could prevent the merge while emitting same instructions? Hmm, find_cross_jump requires RTL streams equal. If we change the C in a way that produces the same instructions but different RTL... e.g., different temp variable names don't matter after rtl. What differs in RTL? Perhaps the order of operations, or use of a different but equivalent expression that gcc canonicalizes to same insns but different RTL... Cross-jump compares insns (RTL patterns) after... Actually find_cross_jump compares the two insn streams with rtx_equal_p and requires insns_equal. If instructions are identical, it merges. To stop merging with real C while keeping identical machine code — that's the classic wall. But the moves table shows similar cases cracked:

- func_80180100: "field-direct &= and -- on s0->unkAC (no temps), dead pad[2] dropped" MATCH.
- func_801835B0: goto loop.
- func_80182560: "s16 temp x for the first 0x2E load + dead reset x=0 (C0414) after t=diff<<9; cse1 drops the value so the 2nd lh is not forwarded, delete_dead_from_cse removes x=0"
- func_8017F5A4: do-while around each byte store keeps the next lbu below the sb.
- func_801876C4: do-while.
- func_801854B8: do-while.
- func_8017F9F4: WALL loop-const-hoist — asm pair stops const hoist.
- func_8017E804: WALL.

For cross-jump barrier (item1), moves table has WALL jump2-crossjump-arms entries, and func_80183C9C's own comment says "The original binary keeps BOTH copies. There is no -fno-crossjumping before gcc 3.3, so the only lever is §5a's zero-byte barrier". But wait — this item is in the residue precisely because the barrier is needed. The task is to find a real-C move that makes the two RTL streams unequal while keeping identical output instructions. 

Idea: find_cross_jump compares insns; if one copy uses a different (but equivalent) instruction sequence that ends up scheduled/combined to identical machine code... Actually if machine code is identical, insns are identical → merge. Unless the difference is in a "note" or in a register that's different but later assigned same. Hmm: cross-jump works before register allocation (jump2 runs before? jump2 is jump_optimize, in the rtl pass before flow? Let's recall gcc 2.7.2 pass order: jump_optimize is run early (after expand? no). Actually jump.c jump_optimize runs multiple times: after combine and before flow (jump2), and after reload (jump). The cross-jump pass is in jump_optimize. At jump2 time, pseudos are still virtual registers. So two copies using different pseudo registers (e.g., temp var names that don't get coalesced) would have different RTL → no merge, but after local-alloc they could map to the same hard register → identical machine code!

That's the key: use a distinct temp variable in one copy so the RTL reg numbers differ, while the allocator still assigns the same hard reg. E.g., case1's tail uses `x = ++p->unk1C` with iVar1... Actually case 3's body: `unk1C += 1; if (unk1C < 0x10) goto TAIL; goto HITSTUN;`. Case 1's tail: `unk1C += 1; if (unk1C < 0x10) goto TAIL; goto HITSTUN;` identical.

To make RTL differ: compute `unk1C += 1` via a temp in one copy: `iVar2 = p->unk1C + 1; p->unk1C = iVar2; if (iVar2 < 0x10)...` Hmm, that changes code shape possibly but may still generate the same 9 instructions (lw, addiu, sw, slti, bnez...). And the RTL differs (extra pseudo) unless combine/cse folds it. Actually cse would merge the add? cse replaces equivalent expressions; within an EBB. Since the two copies are in different blocks and cse runs before jump2... hmm cse might make them equal again. This is exactly the "launder" problem.

Alternatively, use a `do{}while(0)` block around the tail in ONE copy — does a block split change RTL? No, blocks don't change RTL at jump2; jump2 might see a NOTE_INSN_LOOP_BEG though! do{}while(0) creates a loop note; jump2 cross-jump compares insns including notes? insns_equal ignores notes? Actually the barrier works because asm insn is in the stream. A do-while adds NOTE_INSN_LOOP_BEG/END notes; find_cross_jump walks over notes? Let me check gcc 2.7.2 jump.c.

Let me look at jump.c's find_cross_jump.

Given the large amount of work, maybe a smarter approach: use the existing tool `delever_search --run`? No, that's a campaign; our brief says use dt.sh per candidate, budget 20-30 min per item.

Let me check jump.c.

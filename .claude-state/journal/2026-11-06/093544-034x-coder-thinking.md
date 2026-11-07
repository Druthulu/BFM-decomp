---
ts: 2026-11-06T16:35:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qQYQIg1Hho7REg8AkgMD
---
All merge (score 20). So call spelling doesn't change RTL equality.

Let me think about the keepalive once more, because if I can crack it, the best might drop. But the merge dominates.

Actually, wait. Let me reconsider: is the barrier's purpose really to block cross-jump, or does it do something else? Removing it gave 19/307. Let me look at what mine's structure is without the barrier: it merges the two 4-call blocks. 10 insns fewer + li = 11 fewer (307 vs 318). Yes.

Since the target keeps both blocks, and plain C merges them, the wall is jump2-crossjump. The only C lever to prevent it changes bytes. So WALL.

Now, per the brief, WALL needs ≥20 min. I'm at 8 min. I should keep trying for 12 more minutes. Let me use the time on a different angle: maybe the target's two blocks differ subtly in a way I can reproduce: let me diff target block A and block B byte-by-byte.

A: 158 jal, 15c move a0,zero, 160 jal, 164 nop, 168 jal, 16c nop, 170 jal, 174 move a0,zero, 178 j, 17c nop
B: 198 jal, 19c move a0,zero, 1a0 jal, 1a4 nop, 1a8 jal, 1ac nop, 1b0 jal, 1b4 move a0,zero, 1b8 j, 1bc nop

They look identical. Let me verify the jal targets/relocations are the same functions. From target.s: A: 158 R_MIPS_26 func_800D2D44; 160 func_800468FC; 168 func_8002D8D4; 170 func_800D2AA0. B: 198 func_800D2D44; 1a0 func_800468FC; 1a8 func_8002D8D4; 1b0 func_800D2AA0. Yes identical.

So the original source must have had something blocking cross-jump. Since the original compiled with the same gcc, and the only difference between our body and the original is the source spelling, the original had some construct. What construct blocks cross-jump with zero bytes? An empty asm is exactly such a construct, and the real game code likely had a macro like `asm("")` or `volatile`? Or the original had `#pragma`? Hmm.

Wait, maybe the original had a *label* in the middle that was referenced by a goto from a place that later became unreachable/optimized. Or the original code structure differed such that one block was reachable by fallthrough and the other by jump, making the *preceding* insns different (find_cross_jump gives up at a label in stream 1). 

Look at find_cross_jump for unconditional jumps: `find_cross_jump(insn, JUMP_LABEL(insn), 1, ...)`. It compares stream 1 (before jump A) and stream 2 (before the ret label). Stream 2 = insns before `ret:` label = func_80059658(1) block etc. Those differ from block A's calls, so this call finds nothing. Then it tries other jumps to the same label (jump_chain): finds jump B and calls find_cross_jump(jumpA, jumpB, 2). This compares before-A and before-B. Both blocks identical → merge.

To prevent: make the *insns before* differ within the first 2 compared. That means the last 1-2 insns before the `j ret` must differ between the blocks while emitting the same bytes. The insns before j: A: jal func_800D2AA0 + move a0,zero (delay). B: same. If in block A we wrote the last call differently such that the RTL differs but bytes same... e.g., call func_800D2AA0 with an argument that is a register known zero vs const 0. If the source is `func_800D2AA0(i)` where i is a variable that's 0 and cse can't prove it → RTL `move a0,i` vs `move a0,zero` — bytes might still be `move a0,zero` if i is allocated to zero? No, i would be a register load.

What if we use a *parameter* that is zero? arg0 is a pointer, nonzero.

Hmm. What about the func_800D2AA0 call itself: the CALL_INSN_FUNCTION_USAGE for `func_800D2AA0(0)` includes `(use (reg:SI 4))`? If in block A we pass the argument via a *different* hard register... the ABI fixes a0.

OK, truly no byte-neutral difference.

Alternative: prevent the merge by making stream 1 hit a CODE_LABEL before minimum 2 insns. The label must be within the last 2 insns of block A. A label referenced by a jump from... the ret label? What if block A's `goto ret` is actually `goto L; ... L: goto ret;`? Emits j.

Hmm, what if block A ends with a call and then `goto ret`, and we place a label *after* the last call (before the goto) that is referenced by a `goto` from elsewhere that compiles to nothing? A goto to the next insn is deleted by jump1. 

What if the label is referenced by a *switch case* that jump1 turns into a fallthrough? Case labels in a switch emit a comparison/jump table.

What if the label is referenced by a computed goto (&&L)? Emits address materialization (lui/addiu).

Dead end.

Another angle: could we prevent the merge by *disabling cross-jump for the whole function*? No C control.

So WALL. I'm confident. Let me wait out the 20 min productively by trying the keepalive angle (maybe it changes best from 5 to 4).

Keepalive ideas not yet tried:
- e1: `v0r = 1;` where v0r is declared `s32 v0r;` but used in a *loop* after? no.
- e2: make the function's last statement `func_80010A98();` and the `v0r=1` before it: `v0r = 1; func_80010A98();` — target has li v0,1 AFTER the jal. Wrong order but maybe gcc reorders? try.
- e3: `v0r = 1;` at the top (init) and never read: dead.
- e4: pass v0r as an argument to a *new* call? changes bytes.
- e5: `i = 1;` where i is used in the loop earlier (i = (D_800EC9CC == 0) inside the loop). At the end, assigning i=1 is dead → flow deletes. But maybe flow keeps it because i is used in a loop? Liveness is computed; dead at end → deleted. c06 tried `i = 1;` → 20.
- e6: `sp18[0] = 1;`? store.
- e7: `D_800EC9F0 = v0r = 1;`? stores 1 to global (changes bytes: extra store).
- e8: Make v0r `static`? Then a store to memory. no.

The only real fix is a return type change. WALL expand-void-return.

Now, best = 5 (c38). The evidence: jump2 cross-jump merges the two identical arms; reorder costs 4 insns; keepalive li v0,1 needs the return type.

Which tag? I'll use `jump2-crossjump-arms` (existing tag). The wall column allows one tag. Evidence ≤140 chars: "jump2 cross-jump merges the two identical 4-call arms (10 ins); blocking it needs a byte-changing reorder (best 5); keepalive li v0,1 = expand void return".

That's ~150 chars. Trim.

Actually, hmm: the "best" should be the lowest score of a lever-free body. c38 = 5. Good.

But wait: is c38 really lever-free? It has no pin/barrier/keepalive and no register/asm. Yes. But it's derived from w1 which deleted the barrier and keepalive. Confirm grep found no asm/register in c38/c39 (the grep output was empty). Good.

Time: need 20 min → 09:47. It's 09:35. Let me do a few more experiments to be thorough and fill the time: test whether the merge can be prevented by making one block's *goto* target a different label that resolves to the same address (e.g., add a second label `ret2:` right before `ret:` and `goto ret2` from block B). That's byte-neutral! `goto ret2; ... ret2: ret: func_80010A98();` — two labels at the same address. Then the two jumps have DIFFERENT LABEL_REFs (ret vs ret2)! Cross-jump's find_cross_jump(jumpA, jumpB) requires... does it compare the jump insns themselves? It compares insns BEFORE the jumps, not the jumps. But do_cross_jump requires both jumps to the same place? Let's look: for unconditional jumps, it tries `jump_chain[UID(JUMP_LABEL(insn))]` — targets with the same JUMP_LABEL. With different labels, they're not in the same chain, so no merge via that path. And the first path compares before jumpA vs before the ret label — before ret2 label = insns before it, which is the same stream? Hmm, ret2 and ret at the same address: before ret2 is the same insn sequence as before ret (both labels precede the same func_80010A98). Wait, the code is `ret: func_80010A98(); v0r=1;`. If we add `ret2:` immediately before `ret:`, then before ret2 = the same insns as before ret (the tail of block B? no...).

Let's think concretely. After adding:
```
    if (A) { ...; goto ret; }
    if (B) { ...; goto ret2; }
    ...
done:
    ...
after:
    ...
ret2:
ret:
    func_80010A98();
    v0r = 1;
```
Now jumpA targets ret, jumpB targets ret2. Cross-jump: for jumpA (simplejump), find_cross_jump(jumpA, ret_label, 1) compares before jumpA (block A) with before ret label (insns before ret, which are the same as before ret2 — since ret2 immediately precedes ret, prev_real_insn(ret) = prev_real_insn(ret2) = the last insn before both). Those differ. Then it tries other jumps to the same label (ret): only jumpA. So no merge. For jumpB, other jumps to ret2: only jumpB. So no merge!

But wait — will the assembler/linker coalesce the two labels? They're at the same address; two CODE_LABELs, both referenced, both kept. The bytes are identical (labels emit nothing). This could be byte-neutral! Brilliant.

But careful: gcc's jump1 (before reload) might merge/redirect jumps: `follow_jumps`/`thread_jumps` can redirect a jump to ret2 to ret if they're the same address? In jump1, `follow_jumps` follows LABEL_REF chains, not identical-address labels. Since ret2 is not a jump to another label, no redirect. Also `delete_insn` of an unused label — both are used.

However, jump1's `jump_optimize` also does "if a jump jumps to a label followed by another label" — hmm, there's code that merges labels? In jump1, `delete_jump` etc. There's `jump_to_label_p`. Actually there's a known optimization: if two labels are adjacent, gcc may delete one? The CODE_LABEL has LABEL_NUSES; adjacent labels both used are kept. But jump1 might redirect jumpB's target from ret2 to ret via `follow_jumps`? follow_jumps only follows chains where the label's next insn is a jump. ret2's next is ret (a label, not a jump). So no.

Also: line notes between labels — fine.

Let's try it! This is a real-C construct (an extra label + goto), no asm, no register, no levers. If it works, the barrier is cracked and score drops to 1 (just the keepalive li).

Actually wait: does a `goto` to a label count as a lever? No. It's real C.

Let me try variants:
- f01: block B `goto ret2;` with `ret2: ret:` at the end.
- f02: block A goto ret, block B goto ret2 (same).
- f03: three labels? 

Let me write f01. Also try placing ret2 AFTER ret (both before func_80010A98). Same address.

Hmm, but will the two labels actually be at the same address? `ret2:\nret:\n func_80010A98();` — yes.

But there's a catch: jump2's cross-jump could still merge the two blocks via the "return insns" path or via the conditional jumps path. The conditional jumps: `beqz v0, labelA` and `beqz v0, labelB` (the if-targets) are different blocks. Cross-jump of conditional jumps requires jump_back_p. Probably not.

Also, after cross-jump of unconditional jumps is blocked, is there any other merge? The two blocks might be merged by jump1's `thread_jumps`? No, that's for jump-to-jump.

Let me test.

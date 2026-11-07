---
ts: 2026-11-06T14:24:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_i9OH8hASZyZSOVyT8QKZ
---
Line 1220: `propagate_block(..., 1, ...)` — final=1. So on the final pass, dead stores are deleted before counting refs. Confirmed: dead stores don't add refs.

BUT: the deletion uses `insn_dead_p(PATTERN (insn), old, 0)` where `old` is the live set at the end of the insn (from the backward scan). So an insn is dead if all its SET dests are dead. For `t = i`, if t is dead, it's deleted, and the use of i isn't counted.

Hmm. BUT what about an insn that's a SET whose dest is dead but which has a USE (not a SET) of i? `insn_dead_p` checks the pattern: for a SET, it checks if the dest is dead. If the insn is `(set t (plus i 1))` and t is dead, insn_dead_p returns 1 and it's deleted, use not counted.

So we need a use of i in an insn whose DEST is LIVE (so not deleted), but where the use of i doesn't generate extra code. The worked example did this: `r = p + i` where r is live (used by the store). So the insn `r = p + i` has a live dest and is counted. Then cse1 (before flow) would normally fold r into the store address, eliminating the separate insn. The do-while(0) prevents that fold, so the insn survives to flow and is counted. But then the final code has `r = p+i` as a separate add? The worked example's final code must have had the add as a separate instruction that matches the target. So the target naturally has that add.

For our case, is there an existing add that we can attribute to i? The target's loop has:
- `addu $11,$11,2` (dst++)
- `addu $10,$10,1` (i++)
- `addu $9,$9,2` (src++)

If I express one of these as an expression involving i, e.g., `src = src + i - i + 2`? folds.

What if the increment is `src += (i >= 0) + (i >= 0)`? That would compute the comparison, extra code.

Hmm.

What about the address computation for the store: `*dst = out`. If I write `dst[i % n] = out`? no.

Let me look at the worked example's target: it had a real `add` that the source computed. In our target, the loop's only adds are the three increments.

Hmm, what if I make the `i++` increment produce TWO RTL occurrences? `i = i + 1` produces set dest i + use i = 2 occurrences, same as i++. No.

What if `i += 1` where the RHS is a constant — same.

What if `i = i + 1` is written as `i = 1 + i`? same.

Hmm.

OK here's another thought: what if I add a real use of i in the *loop condition* in a way that folds into the slt. E.g., `while ((i - n) < 0)` — gcc's fold might simplify to `i < n` (slt), same code, and the ref to i is still 1. No gain.

What about `while (i < n)` written as `while (i <= n - 1)`? fold -> i < n. Same.

What if I write `while (i < n)` and ALSO use i in a real computation that folds into the slt? There's only one slt.

Hmm.

Let me reconsider the live_length lever. The target i live=41, ours=39. The asm adds 2 to live_length (as I computed). If I could extend i's live_length by 4 (to 43), priority = 33/43 = 0.767 < dst 0.917 -> i loses. Wrong direction! I want i's live SHORTER or refs HIGHER.

Wait, i's priority = 33/live. To make i WIN, increase priority = decrease live or increase refs. So shorten i's live to <= 36 (tie at 36) or <=35 (clear win). Currently 39. Need -3 or -4.

How to shorten i's live range? Move `i = 0` later (closer to the loop) or the last use earlier. The last use is the slt in the latch. Can't move.

Moving `i = 0` later: b2 moved it after src/dst but live stayed 39. Why? Because the RTL order put i=0 first anyway (sched1? no, flow is pre-sched). Hmm, but flow's live_length is computed on the pre-sched RTL. If the C order is src; dst; i=0, expand emits load; add; set i=0. Then flow should see i born later. Unless expand/jump reordered. Let me check the pre-flow RTL order. The .jump dump is after jump_optimize (line ~2920). Let me look at the .jump dump for b2 around the setup.

Actually, I dumped c1 and b2 with cc1_dumps_tu which includes .jump (jump.c dump). Let me look at b2's .jump dump insn order for the setup block. But .jump is huge. Let me grep for the relevant insns.

Alternatively, maybe live_length counts the register as live from the START of the block if it's live at the block start (because it's used later in the loop). Hmm! i is live at the start of block 14 (loop body) because of the back edge. And i=0 is in block 13. If i=0 is the last insn of block 13, then i is live throughout block 13 from... no, only from i=0 to the end of block13.

Wait, maybe i=0 is placed at the END of block 13 regardless of C order because sched1... no, flow is pre-sched.

Let me look at the .jump dump for b2 to see the actual pre-flow order. Actually, maybe simpler: let me look at the .rtl dump (after expand?) or .jump.

Hmm, this is a lot of effort. Let me instead try a more aggressive live-range shortening: move `i = 0;` to AFTER the `if (n > 0)` check? Not possible (i must be 0 before the loop).

What if I initialize i differently: `i = 0;` combined with the do-while? E.g., `for (i = 0; ...)`.

Hmm.

Actually, let me reconsider the priority formula. Maybe I can REDUCE i's live by making i die and be re-born? No.

Let me try a completely different angle: change the loop so that the comparison uses a DIFFERENT variable that's a copy of i, and i is used only in the increment. Then the "i" pseudo (reg160) would have fewer uses... no, we want more refs on reg160.

OK let me look at the actual .jump dump to understand the pre-flow RTL. Let me grep b2's .jump for the setup.

Actually, let me reconsider: maybe the live_length of i is 39 regardless because the loop body is counted multiple times? Let me count the loop: block14 (body) + block17 (latch). The loop body has ~50 insns. If live_length counted the loop body once, 39 makes sense for i (setup + one iteration). Moving i=0 by 2 insns should change it. Unless i=0 is not where I think.

Let me look at the flow dump (.flow) which might show the live sets per insn. Or the .jump dump. Let me grep the .jump dump for the setup insns in b2.

Actually, let me just test an extreme: move `i = 0;` to just before the `do` (inside the `if (n > 0)`), i.e., after the guard. That would place i=0 after the blez, shortening i's live by the whole setup. But it might change code (i=0 would be after the branch). Let me test the score — if it's 0, great.

Variant: 
```
n = ...;
src = ...;
dst = src + n;
if (n > 0) {
    i = 0;
    do { ... } while (i < n);
}
```
But i is declared outside. The target has `move $10,$0` BEFORE the blez. If I move i=0 after the guard, the asm would place it after the blez (or reorg might move it into the delay slot). The target has it before the blez. So likely a mismatch. But let me test to see.

Actually, hold on. Let me re-examine the target asm:
```
	mult	$3,$2
	move	$10,$0        # i = 0
	lw	$9,0($13)     # src = arg0->data
	mflo	$12
	sll	$2,$12,1
	blez	$12,$L129
	addu	$11,$9,$2     # dst = src + n
```
So i=0 is before src load, before the blez. If I move i=0 after the guard, sched1 might hoist it back (it's independent). Actually sched1 reorders within basic blocks. The blez ends block 13? No — the blez and its delay slot are in block 13. The `addu dst` is in the delay slot (block 13's end). If i=0 is inside the `if` block (block 14), it would be after the branch. sched1 operates within a block, so it can't move i=0 from block 14 to block 13. So the code would differ. Bad.

Hmm.

Let me look at this from yet another angle: maybe the target's live_length 41 for i comes from the asm adding 2, and the ORIGINAL (real C) source also had i live 41 naturally. What would make i live 41? Two more insns where i is live. The asm insn (1) plus the ref counting adds 1 to live_length (the set of the reg at birth, line 2073 `reg_live_length[regno]++`). So the asm adds 2. A real C use in the loop would also add 1-2 to live_length and +3 refs. But we established real uses in the loop would emit code unless folded.

Wait — what if the real use is a use that gets folded into an existing instruction by combine, but combine runs AFTER flow. So flow counts the ref and live, then combine folds it. That's the worked example's do-while(0) trick: the do-while(0) prevents cse1 from folding, but combine (after flow) CAN fold it? Let me re-read: "do{}while(0) around two copies splits cse1's EBB so sched1 keeps their birth order". And in func_80181F4C, the `do { r = p + i; } while (0);` is followed by `*(s16 *)(r + 0xE) = ...`. So r IS used. cse1 would normally merge r into the store address; the do-while(0) prevents it. But then how does the final code match? The final code must have the add as a separate instruction because the target does. Let me look at func_80181F4C's win.c and target to understand. Actually, the note says the do-while(0) is "in the 0xE store". The store address `r + 0xE` where r = p+i. The target likely computes `p+i` in a register then stores at offset 0xE. So the add IS in the target. So the do-while(0) preserves a real add that the target has.

For our loop, the target's only adds are the increments. So we need i to appear in an increment. 

Hmm, what if I rewrite `i++` as something that produces the same `addu $10,$10,1` but with an extra use of i? Like `i = i + 1` — same 2 occurrences. `i += 1` same.

What if `i = (i + 1)` and also use i's old value somewhere? That would be an extra use.

What if the increment is `src += 2` and I express the 2 as `i - i + 2`? folds.

What if `dst = dst + (i - i) + 1`? folds.

Hmm.

OK, let me look at whether the loop could naturally be a `for` loop with the increment in the header, which might produce a different RTL ref count for i. f1 gave frame 32 (bad), but let me check its loop refs. Maybe the for loop with the right form gives i=12.

Actually, f1 changed the frame size, meaning an extra callee-saved reg was used. That's bad.

Let me try a for loop that keeps the do-while shape but moves i++ into the condition: `do { ... } while (i++ < n - 1)`? Hmm, semantics: we want to iterate n times. `do {...} while (++i < n)` with i starting -1? Changes i's init.

Actually, the target has i++ then slt. `do {...; i++;} while (i < n)`. If I write `do {...} while (++i < n)`, the increment happens in the condition. RTL: i = i+1 then slt(i,n). Same instructions, same order! And the ref count: ++i in the condition — same 2 occurrences + slt use. No change.

Hmm.

Let me try a different decomposition: make `i` the loop counter AND use it in the load address via the do-while(0) trick with a GIV that folds into the existing `lhu`/`addu`. 

Actually — here's an idea based on the worked example. The worked example's `r = p + i` folded into the store address because the store used r. For us, the LOAD `px = *src` — what if I write `px = *(u16 *)((u8 *)src + i - i);`? folds.

What if the loop keeps `src` but I express the load address as `src + i*0`? folds.

Hmm.

OK, let me try the array-index for-loop (f3) and see. And maybe the do-while(0) trick around a real i use in the address with the base pointers.

Let me write f3: for loop with array indexing where src and dst are base pointers that don't advance.

Actually wait — in b1, the do-while with src[i]/dst[i] scored 52. The for-loop version might strength-reduce better. Let me test.

Let me also test a variant where only the store uses i: keep src as a pointer increment, but dst as a base pointer indexed by i:
```
src = arg0->data;
dst = src + n;   // base
for (i=0; i<n; i++) {
    px = *src;
    ...
    dst[i] = out;
    src++;
}
```
Here dst is fixed, dst[i] uses i. loop.c strength-reduces dst[i] to a pointer increment; the final code should be `sh out,0(dstp); dstp += 2`. And i has refs from the index. Let me test this (f4).

Actually, let me be efficient and test f3 and f4 together.

f3:
```
n = arg0->w * arg0->h;
src = arg0->data;
dst = src + n;
if (n > 0) {
    for (i = 0; i < n; i++) {
        px = src[i];
        ...
        dst[i] = out;
    }
}
```
f4:
```
n = arg0->w * arg0->h;
src = arg0->data;
dst = src + n;
i = 0;
if (n > 0) {
    do {
        px = *src;
        ...
        dst[i] = out;
        src++;
        i++;
    } while (i < n);
}
```
Hmm f4 uses dst[i] with i, and src++ separately. Let me test.

Let me generate f3 and f4.

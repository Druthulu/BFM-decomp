---
ts: 2026-11-06T16:53:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6sNuxmkt1Q4GtR1q2tAK
---
No change (10). The allocator still puts the loaded value in $a0 and the sign-ext temp in $v0.

Hmm, the sign-ext temp still exists (the `(s16)v1`). In p02, the temp takes $v0. Splitting the loaded value doesn't dislodge it.

What if I split the *temp*: no.

Let me think about the order of allocation. In the branch block, the quantities are: v0 (unk70/loaded), v1 (used in the compare), the sign-ext temp, a0r, at, v0x. local-alloc allocates block-local qtys first, then global.

The sign-ext temp is block-local (used only in the branch block). It gets $2 (highest local priority). Then v0 (global) can't get $2 → $a0.

In the target, the temp is tied to v1 ($3) — why? Because local-alloc's *copy suggestion*: `sra v1,temp` is not a copy. Hmm.

Wait, maybe in the target the temp doesn't exist: the RTL is `sll v1,v1,16; sra v1,v1,16` — both self-sets, no temp. That's what t01 tried (self-sets) and got 65 ins. In t01, the temp was gone but the loaded value still went to $a0 (a0r coalesced). Let me look at t01's first block: `lh a0,0(at)` — the loaded value in a0. Why not v0? Because the sign-ext self-set doesn't compete, but then what took $v0? Let me objdump t01.

Actually in t01, the branch's v0 (unk70) is used early and dies at the load; the loaded value could reuse $v0. But it went to $a0. Maybe global-alloc put v0 in $a0 because of the JOIN/K v0b taking $v0? In p02, v0b (JOIN/K) got $v0 and the branch's v0 got $a0. So the conflict is between the branch v0 and v0b — they're different variables with disjoint ranges; both could be $v0, but global-alloc gave v0b $v0 and v0 $a0.

Hmm, global-alloc's priority: v0b (JOIN/K, short) beats v0 (block1+branches, long). If I split the branches' v0 from block1's v0 (q01 did, 29) it got worse.

What if I make v0b (JOIN/K) a *local* variable (declared in an inner block) so local-alloc handles it and it doesn't compete globally? C0087: declaration scope is the lever. The JOIN/K region is not a block in the source... I could wrap it:
```
JOIN:
    {
        s32 v0b;
        if (!func_8012BEE8(s0)) goto K;   // goto out of a block is fine
        v0b = ...;
        ...
    }
K:
    ...
```
A goto into/out of a block is allowed if no VLA. K is a label outside. Hmm, `goto K` from inside the block jumps out — allowed. But the variable declared inside the block is local to that block → local allocno.

Let me try wrapping the JOIN region in a block with a local v0b. But the `goto K` from inside the block to outside is fine.

Actually, p02's structure:
```
JOIN:
    if (!func_8012BEE8((s32)s0)) {
        goto K;
    }
    v0 = unk70; ... v0 = *(u16*)at; s0->unk1C = v0; func_8012C588(0x1A4, s0);
K:
    v0 = unk70; if (v0 == 0) func_8017F348(s0);
```
Hmm, wait: p02 renamed all v0 from JOIN onward to v0b. So:
```
JOIN:
    if (!func_8012BEE8(s0)) goto K;
    v0b = unk70; ... v0b = *(u16*)at; s0->unk1C = v0b; func_8012C588(...);
K:
    v0b = unk70; if (v0b == 0) func_8017F348(s0);
```
v0b is used across the JOIN and K blocks → global.

If I make v0b block-local... the K use is in a different block, so it can't be one variable. Split into v0b (JOIN block) and v0c (K block), each block-local if declared inside blocks. Hmm.

Actually, let's reconsider. Maybe the right approach is different: make the *sign-ext temp* not exist by using the self-set (t01) AND fix the a0r coalescing.

In t01: the missing `move a0,v0` means a0r coalesced with the loaded value. To prevent coalescing, make a0r's value live longer or the loaded value die... The target has `move a0,v0` because a0r must survive while v0 is modified. If a0r and the loaded value are in the same register, the modification `v0 = v0-0x30` would clobber a0r, so the compiler must either use a different register or emit the move. gcc's combine/regalloc chose to coalesce and then... wait, if they're the same register, `v0 = v0-0x30` would clobber a0r, which is wrong! Unless the store of a0r happens before the modification. In the target, the store is in the delay slot of the branch at 33b8, after the slt. Hmm, a0r is stored only if `v0 >= v1`.

In t01's code: `addiu v0,a0,-48; slt v0,v0,v1; bnez v0,...; ...; sh a0,48(a1)`. Here a0 holds the original loaded value, and v0 = a0-48. So a0r = a0 and the loaded value are the same register, and the modification is in v0 (a separate register). Wait, `addiu v0,a0,-48` writes v0 from a0 — so v0 (the source variable) is $v0 and a0r is $a0! The loaded value was in $a0, then copied to $v0 via addiu. So actually the loaded value (v0x) is in $a0 and a0r is also $a0 (coalesced), and the modified value goes to $v0.

But the target has the loaded value in $v0, then `move a0,v0` (a0r=$a0), then `addiu v0,v0,-48`.

So in t01 the loaded value went to $a0 (a0r's register) and the modified value to $v0. In the target, the loaded value is $v0 and a0r is $a0.

Hmm, so the allocator wants the loaded value in $a0. Why? Because a0r = v0 is a copy and local-alloc suggests the same register; it chose $a0 for a0r (global priority?) and tied the loaded value to it.

I'm going in circles. Let me try a different structural approach: maybe use `a0r` directly as the loaded value and avoid the copy:
```
a0r = *(s16*)at;
v0 = a0r - 0x30;
if (v0 >= v1) { a1->unk30 = a0r; }
```
That's u01 essentially (v0x = load; a0r = v0x). It gave 10.

Hmm.

Let me look at this from the "what would the original source be" angle. The decomp author wrote this body and needed a pin for v0. The original Square source probably used a different variable structure that naturally yields $v0. Maybe the original used `arg0`/`p` differently.

Honestly, item 3 might be a WALL. I've done ~30 tries now. Let me count: w1, m01-m08 (8), n01-n13 (9), o01-o02 (2), p01-p03 (3), q01-q03 (3), r01-r06 (6), s01-s03 (3), t01-t03 (3), u01-u03 (3) = 41 tries. Time: started 09:44, now ~09:56 = 12 min. Need 20 min → until 10:04.

Let me continue trying a few more structural ideas for another 8 minutes, then record the WALL with best 9 (t01) or 10 (p02). Note: t01 is 9 but has a wrong coalescing (65 ins). The "best" is the lowest score: 9.

Hmm, but a WALL's best should be a legitimate lever-free body; t01 is lever-free (no pin/asm). Fine.

Let me try a few more:
- v01: p02 + wrap JOIN in a block with a local v0b.
- v02: p02 + make the K v0 a separate variable.
- v03: t01 + prevent a0r coalescing by making a0r live across the modification differently (e.g., store a0r before v0 = v0-0x30? no, changes order).
- v04: use `a0r = *(s16*)at;` and `v0 = a0r - 0x30;` on top of t01 (self-set extension) — combine might still coalesce.
- v05: split v0 in the branch as v0x with the sign-ext self-set.

Let me try v01/v02 quickly. Actually, let me reconsider the whole thing: p02's remaining diff is just the branch blocks: the loaded value in $a0 vs $v0, plus the sll/sra placement. If I can get the loaded value into $v0, score → maybe 0.

The loaded value is the branch's `v0` (same var as block1). In block1 it's $v0 (correct!). In the branches it's $a0. Why does the SAME variable get different registers in different blocks? Because local-alloc can reassign per block if the variable is local... but v0 is global. Hmm, wait: in p02, v0 is used in block1 and the branches (global allocno), but global-alloc assigns ONE register for the whole function. So how can it be $v0 in block1 and $a0 in the branches? It can't!

Unless the loaded value in the branches is a *different* pseudo. In the branch, `v0 = *(s16 *)at;` sets v0; `a0r = v0;`; `v0 = v0 - 0x30`. The RTL: v0 is one pseudo. But the diff shows `lh a0,0(at)` — so the load dest is $a0. That means the pseudo allocated to $a0 is the *load result* which combine may have renamed to a0r (copy propagation: a0r = v0 → use a0r directly). Then `addiu v0,a0,-48` computes v0 from a0r. So the load's value is a0r ($a0), and v0 is a separate pseudo ($v0).

In the target: `lh v0,0(at)` (v0), `move a0,v0` (a0r=v0), `addiu v0,v0,-48`. So the load dest is v0.

The difference: combine propagated the copy `a0r = v0` into using a0r at the load (i.e., the load's dest became a0r). In the target it didn't.

Why? Because combine's copy propagation depends on register allocation (combine runs before allocation!). Hmm, `a0r = v0` — combine could propagate v0 into a0r's uses, but here it's the reverse: the load writes v0, then a0r = v0. Combine might replace a0r with v0 (copy propagation) → then `v0 = v0 - 0x30` and the store uses v0. But v0 is modified, so the store must use the old value → combine can't propagate past the modification. So the copy stays.

Then why does mine's load write a0r? Maybe local-alloc coalesced the copy (a0r and v0 get the same register) and then the addiu... no, if they coalesced, the addiu would be `addiu v0,a0` only if v0 is a different register.

I think I'm overanalyzing. Let me try a completely different source spelling for the branch tail:
```
v0 = *(s16 *)at;
a0r = v0;
v0 = a0r - 0x30;      // use a0r instead of v0
if (v0 >= v1) { store a0r; }
```
Maybe this prevents coalescing? Let me try (v04).

Also:
```
a0r = *(s16 *)at;
v0 = a0r - 0x30;
```
(u01 tried).

Let me just try a batch of ~8 and then wrap up.

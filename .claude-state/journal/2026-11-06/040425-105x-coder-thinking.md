---
ts: 2026-11-06T11:04:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_h6uKS6SOp87fPNp6bfDq
---
x_ns16 (n declared s16) fixed the outer-else `li v0,3` (position 60). Remaining: the loop delay slot (lever 5): mine lacks `addiu v0,s1,1` at position 84 and the branch targets differ.

This is the reorg delay-slot fill issue. The `__asm__("")` was at the head of the if-body. Without it, reorg fills the `beqz` slot from the fall-through; the target fills it with the branch target's `addiu v0,s1,1`.

Let me think about what the target's code is:
```
fdc: beqz v0,ff8       # if (D_80115158[i].h == 0) goto ff8 (i++)
fe0: addiu v0,s1,1     # delay slot (copied)
fe4: move a0,s0        # call setup
fe8: jal func_801880E0
fec: move a1,s2
ff0: move s0,v0
ff4: addiu v0,s1,1     # i++
ff8: move s1,v0
```
So the delay slot is filled with a *copy* of the fall-through's `addiu v0,s1,1` (at ff4). That's reorg's fill_simple_delay_slots copying an insn from the branch target (ff8 is `move s1,v0`... hmm, the copy is from ff4 which is before the target ff8).

Actually the delay slot at fe0 duplicates ff4's addiu. reorg can fill a delay slot with an insn from the branch target if the branch is taken... but then it must not execute on the taken path. Here the branch is taken when the if is false (beqz v0 → ff8). The delay slot executes on both paths. The addiu at ff4 is on the fall-through path (the call path). Copying it into the delay slot means it executes twice on the fall-through path? No: if the delay slot has the addiu, the fall-through path continues at fe4 (move a0,s0) and later at ff4 executes the addiu again. So it's duplicated: once in the slot, once at ff4. That's exactly what the comment says ("the duplicated addiu $v0,$s1,1 the target has in both the delay slot and after the call").

Why would reorg duplicate it? That's the "fill from the branch target" behavior: reorg can fill a delay slot with an insn from the target block if it's safe (the insn is executed anyway). Hmm, actually reorg's fill_simple_delay_slots looks at the fall-through (next insns) first; if the branch is conditional and the slot is filled from the fall-through, it must not be an insn that's needed later.

The asm fence made the forward scan stop, so reorg looked at the branch TARGET instead (fill from target).

Real-C replacement: hmm. This is a reorg behavior influenced by the presence of an asm insn. 

Can a do-while produce a similar effect? The do-while emits a LOOP note, not an insn. reorg's stop_search_p checks for insns it can't move (asm, calls, etc.).

What if we put a real C construct that reorg won't move past at the head of the if-body? E.g., a function call? No.

Hmm. What if we restructure the loop so the delay slot naturally gets the addiu? E.g., put `i++` BEFORE the call:
```
do {
    i++;
    if (D_80115158[i-1].h != 0) { ot = call(ot, w, i-1); }
    w++;
} while (i < cnt);
```
That changes the codegen.

What if the if-body is inverted: `if (h == 0) goto skip; ...`? C doesn't have goto-free... we can use `if (h == 0) { } else { call }`.

Let me try a few loop shapes:
1. `if (D_80115158[i].h != 0) { call } else { }` (empty else)
2. `if (!D_80115158[i].h) { } else { call }`
3. `if (D_80115158[i].h == 0) { i++; w++; continue; } call; i++; w++;`
4. Move `i++` before the if:
```
do {
    i++;
    if (D_80115158[i - 1].h != 0) ot = call(ot, w, i - 1);
    w++;
} while (i < cnt);
```
Hmm, the index arithmetic changes.

5. Use a `while` with the counter updated differently.

Time: ~04:50. Let me try a few quickly, then record.

Actually, note the diff also shows the branch at 73 and 93 (target offsets differ by 4) — those are consequences of the missing insn.

Let me generate 4-5 loop-shape variants from x_ns16 and score.

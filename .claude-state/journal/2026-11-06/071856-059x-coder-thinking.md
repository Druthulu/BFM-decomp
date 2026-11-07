---
ts: 2026-11-06T14:18:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cBRDZzIwqbiqV7SibEkg
---
The allocation order (highest priority first): 175 171 187 153 179 195 161 162 160 159 213 180 73 76 75 74.

So 162 (dst) comes before 160 (i). 161 (src) before 162. So the order is: src, dst, i. Target needs i before dst.

Now let me compute the priorities to see the margins. I know refs and live lengths from the lreg dump:
- 161 src: 13 refs, 38 live -> 3*13/38 = 1.026
- 162 dst: 11 refs, 36 live -> 3*11/36 = 0.917
- 160 i: 11 refs, 39 live -> 3*11/39 = 0.846

Order: src (1.026) > dst (0.917) > i (0.846). ✓ matches.

Target: i=14/41 -> 3*14/41 = 1.024; src=15/40 -> 3*15/40=1.125; dst=11/37=0.892. Order: src > i > dst. ✓

So I need to get i above dst. Options:
1. i refs 12 (3*12/39=0.923 > 0.917) — margin 0.006.
2. dst live 40+ (33/40=0.825 < 0.846).
3. dst refs 10 (30/36=0.833 < 0.846).
4. i live 36 or less (33/36=0.917 == dst; tie -> i lower allocno number wins if i's allocno < dst's). i is declared before dst so i's pseudo number is lower. But allocno numbers are assigned per pseudo in order, so i's allocno < dst's. If priorities tie exactly, i wins. So i live 36 gives a tie at 0.917 — but wait, the priority is computed as `int` via `(double)... * 10000` then truncated to int. Both would be 0.9166*10000=9166. Tie -> allocno compare -> i wins (lower allocno). 

Hmm, i live 36 means shortening i's live range by 3. dst live 40 means extending by 4.

Option 2 (extend dst live) is the most tractable: move dst's definition earlier in the C. But b2/b3 didn't change the score — let me check whether they changed the live lengths. Let me dump b2.

Actually, hold on. b2 reordered to `src; dst; i=0`. dst's birth is before i=0. In the original, dst is after i=0 and src. So b2 moves dst's birth earlier by 1 insn (i=0). That's +1 live. Not enough (need +4). Also i's birth moves later by 1 (after dst) -> i live 38, priority 33/38=0.868 < 0.917. Still dst wins.

Let me try to extend dst's live range more aggressively. Move `dst = src + n;` to before `src = arg0->data`? Not possible (uses src).

But I can compute dst differently: `dst = arg0->data + n;` — then dst doesn't depend on the src variable's assignment, so it can be moved earlier! E.g.:
```
n = arg0->w * arg0->h;
dst = arg0->data + n;
i = 0;
src = arg0->data;
```
This makes dst born early (right after n), extending its live range significantly. But it adds a second load of arg0->data (the `lw $9,0($13)` would be duplicated or cse'd). cse would merge the two loads of arg0->data (same address, no intervening store) -> one load, and dst = that + n. Hmm, but then the instruction order might change.

Wait — actually, if I write `dst = arg0->data + n; src = arg0->data;`, cse2 (before flow) would CSE the two `arg0->data` loads into one pseudo. Then `dst = p + n` and `src = p`. But then dst and src share the loaded value. The target has `lw $9,0($13)` (src = arg0->data) then `addu $11,$9,$2` (dst = src + n). If cse merges, we'd get the same. But the RTL order might differ.

Hmm, this could also change live ranges.

Alternatively, extend dst's live range by adding a real use of dst EARLY (before its def)? No, that's a use-before-def.

Hmm, what about the "dst = src + n" being used in a way that its def is earlier but the use is the same. The live_length = death - birth (roughly). Extending birth earlier by moving the def earlier.

Let me reconsider: maybe there's a much simpler lever I'm missing. Let me look at how the ORIGINAL source might have looked. The comment says the src asm keeps src "above i, below the mfhi temp" and i asm "lifts i over dst". Maybe the original loop was written with a `for` loop where the increment `i++` was in the for-header, changing the RTL order and thus the live ranges/refs.

Let me try a `for` loop:
```
for (i = 0; i < n; i++) {
    ...
    *dst = out;
    dst++;
    src++;
}
```
This puts i++ at the bottom (same RTL) but the loop structure might differ. Let me test.

Also try `while` loop:
```
i = 0;
while (i < n) {
    ...
}
```
gcc's loop inversion.

Let me batch these two.

Also: what if `i` is used in the loop condition at the TOP and the do-while is gone. The target is do-while though. But gcc's loop.c may convert while to do-while (loop inversion) if the loop is entered... Actually gcc 2.7.2 does "loop inversion" only in specific cases. Let me test.

Let me also try the `for` loop with the increment in the header.

And another idea: make the loop body use `i` in the store address as `dst[i-i]`? folds.

Let me batch: f1 = for loop; f2 = while loop; f3 = for loop with i++ in header and dst++/src++ at bottom.

Let me write f1 as a full body.

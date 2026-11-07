---
ts: 2026-11-06T14:15:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1obFlqrfOmabfzxcTjpM
---
Pass order: jump, cse, loop, cse2, flow_analysis, combine, sched1, local-alloc, global-alloc, reload, sched2.

So flow_analysis (which computes reg_n_refs) runs BEFORE combine. If I add a real use of i that flow counts, and combine later deletes the instruction, then global-alloc still sees the inflated ref count. 

But wait — combine deleting the instruction changes the instruction stream. If it deletes an instruction that's not in the target, then the final code still matches target (since the instruction was extra). But if combine does NOT delete it, we get an extra instruction -> mismatch.

Actually even better: the use of i in `dst = src + n + i` — combine would need to fold i=0. Does combine know i==0 at that point? There's a REG_EQUAL (const 0) note on the set of i. combine's `try_combine` uses `reg_last_set_value`... Hmm, combine doesn't generally do constant propagation via REG_EQUAL for arbitrary uses. It might not fold. Then the code would have an extra addu. Risky.

Alternative: make the extra use of i be in an expression that is otherwise already computed, so no extra instruction. For example, the loop condition `i < n`: if I write `(i < n)` and ALSO `(n > i)` somewhere? no.

Hmm, what about a use of i that is DEAD and gets deleted by dead-code elimination — but flow runs before dce? Dead code elimination (in jump.c `delete_dead_jumptables`? or in `life_analysis`)... The `flow_analysis` call computes refs; then combine; sched; local/global alloc; then reload; then sched2; then `if (flag_... )` maybe `flow_analysis` again? Actually there's a second flow pass after reload? Let me check around 3105-3120. But reg_n_refs for global-alloc is set by the flow at 2983. Dead code elimination happens in jump.c's `delete_noop_moves` / `delete_dead_code`? Actually gcc 2.7.2's `jump_optimize` is called at line ~2920 before flow. And there's `delete_dead_code` inside jump_optimize. But our extra use is added after that.

Hmm. What about the `if (n > 0)` guard — could I use i there in a way that folds to the existing `blez`? `if (i < n)` with i=0: gcc emits `slt $2,$10,$12; bne` or `bge`? It doesn't know i=0. So extra instruction.

Let me reconsider. Maybe I'm overcomplicating. Let me look at what the ACTUAL original game source likely was, or find similar functions in the codebase that match this pattern. The three TUs are the same function. Maybe another shard already cracked a similar "keepalive ref-count" item.

Let me look at the retriever? I have "/usr/bin/python3 tools/pa_ext.py ask". Actually the task says I can use retriever-code via pa_ext.py. Let me ask about similar cracked keepalive ref-count cases. Hmm, but it may not be that useful.

Let me instead look at the worked example .run/P40/T10/func_80181F4C/notes.md and win.c for technique.

Actually, let me focus. The most direct lever: add a real use of i that flow counts and combine/sched removes without changing code. 

Actually — here's a much cleaner idea. What about making the loop counter `i` also serve as the `dst` offset? Specifically, the target has three increments: dst+=2, i+=1, src+=2. What if I express `dst` as `src + n` and then in the loop increment dst — no.

Alternative clean idea: change the loop to use i as the *only* counter and derive src/dst via i, but strength-reduced... no.

Let me look at this from the "what did the original source look like" angle. The target code computes:
- src starts at arg0->data, dst = src + n.
- Each iteration: load *src, store *dst, src+=2, dst+=2, i+=1, compare i<n.

The natural source:
```
u16 *src = arg0->data;
u16 *dst = src + n;
for (i = 0; i < n; i++) {
    u16 px = *src;
    ...
    *dst = out;
    src++;
    dst++;
}
```
Here i is used only in the for-condition and i++. Same as ours (do-while). Hmm.

But wait — the target's i=0 (`move $10,$0`) is placed before the blez guard, and the increments are at the bottom. A for-loop `for (i=0; i<n; i++)` would give exactly this. Our do-while with explicit i++ should be equivalent.

So the original probably had the same structure, and the target's i ref count is naturally 14? But our C gives 11. That means the original source had MORE uses of i, OR the original was compiled with different flags/pass behavior.

Hmm wait — maybe the target's i ref count is 14 because the original had `i` used in the load/store addressing that loop.c then strength-reduced. If loop.c strength-reduced `src[i]` and `dst[i]` into pointers, the pointer increments would be in the loop, and i's refs would include the addressing uses (before loop.c?) but flow runs AFTER loop.c. So the strength-reduced form wouldn't have i in the addressing.

Hmm, but loop.c might leave the original i uses and add GIVs. The final code has i++ and slt only.

Let me try the array-index formulation anyway and see what code it produces. If it produces the same code with i in t2, great.

Actually, let me first test the simple variants. Let me batch.

Let me write the variants. I'll use mkvar.py with exact strings from c1.c.

Let me first view c1.c's relevant lines to get exact text.

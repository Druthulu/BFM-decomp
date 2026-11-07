---
ts: 2026-11-06T11:53:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jqf06gOiSOWCIBCmb8GN
---
Still forwarding. So the in_struct hash difference didn't help (maybe MEM_IN_STRUCT_P isn't set for a simple u8 field, or the hash doesn't distinguish).

Let me look at line 1951 context: `if (MEM_IN_STRUCT_P (x)) hash_arg_in_struct = 1;` — this is in `hash_rtx` for MEM. And line 1488: `new->in_struct = hash_arg_in_struct;`. And `lookup` uses the hash. So if the store's mem has in_struct and the load's doesn't, hashes differ. But apparently they're both the same (maybe both set or both unset).

Hmm.

Let me step back and consider: maybe the target's lbu is achievable by making the reload read a **different but equal address expression** that hashes differently. E.g., the store at `(u8*)arg0 + 6` and the load at `(u8*)((u8*)arg0) + 6`? Same RTL.

What if the load uses a **different constant folding**: `*(u8 *)((u8 *)arg0 + 3 + 3)` → fold to +6. Same.

What if the load's address is `(plus (reg) (const 6))` vs `(plus (const 6) (reg))`? fold_rtx normalizes.

Hmm.

Let me try a different tack: prevent cse from recording the STORE by making its source not in the hash table. From the code: `|| sets[i].src_elt == 0` → "If we didn't put a REG_EQUAL value or a source into the hash table, there is no point in recording DEST." So if the store's source value has no src_elt (i.e., it's not a register/constant in the table), cse won't record the destination!

What source values have src_elt == 0? The store's src is `(subreg:QI (reg:SI temp_v0) 0)`. cse looks up the subreg; if temp_v0 has a known value in the table, src_elt is found. If temp_v0's value is not recorded (e.g., it's a memory load whose value cse didn't track?), src_elt might be 0.

In our case, temp_v0 = p[6] - temp_a0 (an arithmetic result). cse might track it as a computed value (subu) — cse doesn't usually track arithmetic results unless they're simple. Actually cse DOES track computed values (it's a global value numbering). The subtraction result is in the table.

Hmm.

Alternatively, make the store source a value cse can't represent: e.g., if the stored value came from a function call return. But there's no call there.

What if the store value is `(u8)temp_v0` where temp_v0 is loaded from memory right before? No.

Let me look at what makes src_elt == 0. In cse_insn, `sets[i].src_elt = lookup(src, ...)`. For a SUBREG source, cse might not look up subregs. Hmm, but our w1 forwards, so the subreg source was recorded.

Let me try making the store source a **bit-field extract** or something cse doesn't track.

Alternatively, make the store source a QImode variable:
```
u8 sv = (u8)temp_v0;
*(u8*)(arg0+6) = sv;
temp_v0 = *(u8*)(arg0+6);
```
The store src is `(reg:QI sv)`, which cse tracks → forwards. Tried (w5) → score 9 (worse, extra insn).

Hmm.

Let me reconsider: maybe the answer is a WALL. Score 1 is very close, but the wall tag `cse-store-forward` explicitly says "only a barrier/volatile stops it".

But before giving up, let me try the goto label more forcefully. The issue: the label was removed. What if I make the label a real branch target that can't be removed? E.g.:

```
if (temp_a0 == 0xFF) goto L1;
*(u8 *)((u8 *)arg0 + 6) = (u8)temp_v0;
L1:
temp_v0 = *(u8 *)((u8 *)arg0 + 6);
```
That adds a branch — changes code. No.

What about a label used by a `&&` fold? No.

Let me check whether cse's EBB is actually split by the do-while. Let me dump w2's cse and look at the block processing lines (";; Processing block from ..."). If there are two blocks around the store/load, then cse shouldn't forward. It did forward, so the block wasn't split at the right place.

Let me look at the cse dump for w2.

Actually, C0535 says do-while splits cse1's EBB — but maybe only when the loop body contains a copy. Hmm.

Let me try a real loop that the compiler can't eliminate:
```
for (i = 0; i < 1; i++) { *(u8*)(arg0+6) = (u8)temp_v0; }
```
loop.c might optimize it. Let me test.

Also `do { ... } while (temp_a0);` with a real condition — but that would change control flow (loop).

Hmm, what about putting the reload inside a `do { } while (0)` that is NOT adjacent? I tried.

Let me try the cse dump to understand the EBB. Time is limited; let me do it for w2.

Actually, let me reconsider the whole approach. Maybe there's a much simpler real-C crack: the original code might not have the barrier because the reload is from a **volatile**... no.

Wait — maybe the target's lbu comes from the fact that the store is `sb v0,6(s0)` and the load is `lbu v0,6(s0)`, and the compiler DID forward, but then the `lbu` was re-inserted because of the **`(u8)` cast on a memory operand**. Hmm no.

Let me look at the actual function in the game via the disassembly of the original ROM? Not available.

Let me try the `for` loop idea and a couple more, then decide.

Actually, here's a thought: what if the store and the load are separated by the **`temp_v1` stores**? Target order: sb +6, lbu +6, addiu, sb +5, sh×2, sh×4. The sh stores are after the lbu. If I move one of the `sh` stores between the sb and the lbu, cse's store-forwarding for the QI entry might be invalidated by the intervening store (a store to a different address doesn't invalidate a different address's entry, but cse's invalidate_memory may invalidate based on alias sets — a SH store to a different address within the same struct might invalidate the QI entry if it's considered "nonscalar"?).

Actually, if the intervening store is to a potentially-aliasing address, cse's `invalidate_memory` would remove the QI entry. For example, if the intervening store is to `(u8*)(arg0+0x10)` (scalar), it invalidates "variable addresses" — the QI entry at arg0+6 is a variable address too, so it might be invalidated! Let me check: invalidate_memory's `nonscalar` logic.

From cse.c around 1690-1720:
```
static void
invalidate_memory (writes)
{
  ...
  /* If we wrote a single scalar, invalidate only the same.  */
  ...
}
```
Let me read it.

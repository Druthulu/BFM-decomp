---
ts: 2026-11-06T01:33:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wqUAQH9oWh2mmQLA5mZh
---
Key: "one side falls through into the label ⇒ find_cross_jump's minimum is 1". Our case: zero falls through into the epilogue label; dec jumps to it. So minimum=1 applies, and the single `sw` matches. To stop it, we need the store insns to NOT be renumbered-equal, or the tail of zero to differ.

Options to make them differ:
- Make zero's store use a different SYMBOL/offset structure: e.g., store via a pointer `p = (s32*)((u8*)a0 + 0x1C); *p = 0x1D;` → RTL: (set (mem:SI (reg p)) (const 29)) — the address is a reg, whereas dec's is (plus s0 28)? Actually dec's is also (plus s0 28) after... hmm in RTL, struct field access is (mem (plus (reg) (const 28))). With a pointer variable p = a0+0x1C, the address is (reg p) which is different structure → not equal even after renaming (renumbering maps registers consistently; (mem (reg p)) vs (mem (plus (reg s0) (const 28))) — not equal). But codegen: p would be computed as addiu p,s0,28 → extra instruction! Target has direct sw 28(s0) with no addiu. Unless p = a0 (base pointer) and p->unk1C: (mem (plus (reg p) (const 28))) — renumbering maps p→s0 → equal. No good.

- Make the store in zero a different *mode*: target is `sw`. Both s32.

- Make the value not renumbered-equal: cross-jump's rtx_renumbered_equal_p allows register renaming, so different pseudos still equal. But it does NOT allow differing constants or differing memory structures.

- Use `((Unk*)a0)->unk1C = 0x1D + 0;`? cse folds to 29. Same.

- Store via a union or bitfield? changes insn.

Hmm, but what about the *other* matching direction: could we make zero's tail two insns matching dec's? No, dec's tail is one sw.

Alternatively, prevent the fall-through minimum=1 by making zero NOT fall through into the epilogue but instead have an explicit `j`... that adds an insn. But wait, target zero falls through with no j. So no.

Alternative: make dec's store differ. dec: `unk1C = unk1C - 1`. The store's address (plus s0 28), value reg. If we could make dec's store use a different addressing form: e.g., in dec, compute via pointer: `p = (s32*)((u8*)a0 + 0x1C); *p = *p - 1;` → address (reg p) requires addiu p,s0,28 → extra insn in target? Target dec has lw v0,28(s0); addiu v0,-1; j; sw v0,28(s0). No addiu for address. So no.

Hmm. What if we change the *load* in dec to make the RTL of the store differ? The store's source pseudo: cross-jump renumbers. But there's a subtlety: rtx_renumbered_equal_p for MEM addresses requires... let me recall the actual function. In jump.c:

```
static int
rtx_renumbered_equal_p (x, y)
...
```
For REG: returns 1 if reg_renumber equal or if both are regs with same mode and "the same value"? Actually it has:
```
case REG:
  /* If the two registers are the same, return 1.  */
  if (x == y) return 1;
  /* If both are pseudos, they match if ... */
```
Let me get the actual source. The tarball is 10MB maybe; extracting just jump.c is fine. Let me list tarball contents.

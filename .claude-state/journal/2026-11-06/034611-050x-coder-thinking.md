---
ts: 2026-11-06T10:46:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZkGqY5yhiQrsdv78Ib7a
---
Key: "A volatile and non-volatile reference can be interchanged" — so making only the load volatile doesn't block movement relative to non-volatile stores. Both must be volatile. That's a lot of volatiles (would change the MEM rtx? No — MEM_VOLATILE_P doesn't change the generated code except for ordering... actually volatile MEMs are not cse'd and not deleted, but the codegen is the same).

But making stores volatile would prevent dead-store elimination and reordering — the emitted instructions are identical (sw). The risk: volatile MEMs can't be combined, may inhibit some optimizations (like the bitfield RMW). But it's a real C qualifier, not an asm barrier. Is it "a lever"? Hmm. The task's spirit is "real C moves only" and no barrier. Volatile is a real C construct; the project itself uses `volatile u16 *pbh` in func_8018B238 as a deliberate spelling (§37/§36 bitfield double read). But using volatile purely to order instructions is exactly what a barrier does. I'd call it a lever of the "barrier" kind. Risky for the bank.

Let me look at the moves.md for barrier MATCHes to see what people used: "barrier | func_8003388C | MATCH — barrier: vo stores via plain casts (no /s, load can't pass)". So the trick is to spell stores via plain casts so the load can't pass. That's type-based aliasing: a store through a cast that the load's alias analysis can't disambiguate.

For our case: the load is `lw` from unkC4 (196) and the preceding stores are to 2, 192, 188, 92. We want the load to not pass *any* of them (it must stay at 28, i.e., after the unk5C store at 92). Hmm, but the target has the load AFTER all four stores. If the load can't pass the unk5C store, it stays after it — and since the other stores precede unk5C, it can't pass them either. So we just need the load to be dependent on the unk5C store (or any store before it).

The mem-dependence rule: "A MEM_IN_STRUCT reference at a non-QImode varying address can never conflict with a non-MEM_IN_STRUCT reference at a fixed address."

So if the load is a MEM_IN_STRUCT (a struct field access) at a *varying* address... our address is fixed (base reg + const). Hmm.

Type-based: in gcc 2.7.2, `MEM_IN_STRUCT_P` and the alias sets from `get_alias_set`. Two accesses to the same struct type at different offsets are provably distinct.

What if the load is through a `char*`/`u8*` cast? "We must allow QImode aliasing" — but the load is s32 (SImode), so a QImode store to the same location... The rule says a MEM_IN_STRUCT non-QImode at a *varying* address never conflicts with a non-MEM_IN_STRUCT fixed address. Our addresses are fixed.

So to create a dependence we need a *varying* address (a register without a constant offset). E.g., if the load's address is `(reg)` alone (computed into a register), and the store's is `(plus reg const)`... hmm, then the load's address is varying (a reg) → but the store is MEM_IN_STRUCT? 

Alternatively, make the store's address varying: e.g., compute the address of unk5C into a pointer variable and store through it: `*(u16 *)((u8 *)a0 + 0x5C) = 0x8000;` — the address is (plus reg 92), still fixed.

Hmm, what about using a pointer variable: `u16 *p = &((Unkstruct*)a0)->unk5C; *p = 0x8000;` — after cse, p becomes the same address.

What if the store is through a `u8 *` (QImode)? Then it aliases everything (QImode aliasing). A u8 store to 92(s0) would conflict with the s32 load at 196? Per the rule: QImode aliasing is allowed because char pointers can alias anything → true_dependence returns 1 if either is QImode? Let's read true_dependence.

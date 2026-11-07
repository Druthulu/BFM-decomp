---
ts: 2026-11-06T11:54:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_27YJYnqdclDtGWIi72if
---
`sets[i].src_elt = lookup(src, ...)`. lookup returns 0 if not found. Then the store's dest isn't recorded if src_elt == 0.

So I need the store's SRC to not be in the table. For a REG src (temp_v0), cse always has an entry for a register (registers are always in the table with their qty). Actually `lookup` for a REG finds the register's quantity entry — always present. So src_elt != 0 for a reg src.

For a SUBREG src `(subreg:QI (reg:SI) 0)`, cse's lookup may find it if the subreg was simplified. It was recorded (forwarding happened), so found.

To make lookup return 0: the src must be a complex expression not in the table. E.g., a fresh arithmetic expression. But cse inserts the src of each insn into the table... Actually `insert` is called for the src in `cse_insn`? Let me check — the dest is inserted, and the src is looked up. If the src isn't found, it's still not inserted as such? Hmm, cse's design: each SET's src is looked up; the dest is inserted. So an expression appears in the table only via being a dest of some insn.

So if the store's src is an expression that is NOT the dest of any previous insn, lookup returns 0!

In our case, the store's src is `(subreg:QI (reg 75) 0)`. The reg 75 is a dest of the subu insn, so it's in the table. The subreg of it — `lookup` of a SUBREG: cse's `lookup` hashes the subreg; the entry might exist because when reg 75's value was inserted, cse also created lowpart entries? Line 7372: "If we have (set (subreg:m1 (reg:m2 foo) 0) (bar:m1)), ... make that equivalence as well". Hmm, that's for dests.

Actually, the store's src `(subreg:QI (reg:SI 75) 0)` — cse's `fold_rtx` may replace it with a QImode reg via `gen_lowpart_if_possible`, creating `(reg:QI 75)`? Then lookup finds reg 75's QI entry.

Hmm.

What if the store src is a complex expression like `(plus (reg) (const))` that isn't a dest? For example:
```
*(u8*)(arg0+6) = (u8)(temp_v0 + 0);  // combine simplifies
```
combine runs BEFORE cse1? The pass order: combine runs after cse1? Let me check: in gcc 2.7.2, the order is cse (cse1), then combine? Actually `rest_of_compilation`: cse, then jump_optimize, then combine? Let me recall: cse1 → ... → combine → ... → cse2? The dumps list `.cse`, `.combine`, `.cse2` — so cse1 runs before combine. So at cse1 time, `(u8)(temp_v0 + 0)` is `(subreg:QI (plus:SI (reg) (const_int 0)))`. The front-end might fold +0 away.

What about `(u8)(temp_v0 ^ 0)`? folded.

What about a real computation: `(u8)(temp_v0 & 0xFF)` → `(subreg:QI (and:SI (reg) (const 255)))`. At cse1 time, the AND is not folded (combine later). The store src is this AND expression, which is not the dest of any previous insn → lookup returns 0 → store NOT recorded → reload stays lbu!

And combine (after cse1) will simplify `(subreg:QI (and:SI (reg) 255))` into `(subreg:QI (reg))` for the store, so the final asm still has `sb v0,6(s0)`.

But wait — will the extra `andi` appear in the final asm? Combine should remove it since sb only uses the low byte. Let me test!

Also, the value temp_v0 is used for temp_v1 = -(temp_v0 & 0xFF) — the andi there is separate.

So variant w11:
```
*(u8 *)((u8 *)arg0 + 6) = (u8)(temp_v0 & 0xFF);
```
Let me test. This is a real-C move (an explicit mask), arguably not a lever.

Let me also try `(u8)(temp_v0 | 0)`, `(u8)(temp_v0 ^ 0xFF ^ 0xFF)`.

Let me test w11.

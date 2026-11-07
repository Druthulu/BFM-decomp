---
ts: 2026-11-06T11:49:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MJB0KHfLeDceKU9RyS9H
---
Neither helped. The do-while doesn't split the EBB here (or cse still forwards).

Let me think. The store `*(u8*)(arg0+6) = (u8)temp_v0;` then `temp_v0 = *(u8*)(arg0+6);`. cse's store forwarding.

Alternative real-C: make the second read not obviously the same address. E.g.:
```
u8 *p6 = (u8 *)arg0 + 6;
*p6 = (u8)temp_v0;
temp_v0 = *p6;
```
cse would still forward through p6.

What if the reload uses a different base expression? cse tracks memory by address; if the address expressions are equal it forwards.

What if the store is via a pointer that cse can't prove equals the load address? E.g., store via `((u8 *)arg0)[6]` and load via `*(u8 *)((u8 *)arg0 + 6)` — same RTL.

Hmm. What about making the reload volatile? That's a lever (barrier-like). Not allowed.

What about an intervening function call? That would change the code (target has no call there).

What about making temp_v0's type u8? If `u8 temp_v0`, then the reload would be `lbu` and the stored value... Let's think: 
```
u8 temp_v0;
temp_v0 = *(u8*)(arg0+6) - temp_a0;  // int promotion, assigned to u8
```
Hmm, `*(u8*) - temp_a0` is int; assigning to u8 truncates → andi 0xff, stored. Then `temp_v0 = *(u8*)(arg0+6)` reload.

But the target computes `temp_v0 = *(u8*)(arg0+6) - temp_a0;` as s32 (subu), then `temp_v1 = -(temp_v0 & 0xFF)`, and `sb v0,6(s0)` (store low byte). So temp_v0 is s32.

Alternative: store through a separate u8 variable:
```
u8 storeval = (u8)temp_v0;
*(u8*)(arg0+6) = storeval;
temp_v0 = *(u8*)(arg0+6);
```
cse might forward storeval, but the reload is `lbu`. cse forwards the stored value (storeval) into the load → temp_v0 = storeval (u8, zero-extended) → no lbu. Same.

Hmm. What if the store happens through a *different* alias, e.g., store as s16? No, target stores sb.

What if the reload is done via a pointer variable assigned from arg0? `u8 *q = (u8*)arg0;` then `q[6] = ...; temp_v0 = q[6];` — same.

The real original C must have had something that prevented forwarding. Maybe the original code is:
```
temp_v0 = *(u8 *)(arg0 + 6) - temp_a0;
temp_v1 = -(temp_v0 & 0xFF);
*(u8 *)(arg0 + 6) = temp_v0;
temp_v0 = *(u8 *)(arg0 + 6);
```
and cse in the ORIGINAL also forwards? But the target shows lbu, so no forwarding. Why not?

Maybe because the store's value `temp_v0` (s32) is stored as QImode; cse records the stored value as `(subreg:QI temp_v0 0)`, and the reload is `(zero_extend:SI (mem:QI ...))`. cse's `cse_insn` can forward if the stored value's mode matches. `sb` stores a QImode subreg. The load is QImode zero-extended. In gcc 2.7.2 cse, forwarding a store into a load requires the same mode and the value to be a register. Here the stored value is `(subreg:QI (reg:SI v0) 0)`, and the load result is `(zero_extend:SI (reg:QI ...))`. cse might not equate them because the stored value is a SUBREG, not a REG.

But in my w1, it DID forward (andi v0,v0,0xff). Hmm, so cse created an equivalence.

Wait, in mine the result was `andi v0,v0,0xff` at line 12 — that's not exactly forwarding the store; it's cse knowing that the byte at (arg0+6) equals the low byte of v0, so the reload `(u8)*(arg0+6)` becomes `v0 & 0xff`. That's the "cse-store-forward" wall.

So why doesn't the original forward? Maybe the original's store was `*(u8*)(arg0+6) = temp_v0;` without the `(u8)` cast. Then the RTL store is `(subreg:QI (reg:SI v0) 0)` — same thing.

Hmm, or maybe the original had the reload BEFORE the store? No, target order is store then reload.

Wait — maybe the target's lbu is NOT a reload of the store but a genuinely different value... no, it's the same address.

Alternatively, maybe the original code used a pointer variable for the reload that cse treats as a different address because it's loaded from memory? E.g., `u8 *p = ...;` no.

Hmm, let me reconsider: maybe the original did:
```
temp_v0 = *(u8 *)((u8 *)arg0 + 6) - temp_a0;
temp_v1 = -(temp_v0 & 0xFF);
*(u8 *)((u8 *)arg0 + 6) = (u8)temp_v0;
...
temp_v0 = *(u8 *)((u8 *)arg0 + 6);
```
with something in between that invalidates cse's memory knowledge? Like the `*(u8*)(arg0+5) = ...` store? No, different address.

Wait, in my w1 the order is: store at +6, then reload, then store at +5. The target also: sb +6, lbu +6, sb +5. So nothing in between.

Unless the original had a call or a `volatile` between them. But the target shows them adjacent.

Hold on. Maybe cse's behavior depends on the *declaration* of temp_v0. In my w1, temp_v0 is s32 and I wrote `(u8)temp_v0` in the store. cse recorded `(subreg:QI v0 0)`. 

What if the store value is not a register but a memory/expression? E.g., if I inline the computation:
```
*(u8*)((u8*)arg0+6) = (u8)(*(u8*)((u8*)arg0+6) - temp_a0);
```
Then the stored value isn't a simple reg, and cse can't forward. But that changes temp_v0's definition and temp_v1's use of temp_v0. Let me think about the target:
- temp_v0 = byte[6] - temp_a0 (s32)
- temp_v1 = -(temp_v0 & 0xFF)
- byte[6] = (u8)temp_v0
- temp_v0 = byte[6]  (reload, lbu)

If I write:
```
temp_v0 = *(u8*)(arg0+6) - temp_a0;
temp_v1 = -(temp_v0 & 0xFF);
*(u8*)(arg0+6) = (u8)temp_v0;
temp_v0 = *(u8*)(arg0+6);
```
that's w1.

To avoid forwarding, make the stored expression something cse can't equate: e.g., store `(u8)(temp_v0 & 0xFF)` — same value. Or store `(u8)temp_v0 + 0` — changes to addiu.

What if the store value is a separate u8 variable that is set from temp_v0, and the reload reads it back:
```
u8 b = (u8)temp_v0;
*(u8*)(arg0+6) = b;
temp_v0 = *(u8*)(arg0+6);
```
cse: store value = (subreg:QI b). Load → b. Since b is a QI reg, cse CAN forward → `(zero_extend:SI b)` → andi. Hmm.

What if the store uses a computed expression that cse doesn't simplify to a reg, e.g. `*(u8*)(arg0+6) = (u8)(temp_v0 - 0);`? combine would simplify.

Hmm.

Let me look at the actual mechanism in the target. Perhaps the original used `temp_v0 = *(u8 *)((u8 *)arg0 + 6);` where the load is NOT the same as the store because the store wrote a *different* variable's value. In the target, the store `sb v0,6(s0)` stores v0 = temp_v0 (the s32). The reload `lbu v0,6(s0)` loads the byte. If the store value is a SUBREG of an SImode reg, cse in gcc 2.7.2 might not forward because it only forwards when the stored value is exactly a register of the load's mode. A SUBREG isn't. But my w1 DID forward — maybe because combine/cse simplified `(u8)temp_v0` to `(subreg:QI (reg:SI))` and then cse's `record_jump_equiv`... 

Actually, wait: maybe my w1's `andi v0,v0,0xff` isn't store-forwarding but something else. Let me check the cse dump for w1 to see what happened.

Let me use hdump for w1 and look at the cse output. But that takes time. Alternatively, let me look at the .cse dump around the store/load.

Actually, let me think about a simpler approach: the target's lbu could be reproduced if the compiler doesn't know the store happened — e.g., if the store is through a `volatile`-less pointer but the load is through a differently-typed pointer that cse treats as a different memory reference? cse tracks memory by address and alias set. `(u8*)arg0 + 6` for both. Same.

What if the reload is through `*(s8*)` vs store `*(u8*)`? Same address, different mode — cse might still forward with a sign_extend.

Hmm.

Let me try a different angle: maybe the original had the reload FIRST (before the store) and the store after — no, target order.

Let me check the cse dump to understand exactly what cse does in w1. Let me run hdump.

Actually, more efficient: try a batch of variants and see if any avoids the forward:
1. store value via u8 var `b`.
2. store `(u8)(temp_v0 & 0xFF)`.
3. reload via `(s8 *)` cast.
4. reload via a `u8 *p = (u8*)arg0 + 6;` pointer.
5. store via `u8 *q = (u8*)arg0 + 6;`.
6. reorder: store at +5 before the reload.
7. declare temp_v0 as u8? no.
8. use `(u8)*(u8*)` — same.
9. store then reload through `((u8*)arg0)[6]`.
10. insert a dummy store to another field between (changes code).

Wait — idea: what if the store is `*(u8 *)((u8 *)arg0 + 6) = temp_v0;` WITHOUT the (u8) cast? Then the RTL store value is `(subreg:QI (reg:SI temp_v0) 0)`. Same.

Hmm, but maybe with the cast the front-end emits `(subreg:QI (reg:SI))` and cse handles it; without the cast, the store is a `set (mem:QI) (reg:SI)` with a mode mismatch, which gcc represents differently (a paradoxical subreg) and cse might not forward. Let me try removing the cast!

Actually in C, assigning an s32 to a u8 lvalue truncates; the front-end emits `(subreg:QI (reg:SI) 0)`. Same either way. But maybe not.

Let me look at the cse dump for w1 to be precise. It's the fastest way.

Let me run hdump for w1 and grep the cse output around D_80120216... wait, the address is (arg0+6) via a register, not a symbol. The cse dump would show (mem:QI (reg...)). Hard to grep.

Alternative: compare the RTL of orig (pinned+barrier) and w1 around the store. In orig, the barrier is an asm; in w1, no barrier.

Hmm, let me just try variants. Let me write w4-w9 with different spellings and score.

Variant w4: no cast in the store:
`*(u8 *)((u8 *)arg0 + 6) = temp_v0;`
Variant w5: store via u8 var b.
Variant w6: reload via `*(s8 *)` cast into s32: `temp_v0 = *(s8 *)((u8 *)arg0 + 6);` — would give lb (sign) not lbu. Target lbu. No.
Variant w7: pointer vars.
Variant w8: `temp_v0 = (u8)*(u8 *)((u8 *)arg0 + 6);` — same.
Variant w9: swap: store at +5 before reload.

Let me also try a `do{}while(0)` around the store AND reload together.

Let me generate and score.

---
ts: 2026-11-06T16:56:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LmRhznurGGRvpER6GT5C
---
The s-launder residual: without it, the compiler re-materializes `&D_800AE620` at each field load (`lui v1,0x0; lw v1,0(v1)` etc.) instead of keeping the base in $a2. So the s-launder forces the base pointer into a register (a2) so the loads use displacements.

Real-C to keep the base in a register: use a local pointer `s = &D_800AE620;` and read `s->w[i]` — that's already the source! The compiler still rematerializes because cse decides the address is constant. The launder `asm("" : "=r"(s) : "0"(s))` ties s to itself, making it a real value.

C0414's dead-reset idea: `s = &D_800AE620; ...; s = 0;`? That would kill cse's equivalence but the loads happen before the reset. Hmm, cse processes the block forward; the equivalence for `s` is killed by the second set, but the loads are BEFORE it, so they still use the equivalence.

The problem is that cse doesn't keep `s` in a register across the loads — it rematerializes the *address* at each load because the address is a constant (SYMBOL_REF). To prevent that, the pointer must not be a known constant... but it is.

Alternative real-C: read the fields through a pointer that cse can't fold, e.g., via a `volatile`? no.

Hmm, but wait: with the launder, the base is in $a2 and the loads are `lw v1,0(a2)` etc. Without it, `lui v1; lw v1,0(v1)`. The difference is 6 extra insns.

What real-C makes gcc keep the base? If `s` is a *parameter* or a value whose address isn't constant... The address IS constant (D_800AE620). cse's `find_best_addr`/`cse_insn` may replace the address with a register if the address expression is in the hash table. Hmm.

Actually, the shipped source uses the launder `asm("" : "=r"(s) : "0"(s))` to force `s` into a register. Real-C alternative: make `s` a value that's not a compile-time constant. E.g., `Blk20 *s = &D_800AE620;` — the address is still constant. What if we pass it through a function? no.

What if we use an array index: `((Blk20*)&D_800AE620)->w[i]`? same.

Hmm, what about the classic: `s = (Blk20 *)((u8 *)&D_800AE620 + 0);`? The +0 might not fold, producing an addiu... but that's 1 insn, not 6. And cse might still fold.

What about making the loads volatile? changes bytes.

Alternatively: maybe use a struct assignment `m = D_800AE620;` instead of the hand-expanded copy! The header comment in item 2 mentioned a §48 STRUCT ASSIGN vs hand-rolled temp copy. Here the hand-expanded copy exists "so no block move". But maybe with the s-launder gone, a struct assignment is the natural C. Let me try `m = D_800AE620;` (one statement) and see if it matches the target's 6-lw/6-sw block. The target's copy block:
```
e28 lui a2, D_800AE620
e2c addiu a2
e30 lw v1,0(a2); lw a0,4(a2); lw a1,8(a2); sw v1,32(sp); sw a0,36(sp); sw a1,40(sp)
e48 lw v1,12(a2); lw a0,16(a2); lw a1,20(a2); sw ... 44,48,52
e60 lw v1,24(a2); lw a0,28(a2); sw 56,60
```
That's a 32-byte copy (8 words) with the base in a2 and 3 carriers (v1,a0,a1) — exactly move_by_pieces. A plain `m = D_800AE620;` (struct assignment) would emit exactly that! The header comment says "hand-expanded so no block move" — but maybe that was needed with the pins. Let me try `m = D_800AE620;` and remove the hand-expanded block.

Let me test:
- z01: replace the whole hand-expanded block (with the s-launder and the keepalive) with `m = D_800AE620;`, keeping the q dead-reset.
- z02: same but keep the keepalive? Not needed if the block is gone.

The pins t0/t1/t2 would be unused → remove them (they're other-kind levers, allowed to be removed).

Let me construct z01:
```
    m = D_800AE620;
```
replacing the block from `    /* m = D_800AE620; ...` through the closing `}` after the keepalive.

Then keep the q dead-reset (y01's q=0).

Let me test.

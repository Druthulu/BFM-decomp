---
ts: 2026-11-06T09:15:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gaZEQ5ByiHzA7d3Oyot8
---
Difference at 5b4-5c8: target:
```
5b4 beqz v0,5f4
5b8 li a0,11        (delay slot!)
5bc addiu v0,s0,-310
5c0 sltiu v0,v0,70
5c4 beqz v0,5f8
5c8 move a1,zero    (delay slot)
5cc lui a1,...
```
mine:
```
5b4 beqz v0,5ec
5b8 addiu v0,s0,-310
5bc sltiu v0,v0,70
5c0 beqz v0,5ec
5c4 li a0,11        (delay slot)
5c8 lui a1,...
```
So the `li a0,11` (the argument for the 11-call) is placed differently: target hoists it into the first beqz's delay slot (5b8), mine puts it in the second beqz's delay slot (5c4). This is sched/dbr ordering — related to the register pressure? Hmm, actually target also has `move a1,zero` at 5c8 in the delay slot of the second beqz (from the else branch of the second if: `func_801F0E24(11,0,0)`), then the taken path continues.

Hmm, so in target the source's second if block is:
```
if (func_801F0E0C(p[57],13,24)) {
    t2 = ...;
    if (t2) {
        func_801F0E24(11, D_801F217C, func_801F0F2C);
        goto Lcont;
    }
}
goto Lshared;
Lzero: ...
Lshared: func_801F0E24(11,0,0);
Lcont: ...
```
The `li a0,11` is common to both the t2 path and Lshared path. Target places it early (5b8, in the first beqz's delay slot), mine places it at 5c4.

This is a scheduling difference likely caused by register allocation (v0/v1 swap) affecting... hmm, actually the dbr delay slot fill depends on insn order from sched1.

OK. This is a rich item. Let me consider real-C moves to get res in v0 (target) rather than v1.

Target tail: flg in v1, res in v0. Mine: flg in v0, res in v1. Both pseudos live in the tail block. Allocation order in local-alloc: by qty priority. res is used by the asm keepalive → refs maybe higher; flg has 2 refs. Hmm, but mine gives v0 to flg and v1 to res. Wait, actually the `lui v0; lw v0` in mine is flg (D_801F84AC load), and res in v1. In target, flg is v1 and res v0.

The declaration order in orig: `res` is declared last (after flg? actually the pin decl is first among locals: p, v, t2, flg, res(pin)). In my p2.c I replaced the pin line with `s32 *res;` which keeps res last. Hmm.

qty allocation order: local-alloc allocates in order of qty number? Or priority (refs/live length)? From moves.md: "lreg-qty-priority local-alloc qty priority (refs/live length)". res has refs: set 0, set &D, use in asm = 3; flg: set from load, use in test = 2. So res higher priority → gets v0 first. But mine gave res v1! Unless... wait, maybe I misread: in mine, `lui v0; lw v0` = load D_801F84AC into v0 = flg. `move v1,zero` = res=0. So flg got v0, res got v1. Hmm, so res priority lower?

Live lengths: res is live from `res=0` to asm; flg live from load to the beqz. Similar.

But maybe the key is that v0 is *reserved* for the return register use? No, void function.

Hmm, alternatively local-alloc allocates in *reverse* qty order or by regs_live... Let me try simple real-C permutations:
1. Move `flg = D_801F84AC;` before `res = 0;` (statement order).
2. Declare res before flg.
3. Make flg s32 and use `if (flg)` vs `if (flg != 0)`.
4. Remove flg entirely: `if (D_801F84AC != 0) res = ...` — changes codegen (load into temp).
5. Use `res = 0; if (D_801F84AC) res = ...`.

Let me try a few.

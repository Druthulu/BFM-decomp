---
ts: 2026-11-06T16:38:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CcIg0hoEejWjzE4utNvP
---
In win.c: 72 = param pseudo (a1), 73 = self (a0). Uses: then uses 72 (a1)?? and else uses 73 (a0). Hmm.

Wait — the disposition 72 in 5 (a1), 73 in 4 (a0). And then-arm uses a1 = 72, else uses a0 = 73. So the source `self` was split: in the then block, uses refer to 72 (param), in else to 73 (self). That's cse rewriting self→param in the then block? Or the opposite.

Interesting. In the pinned orig, only 73 (self) exists as a global pseudo and it's in a1, used in both arms.

So the presence of the *param pseudo* 72 is what creates the split. Why does expand create a param pseudo 72 in win.c but not in orig.c? In orig.c, `self = arg0 + zr`: the addition uses arg0 as a hard reg operand directly? expand_binop may copy the param to a pseudo first... Hmm, but in orig only 73 exists.

Wait, in orig, 73 = self is set from a0 (the hard reg) directly: `(set (reg/v:SI 73) (reg:SI 4 a0))`. No param pseudo.

In win.c, `self = arg0;` produced 72 = a0 then 73 = 72. Why two? Because a simple assignment `self = arg0` where self is a VAR_DECL: expand creates a pseudo for the *parameter* (72) at function entry? Hmm, parameters are expanded at entry via assign_parms which creates pseudo 72 for arg0 (since it's used). In orig, the parameter is used in the addition... also should create a param pseudo.

Unless: in orig, the parameter is used only in `self = arg0 + zr`, and expand_binop with a hard reg operand uses it directly (no pseudo). Then why does win.c create 72? Because `self = arg0` calls store_expr → expand_expr(arg0) returns a0 hard reg, then stores into self's pseudo (73). That's ONE insn `(set 73 a0)`, no 72. But the dump shows 72 exists with `(set 72 (reg a0))`.

Hmm, the rtl dump of c1 earlier showed insn 4 `(set 72 (reg a0))` and insn 11 `(set 73 (reg 72))`. So expand created 72 = a0 at entry (parameter expansion) and then 73 = 72 for self. Why would `self = arg0` produce a copy from a pseudo rather than the hard reg? Because after assign_parms, arg0's pseudo is 72, and uses of the param refer to 72.

In orig, why no 72? Let me check o1's rtl dump.

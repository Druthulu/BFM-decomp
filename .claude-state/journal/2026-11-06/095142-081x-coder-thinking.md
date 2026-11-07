---
ts: 2026-11-06T16:51:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1OyGuS4E0aEZwVac3rmJ
---
In the orig cse2, at site 1: reg 86 = symbol, then reg 86 = asm (invalidates). At site 4 (group B, line 587): reg 101 = symbol (fresh pseudo). So each site's m is a fresh pseudo.

So cse would have merged site 4's constant into 86 if 86 still held it. The asm kills it.

Now, in the win/x1 version, cse merged sites into one pseudo. We need each site's constant to be a separate pseudo.

Key insight: cse merges *registers with known constant values* only if the register is still valid AND the cost favors it. Here the cost favors the register (symbol = 2 insns). If we could make the constant cheaper (cost ≤ 1), cse might prefer the constant. CONST_COSTS: SYMBOL_REF_FLAG(symref) ? 1 : 2. SYMBOL_REF_FLAG is set for symbols in small data / "const" sections? Let me check when mips sets SYMBOL_REF_FLAG.

In mips.c, SYMBOL_REF_FLAG is set for symbols... let me grep.

---
ts: 2026-10-22T11:35:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_rvidfYF36UYTOJmzGktc
---
Not found in the RTL dumps at all. So the magic multiply is generated LATE — in `expand` (the division expansion happens in expand, generating a `mult` with a constant)... Hmm, but the constant should appear as `(const_int 1717960703)`.

Let me grep for "multsi3" or "divsi3" in the dumps, and for "6667".

Hmm — maybe the constant is split into `lui`/`ori` at the RTL level and the value appears as 0x6666 and 0x6667 in the dump. Let me grep for "0x6666" in the .i files (I did: 0 matches). Hmm.

Maybe the division is expanded using a `multsi3` libcall/pattern, and the constant is inside a `parallel` with `const_int`. Let me grep for "const_int 1717960703" — I did grep 1717960703 and got 0.

Hmm! Maybe the dumps only cover part of the file? The dumps are for the whole TU. The function is in there.

Let me grep for the function's name in the cse2 dump and check the region for the mult.

Alternatively, maybe the division uses `divsi3` (a libcall) and the constant comes from `sdivsi3`... no.

Let me search the .s file for the actual assembly of func_801832A8 to confirm and then look at the .i for "multsi3".

Hmm, let me try grep "multsi3" in the cse2 dump.

Actually, maybe the issue is that the dumps I made are of the TU with the function, but the "0x6666" constant is created by `split_constant` in reload.c (the pseudo is set by a `lui`+`ori` pair created by reload's `reload` when the constant doesn't fit in an immediate). So the RTL pseudo would be set by `(set (reg) (const_int 1717960703))` — hmm.

Wait, but for `mult`, the operand is the constant directly: `(mult:SI (reg:SI 167) (const_int 1717960703))`. That should show up in the RTL. Unless GCC expanded the division using a `multsi3` insn pattern with the constant inside.

Let me grep for "multsi3" in cse2.

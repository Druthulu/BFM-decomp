---
ts: 2026-10-21T23:42:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_hZVqTtma7eIEAbCnV7il
---
Now I have the full ROM asm for func_8014C308 (39 ins):

```
 0  lhu  v0,0(a1)
 1  nop
 2  beqz v0,6abc        ; ret 0
 3  move v0,zero
 4  lw   v0,88(a1)
 5  nop
 6  beqz v0,6abc
 7  move v0,zero
 8  lhu  v0,94(a1)
 9  nop
10  beq  v0,a2,6ab8
11  li   v1,0x8000
12  lw   v0,92(a1)
13  nop
14  andi v0,v0,0xc100
15  bne  v0,v1,6abc
16  move v0,zero
17  lh   v0,174(a1)
18  andi v1,a3,0xffff
19  and  v0,v0,v1
20  bnez v0,6ab8
21  li   v1,9
22  beq  a2,v1,6abc
23  li   v0,1
24  li   v1,17
25  beq  a2,v1,6abc
26  li   v1,41
27  beq  a2,v1,6abc
28  li   v1,10
29  beq  a2,v1,6abc
30  nop
31  lw   v0,376(a0)
32  nop
33  xor  v0,v0,a1
34  j    6abc
35  sltu v0,zero,v0
36  move v0,zero
37  nop
38  nop
```
Interesting: the "return 1" path is at 6abc?? Wait, branches to 6abc = "return 0" path? Let's see: 6abc is +0x94 = the block at ins 36-38 (move v0,zero; nop; nop) → return 0. And 6ab8 = +0x90 = ins 34-35 (j 6abc; sltu v0,zero,v0) → the "return != 0" path: v0 = (v0 != 0) → 1.

So the "return 1" arms branch to 6abc?? Hmm: `beq a2,v1,6abc` — that goes to the return-0 block?! That can't be right semantically.

Wait, maybe the block at 6abc is the return block that returns v0 (the value in v0). Let's re-read: ins 36 `move v0,zero` — that's setting the return value to 0 — that's the "return 0" block. And ins 34-35: `j 6abc; sltu v0,zero,v0` — the delay slot of the jump computes v0 = (v0 != 0), then jumps to 6abc which returns v0. So the block at 6abc is a shared "return v0" block! But it contains `move v0,zero` at 36? That would overwrite.

Hmm, unless the return block at 6abc is: ins 36 `move v0,zero` is the "return 0" case; and there's a separate return path where v0 already holds 1. But both branch to 6abc...

Wait: look at ins 2: `beqz v0,6abc` then ins 3 `move v0,zero` in the delay slot → so the branch is taken when v0==0 and the delay slot sets v0=0 → returns 0. The fallthrough path continues. So 6abc = the "move v0,zero; nop; nop" block → return 0.

But then `beq a2,v1,6abc` (arg2 == 9 → return 1) would return 0?! Semantically wrong... unless the ROM code is different from the C's semantics. Hmm, wait. Let's re-read the source:

```c
if ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0) {
    v0 = 1;
    v1 = 9;
    if (arg2 == v1) return v0;
    ...
    return *(s32 *)((u8 *)arg0 + 0x178) != arg1;
}
return 0;
```
So when arg2==9 → return 1. In the ROM: `beq a2,v1,6abc` where 6abc is the return-0 block?? That doesn't match. Unless 6abc is actually the block that returns v0 where v0 was set to 1... but ins 36 `move v0,zero` sets v0=0.

Hold on. Let me re-read the block layout. ins 34 `j 6abc`, ins 35 `sltu v0,zero,v0` (delay slot), ins 36 `move v0,zero`, 37 nop, 38 nop. Address of ins 36 = 6ab8+? Let's compute: func starts at 0x8014C308 (6ab8 in the objdump's local labels? The tool prints addresses like 6ab8 relative to some base). Actually the labels 6abc/6ab8 are absolute-ish addresses in the object's symbol space (e.g. 0x8014C308 → "6ab8"?). Hmm: the function label is `func_8014C308+0x90` for 6ab8 → 6ab8 = 0x8014C308+0x90 = 0x8014C398. And 6abc = 0x8014C39C = +0x94.

So block at +0x90 (ins 34,35) and block at +0x94 (ins 36,37,38).

ins 34 is at +0x88? Let's map: ins 0 at +0x00, each ins 4 bytes: ins n at +0x4n. ins 34 → +0x88, ins 35 → +0x8c, ins 36 → +0x90, ins 37 → +0x94, ins 38 → +0x98.

Hmm! But the labels say 6abc = +0x94 → ins 37. And 6ab8 = +0x90 → ins 36.

So: branch to 6abc (+0x94) = ins 37 (nop) — hmm, that doesn't look like a block start either.

Let me recompute: the target listing's addresses: `beqz v0,6abc <func_8014C308+0x94>`. So 6abc = +0x94 = ins 37 (since ins 0 at +0). Hmm, ins 37 is a nop. That means the branch goes to +0x94 where ins 37 (nop) and ins 38 (nop) are... and the delay slot of the branch has `move v0,zero`.

Wait, I mis-assigned: the `move v0,zero` after `beqz v0` is the DELAY SLOT of the branch (MIPS: branch delay slot). Yes! ins 2 `beqz v0,6abc` + ins 3 `move v0,zero` (delay slot). So the block at +0x94 (ins 37-38) is the return: `jr $ra; move v0,$2`? But we only see nop nop at 37,38... The `jr $ra` must be in there. Hmm, the target listing ends at ins 38 with nop nop. Let me look: ins 36 `move v0,zero`, 37 `nop`, 38 `nop`. Where's `jr $ra`?

Maybe the tool's insns_from_object stops before the epilogue? Or the epilogue is at 37: `jr $ra` with delay slot `move v0,$2`? The listing shows 37 nop, 38 nop.

Hmm, the masked comparison might strip `jr $ra`? Unlikely.

Let me reconsider the count: "mine 2 ins, target 39". The insert opcode was target[0:37] (37 ins) then "replace mine[1:2] target[38:39]" → so target has 39 ins total (0..38), and the last shown pair is mine[1] `move v0,zero` vs target[38] `nop`.

So target ins 37 = nop, 38 = nop. Hmm, so where's the return? Maybe the function's epilogue (jr $ra) is emitted as a separate "end" and the tool's extraction ends at the last instruction before... no.

Wait, maybe I mis-read: ins 36 `move v0,zero`, ins 37 `nop`, ins 38 `nop` — maybe the epilogue is:
```
34  j   6abc(+0x94)
35  sltu v0,zero,v0    (delay slot)
36  move v0,zero       <- this is the "return 0" case? 
37  nop
38  nop
```
Hmm, but 36 `move v0,zero` would be at +0x90, and 6ab8 = +0x90 → so the branch target 6ab8 points at ins 36 (`move v0,zero`)! And `bnez v0,6ab8` at ins 20 → jumps to ins 36 → move v0,zero → return 0. Yes! That's the "return 0" path.

And 6abc = +0x94 → ins 37 (nop) — the shared return block: ins 37 `nop`?? We need `jr $ra`.

Unless the epilogue is `jr $ra` at +0x94 with delay slot `move v0,$2`... but listing shows nop.

Hmm, maybe the tool's listing is of "the function's instructions" excluding the epilogue? Let me look at how insns_from_object works... Perhaps the object is a "tail.data.o" fragment and the function's epilogue lives in another section? Unlikely.

Let me just count instructions: target 39. Let me map addresses:
ins 0: +0x00 lhu v0,0(a1)
ins 1: +0x04 nop
ins 2: +0x08 beqz v0,+0x94
ins 3: +0x0c move v0,zero
ins 4: +0x10 lw v0,88(a1)
ins 5: +0x14 nop
ins 6: +0x18 beqz v0,+0x94
ins 7: +0x1c move v0,zero
ins 8: +0x20 lhu v0,94(a1)
ins 9: +0x24 nop
ins 10: +0x28 beq v0,a2,+0x90
ins 11: +0x2c li v1,0x8000
ins 12: +0x30 lw v0,92(a1)
ins 13: +0x34 nop
ins 14: +0x38 andi v0,v0,0xc100
ins 15: +0x3c bne v0,v1,+0x94
ins 16: +0x40 move v0,zero
ins 17: +0x44 lh v0,174(a1)
ins 18: +0x48 andi v1,a3,0xffff
ins 19: +0x4c and v0,v0,v1
ins 20: +0x50 bnez v0,+0x90
ins 21: +0x54 li v1,9
ins 22: +0x58 beq a2,v1,+0x94
ins 23: +0x5c li v0,1
ins 24: +0x60 li v1,17
ins 25: +0x64 beq a2,v1,+0x94
ins 26: +0x68 li v1,41
ins 27: +0x6c beq a2,v1,+0x94
ins 28: +0x70 li v1,10
ins 29: +0x74 beq a2,v1,+0x94
ins 30: +0x78 nop
ins 31: +0x7c lw v0,376(a0)
ins 32: +0x80 nop
ins 33: +0x84 xor v0,v0,a1
ins 34: +0x88 j +0x94
ins 35: +0x8c sltu v0,zero,v0 (delay slot)
ins 36: +0x90 move v0,zero
ins 37: +0x94 nop
ins 38: +0x98 nop

Hmm, so the function's last instructions are 3 nops? That's odd, but the ROM function might genuinely end with padding? Actually wait: MIPS functions end with `jr $ra; move v0,$2` (or nop). The listing shows ins 37 nop, 38 nop — where's jr?

Unless... the branch target +0x94 with the delay slot `move v0,zero` — i.e., the block at +0x94 IS the return block, and the epilogue `jr $ra` is at +0x98 = ins 38? But ins 38 shows "nop".

Hmm, maybe the tool's masked_word ignores/deletes some instructions? Or the object dump shows the epilogue as part of a "common" block?

Alternatively the ROM code ends with:
```
+0x94: jr $ra
+0x98: move v0,v0   (or nop)
```
and the tool prints mnemonic "nop" for `jr`? No.

Wait, maybe ins 37 "nop" is actually "jr $ra" and the tool's dump replaced it? Unlikely.

Hmm, let me reconsider: maybe the delay slot of the branch at +0x08 is `move v0,zero` (ins 3) — yes that's standard for `return 0`.

And what about the branches to +0x94: those are the "return v0" cases where v0=1 (from ins 23 li v0,1)? But ins 23 `li v0,1` comes AFTER ins 22 `beq a2,v1,+0x94`. So the branch at 22 (arg2==9) jumps to +0x94 — but v0 hasn't been set to 1 yet at that point! Unless v0 was set earlier... no, at ins 22 v0 holds the `and` result (v0 = lh & andi = 0 since we're in the ==0 branch). Hmm, v0 = 0 at that point.

Hmm! So `beq a2,v1,+0x94` with v0=0 → returns 0?! But the C says return 1.

Unless +0x94 block is NOT the return-0 block. Let's reconsider: maybe the function's epilogue is at +0x94: `jr $ra` (ins 37?) and the delay slot ins 38 `move v0,$2`? The listing shows "nop" though.

Hmm, wait. Maybe I mis-assume that the diff lines print in target order correctly with the address labels. The label "+0x94" might be the address of the instruction AFTER the delay slot? No, branch targets are instruction addresses.

Let me look at the tool's masked_word / insns_from_object to see whether it filters. Actually — maybe the function's epilogue is at +0x94 and consists of `jr $ra` + `move v0,$2`, but the object's function symbol boundaries cut it: the tool might extract instructions between the function label and the next symbol, and the ROM's ov function might be split... The ROM function func_8014C308 at 0x8014C308 — the next function starts at 0x8014C39C+? 39 ins = 156 bytes → 0x8014C308+0x9C = 0x8014C3A4. So the function ends at +0x9C.

So ins 36..38 = +0x90..+0x98: move v0,zero; nop; nop. And the branch target +0x94 = ins 37.

Hmm, what if the real ROM code at +0x90 is:
```
+0x90: jr $ra
+0x94: move v0,zero
```
No...

I think the tool's instruction extraction may normalize `jr $ra`? Let me check masked_diff.insns_from_object.

Actually — maybe the tool prints "nop" for instructions it can't disassemble? Let me look at the code.

Let me grep insns_from_object in tools/masked_diff.py.

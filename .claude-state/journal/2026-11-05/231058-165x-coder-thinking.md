---
ts: 2026-11-06T06:10:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gHx3azoS9IEPheP7PBbj
---
Still 67. The extra copy persists.

So q1 (using (s32)a0 directly) is the best at 11/64.

Let me look at q1's full asm and compare with the target to find the remaining issues.

q1's diff:
1. insn 9 `j 2958` vs target `j 295c` — a layout difference (mine is 4 bytes shorter overall).
2. The v1 pin: `lh a0,0(at)` vs `lh v1,0(at)`, and the subsequent register swap.
3. insn 50 `lh v0,256(a0)` vs `lh v0,256(s0)`.

Since mine is 64 ins and target 65, mine is missing one instruction. Which one? The target has both `lw v0,32(s0)` at 25 and... hmm, mine has `lw v1,32(s0)` at 19. Both have one lw.

Let me count: the diff shows "replace mine[25:28] target[25:29]" — mine has 3 insns, target 4. So target has one more: `lw v0,32(s0)` placed at 25 in the target vs mine's `lw v1,32(s0)` at 19. Hmm.

Let me just dump q1's asm and compare side by side.

Actually, let me think about the structure. The source:
```c
v1 = D_80184CA8[unk70];        // lh v1,0(at)
unkFE = (v1 & 0xF000) >> 12;   // andi v0,v1,0xf000; sra v0,v0,0xc; sh v0,254(s0)
unk100 = v1 & 0xF;             // andi v0,v1,0xf; sh v0,256(s0)
v0 = unk20;                    // lw v0,32(s0)
v0->unk12 = v1 & 0xFF0;        // andi v1,v1,0xff0; sh v1,18(v0)
v1 = unk100;                   // lh v1,256(s0)
if (v1 == 2) ...
```
Target asm:
```
28a0 lh v0,112(s0)     unk70
28a8 sll v0,v0,1
28ac lui at,...
28b0 addu at,at,v0
28b4 lh v1,0(at)       v1 = D_80184CA8[unk70]
28b8 nop
28bc andi v0,v1,0xf000
28c0 sra v0,v0,0xc
28c4 sh v0,254(s0)     unkFE
28c8 andi v0,v1,0xf
28cc sh v0,256(s0)     unk100
28d0 lw v0,32(s0)      v0 = unk20
28d4 andi v1,v1,0xff0
28d8 sh v1,18(v0)      unk12
28dc lh v1,256(s0)     v1 = unk100 (2nd)
28e0 li v0,2
28e4 bne v1,v0,28f8
```
Mine (q1) from the diff:
```
18 lh a0,0(at)         v1 = D_80184CA8[unk70] in a0
19 lw v1,32(s0)        v0 = unk20 in v1
20 andi v0,a0,0xf000
...
23 andi v0,a0,0xf
25 andi v0,a0,0xff0
26 sh v0,18(v1)
27 lh a0,256(s0)
29 bne a0,v0,...
```
So mine uses a0 for the loaded value and v1 for the unk20 pointer. Target uses v1 for the loaded value and v0 for the pointer.

The registers are rotated by one. Hmm.

Local-alloc: the loaded value (5 refs), the unk20 pointer (2 refs), the masks (locals). 

In the target, the loaded value is in $3 (v1) and the pointer in $2 (v0). So the pointer got the *better* register. Why? Because the pin forced the loaded value to $3, freeing $2 for the pointer.

Without the pin: the loaded value has more refs → higher density → gets $2. But mine has it in a0 ($4)! So the masks took $2 and $3.

Hmm: the masks are separate pseudos (`v1 & 0xF000` result, `v1 & 0xF` result, `v1 & 0xFF0` result). In mine, the mask results go to v0 ($2). Then the pointer to v1 ($3) and the loaded value to a0 ($4)?

Let me look at the lreg densities for q1. Let me dump q1.

Actually, let me think about how to get the target's allocation. The target: loaded value v1 ($3), pointer v0 ($2), masks v0/v1 (reused).

Hmm, the target's masks reuse v0 and v1 — the same registers as the values. So the masks are in the same registers as the sources (combine folds the andi into the same reg).

In mine, the masks go to v0 (a different reg from the source a0).

Hmm.

What if the source's variable names matter? The decompiled source uses `v1` and `v0` as variable names. gcc doesn't care about names.

Let me try declaring the variables in a different order, or splitting them.

Actually, let me try the simplest thing: declare the loaded value and the pointer as separate variables with different types, e.g.:
```c
s16 v1;   // the loaded D_80184CA8 value (s16)
s32 v0;   // the pointer
```
The target's `lh v1,0(at)` loads an s16. If v1 is s16, its qty size is 2 (lower density). Then the pointer (s32) might win $2... Hmm, but the masks need the sign-extended value.

Let me try: `s16 v1;` and adjust. The target's `andi v0,v1,0xf000` uses the loaded value directly (sign-extended). If v1 is s16, the uses need sign-extension (sll/sra) — extra instructions unless gcc knows.

Hmm, `D_80184CA8` is declared as what? Let me check. `lh v1,0(at)` suggests s16.

Let me look at the declaration: `extern s16 D_80184CA8[];` probably.

Let me try v1 as s16 and see.

Also, let me try swapping the order of the statements:
```c
v0 = ((Unkstruct_800B5CB8 *)(s32)a0)->unk20;   // load the pointer first
v1 = D_80184CA8[...];
...
```
Hmm, that changes the asm order.

Let me try a batch:
- s1: `s16 v1;`
- s2: move `v0 = unk20;` before the masks.
- s3: split the masks into separate temps.

Let me test s1 first.

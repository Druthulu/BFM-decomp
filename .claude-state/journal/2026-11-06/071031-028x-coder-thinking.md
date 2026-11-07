---
ts: 2026-11-06T14:10:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qOdAgcQd5w3z4qDTwu79
---
Now the mapping is clear:
- reg 160 = src (pointer, used 14 times)
- reg 161 = dst (pointer, used 15 times)
- reg 159 = n (used 9 times)
- reg 162 = ? wait — reg 162 is used in insn 391 `(set (mem:HI (reg/v:SI 162))` and 394 `(set (reg/v:SI 162) (plus ... 2))`. Hmm, that's the destination pointer at the store, but the store is `*dst = out` and `dst++`. Wait, but I thought 161 = dst. Let me re-read.

Actually:
- insn 391: `(set (mem:HI (reg/v:SI 162)) (subreg:HI (reg/v:SI 175) 0))` — this is `*dst = out`.
- insn 394: `(set (reg/v:SI 162) (plus (reg/v:SI 162) 2))` — dst++.
So reg 162 = dst.
- insn 397: `(set (reg/v:SI 160) (plus (reg/v:SI 160) 1))` — i++?? Wait, +1. Hmm, but 160 was src (the asm at 329 references reg 160). Let me re-check.

Hold on. insn 397 adds 1 to reg 160. And insn 400 adds 2 to reg 161. And insn 406 `slt reg 160, reg 159` — i < n. So reg 160 = i, not src!

But insn 329 asm references reg/v:SI 160. The src keepalive comment says "+2 refs on src". Hmm. Let me re-read the asm at 329:
```
(insn 329 365 341 (asm_operands ("") ("") 0[ 
            (reg/v:SI 160)
        ] 
```
So the asm at 329 takes reg 160. And reg 160 is the one incremented by 1 and compared in slt. So reg 160 = i? But wait, `i++` is +1 and `src++` is +2. Let me recheck:
- insn 394: reg 162 += 2 (dst++)
- insn 397: reg 160 += 1 — hmm i++ would be +1, src++ would be +2.
- insn 400: reg 161 += 2 (src++)

Wait, that gives: reg 162 += 2, reg 160 += 1, reg 161 += 2. So reg 160 = i (increment 1), reg 162 = dst (increment 2), reg 161 = src (increment 2). And insn 406 compares reg 160 (i) < reg 159 (n). And the store uses reg 162 (dst). And the load? Let me check the load insn uses reg 161.

But then insn 329 (asm) references reg 160 = i. Yet the source order is: src asm first, then i asm. Hmm, but in RTL the asm at insn 329 appears AFTER the mult insns (which are the r/g/b computations). That's odd. Actually the asm statements get scheduled? No, this is the .lreg dump which is after... hmm, -dl is the local-alloc dump, which is after global-alloc and sched1? Actually pass order: sched1 runs before local-alloc. The RTL here is post-sched1 (reordered). So the asm at insn 329 got scheduled late (it's an asm with a use of reg 160). Hmm.

Wait, but there are two asm statements, and here we see two asm_operands at relative 938 (insn 312) and 1073 (insn 329). Let me check insn 312.

Actually, hold on. The reg numbers: reg 160 gets +1 (i++), and reg 161 +2. Let me verify by looking at where reg 161 is loaded (lhu). Let me grep the block 14 RTL for reg 161.

Actually let me re-examine. The original C:
```
n = arg0->w * arg0->h;
i = 0;
src = arg0->data;
__asm__("" :: "r"(src));   // refs src
dst = src + n;
if (n > 0) {
  do {
    u16 px;
    ...
    __asm__("" :: "r"(i));  // refs i
    px = *src;
    ...
    *dst = out;
    dst++;
    i++;
    src++;
  } while (i < n);
}
```

In RTL:
- `i = 0` -> some insn set reg 160 = 0.
- `src = arg0->data` -> reg 161 = load.
- asm src -> use reg 161.
- `dst = src + n` -> reg 162 = 161 + 159.
- asm i -> use reg 160.
- `px = *src` -> load from reg 161.
- `*dst = out` -> store to reg 162.
- dst++ -> 162 += 2
- i++ -> 160 += 1
- src++ -> 161 += 2
- i < n -> slt 160, 159

But the asm at insn 329 references reg 160, and it appears after the mults. That would be the i asm scheduled late. And insn 312 references? Let me check relative line 938.

Hmm wait, actually the order in the source: src asm appears BEFORE `dst = src+n`, and i asm appears inside the do-while before `px = *src`. But in the lreg RTL, the insns got reordered by sched1. The src asm (insn 312?) and i asm (insn 329). Let me check insn 312's operand.

Let me read around relative line 938.

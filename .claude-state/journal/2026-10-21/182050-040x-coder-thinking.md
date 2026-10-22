---
ts: 2026-10-22T00:20:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_a7BFcASu8Ix2f6n9Tbm7
---
Now I have the full target. Key part (first block, lines 17-29):

```
9c3c: lw v0,100(s0)      ; unk64
9c40: lh v1,10(s0)       ; CAST_SIGN(s16,(s32)a0,0xA) = a0->field A
9c44: lh v0,10(v0)       ; *(s16*)(unk64+0xA)
9c48: lui a0,0x0
9c4c: lh a0,0(a0)        ; (s16)D_80126B62
9c50: addu v1,v1,v0      ; sum
9c54: subu v0,a0,v1      ; diff = D_80126B62 - sum
9c58: bgez v0,9c68       ; if (diff >= 0) goto 9c68
9c5c: slti v0,v0,16      ; delay: diff < 0x10
9c60: subu v0,v1,a0      ; diff = sum - D_80126B62
9c64: slti v0,v0,16
9c68: bnez v0,9d08       ; if (diff<0x10) -> return 1
9c6c: li v0,1
9c70: jal ...            ; else: continue to second part (fallthrough)
9c74: li a0,854
```

Interesting: in the first block there's NO launder (the source's first block has no asm). And the first block's structure: `bgez v0,9c68` — since diff>=0 branch goes to the shared slti/bnez. Note the delay slot of bgez computes `slti v0,v0,16` — the diff<0x10 test computed speculatively for the diff>=0 path... wait no, delay slot executes regardless: slti v0,v0,16 computes diff<0x10 for the *original* diff (before recompute). Then the else path (diff<0) recomputes diff and re-tests. So GCC duplicated the test. Fine.

Now the SECOND block (9cc4-9d04) has the two launders:
```
9cd8: subu v0,a0,v1
9cdc: bltz v0,9cf4
9ce0: slti v0,v0,16      ; delay
9ce4: bnez v0,9d08
9ce8: li v0,1
9cec: j 9d08
9cf0: move v0,zero
9cf4: subu v0,v1,a0
9cf8: slti v0,v0,16
9cfc: bnez v0,9d08
9d00: li v0,1
9d04: move v0,zero
```

Compare with the FIRST block (no launder), which has the pattern:
```
9c54: subu v0,a0,v1
9c58: bgez v0,9c68
9c5c: slti v0,v0,16
9c60: subu v0,v1,a0
9c64: slti v0,v0,16
9c68: bnez v0,9d08
9c6c: li v0,1
```

So the second block in the target has the "bnez/li/j/move" structure, which is what you'd get WITHOUT launder but with an extra `return 0` path. Hmm.

Now, my c1 (no launder) generated:
```
9cd8: subu v0,a0,v1
9cdc: bltz v0,9cec
9ce0: nop
9ce4: j 9cfc
9ce8: slti v0,v0,16
9cec: subu v0,v1,a0
9cf0: j 9cfc
9cf4: slti v0,v0,16
9cf8: move v0,zero
```
So in mine, the `if (diff<0x10) return 1;` was dropped!? Where's "li v0,1"? Hmm, mine has `j 9cfc` twice and one `move v0,zero`. So the return-1 path is missing entirely, and the slti results are dead.

That means GCC 2.7.2 miscompiled?? OR... my c1's structure differs semantically! Let me re-read c1:

```
s32 diff = *(s16 *)(s1 + 0xA) - sum;
if (diff >= 0) {
    if (diff < 0x10) {
        return 1;
    }
    return 0;
} else {
    diff = sum - *(s16 *)(s1 + 0xA);
    if (diff < 0x10) {
        return 1;
    }
    return 0;
}
```
Semantically fine. But GCC 2.7.2 generated code that always returns 0? That can't be.

Hmm wait, maybe I misread the disassembly of my candidate. Let me read the full dis1.log.

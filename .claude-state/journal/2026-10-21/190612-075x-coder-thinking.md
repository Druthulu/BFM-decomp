---
ts: 2026-10-22T01:06:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Omeqay5DBXVoV4wLRSh7
---
Target for func_8014FD54 (40 ins):

```
 0: addiu sp,sp,-40
 1: sw s0,32(sp)
 2: move s0,a0
 3: addiu a1,sp,16
 4: move a2,a1
 5: li v0,7
 6: sw ra,36(sp)
 7: sh zero,16(sp)
 8: sh zero,18(sp)
 9: jal func_80149290
10: sh v0,20(sp)
11: move a0,s0
12: addiu s0,sp,24
13: move a1,s0
14: move a2,s0
15: li v0,-24
16: sh zero,24(sp)
17: sh zero,26(sp)
18: jal func_80149290
19: sh v0,28(sp)
20: li a0,1
21: addiu a1,sp,16
22: jal func_80149290
23: move a2,s0
24: move v1,v0        <- the call result copied out of $2
25: beqz v1,+0x88
26: andi v1,v1,0x8000
27: beqz v1,+0x8c
28: move v0,zero
29: lbu v0,30(sp)
30: nop
31: xori v0,v0,0x15
32: j +0x8c
33: sltiu v0,v0,1
34: move v0,zero
35: lw ra,36(sp)
36: lw s0,32(sp)
37: addiu sp,sp,40
38: jr ra
39: nop
```
Wait, ins 38 = `jr ra`? The listing shows ins 37 `addiu sp,sp,40` and the replace at mine[1:2] target[39:40] = `nop`. So ins 38 = `jr ra` (not shown? hmm, the insert covered target[0:38] = ins 0..37, and target[38:39] = the replaced one = `nop`?? Hmm: "replace mine[1:2] target[39:40]" means target[39] = `nop` and mine[1] = `move v0,zero`.

So target ins 38 = `jr ra` and ins 39 = `nop` ✓.

So the target:
- `move v1,v0` at ins 24: the call result is copied from $2 to $3 (v1) — so the "result" variable is $3!
- ins 25: `beqz v1,+0x88` (the ret == 0 test → jump to ins 34 (the return-0 block: `move v0,zero` at 34? let me compute: +0x88 = 0x88/4 = 34 → ins 34 = `move v0,zero`; +0x8c = 35 → ins 35 = `lw ra,36(sp)`).
  Hmm: ins 34 `move v0,zero` then ins 35 `lw ra` — so the return-0 path is ins 34-39.
- ins 26: `andi v1,v1,0x8000` (the mask test on v1)
- ins 27: `beqz v1,+0x8c` (if the mask is 0 → jump to ins 35 = the epilogue with v0 = ? hmm, ins 35 is `lw ra` — so the return value in $2 is whatever it was: the call result? Hmm, the `move v0,zero` at ins 28 is in the delay slot of the beqz at ins 27 → so $2 = 0 ✓ (return 0).

So: ins 27 `beqz v1,+0x8c` with the delay slot ins 28 `move v0,zero` → return 0 ✓.
- ins 29: `lbu v0,30(sp)` (the byte at buf2+6)
- ins 31: `xori v0,v0,0x15`
- ins 32: `j +0x8c` with the delay slot ins 33 `sltiu v0,v0,1` → the return value = (byte != 0x15) ✓

So the target's structure matches orig.c:
```
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) {
    result = 0;
    if ((ret & 0x8000) != 0) {
        result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
    }
} else {
    result = 0;
}
return result;
```
Hmm, in the target: `move v1,v0` (the call result → v1 = $3), `beqz v1` (ret == 0 → return 0), `andi v1,v1,0x8000` (the mask on v1), `beqz v1` (mask == 0 → return 0), then the byte compare.

Note: the target has NO `move v0,zero` for the "ret == 0" path except in the delay slots ✓.

So the key register facts:
- the call result is copied to $3 (v1) — this is the "ret" variable.
- the RESULT (the return value) is computed in $2 (v0): `lbu v0,30(sp)`, `xori v0,v0,0x15`, `sltiu v0,v0,1` ✓.
- the return-0 paths set $2 = 0 (`move v0,zero` in the delay slots).

So the pinned variable in orig.c is `result` pinned to $2 — but in the target, the RESULT_DECL is $2 naturally (v0) and the "result" variable is a copy... hmm.

Actually in the target, the returned value is computed directly in $2 (the RESULT_DECL) — there's no separate "result" variable! The `result = *(u8*)(buf2+6) == 0x15` is computed into $2 and returned.

So the lever-free source should be something like:
```
int ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0 && (ret & 0x8000) != 0) {
    return *(unsigned char *)((char *)buf2 + 6) == 0x15;
}
return 0;
```
That's a much simpler shape! The `result` variable disappears; the return value is computed directly.

The notes said the best lever-free was 6 (P1/P2 = direct returns). Let me look at P1/P2 and their diff.

Let me score the existing candidates and get the P1 diff.

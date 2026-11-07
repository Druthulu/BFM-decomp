---
ts: 2026-11-06T16:27:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pcdTpf1DS3bB2bG0Q0C8
---
Now, let me build a lever-free body for item 1. The kinds = pin. So I must remove both `register s32 ret __asm__("$3")` and `register s32 m __asm__("$2")` pins. The result must score 0 with no pins.

Let me write a plain body and test. First, what does the plain body look like?

```c
void func_800CB118(s32 a0) {
    s32 sp20[2];
    s32 sp28;
    s32 ret;
    s32 m;

    func_80162FF4(a0, 0, 0x4000, 0);
    func_80162FC0((s32 *) a0);
    if (func_80146E98(a0) != 0) {
        func_80146CA0((void *) a0);
        return;
    }
    ret = func_801638A0((u8 *) a0, (s32) sp20);
    if (ret == 0) {
    } else if ((m = ret & 0x8000) != 0) {
        ((Unkstruct_80126B58 *)a0)->unk2C = 0;
        CAST_WIDTH(s32, a0, 0x24) = 0;
    } else {
        func_80146E90((s32 *) a0, 0x20);
        func_80146CA0((void *) a0);
        return;
    }
    ...
}
```

Let me just create the file and score it. Note: dt.sh takes an absolute path resolved via realpath; fine.

Wait — orig.c has `register ... __asm__` lines with `// !FAKE` comments. When removing them, need to also remove the comments. Yes.

Let me write the first candidate. Also note that `ret` and `m` declarations: with the pins removed, keep as `s32 ret; s32 m;`. But possibly the target needs m declared. Let's test.

Note the target: 
- `move v1,v0` after call. 
- `andi v0,v1,0x8000` 
- `beqz v1` for ret==0 test.

Actually wait. Look more carefully at the target order:

```
344: jal func_801638A0
348: addiu a1,sp,32     <- delay slot
34c: move v1,v0
350: beqz v1, 384
354: andi v0,v1,0x8000   <- delay slot
358: bnez v0, 37c
35c: nop
360: move a0,s0
...
```

So ret==0 → goto 384 (the common tail). ret != 0 → andi m. m != 0 → 37c (stores). else → 360 (call func_80146E90...).

So this is `if (ret == 0) {} else if (m...)`. Interesting: for ret==0, the flow goes to the tail; the `if(ret==0){}` empty branch collapses.

Now plain C. gcc 2.7.2 will produce:
- call; then pseudo for ret. Since `ret` used in test and in andi. Local-alloc: ret gets a hard reg. Copy preference from v0 return... The call result pseudo gets v0 in local-alloc via `reg_preferred`? Actually in gcc 2.7.2, the return value is copied from hard reg v0 into a pseudo with a `set` in the call's following insn? Let me look at what the build produces for the pinned version and the lever-free version.

Best: write the candidate and diff.

Let me do it.

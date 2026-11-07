---
ts: 2026-11-06T09:55:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PFwmG9r30FnFWjR7C39y
---
Some extractions are slightly off (CD314 tail, 801810E4 tail). Let me fix:

- CD314 ends at line 274 (`}` closing) per sed 270-282: lines 270 `}`, 271 barrier, 272 `((void...`, 273 `}`. Wait output showed:
```
    }
    __asm__ __volatile__("" ::: "a0");  // barrier
    ((void (*)(s32))func_80146C3C)(s0);
}
```
That's lines 270,271,272,273. Then blank 274,275,276,277 then func_800CD458 at 278. So range 229..273.

- 801810E4: 6375..6467? Output at 6460-6475:
```
6460        ((Unkstruct_800B5CB8 *)a0)->unk14 += 0x8000;
6461    }
6462    if (--((Unkstruct_800B5CB8 *)a0)->unk1C == -1) {
6463        func_801292C8((u8 *)a0);
6464    }
6465    CAST_SIGN(u16, (u8 *)a0, 0x2) += 1;
6466 }
```
Hmm need exact. Let me check line numbers precisely with grep -n for "^}" near.

Actually from the earlier output: `sed -n '6460,6475p'` printed starting "        ((Unkstruct_800B5CB8 *)a0)->unk14 += 0x8000;" — that's line 6460. Then 6461 "}", 6462 if, 6463 func, 6464 }, 6465 CAST_SIGN, 6466 "}", 6467 blank, 6468 blank, 6469 "extern void (*D_8018A250[])(void);", 6470 blank, 6471 void func_801813D4. So function is 6375..6466.

Let me fix both.

Also 80023BF0: 13479..13639? Earlier sed 13634-13642 showed:
```
13634    ((PTag_80023BF0 *)pkt)->len = 1;
13635    *(u32 *)(pkt + 4) = ...
13636    ((PTag_80023BF0 *)pkt)->addr = otab[idx].addr;
13637    D_800A5E60 = pkt + 0x40;
13638    otab[idx].addr = (u32)pkt;
13639 }
13640
13641
13642 s32 func_80024054
```
Good, 13479..13639 correct.

CF3E8: 282..475 correct? 475 is "}". Yes from grep.

Let me redo CD314 and 810E4.

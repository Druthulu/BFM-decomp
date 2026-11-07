---
ts: 2026-11-06T12:15:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_87mJvqZOF0Qwsr0EDrPE
---
The function func_80180BE0 is at lines 4630-4674 approximately. Let me extract it precisely. It ends at the closing `}` before the blank lines and `extern void func_80180D04`.

From the output:
```
4630 void func_80180BE0(s32 arg0, s32 arg1, s16 *arg2)
...
    }
}
```
Let me find the exact end line. The function body ends with:
```
    } else {
        out = arg2;
        __asm__ __volatile__("" : "=r"(out) : "0"(out));  // !FAKE: launder
        *(Blk12_80180BE0 *)out = *(Blk12_80180BE0 *)(v + idx * 12);
    }
}
```
Let me get the line numbers.

Also, I need to check the types Blk12_80180BE0 — defined elsewhere in the TU. Since this is a TU item (not a header), the body file is the function definition only, and the TU provides the types.

The kinds are keepalive,launder,pin — ALL three kinds must go. So the pins `w asm("$2")` and `out asm("$8")` must go too, plus the keepalive and the two launders.

That's a lot. Let me first extract the function and get the baseline.

Let me find the end line.

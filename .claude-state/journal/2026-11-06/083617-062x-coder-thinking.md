---
ts: 2026-11-06T15:36:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KaSHuCiuYY3VYo0lQzqq
---
Wait b4/b5: the block structure. Let me check the exact text. Lines 181-191:
```
            if (s0 != 0) {
                v0 = func_8004787C(...);
                *(u16 *)(s1 + 6) = ...;
                v0 = func_80047948(...);
                *(u16 *)(s1 + 0xE) = ...;
                /* comment */
            }
        }
        if (s0 != 0) {
```
After removing the asm, the comment remains. My replace target `'            }\n        }\n        if (s0 != 0) {'` should match. But for b4 I insert `v0 = 0;` before the closing `}` of the if — that's after the stores. OK.

Hmm, but b5 `s0 = v0;` after the if: v0 at that point is the result of func_80047948(...) (line 184-185), not the s0 value. That changes semantics! Remove b5. Let me fix.

Also b6/b7: `u16 s0` with `s0 = call(...) & 0x8000` — the andi target is 0x8000; u16 truncation is value-preserving. But `if (s0 != 0)` with u16 → promotes to int, fine.

Let me remove b5.

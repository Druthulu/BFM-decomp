---
ts: 2026-11-06T10:08:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_g3c2llOGWOjrZn24XRFu
---
The residual is exactly the 17-ins second-branch dead computation. The only other mismatch is the branch target address (19fc vs 1a40), which is a consequence of the missing block. So the lever-free body's only residual is the dead computation: flow/expand deleted it. This is `flow-unused-result`.

Now, is there any lever-free way to keep a dead computation? The target's dead computation includes `slti v0,v1,31; li v1,31`. Could a *real* C construct produce a dead `slti` and `li`? Only a comparison whose result is unused. E.g., `if (v1 < 0x1F) { }` — gcc deletes it. `v0 = (v1 < 0x1F);` then v0 dead — deleted.

So WALL flow-unused-result. Best lever-free = 19 (v02).

But wait, the brief wants ≥30 tries on the item. I've done 32. Good.

However, I should double check: maybe the *first branch* also needs the $2 pin (the orig had it). With lever-free v02, the first branch matched? The diff shows only index 29 (branch address) and the second block. So the first branch matched exactly! Great — so the $2 pin wasn't needed for the first branch in v02. Wait, b1 (with SEC_STD) had a1↔v0/v1 swaps. v02 (SEC_NOV1) has no swaps. Interesting: removing the dead computation from the source (rather than letting flow delete it) changed the allocation. So v02 is much closer: only the missing dead block.

So item 4 is WALL flow-unused-result, best 19.

Hmm, but hold on — could we keep the dead block by keeping only the *keepalive* (PARTIAL:keepalive) and dropping the pin? The orig has keepalives on cmp and tmp3 (both keepalive kind) and pins v0 $2, tmp3 $3 (pin kind). If we drop the pins but keep the keepalives:
- cmp keepalive keeps the slti v0,v1,31.
- tmp3 without pin (plain s32 = 0x1F) + keepalive keeps a li, but in which reg? Target has li v1,31 ($3). Without the pin, it might be $2 or $3.
- The v0 pin removal: the first branch needs v0? In v02 lever-free, the first branch matched without a pin. So maybe dropping the v0 pin is fine.

Let me test a PARTIAL:keepalive variant for item 4: keep both keepalives, drop both pins. Structure:
```c
void func_8017D730(void) {
    s32 a0;
    s32 v0;
    s32 v1;
    s32 t;
    s32 rem;

    ...
    if (rem == D_80185D00) {
        ... (first branch as orig, no levers)
    }
    ...
    if (rem == D_80185D04) {
        t = ...;
        v0 = ...;
        v1 = 0x7F - v0;
        {
            s32 cmp = (v1 < 0x1F);
            __asm__ __volatile__("" :: "r"(cmp));  // keepalive
        }
        {
            s32 tmp3 = 0x1F;
            __asm__ __volatile__("" :: "r"(tmp3));  // keepalive
        }
        func_8002D4C8(0x407, 0);
    }
}
```
Score? The tmp3 might land in $3 or elsewhere. Let me test. If 0 → PARTIAL:keepalive (big win). Let me try.

Also a variant keeping only the tmp3 keepalive or only cmp keepalive. But PARTIAL requires a kind fully removed; keeping both keepalives and dropping pins = PARTIAL:keepalive.

Let me create this file. I'll base it on orig.c and remove the two `register ... __asm__` pins, converting tmp3 to a plain `s32 tmp3 = 0x1F;` and v0 to plain `s32 v0;`. Keep the keepalive asm lines.

orig.c item4 is:
```
void func_8017D730(void) {
    s32 a0;
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)
    s32 v1;
    s32 t;
    s32 rem;
...
            {
                s32 cmp = (v1 < 0x1F);
                __asm__ __volatile__("" :: "r"(cmp));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus10)
            }
            {
                register s32 tmp3 __asm__("$3") = 0x1F;  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus10)
                __asm__ __volatile__("" :: "r"(tmp3));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus10)
            }
```
Let me sed the pins away:
- `register s32 v0 __asm__("$2");  // ...` → `s32 v0;`
- `register s32 tmp3 __asm__("$3") = 0x1F;  // ...` → `s32 tmp3 = 0x1F;`
Keep keepalives.

Let me create k1.c.

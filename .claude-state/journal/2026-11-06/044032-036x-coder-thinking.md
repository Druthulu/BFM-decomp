---
ts: 2026-11-06T11:40:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Cz3cMy4FZBIBL7gOOO7q
---
Excellent! This is the exact solution pattern. Key differences from my attempt:

1. `s16 n` (I had it in v_store_s16n — good).
2. `do { } while (0);` AFTER the call, INSIDE the if-body. The LOOP notes stop reorg's forward scan. I had the do-while AROUND the call (v_lab_do2) and v_store_do; but not empty AFTER the call.
3. Struct alias: they used `extern struct { s32 v; } aD801151D0 __asm__("D_801151D0");` — an asm-label alias because they kept `extern s32 D_801151D0;` for the read. I used a direct struct declaration `extern struct { s32 v; } D_801151D0;` which avoids the asm alias. My v_store_s16n read `D_801151D0.v` and worked (score 4), so the direct struct declaration is fine (no asm needed). Good — cleaner.

So I need: v_store_s16n + `do { } while (0);` AFTER the call (inside the if-body). That's exactly v_lab_do2 but placed AFTER the call. Let me check my v_lab_do2: it wrapped the call in do{...}while(0) — the do-while is around the call, so the loop notes are before the call (loop begins before the call). The sibling put `do { } while (0);` AFTER the call. Let me make that variant.

Also, the `// !FAKE: do-while` comment is required for do-while. Good.

Let me also confirm: their D_801151D0 read uses the plain `D_801151D0` (the s32 extern) and the store uses the struct alias. I'll use the direct struct for both (simpler, no asm). But wait — does reading `D_801151D0.v` vs `D_801151D0` matter? It's a component ref load; should be identical `lw`. My v_store worked (score 5→4), so yes.

Actually, to minimize risk, let me mirror the sibling exactly but replace the asm-label alias with a direct struct declaration (avoiding asm). Let me create the variant: base = v_store_s16n, add `do { } while (0);` after the call.

Let me write gen3.py or just create the file. Let me use a quick python transform.

The call line in v_store_s16n:
```
            if (D_80115158[i].h != 0) {
                ot = ((s32 * (*)(s32 *, Panel_S40_8018B238_80188778 *, s16))func_801889B8)(ot, w, i);
            }
```
Change to:
```
            if (D_80115158[i].h != 0) {
                ot = ((s32 * (*)(s32 *, Panel_S40_8018B238_80188778 *, s16))func_801889B8)(ot, w, i);
                do { } while (0);  // !FAKE: do-while
            }
```

Let me write v_win.c via Write (small edit from v_store_s16n). Actually I'll use a one-off python script or Edit. The file v_store_s16n.c exists; I can Read it then Edit. But I already have its content (nopin + store + s16n). Let me just Write v_win.c directly with the full content, mirroring the sibling.

Let me construct it from nopin.c content with: struct D_801151D0 (direct), s16 n, empty do-while after call. I'll write the full file.

---
ts: 2026-11-06T05:24:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kFhZfQMPxBW1lWdZZyvi
---
The preprocessed function is exactly what I probed (modulo the typedef names being resolved). So why does the real TU give frame 16?

Difference: the real function's return type and the *declaration before* — line 45153-45158 has `void func_801757E0(s32 a0)`. And line 45161. In my probe, pad functions before. Hmm.

Could the frame size be affected by a *previous function*? No, frame is per function.

Unless... `frame_offset` is reset per function in `init_function_start`? Yes, `frame_offset = 0` in init_function_start. Hmm.

Wait — maybe the .s frame 16 belongs to a *different* function and I mis-identified. Let me check the function's .s text vs the standalone. Actually let me look at the real orig.s function in full again — it had `.frame $sp,16` and `subu $sp,$sp,16`. Let me compare with the standalone t4.s function text.

Actually — hold on. Let me reconsider: the real orig.c (hdump-spliced TU) includes the body at line 2759, and the `.file 117` directive points to orig.c. The function is at .s line 4105. But wait, the .s order: functions appear in TU order. func_801757E0 at .s ~4080, then func_80175820 at 4105. Good.

Hmm, let me just recheck the .frame of the real orig.s and the real nobar .s, and also the standalone t4. Maybe I misread and the nobar .s also had frame 16 (I checked line 4106 of dumps_nb/nb.s → frame 0). Let me verify again with the actual function body text in each.

Actually, maybe the difference between orig and nobar in the real TU is NOT the asm but the **line numbers / .file**? No.

Let me look at the real orig.s function and the standalone t4.s function side by side.

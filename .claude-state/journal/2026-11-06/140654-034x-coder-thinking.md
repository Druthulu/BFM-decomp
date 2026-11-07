---
ts: 2026-11-06T21:06:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_02n461wm2xROOsBafWm2
---
258 files reference func_80148D44! It's a shared function included by many TUs. But the item is TU-specific (src/ov_SC01_077/ov_SC01_077_after.c) — not a header. So the same body appears in many TUs via... let me check one, e.g., src/ov_SC03_099/ov_SC03_099_after.c. Maybe it's a duplicate body with a different definition (some matched, some not). Let me see the definition there.

Actually, the dedup map config/dedup.us.yaml records shared bodies. func_80148D44 at 0x80148D44 is within SC01's range? The item's TU is ov_SC01_077. Other overlays may have their own copy at a different address. But grep found the name in 258 files, likely as calls.

Let me look at ov_SC03_099_after.c's def of func_80148D44.

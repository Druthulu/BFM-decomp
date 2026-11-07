---
ts: 2026-11-06T04:36:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UHF6UUiUfcwYwAMDekAE
---
Let me build z11: duplicate the 0x18 store in each arm, remove the shared store (line 71). For the else arm, keep its own store (already there) and goto call.

- n<8 arm: after line 39 add `((Unk*)p)->unk18 = v;`
- n<0x16: after line 43 add the store.
- ==0: after line 53 add the store.
- <0x11: after line 62 add the store.
- else: already has both + goto call.
- Remove line 71 (shared store) and keep `call:`.

Then the arms fall through to the call label (no goto needed except else's). Let me build with awk.

Note: without the shared store, the arms must fall through to `call:`; the compiler will place the label and jumps accordingly. The cross-jump should merge the identical stores.

Let me construct z11 from z8.

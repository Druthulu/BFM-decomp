---
ts: 2026-10-22T09:23:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_93PANvtVWAh92MLu6f7K
---
Now let's find the function's RTL and the plus tree. Let me search for the plus with the shift in the .rtl dump for func_80184828.

The function section format: ";; Function func_80184828". Let me extract and grep for "plus".

Let me write an extraction that shows the function's insns per pass, filtered to lines containing "plus" or "lsh"/"mult".

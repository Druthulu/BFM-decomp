---
agent: ext-T11.cW48x
label: T11.cW48x
---
Three items: item 3 (pin $3) needs the unkCC load to reach $3 without the pin; item 2 (header, pin $7) needs the equal pointers a7/v1 to survive cse as two registers; item 1 (keepalive) needs a1's address load to stay early and a0's $4 pin to keep the double move. I'll start each with the direct pin/asm removal to see the residual, then move it with real C.

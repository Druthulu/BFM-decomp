---
ts: 2026-11-06T16:28:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5O15VWF9qaerO3InOpjY
---
Target:
```
move a1,a0          ; self = arg0 (copy, from zr pin? "self = arg0 + zr" produced move a1,a0)
lh v0,170(a1)       ; flag
sh zero,92(a1)
sh zero,152(a1)
bnez v0, else
sw zero,28(a1)      ; in delay slot
li a0,-129          ; mask
lw v1,32(a1)        ; p = self->unk20
lw v0,220(a1)       ; f
lhu v1,24(v1)       ; p = *(u16*)(p+0x18)
and v0,v0,a0
sw v0,220(a1)
j end
sh v1,256(a1)       ; delay slot
else:
lw v0,32(a1)
lw v1,220(a1)
lhu v0,24(v0)
ori v1,v1,0x80
sw v1,220(a1)
sh v0,260(a1)
end:
jr ra
nop
```

Mine (pin-free) currently:
- self in a1? mine at ins 0: probably `move a0,a0`? Let's get mine dump. Run dt with --keep? Easier: use --try --keep to keep candidate object then objdump. Let's do that with a tail showing object path.

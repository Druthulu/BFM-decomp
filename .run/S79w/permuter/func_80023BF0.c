















extern u8 D_800AF630[];
extern u8 D_800A6610[];
extern u16 D_800B9A02;
extern u8 *D_800A5E60;
typedef struct 
{
  s16 vx;
  s16 vy;
  s16 vz;
  s16 pad;
} Vec23BF0;
void func_80023BF0(s32 arg0)
{
  Vec23BF0 v;
  u32 xy;
  u32 sxy2;
  u32 mac0;
  u32 new_var;
  s32 z;
  u32 flags;
  u16 *prims;
  u16 b9;
  u16 idx;
  u32 *new_var3;
  s32 x;
  s32 y;
  u32 *otab;
  u8 *pkt;
  u32 code;
  s32 tpage;
  s32 tp;
  u8 *mat;
  u32 new_var2;
register u32 m24 __asm__("$11");
register u32 e1 __asm__("$4");
register u32 base __asm__("$3");
  mat = D_800AF630;
  prims = *((u16 **) (arg0 + 0x20));
  b9 = D_800B9A02;
  flags = *((u32 *) (arg0 + 4));
  otab = (u32 *) ((b9 * 0x4000) + D_800A6610);
  if (flags & 0x4000000)
  {
    u8 *m = mat + 0x18;
__asm__ volatile ( "lw $12, 0(%0);" "lw $13, 4(%0);" "ctc2 $12, $0;" "ctc2 $13, $1;" "lw $12, 8(%0);" "lw $13, 12(%0);" "lw $14, 16(%0);" "ctc2 $12, $2;" "ctc2 $13, $3;" "ctc2 $14, $4" : : "r"(m) : "$12", "$13", "$14");
__asm__ volatile ( "lw $12, 20(%0);" "lw $13, 24(%0);" "ctc2 $12, $5;" "lw $14, 28(%0);" "ctc2 $13, $6;" "ctc2 $14, $7" : : "r"(m) : "$12", "$13", "$14");
    v.vx = (*((u16 *) (arg0 + 8))) + (*((u16 *) (arg0 + 0x2E)));
    v.vy = (*((u16 *) (arg0 + 0xA))) + (*((u16 *) (arg0 + 0x30)));
    v.vz = (*((u16 *) (arg0 + 0xC))) + (*((u16 *) (arg0 + 0x32)));
__asm__ volatile("lwc2 $0, 0(%0);lwc2 $1, 4(%0)" : : "r"(&v));
__asm__ volatile("nop;nop;rtps");
__asm__ volatile("swc2 $14, 0(%0)" : : "r"(&xy) : "memory");
__asm__ volatile("swc2 $8, 0(%0)" : : "r"(&sxy2) : "memory");
__asm__ volatile("cfc2 $12, $31;nop;sw $12, 0(%0)" : : "r"(&mac0) : "$12", "memory");
__asm__ volatile("mfc2 $12, $19;nop;sra $12, $12, 2;sw $12, 0(%0)" : : "r"(&z) : "$12", "memory");
    if (z <= 0)
    {
      return;
    }
    idx = z + 1;
    {
      u32 t = xy;
      x = (*((u16 *) (arg0 + 0xE))) + t;
      y = t >> 16;
    }
  }
  else
  {
    x = (*((u16 *) (arg0 + 0xE))) + ((*((u16 *) (arg0 + 8))) + (*((u16 *) (arg0 + 0x2E))));
    idx = *((u16 *) (arg0 + 0x2C));
    y = (*((u16 *) (arg0 + 0xA))) + (*((u16 *) (arg0 + 0x30)));
  }
  tp = ((*((u8 *) (arg0 + 0x27))) + 0x100) << 6;
  if ((*((u8 *) (arg0 + 0x27))) < 0xE0)
  {
    tpage = tp | 0x16;
  }
  else
  {
    tpage = tp | 0x10;
  }
  pkt = D_800A5E60;
__asm__ __volatile__("");
__asm__ __volatile__("");
__asm__ __volatile__("");
__asm__ __volatile__("");
__asm__ __volatile__("");
__asm__ __volatile__("");
__asm__ __volatile__("");
__asm__ __volatile__("");
__asm__ __volatile__("");
__asm__ __volatile__("");
__asm__ __volatile__("");
__asm__ __volatile__("");
__asm__ __volatile__("");
  if (!(flags & 0x400000))
  {
    u16 c;
    base = 0x74000000;
    if (flags & 0x40000000)
    {
      base = 0x76000000;
    }
    code = (*((u8 *) (arg0 + 0x26))) << 16;
    code = code | (((*((u8 *) (arg0 + 0x25))) << 8) | base);
    code = code | (*((u8 *) (arg0 + 0x24)));
__asm__ __volatile__("");
    c = *prims;
    if (c != 0xFFFF)
    {
      m24 = 0xFFFFFF;
      do
      {
        switch (c)
        {
          case 0x1850:

          case 0x1858:
            *((u16 *) (pkt + 8)) = x + 4;
            *((u16 *) (pkt + 0xA)) = y - 7;
            break;

          case 0x3870:
            x += 7;
            prims++;
            continue;

          case 0x3871:
            x += 4;
            prims++;
            continue;

          case 0x3872:
            x += 2;
            prims++;
            continue;

          default:
            *((u16 *) (pkt + 8)) = x;
            x += 7;
            *((u16 *) (pkt + 0xA)) = y;
            break;

        }

        *((u32 *) pkt) = 0x3000000;
        *((u32 *) (pkt + 4)) = code;
        *((u16 *) (pkt + 0xC)) = *(prims++);
        new_var3 = &otab[idx];
        *((u16 *) (pkt + 0xE)) = tpage;
        *((u32 *) pkt) = ((*((u32 *) pkt)) & 0xFF000000) | ((*new_var3) & m24);
        otab[idx] = (otab[idx] & 0xFF000000) | (((u32) pkt) & m24);
        pkt += 0x10;
      }
      while ((c = *prims) != 0xFFFF);
    }
  }
  else
  {
    u16 c;
    base = 0x64000000;
    if (flags & 0x40000000)
    {
      base = 0x66000000;
    }
    code = (*((u8 *) (arg0 + 0x26))) << 16;
    code = code | (((*((u8 *) (arg0 + 0x25))) << 8) | base);
    code = code | (*((u8 *) (arg0 + 0x24)));
__asm__ __volatile__("");
    c = *prims;
    if (c != 0xFFFF)
    {
      do
      {
        if (c == 0x3870)
        {
          m24 = 0xFFFFFF;
          x += 0x10;
          prims++;
        }
        else
        {
          *((u16 *) (pkt + 8)) = x;
          x += 0x10;
          *((u16 *) (pkt + 0xA)) = y;
          *((u32 *) pkt) = 0x4000000;
          *((u32 *) (pkt + 4)) = code;
          *((u16 *) (pkt + 0xC)) = *(prims++);
          *((u16 *) (pkt + 0xE)) = tpage;
          *((u32 *) (pkt + 0x10)) = 0x180010;
          new_var2 = otab[idx];
          *((u32 *) pkt) = ((*((u32 *) pkt)) & 0xFF000000) | (new_var2 & m24);
          otab[idx] = (otab[idx] & 0xFF000000) | (((u32) pkt) & m24);
          pkt += 0x14;
        }
      }
      while ((c = *prims) != 0xFFFF);
    }
  }
  pkt[3] = 1;
  e1 = 0xE1000015;
  *((u32 *) (pkt + 4)) = ((flags >> 23) & 0x60) | e1;
  new_var = otab[idx];
  *((u32 *) pkt) = ((*((u32 *) pkt)) & 0xFF000000) | (new_var & 0xFFFFFF);
  D_800A5E60 = pkt + 0x40;
  otab[idx] = (otab[idx] & 0xFF000000) | (((u32) pkt) & 0xFFFFFF);
}
















typedef struct 
{
  s32 w[8];
} Blk20;
extern Blk20 D_800AE620;
extern s32 D_801AAD00[];
extern s32 D_801AAD08[];
extern void func_8012C1B8(void);
extern void func_8012C218(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
typedef struct 
{
  s16 h0;
  s16 h1;
  s16 h2;
  s16 h3;
} Q_8017DF28;
typedef struct 
{
  s32 x;
  s32 y;
  s32 z;
} VEC_8017DF28;
void func_8017DF28(s32 param_1)
{
  Blk20 mtx;
  VEC_8017DF28 pos;
  VEC_8017DF28 *mptr;
  s32 obj;
  mtx = D_800AE620;
  obj = ((s32 (*)(void)) func_8012C1B8)();
  pos.x = 0;
  if (obj == 0)
  {
    func_8012C218((void *) param_1);
    return;
  }
  func_8001C214(obj, (s32) D_801AAD08);
  *((Q_8017DF28 *) (obj + 0x08)) = *((Q_8017DF28 *) ((*((s32 *) (param_1 + 0x20))) + 0x08));
  *((Q_8017DF28 *) (obj + 0x10)) = *((Q_8017DF28 *) ((*((s32 *) (param_1 + 0x20))) + 0x10));
  *((Q_8017DF28 *) (obj + 0x18)) = *((Q_8017DF28 *) ((*((s32 *) (param_1 + 0x20))) + 0x18));
  *((s32 *) (obj + 0x04)) = *((s32 *) ((*((s32 *) (param_1 + 0x20))) + 0x04));
  *((u16 *) (obj + 0x2C)) = *((u16 *) ((*((s32 *) (param_1 + 0x20))) + 0x2C));
  *((s32 *) (param_1 + 0xCC)) = obj;
  *((s32 *) ((*((s32 *) (param_1 + 0x20))) + 0x24)) = (s32) D_801AAD00;
  *((s32 *) (param_1 + 0x48)) = 0xC000;
  *((u16 *) (param_1 + 0xA)) = (*((u16 *) (param_1 + 0xA))) - 0xB0;
  *((u16 *) ((*((s32 *) (param_1 + 0x20))) + 0x12)) = *((u16 *) (param_1 + 0x62));
  func_8012B2CC(param_1);
  *((u16 *) (param_1 + 0xAE)) = 0x2000;
  pos.y = -0xC0000;
  pos.x = 0;
  pos.z = -0x80000;
  RotMatrixY(*((s16 *) (param_1 + 0x62)), mptr);
  func_800484EC((s32) mptr, (s32) (&pos), param_1 + 0x10);
  param_1 += 0;
  func_8002D4C8(0x955, 0);
  mptr = (VEC_8017DF28 *) (&mtx);
  *((u16 *) (param_1 + 0x2)) = (*((u16 *) (param_1 + 0x2))) + 1;
}
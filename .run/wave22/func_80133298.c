typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

extern s32 D_80126B5C;
extern s32 D_80126B60;
extern s32 D_80126B64;

void func_8012B2CC(s32);
void func_8012F0BC(s32*, s32*, s32*);
void func_8012F1A4(s32*, s32, s32*);
void func_8013339C(short*, short*);

void func_80133298(s32 arg0)
{
    typedef struct { s32 vx, vy, vz, pad; } Vec_80133298;
    typedef struct { s16 m[3][3]; s32 t[3]; } Mtx_80133298;
    Vec_80133298 vin;
    Vec_80133298 vout;
    Vec_80133298 tmp;
    Mtx_80133298 mtx;

    vin.vx = D_80126B5C;
    vin.vy = D_80126B60;
    vin.vz = D_80126B64;
    func_8012F0BC((s32*)(*(s32*)(arg0 + 0x20) + 0x34), (s32*)&vin, (s32*)&tmp);
    func_8012B2CC(arg0);
    mtx = *(Mtx_80133298*)(*(s32*)(arg0 + 0x20) + 0x34);
    func_8013339C((short*)&mtx, (short*)(*(s32*)(arg0 + 0x20) + 0x18));
    func_8012F1A4((s32*)&mtx, (s32)&tmp, (s32*)&vout);
    D_80126B5C = vout.vx;
    D_80126B60 = vout.vy;
    D_80126B64 = vout.vz;
}

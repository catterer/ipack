#ifndef __IPACK_H_
#define __IPACK_H_

#define IPA_R(i,f,s,a,...)  IPA##f##_F(f,s,a) IPA_EX(FST,IPA_EX(CAT,IPA_X,IPA_Y __VA_ARGS__))(i)
#define IPA_EAT(f,s,a,...)  f,s,__VA_ARGS__

#define IPA_EX(cmd,...)     IPA_##cmd(__VA_ARGS__)
#define IPA_CAT(a,...)      a##__VA_ARGS__
#define IPA_FST(a,...)      a
#define IPA_Y()             Y
#define IPA_XIPA_Y          IPA_RI,~
#define IPA_XY              IPA_END,~
#define IPA_RI(i)           IPA_R##i
#define IPA_END(i)          IPA_END_
#define IPA_END_(...)       1

#define IPA_R1(...)         IPA_R(2,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R2(...)         IPA_R(3,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R3(...)         IPA_R(4,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R4(...)         IPA_R(5,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R5(...)         IPA_R(6,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R6(...)         IPA_R(7,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R7(...)         IPA_R(8,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R8(...)         IPA_R(9,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R9(...)         IPA_R(10,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R10(...)        IPA_R(11,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R11(...)        IPA_R(12,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R12(...)        IPA_R(13,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R13(...)        IPA_R(14,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R14(...)        IPA_R(15,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R15(...)        IPA_R(16,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R16(...)        IPA_R(17,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R17(...)        IPA_R(18,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R18(...)        IPA_R(19,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R19(...)        IPA_R(20,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R20(...)        IPA_R(21,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R21(...)        IPA_R(22,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R22(...)        IPA_R(23,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R23(...)        IPA_R(24,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R24(...)        IPA_R(25,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R25(...)        IPA_R(26,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R26(...)        IPA_R(27,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R27(...)        IPA_R(28,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R28(...)        IPA_R(29,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R29(...)        IPA_R(30,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R30(...)        IPA_R(31,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R31(...)        IPA_R(32,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R32(...)        IPA_R(33,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R33(...)        IPA_R(34,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R34(...)        IPA_R(35,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R35(...)        IPA_R(36,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R36(...)        IPA_R(37,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R37(...)        IPA_R(38,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R38(...)        IPA_R(39,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R39(...)        IPA_R(40,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R40(...)        IPA_R(41,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R41(...)        IPA_R(42,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R42(...)        IPA_R(43,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R43(...)        IPA_R(44,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R44(...)        IPA_R(45,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R45(...)        IPA_R(46,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R46(...)        IPA_R(47,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R47(...)        IPA_R(48,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R48(...)        IPA_R(49,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R49(...)        IPA_R(50,__VA_ARGS__)(IPA_EAT(__VA_ARGS__))
#define IPA_R50(...)        clone_IPA_Rx_macros_if_you_really_need_more_args

#define IPACK_F(f,s,a)      !((s)->cursor_back = (s)->cursor, \
                            IPA##f##_CB_##a(s,IPA##f##_ARG_##a), \
                            (s)->rc ? (s)->cursor = (s)->cursor_back:0, (s)->rc) &&
#define IPARSE_F(f,s,a)     ((s)->rc = IPA##f##_CB_##a((s)->data + (s)->cursor, (s)->len - (s)->cursor,IPA##f##_ARG_##a))>=0 && \
                            (assert((long long)(s)->rc <= IPARSE_RLEN(s)),1) && \
                            ((s)->cursor+=(s)->rc) &&

#endif

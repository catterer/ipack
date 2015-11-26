#ifndef _IPACK_H_
#define _IPACK_H_

#include "_ipack.h"

//                          README
//
// Usage:
//
//          If you use IPACK / IPARSE, you MUST check the return value.
//          If you don't want to, use IPACKF / IPARSEF, which check it themselves and abort() if smth went wrong
//
// Examples:
//
//          rc = IPARSE(ps, u32(&id), u32(&time), lps(&name,&len));
//          if( rc ) {
//              // ERROR: Invalid packet! (or whatever you were parsing)
//          }
//
//          IPARSEF( ps, u32(&timestamp), msgid(&mid) ); // Nothing can go wrong. Yeah. I'm sure.
//
//          
//          rc = IPACK( ps, u64(intval), lps(str, strlen) );
//          if( rc ) {
//              // ERROR: Maybe buffer is too short?
//          }
//
//          IPACKF( ps, u64(intval), fmt( "msg: %s", str ) ); // I'm sure that buffer is long enough
//
//
//  Creating your types:
//          
//          If it is common type, put it in ipack_types.h. If it is app- or need-specific, put it in corresponding file.
//          Try to use the macros below in ipack types you create.
//          Don't forget to check 'len' argument in iparse_* types.
//
//  Examples:
//
//          See ipack_types.h if you want

#define IPACK_IS_FAILED( s )  ((s)->rc)
#define IPACK_SET_FAIL( s ) ((s)->rc = -1)
#define IPACK_LEN( s )      ((s)->cursor)
#define IPACK_OFFSET( s )   IPACK_LEN(s)
#define IPACK_DATA( s )     ((s)->buffer)
#define IPACK_RLEN( s )     ((s)->size - IPACK_LEN(s))
#define IPACK_RBUF( s )     ((s)->buffer + (s)->cursor)
#define IPACK_DL( s )       IPACK_DATA(s), IPACK_LEN(s)
#define IPACK_LD( s )       (int)IPACK_LEN(s), IPACK_DATA(s)
#define IPACK_SL( st )      ((sl_t){.s = IPACK_DATA(st), .l = IPACK_LEN(st)})
#define IPACK_DS( s )       (ds_t){.base = IPACK_DATA(s), .size = IPACK_LEN(s)}
#define IPACK_IS_STATIC( s )((s)->static_buf)

#define IPARSE_ABUF(s)    (s)->data
#define IPARSE_ALEN(s)    (s)->len
#define IPARSE_ASL(s)     SLdl(IPARSE_ABUF(s), IPARSE_ALEN(s))
#define IPARSE_ADL(s)     IPARSE_ABUF(s), IPARSE_ALEN(s)
#define IPARSE_ALD(s)     (int)IPARSE_ALEN(s), IPARSE_ABUF(s)

#define IPARSE_BUF(s)     IPARSE_ABUF(s)
#define IPARSE_LEN(s)     (s)->cursor
#define IPARSE_SL(s)      SLdl(IPARSE_BUF(s), IPARSE_LEN(s))
#define IPARSE_DL(s)      IPARSE_BUF(s), IPARSE_LEN(s)
#define IPARSE_LD(s)      (int)IPARSE_LEN(s), IPARSE_BUF(s)

#define IPARSE_RBUF(s)    (IPARSE_ABUF(s) + IPARSE_LEN(s))
#define IPARSE_RLEN(s)    (IPARSE_ALEN(s) - IPARSE_LEN(s))
#define IPARSE_RSL(s)     SLdl(IPARSE_RBUF(s), IPARSE_RLEN(s))
#define IPARSE_RDL(s)     IPARSE_RBUF(s), IPARSE_RLEN(s)
#define IPARSE_RLD(s)     (int)IPARSE_RLEN(s), IPARSE_RBUF(s)

#define IPARSE_DATA(s)    IPARSE_BUF(s)
#define IPARSE_EMPTY(s)   (!IPARSE_RLEN(s))

#define IPACK_LPS_STACK_SZ  32
#define IPACK_ALLOCBY       (1 KiB)
#define IPACK(s,...)        ((void)(assert(!(s)->rc && (s)->size >= (s)->cursor), \
                            IPA_R1(CK,s,__VA_ARGS__,())), (s)->rc)
#define IPACKF(...)         (IPACK(__VA_ARGS__) && (abort(),1))
#define IPACKQ(...)         ({ IPACK(__VA_ARGS__); })

#define IPARSE(s,...)       ((void)(assert((s)->rc>=0 && (s)->len >= (s)->cursor), \
                            IPA_R1(RSE,s,__VA_ARGS__,())), (s)->rc<0)
#define IPARSEF(...)        (IPARSE(__VA_ARGS__) && (abort(),1))

#define IPACK_TO_SL(ps) (sl_t) { .s = IPACK_DATA(ps), .l = IPACK_LEN(ps) }
#define IPACK_TO_DS(ps) (ds_t) { .base = IPACK_DATA(ps), .size = IPACK_LEN(ps) }

#define IPARSE_INIT(data, len) (iparse_init(&(iparse_t){}, (char *) (data), (len)))
#define IPARSE_INIT_SL(sl) IPARSE_INIT_FROM_SL(sl)
#define IPARSE_INIT_DC(sl) IPARSE_INIT_FROM_DC(sl)
#define IPARSE_INIT_IPACK(ps) IPARSE_INIT_FROM_IPACK(ps)
#define IPARSE_INIT_FROM_SL(sl) IPARSE_INIT((sl).s, (sl).l)
#define IPARSE_INIT_FROM_DC(dc) IPARSE_INIT((dc)->data, (dc)->len)
#define IPARSE_INIT_FROM_IPACK(ps) IPARSE_INIT(IPACK_DATA(ps), IPACK_LEN(ps))
#define IPARSE_INIT_FROM_IPARSE(ps) IPARSE_INIT(IPARSE_RBUF(ps), IPARSE_RLEN(ps))


#define IPACK_INIT_FROM_SL(sl) (ipack_init_from(&(ipack_t){}, (sl).s, (sl).l))
#define IPACK_DBUF_INIT() (ipack_dbuf_init(&(ipack_t){}, 0, 0))
#define IPACK_INIT(data, len) (ipack_init(&(ipack_t){}, data, len))
#define IPACK_INIT_FROM_STATIC(buf) IPACK_INIT(buf, sizeof(buf))
#define IPACK_INIT_FXD(len) IPACK_INIT((char[len]) {}, len)

#define IPACK_NEW(data, len) ipack_init(&(ipack_t) {}, data, len)
#define IPACK_NEW_FROM_STATIC(buf) IPACK_NEW(buf, sizeof(buf))
#define IPACK_NEW_STATIC(len) IPACK_NEW(_buf(len), len)

#define IPACK_DBUF_NEW() ipack_dbuf_init(&(ipack_t) {}, 0, 0)

#define IPARSE_TO_SL(ps) sl_init(IPARSE_RBUF(ps), IPARSE_RLEN(ps))

#define IPARSE_NEW(data, len) iparse_init(&(iparse_t) {}, (char *) (data), len)
#define IPARSE_NEW_FROM_SL(sl) IPARSE_NEW((sl).s, (sl).l)
#define IPARSE_NEW_FROM_DC(dc) IPARSE_NEW(dc->data, dc->len)
#define IPARSE_NEW_FROM_IPACK(ps) IPARSE_NEW(IPACK_DATA(ps), IPACK_LEN(ps))
#define IPARSE_NEW_FROM_IPARSE(ps) IPARSE_NEW(IPARSE_RBUF(ps), IPARSE_RLEN(ps))

#define IPARSE_FROM(data, len, ...) ({ iparse_t *in = IPARSE_NEW(data, len); IPARSE(in, __VA_ARGS__); })
#define IPARSE_FROM_SL(sl, ...) IPARSE_FROM((sl).s, (sl).l, __VA_ARGS__)

#define with_lps(ps) \
    for (int step = 1; step && ({ ipack_lps_start(ps); 1; }); ipack_lps_finish(ps), step = 0)

#define with_tlv(ps, tag) \
    for (int step = 1; step && ({ IPACKF(ps, u32(tag)); ipack_lps_start(ps); 1; }); ipack_lps_finish(ps), step = 0)

#define tlv_foreach(tag, ps, in)                \
    for (int step = 1;          step; )         \
    for (uint32_t tag = 0;      step; )         \
    for (sl_t value;            step; )         \
    for (iparse_t *ps;          step; )         \
    for (;                      step; step = 0) \
    while (IPARSE_RLEN(in) && ! IPARSEF(in, u32(&tag), sl(&value)) && (ps = IPARSE_NEW_FROM_SL(value)))

typedef struct ipack_t ipack_t;

#define IPACK_FLAG_LPS16  0x0001
#define IPACK_FLAG_NET    0x0002

struct ipack_t {
// TODO
// There are some ideas about using imgn_buffer in ipack to reduce bicycle building of dynamic buffers

// XXX 
// If you add fields here don't forget to check ipack_reset()
        int         rc;
        char *      buffer;
        bool        static_buf;
        size_t      size;
        size_t      cursor;
        size_t      cursor_back;

        size_t      lps_stack[ IPACK_LPS_STACK_SZ ];
        uint32_t    lps_stack_flags[ IPACK_LPS_STACK_SZ ];
        unsigned    lps_stack_ptr;

        ipack_t     *prev;
        ipack_t     *next;
};

typedef struct iparse_t {
        int         rc;
        char *      data;
        size_t      len;
        size_t      cursor;
} iparse_t;

static inline iparse_t *iparse_init( iparse_t * ps, char * data, size_t len )
{
    memset( ps, 0, sizeof(*ps) );
    ps->data = data;
    ps->len = len;
    return ps;
}

static inline void iparse_reset(iparse_t* ps)
{
    iparse_init(ps, ps->data, ps->len);
}

static inline void ipack_fmt( ipack_t * ps, bool trunc, const char * fmt, ... ) __attribute__((format(printf, 3, 4)));

static inline int ipack_reserve( ipack_t * ps, size_t required )
{
    if (IPACK_RLEN(ps) >= required)
        return 0;

    if (ps->static_buf)
        return -1;

    size_t t = ((IPACK_LEN(ps) + required) / IPACK_ALLOCBY + 1) * IPACK_ALLOCBY;
    size_t ext = MAX(t, ps->size * 2);

    ps->buffer = (char*)realloc(ps->buffer, ext);
    assert(ps->buffer);

    ps->size = ext;

    return 0;
}

static inline void _ipack_append( ipack_t * ps, const char * data, size_t len )
{
    if( IPACK_IS_FAILED( ps ) )
        return;
    if( ipack_reserve( ps, len ) ) {
        IPACK_SET_FAIL( ps );
        return;
    }
    assert( IPACK_RLEN( ps ) >= len );

// Optimization: do not call memcpy() for ipack_[u]int(8|16|32|64)
#define CASE_UNS(nbits) \
    case sizeof(uint##nbits##_t): *(uint##nbits##_t*)IPACK_RBUF(ps) = *(uint##nbits##_t*)data; break
    switch(len) {
        CASE_UNS(64);
        CASE_UNS(32);
        CASE_UNS(16);
        CASE_UNS(8);
        default: memcpy( IPACK_RBUF( ps ), data, len );
    }
    ps->cursor += len;
}

static inline void _ipack_lps_start( ipack_t *ps, uint32_t flags )
{
    size_t sz = flags & IPACK_FLAG_LPS16 ? sizeof(uint16_t) : sizeof(uint32_t);
    if( ipack_reserve( ps, sz ) ) {
        IPACK_SET_FAIL( ps );
        return;
    }
    ps->lps_stack[ ps->lps_stack_ptr ] = ps->cursor;
    ps->lps_stack_flags[ ps->lps_stack_ptr ] = flags;

    ps->lps_stack_ptr++;
    ps->cursor += sz;
    assert( ps->lps_stack_ptr < IPACK_LPS_STACK_SZ );
}

static inline void ipack_lps_start( ipack_t *ps )
{
    _ipack_lps_start(ps, 0);
}

static inline void ipack_lps16_start( ipack_t *ps )
{
    _ipack_lps_start(ps, IPACK_FLAG_LPS16);
}

static inline void ipack_lps16n_start( ipack_t *ps )
{
    _ipack_lps_start(ps, IPACK_FLAG_LPS16 | IPACK_FLAG_NET);
}

static inline size_t ipack_lps_finish( ipack_t * ps )
{
    assert( ps->lps_stack_ptr );
    size_t lps_start = ps->lps_stack[--ps->lps_stack_ptr];
    uint32_t flags = ps->lps_stack_flags[ps->lps_stack_ptr];

    int lps16 = flags & IPACK_FLAG_LPS16;
    int net = flags & IPACK_FLAG_NET;

    char *p = ps->buffer + lps_start;
    size_t sz = ps->cursor - lps_start - (lps16 ? sizeof(uint16_t) : sizeof(uint32_t));

    if (lps16) {
        assert(sz <= UINT16_MAX);
        if (net)
            *(uint16_t*) p = htons(sz);
        else
            *(uint16_t*) p = sz;
    } else {
        assert(sz <= UINT32_MAX);
        if (net)
            *(uint32_t*) p = htonl(sz);
        else
            *(uint32_t*) p = sz;
    }

    return sz;
}

static inline void ipack_lps_finish_all( ipack_t * ps )
{
    while( ps->lps_stack_ptr )
        ipack_lps_finish( ps );
}

static inline void ipack_lps_rollback( ipack_t * ps )
{
    assert( ps->lps_stack_ptr );
    ps->cursor = ps->lps_stack[--ps->lps_stack_ptr];
}

static inline ipack_t *ipack_init( ipack_t * ps, char * buffer, size_t size )
{
    memset( ps, 0, sizeof(*ps) );

    ps->buffer = buffer;
    ps->size = size;

    ps->static_buf = true;

    return ps;
}

static inline ipack_t *ipack_init_from( ipack_t * ps, char * buffer, size_t cursor )
{
    memset( ps, 0, sizeof(*ps) );

    ps->buffer = buffer;
    ps->size = cursor;
    ps->cursor = cursor;
    ps->cursor_back = cursor;

    if (buffer) {
        ps->static_buf = true;
        return ps;
    }

    return ps;
}

static inline ipack_t *ipack_dbuf_init( ipack_t * ps, size_t prealloc, size_t allocby )
{
    memset(ps, 0, sizeof(*ps));

    if (prealloc && ipack_reserve(ps, prealloc))
        IPACK_SET_FAIL(ps);

    return ps;
}

static inline void ipack_copy( ipack_t * src, ipack_t * dst )
{
    *dst = *src;
    dst->buffer = malloc(src->size);
    memcpy(dst->buffer, src->buffer, src->size);
}

static inline void ipack_reset( ipack_t * ps )
{
    ps->cursor = 0;
    ps->rc = 0;
    ps->cursor_back = 0;
    ps->lps_stack_ptr = 0;
}

static inline void ipack_reset_to(ipack_t *ps, size_t off)
{
    assert(off <= ps->cursor);
    ps->cursor = off;
}

static inline void ipack_dbuf_destroy(ipack_t * ps);

static inline sl_t ipack_release(ipack_t *ps)
{
    if (ps->next) {
        ipack_dbuf_destroy(ps->next);
        freep(&ps->next);
    }

    return IPACK_TO_SL(ps);
}

static void ipack_dbuf_destroy(ipack_t * ps)
{
    assert(ps->static_buf == false);

    sl_free(ipack_release(ps));
}

#endif // _IPACK_H_


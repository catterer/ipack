#ifndef _IPACK_TYPES_H_
#define _IPACK_TYPES_H_

typedef struct tlv_t {
    union {
        uint32_t    tag;
        uint32_t    t;
    };
    union {
        uint32_t    len;
        uint32_t    l;
    };
    union {
        char        val[0];
        char        v[0];
    };
}   __attribute__((packed)) tlv_t;

#define IPACK_CB_u32(...)  ipack_u32
#define IPACK_ARG_u32(...) __VA_ARGS__
static inline void ipack_u32( ipack_t *ps, uint32_t x )
{
    _ipack_append( ps, (char*)&x, sizeof(x) );
}

#define IPACK_CB_u32n(...) ipack_u32n
#define IPACK_ARG_u32n(...) __VA_ARGS__
static inline void ipack_u32n(ipack_t *ps, uint32_t x)
{
    x = htonl(x);
    _ipack_append(ps, (char *) &x, sizeof(x));
}

#define IPACK_CB_u64(...)  ipack_u64
#define IPACK_ARG_u64(...) __VA_ARGS__
static inline void ipack_u64( ipack_t *ps, uint64_t x )
{
    _ipack_append( ps, (char*)&x, sizeof(x) );
}

#define IPACK_CB_u16(...)  ipack_u16
#define IPACK_ARG_u16(...) __VA_ARGS__
static inline void ipack_u16( ipack_t *ps, uint16_t x )
{
    _ipack_append( ps, (char*)&x, sizeof(x) );
}

#define IPACK_CB_u16n(...) ipack_u16n
#define IPACK_ARG_u16n(...) __VA_ARGS__
static inline void ipack_u16n(ipack_t *ps, uint16_t x)
{
    x = htons(x);
    _ipack_append(ps, (char *) &x, sizeof(x));
}

#define IPACK_CB_u8(...)  ipack_u8
#define IPACK_ARG_u8(...) __VA_ARGS__
static inline void ipack_u8( ipack_t *ps, uint8_t x )
{
    _ipack_append( ps, (char*)&x, sizeof(x) );
}

#define IPACK_CB_i64(...)  ipack_i64
#define IPACK_ARG_i64(...) __VA_ARGS__
static inline void ipack_i64( ipack_t *ps, int64_t x )
{
    _ipack_append( ps, (char*)&x, sizeof(x) );
}

#define IPACK_CB_i32(...)  ipack_i32
#define IPACK_ARG_i32(...) __VA_ARGS__
static inline void ipack_i32( ipack_t *ps, int32_t x )
{
    _ipack_append( ps, (char*)&x, sizeof(x) );
}

#define IPACK_CB_i16(...)  ipack_i16
#define IPACK_ARG_i16(...) __VA_ARGS__
static inline void ipack_i16( ipack_t *ps, int16_t x )
{
    _ipack_append( ps, (char*)&x, sizeof(x) );
}

#define IPACK_CB_i8(...)  ipack_i8
#define IPACK_ARG_i8(...) __VA_ARGS__
static inline void ipack_i8( ipack_t *ps, int8_t x )
{
    _ipack_append( ps, (char*)&x, sizeof(x) );
}

#define IPACK_CB_dob(...)  ipack_dob
#define IPACK_ARG_dob(...) __VA_ARGS__
static inline void ipack_dob( ipack_t *ps, double x )
{
    _ipack_append( ps, (char*)&x, sizeof(x) );
}

#define IPACK_CB_tlv(...) CAT(IPACK_CB_tlv_, NARG(__VA_ARGS__))(__VA_ARGS__)
#define IPACK_CB_tlv_1(...) ipack_tlv_sl
#define IPACK_CB_tlv_2(...) ipack_tlv_sl
#define IPACK_CB_tlv_3(...) ipack_tlv

#define IPACK_ARG_tlv(...) CAT(IPACK_ARG_tlv_, NARG(__VA_ARGS__))(__VA_ARGS__)
#define IPACK_ARG_tlv_1(tag) tag, sl_none
#define IPACK_ARG_tlv_2(...) __VA_ARGS__
#define IPACK_ARG_tlv_3(...) __VA_ARGS__

static inline void ipack_tlv( ipack_t *ps, uint32_t tag, const char * data, uint32_t len )
{
    _ipack_append( ps, (char*) &tag, sizeof(tag) );
    _ipack_append( ps, (char*) &len, sizeof(len) );
    _ipack_append( ps, data, len );
}

#define IPACK_CB_tlv16n(...)  ipack_tlv16n
#define IPACK_ARG_tlv16n(...) __VA_ARGS__
static inline void ipack_tlv16n( ipack_t *ps, uint16_t tag, const char * data, uint16_t len )
{
    uint16_t tag_n = htons(tag);
    uint16_t len_n = htons(len);
    _ipack_append( ps, (char*)&tag_n, sizeof(tag_n) );
    _ipack_append( ps, (char*)&len_n, sizeof(len_n) );
    _ipack_append( ps, data, len );
}

static inline void ipack_tlv_sl(ipack_t *ps, uint32_t tag, sl_t data)
{
    ipack_tlv(ps, tag, SLSL(data));
}

#define IPACK_CB_tlv_u32(...) ipack_tlv_u32
#define IPACK_ARG_tlv_u32(...) __VA_ARGS__

static inline void ipack_tlv_u32(ipack_t *ps, uint32_t tag, uint32_t value)
{
    ipack_tlv(ps, tag, (char *) &value, sizeof(value));
}

#define IPACK_CB_lps(...)  ipack_lps
#define IPACK_ARG_lps(...) __VA_ARGS__
static inline void ipack_lps( ipack_t *ps, const char * data, uint32_t len )
{
    ipack_u32(ps, len);
    _ipack_append( ps, data, len );
}

#define IPACK_CB_lps16(...) ipack_lps16
#define IPACK_ARG_lps16(...) __VA_ARGS__
static inline void ipack_lps16(ipack_t *ps, const char *data, uint16_t len)
{
    ipack_u16(ps, len);
    _ipack_append(ps, data, len);
}

#define IPACK_CB_lps16n(...) ipack_lps16n
#define IPACK_ARG_lps16n(...) __VA_ARGS__
static inline void ipack_lps16n(ipack_t *ps, const char *data, uint16_t len)
{
    ipack_u16n(ps, len);
    _ipack_append(ps, data, len);
}

#define IPACK_CB_sl(...)  ipack_sl
#define IPACK_ARG_sl(...) __VA_ARGS__
static inline void ipack_sl( ipack_t *ps, sl_t sl )
{
    return ipack_lps( ps, SLSL(sl) );
}

#define IPACK_CB_sl16(...)  ipack_sl16
#define IPACK_ARG_sl16(...) __VA_ARGS__
static inline void ipack_sl16( ipack_t *ps, sl_t sl )
{
    return ipack_lps16( ps, SLSL(sl) );
}

#define IPACK_CB_sl16n(...)  ipack_sl16n
#define IPACK_ARG_sl16n(...) __VA_ARGS__
static inline void ipack_sl16n( ipack_t *ps, sl_t sl )
{
    return ipack_lps16n( ps, SLSL(sl) );
}

#define IPACK_CB_str_to_lps(...)  ipack_str_to_lps
#define IPACK_ARG_str_to_lps(...) __VA_ARGS__

#define IPACK_CB_str_to_sl(...) ipack_str_to_lps
#define IPACK_ARG_str_to_sl(...) __VA_ARGS__

#define IPACK_CB_sls(...) ipack_str_to_lps
#define IPACK_ARG_sls(...) __VA_ARGS__

static inline void ipack_str_to_lps( ipack_t *ps, const char * data )
{
    ipack_lps( ps, data, data ? strlen(data) : 0 );
}

#define IPACK_CB_base64(...)  ipack_base64
#define IPACK_ARG_base64(...) false, __VA_ARGS__
#define IPACK_CB_xbase64(...)  ipack_base64
#define IPACK_ARG_xbase64(...) true, __VA_ARGS__
static inline void ipack_base64(ipack_t *ps, bool x, const char * data, size_t len)
{
    if (!len)
        return;
    uint32_t max_len = (len*4/3)+10;
    ipack_reserve(ps, max_len);
    int stop;
    size_t r;
    if (x)
        r = enc_xbase64_nopad(IPACK_RBUF(ps), IPACK_RLEN(ps), data, len, &stop);
    else
        r = enc_base64_nopad(IPACK_RBUF(ps), IPACK_RLEN(ps), data, len, &stop);

    if (stop != len) {
        IPACK_SET_FAIL(ps);
        return;
    }
    ps->cursor += r;
}

#define IPACK_CB_url_enc(...)  ipack_url_enc
#define IPACK_ARG_url_enc(...) __VA_ARGS__
static inline void ipack_url_enc( ipack_t *ps, char * data, size_t len)
{
    static const char * _upper_hex = "0123456789ABCDEF"; /* don't change case */
    if( IPACK_IS_FAILED( ps ) )
        return;

    if( ipack_reserve( ps, 3 * len ) ) {
        IPACK_SET_FAIL( ps );
        return;
    }

    assert( IPACK_RLEN( ps ) >= 3 * len );

    char * p = data, ch = 0;
    while ((p < data+len) && (ch = *p)) {
        if ( ((ch >= '0') && (ch <= '9')) ||
                ((ch >= 'a') && (ch <= 'z')) ||
                ((ch >= 'A') && (ch <= 'Z')) ||
                (ch == '-') ||
                (ch == '.') ||
                (ch == '_') ||
                (ch == '~')) {
            *IPACK_RBUF( ps ) = ch;
            ps->cursor++;
        } else {
            *IPACK_RBUF( ps ) = '%';
            ps->cursor++;
            *IPACK_RBUF( ps ) = _upper_hex[(ch >> 4) & 0xf];
            ps->cursor++;
            *IPACK_RBUF( ps ) = _upper_hex[ch & 0xf];
            ps->cursor++;
        }
        p++;
    }
}

#define IPACK_CB_sl_to_blob(...) ipack_blob
#define IPACK_ARG_sl_to_blob(sl) SLSL(sl)

#define IPACK_CB_blob(...)  ipack_blob
#define IPACK_ARG_blob(src, ...) (char *) (src), DEFAULT(sizeof(*(src)), __VA_ARGS__)
static inline void ipack_blob( ipack_t *ps, char * data, size_t len )
{
    if (data && len) _ipack_append( ps, data, len );
}

#define IPACK_CB_itimer(...)  ipack_itimer
#define IPACK_ARG_itimer(...) __VA_ARGS__
static inline void ipack_itimer( ipack_t * ps, itimer_t * t )
{
    assert( t->chain );
    log_i( "IPACK: appending %" PRIi64 ", %" PRIu32, t->last_activity, t->chain->timeout );
    _ipack_append( ps, (char*)&t->last_activity, sizeof( t->last_activity ) );
    _ipack_append( ps, (char*)&t->chain->timeout, sizeof( t->chain->timeout ) );
}

#define IPACK_CB_vint(...)  ipack_vint
#define IPACK_ARG_vint(...) __VA_ARGS__
static inline void ipack_vint( ipack_t * ps, const uintmax_t v )
{
#if UINTMAX_MAX != ULLONG_MAX
#error "we assume sizeof(size_t) must be equal sizeof(ullong)"
#endif
   int bits_n = sizeof(v) * 8 - (v ? __builtin_clzll(v) : 63);
   size_t size = bits_n / 7 + (bits_n % 7 ? 1 : 0);

   // We could write directly to buffer, but using alloca + _ipack_append
   // is more simple, safe, and does not require hacking offset
   char * b = (char *)alloca(size);

   for (size_t i = 0; i < size; ++i)
       b[i] = 0x7F & v >> 7 * (size - 1 - i);

   for (size_t i = 0; i < size - 1; ++i)
       b[i] |= 0x80;

   _ipack_append( ps, b, size );
}

#define IPACK_CB_u32_to_vlps(...)  ipack_u32_to_vlps
#define IPACK_ARG_u32_to_vlps(...) __VA_ARGS__
static inline void ipack_u32_to_vlps( ipack_t * ps, uint32_t v )
{
    ipack_vint( ps, sizeof(v) );
    _ipack_append( ps, (char*)&v, sizeof(v) );
}

#define IPACK_CB_vsl(...) ipack_vlps
#define IPACK_ARG_vsl(sl) SLSL(sl)

#define IPACK_CB_vlps(...)  ipack_vlps
#define IPACK_ARG_vlps(...) __VA_ARGS__
static inline void ipack_vlps( ipack_t * ps, const char * data, size_t len )
{
    ipack_vint( ps, len );
    _ipack_append( ps, data, len );
}

#define IPACK_CB_vtlv(...) ipack_vtlv
#define IPACK_ARG_vtlv(...) __VA_ARGS__
static inline void ipack_vtlv(ipack_t *ps, uint32_t tag, sl_t value)
{
    ipack_vint(ps, tag);
    ipack_vlps(ps, value.s, value.l);
}

#define IPACK_CB_strft(...)  ipack_strftime
#define IPACK_ARG_strft(...) __VA_ARGS__
static inline void ipack_strftime( ipack_t * ps, const char * fmt, time_t time )
{
    ipack_reserve( ps, IPACK_ALLOCBY );
    struct tm bdtime;
    localtime_r( &time, &bdtime );
    size_t rc = strftime( IPACK_RBUF( ps ), IPACK_RLEN( ps ), fmt, &bdtime );
    ps->cursor += rc;
}

static void ipack_alarm_zerocb( void * udata )
{
    char * str = (char*)udata;
    log_a( "IPACK: Double reserving for string '%s'", str );
    free( str );
}

#define IPACK_CB_vfmt(...)  ipack_vfmt
#define IPACK_ARG_vfmt(...) false, __VA_ARGS__
#define IPACK_CB_vfmtt(...)  ipack_vfmt
#define IPACK_ARG_vfmtt(...) true, __VA_ARGS__
static inline void ipack_vfmt( ipack_t * ps, bool trunc, const char * fmt, va_list ap )
{
    size_t rest_len;
    int len;
    va_list local_ap;
    bool reserved_already = false;

    // XXX remove it when ps->size_max will appear
    // when it happens also change bonus to 1 if ps->allocby && trunc
    assert( !(!ps->static_buf && trunc) );

    // XXX
    // This strange cycle is for vsnprintf, which may lie about
    // estimated buffer size. See example in http://linux.die.net/man/3/snprintf
    do {
        rest_len = IPACK_RLEN( ps );
        va_copy( local_ap, ap );
        len = vsnprintf( IPACK_RBUF( ps ), rest_len, fmt, local_ap );
        va_end( local_ap );

        if( len < 0 ) {
            log_a( "IPACK: Failed to vsnprintf! strerror '%s', format %s", strerror( errno ), fmt );
            IPACK_SET_FAIL( ps );
            return;
        }

        if( (size_t)len < rest_len ) {
            ps->cursor += len;
            return;
        }

        if( reserved_already )
            zerocb_add( ipack_alarm_zerocb, strdup( IPACK_DATA(ps) ) );

        if( ipack_reserve( ps, len + 1 /* \0 */) ) {
            if( trunc )
                ps->cursor += rest_len - 1 /* \0 */;
            else
                IPACK_SET_FAIL( ps );
            return;
        }
        reserved_already = true;
    } while(1);
}

#define IPACK_CB_fmt(...)  ipack_fmt
#define IPACK_ARG_fmt(...) false, __VA_ARGS__
#define IPACK_CB_fmtt(...)  ipack_fmt
#define IPACK_ARG_fmtt(...) true, __VA_ARGS__
static inline void ipack_fmt( ipack_t * ps, bool trunc, const char * fmt, ... )
{
    va_list ap;
    va_start(ap, fmt);
    ipack_vfmt( ps, trunc, fmt, ap );
    va_end(ap);
}

#ifdef _NEED_SORM_LOG_

#define IPACK_CB_sorm_szl(...)  ipack_sorm_szl
#define IPACK_ARG_sorm_szl(...) __VA_ARGS__
// do printf("<SORM_DELIM>%.*s", szl.l, szl.s)
// or if (!szl.l) printf("<SORM_DELIM>%s", szl.s)
// and screen <SORM_DELIM> in input strings
#define SORM_DELIM '|'
#define SORM_SCREEN '_'
#define SORM_SCREEN_STR "_"
#define SORM_NULL_STR "-"
static inline void ipack_sorm_szl( ipack_t * ps, szl_t szl)
{
    size_t rest_len = IPACK_RLEN( ps );
    size_t wr_len = 0;

    if (rest_len < 2) {
        IPACK_SET_FAIL( ps );
        return;
    }

    *(char*)(IPACK_RBUF( ps )) = SORM_DELIM;
    wr_len++;

    if (!szl.s) {
        szl_t _null = {SORM_NULL_STR, MIN(STRLN(SORM_NULL_STR), rest_len - wr_len)};
        memcpy( IPACK_RBUF( ps ) + wr_len, _null.s, _null.l);
        wr_len += _null.l;
    } else {
        int len = szl.l;
        char * c = szl.s;

        while ( (wr_len < rest_len) &&
                (len ||
                (!szl.l && *c)) )
        {
            if (*c != SORM_DELIM) {
                *(char*)(IPACK_RBUF( ps ) + wr_len) = *c;
                wr_len++;
            } else {
                szl_t screen = {SORM_SCREEN_STR, MIN(STRLN(SORM_SCREEN_STR), rest_len - wr_len)};
                memcpy( IPACK_RBUF( ps ) + wr_len, screen.s, screen.l);
                wr_len += screen.l;
            }

            c++;
            if (len) len--;
        }
    }

    if (wr_len < rest_len) {
        ps->cursor += wr_len;
        return;
    }

    ps->cursor += rest_len;
    IPACK_SET_FAIL( ps );
}

#define IPACK_CB_sorm_delim(...)  ipack_sorm_delim
#define IPACK_ARG_sorm_delim(...) NULL
static inline void ipack_sorm_delim( ipack_t * ps, void * ptr)
{
    char delim = SORM_DELIM;
    _ipack_append (ps, &delim, sizeof(delim));
}


#define IPACK_CB_sorm_vfmtt(...)  ipack_sorm_vfmt
#define IPACK_ARG_sorm_vfmtt(...) false, __VA_ARGS__
static inline void ipack_sorm_vfmt( ipack_t * ps, bool trunc, const char * fmt, va_list ap )
{
    char * start = IPACK_RBUF( ps );
    ipack_vfmt( ps, trunc, fmt, ap );
    if (IPACK_IS_FAILED( ps ))
        return;

    char * end = IPACK_RBUF( ps );
    for (char * c = start; c < end; c++) {
        if (*c == SORM_DELIM)
            *c = SORM_SCREEN;
    }
}

#endif

#define IPACK_CB_sockaddr(...)  ipack_sockaddr
#define IPACK_ARG_sockaddr(...) __VA_ARGS__
static inline void ipack_sockaddr( ipack_t * ps, struct sockaddr * addr)
{
    if (!addr || !(addr->sa_family == AF_INET || addr->sa_family == AF_INET6)) {
        IPACK_SET_FAIL( ps );
        return;
    }

    if (ipack_reserve( ps, addr->sa_family == AF_INET ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN )) {
        IPACK_SET_FAIL( ps );
        return;
    }

    if (addr->sa_family == AF_INET6) {
        inet_ntop ( AF_INET6, &((struct sockaddr_in6 *) addr)->sin6_addr, IPACK_RBUF( ps ), IPACK_RLEN( ps ) );
    } else {
        inet_ntop ( AF_INET, &((struct sockaddr_in *) addr)->sin_addr, IPACK_RBUF( ps ), IPACK_RLEN( ps ) );
    }

    ps->cursor += strlen (IPACK_RBUF( ps ));
}

#define IPACK_CB_rid(...) ipack_rid
#define IPACK_ARG_rid(...) __VA_ARGS__
static inline void ipack_rid(ipack_t *ps, rid_t rid)
{
    ipack_u64(ps, rid.value);
}

// ------- Default IPARSE types ---------
// IN:
//      data - pointer to data need to be parsed,
//      len - length of remaining data. MUST be checked for enough data amount.
// OUT:
//      len of parsed field
//      or -1 on error

#define IPARSE_CB_u8(...)  iparse_u8
#define IPARSE_ARG_u8(...) __VA_ARGS__
static inline int  iparse_u8( char * data, size_t len, uint8_t *x )
{
    if( len < sizeof(*x) ) return -1;
    *x = *(uint8_t*)data;
    return sizeof(*x);
}

#define IPARSE_CB_u16(...)  iparse_u16
#define IPARSE_ARG_u16(...) __VA_ARGS__
static inline int  iparse_u16( char * data, size_t len, uint16_t *x )
{
    if( len < sizeof(*x) ) return -1;
    *x = *(uint16_t*)data;
    return sizeof(*x);
}

#define IPARSE_CB_u32p(...)  iparse_u32p
#define IPARSE_ARG_u32p(...) __VA_ARGS__
static inline int  iparse_u32p( char * data, size_t len, uint32_t **x )
{
    if( len < sizeof(**x) ) return -1;
    *x = (uint32_t*)data;
    return sizeof(**x);
}

#define IPARSE_CB_u32(...)  iparse_u32
#define IPARSE_ARG_u32(...) __VA_ARGS__
static inline int  iparse_u32( char * data, size_t len, uint32_t *x )
{
    if( len < sizeof(*x) ) return -1;
    *x = *(uint32_t*)data;
    return sizeof(*x);
}

#define IPARSE_CB_i64(...)  iparse_i64
#define IPARSE_ARG_i64(...) __VA_ARGS__
static inline int  iparse_i64( char * data, size_t len, int64_t *x )
{
    if( len < sizeof(*x) ) return -1;
    *x = *(int64_t*)data;
    return sizeof(*x);
}

#define IPARSE_CB_u64(...)  iparse_u64
#define IPARSE_ARG_u64(...) __VA_ARGS__
static inline int  iparse_u64( char * data, size_t len, uint64_t *x )
{
    if( len < sizeof(*x) ) return -1;
    *x = *(uint64_t*)data;
    return sizeof(*x);
}

#define IPARSE_CB_i32(...)  iparse_i32
#define IPARSE_ARG_i32(...) __VA_ARGS__
static inline int  iparse_i32( char * data, size_t len, int32_t *x )
{
    if( len < sizeof(*x) ) return -1;
    *x = *(int32_t*)data;
    return sizeof(*x);
}

#define IPARSE_CB_dob(...)  iparse_dob
#define IPARSE_ARG_dob(...) __VA_ARGS__
static inline int  iparse_dob( char * data, size_t len, double *x )
{
    if( len < sizeof(*x) ) return -1;
    *x = *(double*)data;
    return sizeof(*x);
}

#define IPARSE_CB_lps_to_stream(...)  iparse_lps_to_stream
#define IPARSE_ARG_lps_to_stream(...) __VA_ARGS__
static inline int  iparse_lps_to_stream( char * data, size_t len, iparse_t * stream )
{
    dc_t *res = (dc_t*)data;
    if( len < sizeof(*res) || len < dc_size(res) )
        return -1;
    iparse_init( stream, (char *) dc_data(res), dc_len(res) );
    return dc_size(res);
}

#define IPARSE_CB_sl(...)  iparse_sl
#define IPARSE_ARG_sl(...) __VA_ARGS__
static inline int  iparse_sl( char * data, size_t len, sl_t * sl )
{
    dc_t *res = (dc_t*)data;
    if( len < sizeof(*res) || len < dc_size(res) )
        return -1;

    size_t res_len = dc_len(res);
    char *res_data = res_len ? (char *) dc_data(res) : NULL;

    if (sl) *sl = (sl_t){ res_data, res_len };

    return dc_size(res);
}

#define IPARSE_CB_sl_alloc(...)  iparse_sl_alloc
#define IPARSE_ARG_sl_alloc(...) __VA_ARGS__
static inline int  iparse_sl_alloc( char * data, size_t len, sl_t * sl)
{
    *sl = NULLsl;
    sl_t r;
    int rc = iparse_sl(data, len, &r);
    if (rc < 0)
        return -1;
    *sl = sl_dup(r);
    return rc;
}

#define IPARSE_CB_sldup(...)  iparse_sldup
#define IPARSE_ARG_sldup(...) __VA_ARGS__
static inline int  iparse_sldup( char * data, size_t len, sl_t * sl )
{
    int res = iparse_sl(data, len, sl);
    *sl = sldup(*sl);
    return res;
}

#define IPARSE_CB_sl_copy(...)  iparse_sl_copy
#define IPARSE_ARG_sl_copy(...) __VA_ARGS__
static inline int  iparse_sl_copy( char * data, size_t len, sl_t * sl, char * buf, size_t buflen )
{
    dc_t *res = (dc_t*)data;
    if( len < sizeof(*res) || len < dc_size(res) )
        return -1;
    assert( dc_len(res) < buflen );
    memcpy( buf, dc_data(res), dc_len(res) );
    buf[dc_len(res)] = 0;
    *sl = (sl_t){ .s = buf, .l = dc_len(res) };
    return dc_size(res);
}

#define IPARSE_CB_dc(...)  iparse_dc
#define IPARSE_ARG_dc(...) __VA_ARGS__
static inline int  iparse_dc( char * data, size_t len, dc_t ** dc )
{
    dc_t *res = (dc_t*)data;
    if( len < sizeof(*res) || len < dc_size(res) )
        return -1;

    *dc = res;
    return dc_size(res);
}

#define IPARSE_CB_lps(...)  iparse_lps
#define IPARSE_ARG_lps(...) __VA_ARGS__
static inline int  iparse_lps( char * data, size_t len, char ** out_p, uint32_t *out_len_p )
{
    if( len < sizeof(*out_len_p) )
        return -1;
    *out_len_p = *(uint32_t*)data;
    if( *out_len_p > len - sizeof(*out_len_p) )
        return -1;
    *out_p = data + sizeof(*out_len_p);
    return sizeof(*out_len_p) + *out_len_p;
}

#define IPARSE_CB_lps2ds(...)  iparse_lps2ds
#define IPARSE_ARG_lps2ds(...) __VA_ARGS__
static inline int iparse_lps2ds(char * data, size_t len, ds_t* res)
{
    char * lps_data;
    uint32_t lps_len;
    int offset;

    if ((offset = iparse_lps(data, len, &lps_data, &lps_len)) < 0)
        return -1;

    res->size = lps_len;
    res->base = lps_data;

    return offset;
}

#define IPARSE_CB_lps2sl(...)  iparse_lps2sl
#define IPARSE_ARG_lps2sl(...) __VA_ARGS__
static inline int iparse_lps2sl(char * data, size_t len, sl_t* res)
{
    char * lps_data;
    uint32_t lps_len;
    int offset;

    if ((offset = iparse_lps(data, len, &lps_data, &lps_len)) < 0)
        return -1;

    res->l = lps_len;
    res->s = lps_data;

    return offset;
}

#define IPARSE_CB_tlv(...)  iparse_tlv
#define IPARSE_ARG_tlv(...) __VA_ARGS__
static inline int iparse_tlv( char * data, size_t len, tlv_t ** val )
{
    tlv_t * tlv = (tlv_t *)data;
    if (len < sizeof(*tlv) || len < sizeof(*tlv) + tlv->len)
        return -1;

    *val = tlv;
    return sizeof(*tlv) + tlv->len;
}

// use imagine_xlog_timer_add() to create timer from start, to
#define IPARSE_CB_itimer(...)  iparse_itimer
#define IPARSE_ARG_itimer(...) __VA_ARGS__
static inline int  iparse_itimer( char * data, size_t len, int64_t *start, time_t * to )
{
    itimer_t *t;
    assert( sizeof(t->last_activity) == sizeof(*start) );
    assert( sizeof(t->chain->timeout) == sizeof(*to) );

    if( len < sizeof(*start) + sizeof(*to) )
        return -1;

    if( start )
        *start = *(int64_t*)data;
    if( to )
        *to = *(time_t*)(data + sizeof(*start));
    return sizeof(*start) + sizeof(*to);
}

#define IPARSE_CB_vint(...)  iparse_vint
#define IPARSE_ARG_vint(...) __VA_ARGS__
static inline int  iparse_vint( char * data, size_t len, uintmax_t * res )
{
    size_t i;
    *res = 0;
    for (i = 0; !i || data[i - 1] & 0x80; ++i) {
        if (i >= len || 7 * i >= 8 * sizeof(*res)) {
            *res = UINTMAX_MAX;
            return -1;
        }
        *res <<= 7;
        *res |= data[i] & 0x7F;
    }
    return i;
}

#define IPARSE_CB_vint_to_u32(...)  iparse_vint_to_u32
#define IPARSE_ARG_vint_to_u32(...) __VA_ARGS__
static inline int  iparse_vint_to_u32( char * data, size_t len, uint32_t * res)
{
    uintmax_t raw = 0;
    int rc = iparse_vint( data, len, &raw );
    if( raw > UINT32_MAX ) {
        *res = UINT32_MAX;
        return -1;
    }
    *res = (uint32_t)raw;
    return rc;
}

#define IPARSE_CB_vlps(...)  iparse_vlps
#define IPARSE_ARG_vlps(...) __VA_ARGS__
static inline int  iparse_vlps( char * data, size_t len, char ** out_p, uint32_t *out_len_p )
{
    *out_p = NULL;
    *out_len_p = 0;

    int rc;
    rc = iparse_vint_to_u32( data, len, out_len_p );
    if( rc < 0 )
        return -1;
    if( len < rc + *out_len_p )
        return -1;
    *out_p = data + rc;
    return rc + *out_len_p;
}

#define IPARSE_CB_vsl(...) iparse_vlps_to_sl
#define IPARSE_ARG_vsl(...) __VA_ARGS__

#define IPARSE_CB_vlps_to_sl(...)  iparse_vlps_to_sl
#define IPARSE_ARG_vlps_to_sl(...) __VA_ARGS__
static inline int  iparse_vlps_to_sl( char * data, size_t len, sl_t * res )
{
    char * s;
    uint32_t l;
    int r = iparse_vlps( data, len, &s, &l );
    if( r < 0 )
        return -1;
    if(res)
        *res = (sl_t){.s = s, .l = l};

    return r;
}

#define IPARSE_CB_vlps_to_u32(...)  iparse_vlps_to_u32
#define IPARSE_ARG_vlps_to_u32(...) __VA_ARGS__
static inline int  iparse_vlps_to_u32( char * data, size_t len, uint32_t * res )
{
    char * s;
    uint32_t l;
    int r = iparse_vlps( data, len, &s, &l );
    if( r < 0 )
        return -1;
    if( l != 4 )
        return -1;
    if(res)
        *res = *(uint32_t*)s;
    return r;
}

#define IPACK_CB_dc_to_vlps(...) ipack_dc_to_vlps
#define IPACK_ARG_dc_to_vlps(...) __VA_ARGS__
static inline void ipack_dc_to_vlps(ipack_t *ps, const dc_t *dc)
{
    uint32_t len = dc ? dc->len : 0;

    ipack_vint(ps, len);

    if (len) _ipack_append(ps, (const char *)dc->data, dc->len);
}

#define IPACK_CB_str_to_vlps(...) ipack_str_to_vlps
#define IPACK_ARG_str_to_vlps(...) __VA_ARGS__
static inline void ipack_str_to_vlps(ipack_t *ps, const char *str)
{
    uint32_t len = str ? strlen(str) : 0;

    ipack_vint(ps, len);

    if (len) _ipack_append(ps, str, len);
}

#define IPARSE_CB_blob(...)  iparse_blob
#define IPARSE_ARG_blob(...) __VA_ARGS__
static inline int iparse_blob(char * data, size_t len, void **p, size_t n)
{
    if (n > len) return -1;
    *p = data;
    return n;
}

#define IPARSE_CB_memcpy(...) iparse_memcpy
#define IPARSE_ARG_memcpy(dest, ...) dest, DEFAULT(sizeof(*(dest)), __VA_ARGS__)
static inline int iparse_memcpy(char *data, size_t len, void *dest, size_t n)
{
    if (n > len) return -1;
    memcpy(dest, data, n);
    return n;
}

#define IPACK_CB_dc(...) ipack_dc
#define IPACK_ARG_dc(...) __VA_ARGS__
static inline void ipack_dc(ipack_t *ps, dc_t *dc)
{
    _ipack_append(ps, (char *) dc, dc_size(dc));
}

#define IPACK_CB_ds2lps(...) ipack_lps
#define IPACK_ARG_ds2lps(ds) ds.base, (uint32_t) ds.size

#define IPACK_CB_ipack(...) ipack_blob
#define IPACK_ARG_ipack(ps) IPACK_DATA(ps), IPACK_LEN(ps)

#define IPACK_CB_str16n(...)  ipack_str16n
#define IPACK_ARG_str16n(...) __VA_ARGS__
static inline void ipack_str16n(ipack_t *ps, const char * data)
{
    ipack_lps16n(ps, data, data ? strlen(data) : 0);
}

#define IPARSE_CB_u16n(...) iparse_u16n
#define IPARSE_ARG_u16n(...) __VA_ARGS__
static inline int iparse_u16n(char *data, size_t len, uint16_t *x)
{
    if (len < sizeof(*x)) return -1;
    *x = ntohs(*(uint16_t *) data);
    return sizeof(*x);
}

#define IPARSE_CB_u32n(...) iparse_u32n
#define IPARSE_ARG_u32n(...) __VA_ARGS__
static inline int iparse_u32n(char *data, size_t len, uint32_t *x)
{
    if (len < sizeof(*x)) return -1;
    *x = ntohl(*(uint32_t *) data);
    return sizeof(*x);
}

#define IPARSE_CB_lps16n(...) iparse_lps16n
#define IPARSE_ARG_lps16n(...) __VA_ARGS__
static inline int iparse_lps16n(char *data, size_t len, char **out_p, uint16_t *out_len_p)
{
    if (len < sizeof(*out_len_p))
        return -1;

    uint16_t n = ntohs(*(uint16_t *) data);

    if (n > len - sizeof(*out_len_p))
        return -1;

    *out_p      = data + sizeof(*out_len_p);
    *out_len_p  = n;

    return sizeof(*out_len_p) + n;
}

#define IPARSE_CB_lps16n_to_sl(...) iparse_lps16n_to_sl
#define IPARSE_ARG_lps16n_to_sl(...) __VA_ARGS__
static inline int iparse_lps16n_to_sl(char *data, size_t len, sl_t * out)
{
    char * s;
    uint16_t l;
    int r = iparse_lps16n(data, len, &s, &l);
    if (r < 0)
        return -1;
    *out = (sl_t){.s = s, .l = l};
    return r;
}

#define IPARSE_CB_sl16n(...) iparse_lps16n_to_sl
#define IPARSE_ARG_sl16n(...) __VA_ARGS__

#define IPARSE_CB_lps8_to_sl(...) iparse_lps8_to_sl
#define IPARSE_ARG_lps8_to_sl(...) __VA_ARGS__
static inline int iparse_lps8_to_sl(char *data, size_t len, sl_t *out)
{
    if (len < sizeof(uint8_t))
        return -1;

    uint8_t outlen = *(uint8_t *) data;

    if (outlen > len - sizeof(uint8_t))
        return -1;

    if (out) {
        out->s = data + sizeof(uint8_t);
        out->l = outlen;
    }

    return sizeof(uint8_t) + outlen;
}

#define IPARSE_CB_tlv16n(...) iparse_tlv16n
#define IPARSE_ARG_tlv16n(...) __VA_ARGS__
static inline int iparse_tlv16n(char *data, size_t len, uint16_t *tag, sl_t *value)
{
    size_t _len = len;
    int r;

    if ((r = iparse_u16n(data, len, tag)) < 0)
        return -1;

    data += r;
    len -= r;

    if ((r = iparse_lps16n_to_sl(data, len, value)) < 0)
        return -1;

    data += r;
    len -= r;

    return _len - len;
}

#define IPARSE_CB_rid(...) iparse_rid
#define IPARSE_ARG_rid(...) __VA_ARGS__
static inline int iparse_rid(char *data, size_t len, rid_t *rid)
{
    return iparse_u64(data, len, &rid->value);
}

#define IPARSE_CB_vtlv(...) iparse_vtlv
#define IPARSE_ARG_vtlv(...) __VA_ARGS__
static inline int iparse_vtlv(char *data, size_t len, uint32_t *tag, sl_t *value)
{
    uint32_t tag_len;
    void *tag_value;

    int r, t;

    if ((r = iparse_vint_to_u32(data, len, tag)) < 0)
        return -1;

    if ((t = iparse_vlps(data + r, len - r, (char **) &tag_value, &tag_len)) < 0)
        return -1;

    if (value) *value = sl_init(tag_value, tag_len);

    return r + t;
}

static inline void ipack_vlps_start(ipack_t **ps)
{
    assert(ps && *ps && !(*ps)->static_buf);

    ipack_t *next = (*ps)->next;

    if (next)
        ipack_reset(next);
    else {
        next = (ipack_t *)malloc(sizeof(ipack_t));
        ipack_dbuf_init(next, 0, 0);
        next->prev = *ps;

        (*ps)->next = next;
    }

    *ps = next;
}

static inline void ipack_vlps_end(ipack_t **ps)
{
    assert(ps && *ps && !(*ps)->static_buf && (*ps)->prev);

    ipack_t *prev = (*ps)->prev;
    IPACKF(prev, vint(IPACK_LEN(*ps)), ipack(*ps));
    *ps = prev;
}

#ifdef _NEED_GEO_
#include "geo.h"

#define IPACK_CB_gcoord(...)  ipack_gcoord
#define IPACK_ARG_gcoord(...) __VA_ARGS__
static inline void ipack_gcoord( ipack_t *ps, GCoord c )
{
    _ipack_append( ps, (char*)&c.lat, sizeof(c.lat) );
    _ipack_append( ps, (char*)&c.lon, sizeof(c.lon) );
}

#define IPARSE_CB_gcoord(...)  iparse_gcoord
#define IPARSE_ARG_gcoord(...) __VA_ARGS__
static inline int  iparse_gcoord( char * data, size_t len, GCoord * c )
{
    size_t sz = sizeof (double);
    if (iparse_dob (data, len, &c->lat) < 0)
        return -1;
    if (iparse_dob (data + sz, len - sz, &c->lon) < 0)
        return -1;
    return sz * 2;
}

#endif

#endif

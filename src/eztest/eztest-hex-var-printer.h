#ifndef EZTEST_D_EZTEST_D_EZTEST_HEX_VAR_PRINTER_H_
#define EZTEST_D_EZTEST_D_EZTEST_HEX_VAR_PRINTER_H_

#include "eztest-lang.h"
#include "eztest-libc.h"

#if EZTEST_CXX_LANG_ || EZTEST_C_LANG_ >= 2011
EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
EZTEST_NAMESPACE_BEGIN_

EZTEST_PRIVATE_CXX_INL_ int
eztest_hex_print_var(const uint8_t *       eztest_op,
                     EZTEST_STD_NS_ size_t eztest_op_size) {
    
    EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    static const EZTEST_STD_NS_ size_t eztest_k_hexstr_max_bytes = 40;
    EZTEST_STD_NS_ size_t              eztest_op_cur_idx         = 0;
    int                                eztest_truncated          = 0;
    int                                eztest_ret                = 0;
    if (eztest_op_size > eztest_k_hexstr_max_bytes) {
        eztest_op_size   = eztest_k_hexstr_max_bytes;
        eztest_truncated = 1;
    }
    eztest_ret += EZTEST_PRINTF_("[");
    for (; eztest_op_cur_idx < eztest_op_size; ++eztest_op_cur_idx) {
        if (eztest_op_cur_idx != 0) {
            eztest_ret += EZTEST_PRINTF_(", ");
        }
        EZTEST_DISABLE_WUNSAFE_BUFFER_USAGE_
        eztest_ret += EZTEST_PRINTF_(
            "%hhx",
            /* NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic) */
            EZTEST_CAST_(uint8_t, eztest_op[eztest_op_cur_idx] & 0xffU)
            /* NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic) */
        );
        EZTEST_REENABLE_WUNSAFE_BUFFER_USAGE_
    }
    if (eztest_truncated != 0) {
        eztest_ret += EZTEST_PRINTF_(", ...");
    }
    eztest_ret += EZTEST_PRINTF_("]");
    return eztest_ret;
}
EZTEST_NAMESPACE_END_
#endif

#endif

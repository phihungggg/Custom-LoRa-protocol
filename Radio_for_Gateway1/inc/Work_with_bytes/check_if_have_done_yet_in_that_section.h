#ifndef CHECK_IF_HAVE_DONE_YET_IN_THAT_SECTION_H
#define  CHECK_IF_HAVE_DONE_YET_IN_THAT_SECTION_H


#ifdef __cplusplus
extern "C" {
#endif

#include "STANDARD_LIB.h"



uint8_t check_if_have_done_yet_in_that_section(uint32_t beginning_address, uint8_t byte_to_check,  uint8_t count,uint32_t *address_after_jump) ;



#ifdef __cplusplus
}
#endif

#endif
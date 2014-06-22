#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

// Macros to help debug

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr, "[ERROR] (function %s: errno: %s , In %s:%d) \n" M "\n\n", __FUNCTION__, clean_errno() ,__FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error;}

#define check_mem(A) check((A), "Out of memory.")

#endif

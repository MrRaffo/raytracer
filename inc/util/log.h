/*
 * A simple logging system
 * 
 * Consider allowing the user to specify log files, redirecting from terminal
 * is fine for now
 *
 * Paul Rafferty May 2019
 */

#ifndef __log_h__
#define __log_h__

// check for the c version of __func__ to use
#if __STDC_VERSION__ < 199901L
#       if __GNUC__ >= 2
#               define __func__ __FUNCTION__
#       else
#               define __func__ "unknown"
#       endif   // __GNUC__ >= 2
#endif // __STDC_VERSION__

#define log_message(F, T, M, ...) fprintf(F, T "::[%s:%d:%s()]: " M " \n", \
                        __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define log_out(M, ...) fprintf(stdout, M, ##__VA_ARGS__)
#define log_msg(M, ...) fprintf(stdout, "[LOG] " M "\n", ##__VA_ARGS__)
#define log_dbg(M, ...) log_message(stdout, "[DBG]", M, ##__VA_ARGS__)
#define log_wrn(M, ...) log_message(stdout, "[WRN]", M, ##__VA_ARGS__)
#define log_err(M, ...) log_message(stderr, "[ERR]", M, ##__VA_ARGS__)

#endif // __log_h__

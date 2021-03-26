#ifndef __IRPC_COMMON_H__
#define __IRPC_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#define irpc_log(fmt, ...) \
    do { fprintf(stderr, "[server]%s %d: " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__); } while (0)
    
#define IRPC_STRCPY_S(x,y) snprintf(x, sizeof(x) - 1, "%s", y)

#define IRPC_STRCPY_D(x,y) snprintf(x, sizeof(x) - 1, "%d", y)

#define IRPC_ASSERT(x) \
                do { \
                    if((x) == 0) \
                    { \
                        irpc_log("input wrong\n"); \
                        return (-1); \
                    } \
                }while(0)
#define IRPC_VOID_ASSERT(x) \
                do { \
                    if((x) == 0) \
                    { \
                        irpc_log("input wrong\n"); \
                        return ; \
                    } \
                }while(0)

#ifdef __cplusplus
}
#endif
#endif

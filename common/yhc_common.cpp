
#include "yhc_common_type.h"
#include "yhc_common.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>


YHC_VOID logPrint(YHC_LOG_LEVEL_E enPrintLevel, const YHC_CHAR *pFile, const YHC_CHAR *pFunc, YHC_U32 u32Line, const YHC_CHAR *fmt, ...)
{
    YHC_U32         u32Length = 0;
    YHC_CHAR        astrLine[10];
    YHC_CHAR        au32Str[LOG_MAX_CHAR];
    const YHC_CHAR  *pstrTemp = YHC_NULL;
    va_list         arg_ptr;

    va_start(arg_ptr, fmt);

    /* display file name */
    strncpy(au32Str+u32Length, pFile, strlen(pFile));
    u32Length += strlen(pFile);
    au32Str[u32Length] = ':';
    u32Length++;

    /* display function name */
    strncpy(au32Str+u32Length, pFunc, strlen(pFunc));
    u32Length += strlen(pFunc);
    au32Str[u32Length] = ':';
    u32Length++;

    /* display line number */
    sprintf(astrLine, "%d", u32Line);
    strncpy(au32Str+u32Length, astrLine, strlen(astrLine));
    u32Length += strlen(astrLine);
    au32Str[u32Length] = ',';
    u32Length++;

    /* display variable parameter*/
    u32Length += vsprintf(au32Str+u32Length, fmt, arg_ptr);

    au32Str[u32Length] = '\0';

    switch(enPrintLevel)
    {
        case YHC_PRINT_LEVEL_V:
            /* ��ɫ white */
            printf("\033[0;37mV/%s\n\033[0m", au32Str);
            break;

        case YHC_PRINT_LEVEL_D:
            /* ����ɫ deep green*/
            printf("\033[0;36mD/%s\n\033[0m", au32Str);
            break;

        case YHC_PRINT_LEVEL_I:
            /* ��ɫ green */
            printf("\033[0;32mI/%s\n\033[0m", au32Str);
            break;

        case YHC_PRINT_LEVEL_W:
            /* ��ɫ blue */
            printf("\033[0;35mW/%s\n\033[0m", au32Str);
            break;

        case YHC_PRINT_LEVEL_E:
            /* ��ɫ red */
            printf("\033[0;31mE/%s\n\033[0m", au32Str);
            break;

        case YHC_PRINT_LEVEL_F:
            /* ��������˸�����ԡ��»��ߡ���ɫ highilght,twinkle,reverse,underline,red*/
            printf("\033[1;4;5;7;31mF/%s\n\033[0m", au32Str);
            break;

        default:
            printf("%s\n", au32Str);
            break;
    }

    va_end(arg_ptr);
}


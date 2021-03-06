#define LOG_NDEBUG 0
#define LOG_TAG "YHC@logic_picture.cpp"

#include "logic_picture.h"
#include "yhc_common.h"
#include "logic_dbo.h"


pthread_t TestPthreadIdOne;
using namespace android;


static void *testPthreadOne(void *arg)
{
    YHC_DB_TEST1_ST stTest1;
    YHC_DB_TEST2_ST stTest2;
    memset(&stTest1, 0, sizeof(YHC_DB_TEST1_ST));
    memset(&stTest2, 0, sizeof(YHC_DB_TEST2_ST));

    FILE *PfILE;
    PfILE = fopen("/yhc/db/test.db", "w+b");
    YHC_U32 u32Length = 15;

    LOGI("1");

    fseek(PfILE, 0, SEEK_SET);
    LOGI("2");

    fwrite(&u32Length, 1, sizeof(u32Length), PfILE);
    LOGI("3");

    fseek(PfILE, 4, SEEK_SET);
    LOGI("4");
    fwrite(&u32Length, 1, sizeof(u32Length), PfILE);
    LOGI("5");

    fseek(PfILE, 8, SEEK_SET);
    LOGI("6");
    fwrite(&u32Length, 1, sizeof(u32Length), PfILE);
    LOGI("7");
    LOGI("ab");

    while(1)
    {
        YhcDbo::getDbo()->query(YHC_DBO_ATTR_TEST1, &stTest1, sizeof(YHC_DB_TEST1_ST));
        YhcDbo::getDbo()->query(YHC_DBO_ATTR_TEST2, &stTest2, sizeof(YHC_DB_TEST2_ST));
        LOGI("TEST1, u32Frame:%d, u32Width:%d", stTest1.u32Frame, stTest1.u32Width);
        LOGI("TEST2, pName:%s, u32Width:%d", stTest2.pName, stTest2.u32Width);
//        TestService::initinstace()->notify(111, 222);
        sleep(1);
    }
    return (void*)0;
}


YHC_S32 setAspect_Logic(YHC_PICTURE_ASPECT_E enAspect)
{
    LOGE("I AM holly!");
    pthread_create(&TestPthreadIdOne, NULL, testPthreadOne, NULL);
    return YHC_SUCCESS;
}


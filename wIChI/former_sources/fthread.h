#ifndef __FTHREAD_H__
#define __FTHREAD_H__

enum {THREAD_STARTED,THREAD_FINISHED};

struct ThreadData
{
	INChIParams * pINChIParams;
	int (*pf) (int nCode);
};

UINT ThreadFunction(void * data);
UINT ThreadBatchFunction(void * data);

#endif

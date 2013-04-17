#ifndef __DEF__
#define __DEF__

#define F_CPU 24000000UL

typedef enum {
	kActive, kError, kSuspended, kClosed, kBusy
} kStatusEnum;

#endif

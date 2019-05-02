#ifndef SCONTEXT_H
#define SCONTEXT_H

#include "SConfig.h"

enum ETransformationType
{
	ETransformationType_Img,
	ETransformationType_Video,
	ETransformationType_Empty
};

// Global app's context
struct SContext
{
	SConfig config;
};

#endif // SCONTEXT_H

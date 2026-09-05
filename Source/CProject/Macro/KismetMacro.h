#pragma once

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetArrayLibrary.h"

#define KismetDelay(FunctionName,object,Delaytime) \
FLatentActionInfo actionInfo(0,0, FunctionName,object);\
UKismetSystemLibrary::Delay(object, Delaytime, actionInfo);

#define KismetRetriggerableDelay(FunctionName,object,Delaytime) \
FLatentActionInfo actionInfo(0,0, FunctionName,object);\
UKismetSystemLibrary::RetriggerableDelay(object, Delaytime, actionInfo);
#pragma once

#include <type_traits>

#define GetClassName(x) std::remove_reference<decltype(*x)

#define CreateDefaultSubobjectAuto(Component) \
Component = CreateDefaultSubobject<GetClassName(Component)>::type>(#Component)

#define MapAdd(Map,Key,Value) Map.Add(TTuple<decltype(Key),decltype(Value)>(Key,Value))

#define SetPauseTimer(Timer) \
if(!GetWorld()->GetTimerManager().IsTimerPaused(Timer)){GetWorld()->GetTimerManager().PauseTimer(Timer);}

#define SetUnPauseTimer(Timer) \
if(GetWorld()->GetTimerManager().IsTimerPaused(Timer)){GetWorld()->GetTimerManager().UnPauseTimer(Timer);}

#define DestroyActor(Actor) if (IsValid(Actor)) Actor->Destroy();

#define SetAttachRules(RuleName) FAttachmentTransformRules const RuleName(EAttachmentRule::SnapToTarget, true);

#define SpawnActorUseClass(spawnActor,ActorClass,Param)spawnActor = GetWorld()->SpawnActor<GetClassName(spawnActor)>::type > (ActorClass, Param);

#define SpawnActorUseClass_Transform(spawnActor,ActorClass,transform,Param)spawnActor = GetWorld()->SpawnActor<GetClassName(spawnActor)>::type > (ActorClass,transform, Param);


#define PlayMontageCharacter(Class,Montage,PlayRate,Section,DelegateTypeString,x)\
Class::ClearMontageDelegate();\
MontageDelegate = DelegateTypeString;\
PlayAnimMontage(Montage, PlayRate, Section);\
x;\


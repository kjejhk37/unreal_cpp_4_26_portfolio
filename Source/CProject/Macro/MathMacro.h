#pragma once

#define RotatorXYZ(x,y,z) FRotator(y,z,x)

							// y,z,x				x,y,z
#define RotatorToFVectorForm(Pitch,Yaw,Roll) FVector(Roll,Pitch,Yaw)

#define ActorLocalToWorldLocation(Actor,localLocation)\
(Actor->GetActorForwardVector() * localLocation.X + Actor->GetActorUpVector() * localLocation.Z + Actor->GetActorRightVector() * localLocation.Y) + Actor->GetActorLocation();

#define ActorLocalToWorldVector(Actor,localLocation)\
(Actor->GetActorForwardVector() * localLocation.X + Actor->GetActorUpVector() * localLocation.Z + Actor->GetActorRightVector() * localLocation.Y);

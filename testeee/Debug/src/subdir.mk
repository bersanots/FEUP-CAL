################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Bicicleta.cpp \
../src/Interfaces.cpp \
../src/Localizacao.cpp \
../src/Main.cpp \
../src/PontoPartilha.cpp \
../src/Sistema.cpp \
../src/Utente.cpp \
../src/Utilizacao.cpp 

OBJS += \
./src/Bicicleta.o \
./src/Interfaces.o \
./src/Localizacao.o \
./src/Main.o \
./src/PontoPartilha.o \
./src/Sistema.o \
./src/Utente.o \
./src/Utilizacao.o 

CPP_DEPS += \
./src/Bicicleta.d \
./src/Interfaces.d \
./src/Localizacao.d \
./src/Main.d \
./src/PontoPartilha.d \
./src/Sistema.d \
./src/Utente.d \
./src/Utilizacao.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



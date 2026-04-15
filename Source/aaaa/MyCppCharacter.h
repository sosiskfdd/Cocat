#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCppCharacter.generated.h"

// Класс нашего персонажа
UCLASS()
class YOURPROJECTNAME_API AMyCppCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Конструктор
    AMyCppCharacter();

protected:
    // Функция, вызываемая при старте игры
    virtual void BeginPlay() override;

    // Функция для настройки ввода
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // --- Настройка Enhanced Input ---
    // Обработчик движения
    void Move(const struct FInputActionValue& Value);
    // Обработчик прыжка
    void StartJump();
    void StopJump();

    // Ссылки на созданные в редакторе ассеты
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    class UInputMappingContext* InputMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    class UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    class UInputAction* JumpAction;
};
#include "MyCppCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"

// Конструктор
AMyCppCharacter::AMyCppCharacter()
{
    // Необязательно: настраиваем скорость ходьбы
    GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

// Функция, которая вызывается в начале игры
void AMyCppCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Получаем контроллер, управляющий этим персонажем
    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        // Получаем сабсистему Enhanced Input для этого игрока
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            // Добавляем Mapping Context, чтобы активировать наши привязки клавиш
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }
}

// Функция, которая привязывает клавиши к нашим обработчикам
void AMyCppCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Пытаемся привести стандартный InputComponent к EnhancedInputComponent
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Привязываем действие движения
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCppCharacter::Move);
        // Привязываем действие прыжка
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyCppCharacter::StartJump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyCppCharacter::StopJump);
    }
}

// --- Обработчики ввода ---
// Функция для движения (вызывается, пока зажата клавиша)
void AMyCppCharacter::Move(const FInputActionValue& Value)
{
    // Получаем вектор движения из значения действия
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // Получаем направления относительно поворота контроллера
        const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // Добавляем движение
        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

// Функция, вызываемая при нажатии клавиши прыжка
void AMyCppCharacter::StartJump()
{
    Jump();
}

// Функция, вызываемая при отпускании клавиши прыжка
void AMyCppCharacter::StopJump()
{
    StopJumping();
}

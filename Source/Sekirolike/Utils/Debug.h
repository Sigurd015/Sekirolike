#pragma once

namespace Helper
{
	enum LogLevel : uint8
	{
		Error, Warning, Display
	};

	class Debug
	{
	public:
		static void Log(const FString& Msg, const LogLevel Level = LogLevel::Display,
		                int32 InKey = -1)
		{
			if (GEngine)
			{
				FColor Color = FColor::Yellow;
				switch (Level)
				{
				case LogLevel::Error:
					Color = FColor::Red;
					UE_LOG(LogTemp, Error, TEXT("%s"), *Msg);
					break;
				case LogLevel::Warning:
					Color = FColor::Yellow;
					UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
					break;
				default:
				case LogLevel::Display:
					Color = FColor::Green;
					UE_LOG(LogTemp, Display, TEXT("%s"), *Msg);
					break;
				}
#if WITH_EDITOR
				GEngine->AddOnScreenDebugMessage(InKey, 5, Color, Msg);
#endif
			}
		};
	};
}

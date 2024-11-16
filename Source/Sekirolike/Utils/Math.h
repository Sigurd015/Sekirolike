#pragma once

namespace Helper
{
	class Math
	{
	public:
		// Elliptical Grid Mapping
		// See: https://arxiv.org/ftp/arxiv/papers/1509/1509.06344.pdf
		static void EllipticalGridMapping(const FVector2D& InVector, const FVector& Forward, const FVector& Right,
		                                  double& OutNorm, FVector& OutVector)
		{
			FVector2D TempVec = FVector2D::ZeroVector;
			TempVec.X = InVector.X * FMath::Sqrt(1.0f - 0.5f * (InVector.Y * InVector.Y));
			TempVec.Y = InVector.Y * FMath::Sqrt(1.0f - 0.5f * (InVector.X * InVector.X));

			OutNorm = FMath::Sqrt(TempVec.X * TempVec.X + TempVec.Y * TempVec.Y);
			OutVector = TempVec.X * Right + TempVec.Y * Forward;
		}
	};
}

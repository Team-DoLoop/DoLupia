// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGame/Grid2048.h"

#include "Components/TextBlock.h"
#include "UserInterface/MiniGame/MiniGameTile2048Widget.h"

AGrid2048::AGrid2048()
{
    PrimaryActorTick.bCanEverTick = true;
    NewGrid();
    NewNumber();
}

void AGrid2048::BeginPlay()
{
    Super::BeginPlay();

    if (GridWidgetClass)
    {
		for(int x = 0; x < 4; ++x)
		{
			for(int y = 0; y < 4; ++y)
			{
				if (UMiniGameTile2048Widget* Widget = CreateWidget<UMiniGameTile2048Widget>( GetWorld() , GridWidgetClass ))
                {
                    GridWidget.Add( Widget );
                    Widget->SetPositionInViewport(FVector2D(static_cast<float>(x) * 100.f + 100.f, static_cast<float>(y) * 100.f + 100.f));
                    Widget->AddToViewport();
                }
			}
		}


    }

    Draw();
}

void AGrid2048::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
}

void AGrid2048::NewGrid()
{
    Grid.SetNum( 4 );
    for (int32 i = 0; i < 4; ++i)
    {
        Grid[i].SetNum( 4 );
        for (int32 j = 0; j < 4; ++j)
        {
            Grid[i][j] = 0;
        }
    }
}

void AGrid2048::NewNumber()
{
	if(IsFull())
	{   
        for (int32 i = 0; i < 4; ++i)
        {
            for (int32 j = 0; j < 4; ++j)
            {
                GridWidget[i * 4 + j]->ReStartMiniGame();
                Grid[i][j] = 0;
            }

        }

        GEngine->AddOnScreenDebugMessage( 0 , 10.f , FColor::Cyan , TEXT( "Game Over!" ) );
        return;
	}

    while (true)
    {
        int32 x = FMath::RandRange( 0 , 3 );
        int32 y = FMath::RandRange( 0 , 3 );
        if (Grid[x][y] == 0)
        {
            Grid[x][y] = 2;
            return;
        }
    }
}

bool AGrid2048::IsFull() const
{
    for (int32 x = 0; x < 4; ++x)
    {
        for (int32 y = 0; y < 4; ++y)
        {
            if (Grid[x][y] == 0)
                return false;
        }
    }
    return true;
}

FVector AGrid2048::CalculateLocation( int32 X , int32 Y ) const
{
    // 가로와 세로 간격
    float CellSizeX = 100.0f; // 셀 가로 크기
    float CellSizeY = 100.0f; // 셀 세로 크기

    // 그리드의 시작 위치
    float StartX = 0.0f; // 그리드 시작 위치 X
    float StartY = 0.0f; // 그리드 시작 위치 Y

    // 셀의 중심 위치 계산
    float CellCenterX = StartX + (X + 0.5f) * CellSizeX; // 셀 중심 X 위치
    float CellCenterY = StartY + (Y + 0.5f) * CellSizeY; // 셀 중심 Y 위치

    // 실제 위치 반환
    return FVector( CellCenterX , CellCenterY , 0.0f ); // 2D 그리드이므로 Z는 0으로 설정합니다.
}

void AGrid2048::Draw()
{
    if (GridWidget.Num() <= 0) return;


    for (int32 x = 0; x < 4; ++x)
    {
        for (int32 y = 0; y < 4; ++y)
        {
            UpdateCell( x , y , Grid[x][y] );
        }
    }
}

void AGrid2048::SquashColumn( TArray<int32>& Column )
{
    for (int32 dest = 3; dest >= 0; --dest)
    {
        int32 src = dest - 1;
        while (src >= 0 && Column[src] == 0)
            --src;
        if (src < 0)
            break;
        if (Column[dest] == Column[src])
        {
            Column[dest] *= 2;
            Column[src] = 0;
        }
        if (Column[dest] == 0)
        {
            Swap( Column[dest] , Column[src] );
            ++dest;
        }
    }
}

void AGrid2048::FlipVertically()
{
    for (int32 x = 0; x < 4; ++x)
    {
        Swap( Grid[x][0] , Grid[x][3] );
        Swap( Grid[x][1] , Grid[x][2] );
    }
}

void AGrid2048::FlipDiagonally()
{
    Swap( Grid[1][0] , Grid[0][1] );
    Swap( Grid[2][0] , Grid[0][2] );
    Swap( Grid[3][0] , Grid[0][3] );
    Swap( Grid[2][1] , Grid[1][2] );
    Swap( Grid[3][1] , Grid[1][3] );
    Swap( Grid[3][2] , Grid[2][3] );
}

void AGrid2048::Squash( int32 Key )
{
	if(IsFull())
		return;

    const int32 KeyLeft = 0;   // Replace with actual value
    const int32 KeyRight = 1;  // Replace with actual value
    const int32 KeyUp = 2;     // Replace with actual value
    const int32 KeyDown = 3;   // Replace with actual value

    if (Key == KeyLeft || Key == KeyRight)
        FlipDiagonally();
    if (Key == KeyUp || Key == KeyLeft)
        FlipVertically();

    for (int32 x = 0; x < 4; ++x)
        SquashColumn( Grid[x] );

    if (Key == KeyUp || Key == KeyLeft)
        FlipVertically();
    if (Key == KeyLeft || Key == KeyRight)
        FlipDiagonally();
}

void AGrid2048::UpdateCell(int32 x, int32 y, int32 Value)
{

    UMiniGameTile2048Widget* Tile2048Widget = GridWidget[x * 4 + y];

    if (UTextBlock* CellTextBlock = Tile2048Widget->Test)
    {
        if (Value != 0)
        {
            Tile2048Widget->SetTileValue(Value);

            CellTextBlock->SetText( FText::FromString( FString::FromInt( Value ) ) );

            // Set the text color and font size based on the value
            FSlateColor TextColor;
            FSlateFontInfo FontInfo = CellTextBlock->Font;
            FontInfo.Size = 24;  // Default size, adjust as needed

            switch (Value)
            {
            case 2:
                TextColor = FSlateColor( FLinearColor::Black );
                break;
            case 4:
                TextColor = FSlateColor( FLinearColor::Red );
                break;
                // Add more cases for higher values with appropriate colors
            default:
                TextColor = FSlateColor( FLinearColor::Yellow );
                break;
            }

            CellTextBlock->SetColorAndOpacity( TextColor );
            CellTextBlock->SetFont( FontInfo );
        }
        else
        {
            GridWidget[x * 4 + y]->SetTileValue( E2048Color::None );
            CellTextBlock->SetText( FText::FromString( TEXT( "" ) ) );
        }
    }
}

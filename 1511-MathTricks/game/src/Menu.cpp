#include <Menu.h>

Menu::Menu()
{
}

void Menu::DrawMenu()
{
	DrawText("Math Tricks", 375, (540 + (540 * 0.25)) / 8, 70, WHITE);
	DrawText("by 1511", 510, (540 + (540 * 0.25)) / 8 + 70, 45, BLUE);

	DrawText("Input the board size:", 265, (540 + (540 * 0.25)) / 8 + 200, 60, WHITE);

	Rectangle textBox = { 530 , (540 * 0.25) / 8 + 340, 75, 50 };
    static bool mouseOnText = false;
    int framesCounter = 0;

    if (CheckCollisionPointRec(GetMousePosition(), textBox))
    {
        mouseOnText = true;
    }
    else
    {
        mouseOnText = false;
    }


    if (mouseOnText)
    {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        int key = GetCharPressed();

        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (letterCount < 3))
            {
                input[letterCount] = (char)key;
                input[letterCount + 1] = '\0';
                letterCount++;
            }
            if (letterCount == 1)
            {
                input[letterCount] = ' ';
                input[letterCount + 1] = '\0';
                letterCount++;
            }

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            input[letterCount] = '\0';
        }
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (mouseOnText)
    {
        framesCounter++;
    }
    else
    {
        framesCounter = 0;
    }

    DrawRectangleRec(textBox, RAYWHITE);
    if (mouseOnText)
    {
        DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKBLUE);
    }
    else
    {
        DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
    }

    DrawText(input, (int)textBox.x + 5, (int)textBox.y + 8, 40, BLUE);

    inputWidth = input[0] - 48;
    inputHeight = input[2] - 48;

    startGame = StartGame();
}

bool Menu::StartGame()
{
    Rectangle box = { 510,(540 + (540 * 0.25)) / 8 + 400, 125, 50 };

    static bool warn = false;

    DrawText("Play", 510, (540 * 0.25) / 8 + 470, 60, WHITE);
    if (CheckCollisionPointRec({ (float)GetMouseX(), (float)GetMouseY() }, box))
    {
        DrawText("Play", 510, (540 * 0.25) / 8 + 470, 60, SKYBLUE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (inputHeight < 4 || inputHeight > 9 || inputWidth < 4 || inputWidth > 9)
            {
               warn = true;
            }
            else
            {
                return 1;
            }
        }
    }

    if (warn == true)
    {
        DrawText("INPUT NUMBERS BETWEEN 4 and 9", 300, (540 * 0.25) / 8 + 410, 30, GOLD);
    }

    return 0;
}
/*****************************************************************
*
*   Made with Raylib v1.0 - A badge that tells others that your project was made with raylib.
*
*   DESCRIPTION:
*
*   This library supplies a small badge you can insert inside your projects to
*   tell other people that this game/tool was made using raylib.
*
*   CONFIGURATION:
*
*   #define MADE_WITH_RAYLIB_IMPLEMENTATION
*        Generates the implementation of the library into the included file.
*        If not defined, the library is in header only mode and can be included in other headers
*        or source files without problems. But only ONE file should hold the implementation.
*
*   #define MADE_WITH_RAYLIB_PADDING
*       Sets the badge's padding.
*
*   #define MADE_WITH_RAYLIB_FONT_SIZE
*       Sets the badge's font size. Does not change the "made with" text.
*
*   #define MADE_WITH_RAYLIB_DEBUG
*       Logs debug messages.
*
*   LICENSE: MIT License
*
*   Copyright (c) 2023 ThaCuber
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*
*****************************************************************/

#ifndef MADE_WITH_RAYLIB_H
#define MADE_WITH_RAYLIB_H

// Initializes the badge.
void InitMadeWithRaylib();
// Gets the size of the scaled badge.
Vector2 GetMadeWithRaylibBadgeSize(float scale);
// Displays the badge with extra parameters.
void MadeWithRaylibEx(Vector2 pos, float scale, Color textColor, Color backgroundColor, bool center, bool directToWebsite);
// Displays the badge.
void MadeWithRaylib(Vector2 pos, float scale, Color textColor, Color backgroundColor);
// Deinitalizes the badge.
void EndMadeWithRaylib();

#ifndef MADE_WITH_RAYLIB_PADDING
#define MADE_WITH_RAYLIB_PADDING 8
#endif // MADE_WITH_RAYLIB_PADDING

#ifndef MADE_WITH_RAYLIB_FONT_SIZE
#define MADE_WITH_RAYLIB_FONT_SIZE 30
#endif // MADE_WITH_RAYLIB_FONT_SIZE

#endif // MADE_WITH_RAYLIB_H

#ifdef MADE_WITH_RAYLIB_IMPLEMENTATION

static RenderTexture2D madeWithRaylibBadge = {0};
static bool madeWithRaylibInit = false;
static int raylibTextSize = -1;

void InitMadeWithRaylib()
{
#ifdef MADE_WITH_RAYLIB_DEBUG
    TraceLog(LOG_INFO, "MWR: Initializing badge...");
#endif
    if (raylibTextSize == -1) raylibTextSize = MeasureText("raylib", MADE_WITH_RAYLIB_FONT_SIZE);
    madeWithRaylibBadge = LoadRenderTexture(
        raylibTextSize + MADE_WITH_RAYLIB_PADDING*2,
        MADE_WITH_RAYLIB_FONT_SIZE + MADE_WITH_RAYLIB_PADDING*2
    );
    madeWithRaylibInit = true;
#ifdef MADE_WITH_RAYLIB_DEBUG
    TraceLog(LOG_INFO, "MWR: Finished initialized badge.");
#endif
}

Vector2 GetMadeWithRaylibBadgeSize(float scale)
{
    return (Vector2) {
        (raylibTextSize + MADE_WITH_RAYLIB_PADDING*2) * scale,
        (MADE_WITH_RAYLIB_FONT_SIZE + MADE_WITH_RAYLIB_PADDING*2) * scale
    };
}

void MadeWithRaylib(Vector2 pos, float scale, Color textColor, Color backgroundColor)
{
    MadeWithRaylibEx(pos, scale, textColor, backgroundColor, true, true);
}

void MadeWithRaylibEx(Vector2 pos, float scale, Color textColor, Color backgroundColor, bool center, bool directToWebsite)
{
    if (!madeWithRaylibInit)
    {
        TraceLog(LOG_ERROR, "MWR: The badge isn't initialized.");
        return;
    }

    float width = (raylibTextSize + MADE_WITH_RAYLIB_PADDING*2) * scale;
    float height = (MADE_WITH_RAYLIB_FONT_SIZE + MADE_WITH_RAYLIB_PADDING*2) * scale;
    Rectangle actualRect = {pos.x, pos.y, width, height};
    if (center)
    {
        actualRect.x -= width/2;
        actualRect.y -= height/2;
    }

    if (directToWebsite)
    {
        bool inBounds = CheckCollisionPointRec(GetMousePosition(), actualRect);
        SetMouseCursor(inBounds? MOUSE_CURSOR_POINTING_HAND : MOUSE_CURSOR_ARROW);
        if (inBounds && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) OpenURL("https://www.raylib.com/");
    }

    BeginTextureMode(madeWithRaylibBadge);
        ClearBackground(backgroundColor);
        DrawText("made with", MADE_WITH_RAYLIB_PADDING, MADE_WITH_RAYLIB_PADDING, 1, textColor);
        DrawText("raylib", MADE_WITH_RAYLIB_PADDING, MADE_WITH_RAYLIB_PADDING, MADE_WITH_RAYLIB_FONT_SIZE, textColor);
    EndTextureMode();

    DrawTexturePro(
        madeWithRaylibBadge.texture,
        (Rectangle){0, 0, madeWithRaylibBadge.texture.width, -madeWithRaylibBadge.texture.height},
        actualRect, (Vector2){0, 0}, 0, WHITE
    );
}

void EndMadeWithRaylib()
{
    if (!madeWithRaylibInit)
    {
        TraceLog(LOG_ERROR, "MWR: Badge hasn't been initialized.\"\"");
        return;
    }
#ifdef MADE_WITH_RAYLIB_DEBUG
    TraceLog(LOG_INFO, "MWR: Destroying badge...");
#endif
    UnloadRenderTexture(madeWithRaylibBadge);
    madeWithRaylibBadge = (RenderTexture2D){0};
    madeWithRaylibInit = false;
#ifdef MADE_WITH_RAYLIB_DEBUG
    TraceLog(LOG_INFO, "MWR: Finished destroying badge.");
#endif
}

#endif // MADE_WITH_RAYLIB_IMPLEMENTATION

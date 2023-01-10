# Made with Raylib

A badge that tells others that your project was made with raylib.

# Installation

Made with Raylib is a header only library, so just dragging it into your project will do.
And of course, it requires [raylib](https://raylib.com).

# Customization

The library only has 2 customization flags:
```c
#define MADE_WITH_RAYLIB_PADDING 8
#define MADE_WITH_RAYLIB_FONT_SIZE 30
```

# Functions

```c
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
```

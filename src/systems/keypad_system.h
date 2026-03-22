#ifndef KEYPAD_SYSTEM_H
#define KEYPAD_SYSTEM_H

typedef struct {
    Rectangle bounds;
    int value;
} KeypadButton;

typedef struct {
    char password[10];
    int passLength;
    int maxLength;

    bool isOpen;
    bool opening;
    
    int startXkeypad;
    int startYkeypad;
    int size;
    int gap;

    Rectangle panel;
    Rectangle target;
    Rectangle start;
    Rectangle closeButton;
    KeypadButton button[12];

    bool passwordEntered;
    bool passwordCorrect;

    const char *correctPassword;
} Keypad;

void InitKeypad(Keypad *kp);
void HandleUpdateKeypad(Keypad *kp);
void UpdateKeypad(Keypad *kp);
void DrawKeypad(Keypad *kp);

#endif
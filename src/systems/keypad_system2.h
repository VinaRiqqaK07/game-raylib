#ifndef KEYPAD_SYSTEM2_H
#define KEYPAD_SYSTEM2_H

typedef struct {
    Rectangle bounds;
    int value;
} KeypadButton2;

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
    KeypadButton2 button[12];

    bool passwordEntered;
    bool passwordCorrect;

    const char *correctPassword;
} Keypad2;

void InitKeypad2(Keypad2 *kp);
void HandleUpdateKeypad2(Keypad2 *kp);
void UpdateKeypad2(Keypad2 *kp);
void DrawKeypad2(Keypad2 *kp);

#endif
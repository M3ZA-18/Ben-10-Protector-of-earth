#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

struct DialogueLine {
    string name;
    string text;
    Texture texture;
    int side;
};

const float WinW = 1800.0f;
const float WinH = 900.0f;
const float BoxW = 1400.0f;
const float BoxH = 150.0f;
const float MaxDim = 160.0f;
const float DimSpeed = 15.0f;
const float PortraitSpeed = 0.2f;

Texture texhero, texshinra, texgwen;
DialogueLine script[3][5];
int LineCnt[3]{ 5,5 ,5 };

int ActiveDialogue = 0;
int LineNumer = 0;
int CharCount = 0;
float DimNow = 0.0f;
int framecounter = 0;
bool isDialogueActive = false;
bool isTyping = false;
string currentText = "";
string lastSpeaker = "";

Sprite portrait;
Vector2f portraitPos(0, 0);
Text SkipText;
RectangleShape Dim(Vector2f(WinW, WinH));
RectangleShape textBox;
RectangleShape nameBox;
Text nameText;
Text speechText;
ConvexShape Arrow;
Font dialogueFont;
Clock dialogueClock;

void initDialogue() {
    if (!dialogueFont.loadFromFile("arial.ttf")) cout << "Failed to load arial.ttf for dialogue" << endl;

    texhero.loadFromFile("hero.png");
    texshinra.loadFromFile("Shinra_Kageyomi.png");
    texgwen.loadFromFile("gwen.png");

    // Boss 1 start (ActiveDialogue = 0)
    script[0][0] = { "", "Look at you, Tennyson. Walking into your grave with a smile.\n Do you even realize what's coming for you? \n I am Shinra Kageyomi,kid ", texshinra, 1 };
    script[0][1] = { "Ben", "I've faced world eaters and space tyrants, Shinra.\n You're just... a guy with a bad haircut and a sword.", texhero, 0 };
    script[0][2] = { "Shinra Kageyomi", "This 'toy' on your wrist won't save you from the shadows.\n My blade doesn't just cut flesh it claims souls!", texshinra, 1 };
    script[0][3] = { "Shinra Kageyomi", "The spirits inside this steel are hungry, Ben...\n and they're dying to meet you. Literally.", texshinra, 1 };
    script[0][4] = { "Ben", "Tell them to wait their turn. I've got ten different ways\n to kick your butt, and I'm still deciding which one to use!", texhero, 0 };

    // Boss 1 Death (ActiveDialogue = 1)
    script[1][0] = { "Shinra Kageyomi", "No! My shadows... fading? How can a kid with a blinking watch\n outmatch the Master of Souls?!", texshinra, 1 };
    script[1][1] = { "Ben", "It's not just a watch, Shinra. It's the hero inside it.\n (Though the watch definitely helps a lot.)", texhero, 0 };
    script[1][2] = { "Shinra Kageyomi", "Enjoy your 'victory' while it lasts... Even the brightest stars\n eventually get swallowed by the dark.", texshinra, 1 };
    script[1][3] = { "Shinra Kageyomi", "One day, that watch will fail you... and you'll realize\n you're nothing but a boy playing hero!", texshinra, 1 };
    script[1][4] = { "Ben", "You're the third guy this week to tell me that.\n Now go haunt someone else I've got a world to save.", texhero, 0 };

    // Gwen tutorial
    script[2][0] = { "Gwen", "Ben! Do something! And 'running away' doesn't count as a plan!", texgwen, 1 };
    script[2][1] = { "Gwen", "A and D to move, Space to jump.\n Even Greymatter could remember that!", texgwen, 1 };
    script[2][2] = { "Gwen", "K is for punching. Use U for Special moves \n try not to break anything important!", texgwen, 1 };
    script[2][3] = { "Gwen", "Arrows to cycle, Enter to transform. \n And please... pick someone useful this time!", texgwen, 1 };
    script[2][4] = { "Gwen", "You have 30 seconds before you're just 'Normal Ben' again.\n  Don't mess it up!", texgwen, 1 };

    // UI Setup
    SkipText.setFont(dialogueFont);
    SkipText.setString("Press Spacebar or Left Click to skip");
    SkipText.setCharacterSize(30);
    SkipText.setFillColor(Color(200, 200, 200, 200));
    SkipText.setPosition(20, 20);

    textBox.setFillColor(Color(230, 230, 230, 120));
    textBox.setOutlineThickness(5);
    textBox.setOutlineColor(Color::Black);

    nameBox.setFillColor(Color::Black);

    nameText.setFont(dialogueFont);
    nameText.setCharacterSize(36);
    nameText.setFillColor(Color::White);
    nameText.setStyle(Text::Bold);

    speechText.setFont(dialogueFont);
    speechText.setCharacterSize(40);
    speechText.setFillColor(Color::Black);
    speechText.setStyle(Text::Bold);

    Arrow.setPointCount(3);
    Arrow.setFillColor(Color::Black);
    Arrow.setPoint(0, { 0,0 }); Arrow.setPoint(1, { 30,0 }); Arrow.setPoint(2, { 15,15 });
}

void triggerDialogue(int dialogueID) {
    if (!isDialogueActive) {
        isDialogueActive = true;
        ActiveDialogue = dialogueID;
        LineNumer = 0;
        CharCount = 0;
        isTyping = true;
        currentText = script[ActiveDialogue][LineNumer].text;
        portraitPos.x = (script[ActiveDialogue][LineNumer].side == 0) ? -300.0f : WinW + 300.0f;
        lastSpeaker = script[ActiveDialogue][LineNumer].name;
    }
}

void handleDialogueEvents(Event& event) {
    if (event.type == Event::MouseButtonPressed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)) {
        if (isTyping) {
            CharCount = (int)currentText.size();
            isTyping = false;
        }
        else if (LineNumer < LineCnt[ActiveDialogue] - 1) {
            LineNumer++;
            CharCount = 0;
            isTyping = true;
            currentText = script[ActiveDialogue][LineNumer].text;

            if (script[ActiveDialogue][LineNumer].name != lastSpeaker) {
                portraitPos.x = (script[ActiveDialogue][LineNumer].side == 0) ? -300.0f : WinW + 300.0f;
            }
            lastSpeaker = script[ActiveDialogue][LineNumer].name;
        }
        else {
            isDialogueActive = false;
        }
    }
}

void updateDialogue() {
    float dt = dialogueClock.restart().asSeconds();

    // Dimming logic
    if (isDialogueActive && DimNow < MaxDim) {
        DimNow += DimSpeed;
        if (DimNow > MaxDim) DimNow = MaxDim;
    }
    else if (!isDialogueActive && DimNow > 0.0f) {
        DimNow -= DimSpeed;
        if (DimNow < 0.0f) DimNow = 0.0f;
    }
    Dim.setFillColor(Color(0, 0, 0, (int)DimNow));

    if (isDialogueActive) {
        
        if (isTyping) {
            framecounter++;
            if (framecounter >= 2) {
                if (CharCount < (int)currentText.size()) CharCount++;
                else isTyping = false;
                framecounter = 0;
            }
        }
        speechText.setString(currentText.substr(0, CharCount));

        FloatRect textRect = speechText.getLocalBounds();
        speechText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

        float finalH = max(BoxH, textRect.height + 60.0f);
        float centerX = WinW * 0.5f;
        float centerY = WinH * 0.85f;

        textBox.setSize(Vector2f(BoxW, finalH));
        textBox.setOrigin(BoxW / 2.0f, finalH / 2.0f);
        textBox.setPosition(centerX, centerY);
        speechText.setPosition(centerX, centerY);

        nameText.setString(script[ActiveDialogue][LineNumer].name);
        FloatRect NameRect = nameText.getLocalBounds();
        nameBox.setSize(Vector2f(NameRect.width + 40, 50));

        float boxTopLeftX = centerX - (BoxW / 2.0f);
        float boxTopLeftY = centerY - (finalH / 2.0f);
        nameBox.setPosition(boxTopLeftX, boxTopLeftY - 50);
        nameText.setPosition(boxTopLeftX + 20, boxTopLeftY - 45);

        if (!isTyping) {
            Arrow.setPosition(centerX + (BoxW / 2.0f) - 50, centerY + (finalH / 2.0f) - 40);
        }

        portrait.setTexture(script[ActiveDialogue][LineNumer].texture, true);
        FloatRect pBounds = portrait.getLocalBounds();
        float pScale = (WinH * 0.75f) / pBounds.height;
        portrait.setScale(pScale, pScale);
        portrait.setOrigin((script[ActiveDialogue][LineNumer].side == 1) ? pBounds.width : 0, pBounds.height);

        float MaxX = (script[ActiveDialogue][LineNumer].side == 1) ? WinW * 0.95f : WinW * 0.05f;
        float DiffX = MaxX - portraitPos.x;
        float floorY = boxTopLeftY + (pBounds.height * pScale * 0.25f);

        portraitPos.x += DiffX * PortraitSpeed;
        portraitPos.y = floorY;
        portrait.setPosition(portraitPos);
    }
}

void drawDialogue(RenderWindow& window) {
    if (DimNow > 0.5f) {
        window.draw(Dim);
    }
    if (isDialogueActive) {
        window.draw(portrait);
        window.draw(textBox);
        window.draw(nameBox);
        window.draw(nameText);
        window.draw(speechText);
        window.draw(SkipText);
        if (!isTyping) window.draw(Arrow);
    }
}
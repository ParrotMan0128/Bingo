#include <iostream>
#include <time.h>

#define DrawLine cout << "===========================================" << endl

using namespace std;

enum AI_MODE {

    AM_EASY = 1, AM_HARD = 2

};

enum LINE_NUMBER {

    LN_H1,
    LN_H2,
    LN_H3,
    LN_H4,
    LN_H5,
    LN_V1,
    LN_V2,
    LN_V3,
    LN_V4,
    LN_V5,
    LN_LT,
    LN_RT

};

void SetNumber(int* Array);

void Shuffle(int* Array);

AI_MODE SelectAIMode();

void OutputNumber(int* Array);

bool ChangeNumbertoStar(int* Array, int Input);

int SelectAINumber(int* Array, AI_MODE Mode);

int CountBingo(int* Array);

int CountBingoH(int* Array);

int CountBingoV(int* Array);

int CountBingoLTD(int* Array);

int CountBingoRTD(int* Array);

int main()
{

    srand((unsigned int)time(0));

    int iNumber[25] = {};
    int iAINumber[25] = {};

    SetNumber(iNumber);
    SetNumber(iAINumber);

    Shuffle(iNumber);
    Shuffle(iAINumber);

    int iBingo = 0, iAIBingo = 0;

    //AI모드를 선택한다.
    AI_MODE AIMode = SelectAIMode();

    while (true) {

        system("cls");

        DrawLine;

        cout << "[ Player ] Bingo | " << iBingo << endl << endl;

        OutputNumber(iNumber);

        DrawLine;

        cout << "[ AI ] Bingo | " << iAIBingo << endl;

        if (AIMode == AM_EASY) {

            cout << "[ Mode ] Easy" << endl;
                
        }
        else {

            cout << "[ Mode ] Hard" << endl;

        }

        OutputNumber(iAINumber);

        DrawLine;

        if (iBingo >= 5 && iBingo > iAIBingo) {

            cout << "[!] 당신의 승리입니다!" << endl;
            break;

        }
        else if (iBingo >= 5 && iAIBingo >= 5) {

            if (iBingo > iAIBingo) {

                cout << "[!] 당신의 승리입니다!" << endl;
                break;

            }
            else if (iAIBingo > iBingo) {

                cout << "[!] AI의 승리입니다!" << endl;
                break;

            }
            else {

                cout << "[!] 무승부!" << endl;
                break;

            }

        }
        else if (iAIBingo >= 5 && iAIBingo > iBingo) {

            cout << "[!] AI의 승리입니다!" << endl;
            break;

        }

        cout << "[!] 숫자를 입력해주세요 (0 : 종료) >> ";

        int iInput;
        cin >> iInput;

        if (iInput == 0) {

            break;

        }
        else if (iInput < 1 || iInput > 25) {

            continue;

        }

        bool bAcc = ChangeNumbertoStar(iNumber, iInput);
        ChangeNumbertoStar(iAINumber, iInput);

        if (bAcc) {

            continue;

        }

        iInput = SelectAINumber(iAINumber, AIMode);

        ChangeNumbertoStar(iNumber, iInput);
        ChangeNumbertoStar(iAINumber, iInput);

        iBingo = CountBingo(iNumber);
        iAIBingo = CountBingo(iAINumber);

    }

    cout << "[!] 게임을 종료합니다";

    return 0;
    
}

void SetNumber(int* Array) {

    {
        for (int i = 0; i < 25; ++i) {

            Array[i] = i + 1;
        }
    }
}

void Shuffle(int* Array) {

    int iTemp, idx1, idx2;

    for (int i = 0; i < 100; i++) {

        idx1 = rand() % 25;
        idx2 = rand() % 25;

        iTemp = Array[idx1];
        Array[idx1] = Array[idx2];
        Array[idx2] = iTemp;

    }
}

AI_MODE SelectAIMode() {

    int iAIMode;

    while (true) {

        cout << "[!] AI난이도를 선택해주세요" << endl << "[!] 1. 쉬움 | 2. 어려움 | ";
        cin >> iAIMode;

        if (iAIMode >= AM_EASY && iAIMode <= AM_HARD) {

            break;

        }
    }

    return (AI_MODE)iAIMode;
}

void OutputNumber(int* Array) {

    for (int i = 0; i < 5; i++) {

        for (int j = 0; j < 5; j++) {

            if (Array[i * 5 + j] != INT_MAX) {

                cout << Array[i * 5 + j] << "\t";

            }
            else {

                cout << "*\t";

            }
        }

        cout << endl << endl;

    }
}

bool ChangeNumbertoStar(int* Array, int Input) {

    for (int i = 0; i < 25; ++i) {

        if (Input == Array[i]) {

            Array[i] = INT_MAX;

            return false;

        }
    }

    for (int i = 0; i < 25; ++i) {

        if (Input == Array[i]) {

            Array[i] = INT_MAX;

            return false;

        }
    }

    return true;

}

int SelectAINumber(int* Array, AI_MODE Mode) {

    int Input;
    int NoneSelectCount = 0;
    int NoneSelect[25] = {};

    if (Mode == AM_EASY) {

        for (int i = 0; i < 25; ++i) {

            if (Array[i] != INT_MAX) {

                NoneSelect[NoneSelectCount] = Array[i];
                ++NoneSelectCount;

            }
        }

        Input = NoneSelect[rand() % NoneSelectCount];

    }
    else {

        int iLine;
        int iStarCount = 0;
        int iSaveCount = 0;

        for (int i = 0; i < 5; ++i) {

            iStarCount = 0;

            for (int j = 0; j < 5; ++j) {

                if (Array[i * 5 + j] == INT_MAX) {

                    ++iStarCount;

                }
            }

            if (iStarCount < 5 && iSaveCount < iStarCount) {

                iLine = i;
                iSaveCount = iStarCount;

            }
        }

        for (int i = 0; i < 5; ++i) {

            iStarCount = 0;

            for (int j = 0; j < 5; ++j) {

                if (Array[j * 5 + i] == INT_MAX) {

                    ++iStarCount;

                }
            }

            if (iStarCount < 5 && iSaveCount < iStarCount) {

                iLine = i + 5;
                iSaveCount = iStarCount;

            }
        }

        iStarCount = 0;
        for (int i = 0; i < 25; i += 6) {

            if (iStarCount < 5 && iSaveCount < iStarCount) {

                iLine = LN_LT;
                iSaveCount = iStarCount;

            }
        }

        iStarCount = 0;
        for (int i = 4; i < 20; i += 4) {

            if (iStarCount < 5 && iSaveCount < iStarCount) {

                iLine = LN_RT;
                iSaveCount = iStarCount;

            }
        }

        if (iLine <= LN_H5) {

            for (int i = 0; i < 5; ++i) {


                if (Array[iLine * 5 + i] != INT_MAX) {

                    Input = Array[iLine * 5 + i];
                    break;
                }
            }
        }
        else if (iLine <= LN_V5) {

            for (int i = 0; i < 5; ++i) {

                if (Array[i * 5 + (iLine - 5)] != INT_MAX) {

                    Input = Array[i * 5 + (iLine - 5)];
                    break;
                }
            }
        }
        else if (iLine == LN_LT) {

            for (int i = 0; i < 25; i += 6) {

                if (Array[i] != INT_MAX) {

                    Input = Array[i];
                    break;

                }
            }
        }
        else {

            for (int i = 4; i < 20; i += 4) {

                if (Array[i] != INT_MAX) {

                    Input = Array[i];
                    break;

                }
            }
        }
    }

    return Input;
}

int CountBingo(int* Array) {

    int Bingo = 0;

    Bingo = Bingo + CountBingoH(Array);
    Bingo = Bingo + CountBingoV(Array);
    Bingo = Bingo + CountBingoLTD(Array);
    Bingo = Bingo + CountBingoRTD(Array);

    return Bingo;

}

int CountBingoH(int* Array) {

    int Star = 0;
    int Bingo = 0;

    for (int i = 0; i < 5; ++i) {

        Star = 0;

        for (int j = 0; j < 5; ++j) {

            if (Array[i * 5 + j] == INT_MAX) {

                ++Star;

            }
        }

        if (Star == 5) {
            ++Bingo;
        }
    }

    return Bingo;

}

int CountBingoV(int* Array) {

    int Star = 0;
    int Bingo = 0;

    for (int i = 0; i < 5; ++i) {

        Star = 0;

        for (int j = 0; j < 5; ++j) {

            if (Array[j * 5 + i] == INT_MAX) {

                ++Star;

            }
        }

        if (Star == 5) {
            ++Bingo;
        }
    }

    return Bingo;

}

int CountBingoLTD(int* Array) {

    int Star = 0;
    int Bingo = 0;

    for (int i = 0; i < 25; i += 6) {

        if (Array[i] == INT_MAX) {

            ++Star;

        }

        if (Star == 5) {
            ++Bingo;
        }
    }

    return Bingo;

}

int CountBingoRTD(int* Array) {

    int Star = 0;
    int Bingo = 0;

    for (int i = 4; i <= 20; i += 4) {

        if (Array[i] == INT_MAX) {

            ++Star;

        }

        if (Star == 5) {
            ++Bingo;
        }
    }

    return Bingo;

}

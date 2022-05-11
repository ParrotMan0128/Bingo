#include <iostream>
#include <time.h>

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

int main()
{

    srand((unsigned int)time(0));

    int iNumber[25] = {};
    int iAINumber[25] = {};

    for (int i = 0; i < 25; i++) {

        iNumber[i] = i + 1;
        iAINumber[i] = i + 1;

    }

    int iTemp, idx1, idx2;

    for (int i = 0; i < 100; i++) {

        idx1 = rand() % 25;
        idx2 = rand() % 25;

        iTemp = iNumber[idx1];
        iNumber[idx1] = iNumber[idx2];
        iNumber[idx2] = iTemp;

        idx1 = rand() % 25;
        idx2 = rand() % 25;

        iTemp = iAINumber[idx1];
        iAINumber[idx1] = iAINumber[idx2];
        iAINumber[idx2] = iTemp;

    }

    int iBingo = 0, iAIBingo = 0;
    int iAIMode;

    while (true) {

        cout << "[!] AI난이도를 선택해주세요" << endl << "[!] 1. 쉬움 | 2. 어려움 | ";
        cin >> iAIMode;

        if (iAIMode >= AM_EASY && iAIMode <= AM_HARD) {

            break;

        }
        else {

            continue;

        }

    }

    int iNoneSelect[25] = {};
    int iNoneSelectCount = 0;

    while (true) {

        system("cls");

        cout << "===========================================" << endl;

        cout << "[ Player ] Bingo | " << iBingo << endl << endl;

        for (int i = 0; i < 5; i++) {

            for (int j = 0; j < 5; j++) {

                if (iNumber[i * 5 + j] != INT_MAX) {

                    cout << iNumber[i * 5 + j] << "\t";

                }
                else {

                    cout << "*\t";

                }

            }

            cout << endl << endl;

        }

        cout << "===========================================" << endl;

        cout << "[ AI ] Bingo | " << iAIBingo << endl;

        if (iAIMode == AM_EASY) {

            cout << "[ Mode ] Easy" << endl;
                
        }
        else {

            cout << "[ Mode ] Hard" << endl;

        }

        for (int i = 0; i < 5; i++) {

            for (int j = 0; j < 5; j++) {

                if (iAINumber[i * 5 + j] != INT_MAX) {

                    cout << iAINumber[i * 5 + j] << "\t";

                }
                else {

                    cout << "*\t";

                }

            }

            cout << endl << endl;

        }

        cout << "===========================================" << endl;

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

        cout << "[!] 숫자를 입력해주세요 (0 : 종료) | ";

        int iInput;
        cin >> iInput;

        if (iInput == 0) {

            break;

        }
        else if (iInput < 1 || iInput > 25) {

            continue;

        }

        bool bAcc = true;

        for (int i = 0; i < 25; ++i) {

            if (iInput == iNumber[i]) {

                bAcc = false;
                iNumber[i] = INT_MAX;
                break;

            }
        }

        for (int i = 0; i < 25; ++i) {

            if (iInput == iAINumber[i]) {

                bAcc = false;
                iAINumber[i] = INT_MAX;
                break;

            }
        }
        
        if (bAcc == true) {

            continue;

        }

        if (iAIMode == AM_EASY) {

            iNoneSelectCount = 0;

            for (int i = 0; i < 25; ++i) {

                if (iAINumber[i] != INT_MAX) {

                    iNoneSelect[iNoneSelectCount] = iAINumber[i];
                    ++iNoneSelectCount;

                }
            }

            iInput = iNoneSelect[rand() % iNoneSelectCount];

        }
        else {

            int iLine;
            int iStarCount = 0;
            int iSaveCount = 0;

            for (int i = 0; i < 5; ++i) {

                iStarCount = 0;

                for (int j = 0; j < 5; ++j) {

                    if (iAINumber[i * 5 + j] == INT_MAX) {

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

                    if (iAINumber[j * 5 + i] == INT_MAX) {

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

            cout << iLine;

            if (iLine <= LN_H5) {

                for (int i = 0; i < 5; ++i) {


                    if (iAINumber[iLine * 5 + i] != INT_MAX) {

                        iInput = iAINumber[iLine * 5 + i];
                        break;
                    }

                }

            }
            else if (iLine <= LN_V5) {

                for (int i = 0; i < 5; ++i) {

                    if (iAINumber[i * 5 + (iLine - 5)] != INT_MAX) {

                        iInput = iAINumber[i * 5 + (iLine - 5)];
                        break;
                    }
                }
            }
            else if (iLine == LN_LT) {

                for (int i = 0; i < 25; i += 6) {

                    if (iAINumber[i] != INT_MAX) {

                        iInput = iAINumber[i];
                        break;

                    }

                }

            }
            else {

                for (int i = 4; i < 20; i += 4) {

                    if (iAINumber[i] != INT_MAX) {

                        iInput = iAINumber[i];
                        break;

                    }
                }
            }

        }

        for (int i = 0; i < 25; ++i) {

            if (iInput == iNumber[i]) {

                iNumber[i] = INT_MAX;
                break;

            }
        }

        for (int i = 0; i < 25; ++i) {

            if (iInput == iAINumber[i]) {

                iAINumber[i] = INT_MAX;
                break;

            }
        }

        iBingo = iAIBingo = 0;

        int iStar1 = 0, iStar2 = 0;
        int iAIStar1 = 0, iAIStar2 = 0;

        for (int i = 0; i < 5; ++i) {

            iStar1 = iStar2 = iAIStar1 = iAIStar2 = 0;

            for (int j = 0; j < 5; ++j) {

                if (iNumber[i * 5 + j] == INT_MAX) {

                    ++iStar1;

                }

                if (iNumber[j * 5 + i] == INT_MAX) {

                    ++iStar2;

                }

                if (iAINumber[i * 5 + j] == INT_MAX) {

                    ++iAIStar1;

                }

                if (iAINumber[j * 5 + i] == INT_MAX) {

                    ++iAIStar2;

                }
            }

            if (iStar1 == 5) {

                ++iBingo;

            }

            if (iStar2 == 5) {

                ++iBingo;

            }

            if (iAIStar1 == 5) {

                ++iAIBingo;

            }

            if (iAIStar2 == 5) {

                ++iAIBingo;

            }
        }

        iStar1 = iAIStar1 = 0;

        for (int i = 0; i < 25; i += 6) {

            if (iNumber[i] == INT_MAX) {

                ++iStar1;

            }

            if (iStar1 == 5) {

                ++iBingo;

            }

            if (iAINumber[i] == INT_MAX) {

                ++iAIStar1;

            }

            if (iAIStar1 == 5) {

                ++iAIBingo;

            }

        }

        iStar1 = iAIStar1 = 0;

        for (int i = 4; i <= 20; i += 4) {

            if (iNumber[i] == INT_MAX) {

                ++iStar1;

            }

            if (iStar1 == 5) {

                ++iBingo;

            }

            if (iAINumber[i] == INT_MAX) {

                ++iAIStar1;

            }

            if (iAIStar1 == 5) {

                ++iAIBingo;

            }

        }
    }

    cout << "[!] 게임을 종료합니다";

    return 0;
    
}

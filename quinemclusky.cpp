#include "quinemclusky.h"
//----Global Variables
int i, j, temp, NumberOfVariable, NumberOfAllMinterm, NumberOfDontCare, NumberOfEPI = 0, NumberOfRemainingMT, NumberOfRemainingPI, NumberOfPI = 0, PotEPINo = 0, NumberOfPossibleEPI = 1, MinimumNo = 0, Groupable = 1;

int *MintermIndicesDecimal, *MintermIndicesDecimal_DontCare, **Minterm_Binary,
    ****Column, **PI_Index,
    **EPI_Index, *NumberCounter, *ReducedPIChart_X, **ReducedPIChart_Y, **ReducedPIChart,
    *For, **Potential_EPI, *NoOfPIForEPI;
//----End of Global Variables.



//D FF---------------------------------

const vector<char> DFF::VAR = {
    'D', 'Q'};

const map<int, pair<int, int>> DFF::extendedtruthtable =
    {
        {{0, {0, 0}},
         {1, {1, 0}},
         {2, {0, 1}},
         {3, {1, 1}}}};

const map<pair<int, int>, int> DFF::excitationtable = {
                {{0, 0}, 0},
                {{0, 1}, 1},
                {{1, 0}, 0},
                {{1, 1}, 1}};

//--------------------------------------

//SR FF---------------------------------

const map<pair<int, int>, pair<int, int>> SRFF::excitationtable = {
    {{0, 0}, {0, 2}},
    {{0, 1}, {1, 0}},
    {{1, 0}, {0, 1}},
    {{1, 1}, {2, 0}}};

const map<int, pair<int, int>> SRFF::extendedtruthtable =
    {
        {0, {0, 0}},
        {1, {1, 1}},
        {2, {0, 0}},
        {3, {1, 0}},
        {4, {0, 1}},
        {5, {1, 1}},
        {6, {3, 3}},
        {7, {3, 3}}};

const vector<char> SRFF::VAR = {
    'S', 'R', 'Q'};
//---------------------------------------

//JK FF----------------------------------
const map<int, pair<int, int>> JKFF::extendedtruthtable =
    {
        {0, {0, 0}},
        {1, {1, 1}},
        {2, {0, 0}},
        {3, {1, 0}},
        {4, {0, 1}},
        {5, {1, 1}},
        {6, {0, 1}},
        {7, {1, 0}}};

const vector<char> JKFF::VAR = {
    'J', 'K', 'Q'};

const map<pair<int, int>, pair<int, int>> JKFF::excitationtable = {
    {{0, 0}, {0, 2}},
    {{0, 1}, {1, 2}},
    {{1, 0}, {2, 1}},
    {{1, 1}, {2, 0}},
    {{3, 3}, {2, 2}}};

//---------------------------------------

//T FF-------------------------------
const vector<char> TFF::VAR = {
    'T', 'Q'};

const map<int, pair<int, int>> TFF::extendedtruthtable =
    {
        {{0, {0, 0}},
         {1, {1, 1}},
         {2, {0, 1}},
         {3, {1, 0}}}};

const map<pair<int, int>, int> TFF::excitationtable = {
                {{0, 0}, 0},
                {{0, 1}, 1},
                {{1, 0}, 1},
                {{1, 1}, 0}};


//-------------------------------------------------------------------


//MISC METHODS-----------------------------------------------
void printTableDouble(string message, auto excitationtable, auto truthtable, auto variableset1, auto variableset2)
{
    cout << message << endl;
    vector<string> sequenceeight = {"0 0 0", "0 0 1", "0 1 0", "0 1 1", "1 0 0", "1 0 1", "1 1 0", "1 1 1"};

    if (variableset1.size() == 3)
    {
        
            cout << variableset1[0] << " " << variableset1[1] << " " << variableset1[2] << " "
                 << "Q`"
                 << " " << variableset2[0] << " " << variableset2[1] << endl;
            for (size_t i = 0; i != 8; ++i)
            {
                cout << sequenceeight[i] << " " << truthtable[i].second << "  ";
                int firstexc = excitationtable[truthtable[i]].first;
                int secondexc = excitationtable[truthtable[i]].second;
                cout << ((firstexc == 2) ? "X" : to_string(firstexc)) << " ";
                cout << ((secondexc == 2) ? "X" : to_string(secondexc)) << endl;
            }
        
        
    }

    //---------------------------------------------------------------    
    vector<string> sequencefour = {"0 0", "0 1", "1 0", "1 1"};

    if (variableset1.size() == 2)
    {
        
            cout << variableset1[0] << " " << variableset1[1] << " "
                 << "Q`"
                 << " " << variableset2[0] << " " << variableset2[1] << endl;
            for (size_t i = 0; i != 4; ++i)
            {
                cout << sequencefour[i] << " " << truthtable[i].second << "  ";
                int firstexc = excitationtable[truthtable[i]].first;
                int secondexc = excitationtable[truthtable[i]].second;
                cout << ((firstexc == 2) ? "X" : to_string(firstexc)) << " ";
                cout << ((secondexc == 2) ? "X" : to_string(secondexc)) << endl;
            }
        
        
    }  

    cout << endl;
}


void printTableSingle(string message, auto excitationtable, auto truthtable, auto variableset1, auto variableset2)
{
    cout << message << endl;
    vector<string> sequenceeight = {"0 0 0", "0 0 1", "0 1 0", "0 1 1", "1 0 0", "1 0 1", "1 1 0", "1 1 1"};
    vector<string> sequencefour = {"0 0", "0 1", "1 0", "1 1"};
    
    if (variableset1.size() == 2)
    {
            cout << variableset1[0] << " " << variableset1[1] << " "
                 << "Q`"
                 << " " << variableset2[0] << endl;
            for (size_t i = 0; i != 4; ++i)
            {
                cout << sequencefour[i] << " " << truthtable[i].second << "  ";
                int firstexc = excitationtable[truthtable[i]];
                cout << ((firstexc == 2) ? "X" : to_string(firstexc)) << " " << endl;
            }
        
    }

    if (variableset1.size() == 3)
    {
        cout << variableset1[0] << " " << variableset1[1] << " " << variableset1[2] << " "
        << "Q`"
        << " " << variableset2[0] << endl;
   for (size_t i = 0; i != 8; ++i)
   {
       cout << sequenceeight[i] << " " << truthtable[i].second << "  ";
       int firstexc = excitationtable[truthtable[i]];
       cout << ((firstexc == 2) ? "X" : to_string(firstexc)) << " " << endl;
   }
    }

}



//----------------------------------------------------------

//-------FOR T TO OFF-----------

void TFF::ToD()
{
    cout << "\n--------T TO D---------" << endl;
    vector<int> mintermsT;
    vector<int> indexdontcareT;
    
    auto truthtableD = DFF::extendedtruthtable;
    auto excitationT = TFF::excitationtable;
    vector<string> variableset = {"T"};
    printTableSingle("T TO D Truth Table", excitationT, truthtableD, DFF::VAR, variableset);
    for (size_t i = 0; i != truthtableD.size(); ++i)
    {
        if (excitationT[truthtableD[i]] == 1 || excitationT[truthtableD[i]] == 2)
        {
            mintermsT.push_back(i);
            if (excitationT[truthtableD[i]] == 2)
                indexdontcareT.push_back(i);
        }
    }
    cout << endl;
    cout << "The minterms in T are : ";
    for (auto i : mintermsT)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in T are : ";
    for (auto i : indexdontcareT)
        cout << i << " ";
    cout << endl;
    NumberOfVariable = DFF::VAR.size();
    NumberOfAllMinterm = mintermsT.size();
    NumberOfDontCare = indexdontcareT.size();
    //QuineMc(mintermsS, indexdontcareS, {'J', 'K', 'Q'});
    cout << "T = ";
    QuineMc(mintermsT, indexdontcareT, DFF::VAR);
    cout << endl;
    
}


void TFF::ToSR()
{
    cout << "\n--------T TO SR---------" << endl;
    vector<int> mintermsT;
    vector<int> indexdontcareT;
    
    auto truthtableSR = SRFF::extendedtruthtable;
    auto excitationT = TFF::excitationtable;
    vector<string> variableset = {"T"};
    printTableSingle("T TO SR Truth Table", excitationT, truthtableSR, SRFF::VAR, variableset);
    for (size_t i = 0; i != truthtableSR.size(); ++i)
    {
        if (excitationT[truthtableSR[i]] == 1 || excitationT[truthtableSR[i]] == 2)
        {
            mintermsT.push_back(i);
            if (excitationT[truthtableSR[i]] == 2)
                indexdontcareT.push_back(i);
        }
    }
    cout << endl;
    cout << "The minterms in T are : ";
    for (auto i : mintermsT)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in T are : ";
    for (auto i : indexdontcareT)
        cout << i << " ";
    cout << endl;
    NumberOfVariable = SRFF::VAR.size();
    NumberOfAllMinterm = mintermsT.size();
    NumberOfDontCare = indexdontcareT.size();
    //QuineMc(mintermsS, indexdontcareS, {'J', 'K', 'Q'});
    cout << "T = ";
    QuineMc(mintermsT, indexdontcareT, SRFF::VAR);
    cout << endl;
    
}


void TFF::ToJK()
{
    cout << "\n--------T TO JK---------" << endl;
    vector<int> mintermsT;
    vector<int> indexdontcareT;
    
    auto truthtableJK = JKFF::extendedtruthtable;
    auto excitationT = TFF::excitationtable;
    vector<string> variableset = {"T"};
    printTableSingle("T TO JK Truth Table", excitationT, truthtableJK, JKFF::VAR, variableset);
    for (size_t i = 0; i != truthtableJK.size(); ++i)
    {
        if (excitationT[truthtableJK[i]] == 1 || excitationT[truthtableJK[i]] == 2)
        {
            mintermsT.push_back(i);
            if (excitationT[truthtableJK[i]] == 2)
                indexdontcareT.push_back(i);
        }
    }
    cout << endl;
    cout << "The minterms in T are : ";
    for (auto i : mintermsT)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in T are : ";
    for (auto i : indexdontcareT)
        cout << i << " ";
    cout << endl;
    NumberOfVariable = JKFF::VAR.size();
    NumberOfAllMinterm = mintermsT.size();
    NumberOfDontCare = indexdontcareT.size();
    //QuineMc(mintermsS, indexdontcareS, {'J', 'K', 'Q'});
    cout << "T = ";
    QuineMc(mintermsT, indexdontcareT, JKFF::VAR);
    cout << endl;
    
}

//------------------------------


//-------FOR D TO OFF-------------

void DFF::ToT()
{
    cout << "\n--------D TO T---------" << endl;
    vector<int> mintermsD;
    vector<int> indexdontcareD;
    
    auto truthtableT = TFF::extendedtruthtable;
    auto excitationD = DFF::excitationtable;
    vector<string> variableset = {"D"};
    printTableSingle("D TO T Truth Table", excitationD, truthtableT, TFF::VAR, variableset);
    for (size_t i = 0; i != truthtableT.size(); ++i)
    {
        if (excitationD[truthtableT[i]] == 1 || excitationD[truthtableT[i]] == 2)
        {
            mintermsD.push_back(i);
            if (excitationD[truthtableT[i]] == 2)
                indexdontcareD.push_back(i);
        }
    }
    cout << endl;
    cout << "The minterms in D are : ";
    for (auto i : mintermsD)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in D are : ";
    for (auto i : indexdontcareD)
        cout << i << " ";
    cout << endl;
    NumberOfVariable = TFF::VAR.size();
    NumberOfAllMinterm = mintermsD.size();
    NumberOfDontCare = indexdontcareD.size();
    //QuineMc(mintermsS, indexdontcareS, {'J', 'K', 'Q'});
    cout << "D = ";
    QuineMc(mintermsD, indexdontcareD, TFF::VAR);
    cout << endl;
    
}


void DFF::ToSR()
{
    cout << "\n--------D TO SR---------" << endl;
    vector<int> mintermsD;
    vector<int> indexdontcareD;
    
    auto truthtableSR = SRFF::extendedtruthtable;
    auto excitationD = DFF::excitationtable;
    vector<string> variableset = {"D"};
    printTableSingle("D TO SR Truth Table", excitationD, truthtableSR, SRFF::VAR, variableset);
    for (size_t i = 0; i != truthtableSR.size(); ++i)
    {
        if (excitationD[truthtableSR[i]] == 1 || excitationD[truthtableSR[i]] == 2)
        {
            mintermsD.push_back(i);
            if (excitationD[truthtableSR[i]] == 2)
                indexdontcareD.push_back(i);
        }
    }
    cout << endl;
    cout << "The minterms in D are : ";
    for (auto i : mintermsD)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in D are : ";
    for (auto i : indexdontcareD)
        cout << i << " ";
    cout << endl;
    NumberOfVariable = SRFF::VAR.size();
    NumberOfAllMinterm = mintermsD.size();
    NumberOfDontCare = indexdontcareD.size();
    //QuineMc(mintermsS, indexdontcareS, {'J', 'K', 'Q'});
    cout << "D = ";
    QuineMc(mintermsD, indexdontcareD, SRFF::VAR);
    cout << endl;
    
}




void DFF::ToJK()
{
    cout << "\n--------D TO JK---------" << endl;
    vector<int> mintermsD;
    vector<int> indexdontcareD;
    
    auto truthtableJK = JKFF::extendedtruthtable;
    auto excitationD = DFF::excitationtable;
    vector<string> variableset = {"D"};
    printTableSingle("D TO JK Truth Table", excitationD, truthtableJK, JKFF::VAR, variableset);
    for (size_t i = 0; i != truthtableJK.size(); ++i)
    {
        if (excitationD[truthtableJK[i]] == 1 || excitationD[truthtableJK[i]] == 2)
        {
            mintermsD.push_back(i);
            if (excitationD[truthtableJK[i]] == 2)
                indexdontcareD.push_back(i);
        }
    }
    cout << endl;
    cout << "The minterms in D are : ";
    for (auto i : mintermsD)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in D are : ";
    for (auto i : indexdontcareD)
        cout << i << " ";
    cout << endl;
    NumberOfVariable = JKFF::VAR.size();
    NumberOfAllMinterm = mintermsD.size();
    NumberOfDontCare = indexdontcareD.size();
    //QuineMc(mintermsS, indexdontcareS, {'J', 'K', 'Q'});
    cout << "D = ";
    QuineMc(mintermsD, indexdontcareD, JKFF::VAR);
    cout << endl;
    
}

//-------------------------------






//-------FOR SR TO OFF-----------
void SRFF::ToD()
{
    cout << "\n--------SR TO D---------" << endl;
    vector<int> mintermsS;
    vector<int> indexdontcareS;
    vector<int> mintermsR;
    vector<int> indexdontcareR;
    auto truthtableD = DFF::extendedtruthtable;
    auto excitationSR = SRFF::excitationtable;
    vector<string> variableset = {"S", "R"};
    printTableDouble("SR TO D Truth Table", excitationSR, truthtableD, DFF::VAR, variableset);
    for (size_t i = 0; i != truthtableD.size(); ++i)
    {
        if (excitationSR[truthtableD[i]].first == 1 || excitationSR[truthtableD[i]].first == 2)
        {
            mintermsS.push_back(i);
            if (excitationSR[truthtableD[i]].first == 2)
                indexdontcareS.push_back(i);
        }

        if (excitationSR[truthtableD[i]].second == 1 || excitationSR[truthtableD[i]].second == 2)
        {
            mintermsR.push_back(i);
            if (excitationSR[truthtableD[i]].second == 2)
                indexdontcareR.push_back(i);
        }
    }
    cout << endl;
    cout << "The minterms in S are : ";
    for (auto i : mintermsS)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in S are : ";
    for (auto i : indexdontcareS)
        cout << i << " ";
    cout << endl;
    NumberOfVariable = DFF::VAR.size();
    NumberOfAllMinterm = mintermsS.size();
    NumberOfDontCare = indexdontcareS.size();
    //QuineMc(mintermsS, indexdontcareS, {'J', 'K', 'Q'});
    cout << "S = ";
    QuineMc(mintermsS, indexdontcareS, DFF::VAR);
    cout << endl;
    cout << "The minterms in R are : ";
    for (auto i : mintermsR)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in R are : ";
    for (auto i : indexdontcareR)
        cout << i << " ";
    cout << endl;
    NumberOfVariable = DFF::VAR.size();
    NumberOfAllMinterm = mintermsR.size();
    NumberOfDontCare = indexdontcareR.size();
    cout << "R = ";
    QuineMc(mintermsR, indexdontcareR, DFF::VAR);
    cout << endl;
}

void SRFF::ToT()
{
    cout << "\n--------SR TO T---------" << endl;
    vector<int> mintermsS;
    vector<int> indexdontcareS;
    vector<int> mintermsR;
    vector<int> indexdontcareR;
    auto truthtableT = TFF::extendedtruthtable;
    auto excitationSR = SRFF::excitationtable;
    vector<string> variableset = {"S", "R"};
    printTableDouble("SR TO T Truth Table", excitationSR, truthtableT, TFF::VAR, variableset);
    for (size_t i = 0; i != truthtableT.size(); ++i)
    {
        if (excitationSR[truthtableT[i]].first == 1 || excitationSR[truthtableT[i]].first == 2)
        {
            mintermsS.push_back(i);
            if (excitationSR[truthtableT[i]].first == 2)
                indexdontcareS.push_back(i);
        }

        if (excitationSR[truthtableT[i]].second == 1 || excitationSR[truthtableT[i]].second == 2)
        {
            mintermsR.push_back(i);
            if (excitationSR[truthtableT[i]].second == 2)
                indexdontcareR.push_back(i);
        }
    }
    cout << endl;
    cout << "The minterms in S are : ";
    for (auto i : mintermsS)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in S are : ";
    for (auto i : indexdontcareS)
        cout << i << " ";
    cout << endl;
    NumberOfVariable = TFF::VAR.size();
    NumberOfAllMinterm = mintermsS.size();
    NumberOfDontCare = indexdontcareS.size();
    //QuineMc(mintermsS, indexdontcareS, {'J', 'K', 'Q'});
    cout << "S = ";
    QuineMc(mintermsS, indexdontcareS, TFF::VAR);
    cout << endl;
    cout << "The minterms in R are : ";
    for (auto i : mintermsR)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in R are : ";
    for (auto i : indexdontcareR)
        cout << i << " ";
    cout << endl;
    NumberOfVariable = TFF::VAR.size();
    NumberOfAllMinterm = mintermsR.size();
    NumberOfDontCare = indexdontcareR.size();
    cout << "R = ";
    QuineMc(mintermsR, indexdontcareR, TFF::VAR);
    cout << endl;
}

    

void SRFF::ToJK()
{
    cout << "\n--------SR TO JK---------" << endl;
    vector<int> mintermsS;
    vector<int> indexdontcareS;
    vector<int> mintermsR;
    vector<int> indexdontcareR;
    auto truthtableJK = JKFF::extendedtruthtable;
    auto excitationSR = SRFF::excitationtable;
    vector<string> variableset = {"S", "R"};
    printTableDouble("SR TO JK Truth Table", excitationSR, truthtableJK, JKFF::VAR, variableset);
    for (size_t i = 0; i != truthtableJK.size(); ++i)
    {
        if (excitationSR[truthtableJK[i]].first == 1 || excitationSR[truthtableJK[i]].first == 2)
        {
            mintermsS.push_back(i);
            if (excitationSR[truthtableJK[i]].first == 2)
                indexdontcareS.push_back(i);
        }

        if (excitationSR[truthtableJK[i]].second == 1 || excitationSR[truthtableJK[i]].second == 2)
        {
            mintermsR.push_back(i);
            if (excitationSR[truthtableJK[i]].second == 2)
                indexdontcareR.push_back(i);
        }
    }
    cout << endl;
    cout << "The minterms in S are : ";
    for (auto i : mintermsS)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in S are : ";
    for (auto i : indexdontcareS)
        cout << i << " ";
    cout << endl;
    NumberOfVariable = JKFF::VAR.size();
    NumberOfAllMinterm = mintermsS.size();
    NumberOfDontCare = indexdontcareS.size();
    //QuineMc(mintermsS, indexdontcareS, {'J', 'K', 'Q'});
    cout << "S = ";
    QuineMc(mintermsS, indexdontcareS, JKFF::VAR);
    cout << endl;
    cout << "The minterms in R are : ";
    for (auto i : mintermsR)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in R are : ";
    for (auto i : indexdontcareR)
        cout << i << " ";
    cout << endl;
    NumberOfVariable = JKFF::VAR.size();
    NumberOfAllMinterm = mintermsR.size();
    NumberOfDontCare = indexdontcareR.size();
    cout << "R = ";
    QuineMc(mintermsR, indexdontcareR, JKFF::VAR);
    cout << endl;
}

//-------FOR SR TO OFF-----------

//-------FOR JK TO OFF-----------

void JKFF::ToSR()
{
    // printTable(5);
    cout << "\n--------JK TO SR---------" << endl;
    vector<int> mintermsJ;
    vector<int> indexdontcareJ;
    vector<int> mintermsK;
    vector<int> indexdontcareK;
    auto truthtableSR = SRFF::extendedtruthtable;
    auto excitationJK = JKFF::excitationtable;
    vector<string> variableset = {"J", "K"};
    printTableDouble("JK TO SR Truth Table", excitationJK, truthtableSR, SRFF::VAR, variableset);
    for (size_t i = 0; i != truthtableSR.size(); ++i)
    {
        if (excitationJK[truthtableSR[i]].first == 1 || excitationJK[truthtableSR[i]].first == 2)
        {
            mintermsJ.push_back(i);
            if (excitationJK[truthtableSR[i]].first == 2)
                indexdontcareJ.push_back(i);
        }

        if (excitationJK[truthtableSR[i]].second == 1 || excitationJK[truthtableSR[i]].second == 2)
        {
            mintermsK.push_back(i);
            if (excitationJK[truthtableSR[i]].second == 2)
                indexdontcareK.push_back(i);
        }
    }
    cout << endl;
    cout << "The minterms in J are : ";
    for (auto i : mintermsJ)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in J are : ";
    for (auto i : indexdontcareJ)
        cout << i << " ";
    cout << endl;
    NumberOfVariable = SRFF::VAR.size();
    NumberOfAllMinterm = mintermsJ.size();
    NumberOfDontCare = indexdontcareJ.size();
    //QuineMc(mintermsS, indexdontcareS, {'J', 'K', 'Q'});
    cout << "J = ";
    QuineMc(mintermsJ, indexdontcareJ, SRFF::VAR);
    cout << endl;
    cout << "The minterms in K are : ";
    for (auto i : mintermsK)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in K are : ";
    for (auto i : indexdontcareK)
        cout << i << " ";
    cout << endl;
    NumberOfVariable = SRFF::VAR.size();
    NumberOfAllMinterm = mintermsK.size();
    NumberOfDontCare = indexdontcareK.size();
    cout << "K = ";
    QuineMc(mintermsK, indexdontcareK, SRFF::VAR);
    cout << endl;
}

void JKFF::ToD()
{
    cout << "\n--------JK TO D---------" << endl;
    vector<int> mintermsJ;
    vector<int> indexdontcareJ;
    vector<int> mintermsK;
    vector<int> indexdontcareK;
    auto truthtableD = DFF::extendedtruthtable;
    auto excitationJK = JKFF::excitationtable;
    vector<string> variableset = {"J", "K"};
    printTableDouble("JK TO D Truth Table", excitationJK, truthtableD, DFF::VAR, variableset);
    for (size_t i = 0; i != truthtableD.size(); ++i)
    {
        if (excitationJK[truthtableD[i]].first == 1 || excitationJK[truthtableD[i]].first == 2)
        {
            mintermsJ.push_back(i);
            if (excitationJK[truthtableD[i]].first == 2)
                indexdontcareJ.push_back(i);
        }

        if (excitationJK[truthtableD[i]].second == 1 || excitationJK[truthtableD[i]].second == 2)
        {
            mintermsK.push_back(i);
            if (excitationJK[truthtableD[i]].second == 2)
                indexdontcareK.push_back(i);
        }
    }
    cout << endl;

    // mintermsJ = {2, 3};
    // indexdontcareJ = {3};

    cout << "The minterms in J are : ";
    for (auto i : mintermsJ)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in J are : ";
    for (auto i : indexdontcareJ)
        cout << i << " ";
    cout << endl;

    NumberOfVariable = DFF::VAR.size();
    NumberOfAllMinterm = mintermsJ.size();
    NumberOfDontCare = indexdontcareJ.size();
    //QuineMc(mintermsS, indexdontcareS, {'J', 'K', 'Q'});
    cout << "J = ";

    QuineMc(mintermsJ, indexdontcareJ, DFF::VAR);
    //QuineMc({1,2,3}, {1, 3}, {'A', 'B', 'C'});

    cout << endl;

    // mintermsK = {0, 1};
    // indexdontcareK = {0};

    cout << "The minterms in K are : ";
    for (auto i : mintermsK)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in R are : ";
    for (auto i : indexdontcareK)
        cout << i << " ";
    cout << endl;
    NumberOfVariable = DFF::VAR.size();
    NumberOfAllMinterm = mintermsK.size();
    NumberOfDontCare = indexdontcareK.size();
    cout << "K = ";

    QuineMc(mintermsK, indexdontcareK, DFF::VAR);
    //QuineMc({1,2,3}, {1, 3}, {'A', 'B', 'C'});
    cout << endl;
}

void JKFF::ToT()
{
    cout << "\n--------JK TO T---------" << endl;
    vector<int> mintermsJ;
    vector<int> indexdontcareJ;
    vector<int> mintermsK;
    vector<int> indexdontcareK;
    auto truthtableT = TFF::extendedtruthtable;
    auto excitationJK = JKFF::excitationtable;
    vector<string> variableset = {"J", "K"};
    printTableDouble("JK TO T Truth Table", excitationJK, truthtableT, TFF::VAR, variableset);
    for (size_t i = 0; i != truthtableT.size(); ++i)
    {
        if (excitationJK[truthtableT[i]].first == 1 || excitationJK[truthtableT[i]].first == 2)
        {
            mintermsJ.push_back(i);
            if (excitationJK[truthtableT[i]].first == 2)
                indexdontcareJ.push_back(i);
        }

        if (excitationJK[truthtableT[i]].second == 1 || excitationJK[truthtableT[i]].second == 2)
        {
            mintermsK.push_back(i);
            if (excitationJK[truthtableT[i]].second == 2)
                indexdontcareK.push_back(i);
        }
    }
    cout << endl;
    cout << "The minterms in J are : ";
    for (auto i : mintermsJ)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in J are : ";
    for (auto i : indexdontcareJ)
        cout << i << " ";
    cout << endl;
    NumberOfVariable = TFF::VAR.size();
    NumberOfAllMinterm = mintermsJ.size();
    NumberOfDontCare = indexdontcareJ.size();
    //QuineMc(mintermsS, indexdontcareS, {'J', 'K', 'Q'});
    cout << "J = ";
    QuineMc(mintermsJ, indexdontcareJ, TFF::VAR);
    cout << endl;
    cout << "The minterms in K are : ";
    for (auto i : mintermsK)
        cout << i << " ";
    cout << endl;
    cout << "The index of dont care in K are : ";
    for (auto i : indexdontcareK)
        cout << i << " ";
    cout << endl;
    NumberOfVariable = TFF::VAR.size();
    NumberOfAllMinterm = mintermsK.size();
    NumberOfDontCare = indexdontcareK.size();
    cout << "K = ";
    QuineMc(mintermsK, indexdontcareK, TFF::VAR);
    cout << endl;
}
//-------FOR JK TO OFF-----------

//----------------------------------

int QuineMc(vector<int> minterms, vector<int> indexdontcare, vector<char> variablesmin)
{
    int k, l, m, n, x, y, LogicProbe;
    /***********Preparation. Collect the information for the boolean
expression***********/
    vector<int *> d1;
    vector<int **> d2;
    vector<int ***> d3;
    vector<int ****> d4;

    // printf("Please provide the information for the sum of minterms.\n\nHow many variables does it contain?\n");
    // scanf("%d", &NumberOfVariable);

    while (NumberOfVariable <= 0)
    {
        printf("The number of variables should be greater than 0, please enter again:\n\n");
        printf("Please provide the information for the sum of minterms.\n\nHow many variables does it contain?\n");
        scanf("%d", &NumberOfVariable);
    }

    // printf("How many minterms (including Don't-Care minterms) does it contain?\n");
    // scanf("%d", &NumberOfAllMinterm);

    while (NumberOfAllMinterm > pow(2, NumberOfVariable) || NumberOfAllMinterm <= 0)
    {
        printf("The number of minterms cannot be greater than 2^%d nor smaller than 1, please enter again:\n", NumberOfVariable);
        printf("How many minterms (including Don't-Care minterms) does it contain?\n");
        scanf("%d", &NumberOfAllMinterm);
    }

    // printf("How many Don't-Care minterms does it contain?\n");
    // scanf("%d", &NumberOfDontCare);
    while (NumberOfDontCare >= NumberOfAllMinterm || NumberOfDontCare < 0)
    {
        printf("The number of Don't-Care minterms cannot be greater than the number of all minterms nor smaller than 0, please enter again:\n");
        printf("How many Don't-Care minterms does it contain?\n");
        scanf("%d", &NumberOfDontCare);
    }
    MintermIndicesDecimal = (int *)malloc(NumberOfAllMinterm * sizeof(int));
    d1.push_back(MintermIndicesDecimal);
    /* Record the decimal indices representing each minterm */
    MintermIndicesDecimal_DontCare = (int *)malloc(NumberOfDontCare * sizeof(int));
    d1.push_back(MintermIndicesDecimal_DontCare);
    /* Record the decimal indices representing Don't-Care minterms */

    for (i = 0; i < NumberOfAllMinterm; i++)
    {
        // if (i == 0)
        //     printf("Please enter the decimal index of the 1st minterm(in ascending order) : ");
        // else if (i == 1)
        //     printf("Please enter the decimal index of the 2nd minterm(in ascending order) : ");
        // else if (i == 2)
        //     printf("Please enter the decimal index of the 3rd minterm(in ascending order) : ");
        // else
        //     printf("Please enter the decimal index of the %dth minterm(in ascending order) : ", i + 1);
        // scanf("%d", &MintermIndicesDecimal[i]);
        MintermIndicesDecimal[i] = minterms[i];
        if (i != 0 && MintermIndicesDecimal[i] <= MintermIndicesDecimal[i - 1])
        {
            printf("The numbers are not in ascending order, please re-enter all the indices again.\n\n");
            i = -1;
        }
        else if (MintermIndicesDecimal[i] >= pow(2, NumberOfVariable))
        {
            printf("\nThe number should be smaller than %d, please re-enter all the indices again.\n\n", pow(2, NumberOfVariable));
            i = -1;
        }
    }
    if (NumberOfDontCare != 0)
    {
        // printf("\n\nWhich of them are Don't-Care terms?\n\n");
        for (i = 0; i < NumberOfDontCare; i++)
        {
            // if (i == 0)
            //     printf("Please enter the decimal index of the 1st Don't Care minterm (in ascending order):");
            // else if (i == 1)
            //     printf("Please enter the decimal index of the 2nd Don'tCare minterm (in ascending order):");
            // else if (i == 2)
            //     printf("Please enter the decimal index of the 3rd Don'tCare minterm (in ascending order):");
            // else
            //     printf("Please enter the decimal index of the %dth Don'tCare minterm (in ascending order):", i + 1);
            // scanf("%d", &MintermIndicesDecimal_DontCare[i]);
            MintermIndicesDecimal_DontCare[i] = indexdontcare[i];
            if (i != 0 &&
                MintermIndicesDecimal_DontCare[i] <= MintermIndicesDecimal_DontCare[i - 1])
            {
                printf("The numbers are not in ascending order, please re-enter all the indices again.\n\n");
                i = -1;
            }
            else if (MintermIndicesDecimal[i] >= pow(2, NumberOfVariable))
            {
                printf("\nThe number should be smaller than %d, please re-enter all the indices again.\n\n", pow(2, NumberOfVariable));
                i = -1;
            }
        }
    }
    /***********Transform the decimal indices into Binary format and obtain relative
information.***********/
    //Minterm_Binary = (int **)malloc(NumberOfAllMinterm * sizeof(int *));
    Minterm_Binary = (int **)malloc((NumberOfAllMinterm + 1) * sizeof(int *));

    d2.push_back(Minterm_Binary);

    for (i = 0; i < (NumberOfAllMinterm + 1); i++)
    {

        Minterm_Binary[i] = (int *)malloc((NumberOfVariable + 4) * sizeof(int));
        d1.push_back(Minterm_Binary[i]);
    }
    DecimalToBinary();

    for (i = 0; i < NumberOfAllMinterm; i++)
    {
        Minterm_Binary[i][NumberOfVariable] = OneCounter(Minterm_Binary[i], NumberOfVariable);
        Minterm_Binary[i][NumberOfVariable + 1] = 0;
        /* '0' means it hasn't been grouped, '1' means it has been
grouped with other terms */
        Minterm_Binary[i][NumberOfVariable + 2] = MintermIndicesDecimal[i];
        /* this is its original minterm */
        Minterm_Binary[i][NumberOfVariable + 3] = MintermIndicesDecimal[i];
        /* this is all the minterms it consists of */
    }
    /***********Prepare the first column for grouping***********/
    Column = (int ****)malloc((NumberOfVariable + 1) * sizeof(int ***));
    d4.push_back(Column);
    for (i = 0; i < NumberOfVariable + 1; i++)
    {
        Column[i] = (int ***)malloc((NumberOfVariable + 1 - i) * sizeof(int **));
        d3.push_back(Column[i]);
        /* Column[i] contains all the terms in the (i+1)th column
*/
    }

    for (i = 0; i < NumberOfVariable + 1; i++)
    {
        for (j = 0; j < NumberOfVariable + 1 - i; j++)
        {
            Column[i][j] = (int **)malloc(Combination(NumberOfVariable, i, j) * sizeof(int *));
            d2.push_back(Column[i][j]);
            /* Column[i][j]
contains all the terms with j '1's in their binary indices in the (i+1)th column */
            for (k = 0; k < Combination(NumberOfVariable, i, j); k++)
            {
                Column[i][j][k] = NULL;
                /* Column[i][j][k]
represents a term with in the j '1's in their binary indices in the (i+1)th column
*/
            }
        }
    }

    for (i = 0; i < NumberOfVariable + 1; i++)
    {
        for (j = 0, k = 0; j < NumberOfAllMinterm; j++)
        {
            if (Minterm_Binary[j][NumberOfVariable] == i)
            {
                Column[0][i][k++] = Minterm_Binary[j];
                /* Prepare the first grouping column */
            }
        }
    }

    /***********Perform the grouping***********/
    for (i = 0; i < NumberOfVariable + 1; i++)
    {
        if (Groupable)
        {
            Groupable = 0;
            for (j = 0; j < NumberOfVariable - i; j++)
            {
                int p, position;
                m = 0;
                for (k = 0; k < Combination(NumberOfVariable, i, j); k++)
                    if (Column[i][j][k] != NULL)
                    {

                        for (l = 0; l < Combination(NumberOfVariable, i, j + 1); l++)
                        {
                            if (Column[i][j + 1][l] != NULL && Column[i][j + 1][l][NumberOfVariable + 2 + i] > Column[i][j][k][NumberOfVariable + 2 + i] &&
                                IsPowerOfTwo(Column[i][j + 1][l][NumberOfVariable + 2 + i] -
                                             Column[i][j][k][NumberOfVariable + 2 + i]))
                            {
                                LogicProbe = 0 - i;
                                /*This LogicProbe is used to check whether this two terms has the same positions of
'-'(which is represented by '2')*/
                                for (n = 1; n <= i; n++)
                                    for (p = 1; p <= i; p++)

                                        if (Column[i][j + 1][l][NumberOfVariable + 1 + n] == Column[i][j][k][NumberOfVariable + 1 +
                                                                                                             p])
                                        {

                                            LogicProbe++;
                                        }
                                if (LogicProbe == 0)
                                {

                                    Groupable = 1;
                                    Column[i][j][k][NumberOfVariable + 1] = 1;
                                    Column[i][j + 1][l][NumberOfVariable + 1] = 1;
                                    Column[i + 1][j][m] = (int *)malloc((NumberOfVariable + 4 + i + pow(2, i + 1)) * sizeof(int));
                                    d1.push_back(Column[i + 1][j][m]);

                                    for (n = 0; n <= NumberOfVariable + 1 + i; n++)
                                    {

                                        Column[i + 1][j][m][n] = Column[i][j][k][n];
                                    }

                                    Column[i + 1][j][m][NumberOfVariable + 3 + i] = Column[i][j][k][NumberOfVariable + 2 + i];

                                    for (n = NumberOfVariable + 4 + i; n < NumberOfVariable + 4 + i + pow(2, i + 1); n++)

                                        Column[i + 1][j][m][n] = 0;

                                    position = log((Column[i][j + 1][l][NumberOfVariable + 2 + i] -
                                                    Column[i][j][k][NumberOfVariable + 2 + i])) /
                                               log(2);

                                    Column[i + 1][j][m][NumberOfVariable - 1 - position] = 2;
                                    Column[i + 1][j][m][NumberOfVariable + 1] = 0;
                                    Column[i + 1][j][m][NumberOfVariable + 2 + i] = position;

                                    for (p = 0; p < pow(2, i); p++)
                                    {

                                        Column[i + 1][j][m][NumberOfVariable + 4 + i + p] = Column[i][j][k][NumberOfVariable + 3 + i +
                                                                                                            p];
                                    }

                                    for (p = pow(2, i); p < pow(2, i + 1); p++)
                                    {

                                        Column[i + 1][j][m][NumberOfVariable + 4 + i + p] = Column[i][j + 1][l][NumberOfVariable + 3 +
                                                                                                                i + p - (int)pow(2, i)];
                                    }
                                    // free(Column[i + 1][j][m]);
                                    m++;
                                }
                            }
                        }
                    }
            }
        }
    }
    /***********NumberCounter count how many times each decimal index occurs***********/
    NumberCounter = (int *)malloc(pow(2, NumberOfVariable) * sizeof(int));
    d1.push_back(NumberCounter);
    for (i = 0; i < pow(2, NumberOfVariable); i++)
        NumberCounter[i] = 0;
    /***********Record the Prime Implicants(duplicates will be removed)***********/
    PI_Index = (int **)malloc(NumberOfAllMinterm * sizeof(int *));
    d2.push_back(PI_Index);
    for (i = 0; i < NumberOfAllMinterm; i++)
    {
        PI_Index[i] = (int *)malloc(3 * sizeof(int));
        d1.push_back(PI_Index[i]);
    }
    for (i = 0; i < NumberOfVariable + 1; i++)
        for (j = 0; j < NumberOfVariable + 1 - i; j++)
            for (k = 0; k < Combination(NumberOfVariable, i, j); k++)
            {
                if (Column[i][j][k] != NULL &&
                    Column[i][j][k][NumberOfVariable + 1] == 0)
                {
                    LogicProbe = 0 - pow(2, i); /*LogicProbe is used to
check whether this PI is a duplicate*/
                    for (l = k - 1; l >= 0; l--)
                        if (LogicProbe != 0)
                        {
                            LogicProbe = 0 - pow(2, i);
                            for (m = 0; m < pow(2, i); m++)
                                for (n = 0; n < pow(2, i); n++)

                                    if (Column[i][j][l][NumberOfVariable + 3 + i + m] == Column[i][j][k][NumberOfVariable + 3 +
                                                                                                         i + n])
                                    {
                                        LogicProbe++;
                                    }
                        }
                    if (LogicProbe != 0)
                    {
                        PI_Index[NumberOfPI][0] = i;
                        PI_Index[NumberOfPI][1] = j;
                        PI_Index[NumberOfPI][2] = k;
                        NumberOfPI++;
                        for (l = 0; l < pow(2, i); l++)
                        {

                            NumberCounter[Column[i][j][k][NumberOfVariable + 3 + i + l]]++;
                        }
                    }
                }
            }
    /***********Remove the DontCare minterms***********/
    for (i = 0; i < NumberOfDontCare; i++)
        NumberCounter[MintermIndicesDecimal_DontCare[i]] = 0;
    EPI_Index = (int **)malloc(NumberOfAllMinterm * sizeof(int *));
    d2.push_back(EPI_Index);
    /***********In the PI Chart, find the minterms which only occurs once, and select 
the PIs which contain these minterms as EPIs and record them. Then set NumberCounter
of this minterms to 0***********/
    for (i = 0; i < pow(2, NumberOfVariable); i++)
        if (NumberCounter[i] == 1)
            for (j = 0; j < NumberOfPI; j++)
                for (k = 0; k < pow(2, PI_Index[j][0]); k++)
                {

                    if (Column[PI_Index[j][0]][PI_Index[j][1]][PI_Index[j][2]][NumberOfVariable + 3 + PI_Index[j][0] + k] == i)
                    {
                        EPI_Index[NumberOfEPI] = PI_Index[j];
                        for (l = 0; l < pow(2, PI_Index[j][0]); l++)

                            NumberCounter[Column[PI_Index[j][0]][PI_Index[j][1]][PI_Index[j][2]][NumberOfVariable + 3 + PI_Index[j][0] + l]] = 0;
                        NumberOfEPI++;
                        k = pow(2, PI_Index[j][0]);
                    }
                }
    /***********Make the Reduced PI Chart***********/
    NumberOfRemainingMT = 0;
    for (i = 0; i < pow(2, NumberOfVariable); i++)
        if (NumberCounter[i] != 0)
            NumberOfRemainingMT++;
    ReducedPIChart_X = (int *)malloc(NumberOfRemainingMT * sizeof(int));
    d1.push_back(ReducedPIChart_X);
    for (i = 0; i < NumberOfRemainingMT; i++)
        ReducedPIChart_X[i] = -1;
    ReducedPIChart_Y = (int **)malloc(NumberOfPI * sizeof(int *));
    d2.push_back(ReducedPIChart_Y);
    for (i = 0; i < NumberOfPI; i++)
        ReducedPIChart_Y[i] = NULL;
    ReducedPIChart = (int **)malloc(NumberOfRemainingMT * sizeof(int *));
    d2.push_back(ReducedPIChart);
    /***********This is the First Row, consist of the remaining minterms decimal
indices***********/
    for (i = 0, j = 0; j < pow(2, NumberOfVariable); j++)
        if (NumberCounter[j] != 0)
        {
            ReducedPIChart_X[i] = j;
            i++;
        }
    /***********This is the First Column, consist of the remaining PIs***********/
    NumberOfRemainingPI = 0;
    for (i = 0; i < NumberOfPI; i++)
        for (j = 0; j < pow(2, PI_Index[i][0]); j++)
        {

            if (NumberCounter[Column[PI_Index[i][0]][PI_Index[i][1]][PI_Index[i][2]][NumberOfVariable + 3 + PI_Index[i][0] + j]] != 0)
            {
                j = pow(2, PI_Index[i][0]);
                ReducedPIChart_Y[NumberOfRemainingPI] = PI_Index[i];
                NumberOfRemainingPI++;
            }
        }
    int variablevectorindex = 0;
    /***********ReducedPIChart[i][j] represent the information of Reduced PI Chart('1'
means picked, '0' means unpicked)***********/
    if (NumberOfRemainingPI != 0)
    {
        for (i = 0; i < NumberOfRemainingMT; i++)
        {
            ReducedPIChart[i] = (int *)malloc(NumberOfRemainingPI * sizeof(int));
            d1.push_back(ReducedPIChart[i]);
        }
        for (i = 0; i < NumberOfRemainingMT; i++)
            for (j = 0; j < NumberOfRemainingPI; j++)
                ReducedPIChart[i][j] = 0;
        for (i = 0; i < NumberOfRemainingPI; i++)
            for (j = 0; j < pow(2, ReducedPIChart_Y[i][0]); j++)
                for (k = 0; k < NumberOfRemainingMT; k++)

                    if (Column[ReducedPIChart_Y[i][0]][ReducedPIChart_Y[i][1]][ReducedPIChart_Y[i][2]][NumberOfVariable + 3 + ReducedPIChart_Y[i][0] + j] == ReducedPIChart_X[k])
                    {
                        ReducedPIChart[k][i] = 1;
                    }
        /***********Select the EPIs from the Reduced PI Chart***********/
        For = (int *)malloc(NumberOfRemainingMT * sizeof(int));
        d1.push_back(For);
        /* For[i] will be
used in the function 'Recursion_For_Loop(int m)' */
        for (i = 0; i < NumberOfRemainingMT; i++)
        {
            For[i] = -1;
        }
        for (i = 0; i < NumberOfRemainingMT; i++)
            NumberOfPossibleEPI = NumberOfPossibleEPI * NumberCounter[ReducedPIChart_X[i]];

        Potential_EPI = (int **)malloc(NumberOfPossibleEPI * sizeof(int *));
        d2.push_back(Potential_EPI);

        for (i = 0; i < NumberOfPossibleEPI; i++)
        {
            Potential_EPI[i] = (int *)malloc(NumberOfRemainingMT * sizeof(int));
            d1.push_back(Potential_EPI[i]);
        }
        Recursion_For_Loop(NumberOfRemainingMT - 1);
        NoOfPIForEPI = (int *)malloc(NumberOfPossibleEPI * sizeof(int));
        d1.push_back(NoOfPIForEPI);
        /*
NoOfPIForEPI[i] will count how many PIs are in each combination that covers all
minterms */
        for (i = 0; i < NumberOfPossibleEPI; i++)
            NoOfPIForEPI[i] = 0;
        for (i = 0; i < NumberOfPossibleEPI; i++)
            for (j = 0; j < NumberOfRemainingMT; j++)
                if (Potential_EPI[i][j] != -1)
                {
                    NoOfPIForEPI[i]++;
                    for (k = j + 1; k < NumberOfRemainingMT; k++)
                        if (Potential_EPI[i][k] == Potential_EPI[i][j])
                            Potential_EPI[i][k] = -1;
                }
        /***********Find the combination which require the least number of PIs to cover all
minterms***********/
        for (i = 1; i < NumberOfPossibleEPI; i++)
            if (NoOfPIForEPI[i] < NoOfPIForEPI[MinimumNo])
                MinimumNo = i;
        for (i = 0; i < NumberOfRemainingMT; i++)
            if (Potential_EPI[MinimumNo][i] != -1)

                EPI_Index[NumberOfEPI++] = ReducedPIChart_Y[Potential_EPI[MinimumNo][i]];
        /***********Print the final result of minimal SOP expression***********/

        // printf("\nThe simplified SOP expression is:\n\n");
        // printf("\n ");
        for (x = 0; x < NumberOfEPI; x++)
        {
            for (y = 0; y < NumberOfVariable; y++)
            {

                if (Column[EPI_Index[x][0]][EPI_Index[x][1]][EPI_Index[x][2]][y] == 1)
                    printf("%c", variablesmin[y]);
                else if (Column[EPI_Index[x][0]][EPI_Index[x][1]][EPI_Index[x][2]][y] == 0)
                    printf("%c'", variablesmin[y]);
            }
            if (x < NumberOfEPI - 1)
                printf("+");
        }
        // printf("\n\nPress any key to exit...");
        // scanf("%d", &i);
        freeallmem(d1, d2, d3, d4);
        return 0;
    }
    else
    {
        // printf("\n\nThe simplified SOP expression is:\n\n");
        // printf("\n ");
        for (x = 0; x < NumberOfEPI; x++)
        {
            for (y = 0; y < NumberOfVariable; y++)
            {

                if (Column[EPI_Index[x][0]][EPI_Index[x][1]][EPI_Index[x][2]][y] == 1)
                    printf("%c", variablesmin[y]);
                else if (Column[EPI_Index[x][0]][EPI_Index[x][1]][EPI_Index[x][2]][y] == 0)
                    printf("%c'", variablesmin[y]);
            }
            if (x < NumberOfEPI - 1)
                printf("+");
        }
        // printf("\n\nPress any key to exit...");
        // scanf("%d", &i);
        freeallmem(d1, d2, d3, d4);
        return 0;
    }
}

int IsDontCare(int MT)
{
    int i;
    for (i = 0; i < NumberOfDontCare; i++)
        if (MT == MintermIndicesDecimal_DontCare[i])
            return 1;
    return 0;
}

void DecimalToBinary()
{
    int i, j, dividend;
    for (i = 0; i < NumberOfAllMinterm; i++)
    {
        dividend = MintermIndicesDecimal[i];
        for (j = NumberOfVariable - 1; j >= 0; j--)
        {
            Minterm_Binary[i][j] = dividend % 2;
            dividend = dividend / 2;
        }
    }
}

int OneCounter(int *binary, int NumberOfDigit)
{
    int i, count = 0;
    for (i = 0; i <= NumberOfDigit - 1; i++)
    {
        if (binary[i] == 1)
            count++;
    }
    return count;
}

int Combination(int n, int ColumnNo, int k)
{
    int Comb, i, NtoK = 1, Kto1 = 1;
    for (i = n; i >= n - k + 1 - ColumnNo; i--)
    {
        NtoK = i * NtoK;
    }
    for (i = k; i >= 1; i--)
    {
        Kto1 = i * Kto1;
    }
    Comb = NtoK / Kto1;
    return Comb;
}

int IsPowerOfTwo(int n)
{
    return (floor(log(n) / log(2)) == (log(n) / log(2)));
}

void Recursion_For_Loop(int m)
{
    int n = m;
    for (For[n] = 0; For[n] < NumberOfRemainingPI; For[n]++)
    {
        if (ReducedPIChart[NumberOfRemainingMT - 1 - n][For[n]])
        {
            if (n > 0)
            {
                m = n;
                m--;
                Recursion_For_Loop(m);
            }
            else if (n == 0)
            {
                for (i = 0; i < NumberOfRemainingMT; i++)
                {

                    Potential_EPI[PotEPINo][i] = For[NumberOfRemainingMT - 1 - i];
                }
                PotEPINo++;
            }
        }
    }
}

void freeallmem(vector<int *> d1, vector<int **> d2, vector<int ***> d3, vector<int ****> d4)
{
    for (auto ptr : d1)
    {
        free(ptr);
    }

    for (auto ptr : d2)
    {
        //if (!(ptr == Minterm_Binary))
        free(ptr);
    }
    for (auto ptr : d3)
        free(ptr);

    for (auto ptr : d4)
        free(ptr);
    //printf ("\nMinter : %p", Minterm_Binary);

    // for (int counter = 0; counter <= NumberOfAllMinterm; ++counter)
    // {
    //     Minterm_Binary[counter] = NULL;
    // }

    // free(Minterm_Binary); //Freeing Minterm_Binary before NULLing it gives an exception
    //Don't know what it is but I'm not able to solve it.
    //Minterm_Binary = NULL;
    Minterm_Binary = NULL;
    Column = NULL;
    NumberCounter = NULL;
    PI_Index = NULL;
    EPI_Index = NULL;
    ReducedPIChart_X = NULL;
    ReducedPIChart_Y = NULL;
    ReducedPIChart = NULL;
    Potential_EPI = NULL;
    NoOfPIForEPI = NULL;

    // if (Potential_EPI != NULL)

    MinimumNo = PotEPINo = NumberOfPI = NumberOfRemainingPI = NumberOfRemainingMT = NumberOfEPI = NumberOfDontCare = NumberOfAllMinterm = NumberOfVariable = temp = j = i = 0;

    Groupable = NumberOfPossibleEPI = 1;
}
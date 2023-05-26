#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;
// Lavoro di gruppo di: Tardi Giuseppe(337492) - Orsi Alina(335150)

//Proprietà:
int calculateScore(char char1, char char2) {
    // Caratteri identici
    if (char1 == char2) {
        return 5; 
    } 
    // Simboli speciali
    else if ((char1 == '{' || char1 == '}' || char1 == '=' || char1 == '&' || char1 == '|') &&
               (char2 == '{' || char2 == '}' || char2 == '=' || char2 == '&' || char2 == '|')) {
        return 5;
    } 
    // Cifre aritmetiche
    else if (isdigit(char1) && isdigit(char2)) {
        return 3;
    } 
    // Match di caratteri (case sensitive)
    else if (char1 == char2) {
        return 2;  
    }
    // Caratteri diversi
    else {
        return -1;  
    }
}
//Algoritmo LCS
string longestCommonSubsequence(const string& source1, const string& source2) {
    int m = source1.length();
    int n = source2.length();

    // Inizializzazione della matrice dei punteggi
    vector<vector<int>> scores(m + 1, vector<int>(n + 1, 0));

    // Calcolo dei punteggi
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int score = calculateScore(source1[i - 1], source2[j - 1]);
            scores[i][j] = max({scores[i - 1][j], scores[i][j - 1], scores[i - 1][j - 1] + score});
        }
    }

    // Costruzione della sottosequenza comune con il punteggio massimo
    string lcs;
    int i = m;
    int j = n;
    while (i > 0 && j > 0) {
        int score = calculateScore(source1[i - 1], source2[j - 1]);
        if (scores[i][j] == scores[i - 1][j - 1] + score) {
            lcs = source1[i - 1] + lcs;
            i--;
            j--;
        } else if (scores[i][j] == scores[i - 1][j]) {
            i--;
        } else {
            j--;
        }
    }
    return lcs;
}
int main() {
    string file1 = "file1.txt";
    string file2 = "file2.txt";

    // Lettura del contenuto di file1
    ifstream file1Stream(file1);
    if (!file1Stream) {
        cerr << "Errore durante l'apertura di " << file1 << endl;
        return 1;
    }

    string source1((istreambuf_iterator<char>(file1Stream)), istreambuf_iterator<char>());
    file1Stream.close();

    // Lettura del contenuto di file2
    ifstream file2Stream(file2);
    if (!file2Stream) {
        cerr << "Errore durante l'apertura di " << file2 << endl;
        return 1;
    }

    string source2((istreambuf_iterator<char>(file2Stream)), istreambuf_iterator<char>());
    file2Stream.close();

    auto score1 = longestCommonSubsequence(source1, source2);
    auto score2 = longestCommonSubsequence(source2, source1);

    if (score1 > score2) {
        cout << "Il miglior file di testo e' " << file1 << endl;
    } else if (score2 > score1) {
        cout << "Il miglior file di testo e' " << file2 << endl;
    } else {
        cout << "I due file di testo hanno una sottosequenza comune con lo stesso punteggio massimo." << endl;
    }
    return 0;
}
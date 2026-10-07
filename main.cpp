#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <fstream>

using namespace std;

bool contient(string mot1, string mot2){
    int j = 0;
    for (int i = 0; i < mot1.length() && j < mot2.length(); i++){
        if (mot1[i] == mot2[j]){
            j++;
        }
    }
    return j == mot2.length();
}

bool contientAvecFind(const string& mot1, const string& mot2) {
    size_t pos = 0;
    for (size_t i = 0; i < mot2.size(); i++) {
        pos = mot1.find(mot2[i], pos);
        if (pos == string::npos)
            return false;
        pos++;
    }
    return true;
}

vector<string> chargerFichier(const string& nomFichier) {
    vector<string> mots;
    ifstream f(nomFichier.c_str());
    string mot;

    if (!f) {
        cout << "Impossible d'ouvrir " << nomFichier << endl;
        return mots;
    }

    while (f >> mot)
        mots.push_back(mot);

    return mots;
}

void remplacerDansVecteur(vector<string>& texte, const string& aChercher, const string& remplacant) {
    if (aChercher.empty()) return;

    for (size_t i = 0; i < texte.size(); i++) {
        size_t pos = 0;
        while ((pos = texte[i].find(aChercher, pos)) != string::npos) {
            texte[i].replace(pos, aChercher.length(), remplacant);
            pos += remplacant.length();
        }
    }
}

int main()
{
    string mot2,nouveauMot;

    cout << "Donner mot2 (mot a chercher) : ";
    cin >> mot2;

    cout << "Donner le mot de remplacement : ";
    cin >> nouveauMot;

    vector<string> roman = chargerFichier("roman.txt");
    cout << "Nombre de mots dans le fichier : " << roman.size() << endl;

    int nb1 = 0;
    auto debut1 = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < roman.size(); i++) {
        if (contient(roman[i], mot2))
            nb1++;
    }
    auto fin1 = chrono::high_resolution_clock::now();
    auto duree1 = chrono::duration_cast<chrono::microseconds>(fin1 - debut1);

    int nb2 = 0;
    auto debut2 = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < roman.size(); i++) {
        if (contientAvecFind(roman[i], mot2))
            nb2++;
    }
    auto fin2 = chrono::high_resolution_clock::now();
    auto duree2 = chrono::duration_cast<chrono::microseconds>(fin2 - debut2);

    cout << "\n--- RESULTATS RECHERCHE ---" << endl;
    cout << "\nSans find : " << nb1 << " mots contiennent mot2, "
         << duree1.count() << " microsecondes" << endl;
    cout << "Avec find : " << nb2 << " mots contiennent mot2, "
         << duree2.count() << " microsecondes" << endl;

    if (nb1 != nb2)
        cout << "ATTENTION : les 2 methodes ne donnent pas le meme resultat !" << endl;


    auto debut3 = chrono::high_resolution_clock::now();
    remplacerDansVecteur(roman, mot2, nouveauMot);
    auto fin3 = chrono::high_resolution_clock::now();
    auto duree3 = chrono::duration_cast<chrono::microseconds>(fin3 - debut3);

    cout << "\n--- RESULTAT REMPLACEMENT ---" << endl;
    cout << "Temps de remplacement dans le vecteur : " << duree3.count() << " microsecondes" << endl;

    return 0;
}

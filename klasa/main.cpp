#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

class Osoba {
    int wiek;
    int numerDziennika;
    string imie;
    string nazwisko;

public:
    Osoba() : wiek(18), numerDziennika(1), imie("Jan"), nazwisko("Kaminski") {}

    bool czySameLitery(const string& tekst) const {
        if (tekst.empty()) return false;
        for (char c : tekst) {
            if (!isalpha(static_cast<unsigned char>(c))) {
                return false;
            }
        }
        return true;
    }

    bool ustawDane(string _imie, string _nazwisko, int _wiek, int _nr) {
        if (_wiek < 1 || _wiek > 100) {
            return false;
        }
        if (!czySameLitery(_imie) || !czySameLitery(_nazwisko)) {
            return false;
        }
        imie = _imie;
        nazwisko = _nazwisko;
        wiek = _wiek;
        numerDziennika = _nr;
        return true;
    }

    void wypisz() const {
        cout << "Nr " << numerDziennika << ": " << imie << " " << nazwisko << ", Wiek: " << wiek << endl;
    }

    string getImie() const { return imie; }
    string getNazwisko() const { return nazwisko; }
    int getWiek() const { return wiek; }
    int getNumer() const { return numerDziennika; }
};

class Klasa {
    Osoba t[3];
    int liczbaUczniow = 0;

public:
    void ustawLiczbeUczniow(int ile) {
        liczbaUczniow = ile;
    }

    bool ustawUcznia(int indeks, string imie, string nazwisko, int wiek, int nr) {
        if (indeks >= 0 && indeks < 3) {
            return t[indeks].ustawDane(imie, nazwisko, wiek, nr);
        }
        return false;
    }

    void wyswietlKlase() const {
        for (int i = 0; i < liczbaUczniow; i++) {
            cout << "[" << i + 1 << "] ";
            t[i].wypisz();
        }
    }

    void zapiszDoPliku(string nazwaPliku) const {
        ofstream plik(nazwaPliku);
        if (plik.is_open()) {
            plik << "LISTA UCZNIOW W KLASIE" << endl;
            for (int i = 0; i < liczbaUczniow; i++) {
                plik << "Nr " << t[i].getNumer() << ". " << t[i].getImie() << " " << t[i].getNazwisko() << " - Wiek: " << t[i].getWiek() << endl;
            }
            plik.close();
            cout << "Dane zostaly pomyslnie zapisane w pliku: " << nazwaPliku << endl;
        } else {
            cout << "Blad: Nie udalo sie utworzyc pliku w podanej sciezce!" << endl;
        }
    }

    void wczytajZPliku(string nazwaPliku) {
        ifstream plik(nazwaPliku);
        string linia;
        if (plik.is_open()) {
            cout << "--- Zawartosc odczytana bezposrednio z pliku TXT ---" << endl;
            while (getline(plik, linia)) {
                cout << linia << endl;
            }
            plik.close();
        } else {
            cout << "Blad: Nie udalo sie otworzyc pliku do wczytania!" << endl;
        }
    }
};

int main() {
    Klasa mojaKlasa;
    int ileOsob = 0;

    cout << "=== KROK 1: OKRESLENIE LICZBY UCZNIOW ===" << endl;
    while (ileOsob < 1 || ileOsob > 3) {
        cout << "Ilu uczniów chcesz wprowadzic (1-3)? ";
        cin >> ileOsob;
        if (ileOsob < 1 || ileOsob > 3) {
            cout << "Niepoprawna liczba! Mo¿esz wybraæ tylko od 1 do 3 uczniów.\n" << endl;
        }
    }

    mojaKlasa.ustawLiczbeUczniow(ileOsob);

    cout << "\n=== KROK 2: WPROWADZANIE I SPRAWDZANIE DANYCH ===" << endl;
    for (int i = 0; i < ileOsob; i++) {
        string imie, nazwisko;
        int wiek;
        bool poprawne = false;

        while (!poprawne) {
            cout << "\nWprowadz dane dla osoby nr " << i + 1 << ":" << endl;
            cout << "Imie: ";
            cin >> imie;
            cout << "Nazwisko: ";
            cin >> nazwisko;
            cout << "Ile lat (wiek 1-100): ";
            cin >> wiek;

            if (mojaKlasa.ustawUcznia(i, imie, nazwisko, wiek, i + 1)) {
                poprawne = true;
            } else {
                cout << "\nBLAD: Niepoprawne dane! Wiek (1-100), imie i nazwisko (tylko litery). Sprobuj ponownie." << endl;
            }
        }
    }

    cout << "\n=== KROK 3: WYPISZ ===" << endl;
    mojaKlasa.wyswietlKlase();

    cout << "\n=== KROK 4: ZAPISZ ===" << endl;
    mojaKlasa.zapiszDoPliku("C:/Users/Dorota/Desktop/eas/uczniowie.txt");

    cout << "\n=== KROK 5: WCZYTAJ ===" << endl;
    mojaKlasa.wczytajZPliku("C:/Users/Dorota/Desktop/eas/uczniowie.txt");

    return 0;
}

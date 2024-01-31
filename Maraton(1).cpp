#include "deklaracje.h"
/**
 * @brief Funkcja sprawdza, czy plik istnieje.
 * @param file Ścieżka do pliku.
 * @return 1, jeśli plik istnieje; 0 w przeciwnym razie.
 */
bool istnieje(string sciezka) {
    ifstream plik_do_spr(sciezka.c_str());
    return plik_do_spr.is_open();
}
/**
 * @brief Funkcja porownuje dwie daty.
 * @param a b Dwie daty ktore porownujemy.
 * @return 1, jeśli a < b; 0 w przeciwnym razie.
 */
bool porownajDaty(const Maraton& a, const Maraton& b) {
    return a.data < b.data;
}
/**
 * @brief Funkcja główna programu.
 * @param argc Liczba argumentów przekazanych do programu.
 * @param argv Tablica na wszystkie argumenty przekazane do programu.
 * @return 0, jeśli program zakończył się poprawnie; 1 w przypadku błędu.
 */
int main(int argc, char* argv[]) {
    //Polskie znaki dla konsoli
    setlocale(LC_ALL, "polish");
/**
 * @brief Sprawdzenie ilosci argumentow, i czy zawiera on parametr -i.
 * @return Jesli nie zawiera -i lub zawiera za malo argumentow zwraca blad.
 */
    if (argc < 3 || string(argv[1]) != "-i") {
        cout << "Użyj -i na początku i podaj przynajmniej jedną ścieżkę do pliku." << endl;
        return 1;
    }
/**
 * @brief Stworzenie wektora przechowujacego dane o maratonach, oraz struktury reprezentuajcej pojedynczy maraton
 */
    vector<Maraton> maratony;
    Maraton nowyMaraton;
 /**
 * @brief Przetwarza pliki  i dodaje dane do wektora, leci przez wszystkie pliki pobrane z argumentu po parametrze -i, pobiera dane z plikow i dodaje je do wektora.
 * @param argc Ilosc argumentow przekazanych do programu.
 * @param argv Tablica ktora przechowuje argumenty przekazane do programu.
 */
    for (int i = 2; i < argc; ++i) {
        // Otwarcie pliku
        ifstream plik(argv[i]);
        // Sprawdzenie czy otwarty, jesli tak to pobieramy dwie pierwsze linijki, a potem reszte w zaleznosci od tego jak wygladaja kolejne linijki, i "zmienne" w nich.
        if (plik.is_open()) {
            getline(plik, nowyMaraton.nazwa);
            getline(plik, nowyMaraton.data);

            while (!plik.eof()) {
                getline(plik, nowyMaraton.NowyZawodnik.miejsce, ',');
                getline(plik, nowyMaraton.NowyZawodnik.imie, ',');
                getline(plik, nowyMaraton.NowyZawodnik.id, ',');
                getline(plik, nowyMaraton.NowyZawodnik.czas);

                maratony.push_back(nowyMaraton);
            }
            plik.close();
        }
        else {
            cout << "Nie udało się otworzyć pliku: " << argv[i] << endl;
        }
    }
/**
 * @brief Przetworzenie wczesniej pobranych danych maratonów zapisanych w strukturze i zapisuje wyniki do plików, leci przez cala zawartosc tablicy (wektora) maratonów, tworzy nazwę pliku na podstawie imienia zawodnika, sprawdza istnienie pliku, a następnie zapisuje lub dodaje wyniki maratonu do pliku.
 */
    //Sortowanie z uzyciem funkcji porownajDaty
    sort(maratony.begin(), maratony.end(), porownajDaty);
    for (const auto& maraton : maratony) {
        // Nazwa pliku na podstawie imienia zawodnika wraz z rozszerzeniem, usuniecie bialej spacji z uzyciem substr.
        string nazwaPliku = maraton.NowyZawodnik.imie.substr(1) + ".txt";
        // Polskie znaki w nazwach plikow.
        setlocale(LC_ALL, ".utf8");
        // Sprawdzenie czy plik istnieje
        if (!istnieje(nazwaPliku)) {
            // Stworzenie pliku
            ofstream nowyPlik(nazwaPliku.c_str());
            // Otworzenie i zapisanie do niego zawartosci, usuniecie bialej spacji z uzyciem funkcji substr.
            if (nowyPlik.is_open()) {
                nowyPlik << maraton.NowyZawodnik.imie.substr(1) << endl << maraton.nazwa << " " << maraton.data << maraton.NowyZawodnik.czas << endl;
                //Zamkniecie pliku.
                nowyPlik.close();
            }
            else {
                //Komunikat bledu
                setlocale(LC_ALL, "polish");
                cout << "Nie udało się utworzyć pliku: " << nazwaPliku << endl;
            }
        }
        //Jeli plik istnieje otworzenie go.
        else {
            ofstream nowyPlik(nazwaPliku.c_str(), ios::app);
            if (nowyPlik.is_open()) {
                //Dopisanie kolejnych maratonow.
                nowyPlik << maraton.nazwa << " " << maraton.data << maraton.NowyZawodnik.czas << endl;
                //Zamkniecie pliku.
                nowyPlik.close();
            }
            else {
                //Komunikat bledu
                cout << "Nie udało się otworzyć pliku: " << nazwaPliku << endl;
            }
        }
    }
    return 0;
}
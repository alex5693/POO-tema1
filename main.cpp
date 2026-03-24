/*
Acest program simulează procesul de admitere la facultate.

Pentru fiecare candidat se introduc numele și prenumele,
vârsta,media de bacalaureat, materia examenului de admitere și nota obținută la examen. Datele pot fi preluate manual de
la tastatură sau automat dintr-un fișier, unde fiecare linie conține informațiile unui candidat.
Programul utiizeaza clasele Candidat, Facultate, Examen si Admitere.

Programul gestionează întregul flux de admitere: permite adăugarea candidaților, verifică dacă există o facultate
corespunzătoare materiei examenului, calculează media de admitere in functie de nota obtinuta la examenul de admitere si
media de la bac și validează datele astfel încât notele să fie corecte. În funcție de media minimă a facultății și de
condițiile obligatorii de promovare, programul stabilește dacă fiecare candidat este admis sau respins.

La final, programul reține doar candidații validați, împreună cu facultatea corespunzătoare, media de admitere și
rezultatul (admis/respins).
*/

#include <iostream>
#include <string>
#include <fstream>

class Candidat {
    std::string nume;
    std::string prenume;
    int varsta;
    float medie_bac;
public:
    Candidat() : varsta(0), medie_bac(0) {}
    Candidat(const std::string& n, const std::string& p, const int& v, const float& m) : nume(n), prenume(p), varsta(v), medie_bac(m) {}

    Candidat(const Candidat& c){
        nume = c.nume;
        prenume = c.prenume;
        varsta = c.varsta;
        medie_bac = c.medie_bac;
    }

    Candidat& operator=(const Candidat& c) {
        if (this != &c) {
            nume = c.nume;
            prenume = c.prenume;
            varsta = c.varsta;
            medie_bac = c.medie_bac;
        }
        return *this;
    }

    ~Candidat() { std::cout<<"~Candidat"<<std::endl;}

    void citire();

    std::string getNume() const { return nume; }
    std::string getPrenume() const { return prenume; }
    int getVarsta() const { return varsta; }
    float getMedie_bac() const { return medie_bac; }

};

void Candidat::citire() {
    std::cout << "Introduceti numele si prenumele candidatului: ";
    std::cin >> nume >> prenume;

    std::cout << "Introduceti varsta candidatului: ";
    std::cin >> varsta;

    std::cout << "Introduceti media de bac a candidatului: ";
    std::cin >> medie_bac;
}
std::ostream& operator<<(std::ostream& out, const Candidat& c) {
    out << "Nume: " << c.getNume() << " " << c.getPrenume() << std::endl
        << "Varsta: " << c.getVarsta() << std::endl
        << "Medie bac: " << c.getMedie_bac() << std::endl;
    return out;
}

class Facultate {
    std::string nume;
    std::string specializare;
    std::string materie_examen;
    int nr_locuri;
    float medie_minima;
public:
    Facultate() : nr_locuri(0), medie_minima(0) {}
    Facultate(const std::string& n, const std::string& sp, const std::string& me,const int& nr,const float& med)  : nume(n), specializare (sp), materie_examen(me),  nr_locuri(nr), medie_minima(med) {}

    std::string getNume() const { return nume; }
    std::string getMaterie_examen() const { return materie_examen; }
    std::string getSpecializare() const { return specializare; }
    int getNr_locuri() const { return nr_locuri; }
    float getMedie_minima() const { return medie_minima; }

};
std::ostream& operator<<(std::ostream& out, const Facultate& f) {
    out << f.getNume() << ", specializare: " << f.getSpecializare() << std::endl;
    return out;
}

class Examen {
    std::string materie;
    float nota;
public:
    Examen() : nota(0) {}
    Examen(const std::string& m, const float& n) : materie(m), nota(n) {}

    void citire();
    std::string getMaterie() const { return materie; }
    float getNota() const { return nota; }

};

void Examen::citire() {
    std::cout << "Introduceti materia examenului: ";
    std::cin >> materie;

    std::cout << "Introduceti nota examenului: ";
    std::cin >> nota;
}
std::ostream& operator<<(std::ostream& out, const Examen& e) {
    out << "Nota admitere: " << e.getNota() << " , materia: " << e.getMaterie() << std::endl;
    return out;
}

class Admitere {
    Candidat candidat;
    Facultate facultate;
    Examen examen;

    float medie_admitere;
    std::string rezultat;

    float calculeazaMedie() const {
        return 0.2 * candidat.getMedie_bac() + 0.8 * examen.getNota();
    }

public:
    Admitere() : medie_admitere(0) {}
    Admitere(const Candidat& c, const Facultate& f, const Examen& e): candidat(c), facultate(f), examen(e) {
        medie_admitere = calculeazaMedie();
    }

    float getMedie_admitere() const { return medie_admitere; }

    std::string getRezultat() const { return rezultat; }
    void setRezultat( const std::string& r) {rezultat = r;}

    friend bool verificareRezultat(Admitere& a);

    friend std::ostream& operator<<(std::ostream& out, const Admitere& a);
};

bool verificareRezultat(Admitere& a) {
    if ( a.candidat.getMedie_bac() < 1 || a.candidat.getMedie_bac() > 10) {
        std::cout << "Medie de bac invalida" << std::endl;
        return false;
    }
    if ( a.examen.getNota() < 1 || a.examen.getNota() > 10 ) {
        std::cout << "Nota la examenul de admitere invalida" << std::endl;
        return false;
    }
    if(a.medie_admitere >= a.facultate.getMedie_minima() && a.candidat.getMedie_bac() >= 6 && a.examen.getNota() >= 5)
        a.setRezultat("Admis");
    else
        a.setRezultat("Respins");
    return true;
}
std::ostream& operator<<(std::ostream& out, const Admitere& a) {
    out << a.candidat << a.facultate << a.examen
        << "Medie de admitere : "<< a.getMedie_admitere() << ", candidat " << a.rezultat << std::endl;
    return out;
}

int main() {
    Candidat candidat;
    Examen examen;
    Admitere admitere[100];

    int nrCandidati = 0;
    int opt=1;

    Facultate facultati[5] = {
        Facultate("Facultatea de Informatica", "Calculatoare", "Informatica", 70, 7.5),
        Facultate("Facultatea de Matematica", "Matematica", "Matematica", 50, 7.0),
        Facultate("Facultatea de Fizica", "Fizica", "Fizica", 60, 6.5),
        Facultate("Facultatea de Chimie", "Chimie", "Chimie", 40, 7.0),
        Facultate("Facultatea de Litere", "Limba si Literatura Romana", "Romana", 60, 7.5)
    };
    int nrFacultati = 5;

    while(opt != 0){
        std::cout << "1 Adauga candidati automat\n";
        std::cout << "2 Adauga candidat manual\n";
        std::cout << "3 Afiseaza candidati\n";
        std::cout << "0 Iesire\n";

        std::cin >> opt;

        if(opt == 1) {
            std::ifstream f("date.txt");

            if(!f) {
                std::cout << "Eroare la deschiderea fisierului!\n";
                continue;
            }

            int n;
            f >> n;

            for(int k = 0; k < n; k++) {
                std::string nume, prenume, materie;
                int varsta;
                float medie_bac, nota;

                f >> nume >> prenume >> varsta >> medie_bac >> materie >> nota;

                candidat = Candidat(nume, prenume, varsta, medie_bac);
                examen = Examen(materie, nota);

                bool gasit = false;

                for(int i = 0; i < nrFacultati; i++){
                    if(examen.getMaterie() == facultati[i].getMaterie_examen()){
                        Admitere a = Admitere(candidat, facultati[i], examen);
                        if ( verificareRezultat(a) ) {
                            admitere[nrCandidati] = a;
                            nrCandidati++;
                        }
                        gasit = true;
                        break;
                    }
                }

                if(!gasit) {
                    std::cout << "Nu exista facultate cu materia examenului introdus.\n" << materie << "\n";
                }
            }

            f.close();
        }
        if(opt == 2) {
            candidat.citire();
            examen.citire();

            bool gasit = false;
            for(int i = 0; i < nrFacultati; i++){
                if(examen.getMaterie() == facultati[i].getMaterie_examen()){
                    Admitere a = Admitere(candidat, facultati[i], examen);
                    if ( verificareRezultat(a) ) {
                        admitere[nrCandidati] = a;
                        nrCandidati++;
                    }
                    gasit = true;
                    break;
                }
            }
            if(!gasit) {
                std::cout << "Nu exista facultate cu materia examenului introdus.\n";
            }
        }
        if(opt == 3) {
            for(int i = 0; i < nrCandidati; i++) {
                std::cout << admitere[i];
                std::cout << std::endl;
            }
        }
    }
}
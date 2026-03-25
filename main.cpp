//Acest program simulează procesul de admitere la facultate.

#include <iostream>
#include <cstring>

// CLASA CANDIDAT retine datele unui candidat (nume, prenume, varsta, medie bac)
class Candidat {
    char* nume;
    char* prenume;
    int varsta;
    float medie_bac;
public:
    // constructor implicit
    Candidat() : nume(nullptr), prenume(nullptr), varsta(0), medie_bac(0) {}

    // constructor cu parametri
    Candidat(const char* n, const char* p, int v, float m) {
        nume = new char[strlen(n) + 1];
        strcpy(nume, n);

        prenume = new char[strlen(p) + 1];
        strcpy(prenume, p);

        varsta = v;
        medie_bac = m;
    }

    // constructor de copiere
    Candidat(const Candidat& c) {
        nume = new char[strlen(c.nume) + 1];
        strcpy(nume, c.nume);

        prenume = new char[strlen(c.prenume) + 1];
        strcpy(prenume, c.prenume);

        varsta = c.varsta;
        medie_bac = c.medie_bac;
    }


    Candidat& operator=(const Candidat& c) {
        if (this != &c) {
            delete[] nume;
            delete[] prenume;

            nume = new char[strlen(c.nume) + 1];
            strcpy(nume, c.nume);

            prenume = new char[strlen(c.prenume) + 1];
            strcpy(prenume, c.prenume);

            varsta = c.varsta;
            medie_bac = c.medie_bac;
        }
        return *this;
    }

    // destructor obligatoriu pentru a elibera memoria alocata dinamic
     ~Candidat() {
        delete[] nume;
        delete[] prenume;
    }

    void citire() {
        char b1[50], b2[50];

        std::cout << "Introduceti numele si prenumele candidatului: ";
        std::cin >> b1 >> b2;

        delete[] nume;
        delete[] prenume;

        nume = new char[strlen(b1) + 1];
        strcpy(nume, b1);

        prenume = new char[strlen(b2) + 1];
        strcpy(prenume, b2);

        std::cout << "Introduceti varsta candidatului: ";
        std::cin >> varsta;

        std::cout << "Introduceti media de bac a candidatului: ";
        std::cin >> medie_bac;
    }

    // functie inline (optimizare acces)
    inline float getMedie_bac() const { return medie_bac; }

    const char* getNume() const { return nume; }
    const char* getPrenume() const { return prenume; }
    int getVarsta() const { return varsta; }
};

// supraincarcare operator <<
std::ostream& operator<<(std::ostream& out, const Candidat& c) {
    out << "Nume: " << c.getNume() << " " << c.getPrenume() << std::endl
        << "Varsta: " << c.getVarsta() << std::endl
        << "Medie bac: " << c.getMedie_bac() << std::endl;
    return out;
}

/// CLASA FACULTATE retine informatii despre facultate
class Facultate {
    char* nume;
    char* specializare;
    char* materie_examen;
    int nr_locuri;
    float medie_minima;
public:
    Facultate() :  nume(nullptr), specializare(nullptr), materie_examen(nullptr), nr_locuri(0), medie_minima(0) {}

    // constructor cu parametri
    Facultate(const char* n, const char* sp, const char* me, int nr, float med) {
        nume = new char[strlen(n)+1];
        strcpy(nume,n);
        specializare = new char[strlen(sp)+1];
        strcpy(specializare,sp);
        materie_examen = new char[strlen(me)+1];
        strcpy(materie_examen,me);
        nr_locuri = nr;
        medie_minima = med;
    }

    // destructor
    ~Facultate(){
        delete[] nume;
        delete[] specializare;
        delete[] materie_examen;
    }

    // constructor de copiere
    Facultate(const Facultate& f){
        nume = new char[strlen(f.nume) + 1];
        strcpy(nume, f.nume);

        specializare = new char[strlen(f.specializare) + 1];
        strcpy(specializare, f.specializare);

        materie_examen = new char[strlen(f.materie_examen) + 1];
        strcpy(materie_examen, f.materie_examen);

        nr_locuri = f.nr_locuri;
        medie_minima = f.medie_minima;
    }

    Facultate& operator=(const Facultate& f) {
        if (this != &f) {
            delete[] nume;
            delete[] specializare;
            delete[] materie_examen;

            nume = new char[strlen(f.nume) + 1];
            strcpy(nume, f.nume);

            specializare = new char[strlen(f.specializare) + 1];
            strcpy(specializare, f.specializare);

            materie_examen = new char[strlen(f.materie_examen) + 1];
            strcpy(materie_examen, f.materie_examen);

            nr_locuri = f.nr_locuri;
            medie_minima = f.medie_minima;
        }
        return *this;
    }


    const char* getNume() const { return nume; }
    const char* getMaterie_examen() const { return materie_examen; }
    const char* getSpecializare() const { return specializare; }
    int getNr_locuri() const { return nr_locuri; }
    float getMedie_minima() const { return medie_minima; }

};
std::ostream& operator<<(std::ostream& out, const Facultate& f) {
    out << f.getNume() << ", specializare: " << f.getSpecializare() << std::endl;
    return out;
}

/// CLASA EXAMEN retine nota si materia examenului
class Examen {
    char* materie;
    float nota;
public:
    Examen() : materie(nullptr), nota(0) {}

    // constructor cu parametri
    Examen(const char* m, float n) {
        materie = new char[strlen(m)+1];
        strcpy(materie,m);
        nota = n;
    }

    // constructor de copiere
    Examen(const Examen& e) {
        materie = new char[strlen(e.materie)+1];
        strcpy(materie,e.materie);
        nota = e.nota;
    }

    Examen& operator=(const Examen& e){
        if(this!=&e){
            delete[] materie;
            materie = new char[strlen(e.materie)+1];
            strcpy(materie,e.materie);
            nota = e.nota;
        }
        return *this;
    }

    // destructor
    ~Examen(){
        delete[] materie;
    }


    void citire();

    const char* getMaterie() const { return materie; }
    float getNota() const { return nota; }

};

void Examen::citire() {
    char b[50];
        std::cout<<"Introduceti materia examenului: ";
        std::cin>>b;

        delete[] materie;
        materie = new char[strlen(b)+1];
        strcpy(materie,b);

        std::cout<<"Introduceti nota examenului: ";
        std::cin>>nota;
}
std::ostream& operator<<(std::ostream& out, const Examen& e) {
    out << "Nota admitere: " << e.getNota() << " , materia: " << e.getMaterie() << std::endl;
    return out;
}


//  CLASA ADMITERE combina candidat + examen + facultate si calculeaza rezultatul
class Admitere {
    Candidat candidat;
    Facultate facultate;
    Examen examen;

    float medie_admitere;
    char rezultat[20];
    static int total;

    // calculeaza media finala
    float calculeazaMedie() const {
        return 0.2 * candidat.getMedie_bac() + 0.8 * examen.getNota();
    }

public:
    Admitere() : medie_admitere(0) { strcpy(rezultat, ""); } // initializare string

    // constructor cu parametri
    Admitere(const Candidat& c, const Facultate& f, const Examen& e): candidat(c), facultate(f), examen(e) {
        medie_admitere = calculeazaMedie();
        total++;
    }

    float getMedie_admitere() const { return medie_admitere; }
    const char* getRezultat() const { return rezultat; }

    // setter pentru rezultat (Admis / Respins)
    void setRezultat( const char* r) {strcpy(rezultat,r);}

    friend bool verificareRezultat(Admitere& a);

    friend std::ostream& operator<<(std::ostream& out, const Admitere& a);
};
int Admitere::total = 0;

// verifica daca un candidat este admis sau respins
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
    // obiecte folosite pentru citire temporara
    Candidat candidat;
    Examen examen;

    // vector de rezultate finale
    Admitere admitere[100];

    int nrCandidati = 0; // numarul total de candidati validati
    int opt=1; // optiune

    // initializare facultati disponibile
    Facultate facultati[5] = {
        Facultate("Facultatea de Informatica", "Calculatoare", "Informatica", 70, 7.5),
        Facultate("Facultatea de Matematica", "Matematica", "Matematica", 50, 7.0),
        Facultate("Facultatea de Fizica", "Fizica", "Fizica", 60, 6.5),
        Facultate("Facultatea de Chimie", "Chimie", "Chimie", 40, 7.0),
        Facultate("Facultatea de Litere", "Limba si Literatura Romana", "Romana", 60, 7.5)
    };
    int nrFacultati = 5;

    // DATE PENTRU INTRODUCERE AUTOMATA
    // array de candidati
    Candidat candidati[10] = {
        Candidat("Cristi", "Popescu", 21, 9.1),
        Candidat("Ana", "Luca", 19, 8.7),
        Candidat("Mihai", "Ionescu", 22, 7.5),
        Candidat("Elena", "Marinescu", 20, 9.2),
        Candidat("Andrei", "Georgescu", 21, 8.0),
        Candidat("Maria", "Stan", 20, 9.0),
        Candidat("Ioana", "Radu", 19, 7.8),
        Candidat("George", "Popa", 21, 6.9),
        Candidat("Alina", "Matei", 20, 8.5),
        Candidat("Stefan", "Florescu", 19, 5.1)
    };
    // array examene corespunzatoare
    Examen examene[10] = {
        Examen("Informatica", 8.5),
        Examen("Matematica", 9.0),
        Examen("Fizica", 6.5),
        Examen("Chimie", 8.0),
        Examen("Romana", 7.5),
        Examen("Informatica", 9.0),
        Examen("Matematica", 7.0),
        Examen("Fizica", 6.0),
        Examen("Chimie", 7.5),
        Examen("Romana", 6.8)
    };
    int n = 10; // numar candidati

    // meniu principal al programului
    while(opt != 0){
        std::cout << "1 Adauga candidati automat\n";
        std::cout << "2 Adauga candidat manual\n";
        std::cout << "3 Afiseaza candidati\n";
        std::cout << "0 Iesire\n";

        std::cin >> opt;

        if(opt == 1) {

            // citirea fiecarui candidat
            for(int k = 0; k < n; k++) {
                char nume[50],prenume[50],materie[50];
                int varsta;
                float medie_bac, nota;

                candidat = Candidat(candidati[k].getNume(),candidati[k].getPrenume(),candidati[k].getVarsta(),
                    candidati[k].getMedie_bac());

                examen = Examen(examene[k].getMaterie(),examene[k].getNota());
                bool gasit = false;

                // cautam facultatea corespunzatoare
                for(int i = 0; i < nrFacultati; i++){
                    if(strcmp(examen.getMaterie(), facultati[i].getMaterie_examen())==0){

                        Admitere a = Admitere(candidat, facultati[i], examen);

                        // validarea datelor si stabilirea rezultatului
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

        }
        if(opt == 2) {
            candidat.citire();
            examen.citire();

            bool gasit = false;

            // cautam facultatea corespunzatoare
            for(int i = 0; i < nrFacultati; i++){
                if(strcmp(examen.getMaterie(), facultati[i].getMaterie_examen())==0){

                    Admitere a = Admitere(candidat, facultati[i], examen);

                    // validarea datelor si stabilirea rezultatului
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
            // afisam toti candidatii validati
            for(int i = 0; i < nrCandidati; i++) {
                std::cout << admitere[i];
                std::cout << std::endl;
            }
        }
    }
}

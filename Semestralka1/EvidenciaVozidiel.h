#pragma once
#include "Vozidlo.h"
#include "structures/list/linked_list.h"
#include "ObjednavkaTovaru.h"

class EvidenciaVozidiel
{
public:
	/// <summary> Konstruktor. Vytvori novu prazdnu evidenciu. </summary>
	EvidenciaVozidiel();

	/// <summary> Destruktor. </summary>
	~EvidenciaVozidiel();

	/// <summary> Vytvori nove vozidlo s danou SPZ a prida ho do evidencie. Ak uz take vozidlo existuje, vrati false, inak true. </summary>
	bool vytvorNoveVozidlo(string spz, Tovar::Typ typTovaru, size_t datumZaradenia);

	/// <summary> Vytvori optimalne rozlozenie objednavok do vozidiel pre minimalizovanie prevadzkovych nakladov.
	///Aktualizuje prevadzkove naklady pouzitych vozidiel. Vrati celkove naklady na rozvoz danych objednavok. </summary>
	double naplnVozidla(structures::LinkedList<ObjednavkaTovaru *> * objednavkyPodlaRegionov);

	/// <summary> Vypise zoznam vozidiel podla datumu zaradenia do evidencie. </summary>
	void vypisVozidiel();

	/// <summary> Vrati celkovu kapacitu (nosnost) vsetkych vozidiel v evidencii, ktore su 
	///urcene na prepravu daneho typu tovaru. </summary>
	size_t dajKapacituVozidiel(Tovar::Typ typTovaru);

	/// <summary> Zapise evidenciu do suboru. </summary>
	void zapisSa(ofstream * outFile);

	/// <summary> Nacita evidenciu zo suboru. </summary>
	void nacitajSa(ifstream * inFile);

private:
	/// <summary> Zoznam vsetkych evidovanych farmarov.  </summary>
	structures::LinkedList<Vozidlo *> * vozidlaPodlaDatumu_;

	/// <summary> Prida do evidencie nove vozidlo. Kontroluje unikatnost nazvu SPZ. Vrati true ak sa operacia podarila, inak false. </summary>
	bool pridajVozidlo(Vozidlo* noveVozidlo);

	/// <summary> Vrati zoznam dostupnych vozidiel daneho typu.  </summary>
	structures::LinkedList<Vozidlo *> * dajZoznamVozidielTypu(Tovar::Typ typTovaru);
};


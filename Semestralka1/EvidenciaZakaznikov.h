#pragma once

#include "Zakaznik.h"

class EvidenciaZakaznikov
{
public:
	/// <summary> Konstruktor. Vytvori novu prazdnu evidenciu. </summary>
	EvidenciaZakaznikov();

	/// <summary> Destruktor. </summary>
	~EvidenciaZakaznikov();

	/// <summary> Vrati zakaznika na zaklade nazvu. Ak taky zakaznik v evidencii nie je, vrati nullptr. </summary>
	Zakaznik * dajZakaznika(string nazovZakaznika);

	/// <summary> Vrati abecedny zoznam vsetkych evidovanych zakaznikov. </summary>
	structures::List<Zakaznik *> * dajZakaznikov() { return zakazniciPodlaAbecedy_; }

	/// <summary> Vrati abecedny zoznam zakaznikov z daneho regionu. Zoznam vytvori dynamicky! </summary>
	structures::List<Zakaznik *> * dajZakaznikov(size_t region);

	/// <summary> Vytvori noveho Zakaznika a prida ho do evidencie. </summary>
	bool vytvorZakaznika(string nazovNovehoZakaznika, size_t region);

	/// <summary> Zapise evidenciu do suboru. </summary>
	void zapisSa(ofstream * outFile);

	/// <summary> Nacita evidenciu zo suboru. </summary>
	void nacitajSa(ifstream * inFile);

private:
	/// <summary> Zoznam vsetkych evidovanych zakaznikov.  </summary>
	structures::List<Zakaznik *> * zakazniciPodlaAbecedy_;

	/// <summary> Prida do evidencie noveho Zakaznika. Kontroluje unikatnost nazvu Zakaznika. Vrati true ak sa operacia podarila, inak false. </summary>
	bool pridajZakaznika(Zakaznik* novyZakaznik);
};


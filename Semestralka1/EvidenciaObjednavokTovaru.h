#pragma once
#include "Datum.h"
#include "types.h"
#include "Zakaznik.h"
#include "structures/list/linked_list.h"
#include "ObjednavkaTovaru.h"
#include "EvidenciaZakaznikov.h"

/// <summary> Trieda reprezentujuca evidenciu vsetkych objednavok tovaru od zakaznikov. </summary>
class EvidenciaObjednavokTovaru
{
public:
	/// <summary> Konstruktor. Vytvori novu prazdnu evidenciu. </summary>
	EvidenciaObjednavokTovaru();

	/// <summary> Destruktor. </summary>
	~EvidenciaObjednavokTovaru();

	/// <summary> Vytvori novu Objednavku. Skontroluje datum dodania a prida 
	///ju do evidencie. Vrati true ak sa operacia podarila, inak false. </summary>
	bool vytvorNovuObjednavku(Zakaznik * zakaznik, Tovar::Typ typTovaru, double mnozstvo, double jednotkovaPredajnaCena, Datum datumDorucenia, double celkovaKapacitaVozidiel, Datum aktualnyDatum);

	/// <summary> Vrati mnozstvo daneho tovaru, ktore je potrebne vyrobit pre uspokojenie 
	///vsetkych objednavok na nadchadzajuce stanovene obdobie. </summary>
	double dajPoziadavkyNaTovar(Tovar::Typ typTovaru, Datum aktualnyDatum);

	/// <summary> Vrati zoznam vsetkych objednavok zoradenych podla datumu zaevidovania. </summary>
	structures::List<ObjednavkaTovaru *> * dajObjednavky() { return objednavkyPodlaDatumuZaevidovania_; }

	/// <summary> Oznaci objednavky zo zadaneho datumu ako zrealizovane a prida ich do zoznamu zrealizovanych objednavok. Vrati celkovu cenu tychto objednavok. </summary>
	double zrealizujObjednavkyDna(Datum datum);

	/// <summary> Vypise zoznam vsetkych objednavok, ktore sa podarilo zrealizovat za dane casove obdobie. </summary>
	void vypisZrealizovanychObjednavok(Datum datumOd, Datum datumDo);

	/// <summary> Vypise zoznam vsetkych objednavok, ktore sa nepodarilo zrealizovat za dane casove obdobie. </summary>
	void vypisNezrealizovanychObjednavok(Datum datumOd, Datum datumDo);

	/// <summary> Vypise zoznam vsetkych objednavok, ktore maju byt zrealizovane v dany den. </summary>
	void vypisObjednavok(Datum datum);

	/// <summary> Vrati zoznam objednavok, ktore maju byt zrealizovane v zadany den, usporiadany podla trzieb. Zoznam vytvara dynamicky! </summary>
	structures::LinkedList<ObjednavkaTovaru *> * dajObjednavkyPodlaTrzieb(Datum datumDorucenia);

	/// <summary> Vrati zoznam objednavok, ktore maju byt zrealizovane v zadany den, 
	///usporiadany podla cisel regionov, do ktorych maju byt dorucene. Zoznam vytvara dynamicky! </summary>
	structures::LinkedList<ObjednavkaTovaru *> * dajObjednavkyPodlaRegionov(Datum datumDorucenia);

	/// <summary> Zapise evidenciu do suboru. </summary>
	void zapisSa(ofstream * outFile);

	/// <summary> Nacita evidenciu zo suboru. </summary>
	void nacitajSa(ifstream * inFile, EvidenciaZakaznikov * zakaznici);

private:
	/// <summary> Prida do evidencie novu Objednavku. Kontroluje prekrocenie 
	///kapacity vozidiel v dany den dodania. Vrati true ak sa objednavka vytvorila a ulozila, inak false. </summary>
	bool pridajObjednavku(ObjednavkaTovaru* novaObjednavka, double celkovaKapacitaVozidiel);

	/// <summary> Zoznam vsetkych evidovanych objednavok.  </summary>
	structures::List<ObjednavkaTovaru *> * objednavkyPodlaDatumuZaevidovania_;

	/// <summary> Zoznam objednavok, ktore boli zrealizovane. Zoradeny podla datumu zrealizovania.  </summary>
	structures::List<ObjednavkaTovaru *> * zrealizovaneObjednavky_;
};


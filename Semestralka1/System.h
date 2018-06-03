#pragma once

#include "Datum.h"
#include "EvidenciaVozidiel.h"
#include "EvidenciaBioFarmarov.h"
#include "EvidenciaObjednavokTovaru.h"
#include "EvidenciaZakaznikov.h"
#include "EvidenciaZasob.h"
#include "Zisk.h"

/// <summary> Trieda reprezentujuca informacny system firmy C&C. </summary>
class System
{
public:
	/// <summary> Konstruktor. Vytvori novy system. </summary>
	System();

	/// <summary> Konstruktor. Vytvori novy system nacitanim zo zadaneho suboru. </summary>
	System(ifstream * infile);

	/// <summary> Ulozi system. </summary>
	void zapisSa();

	/// <summary> Destruktor. </summary>
	~System();

	/// <summary> Testovanie behu systemu pripravenou sekvenciou prikazov. </summary>
	void testuj();

	/// <summary> Vypise aktualny systemovy datum. </summary>
	Datum * aktualnyDatum() { return datum_; }

	/// <summary> Posunie sa na dalsi den. Zabezpeci aktualizovanie vsetkych sucasti systemu. </summary>
	void dalsiDen();

	/// <summary> Vypise zoznam zakaznikov z daneho regionu a pre dane casove obdobie vypise statistiky ich objednavok. </summary>
	void vypisZakaznikov(size_t region, Datum datumOd, Datum datumDo);

	/// <summary> Vyhlada a vypise farmara, od ktoreho firma nakupila najviac polotovarov daneho typu za dane casove obdobie. </summary>
	void vypisNajuzitocnejsiehoFarmara(Polotovar::Typ typPolotovaru, Datum datumOd, Datum datumDo);

	/// <summary> Vypise zisk firmy za dane casove obdobie. </summary>
	void vypisZiskFirmy(Datum datumOd, Datum datumDo);

	EvidenciaBioFarmarov * dajBioFarmarov() { return bioFarmari_; }
	EvidenciaVozidiel * dajVozidla() { return vozidla_; }
	EvidenciaZakaznikov * dajZakaznikov() { return zakaznici_; }
	EvidenciaObjednavokTovaru * dajObjednavky() { return objednavkyTovaru_; }

private:
	/// <summary> Evidencia biofarmarov. </summary>
	EvidenciaBioFarmarov * bioFarmari_;

	/// <summary> Evidencia vozidiel. </summary>
	EvidenciaVozidiel * vozidla_;

	/// <summary> Evidencia zakaznikov. </summary>
	EvidenciaZakaznikov * zakaznici_;

	/// <summary> Evidencia objednavok tovaru od zakaznikov. </summary>
	EvidenciaObjednavokTovaru * objednavkyTovaru_;

	/// <summary> Evidencia skladovych zasob. </summary>
	EvidenciaZasob * zasoby_;

	/// <summary> Systemovy datum. </summary>
	Datum * datum_;

	/// <summary> Evidencia denneho zisku. Uklada sa do ArrayListu2. Index 0 je nevyuzity. Kazdy index znamena den v poradi. </summary>
	structures::ArrayList2<Zisk *> * zisky_;

	/// <summary> Zabezpeci kontrolu poziadaviek na definovane obdobie. Ak aktualne zasoby 
	///polotovarov nestacia, oslovi farmarov a nakupi. Vrati celkove naklady za nakupene polotovary. </summary>
	double kontrolaPoziadaviek();

	/// <summary> Zisti ktore objednavky na nasledujuci den sa nedokazu vybavit kvoli nedostatku polotovarov 
	///a oznaci ich ako ZRUSENE. Ako prve zrusi tie objednavky, z ktorych ma firma najmensie trzby. Polotovary, ktore sa pouziju na vyrobu odoberie zo skladu. </summary>
	void kontrolaObjednavokNaNasledujuciDen();

	/// <summary> Zrealizuje objednavky, ktore maju datum dorucenia dnesny den. 
	///Rozlozi objednavky do vozidiel a zaeviduje naklady a zisk. </summary>
	void zrealizovanieDnesnychObjednavok(double nakladyNaPolotovary);

	/// <summary> Prida zisk za dnesny den do zoznamu ziskov na index dnesneho datumu. </summary>
	void zaevidujDnesnyZisk(double cenaObjednavokTovaru, double cenaObjednavokPolotovarov, double prevadzkoveNakladyVozidiel);

	/// <summary> Vypise aktualny den a aktualizuje vsetky sucasti systemu. ("Zacatie noveho dna"). </summary>
	void aktualizuj();
};


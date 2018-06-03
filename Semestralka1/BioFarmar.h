#pragma once

#include "types.h"
#include "UdajePolotovar.h"
#include "structures/list/array_list2.h"

/// <summary> Trieda reprezentujuca BioFarmara </summary>
class BioFarmar
{
public:
	/// <summary> Konstruktor. </summary>
	BioFarmar();

	/// <summary> Konstruktor. Vytvori biofarmara s nazvom, ktory nedodava ziadne polotovary. </summary>
	BioFarmar(string nazov);

	/// <summary> Destruktor. </summary>
	~BioFarmar();

	/// <summary> Vrati true ak farmar dodava dany polotovar. </summary>
	bool dodavaPolotovar(Polotovar::Typ typPolotovaru);

	/// <summary> Vrati cenu, za ktoru farmar predava dany polotovar. </summary>
	double dajCenuPolotovaru(Polotovar::Typ typPolotovaru);

	/// <summary> Vrati mnozstvo polotovaru, ktore je farmar schopny dodat.  </summary>
	double dajMnozstvoPolotovaru(Polotovar::Typ typPolotovaru);

	/// <summary> Vrati priemernu nakupnu cenu daneho polotovaru. 
	///(Na zaklade predoslych nakupov od daneho farmara, za stanovene obdobie.) </summary>
	double dajPriemernuCenuPolotovaru(Polotovar::Typ typPolotovaru);

	/// <summary> Kupi od farmara zadane mnozstvo daneho polotovaru. Vrati mnozstvo, ktore biofarmar predal. Vypocita novu priemernu cenu. </summary>
	double predajPolotovar(Polotovar::Typ typPolotovaru, double dopytovaneMnozstvo);

	/// <summary> Prida novy polotovar, ktory moze farmar dodavat. Vrati true ak sa operacia podarila, inak false. </summary>
	bool pridajNovyPolotovar(Polotovar::Typ typPolotovaru);

	/// <summary> ("Prechod na dalsi den"). Aktualizuje udaje o vsetkych dodavanych polotovaroch. 
	///Nemeni priemerne nakupne ceny. </summary>
	void aktualizuj();

	/// <summary> Vrati nazov farmara. </summary>
	string dajNazov() { return nazov_; }

	/// <summary> Vrati vsetky typy polotovarov, ktore farmar dodava. Pole vytvori dynamicky! </summary>
	structures::Array<Polotovar::Typ> * dajPolotovary();

	/// <summary> Zapise biofarmara do suboru. </summary>
	void zapisSa(ofstream * outFile);

	/// <summary> Nacita biofarmara zo suboru. </summary>
	void nacitajSa(ifstream * inFile);

private:
	/// <summary> Nazov farmara. </summary>
	string nazov_;

	/// <summary> Polotovary, ktore farmar dodava. </summary>
	structures::List<UdajePolotovar *> * dodavanePolotovary_;

	/// <summary> Vrati udaje o zadanom polotovare. Ak zadany polotovar nedodava, vrati NULL. </summary>
	UdajePolotovar* dajUdajePolotovar(Polotovar::Typ typPolotovaru);
};
#pragma once

#include "BioFarmar.h"
#include "PriemernaCenaPolotovaru.h"

/// <summary> Trieda reprezentujuca evidenciu vsetkych BioFarmarov. </summary>
class EvidenciaBioFarmarov
{
public:
	/// <summary> Konstruktor. Vytvori novu prazdnu evidenciu. </summary>
	EvidenciaBioFarmarov();

	/// <summary> Destruktor. </summary>
	~EvidenciaBioFarmarov();

	/// <summary> Vytvori noveho BioFarmara bez polotovarov a prida ho do evidencie. </summary>
	bool vytvorBioFarmara(string nazovNovehoBioFarmara);

	/// <summary> Prida novy produkt existujucemu biofarmarovi v evidencii. Prida produkt do zoznamu priemernych cien, 
	///aj do objektu biofarmara. Ak farmar so zadanym nazvom neexistuje vrati false, inak true. </summary>
	bool pridajProduktBioFarmarovi(string nazovBioFarmara, Polotovar::Typ typPolotovaru);

	structures::List<PriemernaCenaPolotovaru *> * dajFarmarovPodlaPriemCien() { return farmariPodlaPriemCien_; }

	structures::List<BioFarmar *> * dajFarmarovPodlaAbecedy() { return farmariPodlaAbecedy_; }

	/// <summary> Ak farmar zo zadanym nazvom existuje v evidencii, vrati ho. Inak vrati nullptr. </summary>
	BioFarmar * dajFarmara(string nazovFarmara);

	/// <summary> Vymaze zo zoznamu stary zaznam a vytvori novy s aktualnou priemernou 
	///cenou a prida ho na spravne miesto do zoznamu. </summary>
	void zoradPodlaPriemCien(BioFarmar * bioFarmar, Polotovar::Typ typPolotovaru);

	/// <summary> Vypise abecedny zoznam farmarov, ktori dodavaju dany polotovar. </summary>
	void vypisBioFarmarovPodlaPolotovaru(Polotovar::Typ typPolotovaru);

	/// <summary> "Prechod na dalsi den". Aktualizuje vsetkych BioFarmarov v evidencii. </summary>
	void aktualizuj();

	/// <summary> Zapise evidenciu do suboru. </summary>
	void zapisSa(ofstream * outFile);

	/// <summary> Nacita evidenciu zo suboru. </summary>
	void nacitajSa(ifstream * inFile);

private:
	/// <summary> Prida do evidencie podla abecedy noveho BioFarmara. Kontroluje unikatnost nazvu BioFarmara. Vrati true ak sa operacia podarila, inak false. </summary>
	bool pridajBioFarmara(BioFarmar* novyFarmar);

	/// <summary> Zoznam vsetkych evidovanych biofarmarov.  </summary>
	structures::List<BioFarmar *> * farmariPodlaAbecedy_;

	/// <summary> Zoznam biofarmarov usporiadanych podla priemernych cien polotovarov. </summary>
	structures::List<PriemernaCenaPolotovaru *> * farmariPodlaPriemCien_;
};


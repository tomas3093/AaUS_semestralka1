#pragma once
#include "structures/list/list.h"
#include "MnozstvoPolotovaru.h"
#include "ObjednavkaPolotovaru.h"

/// <summary> Trieda reprezentuje zoznam aktualnych skladovych zasob, objednanych zasob a evidenciu 
///vsetkych objednavok polotovarov. </summary>
class EvidenciaZasob
{
public:
	/// <summary> Konstruktor. Vytvori prazdny sklad. </summary>
	EvidenciaZasob();

	/// <summary> Destruktor. </summary>
	~EvidenciaZasob();

	/// <summary> Prida do skladu novu zasobu daneho polotovaru. Ak uz je zasoba daneho 
	///polotovaru v evidencii, zvysi ju o dane mnozstvo, inak ju vytvori. </summary>
	void pridajZasobu(Polotovar::Typ typPolotovaru, double mnozstvo);

	/// <summary> Odoberie zadane mnozstvo zasoby zo skladu. 
	///Ak take mnozstvo na sklade nie je vrati true, inak false. </summary>
	bool odoberZasobu(Polotovar::Typ typPolotovaru, double mnozstvo);

	/// <summary> Vrati mnozstvo daneho polotovaru, ktore je momentalne k dispozicii. </summary>
	double dajMnozstvoNaSklade(Polotovar::Typ typPolotovaru);

	/// <summary> Vrati zoznam vsetkych objednavok polotovarov usporiadany podla datumu objednania. </summary>
	structures::List<ObjednavkaPolotovaru *> * dajObjednavkyPolotovarov() { return zoznamObjednavokPolotovarov_; }

	/// <summary> Prida objednavku do zoznamu objednavok na spravne miesto a objednane zasoby prida do zoznamu objednanych zasob. </summary>
	void pridajObjednavkuPolotovaru(ObjednavkaPolotovaru * novaObjednavka);

	/// <summary> "Prechod na dalsi den". Presunie objednane zasoby do skladovych zasob. </summary>
	void aktualizuj();

	/// <summary> Zapise evidenciu do suboru. </summary>
	void zapisSa(ofstream * outFile);

	/// <summary> Nacita evidenciu zo suboru. </summary>
	void nacitajSa(ifstream * inFile, EvidenciaBioFarmarov * biofarmari);

private:
	/// <summary> Zaznam zasob, ktore su momentalne fyzicky na sklade a daju sa pouzit na vyrobu. </summary>
	structures::List<MnozstvoPolotovaru *> * skladoveZasoby_;

	/// <summary> Zoznam zasob, ktore su objednane, ale zatial nie su fyzicky na sklade. </summary>
	structures::List<MnozstvoPolotovaru *> * objednaneZasoby_;

	/// <summary> Zoznam vsetkych doterajsich objednavok polotovarov od biofarmarov usporiadany 
	///podla datumu objednania. </summary>
	structures::List<ObjednavkaPolotovaru *> * zoznamObjednavokPolotovarov_;

	/// <summary> Prida do evidencie objednanych zasob novu zasobu daneho polotovaru. Ak uz je zasoba daneho 
	///polotovaru v evidencii, zvysi ju o dane mnozstvo, inak ju vytvori. </summary>
	void pridajObjednanuZasobu(Polotovar::Typ typPolotovaru, double mnozstvo);
};

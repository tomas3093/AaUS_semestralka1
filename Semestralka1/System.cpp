#include "stdafx.h"
#include "System.h"
#include "EvidenciaObjednavokTovaru.h"


System::System()
	:bioFarmari_(new EvidenciaBioFarmarov()), vozidla_(new EvidenciaVozidiel()),
	zakaznici_(new EvidenciaZakaznikov()), objednavkyTovaru_(new EvidenciaObjednavokTovaru()),
	zasoby_(new EvidenciaZasob()), datum_(new Datum(1)), zisky_(new structures::ArrayList2<Zisk *>())
{
	zisky_->insert(new Zisk(), 0);	// Zaplnenie nevyuziteho miesta
	zisky_->insert(new Zisk(), 1);	// Zaplnenie 1. dna
}

System::System(ifstream* infile)
	:bioFarmari_(new EvidenciaBioFarmarov()), vozidla_(new EvidenciaVozidiel()),
	zakaznici_(new EvidenciaZakaznikov()), objednavkyTovaru_(new EvidenciaObjednavokTovaru()),
	zasoby_(new EvidenciaZasob()), datum_(new Datum(1))
{
	infile->open(FILE_NAME_SYSTEM);
	int datum;
	*infile >> datum;
	*datum_ = datum;

	// Zisky
	int pocet = 0;
	*infile >> pocet;
	zisky_ = new structures::ArrayList2<Zisk*>(pocet);
	zisky_->insert(new Zisk(), 0);	// Zaplnenie nevyuziteho miesta
	for (int i = 1; i < pocet; ++i)
	{
		Zisk * novy = new Zisk();
		novy->nacitajSa(infile);
		zisky_->add(novy);
	}
	infile->close();

	infile->open(FILE_NAME_BIOFARMARI);
	bioFarmari_->nacitajSa(infile);
	infile->close();

	infile->open(FILE_NAME_VOZIDLA);
	vozidla_->nacitajSa(infile);
	infile->close();

	infile->open(FILE_NAME_ZAKAZNICI);
	zakaznici_->nacitajSa(infile);
	infile->close();

	infile->open(FILE_NAME_OBJEDNAVKY_TOVARU);
	objednavkyTovaru_->nacitajSa(infile, zakaznici_);
	infile->close();

	infile->open(FILE_NAME_ZASOBY);
	zasoby_->nacitajSa(infile, bioFarmari_);
	infile->close();
}

void System::zapisSa()
{
	ofstream * outfile = new ofstream();

	outfile->open(FILE_NAME_SYSTEM, ios_base::trunc);
	int datum = *datum_;
	*outfile << datum << endl;

	// Zisky
	int pocet = zisky_->size();
	*outfile << pocet << endl;
	for (int i = 1; i < pocet; ++i)
	{
		(*zisky_)[i]->zapisSa(outfile);
	}
	outfile->close();

	outfile->open(FILE_NAME_BIOFARMARI, ios_base::trunc);
	bioFarmari_->zapisSa(outfile);
	outfile->close();

	outfile->open(FILE_NAME_VOZIDLA, ios_base::trunc);
	vozidla_->zapisSa(outfile);
	outfile->close();

	outfile->open(FILE_NAME_ZAKAZNICI, ios_base::trunc);
	zakaznici_->zapisSa(outfile);
	outfile->close();

	outfile->open(FILE_NAME_OBJEDNAVKY_TOVARU, ios_base::trunc);
	objednavkyTovaru_->zapisSa(outfile);
	outfile->close();

	outfile->open(FILE_NAME_ZASOBY, ios_base::trunc);
	zasoby_->zapisSa(outfile);
	outfile->close();


	delete outfile;
}

System::~System()
{
	delete bioFarmari_;
	delete vozidla_;
	delete zakaznici_;
	delete objednavkyTovaru_;
	delete zasoby_;
	delete datum_;

	for (Zisk* const item : *zisky_)
	{
		delete item;
	}
	delete zisky_;
}

void System::testuj()
{
	bioFarmari_->vytvorBioFarmara("biofarmar_vsetko");
	bioFarmari_->vytvorBioFarmara("biofarmar_zemiakovy");
	bioFarmari_->vytvorBioFarmara("biofarmar_ochucovadlovy");
	bioFarmari_->vytvorBioFarmara("biofarmar_olejovy");
	bioFarmari_->vytvorBioFarmara("biofarmar_n");
	bioFarmari_->vytvorBioFarmara("biofarmar_l");
	bioFarmari_->vytvorBioFarmara("biofarmar_p");
	bioFarmari_->vytvorBioFarmara("biofarmar_c");
	bioFarmari_->vytvorBioFarmara("biofarmar_z");
	bioFarmari_->vytvorBioFarmara("biofarmar_a");
	bioFarmari_->vytvorBioFarmara("biofarmar_v");
	bioFarmari_->vytvorBioFarmara("biofarmar_m");
	bioFarmari_->vytvorBioFarmara("biofarmar_d");
	bioFarmari_->vytvorBioFarmara("biofarmar_w");
	bioFarmari_->vytvorBioFarmara("biofarmar_y");

	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_vsetko", Polotovar::Typ::ZEMIAKY);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_vsetko", Polotovar::Typ::OCHUCOVADLA);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_vsetko", Polotovar::Typ::OLEJ);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_ochucovadlovy", Polotovar::Typ::OCHUCOVADLA);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_zemiakovy", Polotovar::Typ::ZEMIAKY);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_olejovy", Polotovar::Typ::OLEJ);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_n", Polotovar::Typ::OCHUCOVADLA);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_l", Polotovar::Typ::ZEMIAKY);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_p", Polotovar::Typ::OLEJ);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_c", Polotovar::Typ::OCHUCOVADLA);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_z", Polotovar::Typ::ZEMIAKY);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_a", Polotovar::Typ::OLEJ);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_v", Polotovar::Typ::OCHUCOVADLA);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_m", Polotovar::Typ::ZEMIAKY);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_d", Polotovar::Typ::OLEJ);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_w", Polotovar::Typ::OCHUCOVADLA);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_y", Polotovar::Typ::ZEMIAKY);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_y", Polotovar::Typ::OLEJ);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_y", Polotovar::Typ::OCHUCOVADLA);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_w", Polotovar::Typ::ZEMIAKY);
	bioFarmari_->pridajProduktBioFarmarovi("biofarmar_w", Polotovar::Typ::OLEJ);

	vozidla_->vytvorNoveVozidlo("ZA-DFG34", Tovar::Typ::ZEM_LUPIENKY, *datum_);
	vozidla_->vytvorNoveVozidlo("ZA-008LP", Tovar::Typ::ZEM_HRANOLKY, *datum_);
	vozidla_->vytvorNoveVozidlo("ZA-048DD", Tovar::Typ::ZEM_HRANOLKY, *datum_);
	vozidla_->vytvorNoveVozidlo("ZA-347TR", Tovar::Typ::ZEM_LUPIENKY, *datum_);
	vozidla_->vytvorNoveVozidlo("ZA-355GG", Tovar::Typ::ZEM_LUPIENKY, *datum_);

	zakaznici_->vytvorZakaznika("zakaznik", 1);
	zakaznici_->vytvorZakaznika("zakaznik2", 3);
	zakaznici_->vytvorZakaznika("zakaznik4", 8);
	zakaznici_->vytvorZakaznika("zakaznik1", 5);
	zakaznici_->vytvorZakaznika("zakaznik0", 5);

	objednavkyTovaru_->vytvorNovuObjednavku(zakaznici_->dajZakaznika("zakaznik"), Tovar::Typ::ZEM_HRANOLKY, 850, 4, 9, vozidla_->dajKapacituVozidiel(Tovar::Typ::ZEM_HRANOLKY), *datum_);
	objednavkyTovaru_->vytvorNovuObjednavku(zakaznici_->dajZakaznika("zakaznik2"), Tovar::Typ::ZEM_HRANOLKY, 21, 2, 11, vozidla_->dajKapacituVozidiel(Tovar::Typ::ZEM_HRANOLKY), *datum_);
	objednavkyTovaru_->vytvorNovuObjednavku(zakaznici_->dajZakaznika("zakaznik4"), Tovar::Typ::ZEM_LUPIENKY, 10, 6, 12, vozidla_->dajKapacituVozidiel(Tovar::Typ::ZEM_LUPIENKY), *datum_);
	objednavkyTovaru_->vytvorNovuObjednavku(zakaznici_->dajZakaznika("zakaznik4"), Tovar::Typ::ZEM_LUPIENKY, 900, 3, 13, vozidla_->dajKapacituVozidiel(Tovar::Typ::ZEM_LUPIENKY), *datum_);
	objednavkyTovaru_->vytvorNovuObjednavku(zakaznici_->dajZakaznika("zakaznik0"), Tovar::Typ::ZEM_LUPIENKY, 200, 12, 16, vozidla_->dajKapacituVozidiel(Tovar::Typ::ZEM_LUPIENKY), *datum_);
	objednavkyTovaru_->vytvorNovuObjednavku(zakaznici_->dajZakaznika("zakaznik0"), Tovar::Typ::ZEM_LUPIENKY, 100, 12, 16, vozidla_->dajKapacituVozidiel(Tovar::Typ::ZEM_LUPIENKY), *datum_);
	objednavkyTovaru_->vytvorNovuObjednavku(zakaznici_->dajZakaznika("zakaznik0"), Tovar::Typ::ZEM_LUPIENKY, 1000, 12, 16, vozidla_->dajKapacituVozidiel(Tovar::Typ::ZEM_LUPIENKY), *datum_);
	objednavkyTovaru_->vytvorNovuObjednavku(zakaznici_->dajZakaznika("zakaznik1"), Tovar::Typ::ZEM_HRANOLKY, 60000, 1.654, 13, vozidla_->dajKapacituVozidiel(Tovar::Typ::ZEM_HRANOLKY), *datum_);
}

void System::dalsiDen()
{
	datum_->zvysDen();
	
	// Aktualizacia systemu
	cout << "\n*** Aktualny den: " << *datum_ << ". ***\n\n";
	bioFarmari_->aktualizuj();
	zasoby_->aktualizuj();

	// 7.
	double nakladyNaPolotovary = kontrolaPoziadaviek();

	// 8.
	kontrolaObjednavokNaNasledujuciDen();

	// 9. - 10.
	zrealizovanieDnesnychObjednavok(nakladyNaPolotovary);
}

double System::kontrolaPoziadaviek()
{
	double nakladyNaNakupPolotovarov = 0;

	// Prejde kazdy typ polotovaru
	for (int i = 0; i < Polotovar::pocetTypov; ++i)
	{
		Polotovar::Typ typPolotovaru = static_cast<Polotovar::Typ>(i);

		double potrebneMnozstvoPolotovaru = 0;
		// Prejde kazdy mozny typ vyrabaneho tovaru
		for (int j = 0; j < Tovar::pocetTypov; ++j)
		{
			Tovar::Typ typTovaru = static_cast<Tovar::Typ>(j);
			double jednotkoveMnozstvo = dajMnozstvoPolotovaruRecept(typPolotovaru, typTovaru);
			double celkoveMnozstvoTovaru = objednavkyTovaru_->dajPoziadavkyNaTovar(typTovaru, *datum_);
			potrebneMnozstvoPolotovaru += jednotkoveMnozstvo * celkoveMnozstvoTovaru;
		}

		// Zisti ci mam dostatok na sklade, ak nie tak objednam od farmarov
		double mnozstvoZasobyNaSklade = zasoby_->dajMnozstvoNaSklade(typPolotovaru);
		double deficitPolotovaru = potrebneMnozstvoPolotovaru - mnozstvoZasobyNaSklade;
		if (deficitPolotovaru > 0)
		{
			// Vytvorit arraylist farmarov do ktoreho si budem ukladat tych od ktorych som kupil a na konci
			// ich nahadzem do zoznamu podla cien
			structures::List<PriemernaCenaPolotovaru *> * uspesneOsloveniFarmari = new structures::LinkedList<PriemernaCenaPolotovaru *>();
			
			// Prechadzanie zoznamu farmarov a objednavanie, kym sa nevynuluje deficit alebo nedojdu farmari
			structures::List<PriemernaCenaPolotovaru *> * farmariPodlaPriemCien = bioFarmari_->dajFarmarovPodlaPriemCien();
			for (PriemernaCenaPolotovaru* const item : *farmariPodlaPriemCien)
			{
				if (deficitPolotovaru == 0)
				{
					break;
				}
				if (item->dajTypPolotovaru() == typPolotovaru)
				{
					double dodaneMnozstvo = item->dajBioFarmara()->predajPolotovar(item->dajTypPolotovaru(), deficitPolotovaru);
					if (dodaneMnozstvo > 0)
					{
						deficitPolotovaru -= dodaneMnozstvo;
						uspesneOsloveniFarmari->add(new PriemernaCenaPolotovaru(item->dajBioFarmara(), typPolotovaru, -1));
					
						// Prida dodanu zasobu do skladovej evidencie
						ObjednavkaPolotovaru * novaObjednavkaPolotovaru =
							new ObjednavkaPolotovaru(*datum_,
								item->dajBioFarmara(),
								typPolotovaru,
								dodaneMnozstvo,
								item->dajBioFarmara()->dajCenuPolotovaru(typPolotovaru));
						zasoby_->pridajObjednavkuPolotovaru(novaObjednavkaPolotovaru);

						// Celkove naklady na nakup polotovarov
						nakladyNaNakupPolotovarov += dodaneMnozstvo * item->dajBioFarmara()->dajCenuPolotovaru(typPolotovaru);
					}
				}
			}

			// Zoradi uspesne oslovenych farmarov podla nakupnych cien a uvolni pamat
			for (PriemernaCenaPolotovaru* const item : *uspesneOsloveniFarmari)
			{
				bioFarmari_->zoradPodlaPriemCien(item->dajBioFarmara(), item->dajTypPolotovaru());
				delete item;
			}
			delete uspesneOsloveniFarmari;
		}
	}

	return nakladyNaNakupPolotovarov;
}

void System::kontrolaObjednavokNaNasledujuciDen()
{
	structures::LinkedList<ObjednavkaTovaru *> * objednavkyNaNasledujuciDen = objednavkyTovaru_->dajObjednavkyPodlaTrzieb(*datum_ + 1);

	// Prechadza vsetky mozne polotovary
	for (int i = 0; i < Polotovar::pocetTypov; ++i)
	{
		Polotovar::Typ typPolotovaru = static_cast<Polotovar::Typ>(i);
		
		// Prechadza objednavky
		double pozadovaneMnozstvoPolotovaru = 0;
		for (ObjednavkaTovaru* const item : *objednavkyNaNasledujuciDen)
		{
			double jednotkoveMnozstvo = dajMnozstvoPolotovaruRecept(typPolotovaru, item->dajTypTovaru());
			pozadovaneMnozstvoPolotovaru += (jednotkoveMnozstvo * item->dajMnozstvo());
		}

		double mnozstvoNaSklade = zasoby_->dajMnozstvoNaSklade(typPolotovaru);
		double deficitPolotovaru = pozadovaneMnozstvoPolotovaru - mnozstvoNaSklade;

		// Ak mam nedostatok polotovaru, rusim objednavky dokym nemam dostatok
		if (deficitPolotovaru > 0)
		{
			for (ObjednavkaTovaru* const item : *objednavkyNaNasledujuciDen)
			{
				if (deficitPolotovaru <= 0)
				{
					break;
				}

				item->zmenStav(StavObjednavky::ZRUSENA);
				double jednotkoveMnozstvo = dajMnozstvoPolotovaruRecept(typPolotovaru, item->dajTypTovaru());
				pozadovaneMnozstvoPolotovaru -= item->dajMnozstvo();
				deficitPolotovaru = pozadovaneMnozstvoPolotovaru - mnozstvoNaSklade;
			}
		}
		// Odoberie potrebne mnozstvo polotovaru z skladu
		if (!zasoby_->odoberZasobu(typPolotovaru, pozadovaneMnozstvoPolotovaru))
		{
			showErrorMessage("Nedostatocna zasoba na sklade!");
		}
	}

	delete objednavkyNaNasledujuciDen;
}

void System::zrealizovanieDnesnychObjednavok(double nakladyNaPolotovary)
{
	// Zostavi optimalne rozlozenie objednavok do vozidiel
	double prevadzkoveNakladyVozidiel = vozidla_->naplnVozidla(objednavkyTovaru_->dajObjednavkyPodlaRegionov(*datum_));
	
	// Oznaci objednavky ako zrealizovane
	double cenaObjednavokTovaru = objednavkyTovaru_->zrealizujObjednavkyDna(*datum_);

	// Zaeviduje zisk
	zaevidujDnesnyZisk(cenaObjednavokTovaru, nakladyNaPolotovary, prevadzkoveNakladyVozidiel);
}

void System::zaevidujDnesnyZisk(double cenaObjednavokTovaru, double cenaObjednavokPolotovarov,
	double prevadzkoveNakladyVozidiel)
{
	Zisk * dnesnyZisk = new Zisk(cenaObjednavokTovaru, cenaObjednavokPolotovarov, prevadzkoveNakladyVozidiel);
	if (*datum_ < zisky_->size() && (*zisky_)[*datum_] != nullptr)
	{
		delete (*zisky_)[*datum_];
	}
	zisky_->insert(dnesnyZisk, *datum_);
}

void System::vypisZakaznikov(size_t region, Datum datumOd, Datum datumDo)
{
	structures::List<Zakaznik *> * zakaznici = zakaznici_->dajZakaznikov(region);

	cout << "\nZAKAZNICI Z REGIONU " << region << ":\n\n";
	for (Zakaznik* const zakaznik : *zakaznici)
	{
		structures::List<ObjednavkaTovaru *> * vsetkyObjednavky = objednavkyTovaru_->dajObjednavky();

		double celkovyPrijem = 0;

		int zruseneCelkovyPocet = 0;
		double zruseneCelkovaHmotnost = 0;
		double zruseneCelkoveTrzby = 0;

		int zamietnuteCelkovyPocet = 0;
		double zamietnuteCelkovaHmotnost = 0;
		double zamietnuteCelkoveTrzby = 0;

		// Prechadza vsetky objednavky daneho zakaznika
		for (ObjednavkaTovaru* const objednavka : *vsetkyObjednavky)
		{
			// Objednavky daneho zakaznika len zo zadaneho obdobia
			if (objednavka->dajZakaznika() == zakaznik && objednavka->dajDatumZaevidovania() >= datumOd && objednavka->dajDatumDorucenia() <= datumDo)
			{
				double trzbyZObjednavky = objednavka->dajJednotkovuPredajnuCenu() * objednavka->dajMnozstvo();

				switch (objednavka->dajStav())
				{
				case StavObjednavky::ZREALIZOVANA:
					celkovyPrijem += trzbyZObjednavky;
					break;

				case StavObjednavky::ZRUSENA:
					zruseneCelkovyPocet++;
					zruseneCelkovaHmotnost += objednavka->dajMnozstvo();
					zruseneCelkoveTrzby += trzbyZObjednavky;
					break;

				case StavObjednavky::ZAMIETNUTA:
					zamietnuteCelkovyPocet++;
					zamietnuteCelkovaHmotnost += objednavka->dajMnozstvo();
					zamietnuteCelkoveTrzby += trzbyZObjednavky;
				}
			}
		}

		// Vypis zakaznika
		cout << "Zakaznik: " << zakaznik->dajNazov() << endl;
		cout << "Objednavky zakaznika v obdobi od " << datumOd << ". do " << datumDo << ".:\n";
		cout << "Zrusene objednavky: " << zruseneCelkovyPocet << endl;
		cout << "Zrusene objednavky - celkova hmotnost: " << zruseneCelkovaHmotnost << endl;
		cout << "Zrusene objednavky - celkove trzby: " << zruseneCelkoveTrzby << endl;

		cout << "Zamietnute objednavky: " << zamietnuteCelkovyPocet << endl;
		cout << "Zamietnute objednavky - celkova hmotnost: " << zamietnuteCelkovaHmotnost << endl;
		cout << "Zamietnute objednavky - celkove trzby: " << zamietnuteCelkoveTrzby << endl;

		cout << "\n";
	}
	delete zakaznici;
}

void System::vypisNajuzitocnejsiehoFarmara(Polotovar::Typ typPolotovaru, Datum datumOd, Datum datumDo)
{
	structures::List<BioFarmar *> * farmari = bioFarmari_->dajFarmarovPodlaAbecedy();
	
	BioFarmar * aktualneNajlepsiFarmar = nullptr;
	double najlepsieCelkoveMnozstvo = 0;
	double celkovaCena = 0;

	// Prechadza vsetkych farmarov
	for (BioFarmar* const farmar : *farmari)
	{
		// Prechadza vsetky objednavky polotovarov a zisti celkove nakupene mnozstvo daneho polotovaru od aktualneho farmara za dane casove obdobie
		double mnozstvo = 0;
		double cena = 0;
		structures::List<ObjednavkaPolotovaru *> * objednavkyPolotovarov = zasoby_->dajObjednavkyPolotovarov();
		for (ObjednavkaPolotovaru* const objednavka : *objednavkyPolotovarov)
		{
			if (objednavka->dajDatumObjednania() >= datumOd && objednavka->dajDatumObjednania() <= datumDo && objednavka->dajDodavatela() == farmar && objednavka->dajTypPolotovaru() == typPolotovaru)
			{
				mnozstvo += objednavka->dajMnozstvo();
				cena += objednavka->dajMnozstvo() * objednavka->dajJednotkovuNakupnuCenu();
			}
		}

		// Zisti ci sa nasiel lepsi farmar
		if (mnozstvo > najlepsieCelkoveMnozstvo)
		{
			aktualneNajlepsiFarmar = farmar;
			najlepsieCelkoveMnozstvo = mnozstvo;
			celkovaCena = cena;
		}
	}

	// Vypis
	if (aktualneNajlepsiFarmar != nullptr)
	{
		string nazovPolotovaru = Polotovar::toString(typPolotovaru);
		for (char c : nazovPolotovaru) { c = toupper(c); }	// Konverzia na velke pismena

		cout << "\nNAJUZITOCNEJSI FARMAR PRE " << nazovPolotovaru << ":\n\n";
		cout << "Farmar: " << aktualneNajlepsiFarmar->dajNazov() << endl;
		cout << "Celkove mnozstvo zakupeneho polotovaru: " << najlepsieCelkoveMnozstvo << " Kg\n";
		cout << "Celkova cena zakupeneho polotovaru: " << celkovaCena << " Eur\n";
		cout << "Priemerna cena: " << (celkovaCena / najlepsieCelkoveMnozstvo) << " Eur/Kg\n";

		cout << "\n";
	}
	else
	{
		cout << "\nNajuzitocnejsieho farmara sa nepodarilo najst.\n\n";
	}
}

void System::vypisZiskFirmy(Datum datumOd, Datum datumDo)
{
	// Ak prekracuje dnesny datum
	if (datumDo > *datum_)
	{
		datumDo = *datum_;
	}

	// Hranice datumu
	if (datumOd > 0 && datumDo > datumOd)
	{
		double cenaObjednavokTovaru = 0;
		double cenaObjednavokPolotovarov = 0;
		double prevadzkoveNakladyVozidiel = 0;

		for (int i = datumOd; i < datumDo + 1; ++i)
		{
			Zisk * item = (*zisky_)[i];
			if (item != nullptr)
			{
				cenaObjednavokTovaru += item->dajCenuObjednavokTovaru();
				cenaObjednavokPolotovarov += item->dajCenuObjednavokPolotovarov();
				prevadzkoveNakladyVozidiel += item->dajPrevadzkoveNakladyVozidiel();
			}
			else { showErrorMessage("Trying to reach nullptr!"); }
		}

		// Vypis
		cout << "\nSTATISTIKY FIRMY PRE OBDOBIE OD " << datumOd << ". DO " << datumDo << ". :\n\n";
		cout << "Suma cien zrealizovanych objednavok: " << cenaObjednavokTovaru << " Eur\n";
		cout << "Suma nakladov na polotovary: " << cenaObjednavokPolotovarov << " Eur\n";
		cout << "Suma nakladov na prevadzku vozidiel: " << prevadzkoveNakladyVozidiel << " Eur\n";
		cout << "Celkovy zisk za obdobie: " << (cenaObjednavokTovaru - cenaObjednavokPolotovarov - prevadzkoveNakladyVozidiel) << " Eur\n";

		cout << "\n";
	}
	else
	{
		showErrorMessage("Zadane neplatne casove obdobie!");
	}
}

void System::aktualizuj()
{
	// 2.
	//bioFarmari_->vypisBioFarmarovPodlaPolotovaru(Polotovar::Typ::OCHUCOVADLA);

	// 4.
	//vozidla_->vypisVozidiel();

	// 8.
	//objednavkyTovaru_->vypisObjednavok(*datum_ + 1);

	// 11.
	//vypisZakaznikov(5, 1, *datum_);
	//vypisZakaznikov(8, 1, *datum_);

	// 12.
	//objednavkyTovaru_->vypisZrealizovanychObjednavok(1, *datum_);

	// 13.
	//objednavkyTovaru_->vypisNezrealizovanychObjednavok(1, *datum_);

	// 14.
	//vypisNajuzitocnejsiehoFarmara(Polotovar::Typ::ZEMIAKY, *datum_ - 30, *datum_);

	// 15.
	//vypisZiskFirmy(1, *datum_);
}
